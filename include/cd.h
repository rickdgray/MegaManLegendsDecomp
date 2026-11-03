#ifndef CD_H
#define CD_H

// The CD drive: init, control wrappers, callbacks, and CD audio settings.

#include "common.h"
#include "psyq/libcd.h"

#define CD_FILE_COUNT 248

// Cd_error_flags bits
#define CD_ERR_READY   0x04 // error reported to the ready callback
#define CD_ERR_SYNC    0x08 // error reported to the sync callback
#define CD_ERR_TIMEOUT 0x10 // timed out
#define CD_VOL_MAX     0x7F

typedef struct
{
    sint32 sector;
    sint32 size;
    sint32 unk8;
} CD_FILE;

extern CD_FILE Cd_file_tbl[CD_FILE_COUNT]; // every file on the disc: sector, size, unknown

extern uint8 Cd_mode;
extern u_char Cd_result[8];
extern uint8 Cd_error_flags; // CD_ERR_* bits
extern sint32 Cd_wait;

// Unknown (set up by Cd_init)
extern uint8 D_80059BC8;
extern uint8 D_80059BC9;
extern uint8 D_80059BCA;
extern uint8 D_80059BD4;
extern sint32 D_80059C00;
extern uint8 D_80059C48;
extern uint8 D_80059C74;

void Cd_init(void);
void Cd_control_retry(u_char com, u_char *param, u_char *result);
void Cd_controlb_retry(u_char com, u_char *param, u_char *result);
void Cd_set_mode(u_char mode);
void Cd_set_volume(uint8 vol);
void Cd_stop(void);
void Cd_sync_cb(u_char status, u_char *result);

#endif // CD_H
