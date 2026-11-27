#ifndef STCOM29_H
#define STCOM29_H

#include "common.h"
#include "stage_common/rock_neo.h"

// One step of a texture animation script: frames shown for `time_0` ticks (0xFF ends the
// script and loops it, 0 ends it for good).
typedef struct
{
    uint8 time_0;
    sint8 frame_1;
} STCOM29_STEP;

// The 0x24-byte event slot of the scripted objects (freed through Close_EVE_WORK).
typedef struct
{
    uint8 be_flag;          // 00
    uint8 work_id;          // 01
    uint8 reserved02;       // 02
    uint8 type;             // 03
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 reserved0A[2];    // 0A
    sint8 script_C;         // 0C: index into stcom29_D_00BC
    sint8 step_D;           // 0D
    sint8 timer_E;          // 0E
    uint8 reserved0F[0x11]; // 0F
    uint32 key_20;          // 20: the model (Stage_hed_model_get)
} STCOM29_WORK;

// The 0x24-byte event slot of the five-layer texture animation.
typedef struct
{
    uint8 be_flag;       // 00
    uint8 work_id;       // 01
    uint8 reserved02;    // 02
    uint8 type;          // 03
    uint8 reserved04[4]; // 04
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09
    uint8 reserved0A[2]; // 0A
    uint8 step_C[5];     // 0C: each layer's step in stcom29_D_0110
    uint8 timer_11[5];   // 11
    uint8 reserved16[6]; // 16
    uint32 key_1C[2];    // 1C: the models (Stage_hed_model_get)
} STCOM29_ANIM_WORK;

// The record func_8002DC84 returns.
typedef struct
{
    uint32 head;
    uint32 b;
    void *c;
    uint32 d;
} STCOM29_UNPACK;

// The eight bytes func_8002DD1C returns: four (u, v) corners, also passed on as words.
typedef union
{
    uint8 b[8];
    sint32 w[2];
} STCOM29_UV4;

typedef void (*STCOM29_FUNC)(STCOM29_WORK *wp);
typedef void (*STCOM29_ANIM_FUNC)(STCOM29_ANIM_WORK *wp);

extern uint32 stcom29_D_0000[];            // model keys by type
extern uint8 stcom29_D_000C[][8];          // UV corners by frame
extern STCOM29_STEP *stcom29_D_00BC[];     // scripts
extern STCOM29_FUNC *stcom29_D_00E0[];     // routine_0 handlers by type (stcom29_func_0000)
extern uint8 stcom29_D_010C[];             // the model's part by type
extern uint8 stcom29_D_0110[5][29][2];     // each layer's (frame, time) steps
extern uint8 stcom29_D_0234[5][4];         // each layer's first u per corner
extern uint8 stcom29_D_0248[];             // each layer's texture entry
extern uint8 stcom29_D_0250[];             // each layer's model (key_1C index)
extern STCOM29_ANIM_FUNC stcom29_D_0258[]; // routine_0 handlers (stcom29_func_05E0)
extern STCOM29_FUNC stcom29_D_0260[];      // routine_0 handlers (stcom29_func_0920)

void stcom29_func_0294(STCOM29_WORK *wp);
void stcom29_func_04B4(void);
uint8 stcom29_func_055C(void);

// ROCK_NEO.EXE.
extern uint8 *D_8008CE04; // a message script
extern uint8 *D_8008CE3C; // a message script
uint32 Stage_hed_model_get(uint32 key);
sint32 Sce_flag_test(sint32 flag);
void Sce_flag_off(sint32 flag);
sint32 func_8003B2D4(sint32 row, sint32 bit);
STCOM29_UNPACK func_8002DC84(void *obj, sint32 i, sint32 j);
STCOM29_UV4 func_8002DD1C(void *tbl, sint32 idx);
void func_8002DE04(void *tbl, sint32 idx, sint32 *src);
sint32 MojiTaskExec(sint32 arg0, uint8 *script, sint32 arg2);
void Sound_call(sint32 id, sint32 a1, sint32 a2);
void func_80043340(sint32 id, sint32 arg1);

#endif // STCOM29_H
