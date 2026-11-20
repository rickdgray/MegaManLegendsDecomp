#ifndef ST17_H
#define ST17_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom18.h"
#include "stage_common/stcom23.h"

extern void *D_8011ABB8[];       // model table by room (func_80022FD4)
extern void *D_8011AD1C[];       // spawn list by room
extern void *D_8011AD44[];       // exit list by room
extern uint8 D_8011AD54[][0x28]; // by room (func_800371A0)
extern uint8 D_8011ADF4[][8];    // by D_8011AE74[room]
extern sint32 D_8011AE74[];
void func_80100704(void);
extern STAGE_SLOT_FUNC *D_8011A82C[];
extern STAGE_SLOT_FUNC *D_8011A9CC[];
extern STAGE_SLOT_FUNC D_8011AA18[];
extern STAGE_SLOT_FUNC D_8011AAD8[];
extern STAGE_SLOT_FUNC D_8011AB44[];
extern STAGE_SLOT_FUNC D_8011ABB4[];
extern STAGE_ROOM2_FUNC *D_8011AEA4[];
extern sint8 *D_8011B5A4[];
extern sint8 *D_8011B5B4[];
extern sint8 *D_8011B5F8[];
extern sint8 *D_8011B600[];
extern sint8 *D_8011B774[];
extern sint8 *D_8011B780[];
extern sint8 *D_8011B7F4[];
extern sint8 *D_8011B804[];
extern sint8 *D_8011B954[];
extern sint8 *D_8011B978[];
extern sint8 *D_8011BA68[];
extern sint8 *D_8011BA90[];
extern STAGE_OBJ_FUNC D_8011BCD4[];
extern STAGE_OBJ_FUNC D_8011C0E0[];
extern STAGE_OBJ_FUNC D_8011C128[];
extern STAGE_OBJ_FUNC D_8011C290[];
extern STAGE_OBJ_FUNC D_8011C2B0[];
extern STAGE_OBJ_FUNC D_8011C620[];
extern STAGE_OBJ_FUNC D_8011C630[]; // by variant_3

// The room model records with their byte at +0x2F (STAGE_MODEL doesn't name it).
typedef struct
{
    uint8 reserved00[0x2F]; // 00
    sint8 value_2F;         // 2F
    uint8 reserved30[8];    // 30
} ST17_MODEL;

// One zero word of .rodata at this point of the file (INCLUDE_ASM's wrapper, so maspsx drops
// everything else). Retail starts a function's jump tables 8-aligned when it has more than one;
// tools/cc.sh's jt_align only pads between a function's own tables, so the pad before the
// first one comes from here.
#define ST17_RODATA_PAD(NAME)                                                                                                              \
    void __maspsx_include_asm_hack_##NAME()                                                                                                \
    {                                                                                                                                      \
        __asm__(".section .rodata # maspsx-keep\n"                                                                                         \
                "    .word 0 # maspsx-keep\n"                                                                                              \
                ".text # maspsx-keep\n");                                                                                                  \
    }

// The absolute value with the positive test first: GCC 2.7 reserves a stack temporary for it.
#define ST17_ABS(x)    ((x) >= 0 ? (x) : -(x))
#define ST17_MODEL_TBL ((ST17_MODEL *)0x800BBA90)

extern uint8 D_800C3558[]; // ROCK_NEO's camera work
extern STAGE_SCRIPT_ENTRY D_8012123C[];
extern STAGE_SCRIPT_ENTRY D_80121250[];
extern STAGE_SCRIPT_ENTRY D_80121278[];
extern STAGE_SCRIPT_ENTRY D_801212DC[];
extern STAGE_SCRIPT_ENTRY D_80121A94[];
extern STAGE_SCRIPT_ENTRY D_8012204C[];
extern STAGE_SCRIPT_ENTRY D_80121AA8[];
extern STAGE_SCRIPT_ENTRY D_80122060[];
extern STAGE_SCRIPT_ENTRY D_80122074[];
void func_8003187C(void *wp); // frees a 0x5A4-byte work slot
void func_80117A40(sint32 unused, uint8 mode);
void func_80117BEC(sint8 index, sint8 model);
void func_8011896C(void *camera, uint8 mode);
void func_80119838(void *camera, uint8 mode);

// Routines of this module (parameter types from their bodies and callers).
void func_8010BEF0(STAGE_OBJ *wp);
void func_80118310(STAGE_ROOM *wp);
void func_80119444(STAGE_ROOM *wp);
void func_801172C0(STAGE_ROOM *wp);
void func_801188F8(STAGE_ROOM *wp);
void func_8010B420(STAGE_OBJ *wp);
void func_80113BA4(STAGE_FX *wp);
void func_801177F0(STAGE_ROOM *wp);
void func_80101870(STAGE_OBJ *wp);
void func_8010F4D4(STAGE_OBJ *wp);
void func_8010B58C(STAGE_OBJ *wp);
void func_80117370(STAGE_ROOM *wp);
void func_801196A8(STAGE_ROOM *wp);
void func_801173C4(STAGE_ROOM *wp);
void func_801178EC(STAGE_ROOM *wp);
void func_80104F38(STAGE_OBJ *wp);
void func_8010B094(STAGE_OBJ *wp);
void func_8010B130(STAGE_OBJ *wp);
void func_80117648(STAGE_ROOM *wp);
void func_8010B3B4(STAGE_OBJ *wp);
void func_8010B520(STAGE_OBJ *wp);
void func_80117420(STAGE_ROOM *wp);
void func_80103014(STAGE_OBJ *wp);
void func_8010B290(STAGE_OBJ *wp);
void func_8010787C(STAGE_OBJ *wp);
void func_80109CA4(STAGE_OBJ *wp);
void func_80117948(STAGE_ROOM *wp);
void func_801172F4(STAGE_ROOM *wp);
void func_801078F0(STAGE_OBJ *wp);
void func_801179C0(STAGE_ROOM *wp);
void func_80103084(STAGE_OBJ *wp);
void func_80114854(STAGE_OBJ *wp);
void func_80108998(STAGE_OBJ *wp);
void func_8010B190(STAGE_OBJ *wp);
void func_80116D94(STAGE_ROOM *wp);
void func_801175B4(STAGE_ROOM *wp);
void func_801176A8(STAGE_ROOM *wp);
void func_80118818(STAGE_ROOM *wp);
void func_80113FBC(STAGE_FX *wp);
void func_80108B28(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face);
void func_80108BD4(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face);
void func_8010919C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_801091C4(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80109F28(STAGE_OBJ *wp);
void func_80119398(STAGE_ROOM *wp);
void func_8010B5DC(STAGE_OBJ *wp);
void func_8010F520(STAGE_OBJ *wp);
void func_80117740(STAGE_ROOM *wp);
void func_8010147C(STAGE_OBJ *wp);
void func_8010F724(STAGE_OBJ *wp);
void func_80117830(STAGE_ROOM *wp);
void func_80119778(STAGE_ROOM *wp);
void func_801148E0(STAGE_OBJ *wp);
void func_801149C0(STAGE_OBJ *wp);
void func_80114AA0(STAGE_OBJ *wp);
void func_8010AB78(STAGE_OBJ *wp);
void func_8010BF20(STAGE_OBJ *wp);
void func_80113EC8(STAGE_FX *wp);
void func_80114DD0(STAGE_OBJ *wp);
void func_80101534(STAGE_OBJ *wp);
void func_8010AE0C(STAGE_OBJ *wp);
void func_80108A28(STAGE_OBJ *wp);
void func_80100ACC(STAGE_OBJ *wp);
void func_80100828(STAGE_OBJ *wp);
void func_8010A6D0(STAGE_OBJ *wp);
void func_8010B68C(STAGE_OBJ *wp);
void func_8010A04C(STAGE_OBJ *wp);
void func_8010F23C(STAGE_OBJ *wp);
void func_8011A44C(STAGE_ROOM *wp);
void func_80104F98(STAGE_OBJ *wp);
void func_80107970(STAGE_OBJ *wp);
void func_80108864(STAGE_OBJ *wp);
void func_80109D18(STAGE_OBJ *wp);
void func_80106EE4(STAGE_OBJ *wp, STAGE_FACE *face);
void func_80107330(STAGE_OBJ *wp, STAGE_FACE *face);
void func_80107EF8(STAGE_OBJ *wp, STAGE_FACE *face);
void func_8010837C(STAGE_OBJ *wp, STAGE_FACE *face);
void func_801091EC(STAGE_OBJ *wp, STAGE_FACE *face);
void func_8010976C(STAGE_OBJ *wp, STAGE_FACE *face);
void func_80107AEC(STAGE_OBJ *wp, STAGE_FACE16 *face);
void func_8010A3A8(STAGE_OBJ *wp, STAGE_FACE16 *face);
void func_8011A2FC(STAGE_ROOM *wp);
void func_80100978(STAGE_OBJ *wp);
void func_8010130C(STAGE_OBJ *wp);
void func_8010A9CC(STAGE_OBJ *wp);
void func_801130C4(STAGE_FX *wp);
void func_80119EB8(STAGE_ROOM *wp);
void func_8010BC84(STAGE_OBJ *wp, sint32 index);
void func_8010F7DC(STAGE_OBJ *wp);
void func_8010AF08(STAGE_OBJ *wp);
void func_8010A530(STAGE_OBJ *wp);
void func_8010AC6C(STAGE_OBJ *wp);
void func_801050C8(STAGE_OBJ *wp);
void func_8010C6DC(STAGE_OBJ *wp);
void func_80118EC0(STAGE_ROOM *wp);
void func_8010A1B4(STAGE_OBJ *wp);
void func_8010BA40(STAGE_OBJ *wp, sint32 side, sint32 level);
void func_8010B7A4(STAGE_OBJ *wp);
void func_80119474(STAGE_ROOM *wp);
void func_80117EFC(STAGE_ROOM *wp);
void func_8011865C(STAGE_ROOM *wp);
void func_80113894(STAGE_FX *wp);
void func_80101130(STAGE_OBJ *wp);
void func_80114060(STAGE_FX *wp);
void func_80118CD0(STAGE_ROOM *wp);
void func_80108668(STAGE_OBJ *wp);
void func_80117CEC(STAGE_ROOM *wp);
void func_80102B28(STAGE_OBJ *wp);
void func_80100F10(STAGE_OBJ *wp);
void func_80109A58(STAGE_OBJ *wp);
void func_80107C38(STAGE_OBJ *wp);
void func_8010761C(STAGE_OBJ *wp);
void func_8011552C(STAGE_OBJ *wp);
void func_80116B04(STAGE_ROOM *wp);

void func_80102D3C(STAGE_OBJ *wp);
void func_80115780(STAGE_OBJ *wp);
void func_8010702C(STAGE_OBJ *wp);
void func_80103108(STAGE_OBJ *wp);
void func_80108040(STAGE_OBJ *wp);
void func_80106B70(STAGE_OBJ *wp);
void func_8010C36C(STAGE_OBJ *wp);
void func_801161C8(STAGE_OBJ *wp);
void func_80109334(STAGE_OBJ *wp);

void func_80105CF8(STAGE_10C *wp, sint32 angle);

void func_80110344(STAGE_OBJ *wp);

void func_80113A70(STAGE_OBJ *wp);

void func_8010F5D0(STAGE_OBJ *wp);

void func_80110368(STAGE_OBJ *wp);

void func_8010FAA0(STAGE_OBJ *wp);

void func_8011892C(STAGE_OBJ *wp);

void func_801103A0(STAGE_OBJ *wp);

void func_80119A14(uint8 value);

extern uint8 D_8011C264[]; // sprite u, v pairs
extern uint8 D_8011C265[];
extern uint8 D_8011C270[];
extern uint8 D_8011C271[];
void func_80113AF4(STAGE_FX *wp);

extern sint8 D_8011BD38[];
void func_8010BC00(STAGE_OBJ *wp);
void func_8010B300(STAGE_OBJ *wp);

// A talking face's two lip-sync scripts (ST07_FACE's layout; D_80122B78).
typedef struct
{
    sint8 *mouth_0; // 0: shape, then a byte 0x7E (hold) or 0x7F (loop)
    sint8 *eyes_4;  // 4
    sint8 shape_8;  // 8
    sint8 prev_9;   // 9
    sint8 index_A;  // A
    sint8 shape_B;  // B
    sint8 prev_C;   // C
    sint8 index_D;  // D
} ST17_FACE;

// The same with the script positions first (D_80122B68, D_80122B88).
typedef struct
{
    sint8 shape_0;       // 0
    sint8 prev_1;        // 1
    sint8 index_2;       // 2
    sint8 shape_3;       // 3
    sint8 prev_4;        // 4
    sint8 index_5;       // 5
    uint8 reserved06[2]; // 6
    sint8 *mouth_8;      // 8
    sint8 *eyes_C;       // C
} ST17_FACE2;

// Player_work's face shapes (mouth and eyes) at +0x168.
typedef struct
{
    uint8 reserved00[0x168]; // 000
    sint8 mouth_168;         // 168
    sint8 eyes_169;          // 169
} ST17_PL_FACE;

extern ST17_FACE2 D_80122B68;
extern ST17_FACE D_80122B78;
extern ST17_FACE2 D_80122B88;
extern sint8 *D_801219B0[];
extern sint8 *D_801219BC[];
extern sint8 *D_80121FBC[];
extern sint8 *D_80121FCC[];
extern sint8 *D_801226AC[];
extern sint8 *D_801226D0[];

void func_80115014(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011AEE4[];
void func_8010093C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011B028[];
void func_80102FD8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011BD08[];
void func_8010AB3C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011BD1C[];
void func_8010B0F4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C250[];
void func_80113088(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C288[];
void func_8011381C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C63C[];
void func_80114EC4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C648[];
void func_80116930(STAGE_OBJ *wp);

extern STAGE_ROOM2_FUNC D_80121230[];
void func_80116AC8(STAGE_ROOM *wp);

extern STAGE_ROOM2_FUNC D_80121A38[];
void func_80117CB0(STAGE_ROOM *wp);

extern STAGE_ROOM2_FUNC D_80121FDC[];
void func_80118C94(STAGE_ROOM *wp);

extern STAGE_ROOM2_FUNC D_80122A7C[];
void func_8011A710(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_8011C248[];
void func_80112874(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011B0A8[];

extern STAGE_OBJ_FUNC D_8011C60C[];
void func_80114D38(STAGE_OBJ *wp);

void func_801074B8(STAGE_OBJ *wp, STAGE_LIPS *lips);
void func_80108504(STAGE_OBJ *wp, STAGE_LIPS *lips);
void func_801098F4(STAGE_OBJ *wp, STAGE_LIPS *lips);

extern sint8 *D_8011B618[];
extern sint8 *D_8011B63C[];
extern sint8 *D_8011B820[];
extern sint8 *D_8011B83C[];
extern sint8 *D_8011BACC[];
extern sint8 *D_8011BAEC[];

// Routines run on a work slot and its part at +0x88.
typedef void (*ST17_PART_FUNC)(STAGE_OBJ *wp, void *part);

extern ST17_PART_FUNC D_8011AF14[];
extern ST17_PART_FUNC D_8011B4FC[];

extern sint16 *D_8011BC88[];
void func_8010A364(STAGE_OBJ *wp, STAGE_FACE16 *face, sint32 index);

extern STAGE_OBJ_FUNC D_8011B648[];

extern STAGE_OBJ_FUNC D_8011BAF4[];

void func_8005D4E8(void);

// Talk routines: the work slot, the scene's script position and the slot's face.
typedef void (*ST17_TALK_FUNC)(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face);

extern ST17_TALK_FUNC D_8011B844[];

// A marker effect a 0x10C-byte slot leaves where it was (func_80110BA0).
typedef struct
{
    uint8 flags_0;            // 00
    uint8 reserved01;         // 01
    uint8 kind_2;             // 02
    uint8 variant_3;          // 03
    uint8 value_4;            // 4
    uint8 reserved5[0x8];     // 5
    sint8 value_D;            // D
    sint8 value_E;            // E
    uint8 reservedF[0xD];     // F
    sint16 x_1C;              // 1C
    sint16 y_1E;              // 1E
    sint16 z_20;              // 20
    uint8 reserved22[0x16];   // 22
    STCOM_SVECTOR pos_38;     // 38
    uint8 reserved40[4];      // 40
    STCOM_SVECTOR *target_44; // 44: the position it follows
} ST17_MARK;

void func_80110C0C(STAGE_10C *wp, ST17_MARK *ep);
void func_80110C4C(STAGE_10C *wp, ST17_MARK *ep);
void func_80113234(ST17_MARK *wp);
void func_8011338C(ST17_MARK *wp);
void func_80113528(ST17_MARK *wp);
void func_801136C4(ST17_MARK *wp);

// A hit record: the damage in the low 24 bits, kind bits above.
typedef struct
{
    uint32 value_0;
    uint32 value_4;
} ST17_HIT;

// The part at a work slot's +0x328 for func_80100D2C and func_80100E5C: three hit spheres.
typedef struct
{
    uint8 reserved00[4];     // 00
    uint16 flags_4;          // 04
    sint16 value_6;          // 06: rand() each frame
    uint8 reserved08[4];     // 08
    STCOM_SVECTOR vec_C[3];  // 0C
    STCOM_SVECTOR pos_24[3]; // 24
    ST17_HIT hit_3C[3];      // 3C
} ST17_PART88;

#define ST17_PART88_OF(wp) ((ST17_PART88 *)((uint8 *)(wp) + 0x328))

typedef void (*ST17_PART88_FUNC)(STAGE_OBJ *wp, ST17_PART88 *part);
extern ST17_PART88_FUNC D_8011AEE8[];

// Game_work's halfwords at +0x5C and +0x174 as struct fields (func_80100D2C).
typedef struct
{
    uint8 reserved000[0x5C];  // 000
    sint16 value_5C;          // 05C
    sint16 value_5E;          // 05E
    uint8 reserved060[0x114]; // 060
    uint16 value_174;         // 174
} ST17_GAME_WORK;

#define ST17_GAME (*(ST17_GAME_WORK *)&Game_work)

void Swing_Camera2(sint32 a0, sint32 a1, sint32 a2, STCOM_SVECTOR *pos);
void func_80100BD0(STAGE_OBJ *wp, ST17_PART88 *part);
void func_80100D2C(STAGE_OBJ *wp, ST17_PART88 *part);
void func_80100E5C(STAGE_OBJ *wp, ST17_PART88 *part);
sint32 func_80116900(void);
// Routines run on a 0x5A4-byte work slot and its extension at +0x3C0.
typedef void (*ST17_EXT_FUNC)(STAGE_OBJ *wp, void *ext);
extern ST17_EXT_FUNC D_8011BE00[];
// STCOM_SPRITE's layout, with the direction the 0x10C-byte objects keep at +0x1C.
typedef struct
{
    uint32 mode_0;          // 00
    STCOM_COLOR color_4;    // 04
    sint16 pos_8[3];        // 08: x, y, z
    uint8 value_E;          // 0E
    uint8 value_F;          // 0F
    uint16 value_10;        // 10
    sint16 value_12;        // 12
    uint32 hit_14;          // 14
    sint32 value_18;        // 18
    STCOM_SVECTOR dir_1C;   // 1C
    STCOM_SVECTOR position; // 24
    uint8 reserved2C[8];    // 2C
} ST17_SPRITE;

// The state a 0x10C-byte slot keeps at +0xD0 (func_80111A7C's objects).
typedef struct
{
    uint8 flags_0;          // 00: bit 0: done
    uint8 value_1;          // 01
    uint16 random_2;        // 02
    sint16 value_4;         // 04
    sint16 value_6;         // 06
    sint16 value_8;         // 08
    sint16 value_A;         // 0A
    sint16 value_C;         // 0C
    uint8 value_E;          // 0E
    uint8 reserved0F;       // 0F
    sint16 dx_10;           // 10: the target's offset (func_801121CC)
    sint16 dy_12;           // 12
    sint16 dz_14;           // 14
    uint8 reserved16[0x26]; // 16
} ST17_PART_D0;

// A 0x10C-byte work slot with a sprite at +0x88 (STCOM06_WORK's layout) and its state at +0xD0.
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01;                       // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 byte_C;                           // 0C
    sint8 byte_D;                           // 0D
    sint8 byte_E;                           // 0E
    sint8 byte_F;                           // 0F
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STAGE_FIXED value_44;                   // 44
    STAGE_FIXED value_48;                   // 48
    STAGE_FIXED value_4C;                   // 4C
    sint16 value_50;                        // 50
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x24];                 // 64
    ST17_SPRITE sprite;                     // 88
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    uint32 count_CC;                        // CC
    ST17_PART_D0 part_D0;                   // D0
} ST17_10C;

typedef void (*ST17_10C_FUNC)(ST17_10C *wp, ST17_PART_D0 *part);

extern ST17_10C_FUNC D_8011C1F8[];
extern ST17_10C_FUNC D_8011C204[];

void func_80112748(ST17_10C *wp, ST17_PART_D0 *part);
// The position some 0x10C-byte objects home in on, kept in the slot's count_CC word.
#define ST17_TARGET_CC(wp) (*(STCOM_SVECTOR **)&(wp)->count_CC)
extern uint8 D_8011C210[]; // sprite u, v pairs
extern uint8 D_8011C211[];
extern uint8 D_8011C21C[]; // sprite u, v pairs
extern uint8 D_8011C21D[];
extern sint16 *D_8011B700[];
extern sint16 *D_8011B71C[];
void func_80107AA4(STAGE_OBJ *wp, STAGE_FACE16 *face, sint32 index);
void func_80114250(uint8 level);
// A rising spark effect and its emitter (variant_3 1 and 0): the emitter (func_80105530) sheds a
// spark every few frames (func_80105388); a spark fades out while it rises (func_8010526C), and
// ends when its emitter's routine does.
typedef struct ST17_SPARK ST17_SPARK;

struct ST17_SPARK
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
    ST17_SPARK *owner_2C;   // 2C
    uint8 reserved30[0x18]; // 30
};

typedef void (*ST17_SPARK_FUNC)(ST17_SPARK *wp);

extern ST17_SPARK_FUNC D_8011B0AC[];

void func_8010526C(ST17_SPARK *wp);
void func_801052F8(ST17_SPARK *wp);
void func_8010534C(ST17_SPARK *wp);
void func_80105388(ST17_SPARK *wp);
void func_801054D0(ST17_SPARK *wp);
ST17_SPARK *func_80105530(STCOM_SVECTOR *pos, sint32 width, sint32 growth, sint16 count, sint32 rise, uint8 flag);

// Records of a table loaded at 0x8015C010; a zero value_4 ends it (func_80116A64).
typedef struct
{
    sint16 value_0;
    uint8 reserved02[2];
    sint32 value_4;
    uint8 reserved08[4];
} ST17_REC;

#define ST17_REC_TBL ((ST17_REC *)0x8015C010)

// A scratchpad frame counter (stcom08's STCOM08_FRAME).
#define ST17_FRAME (*(uint16 *)0x1F800002)
extern sint16 D_800BBCF8[]; // ROCK_NEO's sine table (64 entries)
extern uint32 D_8011C590[];
extern STAGE_ANIM D_8011C5B8[];
extern STAGE_ANIM D_8011C5D4[];
extern STAGE_ANIM D_8011C5E0[];
extern STAGE_ANIM D_8011C5F4[];
void func_8011475C(STAGE_OBJ *wp);
// Copies of stcom23's and stcom18's routines (the files themselves are not linked here).
extern STCOM23_PARAM D_8011BF8C[];
extern STCOM23_FUNC D_8011C0C0[]; // by type_1C: set up
extern STCOM23_FUNC D_8011C0C8[]; // by type_1C: each frame
extern STCOM23_FUNC D_8011C0D0[]; // by type_1C: destroyed
extern STCOM23_UV D_8011C0D8[];   // the four puffs' textures
extern STCOM18_PAIR D_8011C0EC[6];
extern STCOM18_PAIR D_8011C0F8[6];
extern STCOM18_FUNC D_8011C104[];
void func_8010FEC4(STCOM23_WORK *wp);
void func_80110434(STCOM23_WORK *wp);
void func_801104DC(STCOM23_WORK *wp);
void func_8011058C(STCOM23_WORK *wp);
void func_801105F8(STCOM23_WORK *wp);
void func_801106D8(STCOM18_WORK *wp);
void func_80110774(STCOM18_WORK *wp);
void func_80110938(STCOM18_WORK *wp);
// A grid of 9 rows of 8 cells kept at a work slot's +0x88 (func_80105D04's objects).
typedef struct
{
    STAGE_XYZ *origin_0; // 00
    uint8 state_4;       // 04
    uint8 shade_5;       // 05: subtracted from each color channel
    sint16 frame_6;      // 06: D_8011AF44[frame_6 / 4] is the texture u
    uint16 size_8;       // 08
    sint16 x_A;          // 0A
    sint16 y_C;          // 0C
    sint16 z_E;          // 0E
} ST17_CELL;

typedef struct
{
    sint8 mode_0;            // 00: D_8011B50C handler
    uint8 reserved01[2];     // 01
    uint8 count_3[9];        // 03: per row
    uint16 mask_C;           // 0C: rows that also run D_8011B524
    sint8 kind_E;            // 0E: D_8011B524 handler
    uint8 reserved0F[3];     // 0F
    sint16 frame_12;         // 12
    sint32 value_14;         // 14
    ST17_CELL cell_18[9][8]; // 18
} ST17_GRID;

typedef void (*ST17_GRID_FUNC)(ST17_GRID *grid, ST17_CELL *cell);
typedef void (*ST17_CELL_FUNC)(ST17_CELL *cell, sint32 value);
extern ST17_GRID_FUNC D_8011B50C[];
extern ST17_CELL_FUNC D_8011B524[];
void func_80106120(ST17_GRID *grid, uint8 row, uint8 col);
extern uint8 D_8011AF44[];
extern uint8 D_8011B534[];
extern STAGE_OBJ_FUNC D_8011AEF0[];
extern sint16 D_8011AF0C[4]; // roll steps by frame (func_801016B4)
void func_80101990(STAGE_OBJ *wp);
void func_80053158(STAGE_OBJ *target, STAGE_OBJ *wp);
extern STAGE_OBJ_FUNC D_8011BF78[];
extern STAGE_OBJ *D_80122B48;
void func_80115C24(STAGE_OBJ *wp);
extern STAGE_SCRIPT_ENTRY D_80121A6C[];
extern STAGE_SCRIPT_ENTRY D_80122010[];
extern STAGE_SCRIPT_ENTRY D_80122038[];
void func_80104B34(STAGE_XYZ *pos);
// A grid of 6 rows of 8 cells kept at a work slot's +0x88 (func_80101D10's objects).
typedef struct
{
    sint8 mode_0;            // 00: D_8011AF24 handler
    uint8 mask_1;            // 01: rows that also run D_8011AF38
    uint8 reserved02;        // 02
    uint8 rows_3;            // 03: rows func_80102038 runs
    uint8 count_4[6];        // 04: per row
    uint8 reserved0A;        // 0A
    sint8 kind_B;            // 0B: D_8011AF38 handler
    sint32 frame_C;          // 0C
    sint32 value_10;         // 10
    ST17_CELL cell_14[6][8]; // 14
} ST17_GRID6;

typedef void (*ST17_GRID6_FUNC)(ST17_GRID6 *grid, ST17_CELL *cell);
extern ST17_GRID6_FUNC D_8011AF24[];
extern ST17_CELL_FUNC D_8011AF38[];
void func_801022BC(ST17_GRID6 *grid, uint8 row, uint8 col);

extern ST17_HIT D_80122AC8[];       // hits taken this frame (8 records)
extern STCOM_SVECTOR D_80122A88[8]; // their hit boxes' positions
extern sint8 D_8011BCF0[8];         // the joints they sit on
extern sint16 D_8011BCF8[8];        // their sizes
extern STAGE_OBJ_FUNC D_8011BCE0[]; // by routine_1 (func_8010A6D0)
void func_8010A7E4(STAGE_OBJ *wp);
void func_8010A884(STAGE_OBJ *wp);
void func_801189F0(STAGE_ROOM *wp);
void func_80118B44(sint32 index);
void func_80118B7C(sint32 index);
void func_80118BB4(ST17_PL_FACE *pl);
void func_80117AA4(sint32 index);
void func_80117B08(ST17_PL_FACE *pl);
void func_801114E4(ST17_10C *wp);
// func_801114E4's 24 spiral sparks: each one flies for 16 frames from its start, spiraling out.
typedef struct
{
    sint16 start_0;  // 0: count_CC when it appears
    sint16 radius_2; // 2
    uint16 angle_4;  // 4
    sint16 height_6; // 6
} ST17_SPIRAL;

extern ST17_SPIRAL D_8011C138[24];
STCOM_SVECTOR func_8011134C(ST17_10C *wp);
void func_80111780(ST17_10C *wp);
extern STAGE_SCRIPT_ENTRY D_80122704[];
extern STCOM_SVECTOR D_80122A1C[];
void func_80119A78(void);
extern STAGE_SCRIPT_ENTRY D_80122718[];
extern STCOM_SVECTOR D_80122A2C[];
extern STCOM_SVECTOR D_801219C8[];
extern uint16 D_8011AF58[];
extern STAGE_EV *D_80122B50;
void func_80053AA4(sint32 arg);
void func_8005D87C(void);
void func_8005D6E8(void *wp);
void func_80116510(STAGE_OBJ *wp);
void Game_logo_kill(sint32 index);
sint32 func_801166C8(STAGE_OBJ *wp);
extern STAGE_OBJ *D_80122B4C;
extern sint16 D_800C0F96[]; // an array: its stores stay ordered against struct accesses

// Player_work's halfwords at +0x126, +0x13E and +0x140, read through a pointer (func_801161C8).
typedef struct
{
    uint8 reserved000[0x126]; // 000
    uint16 value_126;         // 126
    uint8 reserved128[0x16];  // 128
    uint16 value_13E;         // 13E
    uint16 value_140;         // 140
} ST17_PL_KEYS;

// A work slot as func_80115C24 sets it up (fields shared by the 0x3C0 and 0x5A4 pools).
typedef struct
{
    uint8 flags_0;                          // 000
    uint8 index_1;                          // 001
    uint8 kind_2;                           // 002
    uint8 variant_3;                        // 003
    uint8 value_4;                          // 004
    uint8 reserved005[3];                   // 005
    uint8 routine_0;                        // 008
    uint8 routine_1;                        // 009
    uint8 routine_2;                        // 00A
    uint8 routine_3;                        // 00B
    uint8 value_C;                          // 00C
    uint8 reserved00D[7];                   // 00D
    STCOM_SVECTOR position;                 // 014
    STCOM_FIXED_VECTOR position_fixed;      // 01C
    STCOM_SVECTOR position_prev;            // 02C
    STCOM_FIXED_VECTOR position_fixed_prev; // 034
    sint16 value_44;                        // 044
    sint16 value_46;                        // 046
    sint16 value_48;                        // 048
    uint8 reserved04A[0xA];                 // 04A
    STCOM_SVECTOR rotation;                 // 054
    STCOM_SVECTOR rotation_prev;            // 05C
    uint8 reserved064[0xA];                 // 064
    sint16 life_6E;                         // 06E
    uint8 reserved070[0x3C];                // 070
    uint8 anim_AC;                          // 0AC
    uint8 anim_prev_AD;                     // 0AD
    uint8 reserved0AE[2];                   // 0AE
    sint16 value_B0;                        // 0B0
    uint8 reserved0B2[0x276];               // 0B2
    STAGE_OBJ *owner_328;                   // 328
    uint8 reserved32C[0x94];                // 32C
    STAGE_OBJ *owner_3C0;                   // 3C0
} ST17_SLOT;

// ROCK_NEO's per-kind records (D_80098844), only the bytes read here.
typedef struct
{
    uint8 reserved00[8]; // 00
    uint8 life_8;        // 08: in units of 32
    uint8 reserved09;    // 09
    uint8 value_A;       // 0A
    uint8 life_B;        // 0B: added per part, in units of 32
    uint8 life_C;        // 0C: in units of 16
} ST17_KIND;

extern ST17_KIND **D_80098844;

// An effect slot (STAGE_FX's layout) with twelve (angle, speed) byte pairs from +0x28: a burst
// of sparks around a work slot (func_80113C84, func_80114060).
typedef struct
{
    uint8 flags_0;        // 00
    uint8 reserved01;     // 01
    uint8 kind_2;         // 02
    uint8 variant_3;      // 03
    uint8 reserved04[4];  // 04
    uint8 routine_0;      // 08
    uint8 routine_1;      // 09
    uint8 routine_2;      // 0A
    uint8 routine_3;      // 0B
    sint8 value_C;        // 0C: the owner's id
    sint8 timer_D;        // 0D
    sint8 frame_E;        // 0E
    sint8 type_F;         // 0F
    uint8 reserved10[4];  // 10
    uint32 mode_14;       // 14
    uint32 color_18;      // 18
    sint16 x_1C;          // 1C
    sint16 y_1E;          // 1E
    sint16 z_20;          // 20
    uint8 u_22;           // 22
    uint8 v_23;           // 23
    uint16 w_24;          // 24
    uint16 h_26;          // 26
    uint8 pair_28[12][2]; // 28
} ST17_BURST;

void func_80113C84(ST17_BURST *wp);
void func_8005D620(void *wp, sint32 a1, sint32 a2, sint32 a3, uint32 a4);
void func_8005D844(sint32 a0, sint32 a1, uint8 a2);
extern STAGE_OBJ *D_80122B54[];
// A jointed model's record at a work slot's +0x440: the model's 0x5A4-byte slot
// (func_80105A0C) and the nine joint rotations it draws with.
typedef struct
{
    void *slot_0;           // 00
    STCOM_SVECTOR rot_4[9]; // 04
} ST17_RIG;

void func_8010C30C(STAGE_OBJ *wp, ST17_RIG *rig);
// Routines of a jointed model: the work slot, the scene's script position and its rig.
typedef void (*ST17_RIG_FUNC)(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST17_RIG *rig);
extern ST17_RIG_FUNC D_8011BDBC[];
void func_8010C014(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST17_RIG *rig);
void func_8010C0C0(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST17_RIG *rig);
void func_8010C1C4(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST17_RIG *rig);
// Creates the model for a jointed work slot (a 0x5A4-byte slot); NULL when none is free.
void *func_80105A0C(STAGE_OBJ *wp, sint8 kind, STCOM_SVECTOR *rot);

// Two jointed models side by side, at a work slot's +0x400: their 0x5A4-byte slots and
// eighteen joint positions (nine for each), placed from D_8011BEE8 (func_8010F600).
typedef struct
{
    void *slot_0;            // 00
    void *slot_4;            // 04
    STCOM_SVECTOR pos_8[18]; // 08
} ST17_RIG2;

typedef void (*ST17_RIG2_FUNC)(STAGE_OBJ *wp, ST17_RIG2 *rig);
extern ST17_RIG2_FUNC D_8011BED8[];
extern STCOM_SVECTOR D_8011BEE8[];
void func_8010F41C(STAGE_OBJ *wp, ST17_RIG2 *rig);
void func_8010F600(STAGE_OBJ *wp, ST17_RIG2 *rig);
// A 0x10C-byte work slot the boss spawns: its arms (kind 2, func_8010F0D8) and its shots
// (kind 7, func_8010EE0C and func_8010EFC8).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01;                  // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 value_4;                     // 04
    uint8 reserved05[7];               // 05
    sint8 value_C;                     // 0C
    sint8 value_D;                     // 0D
    sint8 value_E;                     // 0E
    uint8 value_F;                     // 0F
    uint8 reserved10[4];               // 10
    STCOM_SVECTOR position;            // 14
    STAGE_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x18];            // 2C
    STAGE_FIXED value_44;              // 44: with value_48, the velocity
    STAGE_FIXED value_48;              // 48
    STAGE_FIXED value_4C;              // 4C
    sint16 value_50;                   // 50: with value_4C, the acceleration
    uint8 reserved52[0x3A];            // 52
    STAGE_MATRIX matrix_8C;            // 8C
    STCOM_SVECTOR position_AC;         // AC
    sint32 color_B4;                   // B4
    void *target_B8;                   // B8
    uint8 reservedBC[0x10];            // BC
    void *target_CC;                   // CC
    uint8 reservedD0[0x3C];            // D0
} ST17_SHOT;

// The boss's record at its 0x5A4-byte work slot's +0x3C0 (func_8010C994 sets it up): twelve
// parts, each with its life, its hits this frame and a timer that runs while it is broken.
typedef struct
{
    uint8 reserved00[4];      // 000
    ST17_SHOT *arm_4;         // 004: func_8010F0D8's two objects
    ST17_SHOT *arm_8;         // 008
    STAGE_OBJ *model_C;       // 00C: func_80105A0C's model
    STAGE_OBJ *model_10;      // 010: func_80101B58's model
    uint16 flags_14;          // 014
    sint16 random_16;         // 016: rand() each frame
    sint16 timer_18;          // 018
    sint16 timer_1A;          // 01A
    sint16 y_1C;              // 01C: the height it bobs about
    uint8 value_1E;           // 01E
    uint8 phase_1F;           // 01F: palette flash step (0..0x1F)
    STCOM_SVECTOR pos_20[16]; // 020: the parts' positions
    sint16 life_A0[12];       // 0A0
    sint16 life_max_B8[12];   // 0B8
    ST17_HIT hit_D0[12];      // 0D0
    uint8 timer_130[12];      // 130: 0xFF while the part is whole
    uint8 count_13C;          // 13C
    uint8 count_13D;          // 13D
    uint8 count_13E;          // 13E
    uint8 value_13F;          // 13F
    uint8 flags_140;          // 140
    uint8 flags_141;          // 141
    uint16 frame_142;         // 142
    sint32 count_144;         // 144
    uint8 track_148[0x10];    // 148: func_80036478
    uint8 reserved158[0x8C];  // 158
} ST17_BOSS;

// The boss's hit boxes: four-byte records at its work slot's +0xF8, byte 3 set while one is off
// (record 0 is the body; part i is record i + 1).
typedef struct
{
    uint8 reserved0[3]; // 0
    sint8 off_3;        // 3
} ST17_HITBOX;

typedef struct
{
    uint8 reserved00[0xF8];    // 00
    ST17_HITBOX hitbox_F8[13]; // F8
} ST17_HITBOX_OBJ;

#define ST17_HITBOX_TBL(wp) (((ST17_HITBOX_OBJ *)(wp))->hitbox_F8)

// The boss's numbers in ROCK_NEO's per-kind table (D_8009884C).
typedef struct
{
    uint8 reserved0[8]; // 0
    uint8 life_8;       // 8: part 9's life / 16
    uint8 value_9;      // 9
    uint8 life_A;       // A: parts 0 and 10
    uint8 life_B;       // B: parts 1 and 11
    uint8 life_C;       // C: part 2
    uint8 life_D;       // D: the others
} ST17_BOSS_DATA;

extern ST17_BOSS_DATA **D_8009884C;
extern STCOM_SVECTOR D_8011BE40[16];
extern STCOM_SVECTOR D_8011BEC0;
extern STCOM_SVECTOR D_8011BEC8;
extern sint8 D_8011BED0[]; // message ids, by part

typedef void (*ST17_BOSS_FUNC)(STAGE_OBJ *wp, ST17_BOSS *ext);
extern ST17_BOSS_FUNC D_8011BE08[];
extern ST17_BOSS_FUNC D_8011BE14[];

// The ribbon a kind-0x12 work slot keeps at +0x88 (func_80101A14, func_80101B58): up to six
// strands of eight points, each strand following one position.
typedef struct
{
    STCOM_SVECTOR *pos_0; // 0
    uint8 value_4;        // 4
    uint8 value_5;        // 5
    sint16 value_6;       // 6
    uint8 reserved08[8];  // 8
} ST17_RIBBON_PT;

typedef struct
{
    ST17_RIBBON_PT pt[8];
} ST17_STRAND;

typedef struct
{
    uint8 type_0;             // 88
    uint8 value_1;            // 89
    uint8 value_2;            // 8A: the owner's value_1
    uint8 count_3;            // 8B: strands
    uint8 value_4[6];         // 8C: one per strand
    uint8 reserved0A;         // 92
    uint8 value_B;            // 93
    uint32 value_C;           // 94
    uint32 color_10;          // 98
    ST17_STRAND strand_14[6]; // 9C
} ST17_RIBBON;

#define ST17_RIBBON_OF(wp) ((ST17_RIBBON *)((uint8 *)(wp) + 0x88))

STAGE_OBJ *func_80101A14(STAGE_OBJ *owner, uint8 count, STCOM_SVECTOR *pos);
STAGE_OBJ *func_80101B58(STAGE_OBJ *wp, sint8 kind, STCOM_SVECTOR *pos);
void func_8010C880(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010C994(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010CC54(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010CE88(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010D04C(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010D2CC(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010D534(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010D6EC(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010D908(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010DA94(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010DD10(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010E164(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010E514(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010E660(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010E7F8(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010E924(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010EA58(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010EBC0(STAGE_OBJ *wp, ST17_BOSS *ext, sint16 part, sint32 color);
void func_8010ECD4(STAGE_OBJ *wp, ST17_BOSS *ext);
void func_8010EE0C(STAGE_OBJ *wp, ST17_BOSS *ext, sint32 index);
void func_8010EFC8(STAGE_OBJ *wp, ST17_BOSS *ext, sint32 index);
void func_8010F0D8(STAGE_OBJ *wp, ST17_BOSS *ext);
// A 0x10C-byte slot's six screen points at +0xD4 (func_80110E58 projects them, func_8011142C
// draws them).
typedef struct
{
    uint32 xy_0; // 0
    uint32 z_4;  // 4
} ST17_SXYZ;

typedef struct
{
    uint8 reserved00[0xD4]; // 00
    ST17_SXYZ point_D4[6];  // D4
    uint8 reserved104[0x8]; // 104
} ST17_TRAIL;

void func_8011142C(ST17_TRAIL *wp);
// The part func_80103520 runs on: its flags and its hit record.
typedef struct
{
    STAGE_OBJ *owner_0;   // 00
    uint16 flags_4;       // 04
    uint16 random_6;      // 06: rand() each frame
    uint16 value_8;       // 08
    uint16 timer_A;       // 0A
    sint16 value_C;       // 0C
    sint16 timer_E;       // 0E
    sint16 value_10;      // 10
    sint16 vx_12;         // 12
    sint16 vy_14;         // 14
    sint16 vz_16;         // 16
    sint16 value_18;      // 18
    sint16 value_1A;      // 1A
    sint16 value_1C;      // 1C
    sint16 value_1E;      // 1E
    sint16 value_20;      // 20
    sint16 value_22;      // 22
    sint16 value_24;      // 24
    uint8 reserved26[2];  // 26
    ST17_HIT hit_28;      // 28
    uint8 track_30[0x10]; // 30: func_80036478/func_8003648C
} ST17_PART28;

typedef void (*ST17_PART28_FUNC)(STAGE_OBJ *wp, ST17_PART28 *part);
extern ST17_PART28_FUNC D_8011B03C[];
extern ST17_PART28_FUNC D_8011B044[];
void func_801039E0(STAGE_OBJ *wp, ST17_PART28 *part);
void func_80103E6C(STAGE_OBJ *wp, ST17_PART28 *part);
void func_8010421C(STAGE_OBJ *wp, ST17_PART28 *part);
void func_80104498(STAGE_OBJ *wp, ST17_PART28 *part);
void func_80104900(STAGE_OBJ *wp, ST17_PART28 *part);
void func_801036EC(STAGE_OBJ *wp, ST17_PART28 *part);
void func_801037B4(STAGE_OBJ *wp, ST17_PART28 *part);
sint32 func_8003648C(void *track, void *wp);

void func_8010483C(STAGE_OBJ *wp, ST17_PART28 *part);
void func_801033E4(STAGE_OBJ *wp, ST17_PART28 *part);
void func_80104BBC(STAGE_OBJ *wp, ST17_PART28 *part);
void func_80104D78(STAGE_OBJ *wp, ST17_PART28 *part);
extern ST17_PART28_FUNC D_8011B030[];
extern sint16 D_8011B054[]; // a hit box: -220..220, -220..220, -220..0
extern sint16 D_8011B060[]; // 36 angles

// A copy of the special-weapon shot from r3_shl02 (its SHL_WORK) at 0x80112874: an object slot
// with ROCK_NEO's generic layout up to 0x88, then a model's draw data.
typedef struct
{
    sint8 flags_0; // 00
    uint8 value_1; // 01
    uint8 kind_2;  // 02
    uint8 type_3;  // 03: 0x40 set for a shot fired by another object
    uint8 reserved04[2];
    uint8 flags_6; // 06
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
} ST17_SHL;

// The shot's effect slot from func_80031618 (r3_shl02's SHL_FX).
typedef struct
{
    sint8 routine_0; // 00
    uint8 reserved01;
    uint8 kind_2; // 02
    uint8 flag_3; // 03
    uint8 reserved04[0x18];
    sint16 x_1c; // 1C
    sint16 y_1e; // 1E
    sint16 z_20; // 20
    uint8 reserved22[0xE];
    sint16 vx_30; // 30
    sint16 vy_32; // 32
    sint16 vz_34; // 34
    uint8 reserved36[0xA];
    uint32 value_40; // 40
    uint8 reserved44[4];
} ST17_SHL_FX;

// Player_work's signed bytes past STCOM_PL_WORK's fields.
#define ST17_PL_SBYTE(offset) (*((sint8 *)&Player_work + (offset)))

extern sint16 D_8011C23C[];
void func_801128C4(ST17_SHL *wp);
void func_80112CCC(ST17_SHL *wp);
void func_80112E44(ST17_SHL *wp);
void func_80112F88(ST17_SHL *wp, sint32 arg);
void func_800354E0(sint32 bit);
sint16 func_80039B80(void);
sint32 func_80037634(void *player, sint32 arg);
sint32 func_800375D4(void *player, sint32 arg);
// func_8003430C is declared in stage_common/stage.h.

// A work slot's fields STAGE_OBJ leaves unnamed: +0x80 is ROCK_NEO's distance to the player
// (squared?), as stcom16's value_80.
typedef struct
{
    uint8 reserved00[0x74]; // 00
    uint8 value_74;         // 74
    uint8 reserved75[0xB];  // 75
    uint32 dist_80;         // 80
} ST17_OBJ_FIELDS;

// A work slot's word at +offset as a plain (non-struct) memory reference: GCC 2.7 keeps it
// ordered against scalar global loads, where a struct field store moves past them.
#define ST17_OBJ_WORD(wp, offset) (*(uint32 *)((uint8 *)(wp) + (offset)))
#define ST17_VALUE_74(wp)         (((ST17_OBJ_FIELDS *)(wp))->value_74)
#define ST17_DIST(wp)             (((ST17_OBJ_FIELDS *)(wp))->dist_80)

// The joint vectors some objects keep at a work slot's +0x180 (positions; func_8010C30C copies
// entries 1 to 9 into a rig as its joint rotations).
typedef struct
{
    uint8 reserved000[0x180];    // 000
    STCOM_SVECTOR joint_180[16]; // 180
} ST17_JOINT_OBJ;

#define ST17_JOINT(wp) (((ST17_JOINT_OBJ *)(wp))->joint_180)

// A shot's start offset from its side's joint (func_8010BA40).
typedef struct
{
    sint16 x;
    sint16 z;
} ST17_XZ;

extern uint8 D_8011BD60[];   // joint by side
extern sint16 D_8011BD64[];  // angle spread by level
extern ST17_XZ D_8011BD6C[]; // by side
extern ST17_XZ D_8011BD74[]; // by index (func_8010BC84)
extern sint16 D_8011BD94[4]; // height by index
extern sint16 D_8011BD9C[8]; // random angle
extern sint16 D_8011BDAC[8]; // random rise speed

// The jumping boss's state in its work slot's +0x4E0 area (STAGE_OBJ_HW's layout, extended): a
// saved landing point and heading, and its four spark emitters (func_8010B68C).
typedef struct
{
    sint16 value_0;           // 00
    sint16 timer_2;           // 02
    sint16 value_4;           // 04
    sint16 value_6;           // 06
    STCOM_SVECTOR vec_8;      // 08
    STCOM_SVECTOR vec_10;     // 10: a saved position
    sint16 value_18;          // 18
    STCOM_SVECTOR vec_1A;     // 1A
    sint16 angle_22;          // 22
    ST17_SPARK *sparks_24[4]; // 24
} ST17_HW;

#define ST17_HW_OF(wp) ((ST17_HW *)&(wp)->u_4E0)

// A joint and how far below it (func_8010B68C).
typedef struct
{
    uint8 joint;
    uint8 drop;
} ST17_JOINT_DROP;

extern ST17_JOINT_DROP D_8011BCC8[4];
extern sint8 D_8011BD48[8];  // frames between bursts
extern uint8 D_8011BD50[16]; // joints a burst comes from

// func_80105530 as func_8010B68C calls it: without the flag argument.
typedef ST17_SPARK *(*ST17_SPARK5_FUNC)(STCOM_SVECTOR *pos, sint32 width, sint32 growth, sint16 count, sint32 rise);
void Sound_key_off_voice(sint32 voice);
void Pl00_shot_enable_off(void *pl);
void func_8005D4D4(void);

// Scene_work's work-slot pointers from +0x24 (past STAGE_SCENE_WORK's fields).
#define ST17_SCENE_OBJ(scene, i) (((STAGE_OBJ **)((uint8 *)(scene) + 0x24))[i])
// Scene_work's bytes past STAGE_SCENE_WORK's fields, through a pointer to it.
#define ST17_SCENE_BYTE(scene, offset) (*((uint8 *)(scene) + (offset)))

extern STCOM_SVECTOR D_8011BDC8[7]; // joint offsets (func_8010C36C)
extern STCOM_SVECTOR D_80122B08[7]; // their positions

// A puff of a burst (func_80105638): its start and its per-frame step, in 1/16 units.
typedef struct
{
    STCOM_SVECTOR pos_0;  // 00: x, y, z and the size
    STCOM_SVECTOR step_8; // 08
    uint16 shade_10;      // 10
    sint16 fade_12;       // 12
    uint8 tile_14;        // 14
    uint8 reserved15[3];  // 15
} ST17_PUFF;

extern ST17_PUFF D_8011B0B8[32];

// A tumbling piece of a burst (func_80105830), in a 0x50-byte slot (STAGE_OBJ50's layout, with
// a halfword frame counter at +0xE).
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01[2];   // 01
    uint8 variant_3;       // 03
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 routine_3;       // 0B
    sint8 index_C;         // 0C: its D_8011B3B8 record
    sint8 value_D;         // 0D
    uint16 frame_E;        // 0E
    uint8 reserved10[8];   // 10
    STAGE_MATRIX_W matrix; // 18
    STCOM_SVECTOR pos_38;  // 38
    uint32 color_40;       // 40
    uint8 reserved44[0xC]; // 44
} ST17_PIECE;

// A piece's start and its per-frame steps (position in 1/16 units, rotation in 1/128).
typedef struct
{
    STCOM_SVECTOR pos_0;   // 00: x, y, z and the scale
    STCOM_SVECTOR step_8;  // 08
    STCOM_SVECTOR rot_10;  // 10
    STCOM_SVECTOR spin_18; // 18
    uint8 variant_20;      // 20
    uint8 reserved21[3];   // 21
} ST17_PIECE_DATA;

extern ST17_PIECE_DATA D_8011B3B8[];

// One joint's animation key in a jointed model's record.
typedef struct
{
    STCOM_SVECTOR *rot_0; // 00: the rotation it reads
    uint8 value_4;        // 04
    uint8 value_5;        // 05
    sint16 value_6;       // 06
    uint8 reserved08[8];  // 08
} ST17_JOINT_KEY;

// A jointed model's record, at its 0x5A4-byte slot's +0x88 (func_80105A0C).
typedef struct
{
    uint8 id_0;                  // 00
    uint8 value_1;               // 01
    uint8 count_2;               // 02: joints
    uint8 mode_3[9];             // 03: per joint
    sint16 value_C;              // 0C
    uint8 value_E;               // 0E
    uint8 reserved0F[3];         // 0F
    sint16 value_12;             // 12
    uint32 color_14;             // 14
    ST17_JOINT_KEY key_18[9][8]; // 18
} ST17_MODEL_REC;

// A 0x5A4-byte work slot holding a jointed model (func_80105A0C).
typedef struct
{
    uint8 flags_0;           // 000
    uint8 reserved001;       // 001
    uint8 kind_2;            // 002
    uint8 variant_3;         // 003
    uint8 value_4;           // 004
    uint8 reserved005;       // 005
    uint8 flags_6;           // 006
    uint8 reserved007[5];    // 007
    uint32 value_C;          // 00C
    uint32 value_10;         // 010
    uint8 reserved014[0x74]; // 014
    ST17_MODEL_REC model_88; // 088
    uint8 reserved520[0x84]; // 520
} ST17_MODEL_SLOT;

ST17_MODEL_SLOT *func_80031498(void);
// A 0x10C-byte work slot with a sprite at +0x88 (STCOM06_WORK's layout) and its state at +0xD0.
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01;                       // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 byte_C;                           // 0C
    sint8 byte_D;                           // 0D
    sint8 byte_E;                           // 0E
    sint8 byte_F;                           // 0F
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STAGE_FIXED value_44;                   // 44
    STAGE_FIXED value_48;                   // 48
    STAGE_FIXED value_4C;                   // 4C
    sint16 value_50;                        // 50
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x24];                 // 64
    ST17_SPRITE sprite;                     // 88
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    uint32 count_CC;                        // CC
    uint8 reservedD0[4];                    // D0
    STCOM_SVECTOR trail_D4[6];              // D4: the trail's points
    uint8 reserved104[8];                   // 104
} ST17_10C_B;

extern uint32 D_8011C110[]; // hit kinds, by byte_D
extern uint32 D_8011C11C[]; // func_80037738's amounts, by byte_D

void func_80110E58(ST17_10C_B *wp);

void func_80110CB8(ST17_10C_B *wp);

// Called before their definitions.
void func_80106E94(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80106EBC(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_801072E0(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80107308(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80107EA8(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80107ED0(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_8010832C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80108354(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_8010971C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80109744(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_8010B968(STAGE_OBJ *wp);
void func_8010BE04(STAGE_OBJ *wp);
extern uint8 D_801227D4[];
extern STAGE_ROOM2_FUNC D_80122A34[];
extern sint32 D_80122B98;
void Sce_event_timer_clear(void);
extern STAGE_SCRIPT_ENTRY D_801212F0[];
extern sint16 D_80121978[]; // shake offsets
extern sint32 D_800BC7D4;   // the screen shake
extern STAGE_SCRIPT_ENTRY D_801226DC[];
extern uint8 D_80122768[];
extern STAGE_ROOM2_FUNC D_801227C4[];
extern uint8 D_80122B9C;
extern STAGE_SCRIPT_ENTRY D_801226F0[];
extern STCOM_SVECTOR D_80122A04[];
extern STAGE_SCRIPT_ENTRY D_80122740[];
void Sce_event_next(void);
extern uint8 D_801220E4[];
extern STAGE_ROOM2_FUNC D_80122628[];
void func_8003697C(void);
void func_8001D974(void);
extern STAGE_SCRIPT_ENTRY D_80121FE8[];
extern STAGE_SCRIPT_ENTRY D_80121FFC[];
extern uint8 D_80122088[];
extern STAGE_ROOM2_FUNC D_801220D4[];
extern STAGE_SCRIPT_ENTRY D_80121A44[];
extern uint8 D_80121ABC[];
extern STAGE_ROOM2_FUNC D_80121B08[];
extern uint8 D_80121B18[];
extern STAGE_ROOM2_FUNC D_80121F08[];
extern uint8 D_80121318[];
extern STAGE_ROOM2_FUNC D_801218D0[];
extern uint8 D_80121368[];
extern STAGE_ROOM2_FUNC D_801218E0[];

// PsyQ's TILE (a flat rectangle), as func_80119A78 fills it (ST02_TILE's layout).
typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    short w, h;
} ST17_TILE;

// A work slot's joint positions and matrices (stcom16's layout; func_80113894 reads them through
// func_80036294).
typedef struct
{
    uint8 reserved000[0x14];     // 000
    STCOM_SVECTOR position;      // 014
    uint8 reserved01C[0x164];    // 01C
    STCOM_SVECTOR joint_180[13]; // 180
    STCOM_MATRIX matrix_1E8[8];  // 1E8
} ST17_JOINT_OWNER;

extern ST17_XZ D_8011C2A4[]; // offsets from the joints, by index - 1
ST17_JOINT_OWNER *func_80036294(sint32 id);

#endif // ST17_H
