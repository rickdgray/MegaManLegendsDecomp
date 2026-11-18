// The mods' hooks in the 64-bit port (port/mods/mods.h). bind_retail.py renames each hookable
// base-game function NAME to NAME__orig, so every call to NAME becomes an import that reaches
// mods_host_try: from compiled game code and overlays (port_game_call_import) and from MIPS code
// on the interpreter (the guest dispatch in game_imports.c). It runs the mod's hook when one is
// installed, else the compiled original (wasm2c spells NAME__orig as NAME_0x5Forig). Arguments and results are PS1 words, as in the 32-bit
// port's cdecl hooks.
#include "rock_neo.h"
#include "game_host.h"
#include "mips_memory.h"
#include "port_game.h"

#include <stddef.h>
#include <stdint.h>

void *port_game_instance(void);
struct w2c_env *port_game_env(void);

#define INST ((w2c_rock__neo *)port_game_instance())

static void orig_8003D1E0(uint32_t a0)
{
    w2c_rock__neo_func_8003D1E0_0x5Forig(INST, a0);
}
static void orig_8002FEA4(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3)
{
    w2c_rock__neo_func_8002FEA4_0x5Forig(INST, a0, a1, a2, a3);
}
static void orig_8003F5D8(uint32_t a0)
{
    w2c_rock__neo_func_8003F5D8_0x5Forig(INST, a0);
}
static void orig_8003C88C(uint32_t a0)
{
    w2c_rock__neo_func_8003C88C_0x5Forig(INST, a0);
}
static void orig_8003FDA8(uint32_t a0)
{
    w2c_rock__neo_func_8003FDA8_0x5Forig(INST, a0);
}
static void orig_800158F0(uint32_t a0)
{
    w2c_rock__neo_func_800158F0_0x5Forig(INST, a0);
}

typedef struct
{
    uint32_t addr;
    int nargs;  // PS1 words
    void *orig; // the compiled original, with the game function's own arity
    void *hook; // the mod's hook (same arity), or NULL
} HOOK;

// Keep in step with MOD_HOOKS in bind_retail.py.
static HOOK hooks[] = {
    {0x8003D1E0u, 1, (void *)orig_8003D1E0, NULL},
    {0x8002FEA4u, 4, (void *)orig_8002FEA4, NULL},
    {0x8003F5D8u, 1, (void *)orig_8003F5D8, NULL},
    {0x8003C88Cu, 1, (void *)orig_8003C88C, NULL},
    {0x8003FDA8u, 1, (void *)orig_8003FDA8, NULL},
    {0x800158F0u, 1, (void *)orig_800158F0, NULL},
};
#define NHOOKS (sizeof(hooks) / sizeof(hooks[0]))

static HOOK *find(uint32_t addr)
{
    size_t i;

    for (i = 0; i < NHOOKS; i++)
    {
        if (hooks[i].addr == addr)
        {
            return &hooks[i];
        }
    }
    return NULL;
}

// A hookable address: runs the hook or the original and returns 1; else 0.
int mods_host_try(uint32_t addr, const uint32_t *args, uint32_t *result)
{
    HOOK *h = find(addr);
    void *fn;

    if (h == NULL)
    {
        return 0;
    }
    fn = h->hook != NULL ? h->hook : h->orig;
    if (h->nargs == 1)
    {
        ((void (*)(uint32_t))fn)(args[0]);
    }
    else
    {
        ((void (*)(uint32_t, uint32_t, uint32_t, uint32_t))fn)(args[0], args[1], args[2], args[3]);
    }
    *result = 0; // every hookable function is void
    return 1;
}

void *mods_host_hook(uint32_t addr, void *fn)
{
    HOOK *h = find(addr);

    if (h == NULL)
    {
        return NULL; // not a hook point: add it to MOD_HOOKS and the table above
    }
    h->hook = fn;
    return h->orig;
}

void mods_host_unhook(uint32_t addr)
{
    HOOK *h = find(addr);

    if (h != NULL)
    {
        h->hook = NULL;
    }
}

uint32_t mods_host_call(uint32_t addr, int n, const uint32_t args4[4])
{
    uint32_t args[PORT_GAME_ARG_WORDS] = {0};
    uint32_t result = 0;
    int i;

    for (i = 0; i < n && i < 4; i++)
    {
        args[i] = args4[i];
    }
    if (mods_host_try(addr, args, &result) ||
        port_game_call_native(port_game_instance(), addr, args, &result))
    {
        return result;
    }
    return port_game_call_import(port_game_env(), addr, "mods_call", args);
}

uint8_t *mods_ptr(uint32_t addr)
{
    return (uint8_t *)port_aot_mips_ptr(addr);
}
