// Inline-MIPS interpreter. See mips_asm.h.
#include "mips_asm.h"

#include "gte.h"
#include "psx_mem.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    OP_NOP,
    OP_LW,
    OP_LH,
    OP_LHU,
    OP_LB,
    OP_LBU,
    OP_SW,
    OP_SH,
    OP_SB,
    OP_SRA,
    OP_SLL,
    OP_SRL,
    OP_ADDU,
    OP_SUBU,
    OP_ADDIU,
    OP_MOVE,
    OP_MTC2,
    OP_MFC2,
    OP_CTC2,
    OP_CFC2,
    OP_LWC2,
    OP_SWC2,
    OP_RTPS,
    OP_RTPT,
    OP_NCLIP,
    OP_AVSZ3,
    OP_AVSZ4,
    OP_DPCS,
    OP_MVMVA,
    OP_BREAK,
};

// Register operands: 0..31 are the scratch GPR file, PORT_OPND + n is GCC operand %n.
#define PORT_OPND 32

struct PORT_ASM_INSN
{
    int op;
    int a, b, c; // registers (GPR/operand), or COP2 register numbers, per op
    int32_t imm; // offset or shift amount
    GTE_OP gte;  // fields of a GTE command
};

static const struct
{
    const char *name;
    int op;
} mnemonics[] = {
    {"nop", OP_NOP},     {"lw", OP_LW},       {"lh", OP_LH},       {"lhu", OP_LHU},
    {"lb", OP_LB},       {"lbu", OP_LBU},     {"sw", OP_SW},       {"sh", OP_SH},
    {"sb", OP_SB},       {"sra", OP_SRA},     {"sll", OP_SLL},     {"srl", OP_SRL},
    {"addu", OP_ADDU},   {"subu", OP_SUBU},   {"addiu", OP_ADDIU}, {"move", OP_MOVE},
    {"mtc2", OP_MTC2},   {"mfc2", OP_MFC2},   {"ctc2", OP_CTC2},   {"cfc2", OP_CFC2},
    {"lwc2", OP_LWC2},   {"swc2", OP_SWC2},   {"rtps", OP_RTPS},   {"rtpt", OP_RTPT},
    {"nclip", OP_NCLIP}, {"avsz3", OP_AVSZ3}, {"avsz4", OP_AVSZ4}, {"dpcs", OP_DPCS},
    {"mvmva", OP_MVMVA}, {"break", OP_BREAK},
};

static void fail(const PORT_ASM_PROG *prog, const char *why, const char *at)
{
    fprintf(stderr, "port_asm: %s at \"%s\" in \"%s\" (%s)\n", why, at, prog->text,
            prog->where ? prog->where : "?");
    abort();
}

static const char *skip_ws(const char *s)
{
    while (*s == ' ' || *s == '\t')
    {
        s++;
    }
    return s;
}

static int32_t parse_int(const PORT_ASM_PROG *prog, const char **sp)
{
    const char *s = skip_ws(*sp);
    char *end;
    long v = strtol(s, &end, 0);

    if (end == s)
    {
        fail(prog, "number expected", s);
    }
    *sp = end;
    return (int32_t)v;
}

// "$n" (GPR or coprocessor register number) or "%n" (operand).
static int parse_reg(const PORT_ASM_PROG *prog, const char **sp)
{
    const char *s = skip_ws(*sp);
    int base;

    if (*s == '$')
    {
        base = 0;
    }
    else if (*s == '%')
    {
        base = PORT_OPND;
    }
    else
    {
        fail(prog, "register expected", s);
        return 0;
    }
    s++;
    *sp = s;
    return base + parse_int(prog, sp);
}

// "off(reg)" or a bare "%n" memory operand (its address is the operand's value).
static void parse_mem(const PORT_ASM_PROG *prog, const char **sp, int *reg, int32_t *off)
{
    const char *s = skip_ws(*sp);

    if (*s == '%')
    {
        *off = 0;
        *reg = parse_reg(prog, &s);
        *sp  = s;
        return;
    }
    *off = (*s == '(') ? 0 : parse_int(prog, &s);
    s    = skip_ws(s);
    if (*s != '(')
    {
        fail(prog, "'(' expected", s);
    }
    s++;
    *reg = parse_reg(prog, &s);
    s    = skip_ws(s);
    if (*s != ')')
    {
        fail(prog, "')' expected", s);
    }
    *sp = s + 1;
}

static void expect_comma(const PORT_ASM_PROG *prog, const char **sp)
{
    const char *s = skip_ws(*sp);

    if (*s != ',')
    {
        fail(prog, "',' expected", s);
    }
    *sp = s + 1;
}

static void parse(PORT_ASM_PROG *prog)
{
    const char *s = prog->text;
    PORT_ASM_INSN *out;
    int cap = 8, n = 0;
    size_t i;

    out = malloc(sizeof(*out) * (size_t)cap);
    while (*s)
    {
        char name[16];
        int len = 0;
        PORT_ASM_INSN in;

        s = skip_ws(s);
        if (*s == ';' || *s == '\n')
        {
            s++;
            continue;
        }
        if (*s == '\0')
        {
            break;
        }
        while (isalnum((unsigned char)*s) && len < 15)
        {
            name[len++] = *s++;
        }
        name[len] = '\0';
        memset(&in, 0, sizeof(in));
        in.op = -1;
        for (i = 0; i < sizeof(mnemonics) / sizeof(mnemonics[0]); i++)
        {
            if (strcmp(mnemonics[i].name, name) == 0)
            {
                in.op = mnemonics[i].op;
            }
        }
        in.gte.sf = 1;
        switch (in.op)
        {
            case OP_NOP:
            case OP_RTPS:
            case OP_RTPT:
            case OP_AVSZ3:
            case OP_AVSZ4:
            case OP_DPCS:
                break;
            case OP_NCLIP:
                in.gte.sf = 0;
                break;
            case OP_LW:
            case OP_LH:
            case OP_LHU:
            case OP_LB:
            case OP_LBU:
            case OP_SW:
            case OP_SH:
            case OP_SB:
                in.a = parse_reg(prog, &s);
                expect_comma(prog, &s);
                parse_mem(prog, &s, &in.b, &in.imm);
                break;
            case OP_LWC2:
            case OP_SWC2:
                in.a = parse_reg(prog, &s); // COP2 data register number
                expect_comma(prog, &s);
                parse_mem(prog, &s, &in.b, &in.imm);
                break;
            case OP_SRA:
            case OP_SLL:
            case OP_SRL:
            case OP_ADDIU:
                in.a = parse_reg(prog, &s);
                expect_comma(prog, &s);
                in.b = parse_reg(prog, &s);
                expect_comma(prog, &s);
                in.imm = parse_int(prog, &s);
                break;
            case OP_ADDU:
            case OP_SUBU:
                in.a = parse_reg(prog, &s);
                expect_comma(prog, &s);
                in.b = parse_reg(prog, &s);
                expect_comma(prog, &s);
                in.c = parse_reg(prog, &s);
                break;
            case OP_MOVE:
            case OP_MTC2:
            case OP_MFC2:
            case OP_CTC2:
            case OP_CFC2:
                in.a = parse_reg(prog, &s);
                expect_comma(prog, &s);
                in.b = parse_reg(prog, &s); // COP2 register number for the c2 moves
                break;
            case OP_MVMVA:
                in.gte.sf = parse_int(prog, &s);
                expect_comma(prog, &s);
                in.gte.mx = parse_int(prog, &s);
                expect_comma(prog, &s);
                in.gte.v = parse_int(prog, &s);
                expect_comma(prog, &s);
                in.gte.cv = parse_int(prog, &s);
                expect_comma(prog, &s);
                in.gte.lm = parse_int(prog, &s);
                break;
            case OP_BREAK:
                in.imm = parse_int(prog, &s);
                break;
            default:
                fail(prog, "unsupported instruction", name);
        }
        if (n == cap)
        {
            cap *= 2;
            out = realloc(out, sizeof(*out) * (size_t)cap);
        }
        out[n++] = in;
    }
    prog->insns = out;
    prog->count = n;
}

void port_asm_break(uint32_t code, const char *where)
{
    fprintf(stderr, "port_asm: break 0x%X reached (%s)\n", code, where ? where : "?");
    abort();
}

// A load or store at a KUSEG address below 64 KB (a null record pointer plus a field offset)
// reaches the kernel's RAM on the console. The process can't map that range (vm.mmap_min_addr),
// so it goes to the same RAM through its KSEG0 view, as overlay.c's fault handler does for
// native code. Without this an `lwc2` through a null pointer crashed (func_80027BE0's mesh).
#define MEM_ADDR(addr) ((uint32_t)(addr) < PSX_KUSEG_MIRROR ? PSX_RAM_BASE | (uint32_t)(addr) : (uint32_t)(addr))
#define MEM(type, addr) (*(type *)(uintptr_t)MEM_ADDR(addr))

void port_asm_run(PORT_ASM_PROG *prog, uint32_t *ops)
{
    uint32_t gpr[PORT_OPND];
    int i;

    if (prog->count < 0 || prog->insns == NULL)
    {
        parse(prog);
    }
    memset(gpr, 0, sizeof(gpr));

#define R(r) (*((r) >= PORT_OPND ? &ops[(r) - PORT_OPND] : &gpr[(r)]))
    for (i = 0; i < prog->count; i++)
    {
        const PORT_ASM_INSN *in = &prog->insns[i];
        uint32_t ea             = R(in->b) + (uint32_t)in->imm;

        switch (in->op)
        {
            case OP_NOP:
                break;
            case OP_LW:
                R(in->a) = MEM(uint32_t, ea);
                break;
            case OP_LH:
                R(in->a) = (uint32_t)(int32_t)MEM(int16_t, ea);
                break;
            case OP_LHU:
                R(in->a) = MEM(uint16_t, ea);
                break;
            case OP_LB:
                R(in->a) = (uint32_t)(int32_t)MEM(int8_t, ea);
                break;
            case OP_LBU:
                R(in->a) = MEM(uint8_t, ea);
                break;
            case OP_SW:
                MEM(uint32_t, ea) = R(in->a);
                break;
            case OP_SH:
                MEM(uint16_t, ea) = (uint16_t)R(in->a);
                break;
            case OP_SB:
                MEM(uint8_t, ea) = (uint8_t)R(in->a);
                break;
            case OP_SRA:
                R(in->a) = (uint32_t)((int32_t)R(in->b) >> (in->imm & 31));
                break;
            case OP_SLL:
                R(in->a) = R(in->b) << (in->imm & 31);
                break;
            case OP_SRL:
                R(in->a) = R(in->b) >> (in->imm & 31);
                break;
            case OP_ADDU:
                R(in->a) = R(in->b) + R(in->c);
                break;
            case OP_SUBU:
                R(in->a) = R(in->b) - R(in->c);
                break;
            case OP_ADDIU:
                R(in->a) = R(in->b) + (uint32_t)in->imm;
                break;
            case OP_MOVE:
                R(in->a) = R(in->b);
                break;
            case OP_MTC2:
                gte_write_data(in->b & 31, R(in->a));
                break;
            case OP_MFC2:
                R(in->a) = gte_read_data(in->b & 31);
                break;
            case OP_CTC2:
                gte_write_ctrl(in->b & 31, R(in->a));
                break;
            case OP_CFC2:
                R(in->a) = gte_read_ctrl(in->b & 31);
                break;
            case OP_LWC2:
                gte_write_data(in->a & 31, MEM(uint32_t, ea));
                break;
            case OP_SWC2:
                MEM(uint32_t, ea) = gte_read_data(in->a & 31);
                break;
            case OP_RTPS:
                gte_rtps(&in->gte);
                break;
            case OP_RTPT:
                gte_rtpt(&in->gte);
                break;
            case OP_NCLIP:
                gte_nclip();
                break;
            case OP_AVSZ3:
                gte_avsz3();
                break;
            case OP_AVSZ4:
                gte_avsz4();
                break;
            case OP_DPCS:
                gte_dpcs(&in->gte);
                break;
            case OP_MVMVA:
                gte_mvmva(&in->gte);
                break;
            case OP_BREAK:
                port_asm_break((uint32_t)in->imm, prog->where);
                break;
        }
    }
#undef R
}
