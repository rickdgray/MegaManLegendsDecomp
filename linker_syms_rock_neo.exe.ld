/* Symbols the linker must compute so the program can move (tools/shift_test.py).
   Passed to ld by tools/build.sh before splat's linker script. */

/* End of BSS: PsyQ's start clears BSS up to here and stup1 starts the heap here. */
D_800C5688 = main_BSS_END;

/* PS-X EXE header fields (tools/build.sh assembles splat's header with these). */
EXE_ENTRY = start;
EXE_TEXT_START = main_VRAM;
EXE_TEXT_SIZE = tail_ROM_END - main_ROM_START;

/* Addresses asm_fastmem builds with lui/ori: the lui takes the plain high half, which %hi()
   rounds up for a low half of 0x8000 or more. tools/build.sh rewrites each
   `lui (0xADDR >> 16)` / `ori (0xADDR & 0xFFFF)` pair it finds a LUI_ADDR for here into
   `%hi(LUI_ADDR)` / `%lo(SYMBOL)`; %hi() of SYMBOL - 0x8000 is SYMBOL's plain high half.
   ld warns that these HI16 relocations have no matching LO16; that is intended. */
LUI_80098B44 = D_80098B44 - 0x8000;
LUI_80098B68 = D_80098B68 - 0x8000;
LUI_80098868 = D_80098868 - 0x8000;
LUI_800AD168 = D_800AD168 - 0x8000;
