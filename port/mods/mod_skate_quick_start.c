// Quick skate start: holding Circle gets Mega Man onto the Jet Skates and moving sooner.
//
// Vanilla (src/rock_neo.exe/player.c): standing (routine_1 0), the check routine
// func_8003F5D8 (D_80089FF8[0]) ends in func_80040574, which counts the frames Circle
// (PL_WORK.value134) is held in value44a and, with the skates owned (flags16b & 2) and value44b
// clear, switches to the skates (routine_1 3, value0a 0) on the ninth. The skates' routine
// func_8003D1E0 (D_80089FA4[3]) then plays a start-up: case 0 starts animation 0x38 and goes to
// case 2, which waits for the animation step whose flag byte (value_a6) is set, then case 3
// moves at 0x340 while waiting for the animation's last step (value_a7 -1), plays the start
// sound 0x8C and cruises (case 4). The animation runs in func_8003C418 after the routines, one
// tick a frame (func_8003234C). Until case 3, letting go of Circle cancels (func_8003FDA8).
//
// Measured headless (30 game frames a second; frame 1 is the first with Circle held):
//            skates start   first move   cruising (start sound)
//   vanilla  frame 9        frame 24     frame 29
//   Quick    frame 4        frame 12     frame 15
//   Instant  frame 2        frame 2      frame 2
//
// Circle is also the investigate button (value136): func_80051970 opens doors and starts talk
// on the frame Circle is pressed (value11e) while routine_1 is below 2 or 4, after the player's
// routines; talk then takes Mega Man out of routine_1 0 (0x10). So the skates never start on the
// press frame itself, and a tap near someone talks as before. Away from anything, a tap of two
// frames or more on Instant is a short dash and the usual slide to a stop.
//
// The mod hooks two functions reached through the player's tables (so every call is seen), and
// none that another mod hooks (a retail address takes one hook: port_stub_hook):
// - func_8003F5D8, the standing check: after it, if Mega Man is still standing with Circle held
//   for `hold` frames (value44a) and the game's own conditions hold, starts the skates as
//   func_80040574 would (Instant: already cruising, below).
// - func_8003C88C, the player's frame (D_80089F94[1], which runs the check and the routine):
//   before it, on the skates' start-up, Quick advances the start-up animation one extra tick
//   (twice the speed), never past the step case 2 waits for and never past the end; Instant
//   skips the start-up: the start sound and straight into cruising (case 4, which sets the
//   cruising animation and speed itself this same frame). Letting go of Circle then slides to a
//   stop as from cruising.
#include "mods.h"

#include <stddef.h>
#include <stdint.h>

#define FUNC_STAND_CHECK 0x8003F5D8u // void func_8003F5D8(PL_WORK *pl): D_80089FF8[0]
#define FUNC_PL_FRAME    0x8003C88Cu // void func_8003C88C(PL_WORK *pl): D_80089F94[1]
#define FUNC_ANIM_STEP   0x8003234Cu // void func_8003234C(PL_WORK *pl, sint32 id): one tick
#define FUNC_SOUND_CALL  0x8001A008u // Sound_call(id, a1, a2)

// PL_WORK (include/rock_neo.exe/player.h) offsets.
#define PL_ROUTINE_1 0x09
#define PL_VALUE0A   0x0A // the routine's state; value0b at +0x0B
#define PL_VALUE44   0x44 // forward speed (sint16)
#define PL_VALUE_A6  0xA6 // the animation step's flag byte
#define PL_VALUE_A7  0xA7 // the step's control byte: -1 on the held last step
#define PL_VALUE_AC  0xAC // animation wanted
#define PL_PAD_CUR   0x11C
#define PL_VALUE134  0x134 // the skate button (Circle)
#define PL_FLAGS16B  0x16B // bit 1: the skates are owned
#define PL_VALUE174  0x174
#define PL_VALUE44A  0x44A // frames Circle has been held
#define PL_VALUE44B  0x44B

#define PL_STANDING 0
#define PL_SKATING  3

typedef void (*PL_FN)(uint32_t pl);

enum
{
    START_QUICK,
    START_INSTANT
};

static const char *const starts[] = {"Quick", "Instant"};
// Frames of Circle before the skates start (vanilla 9; never 1, see above).
static const int holds[] = {4, 2};

static MOD_SETTING settings[] = {
    {"start", "Start", starts, 2, START_QUICK, START_QUICK},
};

static PL_FN orig_stand_check;
static PL_FN orig_frame;

#define PL_U8(pl, off)  (*(uint8_t *)((pl) + (off)))
#define PL_S8(pl, off)  (*(int8_t *)((pl) + (off)))
#define PL_U16(pl, off) (*(uint16_t *)((pl) + (off)))

static int is_player(uint32_t addr)
{
    return addr == MODS_PLAYER_WORK;
}

// Cases 0-3 of the skates' routine as they stand by the time cruising starts: case 4 then
// picks the cruising (or turning) animation and speed.
static void skip_start_up(uint8_t *pl)
{
    if (PL_U8(pl, PL_VALUE0A) == 0)
    {
        PL_U8(pl, PL_VALUE174) |= 4;
        PL_U8(pl, PL_VALUE44A)++;
    }
    *(int16_t *)(pl + PL_VALUE44) = 0x340;
    mods_call(FUNC_SOUND_CALL, 3, 0x8C, 0, 0, 0);
    PL_U8(pl, PL_VALUE0A) = 4;
}

static void stand_check_hook(uint32_t addr)
{
    uint8_t *pl = MODS_PTR(addr);

    orig_stand_check(addr);
    // value44a counts only while func_80040574 ran this frame with Circle held and the skates
    // owned (every other path clears it), so this is the game's own count.
    if (is_player(addr) && PL_U8(pl, PL_ROUTINE_1) == PL_STANDING &&
        (PL_U16(pl, PL_PAD_CUR) & PL_U16(pl, PL_VALUE134)) && (PL_U8(pl, PL_FLAGS16B) & 2) &&
        PL_U8(pl, PL_VALUE44B) == 0 && PL_U8(pl, PL_VALUE44A) >= holds[settings[0].value])
    {
        PL_U8(pl, PL_ROUTINE_1) = PL_SKATING;
        PL_U16(pl, PL_VALUE0A)  = 0;
        if (settings[0].value == START_INSTANT)
        {
            skip_start_up(pl);
        }
    }
}

static void frame_hook(uint32_t addr)
{
    uint8_t *pl = MODS_PTR(addr);
    int state   = PL_U8(pl, PL_VALUE0A);

    if (is_player(addr) && PL_U8(pl, PL_ROUTINE_1) == PL_SKATING && state <= 3)
    {
        if (settings[0].value == START_INSTANT)
        {
            skip_start_up(pl); // a start from a jump's landing (value0a 1), or the game's own
        }
        else if (settings[0].value == START_QUICK && state >= 1 && PL_S8(pl, PL_VALUE_A7) != -1 &&
                 (state == 3 || PL_S8(pl, PL_VALUE_A6) == 0))
        {
            // One extra tick of the playing start-up animation, before the routine looks at it.
            mods_call(FUNC_ANIM_STEP, 2, addr, PL_U8(pl, PL_VALUE_AC), 0, 0);
        }
    }
    orig_frame(addr);
}

static void enable(MOD *m, int on)
{
    (void)m;
    if (on)
    {
        orig_stand_check = (PL_FN)mods_hook(FUNC_STAND_CHECK, (void *)stand_check_hook);
        orig_frame       = (PL_FN)mods_hook(FUNC_PL_FRAME, (void *)frame_hook);
        if (orig_stand_check != NULL && orig_frame != NULL)
        {
            return;
        }
        // Both or neither; remove only what this mod installed.
        if (orig_stand_check != NULL)
        {
            mods_unhook(FUNC_STAND_CHECK);
        }
        if (orig_frame != NULL)
        {
            mods_unhook(FUNC_PL_FRAME);
        }
    }
    else if (orig_stand_check != NULL && orig_frame != NULL)
    {
        mods_unhook(FUNC_STAND_CHECK);
        mods_unhook(FUNC_PL_FRAME);
    }
    orig_stand_check = NULL;
    orig_frame       = NULL;
}

MOD mod_skate_quick_start = {
    "skate_quick_start",
    "Quick skate start",
    "Holding Circle starts the Jet Skates sooner. Quick: in half the time. Instant: at once, "
    "straight into cruising.",
    settings,
    1,
    enable,
    NULL,
    NULL,
    NULL,
    0,
};
