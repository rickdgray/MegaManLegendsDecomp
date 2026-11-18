// Hybrid execution of the overlays.
//
// Stage, special-weapon and support code is loaded from the disc into RAM (0x80100000,
// 0x800D8800, 0x801D8000) as MIPS code, and most of it has no C yet. The port runs it on the
// R3000 interpreter (mips_cpu.c):
//
// - Native code calling into an overlay (a routine table, a callback in a work area) makes an
//   ordinary x86 call to the MIPS address. The RAM window is executable only in the pages that
//   hold the jump stubs of ROCK_NEO.EXE's native functions; everywhere else it is not, so the
//   call faults. The SIGSEGV handler sees the faulting instruction pointer equal to the fault
//   address inside PS1 memory, and resumes at port_overlay_entry with the target in eax; that
//   trampoline hands the target and the caller's cdecl arguments to the interpreter and returns
//   v0 (edx = v1) to the caller as if the MIPS function had been native.
// - Interpreted code calling ROCK_NEO.EXE (its functions all native) goes through the stub table:
//   mips_cpu.c calls the native function with a0-a3 and the stack arguments.
// - Overlay functions compiled natively (port/overlays.cmake): port_overlay_native_table lists
//   (address, size, hash of the retail bytes, function); the hash tells which overlay is loaded
//   at that address, since the stage overlays share one. Both directions consult it before
//   interpreting (below).
#define _GNU_SOURCE
#include "mips_cpu.h"
#include "overlay_native.h"
#include "psx_mem.h"
#include "port_stubs.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <ucontext.h>

// --- native overlay functions -----------------------------------------------------------------
//
// port/overlays.cmake compiles the overlay C natively, one module per overlay target, and
// port/tools/gen_ovl_table.py lists every native function with its retail address and a hash of
// its retail bytes (overlay_native.h). The stage overlays share 0x80100000 (and the weapons
// 0x800D8800), so the address alone does not say which module is loaded: a candidate is used
// only when the bytes in RAM hash to the entry's value. Identical bytes mean identical code.
//
// Lookups run on every jump the interpreter takes, so a bitmap of the entry addresses rejects
// the rest first. PORT_OVERLAY_NATIVE=0 in the environment disables the table (everything
// interpreted, for comparisons). The table is weak: a program linked without it just has none.
extern const PORT_OVERLAY_NATIVE port_overlay_native_table[] __attribute__((weak));
extern const int port_overlay_native_count __attribute__((weak));
extern const PORT_OVL_RANGE port_overlay_ranges[] __attribute__((weak));
extern const char *const port_overlay_modules[] __attribute__((weak));
extern const uint32_t port_overlay_native_lo __attribute__((weak));
extern const uint32_t port_overlay_native_hi __attribute__((weak));

static int native_ready;     // the bitmap is built and the table enabled
static uint8_t *native_map;  // one bit per word in [lo, hi): an entry starts there
static uint32_t native_lo, native_hi;
static uint64_t entries;     // native-to-MIPS entries (the trap)
static uint64_t native_calls_mips;   // calls from interpreted code that ran natively
static uint64_t native_calls_trap;   // calls through a retail overlay address from native code
static uint64_t native_rejects;      // candidates whose bytes did not match (another module)
static uint32_t last_hit;            // see port_overlay_native_find
static uint64_t module_calls[256];   // native calls per module
static uint64_t module_rejects[256]; // its candidates rejected (another module loaded)

static uint64_t hash_ranges(const PORT_OVL_RANGE *r, int n)
{
    uint64_t h = 0xCBF29CE484222325ull;
    int i;

    for (; n > 0; n--, r++)
    {
        const uint32_t *w = (const uint32_t *)psx_ptr(r->addr);

        for (i = 0; i < (int)(r->size >> 2); i++)
        {
            h = (h ^ w[i]) * 0x100000001B3ull;
        }
    }
    return h;
}

static void native_init(void)
{
    const char *env = getenv("PORT_OVERLAY_NATIVE");
    int i;

    if (&port_overlay_native_count == NULL || port_overlay_native_count == 0 ||
        (env != NULL && strcmp(env, "0") == 0))
    {
        return;
    }
    native_lo  = port_overlay_native_lo;
    native_hi  = port_overlay_native_hi;
    native_map = calloc(((native_hi - native_lo) >> 5) + 1, 1);
    if (native_map == NULL)
    {
        return;
    }
    for (i = 0; i < port_overlay_native_count; i++)
    {
        uint32_t w = (port_overlay_native_table[i].addr - native_lo) >> 2;

        native_map[w >> 3] |= (uint8_t)(1u << (w & 7));
    }
    native_ready = 1;
}

// The entry for `addr` whose bytes are in RAM now, or NULL.
static const PORT_OVERLAY_NATIVE *native_lookup(uint32_t addr)
{
    const PORT_OVERLAY_NATIVE *e;
    uint32_t w;
    uint64_t h = 0;
    uint32_t hsize = 0;
    int lo, hi;

    if (!native_ready || addr < native_lo || addr >= native_hi)
    {
        return NULL;
    }
    w = (addr - native_lo) >> 2;
    if (!(native_map[w >> 3] & (1u << (w & 7))))
    {
        return NULL;
    }
    lo = 0;
    hi = port_overlay_native_count;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;

        if (port_overlay_native_table[mid].addr < addr)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid;
        }
    }
    for (e = &port_overlay_native_table[lo];
         e < &port_overlay_native_table[port_overlay_native_count] && e->addr == addr; e++)
    {
        const PORT_OVL_RANGE *r = &port_overlay_ranges[e->range];

        // Candidates at one address often have the same size: hash the function once.
        if (e->ranges == 1)
        {
            if (hsize != e->size)
            {
                h     = hash_ranges(r, 1);
                hsize = e->size;
            }
            if (h == e->hash)
            {
                return e;
            }
        }
        else if (hash_ranges(r, e->ranges) == e->hash)
        {
            return e;
        }
        native_rejects++;
        module_rejects[e->module & 0xFF]++;
    }
    return NULL;
}

// For the interpreter (mips_cpu.c): the native code for an overlay address, or NULL. The
// interpreter looks a call up twice, when the jump is taken and when the delay slot has run;
// the second lookup of the same address right after a hit is not counted as another call.
void *port_overlay_native_find(uint32_t addr)
{
    const PORT_OVERLAY_NATIVE *e = native_lookup(addr);

    if (e == NULL)
    {
        last_hit = 0;
        return NULL;
    }
    if (last_hit == addr)
    {
        last_hit = 0;
    }
    else
    {
        last_hit = addr;
        native_calls_mips++;
        module_calls[e->module & 0xFF]++;
    }
    return e->native;
}

// Called by port_overlay_entry: `args` points at the caller's cdecl arguments.
uint64_t port_overlay_call(uint32_t target, const uint32_t *args)
{
    const PORT_OVERLAY_NATIVE *e = native_lookup(target);

    if (e != NULL)
    {
        native_calls_trap++;
        module_calls[e->module & 0xFF]++;
        return ((uint64_t(*)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                             uint32_t, uint32_t, uint32_t, uint32_t))e->native)(
            args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8],
            args[9]);
    }
    entries++;
    return mips_call64(target, args);
}

uint64_t port_overlay_entries(void)
{
    return entries;
}

void port_overlay_print_stats(void)
{
    int i;

    fprintf(stderr,
            "port: overlays: %d native functions in the table%s; %llu calls ran natively (%llu "
            "from interpreted code, %llu through overlay addresses), %llu candidates rejected; "
            "%llu interpreter entries, %llu MIPS instructions\n",
            &port_overlay_native_count != NULL ? port_overlay_native_count : 0,
            native_ready ? "" : " (disabled)",
            (unsigned long long)(native_calls_mips + native_calls_trap),
            (unsigned long long)native_calls_mips, (unsigned long long)native_calls_trap,
            (unsigned long long)native_rejects, (unsigned long long)entries,
            (unsigned long long)mips_cpu_steps());
    for (i = 0; i < 256; i++)
    {
        if (module_calls[i] != 0)
        {
            fprintf(stderr, "port: overlays: %s: %llu native calls, %llu candidates rejected\n",
                    port_overlay_modules[i], (unsigned long long)module_calls[i],
                    (unsigned long long)module_rejects[i]);
        }
    }
}

// The trampoline: entered in place of the faulting call, with the stack as the caller left it
// ([esp] = return address, arguments above) and the MIPS target in eax.
__asm__(".text\n"
        ".globl port_overlay_entry\n"
        ".type port_overlay_entry, @function\n"
        "port_overlay_entry:\n"
        "    leal 4(%esp), %ecx\n"
        "    subl $4, %esp\n" // keep the 16-byte alignment the callee expects
        "    pushl %ecx\n"
        "    pushl %eax\n"
        "    call port_overlay_call\n"
        "    addl $12, %esp\n"
        "    ret\n"
        ".size port_overlay_entry, .-port_overlay_entry\n");
void port_overlay_entry(void);

static int in_psx_memory(uint32_t a)
{
    return (a >= PSX_RAM_BASE && a < PSX_RAM_BASE + PSX_RAM_WINDOW) ||
           (a >= PSX_KUSEG_MIRROR && a < PSX_RAM_WINDOW) ||
           (a >= PSX_SCRATCH_BASE && a < PSX_SCRATCH_BASE + PSX_SCRATCH_PAGE);
}

// The kernel area: native game code reading through a null record pointer.
//
// On the console KUSEG 0x0000-0xFFFF is the BIOS kernel's RAM, and retail code reads it through
// null pointers without harm (func_80027BE0 loads the first face of a mesh before testing its
// face count, and the mesh may have none). The process can't map those addresses
// (vm.mmap_min_addr), so the fault handler finishes the access itself: it decodes the x86 load
// or store (the forms GCC emits for plain memory moves), reads or writes the KSEG0 view of the
// same RAM, and resumes after the instruction. Returns 0 when it did, -1 for an unknown form.
static int modrm_length(const uint8_t *p)
{
    int mod = p[0] >> 6, rm = p[0] & 7, n = 1;

    if (mod != 3 && rm == 4)
    {
        n++; // SIB
        if (mod == 0 && (p[1] & 7) == 5)
        {
            n += 4;
        }
    }
    if (mod == 0 && rm == 5)
    {
        n += 4;
    }
    else if (mod == 1)
    {
        n += 1;
    }
    else if (mod == 2)
    {
        n += 4;
    }
    return n;
}

static const int greg_of[8] = {REG_EAX, REG_ECX, REG_EDX, REG_EBX,
                               REG_ESP, REG_EBP, REG_ESI, REG_EDI};

// The arithmetic flags (CF, PF, AF, ZF, SF, OF), and the ALU operations the fault handler
// performs on a memory operand. Each is done by the CPU itself, so the result and flags are
// exactly what the faulting instruction would have produced.
#define ARITH_FLAGS 0x8D5u

enum
{
    ALU_ADD,
    ALU_OR,
    ALU_ADC,
    ALU_SBB,
    ALU_AND,
    ALU_SUB,
    ALU_XOR,
    ALU_CMP,
    ALU_TEST,
    ALU_INC,
    ALU_DEC,
    ALU_NOT,
    ALU_NEG
};

#define ALU2(insn, sfx, cons)                                                                    \
    __asm__("push %3\n\tpopfl\n\t" insn sfx " %2, %0\n\tpushfl\n\tpopl %1"                         \
            : "+" cons(r), "=&r"(f)                                                              \
            : cons(src), "r"(in_flags)                                                           \
            : "cc")
#define ALU1(insn, sfx, cons)                                                                    \
    __asm__("push %2\n\tpopfl\n\t" insn sfx " %0\n\tpushfl\n\tpopl %1"                             \
            : "+" cons(r), "=&r"(f)                                                              \
            : "r"(in_flags)                                                                      \
            : "cc")

#define ALU_CASES(sfx, cons)                                                                     \
    switch (op)                                                                                  \
    {                                                                                            \
        case ALU_ADD: ALU2("add", sfx, cons); break;                                             \
        case ALU_OR: ALU2("or", sfx, cons); break;                                               \
        case ALU_ADC: ALU2("adc", sfx, cons); break;                                             \
        case ALU_SBB: ALU2("sbb", sfx, cons); break;                                             \
        case ALU_AND: ALU2("and", sfx, cons); break;                                             \
        case ALU_SUB: ALU2("sub", sfx, cons); break;                                             \
        case ALU_XOR: ALU2("xor", sfx, cons); break;                                             \
        case ALU_CMP: ALU2("cmp", sfx, cons); break;                                             \
        case ALU_TEST: ALU2("test", sfx, cons); break;                                           \
        case ALU_INC: ALU1("inc", sfx, cons); break;                                             \
        case ALU_DEC: ALU1("dec", sfx, cons); break;                                             \
        case ALU_NOT: ALU1("not", sfx, cons); break;                                             \
        case ALU_NEG: ALU1("neg", sfx, cons); break;                                             \
    }

// dst op= src at one operand size; returns the result and sets *flags (all of EFLAGS after the
// operation, starting from in_flags so adc/sbb see the carry and inc/dec keep it).
static uint32_t alu(int op, int size, uint32_t dst, uint32_t src, uint32_t in_flags, uint32_t *flags)
{
    uint32_t f = in_flags;

    if (size == 1)
    {
        uint8_t r = (uint8_t)dst;
        uint8_t s8 = (uint8_t)src;
#define src s8
        ALU_CASES("b", "q")
#undef src
        *flags = f;
        return r;
    }
    if (size == 2)
    {
        uint16_t r = (uint16_t)dst;
        uint16_t s16 = (uint16_t)src;
#define src s16
        ALU_CASES("w", "r")
#undef src
        *flags = f;
        return r;
    }
    {
        uint32_t r = dst;
        ALU_CASES("l", "r")
        *flags = f;
        return r;
    }
}

static uint32_t read_sized(const uint8_t *mem, int size)
{
    return size == 1 ? mem[0] : size == 2 ? *(const uint16_t *)mem : *(const uint32_t *)mem;
}

static void write_sized(uint8_t *mem, int size, uint32_t v)
{
    if (size == 1)
    {
        mem[0] = (uint8_t)v;
    }
    else if (size == 2)
    {
        *(uint16_t *)mem = (uint16_t)v;
    }
    else
    {
        *(uint32_t *)mem = v;
    }
}

// A register operand of the given size (8-bit: AL..BL, then AH..BH).
static uint32_t reg_sized(const greg_t *g, int reg, int size)
{
    if (size == 1)
    {
        return reg < 4 ? (uint32_t)g[greg_of[reg]] & 0xFF : ((uint32_t)g[greg_of[reg - 4]] >> 8) & 0xFF;
    }
    return size == 2 ? (uint32_t)g[greg_of[reg]] & 0xFFFF : (uint32_t)g[greg_of[reg]];
}

static void set_reg_sized(greg_t *g, int reg, int size, uint32_t v)
{
    if (size == 1)
    {
        if (reg < 4)
        {
            g[greg_of[reg]] = (g[greg_of[reg]] & ~0xFF) | (v & 0xFF);
        }
        else
        {
            g[greg_of[reg - 4]] = (g[greg_of[reg - 4]] & ~0xFF00) | ((v & 0xFF) << 8);
        }
    }
    else if (size == 2)
    {
        g[greg_of[reg]] = (g[greg_of[reg]] & ~0xFFFF) | (v & 0xFFFF);
    }
    else
    {
        g[greg_of[reg]] = (greg_t)v;
    }
}

// ALU instructions with a memory operand (GCC compares and updates fields in place:
// `cmp %ax,(%edx,%ecx,2)` in func_80019C20, `andb $0xfd,(%eax)` in st1b func_80101724).
// Covers add/or/adc/sbb/and/sub/xor/cmp in their m,r / r,m / m,imm forms, test m,r and m,imm,
// and inc/dec/not/neg m. Updates the destination (unless cmp/test) and the flags.
// Returns the instruction length, or -1 for a form it doesn't know.
static int emulate_low_alu(greg_t *g, const uint8_t *p, int opsize16, uint8_t *mem)
{
    int wsize = opsize16 ? 2 : 4, reg = (p[1] >> 3) & 7, len = 1 + modrm_length(p + 1);
    int op, size, to_reg = 0, writes;
    uint32_t dst, src = 0, res, f;

    if (p[0] < 0x40 && (p[0] & 7) < 4) // the 00-3F block: op m8,r8 / m,r / r8,m8 / r,m
    {
        op     = p[0] >> 3;
        size   = (p[0] & 1) ? wsize : 1;
        to_reg = (p[0] & 2) != 0;
        if (to_reg)
        {
            dst = reg_sized(g, reg, size);
            src = read_sized(mem, size);
        }
        else
        {
            dst = read_sized(mem, size);
            src = reg_sized(g, reg, size);
        }
    }
    else
    {
        switch (p[0])
        {
            case 0x80: // op m8, imm8
                op = reg, size = 1, dst = mem[0], src = p[len], len += 1;
                break;
            case 0x81: // op m, imm16/32
                op = reg, size = wsize, dst = read_sized(mem, size);
                src = size == 2 ? *(const uint16_t *)(p + len) : *(const uint32_t *)(p + len);
                len += size;
                break;
            case 0x83: // op m, imm8 sign-extended
                op = reg, size = wsize, dst = read_sized(mem, size);
                src = (uint32_t)(int32_t)(int8_t)p[len];
                len += 1;
                break;
            case 0x84: // test m8, r8
            case 0x85: // test m, r
                op = ALU_TEST, size = p[0] == 0x84 ? 1 : wsize;
                dst = read_sized(mem, size), src = reg_sized(g, reg, size);
                break;
            case 0xF6: // test/not/neg m8
            case 0xF7: // test/not/neg m
                size = p[0] == 0xF6 ? 1 : wsize;
                dst  = read_sized(mem, size);
                if (reg == 0)
                {
                    op  = ALU_TEST;
                    src = size == 1 ? p[len] : size == 2 ? *(const uint16_t *)(p + len) : *(const uint32_t *)(p + len);
                    len += size;
                }
                else if (reg == 2 || reg == 3)
                {
                    op = reg == 2 ? ALU_NOT : ALU_NEG;
                }
                else
                {
                    return -1; // mul/div through a null pointer: not seen
                }
                break;
            case 0xFE: // inc/dec m8
            case 0xFF: // inc/dec m (push m32 is handled by the caller)
                if (reg > 1)
                {
                    return -1;
                }
                op = reg == 0 ? ALU_INC : ALU_DEC, size = p[0] == 0xFE ? 1 : wsize;
                dst = read_sized(mem, size);
                break;
            default:
                return -1;
        }
    }
    res    = alu(op, size, dst, src, (uint32_t)g[REG_EFL], &f);
    writes = op != ALU_CMP && op != ALU_TEST;
    if (writes)
    {
        if (to_reg)
        {
            set_reg_sized(g, reg, size, res);
        }
        else
        {
            write_sized(mem, size, res);
        }
    }
    g[REG_EFL] = (greg_t)(((uint32_t)g[REG_EFL] & ~ARITH_FLAGS) | (f & ARITH_FLAGS));
    return len;
}

static int emulate_low_access(ucontext_t *uc, uint32_t addr)
{
    const uint8_t *p = (const uint8_t *)(uintptr_t)uc->uc_mcontext.gregs[REG_EIP];
    uint8_t *mem     = (uint8_t *)(uintptr_t)(PSX_RAM_BASE | addr);
    greg_t *g        = uc->uc_mcontext.gregs;
    int opsize16     = 0, len, reg;
    uint32_t v;

    if (*p == 0x66)
    {
        opsize16 = 1;
        p++;
    }
    reg = (p[1] >> 3) & 7;
    switch (p[0])
    {
        case 0x8B: // mov r32/r16, m
            len = 1 + modrm_length(p + 1);
            if (opsize16)
            {
                g[greg_of[reg]] = (g[greg_of[reg]] & ~0xFFFF) | *(uint16_t *)mem;
            }
            else
            {
                g[greg_of[reg]] = (greg_t) * (uint32_t *)mem;
            }
            break;
        case 0x8A: // mov r8, m
            len = 1 + modrm_length(p + 1);
            if (reg < 4)
            {
                g[greg_of[reg]] = (g[greg_of[reg]] & ~0xFF) | mem[0];
            }
            else
            {
                g[greg_of[reg - 4]] = (g[greg_of[reg - 4]] & ~0xFF00) | (mem[0] << 8);
            }
            break;
        case 0x89: // mov m, r32/r16
            len = 1 + modrm_length(p + 1);
            v   = (uint32_t)g[greg_of[reg]];
            if (opsize16)
            {
                *(uint16_t *)mem = (uint16_t)v;
            }
            else
            {
                *(uint32_t *)mem = v;
            }
            break;
        case 0x88: // mov m, r8
            len    = 1 + modrm_length(p + 1);
            v      = (uint32_t)g[greg_of[reg & 3]];
            mem[0] = (uint8_t)(reg < 4 ? v : v >> 8);
            break;
        case 0xFF: // push m32 (/6): an argument read through a null pointer; inc/dec m below
            if (reg != 6 || opsize16)
            {
                len = emulate_low_alu(g, p, opsize16, mem);
                if (len < 0)
                {
                    return -1;
                }
                break;
            }
            len = 1 + modrm_length(p + 1);
            v   = *(uint32_t *)mem;
            g[REG_ESP] -= 4;
            *(uint32_t *)(uintptr_t)g[REG_ESP] = v;
            break;
        case 0x0F:
            reg = (p[2] >> 3) & 7;
            len = 2 + modrm_length(p + 2);
            switch (p[1])
            {
                case 0xB6:
                    v = mem[0];
                    break;
                case 0xB7:
                    v = *(uint16_t *)mem;
                    break;
                case 0xBE:
                    v = (uint32_t)(int32_t)(int8_t)mem[0];
                    break;
                case 0xBF:
                    v = (uint32_t)(int32_t) * (int16_t *)mem;
                    break;
                default:
                    return -1;
            }
            g[greg_of[reg]] = (greg_t)v;
            break;
        default:
            len = emulate_low_alu(g, p, opsize16, mem);
            if (len < 0)
            {
                return -1;
            }
            break;
    }
    g[REG_EIP] = (greg_t)((uintptr_t)p + len);
    return 0;
}

static void on_segv(int sig, siginfo_t *si, void *ctx)
{
    ucontext_t *uc = ctx;
    uint32_t eip   = (uint32_t)uc->uc_mcontext.gregs[REG_EIP];

    if (eip == (uint32_t)(uintptr_t)si->si_addr && in_psx_memory(eip))
    {
        // KUSEG addresses run as their KSEG0 view.
        uc->uc_mcontext.gregs[REG_EAX] = (greg_t)(eip < PSX_RAM_WINDOW ? eip | PSX_RAM_BASE : eip);
        uc->uc_mcontext.gregs[REG_EIP] = (greg_t)(uintptr_t)port_overlay_entry;
        return;
    }
    if ((uint32_t)(uintptr_t)si->si_addr < PSX_KUSEG_MIRROR &&
        emulate_low_access(uc, (uint32_t)(uintptr_t)si->si_addr) == 0)
    {
        static int told;

        if (!told++)
        {
            fprintf(stderr, "port: access to kernel RAM at 0x%04X from 0x%08X (a null pointer; "
                            "emulated, further ones silent)\n",
                    (unsigned)(uintptr_t)si->si_addr, eip);
        }
        return;
    }
    // A real fault: report it and abort (a debugger then shows the faulting frame).
    fprintf(stderr, "port: segmentation fault at %p (eip 0x%08X)\n", si->si_addr, eip);
    abort();
}

// Makes PS1 memory non-executable except [exec_lo, exec_hi) (the stub pages), and installs the
// handler that turns calls into it into interpreter entries.
int port_overlay_init(void)
{
    struct sigaction sa;
    uint32_t lo = port_stub_table[0].addr & ~0xFFFu;
    uint32_t hi = (port_stub_table[port_stub_count - 1].addr + 0x1000u) & ~0xFFFu;

    if (mprotect((void *)(uintptr_t)PSX_RAM_BASE, lo - PSX_RAM_BASE, PROT_READ | PROT_WRITE) != 0 ||
        mprotect((void *)(uintptr_t)hi, PSX_RAM_BASE + PSX_RAM_WINDOW - hi,
                 PROT_READ | PROT_WRITE) != 0 ||
        mprotect((void *)(uintptr_t)PSX_SCRATCH_BASE, PSX_SCRATCH_PAGE, PROT_READ | PROT_WRITE) != 0)
    {
        perror("port_overlay_init: mprotect");
        return -1;
    }
    mprotect((void *)(uintptr_t)PSX_KUSEG_MIRROR, PSX_RAM_WINDOW - PSX_KUSEG_MIRROR,
             PROT_READ | PROT_WRITE);
    native_init();
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = on_segv;
    sa.sa_flags     = SA_SIGINFO | SA_NODEFER;
    sigemptyset(&sa.sa_mask);
    return sigaction(SIGSEGV, &sa, NULL);
}
