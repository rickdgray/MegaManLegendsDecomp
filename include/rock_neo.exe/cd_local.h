#ifndef CD_LOCAL_H
#define CD_LOCAL_H

// rock_neo.exe-specific: CD variables with no name yet. Included at the end of cd.h.
// The slus_006.03 counterparts (shim names in comments) are in include/slus_006.03/cd_local.h.

#include "common.h"
#include "psyq/libcd.h"

#define CD_CMD_COUNT  8
#define CD_RING_SLOTS 10

#define CD_XA_GROUP(id) (((id) >> 28) & 3)  // bits 28-29
#define CD_XA_FILE(id)  (((id) << 4) >> 20) // bits 16-27
#define CD_XA_NUM(id)   ((id)&0xFFFF)       // bits 0-15

extern uint8 Cd_play_mode;          // D_80059BC9
extern uint8 D_800988DC;            // D_80059BCA
extern sint32 Cd_ring_write;        // D_80059C00
extern sint32 Cd_head_checked;      // D_80059C24
extern uint8 D_80098AA0;            // D_80059C48
extern CD_CMD_FUNC cd_subcmd_tbl[]; // run by cd_cmd_subcmd, indexed by the command's arg2

typedef struct
{
    CD_XA_POS start;
    uint32 end;
} CD_XA_TRACK;

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
extern sint32 Cd_xa_start;

// Unknown
extern uint16 D_80098994;

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

// Unknown
void func_8001B7B4(void);
void func_8001D7AC(sint32 index);

#endif // CD_LOCAL_H
