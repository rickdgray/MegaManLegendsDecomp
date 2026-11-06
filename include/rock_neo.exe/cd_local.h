#ifndef CD_LOCAL_H
#define CD_LOCAL_H

// rock_neo.exe-specific: CD variables with no name yet. Included at the end of cd.h.
// The slus_006.03 counterparts (shim names in comments) are in include/slus_006.03/cd_local.h.

#include "common.h"

extern uint8 D_800988D0;         // D_80059BC9
extern uint8 D_800988DC;         // D_80059BCA
extern sint32 D_80098998;        // D_80059C00
extern sint32 D_800989C8;        // D_80059C24
extern uint8 D_80098AA0;         // D_80059C48
extern uint8 D_80098B42;         // D_80059C74
extern CD_CMD_FUNC D_80087670[]; // run by func_8001B858, indexed by the command's arg2

typedef struct
{
    uint32 offset; // sector offset within the file (low 24 bits)
    uint32 unk4;
} CD_POS;

// Unknown
extern uint16 D_80098994;
extern uint8 D_80098AB8;
extern sint32
    *D_80088F9C[16]; // file index tables, selected by the top nibble of func_8001D648's argument
extern CD_POS **D_80088EF8[16]; // matching sector offset tables

void Cd_set_volume(uint8 vol);
void Cd_pause(void);
void Cd_stop(void);
void Cd_read_sync(void);

// Unknown
void func_8001B7B4(void);
void func_8001D648(uint32 arg);
void func_8001D6D8(sint32 sector);
void func_8001D7AC(sint32 index);

#endif // CD_LOCAL_H
