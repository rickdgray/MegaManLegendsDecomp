// The base game's native PsyQ imports. Pure packet builders, GTE routines, and
// software library functions use the retail implementation on the R3000 core.
#include "game_host.h"
#include "rock_neo.h"
#include "import_addresses.h"
#include "mips_cpu.h"
#include "mips_asm.h"
#include "mips_memory.h"
#include "port_game.h"
#include "psx_mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PSYQ_RECT;
struct PSYQ_DISPENV;
struct PSYQ_DRAWENV;
typedef void (*CD_CALLBACK)(uint8_t, uint8_t *);
typedef void (*THREAD_ENTRY)(void);

extern int VSync(int), DrawSync(int), ResetGraph(int);
extern void ResetCallback(void), StopCallback(void), FlushCache(void);
extern void InitGeom(void);
extern void *VSyncCallback(void (*)(void));
extern int CdInit(void), CdReset(int), CdMix(void *);
extern int CdSync(int, uint8_t *), CdGetSector(void *, int);
extern int CdControl(uint8_t, uint8_t *, uint8_t *), CdControlB(uint8_t, uint8_t *, uint8_t *);
extern void *CdReadyCallback(CD_CALLBACK), *CdSyncCallback(CD_CALLBACK);
extern uint32_t *ClearOTagR(uint32_t *, int);
extern void DrawOTag(uint32_t *), SetDispMask(int);
extern int LoadImage(struct PSYQ_RECT *, uint32_t *);
extern struct PSYQ_DISPENV *PutDispEnv(struct PSYQ_DISPENV *);
extern struct PSYQ_DRAWENV *PutDrawEnv(struct PSYQ_DRAWENV *);
extern long OpenEvent(uint32_t, long, long, uint32_t);
extern long EnableEvent(long), TestEvent(long);
extern void InitCARD(long), StartCARD(void), ExitCriticalSection(void);
extern long _bu_init(void), _new_card(void), _card_info(long), _card_load(long), _card_clear(long);
extern long _card_write(long, long, uint8_t *);
extern long EnterCriticalSection(void);
extern long OpenTh(THREAD_ENTRY, uint32_t, uint32_t), CloseTh(long), ChangeTh(long);
extern void port_api_set_guest_threads(void (*start)(uint32_t), void (*change)(int, int));
extern long PCopen(const char *, long, long), PCread(long, void *, long), PCclose(long);
extern long psyq_open(const char *, long), psyq_close(long), psyq_read(long, void *, long);
extern long psyq_write(long, const void *, long), psyq_format(const char *);
extern void *firstfile(const char *, void *), *nextfile(void *);
extern void port_aot_select_game_bios(void);
extern void port_gpu_set_state_address(uint32_t address);
extern void port_gpu_set_draw_env_builder(uint32_t address);

static struct w2c_env *game;

// The mods' hook points (mods_host.c): 1 when `address` is one and it ran.
int mods_host_try(uint32_t address, const uint32_t *args, uint32_t *result);

void *port_game_instance(void)
{
    return game->instance;
}

struct w2c_env *port_game_env(void)
{
    return game;
}
static uint32_t vsync_address, cd_ready_address, cd_sync_address;
static uint32_t guest_stack[8];

static void run_guest_thread(uint32_t entry)
{
    const uint32_t args[PORT_GAME_ARG_WORDS] = {0};
    uint32_t result;

    if (!port_game_call_native(game->instance, entry, args, &result))
        mips_call(entry, args);
}

static void switch_guest_stack(int from, int to)
{
    uint32_t *sp = w2c_rock__neo_0x5F_stack_pointer(game->instance);

    guest_stack[from] = *sp;
    *sp = guest_stack[to];
}

static int call_compiled_game(uint32_t address, const uint32_t args[16], uint32_t *result)
{
    if (mods_host_try(address, args, result))
    {
        return 1;
    }
    return port_game_call_native(game->instance, address, args, result);
}

static int call_retail_overlay(uint32_t address, const uint32_t args[PORT_GAME_ARG_WORDS],
                               uint32_t *result)
{
    // Function-pointer calls (port_game_dispatch) to a mod hook point land here: its compiled
    // body is NAME__orig, which the native dispatch does not list.
    if (mods_host_try(address, args, result))
    {
        return 1;
    }
    if ((address & 3) != 0 ||
        !((address >= 0x800D8800u && address < 0x800F0000u) ||
          (address >= 0x80100000u && address < 0x801F0000u)))
        return 0;
#ifdef PORT_NATIVE_OVERLAYS
    if (port_overlays_call(address, args, result))
        return 1;
#endif
    *result = mips_call(address, args);
    return 1;
}

void port_game_init_imports(struct w2c_env *env)
{
    game = env;
    env->fallback = call_retail_overlay;
#ifdef PORT_NATIVE_OVERLAYS
    port_overlays_init(env);
#endif
    mips_set_guest_dispatch(call_compiled_game);
    port_aot_select_game_bios();
    vsync_address = cd_ready_address = cd_sync_address = 0;
    port_gpu_set_state_address(0x80097718u);
    port_gpu_set_draw_env_builder(0x8007E1A8u);
    port_api_set_guest_threads(run_guest_thread, switch_guest_stack);
}

static void *guest_ptr(uint32_t address)
{
    return address != 0 ? port_aot_mips_ptr(address) : NULL;
}

// The guest stores four 32-bit words per inline-assembly descriptor. Cache the
// host pointers separately rather than putting them into a guest structure.
typedef struct ASM_CACHE
{
    struct ASM_CACHE *next;
    uint32_t address;
    PORT_ASM_PROG program;
} ASM_CACHE;

static void run_inline_asm(uint32_t address, uint32_t operands)
{
    static ASM_CACHE *cache[256];
    ASM_CACHE **bucket = &cache[(address >> 4) & 255];
    ASM_CACHE *entry = *bucket;

    for (; entry != NULL && entry->address != address; entry = entry->next)
        ;
    if (entry == NULL)
    {
        const uint32_t *descriptor = guest_ptr(address);

        entry = malloc(sizeof(*entry));
        if (entry == NULL)
            abort();
        *entry = (ASM_CACHE){
            *bucket, address,
            {guest_ptr(descriptor[0]), guest_ptr(descriptor[1]), -1, NULL},
        };
        *bucket = entry;
    }
    port_asm_run(&entry->program, guest_ptr(operands));
}

static void call_callback(uint32_t address, uint8_t status, uint8_t *data, uint32_t buffer)
{
    uint32_t args[PORT_GAME_ARG_WORDS] = {status};
    uint32_t result;

    if (data != NULL)
    {
        memcpy(guest_ptr(buffer), data, 8);
        args[1] = buffer;
    }
    if (!port_game_call_native(game->instance, address, args, &result))
    {
        mips_call(address, args);
    }
}

static void vsync_callback(void)
{
    call_callback(vsync_address, 0, NULL, 0);
}

static void cd_ready_callback(uint8_t status, uint8_t *data)
{
    call_callback(cd_ready_address, status, data, 0x80218000u);
}

static void cd_sync_callback(uint8_t status, uint8_t *data)
{
    call_callback(cd_sync_address, status, data, 0x80218008u);
}

// --trace-imports (on by default in the Apple TV app, where nothing else shows what the game is
// doing): logs the first call of each library function, and every 300 blanks the last few
// functions called, so a stall shows where the game waits.
int port_game_trace_imports;

static void trace_import(uint32_t address, const char *name)
{
    static const char *seen[512];
    static const char *recent[6];
    static int recent_n;
    static uint32_t last_report;
    uint32_t h = (uint32_t)(((uintptr_t)name >> 3) & 511), now;
    int i;

    (void)address;
    while (seen[h] != NULL && seen[h] != name)
    {
        h = (h + 1) & 511;
    }
    if (seen[h] == NULL)
    {
        seen[h] = name;
        port_log("import: first call to %s at blank %u", name, port_vblank_count());
    }
    for (i = 0; i < 6 && recent[i] != name; i++)
    {
    }
    if (i == 6)
    {
        recent[recent_n++ % 6] = name;
    }
    now = port_vblank_count();
    if (now - last_report >= 300)
    {
        last_report = now;
        port_log("status: blank %u; recently called %s %s %s %s %s %s", now,
                 recent[0] ? recent[0] : "-", recent[1] ? recent[1] : "-",
                 recent[2] ? recent[2] : "-", recent[3] ? recent[3] : "-",
                 recent[4] ? recent[4] : "-", recent[5] ? recent[5] : "-");
        memset(recent, 0, sizeof(recent));
        recent_n = 0;
    }
}

uint32_t port_game_call_import(struct w2c_env *env, uint32_t address, const char *name,
                               const uint32_t args[PORT_GAME_ARG_WORDS])
{
    uint32_t a0 = args[0], a1 = args[1], a2 = args[2], a3 = args[3];
    uint32_t old;

    if (port_game_trace_imports)
    {
        trace_import(address, name);
    }
    if (mods_host_try(address, args, &old))
    {
        return old;
    }

    switch (address)
    {
        case GAME_IMPORT_ChangeClearPAD:
        case GAME_IMPORT_func_800175D8:
        case GAME_IMPORT_func_800175FC:
            return 0; // Host pad state and stacks have no BIOS scratchpad counterpart.
        case GAME_IMPORT_CdInit:
            return CdInit();
        case GAME_IMPORT_CdReset:
            return CdReset(a0);
        case GAME_IMPORT_CdMix:
            return CdMix(guest_ptr(a0));
        case GAME_IMPORT_CdSync:
            return CdSync(a0, guest_ptr(a1));
        case GAME_IMPORT_CdGetSector:
            return CdGetSector(guest_ptr(a0), a1);
        case GAME_IMPORT_CdControl:
            return CdControl(a0, guest_ptr(a1), guest_ptr(a2));
        case GAME_IMPORT_CdControlB:
            return CdControlB(a0, guest_ptr(a1), guest_ptr(a2));
        case GAME_IMPORT_CdReadyCallback:
            old = cd_ready_address;
            cd_ready_address = a0;
            CdReadyCallback(a0 ? cd_ready_callback : NULL);
            return old;
        case GAME_IMPORT_CdSyncCallback:
            old = cd_sync_address;
            cd_sync_address = a0;
            CdSyncCallback(a0 ? cd_sync_callback : NULL);
            return old;
        case GAME_IMPORT_VSyncCallback:
            old = vsync_address;
            vsync_address = a0;
            VSyncCallback(a0 ? vsync_callback : NULL);
            return old;
        case GAME_IMPORT_VSync:
            return VSync(a0);
        case GAME_IMPORT_ResetCallback:
            ResetCallback();
            return 0;
        case GAME_IMPORT_StopCallback:
            StopCallback();
            return 0;
        case GAME_IMPORT_FlushCache:
            FlushCache();
            return 0;
        case GAME_IMPORT_ClearOTagR:
            return psx_addr(ClearOTagR(guest_ptr(a0), a1));
        case GAME_IMPORT_DrawOTag:
            DrawOTag(guest_ptr(a0));
            return 0;
        case GAME_IMPORT_DrawSync:
            return DrawSync(a0);
        case GAME_IMPORT_InitGeom:
            InitGeom();
            return 0;
        case GAME_IMPORT_ResetGraph:
            return ResetGraph(a0);
        case GAME_IMPORT_PutDispEnv:
            return psx_addr(PutDispEnv(guest_ptr(a0)));
        case GAME_IMPORT_PutDrawEnv:
            return psx_addr(PutDrawEnv(guest_ptr(a0)));
        case GAME_IMPORT_LoadImage:
            return LoadImage(guest_ptr(a0), guest_ptr(a1));
        case GAME_IMPORT_SetDispMask:
            SetDispMask(a0);
            return 0;
        case GAME_IMPORT_InitPAD:
            port_pad_init(guest_ptr(a0), a1, guest_ptr(a2), a3);
            return 0;
        case GAME_IMPORT_StartPAD:
            port_pad_start(1);
            return 0;
        case GAME_IMPORT_OpenEvent:
            return OpenEvent(a0, a1, a2, a3);
        case GAME_IMPORT_EnableEvent:
            return EnableEvent(a0);
        case GAME_IMPORT_TestEvent:
            return TestEvent(a0);
        case GAME_IMPORT_PCopen:
            return PCopen(guest_ptr(a0), a1, a2);
        case GAME_IMPORT_PCread:
            return PCread(a0, guest_ptr(a1), a2);
        case GAME_IMPORT_func_8007699C:
            return PCclose(a0);
        case GAME_IMPORT_open:
            return psyq_open(guest_ptr(a0), a1);
        case GAME_IMPORT_close:
            return psyq_close(a0);
        case GAME_IMPORT_read:
            return psyq_read(a0, guest_ptr(a1), a2);
        case GAME_IMPORT_write:
            return psyq_write(a0, guest_ptr(a1), a2);
        case GAME_IMPORT_format:
            return psyq_format(guest_ptr(a0));
        case GAME_IMPORT_firstfile:
            return psx_addr(firstfile(guest_ptr(a0), guest_ptr(a1)));
        case GAME_IMPORT_nextfile:
            return psx_addr(nextfile(guest_ptr(a0)));
        case GAME_IMPORT_strcpy:
            strcpy(guest_ptr(a0), guest_ptr(a1));
            return a0;
        case GAME_IMPORT_strcat:
            strcat(guest_ptr(a0), guest_ptr(a1));
            return a0;
        case GAME_IMPORT_func_8007FC88:
            InitCARD(a0);
            return 0;
        case GAME_IMPORT_func_8007FCE0:
            StartCARD();
            return 0;
        case GAME_IMPORT__bu_init:
            return _bu_init();
        case GAME_IMPORT__new_card:
            return _new_card();
        case GAME_IMPORT__card_info:
            return _card_info(a0);
        case GAME_IMPORT__card_load:
            return _card_load(a0);
        case GAME_IMPORT__card_clear:
            return _card_clear(a0);
        case GAME_IMPORT__card_write:
            return _card_write(a0, a1, guest_ptr(a2));
        case GAME_IMPORT_func_8007FF70:
            return EnterCriticalSection();
        case GAME_IMPORT_func_8007FF80:
            ExitCriticalSection();
            return 0;
        case GAME_IMPORT_OpenTh:
            old = OpenTh((THREAD_ENTRY)(uintptr_t)a0, a1, a2);
            if (old != UINT32_MAX)
            {
                unsigned slot = old & 0xFFFF;
                uint32_t end = (uint32_t)w2c_rock__neo_memory(game->instance)->size;

                guest_stack[slot] = end - (slot - 1) * 0x40000u;
            }
            return old;
        case GAME_IMPORT_CloseTh:
            return CloseTh(a0);
        case GAME_IMPORT_ChangeTh:
            return ChangeTh(a0);
        case 0:
            if (strcmp(name, "abs") == 0)
                return (int32_t)a0 < 0 ? 0 - a0 : a0;
            if (strcmp(name, "port_vblank_idle") == 0)
            {
                port_vblank_idle();
                return 0;
            }
            if (strcmp(name, "port_asm_run") == 0)
            {
                run_inline_asm(a0, a1);
                return 0;
            }
            port_log("game64: unsupported import %s", name);
            port_stop(1, "unbound game import");
        default:
            return mips_call(address, args);
    }
}
