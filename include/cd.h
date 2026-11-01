#ifndef CD_H
#define CD_H

// The CD drive: init, control wrappers, callbacks, and CD audio settings.

#include "common.h"
#include "psyq/libcd.h"

// Cd_error_flags bits
#define CD_ERR_READY 0x04   // error reported to the ready callback
#define CD_ERR_SYNC 0x08    // error reported to the sync callback
#define CD_ERR_TIMEOUT 0x10 // timed out

extern uint8 Cd_mode;
extern u_char Cd_result[8];
extern uint8 Cd_error_flags; // CD_ERR_* bits

// Unknown (set up by Cd_init)
extern sint32 D_80059BB4;
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
