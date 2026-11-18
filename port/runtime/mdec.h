// A software model of the PS1's MDEC (motion decoder), for PsyQ's libpress run by the MIPS
// interpreter (the boot shim's movie player): DecDCTin writes a command word to MDEC0 and sends
// its parameters by DMA channel 0; DecDCTout fetches the decoded pixels by DMA channel 1.
//
// Commands: 1 decodes run-length coded macroblocks (Cr, Cb, then four Y blocks; dequantized,
// IDCT with the uploaded scale table, YUV to RGB) to 15- or 24-bit pixels, 16x16 per macroblock
// in input order; 2 sets the quantization tables; 3 sets the IDCT scale table. A command
// completes as soon as its last parameter word arrives, so the status register never reports
// busy and the output is ready when DecDCTout asks for it.
#ifndef PORT_MDEC_H
#define PORT_MDEC_H

#include <stdint.h>

void mdec_reset(void);
void mdec_write_cmd(uint32_t word); // MDEC0
void mdec_write_ctl(uint32_t word); // MDEC1
uint32_t mdec_read_status(void);    // MDEC1
uint32_t mdec_read_data(void);      // MDEC0
void mdec_dma_in(const uint32_t *src, uint32_t words);
void mdec_dma_out(uint32_t *dst, uint32_t words);

#endif
