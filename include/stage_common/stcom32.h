#ifndef STCOM32_H
#define STCOM32_H

#include "common.h"
#include "stage_common/rock_neo.h"

// A matrix whose identity setup writes it as eight words.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
} STCOM32_MATRIX;

#define STCOM32_IDENTITY(mw)                                                                                                               \
    ((mw)->words[0] = 0x1000, (mw)->words[1] = 0, (mw)->words[2] = 0x1000, (mw)->words[3] = 0, (mw)->words[4] = 0x1000,                    \
     (mw)->words[5] = 0, (mw)->words[6] = 0, (mw)->words[7] = 0)

// Variants 1..3 are a sprite instead of a model: its record overlays the matrix.
typedef struct
{
    uint32 tpage_0; // 14: palette << 16 | texture page
    uint32 color_4; // 18
    sint16 x_8;     // 1C
    sint16 y_A;     // 1E
    sint16 z_C;     // 20
    uint8 u_E;      // 22
    uint8 v_F;      // 23
    sint16 w_10;    // 24
    sint16 h_12;    // 26
} STCOM32_SPRITE;

// The 0x50-byte work slot (func_80031734) of an item the player picks up: a model (variant 0)
// or a sprite (1..3).
typedef struct
{
    uint8 be_flag;       // 00
    uint8 slot;          // 01: pool id and slot
    uint8 id;            // 02
    uint8 type;          // 03
    uint8 reserved04[4]; // 04
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09
    uint8 timer_A;       // 0A: also the model's turn
    uint8 reserved0B[5]; // 0B
    void *model_10;      // 10
    union
    {
        struct
        {
            uint8 reserved14[4];   // 14
            STCOM32_MATRIX matrix; // 18
        } model;
        STCOM32_SPRITE sprite; // 14
    } u_14;
    STCOM_SVECTOR pos_38; // 38
    uint32 color_40;      // 40
    uint8 reserved44[4];  // 44
    sint32 hit_48;        // 48
    sint32 value_4C;      // 4C
} STCOM32_WORK;

// Where a stage keeps the sprite's texture (stage_0 -1 ends the table).
typedef struct
{
    sint8 stage_0;  // 0
    uint8 tp_1;     // 1: texture page color mode
    uint8 abr_2;    // 2: semi-transparency
    uint8 page_3;   // 3: texture page number
    sint16 clut_x4; // 4: palette position
    sint16 clut_y6; // 6
} STCOM32_TEXTURE;

typedef void (*STCOM32_FUNC)(STCOM32_WORK *wp);

extern STCOM32_FUNC stcom32_D_0000[];    // routine_0 handlers (stcom32_func_0000)
extern uint32 stcom32_D_000C[];          // model
extern sint32 stcom32_D_0068[];          // scene flag set once picked up, by type
extern STCOM32_TEXTURE stcom32_D_0078[]; // by stage
extern uint8 stcom32_D_0098[][4];        // the sprite's u, v, w, h by type
extern sint32 stcom32_D_00A8[];          // the item given, by type

void stcom32_func_0678(STCOM32_WORK *wp);

// ROCK_NEO.EXE.
void func_80031A4C(STCOM32_WORK *wp);
STCOM_MATRIX *RotMatrixX(sint32 r, STCOM_MATRIX *m);
STCOM_MATRIX *RotMatrixY(sint32 r, STCOM_MATRIX *m);
STCOM_MATRIX *RotMatrixZ(sint32 r, STCOM_MATRIX *m);

// The scratchpad's frame counter.
#define STCOM32_FRAME (*(uint16 *)0x1F800002)

#endif // STCOM32_H
