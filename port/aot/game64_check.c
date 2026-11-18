// Compare a cross-module, compiled base-game call against the retail executable.
#include "game_probe.h"
#include "game_host.h"
#include "mips_cpu.h"
#include "mips_memory.h"
#include "psx_mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCENE_PALETTE_STEP 0x8001E3F0u
#define PALETTE_COLORS     0x8008F168u
#define PALETTE_INCREMENT  0x800891B4u
#define PALETTE_RANGES     0x80097A38u
#define PALETTE_TIMER      0x800C1B70u
#define PALETTE_OUTPUT    (PALETTE_COLORS + 0x4000u)

static void prepare_palette(void)
{
    uint16_t *colors = psx_ptr(PALETTE_COLORS);
    uint16_t *ranges = psx_ptr(PALETTE_RANGES);
    uint16_t *out = psx_ptr(PALETTE_OUTPUT);

    ranges[0] = ranges[1] = ranges[2] = 0;
    ranges[3] = 1;
    memset(out, 0, 0x300);
    *(uint16_t *)psx_ptr(PALETTE_TIMER) = 32;
    *(uint16_t *)psx_ptr(PALETTE_INCREMENT) = 1;
    for (unsigned i = 0; i < 0x180; i++)
    {
        colors[i] = (uint16_t)(0xFFFFu - i);
    }
}

static int check_indirect(w2c_game__probe *module)
{
    // func_800665FC indexes the retail memory-card routine table with mode_4.
    // Mode 3 calls func_80066750, which clears the work state and returns 1.
    uint8_t *work = psx_ptr(0x80098910u);
    const uint8_t initial[0x14] = {0x12, 0x34, 0, 0, 3, 5, 7, 9};
    const uint32_t args[8] = {2};
    uint8_t expected[sizeof(initial)];

    memcpy(work, initial, sizeof(initial));
    uint32_t result = w2c_game__probe_func_800665FC(module, args[0]);
    memcpy(expected, work, sizeof(expected));
    memcpy(work, initial, sizeof(initial));
    uint32_t retail_result = mips_call(0x800665FCu, args);
    return result == 1 && retail_result == result && expected[4] == 0 &&
           memcmp(expected, work, sizeof(expected)) == 0;
}

int main(int argc, char **argv)
{
    w2c_game__probe module;
    struct w2c_env env = {&module};
    uint8_t expected[0x300];
    const uint32_t args[8] = {0};
    int ok = 0;

    if (argc != 2 || sizeof(void *) != 8)
    {
        return EXIT_FAILURE;
    }

    wasm_rt_init();
    wasm2c_game__probe_instantiate(&module, &env);
    wasm_rt_memory_t *memory = w2c_game__probe_memory(&module);
    port_aot_mips_bind(memory->data, memory->size);

    if (psx_load_exe(argv[1], NULL) == 0)
    {
        prepare_palette();
        w2c_game__probe_func_8001E3F0(&module, args[0]);
        memcpy(expected, psx_ptr(PALETTE_OUTPUT), sizeof(expected));
        if (*(const uint16_t *)psx_ptr(PALETTE_TIMER) == 33 && expected[0] != 0)
        {
            prepare_palette();
            mips_call(SCENE_PALETTE_STEP, args);
            ok = *(const uint16_t *)psx_ptr(PALETTE_TIMER) == 33 &&
                 memcmp(expected, psx_ptr(PALETTE_OUTPUT), sizeof(expected)) == 0 &&
                 check_indirect(&module);
        }
    }

    port_aot_mips_bind(NULL, 0);
    wasm2c_game__probe_free(&module);
    wasm_rt_free();
    puts(ok ? "game64_check: compiled palette and indirect dispatch match retail MIPS"
            : "game64_check: base-game comparison failed");
    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
