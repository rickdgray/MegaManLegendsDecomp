#ifndef ST1E_H
#define ST1E_H

#include "common.h"
#include "stage_common/stage.h"

extern STAGE_SLOT_FUNC *D_80103DC8[];
extern STAGE_SLOT_FUNC *D_80103F3C[];
extern STAGE_SLOT_FUNC D_80103F58[];
extern STAGE_SLOT_FUNC D_8010403C[];
extern STAGE_SLOT_FUNC D_801040C8[];
extern STAGE_SLOT_FUNC D_801040E4[];
extern STAGE_ROOM2_FUNC *D_8010440C[];
extern STAGE_OBJ_FUNC D_80104A24[];
void func_80101AF0(STAGE_OBJ *wp);
void func_80101C0C(STAGE_OBJ *wp);
extern STAGE_MOUTH *D_801098E8[];
extern STAGE_MOUTH *D_801098E8_S __asm__("D_801098E8");
extern sint16 D_801098EC[];
extern STAGE_MOUTH *D_801098F0[];
extern STAGE_MOUTH *D_801098F0_S __asm__("D_801098F0");
extern sint16 D_801098F4[];
extern STAGE_OBJ_FUNC D_80104E1C[];
void func_8010200C(STAGE_OBJ *wp);
void func_80102134(STAGE_OBJ *wp);
extern STAGE_MOUTH *D_80109900[];
// The lip-sync script pointers also read and written as scalars (the same symbols): retail
// reaches them by lui/%lo there, and through their address only for the jump back (+=).
extern STAGE_MOUTH *D_80109900_S __asm__("D_80109900");
extern sint16 D_80109904[];
extern STAGE_MOUTH *D_80109908[];
extern STAGE_MOUTH *D_80109908_S __asm__("D_80109908");
extern sint16 D_8010990C[];
extern STAGE_OBJ_FUNC D_801052D4[];
void func_80102818(STAGE_OBJ *wp);
void func_80102940(STAGE_OBJ *wp);
extern STAGE_OBJ_FUNC D_801058DC[];

// A sign panel: a matrix and a sprite position (func_80102ED8).
typedef struct
{
    uint8 be_flag;         // 00
    uint8 slot;            // 01
    uint8 reserved02;      // 02
    uint8 type;            // 03
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 reserved09[0xF]; // 09
    STAGE_MATRIX matrix;   // 18
    STCOM_SVECTOR pos_38;  // 38
    sint32 color_40;       // 40
} ST1E_PANEL;

// The scrolling text's position: frames, the top line and frames that line has held.
typedef struct
{
    sint32 frame; // 0
    sint16 line;  // 4
    sint16 count; // 6
} ST1E_SCROLL_POS;

// The scrolling text (func_80102FD8).
typedef struct
{
    uint8 be_flag;          // 00
    uint8 slot;             // 01
    uint8 reserved02[6];    // 02
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint8 value_C;          // 0C
    sint8 value_D;          // 0D
    sint8 value_E;          // 0E
    sint8 value_F;          // 0F
    uint8 reserved10[0x18]; // 10
    ST1E_SCROLL_POS pos;    // 28
} ST1E_SCROLL;

// A line of the scrolling text: three glyphs (one per column), then the frames of 18 lines it
// holds before the next line comes in (D_8010563C).
typedef struct
{
    uint8 ch[3]; // 0
    uint8 hold;  // 3
} ST1E_LINE;

extern ST1E_LINE D_8010563C[];

extern STAGE_LIP_CUES D_801098F8;
extern STAGE_LIP_CUES D_80109910;
extern STAGE_MOUTH *D_80104C54[];
extern STAGE_MOUTH *D_80104CA8[];
extern STAGE_MOUTH *D_80105098[];
extern STAGE_MOUTH *D_801050EC[];
extern STAGE_MOUTH_CUE D_80104CFC[];
extern STAGE_MOUTH_CUE D_80104D8C[];
extern STAGE_MOUTH_CUE D_80105164[];
extern STAGE_MOUTH_CUE D_801051E8[];
extern STAGE_OBJ_FUNC D_80104A38[]; // routine_1 handlers (func_80101E3C)
extern STAGE_OBJ_FUNC D_80104A4C[]; // routine_0 handlers (func_80101EC4)
extern uint8 D_8010444C[];
extern STAGE_SCRIPT_ENTRY D_8010487C[];
extern uint8 D_8010496C[];
extern STAGE_XYZ D_801052EC[];

// A texture animation step: frame `frame` held `count` frames.
typedef struct
{
    uint8 frame;
    uint8 count;
} ST1E_ANIM;

typedef void (*ST1E_EV_FUNC)(STAGE_EV *wp);

// A font glyph: its texture rectangle (func_8010320C).
typedef struct
{
    uint8 u0;
    uint8 v0;
    uint8 u1;
    uint8 tpage;
} ST1E_GLYPH;

extern ST1E_GLYPH D_80105330[];

extern uint32 D_80105BB8[]; // texture keys (func_80103760)
extern ST1E_ANIM D_80105BE0[];
extern ST1E_ANIM D_80105BFC[];
extern ST1E_ANIM D_80105C08[];
extern ST1E_ANIM D_80105C1C[];
extern ST1E_EV_FUNC D_80105C34[]; // by type (func_80103D3C)

void func_8010033C(uint8 mode);
void func_80101078(STAGE_ROOM *wp);
void func_80101118(STAGE_ROOM *wp);
void func_80101E3C(STAGE_OBJ *wp);
void func_8010227C(STAGE_OBJ *wp);
void func_80102698(STAGE_OBJ *wp);
void func_80102A88(STAGE_OBJ *wp);
void func_80102D70(STAGE_OBJ *wp);
void func_80102E4C(ST1E_PANEL *wp);

extern void *D_80104190[];       // model table by room
extern void *D_80104238[];       // spawn list by room
extern void *D_8010426C[];       // exit list by room
extern uint8 D_80104288[][0x28]; // by room (func_800371A0)
extern uint8 D_801043A0[][8];    // by D_801043B8[room]
extern sint32 D_801043B8[];
void func_8010028C(void);

#endif // ST1E_H
