#ifndef CD_H
#define CD_H

// The CD module (Capcom's cd file): drive control, the command queue, reads and their
// callbacks, XA audio and combined files. Both programs have a copy of the module; ROCK_NEO's
// is larger. Declarations one program lacks are labelled; unused ones compile to nothing.

#include "common.h"
#include "psyq/libcd.h"
#include "psyq/libgpu.h"

// =============================================================================================
// Constants

// Sectors and files
#define CD_SECTOR_SIZE         0x800                // data bytes per CD sector (mode 2 form 1)
#define CD_SECTOR_WORDS        (CD_SECTOR_SIZE / 4) // CdGetSector size of a sector's data
#define CD_SECTOR_HEADER_WORDS 3                    // CdGetSector size of a sector's header and subheader
#define CD_SECTOR_MASK         0xFFFFFF             // low 24 bits: sector offset within a file
#define CD_FILE_COUNT          248                  // entries in Cd_file_tbl
#define CD_GETLOCP_ABS         5                    // offset of the absolute position in the CdlGetlocP result
#define CD_RING_SLOTS          10                   // sectors in Cd_ring_buf (ROCK_NEO only)

// Timing and volume
#define CD_CMD_TIMEOUT    150  // frames to wait for a read or seek to finish (CD_ERR_CMD_TIMEOUT)
#define CD_STREAM_TIMEOUT 150  // frames to wait for streaming to start (CD_ERR_TIMEOUT)
#define CD_VOL_MAX        0x7F // full CD audio volume (Cd_set_volume)

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
#define CD_ERR_BAD_DATA     0x20 // a file's first word doesn't match its Cd_file_tbl head
#define CD_ERR_WRONG_SECTOR 0x40 // a sector arrived that wasn't the one expected

// Cd_play_mode
#define CD_PLAY_NONE    0 // set by seeks and Cd_stop
#define CD_PLAY_XA_STOP 1 // set by the XA stop/pause subcommands (meaning provisional)
#define CD_PLAY_XA      2 // XA playing: Cd_cmd_exec watches for its end
#define CD_PLAY_MOVIE   3 // a movie is streaming (shim only)

// CD_CMD.type
#define CD_CMD_END        0 // end of the queue
#define CD_CMD_READ       1 // read a file into a buffer
#define CD_CMD_SUBCMD     2 // args.subcmd.sub selects a CD_SUBCMD_*
#define CD_CMD_XA_PLAY    4
#define CD_CMD_PLAY_MOVIE 5 // implemented in the shim only
#define CD_CMD_READ_COMB  6 // queued by Cd_read_comb
#define CD_CMD_SEEK       7

#define CD_CMD_QUEUE_LEN 16 // entries in Cd_cmd_queue

// CD_CMD.args.subcmd.sub, for CD_CMD_SUBCMD
#define CD_SUBCMD_NOP      0
#define CD_SUBCMD_XA_STOP  1
#define CD_SUBCMD_XA_PAUSE 2
#define CD_SUBCMD_MUTE     3 // toggle mute (Cd_muted)

// XA audio (ROCK_NEO only, apart from Cd_xa_state)
// Cd_xa_state
#define CD_XA_PLAYING 0
#define CD_XA_STOPPED 1 // next play seeks and restarts
#define CD_XA_PAUSED  2 // next play resumes without seeking
#define CD_XA_OFF     7 // not playing XA (initial; set when a data read starts)

#define CD_XA_LOOP      0x40000000 // Cd_xa_flags: replay the track when it reaches its end
#define CD_XA_FILE_NO   1          // the file number in an XA sector's subheader (CdlFILTER.file)
#define CD_XA_CHAN_MASK 0x1F       // XA channel (0-31)

// A packed track reference (Cd_xa_play_id, Cd_xa_seek_id); bit 30 is CD_XA_LOOP.
#define CD_XA_GROUP(id) (((id) >> 28) & 3)  // bits 28-29
#define CD_XA_FILE(id)  (((id) << 4) >> 20) // bits 16-27
#define CD_XA_NUM(id)   ((id)&0xFFFF)       // bits 0-15

// Combined ("comb") files (ROCK_NEO only)
//
// A combined file packs several entries, each one a header sector and its data sectors.
// cd_cmd_read_comb sends each entry where its type says, as the sectors arrive.

// CD_COMB_HEAD.type, Cd_comb_type
#define CD_COMB_END    -1 // end of the file
#define CD_COMB_DATA   0  // bytes to arg[0]
#define CD_COMB_TIM    1  // CLUT (header) at arg[0..3], image tiles at arg[4..7]
#define CD_COMB_TILES  3  // image tiles at arg[0], arg[1]; arg[2] x arg[3] tiles
#define CD_COMB_IMAGE  4  // one image in the header (unused in the shipped data)
#define CD_COMB_VAB    5  // VAB header, then body, into Game_work.vab[arg[0]]
#define CD_COMB_SEQ    7  // presumably a single sequence (unused in the shipped data)
#define CD_COMB_SEP    8  // a SEP sequence package, into a sequence slot (the files' .sep)
#define CD_COMB_CLUT   9  // a small image in the header; in the data, palette sets (to Clut_buf when x < CLUT_BUF_COLS)
#define CD_COMB_IMAGE3 10 // as CD_COMB_IMAGE, but 64 wide, arg[2] x arg[3] / 64 high
// Types 2 and 6 only set the state; their sectors are dropped.

#define CD_COMB_IMAGE3_W  64
#define CD_COMB_TILE_SIZE 32 // width and height of the tiles of CD_COMB_TIM and CD_COMB_TILES

// =============================================================================================
// Types

// A Cd_file_tbl entry: one file on the disc.
typedef struct
{
    sint32 sector; // first sector
    sint32 size;   // bytes
    sint32 head;   // the file's first word, checked on reads (CD_ERR_BAD_DATA)
} CD_FILE;

// An XA position: a sector offset within the file, with the XA channel in its top byte.
typedef union
{
    uint32 offset; // low 24 bits: sector offset (CD_SECTOR_MASK)
    struct
    {
        uint8 pad[3];
        uint8 chan; // top byte: XA channel
    } b;
} CD_XA_POS;

// A Cd_xa_track_tbl entry.
typedef struct
{
    CD_XA_POS start;
    uint32 end;
} CD_XA_TRACK;

typedef struct
{
    sint32 file;     // Cd_file_tbl index
    CD_XA_POS start; // sector offset (low 24 bits), channel (top byte)
    uint32 end;      // sector offset (low 24 bits) where the track ends (Cd_xa_end_sector)
} CD_XA_ARGS;

// Command arguments are copied as one 12-byte block; the layout depends on CD_CMD.type.
typedef union
{
    sint32 word[3]; // the raw arguments, for code that moves commands without interpreting them
    struct          // CD_CMD_PLAY_MOVIE (shim only)
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
    sint32 type; // CD_CMD_*
    CD_CMD_ARGS args;
} CD_CMD;

typedef void (*CD_CMD_FUNC)(void);

// A comb entry's header sector.
typedef struct
{
    uint32 type;                               // 0x00: CD_COMB_*
    uint32 size;                               // 0x04: bytes of data
    sint32 count;                              // 0x08: sectors (the header's own included, for some types)
    uint32 arg[61];                            // 0x0C: depends on the type
    u_long data[(CD_SECTOR_SIZE - 0x100) / 4]; // 0x100: image or CLUT data, for image types
} CD_COMB_HEAD;

// The comb entry being read (Cd_comb_work).
typedef struct
{
    uint32 size;  // 0x00
    sint32 count; // 0x04
    union         // 0x08: by type
    {
        struct // CD_COMB_DATA
        {
            uint8 *dest;
        } data;
        struct // CD_COMB_TIM
        {
            sint32 clut_x, clut_y, clut_w, clut_h;
            sint32 x, y;
            uint32 w, h;
            sint32 pad[2];
            sint32 col, row; // the next tile
        } tim;
        struct // CD_COMB_TILES
        {
            sint32 x, y;
            sint32 cols, rows;
            sint32 pad[6];
            sint32 col, row; // the next tile
        } tiles;
        struct // CD_COMB_VAB
        {
            sint32 slot; // Game_work.vab index
            sint32 num;
            uint32 sbaddr;    // SPU address
            sint32 head_size; // bytes of VAB header still to copy
            uint8 *dest;      // where the header is copied
            uint8 load;       // 0: already loaded, skip the sectors
        } vab;
        struct // CD_COMB_SEQ
        {
            sint32 pad[2];
            uint8 *dest;
            uint8 load; // 0: already loaded, skip the data
        } sound;
        struct // CD_COMB_SEP
        {
            sint32 pad[3];
            uint8 *dest;
            uint8 load; // 0: already loaded, skip the data
        } sound2;
    } u;
} CD_COMB_WORK;

// =============================================================================================
// Variables

// The drive
extern uint8 Cd_mode;
extern u_char Cd_result[8];
extern volatile uint8 Cd_status; // CD_STATUS_*
extern volatile uint8 Cd_stat;   // drive status byte after the last command (ROCK_NEO only)
extern uint8 Cd_sync_done;
extern uint8 Cd_error_flags; // CD_ERR_*
extern uint32 Cd_wait;
extern uint8 Cd_play_mode; // CD_PLAY_*
extern uint8 Cd_muted;     // 1 while muted by cd_subcmd_mute

// Every file on the disc
extern CD_FILE Cd_file_tbl[CD_FILE_COUNT];

// The command queue
extern CD_CMD Cd_cmd_queue[CD_CMD_QUEUE_LEN];
extern CD_CMD *Cd_cmd_write_ptr;    // next free slot
extern CD_CMD *Cd_cmd_exec_ptr;     // the command being run
extern uint32 Cd_cmd_routine;       // the running command's current step; cleared on dequeue
extern CD_CMD_FUNC cd_cmd_tbl[];    // handlers by CD_CMD.type (6 in the shim, 8 in ROCK_NEO)
extern CD_CMD_FUNC cd_subcmd_tbl[]; // handlers by args.subcmd.sub (ROCK_NEO only)

// Reading: position, the read buffer and the sector ring
extern CdlLOC Cd_loc;
extern sint32 Cd_file_sector; // next expected sector of the file being read
extern uint32 Cd_head_state;  // 0: the next sector is a header; nonzero: past it
extern uint8 *Cd_read_buf;    // where Cd_ready_cb_buf puts the next sector
extern sint32 Cd_read_left;   // bytes still to read

extern uint8 Cd_ring_ready[CD_RING_SLOTS];               // 1 while a slot holds an unread sector
extern uint8 Cd_ring_buf[CD_RING_SLOTS][CD_SECTOR_SIZE]; // shared memory: see notes/rock_neo.md
extern sint32 Cd_ring_write;                             // next slot Cd_ready_cb_ring fills
extern sint32 Cd_ring_read;                              // next slot cd_cmd_read_comb reads

// Movies (shim only)
extern sint32 Cd_movie_playing;

// XA audio
extern uint8 Cd_xa_state;                 // CD_XA_*
extern sint32 *Cd_xa_file_tbl[16];        // Cd_file_tbl index, by group and file
extern CD_XA_TRACK **Cd_xa_track_tbl[16]; // start and end, by group, file and track
extern uint32 Cd_xa_id;                   // reference of the current track (replayed to loop)
extern sint32 Cd_xa_flags;                // CD_XA_LOOP
extern sint32 Cd_xa_start;                // start of the current track
extern uint32 Cd_xa_end_sector;           // sector at which Cd_cmd_exec stops or loops the track
extern uint32 Cd_xa_sector;               // current absolute sector (from CdlGetlocP)
extern uint16 Cd_mute_save;               // Sound_work.serial_vol, saved while muted

// Combined files
extern uint32 Cd_comb_type;       // CD_COMB_* of the entry being read
extern CD_COMB_WORK Cd_comb_work; // the entry being read
// LoadImage rectangle of comb reads. Declared without a size on purpose: as an 8-byte RECT,
// GCC treats it as small data, rates its address as cheap as a register, and stops
// addressing rect->x through the RECT pointer as the original does. Probably part of a
// larger object.
extern RECT Cd_comb_rect[]; // HACK: needs a size

extern uint8 Cd_unused; // cleared by Cd_init; never read in either program

// =============================================================================================
// Functions

// The drive
void Cd_init(void);
void Cd_control_retry(u_char com, u_char *param, u_char *result);
void Cd_controlb_retry(u_char com, u_char *param, u_char *result);
void Cd_set_mode(u_char mode);
void Cd_set_volume(uint8 vol);
void Cd_stop(void);
void Cd_pause(void); // ROCK_NEO only
void Cd_sync_cb(u_char status, u_char *result);

// The command queue
void Cd_cmd_exec(void);
void Cd_cmd_dequeue(void);
sint32 Cd_read_sync2(void);                                        // nonzero while commands are queued
void Cd_read_sync(void);                                           // wait until the queue is empty (ROCK_NEO only)
void Cd_cmd_set_movie(sint32 file, sint32 end_frame, uint16 skip); // shim only

// Reading (ROCK_NEO only)
void Cd_seek(sint32 sector);
void Cd_seek_file(sint32 index);
void Cd_read_start_buf(sint32 file, uint8 *buf);
void Cd_read_start_ring(sint32 file);
void Cd_ready_cb_buf(u_char status, u_char *result);
void Cd_ready_cb_ring(u_char status, u_char *result);

// XA audio (ROCK_NEO only)
void Cd_xa_play_id(uint32 id);
void Cd_xa_seek_id(uint32 id);
void cd_subcmd_mute(void);

#endif // CD_H
