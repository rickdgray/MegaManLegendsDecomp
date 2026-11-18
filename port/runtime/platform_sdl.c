// SDL3 window and input. See platform_sdl.h; the settings come from port_config.h.
#define _GNU_SOURCE
#include "platform_sdl.h"

#include "gpu.h"
#include "port_config.h"
#include "port_overlay.h"
#include "port_remote.h"

#include <SDL3/SDL.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MAX_BIND 4

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static SDL_Gamepad *gamepads[PLATFORM_PADS];
static int full_vram   = 1;
static int analog_mode = 1;
static int integer_scale;
static int deadzone = 3277;  // stick units (of 32767)
static int trigger  = 16384; // trigger units
static int swap_sticks;

// --- bindings -------------------------------------------------------------------------------

static const struct
{
    const char *name;
    uint16_t bit;
} psx_buttons[] = {
    {"up", PSX_PAD_UP},         {"down", PSX_PAD_DOWN},           {"left", PSX_PAD_LEFT},
    {"right", PSX_PAD_RIGHT},   {"cross", PSX_PAD_CROSS},         {"circle", PSX_PAD_CIRCLE},
    {"square", PSX_PAD_SQUARE}, {"triangle", PSX_PAD_TRIANGLE},   {"l1", PSX_PAD_L1},
    {"l2", PSX_PAD_L2},         {"r1", PSX_PAD_R1},               {"r2", PSX_PAD_R2},
    {"l3", PSX_PAD_L3},         {"r3", PSX_PAD_R3},               {"start", PSX_PAD_START},
    {"select", PSX_PAD_SELECT},
};
#define PSX_BUTTONS (int)(sizeof(psx_buttons) / sizeof(psx_buttons[0]))

// Keyboard slots: the 16 buttons, then 8 stick directions, then the port's keys.
enum
{
    K_LSTICK_UP = 16,
    K_LSTICK_DOWN,
    K_LSTICK_LEFT,
    K_LSTICK_RIGHT,
    K_RSTICK_UP,
    K_RSTICK_DOWN,
    K_RSTICK_LEFT,
    K_RSTICK_RIGHT,
    K_FULLSCREEN,
    K_ANALOG,
    K_VRAM,
    K_QUIT,
    K_MODS, // the mod panel (a host button: PORT_HOST_MODS)
    K_COUNT
};
static const char *const key_extra[] = {
    "lstick_up",   "lstick_down", "lstick_left",  "lstick_right", "rstick_up",
    "rstick_down", "rstick_left", "rstick_right", "fullscreen",   "analog_toggle",
    "vram_view",   "quit",        "mods_menu"};
static SDL_Scancode keys[K_COUNT][MAX_BIND];

// Gamepad inputs: SDL buttons, plus the two triggers and the stick directions (which SDL
// reports as axes; pressed past `[pad] trigger`, so e.g. `l1 = rightstick_left` works).
#define PAD_TRIGGER_L (SDL_GAMEPAD_BUTTON_COUNT + 0)
#define PAD_TRIGGER_R (SDL_GAMEPAD_BUTTON_COUNT + 1)
#define PAD_STICK_DIR (SDL_GAMEPAD_BUTTON_COUNT + 2) // + stick * 4 + (left, right, up, down)
#define PAD_NONE      (-1)
static int pad_binds[16][MAX_BIND];
static int pad_mods_binds[MAX_BIND]; // gamepad.mods_menu (PORT_HOST_MODS)

static const struct
{
    const char *name;
    int input;
} pad_inputs[] = {
    {"south", SDL_GAMEPAD_BUTTON_SOUTH},
    {"east", SDL_GAMEPAD_BUTTON_EAST},
    {"west", SDL_GAMEPAD_BUTTON_WEST},
    {"north", SDL_GAMEPAD_BUTTON_NORTH},
    {"back", SDL_GAMEPAD_BUTTON_BACK},
    {"guide", SDL_GAMEPAD_BUTTON_GUIDE},
    {"start", SDL_GAMEPAD_BUTTON_START},
    {"leftstick", SDL_GAMEPAD_BUTTON_LEFT_STICK},
    {"rightstick", SDL_GAMEPAD_BUTTON_RIGHT_STICK},
    {"leftshoulder", SDL_GAMEPAD_BUTTON_LEFT_SHOULDER},
    {"rightshoulder", SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER},
    {"dpup", SDL_GAMEPAD_BUTTON_DPAD_UP},
    {"dpdown", SDL_GAMEPAD_BUTTON_DPAD_DOWN},
    {"dpleft", SDL_GAMEPAD_BUTTON_DPAD_LEFT},
    {"dpright", SDL_GAMEPAD_BUTTON_DPAD_RIGHT},
    {"misc1", SDL_GAMEPAD_BUTTON_MISC1},
    {"touchpad", SDL_GAMEPAD_BUTTON_TOUCHPAD},
    {"lefttrigger", PAD_TRIGGER_L},
    {"righttrigger", PAD_TRIGGER_R},
    {"leftstick_left", PAD_STICK_DIR + 0},
    {"leftstick_right", PAD_STICK_DIR + 1},
    {"leftstick_up", PAD_STICK_DIR + 2},
    {"leftstick_down", PAD_STICK_DIR + 3},
    {"rightstick_left", PAD_STICK_DIR + 4},
    {"rightstick_right", PAD_STICK_DIR + 5},
    {"rightstick_up", PAD_STICK_DIR + 6},
    {"rightstick_down", PAD_STICK_DIR + 7},
};

// Splits "a, b, c" into trimmed names; returns how many.
static int split_list(const char *list, char names[MAX_BIND][48])
{
    int n = 0;

    while (list != NULL && *list != 0 && n < MAX_BIND)
    {
        const char *comma = strchr(list, ',');
        size_t len        = comma != NULL ? (size_t)(comma - list) : strlen(list);

        while (len > 0 && (*list == ' ' || *list == '\t'))
        {
            list++;
            len--;
        }
        while (len > 0 && (list[len - 1] == ' ' || list[len - 1] == '\t'))
        {
            len--;
        }
        if (len > 0 && len < 48)
        {
            memcpy(names[n], list, len);
            names[n][len] = 0;
            n++;
        }
        list = comma != NULL ? comma + 1 : NULL;
    }
    return n;
}

static void bind_keys(int slot, const char *key)
{
    char names[MAX_BIND][48];
    int i, n = split_list(port_config_get("keyboard", key), names);

    for (i = 0; i < MAX_BIND; i++)
    {
        keys[slot][i] = SDL_SCANCODE_UNKNOWN;
    }
    for (i = 0; i < n; i++)
    {
        keys[slot][i] = SDL_GetScancodeFromName(names[i]);
        if (keys[slot][i] == SDL_SCANCODE_UNKNOWN)
        {
            fprintf(stderr, "port: settings: unknown key \"%s\" for keyboard.%s\n", names[i], key);
        }
    }
}

static void bind_pad_list(int binds[MAX_BIND], const char *key)
{
    char names[MAX_BIND][48];
    int i, j, n = split_list(port_config_get("gamepad", key), names);

    for (i = 0; i < MAX_BIND; i++)
    {
        binds[i] = PAD_NONE;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < (int)(sizeof(pad_inputs) / sizeof(pad_inputs[0])); j++)
        {
            if (strcasecmp(names[i], pad_inputs[j].name) == 0)
            {
                binds[i] = pad_inputs[j].input;
                break;
            }
        }
        if (binds[i] == PAD_NONE)
        {
            fprintf(stderr, "port: settings: unknown gamepad input \"%s\" for gamepad.%s\n",
                    names[i], key);
        }
    }
}

static void bind_pad(int slot, const char *key)
{
    bind_pad_list(pad_binds[slot], key);
}

static void load_settings(void)
{
    const char *mappings = port_config_get("gamepad", "mappings");
    const char *mode     = port_config_get("pad", "mode");
    int i;

    for (i = 0; i < PSX_BUTTONS; i++)
    {
        bind_keys(i, psx_buttons[i].name);
        bind_pad(i, psx_buttons[i].name);
    }
    for (i = K_LSTICK_UP; i < K_COUNT; i++)
    {
        bind_keys(i, key_extra[i - K_LSTICK_UP]);
    }
    bind_pad_list(pad_mods_binds, "mods_menu");
    analog_mode   = mode == NULL || strcasecmp(mode, "digital") != 0;
    integer_scale = port_config_bool("video", "integer_scale", 0);
    deadzone      = port_config_int("pad", "deadzone", 10) * 32767 / 100;
    trigger       = port_config_int("pad", "trigger", 50) * 32767 / 100;
    swap_sticks   = port_config_bool("gamepad", "swap_sticks", 0);
    if (mappings != NULL && *mappings != 0)
    {
        char *path = port_data_path(mappings);

        if (SDL_AddGamepadMappingsFromFile(path) < 0)
        {
            fprintf(stderr, "port: gamepad mappings %s: %s\n", path, SDL_GetError());
        }
        free(path);
    }
}

static int key_is(SDL_Scancode sc, int slot)
{
    int i;

    for (i = 0; i < MAX_BIND; i++)
    {
        if (keys[slot][i] != SDL_SCANCODE_UNKNOWN && keys[slot][i] == sc)
        {
            return 1;
        }
    }
    return 0;
}

static int key_held(const bool *state, int slot)
{
    int i;

    for (i = 0; i < MAX_BIND; i++)
    {
        if (keys[slot][i] != SDL_SCANCODE_UNKNOWN && state[keys[slot][i]])
        {
            return 1;
        }
    }
    return 0;
}

// --- gamepads -------------------------------------------------------------------------------

static void open_gamepad(SDL_JoystickID id)
{
    int i;

    for (i = 0; i < PLATFORM_PADS; i++)
    {
        if (gamepads[i] != NULL && SDL_GetGamepadID(gamepads[i]) == id)
        {
            return;
        }
    }
    for (i = 0; i < PLATFORM_PADS; i++)
    {
        if (gamepads[i] == NULL)
        {
            gamepads[i] = SDL_OpenGamepad(id);
            if (gamepads[i] != NULL)
            {
                printf("pad %d: %s\n", i + 1, SDL_GetGamepadName(gamepads[i]));
            }
            return;
        }
    }
}

static void close_gamepad(SDL_JoystickID id)
{
    int i;

    for (i = 0; i < PLATFORM_PADS; i++)
    {
        if (gamepads[i] != NULL && SDL_GetGamepadID(gamepads[i]) == id)
        {
            printf("pad %d: disconnected\n", i + 1);
            SDL_CloseGamepad(gamepads[i]);
            gamepads[i] = NULL;
        }
    }
}

// --- window ---------------------------------------------------------------------------------

int platform_init(const char *title, int scale)
{
    int smooth = port_config_bool("video", "smooth", 0);

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return -1;
    }
    load_settings();
    scale = port_config_int("video", "scale", scale);
    if (scale < 1)
    {
        scale = 1;
    }
    window = SDL_CreateWindow(title, 320 * scale, 240 * scale, SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
        return -1;
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
        return -1;
    }
    SDL_SetRenderVSync(renderer, 1);
    // The PS1's 15-bit pixels (red in the low bits) are SDL's XBGR1555 exactly.
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_XBGR1555, SDL_TEXTUREACCESS_STREAMING,
                                GPU_VRAM_W, GPU_VRAM_H);
    if (texture == NULL)
    {
        fprintf(stderr, "SDL_CreateTexture: %s\n", SDL_GetError());
        return -1;
    }
    SDL_SetTextureScaleMode(texture, smooth ? SDL_SCALEMODE_LINEAR : SDL_SCALEMODE_NEAREST);
    if (port_config_bool("video", "fullscreen", 0))
    {
        SDL_SetWindowFullscreen(window, true);
    }
    return 0;
}

// --- audio ----------------------------------------------------------------------------------

static SDL_AudioStream *audio_stream;
static void (*audio_pull)(int16_t *out, int frames);

// SDL's audio thread asks for more data: hand it what the game has mixed.
static void SDLCALL audio_more(void *userdata, SDL_AudioStream *stream, int additional, int total)
{
    int16_t buf[1024 * 2];

    (void)userdata;
    (void)total;
    while (additional > 0)
    {
        int n = additional / 4;

        if (n > 1024)
        {
            n = 1024;
        }
        if (n == 0)
        {
            n = 1;
        }
        audio_pull(buf, n);
        SDL_PutAudioStreamData(stream, buf, n * 4);
        additional -= n * 4;
    }
}

int platform_audio_open(int rate, void (*pull)(int16_t *out, int frames))
{
    SDL_AudioSpec spec;

    if (!SDL_InitSubSystem(SDL_INIT_AUDIO))
    {
        fprintf(stderr, "SDL audio: %s\n", SDL_GetError());
        return -1;
    }
    spec.format   = SDL_AUDIO_S16;
    spec.channels = 2;
    spec.freq     = rate;
    audio_pull    = pull;
    audio_stream =
        SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, audio_more, NULL);
    if (audio_stream == NULL)
    {
        fprintf(stderr, "SDL audio device: %s\n", SDL_GetError());
        return -1;
    }
    SDL_ResumeAudioStreamDevice(audio_stream);
    return 0;
}

void platform_audio_lock(int lock)
{
    if (audio_stream == NULL)
    {
        return;
    }
    if (lock)
    {
        SDL_LockAudioStream(audio_stream);
        SDL_ClearAudioStream(audio_stream);
    }
    else
    {
        SDL_UnlockAudioStream(audio_stream);
    }
}

void platform_shutdown(void)
{
    int i;

    if (audio_stream != NULL)
    {
        SDL_DestroyAudioStream(audio_stream);
        audio_stream = NULL;
    }

    for (i = 0; i < PLATFORM_PADS; i++)
    {
        if (gamepads[i] != NULL)
        {
            SDL_CloseGamepad(gamepads[i]);
            gamepads[i] = NULL;
        }
    }
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
    }
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

// --- input ----------------------------------------------------------------------------------

static uint8_t axis_byte(Sint16 v)
{
    if (v > -deadzone && v < deadzone)
    {
        v = 0;
    }
    return (uint8_t)((v + 32768) >> 8);
}

static int pad_input(SDL_Gamepad *gp, int input)
{
    if (input == PAD_TRIGGER_L)
    {
        return SDL_GetGamepadAxis(gp, SDL_GAMEPAD_AXIS_LEFT_TRIGGER) > trigger;
    }
    if (input == PAD_TRIGGER_R)
    {
        return SDL_GetGamepadAxis(gp, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) > trigger;
    }
    if (input >= PAD_STICK_DIR && input < PAD_STICK_DIR + 8)
    {
        int d          = input - PAD_STICK_DIR;
        int right      = d >= 4;
        int vertical   = (d & 2) != 0;
        int positive   = (d & 1) != 0;
        SDL_GamepadAxis a = vertical ? (right ? SDL_GAMEPAD_AXIS_RIGHTY : SDL_GAMEPAD_AXIS_LEFTY)
                                     : (right ? SDL_GAMEPAD_AXIS_RIGHTX : SDL_GAMEPAD_AXIS_LEFTX);
        Sint16 v       = SDL_GetGamepadAxis(gp, a);

        return positive ? v > trigger : v < -trigger;
    }
    return input >= 0 && SDL_GetGamepadButton(gp, (SDL_GamepadButton)input);
}

static void read_gamepad(SDL_Gamepad *gp, PSX_PAD_STATE *s)
{
    SDL_GamepadAxis lx = SDL_GAMEPAD_AXIS_LEFTX, ly = SDL_GAMEPAD_AXIS_LEFTY;
    SDL_GamepadAxis rx = SDL_GAMEPAD_AXIS_RIGHTX, ry = SDL_GAMEPAD_AXIS_RIGHTY;
    int i, j;

    for (i = 0; i < PSX_BUTTONS; i++)
    {
        for (j = 0; j < MAX_BIND; j++)
        {
            if (pad_binds[i][j] != PAD_NONE && pad_input(gp, pad_binds[i][j]))
            {
                s->buttons |= psx_buttons[i].bit;
            }
        }
    }
    for (j = 0; j < MAX_BIND; j++)
    {
        if (pad_mods_binds[j] != PAD_NONE && pad_input(gp, pad_mods_binds[j]))
        {
            s->host |= PORT_HOST_MODS;
        }
    }
    if (swap_sticks)
    {
        lx = SDL_GAMEPAD_AXIS_RIGHTX;
        ly = SDL_GAMEPAD_AXIS_RIGHTY;
        rx = SDL_GAMEPAD_AXIS_LEFTX;
        ry = SDL_GAMEPAD_AXIS_LEFTY;
    }
    s->lx = axis_byte(SDL_GetGamepadAxis(gp, lx));
    s->ly = axis_byte(SDL_GetGamepadAxis(gp, ly));
    s->rx = axis_byte(SDL_GetGamepadAxis(gp, rx));
    s->ry = axis_byte(SDL_GetGamepadAxis(gp, ry));
}

static void read_keyboard(PSX_PAD_STATE *s)
{
    const bool *state = SDL_GetKeyboardState(NULL);
    int i;

    for (i = 0; i < PSX_BUTTONS; i++)
    {
        if (key_held(state, i))
        {
            s->buttons |= psx_buttons[i].bit;
        }
    }
    if (key_held(state, K_MODS))
    {
        s->host |= PORT_HOST_MODS;
    }
    if (key_held(state, K_LSTICK_LEFT))
    {
        s->lx = 0x00;
    }
    if (key_held(state, K_LSTICK_RIGHT))
    {
        s->lx = 0xFF;
    }
    if (key_held(state, K_LSTICK_UP))
    {
        s->ly = 0x00;
    }
    if (key_held(state, K_LSTICK_DOWN))
    {
        s->ly = 0xFF;
    }
    if (key_held(state, K_RSTICK_LEFT))
    {
        s->rx = 0x00;
    }
    if (key_held(state, K_RSTICK_RIGHT))
    {
        s->rx = 0xFF;
    }
    if (key_held(state, K_RSTICK_UP))
    {
        s->ry = 0x00;
    }
    if (key_held(state, K_RSTICK_DOWN))
    {
        s->ry = 0xFF;
    }
}

// Digital mode: the console's plain pad has no sticks, so the left stick drives the d-pad.
static void stick_to_dpad(PSX_PAD_STATE *s)
{
    if (s->lx < 0x40)
    {
        s->buttons |= PSX_PAD_LEFT;
    }
    if (s->lx > 0xC0)
    {
        s->buttons |= PSX_PAD_RIGHT;
    }
    if (s->ly < 0x40)
    {
        s->buttons |= PSX_PAD_UP;
    }
    if (s->ly > 0xC0)
    {
        s->buttons |= PSX_PAD_DOWN;
    }
    s->lx = s->ly = s->rx = s->ry = 0x80;
}

int platform_poll(PSX_PAD_STATE pads[PLATFORM_PADS])
{
    SDL_Event ev;
    int i;

    while (SDL_PollEvent(&ev))
    {
        switch (ev.type)
        {
            case SDL_EVENT_QUIT:
                return 0;
            case SDL_EVENT_KEY_DOWN:
                if (ev.key.repeat)
                {
                    break;
                }
                if (key_is(ev.key.scancode, K_QUIT))
                {
                    return 0;
                }
                if (key_is(ev.key.scancode, K_VRAM))
                {
                    full_vram = !full_vram;
                }
                if (key_is(ev.key.scancode, K_ANALOG))
                {
                    analog_mode = !analog_mode;
                    printf("pad mode: %s\n", analog_mode ? "analog" : "digital");
                }
                if (key_is(ev.key.scancode, K_FULLSCREEN))
                {
                    SDL_SetWindowFullscreen(window,
                                            !(SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN));
                }
                break;
            case SDL_EVENT_GAMEPAD_ADDED:
                open_gamepad(ev.gdevice.which);
                break;
            case SDL_EVENT_GAMEPAD_REMOVED:
                close_gamepad(ev.gdevice.which);
                break;
            default:
                break;
        }
    }
    for (i = 0; i < PLATFORM_PADS; i++)
    {
        psx_pad_reset(&pads[i]);
        pads[i].analog    = analog_mode;
        pads[i].connected = (i == 0) || gamepads[i] != NULL;
        if (gamepads[i] != NULL)
        {
            read_gamepad(gamepads[i], &pads[i]);
        }
    }
    read_keyboard(&pads[0]);
    if (!analog_mode)
    {
        for (i = 0; i < PLATFORM_PADS; i++)
        {
            stick_to_dpad(&pads[i]);
        }
    }
    return 1;
}

void platform_set_full_vram(int on)
{
    full_vram = on;
}

// The port's text layer (port_overlay.h) over the picture: a 320x240 space of 8x8 cells,
// letterboxed like the game, so it scales with the window.
static void draw_overlay(const PORT_OVERLAY *o)
{
    static const SDL_Color colours[OVL_COLOURS] = {
        {230, 230, 230, 255}, // OVL_TEXT
        {150, 160, 175, 255}, // OVL_DIM
        {255, 210, 90, 255},  // OVL_TITLE
        {120, 220, 255, 255}, // OVL_CURSOR
        {120, 235, 130, 255}, // OVL_ON
        {235, 120, 110, 255}, // OVL_OFF
    };
    const float cell = (float)SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    char run[PORT_OVERLAY_COLS + 1];
    int row, col;

    if (o == NULL || !o->visible)
    {
        return;
    }
    SDL_SetRenderLogicalPresentation(renderer, PORT_OVERLAY_COLS * 8, PORT_OVERLAY_ROWS * 8,
                                     SDL_LOGICAL_PRESENTATION_LETTERBOX);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    if (o->shade > 0)
    {
        SDL_FRect all = {0, 0, PORT_OVERLAY_COLS * 8, PORT_OVERLAY_ROWS * 8};

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, (Uint8)(o->shade > 255 ? 255 : o->shade));
        SDL_RenderFillRect(renderer, &all);
    }
    if (o->box_w > 0 && o->box_h > 0)
    {
        SDL_FRect box = {o->box_x * cell - 4, o->box_y * cell - 4, o->box_w * cell + 8,
                         o->box_h * cell + 8};

        SDL_SetRenderDrawColor(renderer, 10, 20, 45, 225);
        SDL_RenderFillRect(renderer, &box);
        SDL_SetRenderDrawColor(renderer, 90, 140, 220, 255);
        SDL_RenderRect(renderer, &box);
    }
    // Runs of one colour per call.
    for (row = 0; row < PORT_OVERLAY_ROWS; row++)
    {
        col = 0;
        while (col < PORT_OVERLAY_COLS)
        {
            int start = col, n = 0, c = o->colour[row][col];

            while (col < PORT_OVERLAY_COLS && o->colour[row][col] == c)
            {
                char ch = o->text[row][col];

                run[n++] = ch >= 0x20 && ch < 0x7F ? ch : ' ';
                col++;
            }
            run[n] = 0;
            if (strspn(run, " ") != (size_t)n)
            {
                SDL_Color k = colours[c < OVL_COLOURS ? c : 0];

                SDL_SetRenderDrawColor(renderer, k.r, k.g, k.b, k.a);
                SDL_RenderDebugText(renderer, start * cell, row * cell, run);
            }
        }
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

// A 24-bit display (GP1(08h) bit 4, the movies): each display pixel is three bytes of VRAM,
// red first, packed across the 16-bit pixels from the display area's left edge.
static SDL_Texture *texture24;

static int present24(const uint16_t *vram, int x, int y, int w, int h, const PORT_OVERLAY *o)
{
    static uint8_t rgb[GPU_VRAM_W * GPU_VRAM_H * 3 / 2];
    SDL_FRect src;
    int row, col;

    if (texture24 == NULL)
    {
        texture24 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING,
                                      GPU_VRAM_W * 2 / 3, GPU_VRAM_H);
        if (texture24 == NULL)
        {
            return -1;
        }
        SDL_SetTextureScaleMode(texture24, port_config_bool("video", "smooth", 0)
                                               ? SDL_SCALEMODE_LINEAR
                                               : SDL_SCALEMODE_NEAREST);
    }
    if (w > GPU_VRAM_W * 2 / 3)
    {
        w = GPU_VRAM_W * 2 / 3;
    }
    for (row = 0; row < h; row++)
    {
        const uint16_t *line = &vram[((y + row) & (GPU_VRAM_H - 1)) * GPU_VRAM_W];

        for (col = 0; col < w * 3; col++)
        {
            int byte    = x * 2 + col;
            uint16_t px = line[(byte >> 1) & (GPU_VRAM_W - 1)];
            rgb[row * w * 3 + col] = (uint8_t)((byte & 1) ? px >> 8 : px);
        }
    }
    src.x = 0;
    src.y = 0;
    src.w = (float)w;
    src.h = (float)h;
    SDL_UpdateTexture(texture24, NULL, rgb, w * 3);
    SDL_SetRenderLogicalPresentation(renderer, w, h,
                                     integer_scale ? SDL_LOGICAL_PRESENTATION_INTEGER_SCALE
                                                   : SDL_LOGICAL_PRESENTATION_LETTERBOX);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture24, &src, NULL);
    draw_overlay(o);
    SDL_RenderPresent(renderer);
    return 0;
}

static void present(const uint16_t *vram, int x, int y, int w, int h, int is24,
                    const PORT_OVERLAY *o)
{
    SDL_FRect src;

    if (is24 && !full_vram && w > 0 && h > 0 && present24(vram, x, y, w, h, o) == 0)
    {
        return;
    }
    SDL_UpdateTexture(texture, NULL, vram, GPU_VRAM_W * 2);
    if (full_vram || w <= 0 || h <= 0)
    {
        src.x = 0;
        src.y = 0;
        src.w = GPU_VRAM_W;
        src.h = GPU_VRAM_H;
    }
    else
    {
        src.x = (float)x;
        src.y = (float)y;
        src.w = (float)w;
        src.h = (float)h;
    }
    SDL_SetRenderLogicalPresentation(renderer, (int)src.w, (int)src.h,
                                     integer_scale ? SDL_LOGICAL_PRESENTATION_INTEGER_SCALE
                                                   : SDL_LOGICAL_PRESENTATION_LETTERBOX);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, &src, NULL);
    draw_overlay(o);
    SDL_RenderPresent(renderer);
}

void platform_present(void)
{
    const GPU_DISPLAY *d = gpu_display();

    present(gpu_vram(), d->x, d->y, d->w, d->h, d->is24, port_overlay());
}

// --- window host (port_remote.h) ------------------------------------------------------------

static volatile sig_atomic_t host_signal;

static void on_host_signal(int sig)
{
    host_signal = sig;
}

int platform_host_run(int child)
{
    static uint16_t vram[GPU_VRAM_W * GPU_VRAM_H];
    static PORT_OVERLAY overlay; // the game's text layer, with its frames
    PORT_REMOTE *r           = port_remote();
    const GPU_DISPLAY *d     = gpu_display();
    int32_t disp[5]          = {d->x, d->y, d->w, d->h, d->is24};
    PSX_PAD_STATE pads[PLATFORM_PADS];
    struct pollfd pfd;
    int status = 0, fresh = 1;
    unsigned shown = 0;

    signal(SIGINT, on_host_signal);
    signal(SIGTERM, on_host_signal);
    memcpy(vram, gpu_vram(), sizeof(vram)); // the shim's last picture until the game's first
    pfd.fd     = port_remote_event_fd();
    pfd.events = POLLIN;
    for (;;)
    {
        if (waitpid(child, &status, WNOHANG) == child)
        {
            break;
        }
        if (host_signal != 0 || !platform_poll(pads))
        {
            struct timespec ts = {0, 10000000};
            int i;

            // Ask the game to stop (it finishes its files), then make sure.
            r->quit = 1;
            for (i = 0; i < 300 && waitpid(child, &status, WNOHANG) != child; i++)
            {
                nanosleep(&ts, NULL);
            }
            if (i == 300)
            {
                kill(child, SIGKILL);
                waitpid(child, &status, 0);
            }
            break;
        }
        memcpy(r->pads, pads, sizeof(pads));
        if (port_remote_take_frame(vram, disp, &overlay) || fresh)
        {
            shown += !fresh;
            present(vram, disp[0], disp[1], disp[2], disp[3], disp[4], &overlay);
            fresh = 0;
        }
        else
        {
            poll(&pfd, 1, 8);
        }
    }
    platform_shutdown();
    fprintf(stderr, "port: window host: showed %u frames of the game\n", shown);
    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }
    if (WIFSIGNALED(status))
    {
        fprintf(stderr, "port: the game ended by signal %d (%s)\n", WTERMSIG(status),
                strsignal(WTERMSIG(status)));
        return 128 + WTERMSIG(status);
    }
    return 1;
}
