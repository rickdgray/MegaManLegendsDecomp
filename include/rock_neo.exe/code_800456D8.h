#ifndef CODE_800456D8_H
#define CODE_800456D8_H

// code_800456D8.c's subsystem (not identified yet; rename with the file). Its objects are the
// WORK_48 pool slots of code_8002E7A8.h.

#include "common.h"
#include "code_8002E7A8.h"
#include "stage.h"

// Kind 0x86 of the WORK_48 pool (handler func_8004569C). A model kind (debris); func_80045CE8 spawns it.
typedef struct
{
    uint8 be_flag; // 0x00-0x0B: the header shared by every kind (see WORK_48)
    uint8 work_id; // pool kind (0x10 * pool number) | slot index
    uint8 id;      // 0x86
    uint8 type;
    uint8 handler;
    uint8 flag_5;
    uint8 flags;
    uint8 pad_7;
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2; // also a value: the size, indexing D_80097E64 and D_8008A310 (func_80045750)
    uint8 routine_3; // also a timer: frames left, counted down (func_80045918, func_8004594C)
    sint16 ang_y_C;  // Y rotation of the matrix
    sint16 ang_x_E;  // X rotation of the matrix (func_80045AB4)
    uint32 field_10;
    uint8 *data_14; // model data of the EBD entry, set by Model_work_init
    sint16 m[3][3]; // 0x18: rotation and scale (diagonal = pos_38.pad), passed as a MATRIX whose t
    uint16 pad_2A;  //       bytes hold the speed and acceleration below
    sint16 vx_2C;   // 0x2C: speed, added to pos_38 each frame
    sint16 vy_2E;
    sint16 vz_30;
    sint16 ax_32; // 0x32: acceleration, added to the speed each frame
    sint16 ay_34;
    sint16 az_36;
    SVECTOR pos_38; // 0x38: position (x, y = height, z)
    uint32 rgbc_40; // 0x40: code and colour
    void *ptr_44;   // table the object steps through (D_8009A5A0, ..., set by func_80045CE8)
} W48_86_WORK;      // 0x48 bytes

typedef void (*W48_86_FUNC)(W48_86_WORK *wp);

// Kind 0x87 of the WORK_48 pool (handler func_8004602C). A model kind (debris); func_80046B34 spawns it.
typedef struct
{
    uint8 be_flag; // 0x00-0x0B: the header shared by every kind (see WORK_48)
    uint8 work_id; // pool kind (0x10 * pool number) | slot index
    uint8 id;      // 0x87
    uint8 type;
    uint8 handler;
    uint8 flag_5;
    uint8 flags;
    uint8 pad_7;
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2; // also a value: the size, indexing D_8008A618[type], D_80097EE0, D_80097EE8
    uint8 routine_3; // also a timer: frames left, counted down (func_8004622C, func_80046438)
    sint16 ang_y_C;  // Y rotation of the matrix
    sint16 ang_x_E;  // X rotation of the matrix (func_80046890)
    uint32 field_10;
    uint8 *data_14; // model data of the EBD entry, set by Model_work_init
    sint16 m[3][3]; // 0x18: rotation and scale (diagonal = pos_38.pad), passed as a MATRIX whose t
    uint16 pad_2A;  //       bytes hold the speed and acceleration below
    sint16 vx_2C;   // 0x2C: speed, added to pos_38 each frame
    sint16 vy_2E;
    sint16 vz_30;
    sint16 ax_32; // 0x32: acceleration, added to the speed each frame
    sint16 ay_34;
    sint16 az_36;
    SVECTOR pos_38; // 0x38: position (x, y = height, z)
    uint32 rgbc_40; // 0x40: code and colour
    void *ptr_44;   // table the object steps through (D_8009A5A0, ..., set by func_80046B34)
} W48_87_WORK;      // 0x48 bytes

typedef void (*W48_87_FUNC)(W48_87_WORK *wp);

// Kind 0x88 of the WORK_48 pool (handler func_80047318). A model kind that becomes a sprite: routine 3 (func_80047CD8) steps a sprite animation over the bytes the model used, so 0x14-0x43 are an EFC, like WORK_48.efc.
typedef struct
{
    uint8 be_flag; // 0x00-0x0B: the header shared by every kind (see WORK_48)
    uint8 work_id; // pool kind (0x10 * pool number) | slot index
    uint8 id;      // 0x88
    uint8 type;
    uint8 handler;
    uint8 flag_5;
    uint8 flags;
    uint8 pad_7;
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2; // also a value: the colour's fade level, or frames left from D_8008A6CD
    uint8 routine_3; // also a counter: the spin, RotMatrixY(++routine_3 << 7) (func_800477A0)
    sint8 work_0;
    uint8 work_1; // 0D
    uint8 work_2; // 0E
    uint8 work_3; // 0F
    uint32 field_10;
    EFC efc;         // 0x14
    sint16 hw_44[2]; // hw_44[0] += hw_44[1] each frame, then added to efc.model.pos.pad
                     // (func_800477A0)
} W48_88_WORK;       // 0x48 bytes

typedef void (*W48_88_FUNC)(W48_88_WORK *wp);

// The eight spark lines of kind 0x89, reached through one pointer (func_80047DD8, func_80047EC8).
typedef struct
{
    uint16 ang[8]; // angle of each line
    sint16 idx[8]; // length of each line: grows by one each frame, wrapping at 8
} W48_89_LINES;

// Kind 0x89 of the WORK_48 pool (handler func_80047D9C). A sprite kind.
typedef struct
{
    uint8 be_flag; // 0x00-0x0B: the header shared by every kind (see WORK_48)
    uint8 work_id; // pool kind (0x10 * pool number) | slot index
    uint8 id;      // 0x89
    uint8 type;
    uint8 handler;
    uint8 flag_5;
    uint8 flags;
    uint8 pad_7;
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2;
    uint8 routine_3;
    uint32 field_C;
    uint32 field_10;
    uint32 code_14;   // packed start word
    uint32 rgbc_18;   // code and colour
    sint16 pos_1C[3]; // position (x, y, z): the player's joint 11 or 14 (func_80047EC8)
    uint8 field_22;
    uint8 field_23;
    uint16 field_24;
    uint16 field_26;
    W48_89_LINES lines_28; // 0x28
} W48_89_WORK;             // 0x48 bytes

typedef void (*W48_89_FUNC)(W48_89_WORK *wp);

// Kind 0x8A of the WORK_48 pool (handler func_80048354). A sprite kind stepping the 6-byte records of D_8008A730/D_8008A748.
typedef struct
{
    uint8 be_flag; // 0x00-0x0B: the header shared by every kind (see WORK_48)
    uint8 work_id; // pool kind (0x10 * pool number) | slot index
    uint8 id;      // 0x8A
    uint8 type;
    uint8 handler;
    uint8 flag_5;
    uint8 flags;
    uint8 pad_7;
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2;
    uint8 routine_3;
    sint8 work_0;
    sint8 idx_D;   // index into the records of D_8008A730/D_8008A748 (func_80048390) (Capcom: work_1)
    uint8 timer_E; // counts down per record (Capcom: work_2)
    uint8 work_3;
    uint32 field_10;
    uint32 code_14;   // packed start word
    uint32 rgbc_18;   // code and colour
    uint16 pos_1C[3]; // position (x, y, z)
    uint8 field_22;
    uint8 field_23;
    uint16 field_24;
    uint16 field_26;
    uint8 pad_28[0x20];
} W48_8A_WORK; // 0x48 bytes

typedef void (*W48_8A_FUNC)(W48_8A_WORK *wp);

// 6-byte records stepped by func_80048390 / func_80048484.
typedef struct
{
    uint16 val_0; // low byte copied to W48_8A_WORK.field_22
    uint16 val_2; // low byte copied to W48_8A_WORK.field_23
    uint8 time_4; // copied to W48_8A_WORK.timer_E
    uint8 pad_5;
} W48_8A_REC;

// Per-slot tables of effect specs, one per pool kind (func_80047148, func_80047228).
typedef struct
{
    uint32 spec; // packed counts and kinds for func_80046B34
    uint32 pad_4[3];
} SPEC_ENT;

extern W48_88_FUNC D_8008A708[]; // routine_0 dispatch table of func_80047318
extern W48_89_FUNC D_8008A724[]; // routine_0 dispatch table of func_80047D9C
extern W48_8A_FUNC D_8008A76C[]; // routine_0 dispatch table of func_80048354
extern W48_86_FUNC D_8008A358[]; // routine_0 dispatch table of func_8004569C
extern WORK48_FUNC D_8008A778[]; // handler dispatch table of func_800485E4

// Initial values copied into a WORK_48 by func_80047C84.
// The records are 8 bytes each, so the indexes below step by 8 bytes (func_80047CD8).
extern uint32 D_8008A6C8[];

extern uint8 D_8008A6CC[];
extern uint8 D_8008A6CD[];
extern uint8 D_8008A6CE[];
extern uint8 D_8008A6CF[];
extern W48_8A_REC D_8008A730[];
extern W48_8A_REC D_8008A748[];
extern W48_88_FUNC D_8008A718[]; // routine_1 dispatch table of func_800476A4
extern SLOT_OWNER D_800986D8;

// Four rows of 32 words sampled by func_80046F38 into four rows of five words (D_8009A6C0).
extern uint32 D_8008A378[4][32];

extern uint32 D_8009A6C0[4][5];
extern uint32 D_8008A578[6];
extern uint32 D_8009A710[6][4];
extern uint16 D_80097E64[];      // indexed by WORK_48.routine_2 (func_800459C0)
extern uint16 D_80097EE0[];      // indexed by WORK_48.routine_2 (func_8004678C)
extern uint16 D_80097E7A[];      // angle step per spawn count (func_80045CE8)
extern sint16 D_80097E9C[];      // indexed by WORK_48.routine_2 (func_80045CE8)
extern uint16 D_80097EA8[];      // indexed by WORK_48.routine_2 (func_80045CE8)
extern uint8 D_8008A2B0[][16];   // routine_2 choices per kind (func_80045CE8)
extern W48_87_FUNC D_8008A6A8[]; // routine_0 dispatch table of func_8004602C
extern uint16 D_80097EC0[][4];   // four halfwords per entry, indexed by routine_1 (func_8004602C)
extern uint8 D_80097EE8[];       // indexed by routine_2 (func_8004602C)
extern uint16 D_80097EEC[][4];   // [type][routine_2]: hit radius (func_80046A0C)
extern uint16 D_8008A678[][8];   // [Game_work 0x5B][routine_2] (func_80046A0C)
extern uint16 D_8008A680[][8];
extern uint16 D_80097EFA[];    // angle step per spawn count (func_80046B34)
extern sint16 D_80097F1C[];    // indexed by WORK_48.routine_2 (func_80046B34)
extern uint16 D_80097F24[];    // indexed by WORK_48.routine_2 (func_80046B34)
extern uint8 D_8008A5A8[][16]; // routine_2 choices per kind (func_80046B34)
extern uint8 D_8009A5A0[];
extern uint8 D_8009A5D0[];
extern uint8 D_8009A600[];
extern uint8 D_8009A630[];
extern uint8 D_8009A660[];
extern SPEC_ENT **D_80098844;
extern SPEC_ENT **D_8009884C;
extern SPEC_ENT **D_80098928;
extern SPEC_ENT **D_8009892C;
extern HIT_ENT D_8008A618[][4]; // [type][routine_2] (func_8004622C); splat's D_8008A622 is [0][0].max_A
extern HIT_ENT D_8008A310[];    // indexed by routine_2 (func_80045750)

#endif // CODE_800456D8_H
