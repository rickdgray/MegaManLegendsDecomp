// mml: Mega Man Legends, natively. Loads the owner's ROCK_NEO.EXE into the PS1 memory window
// (its data is the game's data; its code is replaced function by function with the native
// build's), installs the stub table, and runs ROCK_NEO.EXE's main.
//
// Compiled with -DPORT_SHIM this is `mml_boot`, the boot shim (SLUS_006.03: the Capcom logo
// movie, then LoadExec) on the same runtime; its LoadExec runs `mml` with the same arguments
// (port/psyq/shim_psyq.c). The shim writes its --wav and --dump files with "-boot" in the name.
//
// Usage: mml [options] [path/to/ROCK_NEO.EXE]
//        mml_boot [options] [path/to/SLUS_006.03]
//   --headless          no window (the only mode until 32-bit SDL3 is installed)
//   --frames N          stop after N drawn frames
//   --vblanks N         stop after N vertical blanks (also catches a game that stops drawing)
//   --fast N            run the vertical blank at N Hz instead of 60
//   --dump FILE         write VRAM to FILE (PPM) when stopping
//   --stop-on-cd        stop at the first CD read
//   --disc PATH         the disc image: a .cue file or a directory with one (default disc/image)
//   --cd-speed N        run the CD drive N times faster than the hardware
//   --buttons MASK      headless: buttons held on pad 1 (PS1 bits, e.g. 0x0008 = Start)
//   --input SCRIPT      scripted pad 1 presses: VBLANK:MASK[:LEN],... (LEN blanks, default 6)
//   --dump-at V1,V2     also dump VRAM at these vblank counts, to DUMP-V.ppm
//   --wav FILE          also write the sound to FILE (16-bit stereo 44.1 kHz WAV, game time)
//   --mute              no audio device (the window build plays sound by default)
//   --verbose           log every frame
//   --poke SCRIPT       testing: VBLANK:ADDR=BYTE,... writes PS1 memory at those blanks
//   --watch ADDR:LEN,.. testing: logs those bytes of PS1 memory every 60 blanks
//   --config FILE       settings file (default $XDG_CONFIG_HOME/megaman-legends/config.ini)
//   --card1 PATH        memory card image in slot 1 (default from the settings: card1.mcd in
//   --card2 PATH        $XDG_DATA_HOME/megaman-legends/); "" leaves the slot empty
//   --vanilla           the original game, no start-up menu
//   --mods LIST         a modded run with these mods (ids separated by commas, `all`, `none`,
//                       or `default` for the settings' [mods] enabled), no start-up menu;
//                       memory cards from [cards] slot1_mods/slot2_mods
#include "gpu.h"
#include "gte.h"
#include "mips_cpu.h"
#include "mods.h"
#include "port_audio.h"
#include "port_config.h"
#include "port_game.h"
#include "port_remote.h"
#include "port_script.h"
#include "port_stubs.h"
#include "psx_mem.h"
#include "spu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PORT_DEFAULT_DISC
#define PORT_DEFAULT_DISC "disc/image"
#endif
#ifndef PORT_DEFAULT_EXE
#define PORT_DEFAULT_EXE "disc/extracted/ROCK_NEO.EXE"
#endif

#ifdef PORT_SHIM
extern char **port_shim_argv; // port/psyq/shim_psyq.c

// FILE.ext -> FILE-boot.ext: the shim's own output files, so the game's keep their names.
static const char *boot_name(const char *path)
{
    const char *dot = strrchr(path, '.'), *slash = strrchr(path, '/');
    size_t stem     = dot != NULL && (slash == NULL || dot > slash) ? (size_t)(dot - path)
                                                                    : strlen(path);
    char *s         = malloc(strlen(path) + 6);

    memcpy(s, path, stem);
    strcpy(s + stem, "-boot");
    strcat(s, path + stem);
    return s;
}
#endif

void psx_main(void);                // src/rock_neo.exe/main.c (main, renamed for the port)
void port_kernel_init(uint32_t gp); // port/psyq/libapi.c

static int usage(void)
{
    fprintf(stderr, "usage: mml [--headless] [--frames N] [--vblanks N] [--fast HZ] [--dump FILE]\n"
                    "           [--stop-on-cd] [--disc PATH] [--cd-speed N] [--buttons MASK]\n"
                    "           [--input SCRIPT] [--dump-at V1,V2,...]\n"
                    "           [--wav FILE] [--mute] [--verbose] [--config FILE]\n"
                    "           [--deterministic | --realtime] [--script FILE] [--serve DIR]\n"
                    "           [--card1 PATH] [--card2 PATH] [--vanilla | --mods LIST]\n"
                    "           [ROCK_NEO.EXE]\n");
    return 2;
}

int main(int argc, char **argv)
{
    const char *exe  = PORT_DEFAULT_EXE;
    const char *disc = NULL;
    const char *config = NULL, *card[2] = {NULL, NULL};
    const char *wav = NULL;
    const char *mods_cli = NULL; // --vanilla ("vanilla") or --mods LIST
    int mods_ask;
    PSX_EXE_INFO info;
    int mute = 0;
    int clock_mode = -1; // --deterministic / --realtime; by default game-paced when headless
    int i, n;

    port_options.headless = 0;
    for (i = 1; i < argc; i++)
    {
        const char *a = argv[i];
        const char *v = i + 1 < argc ? argv[i + 1] : NULL;

        if (strcmp(a, "--headless") == 0)
        {
            port_options.headless = 1;
        }
        else if (strcmp(a, "--frames") == 0 && v != NULL)
        {
            port_options.max_frames = atoi(v);
            i++;
        }
        else if (strcmp(a, "--vblanks") == 0 && v != NULL)
        {
            port_options.max_vblanks = atoi(v);
            i++;
        }
        else if (strcmp(a, "--fast") == 0 && v != NULL)
        {
            port_options.vblank_hz = atoi(v);
            i++;
        }
        else if (strcmp(a, "--dump") == 0 && v != NULL)
        {
            port_options.dump = v;
            i++;
        }
        else if (strcmp(a, "--buttons") == 0 && v != NULL)
        {
            port_options.buttons = (uint16_t)strtoul(v, NULL, 0);
            i++;
        }
        else if (strcmp(a, "--input") == 0 && v != NULL)
        {
            port_options.input = v;
            i++;
        }
        else if (strcmp(a, "--dump-at") == 0 && v != NULL)
        {
            port_options.dump_at = v;
            i++;
        }
        else if (strcmp(a, "--stop-on-cd") == 0)
        {
            port_options.stop_on_cd = 1;
        }
        else if (strcmp(a, "--disc") == 0 && v != NULL)
        {
            disc = v;
            i++;
        }
        else if (strcmp(a, "--cd-speed") == 0 && v != NULL)
        {
            port_cd_speed = atoi(v) > 0 ? atoi(v) : 1;
            i++;
        }
        else if (strcmp(a, "--wav") == 0 && v != NULL)
        {
            wav = v;
            i++;
        }
        else if (strcmp(a, "--mute") == 0)
        {
            mute = 1;
        }
        else if (strcmp(a, "--poke") == 0 && v != NULL)
        {
            port_options.poke = v;
            i++;
        }
        else if (strcmp(a, "--watch") == 0 && v != NULL)
        {
            port_options.watch = v;
            i++;
        }
        else if (strcmp(a, "--config") == 0 && v != NULL)
        {
            config = v;
            i++;
        }
        else if ((strcmp(a, "--card1") == 0 || strcmp(a, "--card2") == 0) && v != NULL)
        {
            card[a[6] - '1'] = v;
            i++;
        }
        else if (strcmp(a, "--script") == 0 && v != NULL)
        {
            if (port_script_load(v) != 0)
            {
                return 1;
            }
            i++;
        }
        else if (strcmp(a, "--serve") == 0 && v != NULL)
        {
            port_options.serve_dir = v;
            i++;
        }
        else if (strcmp(a, "--deterministic") == 0)
        {
            clock_mode = 1;
        }
        else if (strcmp(a, "--realtime") == 0)
        {
            clock_mode = 0;
        }
        else if (strcmp(a, "--vanilla") == 0)
        {
            mods_cli = "vanilla";
        }
        else if (strcmp(a, "--mods") == 0 && v != NULL)
        {
            mods_cli = v;
            i++;
        }
        else if (strcmp(a, "--verbose") == 0)
        {
            port_options.verbose = 1;
        }
        else if (a[0] == '-')
        {
            return usage();
        }
        else
        {
            exe = a;
        }
    }

    port_options.deterministic = clock_mode >= 0 ? clock_mode : port_options.headless;

    // Settings: written out with their defaults the first time a window opens without them.
    if (port_config_load(config, !port_options.headless) != 0)
    {
        return 1;
    }
    if (card[0] != NULL)
    {
        port_config_set("cards", "slot1", card[0]);
    }
    if (card[1] != NULL)
    {
        port_config_set("cards", "slot2", card[1]);
        port_config_set("cards", "slot2_insert", "yes");
    }
    port_config_apply_cards();
    // Vanilla or mods (port/mods/): the start-up menu asks only in a window of its own (not
    // headless, not the game under the boot shim's window, which gets the choice in argv).
    mods_ask = mods_configure(mods_cli, port_options.headless || getenv(PORT_REMOTE_ENV) != NULL);
    if (mods_ask < 0)
    {
        return 2;
    }
    if (disc == NULL)
    {
        const char *d = port_config_get("game", "disc");

        disc = d != NULL && *d != 0 ? d : PORT_DEFAULT_DISC;
    }

#ifdef PORT_SHIM
    port_shim_argv = argv;
    if (wav != NULL)
    {
        wav = boot_name(wav);
    }
    if (port_options.dump != NULL)
    {
        port_options.dump = boot_name(port_options.dump);
    }
#endif
    if (psx_mem_init() != 0 || psx_load_exe(exe, &info) != 0)
    {
        return 1;
    }
    n = port_install_stubs();
    if (n < 0)
    {
        return 1;
    }
    port_log("loaded %s (0x%X bytes at 0x%08X); %d functions at retail addresses", exe, info.t_size,
             info.t_addr, n);
    if (port_cd_open(disc) != 0)
    {
        port_log("no disc image at %s: the game will wait at its first CD read", disc);
    }
    port_kernel_init(info.gp0);
    // The header leaves gp 0 (the start-up code sets it); the overlays address ROCK_NEO.EXE's small
    // data through it (gp = 0x80097864).
    mips_gp = info.gp0 != 0 ? info.gp0 : 0x80097864u;
#ifndef PORT_SHIM // the shim loads no overlays
    if (port_overlay_init() != 0)
    {
        return 1;
    }
#endif
    gpu_init();
    gte_reset();
    spu_reset();
    if (wav != NULL && port_audio_wav_open(wav) != 0)
    {
        return 1;
    }
    if (!port_options.headless && port_window_open("Mega Man Legends", 2) != 0)
    {
        fprintf(stderr, "mml: this build has no window support (needs 32-bit SDL3); use "
                        "--headless\n");
        return 1;
    }
    if (!port_options.headless && !mute && !port_config_bool("audio", "mute", 0) &&
        port_audio_device_open() != 0)
    {
        port_log("no audio device: running silent");
    }
    if (mods_ask == 1 && !port_options.headless)
    {
        mods_startup_menu();
    }
    mods_apply_cards(card[0] != NULL, card[1] != NULL); // a modded run's own saves
#ifdef PORT_SHIM
    port_shim_argv = mods_child_argv(argv); // the game gets the choice, so it does not ask
#else
    mods_start(); // the enabled mods' hooks; nothing in a vanilla run
#endif

    psx_main();
    port_stop(0, "main returned");
}
