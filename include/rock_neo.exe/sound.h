#ifndef SOUND_H
#define SOUND_H

#include "common.h"
#include "psyq/libsnd.h"
#include "psyq/libcd.h"

#define SOUND_FLAG_MONO   0x0001
#define SOUND_FLAG_CD_OFF 0x8000

#define SOUND_DATA_BUF ((uint8 *)0x8013B000) // sound data loaded by comb reads (types 7, 8)
#define VAB_HEAD_BUF   ((uint8 *)0x8014B000) // VAB headers, one per Game_work.vab slot
#define VAB_HEAD_SIZE  0x1820

#define SOUND_CALL_MAX 24 // entries in the sound call queue (D_800BE4F8)

// CD/sound mixer state at 0x800AD140..0x800AD163 (0x24 bytes; 0x800AD164..67 is never accessed,
// and 0x800AD168 starts an unrelated buffer). Widths and signedness are from the load/store
// instructions. Most fields are touched through D_800AD1xx labels (see "Unknown" below); only
// func_8001AEF0, func_8001AA8C and func_8001AC58 (sound.s) address them through Sound_work.
typedef struct
{
    uint8 unk00[2]; // 0x00: never accessed
    uint16 flags;   // 0x02: bit 0 = mono (see Cd_set_volume); bit 15 set by Cd_stop/cd_subcmd_mute.
        //       lhu/andi 0x8000 in func_8001AEF0, B644/B6FC/B89C/B7B4/CB7C, Cd_set_volume
    sint16 unk04; // 0x04: lh (func_8001AEF0, master volume factor); init in func_80019DE0
    sint16 serial_vol;
    sint16 unk08; // 0x08: lh (func_8001A274); init 0x40 in func_80019DE0
    sint16 unk0A; // 0x0A: lh (func_8001AEF0); init 0x64 in func_80019DE0
    sint16 unk0C; // 0x0C: lh; &unk0C passed to func_8001AE6C (read/written as 16-bit) by func_8001AEF0
    sint16 unk0E; // 0x0E: lh; &unk0E passed to func_8001AE6C by func_8001AEF0; also written by cd_cmd_xa_play
    sint16 unk10; // 0x10: lh (func_8001A274); &unk10 passed to func_8001AE6C by func_8001AEF0
    sint16 unk12; // 0x12: lh; &unk12 passed to func_8001AE6C; set to 0x7F by func_8001AA8C/func_8001AC58
    CdlATV atv;   // 0x14: CD audio volume (val0..val3, bytes), applied with CdMix; Cd_set_volume
    sint8 unk18;  // 0x18: lb/lbu (func_8001AEF0, compared with unk19); init in func_80019DE0
    sint8 unk19;  // 0x19: lb/sb (func_8001AEF0, copy of unk18); cleared in func_80019DE0
    uint8 unk1A;  // 0x1A: lbu/sb (func_8001AEF0 reverb state 0/1); cleared in func_80019DE0
    uint8 unk1B;  // 0x1B: lbu/sb (func_8001AEF0 countdown, set to 0x1E)
    uint8 *unk1C; // 0x1C: lw (func_8001AEF0: pointer to 3-byte reverb entries); set by func_80019DE0
                  //       (&D_800821F8) and func_80019F94
    uint8 *unk20; // 0x20: lw/sw (func_8001AEF0: last applied unk1C); cleared in func_80019DE0
} SOUND_WORK;

// An entry of Sound_seq_tbl, filled by cd_cmd_read_comb's types 7 and 8.
typedef struct
{
    uint8 num;  // 0x0: number of the data loaded; a new number reloads it
    uint8 unk1; // 0x1: type 8 only
    uint8 pad2[2];
    uint8 *data; // 0x4: in SOUND_DATA_BUF
} SOUND_DATA;

// A queued sound call, 0x14 bytes; Sound_call appends one at D_80098938.
typedef struct
{
    uint8 busy; // 0x0: cleared on queueing
    uint8 pad1;
    sint16 id;     // 0x2
    sint32 arg1;   // 0x4
    sint32 arg2;   // 0x8
    uint8 unkC[8]; // 0xC: untouched by Sound_call
} SOUND_CALL;

// An entry of the table at D_80098AF8, 8 bytes; polled by func_8001A0A8.
typedef struct
{
    sint16 unk0; // 0x0: -1 when unused; first argument of SsIsEos
    sint8 unk2;  // 0x2: -1 when unused
    sint8 unk3;  // 0x3: priority of the sequence playing (lb)
    uint8 unk4;  // 0x4: second argument of SsIsEos
    uint8 unk5;  // 0x5: SsIsEos result, stored by func_8001A110
    sint16 unk6; // 0x6: id of the SOUND_CALL playing
} SOUND_SEQ_CHAN;

// An entry of the table at D_8008241C, 4 bytes.
typedef struct
{
    uint8 type; // 0x0: bits 0-5 = bank number (func_8001A1FC), bits 6-7 select the handler in D_80082C64
    uint8 unk1; // 0x1: bits 0-6 = program number
    uint8 unk2; // 0x2: high nibble = tone offset in the program; low nibble = priority (D_80098B48)
    uint8 unk3; // 0x3: bits 0-4 = SPU voice, bits 5-6 = extra tones to play
} SOUND_CALL_INFO;

// One VAB header slot in VAB_HEAD_BUF, VAB_HEAD_SIZE bytes: VabHdr, 128 ProgAtr, then the tones (0x820)
typedef struct
{
    VabHdr hdr;         // 0x000
    ProgAtr prog[128];  // 0x020
    VagAtr tone[8][16]; // 8 programs of 16 tones
} VAB_HEAD;

typedef void (*SOUND_FUNC)(sint32);
typedef void (*SOUND_CALL_FUNC)(SOUND_CALL *call);

extern SOUND_WORK Sound_work;
extern SOUND_DATA Sound_seq_tbl[5];

// Unknown
extern uint32 D_80098958; // flags; 0x800 forces cd_cmd_read_comb to reload VAB bank 4

extern uint8 D_800821F8[][4]; // reverb entries (3 bytes + pad) selected by func_80019F94
extern sint16 D_80082220[6];
extern sint16 D_8008222C;
extern sint16 D_80082274;
extern sint16 D_80082278;
extern SOUND_FUNC D_800823A0[];
extern SOUND_SEQ_CHAN D_80098AF8[];
extern sint16 D_800822D6;
extern sint16 D_80082218;
extern sint16 D_8008229C[6];
extern sint16 D_800822A8[5];
extern uint16 D_800822F2;
extern uint16 D_800822F4;
extern SOUND_CALL *D_80098938;                // next free sound call entry
extern SOUND_CALL D_800BE4F8[SOUND_CALL_MAX]; // the queue; D_80098938 points into it
extern sint32 D_80082C70[12];                 // func_8001A63C: scale table, positive exponents
extern sint32 D_80082CA0[12];                 // func_8001A63C: scale table, negative exponents
extern uint8 D_80098840;                      // step used by func_8001AE6C
extern uint16 *D_80082320[];                  // per-stage sound call id lists, indexed by Game_work.unk051
extern SOUND_CALL_INFO D_8008241C[];          // per-call-id info, indexed by SOUND_CALL.id
extern SOUND_CALL_FUNC D_80082C64[3];
extern uint8 D_80098B48[24]; // per-voice priority of the sound playing (low nibble of SOUND_CALL_INFO.unk2)
extern uint16 D_80082314[];  // func_80019B14: per-stage sound ids
extern uint8 D_800C356E;     // like Game_work.unk050; stage whose sound is loaded?
extern uint8 D_800C356F;     // like Game_work.unk051

extern char D_800C1010[]; // SsSetTableSize work area
extern uint8 D_80098788;
void func_8001D854(sint32 arg); // not sound code; called with 0x10 when the stage's sound list changes
void func_8001A744(uint16 vab_id, SOUND_CALL_INFO *info, VagAtr *tone, SOUND_CALL *call);
sint32 func_8001A834(SOUND_CALL_INFO *info, SOUND_CALL *call);
void func_8001A968(SOUND_CALL *call);
void func_80019B14(sint32 which);
void func_80019C20(void);
void func_80019DE0(void);
void func_8001A274(SOUND_CALL *call, uint16 vol, uint16 *left, uint16 *right, sint16 dist);
sint32 func_8001E83C(sint16 x, sint16 z, sint16 dx, sint16 dz); // not sound code; angle to a point

void func_8001B33C(void);
void Sound_call(sint16 id, sint32 arg1, sint32 arg2);
void func_8001AEF0(void);
sint32 func_8001A63C(sint32 x);
sint32 func_8001A0A8(sint32 idx);

#endif // SOUND_H
