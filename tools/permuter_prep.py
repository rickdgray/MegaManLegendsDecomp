#!/usr/bin/env python3
"""Prepare a decomp-permuter directory for a parked function.

Usage:  tools/permuter_prep.py [target] FunctionName [--src FILE]

target: an executable or an overlay (r3_shl0d). --src names the C file that holds the parked
function (src/rock_neo.exe/cd.c); without it, every C file the target compiles is searched,
including the shared stage code an overlay links (src/stage_common/).

The function must be parked in the source like this:

    #ifdef NON_MATCHING
    <best attempt>
    #else
    INCLUDE_ASM("asm/<target>/nonmatchings/<file>", FunctionName);
    #endif

(or, in src/stage_common/, INCLUDE_ASM(ASM_DIR, FunctionName) with the file's ASM_DIR: the
overlay's own copy of the assembly).

Creates permuter/<target>/<FunctionName>/ with base.c, target.s, target.o, compile.sh and
settings.toml, then run:

    .venv/bin/python tools/vendor/decomp-permuter/permuter.py permuter/<target>/<FunctionName> -j 8
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import targets  # noqa: E402  (tools/targets.py)
from preamble import preamble  # noqa: E402  (tools/preamble.py)

ROOT = Path(__file__).resolve().parent.parent
INCLUDE = ROOT / "include"

AS = [
    "mips-linux-gnu-as", "-EL", "-march=r3000", "-mtune=r3000",
    "-no-pad-sections", "-G0", f"-I{INCLUDE}",
]

# One parked block: the draft, then the INCLUDE_ASM fallback naming the function.
BLOCK = re.compile(
    r"#ifdef NON_MATCHING\n(.*?)#else\s*\n"
    r'INCLUDE_ASM\(("[^"]+"|\w+),\s*(\w+)\);\s*\n#endif',
    re.S,
)
# src/stage_common/: the assembly folder under the overlay's own asm/<target>/ (cc.sh's TARGET_ASM).
ASM_DIR = re.compile(r'^#define ASM_DIR TARGET_ASM "([^"]+)"', re.M)

ASM_PRELUDE = '.include "macro.inc"\n.set noat\n.set noreorder\n.section .text\n\n'


def main() -> None:
    targets.default_target()
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("target", choices=targets.TARGETS)
    ap.add_argument("function")
    ap.add_argument("--src", help="C file containing the parked function (default: search the target's C files)")
    args = ap.parse_args()
    fn = args.function

    if args.src:
        candidates = [ROOT / args.src]
    else:
        candidates = targets.sources(args.target)

    for src_path in candidates:
        text = src_path.read_text()
        m = next((m for m in BLOCK.finditer(text) if m.group(3) == fn), None)
        if m:
            body, asm_dir = m.group(1), m.group(2)
            if asm_dir.startswith('"'):
                asm_dir = asm_dir.strip('"')
            else:
                d = ASM_DIR.search(text)
                if asm_dir != "ASM_DIR" or not d:
                    sys.exit(f"{src_path}: INCLUDE_ASM({asm_dir}, {fn}): no #define ASM_DIR TARGET_ASM \"...\"")
                asm_dir = f"asm/{args.target}" + d.group(1)
            break
    else:
        where = args.src or f"the C files of {args.target}"
        sys.exit(f"{fn}: no '#ifdef NON_MATCHING ... INCLUDE_ASM(..., {fn}) ... #endif' block in {where}")

    out = ROOT / "permuter" / args.target / fn
    out.mkdir(parents=True, exist_ok=True)

    # base.c: the source file's preamble (includes, its own small data and pool definitions,
    # file-local prototypes; tools/preamble.py) plus the draft, fully preprocessed. Keeping the
    # file's own small data defined keeps its $gp accesses as in the build.
    # PERMUTER makes include_asm.h define INCLUDE_ASM as nothing.
    raw = preamble(text) + "\n" + body
    pre = subprocess.run(
        ["cpp", "-P", "-undef", "-nostdinc", f"-I{INCLUDE / args.target}", f"-I{INCLUDE}", "-DPERMUTER",
         "-DNON_MATCHING", f'-DTARGET_ASM="asm/{args.target}"', "-"],
        input=raw, text=True, capture_output=True,
    )
    if pre.returncode != 0:
        sys.exit(f"cpp failed:\n{pre.stderr}")
    (out / "base.c").write_text(pre.stdout)

    # target.s / target.o: the original assembly, assembled with the build's flags.
    asm_path = ROOT / asm_dir / f"{fn}.s"
    if not asm_path.exists():
        sys.exit(f"{asm_path} not found (run tools/split.sh {args.target}?)")
    (out / "target.s").write_text(ASM_PRELUDE + asm_path.read_text())
    subprocess.run(AS + ["-o", str(out / "target.o"), str(out / "target.s")], check=True)

    # compile.sh: the permuter calls it as  compile.sh <input.c> -o <output.o>
    compile_sh = out / "compile.sh"
    compile_sh.write_text(
        "#!/usr/bin/env bash\n"
        "# Invoked by the permuter as: compile.sh <input.c> -o <output.o>\n"
        f'exec "{ROOT}/tools/cc.sh" {args.target} "$1" "$3"\n'
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

    print(f"Ready: permuter/{args.target}/{fn}/")
    print(f"Run:   ./tools/permute.sh [{args.target}] {fn} 8")


if __name__ == "__main__":
    main()
