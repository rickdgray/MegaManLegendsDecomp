#ifndef STCOM22_H
#define STCOM22_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The 0x50-byte work slot (func_80031734) of the objects in stcom22, by type: a lift that
// carries the player (0, 003C..0EA8), a breakable crate (1 and 2, 0F00..13F0), a lever (4,
// 1434..1730), a gate and its switch (6 and 7, 1758..1ED0).
typedef struct STCOM22_WORK STCOM22_WORK;

// What the objects keep in their matrix's translation, reached through a pointer.
typedef struct
{
    sint32 value;      // 2C: the lift's stop height; a scale
    STCOM_SVECTOR rot; // 30
} STCOM22_CTL;

// A matrix whose identity setup writes it as eight words. Its translation is not used: the
// rotation sits in it at +0x30, after a value at +0x2C.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
    struct
    {
        sint16 m[3][3];
        sint16 pad;
        STCOM22_CTL ctl; // 2C
    } f;
} STCOM22_MATRIX;

#define STCOM22_IDENTITY(mw)                                                                                                               \
    ((mw)->words[0] = 0x1000, (mw)->words[1] = 0, (mw)->words[2] = 0x1000, (mw)->words[3] = 0, (mw)->words[4] = 0x1000,                    \
     (mw)->words[5] = 0, (mw)->words[6] = 0, (mw)->words[7] = 0)

struct STCOM22_WORK
{
    uint8 be_flag;         // 00
    uint8 work_id;         // 01: pool id and slot
    uint8 id;              // 02
    uint8 type;            // 03
    uint8 reserved04;      // 04
    uint8 value_5;         // 05: lift: position (low nibble), kind (high nibble)
    uint8 reserved06[2];   // 06
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 value_B;         // 0B
    sint8 value_C;         // 0C
    sint8 value_D;         // 0D
    sint8 value_E;         // 0E: lift speed
    sint8 value_F;         // 0F
    void *model_10;        // 10
    uint8 reserved14[4];   // 14
    STCOM22_MATRIX matrix; // 18
    STCOM_SVECTOR pos_38;  // 38
    uint32 color_40;       // 40
    uint8 reserved44[4];   // 44
    union
    {
        sint32 hit;         // hit result bits
        STCOM22_WORK *gate; // the switch's gate
    } u_48;
    uint8 reserved4C[4]; // 4C
};

typedef void (*STCOM22_FUNC)(STCOM22_WORK *wp);

// Player_work as the lift sees it: the player's carried position at +0x428.
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 work_id;                     // 01
    uint8 reserved02[6];               // 02
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 reserved0A[0xA];             // 0A
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x28];            // 2C
    STCOM_SVECTOR rotation;            // 54
    uint8 reserved5C[0x1A];            // 5C
    sint8 value_76;                    // 76: nonzero while holding something
    uint8 reserved77[0x46];            // 77
    uint8 flags_bd;                    // BD
    uint8 reservedBE[2];               // BE
    void *value_C0;                    // C0: the work slot it holds
    uint8 reservedC4[0xC0];            // C4
    void *target_184;                  // 184: the work slot the player is talking to
    uint8 reserved188[0x2A0];          // 188
    STCOM_FIXED_VECTOR fixed_428;      // 428
    STCOM_SVECTOR pos_438;             // 438
    STCOM_SVECTOR rot_440;             // 440
    uint8 value_448;                   // 448
} STCOM22_PL_WORK;

#define STCOM22_PL ((STCOM22_PL_WORK *)&Player_work)

// Game_work's lift heights at +0x194.
typedef struct
{
    uint8 reserved00[0x7B];  // 00
    sint8 value_7B;          // 7B
    uint8 reserved7C[0x118]; // 7C
    sint16 value_194;        // 194: set once the lift has carried the player in
    sint16 value_196;        // 196: lift 0's height
    sint16 value_198;        // 198: lift 1's height
    sint16 value_19A;        // 19A
} STCOM22_GAME_WORK;

#define STCOM22_GAME ((STCOM22_GAME_WORK *)&Game_work)

// The room-entry request at D_800C3558 (only the fields used here).
typedef struct
{
    uint8 reserved00[0x15]; // 00
    sint8 flags15;          // 15
    uint8 reserved16[2];    // 16
    uint8 fade_in;          // 18
    uint8 fade_out;         // 19
} STCOM22_ENTRY;

extern sint16 stcom22_D_0000[];       // lift: floor box for the ground height
extern uint32 stcom22_D_000C[];       // a model
extern uint32 stcom22_D_0018[];       // a model
extern STCOM22_FUNC stcom22_D_0024[]; // by type
extern STCOM22_FUNC stcom22_D_0044[]; // lift: routine_0
extern STCOM22_FUNC stcom22_D_0050[]; // lift: routine_1
extern STCOM22_FUNC stcom22_D_0068[]; // crate: routine_0
extern STCOM22_FUNC stcom22_D_0074[]; // crate: routine_1
extern STCOM22_FUNC stcom22_D_007C[]; // lever: routine_0
extern STCOM22_FUNC stcom22_D_0088[]; // lever: routine_1
extern STCOM22_FUNC stcom22_D_0094[]; // gate: routine_0
extern STCOM22_FUNC stcom22_D_00A0[]; // gate: routine_1
extern STCOM22_FUNC stcom22_D_00AC[]; // switch: routine_0

void stcom22_func_04B4(STCOM22_WORK *wp);
void stcom22_func_0FD4(STCOM22_WORK *wp);
void stcom22_func_1C5C(STCOM22_WORK *wp);

// Defined outside this file, at the same address in every stage that links it.
void func_8010D9F8(sint32 a0, sint32 a1, sint32 a2, STCOM_SVECTOR *pos);

// ROCK_NEO.EXE.
extern STCOM22_ENTRY D_800C3558;
sint32 Sce_flag_test(sint32 flag);
void Sce_flag_off(sint32 flag);
STCOM22_WORK *func_80031734(void);
void func_80031A4C(STCOM22_WORK *wp);
sint32 func_80048EA4(STCOM_SVECTOR *pos, sint16 *box, sint32 dy, sint32 kind);
void func_80052528(STCOM22_WORK *wp);
sint32 func_80031DCC(STCOM_FIXED_VECTOR *pos, sint32 angle, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_angle,
                     sint32 target_range);
sint32 Stage_map_cell_get(sint32 a0, STCOM_SVECTOR *pos);
uint32 Stage_idx_model_set(sint32 idx, uint32 key);

#endif // STCOM22_H
