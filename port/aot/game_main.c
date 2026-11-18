// Entry for the compiled boot shim and base game: headless by default (tests), or with
// --window a window with sound and gamepads, paced in real time on the game-paced clock.
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
#include "port_config.h"
#include "mods.h"
#include "shim_host.h"
#include "spu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef PORT_APPLETV
// The Apple TV app: SDL provides the UIKit entry point and calls main() below. The disc and the
// two executables are in the app bundle; settings and memory cards go to SDL's per-app folder.
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#endif

extern void port_kernel_init(uint32_t gp);
extern int port_game_trace_imports;
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
    const char *shim = PORT_DEFAULT_SHIM;
    int boot = 1;
    int window = 0;
    int vblanks_set = 0;
    const char *card1 = NULL;
    const char *mods_cli = NULL; // --vanilla / --mods LIST (port/mods/mods.h)
    int mods_ask;

    port_options.headless = 1;
    port_options.deterministic = 1;
    port_options.max_vblanks = 40000;
#ifdef PORT_APPLETV
    {
        static char exe_path[1024], shim_path[1024], disc_path[1024];
        const char *base = SDL_GetBasePath();
        char *pref = SDL_GetPrefPath("CoastRedWood", "MegaManLegends");

        snprintf(exe_path, sizeof(exe_path), "%sgame/ROCK_NEO.EXE", base ? base : "");
        snprintf(shim_path, sizeof(shim_path), "%sgame/SLUS_006.03", base ? base : "");
        snprintf(disc_path, sizeof(disc_path), "%sgame/disc", base ? base : "");
        exe  = exe_path;
        shim = shim_path;
        disc = disc_path;
        if (pref != NULL)
        {
            setenv("XDG_CONFIG_HOME", pref, 1);
            setenv("XDG_DATA_HOME", pref, 1);
            SDL_free(pref);
        }
        window                  = 1;
        port_game_trace_imports = 1;
        // The Siri Remote is not a game controller: without this it would be pad 1 and the
        // Xbox controller pad 2.
        SDL_SetHint(SDL_HINT_TV_REMOTE_AS_JOYSTICK, "0");
    }
#endif
    for (int i = 1; i < argc; i++)
    {
        const char *option = argv[i];
        const char *value = i + 1 < argc ? argv[i + 1] : NULL;

        if (strcmp(option, "--headless") == 0 || strcmp(option, "--deterministic") == 0)
            continue;
        if (strcmp(option, "--window") == 0)
        {
            window = 1;
            continue;
        }
        if (strcmp(option, "--trace-imports") == 0)
        {
            port_game_trace_imports = 1;
            continue;
        }
        if (strcmp(option, "--vanilla") == 0)
        {
            mods_cli = "vanilla";
            continue;
        }
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
        {
            port_options.max_vblanks = atoi(value);
            vblanks_set              = 1;
        }
        else if (strcmp(option, "--dump") == 0)
            port_options.dump = value;
        else if (strcmp(option, "--dump-at") == 0)
            port_options.dump_at = value;
        else if (strcmp(option, "--shim") == 0)
            shim = value;
        else if (strcmp(option, "--wav") == 0)
            wav = value;
        else if (strcmp(option, "--card1") == 0)
            card1 = value;
        else if (strcmp(option, "--mods") == 0)
            mods_cli = value;
        else if (strcmp(option, "--script") == 0)
            script = value;
        else
        {
            fprintf(stderr, "game64: unknown option %s\n", option);
            return 2;
        }
        i++;
    }
    if (window)
    {
        port_options.headless    = 0;
        port_options.paced       = 1;
        if (!vblanks_set)
        {
            port_options.max_vblanks = 0;
        }
        if (port_config_load(NULL, 1) != 0)
        {
            return 1;
        }
        port_config_apply_cards();
    }
    if (card1 != NULL)
    {
        memcard_set_path(0, card1, 1);
    }
    // Vanilla or mods: in a window [mods] startup decides (the menu by default); headless runs
    // are vanilla unless --mods says otherwise.
    mods_ask = mods_configure(mods_cli, !window);
    if (mods_ask < 0)
    {
        return 2;
    }
    if (port_cd_open(disc) != 0)
    {
        return 1;
    }
    if (window)
    {
        if (port_window_open("Mega Man Legends", 2) != 0)
        {
            fprintf(stderr, "game64: this build has no window support (needs SDL3)\n");
            return 1;
        }
        if (!port_config_bool("audio", "mute", 0) && port_audio_device_open() != 0)
        {
            port_log("no audio device: running silent");
        }
        if (mods_ask == 1)
        {
            mods_startup_menu();
        }
    }
    mods_apply_cards(card1 != NULL, 0); // a modded run's own saves
    if ((boot && !boot_game(shim)) ||
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
    mods_start(); // the enabled mods' hooks; nothing in a vanilla run
    gpu_init();
    gte_reset();
    spu_reset();
    w2c_rock__neo_psx_main(&module);
    port_aot_mips_bind(NULL, 0);
    wasm2c_rock__neo_free(&module);
    wasm_rt_free();
    return 0;
}
