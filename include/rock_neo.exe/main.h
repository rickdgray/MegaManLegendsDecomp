#ifndef ROCK_MAIN_H
#define ROCK_MAIN_H

#include "common.h"
#include "display.h"
#include "code_8001786c.h"
#include "debug.h"
#include "kernel.h"

#define SCRATCH_BUFFER_INDEX (*(uint8 *)0x1F800000)
#define SCRATCH_VSYNC_WAIT   (*(uint8 *)0x1F800001)
#define SCRATCH_FRAME_COUNT  (*(uint16 *)0x1F800002)
#define SCRATCH_PRIM_PTR     (*(uint32 **)0x1F80003C)
#define SCRATCH_SCREEN_WORD  (*(uint32 *)0x1F800070)

#define THREAD_RUNNING 0x7F

// Exception screen: register slots of the BIOS thread control block
#define TCB_R_EPC   32
#define TCB_R_MDHI  33
#define TCB_R_MDLO  34
#define TCB_R_SR    35
#define TCB_R_CAUSE 36
#define EXC_BREAK   9

// Text position for func_8001FE38: x in 8-pixel columns, y in rows, colour
#define DEBUG_TEXT_POS(x, y, c) (((x) << 3) | ((y) << 12) | ((c) << 17))

// The current display buffer, D_80098934, seen as a whole DISP_ENV.
#define CURRENT_DISP_ENV ((DISP_ENV *)D_80098934)

// BIOS thread control block (0xC0 bytes)
typedef struct
{
    sint32 status;
    sint32 mode;
    uint32 reg[40];
    sint32 system[6];
} TCB;

// BIOS process table entry; its first word points to the running thread's TCB
typedef struct
{
    TCB *entry;
    sint32 flag;
} TCBH;

// Table of tables entry 1 (0x108): the process table
#define BIOS_PROCESS_TABLE (*(TCBH **)KERNEL_ADDR(0x108))

// Exception screen label: position and colour, then the text
typedef struct
{
    uint8 x;
    uint8 y;
    uint8 color;
    uint8 reserved3;
    char *text;
} DEBUG_TEXT;

extern uint8 D_80098A8C;
extern volatile sint32 D_80098A90;
extern sint32 D_800D9B00;
extern sint32 D_800D9BCC;
extern sint32 D_800D9BD0;
extern u_long D_8009BF88[][0x200];
extern u_long D_8009AE48[][0x200];
extern uint32 D_800806EC[][2];
extern uint8 D_800C0FC0[];
extern DISP_ENV D_800C0C48[2];
extern sint16 D_800BAEB0[];
extern sint16 D_800BBCF8[];
extern DEBUG_TEXT D_80080730[];
extern DEBUG_TEXT D_80080858[];
extern char D_800979A4[];
extern char D_8009787C[], D_80097880[], D_80097884[], D_8009788C[];
extern char D_80097894[], D_8009789C[], D_800978A4[], D_800978A8[];
extern char D_800978AC[], D_800978B0[], D_800978B4[], D_800978B8[];
extern char D_800978BC[], D_800978C0[], D_800978C4[], D_800978C8[];

void __main(void);
void StopCallback(void);
void Cd_init(void);
void func_80012938(void);
void func_80012988(uint32 *value);
void func_80012A5C(DEBUG_MEMORY_ROW *rows, uint32 mode);
void func_80020A40(void);
void func_80011F04(void);
void func_800131FC(void);
void func_80012BC4(void);
void func_80012C80(void);
void func_800120A8(void);
void func_80017734(void);
void func_800178FC(void);
void func_80017B24(void);
void func_8001A110(void);
void func_8001C95C(void);
void func_800203A8(void);
void func_80053B40(void);
void func_80064060(void);
void func_80077748(sint32 mode);
void InitGeom(void);
void func_8007B118(sint32 x, sint32 y);
void func_8007B138(sint32 h);
void func_8006479C(void);
void func_80019DE0(void);
void func_8002037C(void);
void func_800177CC(void *start, void *end);
sint32 rcos(sint32 angle);
sint32 rsin(sint32 angle);

#endif // ROCK_MAIN_H
