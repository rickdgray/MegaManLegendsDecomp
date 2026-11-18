#ifndef SOUND_H
#define SOUND_H

#include "common.h"
#include "psyq/libcd.h"
#include "psyq/libsnd.h"

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

// Local views for the sound helpers (additive).
typedef struct
{
    uint32 arg1;
    uint32 arg2;
} SOUND_ARGS;

typedef struct
{
    uint8 kind; // 0 = Sound_call, 1 = Sound_call2
    uint8 reserved01;
    sint16 id;
    SOUND_ARGS args;
    uint8 reserved0c[8];
} SOUND_CALL; // 0x14 bytes

typedef struct
{
    uint8 id;
    uint8 reserved01[7];
} SOUND_ENTRY; // 8-byte stride

typedef void (*SOUND_FUNC)(sint32 arg);

// Signed view of GAME_WORK.flags_53 (lb in the original)
#define GAME_WORK_FLAG53 (*(sint8 *)((uint8 *)&Game_work + 0x53))
typedef struct
{
    uint8 reserved00[0x1BA];
    SOUND_ENTRY slots[5];
} GAME_WORK_SOUND_VIEW;
#define GAME_WORK_VIEW  ((GAME_WORK_SOUND_VIEW *)&Game_work)
#define GAME_WORK_SLOTS ((SOUND_ENTRY *)((uint8 *)&Game_work + 0x1BA))
extern SOUND_CALL D_800BE6D8[];

extern uint32 D_800821F8[];
extern sint16 D_80082274;
extern sint16 D_80082278;
extern sint16 D_80082218;
extern sint16 D_800822D6;
extern uint16 D_800822A6[]; // table of 6 ends here; no symbol at its base 0x800822A0
#define D_800822A0 (D_800822A6 - 5)
extern uint16 D_800822B0[]; // table of 5 ends here; no symbol at its base 0x800822A8
#define D_800822A8 (D_800822B0 - 4)
extern uint16 D_800822F2;
extern uint16 D_800822F4;
extern SOUND_ENTRY D_80098AD0[];
extern SOUND_CALL *D_80098938;
extern uint32 D_80098958;
extern SOUND_FUNC D_800823A0[];

extern uint16 *D_80082320[];
extern void func_8001B33C(void);
extern void func_8001D854(sint32 arg);
typedef struct
{
    uint8 reserved0[2];
    uint8 priority_2;
    uint8 voice_3;
} SOUND_VOICE;

typedef struct
{
    uint8 reserved00[0x14];
    sint16 x;
    sint16 y;
    sint16 z;
    uint8 reserved1A[0x3C];
    sint16 rot_56;
} SOUND_PLAYER;

typedef struct
{
    uint8 kind_0;
    uint8 reserved1[3];
    sint16 x_4;
    sint16 reserved6;
    sint16 z_8;
} SOUND_POS;

extern SOUND_PLAYER *p_Player_work;
#define SOUND_DIST_TBL ((sint16 *)((uint8 *)&Game_work + 0x1E0))
extern uint8 D_80098B48[];
extern sint32 SpuGetKeyStatus(uint32 voice_bit);
extern sint32 SquareRoot0(sint32 v);
typedef void (*SOUND_CALL_FUNC)(SOUND_CALL *call);
extern SOUND_CALL D_800BE4F8[];
typedef struct
{
    uint8 flags;
    uint8 byte_1; // low 7 bits: tone index high part
    uint8 byte_2; // high nibble: tone index low part
    uint8 byte_3; // bits 0-4: first voice slot, bits 5-6: extra tone count
} SOUND_INFO;
#define GAME_WORK_SLOT_VAB(i) (*(uint16 *)((uint8 *)&Game_work + 0x1B8 + (i) * 8))
#define SOUND_TONE_BASE       0x8014B820
extern SOUND_INFO D_8008241C[];
extern SOUND_CALL_FUNC D_80082C64[];
extern uint8 D_80098AFD[][8];
extern void func_8001AEF0(void);
extern sint32 Sce_flag_test(sint32 flag);
extern sint16 SsIsEos(sint16 vab_id, sint16 prog);
extern sint16 D_8008222A[];
#define D_80082224 (D_8008222A - 5)
extern sint16 D_8008222C;
extern uint8 D_80098840;
extern sint16 D_80098AF8[][4];
extern sint8 D_80098AFA[][8];
extern uint8 D_80098AFC[][8];
extern sint32 D_80082C70[];
extern sint32 D_80082CA0[];
extern sint32 func_8001A63C(sint32 n);
extern void func_80070114(sint32 arg);
extern void func_8007013C(sint32 arg0, sint32 arg1);
extern void SsUtKeyOffV(sint16 voice);
extern void SpuSetKey(sint32 on_off, uint32 voice_bit);

// Local view of PsyQ's SpuVoiceAttr (0x40 bytes)
typedef struct
{
    uint32 voice;    // 0x00
    uint32 mask;     // 0x04
    uint16 volume_l; // 0x08
    uint16 volume_r; // 0x0A
    uint8 reserved0c[8];
    uint16 pitch; // 0x14
    uint8 reserved16[6];
    uint32 addr; // 0x1C
    uint8 reserved20[0x1A];
    uint16 adsr1; // 0x3A
    uint16 adsr2; // 0x3C
    uint8 reserved3e[2];
} SOUND_VOICE_ATTR;

// Local view of a VAB tone entry used by func_8001A744
typedef struct
{
    uint8 reserved00[2];
    uint8 pan_2;
    uint8 reserved03;
    uint8 note_4;
    uint8 frac_5;
    uint8 note_6;
    uint8 reserved07[9];
    uint16 adsr1_10;
    uint16 adsr2_12;
    uint8 reserved14[2];
    sint16 vag_16;
    uint8 reserved18[8];
} SOUND_TONE; // 0x20 bytes

extern sint32 func_8001A834(SOUND_VOICE *voice, SOUND_POS *pos);
extern void func_8001A274(SOUND_POS *pos, uint32 pan, uint16 *left, uint16 *right, sint16 dist);
extern void SpuSetKeyOnWithAttr(SOUND_VOICE_ATTR *attr);
extern sint32 SsUtGetVagAddr(sint16 vab, sint16 vag);

extern uint16 D_80082314[];

// Local view of PsyQ's SpuEnv
typedef struct
{
    uint32 mask;
    uint32 value;
} SOUND_SPU_ENV;

extern void func_8006B594(void);
extern uint8 D_800C1010[];
extern void SsSetTableSize(void *table, sint32 s_max, sint32 t_max);
extern void SsSetTickMode(sint32 mode);
extern void SsStart(void);
extern void SpuSetEnv(SOUND_SPU_ENV *env);

// Local view of the 8-byte entries of D_80098AF8
typedef struct
{
    sint16 seq;   // 0x00: SsSeq access number, -1 if closed
    sint8 kind;   // 0x02: -1 none, 0 SEQ, otherwise SEP
    sint8 prio;   // 0x03
    uint8 arg_4;  // 0x04
    uint8 flag_5; // 0x05
    sint16 id;    // 0x06: sound call id
} SOUND_SEQ;
#define SOUND_SEQ_TBL ((SOUND_SEQ *)D_80098AF8)
extern sint32 D_80098AD4[][2];
extern sint16 SsSepOpen(sint32 addr, sint16 vab, uint8 seq_num);
extern void SsSepPlay(sint16 seq, uint8 sep, sint32 mode, sint32 loop);
extern sint32 func_8001A238(sint32 id);
extern sint16 SsSeqOpen(sint32 addr, sint16 vab);
extern void SsSeqPlay(sint16 seq, sint32 mode, sint32 loop);
extern void SsSeqClose(sint16 seq);
extern void SsSepClose(sint16 seq);

extern sint32 ccos(sint32 angle);
extern sint32 func_8001E83C(sint16 x0, sint16 z0, sint16 x1, sint16 z1);
#define GAME_WORK_FLAG58 (*(sint8 *)((uint8 *)&Game_work + 0x58))

extern sint32 func_8001AE6C(sint32 flags, uint16 *p);
extern void SsSetMVol(sint16 voll, sint16 volr);
extern void func_80075AA4(void);
extern void func_80075AB8(void);
extern void func_80070634(sint16 seq, sint16 voll, sint16 volr);
extern void func_80070694(sint16 seq, uint8 sep, sint16 voll, sint16 volr);
extern void func_80070974(sint32 arg);
extern void SsSetReservedVoice(uint8 voices);
extern void SsUtSetReverbType(sint16 type);
extern void func_800721C4(void);
extern void SsUtSetReverbDepth(sint16 left, sint16 right);
extern void SsSetRVol(sint16 left, sint16 right);

#endif // SOUND_H
