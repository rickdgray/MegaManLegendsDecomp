#ifndef CODE_80043F34_H
#define CODE_80043F34_H

// code_80043F34.c's subsystem (not identified yet; rename with the file). Its objects are the
// WORK_48 pool slots of code_8002E7A8.h.

#include "common.h"
#include "code_8002E7A8.h"

// Kind 0x80 of the WORK_48 pool (handler func_80043F34). A model kind; func_80043F70 spawns two more of it.
typedef struct
{
    uint8 be_flag; // 0x00-0x0B: the header shared by every kind (see WORK_48)
    uint8 work_id; // pool kind (0x10 * pool number) | slot index
    uint8 id;      // 0x80
    uint8 type;
    uint8 handler;
    uint8 flag_5;
    uint8 flags;
    uint8 pad_7;
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2; // also a value: the colour's fade level (func_8004441C)
    uint8 routine_3; // also a counter: the spin, RotMatrixY(++routine_3 << 7) (func_8004441C)
    sint8 sound_C;   // nonzero: func_80043F70 plays sound 0xA1 after the init (Capcom: work_0)
    sint8 size_D;    // column of D_8008A138 (func_80043F70) and index into D_80097DDC, the size (Capcom: work_1)
                     // passed to func_800341BC (func_800441CC)
    sint8 variant_E; // index into D_80097DE0 (the model id), nonzero sets bit 7 of be_flag (Capcom: work_2)
                     // (func_80043F70); 0 or 1 selects func_800441CC's func_800341BC call
    sint8 level_F;   // nonzero in variant 0, type 6: adds 0x20/0x30/0x40 to Player_work's owner (Capcom: work_3)
    uint32 field_10;
    uint8 *data_14;  // model data of the EBD entry, set by Model_work_init
    MATRIX mtx;      // 0x18: rotation and scale (diagonal = pos_38.pad)
    SVECTOR pos_38;  // 0x38: position (x, y = height, z)
    uint32 rgbc_40;  // 0x40: code and colour
    sint16 hw_44[2]; // set from D_8008A138 (func_80043F70); func_8004441C adds [1] to [0], and
                     // [0] to pos_38.pad (the scale)
} W48_80_WORK;       // 0x48 bytes

typedef void (*W48_80_FUNC)(W48_80_WORK *wp);

// Per-size_D scale limits of func_8004441C (type 0, 1 and 3; D_8008A1C8 uses only limit)
typedef struct
{
    sint16 limit; // the scale under which the object ends
    sint16 speed; // hw_44[0] once the scale shrinks
    sint16 high;  // above it the colour stays full
    sint16 field_6;
} W48_80_SCALE;

// The same for type 2: past limit, routine_2 grows by step each frame (fading the colour)
typedef struct
{
    sint16 limit;
    uint8 step;
    uint8 pad_3;
    sint16 field_4[2];
} W48_80_FADE;

// Kind 0x81 of the WORK_48 pool (handler func_8004495C). A model kind.
typedef struct
{
    uint8 be_flag; // 0x00-0x0B: the header shared by every kind (see WORK_48)
    uint8 work_id; // pool kind (0x10 * pool number) | slot index
    uint8 id;      // 0x81
    uint8 type;
    uint8 handler;
    uint8 flag_5;
    uint8 flags;
    uint8 pad_7;
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2;
    uint8 routine_3; // also a timer: frames left, counted down (func_80044A00)
    uint32 field_C;
    uint32 field_10;
    uint8 *data_14; // model data of the EBD entry, set by Model_work_init
    MATRIX mtx;     // 0x18: rotation and scale (diagonal = pos_38.pad)
    SVECTOR pos_38; // 0x38: position (x, y = height, z)
    uint32 rgbc_40; // 0x40: code and colour
    void *ptr_44;   // the word at 0x10 of the block the model data's word at 0x70 points to
} W48_81_WORK;      // 0x48 bytes

typedef void (*W48_81_FUNC)(W48_81_WORK *wp);

// Kind 0x82 of the WORK_48 pool (handler func_80044AB0). A sprite kind; func_80043E00 spawns it.
typedef struct
{
    uint8 be_flag; // 0x00-0x0B: the header shared by every kind (see WORK_48)
    uint8 work_id; // pool kind (0x10 * pool number) | slot index
    uint8 id;      // 0x82
    uint8 type;
    uint8 handler;
    uint8 flag_5;
    uint8 flags;
    uint8 pad_7;
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2; // also a value: the step (1..5) indexing func_80044BA0's per-step tables
    uint8 routine_3; // also a timer: frames left in the step, from D_8008A240 (func_80044BA0)
    sint8 work_0;    // set by the spawner (func_80043E00)
    uint8 work_1;    // 0D
    uint8 work_2;    // 0E
    uint8 work_3;    // 0F
    uint32 field_10;
    uint32 code_14;   // packed start word
    uint32 rgbc_18;   // code and colour
    uint16 pos_1C[3]; // position (x, y, z)
    uint8 field_22;
    uint8 field_23;
    uint16 field_24;
    uint16 field_26;
    uint8 pad_28[0x20];
} W48_82_WORK; // 0x48 bytes

typedef void (*W48_82_FUNC)(W48_82_WORK *wp);

// Kind 0x83 of the WORK_48 pool (handler func_80044C58). A sprite kind; func_80037890 spawns it.
typedef struct
{
    uint8 be_flag; // 0x00-0x0B: the header shared by every kind (see WORK_48)
    uint8 work_id; // pool kind (0x10 * pool number) | slot index
    uint8 id;      // 0x83
    uint8 type;
    uint8 handler;
    uint8 flag_5;
    uint8 flags;
    uint8 pad_7;
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2;
    uint8 routine_3; // also a timer: frames left, reloaded from D_80097DE4[type] (func_80044C94)
    uint32 field_C;
    uint32 field_10;
    uint32 code_14;   // packed start word
    uint32 rgbc_18;   // code and colour
    uint16 pos_1C[3]; // position (x, y, z)
    uint8 field_22;
    uint8 field_23;
    uint16 field_24;
    uint16 field_26;
    uint8 pad_28[0x20];
} W48_83_WORK; // 0x48 bytes

typedef void (*W48_83_FUNC)(W48_83_WORK *wp);

// Kind 0x84 of the WORK_48 pool (handler func_80045074). A sprite kind; func_80043740 spawns it.
typedef struct
{
    uint8 be_flag; // 0x00-0x0B: the header shared by every kind (see WORK_48)
    uint8 work_id; // pool kind (0x10 * pool number) | slot index
    uint8 id;      // 0x84
    uint8 type;
    uint8 handler;
    uint8 flag_5;
    uint8 flags;
    uint8 pad_7;
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2; // also a value: the step indexing D_8008A278 (func_80045170)
    uint8 routine_3; // also a timer: frames left in the step, from D_8008A278 (func_80045170)
    sint8 work_0;
    uint8 work_1; // 0D
    uint8 work_2; // 0E
    uint8 work_3; // 0F
    uint32 field_10;
    uint32 code_14;   // packed start word
    uint32 rgbc_18;   // code and colour
    uint16 pos_1C[3]; // position (x, y, z)
    uint8 field_22;
    uint8 field_23;
    uint16 field_24;
    uint16 field_26;
    uint8 pad_28[0x20];
} W48_84_WORK; // 0x48 bytes

typedef void (*W48_84_FUNC)(W48_84_WORK *wp);

// Kind 0x85 of the WORK_48 pool (handler func_80045238). A sprite kind: add is added to spd, and spd to pos_1C, each frame.
typedef struct
{
    uint8 be_flag; // 0x00-0x0B: the header shared by every kind (see WORK_48)
    uint8 work_id; // pool kind (0x10 * pool number) | slot index
    uint8 id;      // 0x85
    uint8 type;
    uint8 handler;
    uint8 flag_5;
    uint8 flags;
    uint8 pad_7;
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2; // also a value: the brightness, counted down from 0x10 into rgbc_18
    uint8 routine_3;
    uint32 field_C;
    uint32 field_10;
    uint32 code_14;   // packed start word
    uint32 rgbc_18;   // code and colour
    uint16 pos_1C[3]; // position (x, y, z)
    uint8 field_22;
    uint8 field_23;
    uint16 field_24;
    uint16 field_26;
    SVECTOR add; // 0x28: acceleration
    SVECTOR spd; // 0x30: speed
    uint8 pad_38[8];
    uint32 dir_40; // 0x40: direction of the speed (rsin/rcos, func_80045400); 0xFFFF: none
    uint32 field_44;
} W48_85_WORK; // 0x48 bytes

typedef void (*W48_85_FUNC)(W48_85_WORK *wp);

// Start values of a W48_85_WORK for func_80045274, indexed by type (bits 0-3)
typedef struct
{
    uint32 field_14;
    uint32 field_18;
    uint8 field_22;
    uint8 field_23;
    uint8 field_24; // used when type < 0x10; otherwise field_24 is 0x40
    uint8 routine_8;
} INIT_48;

extern W48_80_FUNC D_8008A208[]; // routine_0 dispatch table of func_80043F34
extern W48_80_FUNC D_8008A214[]; // routine_1 dispatch table of func_800441CC
extern W48_81_FUNC D_8008A220[]; // routine_0 dispatch table of func_8004495C
extern W48_82_FUNC D_8008A250[]; // routine_0 dispatch table of func_80044AB0
extern W48_83_FUNC D_8008A258[]; // routine_0 dispatch table of func_80044C58
extern W48_84_FUNC D_8008A288[]; // routine_0 dispatch table of func_80045074
extern W48_85_FUNC D_8008A290[]; // routine_0 dispatch table of func_80045238

// Two halfwords per entry, indexed by routine_0 - 5; func_80045650 stores them as bytes into
// W48_85_WORK.field_22 and field_23 (splat labels the second halfword D_80097E0A)
extern uint16 D_80097E08[][2];

// Per-step tables of func_80044BA0, indexed by routine_2 (1..5): two bytes for W48_82_WORK.field_22/23
// (splat labels the second byte D_8008A235) and the step's duration
extern uint8 D_8008A234[][2];
extern uint8 D_8008A240[];
extern uint8 D_8008A248[]; // W48_82_WORK.field_24 of func_80044BA0, indexed by routine_1 (frame count)

// The same per-step tables for func_800450B0/func_80045170 (kind 0x84): bytes for field_22/23
// (splat labels the second byte D_8008A26D), durations, and a scale for field_24 (times
// work_0, >> 4) indexed by routine_1
extern uint8 D_8008A26C[][2];
extern uint8 D_8008A278[];
extern uint8 D_8008A280[];

extern INIT_48 D_80097DF0[]; // 2 entries; func_80045274

// Slot owner passed to func_800341BC by func_800441CC (.sdata 0x800986C0, 16 bytes, in a
// file not identified yet)
extern SLOT_OWNER D_800986C0;

// W48_80_WORK.hw_44[0] and [1] of func_80043F70, [type & 0xF][size_D] (splat labels the
// second halfword D_8008A13A)
extern uint16 D_8008A138[][4][2];

extern W48_80_SCALE D_8008A1A8[]; // 4 entries, by size_D; splat labels speed D_8008A1AA and
                                  // the rest D_8008A1AC
extern W48_80_SCALE D_8008A1C8[]; // 4 entries, by size_D
extern W48_80_FADE D_8008A1E8[];  // 4 entries, by size_D; splat labels step D_8008A1EA

#endif
