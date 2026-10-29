#ifndef CMD_H
#define CMD_H

#include "common.h"

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

extern Command  g_cmdQueue[16];             /* 0x8005b348 */
extern Command *g_cmdWritePtr;              /* 0x80059c08 */

/* Per-command progress, cleared on dequeue. Rename once identified. */
extern int D_80059C20;
extern int D_80059C24;

void InitCd(void);
void QueuePlayMovie(int arg1, int arg2, short arg3);
void DequeueCommand(void);
int  IsBusy(void);

#endif /* CMD_H */