// Headless entry for the compiled boot shim and base game.
#include "rock_neo.h"
#include "game_host.h"
#include "gpu.h"
#include "gte.h"
#include "memcard.h"
#include "mdec.h"
#include "mips_cpu.h"
#include "mips_memory.h"
#include "port_game.h"
#include "port_audio.h"
#include "port_script.h"
#include "psx_mem.h"
#include "psx_io.h"
#include "shim_host.h"
#include "spu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void port_kernel_init(uint32_t gp);
extern void port_libetc_reset_session(void);
extern void port_cd_reset_session(void);

static int boot_game(const char *path)
{
    w2c_shim shim;
    PORT_OPTIONS game_options = port_options;
    int ok = 0;

    port_options.dump = port_options.dump_at = NULL;
    port_options.max_vblanks = 4500;
    port_aot_shim_start(&shim);
    if (psx_load_exe(path, NULL) == 0)
    {
        gpu_init();
        gte_reset();
        spu_reset();
        ok = port_aot_shim_wait_for_loadexec(&shim);
    }
    port_libetc_reset_session();
    port_cd_reset_session();
    psx_io_reset();
    mdec_reset();
    port_aot_shim_finish(&shim);
    port_reset_clock();
    port_options = game_options;
    if (ok)
        port_log("game64: starting ROCK_NEO.EXE in the same process");
    return ok;
}

int main(int argc, char **argv)
{
    w2c_rock__neo module;
    struct w2c_env env = {&module};
    PSX_EXE_INFO info;
    const char *exe = PORT_DEFAULT_EXE;
    const char *disc = PORT_DEFAULT_DISC;
    const char *wav = NULL;
    const char *script = NULL;
    int boot = 1;

    port_options.headless = 1;
    port_options.deterministic = 1;
    port_options.max_vblanks = 40000;
    for (int i = 1; i < argc; i++)
    {
        const char *option = argv[i];
        const char *value = i + 1 < argc ? argv[i + 1] : NULL;

        if (strcmp(option, "--headless") == 0 || strcmp(option, "--deterministic") == 0)
            continue;
        if (strcmp(option, "--skip-boot") == 0)
        {
            boot = 0;
            continue;
        }
        if (option[0] != '-')
        {
            exe = option;
            continue;
        }
        if (value == NULL)
            return 2;
        if (strcmp(option, "--disc") == 0)
            disc = value;
        else if (strcmp(option, "--vblanks") == 0)
            port_options.max_vblanks = atoi(value);
        else if (strcmp(option, "--dump") == 0)
            port_options.dump = value;
        else if (strcmp(option, "--dump-at") == 0)
            port_options.dump_at = value;
        else if (strcmp(option, "--wav") == 0)
            wav = value;
        else if (strcmp(option, "--card1") == 0)
            memcard_set_path(0, value, 1);
        else if (strcmp(option, "--script") == 0)
            script = value;
        else
        {
            fprintf(stderr, "game64: unknown option %s\n", option);
            return 2;
        }
        i++;
    }
    if (port_cd_open(disc) != 0)
    {
        return 1;
    }
    if ((boot && !boot_game(PORT_DEFAULT_SHIM)) ||
        (script != NULL && port_script_load(script) != 0))
        return 1;
    wasm_rt_init();
    wasm2c_rock__neo_instantiate(&module, &env);
    wasm_rt_memory_t *memory = w2c_rock__neo_memory(&module);
    port_aot_mips_bind(memory->data, memory->size);
    if (psx_load_exe(exe, &info) != 0 || (wav != NULL && port_audio_wav_open(wav) != 0))
    {
        return 1;
    }
    mips_gp = info.gp0 ? info.gp0 : 0x80097864u;
    port_kernel_init(mips_gp);
    port_game_init_imports(&env);
    gpu_init();
    gte_reset();
    spu_reset();
    w2c_rock__neo_psx_main(&module);
    port_aot_mips_bind(NULL, 0);
    wasm2c_rock__neo_free(&module);
    wasm_rt_free();
    return 0;
}
