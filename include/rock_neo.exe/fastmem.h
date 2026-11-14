#ifndef FASTMEM_H
#define FASTMEM_H

// asm_fastmem: Capcom's hand-written copy routines.

#include "common.h"

// Unknown (local labels in asm_fastmem until registered)
void Mem_copy4(void *src, void *dst, sint32 words);   // copies words
void Mem_copy16(void *src, void *dst, sint32 blocks); // copies 16-byte blocks
void Mem_copy32(void *src, void *dst, sint32 blocks); // copies 32-byte blocks
void func_800177CC(void *start, void *last);          // zeroes words from start up to and including last

#endif // FASTMEM_H
