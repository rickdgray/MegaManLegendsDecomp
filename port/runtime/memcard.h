// PS1 memory cards as raw 128 KB image files (the `.mcd`/`.mcr` format emulators use: 16 blocks
// of 8 KB, 64 frames of 128 bytes each; block 0 holds the "MC" header and the directory).
//
// A slot is backed by a file path. The image is kept in memory and written back whole (to a
// temporary file, then renamed over the old one) after every change, so a crash never leaves a
// half-written card. A missing file reads as a freshly formatted card when the slot is set to
// "create" (slot 1 by default) and as an empty slot otherwise; the file appears with the first
// write. A file changed by another program is read again at the next card check, which the game
// sees as a new card having been inserted.
#ifndef PORT_MEMCARD_H
#define PORT_MEMCARD_H

#include <stdint.h>

#define MEMCARD_SLOTS       2
#define MEMCARD_SIZE        0x20000
#define MEMCARD_FRAME       128
#define MEMCARD_FRAMES      (MEMCARD_SIZE / MEMCARD_FRAME)
#define MEMCARD_BLOCK       0x2000
#define MEMCARD_BLOCKS      16 // block 0 is the directory; 1..15 hold data
#define MEMCARD_NAME_MAX    20

// Sets the file behind `slot` (0 or 1). `create`: a missing file is an inserted, formatted card.
// A NULL path leaves the slot empty.
void memcard_set_path(int slot, const char *path, int create);
const char *memcard_path(int slot);

// Card checks. memcard_poll re-reads the file if it changed on disk and returns 1 when the card
// counts as newly inserted (the first check after start-up, or a changed file), 0 otherwise,
// -1 when the slot is empty.
int memcard_poll(int slot);
int memcard_present(int slot);
int memcard_formatted(int slot);
// The game acknowledged the new card (its _card_clear or a sector write).
void memcard_ack(int slot);

// Raw frames (128 bytes).
int memcard_read_frame(int slot, int frame, uint8_t *buf);
int memcard_write_frame(int slot, int frame, const uint8_t *buf);

// A freshly formatted card (header, free directory, empty broken-sector list).
int memcard_format(int slot);
void memcard_format_image(uint8_t *image);

// Files. A file is identified by its first block (1..15).
typedef struct
{
    char name[MEMCARD_NAME_MAX + 1];
    uint32_t size; // bytes, a multiple of 8 KB
    int first;     // first block
} MEMCARD_FILE;

// Fills `out` with the index-th used file (in directory order); returns 1, or 0 past the end.
int memcard_file_at(int slot, int index, MEMCARD_FILE *out);
// Looks a file up by name; returns its first block, or -1.
int memcard_find(int slot, const char *name, MEMCARD_FILE *out);
// Allocates `blocks` blocks under `name`; returns the first block, or -1 (exists, no room).
int memcard_create(int slot, const char *name, int blocks);
// Deletes a file (its directory entries are marked deleted, as the BIOS does). Returns 0 or -1.
int memcard_erase(int slot, const char *name);
// Reads or writes `n` bytes at `offset` within the file starting at block `first`, following its
// block chain. Returns n, or -1 when the range leaves the file.
int memcard_file_io(int slot, int first, uint32_t offset, void *buf, uint32_t n, int write);
// Free data blocks.
int memcard_free_blocks(int slot);

// Checks an image's structure (header, directory checksums and chains). Returns 0 when it is
// a valid formatted card, else -1 with a message in `why` (for tests and the loader).
int memcard_check_image(const uint8_t *image, char *why, int why_size);

#endif
