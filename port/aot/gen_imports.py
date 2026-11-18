"""Adapt wasm2c's guest word imports to the host's PsyQ dispatcher."""

import argparse
import re
from pathlib import Path

from gen_link import retail_address, retail_symbols

IMPORT = re.compile(
    r"^/\* import: 'env' '([^']+)' \*/\n(\w+) (\w+)\(struct w2c_env\*([^\n]*)\);$",
    re.MULTILINE,
)


def generate(header, globals_, locals_, overlay=False):
    lines = [f'#include "{header.name}"', '#include "game_host.h"', '']
    symbols = ["/* Retail addresses for the base game's host imports. */", "#pragma once", ""]
    ir = header.read_text()
    imports = IMPORT.findall(ir)
    if len(imports) != ir.count("/* import:") - int(overlay):
        raise ValueError("unsupported wasm2c import declaration")
    for name, result, wrapper, parameters in imports:
        if name == "port_game_dispatch":
            if overlay:
                lines.extend((
                    f"u32 {wrapper}(struct w2c_env *env, u32 address, u32 a0, u32 a1, u32 a2)",
                    "{",
                    "    return port_overlay_dispatch(env, address, a0, a1, a2);",
                    "}",
                ))
            continue
        fields = parameters.removeprefix(", ").split(", ") if parameters else []
        if any(field != "u32" for field in fields) or result not in ("u32", "void"):
            raise ValueError(f"unsupported import signature for {name}")
        args = [f"a{i}" for i in range(len(fields))]
        signature = "".join(f", u32 {arg}" for arg in args)
        address = retail_address(name, globals_, True) or retail_address(name, locals_, True)
        if address is None and name not in ("abs", "port_asm_run", "port_vblank_idle"):
            raise ValueError(f"no retail address or host implementation for {name}")
        symbols.append(f"#define GAME_IMPORT_{name} 0x{address or 0:08X}u")
        call = "port_overlay_import" if overlay else "port_game_call_import"
        lines.extend((
            f"{result} {wrapper}(struct w2c_env *env{signature})",
            "{",
            f"    const uint32_t args[PORT_GAME_ARG_WORDS] = {{{', '.join(args) or '0'}}};",
            f"    {'return' if result == 'u32' else '(void)'} "
            f'{call}(env, 0x{address or 0:08X}u, "{name}", args);',
            "}",
            "",
        ))
    return "\n".join(lines), "\n".join(symbols) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("elf", type=Path)
    parser.add_argument("header", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("addresses", type=Path)
    parser.add_argument("--overlay-elf", type=Path)
    args = parser.parse_args()
    try:
        globals_, locals_ = retail_symbols(args.elf)
        if args.overlay_elf:
            stage_globals, stage_locals = retail_symbols(args.overlay_elf)
            globals_.update((name, symbol) for name, symbol in stage_globals.items() if symbol[1] == "FUNC")
            locals_.update((name, symbol) for name, symbol in stage_locals.items() if symbol[1] == "FUNC")
        wrappers, addresses = generate(args.header, globals_, locals_, bool(args.overlay_elf))
        args.output.write_text(wrappers)
        args.addresses.write_text(addresses)
    except ValueError as error:
        parser.error(str(error))


if __name__ == "__main__":
    main()
