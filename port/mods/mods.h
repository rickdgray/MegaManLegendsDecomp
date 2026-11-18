// The mod system of the native port. Compiled into the port only; the
// matching PS1 builds never see it.
//
// A run is either vanilla or modded, settled before the game starts: the start-up menu in the
// window, `[mods] startup` in the settings, or `--vanilla` / `--mods LIST` on the command line.
// In a vanilla run nothing here acts: no hook is installed, the pads go to the game untouched,
// the text layer stays hidden. A modded run uses its own memory-card files ([cards] slot1_mods,
// slot2_mods), so it never writes the vanilla saves.
//
// A mod (one MOD record, listed in mods_list.c) changes the game through hooks on its functions:
// every native game function sits at its retail address behind a jump, and mods_hook points
// that jump at the mod's own function, which calls on to the original. No game source changes. While the game's pause menu (the
// sub-screen) is open, the mod-panel button (M, or a click of the right stick) opens the mod
// panel over it: a page per mod, with its on/off switch and its settings, or a page of its own
// (page_draw/page_input).
#ifndef PORT_MODS_H
#define PORT_MODS_H

#include "pad.h"
#include "port_overlay.h"

#include <stdint.h>

// A setting: one of a list of named values, stored in the settings file as
// `[mods] <mod id>.<key> = <value name>`.
typedef struct
{
    const char *key;   // e.g. "speed"
    const char *label; // e.g. "Speed"
    const char *const *choices;
    int count;
    int initial; // the default value's index
    int value;   // the current value's index
} MOD_SETTING;

typedef struct MOD MOD;
struct MOD
{
    const char *id;    // settings and command-line name, e.g. "fast_skates"
    const char *name;  // the menus' name, e.g. "Faster skates"
    const char *about; // one or two sentences for its page
    MOD_SETTING *settings;
    int nsettings;
    // Switches the mod on (1) or off (0) in the running game: installs or removes its hooks.
    // Called once at the start for every enabled mod, then from the panel. May be NULL.
    void (*enable)(MOD *m, int on);
    // A setting changed (the panel). May be NULL; the mod can also read setting->value live.
    void (*changed)(MOD *m, MOD_SETTING *s);
    // A page of its own (e.g. a teleport list) under the on/off line, in place of the settings
    // list; both NULL for the usual page. page_draw fills panel rows top..bottom (inclusive);
    // page_input gets pad 1's newly pressed PS1 buttons (PSX_PAD_*; repeats included for the
    // d-pad) and returns 1 when the page lets go of the cursor (Up from its first line: the
    // cursor goes back to the on/off line). Triangle always goes back to the mod list.
    void (*page_draw)(MOD *m, PORT_OVERLAY *o, int top, int bottom, int focused);
    int (*page_input)(MOD *m, uint16_t pressed);
    int enabled; // the mod is on (in a modded run)
};

// Every mod the port has (mods_list.c), NULL-terminated.
extern MOD *const mods_list[];

// --- start-up (host_main.c) -------------------------------------------------------------------

// Settles vanilla or mods. `cli`: NULL (no option), "vanilla" (--vanilla) or --mods' LIST (mod
// ids separated by commas, `all`, `none`, or `default` for [mods] enabled). Without an option a
// headless run is vanilla; otherwise [mods] startup decides (ask / vanilla / mods). Returns 1
// when the start-up menu should ask, 0 when settled. Reports unknown mod ids; -1 on a bad LIST.
int mods_configure(const char *cli, int headless);
// The start-up menu in the window (SDL builds; vanilla preselected). Settles the choice.
void mods_startup_menu(void);
// A modded run's memory cards ([cards] slot1_mods / slot2_mods), unless --card1 / --card2 named
// a card. Call after port_config_apply_cards.
void mods_apply_cards(int card1_given, int card2_given);
// The arguments for the game program after the boot shim (LoadExec): `argv` without any
// --mods/--vanilla, plus the settled choice, so the game neither asks again nor differs.
char **mods_child_argv(char **argv);
// The game program, after the stub table is installed: switches the enabled mods on and lets
// the pause panel work. Nothing in a vanilla run.
void mods_start(void);
// 1 in a modded run.
int mods_active(void);

// --- the running game (port_game.c) -----------------------------------------------------------

// Every vertical blank, on the pads about to go to the game: notes pad 1 for the panel, and
// while the panel is open (and until the buttons that closed it are let go) keeps them from the
// game. Nothing in a vanilla run.
void mods_pad_filter(PSX_PAD_STATE pads[2]);
// Every drawn frame: the panel's menu and its text layer. Nothing in a vanilla run.
void mods_frame(void);

// --- for mods ---------------------------------------------------------------------------------

// Points the game function at retail address `addr` at `fn` and returns the original for fn to
// call, or NULL (logged) when it cannot. Hooks and originals take and return PS1 words: every
// argument a uint32_t (game pointers as PS1 addresses; MODS_PTR reads them), as many as the
// game function has. The same mod code then runs in the 32-bit port (a jump at the retail
// address) and the 64-bit one (a compiled hook point; port/aot/mods_host.c).
void *mods_hook(uint32_t addr, void *fn);
void mods_unhook(uint32_t addr);
// Closes the pause panel (a page that hands control back to the game, e.g. a teleport). The
// buttons still held reach the game only after they are let go.
void mods_panel_close(void);
// Stores a setting's current value in the settings file (the panel does this on a change).
void mods_save_setting(MOD *m, MOD_SETTING *s);

// The game's state the panel and mods read (PS1 addresses).
#define MODS_GAME_WORK 0x800C1B10u // Game_work: routine_0 +0, routine_1 +1, stage +0x50, room +0x51
#define MODS_PLAYER_WORK 0x800B51B0u // Player_work (PL_WORK, include/rock_neo.exe/player.h)
// PS1 memory: a host pointer to PS1 address `a`, and reads and writes through it.
#ifdef PORT_AOT_MIPS
uint8_t *mods_ptr(uint32_t addr); // the 64-bit port's guest memory
#define MODS_PTR(a) mods_ptr((uint32_t)(a))
#else
#define MODS_PTR(a) ((uint8_t *)(uintptr_t)(a)) // PS1 memory at its own addresses
#endif
#define MODS_PEEK8(a)     (*(volatile uint8_t *)MODS_PTR(a))
#define MODS_PEEK16(a)    (*(volatile int16_t *)MODS_PTR(a))
#define MODS_POKE8(a, v)  (*(volatile uint8_t *)MODS_PTR(a) = (uint8_t)(v))
#define MODS_POKE16(a, v) (*(volatile int16_t *)MODS_PTR(a) = (int16_t)(v))
#define MODS_POKE32(a, v) (*(volatile uint32_t *)MODS_PTR(a) = (uint32_t)(v))
// Calls the game function at retail address `addr` with `n` (0-4) word arguments.
uint32_t mods_call(uint32_t addr, int n, uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3);

#endif
