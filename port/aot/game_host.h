#ifndef PORT_AOT_GAME_HOST_H
#define PORT_AOT_GAME_HOST_H

#include <stdint.h>

#define PORT_GAME_ARG_WORDS 16

// Instance of the wasm2c module issuing a call. The game_probe test module
// and the full ROCK_NEO module each provide their own generated dispatch.
struct w2c_env
{
    void *instance;
    int (*fallback)(uint32_t address, const uint32_t args[PORT_GAME_ARG_WORDS], uint32_t *result);
    uint32_t *overlay_sp;
};

uint32_t port_game_call_import(struct w2c_env *env, uint32_t address, const char *name,
                               const uint32_t args[PORT_GAME_ARG_WORDS]);
void port_game_init_imports(struct w2c_env *env);

int port_game_call_native(void *instance, uint32_t address,
                          const uint32_t args[PORT_GAME_ARG_WORDS], uint32_t *result);

#ifdef PORT_NATIVE_OVERLAYS
typedef struct
{
    const char *name;
    uint32_t base, end;
    uint64_t stamp;
    void (*init)(struct w2c_env *env);
    uint32_t *(*stack_pointer)(void);
    int (*call)(uint32_t address, const uint32_t args[PORT_GAME_ARG_WORDS], uint32_t *result);
} PORT_AOT_OVERLAY;

void port_overlays_init(struct w2c_env *env);
int port_overlays_call(uint32_t address, const uint32_t args[PORT_GAME_ARG_WORDS], uint32_t *result);
uint32_t port_overlay_import(struct w2c_env *env, uint32_t address, const char *name,
                             const uint32_t args[PORT_GAME_ARG_WORDS]);
uint32_t port_overlay_dispatch(struct w2c_env *env, uint32_t address,
                               uint32_t a0, uint32_t a1, uint32_t a2);
#endif

#endif
