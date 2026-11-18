// Input scripts: see port_script.h.
//
// One command per line; `#` starts a comment. Time is counted in vertical blanks; each command
// starts at the blank where the previous one ended.
//
//   let NAME ADDR[:TYPE]        a name for a memory value (TYPE u8 s8 u16 s16 u32; default u8)
//   wait N                      no buttons for N blanks
//   press BUTTONS [N]           hold N blanks (default 6), then release N blanks
//   hold BUTTONS N              hold N blanks
//   hold BUTTONS until COND [max N]   hold until COND holds (fails after N blanks, default 3600)
//   mash BUTTONS until COND [max N]   press repeatedly (6 on, 6 off) until COND
//   mash BUTTONS N              press repeatedly for N blanks
//                               (hold and mash also take `with BUTTONS` after the first
//                               BUTTONS: held all along, e.g. `mash square with r2 600`)
//   until COND [max N]          no buttons until COND
//   expect COND                 a checkpoint: stops with a failure unless COND holds now
//   mark NAME                   logs NAME, the blank and a hash of VRAM's display area
//   dump NAME                   writes VRAM to DUMP-NAME.ppm (with --dump DUMP)
//   ram NAME                    writes PS1 RAM (2 MB) and the scratchpad (1 KB) to
//                               DUMP-NAME.ram (for finding values to wait on)
//   end                         stops the program successfully (also at the end of the file)
//   serve                       writing scripts: keeps the run here and forks a continuation
//                               per request (--serve DIR; port_fork_serve in port_game.c)
//
// BUTTONS: names joined by `+` (cross circle square triangle up down left right l1 l2 r1 r2 l3
// r3 start select; `mods` is the port's mod-panel button, PORT_HOST_MODS), or `none`. COND: VALUE OP NUMBER, joined by `&&`; VALUE is a `let` name or
// ADDR[:TYPE]; OP is == != < <= > >=; numbers in C notation (0x.., negative allowed).
#include "port_script.h"

#include "gpu.h"
#include "port_game.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    C_WAIT,
    C_PRESS,
    C_HOLD,
    C_HOLD_UNTIL,
    C_MASH_UNTIL,
    C_MASH,
    C_UNTIL,
    C_EXPECT,
    C_MARK,
    C_DUMP,
    C_RAM,
    C_END,
    C_SERVE
};

enum
{
    T_U8,
    T_S8,
    T_U16,
    T_S16,
    T_U32
};

#define MAX_TERMS 4

typedef struct
{
    uint32_t addr;
    int type;
    int op; // 0 == 1 != 2 < 3 <= 4 > 5 >=
    int32_t value;
} TERM;

typedef struct
{
    int kind;
    int line;
    uint32_t buttons; // PS1 bits, and PORT_SCRIPT_MODS for the port's mod-panel button
    uint32_t held;    // `with`: held under the pressed buttons
    uint32_t n;   // blanks, or the limit for the `until` forms
    int nterms;
    TERM terms[MAX_TERMS];
    char name[48];
    char text[128]; // the source line, for messages
} COMMAND;

typedef struct
{
    char name[32];
    uint32_t addr;
    int type;
} ALIAS;

static COMMAND *cmds;
static int ncmds;
static ALIAS aliases[64];
static int naliases;
static int cur;
static uint32_t cur_start;
static int cur_started;
static int replaced;

static const struct
{
    const char *name;
    uint32_t bit;
} button_names[] = {
    {"select", 0x0001}, {"l3", 0x0002},     {"r3", 0x0004},       {"start", 0x0008},
    {"up", 0x0010},     {"right", 0x0020},  {"down", 0x0040},     {"left", 0x0080},
    {"l2", 0x0100},     {"r2", 0x0200},     {"l1", 0x0400},       {"r1", 0x0800},
    {"triangle", 0x1000}, {"circle", 0x2000}, {"cross", 0x4000}, {"square", 0x8000},
    {"mods", PORT_SCRIPT_MODS},
};

static const char *script_path;

static int parse_error(int line, const char *what, const char *tok)
{
    fprintf(stderr, "port: %s:%d: %s%s%s\n", script_path, line, what, tok ? ": " : "",
            tok ? tok : "");
    return -1;
}

static int parse_buttons(const char *s, uint32_t *out)
{
    char buf[128];
    char *p, *save;

    *out = 0;
    if (strcmp(s, "none") == 0)
    {
        return 0;
    }
    snprintf(buf, sizeof(buf), "%s", s);
    for (p = strtok_r(buf, "+", &save); p != NULL; p = strtok_r(NULL, "+", &save))
    {
        size_t i;

        for (i = 0; i < sizeof(button_names) / sizeof(button_names[0]); i++)
        {
            if (strcmp(p, button_names[i].name) == 0)
            {
                *out |= button_names[i].bit;
                break;
            }
        }
        if (i == sizeof(button_names) / sizeof(button_names[0]))
        {
            return -1;
        }
    }
    return 0;
}

static int parse_number(const char *s, int32_t *out)
{
    char *e;
    long long v = strtoll(s, &e, 0);

    if (*s == 0 || *e != 0)
    {
        return -1;
    }
    *out = (int32_t)v;
    return 0;
}

static int parse_value(const char *s, uint32_t *addr, int *type)
{
    char buf[64];
    char *colon, *e;
    int i;

    for (i = 0; i < naliases; i++)
    {
        if (strcmp(s, aliases[i].name) == 0)
        {
            *addr = aliases[i].addr;
            *type = aliases[i].type;
            return 0;
        }
    }
    snprintf(buf, sizeof(buf), "%s", s);
    colon = strchr(buf, ':');
    *type = T_U8;
    if (colon != NULL)
    {
        static const char *types[] = {"u8", "s8", "u16", "s16", "u32"};

        *colon = 0;
        for (i = 0; i < 5 && strcmp(colon + 1, types[i]) != 0; i++)
        {
        }
        if (i == 5)
        {
            return -1;
        }
        *type = i;
    }
    *addr = (uint32_t)strtoul(buf, &e, 0);
    if (*e != 0 || *addr < 0x80000000u || *addr >= 0x80200000u)
    {
        return -1;
    }
    return 0;
}

// COND starting at tok[i]; returns the index after it, or -1.
static int parse_cond(COMMAND *c, char **tok, int ntok, int i)
{
    static const char *ops[] = {"==", "!=", "<", "<=", ">", ">="};

    c->nterms = 0;
    for (;;)
    {
        TERM *t;
        int k;

        if (i + 3 > ntok || c->nterms == MAX_TERMS)
        {
            return -1;
        }
        t = &c->terms[c->nterms++];
        if (parse_value(tok[i], &t->addr, &t->type) != 0)
        {
            return -1;
        }
        for (k = 0; k < 6 && strcmp(tok[i + 1], ops[k]) != 0; k++)
        {
        }
        if (k == 6 || parse_number(tok[i + 2], &t->value) != 0)
        {
            return -1;
        }
        t->op = k;
        i += 3;
        if (i < ntok && strcmp(tok[i], "&&") == 0)
        {
            i++;
            continue;
        }
        return i;
    }
}

// The optional `max N` after a condition.
static int parse_max(COMMAND *c, char **tok, int ntok, int i)
{
    int32_t n;

    c->n = 3600;
    if (i == ntok)
    {
        return 0;
    }
    if (i + 2 == ntok && strcmp(tok[i], "max") == 0 && parse_number(tok[i + 1], &n) == 0 && n > 0)
    {
        c->n = (uint32_t)n;
        return 0;
    }
    return -1;
}

int port_script_load(const char *path)
{
    FILE *f = fopen(path, "r");
    char line[512];
    int lineno = 0, cap = 0;

    script_path = path;
    if (f == NULL)
    {
        perror(path);
        return -1;
    }
    while (fgets(line, sizeof(line), f) != NULL)
    {
        char *tok[24];
        char text[128];
        char *p, *save, *hash;
        int ntok = 0;
        COMMAND c;
        int32_t n;

        lineno++;
        if ((hash = strchr(line, '#')) != NULL)
        {
            *hash = 0;
        }
        snprintf(text, sizeof(text), "%.127s", line);
        text[strcspn(text, "\r\n")] = 0;
        for (p = strtok_r(line, " \t\r\n", &save); p != NULL && ntok < 24;
             p = strtok_r(NULL, " \t\r\n", &save))
        {
            tok[ntok++] = p;
        }
        if (ntok == 0)
        {
            continue;
        }
        memset(&c, 0, sizeof(c));
        c.line = lineno;
        for (p = text; isspace((unsigned char)*p); p++)
        {
        }
        snprintf(c.text, sizeof(c.text), "%.127s", p);
        for (n = (int32_t)strlen(c.text); n > 0 && isspace((unsigned char)c.text[n - 1]); n--)
        {
            c.text[n - 1] = 0;
        }
        if (strcmp(tok[0], "let") == 0)
        {
            ALIAS *a;

            if (ntok != 3 || naliases == 64)
            {
                fclose(f);
                return parse_error(lineno, "expected: let NAME ADDR[:TYPE]", NULL);
            }
            a = &aliases[naliases];
            snprintf(a->name, sizeof(a->name), "%s", tok[1]);
            if (parse_value(tok[2], &a->addr, &a->type) != 0)
            {
                fclose(f);
                return parse_error(lineno, "bad address", tok[2]);
            }
            naliases++;
            continue;
        }
        else if (strcmp(tok[0], "wait") == 0 && ntok == 2 && parse_number(tok[1], &n) == 0)
        {
            c.kind = C_WAIT;
            c.n    = (uint32_t)n;
        }
        else if (strcmp(tok[0], "press") == 0 && (ntok == 2 || ntok == 3))
        {
            c.kind = C_PRESS;
            c.n    = 6;
            if (parse_buttons(tok[1], &c.buttons) != 0 ||
                (ntok == 3 && (parse_number(tok[2], &n) != 0 || n <= 0)))
            {
                fclose(f);
                return parse_error(lineno, "expected: press BUTTONS [N]", NULL);
            }
            if (ntok == 3)
            {
                c.n = (uint32_t)n;
            }
        }
        else if ((strcmp(tok[0], "hold") == 0 || strcmp(tok[0], "mash") == 0) && ntok >= 3)
        {
            if (parse_buttons(tok[1], &c.buttons) != 0)
            {
                fclose(f);
                return parse_error(lineno, "bad buttons", tok[1]);
            }
            if (ntok >= 5 && strcmp(tok[2], "with") == 0)
            {
                int k;

                if (parse_buttons(tok[3], &c.held) != 0)
                {
                    fclose(f);
                    return parse_error(lineno, "bad buttons", tok[3]);
                }
                for (k = 4; k < ntok; k++)
                {
                    tok[k - 2] = tok[k];
                }
                ntok -= 2;
            }
            if (strcmp(tok[2], "until") == 0)
            {
                int i = parse_cond(&c, tok, ntok, 3);

                c.kind = tok[0][0] == 'h' ? C_HOLD_UNTIL : C_MASH_UNTIL;
                if (i < 0 || parse_max(&c, tok, ntok, i) != 0)
                {
                    fclose(f);
                    return parse_error(lineno, "bad condition", c.text);
                }
            }
            else if (ntok == 3 && parse_number(tok[2], &n) == 0)
            {
                c.kind = tok[0][0] == 'h' ? C_HOLD : C_MASH;
                c.n    = (uint32_t)n;
            }
            else
            {
                fclose(f);
                return parse_error(lineno, "expected: hold/mash BUTTONS N | ... until COND", NULL);
            }
        }
        else if (strcmp(tok[0], "until") == 0 || strcmp(tok[0], "expect") == 0)
        {
            int i = parse_cond(&c, tok, ntok, 1);

            c.kind = tok[0][0] == 'u' ? C_UNTIL : C_EXPECT;
            if (i < 0 || (c.kind == C_UNTIL ? parse_max(&c, tok, ntok, i) != 0 : i != ntok))
            {
                fclose(f);
                return parse_error(lineno, "bad condition", c.text);
            }
        }
        else if ((strcmp(tok[0], "mark") == 0 || strcmp(tok[0], "dump") == 0 ||
                  strcmp(tok[0], "ram") == 0) &&
                 ntok == 2)
        {
            c.kind = tok[0][0] == 'm' ? C_MARK : tok[0][0] == 'd' ? C_DUMP : C_RAM;
            snprintf(c.name, sizeof(c.name), "%s", tok[1]);
        }
        else if (strcmp(tok[0], "end") == 0 && ntok == 1)
        {
            c.kind = C_END;
        }
        else if (strcmp(tok[0], "serve") == 0 && ntok == 1)
        {
            c.kind = C_SERVE;
        }
        else
        {
            fclose(f);
            return parse_error(lineno, "unknown command", c.text);
        }
        if (ncmds == cap)
        {
            cap  = cap ? cap * 2 : 64;
            cmds = realloc(cmds, (size_t)cap * sizeof(COMMAND));
        }
        cmds[ncmds++] = c;
    }
    fclose(f);
    return 0;
}

int port_script_replace(const char *path)
{
    free(cmds);
    cmds        = NULL;
    ncmds       = 0;
    cur         = 0;
    cur_started = 0;
    replaced    = 1;
    return port_script_load(path);
}

int port_script_active(void)
{
    return script_path != NULL;
}

static int32_t read_value(const TERM *t)
{
    const volatile uint8_t *p = (const volatile uint8_t *)(uintptr_t)t->addr;

    switch (t->type)
    {
        case T_S8:
            return *(const volatile int8_t *)p;
        case T_U16:
            return *(const volatile uint16_t *)p;
        case T_S16:
            return *(const volatile int16_t *)p;
        case T_U32:
            return (int32_t) * (const volatile uint32_t *)p;
        default:
            return *p;
    }
}

static int cond_holds(const COMMAND *c)
{
    int i;

    for (i = 0; i < c->nterms; i++)
    {
        const TERM *t = &c->terms[i];
        int32_t v     = read_value(t);
        int ok;

        if (t->type == T_U32)
        {
            uint32_t a = (uint32_t)v, b = (uint32_t)t->value;

            ok = t->op == 0 ? a == b : t->op == 1 ? a != b : t->op == 2 ? a < b
                                                 : t->op == 3 ? a <= b
                                                 : t->op == 4 ? a > b
                                                              : a >= b;
        }
        else
        {
            int32_t b = t->value;

            ok = t->op == 0 ? v == b : t->op == 1 ? v != b : t->op == 2 ? v < b
                                                 : t->op == 3 ? v <= b
                                                 : t->op == 4 ? v > b
                                                              : v >= b;
        }
        if (!ok)
        {
            return 0;
        }
    }
    return 1;
}

static void report_values(const COMMAND *c)
{
    int i;

    for (i = 0; i < c->nterms; i++)
    {
        port_log("script:   0x%08X = %d (0x%X)", c->terms[i].addr, read_value(&c->terms[i]),
                 (unsigned)read_value(&c->terms[i]));
    }
}

static void fail(const COMMAND *c, uint32_t v, const char *why)
{
    port_log("script: FAILED at blank %u, line %d (%s): %s", v, c->line, c->text, why);
    report_values(c);
    port_stop(1, "script failed");
}

// FNV-1a over the display area: a fingerprint of the picture for the log.
static uint64_t display_hash(void)
{
    const GPU_DISPLAY *d = gpu_display();
    const uint16_t *vram = gpu_vram();
    uint64_t h           = 0xcbf29ce484222325ull;
    int x, y;

    for (y = 0; y < d->h && d->y + y < GPU_VRAM_H; y++)
    {
        for (x = 0; x < d->w && d->x + x < GPU_VRAM_W; x++)
        {
            uint16_t p = vram[(d->y + y) * GPU_VRAM_W + d->x + x];

            h = (h ^ (p & 0xFF)) * 0x100000001b3ull;
            h = (h ^ (p >> 8)) * 0x100000001b3ull;
        }
    }
    return h;
}

uint32_t port_script_buttons(uint32_t v)
{
    while (cur < ncmds)
    {
        COMMAND *c = &cmds[cur];
        uint32_t t;

        if (!cur_started)
        {
            cur_started = 1;
            cur_start   = v;
        }
        t = v - cur_start;
        switch (c->kind)
        {
            case C_WAIT:
                if (t < c->n)
                {
                    return 0;
                }
                break;
            case C_PRESS:
                if (t < c->n)
                {
                    return c->buttons;
                }
                if (t < 2 * c->n)
                {
                    return 0;
                }
                break;
            case C_HOLD:
                if (t < c->n)
                {
                    return c->buttons | c->held;
                }
                break;
            case C_MASH:
                if (t < c->n)
                {
                    return (t % 12 < 6 ? c->buttons : 0) | c->held;
                }
                break;
            case C_HOLD_UNTIL:
            case C_MASH_UNTIL:
            case C_UNTIL:
                if (!cond_holds(c))
                {
                    if (t >= c->n)
                    {
                        fail(c, v, "timed out");
                    }
                    if (c->kind == C_UNTIL || (c->kind == C_MASH_UNTIL && t % 12 >= 6))
                    {
                        return c->held;
                    }
                    return c->buttons | c->held;
                }
                if (port_options.verbose)
                {
                    port_log("script: line %d done at blank %u (%u blanks)", c->line, v, t);
                }
                break;
            case C_EXPECT:
                if (!cond_holds(c))
                {
                    fail(c, v, "checkpoint not met");
                }
                port_log("script: checkpoint line %d (%s) at blank %u: ok", c->line, c->text, v);
                break;
            case C_MARK:
                port_log("script: mark %s at blank %u, display %016llx", c->name, v,
                         (unsigned long long)display_hash());
                break;
            case C_DUMP:
            case C_RAM:
                if (port_options.dump != NULL)
                {
                    char path[1024];
                    size_t len = strlen(port_options.dump);

                    if (len > 4 && strcmp(port_options.dump + len - 4, ".ppm") == 0)
                    {
                        len -= 4;
                    }
                    snprintf(path, sizeof(path), "%.*s-%s.%s", (int)len, port_options.dump,
                             c->name, c->kind == C_RAM ? "ram" : "ppm");
                    if (c->kind == C_RAM)
                    {
                        FILE *f = fopen(path, "wb");

                        if (f != NULL)
                        {
                            fwrite((const void *)(uintptr_t)0x80000000u, 1, 0x200000, f);
                            fwrite((const void *)(uintptr_t)0x1F800000u, 1, 0x400, f);
                            fclose(f);
                        }
                    }
                    else if (port_dump_vram(path) == 0)
                    {
                        port_log("script: blank %u: wrote VRAM to %s", v, path);
                    }
                }
                break;
            case C_END:
                port_log("script: end at blank %u", v);
                port_stop(0, "script complete");
            case C_SERVE:
                replaced = 0;
                port_fork_serve();
                if (replaced)
                {
                    continue; // a child with the request's script, from its first command
                }
                break;
        }
        cur++;
        cur_started = 0;
    }
    port_log("script: end at blank %u", v);
    port_stop(0, "script complete");
}
