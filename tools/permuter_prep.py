#!/usr/bin/env python3
"""Prepare a decomp-permuter directory for a parked function.

Usage:  tools/permuter_prep.py FunctionName [--src src/main.c]

The function must be parked in the source like this:

    #ifdef NON_MATCHING
    <best attempt>
    #else
    INCLUDE_ASM("asm/nonmatchings/main", FunctionName);
    #endif

Creates permuter/<FunctionName>/ with base.c, target.s, target.o, compile.sh and
settings.toml, then run:

    .venv/bin/python tools/vendor/decomp-permuter/permuter.py permuter/<FunctionName> -j 8
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
INCLUDE = ROOT / "include"

AS = [
    "mips-linux-gnu-as", "-EL", "-march=r3000", "-mtune=r3000",
    "-no-pad-sections", "-G0", f"-I{INCLUDE}",
]

# One parked block: the draft, then the INCLUDE_ASM fallback naming the function.
BLOCK = re.compile(
    r"#ifdef NON_MATCHING\n(.*?)#else\s*\n"
    r'INCLUDE_ASM\("([^"]+)",\s*(\w+)\);\s*\n#endif',
    re.S,
)

ASM_PRELUDE = '.include "macro.inc"\n.set noat\n.set noreorder\n.section .text\n\n'


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("function")
    ap.add_argument("--src", default="src/main.c", help="C file containing the parked function")
    args = ap.parse_args()
    fn = args.function

    src_path = ROOT / args.src
    text = src_path.read_text()

    for m in BLOCK.finditer(text):
        if m.group(3) == fn:
            body, asm_dir = m.group(1), m.group(2)
            break
    else:
        sys.exit(f"{fn}: no '#ifdef NON_MATCHING ... INCLUDE_ASM(..., {fn}) ... #endif' block in {args.src}")

    out = ROOT / "permuter" / fn
    out.mkdir(parents=True, exist_ok=True)

    # base.c: the source file's includes plus the draft, fully preprocessed.
    # PERMUTER makes include_asm.h define INCLUDE_ASM as nothing.
    includes = [line for line in text.splitlines() if line.startswith("#include")]
    raw = "\n".join(includes) + "\n\n" + body
    pre = subprocess.run(
        ["cpp", "-P", "-undef", "-nostdinc", f"-I{INCLUDE}", "-DPERMUTER", "-DNON_MATCHING", "-"],
        input=raw, text=True, capture_output=True,
    )
    if pre.returncode != 0:
        sys.exit(f"cpp failed:\n{pre.stderr}")
    (out / "base.c").write_text(pre.stdout)

    # target.s / target.o: the original assembly, assembled with the build's flags.
    asm_path = ROOT / asm_dir / f"{fn}.s"
    if not asm_path.exists():
        sys.exit(f"{asm_path} not found (run tools/split.sh?)")
    (out / "target.s").write_text(ASM_PRELUDE + asm_path.read_text())
    subprocess.run(AS + ["-o", str(out / "target.o"), str(out / "target.s")], check=True)

    # compile.sh: the permuter calls it as  compile.sh <input.c> -o <output.o>
    compile_sh = out / "compile.sh"
    compile_sh.write_text(
        "#!/usr/bin/env bash\n"
        "# Invoked by the permuter as: compile.sh <input.c> -o <output.o>\n"
        f'exec "{ROOT}/tools/cc.sh" "$1" "$3"\n'
    )
    compile_sh.chmod(0o755)

    (out / "settings.toml").write_text(
        f'func_name = "{fn}"\n'
        'compiler_type = "gcc"\n'
        'objdump_command = "mips-linux-gnu-objdump -drz"\n'
    )

    # Sanity check: the draft must compile with the real toolchain.
    check = subprocess.run([str(compile_sh), str(out / "base.c"), "-o", str(out / "base.o")],
                           capture_output=True, text=True)
    if check.returncode != 0:
        sys.exit(f"base.c does not compile:\n{check.stderr}")

    print(f"Ready: permuter/{fn}/")
    print(f"Run:   .venv/bin/python tools/vendor/decomp-permuter/permuter.py permuter/{fn} -j 8")


if __name__ == "__main__":
    main()
