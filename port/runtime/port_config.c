// Settings file. See port_config.h.
#define _GNU_SOURCE
#include "port_config.h"

#include "memcard.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

#define APP_DIR "megaman-legends"

const char port_config_default_text[] =
    "# Mega Man Legends (native port) settings. Delete a line to get its default back;\n"
    "# delete the file to get this one again. README.md in the source tree has the details.\n"
    "\n"
    "[game]\n"
    "# The disc image: a .cue file or a directory holding one. Empty: the build's default\n"
    "# (disc/image in the source tree). --disc overrides it.\n"
    "disc =\n"
    "\n"
    "[cards]\n"
    "# Memory-card images: raw 128 KB files (.mcd/.mcr, as PS1 emulators use). A name without\n"
    "# a directory lives in ~/.local/share/megaman-legends/ ($XDG_DATA_HOME). Slot 1 is always\n"
    "# inserted (the file appears with the first save); slot 2 only when its file exists or\n"
    "# slot2_insert = yes. Empty: no card in that slot. --card1/--card2 override them.\n"
    "slot1 = card1.mcd\n"
    "slot2 = card2.mcd\n"
    "slot2_insert = no\n"
    "# A modded run's cards (the [mods] section): separate files, so mods never write the\n"
    "# vanilla saves. --card1/--card2 still override them.\n"
    "slot1_mods = card1-mods.mcd\n"
    "slot2_mods = card2-mods.mcd\n"
    "\n"
    "[video]\n"
    "# Window size as a multiple of 320x240.\n"
    "scale = 3\n"
    "fullscreen = no\n"
    "# Whole-number scaling only (sharp pixels, black borders).\n"
    "integer_scale = no\n"
    "# Smooth (linear) filtering instead of sharp pixels.\n"
    "smooth = no\n"
    "\n"
    "[audio]\n"
    "# 0-100.\n"
    "volume = 100\n"
    "mute = no\n"
    "\n"
    "[pad]\n"
    "# analog: a DualShock in analog mode (sticks work; the game supports them);\n"
    "# digital: a plain pad, the left stick then moves the d-pad. F3 switches while playing.\n"
    "mode = analog\n"
    "# Stick dead zone in percent (sticks are reported centred inside it).\n"
    "deadzone = 10\n"
    "# Triggers count as pressed past this percentage.\n"
    "trigger = 50\n"
    "\n"
    "[keyboard]\n"
    "# PS1 button = SDL key name (https://wiki.libsdl.org/SDL3/SDL_Scancode without SDL_SCANCODE_;\n"
    "# e.g. A, Space, Return, Left Shift, Keypad 8). Several keys: separate them with commas.\n"
    "# Empty: no key.\n"
    "up = Up\n"
    "down = Down\n"
    "left = Left\n"
    "right = Right\n"
    "cross = X\n"
    "circle = C\n"
    "square = Z\n"
    "triangle = S\n"
    "l1 = W\n"
    "l2 = Q\n"
    "r1 = E\n"
    "r2 = R\n"
    "l3 =\n"
    "r3 =\n"
    "start = Return\n"
    "select = Right Shift\n"
    "# The left and right analog sticks (analog mode).\n"
    "lstick_up = I\n"
    "lstick_down = K\n"
    "lstick_left = J\n"
    "lstick_right = L\n"
    "rstick_up =\n"
    "rstick_down =\n"
    "rstick_left =\n"
    "rstick_right =\n"
    "# The port's own keys.\n"
    "fullscreen = F11\n"
    "analog_toggle = F3\n"
    "vram_view = Tab\n"
    "quit = Escape\n"
    "# The mod panel, while the game's pause menu is open (modded runs only).\n"
    "mods_menu = M\n"
    "\n"
    "[gamepad]\n"
    "# PS1 button = gamepad button, by position (SDL's names): south east west north,\n"
    "# leftshoulder rightshoulder lefttrigger righttrigger leftstick rightstick back start\n"
    "# guide dpup dpdown dpleft dpright, misc1, touchpad, and stick directions\n"
    "# leftstick_left/_right/_up/_down, rightstick_left/... (e.g. l1 = leftshoulder,\n"
    "# rightstick_left). Several: commas. Empty: none.\n"
    "# SDL's built-in database knows most pads; `mappings` adds a gamecontrollerdb.txt.\n"
    "cross = south\n"
    "circle = east\n"
    "square = west\n"
    "triangle = north\n"
    "l1 = leftshoulder\n"
    "r1 = rightshoulder\n"
    "l2 = lefttrigger\n"
    "r2 = righttrigger\n"
    "l3 = leftstick\n"
    "r3 = rightstick\n"
    "select = back\n"
    "start = start\n"
    "up = dpup\n"
    "down = dpdown\n"
    "left = dpleft\n"
    "right = dpright\n"
    "# Swap the sticks (yes/no).\n"
    "swap_sticks = no\n"
    "mappings =\n"
    "# The mod panel, while the game's pause menu is open (modded runs only). Not sent to\n"
    "# the game as a PS1 button while the panel takes it.\n"
    "mods_menu = rightstick\n"
    "\n"
    "[mods]\n"
    "# Vanilla or mods. ask: a menu in the window before the game\n"
    "# starts (Vanilla preselected); vanilla; mods. --vanilla and --mods LIST override it;\n"
    "# headless runs are vanilla unless --mods is given.\n"
    "startup = ask\n"
    "# The mods a modded run switches on: ids separated by commas, `all`, or empty for none.\n"
    "# The start-up menu and the pause panel change it.\n"
    "enabled = fast_skates\n"
    "# Faster skates: Mega Man's speed on the Jet Skates (1.5x, 2x, 3x).\n"
    "fast_skates.speed = 2x\n";

typedef struct
{
    char *section, *key, *value;
} ENTRY;

static ENTRY *entries;
static int count, capacity;
static char *file_path;

static void set(const char *section, const char *key, const char *value)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcasecmp(entries[i].section, section) == 0 && strcasecmp(entries[i].key, key) == 0)
        {
            free(entries[i].value);
            entries[i].value = strdup(value);
            return;
        }
    }
    if (count == capacity)
    {
        capacity = capacity ? capacity * 2 : 128;
        entries  = realloc(entries, (size_t)capacity * sizeof(*entries));
        if (entries == NULL)
        {
            abort();
        }
    }
    entries[count].section = strdup(section);
    entries[count].key     = strdup(key);
    entries[count].value   = strdup(value);
    count++;
}

void port_config_set(const char *section, const char *key, const char *value)
{
    set(section, key, value);
}

static char *trim(char *s)
{
    char *e;

    while (isspace((unsigned char)*s))
    {
        s++;
    }
    e = s + strlen(s);
    while (e > s && isspace((unsigned char)e[-1]))
    {
        *--e = 0;
    }
    return s;
}

static void parse(const char *text, const char *name)
{
    char section[64] = "";
    const char *p    = text;
    int line         = 0;

    while (*p != 0)
    {
        const char *nl = strchr(p, '\n');
        size_t len     = nl != NULL ? (size_t)(nl - p) : strlen(p);
        char buf[1024], *s, *eq;

        line++;
        if (len >= sizeof(buf))
        {
            len = sizeof(buf) - 1;
        }
        memcpy(buf, p, len);
        buf[len] = 0;
        p += len + (nl != NULL);
        s = trim(buf);
        if (*s == 0 || *s == '#' || *s == ';')
        {
            continue;
        }
        if (*s == '[')
        {
            char *close = strchr(s, ']');

            if (close != NULL)
            {
                *close = 0;
                snprintf(section, sizeof(section), "%s", trim(s + 1));
                continue;
            }
        }
        eq = strchr(s, '=');
        if (eq == NULL)
        {
            fprintf(stderr, "port: %s:%d: not `key = value`: %s\n", name, line, s);
            continue;
        }
        *eq = 0;
        set(section, trim(s), trim(eq + 1));
    }
}

static char *xdg_dir(const char *var, const char *fallback)
{
    const char *base = getenv(var);
    const char *home = getenv("HOME");
    char *out;

    if (base != NULL && base[0] == '/')
    {
        if (asprintf(&out, "%s/%s", base, APP_DIR) < 0)
        {
            abort();
        }
    }
    else if (asprintf(&out, "%s/%s/%s", home != NULL ? home : ".", fallback, APP_DIR) < 0)
    {
        abort();
    }
    return out;
}

static void mkdir_p(const char *dir)
{
    char *d = strdup(dir), *p;

    for (p = d + 1; *p != 0; p++)
    {
        if (*p == '/')
        {
            *p = 0;
            mkdir(d, 0755);
            *p = '/';
        }
    }
    mkdir(d, 0755);
    free(d);
}

int port_config_load(const char *path, int write_default)
{
    FILE *f;
    char *text;
    long n;

    parse(port_config_default_text, "defaults");
    free(file_path);
    if (path != NULL)
    {
        file_path = strdup(path);
    }
    else
    {
        char *dir = xdg_dir("XDG_CONFIG_HOME", ".config");

        if (asprintf(&file_path, "%s/config.ini", dir) < 0)
        {
            abort();
        }
        free(dir);
    }
    f = fopen(file_path, "rb");
    if (f == NULL)
    {
        if (errno != ENOENT)
        {
            fprintf(stderr, "port: cannot read %s: %s\n", file_path, strerror(errno));
            return -1;
        }
        if (write_default)
        {
            char *dir = strdup(file_path), *slash = strrchr(dir, '/');

            if (slash != NULL)
            {
                *slash = 0;
                mkdir_p(dir);
            }
            free(dir);
            f = fopen(file_path, "wx");
            if (f != NULL)
            {
                fputs(port_config_default_text, f);
                fclose(f);
                fprintf(stderr, "port: wrote the default settings to %s\n", file_path);
            }
        }
        return 0;
    }
    fseek(f, 0, SEEK_END);
    n = ftell(f);
    fseek(f, 0, SEEK_SET);
    text = malloc((size_t)n + 1);
    if (text == NULL || fread(text, 1, (size_t)n, f) != (size_t)n)
    {
        fclose(f);
        free(text);
        return -1;
    }
    text[n] = 0;
    fclose(f);
    parse(text, file_path);
    free(text);
    return 0;
}

const char *port_config_file(void)
{
    return file_path;
}

const char *port_config_get(const char *section, const char *key)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcasecmp(entries[i].section, section) == 0 && strcasecmp(entries[i].key, key) == 0)
        {
            return entries[i].value;
        }
    }
    return NULL;
}

int port_config_int(const char *section, const char *key, int fallback)
{
    const char *v = port_config_get(section, key);
    char *e;
    long n;

    if (v == NULL || *v == 0)
    {
        return fallback;
    }
    n = strtol(v, &e, 0);
    return *e == 0 ? (int)n : fallback;
}

int port_config_bool(const char *section, const char *key, int fallback)
{
    const char *v = port_config_get(section, key);

    if (v == NULL)
    {
        return fallback;
    }
    if (!strcasecmp(v, "1") || !strcasecmp(v, "yes") || !strcasecmp(v, "true") ||
        !strcasecmp(v, "on"))
    {
        return 1;
    }
    if (!strcasecmp(v, "0") || !strcasecmp(v, "no") || !strcasecmp(v, "false") ||
        !strcasecmp(v, "off"))
    {
        return 0;
    }
    return fallback;
}

void port_config_each(const char *section, void (*fn)(const char *, const char *, void *),
                      void *ctx)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcasecmp(entries[i].section, section) == 0)
        {
            fn(entries[i].key, entries[i].value, ctx);
        }
    }
}

char *port_data_path(const char *name)
{
    char *dir, *out;

    if (name[0] == '/')
    {
        return strdup(name);
    }
    if (name[0] == '~' && name[1] == '/' && getenv("HOME") != NULL)
    {
        if (asprintf(&out, "%s%s", getenv("HOME"), name + 1) < 0)
        {
            abort();
        }
        return out;
    }
    dir = xdg_dir("XDG_DATA_HOME", ".local/share");
    if (asprintf(&out, "%s/%s", dir, name) < 0)
    {
        abort();
    }
    free(dir);
    return out;
}

void port_config_apply_cards(void)
{
    static const char *keys[MEMCARD_SLOTS] = {"slot1", "slot2"};
    int slot;

    for (slot = 0; slot < MEMCARD_SLOTS; slot++)
    {
        const char *v = port_config_get("cards", keys[slot]);
        char *path;

        if (v == NULL || *v == 0)
        {
            memcard_set_path(slot, NULL, 0);
            continue;
        }
        path = port_data_path(v);
        memcard_set_path(slot, path,
                         slot == 0 || port_config_bool("cards", "slot2_insert", 0));
        free(path);
    }
}

int port_config_save(const char *section, const char *key, const char *value)
{
    FILE *f;
    char *text = NULL, *out, *tmp;
    size_t len = 0, cap;
    const char *p, *insert_at = NULL, *replace_at = NULL, *replace_end = NULL;
    char cur[64]   = "";
    int in_section = 0, ok;

    set(section, key, value);
    if (file_path == NULL)
    {
        return -1;
    }
    f = fopen(file_path, "rb");
    if (f != NULL)
    {
        long n;

        fseek(f, 0, SEEK_END);
        n = ftell(f);
        fseek(f, 0, SEEK_SET);
        text = malloc((size_t)n + 1);
        if (text == NULL || fread(text, 1, (size_t)n, f) != (size_t)n)
        {
            fclose(f);
            free(text);
            return -1;
        }
        text[n] = 0;
        len     = (size_t)n;
        fclose(f);
    }
    else
    {
        text = strdup(port_config_default_text);
        len  = strlen(text);
    }
    // Find the key's line in its section, or the end of the section's last setting.
    for (p = text; *p != 0;)
    {
        const char *nl = strchr(p, '\n'), *end = nl != NULL ? nl + 1 : p + strlen(p);
        char line[1024], *s, *eq;
        size_t l = (size_t)(end - p);

        if (l >= sizeof(line))
        {
            l = sizeof(line) - 1;
        }
        memcpy(line, p, l);
        line[l] = 0;
        s       = trim(line);
        if (*s == '[' && strchr(s, ']') != NULL)
        {
            *strchr(s, ']') = 0;
            snprintf(cur, sizeof(cur), "%s", trim(s + 1));
            in_section = strcasecmp(cur, section) == 0;
            if (in_section)
            {
                insert_at = end;
            }
        }
        else if (in_section && *s != 0 && *s != '#' && *s != ';' && (eq = strchr(s, '=')) != NULL)
        {
            *eq = 0;
            if (strcasecmp(trim(s), key) == 0)
            {
                replace_at  = p;
                replace_end = end;
                break;
            }
            insert_at = end;
        }
        p = end;
    }
    cap = len + strlen(section) + strlen(key) + strlen(value) + 32;
    out = malloc(cap);
    if (out == NULL)
    {
        free(text);
        return -1;
    }
    if (replace_at != NULL)
    {
        snprintf(out, cap, "%.*s%s = %s\n%s", (int)(replace_at - text), text, key, value,
                 replace_end);
    }
    else if (insert_at != NULL)
    {
        snprintf(out, cap, "%.*s%s%s = %s\n%s", (int)(insert_at - text), text,
                 insert_at > text && insert_at[-1] != '\n' ? "\n" : "", key, value, insert_at);
    }
    else
    {
        snprintf(out, cap, "%s%s\n[%s]\n%s = %s\n", text,
                 len > 0 && text[len - 1] != '\n' ? "\n" : "", section, key, value);
    }
    free(text);
    {
        char *dir = strdup(file_path), *slash = strrchr(dir, '/');

        if (slash != NULL)
        {
            *slash = 0;
            mkdir_p(dir);
        }
        free(dir);
    }
    if (asprintf(&tmp, "%s.tmp", file_path) < 0)
    {
        free(out);
        return -1;
    }
    f  = fopen(tmp, "wb");
    ok = f != NULL && fputs(out, f) >= 0;
    if (f != NULL && fclose(f) != 0)
    {
        ok = 0;
    }
    if (ok && rename(tmp, file_path) != 0)
    {
        ok = 0;
    }
    if (!ok)
    {
        fprintf(stderr, "port: cannot write %s: %s\n", file_path, strerror(errno));
        unlink(tmp);
    }
    free(tmp);
    free(out);
    return ok ? 0 : -1;
}
