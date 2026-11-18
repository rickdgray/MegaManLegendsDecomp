// Load a PS-X EXE into the active PS1 memory backend.
#include "psx_mem.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

static uint32_t le32(const uint8_t *b)
{
    return (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
}

int psx_load_exe(const char *path, PSX_EXE_INFO *info)
{
    uint8_t hdr[0x800];
    PSX_EXE_INFO in;
    FILE *f = fopen(path, "rb");

    if (f == NULL)
    {
        fprintf(stderr, "psx_mem: cannot open %s: %s\n", path, strerror(errno));
        return -1;
    }
    if (fread(hdr, 1, sizeof(hdr), f) != sizeof(hdr) || memcmp(hdr, "PS-X EXE", 8) != 0)
    {
        fprintf(stderr, "psx_mem: %s is not a PS-X EXE\n", path);
        fclose(f);
        return -1;
    }
    in.pc0    = le32(hdr + 0x10);
    in.gp0    = le32(hdr + 0x14);
    in.t_addr = le32(hdr + 0x18);
    in.t_size = le32(hdr + 0x1C);
    in.b_addr = le32(hdr + 0x28);
    in.b_size = le32(hdr + 0x2C);
    in.s_addr = le32(hdr + 0x30);
    in.s_size = le32(hdr + 0x34);
    if (in.t_addr < PSX_RAM_BASE || in.t_addr > PSX_RAM_BASE + PSX_RAM_SIZE ||
        in.t_size > PSX_RAM_BASE + PSX_RAM_SIZE - in.t_addr || psx_ptr(in.t_addr) == NULL)
    {
        fprintf(stderr, "psx_mem: %s loads outside RAM (0x%08X + 0x%X)\n", path, in.t_addr,
                in.t_size);
        fclose(f);
        return -1;
    }
    if (fread(psx_ptr(in.t_addr), 1, in.t_size, f) != in.t_size)
    {
        fprintf(stderr, "psx_mem: %s is truncated\n", path);
        fclose(f);
        return -1;
    }
    fclose(f);
    if (in.b_size != 0 && psx_ptr(in.b_addr) != NULL)
    {
        memset(psx_ptr(in.b_addr), 0, in.b_size);
    }
    if (info != NULL)
    {
        *info = in;
    }
    return 0;
}

