/* Smoke test for the local toolchain: QueuePlayMovie, matched on decomp.me (PSYQ4.0). */

typedef struct {
    int   arg1;
    int   arg2;
    short arg3;
} CommandArgs;

typedef struct {
    int         type;
    CommandArgs args;
} Command;

extern Command *g_cmdWritePtr;

void QueuePlayMovie(int arg1, int arg2, short arg3) {
    g_cmdWritePtr->type = 5;
    g_cmdWritePtr->args.arg1 = arg1;
    g_cmdWritePtr->args.arg2 = arg2;
    g_cmdWritePtr->args.arg3 = arg3;
    g_cmdWritePtr++;
}