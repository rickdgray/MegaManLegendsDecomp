#ifndef STAGE_COMMON_STAGE_H
#define STAGE_COMMON_STAGE_H

#include "common.h"
#include "psyq/libgpu.h"
#include "stage_common/rock_neo.h"

// Types and ROCK_NEO.EXE declarations for the stage-unique code (r3_st01, r3_st18, r3_st15,
// r3_st16, r3_st1e, r3_st07, r3_st02, r3_st17): the room setup and room scripts every stage module
// has, and the work slots its objects run on. Only the fields used so far.

// Scratchpad: the slot routine tables a stage installs when it loads (ROCK_NEO's game.h
// GAME_TABLE_*), and the current room's map.
typedef void (*STAGE_SLOT_FUNC)(void *wp);
#define STAGE_TABLE_3C0 (*(STAGE_SLOT_FUNC ***)0x1F800058)
#define STAGE_TABLE_5A4 (*(STAGE_SLOT_FUNC ***)0x1F80005C)
#define STAGE_TABLE_10C (*(STAGE_SLOT_FUNC **)0x1F800060)
#define STAGE_TABLE_48  (*(STAGE_SLOT_FUNC **)0x1F800064)
#define STAGE_TABLE_24  (*(STAGE_SLOT_FUNC **)0x1F800068)
#define STAGE_TABLE_50  (*(STAGE_SLOT_FUNC **)0x1F80006C)
#define STAGE_MAP_X0    (*(uint8 *)0x1F800040)
#define STAGE_MAP_Z0    (*(uint8 *)0x1F800041)
#define STAGE_MAP_X1    (*(uint8 *)0x1F800042)
#define STAGE_MAP_Z1    (*(uint8 *)0x1F800043)
#define STAGE_MAP_W     (*(uint16 *)0x1F800044)
#define STAGE_MAP_H     (*(uint16 *)0x1F800046)
#define STAGE_MAP_CELLS (*(sint16 **)0x1F800048)
#define STAGE_MAP_INFO  (*(void **)0x1F80004C)
#define STAGE_MAP_EXITS (*(void **)0x1F800050)
// The cell attribute table, loaded from the stage archive.
#define STAGE_CELL_INFO ((void *)0x8015C000)

// A room's map, loaded from the stage archive at 0x80164004 (one per room).
typedef struct
{
    uint8 x0;      // 0
    uint8 z0;      // 1
    uint8 w;       // 2
    uint8 h;       // 3
    sint16 *cells; // 4
} STAGE_MAP;

#define STAGE_MAP_TBL ((STAGE_MAP *)0x80164004)

// A 0x3C0-byte work slot (defined below).
typedef struct STAGE_WORK STAGE_WORK;

// The room script work at D_800989F8 (ROCK_NEO's CODE68_WORK).
typedef struct STAGE_ROOM_WORK STAGE_ROOM_WORK;
typedef void (*STAGE_ROOM_FUNC)(STAGE_ROOM_WORK *wp);

struct STAGE_ROOM_WORK
{
    uint8 flags_0;           // 00
    uint8 reserved01[3];     // 01
    uint8 routine_4;         // 04
    uint8 routine_5;         // 05
    uint8 routine_6;         // 06
    uint8 routine_7;         // 07
    uint8 routine_8;         // 08
    uint8 reserved09[3];     // 09
    sint32 timer_C;          // 0C
    sint32 frame_10;         // 10: frames since the room started
    sint32 word_14;          // 14
    uint8 reserved18[0xC];   // 18
    STAGE_WORK *child_24;    // 24: the objects the script drives
    STAGE_WORK *child_28;    // 28
    STAGE_WORK *child_2C;    // 2C
    STAGE_WORK *child_30;    // 30
    STAGE_WORK *child_34;    // 34
    STAGE_WORK *child_38;    // 38
    uint8 reserved3C[0x68];  // 3C
    STAGE_ROOM_FUNC *tbl_A4; // A4: [0] is also read as a byte (0xFF: no script)
};

// A room model record (ROCK_NEO's 0x38-byte C8001F828_MODEL, built by Room_model_init).
typedef struct
{
    sint32 x, y;
} STAGE_FIX2;

typedef struct
{
    sint16 x, y;
} STAGE_SHORT2;

typedef struct
{
    uint8 flags_0;            // 00: bit 1 hides it?
    uint8 reserved01[3];      // 01
    STAGE_FIX2 fpos_4;        // 04
    STAGE_SHORT2 pos_C;       // 0C
    STAGE_FIX2 fpos_prev_10;  // 10
    STAGE_SHORT2 pos_prev_18; // 18
    uint8 reserved1C[4];      // 1C
    sint16 value_20;          // 20
    sint16 value_22;          // 22
    uint8 reserved24[0x14];   // 24
} STAGE_MODEL;

// The room model table (ROCK_NEO's C8001F828_MODEL records) through its symbol: GCC keeps the
// address in a register for a read-modify-write, and indexes it with the symbol first. Models 1
// and 2's flags are also reached through their own symbols.
extern STAGE_MODEL D_800BBA90[];
extern uint8 D_800BBAC8;
extern uint8 D_800BBB00;

// A room script command (ROCK_NEO's CODE68_ENTRY).
typedef struct
{
    uint8 reserved00[0x14];
} STAGE_SCRIPT_ENTRY;

// D_800BBA90 at its fixed address: GCC treats the records' fields as distinct memory.
#define STAGE_MODEL_TBL ((STAGE_MODEL *)0x800BBA90)

// ROCK_NEO's sub-mode state (CODE800133D8_STATE).
typedef struct
{
    uint8 routine_0;
    uint8 routine_1;
} STAGE_SUB_STATE;

typedef void (*STAGE_THREAD_FUNC)(void);

// A 16.16 position also read by its integer halves.
typedef union
{
    STCOM_FIXED_VECTOR v;
    struct
    {
        STCOM_FIXED x, y, z, pad;
    } f;
} STAGE_FIXED_VECTOR;

// A MATRIX also written as eight words: Capcom's code sets the identity with word stores.
typedef union
{
    STCOM_MATRIX m;
    sint32 w[8];
} STAGE_MATRIX;

#define STAGE_MATRIX_IDENTITY(mw)                                                                                                          \
    ((mw)[0] = 0x1000, (mw)[1] = 0, (mw)[2] = 0x1000, (mw)[3] = 0, (mw)[4] = 0x1000, (mw)[5] = 0, (mw)[6] = 0, (mw)[7] = 0)

// The display link record; ordering-table entries from +0x74.
typedef struct
{
    uint8 reserved00[0x74];
    u_long ot_74;
    u_long ot_78;
} STAGE_LINK;

#define STAGE_PACKET_PTR ((POLY_FT4 **)0x1F800070)

extern STAGE_LINK *Disp_env_ptr;

// Game_work's byte at +0x82 (STCOM_GAME_WORK stops at +0x81). The pointer-plus form keeps
// its address in a register for a read-modify-write; ((uint8 *)&Game_work)[0x82] does not.
#define STAGE_GAME_FLAGS_82 (*((uint8 *)&Game_work + 0x82))

// Game_work's room-script set at +0x52 and Player_work's bytes past STCOM_PL_WORK's named fields.
#define STAGE_GAME_VALUE_52     (*((sint8 *)&Game_work + 0x52))
#define STAGE_GAME_BYTE(offset) (*((uint8 *)&Game_work + (offset)))
#define STAGE_PL_BYTE(offset)   (*((uint8 *)&Player_work + (offset)))
// Game_work's halfwords past STCOM_GAME_WORK's named fields.
#define STAGE_GAME_S16(offset) (*(sint16 *)((uint8 *)&Game_work + (offset)))
#define STAGE_GAME_U16(offset) (*(uint16 *)((uint8 *)&Game_work + (offset)))
// Player_work's halfwords past STCOM_PL_WORK's named fields.
#define STAGE_PL_S16(offset) (*(sint16 *)((uint8 *)&Player_work + (offset)))

// Scene_work (ROCK_NEO's SCENE_WORK): the current script line, for lip-sync tables.
typedef struct
{
    uint8 reserved00[0xC];
    uint16 value_C; // 0C: mouth shape
} STAGE_SCENE_FACE;

typedef struct
{
    uint8 reserved00[8];
    union
    {
        uint16 value_8; // 08: the scene playing
        uint8 byte[2];  // 08: [1] read on its own
    } u_8;
    uint8 value_A;          // 0A
    uint8 reserved0B[5];    // 0B
    sint32 value_10;        // 10
    uint8 reserved14[0x8];  // 14
    uint32 value_1C;        // 1C
    uint8 reserved20[0x10]; // 20
    STAGE_SCENE_FACE *face; // 30
} STAGE_SCENE_WORK;

extern STAGE_SCENE_WORK Scene_work;
extern STAGE_ROOM_WORK D_800989F8;
// An array: GCC keeps its address in a register for a read-modify-write.
extern STAGE_SUB_STATE D_80098AA8[];
extern uint8 D_80098A8C;
extern uint8 D_800A395C;
extern uint8 *D_800BC7F0;
extern void D_80013420(void); // ROCK_NEO.EXE's func_80013420

void Room_model_init(void *tbl);
void Obj_spawn_tbl_set(void *spawn, sint32 spawn_player);
void func_800371A0(void *blocks, void *arg1);
void func_8005DC10(sint32 arg);
void func_8001DDE4(sint32 id);
void func_8001E6C0(sint32 a0, sint32 a1, sint32 a2);
// Spawns a scene command's object; returns its work slot (ROCK_NEO's SCENE_SLOT, any slot size).
void *Scene_obj_ent_open(void *entry);
void Sce_event_set(void *a, void *b);
void func_80067B7C(void);
sint32 Sce_flag_test(sint32 flag);
sint32 MojiTaskExec(sint32 arg0, uint8 *script, sint32 arg2);
extern uint8 *D_8008CE90;
extern uint16 D_800C0C2A;
void Sound_seq_stop_all(void);
void Cd_xa_play_id(uint32 arg);
uint32 func_8001D878(void);
uint32 func_8001DE84(void);
void Sce_camera_update(void);
void Sce_event_update(void);
void Obj_work_flag_change(sint32 mask, sint32 flags);
void Cd_subcmd(sint32 arg0, sint32 arg1, sint32 arg2);
void func_80039820(void);
void func_80012F78(STAGE_THREAD_FUNC entry);
sint32 Model_uv_cell(sint32 id, sint32 a1, sint32 a2, sint32 a3);
void Model_mesh_uv_copy(void *model, uint32 idx, sint32 delta);
uint32 Stage_hed_model_get(uint32 key);
// Allocates a 0x24-byte event slot; NULL when none is free.
void *Open_EVE_WORK(void);

// Palette slots in a work slot: eight bytes apart, from +0x186.
typedef struct
{
    sint16 color;
    uint8 reserved02[6];
} STAGE_PAL;

// A face's lip-sync script step: shape `id` held `count` frames (negative: jump back).
typedef struct
{
    uint8 id;
    uint8 reserved01;
    sint16 count;
} STAGE_MOUTH;

// When a script line starts a lip-sync table: id 0xFF ends the list.
typedef struct
{
    union
    {
        uint16 scene;
        uint8 end; // 0xFF
    } u;
    uint16 line;
    uint16 index;
} STAGE_MOUTH_CUE;

// A 0x3C0-byte work slot: only the fields used here.
struct STAGE_WORK
{
    sint8 flags_0;       // 00
    uint8 reserved01[2]; // 01
    uint8 variant_3;     // 03
    uint8 reserved04[4]; // 04
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09
    uint8 routine_2;     // 0A
    uint8 routine_3;     // 0B
    sint8 timer_C;       // 0C
    sint8 value_D;       // 0D
    union
    {
        struct
        {
            sint8 level;     // 0E: blink level
            sint8 direction; // 0F
        } blink;
        sint16 angle; // 0E
    } u_E;
    sint32 value_10;                   // 10
    STCOM_SVECTOR position;            // 14
    STAGE_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x28];            // 2C
    sint16 rotation_54;                // 54
    sint16 rot_y_56;                   // 56
    uint8 reserved58[0x20];            // 58
    sint32 value_78;                   // 78
    uint8 reserved7C[0xC];             // 7C
    void *model_88;                    // 88
    uint8 reserved8C[0xC];             // 8C
    uint8 *anim_98;                    // 98: current animation frame
    uint8 reserved9C[0x10];            // 9C
    uint8 anim_AC;                     // AC
    uint8 reservedAD[0x63];            // AD
    uint8 value_110;                   // 110
    uint8 reserved111[0x37];           // 111
    sint8 value_148[4];                // 148
    uint8 reserved14C[0xC];            // 14C
    STCOM_SVECTOR_W scale;             // 158
    uint8 reserved160[0x26];           // 160
    STAGE_PAL pal[24];                 // 186
    uint8 reserved246[2];              // 246
    STAGE_MATRIX matrix_248;           // 248
    uint8 reserved268[0x20];           // 268
    STAGE_MATRIX matrix_288;           // 288
    uint8 reserved2A8[0x118];          // 2A8
};

typedef void (*STAGE_FUNC)(STAGE_WORK *wp);

// A 0x48-byte effect slot (func_80031618; freed through func_80031988).
typedef struct STAGE_EFFECT STAGE_EFFECT;

struct STAGE_EFFECT
{
    uint8 flags_0;       // 00
    uint8 reserved01;    // 01
    uint8 kind_2;        // 02
    uint8 variant_3;     // 03
    uint8 reserved04[2]; // 04
    uint8 flags_6;       // 06
    uint8 reserved07;    // 07
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09
    uint8 routine_2;     // 0A
    uint8 routine_3;     // 0B
    sint8 value_C;       // 0C
    sint8 timer_D;       // 0D
    sint8 frame_E;       // 0E
    sint8 type_F;        // 0F
    uint8 reserved10[4]; // 10
    uint32 mode_14;      // 14
    uint32 color_18;     // 18
    sint16 x_1C;         // 1C
    sint16 y_1E;         // 1E
    sint16 z_20;         // 20
    uint8 u_22;          // 22
    uint8 v_23;          // 23
    sint16 w_24;         // 24
    sint16 h_26;         // 26
    union
    {
        STAGE_EFFECT *parent; // the spawner
        STAGE_WORK *object;   // the object it follows
        sint16 value;
    } u_28;
    STCOM_FIXED x_2C;    // 2C
    STCOM_FIXED y_30;    // 30
    STCOM_FIXED z_34;    // 34
    uint8 reserved38[4]; // 38
    sint16 size_3C;      // 3C: 8.8
    sint16 angle_3E;     // 3E
    sint32 value_40;     // 40
    uint8 reserved44[4]; // 44
};

typedef void (*STAGE_EFFECT_FUNC)(STAGE_EFFECT *wp);

// A talking face's two animation scripts (eyes and mouth), inside a work slot at +0x4E0.
typedef struct
{
    sint16 timer_0; // 0
    sint16 value_2; // 2
    sint8 *mouth_4; // 4: shape, then a byte 0x7E (hold) or 0x7F (loop)
    sint8 *eyes_8;  // 8
    sint8 shape_C;  // C
    sint8 prev_D;   // D
    sint8 index_E;  // E
    sint8 shape_F;  // F
    sint8 prev_10;  // 10
    sint8 index_11; // 11
} STAGE_FACE;

// A work slot carrying its own rotation matrix (func_80101C08).
typedef struct
{
    uint8 flags_0;       // 00
    uint8 reserved01[7]; // 01
    uint8 routine_0;     // 08
    uint8 reserved09[3]; // 09
    uint16 angle_C;      // 0C
    uint8 level_E;       // 0E: light level
    uint8 reserved0F[9]; // 0F
    STAGE_MATRIX matrix; // 18
    uint8 reserved38[8]; // 38
    sint32 color_40;     // 40
} STAGE_LIGHT;

// A 0x24-byte event slot (Open_EVE_WORK; freed through Close_EVE_WORK).
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01;      // 01
    uint8 kind_2;          // 02
    uint8 reserved03[9];   // 03
    sint8 timer_C;         // 0C
    sint8 step_D;          // 0D
    uint8 reserved0E[0xE]; // 0E
    uint32 key_1C;         // 1C
    uint8 reserved20[4];   // 20
} STAGE_EVENT;

// The record func_8002DC84 returns.
typedef struct
{
    uint32 head;
    uint32 b;
    void *c;
    uint32 d;
} STAGE_UNPACK;

// ROCK_NEO.EXE (the stcom headers declare some of these with their own types).
void func_80031988(void *wp);
STCOM_MATRIX *RotMatrixY(sint32 r, STCOM_MATRIX *m);
STCOM_MATRIX *RotMatrix(STCOM_SVECTOR *r, STCOM_MATRIX *m);
STCOM_MATRIX *MulMatrix(STCOM_MATRIX *m0, STCOM_MATRIX *m1);
void ApplyMatrixLV(STCOM_MATRIX *m, STCOM_FIXED_VECTOR *v0, STCOM_FIXED_VECTOR *v1);
STAGE_UNPACK func_8002DC84(void *obj, sint32 i, sint32 j);
void func_8002DE04(void *tbl, sint32 idx, sint32 *src);

// A pair of faces' lip-sync cue lists (mouth and eyes, or two speakers). A struct, not two
// pointers: GCC keeps the stores in order with the work slot's, and increments each directly.
typedef struct
{
    STAGE_MOUTH_CUE *cue_0;
    STAGE_MOUTH_CUE *cue_4;
} STAGE_LIP_CUES;

// Scene_work's bytes past STAGE_SCENE_WORK's fields (+8 and +9 are also read as bytes).
#define STAGE_SCENE_BYTE(offset) (*((uint8 *)&Scene_work + (offset)))
#define STAGE_SCENE_WORD(offset) (*(sint32 *)((uint8 *)&Scene_work + (offset)))

// A 16.16 value also read as two signed halves (an angle and a radius, say).
typedef union
{
    sint32 value;
    struct
    {
        uint16 fraction;
        sint16 integer;
    } words;
    sint16 half[2];
} STAGE_FIXED;

// A talking face kept in halfwords (at a work slot's +0x4E0).
typedef struct
{
    sint16 shape_0;  // 00
    sint16 prev_2;   // 02
    sint16 index_4;  // 04
    sint16 shape_6;  // 06
    sint16 prev_8;   // 08
    sint16 index_A;  // 0A
    sint16 *mouth_C; // 0C: shape, then 0x3FFF (hold) or 0x7FFF (loop)
    sint16 *eyes_10; // 10
} STAGE_FACE16;

// Two lip-sync script positions and their scripts (at a work slot's +0x4E0; st17's func_80107478 and the like reset them).
typedef struct
{
    uint8 reserved00[4]; // 0
    sint8 index_4;       // 4
    sint8 count_5;       // 5
    sint8 index_6;       // 6
    sint8 count_7;       // 7
    sint8 *mouth_8;      // 8
    sint8 *eyes_C;       // C
} STAGE_LIPS;

// The halfwords some objects keep at a work slot's +0x4E0 instead of a face.
typedef struct
{
    sint16 value_0;        // 00
    sint16 timer_2;        // 02
    sint16 value_4;        // 04
    sint16 value_6;        // 06
    STCOM_SVECTOR vec_8;   // 08
    STCOM_SVECTOR vec_10;  // 10: a saved position
    sint16 value_18;       // 18
    uint8 reserved1A[0xA]; // 1A
} STAGE_OBJ_HW;

// A fuller view of the work slots STAGE_WORK describes (0x3C0 bytes; the 0x5A4-byte slots carry
// a talking face at +0x4E0), for the code matched after STAGE_WORK was laid out. The two views
// should be merged.
typedef struct STAGE_OBJ STAGE_OBJ;

struct STAGE_OBJ
{
    sint8 flags_0;    // 00
    uint8 value_1;    // 01
    uint8 kind_2;     // 02
    uint8 variant_3;  // 03
    uint8 value_4;    // 04
    uint8 reserved05; // 05
    uint8 flags_6;    // 06
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
    sint32 value_10;                        // 10
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
    STAGE_OBJ *owner_308;                   // 308: the object that spawned it
    uint8 reserved30C[0xB4];                // 30C
    uint8 ext_3C0[0x120];                   // 3C0
    union
    {
        STAGE_FACE face;
        STAGE_FACE16 face16;
        STAGE_LIPS lips;
        STAGE_OBJ_HW hw;
    } u_4E0; // 4E0
};

typedef void (*STAGE_OBJ_FUNC)(STAGE_OBJ *wp);

// Player_work seen as a work slot (STCOM_PL_WORK doesn't name the saved position and rotation).
#define STAGE_PL_OBJ ((STAGE_OBJ *)&Player_work)

// A 0x48-byte effect slot as STAGE_EFFECT, with the fields past +0x34 the stage-unique effects use.
typedef struct STAGE_FX STAGE_FX;

struct STAGE_FX
{
    uint8 flags_0;       // 00
    uint8 reserved01;    // 01
    uint8 kind_2;        // 02
    uint8 variant_3;     // 03
    uint8 reserved04[2]; // 04
    uint8 flags_6;       // 06
    uint8 reserved07;    // 07
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09
    uint8 routine_2;     // 0A
    uint8 routine_3;     // 0B
    sint8 value_C;       // 0C
    sint8 timer_D;       // 0D
    sint8 frame_E;       // 0E
    sint8 type_F;        // 0F
    uint8 reserved10[4]; // 10
    uint32 mode_14;      // 14
    uint32 color_18;     // 18
    sint16 x_1C;         // 1C
    sint16 y_1E;         // 1E
    sint16 z_20;         // 20
    uint8 u_22;          // 22
    uint8 v_23;          // 23
    uint16 w_24;         // 24
    uint16 h_26;         // 26
    union
    {
        STAGE_FX *parent;  // the spawner
        STAGE_OBJ *object; // the object it follows
        sint32 count;      // frames left
    } u_28;
    STAGE_FIXED x_2C;     // 2C
    STAGE_FIXED y_30;     // 30
    STAGE_FIXED z_34;     // 34
    STAGE_FIXED value_38; // 38
    STAGE_FIXED value_3C; // 3C
    sint32 value_40;      // 40
    uint8 reserved44[4];  // 44
};

typedef void (*STAGE_FX_FUNC)(STAGE_FX *wp);

// A sprite frame in a table of four-byte records.
typedef struct
{
    uint8 u;
    uint8 v;
    uint16 w;
} STAGE_UVW;

STCOM_SVECTOR *ApplyMatrixSV(STCOM_MATRIX *m, STCOM_SVECTOR *v, STCOM_SVECTOR *r);

// A fuller view of the room script work (STAGE_ROOM_WORK), with all the objects it drives.
typedef struct STAGE_ROOM STAGE_ROOM;
typedef void (*STAGE_ROOM2_FUNC)(STAGE_ROOM *wp);

struct STAGE_ROOM
{
    uint8 flags_0;            // 00
    uint8 reserved01[3];      // 01
    uint8 routine_4;          // 04
    uint8 routine_5;          // 05
    uint8 routine_6;          // 06
    uint8 routine_7;          // 07
    uint8 routine_8;          // 08
    uint8 reserved09[3];      // 09: [1] flags (bit 0: skip, bit 7: skipping off)
    sint32 timer_C;           // 0C
    sint32 frame_10;          // 10: frames since the room started
    sint32 word_14;           // 14
    uint8 reserved18[0xC];    // 18
    STAGE_OBJ *child_24;      // 24: the objects the script drives
    STAGE_OBJ *child_28;      // 28
    STAGE_OBJ *child_2C;      // 2C
    STAGE_OBJ *child_30;      // 30
    STAGE_OBJ *child_34;      // 34
    STAGE_OBJ *child_38;      // 38
    STAGE_OBJ *child_3C;      // 3C
    STAGE_OBJ *child_40;      // 40
    STAGE_OBJ *child_44;      // 44
    STAGE_OBJ *child_48;      // 48
    STAGE_OBJ *child_4C;      // 4C
    STAGE_OBJ *child_50;      // 50
    STAGE_OBJ *child_54;      // 54
    STAGE_OBJ *child_58;      // 58
    STAGE_OBJ *child_5C;      // 5C
    STAGE_OBJ *child_60;      // 60
    uint8 reserved64[0x40];   // 64
    STAGE_ROOM2_FUNC *tbl_A4; // A4: [0] is also read as a byte (0xFF: no script)
};

// A 0x10C-byte work slot (Open_SHL_WORK).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01;                  // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 reserved04[4];               // 04
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 routine_2;                   // 0A
    uint8 routine_3;                   // 0B
    uint8 reserved0C[3];               // 0C
    uint8 value_F;                     // 0F
    uint8 reserved10[4];               // 10
    STCOM_SVECTOR position;            // 14
    STAGE_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x60];            // 2C
    STAGE_MATRIX matrix_8C;            // 8C
    STCOM_SVECTOR position_AC;         // AC
    sint32 color_B4;                   // B4
    uint8 reservedB8[0x14];            // B8
    sint32 x_CC;                       // CC
    sint32 y_D0;                       // D0
    sint32 z_D4;                       // D4
    uint8 reservedD8[4];               // D8
    sint16 radius_DC;                  // DC
    sint16 angle_DE;                   // DE
    sint16 speed_E0;                   // E0
    uint8 reservedE2[0x2A];            // E2
} STAGE_10C;

// ROCK_NEO.EXE's slot allocators (NULL when none is free).
STAGE_10C *Open_SHL_WORK(void);

// ROCK_NEO.EXE's sound work: +6 is the music volume.
typedef struct
{
    uint8 reserved00[6];
    sint16 volume_6;
} STAGE_SOUND_WORK;

extern STAGE_SOUND_WORK Sound_work;
extern uint8 Sound_fade_step_size;
extern uint8 Sound_fade_flags;
void Cd_read_comb(sint32 id);
sint32 Cd_read_sync2(void);
void Sound_fade_start(sint32 arg);
void func_80032304(void *wp, sint32 anim, sint32 arg);
void Pos_Shadow_Trans(STCOM_SVECTOR *pos, sint32 a1, sint32 a2, sint32 a3);
void Model_pose_unpack(void *wp);
void Model_parts_mtx_set_y(void *wp);

// Three shorts (a position in a table).
typedef struct
{
    sint16 x, y, z;
} STAGE_XYZ;

// The eight bytes func_8002DD1C returns: four (u, v) corners, also passed on as words.
typedef union
{
    uint8 b[8];
    sint32 w[2];
} STAGE_UV4;

STAGE_UV4 func_8002DD1C(void *tbl, sint32 idx);

// A 0x24-byte event slot as STAGE_EVENT, with more fields named.
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01;      // 01
    uint8 kind_2;          // 02
    uint8 variant_3;       // 03
    uint8 reserved04[2];   // 04
    uint8 flags_6;         // 06
    uint8 reserved07;      // 07
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 routine_3;       // 0B
    sint8 timer_C;         // 0C
    sint8 step_D;          // 0D
    sint8 value_E;         // 0E
    sint8 value_F;         // 0F
    uint8 reserved10[0xC]; // 10
    uint32 key_1C;         // 1C
    uint8 reserved20[4];   // 20
} STAGE_EV;

// A 0x50-byte slot (func_80031734).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 reserved04[2];    // 04
    uint8 flags_6;          // 06
    uint8 reserved07;       // 07
    uint8 routine_0;        // 08
    uint8 reserved09[0x2F]; // 09
    STCOM_SVECTOR pos_38;   // 38
    sint32 color_40;        // 40
    uint8 reserved44[0xC];  // 44
} STAGE_50;

STAGE_50 *func_80031734(void);

// A 0x3C0-byte work slot as the stage-unique actors use it: STAGE_OBJ with the words and halves
// from +0x44 on named (velocity, the turn speed at +0x64, the talk camera point at +0x180).
typedef struct STAGE_ACTOR STAGE_ACTOR;
typedef void (*STAGE_ACTOR_FUNC)(STAGE_ACTOR *wp);

// The block at +0x348 of STAGE_ACTOR.
typedef struct
{
    uint16 flags_0;        // 348
    uint8 reserved02[2];   // 34A
    sint16 timer_4;        // 34C
    uint8 reserved06[2];   // 34E
    sint16 value_8;        // 350
    uint8 reserved0A[0xA]; // 352
    uint32 hit_14;         // 35C: damage in the low 24 bits, kind bits above
} STAGE_ACTOR_CTL;

struct STAGE_ACTOR
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
    uint8 reserved7C[0x30];                 // 7C
    uint8 anim_AC;                          // AC
    uint8 reservedAD[3];                    // AD
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180: the talk camera's point
    uint8 reserved188[0x1C0];               // 188
    STAGE_ACTOR_CTL ctl;                    // 348
    uint8 reserved360[0x60];                // 360
};

// A matrix whose identity setup writes it as eight words.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
} STAGE_MATRIX_W;

// A 0x50-byte slot (func_80031734) as the stage-unique objects use it (STCOM21_WORK's layout).
typedef struct STAGE_OBJ50 STAGE_OBJ50;
typedef void (*STAGE_OBJ50_FUNC)(STAGE_OBJ50 *wp);

struct STAGE_OBJ50
{
    uint8 flags_0;       // 00
    uint8 index_1;       // 01
    uint8 kind_2;        // 02
    uint8 variant_3;     // 03
    uint8 reserved04[4]; // 04
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09
    uint8 routine_2;     // 0A
    uint8 routine_3;     // 0B
    union
    {
        sint16 half;
        struct
        {
            sint8 lo; // 0C
            sint8 hi; // 0D
        } b;
    } u_C;                 // 0C
    sint8 value_E;         // 0E
    sint8 value_F;         // 0F
    void *model_10;        // 10
    uint8 reserved14[4];   // 14
    STAGE_MATRIX_W matrix; // 18
    STCOM_SVECTOR pos_38;  // 38
    uint32 color_40;       // 40
    sint32 value_44;       // 44
    sint32 value_48;       // 48
    sint32 value_4C;       // 4C
};

void Sound_call(sint32 id, sint32 a1, sint32 a2);
// A texture animation: frame, then frames to hold it (ST02_ANIM, ST1E_ANIM).
typedef struct
{
    uint8 frame;
    uint8 hold;
} STAGE_ANIM;

void func_8002F9EC(void *wp, sint32 arg);
// Allocates a 0x3C0-byte work slot; NULL when none is free.
STAGE_OBJ *func_80031418(void);
// The scratchpad's copy of the current room's map bounds (0x1F800040): STAGE_MAP_X0..STAGE_MAP_H
// as one struct. The room setups write it this way (the struct keeps retail's store order).
typedef struct
{
    uint8 x0; // 40
    uint8 z0; // 41
    uint8 x1; // 42
    uint8 z1; // 43
    uint16 w; // 44
    uint16 h; // 46
} STAGE_MAP_AREA;

#define STAGE_MAP_AREA_SP (*(STAGE_MAP_AREA *)0x1F800040)
// An effect slot that fades out while it rises: +0x28 is its rise per frame and +0x2C the object
// whose routine ends it (r3_st02's ST02_SPARK; also in r3_st19).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[7];    // 01
    uint8 routine_0;        // 08
    uint8 reserved09[4];    // 09
    sint8 timer_D;          // 0D
    uint8 reserved0E;       // 0E
    sint8 type_F;           // 0F
    uint8 reserved10[8];    // 10
    uint32 color_18;        // 18
    uint8 reserved1C[2];    // 1C
    uint16 y_1E;            // 1E
    uint8 reserved20[4];    // 20
    uint16 w_24;            // 24
    uint8 reserved26[2];    // 26
    sint32 rise_28;         // 28
    STAGE_OBJ *owner_2C;    // 2C
    uint8 reserved30[0x18]; // 30
} STAGE_SPARK;

// Routines run on a work slot and its part at +0x88 (r3_st17's ST17_PART_FUNC; also in r3_st0b).
typedef void (*STAGE_PART_FUNC)(STAGE_OBJ *wp, void *part);

// Player_work with the fields the stage-unique code of r3_st00, r3_st05, r3_st06, r3_st0b, r3_st19
// and r3_st1a reaches named by offset (STCOM_PL_WORK names only a few).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved1[0x7];              // 01
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 value_0a;                    // 0A
    uint8 reservedB;                   // 0B
    sint32 value_C;                    // 0C
    uint8 reserved10[0x4];             // 10
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    sint16 value_2C;                   // 2C
    sint16 value_2E;                   // 2E
    sint16 value_30;                   // 30
    uint8 reserved32[0xA];             // 32
    sint32 value_3C;                   // 3C
    uint8 reserved40[0x4];             // 40
    sint16 value_44;                   // 44
    uint8 reserved46[0xE];             // 46
    STCOM_SVECTOR rotation;            // 54
    uint8 reserved5C[0x12];            // 5C
    sint16 value_6E;                   // 6E
    uint8 reserved70;                  // 70
    sint8 flags_71;                    // 71
    uint8 reserved72[0x2];             // 72
    uint8 value_74;                    // 74
    uint8 reserved75;                  // 75
    sint8 value_76;                    // 76
    uint8 reserved77[0x30];            // 77
    sint8 flags_A7;                    // A7
    uint8 reservedA8[0x4];             // A8
    uint8 value_AC;                    // AC
    uint8 reservedAD[0x3];             // AD
    sint16 value_B0;                   // B0
    uint8 reservedB2[0xB];             // B2
    uint8 flags_bd;                    // BD
    uint8 reservedBE[0x2];             // BE
    void *value_C0;                    // C0
    STCOM_SVECTOR value_C4;            // C4
    uint8 reservedCC[0x58];            // CC
    uint16 value_124;                  // 124
    uint8 reserved126[0x42];           // 126
    uint8 value_168;                   // 168
    uint8 value_169;                   // 169
    uint8 reserved16A[0x6];            // 16A
    uint8 value_170;                   // 170
    sint8 value_171;                   // 171
    uint8 reserved172[0x3];            // 172
    uint8 value_175;                   // 175
    uint8 reserved176[0xE];            // 176
    void *target_184;                  // 184
    uint8 reserved188[0x220];          // 188
    sint16 value_3A8;                  // 3A8
    sint16 value_3AA;                  // 3AA
    sint16 value_3AC;                  // 3AC
    uint8 reserved3AE[0x3C];           // 3AE
    sint16 value_3EA;                  // 3EA
    uint8 reserved3EC[0x3C];           // 3EC
    STCOM_FIXED_VECTOR fixed_428;      // 428: a position in 16.16
    STCOM_SVECTOR pos_438;             // 438: the same position
    sint16 value_440;                  // 440
    uint16 value_442;                  // 442
    sint16 value_444;                  // 444
    uint8 reserved446[0x2];            // 446
    uint8 value_448;                   // 448
    uint8 value_449;                   // 449
    uint8 reserved44A[0x4];            // 44A
    sint8 value_44E;                   // 44E
    uint8 reserved44F[0xB8];           // 44F
    sint8 value_507;                   // 507
    sint8 value_508;                   // 508
    uint8 reserved509[0x27B];          // 509
} STAGE_PL_VIEW;

#define STAGE_PL (*(STAGE_PL_VIEW *)&Player_work)

// The frame counter in the scratchpad (bit 0 alternates frames).
#define STAGE_FRAME (*(uint16 *)0x1F800002)

// Scene_work with its object pointers (ROCK_NEO's SCENE_WORK: slot_24[32]).
typedef struct
{
    uint8 reserved00[0x24]; // 00
    STAGE_OBJ *slot_24[32]; // 24
    void *script_A4;        // A4
} STAGE_SCENE_VIEW;

#define STAGE_SCENE (*(STAGE_SCENE_VIEW *)&Scene_work)

// Four bytes per model part in the 0x3C0 slots, from +0x100 (first and last byte used).
typedef struct
{
    uint8 value_0;
    uint8 reserved1[2];
    uint8 value_3;
} STAGE_PART;

// Game_work with the fields the stage-unique code of r3_st00, r3_st05, r3_st06, r3_st0b, r3_st19
// and r3_st1a reaches named by offset (STCOM_GAME_WORK names only a few).
typedef struct
{
    sint8 mode_0;            // 00
    sint8 value_1;           // 01
    uint8 reserved2[0x26];   // 02
    sint32 value_28;         // 28
    sint32 value_2C;         // 2C
    sint32 value_30;         // 30
    sint32 value_34;         // 34
    sint32 value_38;         // 38
    sint32 value_3C;         // 3C
    uint8 reserved40[0x10];  // 40
    sint8 value_50;          // 50
    sint8 value_51;          // 51
    sint8 value_52;          // 52
    uint8 reserved53[0x8];   // 53
    sint8 value_5B;          // 5B
    sint16 value_5C;         // 5C
    uint16 value_5E;         // 5E
    uint8 reserved60[0x6];   // 60
    uint8 value_66;          // 66
    uint8 value_67;          // 67
    uint8 reserved68[0x10];  // 68
    sint8 value_78;          // 78
    uint8 value_79;          // 79
    uint8 value_7A;          // 7A
    uint8 reserved7B[0x6];   // 7B
    uint8 value_81;          // 81
    uint8 reserved82;        // 82
    uint8 value_83;          // 83
    sint32 value_84;         // 84
    uint8 reserved88[8];     // 88
    sint32 value_90;         // 90
    uint8 reserved94[0x8C];  // 94
    sint32 value_120;        // 120
    uint8 reserved124[0x2C]; // 124
    sint32 value_150;        // 150
    uint8 reserved154[0x20]; // 154
    uint16 value_174;        // 174
    uint8 reserved176[4];    // 176
    uint16 value_17A;        // 17A
    sint16 value_17C;        // 17C
    uint8 reserved17E[0x16]; // 17E
    sint16 value_194;        // 194
    sint16 value_196;        // 196
    sint16 value_198;        // 198
    sint16 value_19A;        // 19A
} STAGE_GAME_VIEW;

#define STAGE_GAME (*(STAGE_GAME_VIEW *)&Game_work)

// A slot whose routines keep a matrix at +0x18 (r3_st00, r3_st05).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[7];    // 01
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint8 index_C;          // 0C
    uint8 reserved0D[0xB];  // 0D
    STAGE_MATRIX matrix_18; // 18
    STCOM_SVECTOR pos_38;   // 38
    uint32 color_40;        // 40
} STAGE_MATRIX_OBJ;

// A talking face's two lip-sync scripts, pointers first (r3_st07's ST07_FACE, r3_st17's ST17_FACE).
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
} STAGE_FACE2;

// The same with the script positions first (r3_st17's ST17_FACE2).
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
} STAGE_FACE8;

// A 0xC-byte record in a table of eight (r3_st05 D_80137E18, r3_st06 D_8012B990).
typedef struct
{
    uint8 active_0;     // 0
    uint8 index_1;      // 1
    uint8 value_2;      // 2
    uint8 value_3;      // 3
    void *data_4;       // 4
    uint8 reserved8[4]; // 8
} STAGE_REC;

// The identity as word stores through casts. The casts make each store a plain (non-struct)
// memory reference, so GCC 2.7 may schedule a load from the work slot (RotMatrixY's angle) above
// them; the union stores of STAGE_MATRIX_IDENTITY may alias it. Word 0 is stored last.
#define STAGE_MATRIX_IDENTITY_SCALAR(mw)                                                                                                   \
    (*(sint32 *)&(mw)[1] = 0, *(sint32 *)&(mw)[2] = 0x1000, *(sint32 *)&(mw)[3] = 0, *(sint32 *)&(mw)[4] = 0x1000,                         \
     *(sint32 *)&(mw)[5] = 0, *(sint32 *)&(mw)[6] = 0, *(sint32 *)&(mw)[7] = 0, *(sint32 *)&(mw)[0] = 0x1000)
// The current room's map in the scratchpad (the STAGE_MAP_* fields as one struct). Room setup
// writes it through this view: struct stores keep the room-table loads after them, as in retail.
typedef struct
{
    uint8 x0;      // 0x1F800040
    uint8 z0;      // 41
    uint8 x1;      // 42
    uint8 z1;      // 43
    uint16 w;      // 44
    uint16 h;      // 46
    sint16 *cells; // 48
    void *info;    // 4C
    void *exits;   // 50
} STAGE_MAP_WORK;

#define STAGE_MAP_WORK_PTR ((STAGE_MAP_WORK *)0x1F800040)

// A 16.16 position whose halfword view reads the integer parts (the SHL modules' SHL_FIXED).
typedef union
{
    struct
    {
        sint32 x, y, z, pad;
    } w;
    struct
    {
        uint16 x_lo;
        sint16 x;
        uint16 y_lo;
        sint16 y;
        uint16 z_lo;
        sint16 z;
        uint16 pad_lo;
        sint16 pad;
    } h;
} STAGE_SHOT_FIXED;

// A shot object with the SHL modules' SHL_WORK layout (a model shot's draw data at +0x88): the
// same routines are linked into several stages.
typedef struct
{
    uint8 flags_0; // 00
    uint8 value_1; // 01
    uint8 value_2; // 02
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
    sint8 value_e;   // 0E
    sint8 value_f;   // 0F
    uint8 reserved10[4];
    STCOM_SVECTOR pos;         // 14
    STAGE_SHOT_FIXED fpos;     // 1C
    STCOM_SVECTOR old_pos;     // 2C
    STAGE_SHOT_FIXED old_fpos; // 34
    STCOM_SVECTOR vel;         // 44
    sint16 ax, ay, az;         // 4C
    uint8 reserved52[2];
    STCOM_SVECTOR rot; // 54
    uint8 reserved5c[8];
    sint16 rot_y; // 64
    sint16 rot_x; // 66
    uint8 reserved68[0xC];
    sint8 value_74;
    uint8 reserved75[3];
    void *box_78;  // 78
    sint16 hit_7c; // 7C
    uint8 reserved7e[0xA];
    uint32 word_88;         // 88
    STCOM_MATRIX mtx_8c;    // 8C
    STCOM_SVECTOR draw_pos; // AC
    uint32 color_b4;        // B4
    uint8 reservedb8[4];    // B8
    uint32 col_bc;          // BC
    uint32 col_c0;          // C0
    uint32 col_c4;          // C4: hit accumulator (func_8003430C)
    uint32 col_c8;          // C8
    sint32 value_cc;        // CC
    sint32 value_d0;        // D0
    uint32 value_d4;        // D4
} STAGE_SHOT;

// An effect slot from func_80031618 as the shot routines fill it (the SHL modules' SHL_FX).
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
    uint8 reserved36[2];
    STCOM_SVECTOR pos_38; // 38
    uint32 value_40;      // 40
    uint8 reserved44[4];
} STAGE_SHOT_FX;

sint32 func_800375D4(void *pl, sint32 arg);
void func_8003430C(void *pos_a, sint32 a1, void *pos_b, sint32 a3, sint32 a4, sint32 a5, sint32 a6, void *hit, sint32 flags, sint32 a9,
                   sint32 a10);

// Player_work while a room routine drives it: the bytes at +0xC to +0xE are its own routine
// indices and timer (r3_st06, r3_st0b).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01[0xB];             // 01
    sint8 routine_C;                   // 0C
    sint8 routine_D;                   // 0D
    sint8 timer_E;                     // 0E
    uint8 reserved0F[0x5];             // 0F
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x3FC];           // 2C
    STCOM_FIXED_VECTOR fixed_428;      // 428
    STCOM_SVECTOR pos_438;             // 438
    sint16 value_440;                  // 440
    uint16 value_442;                  // 442
    sint16 value_444;                  // 444
    uint8 reserved446[0x2];            // 446
    uint8 value_448;                   // 448
} STAGE_PL_SCRIPT;

typedef void (*STAGE_PL_SCRIPT_FUNC)(STAGE_PL_SCRIPT *wp);

// A spawned room-script object as the code that ends it sees it (stcom36's STCOM36_OBJ layout).
typedef struct STAGE_SPAWNED STAGE_SPAWNED;
typedef void (*STAGE_SPAWNED_FUNC)(STAGE_SPAWNED *wp);

struct STAGE_SPAWNED
{
    uint8 flags_0;    // 00
    uint8 index_1;    // 01: pool id and slot
    uint8 kind_2;     // 02: first index into the pool's handler table
    uint8 value_3;    // 03
    uint8 handler_4;  // 04: second index (two-level tables)
    uint8 value_5;    // 05
    uint8 flags_6;    // 06
    uint8 reserved07; // 07
    uint8 routine_0;  // 08
};

#define STAGE_SPAWNED_TABLE_3C0 (*(STAGE_SPAWNED_FUNC ***)0x1F800058)
#define STAGE_SPAWNED_TABLE_10C (*(STAGE_SPAWNED_FUNC **)0x1F800060)

sint32 func_8002FE74(uint8 id);

// Returns a work slot by index, or NULL (r3_st00, r3_st1a: tried from 0x1F down).
void *func_800317AC(sint32 index); // returns the slot; callers use it as their own view

// Scene_work's object table at +0x24 (stcom36's obj_24): the scene's objects by slot.
#define STAGE_SCENE_OBJ(i) (((void **)((uint8 *)&Scene_work + 0x24))[i])

// stcom19's floor panel (STCOM19_MATRIX, STCOM19_WORK) as the stage-unique panels use it.
// A matrix whose identity setup writes its halfwords two at a time.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
} STAGE_PANEL_MATRIX;

// The 0x50-byte work slot of a floor panel that turns over (func_80031734).
typedef struct
{
    uint8 flags_0;             // 00
    uint8 reserved01;          // 01
    uint8 kind_2;              // 02
    uint8 value_3;             // 03: 0xFF for the spawner
    uint8 reserved04[4];       // 04
    uint8 routine_0;           // 08
    uint8 reserved09[2];       // 09
    uint8 timer_B;             // 0B
    sint8 dir_C;               // 0C: rotation.y / 0x400
    uint8 value_D;             // 0D
    uint8 reserved0E[0xA];     // 0E
    STAGE_PANEL_MATRIX matrix; // 18: words[5] and words[6] hold the cell values to restore
    STCOM_SVECTOR pos_38;      // 38
    uint32 color_40;           // 40
    sint32 cell_44;            // 44: index into the room's cell table
    uint8 reserved48[8];       // 48
} STAGE_PANEL_WORK;

// A room cell (ROCK_NEO's table at 0x8015C000, 12 bytes each), seen from its value word.
typedef struct
{
    uint32 value;
    uint8 reserved4[8];
} STAGE_CELL;

// The cells at their fixed address: GCC adds the index before the base, as retail does.
#define STAGE_CELLS ((STAGE_CELL *)0x8015C008)

// A 0x10C-byte slot (Open_SHL_WORK) that keeps its direction at +0x64: the pieces the r3_st09 and
// r3_st1d actors spawn (kind 9).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01;                  // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 reserved04[0x10];            // 04
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x38];            // 2C
    sint16 angle_64;                   // 64
    uint8 reserved66[0xA6];            // 66
} STAGE_PIECE;

// The 0x98 bytes from +0x328 of a 0x3C0-byte slot as the stage-unique actors of r3_st09 and
// r3_st1d use them (their routines often reach them through a pointer; offsets relative to
// +0x328). The actors differ, so a field may mean different things.
typedef struct
{
    uint16 flags_0; // 00
    union
    {
        uint16 h;
        uint8 b[2];
    } u_2; // 02
    union
    {
        sint16 h[2];
        sint32 w;
    } u_4;                 // 04
    uint16 value_8;        // 08
    sint16 value_A;        // 0A
    STCOM_SVECTOR pos_C;   // 0C: the hit box's center
    sint32 value_14;       // 14
    sint32 value_18;       // 18
    STCOM_SVECTOR from_1C; // 1C: where a hit came from (flags in pad)
    union
    {
        uint8 track[0x10]; // Track_set
        sint32 w[4];
    } u_24; // 24
    union
    {
        sint16 h[2];
        sint32 w;
    } u_34; // 34
    union
    {
        sint16 h[2];
        sint32 w;
    } u_38; // 38
    union
    {
        uint16 h[2];
        sint32 w;
    } u_3C;            // 3C
    STAGE_OBJ *obj_40; // 40
    union
    {
        STAGE_FX *fx[2];
        uint16 h[2];
    } u_44; // 44
    union
    {
        void *p;
        sint32 i;
    } u_4C;                  // 4C
    STCOM_EFFECT *effect_50; // 50
    STAGE_PIECE *piece_54;   // 54
    union
    {
        STAGE_OBJ *obj;
        sint16 h[2];
    } u_58; // 58
    union
    {
        void *p;
        sint32 w;
        struct
        {
            uint8 value_0;
            sint8 value_1;
            sint8 value_2;
            uint8 value_3;
        } b;
    } u_5C;                 // 5C
    uint8 reserved60[4];    // 60
    sint16 value_64;        // 64
    uint8 reserved66[0x1E]; // 66
    sint16 value_84;        // 84
    uint8 reserved86[4];    // 86
    uint16 value_8A;        // 8A
    uint8 value_8C;         // 8C
    uint8 reserved8D[0xB];  // 8D
} STAGE_ACTOR_EXT;

// A scratchpad halfword the r3_st09 and r3_st1d actors set before Model_parts_mtx_set_y.
#define STAGE_SP_13A (*(uint16 *)0x1F80013A)

// A 0x10C-byte slot (Open_SHL_WORK) of a prop that turns and talks: r3_st03's func_80112098 and its
// copies in r3_st05 and r3_st0e.
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
    sint8 value_C;                          // 0C
    uint8 reserved0D[3];                    // 0D
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    sint32 value_44;                        // 44
    sint32 value_48;                        // 48
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 value_64;                        // 64
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    uint8 *data_78;                         // 78
    uint8 reserved7C[0x10];                 // 7C
    STAGE_MATRIX matrix_8C;                 // 8C
    STCOM_SVECTOR position_AC;              // AC
    sint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    uint16 flags_BC;                        // BC
    uint16 rand_BE;                         // BE
    union
    {
        sint16 h[2];
        sint32 w;
    } u_C0;                 // C0
    uint8 reservedC4[0x48]; // C4
} STAGE_PROP;

// Scene_work at its fixed address: GCC rebuilds the address at each access instead of keeping
// &Scene_work.value_10 in a register across calls (r3_st0b's func_801038C0, r3_st06's
// func_80116570).
#define STAGE_SCENE_PTR ((STAGE_SCENE_WORK *)0x800C4C48)

// stcom15's block (STCOM15_CTL), in the copies r3_st09 and r3_st13 keep at +0x348 or +0x4E0.
typedef struct
{
    uint16 flags_0;          // 00
    uint16 rand_2;           // 02: a new random number every frame
    sint16 timer_4;          // 04
    sint16 level_6;          // 06: row of the kind's table (D_80098844)
    uint16 value_8;          // 08: or'd into the hit block's kind bits
    sint16 timer_A;          // 0A
    STCOM_SVECTOR pos_C;     // 0C: the hit box's center
    uint32 hit_14;           // 14: damage in the low 24 bits, kind bits above
    uint32 value_18;         // 18
    STCOM_SVECTOR target_1C; // 1C: the attacker's position (pad bit 0: from the player?)
    uint8 track_24[0x10];    // 24
    sint16 timer_34;         // 34
    sint16 timer_36;         // 36
    sint16 timer_38;         // 38: frames before it bursts (flags_0 0x40)
    uint16 flag_3A;          // 3A: scene flag (from position.pad)
    union
    {
        uint8 *steps;        // frames per hop (stcom15_D_0050, stcom15_D_005C)
        uint16 flag;         // a scene flag (r3_st13's func_80111E90)
    } u_3C;                  // 3C
    STCOM_EFFECT *effect_40; // 40
    sint16 turn_44;          // 44
    sint16 angle_46;         // 46: its bearing from the player, relative to the player's facing
    uint32 hit_48;           // 48: ground hit flags (Obj_map_push_out)
    void *shot_4C;           // 4C
} STAGE_STCOM15_CTL;

// stcom15's work slot (STCOM15_WORK) with the block at +0x4E0: r3_st09's func_8010FBB8 and r3_st13's
// func_80111814.
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02: index into D_80098844
    uint8 variant_3;                        // 03: flags
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 param_C;                          // 0C
    sint8 param_D;                          // 0D: frames before it charges again
    uint8 param_E;                          // 0E: routine_1 to go back to
    uint8 param_F;                          // 0F: life multiplier - 1 (low 7 bits)
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    sint16 turn_66;                         // 66
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[8];                    // 70
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80: screen depth?
    uint8 reserved84[0x22];                 // 84
    sint8 value_A6;                         // A6: animation frame
    uint8 reservedA7[5];                    // A7
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joints_180[0x6C];         // 180: joint positions
    STAGE_STCOM15_CTL ctl;                  // 4E0
} STAGE_STCOM15_WORK_4E0;

typedef void (*STAGE_STCOM15_FUNC_4E0)(STAGE_STCOM15_WORK_4E0 *wp);

// stcom15's work slot (STCOM15_WORK) with the block at +0x348: r3_st03's func_80105178 and r3_st09's
// func_8010870C.
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02: index into D_80098844
    uint8 variant_3;                        // 03: flags
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 param_C;                          // 0C
    sint8 param_D;                          // 0D: frames before it charges again
    uint8 param_E;                          // 0E: routine_1 to go back to
    uint8 param_F;                          // 0F: life multiplier - 1 (low 7 bits)
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    sint16 turn_66;                         // 66
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[8];                    // 70
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80: screen depth?
    uint8 reserved84[0x22];                 // 84
    sint8 value_A6;                         // A6: animation frame
    uint8 reservedA7[5];                    // A7
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joints_180[0x39];         // 180: joint positions
    STAGE_STCOM15_CTL ctl;                  // 348
    uint8 reserved398[0x28];                // 398
} STAGE_STCOM15_WORK_348;

typedef void (*STAGE_STCOM15_FUNC_348)(STAGE_STCOM15_WORK_348 *wp);

// stcom19's spawner tables (STCOM19_CELL_REC, STCOM19_SPAWN, STCOM19_ROOM, STCOM19_OFFSET), for the
// copies of its panel spawner in r3_st09 and r3_st1d.
// A room cell's record (ROCK_NEO's table at 0x8015C000): its position and its attribute.
typedef struct
{
    STCOM_SVECTOR pos;
    uint32 *info;
} STAGE_CELL_REC;

#define STAGE_CELL_TBL ((STAGE_CELL_REC *)0x8015C000)

// A panel to spawn on every cell whose attribute is type_4: two panels, one per byte of spawn_E
// (variant in the high nibble, direction in the low one).
typedef struct
{
    uint32 key_0;     // 00: 0 ends the list
    uint32 type_4;    // 04
    sint16 x_8;       // 08
    sint16 y_A;       // 0A
    sint16 z_C;       // 0C
    uint8 spawn_E[2]; // 0E
} STAGE_PANEL_SPAWN;

// The rooms that have panels: stage 0xFF ends the table.
typedef struct
{
    uint8 stage;
    uint8 room;
    uint8 reserved2[2];
    STAGE_PANEL_SPAWN *list;
} STAGE_PANEL_ROOM;

// A panel's offset from its cell, per direction.
typedef struct
{
    sint16 x, z;
} STAGE_PANEL_OFFSET;

// Game_work's panel count at +0x7E.
#define STAGE_PANEL_COUNT (*((uint8 *)&Game_work + 0x7E))

// Game_work's halfword at +0x62: a counter the r3_st03, r3_st13 and r3_st1b room scripts compare.
#define STAGE_GAME_COUNT_62 (*(uint16 *)((uint8 *)&Game_work + 0x62))

// A 0x50-byte slot (func_80031734) that spins a model: a matrix at +0x18 turned by the angle at
// +0x4C (r3_st0e and r3_st14).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 value_1;          // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint8 value_C;          // 0C
    sint8 value_D;          // 0D
    sint8 value_E;          // 0E
    sint8 value_F;          // 0F
    uint8 reserved10[8];    // 10
    STAGE_MATRIX matrix_18; // 18
    STCOM_SVECTOR pos_38;   // 38
    uint32 color_40;        // 40
    uint8 reserved44[4];    // 44
    void *slot_48;          // 48
    sint32 angle_4C;        // 4C
} STAGE_SPIN;

// STAGE_PART with a signed last byte (-1 hides the part): r3_st00, r3_st0b.
typedef struct
{
    uint8 value_0;
    uint8 reserved1[2];
    sint8 value_3;
} STAGE_PART_S;

// The scratchpad as a wheeled walker writes it: the wheel angles its model's draw reads
// (r3_st05's func_80111898 area, r3_st19's func_80104D38).
typedef struct
{
    uint8 reserved000[0x138]; // 000
    sint16 wheel_138;         // 138
    uint8 reserved13A[0xE];   // 13A
    sint16 wheel_148;         // 148
} STAGE_WHEEL_SCRATCH;

#define STAGE_WHEEL_SP ((STAGE_WHEEL_SCRATCH *)0x1F800000)

// The camera block at 0x800BC730 (ROCK_NEO's SCENE_CAM): position and angles, 16.16 (r3_st04,
// r3_st05).
typedef struct
{
    uint8 reserved00[0x10]; // 00
    sint32 pos_10;          // 10
    sint32 pos_14;          // 14
    sint32 pos_18;          // 18
    uint8 reserved1C[0x24]; // 1C
    sint32 rot_40;          // 40
    sint32 rot_44;          // 44
    sint32 rot_48;          // 48
} STAGE_CAM;

// A STAGE_REC as its handlers see it: a signed step and a timer (r3_st05 D_80130638, r3_st06).
typedef struct
{
    uint8 active_0;     // 0
    uint8 index_1;      // 1
    sint8 step_2;       // 2
    uint8 value_3;      // 3
    void *data_4;       // 4
    sint16 timer_8;     // 8
    uint8 reservedA[2]; // A
} STAGE_REC_S;

// Player_work's pad words: held at +0x124, pressed at +0x12A (r3_st06; r3_st03's own view has
// them too).
typedef struct
{
    uint8 reserved000[0x124]; // 000
    uint16 pad_124;           // 124
    uint8 reserved126[4];     // 126
    uint16 pad_12A;           // 12A
} STAGE_PL_PAD;

// ROCK_NEO's camera request at 0x800C3560 (D_800C3560 to D_800C3571) through its literal
// address: as struct fields its stores stay in order with loads from a table (r3_st1d, r3_st19).
typedef struct
{
    sint16 x_0;         // 0
    sint16 y_2;         // 2
    sint16 z_4;         // 4
    uint8 reserved6[4]; // 6
    sint16 angle_A;     // A
    sint8 mode_C;       // C
    sint8 value_D;      // D
    uint8 value_E;      // E
    uint8 value_F;      // F
    uint8 value_10;     // 10
    uint8 value_11;     // 11
} STAGE_CAM_REQ;

#define STAGE_CAM_REQ_PTR ((STAGE_CAM_REQ *)0x800C3560)

// PsyQ's TILE (a flat rectangle), as the full-screen fades fill it (ST00_TILE in r3_st00, r3_st0a).
typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    short w, h;
} STAGE_TILE;

#endif // STAGE_COMMON_STAGE_H
