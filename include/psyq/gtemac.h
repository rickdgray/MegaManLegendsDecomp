#ifndef PSYQ_GTEMAC_H
#define PSYQ_GTEMAC_H

/*
 * PsyQ's gtemac.h read_* macros: move a GTE result into a variable (mfc2), for code that runs a
 * GTE command itself (the libgte "_nom" functions, or the inline_c.h command macros). The names
 * are Sony's (the Library Reference's "_nom" entries: "opz is read by macro read_opz"); the
 * bodies are self-written from the game's code, not copied from Sony's header.
 *
 * Data register 24 = MAC0 (OPZ after NCLIP).
 */

// Read the outer product (MAC0; after NCLIP, > 0 means the face is toward the camera) into r0.
#define read_opz(r0) __asm__ volatile("mfc2 %0, $24" : "=r"(r0))

#endif
