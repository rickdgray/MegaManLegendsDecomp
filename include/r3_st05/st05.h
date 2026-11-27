#ifndef ST05_H
#define ST05_H

#include "common.h"
#include "stage_common/stage.h"

// A falling speed that grows by half a unit every five frames (func_801107D8), and a
// scratchpad value that eases in and out (func_8011061C, func_8011070C).
typedef struct
{
    sint16 count_0;      // 0
    uint8 reserved2[2];  // 2
    STAGE_FIXED speed_4; // 4: 16.16
    sint16 value_8;      // 8
    sint16 step_A;       // A
    uint16 count_C;      // C
    uint8 reservedE[2];  // E
} ST05_FALL;

// A hit record of r3_st05's large actor (ST05_OBJ +0x450): func_800341BC's result first.
typedef struct
{
    sint32 hit_0;       // 0
    sint32 value_4;     // 4
    uint8 reserved8[8]; // 8
} ST05_HIT;

// A talking object's state at +0x500 (func_8011EB14's family): flags (bit 2: the mouth moves),
// the script's frame count, and the eye and mouth shapes with the last ones drawn.
typedef struct
{
    uint16 flags_0;       // 00
    uint16 prev_2;        // 02: flags_0 last frame
    sint16 timer_4;       // 04
    sint16 value_6;       // 06
    sint16 value_8;       // 08
    sint16 count_A;       // 0A: the mouth table's step
    sint16 eyes_C;        // 0C
    sint16 eyes_prev_E;   // 0E
    sint16 mouth_10;      // 10
    sint16 mouth_prev_12; // 12
    uint16 random_14;     // 14
} ST05_TALK;

// A view of STAGE_OBJ with the fields r3_st05's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    sint8 be_flag;   // 00
    uint8 work_id;   // 01
    uint8 id;        // 02
    uint8 type;      // 03
    sint16 value_4;  // 04
    sint16 value_6;  // 06
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 routine_2; // 0A
    uint8 routine_3; // 0B
    union
    {
        struct
        {
            sint8 work_0; // 0C
            sint8 work_1; // 0D
        } b;
        sint16 timer; // 0C
    } u_C;
    union
    {
        struct
        {
            sint8 work_2; // 0E
            sint8 work_3; // 0F
        } b;
        sint16 angle; // 0E
    } u_E;
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STAGE_FIXED value_44;                   // 44
    STAGE_FIXED value_48;                   // 48
    STAGE_FIXED value_4C;                   // 4C
    uint16 value_50;                        // 50
    sint16 value_52;                        // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 value_64;                        // 64
    uint8 reserved68[0x6];                  // 68
    sint16 value_6E;                        // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    sint32 value_78;                        // 78
    sint16 value_7C;                        // 7C
    uint8 reserved7E[0x2];                  // 7E
    sint32 value_80;                        // 80
    uint8 reserved84[0x4];                  // 84
    void *model_88;                         // 88
    uint8 reserved8C[0xC];                  // 8C
    uint8 *anim_98;                         // 98
    uint8 reserved9C[8];                    // 9C
    uint8 value_A4;                         // A4: the animation frame
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[0x4];                  // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    sint16 value_AE;                        // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    sint32 value_B4;                        // B4
    union
    {
        sint8 *flag;               // a flag byte to wait on (func_80126440)
        STAGE_OBJ *part;           // a linked part (func_801260D0)
        STCOM_EFFECT *fx;          // the effect it spawned (func_80126160)
    } u_B8;                        // B8
    sint32 value_BC;               // BC
    sint32 value_C0;               // C0
    STCOM_SVECTOR value_C4;        // C4
    sint32 value_CC;               // CC
    uint8 reservedD0[0x2B];        // D0
    uint8 value_FB;                // FB
    uint8 reservedFC[0x4];         // FC
    STAGE_PART part_100[12];       // 100
    uint8 reserved130[0x18];       // 130
    sint8 value_148[4];            // 148
    uint8 reserved14C[0xC];        // 14C
    STCOM_SVECTOR_W scale;         // 158
    uint8 reserved160[0x8];        // 160
    uint8 value_168;               // 168
    uint8 value_169;               // 169
    uint8 reserved16A[0x16];       // 16A
    STCOM_SVECTOR joint_180[0x18]; // 180: pad is the joint's color
    uint8 reserved240[6];          // 240
    uint8 reserved246[0x2];        // 246
    STAGE_MATRIX matrix_248;       // 248
    uint8 reserved268[0x20];       // 268
    STAGE_MATRIX matrix_288;       // 288
    uint8 reserved2A8[0x60];       // 2A8
    uint16 value_308;              // 308
    uint16 value_30A;              // 30A
    sint16 value_30C;              // 30C
    uint8 reserved30E[0x2];        // 30E
    sint16 value_310;              // 310
    uint8 reserved312[0xA];        // 312
    sint32 value_31C;              // 31C
    uint8 reserved320[0x8];        // 320
    uint16 value_328;              // 328
    sint16 value_32A;              // 32A
    uint16 value_32C;              // 32C
    sint16 value_32E;              // 32E
    sint16 value_330;              // 330
    uint8 reserved332[0xA];        // 332
    sint32 value_33C;              // 33C
    sint32 value_340;              // 340
    sint32 value_344;              // 344
    ST05_FALL fall_348;            // 348
    uint16 value_358;              // 358
    uint8 reserved35A[0x2];        // 35A
    sint32 value_35C;              // 35C
    sint32 value_360;              // 360
    sint32 value_364;              // 364
    uint16 value_368;              // 368
    uint16 value_36A;              // 36A
    sint32 value_36C;              // 36C
    uint8 reserved370[0x2];        // 370
    uint16 value_372;              // 372
    uint8 reserved374[0x4];        // 374
    sint32 value_378;              // 378
    sint32 value_37C;              // 37C
    STAGE_OBJ *value_380;          // 380
    uint8 reserved384[0xBC];       // 384
    uint16 value_440;              // 440
    uint16 value_442;              // 442
    sint16 value_444;              // 444
    uint8 reserved446[0x2];        // 446
    sint16 value_448;              // 448
    sint16 value_44A;              // 44A
    uint8 reserved44C[0x94];       // 44C
    STAGE_FACE face;               // 4E0
    uint8 reserved4F4[0xC];        // 4F4
    ST05_TALK talk_500;            // 500
} ST05_OBJ;

typedef void (*ST05_OBJ_FUNC)(ST05_OBJ *wp);

// A view of STAGE_10C with the fields r3_st05's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 work_id;                     // 01
    uint8 id;                          // 02
    uint8 type;                        // 03
    sint16 value_4;                    // 04
    sint16 value_6;                    // 06
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 routine_2;                   // 0A
    uint8 routine_3;                   // 0B
    sint32 value_C;                    // 0C
    sint32 value_10;                   // 10
    STCOM_SVECTOR position;            // 14
    STAGE_FIXED_VECTOR position_fixed; // 1C
    sint32 value_2C;                   // 2C
    sint32 value_30;                   // 30
    sint32 value_34;                   // 34
    sint32 value_38;                   // 38
    sint32 value_3C;                   // 3C
    sint32 value_40;                   // 40
    sint32 value_44;                   // 44
    sint32 value_48;                   // 48
    sint32 value_4C;                   // 4C
    uint16 value_50;                   // 50
    sint16 value_52;                   // 52
    uint8 reserved54[0x2];             // 54
    sint16 value_56;                   // 56
    sint32 value_58;                   // 58
    sint16 value_5C;                   // 5C
    sint16 value_5E;                   // 5E
    sint16 value_60;                   // 60
    uint8 reserved62[0x2];             // 62
    sint32 value_64;                   // 64
    uint8 reserved68[0x6];             // 68
    sint16 value_6E;                   // 6E
    sint32 value_70;                   // 70
    sint32 value_74;                   // 74
    sint32 value_78;                   // 78
    sint16 value_7C;                   // 7C
    uint8 reserved7E[0x2];             // 7E
    sint32 value_80;                   // 80
    uint8 reserved84[0x4];             // 84
    sint32 value_88;                   // 88
    STAGE_MATRIX matrix_8C;            // 8C
    STCOM_SVECTOR position_AC;         // AC
    sint32 color_B4;                   // B4
    sint32 value_B8;                   // B8
    sint32 value_BC;                   // BC
    sint32 value_C0;                   // C0
    sint32 value_C4;                   // C4
    sint32 value_C8;                   // C8
    sint32 x_CC;                       // CC
    sint32 y_D0;                       // D0
    sint32 z_D4;                       // D4
    uint8 reservedD8[0x4];             // D8
    sint16 radius_DC;                  // DC
    sint16 angle_DE;                   // DE
    sint16 speed_E0;                   // E0
    uint8 reservedE2[0x19];            // E2
    uint8 value_FB;                    // FB
    uint8 reservedFC[0x7];             // FC
    uint8 value_103;                   // 103
    uint8 reserved104[0x3];            // 104
    uint8 value_107;                   // 107
    uint8 value_108;                   // 108
    uint8 reserved109[0x2];            // 109
    uint8 value_10B;                   // 10B
} ST05_10C;

typedef void (*ST05_10C_FUNC)(ST05_10C *wp);

// A view of STAGE_FX with the fields r3_st05's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    uint8 be_flag;   // 00
    uint8 work_id;   // 01
    uint8 id;        // 02
    uint8 type;      // 03
    sint16 value_4;  // 04
    uint8 flags;     // 06
    uint8 value_7;   // 07
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 routine_2; // 0A
    uint8 routine_3; // 0B
    sint8 work_0;    // 0C
    sint8 timer_D;   // 0D (Capcom: work_1)
    sint8 frame_E;   // 0E (Capcom: work_2)
    sint8 type_F;    // 0F (Capcom: work_3)
    sint32 value_10; // 10
    uint32 mode_14;  // 14
    uint32 color_18; // 18
    sint16 x_1C;     // 1C
    sint16 y_1E;     // 1E
    sint16 z_20;     // 20
    uint8 u_22;      // 22
    uint8 v_23;      // 23
    uint16 w_24;     // 24
    uint16 h_26;     // 26
    union
    {
        STAGE_FX *parent;  // the spawner
        STAGE_OBJ *object; // the object it follows
    } u_28;
    STAGE_FIXED x_2C;     // 2C
    STAGE_FIXED y_30;     // 30
    STAGE_FIXED z_34;     // 34
    STAGE_FIXED value_38; // 38
    STAGE_FIXED value_3C; // 3C
    sint32 value_40;      // 40
    sint32 value_44;      // 44
} ST05_FX;

typedef void (*ST05_FX_FUNC)(ST05_FX *wp);

// A draw block (at +0x88 of ST05_PROP): the model, its matrix and the position it is drawn at.
typedef struct
{
    void *data_0;          // 00
    STAGE_MATRIX matrix_4; // 04
    STCOM_SVECTOR pos_24;  // 24
} ST05_DRAW;

// A 0x10C-byte slot that keeps its rotation at +0x54 and its matrix at +0x8C (func_80124E28): the
// props of r3_st05_24E28.c.
typedef struct
{
    sint8 be_flag;                          // 00
    uint8 work_id;                          // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 work_0;                           // 0C: hits left (variant 0)
    uint8 work_1;                           // 0D
    sint8 work_2;                           // 0E: func_80036294's id
    sint8 work_3;                           // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel_4C;                 // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    uint8 reserved66[8];                    // 66
    sint16 value_6E;                        // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    uint8 *data_78;                         // 78
    uint8 reserved7C[0xC];                  // 7C
    ST05_DRAW draw_88;                      // 88
    sint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    sint32 hit_BC;                          // BC
    uint8 reservedC0[0xC];                  // C0
    uint32 value_CC;                        // CC: spin
    uint8 reservedD0[0x3C];                 // D0
} ST05_PROP;

typedef void (*ST05_PROP_FUNC)(ST05_PROP *wp);

void func_80109E70(uint8 *arg0);

void func_80122E60(uint8 *arg0);

void func_80122E74(uint8 *arg0);

void func_80125D5C(STAGE_OBJ *wp);

void func_801253EC(STAGE_OBJ *wp);

void func_8010BE44(STAGE_OBJ *wp);

void func_8010C644(STAGE_OBJ *wp);

void func_801100BC(STAGE_OBJ *wp);

void func_801100DC(STAGE_OBJ *wp);

void func_80112264(STAGE_OBJ *wp);

void func_80110B78(STAGE_OBJ *wp);

void func_801175C8(STAGE_OBJ *wp);

void func_801175E8(STAGE_OBJ *wp);

void func_8011A7C8(STAGE_OBJ *wp);

void func_8011B094(STAGE_OBJ *wp);

void func_8011EBFC(STAGE_OBJ *wp);

void func_80122C34(STAGE_OBJ *wp);

void func_80125390(STAGE_OBJ *wp);

void func_80106074(uint8 index);

void func_80103744(STAGE_ROOM *wp);

sint32 func_80107CC8(STAGE_ROOM *wp);

void func_801279A8(STAGE_OBJ *wp);

void Sce_event_next(void);
void func_801067A0(STAGE_OBJ *wp);

extern STAGE_ROOM2_FUNC D_8012EF08[];
void func_80102A6C(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_80130AFC[];
void func_8010BBC0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801317FC[];
void func_801169F0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80131320[];
void func_8010FE10(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80131830[];
void func_80117344(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801322A0[];
void func_80125354(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801322A8[];
void func_801253B0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801322B8[];
void func_80125600(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801322C4[];
void func_8012563C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801323CC[];
void func_80125FBC(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801323E4[];
void func_80125FF8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80132408[];
void func_80127154(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80137644[];
void func_801278D8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8013764C[];
void func_801279D0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801378A0[];
void func_8012B078(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80137A80[];
void func_8012C9B0(STAGE_OBJ *wp);

void func_80107010(STAGE_ROOM *wp);

void func_80107198(STAGE_ROOM *wp);

void func_80107258(STAGE_ROOM *wp);

void func_80107320(STAGE_ROOM *wp);

void func_80107660(STAGE_ROOM *wp);

void func_80107570(STAGE_ROOM *wp);

void func_801076A4(STAGE_ROOM *wp);

void func_801077D8(STAGE_ROOM *wp);

void func_80107794(STAGE_ROOM *wp);

void func_8010790C(STAGE_ROOM *wp);

void func_801078C8(STAGE_ROOM *wp);

void func_80118640(STAGE_OBJ *wp);

void func_801070D0(STAGE_ROOM *wp);

void func_801073E0(STAGE_ROOM *wp);

void func_801074A8(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_801318D8[];
void func_801186FC(STAGE_OBJ *wp);

void func_8011E704(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80137754[];
void func_8012A920(STAGE_OBJ *wp);

void func_8012B8FC(STAGE_OBJ *wp);

extern ST05_OBJ_FUNC D_80131B10[];
extern ST05_OBJ_FUNC D_80131B1C[];
void func_8011F5A0(ST05_OBJ *wp);
void func_8011EBAC(ST05_OBJ *wp);

extern STAGE_OBJ_FUNC D_80132400[];
void func_80126940(STAGE_OBJ *wp);

void func_80101228(STAGE_ROOM *wp);

void func_8010BFA4(ST05_OBJ *wp);

void func_80123094(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80137A98[];
void func_8005C230(sint32);
void func_8012C9EC(STAGE_OBJ *wp);

void func_80118D1C(STAGE_OBJ *wp);

void func_80106840(STAGE_OBJ *wp);

void func_80102854(STAGE_ROOM *wp);

void func_80106670(STAGE_OBJ *wp);

void func_801183FC(STAGE_OBJ *wp);

void func_801067D0(STAGE_ROOM *wp);

void func_801028D0(uint8 arg0);

void func_80100B5C(STAGE_ROOM *wp);

void func_8012603C(STAGE_OBJ *wp);

void func_8012C1F4(STAGE_OBJ *wp);

void func_8012C29C(STAGE_OBJ *wp);

extern sint8 D_8012E45C[]; // mouth shapes, every second byte (eyes in D_8012E45D)
extern sint8 D_8012E45D[];
void func_8010127C(STAGE_ROOM *wp);

extern STAGE_SLOT_FUNC *D_8012D9C4[];
extern STAGE_SLOT_FUNC *D_8012DB04[];
extern STAGE_SLOT_FUNC D_8012DB2C[];
extern STAGE_SLOT_FUNC D_8012DBEC[];
extern STAGE_SLOT_FUNC D_8012DC1C[];
extern STAGE_SLOT_FUNC D_8012DC30[];

// Used by functions still in assembly (types from their accesses).
extern uint8 D_800987B5;
extern sint32 D_800989FC;
extern STAGE_ACTOR D_8009F108[]; // ROCK_NEO's 0x3C0-byte slots
extern uint8 D_800A395A;
extern uint8 D_800A395B;
extern sint32 D_800A3964;
extern sint32 D_800A3988;
extern sint16 D_800BBCF8[];
extern sint32 D_800BC7D4;
extern STAGE_50 D_800BF118[];
extern uint32 D_800989CC;
extern uint16 D_800C0F96[];
extern sint16 D_800C0F9A;
extern uint8 D_80100384[];
extern sint32 D_8012E438[];
extern sint8 D_8012E45E;
extern sint8 D_8012E45F;
extern sint8 D_8012E466;
extern sint8 D_8012E467;
extern sint16 D_8012E468[];
extern uint8 D_8012E4DC[];
extern uint8 D_8012E60C[];
extern STAGE_ROOM2_FUNC D_8012E740[];
extern STAGE_ROOM2_FUNC D_8012E790[];
extern uint8 D_8012E7E8[];
extern STAGE_SCRIPT_ENTRY D_8012E7FC[];
extern uint8 D_8012E874[];
extern uint8 D_8012E8E8[];
extern uint8 D_8012EDE0[];
extern STAGE_ROOM2_FUNC D_8012EE28[];
extern STAGE_ROOM2_FUNC D_8012EE38[];
extern sint16 D_8012EF00[];
extern uint8 D_8012EF14[];
extern uint8 D_8012EF28[];
extern uint8 D_8012EF3C[];
extern uint8 D_8012EF50[];
extern STAGE_ROOM2_FUNC D_8012F144[];
extern uint8 D_8012F154[];
extern STAGE_ROOM2_FUNC D_8012F3B8[];
extern STAGE_ROOM_FUNC D_80130184[]; // [0] is also read as a byte (0xFF: no script)
extern uint8 D_80130194[];
extern STAGE_ROOM_FUNC D_80130224[]; // [0] is also read as a byte (0xFF: no script)
extern uint8 D_801302AC[];
extern uint8 D_80130774[];
extern uint8 D_80130788[];
extern uint8 D_80130984[];
extern STAGE_SCRIPT_ENTRY D_8013098C[];
extern uint8 D_801309B4[];
extern uint8 D_801309BC[][8];
extern uint8 D_80130A24[];
extern uint8 D_80130A2C[];
extern uint8 D_80130A34[];
extern STCOM_SVECTOR D_80130A3C; // func_80106E38's map cell
extern uint8 D_80130A9C[];
extern uint8 D_80130AA4[];
extern uint8 D_80130B18[];
// Where each variant of func_8010BFF8's actor walks to (x, z) and its turn speed (pad).
extern STCOM_SVECTOR D_80130B24[];
extern uint8 D_80130B6C[];
extern uint8 D_80130B70[][4]; // joints that spark, by the step in D_80130B6C (func_8010CA98)
extern uint8 D_80130B88[];
extern uint8 D_801313BC[];
extern sint32 D_801313C8[];
extern uint8 D_801313D4[];
extern uint8 D_801313D8[];
extern uint8 D_8013143C[];
extern sint16 D_8013179C[];
extern uint16 D_801317AC[];
extern uint8 D_801317B4[];
extern uint8 D_801317B7[];
extern uint8 D_801317BA[];
extern uint8 D_801317C0[3][2]; // the pairs of walkers that can meet
extern uint8 D_801317C8[];
extern uint8 D_801317CC[];
extern sint32 D_801317D0[];
extern uint8 D_80131814[];
extern uint8 D_80131824[];
extern uint8 D_8013184C[];
extern STCOM_SVECTOR D_80131858[]; // points func_801176C0 and func_8011777C turn to
extern sint16 D_80131864;
extern sint32 D_80131898;
extern sint32 D_801318A0;
extern uint16 D_801318B8[];
extern uint8 D_801318C0[];
extern uint8 D_801318CC[];
extern STCOM_SVECTOR D_80131910[]; // the boats' start points (pad: heading), by index_C
extern sint16 D_80131920[];        // the boat's box (its data_78; func_80048EA4)
extern sint16 D_8013192C[];        // 36 roll angles
extern uint8 D_801319C8[];
extern sint8 D_801319D4[][4]; // the boss's areas: x0, z0, x1, z1 in units of 0x200
extern sint8 D_801319D5[];
extern sint8 D_801319D6[];
extern sint8 D_801319D7[];
extern STCOM_SVECTOR D_80131A14[]; // the large actor's targets (ST05_BOSS_CTL target_C0)
extern uint8 D_80131A17[];
extern sint16 D_80131A18[];
extern uint16 D_80131A1A[];
extern uint8 D_80131A1B[];
extern sint16 D_80131A20;
extern uint8 D_80131A34[][4]; // the large actor's next routine: by distance, then at random
extern uint8 D_80131A4C[];
// The holder's animation steps (func_8011DE74): anim, frames, anim, frames, ... from D_80131A70,
// read from the first frame count: step i's frames at [i * 2], its animation at [i * 2 - 1].
extern sint32 D_80131A74[];
extern sint32 D_80131A88;
extern sint32 D_80131AC0;
extern sint8 D_80131B00[];
extern sint8 D_80131B01[];
extern uint8 D_80131B04[];
extern sint16 *D_80131B84;
// The five lip-sync scripts D_80131B84..D_80131B94 read as one table (func_8011EC1C): an array
// element may alias the talk-block stores, so GCC 2.7 keeps the loads in source order.
extern sint16 *D_80131B84_T[] __asm__("D_80131B84");
extern sint16 *D_80131B88;
extern sint16 *D_80131B8C;
extern sint16 *D_80131B90;
extern sint16 *D_80131B94;
extern uint8 D_80131BBC[];
extern uint8 D_80131C9C[];
extern uint8 D_80131CA4[];
extern uint8 D_80131CAC[];
extern uint8 D_80131CB4[];
extern uint8 D_80131CBC[];
extern uint8 D_801321A8[];
extern uint8 D_801322CC[][2]; // points (x, z) in 256-unit steps
extern uint8 D_801322CD[];
extern uint8 D_801322E4[][4]; // [0]: a point of D_801322CC
// Where each variant of func_80125724's prop starts.
extern STCOM_SVECTOR D_8013231C[];
extern STAGE_SCRIPT_ENTRY D_8013232C[];
extern STAGE_SCRIPT_ENTRY D_80132354[];
extern uint16 D_80132390[];
extern uint8 D_801323A0[];
extern uint8 D_801323A8[];
extern uint8 D_801323F4[];
extern uint8 D_80137760[];
extern STAGE_SCRIPT_ENTRY D_8013776C[];
extern STAGE_SCRIPT_ENTRY D_80137780[]; // by STAGE_FRAME & 3
extern STAGE_SCRIPT_ENTRY D_801377D0[]; // by (STAGE_FRAME & 0x30) >> 4
extern STCOM_SVECTOR D_80137820[];      // by work_2 (func_8012AB24)
extern STCOM_SVECTOR D_80137840[][4];   // camera angles by variant and work_2 (func_8012AB24)
extern uint8 D_801378B0[];
extern uint8 D_801378BC[];
extern uint8 D_801378BD[];
// The shop counters' time limits by kind: D_801379F8's 0x34-byte records seen from 0xC bytes earlier.
typedef struct
{
    uint32 limit_0[3];      // 00: by kind
    uint8 reserved0C[0x28]; // 0C
} ST05_LIMIT;

extern ST05_LIMIT D_801379EC[];
extern STAGE_PL_VIEW *D_80137DA0;
extern sint16 D_80137DA8;
extern sint16 D_80137DAC;
extern uint8 D_80137DB0;
extern uint16 D_80137DB4;
extern uint16 D_80137DB8;
extern uint8 D_80137DBC;
extern uint8 D_80137DC4;
extern uint8 D_80137DC5;
extern uint8 D_80137DC6;
extern uint8 D_80137DC7;
extern sint16 D_80137DC8;
extern sint16 D_80137DCA;
extern sint16 D_80137DCC;
extern sint16 D_80137DCE;
extern uint8 D_80137DD4;
extern uint8 D_80137DD5;
extern uint8 D_80137DD6;
extern uint8 D_80137DD7;
extern sint16 D_80137DD8;
extern sint16 D_80137DDA;
extern sint16 D_80137DDC;
extern sint16 D_80137DDE;
extern uint8 D_80137DF8;
extern sint16 D_80137E02;
extern sint16 D_80137E04;
extern sint16 D_80137E06;
extern sint16 D_80137E08;
extern sint16 D_80137E0A;
extern sint16 *D_80137E0C;
extern sint32 D_80137E10;
extern uint8 D_80137E78;
extern STCOM_MATRIX D_80137E90;
extern STCOM_MATRIX D_80137EB0;
extern STCOM_MATRIX D_80137ED0;
extern STCOM_MATRIX D_80137EF0;
extern STCOM_MATRIX D_80137F10;
extern STCOM_SVECTOR D_80137F30[]; // one vector; an array keeps its address in a register (func_80112284)
extern STCOM_FIXED_VECTOR D_80137F38;
extern STCOM_FIXED_VECTOR D_80137F58;
extern sint32 D_80137F6C;
extern sint32 D_80137F70;
extern sint32 D_80137F80;
extern sint32 D_80137F88;
extern sint16 *D_80137F84;
extern sint16 *D_80137F8C;
extern sint32 D_80137F98;
extern sint32 D_80137F9C;
// A scale vector whose y and z func_80127A0C writes as their own symbols (D_80137FA4, D_80137FA8).
extern STCOM_FIXED_VECTOR D_80137FA0;
extern sint32 D_80137FA4;
extern sint32 D_80137FA8;
extern sint16 D_80137FB0;
extern uint8 D_80138018;
extern sint32 D_80138024;
extern uint8 D_80138034;
extern sint32 D_8013803C;
extern sint32 D_80138040;
extern sint32 D_80138044;
extern sint32 D_80138048;
extern sint32 D_8013804C;
extern sint16 D_8013807C;
extern uint8 D_80138084;
extern STAGE_OBJ *D_80138088[2]; // [1] is D_8013808C, the animal func_801179D4 sets up
extern sint32 D_80138098;
extern sint32 D_801380A8;
extern sint32 D_801380AC;
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern sint32 D_80164008[];

void func_80112230(ST05_OBJ *wp);

extern ST05_OBJ_FUNC D_80130B3C[];
void func_8010C1A8(ST05_OBJ *wp);

void func_80110344(ST05_OBJ *wp);

extern STAGE_OBJ_FUNC D_80130AF0[];

void func_80031A4C(void *wp);

void func_80052528(void *wp);

extern STAGE_REC D_80137E18[];

void func_8002FBF4(void *wp);

extern sint16 *D_80131C64[];
extern sint16 *D_80131C80[];

extern void *D_80130638[];

extern STAGE_ROOM2_FUNC D_801307FC[];

void Sce_flag_off(sint32 flag);

extern STAGE_FACE16 D_80137E00;
extern sint16 *D_8012F43C[];
extern sint16 *D_8012F448[];
extern STAGE_FX D_800A3B40[];
sint32 func_80048E18(void *arg);
void func_80105E2C(sint8 index);
uint8 func_80107D68(void);

extern void *D_8012DCFC[];
extern void *D_8012DFB8[];
extern void *D_8012E1F4[];
extern uint8 D_8012E208[][0x28];
extern uint8 D_8012E2D0[][8];
extern STCOM_SVECTOR D_8012E44C[];
uint32 Stage_idx_model_set(sint32 idx, uint32 key);
sint32 Map_cell_get(STCOM_SVECTOR *pos);

void Sound_call(sint32 id, sint32 a1, sint32 a2);
void func_8003187C(void *wp);
sint32 Sound_seq_is_eos(sint32 arg);
void stcom36_func_0028(sint8 room);
void func_801267B0(STAGE_OBJ *wp, uint8 kind);
void func_80106B28(void);

// A 0x20-byte control block of ST05_ACTOR (at +0x348 and +0x368).
typedef struct
{
    uint16 flags_0;         // 00
    uint16 value_2;         // 02
    sint16 timer_4;         // 04
    sint16 value_6;         // 06
    sint16 value_8;         // 08
    sint16 timer_A;         // 0A
    STCOM_SVECTOR target_C; // 0C: where the actor turns or walks to
    uint32 hit_14;          // 14: damage in the low 24 bits, kind bits above
    uint16 value_18;        // 18
    uint16 value_1A;        // 1A
    uint16 value_1C;        // 1C
    uint16 value_1E;        // 1E
} ST05_ACTOR_CTL;

// A 0x3C0-byte work slot as this stage's villagers use it: STAGE_ACTOR with the blocks at +0x348
// and +0x368 named.
typedef struct
{
    sint8 be_flag;                          // 00
    uint8 work_id;                          // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 timer_C;                          // 0C (Capcom: work_0)
    sint8 work_1;                           // 0D
    sint8 work_2;                           // 0E
    sint8 work_3;                           // 0F: a timer or flags
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel_4C;                 // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    sint16 spin_66;                         // 66
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    uint8 *data_78;                         // 78
    uint8 reserved7C[0x28];                 // 7C
    uint8 value_A4;                         // A4
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    sint16 turn_B4;                         // B4
    uint8 reservedB6[0xE];                  // B6
    STCOM_SVECTOR value_C4;                 // C4
    uint8 reservedCC[0x44];                 // CC
    uint8 frame_110;                        // 110: the face frame
    uint8 reserved111[0x47];                // 111
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180: the talk camera's point
    uint8 reserved188[0x1C0];               // 188
    ST05_ACTOR_CTL ctl;                     // 348
    ST05_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST05_ACTOR;

extern ST05_ACTOR *D_8013808C; // the animal func_801179D4 sets up (D_80138088[1])

typedef void (*ST05_ACTOR_FUNC)(ST05_ACTOR *wp);

// ST05_ACTOR_CTL as func_8010C1F4's family uses it: the point it backs away from at +0x1C.
typedef struct
{
    uint16 flags_0;         // 00
    uint16 value_2;         // 02
    sint16 timer_4;         // 04
    sint16 value_6;         // 06
    sint16 value_8;         // 08
    sint16 timer_A;         // 0A: damage taken while guarding
    STCOM_SVECTOR target_C; // 0C
    uint32 hit_14;          // 14: damage in the low 24 bits, kind bits above
    uint16 value_18;        // 18
    uint16 value_1A;        // 1A
    STCOM_SVECTOR from_1C;  // 1C
    uint8 track_24[0x10];   // 24: Track_reset's record
    sint16 sparks_34;       // 34: spark bursts so far (func_8010CA98)
} ST05_GUARD_CTL;

// A 0x3C0-byte slot of func_8010C1F4's family: ST05_ACTOR's fields, its block at +0x348, then a
// tracking record at +0x36C.
typedef struct
{
    sint8 be_flag;                          // 00
    uint8 work_id;                          // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 reserved04[2];                    // 04
    uint8 flags;                            // 06: 0x80 keeps it when far away
    uint8 reserved07;                       // 07
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 timer_C;                          // 0C (Capcom: work_0)
    sint8 work_1;                           // 0D
    sint8 work_2;                           // 0E
    sint8 work_3;                           // 0F: a timer or flags
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel_4C;                 // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    sint16 spin_66;                         // 66
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    uint8 *data_78;                         // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80: distance to the player (squared?)
    uint8 reserved84[0x20];                 // 84
    uint8 value_A4;                         // A4
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    sint16 turn_B4;                         // B4
    uint8 reservedB6[0xE];                  // B6
    STCOM_SVECTOR value_C4;                 // C4
    uint8 reservedCC[0x44];                 // CC
    uint8 frame_110;                        // 110: the face frame
    uint8 reserved111[0x47];                // 111
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joint_180[0x18];          // 180: pad is the joint's color
    uint8 reserved240[0x108];               // 240
    ST05_GUARD_CTL ctl;                     // 348
    uint8 reserved37E[0x42];                // 37E
} ST05_GUARD;

typedef void (*ST05_GUARD_FUNC)(ST05_GUARD *wp);

extern uint8 D_80130B60[];
void func_8010C37C(ST05_GUARD *wp);

extern ST05_ACTOR_FUNC D_80131820[];
void func_80116E8C(ST05_ACTOR *wp);

void func_80126D98(STAGE_SHOT *wp);
void func_80126F10(STAGE_SHOT *wp);
void func_80127054(STAGE_SHOT *wp, sint32 arg);

sint32 SquareRoot0(sint32 v);
sint32 func_80118D74(STCOM_SVECTOR *a, STCOM_SVECTOR *b);

sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
extern STCOM_FIXED_VECTOR D_80137F68;
sint32 func_801171D0(ST05_ACTOR *wp);

extern uint32 stcom36_D_0000;
extern STAGE_SPAWNED *stcom36_E2_0000[];

void func_80105F2C(sint8 index);

void func_801071DC(STAGE_ROOM *wp);
void func_801074F4(STAGE_ROOM *wp);

void func_80107364(STAGE_ROOM *wp);

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
} ST05_SHL;

// Player_work's signed bytes past STCOM_PL_WORK's fields.
#define ST05_PL_SBYTE(offset) (*((sint8 *)&Player_work + (offset)))

void func_800354E0(sint32 bit);
sint16 func_80039B80(void);
sint32 func_80037634(void *player, sint32 arg);
void func_80126990(ST05_SHL *wp);

extern ST05_ACTOR_FUNC D_80131974[];

extern STAGE_ROOM_FUNC D_8012F458[];

void func_80105220(STAGE_ROOM_WORK *wp);

// A node of the course the r3_st05 walker follows (func_80116528): its id, a position and the
// neighbouring node in each of four directions (-1: none).
typedef struct
{
    uint16 id_0;         // 0
    uint8 reserved2[2];  // 2
    sint16 x_4;          // 4: centre
    sint16 z_6;          // 6
    sint16 w_8;          // 8: extent
    sint16 d_A;          // A
    sint8 link_C[4];     // C
    uint8 reserved10[4]; // 10
} ST05_NODE;

extern ST05_NODE *D_80131790[]; // each variant's course
extern sint16 D_801317A4[];

// A flag per direction (the walker's open ways); D_801004E0 holds all zeros.
typedef struct
{
    uint8 dir[4];
} ST05_DIRS;

extern const ST05_DIRS D_801004E0;

// The walker's control block at +0x308 of its 0x3C0-byte slot.
typedef struct
{
    uint16 flags_0;          // 308
    uint16 random_2;         // 30A
    sint16 timer_4;          // 30C
    uint8 reserved06[2];     // 30E
    uint16 value_8;          // 310: or'ed into the hit attributes
    sint16 value_A;          // 312
    STCOM_SVECTOR hit_pos_C; // 314
    sint32 hit_14;           // 31C
    uint8 reserved18[0xC];   // 320
    uint8 track_24[0x10];    // 32C: func_8003648C
    STAGE_OBJ *part_34;      // 33C
    ST05_NODE *node_38;      // 340: the node it walks from
    ST05_NODE *node_3C;      // 344: the node it walks to
    STCOM_SVECTOR target_40; // 348: where it walks
    sint8 value_48;          // 350
    sint8 node_id_49;        // 351
    sint8 dir_4A;            // 352
    sint8 value_4B;          // 353
    uint16 value_4C;         // 354
    uint16 angle_4E;         // 356: a wheel angle (scratchpad 0x1F800138)
    uint16 mask_50;          // 358
    sint16 value_52;         // 35A
    sint32 life_54;          // 35C
    uint8 reserved58[0x60];  // 360
} ST05_WALKER_CTL;

// A 0x3C0-byte slot that walks a course of nodes (ST05_OBJ's fields, then its control block).
typedef struct
{
    sint8 be_flag;   // 00
    uint8 work_id;   // 01
    uint8 id;        // 02
    uint8 type;      // 03
    sint16 value_4;  // 04
    sint16 value_6;  // 06
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 routine_2; // 0A
    uint8 routine_3; // 0B
    union
    {
        struct
        {
            sint8 work_0; // 0C
            sint8 work_1; // 0D
        } b;
        sint16 timer; // 0C
    } u_C;
    union
    {
        struct
        {
            sint8 work_2; // 0E
            sint8 work_3; // 0F
        } b;
        sint16 angle; // 0E
    } u_E;
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    sint16 speed_44;                        // 44
    uint8 reserved46[2];                    // 46
    STAGE_FIXED value_48;                   // 48
    sint16 accel_4C;                        // 4C
    uint8 reserved4E[2];                    // 4E
    uint16 value_50;                        // 50
    sint16 value_52;                        // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 value_64;                        // 64
    sint16 turn_66;                         // 66
    uint8 reserved68[0x6];                  // 68
    sint16 value_6E;                        // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    uint8 *data_78;                         // 78
    sint16 value_7C;                        // 7C
    uint8 reserved7E[0x2];                  // 7E
    uint32 value_80;                        // 80
    uint8 reserved84[0x4];                  // 84
    void *model_88;                         // 88
    uint8 reserved8C[0xC];                  // 8C
    uint8 *anim_98;                         // 98
    uint8 reserved9C[8];                    // 9C
    uint8 value_A4;                         // A4: the animation frame
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[0x4];                  // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    sint16 value_AE;                        // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    sint32 value_B4;                        // B4
    sint32 value_B8;                        // B8
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    sint32 value_CC;                        // CC
    uint8 reservedD0[0x2B];                 // D0
    uint8 value_FB;                         // FB
    uint8 reservedFC[0x4];                  // FC
    STAGE_PART part_100[12];                // 100
    uint8 reserved130[0x18];                // 130
    sint8 value_148[4];                     // 148
    uint8 reserved14C[0xC];                 // 14C
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x8];                 // 160
    uint8 value_168;                        // 168
    uint8 value_169;                        // 169
    uint8 reserved16A[0x16];                // 16A
    STCOM_SVECTOR pos_180;                  // 180
    uint8 reserved188[0xC0];                // 188
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0x60];                // 2A8
    ST05_WALKER_CTL ctl;                    // 308
} ST05_WALKER;

// The record func_80036294 returns (by id): a kind, a counter, a timer and flags.
typedef struct
{
    uint8 reserved00[2]; // 00
    uint8 id;            // 02
    uint8 reserved03[9]; // 03
    sint8 value_C;       // 0C
    sint8 timer_D;       // 0D
    uint8 reserved0E;    // 0E
    uint8 flags_F;       // 0F
} ST05_LINK;

ST05_LINK *func_80036294(sint32 id);

// Player_work with its vectors at +0xC4 and +0x3A8 (r3_st14's ST14_PL_VIEW).
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 work_id;                     // 01
    uint8 reserved02[6];               // 02
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 reserved0A[2];               // 0A
    sint8 step_C;                      // 0C: a lesson's step (func_8012656C)
    sint8 count_D;                     // 0D
    uint8 reserved0E[6];               // 0E
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x28];            // 2C
    STCOM_SVECTOR rotation;            // 54
    uint8 reserved5C[0x61];            // 5C
    uint8 flags_bd;                    // BD
    uint8 reservedBE[6];               // BE
    STCOM_SVECTOR value_C4;            // C4
    uint8 reservedCC[0x58];            // CC
    uint16 value_124;                  // 124: STAGE_PL_VIEW value_124
    uint8 reserved126[2];              // 126
    uint16 pad_128;                    // 128: buttons
    uint16 pad_12A;                    // 12A
    uint8 reserved12C[0xC];            // 12C
    uint16 pad_138;                    // 138
    uint8 reserved13A[0x26E];          // 13A
    STCOM_SVECTOR joint_3A8[15];       // 3A8: ROCK_NEO's pos_3a8
    uint8 reserved420[8];              // 420
    STCOM_FIXED_VECTOR push_428;       // 428: a 16.16 position it is pushed to
    STCOM_SVECTOR push_438;            // 438
    sint16 value_440;                  // 440
    sint16 angle_442;                  // 442
    sint16 value_444;                  // 444
    uint8 reserved446[2];              // 446
    uint8 value_448;                   // 448: its routine request
    uint8 reserved449[0x33B];          // 449
} ST05_PL_VIEW;

// The control block at +0x328 of a wheeled cart's slot (func_80111CEC's family).
typedef struct
{
    uint16 flags_0;             // 328: bit 0 ends the routine, bit 8 the player is near
    uint16 value_2;             // 32A
    sint16 timer_4;             // 32C
    sint16 value_6;             // 32E
    uint16 value_8;             // 330: or'ed into the hit attributes
    sint16 timer_A;             // 332
    STCOM_SVECTOR hit_pos_C;    // 334
    sint32 value_14;            // 33C: func_800341BC's result
    sint32 value_18;            // 340
    uint8 reserved1C[8];        // 344
    uint8 track_24[0x10];       // 34C: func_800364B0
    ST05_LINK *link_34;         // 35C: func_80036294's record
    sint16 timer_38;            // 360
    sint16 side_3A;             // 362: joint_180's index (3 or 5)
    sint16 *value_3C;           // 364: points at value_40
    sint16 value_40[2];         // 368
    STAGE_OBJ *part_44;         // 36C
    sint32 joint_48;            // 370: the joint func_80111898 turns
    STCOM_EFFECT *fx_4C;        // 374
    struct ST05_PROP_B *obj_50; // 378: a Open_SHL_WORK slot
    ST05_PL_VIEW *pl_54;        // 37C: the player (func_801134E0)
    sint32 value_58[2];         // 380
} ST05_WAGON_CTL;

// A 0x3C0-byte slot of a wheeled cart (ST05_WALKER's fields, then its control block at +0x328).
typedef struct
{
    sint8 be_flag;   // 00
    uint8 work_id;   // 01
    uint8 id;        // 02
    uint8 type;      // 03
    sint16 value_4;  // 04
    sint16 value_6;  // 06
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 routine_2; // 0A
    uint8 routine_3; // 0B
    union
    {
        struct
        {
            sint8 work_0; // 0C
            sint8 work_1; // 0D
        } b;
        sint16 timer; // 0C
    } u_C;
    union
    {
        struct
        {
            sint8 work_2; // 0E
            sint8 work_3; // 0F
        } b;
        sint16 angle; // 0E
    } u_E;
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    sint16 speed_44;                        // 44
    uint8 reserved46[2];                    // 46
    STAGE_FIXED value_48;                   // 48
    sint16 accel_4C;                        // 4C
    uint8 reserved4E[2];                    // 4E
    uint16 value_50;                        // 50
    sint16 value_52;                        // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 value_64;                        // 64
    sint16 turn_66;                         // 66
    uint8 reserved68[0x6];                  // 68
    sint16 value_6E;                        // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    uint8 *data_78;                         // 78
    sint16 value_7C;                        // 7C
    uint8 reserved7E[0x2];                  // 7E
    uint32 value_80;                        // 80
    uint8 reserved84[0x4];                  // 84
    void *model_88;                         // 88
    uint8 reserved8C[0xC];                  // 8C
    uint8 *anim_98;                         // 98
    uint8 reserved9C[8];                    // 9C
    uint8 value_A4;                         // A4: the animation frame
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[0x4];                  // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    sint16 value_AE;                        // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    sint32 value_B4;                        // B4
    sint32 value_B8;                        // B8
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint16 value_C8;                        // C8
    sint16 timer_CA;                        // CA
    sint32 value_CC;                        // CC
    uint8 reservedD0[0x2B];                 // D0
    uint8 value_FB;                         // FB
    uint8 reservedFC[0x4];                  // FC
    STAGE_PART part_100[12];                // 100
    uint8 reserved130[0x18];                // 130
    sint8 value_148[4];                     // 148
    uint8 reserved14C[0xC];                 // 14C
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x8];                 // 160
    uint8 value_168;                        // 168
    uint8 value_169;                        // 169
    uint8 reserved16A[0x16];                // 16A
    STCOM_SVECTOR joint_180[6];             // 180: 0 the centre, 1 the hitch, 3 and 5 the sides
    uint8 reserved1B0[0x38];                // 1B0
    STAGE_MATRIX matrix_1E8[6];             // 1E8: by joint_180's index
    uint8 reserved2A8[0x60];                // 2A8
    uint8 reserved308[0x20];                // 308
    ST05_WAGON_CTL ctl;                     // 328
    uint8 reserved388[0x38];                // 388
} ST05_WAGON;

typedef void (*ST05_WAGON_FUNC)(ST05_WAGON *wp);

extern ST05_WAGON_FUNC D_80131380[];
extern ST05_WAGON_FUNC D_80131398[];
sint32 func_800364B0(void *track, void *wp, sint32 angle);

typedef void (*ST05_WALKER_FUNC)(ST05_WALKER *wp);

extern ST05_WALKER_FUNC D_801313DC[];
extern ST05_WALKER_FUNC D_801313F8[];
extern ST05_WALKER_FUNC D_80131424[];
extern ST05_WALKER_FUNC D_80131430[];
void func_801146EC(ST05_WALKER *wp);
void func_8011472C(ST05_WALKER *wp);
sint32 func_80116254(ST05_WALKER *wp);
sint32 func_80116380(ST05_WALKER *wp);
void func_80116528(ST05_WALKER *wp);
void Track_stop(void *track);
void Track_reset(void *track, uint8 arg1, uint32 arg2);
sint32 Obj_ceiling_height_get(void *wp);

// A ROCK_NEO record per kind (D_80098844), as the walker reads it.
typedef struct
{
    uint8 reserved00[8]; // 00
    uint8 life_8;        // 08
    uint8 limit_9;       // 09: damage that knocks it back (ST05_VILLAGER_CTL timer_A)
    uint8 life_A[5];     // 0A: by variant, in units of 32
    uint8 track_F;       // 0F
    uint8 reserved10[8]; // 10
    uint8 life_18;       // 18: func_8010C1F4's guard
    uint8 limit_19;      // 19: the damage it guards before it backs away
} ST05_KIND;

extern ST05_KIND **D_80098844;
extern ST05_KIND **D_8009884C; // the boss's kinds (func_8011D830 reads life_A[0])

// The walkers' shared state outside the module.
extern STAGE_10C *D_80138094;
extern STAGE_OBJ *D_801380A0[]; // each variant's part
extern STAGE_OBJ *D_801380A4;   // D_801380A0[1]

// D_801380A0 as func_8010A21C reads it: the parts are villagers.
#define ST05_VILLAGERS ((ST05_VILLAGER **)D_801380A0)
extern ST05_WALKER *D_801380B8[];

// The walker passes only two arguments (retail leaves a2 as the call before left it).
void func_80047148(void *wp, STCOM_SVECTOR *pos);
sint32 func_80115E98(ST05_WALKER *wp); // callers copy v0 unextended: an int result
sint16 func_801160F8(ST05_WALKER *wp);

// Fixed data area words outside the module (scene state).
extern sint32 D_80138020;
extern sint32 D_80138078;
extern sint32 D_80138080;

// The pair of walkers func_80113E6C checks, with their parts, and the distances of all pairs.
extern STAGE_OBJ *D_80137F48;
extern STAGE_OBJ *D_80137F4C;
extern ST05_WALKER *D_80137F50;
extern ST05_WALKER *D_80137F54;
extern uint32 D_80138028[3];

void func_8005D620(void *wp, sint32 a1, sint32 a2, sint32 a3, sint32 a4);

extern STAGE_OBJ_FUNC D_80137AA4[];

extern STAGE_SLOT_FUNC D_80132190[];
void func_80122BA4(STAGE_PROP *wp);

// A 0x5A4-byte slot with a word at +0x524 that enables its shadow (func_8011DDF8).
typedef struct
{
    sint8 be_flag;    // 00
    uint8 work_id;    // 01
    uint8 id;         // 02
    uint8 type;       // 03
    uint8 value_4;    // 04
    uint8 reserved05; // 05
    uint8 flags;      // 06
    uint8 reserved07; // 07
    uint8 routine_0;  // 08
    uint8 routine_1;  // 09
    uint8 routine_2;  // 0A
    uint8 routine_3;  // 0B
    union
    {
        struct
        {
            sint8 work_0; // 0C
            sint8 work_1; // 0D
        } b;
        sint16 timer; // 0C
    } u_C;
    union
    {
        struct
        {
            sint8 work_2; // 0E
            sint8 work_3; // 0F
        } b;
        sint16 angle; // 0E
    } u_E;
    uint8 *data_10;                         // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STAGE_FIXED value_44;                   // 44
    STAGE_FIXED value_48;                   // 48
    STAGE_FIXED value_4C;                   // 4C
    sint16 value_50;                        // 50: with value_4C, the acceleration
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0xA];                  // 64
    sint16 life_6E;                         // 6E
    uint8 reserved70[0x8];                  // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[0xC];                  // 7C
    void *model_88;                         // 88
    uint8 reserved8C[0xC];                  // 8C
    uint8 *anim_98;                         // 98: current animation frame
    uint8 reserved9C[0x8];                  // 9C
    uint8 value_A4;                         // A4
    uint8 reservedA5[0x2];                  // A5
    sint8 value_A7;                         // A7
    uint8 reservedA8[0x4];                  // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2: life_6E before this frame's hits
    uint8 reservedB4[0x4C];                 // B4
    uint8 value_100;                        // 100
    uint8 reserved101[0xF];                 // 101
    uint8 value_110;                        // 110
    uint8 reserved111[0x37];                // 111
    sint8 value_148[4];                     // 148
    uint8 reserved14C[0xC];                 // 14C
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x26];                // 160
    STAGE_PAL pal[24];                      // 186
    uint8 reserved246[2];                   // 246
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0x60];                // 2A8
    void *owner_308;                        // 308: the object that spawned it
    uint8 reserved30C[0xB4];                // 30C
    uint8 ext_3C0[0x160];                   // 3C0
    STAGE_ACTOR *target_520;                // 520: the slot of kind 0x2A it holds
    sint32 value_524;                       // 524
} ST05_HOLDER;

typedef void (*ST05_HOLDER_FUNC)(ST05_HOLDER *wp);

extern ST05_HOLDER_FUNC D_80131A5C[];

// A 0x24-byte event slot that cycles two four-color records (func_80127224).
typedef struct
{
    uint8 be_flag;          // 00
    uint8 work_id;          // 01
    uint8 reserved02[6];    // 02
    uint8 routine_0;        // 08
    uint8 reserved09[0x13]; // 09
    uint32 *colors_1C[2];   // 1C: each four pairs of words
} ST05_GLOW_EV;

void func_801200DC(STAGE_FACE16 *face, sint32 index);

// Scene_work's byte at +7 through its literal address (func_8011FBA4 reads and bumps it; a
// symbol address would be kept in a register).
#define ST05_SCENE_STEP (STAGE_SCENE_PTR->reserved00[7])

// Per variant: an animation and a value (D_80131890; func_80118684, func_80118748).
typedef struct
{
    sint32 anim_0;  // 0
    sint32 value_4; // 4
} ST05_VARIANT_ANIM;

extern ST05_VARIANT_ANIM D_80131890[];
// The same table read from the first value, as func_80117AD8 reads it: variant i's value at [i * 2],
// its animation at [i * 2 - 1] (as D_80131A74).
extern sint32 D_80131894[];

extern ST05_ACTOR_FUNC D_80131358[];

typedef void (*ST05_FALL_FUNC)(ST05_OBJ *wp, STAGE_SCENE_WORK *scene, ST05_FALL *fall);

extern ST05_FALL_FUNC D_80131344[];

extern ST05_ACTOR_FUNC D_8013132C[];

extern ST05_ACTOR_FUNC D_8013183C[];

extern ST05_ACTOR_FUNC D_80131868[];

void func_80117490(ST05_ACTOR *wp);
void func_8010FF58(ST05_ACTOR *wp);

extern ST05_OBJ_FUNC D_801323AC[];

extern STAGE_CAM Sce_camera_work;

void func_8010BD0C(ST05_ACTOR *wp);
void func_8010BBFC(ST05_ACTOR *wp);
extern ST05_ACTOR_FUNC D_80130B08[];

extern STAGE_ROOM_FUNC D_80130970[];
extern STAGE_ROOM_FUNC *D_80130930[];

void func_8001E4C4(void *a, void *b);

sint32 func_80048EA4(STCOM_SVECTOR *pos, void *a1, sint32 a2, sint32 a3);
void func_8012B44C(STAGE_OBJ50 *wp);

void func_8001E390(sint32 id);

// A 0x34-byte record of the shop counters (by work slot work_3): where func_8012B680 puts the
// player, and func_8012B948's numbers.
typedef struct
{
    sint32 value_0;         // 00
    sint32 value_4[3];      // 04: by kind
    sint32 value_10;        // 10
    uint8 value_14[4];      // 14
    sint16 x_18;            // 18
    sint16 z_1A;            // 1A
    sint16 angle_1C;        // 1C
    uint8 reserved1E[0x16]; // 1E
} ST05_SPOT;

extern ST05_SPOT D_801379F8[];

// A shop counter's item to put out (func_8012B544): position, variant and a flag; x == 0 ends the list.
typedef struct
{
    sint16 x_0;      // 0
    sint16 z_2;      // 2
    uint8 variant_4; // 4
    uint8 flag_5;    // 5
} ST05_ITEM;

// A position in a list that ends with x == 0.
typedef struct
{
    sint16 x_0; // 0
    sint16 z_2; // 2
} ST05_SPOT_POS;

// The shop counters' 0x34-byte records start here; ST05_SPOT views the same records from +0x14.
typedef struct
{
    ST05_ITEM *items_0;     // 00
    ST05_SPOT_POS *spots_4; // 04
    uint8 reserved08[0x2C]; // 08
} ST05_COUNTER;

extern ST05_COUNTER D_801379E4[];

// A 0x3C0-byte work slot as this stage's villagers use it: STAGE_ACTOR with the blocks at +0x348
// and +0x368 named.
typedef struct
{
    sint8 be_flag;                          // 00
    uint8 work_id;                          // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 timer_C;                          // 0C (Capcom: work_0)
    sint8 work_1;                           // 0D
    sint8 work_2;                           // 0E
    uint8 work_3;                           // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    uint8 reserved66[8];                    // 66
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[0x28];                 // 7C
    uint8 value_A4;                         // A4
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0x10];                 // B4
    STCOM_SVECTOR value_C4;                 // C4
    uint8 reservedCC[0x8C];                 // CC
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180: the talk camera's point
    uint8 reserved188[0x1C0];               // 188
    ST05_ACTOR_CTL ctl;                     // 348
    ST05_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST05_ACTOR_B;

void stcom01_func_0000(ST05_ACTOR_B *wp);
extern STAGE_STCOM15_FUNC_348 D_80130A44[];
void func_80107E08(STAGE_STCOM15_WORK_348 *wp);

// The block at +0xBC of ST05_PROP_B (STCOM31_CTL's layout).
typedef struct
{
    uint16 flags_0;        // BC: 1 ends the state, 2 once it has landed
    uint16 random_2;       // BE: rand() each frame
    sint16 timer_4;        // C0
    uint16 reserved6;      // C2
    sint32 hit_8;          // C4: func_800341BC's result
    uint8 reservedC[0x44]; // C8
} ST05_PROP_CTL;

// A 0x10C-byte slot (Open_SHL_WORK) of a prop drawn as a model, laid out as stcom31's vehicle
// (STCOM31_WORK); STAGE_PROP describes the same slot with the velocity as words.
typedef struct ST05_PROP_B ST05_PROP_B;

struct ST05_PROP_B
{
    sint8 be_flag;                          // 00
    uint8 work_id;                          // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 work_0;                           // 0C: heading / 0x200
    uint8 work_1;                           // 0D
    uint8 work_2;                           // 0E
    uint8 work_3;                           // 0F
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR_W rotation;               // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    union
    {
        sint16 h[2];
        sint32 w;
    } spin_64;              // 64: [1] a turn speed
    uint8 reserved68[6];    // 68
    sint16 value_6E;        // 6E
    sint32 value_70;        // 70
    sint32 value_74;        // 74
    void *data_78;          // 78
    uint8 reserved7C[0x10]; // 7C
    STCOM_MATRIX matrix;    // 8C
    STCOM_SVECTOR pos_AC;   // AC
    uint32 color_B4;        // B4
    uint8 reservedB8[4];    // B8
    ST05_PROP_CTL ctl;      // BC
};

typedef void (*ST05_PROP_FUNC_B)(ST05_PROP_B *wp);

extern ST05_PROP_FUNC_B D_80132184[];
void func_801228EC(ST05_PROP_B *wp);

void func_80122A9C(ST05_PROP_B *wp);

void func_80122E88(ST05_PROP_B *wp);

void func_80122FE4(ST05_PROP_B *wp);

typedef struct
{
    uint8 be_flag;       // 00
    uint8 work_id;       // 01
    uint8 reserved02[2]; // 02
    uint8 value_4;       // 04
    uint8 delay_5[3];    // 05: per lift
    union
    {
        sint8 state[4];  // 08: per lift: 0 rising, 1 sinking
        uint8 routine_0; // 08
        uint32 word;
    } u_8;
    uint16 cell_C[3];    // 0C: per lift, its map object (Map_cell_get)
    uint8 reserved12[2]; // 12
    sint16 value_14[3];  // 14
    uint8 reserved1A[2]; // 1A
    uint32 *color_1C[2]; // 1C
} ST05_EVENT;

// A model part as func_80127190 reads it from a Stage_hed_model_get record: its colors at +0x24.
typedef struct
{
    uint8 reserved00[0x24]; // 00
    uint32 *color_24;       // 24: four words of two colors each
} ST05_MODEL_PART;

// The model record Stage_hed_model_get returns (key & 0xFFFFFF).
typedef struct
{
    uint8 reserved00[0x18];      // 00
    ST05_MODEL_PART *part_18[2]; // 18
} ST05_MODEL;

void func_80127190(ST05_EVENT *wp);

// A 0x10C-byte slot (Open_SHL_WORK) a villager carries above its head and then throws.
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 work_id;                     // 01
    uint8 id;                          // 02
    uint8 type;                        // 03
    uint8 reserved04[4];               // 04
    uint8 routine_0;                   // 08
    uint8 reserved09[0xB];             // 09
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x38];            // 2C
    sint16 turn_64;                    // 64: direction it is thrown in
    uint8 reserved66[0x36];            // 66
    sint32 value_9C;                   // 9C: throw speed
    sint32 value_A0;                   // A0: throw height
    uint8 reservedA4[0x68];            // A4
} ST05_HELD;

// The control block at +0x348 of ST05_VILLAGER.
typedef struct
{
    uint16 flags_0;         // 00
    uint16 value_2;         // 02
    sint16 timer_4;         // 04
    sint16 value_6;         // 06
    sint16 value_8;         // 08
    sint16 timer_A;         // 0A
    STCOM_SVECTOR target_C; // 0C: where the actor turns or walks to
    uint32 hit_14;          // 14: damage in the low 24 bits, kind bits above
    uint32 value_18;        // 18
    STCOM_SVECTOR from_1C;  // 1C: where the hit came from (pad bit 0: use it)
    uint8 track_24[0x10];   // 24: Track_reset's record
    uint32 range_34;        // 34
    ST05_HELD *other_38;    // 38: the slot it carries
    uint8 reserved3C[4];    // 3C
} ST05_VILLAGER_CTL;

typedef struct ST05_VILLAGER ST05_VILLAGER;

// A 0x3C0-byte work slot as this stage's villagers use it: STAGE_ACTOR with the block at +0x348
// named.
struct ST05_VILLAGER
{
    sint8 be_flag;                          // 00
    uint8 work_id;                          // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 value_4;                          // 04
    uint8 reserved05;                       // 05
    uint8 flags;                            // 06
    uint8 reserved07;                       // 07
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 timer_C;                          // 0C (Capcom: work_0)
    sint8 work_1;                           // 0D
    sint8 work_2;                           // 0E
    sint8 work_3;                           // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel_4C;                 // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    sint16 spin_66;                         // 66
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80
    uint8 reserved84[0x18];                 // 84
    sint32 value_9C;                        // 9C
    sint32 value_A0;                        // A0
    uint8 value_A4;                         // A4
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0x10];                 // B4
    STCOM_SVECTOR value_C4;                 // C4
    uint8 reservedCC[0x2F];                 // CC
    sint8 value_FB;                         // FB
    uint8 reservedFC[7];                    // FC
    sint8 value_103;                        // 103
    uint8 reserved104[3];                   // 104
    sint8 value_107;                        // 107
    uint8 reserved108[3];                   // 108
    sint8 value_10B;                        // 10B
    uint8 reserved10C[3];                   // 10C
    sint8 value_10F;                        // 10F
    uint8 value_110;                        // 110
    uint8 reserved111[0x47];                // 111
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180[6];             // 180: [0] the talk camera's point; the body's points
    uint8 reserved1B0[0x198];               // 1B0
    ST05_VILLAGER_CTL ctl;                  // 348
    uint8 reserved388[0x38];                // 388
};

// ends when its emitter's routine does.
typedef struct ST05_SPARK ST05_SPARK;

struct ST05_SPARK
{
    uint8 be_flag;          // 00
    uint8 work_id;          // 01
    uint8 id;               // 02
    uint8 type;             // 03
    uint8 reserved04[2];    // 04
    uint8 flags;            // 06
    uint8 reserved07;       // 07
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B: emitter: frames to the next spark
    sint8 work_0;           // 0C
    sint8 timer_D;          // 0D (Capcom: work_1)
    sint8 width_E;          // 0E: emitter: the sparks' width (Capcom: work_2)
    sint8 type_F;           // 0F: growth per frame (Capcom: work_3)
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
    ST05_SPARK *owner_2C;   // 2C
    uint8 reserved30[0x18]; // 30
};

void func_801085CC(ST05_VILLAGER *wp);

void func_801088F4(ST05_VILLAGER *wp);

void func_80108A54(ST05_VILLAGER *wp);

sint32 func_80031E60(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);
void func_80108BA4(ST05_VILLAGER *wp);

void func_80108DFC(ST05_VILLAGER *wp);

void func_80109198(ST05_VILLAGER *wp);

void func_801095E0(ST05_VILLAGER *wp);

void func_80109D44(ST05_VILLAGER *wp);

void func_80109F84(ST05_VILLAGER *wp);

void func_80109E84(ST05_VILLAGER *wp);

sint32 func_8010A508(ST05_VILLAGER *wp);

sint32 func_8010A608(ST05_VILLAGER *wp);

void func_80109AE4(ST05_VILLAGER *wp);

void func_80108324(ST05_VILLAGER *wp);

void func_80107FF0(ST05_VILLAGER *wp);

extern STAGE_SLOT_FUNC D_80130A50[];

void func_8010A21C(ST05_VILLAGER *wp);

// A face routine of D_80131B9C: the object and its face block at +0x4E0.
typedef void (*ST05_FACE16_FUNC)(STAGE_OBJ *wp, STAGE_FACE16 *face);

extern ST05_FACE16_FUNC D_80131B9C[];
void func_80120120(STAGE_OBJ *wp, STAGE_FACE16 *face);

// The control block at +0x328 of ST05_BOAT.
typedef struct
{
    uint16 flags_0;       // 00
    uint16 random_2;      // 02: rand() each frame
    sint16 timer_4;       // 04
    sint16 timer_6;       // 06
    uint16 count_8;       // 08
    sint16 count_A;       // 0A: frames in func_8011A194's step
    sint16 roll_C;        // 0C: index into D_8013192C; -1 none
    uint8 reserved0E[2];  // 0E
    uint16 value_10;      // 10: the kind's life_A[0]
    sint16 sink_12;       // 12
    sint16 rise_14;       // 14
    sint16 rise_16;       // 16: how fast it sinks (func_8011A194)
    sint32 hit_18;        // 18: Obj_map_push_out's result
    sint32 ground_1C;     // 1C: 1 on the ground
    sint32 hit_20;        // 20: func_800341BC's record
    sint32 value_24;      // 24
    uint8 track_28[0x10]; // 28: Track_reset/func_8003648C
} ST05_BOAT_CTL;

// A 0x3C0-byte work slot of the boats (D_801318F4's routines).
typedef struct
{
    sint8 be_flag;                          // 00
    uint8 work_id;                          // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 index_C;                          // 0C: into D_80131910 (Capcom: work_0)
    uint8 work_1;                           // 0D
    uint8 work_2;                           // 0E
    uint8 work_3;                           // 0F
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    union
    {
        sint16 h[2];
        sint32 w;
    } turn_64;                // 64
    uint8 reserved68[6];      // 68
    sint16 life_6E;           // 6E
    uint8 reserved70[8];      // 70
    sint16 *data_78;          // 78
    uint8 reserved7C[4];      // 7C
    uint32 dist_80;           // 80: squared distance to the player
    uint8 reserved84[0x23];   // 84
    sint8 value_A7;           // A7: -1 at the end of the animation
    uint8 reservedA8[4];      // A8
    uint8 anim_AC;            // AC
    uint8 anim_prev_AD;       // AD
    uint8 reservedAE[2];      // AE
    sint16 life_max_B0;       // B0
    sint16 life_prev_B2;      // B2
    uint8 reservedB4[0xA4];   // B4
    STCOM_SVECTOR_W scale;    // 158
    uint8 reserved160[0x20];  // 160
    STCOM_SVECTOR value_180;  // 180
    uint8 reserved188[0x1A0]; // 188
    ST05_BOAT_CTL ctl;        // 328
    uint8 reserved360[0x60];  // 360
} ST05_BOAT;

typedef void (*ST05_BOAT_FUNC)(ST05_BOAT *wp, ST05_BOAT_CTL *ctl);

void func_80118FF8(ST05_BOAT *wp, ST05_BOAT_CTL *ctl);
void func_80119188(ST05_BOAT *wp, ST05_BOAT_CTL *ctl);
void func_801193C8(ST05_BOAT *wp, ST05_BOAT_CTL *ctl);
void func_8011948C(ST05_BOAT *wp, ST05_BOAT_CTL *ctl);
sint32 func_8011953C(sint16 x, sint16 z, sint16 side);
void func_80119E3C(ST05_BOAT *wp, ST05_BOAT_CTL *ctl);
void func_8011A094(ST05_BOAT *wp, ST05_BOAT_CTL *ctl);
sint32 func_80119D90(ST05_BOAT *wp);

extern ST05_BOAT_FUNC D_80131900[];
void func_80119718(ST05_BOAT *wp, ST05_BOAT_CTL *ctl);
void func_80119A90(ST05_BOAT *wp, ST05_BOAT_CTL *ctl);
void func_80119BE0(ST05_BOAT *wp, ST05_BOAT_CTL *ctl);

// A 0x10C-byte slot (Open_SHL_WORK) of kind 1: the spray a boat throws up (type 0x24) and the boss's
// shots (types 0 and 1, func_8011C9B0).
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 work_id;                     // 01
    uint8 id;                          // 02
    uint8 reserved03;                  // 03
    uint8 value_4;                     // 04
    uint8 reserved05[0xA];             // 05
    sint8 type_F;                      // 0F
    uint8 reserved10[4];               // 10
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x18];            // 2C
    STCOM_SVECTOR velocity;            // 44
    STCOM_SVECTOR accel;               // 4C
    uint8 reserved54[0xB8];            // 54
} ST05_SPRAY;

void func_8011986C(ST05_BOAT *wp, ST05_BOAT_CTL *ctl);

// The scratchpad angles Model_parts_mtx_set_y tilts a model by: x and z.
#define ST05_SP_TILT ((STCOM_SVECTOR *)0x1F800128)

// The same scratchpad angles as an array by joint (func_80111898): its model's draw reads them.
#define ST05_SP_JOINT ((STCOM_SVECTOR *)0x1F800120)

extern ST05_BOAT_FUNC D_801318F4[];

// The talking face at +0x4E0 of the D_80131B9C objects, with their own counters after it.
typedef struct
{
    STAGE_FACE16 face; // 00
    uint8 value_14;    // 14
    uint8 count_15;    // 15
    uint8 timer_16;    // 16
} ST05_FACE;

void func_80120268(ST05_OBJ *wp);
void func_80120348(ST05_OBJ *wp);
void func_80120434(ST05_OBJ *wp);

#define ST05_PL (*(ST05_PL_VIEW *)&Player_work)

// An absolute value written out (the argument is evaluated twice).
#define ST05_ABS(x) ((x) < 0 ? -(x) : (x))

// Called without its argument (retail passes whatever a0 holds).
void func_8011CF8C();

// STAGE_PART with its second byte named: -1 once the boss's joint is blown off (func_8011C720).
typedef struct
{
    uint8 value_0;
    sint8 value_1;
    uint8 reserved2;
    uint8 value_3;
} ST05_PART;

// The control block at +0x440 of ST05_BOSS.
typedef struct
{
    uint16 flags_0;            // 440
    uint16 random_2;           // 442
    sint16 timer_4;            // 444
    uint8 reserved6[2];        // 446
    uint16 value_8;            // 448: or'ed into the hit attributes
    sint16 timer_A;            // 44A
    uint8 reservedC[4];        // 44C
    ST05_HIT hit_10[9];        // 450: cleared each frame
    uint8 track_A0[0x10];      // 4E0: Track_reset
    STCOM_SVECTOR hit_pos_B0;  // 4F0: func_800341BC's point
    STCOM_SVECTOR home_B8;     // 4F8: pad is the heading
    STCOM_SVECTOR target_C0;   // 500: pad is the angle from it to the player
    STCOM_SVECTOR size_C8;     // 508: func_80030418's box
    STCOM_FIXED_VECTOR out_D0; // 510: func_80030418's push
    uint32 dist_E0;            // 520: squared distance to the player
    uint8 reservedE4[2];       // 524
    sint16 value_E6;           // 526
    uint8 value_E8;            // 528
    uint8 value_E9;            // 529
    uint8 value_EA;            // 52A
    uint8 value_EB;            // 52B
    uint8 value_EC;            // 52C
    uint8 value_ED;            // 52D
    uint8 value_EE;            // 52E
    sint8 value_EF;            // 52F
} ST05_BOSS_CTL;

// The large actor of D_80131988/D_80131998: ST05_OBJ's layout with its control block at +0x440.
typedef struct
{
    sint8 be_flag;   // 00
    uint8 work_id;   // 01
    uint8 id;        // 02
    uint8 type;      // 03
    sint16 value_4;  // 04
    sint16 value_6;  // 06
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 routine_2; // 0A
    uint8 routine_3; // 0B
    union
    {
        struct
        {
            sint8 work_0; // 0C
            sint8 work_1; // 0D
        } b;
        sint16 timer; // 0C
    } u_C;
    union
    {
        struct
        {
            sint8 work_2; // 0E
            sint8 work_3; // 0F
        } b;
        sint16 angle; // 0E
    } u_E;
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STAGE_FIXED value_44;                   // 44
    STAGE_FIXED value_48;                   // 48
    STAGE_FIXED value_4C;                   // 4C
    uint16 value_50;                        // 50
    sint16 value_52;                        // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 value_64;                        // 64
    uint8 reserved68[0x6];                  // 68
    sint16 value_6E;                        // 6E
    sint32 value_70;                        // 70
    sint8 jump_74;                          // 74: nonzero while it jumps (func_8011B8F8)
    uint8 reserved75[3];                    // 75
    sint32 value_78;                        // 78
    sint16 value_7C;                        // 7C
    uint8 reserved7E[0x2];                  // 7E
    sint32 value_80;                        // 80
    uint8 reserved84[0x4];                  // 84
    void *model_88;                         // 88
    uint8 reserved8C[0xC];                  // 8C
    uint8 *anim_98;                         // 98
    uint8 reserved9C[8];                    // 9C
    uint8 value_A4;                         // A4: the animation frame
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[0x4];                  // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    sint16 value_AE;                        // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    sint32 value_B4;                        // B4
    union
    {
        sint8 *flag;               // a flag byte to wait on (func_80126440)
        STAGE_OBJ *part;           // a linked part (func_801260D0)
    } u_B8;                        // B8
    sint32 value_BC;               // BC
    sint32 value_C0;               // C0
    STCOM_SVECTOR value_C4;        // C4
    sint32 value_CC;               // CC
    uint8 reservedD0[0x28];        // D0
    ST05_PART part_F8[14];         // F8: by joint
    uint8 reserved130[0x18];       // 130
    sint8 value_148[4];            // 148
    uint8 reserved14C[0xC];        // 14C
    STCOM_SVECTOR_W scale;         // 158
    uint8 reserved160[0x8];        // 160
    uint8 value_168;               // 168
    uint8 value_169;               // 169
    uint8 reserved16A[0x16];       // 16A
    STCOM_SVECTOR joint_180[0x18]; // 180: pad is the joint's color
    uint8 reserved240[6];          // 240
    uint8 reserved246[0x2];        // 246
    STAGE_MATRIX matrix_248;       // 248
    uint8 reserved268[0x20];       // 268
    STAGE_MATRIX matrix_288;       // 288
    uint8 reserved2A8[0x60];       // 2A8
    uint16 value_308;              // 308
    uint16 value_30A;              // 30A
    sint16 value_30C;              // 30C
    uint8 reserved30E[0x2];        // 30E
    sint16 value_310;              // 310
    uint8 reserved312[0xA];        // 312
    sint32 value_31C;              // 31C
    uint8 reserved320[0x8];        // 320
    uint16 value_328;              // 328
    sint16 value_32A;              // 32A
    uint16 value_32C;              // 32C
    sint16 value_32E;              // 32E
    sint16 value_330;              // 330
    uint8 reserved332[0xA];        // 332
    sint32 value_33C;              // 33C
    sint32 value_340;              // 340
    sint32 value_344;              // 344
    ST05_FALL fall_348;            // 348
    uint16 value_358;              // 358
    uint8 reserved35A[0x2];        // 35A
    sint32 value_35C;              // 35C
    sint32 value_360;              // 360
    sint32 value_364;              // 364
    uint16 value_368;              // 368
    uint16 value_36A;              // 36A
    sint32 value_36C;              // 36C
    uint8 reserved370[0x2];        // 370
    uint16 value_372;              // 372
    uint8 reserved374[0x4];        // 374
    sint32 value_378;              // 378
    sint32 value_37C;              // 37C
    STAGE_OBJ *value_380;          // 380
    uint8 reserved384[0xBC];       // 384
    ST05_BOSS_CTL ctl;             // 440
} ST05_BOSS;

typedef void (*ST05_BOSS_FUNC)(ST05_BOSS *wp);

void func_8011ADB4(ST05_BOSS *wp);
void func_8011AFA0(ST05_BOSS *wp);
void func_8011B0B4(ST05_BOSS *wp);
void func_8011B3CC(ST05_BOSS *wp);
void func_8011B3FC(ST05_BOSS *wp);
void func_8011B534(ST05_BOSS *wp);
void func_8011B8F8(ST05_BOSS *wp);
void func_8011BCF4(ST05_BOSS *wp);
void func_8011BF0C(ST05_BOSS *wp);
void func_8011C09C(ST05_BOSS *wp);
void func_8011C198(ST05_BOSS *wp);
void func_8011C5D8(ST05_BOSS *wp);
void func_8011C720(ST05_BOSS *wp);
void func_8011C9B0(ST05_BOSS *wp);
void func_8011CC64(ST05_BOSS *wp);
void func_8011CE1C(ST05_BOSS *wp);
void func_8011D1E0(ST05_BOSS *wp);
void func_8011D6F8(ST05_BOSS *wp);
sint32 func_8011D580(ST05_BOSS *wp);
sint32 func_8011D830(ST05_BOSS *wp);
sint32 func_8011DA0C(ST05_BOSS *wp);

extern ST05_BOSS_FUNC D_80131988[];
extern ST05_BOSS_FUNC D_80131998[];
void func_8011D044(ST05_SPRAY *wp, uint8 big);
sint32 func_8011D0E8(ST05_BOSS *wp, sint16 width, sint32 turn);

void func_80116A2C(ST05_VILLAGER *wp);

typedef void (*ST05_VILLAGER_FUNC)(ST05_VILLAGER *wp);

extern ST05_VILLAGER_FUNC D_80131808[];
void func_80116B70(ST05_VILLAGER *wp);

void func_80117130(ST05_ACTOR *wp);
sint32 func_80117300(void);

// Game_work's 0x30-byte records from +0x90 (the shop counters' states, by work slot work_3).
typedef struct
{
    uint32 kind_0;          // 00
    uint8 reserved04[0x2C]; // 04
} ST05_GAME_REC;

extern ST05_GAME_REC Game_work_90[] __asm__("Game_work+0x90");

void func_8005C224(sint32 price);

STAGE_OBJ *func_80031498(void);

void func_801037CC(STAGE_PL_VIEW *pl);

// The display buffer index (0 or 1) in the scratchpad (ROCK_NEO's SCRATCH_BUFFER_INDEX).
#define ST05_BUFFER_INDEX (*(uint8 *)0x1F800000)

// PsyQ's TILE (a flat rectangle).
typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    short w, h;
} ST05_TILE;

void SetTile(ST05_TILE *p);

// A full-screen tile and its draw mode per display buffer (func_80101A70 sets them up, func_80102944
// draws them; the tiles' fields are also reached as their own symbols, D_80137DC4..D_80137DDE).
extern ST05_TILE D_80137DC0[2];
extern DR_MODE D_80137DE0[2];

// Game_work's 0x10-byte records from +0x84: three best results per shop counter (work_3).
typedef struct
{
    uint32 score_0;      // 00
    uint16 name_4[4];    // 04
    uint8 reserved0C[4]; // 0C
} ST05_RANK;

extern ST05_RANK Game_work_84[] __asm__("Game_work+0x84");

void func_8012BB3C(void);

STCOM_MATRIX *RotMatrixX(sint32 r, STCOM_MATRIX *m);

sint16 Ceiling_height_get(STCOM_SVECTOR *pos);

void func_80030934(void *a0, void *a1, sint16 a2,
                   sint32 a3); // a3 passed without narrowing (func_8011C9B0)

// A 0x50-byte slot that times a run past the shop counter's items (func_8012BF74, func_8012B788):
// the gate passed so far, the player's position last frame and the frame count.
typedef struct
{
    uint8 be_flag;          // 00
    uint8 work_id;          // 01
    uint8 id;               // 02
    uint8 type;             // 03
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint8 gate_C;           // 0C: the next gate to pass (Capcom: work_0)
    sint8 work_1;           // 0D
    sint8 work_2;           // 0E
    sint8 work_3;           // 0F: the counter
    uint8 reserved10[4];    // 10
    STCOM_SVECTOR pos_14;   // 14: the player's position last frame
    uint8 reserved1C[0x2C]; // 1C
    sint32 time_48;         // 48
    sint32 value_4C;        // 4C
} ST05_RACE;

void func_8005C218(sint32 arg);

void func_8005C24C(sint32 arg);

void func_8001E3F0(sint32 arg);

sint32 func_8003648C(void *track, void *wp);

extern ST05_GUARD_FUNC D_80130B48[];

sint32 func_80031F84(STCOM_SVECTOR *pos, STCOM_SVECTOR *from, sint32 rot, sint32 arg3);

sint32 func_8010D1A8(ST05_GUARD *wp);

sint32 func_80031CA4(STCOM_SVECTOR *a, STCOM_SVECTOR *b, sint32 c, sint32 d);

void func_8012B948(STAGE_OBJ50 *wp);

// Player_work as the stage's player routines take it (r3_st03's ST03_PL): +0x428/+0x438 a second
// position in 16.16 and in halfwords, +0x440 a rotation.
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 work_id;                     // 01
    uint8 reserved02[6];               // 02
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 reserved0A[2];               // 0A
    sint8 step_C;                      // 0C: a lesson's step (func_8012656C)
    sint8 count_D;                     // 0D
    uint8 reserved0E[6];               // 0E
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x28];            // 2C
    STCOM_SVECTOR rotation;            // 54
    uint8 reserved5C[0x61];            // 5C
    uint8 flags_BD;                    // BD
    uint8 reservedBE[0x36A];           // BE
    STCOM_FIXED_VECTOR fixed_428;      // 428
    STCOM_SVECTOR pos_438;             // 438
    STCOM_SVECTOR rot_440;             // 440
    uint8 anim_448;                    // 448
} ST05_PL_SAVE;

void func_80112284(STAGE_OBJ *wp);

sint32 func_80031DCC(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);

STCOM_MATRIX *MulMatrix0(STCOM_MATRIX *m0, STCOM_MATRIX *m1, STCOM_MATRIX *out);
STCOM_MATRIX *TransposeMatrix(STCOM_MATRIX *m0, STCOM_MATRIX *m1);

void func_8011E750(ST05_OBJ *wp);

// Returns a value here (as an implicit int): the allocation of func_8011B8F8 needs it.
sint32 Swing_Camera2(sint32 a0, sint32 a1, sint32 a2, STCOM_SVECTOR *pos);

void func_8003697C(void);

void Sce_event_timer_clear(void);
void func_8005D7C0(void);

void func_80107CEC(void);

sint32 func_80030604(void *a, void *b, STCOM_SVECTOR *size, STCOM_FIXED_VECTOR *out);

void func_80053AA4(sint32 arg);

void func_80039C54(STCOM_FIXED_VECTOR *vec, sint32 dist, sint32 angle,
                   sint32 arg3); // ROCK_NEO.EXE: places the camera

void *func_8001EB98(STAGE_SCRIPT_ENTRY *entry); // ROCK_NEO.EXE: runs a room script command

void func_80101330(STAGE_ROOM *wp);
void func_801013E0(STAGE_ROOM_WORK *wp);
void func_801019DC(STAGE_ROOM *wp);
void func_80101A70(STAGE_ROOM *wp);
void func_80101BE4(STAGE_ROOM_WORK *wp);
void func_80101C24(STAGE_ROOM *wp);
void func_80102944(void);
void func_8010602C(uint8 index, uint8 kind);
void func_80106098(void);

// A 0x50-byte slot (STAGE_OBJ50) as func_8012AB24 runs it: a prize the player opens, with the
// effect it spawned at +0x44.
typedef struct
{
    uint8 be_flag;          // 00
    uint8 work_id;          // 01
    uint8 id;               // 02
    uint8 type;             // 03: 1 and 2 set flags 0x671 and 0x672
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint8 timer_C;          // 0C (Capcom: work_0)
    sint8 work_1;           // 0D
    sint8 work_2;           // 0E: the camera spot, by variant
    sint8 work_3;           // 0F
    void *model_10;         // 10
    uint8 reserved14[0x24]; // 14
    STCOM_SVECTOR pos_38;   // 38
    uint32 color_40;        // 40
    STCOM_EFFECT *fx_44;    // 44
    sint32 value_48;        // 48
    sint32 value_4C;        // 4C
} ST05_PRIZE;

sint32 func_8012AFA0(void);

extern ST05_PROP_FUNC D_801323C0[]; // routine_1 handlers (func_80125880)

#endif
