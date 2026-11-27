#ifndef ST04_H
#define ST04_H

#include "common.h"
#include "stage_common/stage.h"

// ST04_ACTOR_CTL +0x14: a hit record in the first block, the walk goal in the second.
typedef union
{
    uint32 hit;         // damage in the low 24 bits, kind bits above
    STCOM_SVECTOR goal; // the waypoint being walked to (func_8010754C)
} ST04_ACTOR_CTL_14;

// A 0x20-byte control block of ST04_ACTOR (at +0x348 and +0x368).
typedef struct
{
    uint16 flags_0;          // 00
    uint16 value_2;          // 02
    sint16 timer_4;          // 04
    sint16 value_6;          // 06
    uint16 value_8;          // 08: hit kind bits
    sint16 timer_A;          // 0A
    STCOM_SVECTOR target_C;  // 0C: where the actor turns or walks to
    ST04_ACTOR_CTL_14 at_14; // 14
    uint16 value_1C;         // 1C: the waypoint index in the second block
    uint16 value_1E;         // 1E
} ST04_ACTOR_CTL;

// A 0x3C0-byte work slot as this stage's villagers use it: STAGE_ACTOR with the blocks at +0x348
// and +0x368 named.
typedef struct
{
    sint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 timer_C;                          // 0C
    sint8 value_D;                          // 0D
    sint8 value_E;                          // 0E
    uint8 reserved0F;                       // 0F
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
    ST04_ACTOR_CTL ctl;                     // 348
    ST04_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST04_ACTOR;

typedef void (*ST04_ACTOR_FUNC)(ST04_ACTOR *wp);

// A 0x10C-byte work slot: a rock that is knocked into the air and bounces (r3_st04_83E4.c).
typedef struct
{
    uint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 reserved02[6];                    // 02
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A: 1 while flying
    uint8 routine_3;                        // 0B
    uint8 reserved0C[3];                    // 0C
    sint8 value_F;                          // 0F: heading / 16
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    uint8 reserved5C[8];                    // 5C
    sint16 spin_64;                         // 64: rotation.x step
    sint16 spin_66;                         // 66: rotation.y step
    uint8 reserved68[0xC];                  // 68
    uint8 value_74;                         // 74
    uint8 reserved75[3];                    // 75
    void *data_78;                          // 78
    uint8 reserved7C[0x10];                 // 7C
    STAGE_MATRIX_W matrix;                  // 8C
    STCOM_SVECTOR pos_AC;                   // AC
    uint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    uint32 hit_BC[4];                       // BC: hit record (func_800341BC)
    uint8 reservedCC[0x40];                 // CC
} ST04_ROCK;

typedef void (*ST04_ROCK_FUNC)(ST04_ROCK *wp);

// The scene slot that ST04_EV watches (Scene_obj_ent_open's): the header and position.
typedef struct
{
    uint8 be_flag;          // 00
    uint8 slot;             // 01
    uint8 reserved02[4];    // 02
    uint8 flags;            // 06
    uint8 reserved07;       // 07
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    uint8 reserved0C[8];    // 0C
    STCOM_SVECTOR position; // 14
} ST04_SLOT;

// A 0x24-byte event slot that drives a scene slot (Scene_obj_ent_open's) kept at +0x1C.
typedef struct
{
    uint8 be_flag;          // 00
    uint8 slot;             // 01
    uint8 reserved02[6];    // 02
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 reserved0A[0x12]; // 0A
    ST04_SLOT *slot_1C;     // 1C
    uint8 reserved20[4];    // 20
} ST04_EV;

extern STAGE_FUNC D_8010C974[];
extern STAGE_FUNC D_8010C9AC[];
extern STAGE_FUNC D_80111C84[];
extern STAGE_OBJ_FUNC D_80111C9C[];
extern STAGE_FUNC D_80111D14[];
extern STAGE_FUNC D_80111D20[];
extern STAGE_SLOT_FUNC *D_8010A570[];
extern STAGE_SLOT_FUNC *D_8010A6F0[];
extern STAGE_SLOT_FUNC D_8010A6F4[];
extern STAGE_SLOT_FUNC D_8010A7A8[];
extern STAGE_SLOT_FUNC D_8010A7AC[];
extern STAGE_SLOT_FUNC D_8010A808[];
extern STAGE_ROOM2_FUNC D_8010AFC0[];
void func_80104B6C(STAGE_WORK *wp);
void func_80104E08(STAGE_FX *wp);
void func_80105474(STAGE_WORK *wp);
void func_80105794(STAGE_FX *wp);
void func_80106BCC(STAGE_FX *wp);
void func_80108FE0(STAGE_WORK *wp);
void func_80109218(STAGE_OBJ *wp);
void func_80109FA0(STAGE_WORK *wp);
void func_8010A248(STAGE_WORK *wp);
void func_80100200(void);
void func_80101B44(STAGE_ROOM *wp);

void func_80109FDC(STAGE_OBJ *wp);

sint32 func_80101B24(void);

void func_80100AE0(STAGE_ROOM *wp);

sint32 func_80101AC4(void);

extern uint8 D_8010AC64[][0x28]; // by room (func_800371A0)
extern uint8 D_8010AF44[];
extern uint8 D_8010C98C[];
extern uint8 D_8010C9C0[];
extern uint8 D_8010C9D0[];
extern uint8 D_8010CA70[];
extern uint8 D_8010CA9C[][3]; // by ctl2.value_1C: three weights (func_801076F0)
extern uint8 D_80111CA8[];
extern uint8 D_80111CD4[];
extern uint8 D_80111D2C[]; // scene command (Scene_obj_ent_open)

extern uint8 D_800987B5; // D_800987B0[5]
extern sint8 D_80111CE0[];
void func_80031A4C(void *wp);
void func_80109C8C(STAGE_OBJ50 *wp);

sint32 func_80107850(ST04_ACTOR *wp);

void func_80109FE8(STAGE_OBJ50 *wp);

sint32 func_801077E8(ST04_ACTOR *wp);

void func_80106BEC(ST04_ACTOR *wp);

void func_8010919C(STAGE_OBJ50 *wp);

void func_80109EB8(STAGE_OBJ50 *wp);

void func_80107C24(ST04_ACTOR *wp);

void func_80106568(ST04_ACTOR *wp);

void func_801051EC(ST04_ACTOR *wp);

void func_80106048(ST04_ACTOR *wp);

uint8 func_8010A484(ST04_SLOT *slot);
void func_8001E4C4(void *a, void *b);
extern uint8 D_8010AF4C[][8];
extern STAGE_ROOM_FUNC D_8010AF2C[];
extern STAGE_ROOM_FUNC *D_8010AEEC[];
void Sce_event_timer_clear(void);
extern uint8 D_8010BFD4[];
extern STAGE_ROOM2_FUNC D_8010BFCC[];
extern uint16 D_80111CB4[];
STCOM_MATRIX *RotMatrixZ(sint32 r, STCOM_MATRIX *m);
void func_8010A2D4(ST04_EV *wp);

STCOM_MATRIX *RotMatrixZ(sint32 r, STCOM_MATRIX *m);
void func_8010044C(void);

STCOM_MATRIX *RotMatrixZ(sint32 r, STCOM_MATRIX *m);
void func_801004F4(void);

STCOM_MATRIX *RotMatrixZ(sint32 r, STCOM_MATRIX *m);
void func_80101B80(STAGE_ROOM *wp);

void func_8010098C(STAGE_ROOM *wp);

void func_80100948(STAGE_ROOM *wp);

void func_801009D0(STAGE_ROOM *wp);

void func_80100A14(STAGE_ROOM *wp);

void func_80100A58(STAGE_ROOM *wp);

void func_80100A9C(STAGE_ROOM *wp);

void func_80100AFC(STAGE_ROOM *wp);

void func_80100B40(STAGE_ROOM *wp);

void func_80100B84(STAGE_ROOM *wp);

void func_80100BC8(STAGE_ROOM *wp);

void func_80100C0C(STAGE_ROOM *wp);

void func_80100C50(STAGE_ROOM *wp);

void func_80100C94(STAGE_ROOM *wp);

void func_80100CD8(STAGE_ROOM *wp);

void func_80100D68(STAGE_ROOM *wp);

void func_80100DAC(STAGE_ROOM *wp);

void func_80100DF0(STAGE_ROOM *wp);

void func_80100E34(STAGE_ROOM *wp);

void func_80100E78(STAGE_ROOM *wp);

void func_80100EBC(STAGE_ROOM *wp);

void func_80100F4C(STAGE_ROOM *wp);

void func_80100F90(STAGE_ROOM *wp);

void func_80100FD4(STAGE_ROOM *wp);

void func_80101018(STAGE_ROOM *wp);

void func_8010105C(STAGE_ROOM *wp);

void func_801010EC(STAGE_ROOM *wp);

void func_80101130(STAGE_ROOM *wp);

void func_80101174(STAGE_ROOM *wp);

void func_801011B8(STAGE_ROOM *wp);

void func_801011FC(STAGE_ROOM *wp);

void func_80101240(STAGE_ROOM *wp);

void func_80101284(STAGE_ROOM *wp);

void func_801012C8(STAGE_ROOM *wp);

void func_8010130C(STAGE_ROOM *wp);

void func_80101350(STAGE_ROOM *wp);

void func_80101394(STAGE_ROOM *wp);

void func_801013D8(STAGE_ROOM *wp);

void func_8010141C(STAGE_ROOM *wp);

void func_80101460(STAGE_ROOM *wp);

void func_801014A4(STAGE_ROOM *wp);

void func_801014E8(STAGE_ROOM *wp);

void func_80101588(STAGE_ROOM *wp);

void func_801015CC(STAGE_ROOM *wp);

void func_80101610(STAGE_ROOM *wp);

void func_80101654(STAGE_ROOM *wp);

void func_80101698(STAGE_ROOM *wp);

void func_80101738(STAGE_ROOM *wp);

void func_8010177C(STAGE_ROOM *wp);

void func_801017C0(STAGE_ROOM *wp);

void func_80101804(STAGE_ROOM *wp);

void func_80101848(STAGE_ROOM *wp);

void func_801018E8(STAGE_ROOM *wp);

void func_80101970(STAGE_ROOM *wp);

void func_8010192C(STAGE_ROOM *wp);

void func_801019B4(STAGE_ROOM *wp);

void func_801019F8(STAGE_ROOM *wp);

void func_80101A3C(STAGE_ROOM *wp);

void func_80101A80(STAGE_ROOM *wp);

void func_80100D1C(STAGE_ROOM *wp);

void func_80100F00(STAGE_ROOM *wp);

void func_801010A0(STAGE_ROOM *wp);

void func_8010152C(STAGE_ROOM *wp);

void func_801016DC(STAGE_ROOM *wp);

void func_8010188C(STAGE_ROOM *wp);

extern ST04_ACTOR_FUNC D_8010CA4C[];

extern ST04_ROCK_FUNC D_8010CBB0[];
extern uint8 D_8010CBA4[];
void func_8010849C(ST04_ROCK *wp);
void func_801085EC(ST04_ROCK *wp);
sint32 func_80108794(ST04_ROCK *wp);
void func_801088BC(ST04_ROCK *wp);

extern STAGE_OBJ50_FUNC D_80111C90[]; // by type
extern STAGE_OBJ50_FUNC D_80111CC4[]; // by routine_0

uint8 func_801099D8(STAGE_OBJ50 *wp);
void func_8010967C(STAGE_OBJ50 *wp);

// The box func_8010A484 tests a slot's position against.
extern STCOM_SVECTOR D_80111D40; // highest x, y, z
extern STCOM_SVECTOR D_80111D48; // lowest x, y, z

// routine handlers by type (func_80104F7C, func_80105B18, func_801060E8, func_801078A0)
extern ST04_ACTOR_FUNC D_8010C984[];
extern ST04_ACTOR_FUNC D_8010C9CC[];
extern ST04_ACTOR_FUNC D_8010CA2C[];
extern ST04_ACTOR_FUNC D_8010CAA8[];

// The turn step toward a point (ROCK_NEO); this stage uses the int result unnarrowed.
sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);

// The talk camera's point (func_8010528C).
extern STCOM_FIXED_VECTOR D_80111D50;

sint32 func_801076F0(ST04_ACTOR *wp);

sint32 func_8010528C(ST04_ACTOR *wp);
sint32 func_801053BC(void);

void func_80109A60(STAGE_OBJ50 *wp);
uint8 func_80109F34(STAGE_OBJ50 *wp);
STCOM_MATRIX *RotMatrixX(sint32 r, STCOM_MATRIX *m);

// STAGE_OBJ50's +0x48 word as a 16.16 height (a chest lid's), read by its integer half.
#define ST04_OBJ50_Y(wp) (((STAGE_FIXED *)&(wp)->value_48)->words.integer)

// Player_work as the villagers see it: where a scene puts the player (+0x428..+0x448).
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 slot;                        // 01
    uint8 reserved02[18];              // 02
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x28];            // 2C
    STCOM_SVECTOR rotation;            // 54
    uint8 reserved5C[0x128];           // 5C
    void *target_184;                  // 184: the work slot the player is talking to
    uint8 reserved188[0x2A0];          // 188
    STCOM_FIXED_VECTOR fixed_428;      // 428
    STCOM_SVECTOR pos_438;             // 438
    STCOM_SVECTOR rot_440;             // 440
    uint8 value_448;                   // 448
    uint8 reserved449[5];              // 449
    uint8 value_44E;                   // 44E
} ST04_PL_WORK;

extern STAGE_CAM Sce_camera_work;
void func_80053AA4(sint32 arg);

#define ST04_PL ((ST04_PL_WORK *)&Player_work)

extern void *D_8010A8C8[]; // room models by room
extern uint8 D_8010AABB;
extern uint8 D_8010AAA2;
extern void *D_8010AA84[]; // spawn list by room
extern void *D_8010AC4C[]; // exit list by room
extern sint32 D_8010AD9C[];
extern uint8 D_8010AD54[][8]; // by D_8010AD9C[room]

void func_8010207C(sint8 index);

extern ST04_ACTOR_FUNC D_8010C980[];
void func_80104CB8(ST04_ACTOR *wp);

// A 0x3C0-byte enemy slot of this stage set up by func_801067A8 (its own block at +0x348).
typedef struct
{
    sint8 be_flag;    // 00
    uint8 slot;       // 01
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
            sint8 byte_C; // 0C
            sint8 byte_D; // 0D
        } b;
        sint16 timer; // 0C
    } u_C;
    union
    {
        struct
        {
            sint8 byte_E; // 0E
            sint8 byte_F; // 0F
        } b;
        sint16 angle; // 0E
    } u_E;
    void *data_10;                          // 10
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
    sint32 value_64;                        // 64
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[0x8];                  // 70
    void *data_78;                          // 78
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
    uint8 reserved30C[0x3C];                // 30C
    sint16 flags_348;                       // 348
    uint8 reserved34A[2];                   // 34A
    sint32 value_34C;                       // 34C
    sint32 value_350;                       // 350
    uint8 reserved354[8];                   // 354
    sint32 value_35C;                       // 35C
    uint8 reserved360[0xC];                 // 360
    uint8 track_36C[0x18];                  // 36C: Track_reset
    sint16 value_384;                       // 384
    sint16 value_386;                       // 386
    uint8 reserved388[0x38];                // 388
} ST04_GUARD;

// A ROCK_NEO record per object kind (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8; // 08
} ST04_KIND;

extern ST04_KIND **D_80098844;
extern uint8 D_8010CA64[];
void Track_reset(void *track, uint8 arg1, uint32 arg2);

extern ST04_ACTOR_FUNC D_8010C9B8[];
sint32 func_80105A8C(ST04_ACTOR *wp);
void func_801055F0(ST04_ACTOR *wp);

void func_8001E3F0(sint32 arg);

void func_801058CC(ST04_ACTOR *wp);

// Waypoint areas by ctl2.value_1C: a corner and the size (func_8010754C, func_80106C5C).
typedef struct
{
    sint16 x;
    sint16 z;
    sint16 w;
    sint16 d;
} ST04_AREA;

extern ST04_AREA D_8010CA7C[];

void func_8010754C(ST04_ACTOR *wp);

// A scratchpad halfword this stage's villagers set before Model_parts_mtx_set_y.
#define ST04_SP_132 (*(uint16 *)0x1F800132)

extern ST04_ACTOR_FUNC D_8010CA34[];

// The talk camera (func_80107264): ROCK_NEO's camera settings it saves, overrides and restores.
extern uint8 D_800A395A[];
extern sint32 D_800A3964;
extern sint32 D_800A3988[]; // [0]: the talk camera distance
extern sint32 D_800A398C;
extern sint32 D_800A3990;
extern STCOM_FIXED_VECTOR D_800A39D0; // the talk camera's point
extern uint8 D_80111D60;              // the saved D_800A395A[0]
extern uint8 D_80111D64;              // the saved D_800A395A[1]

void func_80107264(ST04_ACTOR *wp);

extern uint8 D_8010BFE8[];
extern STAGE_ROOM2_FUNC D_8010BFD8[];

// The music player (func_8010A044): volume and song by the slot's u_C.b.lo.
extern uint8 D_80111D0C[];
extern uint32 D_80111CF0[];
extern uint16 D_800C0C26;

extern STAGE_SCRIPT_ENTRY D_8010C9DC[]; // the villagers func_80100594 places
ST04_ACTOR *func_8001EB98(STAGE_SCRIPT_ENTRY *entry);

#endif // ST04_H
