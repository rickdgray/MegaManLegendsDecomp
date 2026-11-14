#ifndef CODE_800456D8_H
#define CODE_800456D8_H

// code_800456D8.c's subsystem (not identified yet; rename with the file). Its objects are the
// WORK_48 pool slots of code_8002E7A8.h.

#include "common.h"
#include "code_8002E7A8.h"
#include "stage.h"

typedef void (*WORK48_FUNC)(WORK_48 *wp);

// 6-byte records stepped by func_80048390 / func_80048484.
typedef struct
{
    uint16 val_0; // low byte copied to WORK_48.field_22
    uint16 val_2; // low byte copied to WORK_48.field_23
    uint8 time_4; // copied to field_C.rec.timer
    uint8 pad_5;
} WORK48_REC;

// Per-slot tables of effect specs, one per pool kind (func_80047148, func_80047228).
typedef struct
{
    uint32 spec; // packed counts and kinds for func_80046B34
    uint32 pad_4[3];
} SPEC_ENT;

extern WORK48_FUNC D_8008A708[]; // routine_8 dispatch table of func_80047318
extern WORK48_FUNC D_8008A724[]; // routine_8 dispatch table of func_80047D9C
extern WORK48_FUNC D_8008A76C[]; // routine_8 dispatch table of func_80048354
extern WORK48_FUNC D_8008A778[]; // flag_4 dispatch table of func_800485E4

// Initial values copied into a WORK_48 by func_80047C84.
// The records are 8 bytes each, so the indexes below step by 8 bytes (func_80047CD8).
extern uint32 D_8008A6C8[];

extern uint8 D_8008A6CC[];
extern uint8 D_8008A6CD[];
extern uint8 D_8008A6CE[];
extern uint8 D_8008A6CF[];
extern WORK48_REC D_8008A730[];
extern WORK48_REC D_8008A748[];
extern WORK48_FUNC D_8008A718[]; // field_9 dispatch table of func_800476A4
extern SLOT_OWNER D_800986D8;

// Four rows of 32 words sampled by func_80046F38 into four rows of five words (D_8009A6C0).
extern uint32 D_8008A378[4][32];

extern uint32 D_8009A6C0[4][5];
extern uint32 D_8008A578[6];
extern uint32 D_8009A710[6][4];
extern uint16 D_80097E64[];      // indexed by WORK_48.field_A (func_800459C0)
extern uint16 D_80097EE0[];      // indexed by WORK_48.field_A (func_8004678C)
extern uint16 D_80097E7A[];      // angle step per spawn count (func_80045CE8)
extern sint16 D_80097E9C[];      // indexed by WORK_48.field_A (func_80045CE8)
extern uint16 D_80097EA8[];      // indexed by WORK_48.field_A (func_80045CE8)
extern uint8 D_8008A2B0[][16];   // field_A choices per kind (func_80045CE8)
extern WORK48_FUNC D_8008A6A8[]; // routine_8 dispatch table of func_8004602C
extern uint16 D_80097EC0[][4];   // four halfwords per entry, indexed by field_9 (func_8004602C)
extern uint8 D_80097EE8[];       // indexed by field_A (func_8004602C)
extern uint16 D_80097EEC[][4];   // [flag_3][field_A]: hit radius (func_80046A0C)
extern uint16 D_8008A678[][8];   // [Game_work 0x5B][field_A] (func_80046A0C)
extern uint16 D_8008A680[][8];
extern uint16 D_80097EFA[];    // angle step per spawn count (func_80046B34)
extern sint16 D_80097F1C[];    // indexed by WORK_48.field_A (func_80046B34)
extern uint16 D_80097F24[];    // indexed by WORK_48.field_A (func_80046B34)
extern uint8 D_8008A5A8[][16]; // field_A choices per kind (func_80046B34)
extern uint8 D_8009A5A0[];
extern uint8 D_8009A5D0[];
extern uint8 D_8009A600[];
extern uint8 D_8009A630[];
extern uint8 D_8009A660[];
extern SPEC_ENT **D_80098844;
extern SPEC_ENT **D_8009884C;
extern SPEC_ENT **D_80098928;
extern SPEC_ENT **D_8009892C;
extern HIT_ENT D_8008A618[][4];
extern sint16 D_8008A622[][4][6];
extern HIT_ENT D_8008A310[]; // indexed by field_A (func_80045750)

#endif // CODE_800456D8_H
