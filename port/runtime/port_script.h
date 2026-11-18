// Input scripts (--script FILE): pad 1's buttons, blank by blank, with waits on PS1 memory and
// checkpoints. With the game-paced clock (port_game.h) a script replays exactly, so it serves as
// a regression test (port/tests/smoke.script, `make port-smoke`). The language is described at
// the top of port_script.c.
#ifndef PORT_SCRIPT_H
#define PORT_SCRIPT_H

#include <stdint.h>

// Reads and checks the script. Returns 0, or -1 after reporting the error.
int port_script_load(const char *path);
// Replaces the script with another, run from its first command (keeping the `let` names).
int port_script_replace(const char *path);
// 1 when a script is loaded.
int port_script_active(void);
// The buttons the script holds at vertical blank `v` (called once per blank, in order). Runs
// the checkpoints that fall at this blank; a failed one stops the program with exit status 1,
// the end of the script with 0.
uint32_t port_script_buttons(uint32_t v);
// The bit of port_script_buttons for the port's mod-panel button (PSX_PAD_STATE.host's
// PORT_HOST_MODS): the script button name `mods`.
#define PORT_SCRIPT_MODS 0x10000u

#endif
