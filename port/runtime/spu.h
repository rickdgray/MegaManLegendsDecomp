// A software model of the PS1's SPU (sound processing unit), at the register level.
//
// The game's sound library (PsyQ libsnd and libspu, run from the retail image by the MIPS
// interpreter) programs the SPU exactly as on the console: it writes the voice, key and control
// registers at 0x1F801C00.. and transfers sample data into sound RAM by DMA (channel 4). The
// interpreter forwards those accesses here (psx_io.c). spu_render() then produces 44.1 kHz stereo:
// 24 voices of ADPCM samples with ADSR envelopes, pitch (and pitch modulation), noise, voice and
// main volumes, the reverb unit on its work area in sound RAM, and the CD audio input (XA and
// CD-DA from the drive model, port/psyq/libcd.c).
//
// Not modeled (yet): the hardware's Gaussian interpolation (a 4-point cubic is used), the sound
// RAM interrupt, and the exact FIR filters around the reverb unit.
#ifndef PORT_SPU_H
#define PORT_SPU_H

#include <stdint.h>

#define SPU_RATE      44100
#define SPU_RAM_BYTES 0x80000u

void spu_reset(void);

// Register access; `off` is the address less 0x1F801C00 (0..0x3FF), halfword aligned.
uint16_t spu_read16(uint32_t off);
void spu_write16(uint32_t off, uint16_t value);

// DMA channel 4: words to or from sound RAM at the current transfer address.
void spu_dma_write(const uint32_t *src, uint32_t words);
void spu_dma_read(uint32_t *dst, uint32_t words);

// Mixes `frames` stereo frames (interleaved left, right) into `out`.
void spu_render(int16_t *out, int frames);

// The CD audio input, already at 44.1 kHz stereo: the drive model pushes decoded XA and CD-DA
// here; spu_render takes one frame per output sample once enough is buffered.
void spu_cd_push(const int16_t *stereo, int frames);

// Sound RAM, for tests.
const uint8_t *spu_ram(void);

#endif
