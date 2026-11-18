#!/usr/bin/env python3
"""Rewrite inline MIPS assembly in a preprocessed game C file for the native port.

Usage: asm_rewrite.py <in.i> <out.i>

Every statement `__asm__ volatile("template" : outputs : inputs : clobbers);` becomes a block
that hands the template and the operand values to the runtime's MIPS interpreter
(port/runtime/mips_asm.c), then copies register outputs back. Asm labels on declarations
(`extern T x __asm__("sym");`) are left alone: they are portable symbol aliases.

The rewrite keeps every statement on its original line, so the `# line` markers in the
preprocessed file still point compiler diagnostics at the real source.
"""

import re
import sys

PRELUDE = (
    "typedef struct { const char *text; const char *where; int count; void *insns; } "
    "PORT_ASM_PROG; void port_asm_run(PORT_ASM_PROG *, unsigned int *);\n"
)

LINE_MARK = re.compile(r'^# (\d+) "([^"]*)"')


def skip_string(src, i):
    """i is at an opening quote; return the index after the closing quote."""
    q = src[i]
    i += 1
    while src[i] != q:
        i += 2 if src[i] == "\\" else 1
    return i + 1


def match_paren(src, i):
    """i is at '('; return the index of the matching ')'."""
    depth = 0
    while True:
        c = src[i]
        if c in "\"'":
            i = skip_string(src, i)
            continue
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return i
        i += 1


def split_top(text, sep):
    """Split at sep characters outside parentheses and string literals."""
    parts, depth, start, i = [], 0, 0, 0
    while i < len(text):
        c = text[i]
        if c in "\"'":
            i = skip_string(text, i)
            continue
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif c == sep and depth == 0:
            parts.append(text[start:i])
            start = i + 1
        i += 1
    parts.append(text[start:])
    return parts


def unescape(body):
    return body.encode("latin-1").decode("unicode_escape")


def concat_strings(text):
    """Concatenate adjacent string literals ("a" "b") into one Python string."""
    out = []
    for m in re.finditer(r'"((?:[^"\\]|\\.)*)"', text):
        out.append(unescape(m.group(1)))
    leftover = re.sub(r'"((?:[^"\\]|\\.)*)"', "", text).strip()
    if leftover:
        raise ValueError("unexpected text in asm template: " + leftover)
    return "".join(out)


def parse_operands(text):
    ops = []
    for item in split_top(text, ","):
        item = item.strip()
        if not item:
            continue
        m = re.match(r'^((?:"[^"]*"\s*)+)\((.*)\)$', item, re.S)
        if not m:
            raise ValueError("cannot parse asm operand: " + item)
        ops.append((concat_strings(m.group(1)), m.group(2).strip()))
    return ops


def c_string(s):
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n") + '"'


def rewrite_stmt(template, outputs, inputs, where):
    if template.strip() == "":
        return ";"  # an empty asm is only a scheduling barrier
    operands = outputs + inputs
    n = max(1, len(operands))
    code = [
        "{ static PORT_ASM_PROG port_asm_prog = { %s, %s, -1, 0 }; unsigned int port_asm_ops[%d];"
        % (c_string(template), c_string(where), n)
    ]
    for k, (constraint, expr) in enumerate(operands):
        if "m" in constraint:
            code.append(" port_asm_ops[%d] = (unsigned int)&(%s);" % (k, expr))
        elif k >= len(outputs) or "+" in constraint:
            code.append(" port_asm_ops[%d] = (unsigned int)(%s);" % (k, expr))
    code.append(" port_asm_run(&port_asm_prog, port_asm_ops);")
    for k, (constraint, expr) in enumerate(outputs):
        if "m" not in constraint:
            code.append(" (%s) = (__typeof__(%s))port_asm_ops[%d];" % (expr, expr, k))
    code.append(" }")
    return "".join(code)


def current_location(src, pos, marks):
    """file:line of position pos, from the preprocessor's line markers."""
    line_no, fname = 1, "?"
    for mpos, mline, mfile in marks:
        if mpos > pos:
            break
        line_no, fname, base = mline, mfile, mpos
    else:
        base = marks[-1][0] if marks else 0
    if marks and marks[0][0] <= pos:
        # count newlines after the marker line
        nl_after = src.count("\n", base, pos)
        line_no += nl_after - 1
    return "%s:%d" % (fname, line_no)


def main():
    src = open(sys.argv[1], encoding="latin-1").read()
    marks = []
    offset = 0
    for line in src.splitlines(keepends=True):
        m = LINE_MARK.match(line)
        if m:
            marks.append((offset, int(m.group(1)), m.group(2)))
        offset += len(line)

    out = []
    i = 0
    count = 0
    # Every asm statement; a plain `__asm__(...)` is also an asm label on a declaration, which is
    # kept unless its template is a maspsx directive (matching-build layout only).
    asm_re = re.compile(r"\b__asm__\s*(volatile\b|__volatile__\b)?\s*\(")
    while True:
        m = asm_re.search(src, i)
        if not m:
            out.append(src[i:])
            break
        start = m.start()
        open_paren = m.end() - 1
        close = match_paren(src, open_paren)
        body = src[open_paren + 1 : close]
        parts = split_top(body, ":")
        template = concat_strings(parts[0])
        if not m.group(1) and "maspsx-keep" not in template:
            out.append(src[i : close + 1])  # an asm label or a basic asm: kept
            i = close + 1
            continue
        end = close + 1
        while src[end] in " \t\n":
            end += 1
        if src[end] != ";":
            raise SystemExit("asm_rewrite: asm statement without ';' at %d" % start)
        if "maspsx-keep" in template:
            # .rodata/.text padding for the matching build (st17.h's ST17_RODATA_PAD): nothing
            # natively
            out.append(src[i:start])
            out.append(";" + "\n" * src.count("\n", start, end + 1))
            i = end + 1
            continue
        outputs = parse_operands(parts[1]) if len(parts) > 1 else []
        inputs = parse_operands(parts[2]) if len(parts) > 2 else []
        where = current_location(src, start, marks)
        replacement = rewrite_stmt(template, outputs, inputs, where)
        # keep line structure: preserve any newlines the original statement spanned
        replacement += "\n" * src.count("\n", start, end + 1)
        out.append(src[i:start])
        out.append(replacement)
        i = end + 1
        count += 1

    with open(sys.argv[2], "w", encoding="latin-1") as f:
        f.write(PRELUDE)
        f.write("# 1 \"%s\"\n" % (marks[0][2] if marks else sys.argv[1]))
        f.write("".join(out))


if __name__ == "__main__":
    main()
