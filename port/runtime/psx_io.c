// Hardware registers for interpreted code. See psx_io.h.
#include "psx_io.h"

#include "mdec.h"
#include "mips_cpu.h"
#include "port_game.h"
#include "psx_mem.h"
#include "spu.h"

#include <stdio.h>
#include <string.h>

#define DMA_BASE 0x1F801080u
#define DMA_DPCR 0x1F8010F0u
#define DMA_DICR 0x1F8010F4u
#define SPU_BASE 0x1F801C00u
#define SPU_END  0x1F802000u

static uint32_t dma_regs[7][4]; // MADR, BCR, CHCR per channel
static uint32_t dpcr = 0x07654321u, dicr;
static uint32_t dma_cb[7];
static uint32_t misc[0x800]; // other registers, as storage (word granular)
static uint32_t pending;     // channels whose completion callback is due

void psx_io_reset(void)
{
    memset(dma_regs, 0, sizeof(dma_regs));
    memset(dma_cb, 0, sizeof(dma_cb));
    memset(misc, 0, sizeof(misc));
    dpcr = 0x07654321u;
    dicr = pending = 0;
}

uint32_t psx_dma_set_callback(int channel, uint32_t func)
{
    uint32_t old;

    if (channel < 0 || channel >= 7)
    {
        return 0;
    }
    old             = dma_cb[channel];
    dma_cb[channel] = func;
    return old;
}

static void report(const char *what, uint32_t phys)
{
    static uint32_t seen[64];
    static int nseen;
    int i;

    for (i = 0; i < nseen; i++)
    {
        if (seen[i] == phys)
        {
            return;
        }
    }
    if (nseen < 64)
    {
        seen[nseen++] = phys;
    }
    fprintf(stderr, "port: hardware register %s at 0x%08X (not modeled; ignored)\n", what, phys);
}

// A DMA callback: retail code (MIPS or a native stub) by its PS1 address, or a native function.
void psx_call(uint32_t func)
{
    if (func == 0)
    {
        return;
    }
    if ((func & 0xFF000000u) == 0x80000000u)
    {
        uint32_t args[8] = {0};
        mips_call(func, args);
    }
    else
    {
        ((void (*)(void))(uintptr_t)func)();
    }
}

static void dma_start(int ch)
{
    uint32_t madr = dma_regs[ch][0] & 0x1FFFFCu, bcr = dma_regs[ch][1], chcr = dma_regs[ch][2];
    uint32_t words;
    uint32_t *p = (uint32_t *)psx_ptr(PSX_RAM_BASE | madr);

    switch ((chcr >> 9) & 3)
    {
        case 1: // blocks
            words = (bcr & 0xFFFF) * (bcr >> 16);
            break;
        case 0:
            words = (bcr & 0xFFFF) != 0 ? bcr & 0xFFFF : 0x10000;
            break;
        default:
            report("DMA linked list", DMA_BASE + (uint32_t)ch * 16);
            words = 0;
            break;
    }
    if (p == NULL)
    {
        report("DMA outside RAM", DMA_BASE + (uint32_t)ch * 16);
    }
    else if (ch == 4)
    {
        if (chcr & 1)
        {
            spu_dma_write(p, words);
        }
        else
        {
            spu_dma_read(p, words);
        }
    }
    else if (ch == 0)
    {
        mdec_dma_in(p, words);
    }
    else if (ch == 1)
    {
        mdec_dma_out(p, words);
    }
    else
    {
        report("DMA channel start", DMA_BASE + (uint32_t)ch * 16 + 8);
    }
    dma_regs[ch][2] &= ~0x11000000u; // done: start and trigger bits clear
    if (dicr & (1u << (16 + ch)))
    {
        dicr |= 1u << (24 + ch);
    }
    // The completion interrupt comes after the code that started the transfer has moved on
    // (on the console, at least a few instructions later): psx_io_run_pending runs it when the
    // interpreted library call returns.
    if (dma_cb[ch] != 0)
    {
        pending |= 1u << ch;
    }
}

void psx_io_run_pending(void)
{
    while (pending != 0)
    {
        int ch;
        int blocked;

        for (ch = 0; ch < 7 && !(pending & (1u << ch)); ch++)
        {
        }
        pending &= ~(1u << ch);
        blocked = port_irq_block(); // interrupt context
        psx_call(dma_cb[ch]);
        port_irq_restore(blocked);
    }
}

uint32_t psx_io_read(uint32_t ea, int size)
{
    uint32_t phys = ea & 0x1FFFFFFFu;

    if (phys >= SPU_BASE && phys < SPU_END)
    {
        uint32_t off = phys - SPU_BASE;
        uint32_t v   = spu_read16(off & ~1u);

        if (size == 4)
        {
            v |= (uint32_t)spu_read16((off + 2) & ~1u) << 16;
        }
        else if (size == 1)
        {
            v = (off & 1) ? v >> 8 : v & 0xFF;
        }
        return v;
    }
    if (phys >= DMA_BASE && phys < DMA_DPCR)
    {
        int ch  = (int)((phys - DMA_BASE) >> 4);
        int reg = (int)((phys >> 2) & 3);
        return reg < 3 ? dma_regs[ch][reg] >> ((phys & 3) * 8) : 0;
    }
    if (phys == 0x1F801820u)
    {
        return mdec_read_data();
    }
    if (phys == 0x1F801824u)
    {
        return mdec_read_status();
    }
    if (phys == DMA_DPCR)
    {
        return dpcr;
    }
    if (phys == DMA_DICR)
    {
        return dicr;
    }
    {
        uint32_t w = misc[((phys - PSX_IO_BASE) >> 2) & 0x7FF];
        w >>= (phys & 3) * 8;
        return size == 1 ? w & 0xFF : size == 2 ? w & 0xFFFF : w;
    }
}

void psx_io_write(uint32_t ea, uint32_t value, int size)
{
    uint32_t phys = ea & 0x1FFFFFFFu;

    if (phys >= SPU_BASE && phys < SPU_END)
    {
        uint32_t off = phys - SPU_BASE;

        if (size == 1)
        {
            report("byte store (SPU)", phys);
            return;
        }
        spu_write16(off, (uint16_t)value);
        if (size == 4)
        {
            spu_write16(off + 2, (uint16_t)(value >> 16));
        }
        return;
    }
    if (phys >= DMA_BASE && phys < DMA_DPCR)
    {
        int ch  = (int)((phys - DMA_BASE) >> 4);
        int reg = (int)((phys >> 2) & 3);

        if (reg < 3)
        {
            dma_regs[ch][reg] = value;
            if (reg == 2 && (value & 0x01000000u))
            {
                dma_start(ch);
            }
        }
        return;
    }
    if (phys == DMA_DPCR)
    {
        dpcr = value;
        return;
    }
    if (phys == DMA_DICR)
    {
        // Flag bits (24-30) are cleared by writing ones.
        dicr = (value & 0x00FFFFFFu) | ((dicr & ~value) & 0x7F000000u);
        return;
    }
    if (phys == 0x1F801820u)
    {
        mdec_write_cmd(value);
        return;
    }
    if (phys == 0x1F801824u)
    {
        mdec_write_ctl(value);
        return;
    }
    if (phys >= 0x1F801800u && phys < 0x1F801830u)
    {
        report("store (CD or GPU)", phys);
        return;
    }
    {
        uint32_t *w = &misc[((phys - PSX_IO_BASE) >> 2) & 0x7FF];
        int sh      = (int)(phys & 3) * 8;
        uint32_t m  = size == 1 ? 0xFFu : size == 2 ? 0xFFFFu : 0xFFFFFFFFu;
        *w          = (*w & ~(m << sh)) | ((value & m) << sh);
    }
}
