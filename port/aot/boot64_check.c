// Exercise compiled boot shim code with the original data image inside linear memory.
#include "shim_host.h"
#include "shim_addresses.h"
#include "psx_mem.h"
#include "mips_cpu.h"
#include "mips_memory.h"
#include "gpu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK(test)                                                                                \
    do                                                                                            \
    {                                                                                             \
        if (!(test))                                                                              \
        {                                                                                         \
            fprintf(stderr, "boot64_check:%d: %s failed\n", __LINE__, #test);                        \
            return EXIT_FAILURE;                                                                  \
        }                                                                                         \
    } while (0)

static uint32_t read_word(const uint8_t *p)
{
    return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
}

static void write_word(uint8_t *p, uint32_t value)
{
    p[0] = value;
    p[1] = value >> 8;
    p[2] = value >> 16;
    p[3] = value >> 24;
}

static int check_shim(w2c_shim *shim)
{
    wasm_rt_memory_t *memory = w2c_shim_memory(shim);
    uint8_t *ram = memory->data;
    uint8_t *joy1 = ram + RETAIL_Joy1;
    uint8_t *joy2 = ram + RETAIL_Joy2;
    const uint32_t no_args[8] = {0};

    port_aot_mips_bind(ram, memory->size);
    write_word(ram + RETAIL_Vsync_count, UINT32_MAX);
    w2c_shim_Vsync_handler(shim);
    CHECK(read_word(ram + RETAIL_Vsync_count) == 0);
    w2c_shim_Vsync_handler(shim);
    uint32_t vsync = read_word(ram + RETAIL_Vsync_count);

    write_word(ram + RETAIL_Vsync_count, UINT32_MAX);
    mips_call(RETAIL_Vsync_handler, no_args);
    mips_call(RETAIL_Vsync_handler, no_args);
    CHECK(vsync == 1 && vsync == read_word(ram + RETAIL_Vsync_count));

    // One connected pad presses Cross. The disconnected pad has stale button data.
    uint8_t pad_input[2][0x38] = {
        {0, 0x41, 0xFF, 0xBF, 0x10, 0x20, 0x30, 0x40},
        {[0] = 0xFF, [0x26] = 0xFF},
    };
    uint8_t pad_output[2][2][0x38];
    memcpy(joy1, pad_input[0], sizeof(pad_input[0]));
    memcpy(joy2, pad_input[1], sizeof(pad_input[1]));
    for (unsigned i = 0; i < 2; i++)
    {
        w2c_shim_Pad_update_all(shim);
        memcpy(pad_output[i][0], joy1, sizeof(pad_output[i][0]));
        memcpy(pad_output[i][1], joy2, sizeof(pad_output[i][1]));
    }
    CHECK(pad_output[0][0][0x24] == 4);
    CHECK(read_word(pad_output[0][0] + 0x28) == 0x40000000u);
    CHECK(read_word(pad_output[1][0] + 0x28) == 0x00004000u);
    memcpy(joy1, pad_input[0], sizeof(pad_input[0]));
    memcpy(joy2, pad_input[1], sizeof(pad_input[1]));
    for (unsigned i = 0; i < 2; i++)
    {
        mips_call(RETAIL_Pad_update_all, no_args);
        CHECK(memcmp(pad_output[i][0], joy1, sizeof(pad_output[i][0])) == 0);
        CHECK(memcmp(pad_output[i][1], joy2, sizeof(pad_output[i][1])) == 0);
    }

    uint8_t *queue = ram + RETAIL_Cd_cmd_queue;
    uint8_t *queue_ptr = ram + RETAIL_Cd_cmd_write_ptr;
    const uint32_t movie_args[8] = {0xD0, 145, 0x2008};
    uint8_t command[16];

    write_word(queue_ptr, RETAIL_Cd_cmd_queue);
    CHECK(w2c_shim_Cd_read_sync2(shim) == 0);
    CHECK(mips_call(RETAIL_Cd_read_sync2, no_args) == 0);
    memset(queue, 0, sizeof(command));
    w2c_shim_Cd_cmd_set_movie(shim, movie_args[0], movie_args[1], movie_args[2]);
    CHECK(w2c_shim_Cd_read_sync2(shim) == 1);
    CHECK(read_word(queue_ptr) == RETAIL_Cd_cmd_queue + sizeof(command));
    memcpy(command, queue, sizeof(command));

    write_word(queue_ptr, RETAIL_Cd_cmd_queue);
    memset(queue, 0, sizeof(command));
    mips_call(RETAIL_Cd_cmd_set_movie, movie_args);
    CHECK(mips_call(RETAIL_Cd_read_sync2, no_args) == 1);
    CHECK(read_word(queue_ptr) == RETAIL_Cd_cmd_queue + sizeof(command));
    CHECK(memcmp(command, queue, sizeof(command)) == 0);

    // Dispatch using the function addresses in both retail tables. The intro advances
    // after the CD queue drains, and the movie command writes to the scratchpad.
    uint8_t *intro = ram + RETAIL_Intro_routine_0;
    uint8_t *wait = ram + PSX_SCRATCH_BASE + 1;
    uint8_t *routine = ram + RETAIL_Cd_cmd_routine;
    uint8_t *playing = ram + RETAIL_Cd_movie_playing;
    for (unsigned reference = 0; reference < 2; reference++)
    {
        memset(queue, 0, 48);
        write_word(queue, 5);
        write_word(queue_ptr, RETAIL_Cd_cmd_queue + sizeof(command));
        write_word(ram + RETAIL_Cd_cmd_exec_ptr, RETAIL_Cd_cmd_queue);
        write_word(routine, 5);
        write_word(playing, 1);
        *wait = 1;
        intro[0] = intro[1] = 1;

        if (reference)
        {
            mips_call(RETAIL_Intro_task, no_args);
            CHECK(intro[0] == 1 && intro[1] == 1);
            mips_call(RETAIL_Cd_cmd_exec, no_args);
            mips_call(RETAIL_Intro_task, no_args);
        }
        else
        {
            w2c_shim_Intro_task(shim);
            CHECK(intro[0] == 1 && intro[1] == 1);
            w2c_shim_Cd_cmd_exec(shim);
            w2c_shim_Intro_task(shim);
        }
        CHECK(read_word(queue) == 0 && read_word(queue_ptr) == RETAIL_Cd_cmd_queue);
        CHECK(read_word(playing) == 0 && read_word(routine) == 0);
        CHECK(*wait == 2);
        CHECK(intro[0] == 2 && intro[1] == 0);
    }

    static uint16_t expected_vram[GPU_VRAM_W * GPU_VRAM_H];
    // 160 SPRTs of five words, followed by ten DR_MODE packets of three words.
    uint8_t expected_packets[160 * 20 + 10 * 12];
    uint8_t *packets = ram + RETAIL_copyright_sprt;

    gpu_init();
    memset(packets, 0, sizeof(expected_packets));
    w2c_shim_Intro_init(shim);
    memcpy(expected_vram, gpu_vram(), sizeof(expected_vram));
    memcpy(expected_packets, packets, sizeof(expected_packets));
    CHECK(expected_packets[3] == 4); // SPRT packet length
    unsigned visible_pixels = 0;
    for (size_t i = 0; i < sizeof(expected_vram) / sizeof(expected_vram[0]); i++)
    {
        visible_pixels += expected_vram[i] != 0;
    }
    CHECK(visible_pixels > 0);

    gpu_init();
    memset(packets, 0, sizeof(expected_packets));
    mips_call(RETAIL_Intro_init, no_args);
    CHECK(memcmp(expected_vram, gpu_vram(), sizeof(expected_vram)) == 0);
    CHECK(memcmp(expected_packets, packets, sizeof(expected_packets)) == 0);

    port_aot_mips_bind(NULL, 0);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    w2c_shim shim;
    int result = EXIT_FAILURE;

    CHECK(argc == 2);
    CHECK(sizeof(void *) == 8);
    port_aot_shim_start(&shim);
    if (psx_load_exe(argv[1], NULL) == 0)
    {
        result = check_shim(&shim);
    }
    port_aot_shim_finish(&shim);
    if (result == EXIT_SUCCESS)
    {
        puts("boot64_check: native boot shim checks passed");
    }
    return result;
}
