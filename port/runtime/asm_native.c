// Native equivalents of ROCK_NEO.EXE's hand-written assembly (asm/rock_neo.exe/asm_fastmem.s).
// These routines stay assembly in the matching build; the port needs C with the same effect.
// asm_8002E3D0 (func_8002E3D0, a hand-scheduled renderer loop) is not done yet and still gets
// a generated stub.
#include <stdint.h>

// Move the stack into the scratchpad (sp = 0x1F800400) and back. The native stack stays where
// the host put it; the game only does this for speed.
void func_800175D8(void)
{
}

void func_800175FC(void)
{
}

// Copy `count` words.
void func_80017684(void *src, void *dst, int32_t count)
{
    const uint32_t *s = src;
    uint32_t *d       = dst;

    do
    {
        *d++ = *s++;
    } while (--count != 0);
}

// Copy `count` 16-byte blocks.
void func_800176A4(void *src, void *dst, int32_t count)
{
    const uint32_t *s = src;
    uint32_t *d       = dst;

    do
    {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        s += 4;
        d += 4;
    } while (--count != 0);
}

// Copy `count` 32-byte blocks.
void func_800176DC(void *src, void *dst, int32_t count)
{
    const uint32_t *s = src;
    uint32_t *d       = dst;
    int i;

    do
    {
        for (i = 0; i < 8; i++)
        {
            d[i] = s[i];
        }
        s += 8;
        d += 8;
    } while (--count != 0);
}

// For each set bit of the mask word at 0x80098868, copy that 0x200-byte row of the 0x4000-byte
// buffer at 0x800AD168 to the buffer 0x4000 bytes above it; then clear the mask.
void func_80017734(void)
{
    uint32_t *mask = (uint32_t *)0x80098868;
    uint32_t bits  = *mask;
    uint32_t row;
    int i;

    for (row = 0x800AD168; row != 0x800AD168 + 0x4000; row += 0x200, bits >>= 1)
    {
        if (bits & 1)
        {
            uint32_t *p = (uint32_t *)row;
            for (i = 0; i < 0x200 / 4; i++)
            {
                p[i + 0x4000 / 4] = p[i];
            }
        }
    }
    *mask = 0;
}

// Zero the words from start to end, both included.
void func_800177CC(void *start, void *end)
{
    uint32_t *p = start;

    for (;;)
    {
        *p = 0;
        if (p == (uint32_t *)end)
        {
            break;
        }
        p++;
    }
}

// Clear in b every bit set in a, over 64 words.
void func_8001782C(uint32_t a, uint32_t b)
{
    const uint32_t *s = (const uint32_t *)(uintptr_t)a;
    uint32_t *d       = (uint32_t *)(uintptr_t)b;
    int i;

    for (i = 0; i < 64; i++)
    {
        d[i] &= ~(s[i] & d[i]);
    }
}
