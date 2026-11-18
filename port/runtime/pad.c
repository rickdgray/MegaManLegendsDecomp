// PS1 pad buffer. See pad.h.
#include "pad.h"

#include <string.h>

void psx_pad_reset(PSX_PAD_STATE *s)
{
    memset(s, 0, sizeof(*s));
    s->connected = 1;
    s->analog    = 1;
    s->lx = s->ly = s->rx = s->ry = 0x80;
}

void psx_pad_to_buffer(const PSX_PAD_STATE *s, uint8_t *buf, int size)
{
    uint16_t raw = (uint16_t)~s->buttons;

    memset(buf, 0xFF, (size_t)size);
    if (!s->connected)
    {
        return;
    }
    buf[0] = 0x00;
    buf[1] = s->analog ? PSX_PAD_ID_ANALOG : PSX_PAD_ID_DIGITAL;
    if (size >= 4)
    {
        buf[2] = (uint8_t)(raw & 0xFF);
        buf[3] = (uint8_t)(raw >> 8);
    }
    if (size >= 8 && s->analog)
    {
        buf[4] = s->rx;
        buf[5] = s->ry;
        buf[6] = s->lx;
        buf[7] = s->ly;
    }
}
