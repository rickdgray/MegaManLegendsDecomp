#ifndef CD_H
#define CD_H

// The CD drive: init, control wrappers, callbacks, and CD audio settings.

#include "common.h"

// Cd_status
#define CD_STATUS_IDLE  0x00
#define CD_STATUS_BUSY  0x01 // a read is in progress
#define CD_STATUS_ERROR 0x80

// Cd_error_flags (Capcom's; set by the callbacks and command handlers, cleared when a command starts)
#define CD_ERR_RING_FULL    0x01 // a sector arrived with no free ring slot (Cd_ready_cb_ring)
#define CD_ERR_CMD_TIMEOUT  0x02 // a read or seek command didn't complete in time
#define CD_ERR_READY        0x04 // error reported to the ready callback
#define CD_ERR_SYNC         0x08 // error reported to the sync callback
#define CD_ERR_TIMEOUT      0x10 // streaming didn't start in time (XA play; the shim's movie)
#define CD_ERR_BAD_DATA     0x20 // a file's first word doesn't match its file table entry
#define CD_ERR_WRONG_SECTOR 0x40 // a sector arrived that wasn't the one expected

// CD_CMD.type
#define CD_CMD_END        0
#define CD_CMD_READ       1 // read a file into a buffer
#define CD_CMD_SUBCMD     2 // args.subcmd.sub selects a CD_SUBCMD_*
#define CD_CMD_XA_PLAY    4
#define CD_CMD_PLAY_MOVIE 5 // implemented in the shim only
#define CD_CMD_READ_COMB  6 // queued by Cd_read_comb
#define CD_CMD_SEEK       7

// CD command queue
#define CD_CMD_QUEUE_LEN  16
#define CD_CMD_END        0
#define CD_CMD_PLAY_MOVIE 5

// CD_CMD.args.subcmd.sub for CD_CMD_SUBCMD
#define CD_SUBCMD_NOP      0
#define CD_SUBCMD_XA_STOP  1
#define CD_SUBCMD_XA_PAUSE 2

// Cd_xa_state: XA audio playback
#define CD_XA_PLAYING 0
#define CD_XA_STOPPED 1 // next play seeks and restarts
#define CD_XA_PAUSED  2 // next play resumes without seeking
#define CD_XA_OFF     7 // not playing XA (initial; set when a data read starts)

// Cd_xa_flags
#define CD_XA_LOOP 0x40000000 // replay the track when it reaches its end

#define CD_XA_FILE_NO   1
#define CD_XA_CHAN_MASK 0x1F // XA channel (0-31)

// Cd_play_mode
#define CD_PLAY_NONE    0 // set by seeks and Cd_stop
#define CD_PLAY_XA_STOP 1 // set by the XA stop/pause subcommands (meaning provisional)
#define CD_PLAY_XA      2 // XA playing: Cd_cmd_exec watches for its end

#define CD_SECTOR_MASK         0xFFFFFF // low 24 bits: sector offset within a file
#define CD_SECTOR_SIZE         0x800    // data bytes per CD sector (mode 2 form 1)
#define CD_SECTOR_HEADER_WORDS 3        // CdGetSector size of a sector's header and subheader
#define CD_SECTOR_WORDS        (CD_SECTOR_SIZE / 4) // CdGetSector size of a sector's data
#define CD_FILE_COUNT          248
#define CD_VOL_MAX             0x7F
#define CD_STREAM_TIMEOUT      150
#define CD_CMD_TIMEOUT         150

#define CD_GETLOCP_ABS 5 // offset of the absolute position in the CdlGetlocP result

typedef struct
{
    sint32 sector;
    sint32 size;
    sint32 head;
} CD_FILE;

typedef union
{
    uint32 offset; // low 24 bits: sector offset (CD_SECTOR_MASK)
    struct
    {
        uint8 pad[3];
        uint8 chan; // top byte: XA channel
    } b;
} CD_XA_POS;

typedef struct
{
    sint32 file;     // Cd_file_tbl index
    CD_XA_POS start; // sector offset (low 24 bits), channel (top byte)
    uint32 end;      // sector offset (low 24 bits); saved in Cd_xa_end_sector ("end" is a guess)
} CD_XA_ARGS;

// Command arguments are copied as one 12-byte block; the layout depends on CD_CMD.type.
typedef union
{
    struct // CD_CMD_PLAY_MOVIE (shim only)
    {
        sint32 file;      // movie index into Cd_file_tbl
        sint32 end_frame; // frame number at which playback ends
        uint16 skip;      // pad buttons (matched against Joy1's "on" bits) that skip the movie
    } movie;
    CD_XA_ARGS xa; // CD_CMD_XA_PLAY
    struct         // CD_CMD_SUBCMD
    {
        sint32 arg1;
        sint32 sub; // CD_SUBCMD_*
        uint32 arg3;
    } subcmd;
    struct // CD_CMD_READ, CD_CMD_READ_COMB (file only)
    {
        sint32 file; // Cd_file_tbl index
        uint8 *buf;
    } read;
    struct // CD_CMD_SEEK
    {
        sint32 unused;
        sint32 sector;
    } seek;
} CD_CMD_ARGS;

typedef struct
{
    sint32 type; // CD_CMD_END = end of queue, CD_CMD_PLAY_MOVIE = play movie
    CD_CMD_ARGS args;
} CD_CMD;

typedef void (*CD_CMD_FUNC)(void);

#include "cd_local.h" // per-target CD variables with no name yet

// every file on the disc: sector, size, unknown
extern CD_FILE Cd_file_tbl[CD_FILE_COUNT];

// CD command queue
extern CD_CMD Cd_cmd_queue[CD_CMD_QUEUE_LEN];
extern CD_CMD *Cd_cmd_write_ptr; // next free slot
extern CD_CMD *Cd_cmd_exec_ptr;  // the command being run
extern CD_CMD_FUNC cd_cmd_tbl[CD_CMD_COUNT];

extern uint8 Cd_mode;
extern u_char Cd_result[8];
extern uint8 Cd_error_flags;
extern uint32 Cd_wait;
extern sint32 Cd_movie_playing;
extern uint8 Cd_xa_state;

// The running command's state (cd_cmd_play_movie's switch index); cleared on dequeue.
extern uint32 Cd_cmd_routine;

extern volatile uint8 Cd_status;
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

#endif // CD_H
