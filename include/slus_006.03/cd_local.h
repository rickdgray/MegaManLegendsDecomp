#ifndef CD_LOCAL_H
#define CD_LOCAL_H

// slus_006.03-specific: CD variables with no name yet. Included at the end of cd.h.
// The rock_neo.exe counterparts are in include/rock_neo.exe/cd_local.h.

#include "common.h"

extern uint8 D_80059BC9;
extern uint8 D_80059BCA;
extern sint32 D_80059C00;
extern uint8 D_80059C48;
extern uint8 D_80059C74;
extern sint32 D_80059C24; // cleared with Cd_cmd_routine, not otherwise referenced in the shim

#endif // CD_LOCAL_H
