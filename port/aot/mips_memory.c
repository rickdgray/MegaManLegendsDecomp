#include "mips_memory.h"
#include "psx_mem.h"

#include <stdio.h>
#include <stdlib.h>

static uint8_t *linear_memory;
static uint64_t linear_size;

void port_aot_mips_bind(uint8_t *memory, uint64_t size)
{
    linear_memory = memory;
    linear_size = size;
}

void *port_aot_memory_span(uint32_t address, size_t size)
{
    // The ordinary runtime uses fixed host mappings or raw host stack pointers. Under AOT,
    // MIPS RAM and its mirrors all reach the same offset in the module's linear memory.
    switch (address >> 24)
    {
        case 0x00:
        case 0x80:
        case 0xA0:
            address = PSX_RAM_BASE | (address & (PSX_RAM_WINDOW - 1));
            break;
        default:
            if (address < PSX_SCRATCH_BASE || address >= PSX_SCRATCH_BASE + PSX_SCRATCH_SIZE ||
                size > PSX_SCRATCH_BASE + PSX_SCRATCH_SIZE - address)
            {
                return NULL;
            }
            break;
    }
    if (address >= linear_size || size > linear_size - address)
    {
        return NULL;
    }
    return linear_memory + address;
}

void *psx_ptr(uint32_t address)
{
    return port_aot_memory_span(address, 1);
}

void *port_aot_mips_ptr(uint32_t address)
{
    void *p = psx_ptr(address);

    if (p == NULL)
    {
        fprintf(stderr, "boot64_check: MIPS address 0x%08X outside guest memory\n", address);
        abort();
    }
    return p;
}

uint32_t psx_addr(const void *pointer)
{
    uintptr_t base = (uintptr_t)linear_memory;
    uintptr_t p = (uintptr_t)pointer;

    if (p < base || p - base >= linear_size)
    {
        return 0;
    }
    return (uint32_t)(p - base);
}
