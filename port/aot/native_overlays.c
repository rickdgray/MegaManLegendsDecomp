// Native overlays share the base game's guest RAM and the active guest thread's stack.
#include "game_host.h"
#include "rock_neo.h"
#include "psx_mem.h"
#include "port_game.h"

#include <stdlib.h>
#include <string.h>

extern uint32_t w2c_env_port_game_dispatch(struct w2c_env *, uint32_t, uint32_t, uint32_t, uint32_t);

#define AOT_OVERLAY(module) extern const PORT_AOT_OVERLAY port_overlay_##module;
#include "overlay_registry.inc"
#undef AOT_OVERLAY

static struct
{
    const PORT_AOT_OVERLAY *module;
    int reported;
} overlays[] = {
#define AOT_OVERLAY(module) {&port_overlay_##module, 0},
#include "overlay_registry.inc"
#undef AOT_OVERLAY
};

static struct w2c_env *game;

wasm_rt_memory_t *port_overlay_memory(struct w2c_env *env)
{
    return w2c_rock__neo_memory(env->instance);
}

void port_overlays_init(struct w2c_env *env)
{
    const char *setting = getenv("PORT_OVERLAY_NATIVE");

    if (setting != NULL && strcmp(setting, "0") == 0)
        return;
    game = env;
    for (size_t i = 0; i < sizeof(overlays) / sizeof(overlays[0]); i++)
        overlays[i].module->init(env);
}

static uint64_t loaded_stamp(uint32_t base)
{
    const uint32_t *words = psx_ptr(base);
    uint64_t stamp = 0xCBF29CE484222325ull;

    for (unsigned i = 0; i < 16; i++)
        stamp = (stamp ^ words[i]) * 0x100000001B3ull;
    return stamp;
}

int port_overlays_call(uint32_t address, const uint32_t args[PORT_GAME_ARG_WORDS], uint32_t *result)
{
    if (game == NULL)
        return 0;
    uint32_t last_base = 0;
    uint64_t stamp = 0;
    for (size_t i = 0; i < sizeof(overlays) / sizeof(overlays[0]); i++)
    {
        const PORT_AOT_OVERLAY *module = overlays[i].module;
        if (address < module->base || address >= module->end)
            continue;
        if (module->base != last_base)
        {
            last_base = module->base;
            stamp = loaded_stamp(last_base);
        }
        if (stamp != module->stamp)
            continue;

        uint32_t *base_sp = w2c_rock__neo_0x5F_stack_pointer(game->instance);
        uint32_t *overlay_sp = module->stack_pointer();
        uint32_t previous = *overlay_sp;
        *overlay_sp = *base_sp;
        int found = module->call(address, args, result);
        *base_sp = *overlay_sp;
        *overlay_sp = previous;
        if (!found)
            return 0;
        if (!overlays[i].reported)
        {
            overlays[i].reported = 1;
            port_log("game64: running compiled %s overlay", module->name);
        }
        return 1;
    }
    return 0;
}

uint32_t port_overlay_import(struct w2c_env *env, uint32_t address, const char *name,
                             const uint32_t args[PORT_GAME_ARG_WORDS])
{
    uint32_t *base_sp = w2c_rock__neo_0x5F_stack_pointer(env->instance);
    uint32_t *stage_sp = env->overlay_sp;
    uint32_t previous = *base_sp;
    uint32_t result;

    *base_sp = *stage_sp;
    if (!port_game_call_native(env->instance, address, args, &result))
        result = port_game_call_import(env, address, name, args);
    *stage_sp = *base_sp;
    *base_sp = previous;
    return result;
}

uint32_t port_overlay_dispatch(struct w2c_env *env, uint32_t address,
                               uint32_t a0, uint32_t a1, uint32_t a2)
{
    uint32_t *base_sp = w2c_rock__neo_0x5F_stack_pointer(env->instance);
    uint32_t *stage_sp = env->overlay_sp;
    uint32_t previous = *base_sp;

    *base_sp = *stage_sp;
    uint32_t result = w2c_env_port_game_dispatch(env, address, a0, a1, a2);
    *stage_sp = *base_sp;
    *base_sp = previous;
    return result;
}
