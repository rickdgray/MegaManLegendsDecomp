// Headless entry point for the compiled 64-bit boot shim.
#include "shim_host.h"
#include "psx_mem.h"
#include "gpu.h"
#include "gte.h"
#include "spu.h"
#include "port_audio.h"
#include "port_game.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    const char *exe = PORT_DEFAULT_EXE;
    const char *disc = PORT_DEFAULT_DISC;
    const char *wav = NULL;
    w2c_shim shim;

    port_options.headless = 1;
    port_options.deterministic = 1;
    port_options.max_vblanks = 4500;

    for (int i = 1; i < argc; i++)
    {
        if (i + 1 < argc && strcmp(argv[i], "--exe") == 0)
            exe = argv[++i];
        else if (i + 1 < argc && strcmp(argv[i], "--disc") == 0)
            disc = argv[++i];
        else if (i + 1 < argc && strcmp(argv[i], "--wav") == 0)
            wav = argv[++i];
        else if (i + 1 < argc && strcmp(argv[i], "--dump") == 0)
            port_options.dump = argv[++i];
        else if (i + 1 < argc && strcmp(argv[i], "--dump-at") == 0)
            port_options.dump_at = argv[++i];
        else
        {
            fprintf(stderr, "usage: %s [--exe FILE] [--disc CUE] [--wav FILE] [--dump FILE]"
                            " [--dump-at BLANKS]\n", argv[0]);
            return 2;
        }
    }

    if (port_cd_open(disc) != 0)
        return 1;

    port_aot_shim_start(&shim);
    if (psx_load_exe(exe, NULL) != 0 ||
        (wav != NULL && port_audio_wav_open(wav) != 0))
    {
        port_aot_shim_finish(&shim);
        return 1;
    }
    gpu_init();
    gte_reset();
    spu_reset();
    w2c_shim_psx_main(&shim);
    port_aot_shim_finish(&shim);
    return 1;
}
