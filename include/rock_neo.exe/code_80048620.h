#ifndef CODE_80048620_H
#define CODE_80048620_H

// code_80048620.c (not identified yet; rename with the file): the stage collision services. They
// take any model object (MODEL_WORK) and its collision box (HIT_ENT), both in code_8002E7A8.h.

#include "common.h"
#include "psyq/libgte.h"
#include "code_8002E7A8.h"
#include "player.h"
#include "scene.h"

// Scratchpad byte of per-axis bits the collision code writes: x 1/2 (func_80050B74), z 4/8
// (func_80050BB4), y 0x10/0x20 (func_80050BF4), the low bit of each pair when the move was
// positive. func_80050A24/A90/AFC test them.
#define D_1F8000FF (*(sint8 *)0x1F8000FF)

// Scratchpad vector the collision code keeps; func_80050A24/A90/AFC test its vx/vz/vy.
#define D_1F8000D0 (*(SVECTOR *)0x1F8000D0)

// The whole move the collision of map_push_out checks (D_1F8000C0 - D_1F8000C8; D_1F8000D0 is
// one step of it); func_8004BDC8 weighs its vx and vz against a corner's sides.
#define D_1F8000D8 (*(SVECTOR *)0x1F8000D8)

// Scratchpad halfwords per axis (x, y, z); func_80050B74 clears x and func_80050BB4 clears z
// when their axis's bits in D_1F8000FF were set.
#define D_1F800106 ((sint16 *)0x1F800106)

// Scratchpad halfwords per axis (x, y, z) after D_1F80010C, cleared by map_push_out; a step up
// in func_8004BDC8 copies x and z into D_1F800106.
#define D_1F800112 ((sint16 *)0x1F800112)

// Scratchpad byte map_push_out sets from its argument; func_8004BDC8 lets the box step up onto
// a block only while it is 0.
#define D_1F8000F6 (*(sint8 *)0x1F8000F6)

// D_1F8000F6 and the byte after it in one halfword: func_8004BDC8 stores 0x100 (clears
// D_1F8000F6, sets 0x1F8000F7 to 1) when the box lands.
#define D_1F8000F6_h (*(sint16 *)0x1F8000F6)

// The byte after D_1F8000F6: set when the box landed (func_8004BDC8); func_80051F08 seeds both
// from the rider's field_74 and field_76 and reads them back.
#define D_1F8000F7 (*(sint8 *)0x1F8000F7)

// Scratchpad halfwords per axis (x, y, z) after D_1F800106; the rounded corner push
// (func_8004FF14) sets x and z to minus the push.
#define D_1F80010C ((sint16 *)0x1F80010C)

// Scratchpad offset vector func_8004B3C0 sets (from its argument, or zero).
#define D_1F800124 (*(VECTOR *)0x1F800124)

// The same three words stored one by one (Ceiling_height_get, ...): plain word stores, not struct
// fields, so GCC lets the next block's loads move above them.
#define D_1F800124_w ((sint32 *)0x1F800124)

// The same scratchpad words seen as a collision box (the callers pass an object's hit_78):
// the block tests of Block_test_tbl (func_8004E304, ...) shrink a block's x/z rectangle by it.
#define D_1F800124_box (*(HIT_ENT *)0x1F800124)

// Scratchpad point the block tests of Block_test_tbl check against a block's rectangle (vx, vz).
#define D_1F8000C0 (*(SVECTOR *)0x1F8000C0)

// Sets the MATRIX *m to the identity with eight word stores in address order (front_hit_search):
// the words through a plain sint32 view, t's included (as fields, GCC moves their stores first).
#define MATRIX_IDENTITY_W(m)                                                                                                               \
    (((sint32 *)(m))[0] = 0x1000, ((sint32 *)(m))[1] = 0, ((sint32 *)(m))[2] = 0x1000, ((sint32 *)(m))[3] = 0,                             \
     ((sint32 *)(m))[4] = 0x1000, ((sint32 *)(m))[5] = 0, ((sint32 *)(m))[6] = 0, ((sint32 *)(m))[7] = 0)

// Scratchpad point: the origin of the collision func_80052674 tests (a solid object's).
#define D_1F8000E0 (*(SVECTOR *)0x1F8000E0)

// Scratchpad point the diagonal block tests (func_8004E490, ...) check a second time (vx, vz)
// once D_1F8000C0 is inside: which side of the diagonal it is on picks their return value.
#define D_1F8000C8 (*(SVECTOR *)0x1F8000C8)

// Scratchpad corners of the last rectangle a block test hit: min x/z in D_1F8000F0.vx/vz, max
// in D_1F8000F8.vx/vz.
#define D_1F8000F0 (*(SVECTOR *)0x1F8000F0)
#define D_1F8000F8 (*(SVECTOR *)0x1F8000F8)

// Scratchpad byte: the side of the slope the last slope_fit call placed the box on (1-4: a
// z or x ramp, 5-8: a diagonal one), or 0.
#define D_1F8000FE (*(sint8 *)0x1F8000FE)

// Scratchpad list of up to 4 map cell indexes (Map_cells) around a point, from func_8004B1E0.
#define D_1F800118 ((sint16 *)0x1F800118)

// Scratchpad vector the corner push (func_800501E8) sets vy of (minus the height pushed by).
#define D_1F800100 (*(SVECTOR *)0x1F800100)

// The same vector as halfwords per axis (x, y, z), like D_1F800106 after it: indexed, GCC keeps
// each element's address in a register (solid_push_out), where the fields are plain stores.
#define D_1F800100_h ((sint16 *)0x1F800100)

// 12-byte entry pushed on the D_80098894 list by func_80051B68 (an object and its three
// arguments); D_800BC058 holds 0x40 of them. Solid_collide_all collides every object of the
// D_80098898 list against it, by kind_4: 0-3 a MODEL_WORK solid (1 and 3 with func_80051F08,
// 2 and 3 keeping the pushed axes), 4-7 a WORK_48 with a model EFC (copied to D_8009A770).
// part_6 picks a part of the solid (-1: none), hit_8 is passed to func_80051F08.
typedef struct
{
    union
    {
        MODEL_WORK *model; // kinds 0-3
        WORK_48 *w48;      // kinds 4-7
    } obj;
    sint16 kind_4;
    sint16 part_6;
    sint32 hit_8;
} OBJ_REQ;

// Two lists that Solid_collide_all walks and func_80051B40 resets: write pointers (pool small data)
// and their buffers.
extern OBJ_REQ *D_80098894;
extern MODEL_WORK **D_80098898;
extern OBJ_REQ D_800BC058[0x40];
extern MODEL_WORK *D_800BC360[];

// Stand-in solid for the WORK_48 entries (kinds 4-7) of the D_80098894 list: Solid_collide_all copies
// the object's position, model data and collision box here and collides against it.
extern MODEL_WORK D_8009A770;

// Camera scripts (SCENE_CAM_WORK.arg_C0) for func_80048704, one per quarter turn of the area
// entry's facing angle (D_800C3558.ang_y >> 10).
extern uint32 *D_8008A9E4[4];

// The same for func_80048620, which starts the event table D_8008A9F4 with it.
extern uint32 *D_8008A9D4[4];

// func_80048620's event table: one step (func_80048BE4, an empty function), then the end.
extern EVENT_ENT D_8008A9F4[];

// The special STG_HIT (kind 0x100 and up) front_hit_search finds at or in front of an object.
typedef struct
{
    SVECTOR pos;  // 0x0: the middle of the hit's box; pad: the object's facing (ang.vy)
    uint16 kind;  // 0x8: STG_HIT.kind >> 8, 0 if none
    uint16 flags; // 0xA: STG_HIT.flags
} FRONT_HIT;

// Block test of Block_test_tbl: is D_1F8000C0 inside the rectangle rect (x0, x1, z0, z1) of a block
// of shape kind (STG_HIT.kind)? 0 if not.
typedef sint32 (*BLOCK_TEST_FUNC)(sint16 *rect, sint32 kind);

// The same tests called with the rectangle alone (front_hit_search); most of them only take rect.
typedef sint32 (*BLOCK_TEST_RECT_FUNC)(sint16 *rect);

// The block tests, by the high nibble of STG_HIT.kind.
extern BLOCK_TEST_FUNC Block_test_tbl[8];

// Per stage (Game_work.stage_no), the frame count of func_80048A9C's second wait.
extern uint8 D_8008AA04[];

// The values Front_hit_event hands to func_80063BC8 for its event hits, by FRONT_HIT.kind (0x20
// to 0x64: D_8008AA58 is indexed by the kind itself, so it runs on past its label) or by the
// low nibble of FRONT_HIT.flags (the others, one kind each).
extern uint8 D_8008AA44[];
extern uint8 D_8008AA50[];
extern uint8 D_8008AA58[];
extern uint8 D_8008AA60[];
extern uint8 D_8008AA68[];
extern uint8 D_8008AA6C[];
extern uint8 D_8008AA70[];

sint32 func_80049C24(MODEL_WORK *obj);          // the IDX entry obj touches, or 0
sint32 Obj_ceiling_height_get(MODEL_WORK *obj); // the lowest ceiling over obj (func_80048EA4)
// The nearest wall face on the side pl faces (a quarter of its facing angle), or -/+0x7FFF.
sint32 func_8004976C(PL_WORK *pl);
// Collides obj's move against the map; returns the hit flags (as Pos_map_push_out).
sint32 Obj_map_push_out(MODEL_WORK *obj);
// The lowest ceiling above pos in its map block, or 0x7FFF.
sint32 Ceiling_height_get(SVECTOR *pos);
sint32 Obj_floor_height_get(MODEL_WORK *obj); // floor_height_get at obj's position
// The slope side (D_1F8000FE) of a flag-0x4000 hit at pos, or 0.
sint32 func_8004AF28(SVECTOR *pos);
// The lowest ceiling over pos for the box ent (plus ent's max_A), or 0x7FFF + max_A if none.
sint32 func_80048EA4(SVECTOR *pos, HIT_ENT *ent, sint32 dy, sint32 kind);
// Collides the move old -> pos against ent; returns hit flags (0x1000 = floor).
sint32 Pos_map_push_out(SVECTOR *pos, SVECTOR *old, sint32 n, HIT_ENT *ent);
// Bounces the speed vel (x, y, z) off the walls in hit; 1 if there were any.
sint32 Wall_reflect_spd(sint16 *vel, sint32 hit);
// The map cell value at pos for the box ent, with the hit's flags in bits 16-19; 0 if open.
sint32 func_80049C54(SVECTOR *pos, SVECTOR *prev, HIT_ENT *ent, sint32 kind);
// If obj's routine_0 has bit 0 or 1 set, pushes obj on the list at D_80098898; clears +0x7C.
// Called with player objects, SHL_WORK shots and the stage overlays' objects.
void func_80051BAC(MODEL_WORK *obj);
sint32 func_80048CEC(sint32 index); // Map_cells[index]
sint32 func_80050B68(SVECTOR *v);   // v->vy != 0
sint32 func_80050BF4(SVECTOR *v);
void func_80051B40(void);
// Map_cells at pos, or 0 outside the map window.
sint32 Map_cell_get(SVECTOR *pos);
// 0 if pos is inside the map window, -1 outside.
sint32 Map_area_check(SVECTOR *pos);
// The cell of room map's map (Stage_map_tbl) at pos, or 0 outside it.
sint32 Stage_map_cell_get(sint32 map, SVECTOR *pos);
// The low 12 bits of the pad of the map block under pos, or 0.
sint32 func_80048E18(SVECTOR *pos);
// Reflects *angle off the walls in hit; 1 if there were any.
sint32 func_8004AE88(sint16 *angle, uint32 hit);
void func_8004B3C0(VECTOR *ofs);
sint32 func_80050A24(SVECTOR *v);
sint32 func_80050A90(SVECTOR *v);
sint32 func_80050AFC(SVECTOR *v);
void func_80050B74(SVECTOR *v);
void func_80050BB4(SVECTOR *v);
// If obj's routine_0 has bit 0 or 1 set, pushes obj and the three values on the D_80098894 list.
void func_80051B68(MODEL_WORK *obj, sint32 arg1, sint32 arg2, sint32 arg3);
// Called with an object about to be closed (func_8002FBF4): clears field_76 and field_C0 of every
// live player, WORK_3C0, WORK_5A4 and SHL_WORK whose field_C0 is that object.
void func_80052528(void *key);
void func_80052644(void *key, MODEL_WORK *obj);
void func_80048A40(WORK_48 *wp); // flag_4 2 of func_800485E4 (D_8008A778)
// Acts on the special hit in front of pl (front_hit_search): exits, doors and event triggers.
// Returns the hit's kind, or 0 if there is none.
sint32 Front_hit_event(PL_WORK *pl);
// Carry pl (pos_l, pos, ang.vy; or the saved pos_428, svec_438, ang_440) along with obj, the
// object it rides, by obj's move and turn.
void Ride_move(PL_WORK *pl, MODEL_WORK *obj);
void Ride_move_saved(PL_WORK *pl, MODEL_WORK *obj);
void func_800534E0(MODEL_WORK *obj, MODEL_WORK *rider, VECTOR *pos, VECTOR *old, VECTOR *pt, VECTOR *move);
void Solid_collide_all(void); // per frame (game's game_frame_exec)

#endif // CODE_80048620_H
