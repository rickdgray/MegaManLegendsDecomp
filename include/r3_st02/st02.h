#ifndef ST02_H
#define ST02_H

#include "common.h"
#include "stage_common/stage.h"

// A scratchpad frame counter (stcom08's STCOM08_FRAME).
#define ST02_FRAME (*(uint16 *)0x1F800002)

extern void *D_801068E0[];       // model table by room (Room_model_init)
extern void *D_80106940[];       // spawn list by room
extern void *D_80106968[];       // exit list by room
extern uint8 D_80106978[][0x28]; // by room (func_800371A0)
extern uint8 D_80106A18[][8];    // by D_80106C18[room]
extern sint32 D_80106C18[];
extern STAGE_SLOT_FUNC *D_801067A4[];
extern STAGE_SLOT_FUNC *D_80106844[];
extern STAGE_SLOT_FUNC D_80106864[];
extern STAGE_SLOT_FUNC D_80106868[];
extern STAGE_SLOT_FUNC D_8010688C[];
extern STAGE_SLOT_FUNC D_801068A8[];
extern STAGE_OBJ_FUNC D_80107520[];
extern STAGE_OBJ_FUNC D_80107720[];
void func_801048C0(STAGE_FX *wp);
void func_80104A4C(STAGE_FX *wp);
void func_80104AB8(STAGE_FX *wp);
void func_80104D30(STAGE_FX *wp);
void func_80104D88(STAGE_FX *wp);
void func_80104F1C(STAGE_FX *wp);
void func_80104FE4(STAGE_FX *wp);
void func_80104FF8(STAGE_FX *wp);
extern STAGE_FX_FUNC D_80107B04[];

// A song picked by a scene flag (func_80100238); flag 0xFFFF ends the list.
typedef struct
{
    uint16 flag;
    uint8 id;
    uint8 reserved03;
} ST02_MUSIC;

typedef void (*ST02_EV_FUNC)(STAGE_EV *wp);

extern ST02_MUSIC D_80106C28[];
extern uint8 D_800989FC[]; // the room work's routine_4 (D_800989F8 + 4)
extern sint8 D_800BBB38;
extern sint8 D_800BBB70;
extern sint8 D_800BBBA8;
extern sint8 D_800BBBE0;
extern sint8 D_800BBC18;
extern sint8 D_800BBC50;
extern sint8 D_800BBC88;
extern sint16 D_800BBAB0;
extern sint16 D_800BBC00[]; // an array: GCC keeps its address in a register for a read-modify-write
extern sint16 D_800BBC02;
extern sint16 D_800BBC72;
extern sint16 D_800BBCAA;
extern sint32 D_800BBC54;
extern sint32 D_800BBC58;
extern sint32 D_800BBC8C;
extern sint32 D_800BBC90;
extern uint8 D_8010A5E0; // the screen shake: 0 off, 1 vertical, 2 horizontal
extern uint8 D_8010A5E4; // nonzero: func_8010032C tints the screen
extern uint8 D_8010A5E8;
extern uint8 D_8010A5EC;
extern uint8 D_8010A5F0;
extern uint8 D_8010A5F4;
extern STAGE_OBJ_FUNC D_801074C0[];
extern STAGE_OBJ_FUNC D_801074CC[];
extern STAGE_OBJ_FUNC D_801074D8[];
extern STAGE_OBJ_FUNC D_80107504[];
extern STAGE_OBJ_FUNC D_801076FC[];
extern STAGE_OBJ_FUNC D_80107710[];
extern STAGE_OBJ_FUNC D_80107994[];
extern STAGE_OBJ_FUNC D_801079A0[];
extern STAGE_OBJ_FUNC D_801079AC[];
extern STAGE_OBJ_FUNC D_801079BC[];
extern STAGE_OBJ_FUNC D_80107AAC[];
extern STAGE_FX_FUNC D_80107B44[];
extern ST02_EV_FUNC D_80107EA0[];
extern STAGE_MOUTH *D_801075F0[];
extern STAGE_MOUTH *D_80107614[];
extern STAGE_MOUTH *D_8010781C[];
extern STAGE_MOUTH *D_80107844[];
extern STAGE_MOUTH *D_8010A5F8[];
// The lip-sync script pointers also read and written as scalars (the same symbols): retail
// reaches them by lui/%lo there, and through their address only for the jump back (+=).
extern STAGE_MOUTH *D_8010A5F8_S __asm__("D_8010A5F8");
extern sint16 D_8010A5FC[];
extern STAGE_MOUTH *D_8010A600[];
extern STAGE_MOUTH *D_8010A600_S __asm__("D_8010A600");
extern sint16 D_8010A604[];
extern STAGE_MOUTH *D_8010A610[];
extern STAGE_MOUTH *D_8010A610_S __asm__("D_8010A610");
extern sint16 D_8010A614[];
extern STAGE_MOUTH *D_8010A618[];
extern STAGE_MOUTH *D_8010A618_S __asm__("D_8010A618");
extern sint16 D_8010A61C[];
extern STAGE_LIP_CUES D_8010A608;
extern STAGE_MOUTH_CUE D_80107644[];
extern STAGE_MOUTH_CUE D_80107688[];
void func_80100204(void);
void func_801002C8(uint8 mode);
void func_80100204(void);
void func_801002C8(uint8 mode);
void func_80102830(STAGE_OBJ *wp);
void func_801032B8(STAGE_OBJ *wp);
void func_80102C44(STAGE_OBJ *wp);
void func_80103F08(STAGE_OBJ *wp);
void func_80104550(STAGE_OBJ *wp);
void func_80106108(STAGE_EV *wp);

// Routines of this module (parameter types from their bodies and callers).
void func_80100950(STAGE_ROOM *wp);
void func_801022CC(STAGE_OBJ *wp);
void func_80100E74(STAGE_ROOM *wp);
void func_80102EA4(STAGE_OBJ *wp);
void func_80103C28(STAGE_OBJ *wp);
void func_801009F4(STAGE_ROOM *wp);
void func_801031F8(STAGE_OBJ *wp);
void func_80103818(STAGE_OBJ *wp);
void func_80100830(STAGE_ROOM *wp);
void func_801008D8(STAGE_ROOM *wp);
void func_80100914(STAGE_ROOM *wp);
void func_8010189C(STAGE_ROOM *wp);
void func_801022F0(STAGE_OBJ *wp);
void func_80102DDC(STAGE_OBJ *wp);
void func_80102ED4(STAGE_OBJ *wp);
void func_801031B8(STAGE_OBJ *wp);
void func_80103BE8(STAGE_OBJ *wp);
void func_80103C58(STAGE_OBJ *wp);
void func_801014BC(STAGE_ROOM *wp);
void func_80103230(STAGE_OBJ *wp);
void func_801037D4(STAGE_OBJ *wp);
void func_801028C8(STAGE_OBJ *wp);
void func_8010303C(STAGE_OBJ *wp);
void func_80103088(STAGE_OBJ *wp);
void func_801038E0(STAGE_OBJ *wp);
void func_80103934(STAGE_OBJ *wp);
void func_801039CC(STAGE_OBJ *wp);
void func_80103A20(STAGE_OBJ *wp);
void func_80102338(STAGE_OBJ *wp);
void func_80102914(STAGE_OBJ *wp);
void func_80100874(STAGE_ROOM *wp);
void func_80100970(STAGE_ROOM *wp);
void func_80101FD8(STAGE_OBJ *wp);
void func_80104070(STAGE_OBJ *wp);
void func_801021D8(STAGE_OBJ *wp);
void func_80103D18(STAGE_OBJ *wp);
void func_801010D4(STAGE_ROOM *wp);
void func_80103704(STAGE_OBJ *wp);
void func_80103FEC(STAGE_OBJ *wp);
void func_80102D54(STAGE_OBJ *wp);
void func_80102E1C(STAGE_OBJ *wp);
void func_80106200(STAGE_OBJ *wp);
void func_80103F5C(STAGE_OBJ *wp);
void func_80100694(STAGE_ROOM *wp);
void func_8010176C(STAGE_ROOM *wp);
void func_80100EE4(STAGE_ROOM *wp);
void func_80101420(STAGE_ROOM *wp);
void func_80101800(STAGE_ROOM *wp);
void func_80102458(STAGE_OBJ *wp);
void func_801026E8(STAGE_OBJ *wp);
void func_8010554C(STAGE_FX *wp);
void func_80105618(STAGE_FX *wp);
void func_80100450(STAGE_ROOM *wp);
void func_8010628C(STAGE_OBJ *wp);
void func_8010636C(STAGE_OBJ *wp);
void func_8010644C(STAGE_OBJ *wp);
void func_80105380(STAGE_FX *wp);
void func_80100C90(STAGE_ROOM *wp);
void func_80105464(STAGE_FX *wp);
void func_80105C28(STAGE_OBJ *wp, sint32 x, sint32 y, sint32 z);
void func_80100D78(STAGE_ROOM *wp);
void func_80100728(STAGE_ROOM *wp);
void func_801018DC(STAGE_ROOM *wp);
void func_801020B0(STAGE_OBJ *wp);
void func_80100B6C(STAGE_ROOM *wp);
void func_801012E8(STAGE_ROOM *wp);
void func_80100A28(STAGE_ROOM *wp);
void func_80100F88(STAGE_ROOM *wp);
void func_801019DC(STAGE_ROOM *wp);
STAGE_FX *func_80105724(STAGE_OBJ *wp, sint16 x, sint16 y, sint16 z, uint8 mode);
void func_80102ADC(STAGE_OBJ *wp);
void func_8010348C(STAGE_OBJ *wp);
void func_80103D8C(STAGE_OBJ *wp);
void func_8010652C(STAGE_EV *wp);
void func_801015B0(STAGE_ROOM *wp);
void func_8010469C(STAGE_OBJ *wp);
void func_80101CC0(STAGE_ROOM *wp);

extern sint16 D_800BBAB0;
extern sint32 D_800BBA98;
extern sint32 D_800BBAD0;
extern sint8 D_800BBC18;
extern sint8 D_800BBCC0;

extern sint32 D_80107AE4[];

// A work slot whose +0x44 points at the object that made it (func_80103850).
typedef struct
{
    uint8 reserved00[0xC];  // 00
    sint8 timer_C;          // 0C
    uint8 reserved0D[0x37]; // 0D
    STAGE_OBJ *parent_44;   // 44
} ST02_CHILD;

void func_8010262C(STAGE_OBJ *wp);

STAGE_FX *func_80105884(STAGE_OBJ *wp, sint32 x, sint32 y, sint32 z);

// A room model record (STAGE_MODEL) with the words at +4 and +8 and the halves at +0x20 named.
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[3];    // 01
    sint32 value_4;         // 04
    sint32 value_8;         // 08
    uint8 reserved0C[0x14]; // 0C
    sint16 value_20;        // 20
    sint16 value_22;        // 22
    uint8 reserved24[0xC];  // 24
    uint8 value_30;         // 30
    uint8 reserved31[7];    // 31
} ST02_MODEL;

#define ST02_MODEL_TBL ((ST02_MODEL *)0x800BBA90)

// A lens-flare ring (func_8010469C draws ten): on, its texture cell, its distance along the
// line from the screen centre (percent), its half-size and colour.
typedef union
{
    struct
    {
        uint8 on;      // 0
        uint8 cell;    // 1
        sint16 scale;  // 2
        uint8 size;    // 4
        uint8 r, g, b; // 5
    } f;
    uint8 b[8];
    sint32 w[2];
} ST02_FLARE;

extern ST02_FLARE D_8010A628[10];

// The two previous face shapes a work slot keeps at +0x143 and +0x147 (-1: none yet); STAGE_OBJ
// doesn't name them.
typedef struct
{
    uint8 reserved00[0x143]; // 000
    sint8 prev_143;          // 143
    uint8 reserved144[3];    // 144
    sint8 prev_147;          // 147
} ST02_FACE_PREV;

extern STAGE_LIP_CUES D_8010A620;
extern STAGE_OBJ *D_8010A5D4;
extern sint16 D_800BBC3A;
extern sint16 D_800BBCE2;
extern sint8 D_800BBCF0;
extern STAGE_MOUTH_CUE D_80107868[];
extern STAGE_MOUTH_CUE D_801078D0[];

// A rising spark effect and its emitter (variant_3 1 and 0): the emitter (func_80104448) sheds a
// spark every few frames (func_801042A0); a spark fades out while it rises (func_80104184), and
// ends when its emitter's routine does.
typedef struct ST02_SPARK ST02_SPARK;

struct ST02_SPARK
{
    uint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 reserved04[2];    // 04
    uint8 flags_6;          // 06
    uint8 reserved07;       // 07
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B: emitter: frames to the next spark
    sint8 value_C;          // 0C
    sint8 timer_D;          // 0D
    sint8 width_E;          // 0E: emitter: the sparks' width
    sint8 type_F;           // 0F: growth per frame
    uint8 reserved10[4];    // 10
    uint32 mode_14;         // 14
    uint32 color_18;        // 18
    sint16 x_1C;            // 1C
    uint16 y_1E;            // 1E
    sint16 z_20;            // 20
    uint8 u_22;             // 22
    uint8 v_23;             // 23
    uint16 w_24;            // 24
    uint16 count_26;        // 26: emitter: sparks to run ahead
    sint32 rise_28;         // 28
    ST02_SPARK *owner_2C;   // 2C
    uint8 reserved30[0x18]; // 30
};

typedef void (*ST02_SPARK_FUNC)(ST02_SPARK *wp);

extern ST02_SPARK_FUNC D_80107AB8[];

void func_80104184(ST02_SPARK *wp);
void func_80104210(ST02_SPARK *wp);
void func_80104264(ST02_SPARK *wp);
void func_801042A0(ST02_SPARK *wp);
void func_801043E8(ST02_SPARK *wp);
ST02_SPARK *func_80104448(STAGE_XYZ *pos, sint32 width, sint32 growth, sint16 count, sint32 rise, uint8 flag);

// A texture animation: frame, then frames to hold it.
typedef struct
{
    uint8 frame;
    uint8 hold;
} ST02_ANIM;

extern ST02_ANIM D_80107E4C[];
extern ST02_ANIM D_80107E68[];
extern ST02_ANIM D_80107E74[];

// A sprite piece: an id, a position and a size (func_8010592C draws one).
typedef struct
{
    uint8 id;            // 0
    uint8 reserved01[3]; // 1
    sint16 x;            // 4
    sint16 y;            // 6
    sint16 h;            // 8
    sint16 w;            // A
} ST02_PIECE;

extern ST02_PIECE D_80107B14[4];
void func_8010592C(ST02_PIECE *piece);

extern STAGE_OBJ_FUNC D_801074E4[];

extern STAGE_OBJ_FUNC D_801074F4[];
extern uint32 D_80107E24[];
extern STAGE_ANIM D_80107E88[];
extern STAGE_UVW D_80107AC4[];
extern STAGE_UVW D_80107AD4[];
// PsyQ's TILE (a flat rectangle), as func_8010032C fills it.
typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    short w, h;
} ST02_TILE;

void func_8010032C(uint8 r, uint8 g, uint8 b, uint16 abr);
extern uint8 D_80106C30[];
extern STAGE_SCRIPT_ENTRY D_80107328[];
extern STAGE_ROOM2_FUNC D_8010738C[];
extern sint32 D_8010A5D8;
extern uint32 D_8010A5DC;
// A spinning model that falls and drifts (func_80105AB8): its matrix and position.
typedef struct
{
    uint8 flags_0;        // 00
    uint8 reserved01[7];  // 01
    uint8 routine_0;      // 08
    uint8 routine_1;      // 09
    uint8 routine_2;      // 0A
    uint8 routine_3;      // 0B
    sint16 value_C;       // 0C
    sint16 angle_E;       // 0E: about y
    sint16 roll_10;       // 10: about z
    uint8 reserved12[6];  // 12
    STCOM_MATRIX matrix;  // 18
    STCOM_SVECTOR pos_38; // 38
    uint32 color_40;      // 40
    sint32 fall_44;       // 44: 16.16 speed
} ST02_SPINNER;

void func_80105AB8(ST02_SPINNER *wp);
// Scene_work's word at +0x34 (past STAGE_SCENE_WORK's fields): a work slot the scene drives.
#define ST02_SCENE_OBJ (*(STAGE_OBJ **)((uint8 *)&Scene_work + 0x34))

extern sint16 D_801079E4[];
extern sint16 D_80107A26[];
extern sint16 D_80107A6C[];

// Model_work_init as func_80103704 and func_80103F08 call it: with a third argument (0).
typedef void (*ST02_INIT3_FUNC)(void *wp, uint8 *variant, sint32 arg);
extern sint16 D_801074B4[]; // the vertical shake, by frame & 3
extern sint16 D_801074BC[]; // the horizontal shake, by frame & 1
extern sint32 D_800BC7D0;   // the screen shake offsets (16.16)
extern sint32 D_800BC7D4;
void func_80101B2C(STAGE_ROOM *wp);
void func_80101C80(STAGE_ROOM *wp);
// ROCK_NEO's Cd_subcmd as func_80101CC0 called it: with two arguments (stage.h has three; retail
// leaves a2 unset).
void func_8001D494_2(sint32 arg0, sint32 arg1) __asm__("Cd_subcmd");

#endif // ST02_H
