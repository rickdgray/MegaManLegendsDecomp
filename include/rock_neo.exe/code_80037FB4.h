#ifndef CODE_80037FB4_H
#define CODE_80037FB4_H

// code_80037FB4.c's subsystem (not identified yet; it contains Swing_Camera2, so possibly the
// camera; rename with the file).

#include "common.h"
#include "psyq/libgte.h"

// One of the camera block's five parameter slots (func_80039BBC ... func_80039CEC set one each,
// with the matching CAMERA_WORK.pos[] entry).
typedef struct
{
    sint32 field_0; // 0x200 by default
    sint32 ang;     // angle (0..0xFFF, compared mod 0x1000 by func_8003A154 / func_8003A218)
    sint32 field_8; // 0x30 by default
} CAM_PARAM;

// The camera block at 0x800A3958 (0xE4 bytes; func_80039A60 saves and restores it whole as
// D_8009A478). Capcom's code waits on Camera_work.routine_3 after Swing_Camera2 (check_swing_camera
// in disc/tcrf.txt), which is the byte at 0x800A395F. Code that is not yet converted still uses the
// separate D_800A39xx externs below for the same bytes.
typedef struct
{
    uint8 unk0;
    uint8 mode_1; // 0 after func_80039820, 1 from func_80039FFC, 2 from func_80039E50/func_8003A264
    uint8 unk2;   // set with unk3 by func_80039BA4
    uint8 unk3;
    uint8 routine_0; // overlays set 1, func_8001E6C0 3
    uint8 routine_1; // set to 0/4/6 by the command queue (func_80039A60)
    uint8 routine_2;
    uint8 routine_3; // camera swing: set by Swing_Camera2, 0 when it has died down
    uint8 unk8;
    sint8 unk9; // -8 (func_800394AC) or -4
    sint8 unkA; // -1 when unused (func_8003A13C tests >= 0)
    uint8 padB;
    CAM_PARAM param[5]; // 0x0C
    VECTOR pos[5];      // 0x48: pos[1].vy is 0x96 after the resets
    VECTOR pos_98;      // 0x98: func_800384F0's camera position (also in Scratch_cam_pos)
    VECTOR pos_A8;      // 0xA8: the previous pos_98 (func_80037FB4 saves it before updating)
    SVECTOR ang;        // 0xB8: rotation func_800384F0 builds the view matrix from
    uint8 unkC0[0x24];
} CAMERA_WORK;

// The block as declared: its fields, or the whole block as words.
typedef union
{
    CAMERA_WORK work;
    uint32 words[0x39];
} CAMERA_BLOCK;

extern CAMERA_BLOCK D_800A3958;
extern CAMERA_BLOCK D_8009A478; // saved copy (func_80039A60)

// Capcom's name for the block (Camera_work.routine_3 in check_swing_camera). Most code reaches
// the fields through this cast, which gives every access its own lui; the direct form
// D_800A3958.work.x lets GCC keep the first field's address in a register (func_80039D38,
// func_800384F0).
#define Camera_work (*(CAMERA_WORK *)&D_800A3958)

// Fields of D_800A3958 as separate symbols, for the code not yet converted to CAMERA_WORK.
extern uint8 D_800A395A;
extern uint8 D_800A395B;
extern uint8 D_800A395C; // set to 3 by func_8001E6C0
extern uint8 D_800A395F;
extern uint8 D_800A3960;
extern sint8 D_800A3962;
extern sint32 D_800A396C;
extern uint8 D_800A3959;
extern sint32 D_800A3964;
extern sint32 D_800A39B4;
extern VECTOR D_800A39A0;
extern VECTOR D_800A39B0;
extern VECTOR D_800A39C0;
extern VECTOR D_800A39D0;
extern VECTOR D_800A39E0;
extern sint32 D_800A3968;
extern sint32 D_800A3970;
extern sint32 D_800A3974;
extern sint32 D_800A3978;
extern sint32 D_800A397C;
extern sint32 D_800A3980;
extern sint32 D_800A3984;
extern sint32 D_800A3988;
extern sint32 D_800A398C;
extern sint32 D_800A3990;
extern sint32 D_800A3994;
extern sint32 D_800A3998;
extern sint32 D_800A399C;
extern uint32 *D_8009869C[8]; // camera command queue: pointers to command words (func_80039A60)

void func_80037FB4(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80038370(VECTOR *arg0, VECTOR *arg1); // arg1: point to look at (func_8001E550)
void func_80038324(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_800384A4(VECTOR *arg0, VECTOR *arg1);
void func_80039BBC(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80039C08(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80039C54(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80039CA0(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80039CEC(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_800384F0(VECTOR *pos, sint32 ang_y, sint32 ang_x); // view matrix from pos and angles
void func_800394AC(void);
void func_800395E8(void);
// Sets the camera's field_8; its only caller (player's func_8003EEC0) also passes 0x15E, unused.
void func_80039630(sint32 field_8, sint32 unused);
void func_80039820(void);       // resets the camera behind the player
void func_80039A60(void);       // runs one command of the D_8009869C queue
void func_80039D38(SVECTOR *d); // moves pos[2] and pos[4] by d
void func_80039FAC(VECTOR *pos, sint32 field_0, sint32 ang, sint32 field_8);
void func_80039FFC(VECTOR *pos, sint32 field_0, sint32 ang, sint32 field_8);
sint32 func_8003A13C(void); // D_800A3962 >= 0
sint32 func_8003A154(sint32 a, sint32 lim, sint32 step);
sint32 func_8003A218(sint32 arg0);
void func_8003A264(void);
void func_80039E50(void);
// Returns nothing; declared sint32 for the same reason as Money_add (func_80055C1C needs it).
sint32 func_80039E18(void);
void func_800398E0(sint32 arg0);
// Shakes the camera: power scaled down linearly from distance near (full) to far (none) between
// pos and the camera (Capcom: Swing_Camera2(4, 512, 1024, &Player_work[0].pos)).
void Swing_Camera2(sint32 power, uint32 near, uint32 far, SVECTOR *pos);
sint32 func_800399EC(uint32 *cmd);
void func_80039A38(uint32 *cmd); // forwarded to func_800399EC
sint32 func_80039B80(void);      // D_800A396C, or 0 while D_800A3960 is 0

#endif // CODE_80037FB4_H
