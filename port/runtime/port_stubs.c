// Installs the stub table (port_stubs.h).
#include "port_stubs.h"

#include "psx_mem.h"

#include <stdio.h>

int port_install_stubs(void)
{
    int i;

    for (i = 0; i < port_stub_count; i++)
    {
        if (psx_install_stub(port_stub_table[i].addr, port_stub_table[i].native) != 0)
        {
            fprintf(stderr, "port: cannot install the stub for %s at 0x%08X\n",
                    port_stub_table[i].name, port_stub_table[i].addr);
            return -1;
        }
    }
    return port_stub_count;
}

const PORT_STUB *port_stub_find(uint32_t addr)
{
    int lo = 0, hi = port_stub_count - 1;

    // The table is sorted by address.
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;

        if (port_stub_table[mid].addr == addr)
        {
            return &port_stub_table[mid];
        }
        if (port_stub_table[mid].addr < addr)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid - 1;
        }
    }
    return NULL;
}

// --- mod hooks ------------------------------------------------------------------------------

#define MAX_HOOKS 64

static struct
{
    uint32_t addr;
    void *fn;
} hooks[MAX_HOOKS];
static int nhooks; // 0 in vanilla play: port_stub_target is then the stub table as it stands

void *port_stub_hook(uint32_t addr, void *fn)
{
    const PORT_STUB *st = port_stub_find(addr);
    int i;

    if (st == NULL || st->missing || nhooks == MAX_HOOKS)
    {
        return NULL;
    }
    for (i = 0; i < nhooks; i++)
    {
        if (hooks[i].addr == addr)
        {
            return NULL;
        }
    }
    if (psx_install_stub(addr, (void (*)(void))fn) != 0)
    {
        return NULL;
    }
    hooks[nhooks].addr = addr;
    hooks[nhooks].fn   = fn;
    nhooks++;
    return (void *)st->native;
}

void port_stub_unhook(uint32_t addr)
{
    const PORT_STUB *st = port_stub_find(addr);
    int i;

    for (i = 0; i < nhooks; i++)
    {
        if (hooks[i].addr == addr)
        {
            hooks[i] = hooks[--nhooks];
            if (st != NULL)
            {
                psx_install_stub(addr, st->native);
            }
            return;
        }
    }
}

void *port_stub_target(const PORT_STUB *st)
{
    int i;

    for (i = 0; i < nhooks; i++)
    {
        if (hooks[i].addr == st->addr)
        {
            return hooks[i].fn;
        }
    }
    return (void *)st->native;
}
