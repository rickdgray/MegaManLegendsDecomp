// The port's text layer. See port_overlay.h.
#include "port_overlay.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static PORT_OVERLAY layer;

PORT_OVERLAY *port_overlay(void)
{
    return &layer;
}

void port_overlay_clear(PORT_OVERLAY *o)
{
    memset(o, 0, sizeof(*o));
}

void port_overlay_box(PORT_OVERLAY *o, int x, int y, int w, int h, int shade)
{
    o->visible = 1;
    o->shade   = shade;
    o->box_x   = x;
    o->box_y   = y;
    o->box_w   = w;
    o->box_h   = h;
}

static int put(PORT_OVERLAY *o, int row, int col, int colour, const char *s)
{
    if (row < 0 || row >= PORT_OVERLAY_ROWS)
    {
        return col;
    }
    for (; *s != 0; s++, col++)
    {
        if (col >= 0 && col < PORT_OVERLAY_COLS)
        {
            o->text[row][col]   = *s;
            o->colour[row][col] = (uint8_t)colour;
        }
    }
    return col;
}

int port_overlay_print(PORT_OVERLAY *o, int row, int col, int colour, const char *fmt, ...)
{
    char buf[PORT_OVERLAY_COLS * 2];
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    return put(o, row, col, colour, buf);
}

void port_overlay_center(PORT_OVERLAY *o, int row, int colour, const char *fmt, ...)
{
    char buf[PORT_OVERLAY_COLS * 2];
    int left = 0, width = PORT_OVERLAY_COLS;
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    if (o->box_w > 0)
    {
        left  = o->box_x;
        width = o->box_w;
    }
    put(o, row, left + (width - (int)strlen(buf)) / 2, colour, buf);
}

void port_overlay_log(const PORT_OVERLAY *o, const char *title)
{
    int row, col, last;

    fprintf(stderr, "port: %s\n", title);
    for (row = 0; row < PORT_OVERLAY_ROWS; row++)
    {
        last = -1;
        for (col = 0; col < PORT_OVERLAY_COLS; col++)
        {
            if (o->text[row][col] != 0 && o->text[row][col] != ' ')
            {
                last = col;
            }
        }
        if (last < 0)
        {
            continue;
        }
        fputs("  | ", stderr);
        for (col = 0; col <= last; col++)
        {
            fputc(o->text[row][col] != 0 ? o->text[row][col] : ' ', stderr);
        }
        fputc('\n', stderr);
    }
}
