#ifndef STCOM21_H
#define STCOM21_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The 0x50-byte work slot (func_80031734) of the objects in stcom21: a villager who talks
// (0000..0E48), a treasure chest whose lid opens (0E88..1908) and a smaller box (19D0..1DDC).
typedef struct STCOM21_WORK STCOM21_WORK;

// A matrix whose identity setup writes it as eight words.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
} STCOM21_MATRIX;

#define STCOM21_IDENTITY(mw)                                                                       \
    ((mw)->words[0] = 0x1000, (mw)->words[1] = 0, (mw)->words[2] = 0x1000, (mw)->words[3] = 0,     \
     (mw)->words[4] = 0x1000, (mw)->words[5] = 0, (mw)->words[6] = 0, (mw)->words[7] = 0)

struct STCOM21_WORK
{
    uint8 flags_0;         // 00
    uint8 index_1;         // 01: pool id and slot
    uint8 kind_2;          // 02
    uint8 variant_3;       // 03
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 value_B;         // 0B: message (villager), lid frame (chest)
    sint8 value_C;         // 0C: flags (villager), scene flag - 0x400 (chest)
    sint8 value_D;         // 0D: contents' kind
    sint8 value_E;         // 0E: timer (villager), contents (chest)
    sint8 value_F;         // 0F: rotation
    void *model_10;        // 10
    uint8 reserved14[4];   // 14
    STCOM21_MATRIX matrix; // 18
    STCOM_SVECTOR pos_38;  // 38: pad holds the spawn's scene flag
    uint32 color_40;       // 40
    union
    {
        sint32 flag;          // the scene flag that must be set (chests)
        STCOM_EFFECT *effect; // the effect it waits for (villager)
        STCOM21_WORK *chest;  // the chest a lid belongs to
    } u_44;
    STCOM_FIXED y_48; // 48: hit result bits; a lid's height
    sint32 speed_4C;  // 4C
};

typedef void (*STCOM21_FUNC)(STCOM21_WORK *wp);

// A 0x3C0-byte work slot (func_80031418) as stcom21_func_1908 sets it up.
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 index_1;                     // 01
    uint8 kind_2;                      // 02
    uint8 value_3;                     // 03
    uint8 handler_4;                   // 04
    uint8 reserved05[0xF];             // 05
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x28];            // 2C
    STCOM_SVECTOR rotation;            // 54
} STCOM21_OBJ;

// An offset from the villager, per direction.
typedef struct
{
    sint16 x, z;
} STCOM21_OFFSET;

// Player_work's byte at +0xA7 (sign bit: the message window is done).
#define STCOM21_PL_A7(pl) (*((sint8 *)(pl) + 0xA7))

extern STCOM21_FUNC stcom21_D_0000[];   // villager: routine_0
extern STCOM21_FUNC stcom21_D_000C[];   // villager: routine_1 (talking)
extern uint32 stcom21_D_001C[];         // villager's model
extern STCOM21_OFFSET stcom21_D_0028[]; // villager: where its effect appears, by direction
extern STCOM21_FUNC stcom21_D_0038[];   // chest: routine_0
extern STCOM21_FUNC stcom21_D_0044[];   // chest: by variant_3
extern STCOM21_FUNC stcom21_D_0050[];   // chest: routine_1
extern uint32 stcom21_D_005C[];         // chest's model
extern uint16 stcom21_D_0068[];         // lid angles
extern STCOM21_FUNC stcom21_D_0078[];   // box: routine_0
extern uint32 stcom21_D_0088[];         // box's model

uint8 stcom21_func_0CE8(STCOM21_WORK *wp, STCOM_PL_WORK *pl);
sint32 stcom21_func_0D34(STCOM21_WORK *wp);
void stcom21_func_0D9C(void);
void stcom21_func_0E48(uint8 index, uint8 n);
void stcom21_func_1524(STCOM21_WORK *wp);
uint8 stcom21_func_1880(STCOM21_WORK *wp);
void stcom21_func_1908(STCOM21_WORK *wp);
uint8 stcom21_func_1DDC(STCOM21_WORK *wp);

// ROCK_NEO.EXE.
extern uint8 *D_8008CACC[];
extern uint8 *D_8008CE00;
extern uint8 *D_8008CE04;
extern uint8 *D_8008CE08;
extern uint8 *D_8008CE0C;
extern uint8 *D_8008CE3C;
sint32 Sce_flag_test(sint32 flag);
void Sce_flag_off(sint32 flag);
sint32 MojiTaskExec(sint32 arg0, uint8 *script, sint32 arg2);
STCOM21_WORK *func_80031734(void);
void func_80031A4C(STCOM21_WORK *wp);
STCOM21_OBJ *func_80031418(void);
sint32 func_80031EF0(STCOM_SVECTOR *pos, sint32 angle, sint32 range, STCOM_SVECTOR *target,
                     sint32 target_angle, sint32 target_range);
sint32 func_8004324C(STCOM_PL_WORK *pl);
sint32 Money_check(sint32 a0);
void Money_add(sint32 a0, sint32 a1, sint32 a2);
void func_80043340(sint32 a0, sint32 a1);
void func_8001E390(sint32 a0);
void func_8001E3F0(sint32 a0);
STCOM_MATRIX *RotMatrixX(sint32 r, STCOM_MATRIX *m);
STCOM_MATRIX *RotMatrixY(sint32 r, STCOM_MATRIX *m);
STCOM_MATRIX *RotMatrixZ(sint32 r, STCOM_MATRIX *m);

#endif // STCOM21_H
