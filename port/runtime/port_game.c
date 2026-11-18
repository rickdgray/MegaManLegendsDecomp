// Host side of the running game. See port_game.h.
#define _GNU_SOURCE
#include "port_game.h"

#include "gpu.h"
#include "mods.h"
#include "overlay_native.h"
#include "port_audio.h"
#include "port_remote.h"
#include "port_script.h"
#include "psx_mem.h"
#ifdef PORT_HAVE_SDL
#include "platform_sdl.h"
#endif

#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <ucontext.h>
#include <unistd.h>

#pragma weak port_cd_tick

PORT_OPTIONS port_options = {1, 0, 0, 60, 0, NULL, 0, NULL, NULL, NULL, NULL, 0, 0, NULL};

static volatile uint32_t vblanks;
static void (*vblank_handler)(void);
static volatile int stopping;
static uint32_t frames;
static int display_on;

static uint8_t *pad_buf[2];
static int pad_len[2];
static volatile int pad_started;
static PSX_PAD_STATE pads[2];

// --- logging --------------------------------------------------------------------------------

void port_log(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fputs("port: ", stderr);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
    va_end(ap);
}

#define LOG_KEYS 256

void port_log_limited(const char *key, int limit, const char *fmt, ...)
{
    static const char *keys[LOG_KEYS];
    static int counts[LOG_KEYS];
    static int used;
    va_list ap;
    int i;

    for (i = 0; i < used && keys[i] != key; i++)
    {
    }
    if (i == used)
    {
        if (used == LOG_KEYS)
        {
            return;
        }
        keys[used++] = key;
    }
    if (counts[i]++ >= limit && !port_options.verbose)
    {
        if (counts[i] == limit + 1)
        {
            fprintf(stderr, "port: (%s: further messages suppressed)\n", key);
        }
        return;
    }
    va_start(ap, fmt);
    fputs("port: ", stderr);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
    va_end(ap);
}

int port_window_open(const char *title, int scale)
{
    int r = port_remote_attach();

    if (r != 0)
    {
        return r > 0 ? 0 : -1; // the boot shim's window shows this program's frames
    }
#ifdef PORT_HAVE_SDL
    if (platform_init(title, scale) != 0)
    {
        return -1;
    }
    platform_set_full_vram(0); // the game's picture; Tab shows all of VRAM
    return 0;
#else
    (void)title;
    (void)scale;
    return -1;
#endif
}

// --- vertical blank -------------------------------------------------------------------------

static pid_t game_tid; // the OS thread the game runs on (its threads are coroutines in it)

// The interrupt-time work of one vertical blank. Runs with SIGALRM blocked (in the signal
// handler, or from deliver_vblank).
static void vblank_interrupt(void)
{
    vblanks++;
    if (port_options.max_vblanks != 0 && vblanks >= (uint32_t)port_options.max_vblanks)
    {
        // The game may be spinning in a loop that never reaches the runtime: stop from here.
        port_stop(0, "vblank limit reached");
    }
    if (pad_started)
    {
        port_pad_update();
    }
    if (port_cd_tick != NULL)
    {
        port_cd_tick(); // the CD drive's interrupts (absent from programs without libcd)
    }
    if (vblank_handler != NULL)
    {
        vblank_handler();
    }
    port_audio_tick(); // the SPU, after the interrupt work that feeds it
}

// --- the game-paced clock --------------------------------------------------------------------
// The game only ever waits for a vertical blank in a few places: the main loop's spin on
// Vsync_count (VSYNC_IDLE), VSync(0/n), CdSync(0), the movie player's counted polls
// (port_spin_pause). With port_options.deterministic each of those delivers the blank itself,
// synchronously, so the interrupt work happens at the same point of the game's execution in
// every run: the console with an infinitely fast CPU. The CD drive and the SPU advance per blank
// (port_cd_tick, port_audio_tick), so they follow the same clock. Nothing reads the wall clock.
//
// The interval timer stays as a watchdog: if the game goes WATCHDOG_TICKS seconds without
// reaching a wait point, it reports where it is and delivers a blank (which breaks
// reproducibility: a wait point is missing).

#define WATCHDOG_TICKS 5

static volatile int vblank_on; // between port_vblank_start and port_vblank_stop
static uint32_t watchdog_seen;
static int watchdog_idle;

static int deliver_vblank(void)
{
    sigset_t set, old;

    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old);
    if (sigismember(&old, SIGALRM) || !vblank_on)
    {
        // Interrupts are off (a critical section, or the callbacks stopped): none can arrive.
        sigprocmask(SIG_SETMASK, &old, NULL);
        return 0;
    }
    vblank_interrupt();
    sigprocmask(SIG_SETMASK, &old, NULL);
    return 1;
}

static void watchdog(void *uc)
{
    if (vblanks != watchdog_seen)
    {
        watchdog_seen = vblanks;
        watchdog_idle = 0;
        return;
    }
    if (++watchdog_idle < WATCHDOG_TICKS)
    {
        return;
    }
    watchdog_idle = 0;
    {
        unsigned long pc = 0;
#if defined(__i386__)
        pc = (unsigned long)((ucontext_t *)uc)->uc_mcontext.gregs[REG_EIP];
#elif defined(__x86_64__)
        pc = (unsigned long)((ucontext_t *)uc)->uc_mcontext.gregs[REG_RIP];
#endif
        port_log_limited("watchdog", 5,
                         "game-paced clock: no wait for a vertical blank in %d s (at blank %u, "
                         "pc 0x%lx); delivering one, so this run is not reproducible",
                         WATCHDOG_TICKS, vblanks, pc);
    }
    watchdog_seen = vblanks + 1;
    vblank_interrupt();
}

static void on_alarm(int sig, siginfo_t *si, void *uc)
{
    (void)si;
    // The timer signal goes to the process, and any thread may take it; SDL starts threads of
    // its own. The vertical blank must interrupt the game's thread, so pass it on.
    if (game_tid != 0 && (pid_t)syscall(SYS_gettid) != game_tid)
    {
        syscall(SYS_tgkill, getpid(), game_tid, sig);
        return;
    }
    if (port_options.deterministic)
    {
        watchdog(uc);
        return;
    }
    vblank_interrupt();
}

void port_vblank_start(void (*handler)(void))
{
    struct sigaction sa;
    struct itimerval it;
    long usec = 1000000L / (port_options.vblank_hz > 0 ? port_options.vblank_hz : 60);

    if (port_options.deterministic)
    {
        usec = 1000000L; // the watchdog's second
    }
    vblank_handler = handler;
    vblank_on      = 1;
    game_tid       = (pid_t)syscall(SYS_gettid);
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = on_alarm;
    sa.sa_flags     = SA_RESTART | SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);
    memset(&it, 0, sizeof(it));
    it.it_interval.tv_sec  = usec / 1000000L;
    it.it_interval.tv_usec = usec % 1000000L;
    it.it_value            = it.it_interval;
    setitimer(ITIMER_REAL, &it, NULL);
}

void port_vblank_stop(void)
{
    struct itimerval it;

    memset(&it, 0, sizeof(it));
    setitimer(ITIMER_REAL, &it, NULL);
    vblank_handler = NULL;
    vblank_on      = 0;
}

uint32_t port_vblank_count(void)
{
    return vblanks;
}

int port_irq_block(void)
{
    sigset_t set, old;

    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old);
    return sigismember(&old, SIGALRM);
}

void port_irq_restore(int blocked)
{
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(blocked ? SIG_BLOCK : SIG_UNBLOCK, &set, NULL);
}

// The console's polls per vertical blank in the movie player's CD wait (0x3FFFFF polls are
// about two seconds there).
#define SPIN_POLLS_PER_VBLANK 35000

// See port_prelude.h: one poll of a loop that counts iterations as time.
void port_spin_pause(void)
{
    struct timespec a, b;
    static uint32_t polls;

    if (port_options.deterministic)
    {
        if (++polls >= SPIN_POLLS_PER_VBLANK)
        {
            polls = 0;
            deliver_vblank();
        }
        return;
    }
    clock_gettime(CLOCK_MONOTONIC, &a);
    do
    {
        clock_gettime(CLOCK_MONOTONIC, &b);
    } while ((b.tv_sec - a.tv_sec) * 1000000000L + (b.tv_nsec - a.tv_nsec) < 500);
}

void port_vblank_poll(void)
{
    struct timespec ts = {0, 200000};

    if (port_options.deterministic)
    {
        if (!deliver_vblank())
        {
            nanosleep(&ts, NULL); // nothing can arrive but the watchdog's blank
        }
        return;
    }
    nanosleep(&ts, NULL);
}

void port_vblank_idle(void)
{
    if (port_options.deterministic)
    {
        deliver_vblank();
    }
}

void port_vblank_wait(uint32_t count)
{
    port_audio_flush();
    while ((int32_t)(vblanks - count) <= 0)
    {
        port_vblank_poll();
    }
}

// --- pads -----------------------------------------------------------------------------------

void port_pad_init(uint8_t *buf0, int len0, uint8_t *buf1, int len1)
{
    pad_buf[0] = buf0;
    pad_len[0] = len0;
    pad_buf[1] = buf1;
    pad_len[1] = len1;
    psx_pad_reset(&pads[0]);
    psx_pad_reset(&pads[1]);
    pads[1].connected = 0;
}

void port_pad_start(int on)
{
    pad_started = on;
}

// Scripted input (--input): the buttons pad 1 holds at vertical blank `v` (PS1 bits, and
// PORT_SCRIPT_MODS for the port's mod-panel button).
static uint32_t script_buttons(uint32_t v)
{
    const char *p = port_options.input;
    uint32_t held = 0;

    while (p != NULL && *p != 0)
    {
        char *e;
        unsigned long at = strtoul(p, &e, 0), mask = 0, len = 6;

        if (*e == ':')
        {
            mask = strtoul(e + 1, &e, 0);
            if (*e == ':')
            {
                len = strtoul(e + 1, &e, 0);
            }
        }
        if (v >= at && v < at + len)
        {
            held |= (uint32_t)mask;
        }
        p = strchr(e, ',');
        if (p != NULL)
        {
            p++;
        }
    }
    return held;
}

// --poke: byte writes to PS1 memory at given vertical blanks (testing: e.g. Game_work's save
// request flag), each applied once.
static void apply_pokes(uint32_t v)
{
    const char *p = port_options.poke;

    while (p != NULL && *p != 0)
    {
        char *e;
        unsigned long at = strtoul(p, &e, 0), addr = 0, val = 0;

        if (*e == ':')
        {
            addr = strtoul(e + 1, &e, 0);
            if (*e == '=')
            {
                val = strtoul(e + 1, &e, 0);
            }
        }
        if (v == at && addr >= 0x80000000ul && addr < 0x80200000ul)
        {
            *(volatile uint8_t *)(uintptr_t)addr = (uint8_t)val;
        }
        p = strchr(e, ',');
        if (p != NULL)
        {
            p++;
        }
    }
}

// Adds scripted buttons (PS1 bits and the port's PORT_SCRIPT_MODS) to pad 1.
static void add_script_buttons(uint32_t b)
{
    pads[0].buttons |= (uint16_t)b;
    if (b & PORT_SCRIPT_MODS)
    {
        pads[0].host |= PORT_HOST_MODS;
    }
}

void port_pad_update(void)
{
    PSX_PAD_STATE out[2];
    int i;

    apply_pokes(vblanks);

    if (port_options.headless)
    {
        pads[0].buttons = port_options.buttons;
        pads[0].host    = 0;
        add_script_buttons(script_buttons(vblanks));
        if (port_script_active())
        {
            add_script_buttons(port_script_buttons(vblanks));
        }
    }
    else if (port_remote() != NULL)
    {
        port_remote_poll(pads); // the window host's pads, fresh at every blank
        if (port_options.input != NULL)
        {
            add_script_buttons(script_buttons(vblanks));
        }
    }
    else if (port_options.input != NULL)
    {
        add_script_buttons(script_buttons(vblanks));
    }
    // The mod panel (port/mods/) takes pad 1 while it is open; nothing in vanilla play. A copy:
    // in a window `pads` holds the host's input until the next poll.
    memcpy(out, pads, sizeof(out));
    mods_pad_filter(out);
    for (i = 0; i < 2; i++)
    {
        if (pad_buf[i] != NULL && pad_len[i] >= 2)
        {
            psx_pad_to_buffer(&out[i], pad_buf[i], pad_len[i]);
        }
    }
}

// --- frames ---------------------------------------------------------------------------------

int port_dump_vram(const char *path)
{
    FILE *f           = fopen(path, "wb");
    const uint16_t *v = gpu_vram();
    static uint8_t row[GPU_VRAM_W * 3];
    int x, y;

    if (f == NULL)
    {
        perror(path);
        return -1;
    }
    fprintf(f, "P6\n%d %d\n255\n", GPU_VRAM_W, GPU_VRAM_H);
    for (y = 0; y < GPU_VRAM_H; y++)
    {
        for (x = 0; x < GPU_VRAM_W; x++)
        {
            uint16_t p     = v[y * GPU_VRAM_W + x];
            row[x * 3]     = (uint8_t)((p & 0x1F) << 3);
            row[x * 3 + 1] = (uint8_t)(((p >> 5) & 0x1F) << 3);
            row[x * 3 + 2] = (uint8_t)(((p >> 10) & 0x1F) << 3);
        }
        fwrite(row, 1, sizeof(row), f);
    }
    fclose(f);
    return 0;
}

static int keep_window __attribute__((unused)); // LoadExec hands the window to the next program

// Everything a stop does before the process ends: timer off, report, sound file, dump, window.
static void finish(const char *why)
{
    const GPU_DISPLAY *d = gpu_display();
    const GPU_STATS *s   = gpu_stats();

    stopping = 1;
    port_vblank_stop();
    fprintf(stderr,
            "port: stopping (%s) after %u frames, %u vblanks; display %dx%d at (%d,%d)%s; GPU: "
            "%u commands, %u polygons, %u rects, %u lines, %u fills, %u unknown\n",
            why, frames, vblanks, d->w, d->h, d->x, d->y, display_on ? "" : " (masked)",
            s->commands, s->polygons, s->rects, s->lines, s->fills, s->unknown);
    port_overlay_print_stats();
    port_audio_close();
    if (port_options.dump != NULL && port_dump_vram(port_options.dump) == 0)
    {
        fprintf(stderr, "port: wrote VRAM to %s\n", port_options.dump);
    }
#ifdef PORT_HAVE_SDL
    if (!port_options.headless && port_remote() == NULL && !keep_window)
    {
        platform_shutdown();
    }
#endif
    fflush(NULL);
}

void port_stop(int code, const char *why)
{
    if (stopping)
    {
        _exit(code);
    }
    finish(why);
    _exit(code);
}

void port_exec(const char *path, char *const argv[])
{
    if (stopping)
    {
        _exit(1);
    }
#ifdef PORT_HAVE_SDL
    if (!port_options.headless && port_remote() == NULL)
    {
        // One window across LoadExec (port_remote.h): this process keeps the window and the
        // audio device and becomes the host; the next program runs as its child and draws
        // into the shared block.
        pid_t parent = getpid(), child;

        keep_window = 1;
        finish("LoadExec");
        if (port_remote_create() != 0)
        {
            _exit(1);
        }
        {
            PORT_REMOTE *r = port_remote();

            platform_audio_lock(1);
            port_audio_use_shared(&r->audio_head, &r->audio_tail, r->audio,
                                  PORT_REMOTE_AUDIO_SIZE, 0);
            platform_audio_lock(0);
        }
        port_irq_restore(0);
        child = fork();
        if (child < 0)
        {
            perror("fork");
            _exit(1);
        }
        if (child == 0)
        {
            prctl(PR_SET_PDEATHSIG, SIGTERM); // the window closing ends the game too
            if (getppid() != parent)
            {
                _exit(1);
            }
            execv(path, argv);
            perror(path);
            _exit(1);
        }
        _exit(platform_host_run(child));
    }
#endif
    finish("LoadExec");
    port_irq_restore(0); // the new program starts with the timer signal unblocked
    execv(path, argv);
    perror(path);
    _exit(1);
}

void port_display_enable(int on)
{
    display_on = on;
}

// --dump-at: VRAM dumps at the listed vertical blanks, taken at the first frame end after each.
static const char *dump_next;
static int dump_started;

static void dump_scheduled(void)
{
    char path[1024];
    unsigned long at;
    char *e;

    if (port_options.dump_at == NULL || port_options.dump == NULL)
    {
        return;
    }
    if (!dump_started)
    {
        dump_next    = port_options.dump_at;
        dump_started = 1;
    }
    if (dump_next == NULL || *dump_next == 0)
    {
        return;
    }
    at = strtoul(dump_next, &e, 0);
    if (vblanks < at)
    {
        return;
    }
    snprintf(path, sizeof(path), "%.*s-%lu.ppm",
             (int)(strlen(port_options.dump) > 4 &&
                           strcmp(port_options.dump + strlen(port_options.dump) - 4, ".ppm") == 0
                       ? strlen(port_options.dump) - 4
                       : strlen(port_options.dump)),
             port_options.dump, at);
    if (port_dump_vram(path) == 0)
    {
        port_log("vblank %u, frame %u: wrote VRAM to %s", vblanks, frames, path);
    }
    dump_next = *e == ',' ? e + 1 : NULL;
}

// --watch: PS1 memory as hex, at the first frame end of every 60 blanks (writing input scripts:
// e.g. Player_work's position and rotation).
static void watch_memory(void)
{
    static uint32_t last;
    const char *p = port_options.watch;

    if (p == NULL || vblanks / 60 == last / 60)
    {
        return;
    }
    last = vblanks;
    fprintf(stderr, "port: watch v%u:", vblanks);
    while (*p != 0)
    {
        char *e;
        unsigned long addr = strtoul(p, &e, 0), len = 4, i;

        if (*e == ':')
        {
            len = strtoul(e + 1, &e, 0);
        }
        if (addr >= 0x80000000ul && addr + len <= 0x80200000ul)
        {
            fputc(' ', stderr);
            for (i = 0; i < len; i++)
            {
                fprintf(stderr, "%02X", *(const uint8_t *)(uintptr_t)(addr + i));
            }
        }
        if (*e != ',')
        {
            break;
        }
        p = e + 1;
    }
    fputc('\n', stderr);
}

void port_frame_drawn(void)
{
    frames++;
    watch_memory();
    port_audio_flush();
    dump_scheduled();
    mods_frame(); // the mod panel's menu and its text layer (port/mods/); nothing in vanilla
    if (port_options.verbose)
    {
        const GPU_STATS *s = gpu_stats();
        port_log("frame %u: %u commands, %u polygons, %u rects, %u fills", frames, s->commands,
                 s->polygons, s->rects, s->fills);
    }
    if (!port_options.headless && port_remote() != NULL)
    {
        port_remote_present();
        if (!port_remote_poll(pads))
        {
            port_stop(0, "window closed");
        }
    }
#ifdef PORT_HAVE_SDL
    else if (!port_options.headless)
    {
        if (!platform_poll(pads))
        {
            port_stop(0, "window closed");
        }
        platform_present();
    }
#endif
    if (port_options.max_frames != 0 && frames >= (uint32_t)port_options.max_frames)
    {
        port_stop(0, "frame limit reached");
    }
    gpu_reset_stats();
}

// --- the fork server (writing scripts) ------------------------------------------------------
// A long script is written a piece at a time. Instead of replaying the whole run for every try,
// the `serve` command keeps the run at that point: it waits for a request file DIR/req, renames
// it DIR/req.N, saves PS1 RAM (the game's data and the overlays all live there, in a memory
// object shared across fork), and forks. The child takes the request's settings, logs to
// DIR/log.N and continues the game; the parent waits for it, puts RAM back, writes DIR/done.N
// (the exit status) and takes the next request. Request lines: `script FILE` (run in place of
// the rest of the current script), `vblanks N` (stop N blanks later), `dump PATH`, `dump-at
// LIST` (absolute blanks), `quit`.
void port_fork_serve(void)
{
    const char *dir = port_options.serve_dir;
    static uint8_t *saved;
    static char script[1024], dump[1024], dump_at[4096];
    int n;

    if (dir == NULL)
    {
        port_log("script: serve without --serve DIR: continuing");
        return;
    }
    if (saved == NULL)
    {
        saved = malloc(PSX_RAM_WINDOW);
    }
    port_log("serve: at blank %u, waiting for requests in %s", vblanks, dir);
    for (n = 0;; n++)
    {
        char path[1200], taken[1200], line[4200];
        unsigned long count = 0;
        int quit = 0, status = 0;
        FILE *f;
        pid_t pid;

        snprintf(path, sizeof(path), "%s/req", dir);
        snprintf(taken, sizeof(taken), "%s/req.%d", dir, n);
        while (rename(path, taken) != 0)
        {
            struct timespec ts = {0, 50000000};

            nanosleep(&ts, NULL);
        }
        script[0] = dump[0] = dump_at[0] = 0;
        f = fopen(taken, "r");
        while (f != NULL && fgets(line, sizeof(line), f) != NULL)
        {
            char *v = strchr(line, ' ');

            line[strcspn(line, "\r\n")] = 0;
            if (strcmp(line, "quit") == 0)
            {
                quit = 1;
            }
            if (v == NULL)
            {
                continue;
            }
            *v++ = 0;
            if (strcmp(line, "script") == 0)
            {
                snprintf(script, sizeof(script), "%s", v);
            }
            else if (strcmp(line, "vblanks") == 0)
            {
                count = strtoul(v, NULL, 0);
            }
            else if (strcmp(line, "dump") == 0)
            {
                snprintf(dump, sizeof(dump), "%s", v);
            }
            else if (strcmp(line, "dump-at") == 0)
            {
                snprintf(dump_at, sizeof(dump_at), "%s", v);
            }
        }
        if (f != NULL)
        {
            fclose(f);
        }
        if (quit)
        {
            port_stop(0, "serve: quit");
        }
        memcpy(saved, (void *)(uintptr_t)PSX_RAM_BASE, PSX_RAM_WINDOW);
        fflush(NULL);
        pid = fork();
        if (pid == 0)
        {
            struct itimerval it;
            int fd;

            snprintf(path, sizeof(path), "%s/log.%d", dir, n);
            fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd >= 0)
            {
                dup2(fd, 2);
                close(fd);
            }
            port_options.max_vblanks = count != 0 ? (int)(vblanks + count) : 0;
            port_options.dump        = dump[0] ? dump : NULL;
            port_options.dump_at     = dump_at[0] ? dump_at : NULL;
            port_options.serve_dir   = NULL;
            dump_started             = 0;
            if (script[0] != 0 && port_script_replace(script) != 0)
            {
                _exit(2);
            }
            memset(&it, 0, sizeof(it)); // interval timers are not inherited: the watchdog again
            it.it_interval.tv_sec = 1;
            it.it_value           = it.it_interval;
            setitimer(ITIMER_REAL, &it, NULL);
            port_log("serve: request %d at blank %u", n, vblanks);
            return;
        }
        if (pid > 0)
        {
            waitpid(pid, &status, 0);
        }
        memcpy((void *)(uintptr_t)PSX_RAM_BASE, saved, PSX_RAM_WINDOW);
        snprintf(path, sizeof(path), "%s/done.%d", dir, n);
        f = fopen(path, "w");
        if (f != NULL)
        {
            fprintf(f, "%d\n", WIFEXITED(status) ? WEXITSTATUS(status) : 128 + WTERMSIG(status));
            fclose(f);
        }
    }
}
