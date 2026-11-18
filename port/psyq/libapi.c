// PsyQ libapi (the BIOS kernel interface) for the native port: threads, events, critical
// sections, pad start-up, memory cards on image files (port/runtime/memcard.c), PCdrv.
//
// Threads: the game keeps its own scheduler table at 0x801F8100 and switches with ChangeTh
// (src/rock_neo.exe/main.c). Each kernel thread here is a ucontext coroutine with its own host
// stack; the stack and gp the game passes to OpenTh are PS1 addresses meant for MIPS frames and
// are ignored. Handles are the kernel's: 0xFF000000 | slot, slot 0 being the main thread.
#define _GNU_SOURCE
#ifdef __APPLE__
// Darwin hides the (deprecated, still working) ucontext routines unless asked for XSI.
#define _XOPEN_SOURCE    600
#define _DARWIN_C_SOURCE 1
#endif
#include "port_game.h"
#include "psx_mem.h"
#include "psx_io.h"
#include "memcard.h"
#include "psyq_alias.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>

// Coroutines: ucontext on Linux. Apple's tvOS has the ucontext functions but they do not switch
// (the game's second thread never ran there), so Apple platforms use mml_coro_switch below, a
// stack switch saving the callee-saved registers. -DPORT_OWN_CORO selects it elsewhere too.
#if defined(__APPLE__) && !defined(PORT_OWN_CORO)
#define PORT_OWN_CORO 1
#endif

#define THREADS      8
#define THREAD_STACK (1024 * 1024)
#define HANDLE_TH    0xFF000000u

typedef void (*ENTRY)(void);

typedef struct
{
    int used;
    ENTRY entry;
    ucontext_t ctx;
    void *sp; // PORT_OWN_CORO: the saved stack pointer while switched out
    void *stack;
} THREAD;

static THREAD threads[THREADS] = {{1, NULL, {0}, NULL, NULL}};

#ifdef PORT_OWN_CORO
#ifdef __APPLE__
#define CORO_SYM(name) "_" #name
#else
#define CORO_SYM(name) #name
#endif
// void mml_coro_switch(void **save_sp, void *load_sp): saves the callee-saved registers on the
// current stack, stores its pointer in *save_sp, and resumes the stack at load_sp. A new stack
// (coro_prepare) resumes into mml_coro_trampoline, which calls mml_coro_start.
void mml_coro_switch(void **save_sp, void *load_sp);
void mml_coro_trampoline(void);
void mml_coro_start(void);
#if defined(__aarch64__)
__asm__(".text\n.p2align 2\n.globl " CORO_SYM(mml_coro_switch) "\n" CORO_SYM(mml_coro_switch) ":\n"
        "  sub sp, sp, #160\n"
        "  stp x19, x20, [sp, #0]\n  stp x21, x22, [sp, #16]\n  stp x23, x24, [sp, #32]\n"
        "  stp x25, x26, [sp, #48]\n  stp x27, x28, [sp, #64]\n  stp x29, x30, [sp, #80]\n"
        "  stp d8, d9, [sp, #96]\n  stp d10, d11, [sp, #112]\n  stp d12, d13, [sp, #128]\n"
        "  stp d14, d15, [sp, #144]\n"
        "  mov x2, sp\n  str x2, [x0]\n  mov sp, x1\n"
        "  ldp x19, x20, [sp, #0]\n  ldp x21, x22, [sp, #16]\n  ldp x23, x24, [sp, #32]\n"
        "  ldp x25, x26, [sp, #48]\n  ldp x27, x28, [sp, #64]\n  ldp x29, x30, [sp, #80]\n"
        "  ldp d8, d9, [sp, #96]\n  ldp d10, d11, [sp, #112]\n  ldp d12, d13, [sp, #128]\n"
        "  ldp d14, d15, [sp, #144]\n"
        "  add sp, sp, #160\n  ret\n"
        ".globl " CORO_SYM(mml_coro_trampoline) "\n" CORO_SYM(mml_coro_trampoline) ":\n"
        "  mov x29, #0\n  bl " CORO_SYM(mml_coro_start) "\n  brk #0\n");

static void *coro_prepare(void *stack, size_t size)
{
    uintptr_t top = ((uintptr_t)stack + size) & ~(uintptr_t)15;
    uint64_t *frame = (uint64_t *)(top - 160);

    memset(frame, 0, 160);
    frame[11] = (uint64_t)(uintptr_t)mml_coro_trampoline; // x30: where the switch returns
    return frame;
}
#elif defined(__x86_64__)
__asm__(".text\n.p2align 4\n.globl " CORO_SYM(mml_coro_switch) "\n" CORO_SYM(mml_coro_switch) ":\n"
        "  pushq %rbp\n  pushq %rbx\n  pushq %r12\n  pushq %r13\n  pushq %r14\n  pushq %r15\n"
        "  movq %rsp, (%rdi)\n  movq %rsi, %rsp\n"
        "  popq %r15\n  popq %r14\n  popq %r13\n  popq %r12\n  popq %rbx\n  popq %rbp\n"
        "  ret\n"
        ".globl " CORO_SYM(mml_coro_trampoline) "\n" CORO_SYM(mml_coro_trampoline) ":\n"
        "  xorl %ebp, %ebp\n  call " CORO_SYM(mml_coro_start) "\n  ud2\n");

static void *coro_prepare(void *stack, size_t size)
{
    uintptr_t top = ((uintptr_t)stack + size) & ~(uintptr_t)15;
    uint64_t *frame = (uint64_t *)(top - 72); // so the trampoline's call is 16-byte aligned

    memset(frame, 0, 72);
    frame[6] = (uint64_t)(uintptr_t)mml_coro_trampoline; // the switch's return address
    return frame;
}
#else
#error "PORT_OWN_CORO: no stack switch for this architecture"
#endif
#endif
static int current;

#ifdef PORT_AOT_MIPS
static void (*guest_thread_start)(uint32_t address);
static void (*guest_thread_switch)(int from, int to);

void port_api_set_guest_threads(void (*start)(uint32_t), void (*change)(int, int))
{
    guest_thread_start = start;
    guest_thread_switch = change;
}
#endif

static void thread_start(void);

#ifdef PORT_OWN_CORO
void mml_coro_start(void)
{
    thread_start();
}
#endif

static void thread_start(void)
{
    ENTRY entry = threads[current].entry;

    // A new thread starts with interrupts enabled.
    port_irq_restore(0);
#ifdef PORT_AOT_MIPS
    if (guest_thread_start != NULL)
        guest_thread_start((uint32_t)(uintptr_t)entry);
    else
#endif
        entry();
    port_log("thread 0x%08X returned from its entry function", HANDLE_TH | (uint32_t)current);
    // A kernel thread has nowhere to return to; hand control back to the main thread.
    for (;;)
    {
        long ChangeTh(long handle);
        ChangeTh((long)HANDLE_TH);
    }
}

long OpenTh(ENTRY entry, uint32_t stack, uint32_t gp)
{
    int i;

    (void)stack;
    (void)gp;
    for (i = 1; i < THREADS; i++)
    {
        if (!threads[i].used)
        {
            break;
        }
    }
    if (i == THREADS)
    {
        port_log("OpenTh: no free thread");
        return -1;
    }
    if (threads[i].stack == NULL)
    {
        threads[i].stack = malloc(THREAD_STACK);
        if (threads[i].stack == NULL)
        {
            abort();
        }
    }
    // The slot's previous context (if any) was closed and is never resumed, so its stack is
    // free for the new one even when that thread is the one calling OpenTh's caller back.
#ifdef PORT_OWN_CORO
    threads[i].sp = coro_prepare(threads[i].stack, THREAD_STACK);
#else
    getcontext(&threads[i].ctx);
    threads[i].ctx.uc_stack.ss_sp   = threads[i].stack;
    threads[i].ctx.uc_stack.ss_size = THREAD_STACK;
    threads[i].ctx.uc_link          = NULL;
    makecontext(&threads[i].ctx, thread_start, 0);
#endif
    threads[i].entry = entry;
    threads[i].used  = 1;
    return (long)(HANDLE_TH | (uint32_t)i);
}

long CloseTh(long handle)
{
    int i = (int)((uint32_t)handle & 0xFFFF);

    if (((uint32_t)handle & 0xFF000000u) != HANDLE_TH || i <= 0 || i >= THREADS)
    {
        return 0;
    }
    threads[i].used = 0;
    return 1;
}

long ChangeTh(long handle)
{
    int to = (int)((uint32_t)handle & 0xFFFF);
    int from, blocked;

    if (((uint32_t)handle & 0xFF000000u) != HANDLE_TH || to < 0 || to >= THREADS ||
        !threads[to].used)
    {
        port_log_limited("ChangeTh", 4, "ChangeTh(0x%08lX): no such thread", (unsigned long)handle);
        return 0;
    }
    from = current;
    if (to == from)
    {
        return 1;
    }
    // No interrupt in the middle of a switch; each thread gets its own state back on resume.
    blocked = port_irq_block();
    current = to;
#ifdef PORT_AOT_MIPS
    if (guest_thread_switch != NULL)
        guest_thread_switch(from, to);
#endif
#ifdef PORT_OWN_CORO
    mml_coro_switch(&threads[from].sp, threads[to].sp);
#else
    swapcontext(&threads[from].ctx, &threads[to].ctx);
#endif
    port_irq_restore(blocked);
    return 1;
}

// Critical sections block the vertical-blank interrupt.
long EnterCriticalSection(void)
{
    return port_irq_block() ? 0 : 1;
}

void ExitCriticalSection(void)
{
    port_irq_restore(0);
}

PSYQ_SPLAT_ALIAS(func_8007FF70, EnterCriticalSection);
PSYQ_SPLAT_ALIAS(func_8007FF80, ExitCriticalSection);

void FlushCache(void)
{
}

// --- events ---------------------------------------------------------------------------------

#define EVENTS    16
#define HANDLE_EV 0xF1000000u

#define CLASS_SW_CARD 0xF4000001u
#define CLASS_HW_CARD 0xF0000011u

typedef struct
{
    int used;
    uint32_t desc;
    int32_t spec, mode;
    uint32_t func;
    volatile int fired; // delivered and not yet tested (EvMdNOINTR)
} EVENT;

static EVENT events[EVENTS];

long OpenEvent(uint32_t desc, long spec, long mode, uint32_t func)
{
    int i;

    for (i = 0; i < EVENTS && events[i].used; i++)
    {
    }
    if (i == EVENTS)
    {
        return -1;
    }
    events[i].used = 1;
    events[i].desc = desc;
    events[i].spec = (int32_t)spec;
    events[i].mode = (int32_t)mode;
    events[i].func  = func;
    events[i].fired = 0;
    return (long)(HANDLE_EV | (uint32_t)i);
}

static EVENT *event_of(long ev)
{
    int i = (int)((uint32_t)ev & 0xFFFF);

    if (((uint32_t)ev & 0xFF000000u) != HANDLE_EV || i >= EVENTS || !events[i].used)
    {
        return NULL;
    }
    return &events[i];
}

long CloseEvent(long ev)
{
    EVENT *e = event_of(ev);

    if (e != NULL)
    {
        e->used = 0;
    }
    return 1;
}

long EnableEvent(long ev)
{
    return 1;
}

long DisableEvent(long ev)
{
    return 1;
}

long TestEvent(long ev)
{
    EVENT *e = event_of(ev);

    if (e != NULL && e->fired)
    {
        e->fired = 0;
        return 1;
    }
    return 0;
}

long WaitEvent(long ev)
{
    EVENT *e = event_of(ev);

    if (e != NULL)
    {
        e->fired = 0;
    }
    return 1;
}

// Raises an event (libspu's transfer-complete callback delivers HwSPU/EvSpCOMP this way):
// every open event of that class and spec fires; an EvMdINTR one runs its handler.
#define EV_MD_INTR 0x1000

void DeliverEvent(uint32_t desc, long spec)
{
    int i;

    for (i = 0; i < EVENTS; i++)
    {
        EVENT *e = &events[i];

        if (e->used && e->desc == desc && e->spec == (int32_t)spec)
        {
            if (e->mode == EV_MD_INTR)
            {
                psx_call(e->func);
            }
            else
            {
                e->fired = 1;
            }
        }
    }
}

// --- pads -----------------------------------------------------------------------------------

void InitPAD(uint8_t *buf0, long len0, uint8_t *buf1, long len1)
{
    port_pad_init(buf0, (int)len0, buf1, (int)len1);
}

void StartPAD(void)
{
    port_pad_start(1);
}

void StopPAD(void)
{
    port_pad_start(0);
}

void ChangeClearPAD(int mode)
{
    (void)mode;
}

// --- memory cards ---------------------------------------------------------------------------

// The card BIOS on image files (port/runtime/memcard.c). Every request completes at once and
// delivers its event, as the console's would a few blanks later: the game polls with TestEvent.
//   _card_info  software events: IOE (card there), NEW (a card not seen yet: the first check
//               after power-on or a swapped card), TIMOUT (no card)
//   _card_clear hardware IOE (acknowledges the new card)
//   _card_load  software IOE (directory read), NEW (unformatted), TIMOUT
//   _card_write hardware IOE (one 128-byte frame written)
// Channels are 0x00 (slot 1) and 0x10 (slot 2); the low nibble (multitap) must be 0.
#define EV_SP_IOE    0x0004
#define EV_SP_ERROR  0x8000
#define EV_SP_TIMOUT 0x0100
#define EV_SP_NEW    0x2000

static int card_slot(long chan)
{
    if ((chan & 0x0F) != 0 || (chan & ~0x1FL) != 0)
    {
        return -1;
    }
    return (int)(chan >> 4) & 1;
}

void InitCARD(long val)
{
    (void)val;
}

void StartCARD(void)
{
}

PSYQ_SPLAT_ALIAS(func_8007FC88, InitCARD);
PSYQ_SPLAT_ALIAS(func_8007FCE0, StartCARD);

long _bu_init(void)
{
    return 0;
}

long _card_info(long chan)
{
    int slot = card_slot(chan);
    int r    = slot < 0 ? -1 : memcard_poll(slot);

    DeliverEvent(CLASS_SW_CARD, r < 0 ? EV_SP_TIMOUT : r > 0 ? EV_SP_NEW : EV_SP_IOE);
    return 1;
}

long _card_load(long chan)
{
    int slot = card_slot(chan);

    if (slot < 0 || !memcard_present(slot))
    {
        DeliverEvent(CLASS_SW_CARD, EV_SP_TIMOUT);
    }
    else
    {
        DeliverEvent(CLASS_SW_CARD, memcard_formatted(slot) ? EV_SP_IOE : EV_SP_NEW);
    }
    return 1;
}

long _card_clear(long chan)
{
    int slot = card_slot(chan);

    if (slot < 0 || !memcard_present(slot))
    {
        DeliverEvent(CLASS_HW_CARD, EV_SP_TIMOUT);
        return 1;
    }
    memcard_ack(slot);
    DeliverEvent(CLASS_HW_CARD, EV_SP_IOE);
    return 1;
}

long _card_write(long chan, long block, uint8_t *buf)
{
    int slot = card_slot(chan);

    if (slot < 0 || !memcard_present(slot))
    {
        DeliverEvent(CLASS_HW_CARD, EV_SP_TIMOUT);
        return 1;
    }
    DeliverEvent(CLASS_HW_CARD,
                 memcard_write_frame(slot, (int)block, buf) == 0 ? EV_SP_IOE : EV_SP_ERROR);
    return 1;
}

long _new_card(void)
{
    return 1;
}

// The BIOS file functions on "buXY:" paths (renamed from open, close, ... by gen_link.py so they
// do not clash with the host C library's). Reads and writes move whole 128-byte frames.
#define FREAD  0x0001
#define FWRITE 0x0002
#define FCREAT 0x0200
#define FILES  4
#define FD_BASE 2 // the BIOS numbers files after stdin/stdout

typedef struct
{
    int used, slot, first, mode;
    uint32_t pos, size;
} CARD_FILE;

static CARD_FILE files[FILES];

// "bu00:NAME" -> slot 0 and NAME. Returns the slot, or -1.
static int card_path(const char *path, const char **name)
{
    if (path == NULL || strncmp(path, "bu", 2) != 0 || path[2] < '0' || path[2] > '1' ||
        path[3] != '0' || path[4] != ':')
    {
        return -1;
    }
    *name = path + 5;
    return path[2] - '0';
}

static CARD_FILE *card_file(long fd)
{
    long i = fd - FD_BASE;

    return i >= 0 && i < FILES && files[i].used ? &files[i] : NULL;
}

long psyq_open(const char *path, long mode)
{
    const char *name;
    int slot = card_path(path, &name);
    MEMCARD_FILE info;
    int first, i;

    if (slot < 0)
    {
        port_log_limited("open", 4, "open(\"%s\", 0x%lX): not a memory card path", path,
                         (unsigned long)mode);
        return -1;
    }
    if (!memcard_present(slot) || !memcard_formatted(slot) || *name == 0 ||
        strlen(name) > MEMCARD_NAME_MAX)
    {
        return -1;
    }
    if (mode & FCREAT)
    {
        int blocks = (int)((unsigned long)mode >> 16);

        first = memcard_create(slot, name, blocks > 0 ? blocks : 1);
        if (first < 0)
        {
            port_log("memory card: cannot create %s (%d blocks, %d free)", path,
                     blocks > 0 ? blocks : 1, memcard_free_blocks(slot));
            return -1;
        }
        memcard_find(slot, name, &info);
        port_log("memory card: created %s (%u bytes) in slot %d", path, info.size, slot + 1);
    }
    else
    {
        first = memcard_find(slot, name, &info);
        if (first < 0)
        {
            return -1;
        }
    }
    for (i = 0; i < FILES && files[i].used; i++)
    {
    }
    if (i == FILES)
    {
        return -1;
    }
    files[i].used  = 1;
    files[i].slot  = slot;
    files[i].first = first;
    files[i].mode  = (int)mode;
    files[i].pos   = 0;
    files[i].size  = info.size;
    return FD_BASE + i;
}

long psyq_close(long fd)
{
    CARD_FILE *f = card_file(fd);

    if (f == NULL)
    {
        return -1;
    }
    f->used = 0;
    return fd;
}

static long card_io(long fd, void *buf, long n, int write)
{
    CARD_FILE *f = card_file(fd);

    if (f == NULL || n < 0 || (n % MEMCARD_FRAME) != 0 || f->pos + (uint32_t)n > f->size ||
        !(f->mode & (write ? FWRITE : FREAD)))
    {
        return -1;
    }
    if (memcard_file_io(f->slot, f->first, f->pos, buf, (uint32_t)n, write) != n)
    {
        return -1;
    }
    f->pos += (uint32_t)n;
    if (write)
    {
        port_log_limited("card write", 8, "memory card: wrote 0x%lX bytes to slot %d", n,
                         f->slot + 1);
    }
    return n;
}

long psyq_read(long fd, void *buf, long n)
{
    return card_io(fd, buf, n, 0);
}

long psyq_write(long fd, const void *buf, long n)
{
    return card_io(fd, (void *)buf, n, 1);
}

long psyq_lseek(long fd, long offset, long whence)
{
    CARD_FILE *f = card_file(fd);
    long pos;

    if (f == NULL)
    {
        return -1;
    }
    pos = whence == 0 ? offset : whence == 1 ? (long)f->pos + offset : (long)f->size + offset;
    if (pos < 0 || (uint32_t)pos > f->size)
    {
        return -1;
    }
    f->pos = (uint32_t)pos;
    return pos;
}

long psyq_format(const char *path)
{
    const char *name;
    int slot = card_path(path, &name);

    if (slot < 0 || !memcard_present(slot) || memcard_format(slot) != 0)
    {
        return 0;
    }
    port_log("memory card: formatted slot %d", slot + 1);
    return 1;
}

long psyq_erase(const char *path)
{
    const char *name;
    int slot = card_path(path, &name);

    return slot >= 0 && memcard_erase(slot, name) == 0;
}

// firstfile/nextfile: the DIRENTRY the game passes (name[20], attr, size, next, head,
// system[4]) is filled with the next file matching the pattern ('?' one character, '*' the rest).
typedef struct
{
    char name[20];
    int32_t attr;
    int32_t size;
    uint32_t next;
    int32_t head;
    char system[4];
} PSX_DIRENTRY;

static struct
{
    int slot, index;
    char pattern[MEMCARD_NAME_MAX + 1];
} search = {-1, 0, ""};

static int name_match(const char *pat, const char *name)
{
    for (; *pat != 0; pat++, name++)
    {
        if (*pat == '*')
        {
            return 1;
        }
        if (*name == 0 || (*pat != '?' && *pat != *name))
        {
            return 0;
        }
    }
    return *name == 0;
}

static void *search_next(PSX_DIRENTRY *dir)
{
    MEMCARD_FILE f;

    while (search.slot >= 0 && memcard_file_at(search.slot, search.index++, &f))
    {
        if (name_match(search.pattern, f.name))
        {
            memset(dir, 0, sizeof(*dir));
            memcpy(dir->name, f.name, sizeof(dir->name));
            dir->attr = 0x51;
            dir->size = (int32_t)f.size;
            dir->head = f.first;
            return dir;
        }
    }
    search.slot = -1;
    return NULL;
}

void *firstfile(const char *path, void *dir)
{
    const char *pattern;
    int slot = card_path(path, &pattern);

    search.slot  = slot >= 0 && memcard_present(slot) ? slot : -1;
    search.index = 0;
    snprintf(search.pattern, sizeof(search.pattern), "%s", pattern != NULL && slot >= 0 ? pattern
                                                                                       : "");
    return search_next(dir);
}

void *nextfile(void *dir)
{
    return search_next(dir);
}

// --- PCdrv (development host file access; not on a retail console) --------------------------

long PCopen(const char *name, long flags, long mode)
{
    port_log("PCopen(\"%s\"): no development host", name);
    return -1;
}

long PCread(long fd, void *buf, long n)
{
    return -1;
}

long PCclose(long fd)
{
    return -1;
}

PSYQ_SPLAT_ALIAS(func_8007699C, PCclose);

// --- the BIOS kernel area -------------------------------------------------------------------

// The tables the game reads at KUSEG 0x100 (include/rock_neo.exe/kernel.h): the BIOS's table of
// tables, whose word at +0x10 points to the thread control blocks (0xC0 bytes each) and whose
// word at +0x08 points to the process control block (its first word: the current thread's TCB).
// Natively they only have to be there: the game copies gp from the first TCB and sets the status
// word of the others, and its exception screen reads the current one.
#define KERNEL_TABLE 0x80000100u
#define KERNEL_PCB   0x80007F00u
#define KERNEL_TCBS  0x80008000u
#define TCB_SIZE     0xC0u
#define TCB_GP       0x78u

void port_kernel_init(uint32_t gp)
{
    uint32_t *table = psx_ptr(KERNEL_TABLE);
    uint32_t *pcb   = psx_ptr(KERNEL_PCB);

    memset(psx_ptr(KERNEL_TCBS), 0, THREADS * TCB_SIZE);
    *(uint32_t *)psx_ptr(KERNEL_TCBS + TCB_GP) = gp;
    table[2]                                       = KERNEL_PCB;
    table[3]                                       = 8; // size of the process table
    table[4]                                       = KERNEL_TCBS;
    table[5]                                       = THREADS * TCB_SIZE;
    pcb[0]                                         = KERNEL_TCBS; // current thread: the main one
}
