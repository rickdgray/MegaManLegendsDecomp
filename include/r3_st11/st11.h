#ifndef ST11_H
#define ST11_H

#include "common.h"
#include "stage_common/stage.h"

extern STAGE_OBJ_FUNC D_8010A490[];
extern STAGE_SLOT_FUNC *D_8010945C[];
extern STAGE_SLOT_FUNC *D_80109568[];
extern STAGE_SLOT_FUNC D_80109584[];
extern STAGE_SLOT_FUNC D_80109644[];
extern STAGE_SLOT_FUNC D_80109684[];
extern STAGE_SLOT_FUNC D_801096C4[];
void func_801076A8(STAGE_OBJ *wp);
void func_801000B4(void);

extern uint8 D_80109B8C[];
extern uint8 D_80109B94[];
extern uint8 D_80109B9C[];
extern uint8 D_80109BA4[];
extern uint8 D_80109BAC[];
extern uint8 D_80109BB4[];
extern uint8 D_8010A484[];
extern uint8 D_8010E1B8[];

void Scene_obj_list_open(uint8 *);
void func_80100370(STAGE_ROOM *wp);

void func_80100428(STAGE_ROOM *wp);

void func_8010047C(STAGE_ROOM *wp);

void func_801004D0(STAGE_ROOM *wp);

void func_80100524(STAGE_ROOM *wp);

void func_801003C4(STAGE_ROOM *wp);

void func_8001DEE4(void);
void func_8001E4C4(void *a, void *b);
extern uint8 D_80109BBC[][8];
extern STAGE_ROOM_FUNC D_80109944[];
extern STAGE_ROOM_FUNC *D_80109904[];
void func_8001EB98(void *entry);
extern uint8 D_8010E1CC[];
void func_80100284(void);
void func_801002D0(void);
sint32 func_80100578(void);

extern void *D_80109768[];       // model table by room
extern void *D_80109820[];       // exit list by room
extern void *D_801097BC[];       // spawn list by room
extern uint8 D_80109824[][0x28]; // by room (func_800371A0)
extern uint8 D_8010984C[][8];    // by D_801098E4[room]
extern sint32 D_801098E4[];
void func_80107B00(STAGE_SHOT *wp);
void func_80107C78(STAGE_SHOT *wp);
void func_80107DBC(STAGE_SHOT *wp, sint32 arg);

// A copy of the special-weapon shot from r3_shl02 (its SHL_WORK) at 0x80112874: an object slot
// with ROCK_NEO's generic layout up to 0x88, then a model's draw data.
typedef struct
{
    sint8 be_flag; // 00
    uint8 work_id; // 01
    uint8 id;      // 02
    uint8 type;    // 03: 0x40 set for a shot fired by another object
    uint8 reserved04[2];
    uint8 flags; // 06
    uint8 reserved07;
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 mode_a;    // 0A
    uint8 timer_b;   // 0B
    sint8 index_c;   // 0C
    sint8 bit_d;     // 0D
    uint8 reserved0e[6];
    STCOM_SVECTOR pos;           // 14
    STAGE_FIXED_VECTOR fpos;     // 1C
    STCOM_SVECTOR old_pos;       // 2C
    STAGE_FIXED_VECTOR old_fpos; // 34
    STCOM_SVECTOR vel;           // 44
    sint16 ax, ay, az;           // 4C
    uint8 reserved52[0x12];
    sint16 rot_y; // 64
    sint16 rot_x; // 66
    uint8 reserved68[0x10];
    sint16 *box_78; // 78
    sint16 hit_7c;  // 7C
    uint8 reserved7e[0xE];
    STCOM_MATRIX mtx_8c; // 8C
    STCOM_SVECTOR mpos;  // AC: the model's position
    uint32 color_b4;     // B4
    uint8 reservedb8[0xC];
    uint32 col_c4; // C4: hit accumulator (func_8003430C)
    uint32 col_c8; // C8
} ST11_SHL;

// Player_work's signed bytes past STCOM_PL_WORK's fields.
#define ST11_PL_SBYTE(offset) (*((sint8 *)&Player_work + (offset)))

void func_800354E0(sint32 bit);
sint16 func_80039B80(void);
sint32 func_80037634(void *player, sint32 arg);
void func_801076F8(ST11_SHL *wp);

#endif // ST11_H
