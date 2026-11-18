#ifndef PORT_AOT_MIPS_MEMORY_H
#define PORT_AOT_MIPS_MEMORY_H

#include <stddef.h>
#include <stdint.h>

// The reference interpreter borrows the AOT module's linear memory for one call.
void port_aot_mips_bind(uint8_t *memory, uint64_t size);
void *port_aot_memory_span(uint32_t address, size_t size);
void *port_aot_mips_ptr(uint32_t address);

#endif
