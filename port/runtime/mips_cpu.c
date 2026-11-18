// R3000A interpreter for retail library routines. See mips_cpu.h.
#include "mips_cpu.h"

#include "gte.h"
#include "port_game.h"
#include "port_stubs.h"
#include "psx_io.h"
#include "psx_mem.h"

#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Return address that ends a call: no MIPS code lives in the first page.
#define RETURN_SENTINEL 0x00000BADu
#define STACK_BYTES     0x8000 // MIPS stack for each entry into the interpreter

typedef struct
{
    uint32_t r[32];
    uint32_t hi, lo;
    uint32_t pc, next_pc;
    uint32_t at;     // address of the instruction being executed, for messages and links
    uint32_t native; // a jump to native code is pending: its target (0 = none)
} CPU;

static uint64_t steps;
static uint32_t cop0[32];
uint32_t mips_gp; // gp for MIPS code: ROCK_NEO.EXE's (small data), set at load

uint64_t mips_cpu_steps(void)
{
    return steps;
}

// The process is 32-bit and maps PS1 memory at its own addresses, so a MIPS address is a host
// address.
#define MEM8(a)  (*(uint8_t *)(uintptr_t)(a))
#define MEM16(a) (*(uint16_t *)(uintptr_t)(a))
#define MEM32(a) (*(uint32_t *)(uintptr_t)(a))

static void fatal(const CPU *c, uint32_t insn, const char *what)
{
    fprintf(stderr, "mips_cpu: %s at 0x%08X (instruction 0x%08X)\n", what, c->at, insn);
    abort();
}

// Returns the host address for a load or store at `ea`. KUSEG addresses below 64 KB (the kernel
// area, which the process can't map there) and KSEG1 addresses use the KSEG0 view of RAM; on the
// console a read through a null pointer returns kernel data rather than faulting, and some
// overlay code relies on it.
static uint32_t check_address(const CPU *c, uint32_t insn, uint32_t ea)
{
    // The hardware registers (0x1F801000.., and their KSEG0/KSEG1 mirrors) are not memory here.
    uint32_t phys = ea & 0x1FFFFFFFu;

    if (((ea >> 29) == 0 || (ea >> 29) == 4 || (ea >> 29) == 5) && phys >= 0x1F801000u &&
        phys < 0x1F803000u)
    {
        fatal(c, insn, "hardware register access");
    }
    if (ea < 0x10000u || (ea >> 24) == 0xA0)
    {
        return PSX_RAM_BASE | (ea & 0x00FFFFFFu);
    }
    return ea;
}

// Loads and stores of 1, 2 or 4 bytes: memory, or the hardware registers (psx_io.c).
static uint32_t ld(const CPU *c, uint32_t insn, uint32_t ea, int size)
{
    if (psx_io_is(ea))
    {
        return psx_io_read(ea, size);
    }
    ea = check_address(c, insn, ea);
    return size == 1 ? MEM8(ea) : size == 2 ? MEM16(ea) : MEM32(ea);
}

static void st(const CPU *c, uint32_t insn, uint32_t ea, uint32_t v, int size)
{
    if (psx_io_is(ea))
    {
        psx_io_write(ea, v, size);
        return;
    }
    ea = check_address(c, insn, ea);
    if (size == 1)
    {
        MEM8(ea) = (uint8_t)v;
    }
    else if (size == 2)
    {
        MEM16(ea) = (uint16_t)v;
    }
    else
    {
        MEM32(ea) = v;
    }
}

static void jump_to(CPU *c, uint32_t insn, uint32_t target)
{
    // A retail function the port replaced by native code starts with an x86 jmp (psx_mem.c); an
    // overlay function may have a native replacement too. The call happens once the delay slot
    // has run (mips_run).
    if (target != RETURN_SENTINEL && mips_native_target(target) != NULL)
    {
        c->native = target;
    }
    c->next_pc = target;
}

static void cop2(CPU *c, uint32_t insn)
{
    int rt = (insn >> 16) & 31, rd = (insn >> 11) & 31;

    if (insn & 0x02000000u)
    {
        gte_command(insn & 0x01FFFFFFu);
        return;
    }
    switch ((insn >> 21) & 31)
    {
        case 0x00: // mfc2
            if (rt)
            {
                c->r[rt] = gte_read_data(rd);
            }
            return;
        case 0x02: // cfc2
            if (rt)
            {
                c->r[rt] = gte_read_ctrl(rd);
            }
            return;
        case 0x04: // mtc2
            gte_write_data(rd, c->r[rt]);
            return;
        case 0x06: // ctc2
            gte_write_ctrl(rd, c->r[rt]);
            return;
        default:
            fatal(c, insn, "unknown COP2 instruction");
    }
}

static void special(CPU *c, uint32_t insn)
{
    int rs = (insn >> 21) & 31, rt = (insn >> 16) & 31, rd = (insn >> 11) & 31;
    int sa     = (insn >> 6) & 31;
    uint32_t s = c->r[rs], t = c->r[rt];
    uint32_t v = 0;
    int write  = 1;

    switch (insn & 0x3F)
    {
        case 0x00:
            v = t << sa;
            break;
        case 0x02:
            v = t >> sa;
            break;
        case 0x03:
            v = (uint32_t)((int32_t)t >> sa);
            break;
        case 0x04:
            v = t << (s & 31);
            break;
        case 0x06:
            v = t >> (s & 31);
            break;
        case 0x07:
            v = (uint32_t)((int32_t)t >> (s & 31));
            break;
        case 0x08: // jr
            jump_to(c, insn, s);
            write = 0;
            break;
        case 0x09: // jalr
            v = c->at + 8;
            jump_to(c, insn, s);
            break;
        case 0x0C:
            // The kernel's critical sections (PsyQ's EnterCriticalSection: a0 = 1, v0 = whether
            // interrupts were enabled; ExitCriticalSection: a0 = 2) on the vblank signal.
            if (c->r[4] == 1)
            {
                c->r[2] = port_irq_block() ? 0 : 1;
            }
            else if (c->r[4] == 2)
            {
                port_irq_restore(0);
            }
            else
            {
                fatal(c, insn, "syscall");
            }
            break;
        case 0x0D:
            fatal(c, insn, "break");
            break;
        case 0x10:
            v = c->hi;
            break;
        case 0x11:
            c->hi = s;
            write = 0;
            break;
        case 0x12:
            v = c->lo;
            break;
        case 0x13:
            c->lo = s;
            write = 0;
            break;
        case 0x18:
        {
            int64_t p = (int64_t)(int32_t)s * (int32_t)t;
            c->lo     = (uint32_t)p;
            c->hi     = (uint32_t)((uint64_t)p >> 32);
            write     = 0;
            break;
        }
        case 0x19:
        {
            uint64_t p = (uint64_t)s * t;
            c->lo      = (uint32_t)p;
            c->hi      = (uint32_t)(p >> 32);
            write      = 0;
            break;
        }
        case 0x1A: // div: the R3000's results for x/0 and INT_MIN/-1
            if (t == 0)
            {
                c->lo = ((int32_t)s < 0) ? 1 : 0xFFFFFFFFu;
                c->hi = s;
            }
            else if (s == 0x80000000u && t == 0xFFFFFFFFu)
            {
                c->lo = 0x80000000u;
                c->hi = 0;
            }
            else
            {
                c->lo = (uint32_t)((int32_t)s / (int32_t)t);
                c->hi = (uint32_t)((int32_t)s % (int32_t)t);
            }
            write = 0;
            break;
        case 0x1B:
            if (t == 0)
            {
                c->lo = 0xFFFFFFFFu;
                c->hi = s;
            }
            else
            {
                c->lo = s / t;
                c->hi = s % t;
            }
            write = 0;
            break;
        case 0x20: // add (overflow traps are not modelled)
        case 0x21:
            v = s + t;
            break;
        case 0x22:
        case 0x23:
            v = s - t;
            break;
        case 0x24:
            v = s & t;
            break;
        case 0x25:
            v = s | t;
            break;
        case 0x26:
            v = s ^ t;
            break;
        case 0x27:
            v = ~(s | t);
            break;
        case 0x2A:
            v = (int32_t)s < (int32_t)t;
            break;
        case 0x2B:
            v = s < t;
            break;
        default:
            fatal(c, insn, "unknown SPECIAL instruction");
    }
    if (write && rd)
    {
        c->r[rd] = v;
    }
}

static void step(CPU *c)
{
    uint32_t insn = MEM32(c->pc);
    int op = insn >> 26, rs = (insn >> 21) & 31, rt = (insn >> 16) & 31;
    uint32_t imm  = insn & 0xFFFF;
    uint32_t simm = (uint32_t)(int32_t)(int16_t)imm;
    uint32_t s = c->r[rs], t = c->r[rt];
    uint32_t ea     = s + simm;
    uint32_t pc     = c->pc;
    uint32_t branch = pc + 4 + (simm << 2);
    uint32_t w;
    int sh;

    // Delay slot: the instruction after a jump runs before the jump takes effect.
    c->at      = pc;
    c->pc      = c->next_pc;
    c->next_pc = c->pc + 4;
    steps++;

    switch (op)
    {
        case 0x00:
            special(c, insn);
            break;
        case 0x01: // bltz, bgez, bltzal, bgezal
        {
            int taken = (rt & 1) ? ((int32_t)s >= 0) : ((int32_t)s < 0);
            if ((rt & 0x1E) == 0x10)
            {
                c->r[31] = pc + 8;
            }
            if (taken)
            {
                c->next_pc = branch;
            }
            break;
        }
        case 0x02:
            jump_to(c, insn, (pc & 0xF0000000u) | ((insn & 0x03FFFFFFu) << 2));
            break;
        case 0x03:
            c->r[31] = pc + 8;
            jump_to(c, insn, (pc & 0xF0000000u) | ((insn & 0x03FFFFFFu) << 2));
            break;
        case 0x04:
            if (s == t)
            {
                c->next_pc = branch;
            }
            break;
        case 0x05:
            if (s != t)
            {
                c->next_pc = branch;
            }
            break;
        case 0x06:
            if ((int32_t)s <= 0)
            {
                c->next_pc = branch;
            }
            break;
        case 0x07:
            if ((int32_t)s > 0)
            {
                c->next_pc = branch;
            }
            break;
        case 0x08:
        case 0x09:
            if (rt)
            {
                c->r[rt] = s + simm;
            }
            break;
        case 0x0A:
            if (rt)
            {
                c->r[rt] = (int32_t)s < (int32_t)simm;
            }
            break;
        case 0x0B:
            if (rt)
            {
                c->r[rt] = s < simm;
            }
            break;
        case 0x0C:
            if (rt)
            {
                c->r[rt] = s & imm;
            }
            break;
        case 0x0D:
            if (rt)
            {
                c->r[rt] = s | imm;
            }
            break;
        case 0x0E:
            if (rt)
            {
                c->r[rt] = s ^ imm;
            }
            break;
        case 0x0F:
            if (rt)
            {
                c->r[rt] = imm << 16;
            }
            break;
        case 0x10: // COP0: the status register and friends as plain storage (libpress's
                   // DecDCTvlc sets a status bit around its loop)
            if (rs == 0)
            {
                if (rt)
                {
                    c->r[rt] = cop0[(insn >> 11) & 31];
                }
            }
            else if (rs == 4)
            {
                cop0[(insn >> 11) & 31] = t;
            }
            else if (insn != 0x42000010u) // rfe: nothing to restore
            {
                fatal(c, insn, "COP0 instruction");
            }
            break;
        case 0x12:
            cop2(c, insn);
            break;
        case 0x20:
            w = ld(c, insn, ea, 1);
            if (rt)
            {
                c->r[rt] = (uint32_t)(int32_t)(int8_t)w;
            }
            break;
        case 0x21:
            w = ld(c, insn, ea, 2);
            if (rt)
            {
                c->r[rt] = (uint32_t)(int32_t)(int16_t)w;
            }
            break;
        case 0x22: // lwl
            ea = check_address(c, insn, ea);
            w  = MEM32(ea & ~3u);
            sh = (int)(ea & 3);
            if (rt)
            {
                c->r[rt] = (t & (0x00FFFFFFu >> (sh * 8))) | (w << (24 - sh * 8));
            }
            break;
        case 0x23:
            w = ld(c, insn, ea, 4);
            if (rt)
            {
                c->r[rt] = w;
            }
            break;
        case 0x24:
            w = ld(c, insn, ea, 1);
            if (rt)
            {
                c->r[rt] = w;
            }
            break;
        case 0x25:
            w = ld(c, insn, ea, 2);
            if (rt)
            {
                c->r[rt] = w;
            }
            break;
        case 0x26: // lwr
            ea = check_address(c, insn, ea);
            w  = MEM32(ea & ~3u);
            sh = (int)(ea & 3);
            if (rt)
            {
                c->r[rt] = (t & ~(0xFFFFFFFFu >> (sh * 8))) | (w >> (sh * 8));
            }
            break;
        case 0x28:
            st(c, insn, ea, t, 1);
            break;
        case 0x29:
            st(c, insn, ea, t, 2);
            break;
        case 0x2A: // swl
            ea = check_address(c, insn, ea);
            sh              = (int)(ea & 3);
            w               = MEM32(ea & ~3u);
            MEM32(ea & ~3u) = (w & ~(0xFFFFFFFFu >> (24 - sh * 8))) | (t >> (24 - sh * 8));
            break;
        case 0x2B:
            st(c, insn, ea, t, 4);
            break;
        case 0x2E: // swr
            ea = check_address(c, insn, ea);
            sh              = (int)(ea & 3);
            w               = MEM32(ea & ~3u);
            MEM32(ea & ~3u) = (w & ~(0xFFFFFFFFu << (sh * 8))) | (t << (sh * 8));
            break;
        case 0x32: // lwc2
            ea = check_address(c, insn, ea);
            gte_write_data(rt, MEM32(ea));
            break;
        case 0x3A: // swc2
            ea = check_address(c, insn, ea);
            MEM32(ea) = gte_read_data(rt);
            break;
        default:
            fatal(c, insn, "unknown instruction");
    }
    c->r[0] = 0;
}

typedef uint64_t (*NATIVE_FN)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                              uint32_t, uint32_t, uint32_t, uint32_t);

// The native code for `addr`: a retail function's (the stub table, or a mod's hook on it) or an overlay function's
// replacement (overlay.c), else NULL.
void *mips_native_target(uint32_t addr)
{
    const PORT_STUB *st = port_stub_find(addr);

    if (st != NULL)
    {
        return port_stub_target(st); // a mod's hook (port_stub_hook), else the native code
    }
    return port_overlay_native_find(addr);
}

// Calls native code from MIPS code: a0-a3 and the stack slots at sp+0x10 as cdecl arguments
// (ten words; extra ones are ignored by the callee), the result in v0 (and v1 for a 64-bit one),
// then returns to ra.
static void call_native(CPU *c, void *fn)
{
    const uint32_t *st = (const uint32_t *)(uintptr_t)c->r[29];
    uint64_t r = ((NATIVE_FN)fn)(c->r[4], c->r[5], c->r[6], c->r[7], st[4], st[5], st[6], st[7],
                                 st[8], st[9]);

    c->r[2]    = (uint32_t)r;
    c->r[3]    = (uint32_t)(r >> 32);
    c->pc      = c->r[31];
    c->next_pc = c->pc + 4;
}

// The BIOS function tables: `jr` to 0xA0/0xB0/0xC0 with the function number in t1. PsyQ's
// libc stubs reach the BIOS this way. The memory and string routines are the host's; rand and
// srand are the BIOS's generator (seed * 0x41C64E6D + 0x3039, bits 16-30).
static uint32_t bios_seed;

static void bios_call(CPU *c)
{
    uint32_t a0 = c->r[4], a1 = c->r[5], a2 = c->r[6];
    uint32_t v  = 0;

    switch ((c->pc << 8) | (c->r[9] & 0xFF))
    {
        case 0xA015: // strcat
            strcat((char *)(uintptr_t)a0, (const char *)(uintptr_t)a1);
            v = a0;
            break;
        case 0xA017: // strcmp
            v = (uint32_t)strcmp((const char *)(uintptr_t)a0, (const char *)(uintptr_t)a1);
            break;
        case 0xA018: // strncmp
            v = (uint32_t)strncmp((const char *)(uintptr_t)a0, (const char *)(uintptr_t)a1, a2);
            break;
        case 0xA019: // strcpy
            strcpy((char *)(uintptr_t)a0, (const char *)(uintptr_t)a1);
            v = a0;
            break;
        case 0xA01B: // strlen
            v = (uint32_t)strlen((const char *)(uintptr_t)a0);
            break;
        case 0xA028: // bzero
            memset((void *)(uintptr_t)a0, 0, a1);
            v = a0;
            break;
        case 0xA02A: // memcpy
            memmove((void *)(uintptr_t)a0, (const void *)(uintptr_t)a1, a2);
            v = a0;
            break;
        case 0xA02B: // memset
            memset((void *)(uintptr_t)a0, (int)a1, a2);
            v = a0;
            break;
        case 0xA02F: // rand
            bios_seed = bios_seed * 0x41C64E6Du + 0x3039u;
            v         = (bios_seed >> 16) & 0x7FFF;
            break;
        case 0xA030: // srand
            bios_seed = a0;
            break;
        case 0xA03F: // printf: the format only
            fprintf(stderr, "port: (printf) %s", (const char *)(uintptr_t)a0);
            break;
        default:
            fprintf(stderr,
                    "mips_cpu: BIOS call %02X:%02X (ra 0x%08X, a0 0x%08X a1 0x%08X a2 0x%08X)\n",
                    c->pc, c->r[9], c->r[31], a0, a1, a2);
            abort();
    }
    c->r[2]    = v;
    c->pc      = c->r[31];
    c->next_pc = c->pc + 4;
}

uint64_t mips_call64(uint32_t addr, const uint32_t args[8])
{
    uint8_t *stack;
    uint32_t sp;
    void *fn;
    CPU c;
    int i;

    fn = mips_native_target(addr);
    if (fn != NULL)
    {
        return ((NATIVE_FN)fn)(args[0], args[1], args[2], args[3], args[4], args[5], args[6],
                               args[7], 0, 0);
    }
    // The MIPS stack lives on the host stack of whoever calls: nested entries (native code
    // called from MIPS code calling MIPS code again) and the game's threads, each on its own
    // host stack, then never share one.
    stack = alloca(STACK_BYTES);
    memset(&c, 0, sizeof(c));
    // The callee may store a0-a3 into the 16 bytes the caller reserves at sp; stack arguments
    // follow them.
    sp = ((uint32_t)(uintptr_t)(stack + STACK_BYTES) - 0x40) & ~7u;
    for (i = 0; i < 4; i++)
    {
        c.r[4 + i]                         = args[i];
        ((uint32_t *)(uintptr_t)sp)[4 + i] = args[4 + i];
    }
    c.r[28]   = mips_gp;
    c.r[29]   = sp;
    c.r[30]   = sp;
    c.r[31]   = RETURN_SENTINEL;
    c.pc      = addr;
    c.next_pc = addr + 4;
    while (c.pc != RETURN_SENTINEL)
    {
        if (c.native != 0)
        {
            uint32_t target = c.native;

            c.native = 0;
            if (c.pc == target)
            {
                call_native(&c, mips_native_target(target));
                continue;
            }
        }
        if (c.pc == 0xA0 || c.pc == 0xB0 || c.pc == 0xC0)
        {
            bios_call(&c);
            continue;
        }
        // Branches reach native code too (a tail call through `b`): a stub's x86 jmp opcode
        // 0xE9 is the low byte of the word at the function's address.
        if (MEM8(c.pc) == 0xE9 && port_stub_find(c.pc) != NULL)
        {
            call_native(&c, mips_native_target(c.pc));
            continue;
        }
        step(&c);
    }
    // DMA completion interrupts of transfers the call started (libspu, libpress).
    psx_io_run_pending();
    return ((uint64_t)c.r[3] << 32) | c.r[2];
}

uint32_t mips_call(uint32_t addr, const uint32_t args[8])
{
    return (uint32_t)mips_call64(addr, args);
}
