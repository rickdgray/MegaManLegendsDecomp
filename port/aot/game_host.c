#include "game_host.h"
#include "wasm-rt.h"

#include <inttypes.h>
#include <stdio.h>

uint32_t w2c_env_port_game_dispatch(struct w2c_env *env, uint32_t address, uint32_t a0, uint32_t a1,
                                   uint32_t a2)
{
    const uint32_t args[PORT_GAME_ARG_WORDS] = {a0, a1, a2};
    uint32_t result;

    if (port_game_call_native(env->instance, address, args, &result) ||
        (env->fallback != NULL && env->fallback(address, args, &result)))
    {
        return result;
    }

    fprintf(stderr, "game64: no dispatch target at 0x%08" PRIX32 "\n", address);
    wasm_rt_trap(WASM_RT_TRAP_CALL_INDIRECT);
}
