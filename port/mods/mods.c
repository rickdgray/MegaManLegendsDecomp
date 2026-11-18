// The mod system: the vanilla/mods choice, cards, hooks, and the settings. See mods.h; the
// menus are in mods_menu.c.
#define _GNU_SOURCE
#include "mods.h"

#include "memcard.h"
#include "mods_internal.h"
#include "port_config.h"
#include "port_game.h"
#ifndef PORT_AOT_MIPS
#include "port_stubs.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int mods_mode = MODS_UNSETTLED;
int mods_started;

int mods_active(void)
{
    return mods_mode == MODS_ON;
}

MOD *mods_find(const char *id)
{
    int i;

    for (i = 0; mods_list[i] != NULL; i++)
    {
        if (strcasecmp(mods_list[i]->id, id) == 0)
        {
            return mods_list[i];
        }
    }
    return NULL;
}

int mods_count(void)
{
    int n = 0;

    while (mods_list[n] != NULL)
    {
        n++;
    }
    return n;
}

// Switches on exactly the mods in `list` (ids separated by commas, `all`, `none`/empty).
// Returns -1 after reporting an unknown id.
static int enable_list(const char *list)
{
    char buf[256], *p, *save;
    int i, bad = 0;

    for (i = 0; mods_list[i] != NULL; i++)
    {
        mods_list[i]->enabled = 0;
    }
    if (list == NULL || strcasecmp(list, "none") == 0)
    {
        return 0;
    }
    snprintf(buf, sizeof(buf), "%s", list);
    for (p = strtok_r(buf, ", \t", &save); p != NULL; p = strtok_r(NULL, ", \t", &save))
    {
        MOD *m = mods_find(p);

        if (strcasecmp(p, "all") == 0)
        {
            for (i = 0; mods_list[i] != NULL; i++)
            {
                mods_list[i]->enabled = 1;
            }
        }
        else if (m != NULL)
        {
            m->enabled = 1;
        }
        else
        {
            fprintf(stderr, "port: mods: no mod called \"%s\" (there are:", p);
            for (i = 0; mods_list[i] != NULL; i++)
            {
                fprintf(stderr, " %s", mods_list[i]->id);
            }
            fprintf(stderr, ")\n");
            bad = 1;
        }
    }
    return bad ? -1 : 0;
}

// Reads every setting's value from [mods] <id>.<key>.
static void load_settings(void)
{
    int i, j, k;

    for (i = 0; mods_list[i] != NULL; i++)
    {
        MOD *m = mods_list[i];

        for (j = 0; j < m->nsettings; j++)
        {
            MOD_SETTING *s = &m->settings[j];
            char key[96];
            const char *v;

            snprintf(key, sizeof(key), "%s.%s", m->id, s->key);
            v        = port_config_get("mods", key);
            s->value = s->initial;
            for (k = 0; v != NULL && k < s->count; k++)
            {
                if (strcasecmp(v, s->choices[k]) == 0)
                {
                    s->value = k;
                }
            }
        }
    }
}

int mods_configure(const char *cli, int headless)
{
    const char *startup = port_config_get("mods", "startup");
    const char *enabled = port_config_get("mods", "enabled");

    load_settings();
    if (enable_list(enabled) != 0)
    {
        fprintf(stderr, "port: mods: in %s, [mods] enabled\n", port_config_file());
    }
    if (cli != NULL)
    {
        if (strcasecmp(cli, "vanilla") == 0)
        {
            mods_mode = MODS_VANILLA;
            return 0;
        }
        mods_mode = MODS_ON;
        if (strcasecmp(cli, "default") == 0)
        {
            return 0;
        }
        return enable_list(cli) != 0 ? -1 : 0;
    }
    if (headless)
    {
        mods_mode = MODS_VANILLA; // scripted runs stay exact unless they ask for mods
        return 0;
    }
    if (startup != NULL && strcasecmp(startup, "vanilla") == 0)
    {
        mods_mode = MODS_VANILLA;
        return 0;
    }
    if (startup != NULL && strcasecmp(startup, "mods") == 0)
    {
        mods_mode = MODS_ON;
        return 0;
    }
    if (startup != NULL && strcasecmp(startup, "ask") != 0)
    {
        fprintf(stderr, "port: settings: [mods] startup = %s: ask, vanilla or mods; asking\n",
                startup);
    }
    mods_mode = MODS_VANILLA; // until the menu says otherwise
    return 1;
}

void mods_apply_cards(int card1_given, int card2_given)
{
    static const char *keys[2]  = {"slot1_mods", "slot2_mods"};
    static const char *slots[2] = {"slot1", "slot2"};
    int given[2]                = {card1_given, card2_given};
    int i;

    if (mods_mode != MODS_ON)
    {
        return;
    }
    for (i = 0; i < 2; i++)
    {
        const char *v = port_config_get("cards", keys[i]);

        if (!given[i] && v != NULL && *v != 0)
        {
            port_config_set("cards", slots[i], v);
        }
    }
    port_config_apply_cards();
    port_log("mods: memory card 1: %s", memcard_path(0) != NULL ? memcard_path(0) : "(none)");
}

char *mods_enabled_list(void)
{
    static char buf[512];
    int i;

    buf[0] = 0;
    for (i = 0; mods_list[i] != NULL; i++)
    {
        if (mods_list[i]->enabled)
        {
            if (buf[0] != 0)
            {
                strncat(buf, ",", sizeof(buf) - strlen(buf) - 1);
            }
            strncat(buf, mods_list[i]->id, sizeof(buf) - strlen(buf) - 1);
        }
    }
    return buf;
}

char **mods_child_argv(char **argv)
{
    char **out;
    int n = 0, i, j = 0;

    while (argv[n] != NULL)
    {
        n++;
    }
    out = calloc((size_t)n + 3, sizeof(*out));
    if (out == NULL)
    {
        abort();
    }
    for (i = 0; i < n; i++)
    {
        if (strcmp(argv[i], "--vanilla") == 0)
        {
            continue;
        }
        if (strcmp(argv[i], "--mods") == 0)
        {
            i++; // and its list
            continue;
        }
        out[j++] = argv[i];
    }
    if (mods_mode == MODS_ON)
    {
        const char *list = mods_enabled_list();

        out[j++] = "--mods";
        out[j++] = strdup(*list != 0 ? list : "none");
    }
    else
    {
        out[j++] = "--vanilla";
    }
    out[j] = NULL;
    return out;
}

void mods_start(void)
{
    int i;

    if (mods_mode != MODS_ON)
    {
        return;
    }
    port_log("mods: a modded run; mods on: %s",
             *mods_enabled_list() ? mods_enabled_list() : "none");
    for (i = 0; mods_list[i] != NULL; i++)
    {
        MOD *m = mods_list[i];

        if (m->enabled && m->enable != NULL)
        {
            m->enable(m, 1);
        }
    }
    mods_started = 1;
}

void mods_set_enabled(MOD *m, int on)
{
    if (m->enabled == on)
    {
        return;
    }
    m->enabled = on;
    if (mods_started && m->enable != NULL)
    {
        m->enable(m, on);
    }
    port_log("mods: %s %s", m->id, on ? "on" : "off");
    port_config_save("mods", "enabled", mods_enabled_list());
}

void mods_set_value(MOD *m, MOD_SETTING *s, int value)
{
    if (value < 0)
    {
        value = s->count - 1;
    }
    if (value >= s->count)
    {
        value = 0;
    }
    if (s->value == value)
    {
        return;
    }
    s->value = value;
    if (m->changed != NULL)
    {
        m->changed(m, s);
    }
    port_log("mods: %s.%s = %s", m->id, s->key, s->choices[value]);
    mods_save_setting(m, s);
}

void mods_save_setting(MOD *m, MOD_SETTING *s)
{
    char key[96];

    snprintf(key, sizeof(key), "%s.%s", m->id, s->key);
    port_config_save("mods", key, s->choices[s->value]);
}

#ifdef PORT_AOT_MIPS
// The 64-bit port: hook points compiled into the game (port/aot/mods_host.c).
void *mods_host_hook(uint32_t addr, void *fn);
void mods_host_unhook(uint32_t addr);
uint32_t mods_host_call(uint32_t addr, int n, const uint32_t args[4]);
#endif

void *mods_hook(uint32_t addr, void *fn)
{
#ifdef PORT_AOT_MIPS
    void *orig = mods_host_hook(addr, fn);
#else
    void *orig = port_stub_hook(addr, fn);
#endif

    if (orig == NULL)
    {
        port_log("mods: cannot hook the game function at 0x%08X", addr);
    }
    return orig;
}

void mods_unhook(uint32_t addr)
{
#ifdef PORT_AOT_MIPS
    mods_host_unhook(addr);
#else
    port_stub_unhook(addr);
#endif
}

uint32_t mods_call(uint32_t addr, int n, uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3)
{
#ifdef PORT_AOT_MIPS
    const uint32_t args[4] = {a0, a1, a2, a3};

    return mods_host_call(addr, n, args);
#else
    // The game function's native code is reached through its retail address (cdecl).
    switch (n)
    {
        case 0:
            return ((uint32_t (*)(void))(uintptr_t)addr)();
        case 1:
            return ((uint32_t (*)(uint32_t))(uintptr_t)addr)(a0);
        case 2:
            return ((uint32_t (*)(uint32_t, uint32_t))(uintptr_t)addr)(a0, a1);
        case 3:
            return ((uint32_t (*)(uint32_t, uint32_t, uint32_t))(uintptr_t)addr)(a0, a1, a2);
        default:
            return ((uint32_t (*)(uint32_t, uint32_t, uint32_t, uint32_t))(uintptr_t)addr)(a0, a1,
                                                                                         a2, a3);
    }
#endif
}
