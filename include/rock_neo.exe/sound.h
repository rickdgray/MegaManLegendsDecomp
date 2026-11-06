#ifndef SOUND_H
#define SOUND_H

#include "common.h"
#include "psyq/libcd.h"

#define SOUND_FLAG_MONO   0x0001
#define SOUND_FLAG_CD_OFF 0x8000

// CD/sound mixer state at 0x800AD140..0x800AD163 (0x24 bytes; 0x800AD164..67 is never accessed,
// and 0x800AD168 starts an unrelated buffer). Widths and signedness are from the load/store
// instructions. Most fields are touched through D_800AD1xx labels (see "Unknown" below); only
// func_8001AEF0, func_8001AA8C and func_8001AC58 (sound.s) address them through Sound_work.
typedef struct
{
    uint8 unk00[2]; // 0x00: never accessed
    uint16 flags;   // 0x02: bit 0 = mono (see Cd_set_volume); bit 15 set by Cd_stop/func_8001B7B4.
        //       lhu/andi 0x8000 in func_8001AEF0, B644/B6FC/B89C/B7B4/CB7C, Cd_set_volume
    sint16 unk04; // 0x04: lh (func_8001AEF0, master volume factor); init in func_80019DE0
    sint16 unk06; // 0x06: lh (func_8001AEF0, serial volume factor); also read as lhu / saved and
                  //       cleared by func_8001B7B4 (D_800AD146); init in func_80019DE0
    sint16 unk08; // 0x08: lh (func_8001A274); init 0x40 in func_80019DE0
    sint16 unk0A; // 0x0A: lh (func_8001AEF0); init 0x64 in func_80019DE0
    sint16
        unk0C; // 0x0C: lh; &unk0C passed to func_8001AE6C (read/written as 16-bit) by func_8001AEF0
    sint16
        unk0E; // 0x0E: lh; &unk0E passed to func_8001AE6C by func_8001AEF0; also written by func_8001B89C
    sint16 unk10; // 0x10: lh (func_8001A274); &unk10 passed to func_8001AE6C by func_8001AEF0
    sint16
        unk12; // 0x12: lh; &unk12 passed to func_8001AE6C; set to 0x7F by func_8001AA8C/func_8001AC58
    CdlATV atv;  // 0x14: CD audio volume (val0..val3, bytes), applied with CdMix; Cd_set_volume
    sint8 unk18; // 0x18: lb/lbu (func_8001AEF0, compared with unk19); init in func_80019DE0
    sint8 unk19; // 0x19: lb/sb (func_8001AEF0, copy of unk18); cleared in func_80019DE0
    uint8 unk1A; // 0x1A: lbu/sb (func_8001AEF0 reverb state 0/1); cleared in func_80019DE0
    uint8 unk1B; // 0x1B: lbu/sb (func_8001AEF0 countdown, set to 0x1E)
    uint8
        *unk1C; // 0x1C: lw (func_8001AEF0: pointer to 3-byte reverb entries); set by func_80019DE0
                //       (&D_800821F8) and func_80019F94
    uint8 *unk20; // 0x20: lw/sw (func_8001AEF0: last applied unk1C); cleared in func_80019DE0
} SOUND_WORK;

extern SOUND_WORK Sound_work; // 0x800AD140

#endif // SOUND_H
