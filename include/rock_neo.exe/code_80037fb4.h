#ifndef ROCK_NEO_CODE_80037FB4_H
#define ROCK_NEO_CODE_80037FB4_H

#include "common.h"
#include "player.h"

// Camera vector block: 16 bytes copied as four words.
typedef struct
{
    sint32 x, y, z, w;
} CAM_VEC;

typedef struct
{
    sint16 x, y, z;
} CAM_DELTA;

// A lone word that GCC treats as a struct member, not a plain scalar.
typedef struct
{
    sint32 value;
} CAM_WORD;

// GTE-style rotation angles and matrix, local view.
typedef struct
{
    sint16 vx;
    sint16 vy;
    sint16 vz;
    sint16 pad;
} CAM_ROT;

typedef struct
{
    sint16 m[3][3];
    sint32 t[3];
} CAM_MATRIX;

#define CAM_MATRIX_A ((CAM_MATRIX *)0x1F800008)
#define CAM_MATRIX_C ((CAM_MATRIX *)0x1F8000C0)
#define CAM_MATRIX_E ((CAM_MATRIX *)0x1F8000E0)
#define CAM_VECTOR_F ((sint32 *)0x1F8000F4)
#define CAM_SHIFT    (*(uint8 *)0x1F800074)
#define CAM_POS_X    (*(sint16 *)0x1F800028)
#define CAM_POS_Y    (*(sint16 *)0x1F80002A)
#define CAM_POS_Z    (*(sint16 *)0x1F80002C)
#define CAM_VIEW     ((sint32 *)0x1F800030)

extern CAM_ROT D_800A3A10;
extern sint16 D_800A3A12;
extern sint16 D_800A3A14;
extern sint32 D_800A39F0;
extern sint32 D_800A39F4;
extern sint32 D_800A39F8;

extern void RotMatrixYXZ(CAM_ROT *r, CAM_MATRIX *m);
extern void TransposeMatrix(CAM_MATRIX *m0, CAM_MATRIX *m1);
extern void ApplyMatrixLV(CAM_MATRIX *m, sint32 *v0, sint32 *v1);

extern uint8 D_800A3959;
extern uint8 D_800A395A;
extern uint8 D_800A395B;
extern uint8 D_800A395F;
extern uint8 D_800A3960;
extern sint8 D_800A3961;
extern sint8 D_800A3962;
extern sint32 D_800A3964;
extern sint32 D_800A3968;
extern sint32 D_800A396C;
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
extern CAM_VEC D_800A39A0;
extern CAM_VEC D_800A39B0;
extern sint32 D_800A39B4;
extern CAM_VEC D_800A39C0;
extern CAM_WORD D_800A39C4;
extern CAM_WORD D_800A39C8;
extern CAM_VEC D_800A39D0;
extern CAM_WORD D_800A39E0;
extern CAM_WORD D_800A39E4;
extern CAM_WORD D_800A39E8;

extern sint32 SquareRoot0(sint32 v);
extern sint32 rsin(sint32 a);
extern sint32 rcos(sint32 a);
extern sint32 ratan2(sint32 x, sint32 y);

// Small data ($gp-addressed in retail; not yet owned by this file).
extern sint32 D_80097D2C;
extern sint32 D_80097D6C;
extern uint32 D_80097D70;
extern sint32 D_80098670;
extern sint32 D_80098674;
extern uint32 *D_8009869C[8];
extern sint32 D_80097D28;
extern sint32 D_80097D30;
extern sint32 D_80097D34;
extern sint32 D_80097D38;
extern sint32 D_80097D3C;
extern sint32 D_80097D40;
extern sint32 D_80097D44;
extern sint32 D_80097D48;
extern sint32 D_80097D4C;
extern sint32 D_80097D50;
extern sint32 D_80097D54;
extern uint8 D_80097D58[];
extern sint32 D_80098668;
extern sint32 D_8009866C;
extern sint32 D_80098694;
extern sint32 D_80098698;
extern sint32 D_8009A598[];
extern sint32 D_80098678;
extern sint32 D_8009867C;
extern sint32 D_80098680;
extern CAM_VEC D_800A3A00;
extern sint32 D_80098688;
extern sint32 D_8009868C;
extern sint32 D_80098690;

// Scene_work's routine bytes (SCENE_WORK in scene.h, which this file can't include).
typedef struct
{
    uint8 routine_0;
    uint8 routine_1;
    uint8 reserved02[0xA6];
} CODE37_SCENE;
extern CODE37_SCENE Scene_work;
extern uint8 D_800A395C;
extern uint8 D_800A395D;
extern uint8 D_800A395E;

// Camera work block (0xE4 bytes from D_800A3958) and its saved copy.
typedef struct
{
    uint32 w[0x39];
} CAM_SAVE;

// Field view of the same camera block (D_800A3958).
typedef struct
{
    uint8 routine_0;    // 00
    uint8 mode_1;       // 01
    uint8 flag_2;       // 02
    uint8 flag_3;       // 03
    uint8 flag_4;       // 04
    uint8 flag_5;       // 05
    uint8 flag_6;       // 06
    uint8 flag_7;       // 07
    uint8 flag_8;       // 08
    sint8 step_9;       // 09
    sint8 angle_A;      // 0A
    uint8 reserved0B;   // 0B
    sint32 dist_0C;     // 0C
    sint32 rot_10;      // 10
    sint32 height_14;   // 14
    sint32 value_18;    // 18
    sint32 value_1C;    // 1C
    sint32 value_20;    // 20
    sint32 dist_24;     // 24
    sint32 rot_28;      // 28
    sint32 height_2C;   // 2C
    sint32 value_30;    // 30
    sint32 value_34;    // 34
    sint32 value_38;    // 38
    sint32 dist_3C;     // 3C
    sint32 rot_40;      // 40
    sint32 height_44;   // 44
    CAM_VEC pos_48;     // 48
    CAM_VEC vec_58;     // 58
    CAM_VEC pos_68;     // 68
    CAM_VEC vec_78;     // 78
    CAM_VEC pos_88;     // 88
    CAM_VEC pos_98;     // 98
    CAM_VEC vec_A8;     // A8
    CAM_ROT rot_B8;     // B8
    uint32 work_C0[8];  // C0
    PL_WORK *target_E0; // E0
} CAM_WORK;

// The block as declared. Most code reaches it through the Camera_work cast view (each field
// address folded to its own lui/%lo); the angle setup reaches rot_B8 through the declaration,
// which keeps &rot_B8 in one register for both the vx store and the RotMatrixYXZ argument.
typedef union
{
    CAM_SAVE save;
    CAM_WORK work;
} CAM_BLOCK;

#define Camera_work (*(CAM_WORK *)&D_800A3958)

extern CAM_BLOCK D_800A3958;
extern CAM_SAVE D_8009A478;

sint32 func_800399EC(uint32 *cmd);
void func_80039A38(void *data);
void func_800397E8(void);
void func_800177CC(void *start, void *end);
void func_80039E50(void);
void func_800392CC(void);
void func_80039A60(void);
void func_80039FFC(CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3);

void func_80037FB4(CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80038370(CAM_VEC *vec, CAM_VEC *target);

extern uint16 D_800C0D92;
extern uint8 D_80097D5C[];
extern PL_HEIGHT_INFO D_80097D60;
extern sint16 D_80098660;
extern sint16 D_80098662;
extern sint16 D_80098664;
void func_8001E550(void);
sint32 func_8003A218();
sint32 func_8003A154(sint32 arg0, sint32 arg1, sint32 arg2);
sint32 func_80049C54(PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *prev, PL_HEIGHT_INFO *info,
                     sint32 kind);

#endif
