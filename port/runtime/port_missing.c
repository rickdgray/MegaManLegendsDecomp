// Called by the generated stubs (port/tools/gen_link.py) for functions that have no native
// code yet: still-assembly game functions, PsyQ calls the runtime does not provide, and the
// hand-written routines. Reports each one once; PORT_MISSING_FATAL=1 makes the first one abort.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEEN_MAX 1024

static const char *seen[SEEN_MAX];
static int seen_count;

int port_missing(const char *name, unsigned int addr)
{
    int i;
    const char *fatal;

    for (i = 0; i < seen_count; i++)
    {
        if (seen[i] == name)
        {
            return 0;
        }
    }
    if (seen_count < SEEN_MAX)
    {
        seen[seen_count++] = name;
    }
    fprintf(stderr, "port: %s (0x%08X) has no native code yet\n", name, addr);
    fatal = getenv("PORT_MISSING_FATAL");
    if (fatal != NULL && strcmp(fatal, "0") != 0)
    {
        abort();
    }
    return 0;
}
