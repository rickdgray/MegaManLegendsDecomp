// The host side of a running game (port/runtime/port_game.c): the vertical-blank interrupt,
// frame presentation, headless VRAM dumps, pads, and logging. The native PsyQ libraries
// (port/psyq/) sit on top of it.
//
// Interrupts: the PS1's vertical blank arrives 60 times a second and runs the game's callbacks
// in the middle of whatever code is executing. In real time (windowed play) the port does the
// same with a POSIX interval timer (SIGALRM): the handler runs the VSync callback and the other
// interrupt-time work on the current stack. EnterCriticalSection/ExitCriticalSection block and
// unblock the signal. With the game-paced clock (headless default) the blank is delivered at the
// points where the game waits for one (port_vblank_idle/_wait/_poll, port_spin_pause), and the
// timer is only a watchdog.
#ifndef PORT_GAME_H
#define PORT_GAME_H

#include "pad.h"

#include <stdint.h>

typedef struct
{
    int headless;     // no window: render into VRAM only
    int max_frames;   // stop after this many drawn frames (0 = never)
    int max_vblanks;  // stop after this many vertical blanks (0 = never)
    int vblank_hz;    // interrupt rate (60 as on hardware; faster for headless tests)
    int stop_on_cd;   // stop at the first CD read
    const char *dump; // write VRAM here as a PPM when stopping
    uint16_t buttons; // headless: buttons held on pad 1
    const char *input;   // scripted presses: "VBLANK:MASK[:LEN],..." (pad 1, LEN blanks, default 6)
    const char *dump_at; // also dump VRAM at these vblank counts: "V1,V2,..." to DUMP-V.ppm
    const char *poke;    // debugging: "VBLANK:ADDR=BYTE,..." writes a byte of PS1 memory then
    const char *watch;   // debugging: "ADDR:LEN,..." logs those bytes once per 60 blanks
    int verbose;
    // Game-paced clock (the default headless): vertical blanks happen when the game waits for
    // one, not on a real-time timer, so the same input gives the same run. 0 = real time.
    int deterministic;
    const char *serve_dir; // writing scripts: where the `serve` script command takes requests
} PORT_OPTIONS;

extern PORT_OPTIONS port_options;

// printf-style message to stderr, prefixed "port: ".
void port_log(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
// Logs the message only the first `limit` times this call site's key is seen.
void port_log_limited(const char *key, int limit, const char *fmt, ...)
    __attribute__((format(printf, 3, 4)));

// Opens the game window (SDL builds). Returns 0, or -1 when the build has no window support.
int port_window_open(const char *title, int scale);

// Starts and stops the vertical-blank timer; the handler calls `handler` once per blank.
void port_vblank_start(void (*handler)(void));
void port_vblank_stop(void);
void port_reset_clock(void);
uint32_t port_vblank_count(void);
// Blocks or unblocks the interrupt (critical sections). Returns the previous state (1 = blocked).
int port_irq_block(void);
void port_irq_restore(int blocked);
// Waits until the vblank counter moves past `count`.
void port_vblank_wait(uint32_t count);
// One pass of a loop waiting for something interrupt-driven (CdSync(0), the main loop's
// VSYNC_IDLE): with the game-paced clock it delivers a vertical blank, in real time it sleeps
// briefly (port_vblank_poll) or does nothing (port_vblank_idle).
void port_vblank_poll(void);
void port_vblank_idle(void);
void port_spin_pause(void);

// Called once per DrawOTag: presents the frame, polls input, stops when the options say so.
void port_frame_drawn(void);
void port_display_enable(int on);
// The `serve` script command (writing scripts; port_game.c): keeps this point of the run and
// forks a continuation per request in port_options.serve_dir. Returns in each child.
void port_fork_serve(void);
// Writes all of VRAM as a PPM. Returns 0, or -1 after reporting the error.
int port_dump_vram(const char *path);

// Pad receive buffers (InitPAD); filled at every vertical blank while started.
void port_pad_init(uint8_t *buf0, int len0, uint8_t *buf1, int len1);
void port_pad_start(int on);
void port_pad_update(void);

// The CD drive on the disc image (port/psyq/libcd.c). port_cd_open takes a .cue file or a
// directory holding one; port_cd_tick runs the drive's interrupts at every vertical blank.
int port_cd_open(const char *path);
int port_cd_present(void);
void port_cd_tick(void);
uint32_t port_cd_sectors_read(void);
extern int port_cd_speed;

// Stops the game: dumps VRAM if asked, prints `why`, exits with `code`.
void port_stop(int code, const char *why) __attribute__((noreturn));
// Ends this program like port_stop and runs another in its place (the boot shim's LoadExec).
void port_exec(const char *path, char *const argv[]) __attribute__((noreturn));

#endif
