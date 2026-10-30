#ifndef CMD_H
#define CMD_H

#include "common.h"
#include "psyq/libcd.h"

/* Arguments are copied as one 12-byte block; possibly a union per command type. */
typedef struct {
    int   arg1;
    int   arg2;
    short arg3;
} CommandArgs;                              /* 0x0c */

typedef struct {
    int         type;                       /* 0 = end of queue, 5 = play movie */
    CommandArgs args;
} Command;                                  /* 0x10 */

extern Command  g_cmdQueue[16];
extern Command *g_cmdWritePtr;

/* Per-command progress, cleared on dequeue. Rename once identified. */
extern int D_80059C20;
extern int D_80059C24;

/* CD state set up by InitCd. Unidentified; widths are from the stores. */
extern int      D_80059BB4;
extern u8       D_80059BC8;
extern u8       D_80059BC9;
extern u8       D_80059BCA;
extern u8       g_cdMode;
extern u8       D_80059BD4;
extern u8       D_80059BDC;
extern int      D_80059BD8;
extern int      D_80059C00;
extern Command *g_cmdHead;
extern u_char   g_cdResult[8];
extern u8       D_80059C48;
extern u8       D_80059C74;

extern void   (*g_cmdHandlers[6])(void);

void InitCd(void);
void Cd_ControlRetry(u_char com, u_char *param, u_char *result);
void QueuePlayMovie(int arg1, int arg2, short arg3);
void DequeueCommand(void);
int  IsBusy(void);

#endif /* CMD_H */