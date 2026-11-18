// PS1 memory map in the host process. See psx_mem.h.
#define _GNU_SOURCE
#include "psx_mem.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#ifndef MAP_FIXED_NOREPLACE
#define MAP_FIXED_NOREPLACE 0x100000
#endif

static int mapped;

// Maps `size` bytes at `addr`: from `fd` at `offset` (shared, so several views see the same
// memory), or anonymous memory when fd < 0.
static int map_at(uint32_t addr, uint32_t size, const char *what, int fd, uint32_t offset)
{
    // RWX: the RAM window also holds the jump stubs that stand in for retail function addresses.
    void *want = (void *)(uintptr_t)addr;
    void *got  = mmap(want, size, PROT_READ | PROT_WRITE | PROT_EXEC,
                      (fd >= 0 ? MAP_SHARED : MAP_PRIVATE | MAP_ANONYMOUS) | MAP_FIXED_NOREPLACE,
                      fd, (off_t)offset);

    if (got == MAP_FAILED)
    {
        fprintf(stderr, "psx_mem: cannot map %s at 0x%08X: %s\n", what, addr, strerror(errno));
        return -1;
    }
    if (got != want)
    {
        // Kernels before 4.17 ignore MAP_FIXED_NOREPLACE and treat the address as a hint.
        fprintf(stderr, "psx_mem: %s landed at %p instead of 0x%08X\n", what, got, addr);
        munmap(got, size);
        return -1;
    }
    return 0;
}

// RAM is one memory object mapped twice: at KSEG0 0x80000000, where the game's addresses point,
// and at KUSEG 0x00010000 and up, the same memory without the segment bit. The game strips the
// segment bits from addresses it reads out of its data (`(uint32 *)(p & 0xFFFFFF)` in the
// lighting and model code), and on the console those KUSEG addresses reach the same RAM. The
// first 64 KB (the BIOS kernel area) can't be mapped there (vm.mmap_min_addr); the game reaches
// it through KERNEL_ADDR. When the memory object can't be made, RAM is plain anonymous memory
// without the mirror.
int psx_mem_init(void)
{
    int fd;

    if (mapped)
    {
        return 0;
    }
    fd = memfd_create("psx_ram", 0);
    if (fd >= 0 && ftruncate(fd, PSX_RAM_WINDOW) != 0)
    {
        close(fd);
        fd = -1;
    }
    if (map_at(PSX_RAM_BASE, PSX_RAM_WINDOW, "main RAM", fd, 0) != 0)
    {
        return -1;
    }
    if (fd >= 0)
    {
        if (map_at(PSX_KUSEG_MIRROR, PSX_RAM_WINDOW - PSX_KUSEG_MIRROR, "KUSEG mirror", fd,
                   PSX_KUSEG_MIRROR) != 0)
        {
            fprintf(stderr, "psx_mem: continuing without the KUSEG mirror\n");
        }
        close(fd);
    }
    if (map_at(PSX_SCRATCH_BASE, PSX_SCRATCH_PAGE, "scratchpad", -1, 0) != 0)
    {
        munmap((void *)(uintptr_t)PSX_RAM_BASE, PSX_RAM_WINDOW);
        return -1;
    }
    mapped = 1;
    return 0;
}

void *psx_ptr(uint32_t addr)
{
    if ((addr & 0xFFFFFC00u) == PSX_SCRATCH_BASE)
    {
        return (void *)(uintptr_t)addr;
    }
    // KUSEG 0x00xxxxxx, KSEG0 0x80xxxxxx and KSEG1 0xA0xxxxxx all reach the same RAM; so does
    // the 24-bit address in an ordering-table tag.
    switch (addr >> 24)
    {
        case 0x00:
        case 0x80:
        case 0xA0:
            return (void *)(uintptr_t)(PSX_RAM_BASE | (addr & (PSX_RAM_WINDOW - 1)));
        default:
            return NULL;
    }
}

uint32_t psx_addr(const void *p)
{
    return (uint32_t)(uintptr_t)p;
}

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
    if ((in.t_addr >> 24) != 0x80 || in.t_addr + in.t_size > PSX_RAM_BASE + PSX_RAM_SIZE)
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

int psx_install_stub(uint32_t addr, void (*native)(void))
{
    uint8_t *p       = psx_ptr(addr);
    uintptr_t target = (uintptr_t)native;

    if (p == NULL || (addr >> 24) != 0x80)
    {
        return -1;
    }
#if defined(__i386__)
    {
        uint32_t rel = (uint32_t)(target - ((uintptr_t)p + 5));
        p[0]         = 0xE9; // jmp rel32
        memcpy(p + 1, &rel, 4);
    }
#elif defined(__x86_64__)
    // jmp [rip+0] followed by the 64-bit target (14 bytes; 64-bit builds are for tests only)
    p[0] = 0xFF;
    p[1] = 0x25;
    memset(p + 2, 0, 4);
    memcpy(p + 6, &target, 8);
#else
#error "psx_install_stub: unsupported host"
#endif
    return 0;
}
