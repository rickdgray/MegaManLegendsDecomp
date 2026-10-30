#ifndef CMD_H
#define CMD_H

#include "common.h"
#include "psyq/libcd.h"

// Arguments are copied as one 12-byte block; possibly a union per command type.
typedef struct
{
    int arg1;
    int arg2;
    short arg3;
} CMD_ARGS;

typedef struct
{
    int type; // 0 = end of queue, 5 = play movie
    CMD_ARGS args;
} CMD;

extern CMD Cmd_queue[16];
extern CMD *Cmd_write_ptr;

extern int D_80059C20;
extern int D_80059C24;

extern int D_80059BB4;
extern u8 D_80059BC8;
extern u8 D_80059BC9;
extern u8 D_80059BCA;
extern u8 Cd_mode;
extern u8 D_80059BD4;
extern u8 D_80059BDC;
extern int D_80059BD8;
extern int D_80059C00;
extern CMD *g_cmdHead;
extern u_char Cd_result[8];
extern u8 D_80059C48;
extern u8 D_80059C74;

extern void (*g_cmdHandlers[6])(void);

void Cd_init(void);
void Cd_control_retry(u_char com, u_char *param, u_char *result);
void Cmd_set_movie(int arg1, int arg2, short arg3);
void Cmd_dequeue(void);
int Cmd_busy_check(void);

#endif // CMD_H
