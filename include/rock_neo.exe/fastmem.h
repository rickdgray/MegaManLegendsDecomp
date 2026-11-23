#ifndef FASTMEM_H
#define FASTMEM_H

// asm_fastmem: Capcom's hand-written copy routines.

#include "common.h"

// Unknown (local labels in asm_fastmem until registered)
void Mem_copy4(void *src, void *dst, sint32 words);   // copies words
void Mem_copy16(void *src, void *dst, sint32 blocks); // copies 16-byte blocks
void Mem_copy32(void *src, void *dst, sint32 blocks); // copies 32-byte blocks
void Mem_clear(void *start, void *last);              // zeroes words from start up to and including last
void func_80017734(void);                             // copies the dirty Clut_buf rows (see vram.h); called once per frame by main
void func_8001782C(uint32 *mask, uint32 *dst);        // for 0x40 words: dst &= ~mask
void Stack_to_scratch(void);                          // saves sp at 0x80098B44 and moves the stack to the scratchpad (sp = 0x1F800400)
void Stack_restore(void);                             // restores the sp Stack_to_scratch saved

#endif // FASTMEM_H
