/* Symbols the linker must compute so the program can move (tools/shift_test.py).
   Passed to ld by tools/build.sh before splat's linker script. */

/* End of BSS: PsyQ's start clears BSS up to here and stup1 starts the heap here. */
D_8005DA40 = main_BSS_END;

/* PS-X EXE header fields (tools/build.sh assembles splat's header with these). */
EXE_ENTRY = start;
EXE_TEXT_START = main_VRAM;
EXE_TEXT_SIZE = sector_padding_ROM_END - main_ROM_START;
