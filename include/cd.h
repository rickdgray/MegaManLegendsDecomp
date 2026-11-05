#ifndef CD_H
#define CD_H

// The CD drive: init, control wrappers, callbacks, and CD audio settings.

#include "common.h"

#define CD_FILE_COUNT 248

// Cd_error_flags bits
#define CD_ERR_READY   0x04 // error reported to the ready callback
#define CD_ERR_SYNC    0x08 // error reported to the sync callback
#define CD_ERR_TIMEOUT 0x10 // timed out
#define CD_VOL_MAX     0x7F

// CD command queue
#define CD_CMD_QUEUE_LEN  16
#define CD_CMD_END        0
#define CD_CMD_PLAY_MOVIE 5

typedef struct
{
    sint32 sector;
    sint32 size;
    sint32 unk8;
} CD_FILE;

// Arguments are copied as one 12-byte block; possibly a union per command type. Only the
// play-movie command (type 5) is seen in the shim: (movie index, last frame, skip buttons).
typedef struct
{
    sint32 arg1; // movie index into Cd_file_tbl
    sint32 arg2; // frame number at which playback ends
    uint16 arg3; // pad buttons (matched against Joy1's "on" bits) that skip the movie
} CD_CMD_ARGS;

typedef struct
{
    sint32 type; // CD_CMD_END = end of queue, CD_CMD_PLAY_MOVIE = play movie
    CD_CMD_ARGS args;
} CD_CMD;

typedef void (*CD_CMD_FUNC)(void);

// every file on the disc: sector, size, unknown
extern CD_FILE Cd_file_tbl[CD_FILE_COUNT];

// CD command queue
extern CD_CMD Cd_cmd_queue[CD_CMD_QUEUE_LEN];
extern CD_CMD *Cd_cmd_write_ptr; // next free slot
extern CD_CMD *Cd_cmd_exec_ptr;  // the command being run
extern CD_CMD_FUNC cd_cmd_tbl[6];

extern uint8 Cd_mode;
extern u_char Cd_result[8];
extern uint8 Cd_error_flags; // CD_ERR_* bits
extern sint32 Cd_wait;
extern sint32 Cd_movie_playing;

// The running command's state (cd_cmd_play_movie's switch index); cleared on dequeue.
extern sint32 Cd_cmd_routine;

extern uint8 Cd_status; // set up by Cd_init
extern uint8 Cd_sync_done;

void Cd_init(void);
void Cd_control_retry(u_char com, u_char *param, u_char *result);
void Cd_controlb_retry(u_char com, u_char *param, u_char *result);
void Cd_set_mode(u_char mode);
void Cd_set_volume(uint8 vol);
void Cd_stop(void);
void Cd_sync_cb(u_char status, u_char *result);

void Cd_cmd_set_movie(sint32 arg1, sint32 arg2, uint16 arg3);
void Cd_cmd_exec(void);
void Cd_cmd_dequeue(void);
sint32 Cd_read_sync2(void);

#include "cd_local.h" // per-target CD variables with no name yet

#endif // CD_H
