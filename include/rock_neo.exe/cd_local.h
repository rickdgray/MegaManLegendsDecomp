#ifndef CD_LOCAL_H
#define CD_LOCAL_H

// rock_neo.exe-specific: CD variables with no name yet. Included at the end of cd.h.
// The slus_006.03 counterparts (shim names in comments) are in include/slus_006.03/cd_local.h.

#include "common.h"
#include "psyq/libcd.h"
#include "psyq/libgpu.h"

#define CD_CMD_COUNT  8
#define CD_RING_SLOTS 10

#define CD_XA_GROUP(id) (((id) >> 28) & 3)  // bits 28-29
#define CD_XA_FILE(id)  (((id) << 4) >> 20) // bits 16-27
#define CD_XA_NUM(id)   ((id)&0xFFFF)       // bits 0-15

typedef struct
{
    CD_XA_POS start;
    uint32 end;
} CD_XA_TRACK;

// A combined ("comb") file packs several entries, each one a header sector and its data
// sectors. cd_cmd_read_comb sends each entry where its type says, as the sectors arrive.
// Cd_comb_type (the entry's type)
#define CD_COMB_END    -1 // end of the file
#define CD_COMB_DATA   0  // bytes to arg[0]
#define CD_COMB_TIM    1  // CLUT (header) at arg[0..3], image tiles at arg[4..7]
#define CD_COMB_TILES  3  // image tiles at arg[0], arg[1]; arg[2] x arg[3] tiles
#define CD_COMB_IMAGE  4  // one image in the header, at arg[0..3]
#define CD_COMB_VAB    5  // VAB header, then body, into Game_work.vab[arg[0]]
#define CD_COMB_SOUND  7  // sound data into D_80098AD0[arg[0]]
#define CD_COMB_SOUND2 8  // sound data into D_80098AD0[arg[0]], with a second number
#define CD_COMB_IMAGE2 9  // as CD_COMB_IMAGE
#define CD_COMB_IMAGE3 10 // as CD_COMB_IMAGE, but 64 wide, arg[2] x arg[3] / 64 high

#define CD_COMB_TILE_SIZE 32 // width and height of the tiles of CD_COMB_TIM and CD_COMB_TILES

// A comb entry's header sector.
typedef struct
{
    uint32 type;    // 0x00: CD_COMB_*
    uint32 size;    // 0x04: bytes of data
    sint32 count;   // 0x08: sectors (the header's own included, for some types)
    uint32 arg[61]; // 0x0C: depends on the type
    u_long data[(CD_SECTOR_SIZE - 0x100) / 4]; // 0x100: image or CLUT data, for image types
} CD_COMB_HEAD;

// The entry being read (Cd_comb_work).
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
            sint32 pad[4];
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
        struct // CD_COMB_SOUND
        {
            sint32 pad[2];
            uint8 *dest;
            uint8 load; // 0: already loaded, skip the data
        } sound;
        struct // CD_COMB_SOUND2
        {
            sint32 pad[3];
            uint8 *dest;
            uint8 load; // 0: already loaded, skip the data
        } sound2;
    } u;
} CD_COMB_WORK;

extern CdlLOC Cd_loc;
extern sint32 Cd_file_sector;
extern uint8 Cd_ring_ready[CD_RING_SLOTS];
extern uint8 Cd_ring_buf[CD_RING_SLOTS][CD_SECTOR_SIZE];
extern CD_CMD_FUNC cd_cmd_tbl[];
extern volatile uint8 Cd_stat;
extern uint8 *Cd_read_buf;
extern uint32 Cd_xa_id;
extern sint32 Cd_xa_flags;
extern uint32 Cd_xa_end_sector; // sector at which Cd_cmd_exec stops or continues the read
extern uint32 Cd_xa_sector;     // current absolute sector (from CdlGetlocP)
extern sint32 Cd_read_left;
extern sint32 *Cd_xa_file_tbl[16];
extern CD_XA_TRACK **Cd_xa_track_tbl[16];
extern CD_CMD_FUNC cd_subcmd_tbl[];
extern sint32 Cd_xa_start;
extern uint16 Cd_mute_save;

// Unknown
extern uint8 D_80098AA0;        // D_80059C48
extern sint32 Cd_ring_read;       // next ring slot to read (proposed Cd_ring_read)
extern uint32 Cd_comb_type;       // type of the comb entry being read (CD_COMB_*)
extern CD_COMB_WORK Cd_comb_work; // the comb entry being read
// LoadImage rectangle of comb reads. Declared without a size on purpose: as an 8-byte RECT,
// GCC treats it as small data, rates its address as cheap as a register, and stops
// addressing rect->x through the RECT pointer as the original does. Probably part of a
// larger object.
extern RECT Cd_comb_rect[]; // HACK: needs a size

void Cd_set_volume(uint8 vol);
void Cd_pause(void);
void Cd_stop(void);
void Cd_read_sync(void);
void Cd_seek(sint32 sector);
void Cd_read_start_buf(sint32 file, uint8 *buf);
void Cd_read_start_ring(sint32 file);
void Cd_xa_play_id(uint32 id);
void Cd_ready_cb_buf(u_char status, u_char *result);
void Cd_ready_cb_ring(u_char status, u_char *result);
void Cd_xa_seek_id(uint32 arg);
void cd_subcmd_mute(void);

// Unknown
void func_8001D7AC(sint32 index);

#endif // CD_LOCAL_H
