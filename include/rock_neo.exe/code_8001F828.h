#ifndef CODE_8001F828_H
#define CODE_8001F828_H

#include "common.h"
#include "psyq/libgte.h"

// Draws one map block's model (data pointer, depth). Picked from Map_block_draw_tbl[kind][bit 31 of the
// model's LOD word]. The model starts with a header word: bits 0-7 the number of CLUT words after it
// (copied to Quad_clut_tbl), bits 8-13 the number of parts; the parts follow the CLUT words, two
// words each (texture and face pointers, as func_80023EA8 reads them).
typedef void (*MAP_DRAW_FUNC)(u_long *model, sint32 z);

// [kind][bit 31 of the LOD word]: every entry is one of this file's draw functions.
extern MAP_DRAW_FUNC Map_block_draw_tbl[4][4];

// Pool variable (0x800987D4): cleared by func_8002037C and debug_mem_dump, tested by Print.
extern sint8 D_800987D4;
// Pool variable (0x800987DC): cleared by func_8002037C, read and stepped by Print and
// Debug_text_draw.
extern sint8 D_800987DC;
// Pool variable (0x8009893C): write pointer into Debug_text_buf (Print advances it;
// func_8002037C and Debug_text_draw reset it to the start).
extern uint8 *Debug_text_ptr;
// Debug text queue: Print appends entries while Debug_text_ptr is below its end;
// Debug_text_draw draws and empties it each frame. An entry is x (two bytes, high first), y, the
// colour, then the text up to a 0 byte (control codes: 7 toggles cycling colours, 8 back a
// character, 9 a tab of four, 10 newline, 11 line feed, 12 and 13 nothing).
#define DEBUG_TEXT_BUF_SIZE 0x4B0
extern uint8 Debug_text_buf[DEBUG_TEXT_BUF_SIZE];
// The debug font's CLUTs, by colour (+8: the second half of the font).
extern uint16 D_80097C44[];
// The colours Debug_text_draw cycles through after control code 7.
extern uint8 D_80089888[];

// A short x/y pair. Copied whole: its halfword alignment gives lwl/lwr.
typedef struct
{
    sint16 x, y;
} MODEL_XY;

// A 16.16 fixed-point x/y pair.
typedef struct
{
    sint32 x, y;
} MODEL_FIX2;

// A room model record, 0x38 bytes (the overlays' STAGE_MODEL), D_800BBA90[11]. Room_model_init fills
// it from a model header (eleven halfwords, then the tile map that map_34 points to). With flags_0
// bit 1, Room_model_update draws it as a screen layer of 32x32 SPRTs (one per map word: the u/v and
// CLUT), wrap_x_24 by wrap_y_26 tiles, scrolled by pos_C.
typedef struct
{
    uint8 flags_0;           // 00: the header's first halfword is stored over flags_0 and flags_1;
                             // bit 0: moved each frame (Room_model_update), bit 1: drawn
    uint8 flags_1;           // 01: nonzero: Room_model_init resets the positions to pos_1C,
                             // room_model_pos_wrap wraps x too, and the speeds move it; zero: it
                             // follows the camera
    uint8 reserved02[2];     // 02
    MODEL_FIX2 fpos_4;       // 04
    MODEL_XY pos_C;          // 0C
    MODEL_FIX2 fpos_prev_10; // 10
    MODEL_XY pos_prev_18;    // 18
    MODEL_XY pos_1C;         // 1C: starting position
    sint16 speed_x_20;       // 20: x scroll per frame (8.8)
    sint16 speed_y_22;       // 22: y scroll per frame (8.8); cleared by Room_model_init
    sint16 wrap_x_24;        // 24: room_model_pos_wrap wraps fpos_4.x into [0, wrap_x_24 << 21)
    sint16 wrap_y_26;        // 26: and fpos_4.y into [0, wrap_y_26 << 21)
    uint16 value_28;         // 28: added to each map word, << 14
    uint16 tpage_2A;         // 2A: the layer's draw mode (DR_MODE) tpage bits
    union
    {
        u_long w;    // the SPRTs' colour (low 24 bits)
        uint16 h[2]; // as Room_model_init stores it
        uint8 b[4];  // b[3]: the ordering table entry the layer is linked to
    } rgb_2C;        // 2C
    union
    {
        uint16 w;      // as Room_model_init stores it
        uint8 b[2];    // b[0]: semi-transparent SPRTs (code bit 1), b[1]: the blend mode (tpage bits 5-6)
    } abr_30;          // 30
    uint16 reserved32; // 32
    u_long *map_34;    // 34: the tile map (wrap_x_24 by wrap_y_26 words): the header's data after its
                       // eleven halfwords and six more
} ROOM_MODEL;

// The room models (cleared by Work_pools_init).
extern ROOM_MODEL D_800BBA90[11];

// Pool variables, cleared by Room_model_init unless D_800C356C is -1.
extern sint32 D_80098970;
extern sint32 D_80098A78;

// Room_model_init's argument, kept on the scratchpad while it runs.
#define Scratch_model_hdrs (*(uint16 ***)0x1F800054)

// u/v pairs of a quad being split in four: the corners', then those of the edge midpoints and the
// centre, in the order of the screen XYs. As words: the face's four pairs, two to a word.
typedef union
{
    u_long w[2];
    uint16 h[9];
    uint8 b[18]; // u, then v
} SPLIT_UV;

// The map tiles' scratchpad work area at 0x1F800130: tile_model_draw builds a tile face there, and
// tile_quad_split splits a textured quad from it into four quads and four triangles.
typedef struct
{
    uint8 reserved00[8];
    u_long fog_08;   // 08: fog CLUT bits, OR'd into each primitive's uv0/CLUT word
    u_long clut_0C;  // 0C: the model's CLUT (high half) and tpage (low half)
    u_long rgbc3_10; // 10: colour and code word of the split's triangles (POLY_FT3)
    u_long rgbc4_14; // 14: colour and code word of the face (POLY_FT4, or POLY_FT3)
    uint8 reserved18[8];
    long sxy_20[10]; // 20: screen XY: the four corners, then the split's edge midpoints and centre
    u_long *ot_48;   // 48: the OT entry the face is linked into
    uint8 reserved4C[4];
    SPLIT_UV uv_50; // 50
    uint8 reserved64[0xC];
    SVECTOR v_70[4]; // 70: the face's corners in model space
    u_long clut_90;  // 90: CLUT bits for the uv0/CLUT word (clut_0C's high half)
    u_long tpage_94; // 94: tpage bits for the uv1/tpage word (clut_0C's low half)
    uint8 reserved98[8];
    uint8 idx_A0[28]; // A0: the split's vertex lists (sxy_20 indices): four quads of four, then
                      // four triangles of three
} TILE_WORK;

#define Tile_work (*(TILE_WORK *)0x1F800130)

// Bit n of f, tested through the sign of a shift, as the target does (sll, then bltz/bgez).
#define BIT_TEST(f, n) ((sint32)((f) << (31 - (n))) < 0)

// The same quad split on another scratchpad layout, at 0x1F800100 (quad_split and its copy
// quad_split2), also used by the map block draw functions (func_80023EA8). Field roles as in
// TILE_WORK.
typedef struct
{
    uint8 fog_00[0x20]; // 00: fog CLUT rows by depth (Quad_fog_tbl)
    uint8 idx_20[28];   // 20: the split's vertex lists (sxy_60 indices)
    u_long *ot_3C;      // 3C
    SVECTOR pos_40;     // 40: the model's position
    u_long fog_48;      // 48
    u_long flags_4C;    // 4C: the face's flag word (Quad_face_flags)
    u_long rgbc3_50;    // 50
    u_long rgbc4_54;    // 54
    u_long clut_58;     // 58
    u_long tpage_5C;    // 5C
    union
    {
        long w[10]; // screen XY words
        struct
        {
            uint16 x, y;
        } h[10]; // as halves (func_80023EA8)
    } sxy_60;    // 60
    union
    {
        SPLIT_UV uv; // the split's u/v pairs: the last is written over vtx[0], once it is read
        struct
        {
            u_long uv[2]; // the face's four u/v pairs, two to a word
            uint8 reserved90[8];
            SVECTOR vtx[4]; // 98: the face's corners in model space (Quad_vtx)
        } face;
    } u_88;                 // 88
    uint8 reservedB8[4];    // B8
    sint32 part_z_BC;       // BC: depth up to which func_80023CF0 and its copies draw a block model's
                            // sixth part
    sint32 near_z_C0;       // C0: Quad_near_z
    uint8 reservedC4[4];    // C4
    u_long clut_tbl_C8[16]; // C8: Quad_clut_tbl; the block draw functions copy a model's CLUT words
                            // here
} QUAD_WORK;

#define Quad_work (*(QUAD_WORK *)0x1F800100)
// The face's corners in model space (u_88.face.vtx). quad_split reads them through this pointer,
// not as a Quad_work field: the target keeps the address of Quad_vtx[0].vx in a register for its
// later store to u_88.uv.b[16], the same byte, which needs the plain address.
#define Quad_vtx ((SVECTOR *)0x1F800198)
// sxy_60 as x/y pairs (func_80023EA8's on-screen tests).
#define Quad_sxy ((DVECTOR *)0x1F800160)
// CLUT (high half) and tpage (low half) words, picked by bits 24-27 of a model's first header word
// (Quad_work.clut_tbl_C8 by address, as the quad draws read it; the block draw functions fill it
// through Quad_work, which the target needs for the order of their copies).
#define Quad_clut_tbl ((u_long *)0x1F8001C8)
// The player's position in view space, stored by func_80023728 over reservedB8, part_z_BC and
// near_z_C0: its z stays as Quad_near_z.
#define Quad_pl_view (*(VECTOR *)0x1F8001B8)
// The split's vertex lists (in .sdata, outside this file), copied to Quad_work.idx_20 by
// func_80023728.
extern uint8 D_80097C90[];
// Depth below which func_80024F30 tints a face over the screen centre with D_1F80007C
// (Quad_work.near_z_C0 by address).
#define Quad_near_z (*(sint32 *)0x1F8001C0)
// Quad_work.fog_00 by address, as func_80023EA8 reads it.
#define Quad_fog_tbl ((uint8 *)0x1F800100)
// Quad_work.flags_4C by address: func_80023EA8 stores it this way, not through its Quad_work pointer.
#define Quad_face_flags (*(u_long *)0x1F80014C)
// The face count of the model being drawn (func_80023EA8 stores it).
#define Quad_face_count (*(sint32 *)0x1F8001FC)

// num_format's flags word: the base minus 1 in bits 0-3, a prefix character in bits 4-11.
#define FMT_BASE_MASK 0xF
#define FMT_CHAR_MASK 0xFF0
#define FMT_BASE(n)   ((n)-1)    // the base field for base n
#define FMT_CHAR(c)   ((c) << 4) // the prefix field for character c
#define FMT_LONG      0x10000000 // Print's 'l' size flag (no effect: long and int are one size)
#define FMT_HAS_CHAR  0x04000000 // set by num_format when there is a prefix character
#define FMT_SIGNED    0x08000000 // negative values are printed as their magnitude
#define FMT_ZERO_PAD  0x40000000 // pad with '0' (after the prefix character)
#define FMT_LEFT      0x80000000 // left-justify (pad with spaces after the digits)

// "0123456789ABCDEF": num_format's digits.
extern char Num_digit_tbl[];

// Two tables of 16-bit values (zero in the image, so filled at run time) that func_800272D0 reads
// every fourth entry of, as the cosine and sine of its 16 ring segments (one 4096 = 1.0).
extern sint16 D_800BAEB8[];
extern sint16 D_800BBD00[];

// Tiles too close to draw as a model (map_tile_draw queues them for later): a word per tile, x in
// bits 24-31, y in bits 16-23, the tile id in the low half; D_8009886C (a pool variable) counts them,
// up to 0x80.
extern uint32 D_8009886C;
extern uint32 D_800BBE50[0x80];

// map_view_draw's view of the map window, on the scratchpad at 0x1F800100: the rectangle of cells
// around the camera it draws itself (x0..x1, y0..y1, ends exclusive), which map_view_cols_draw and
// map_view_rows_draw skip, and the slopes of the view's two edges (4096 = 1) they scan between.
typedef struct
{
    sint16 x0;
    sint16 y0;
    sint16 x1;
    sint16 y1;
    sint16 edge_0;
    sint16 edge_1;
} MAP_VIEW;

#define Map_view (*(MAP_VIEW *)0x1F800100)
// Map_view's rectangle by address, as map_view_draw sets it: the target keeps each field's own
// address in a register for its store and clipped re-store, which the struct form doesn't give.
#define Map_view_x0 (*(sint16 *)0x1F800100)
#define Map_view_y0 (*(sint16 *)0x1F800102)
#define Map_view_x1 (*(sint16 *)0x1F800104)
#define Map_view_y1 (*(sint16 *)0x1F800106)

// Fog distances by Scratch_scale_shift (0-2), stored to Scratch_fog_1 by map_view_draw: the second
// table when Scratch_fog_2 bit 2 is set. In .sdata, outside this file.
extern sint32 D_80097C78[3];
extern sint32 D_80097C84[3];

// Print's position word: x in pixels (bits 0-8), y (bits 9-16) and the colour (bits 17-19).
// Capcom's macro, from its use in disc/tcrf.txt (Print(XYC(16, 120, 2), "BUG!!")).
#define XYC(x, y, c) ((x) | ((y) << 9) | ((c) << 17))
// The same word by column and row (8-pixel units).
#define TEXT_POS(x, y, c) (((x) << 3) | ((y) << 12) | ((c) << 17))

void Print(uint32 pos, const char *fmt, ...); // printf-style debug text
void func_80020A40(void);                     // zeroes D_80097C3C
void func_8002037C(void);                     // called at the end of System_init
void Debug_text_draw(void);                   // called once per frame by main
void Room_model_update(void);                 // per frame (game's game_frame_exec)
void Map_draw(void);                          // per frame (game's game_frame_exec)

#endif
