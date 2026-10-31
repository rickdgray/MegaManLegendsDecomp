#ifndef CMD_H
#define CMD_H

#include "common.h"
#include "psyq/libcd.h"

// Arguments are copied as one 12-byte block; possibly a union per command type.
typedef struct
{
    sint32 arg1;
    sint32 arg2;
    sint16 arg3;
} CMD_ARGS;

typedef struct
{
    sint32 type; // 0 = end of queue, 5 = play movie
    CMD_ARGS args;
} CMD;

extern CMD Cmd_queue[16];
extern CMD *Cmd_write_ptr;

extern sint32 D_80059C20;
extern sint32 D_80059C24;

extern sint32 D_80059BB4;
extern uint8 D_80059BC8;
extern uint8 D_80059BC9;
extern uint8 D_80059BCA;
extern uint8 Cd_mode;
extern uint8 D_80059BD4;
extern uint8 D_80059BDC;
extern sint32 D_80059BD8;
extern sint32 D_80059C00;
extern CMD *Cmd_exec_ptr;
extern u_char Cd_result[8];
extern uint8 D_80059C48;
extern uint8 D_80059C74;

typedef void (*CMD_FUNC)(void);

extern CMD_FUNC cmd_tbl[6];

void Cd_init(void);
void Cd_control_retry(u_char com, u_char *param, u_char *result);
void Cmd_set_movie(sint32 arg1, sint32 arg2, sint16 arg3);
void func_80011680(void);
void Cmd_exec(void);
void Cmd_dequeue(void);
sint32 Cmd_busy_check(void);

#endif // CMD_H
