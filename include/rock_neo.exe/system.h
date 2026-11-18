#ifndef SYSTEM_H
#define SYSTEM_H

#include "common.h"
#include "thread.h"

#define SYSTEM_EVENT_CLASS 0xF0000010

typedef void (*SYSTEM_STATE_FUNC)(sint8 *state);

extern THREAD_FUNC D_80098158;
extern sint32 D_800979D8;
extern long D_800988D8;
extern sint8 D_80098B1C;
extern sint8 D_80098B1D;
extern SYSTEM_STATE_FUNC D_80080894[];

long func_8001246C(void);

void Thread_wait(sint32 arg);
void func_80012E10(sint32 index, THREAD_FUNC entry);
void func_80012F78(THREAD_FUNC entry);
void func_80053788(void);

#endif // SYSTEM_H
