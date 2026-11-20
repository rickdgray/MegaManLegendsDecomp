#ifndef ST1C_H
#define ST1C_H

#include "common.h"
#include "stage_common/stage.h"

// A 0x3C0-byte work slot as this stage's objects use it (STAGE_OBJ, with the words at +0x64..+0x74).
typedef struct
{
    sint8 flags_0;                          // 00
    uint8 reserved01;                       // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 timer_C;                          // 0C
    uint8 reserved0D[3];                    // 0D
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR_W rotation;               // 54
    STCOM_SVECTOR_W rotation_prev;          // 5C
    uint32 value_64;                        // 64
    uint8 reserved68[8];                    // 68
    uint32 value_70;                        // 70
    uint32 value_74;                        // 74
    void *data_78;                          // 78
    uint8 reserved7C[0xDC];                 // 7C
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x260];               // 160
} ST1C_OBJ;

// A 0x50-byte slot (func_80031734) as this stage's objects use it (STCOM21_WORK's layout).
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01;      // 01
    uint8 kind_2;          // 02
    uint8 variant_3;       // 03
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 reserved0B;      // 0B
    sint8 index_C;         // 0C
    uint8 reserved0D[3];   // 0D
    void *model_10;        // 10
    uint8 reserved14[4];   // 14
    STCOM_MATRIX matrix;   // 18
    STCOM_SVECTOR pos_38;  // 38
    uint32 color_40;       // 40
    uint8 reserved44[0xC]; // 44
} ST1C_OBJ50;

void func_8010343C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8010446C[];
void func_80103400(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80104478[];
void func_8010345C(STAGE_OBJ *wp);

extern STAGE_SLOT_FUNC *D_80103650[];
extern STAGE_SLOT_FUNC *D_80103790[];
extern STAGE_SLOT_FUNC D_801037A4[];
extern STAGE_SLOT_FUNC D_801037A8[];
extern STAGE_SLOT_FUNC D_801037E0[];
extern STAGE_SLOT_FUNC D_801037E4[];
extern STAGE_ROOM_FUNC *D_80103C84[];
void func_8010001C(void);
void func_801001E0(void);

extern void *D_801038C0[];       // spawn list by room
extern void *D_80103940[];       // exit list by room
extern uint8 D_80103948[][0x28]; // by room (func_800371A0)
extern uint8 D_80103998[][8];    // by D_80103A18[room]
extern sint32 D_80103A18[];
void func_801001D0(void);
extern uint8 D_80103C3C[][8]; // by level (func_80100234)
extern uint8 D_80103C5C[][8]; // by level (func_801002B0)
extern uint8 D_80103C8C[];    // weights by scene flag (func_80100360; indexed from 0x38)
void func_8001DF10(void *entry);
void func_8001E20C(sint32 arg);
uint8 func_80100360(void);
extern uint8 D_80104460[];
void func_80102E3C(ST1C_OBJ *wp);
uint8 func_80102DF8(void);
void func_80102F50(ST1C_OBJ *wp);
void func_80102FD0(ST1C_OBJ *wp);
void func_80103178(ST1C_OBJ *wp);
void Sce_flag_off(sint32 flag);
void func_8001E3F0(sint32 arg);
extern STCOM_SVECTOR D_80104484[]; // position and y rotation by value_C (func_801034C8)
extern uint8 D_801044C4[];         // variant by value_C
extern uint8 D_801044CC[];
void func_801034C8(ST1C_OBJ50 *wp);

#endif // ST1C_H
