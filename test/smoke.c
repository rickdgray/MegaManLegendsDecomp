// Smoke test for the local toolchain: Cmd_set_movie, matched on decomp.me (PSYQ4.0).

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

extern CMD *Cmd_write_ptr;

void Cmd_set_movie(int arg1, int arg2, short arg3)
{
    Cmd_write_ptr->type = 5;
    Cmd_write_ptr->args.arg1 = arg1;
    Cmd_write_ptr->args.arg2 = arg2;
    Cmd_write_ptr->args.arg3 = arg3;
    Cmd_write_ptr++;
}
