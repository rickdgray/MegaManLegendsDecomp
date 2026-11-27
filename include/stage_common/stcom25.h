#ifndef STCOM25_H
#define STCOM25_H

#include "common.h"
#include "stage_common/rock_neo.h"

// A node of a course: a map cell and the nodes it leads to.
typedef struct
{
    uint8 x_0;     // 0: map cell, offset by 0x40
    uint8 z_1;     // 1
    uint8 flags_2; // 2: 0xF chance of each branch, 0x10 turn left, 0xE0 kind of corner
    uint8 dir_3;   // 3: 0x30 direction
    uint8 next[4]; // 4: next nodes (a start record: variant_3, then the first nodes)
} STCOM25_NODE;

// The block at +0xCC of the work slot.
typedef struct
{
    STCOM25_NODE *nodes_0; // CC
    STCOM25_NODE *start_4; // D0: start records, by param_D
    uint8 *order_8;        // D4: node order for the scripted course (start next[0] == 6)
    uint8 dir_C;           // D8: direction it rolls, 0..3
    uint8 dir_D;           // D9
    uint8 node_E;          // DA: the node it rolls to
    uint8 flags_F;         // DB
    sint16 speed_10;       // DC: target speed
    sint16 phase_12;       // DE: how far it has turned over, 0..0x400
    sint16 dist_14;        // E0: distance to the node
    sint16 pivot_16;       // E2: the edge it turns over (x)
    sint16 pivot_18;       // E4: (z)
    sint16 index_1A;       // E6: position in order_8
    sint16 value_1C;       // E8
    uint8 reserved1E[2];   // EA
} STCOM25_CTL;

// The 0x10C-byte work slot (freed through Close_SHL_WORK) of a block that rolls over and over
// along a course of map cells.
typedef struct
{
    uint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 reserved0A[2];                    // 0A
    sint8 course_C;                         // 0C: index into the course tables
    sint8 start_D;                          // 0D: start record
    uint8 reserved0E[6];                    // 0E
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44: x is the speed
    STCOM_SVECTOR_W accel;                  // 4C: x is the acceleration
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x14];                 // 64
    void *data_78;                          // 78
    uint8 reserved7C[0x10];                 // 7C
    STCOM_MATRIX matrix;                    // 8C
    STCOM_SVECTOR draw_pos;                 // AC
    uint32 color_B4;                        // B4
    uint8 reservedB8[0x14];                 // B8
    STCOM25_CTL ctl;                        // CC
    uint8 reservedEC[0x20];                 // EC
} STCOM25_WORK;

typedef void (*STCOM25_FUNC)(STCOM25_WORK *wp);

extern sint16 stcom25_D_0000[][4];     // by course_C: [0] the length of order_8
extern STCOM25_NODE *stcom25_D_03B4[]; // by course_C: nodes
extern STCOM25_NODE *stcom25_D_03E0[]; // by course_C: start records
extern uint8 *stcom25_D_040C[];        // by course_C: node order
extern STCOM25_FUNC stcom25_D_0438[];  // routine_0 (stcom25_func_0000)
extern STCOM25_FUNC stcom25_D_0448[];  // routine_1 (stcom25_func_02CC)

sint16 stcom25_func_06E4(STCOM25_WORK *wp);
void stcom25_func_08AC(STCOM25_WORK *wp);
void stcom25_func_0A38(STCOM25_WORK *wp);
void stcom25_func_0D08(STCOM25_WORK *wp, sint16 size);
void stcom25_func_0E3C(STCOM25_WORK *wp);

// ROCK_NEO.EXE.
// The ground height at a position.
sint16 Ceiling_height_get(STCOM_SVECTOR *pos);
// PsyQ libgte.
STCOM_MATRIX *RotMatrix(STCOM_SVECTOR *r, STCOM_MATRIX *m);

#endif // STCOM25_H
