#ifndef CMD_H
#define CMD_H

// The command queue: requests (e.g. "play this movie") run one at a time by Cmd_exec, one step
// per frame, each by its handler in cmd_tbl.

#include "common.h"

#define CMD_QUEUE_LEN 16
#define CMD_END 0
#define CMD_PLAY_MOVIE 5

// Arguments are copied as one 12-byte block; possibly a union per command type. Only the
// play-movie command (type 5) is seen in the shim: (movie index, last frame, skip buttons).
typedef struct
{
    sint32 arg1; // movie index into Movie_tbl
    sint32 arg2; // frame number at which playback ends
    uint16 arg3; // pad buttons (matched against Joy1's "on" bits) that skip the movie
} CMD_ARGS;

typedef struct
{
    sint32 type; // CMD_END = end of queue, CMD_PLAY_MOVIE = play movie
    CMD_ARGS args;
} CMD;

typedef void (*CMD_FUNC)(void);

extern CMD Cmd_queue[CMD_QUEUE_LEN];
extern CMD *Cmd_write_ptr; // next free slot
extern CMD *Cmd_exec_ptr;  // the command being run
extern CMD_FUNC cmd_tbl[6];

// The running command's state (cmd_play_movie's switch index); cleared on dequeue.
extern sint32 Cmd_routine;

// Unknown
extern sint32 D_80059C24; // cleared with Cmd_routine, not otherwise referenced in the shim

void Cmd_set_movie(sint32 arg1, sint32 arg2, uint16 arg3);
void Cmd_exec(void);
void Cmd_dequeue(void);
sint32 Cmd_busy_check(void);

#endif // CMD_H
