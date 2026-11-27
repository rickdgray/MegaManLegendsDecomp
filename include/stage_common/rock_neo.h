#ifndef STAGE_COMMON_ROCK_NEO_H
#define STAGE_COMMON_ROCK_NEO_H

#include "common.h"
#include "work.h" // the pool slot header and be_flag's bits

// ROCK_NEO.EXE declarations used by the shared stage code. Overlays don't see ROCK_NEO.EXE's
// headers when compiling, so these are the stage code's own views: only the fields it uses.

// Evaluates `x` twice, like Capcom's own.
#define STCOM_ABS(x) ((x) < 0 ? -(x) : (x))
// GCC's builtin abs: it keeps a stack temporary per use, where the macro reserves none.
int abs(int x);

// Game_work's stage (value_50) and room (value_51) read as one halfword: stage | room << 8.
#define STCOM_STAGE_ROOM (*(uint16 *)&Game_work.value_50)

// Player_work at its fixed address: GCC rebuilds a literal address at each access instead of
// keeping it in a register.
#define STCOM_PLAYER_WORK_PTR ((STCOM_PL_WORK *)0x800B51B0)

typedef struct
{
    sint16 x, y, z, pad;
} STCOM_SVECTOR;

// A 16.16 fixed-point value whose integer half is read on its own.
typedef union
{
    sint32 value;
    struct
    {
        uint16 fraction;
        sint16 integer;
    } words;
} STCOM_FIXED;

typedef struct
{
    sint32 x, y, z, pad;
} STCOM_FIXED_VECTOR;

// A short vector also written as two words.
typedef union
{
    STCOM_SVECTOR v;
    uint32 words[2];
} STCOM_SVECTOR_W;

// Game_work (ROCK_NEO's GAME_WORK)
typedef struct
{
    sint8 mode_0;           // 00
    uint8 reserved01[0x4F]; // 01
    sint8 value_50;         // 50: stage
    sint8 value_51;         // 51: room
    sint8 value_52;         // 52: the room's script set
    uint8 reserved53[0x25]; // 53
    uint8 value_78;         // 78
    uint8 value_79;         // 79
    uint8 value_7A;         // 7A
    uint8 reserved7B[6];    // 7B
    uint8 value_81;         // 81
} STCOM_GAME_WORK;

// PsyQ's MATRIX.
typedef struct
{
    sint16 m[3][3];
    sint32 t[3];
} STCOM_MATRIX;

// A primitive's color word (code in the top byte), whose red byte is also read on its own.
typedef union
{
    uint32 word;
    uint8 rgb[4];
} STCOM_COLOR;

// A 0x34-byte sprite record: in stcom06's work slot at +0x88, copied whole into an effect.
typedef struct
{
    uint32 mode_0;          // 00
    STCOM_COLOR color_4;    // 04
    sint16 pos_8[3];        // 08: x, y, z
    uint8 value_E;          // 0E
    uint8 value_F;          // 0F
    uint16 value_10;        // 10
    sint16 value_12;        // 12
    uint32 hit_14;          // 14: collision result bits (spawn speed until the first frame)
    sint32 value_18;        // 18
    uint8 reserved1C[8];    // 1C
    STCOM_SVECTOR position; // 24
    uint8 reserved2C[8];    // 2C
} STCOM_SPRITE;

// A 0x48-byte effect slot from func_80031618 (only the fields used so far).
typedef struct
{
    uint8 be_flag;       // 00
    uint8 work_id;       // 01
    uint8 id;            // 02
    uint8 type;          // 03
    uint8 reserved04[4]; // 04
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09: also a frame counter (stcom14)
    uint8 routine_2;     // 0A
    uint8 timer_B;       // 0B: frames (stcom35)
    uint8 value_C;       // 0C
    sint8 value_D;       // 0D
    sint8 timer_E;       // 0E: frames left
    sint8 value_F;       // 0F
    uint8 reserved10[4]; // 10
    STCOM_SPRITE sprite; // 14 (position at 38)
} STCOM_EFFECT;

// Player_work (ROCK_NEO's PL_WORK)
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 work_id;                     // 01
    uint8 reserved02[6];               // 02
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 value_0a;                    // 0A
    uint8 reserved0B;                  // 0B
    sint32 value_C;                    // 0C
    uint8 reserved10[4];               // 10
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x28];            // 2C
    STCOM_SVECTOR rotation;            // 54
    uint8 reserved5C[0x12];            // 5C
    sint16 value_6E;                   // 6E: compared with half of value_B0 (life?)
    uint8 reserved70;                  // 70
    sint8 flags_71;                    // 71: sign bit tested
    uint8 reserved72[4];               // 72
    sint8 value_76;                    // 76: nonzero while holding something
    uint8 reserved77[0x30];            // 77
    sint8 flags_A7;                    // A7: sign bit tested
    uint8 reservedA8[8];               // A8
    sint16 value_B0;                   // B0
    uint8 reservedB2[0xB];             // B2
    uint8 flags_bd;                    // BD
    uint8 reservedBE[2];               // BE
    void *value_C0;                    // C0: the work slot it holds
    STCOM_SVECTOR value_C4;            // C4
    uint8 reservedCC[0xB8];            // CC
    void *target_184;                  // 184: the work slot the player is talking to
    uint8 reserved188[0x262];          // 188
    sint16 value_3EA;                  // 3EA: a height (stcom11 aims at it)
    uint8 reserved3EC[0x5C];           // 3EC
    uint8 value_448;                   // 448
    uint8 reserved449[0x33B];          // 449
} STCOM_PL_WORK;

extern STCOM_PL_WORK Player_work;
extern STCOM_GAME_WORK Game_work;
extern sint16 D_800C3560;
extern sint16 D_800C3562;
extern sint16 D_800C3564;
extern sint16 D_800C356A;
extern sint8 D_800C356C;
extern sint8 D_800C356D;
extern uint8 D_800C356E;
extern uint8 D_800C356F;
extern uint8 D_800C3570;
extern uint8 D_800C3571;
extern sint16 D_80098A72;
extern sint8 D_800987B0[]; // [0]: nonzero while the screen is fading
extern uint32 Moji_flag;
extern sint32 D_800A396C;
extern uint16 Clut_buf[]; // shadow copy of the texture pages (palettes live here)

sint32 rand(void);
void MojiTaskKill(void);
// ROCK_NEO's prototype takes uint8s, but the stage code passes signed bytes without
// narrowing them (stcom12_func_0710), so it was compiled against an int prototype.
void MojiTaskExec2(sint32 a, sint32 b);
sint32 func_8003A13C(void);
sint32 func_80039E18(void);
sint32 Angle_xz_svector(STCOM_SVECTOR *pos, STCOM_SVECTOR *target);
void func_80039FAC(STCOM_FIXED_VECTOR *pos, sint32 a1, sint32 angle, sint32 a3);
// Muku (turns the angle `rot` at `pos` toward `target` by at most `speed`, returns the
// step) is declared by each file's header: stcom15 uses its result without narrowing (int), the
// others as a sint16.
// Obj_ceiling_height_get (the ground height under a work slot) is declared by each file's header: ROCK_NEO
// returns an int, and stcom15 compares the result unextended, but stcom04 and stcom12 narrow it
// to sint16 at the call.
// Angle_diff_clamp (steps an angle toward a goal by at most a speed, returns the step) is declared
// by each file's header: its callers disagree on the return type (sint16 in stcom01, int in
// stcom04, which retail evidently called without a sint16 prototype).
// Rotates (x, y, z) by `angle` into `out`.
STCOM_FIXED_VECTOR *func_80030058(STCOM_FIXED_VECTOR *out, sint32 angle, sint16 x, sint16 y, sint16 z);
void Model_work_init(void *wp, uint8 *variant);
void func_800322A8(void *wp, sint32 anim, sint32 arg);
void func_80032488(void *wp);
void Model_Shadow_Trans(void *wp, sint32 a1, sint32 a2, sint32 a3);
void func_80051B68(void *wp, sint32 a1, sint32 a2, sint32 a3);
// Moves a work slot by (x, y, z) along its rotation. ROCK_NEO declares sint16 parameters, but
// stcom13 passes velocity * 16 without narrowing, so the stage code saw int ones.
void Obj_pos_set(void *wp, sint32 x, sint32 y, sint32 z);
void func_80063BC8(void *pos, sint32 a1, sint32 a2, sint32 a3);
// Frees a 0x24-byte event work slot.
void Close_EVE_WORK(void *wp);
void Sound_call2(sint16 id, void *args);
void Sce_flag_on(sint32 flag);
void Obj_work_flag_change(sint32 mask, sint32 flags);
void func_8005C150(sint32 index, sint32 mode, sint32 value, sint32 id);
void Fade_start(sint32 arg);
sint32 func_800341BC(void *pos, sint32 half, sint32 arg2, sint32 arg3, sint32 id, void *tbl, sint32 arg6, sint32 arg7, sint32 arg8);
void func_80051BAC(void *wp);
// Allocates an effect record; NULL when none is free.
STCOM_EFFECT *func_80031618(void);
// Sets a 16.16 position from a short one.
void func_80030150(STCOM_FIXED_VECTOR *fixed, STCOM_SVECTOR *pos);
void Close_PL_SHL_WORK(void *wp);
void Wall_reflect_spd(STCOM_SVECTOR *velocity, sint32 hit);
// PsyQ libgte.
sint32 rsin(sint32 a);
sint32 rcos(sint32 a);
void func_80042314(void *pl);
// Nonzero when the player is free to be taken over by a script.
sint32 func_80042238(void *pl);
void Cd_xa_seek_id(sint32 arg);
// Moves `pos` (and its 16.16 copy) by (x, y, z) turned by `angle`. ROCK_NEO declares sint16
// offsets, but stcom17 passes 0xFF710 unnarrowed, so the stage code saw int ones.
void func_8002FFC4(STCOM_SVECTOR *pos, STCOM_FIXED_VECTOR *fixed, sint32 angle, sint32 x, sint32 y, sint32 z);
sint32 func_80049C24(void *wp);
sint32 func_80037BB4(void *wp);
void func_80037738(sint32 value, uint32 amount);
// Distance between two positions.
sint32 Distance_xyz(STCOM_SVECTOR *a, STCOM_SVECTOR *b);
// Frees a 0x10C-byte work slot.
void Close_SHL_WORK(void *wp);
// PsyQ libgte.
STCOM_MATRIX *RotMatrixYXZ(STCOM_SVECTOR *r, STCOM_MATRIX *m);
STCOM_MATRIX *ScaleMatrix(STCOM_MATRIX *m, STCOM_FIXED_VECTOR *v);
// Distance between two work slots' positions.
uint32 Obj_distance_xyz(void *a, void *b);
void func_80032538(void *wp);
void Model_parts_mtx_set_yxz(void *wp);
sint32 Map_area_check(STCOM_SVECTOR *pos);
sint32 Obj_map_push_out(void *wp);
// Frees a 0x3C0-byte work slot.
void func_80031824(void *wp);
// Hand-written: copies `count` 32-byte blocks.
void Mem_copy32(void *src, void *dst, sint32 count);

// D_800C356C read as an array (the same symbol): GCC keeps an array's address in a register
// across calls, where the scalar gets a lui/%lo pair at each access.
extern sint8 D_800C356C_A[] __asm__("D_800C356C");
// Game_work's halfword at +0x5C (a life counter in st17) as an array, for the same reason.
extern sint16 Game_work_5C[] __asm__("Game_work+0x5C");

#endif // STAGE_COMMON_ROCK_NEO_H
