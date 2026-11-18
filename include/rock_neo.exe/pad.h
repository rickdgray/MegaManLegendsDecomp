#ifndef ROCK_PAD_H
#define ROCK_PAD_H

#include "common.h"
#include "display.h"

#define PAD_UP           0x0010
#define PAD_RIGHT        0x0020
#define PAD_DOWN         0x0040
#define PAD_LEFT         0x0080
#define PAD_L1           0x0400
#define PAD_R1           0x0800
#define PAD_REPEAT_DELAY 6

typedef struct
{
    uint8 status;
    uint8 id;
    uint16 buttons;
    uint32 analog;
    uint8 unk08[0x1C];
    uint8 type;
    uint8 flags;
    uint16 held;
    uint16 previous;
    uint16 pressed;
    uint16 released;
    uint16 repeat;
    uint32 analog_copy;
    uint8 unk34[2];
    uint8 unk36;
    uint8 unk37;
    uint8 repeat_state[8];
    uint8 repeat_count[8];
    DISP_ENV disp_env[2];
} PAD_WORK;

extern PAD_WORK Joy1;
extern PAD_WORK Joy2;
extern uint16 D_800C0D8E[];
extern uint16 D_800C0C26;

void Pad_update(PAD_WORK *pad);
void Pad_update_all(void);
void func_800122D0(PAD_WORK *pad);
void func_80012350(PAD_WORK *pad, sint32 mask, sint32 index);

#endif // ROCK_PAD_H
