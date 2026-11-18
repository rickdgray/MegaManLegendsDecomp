"""Generate typed native dispatch for the retail functions exported by wasm2c."""

import argparse
import re
from pathlib import Path

from gen_link import retail_address, retail_symbols
from ovl_elf import Elf, hash_ranges

EXPORT = re.compile(
    r"^/\* export: '([^']+)' \*/\n(void|u32) (\w+)\(([^\n]*)\);$",
    re.MULTILINE,
)


def generate(header, globals_, locals_, overlay, elf):
    entries = {}
    for name, result, function, parameters in EXPORT.findall(header.read_text()):
        if name.startswith("__"):
            continue
        retail_name = "main" if name == "psx_main" else name
        address = retail_address(retail_name, globals_, want_func=True)
        if address is None:
            address = retail_address(retail_name, locals_, want_func=True)
        if address is None:
            raise ValueError(f"export {name} has no retail function address")
        _, *words = parameters.split(", ")
        if any(word != "u32" for word in words):
            raise ValueError(f"unsupported parameters for {name}: {parameters}")
        if len(words) > 16:
            raise ValueError(f"too many arguments to dispatch {name}")
        if address in entries:
            raise ValueError(f"duplicate native function at 0x{address:08X}: {name}")
        args = ", ".join(["instance", *(f"args[{i}]" for i in range(len(words)))])
        call = f"{function}({args});"
        if result == "void":
            body = f"            {call}\n            *result = 0;\n"
        else:
            body = f"            *result = {call}\n"
        entries[address] = body

    if not entries:
        raise ValueError("no retail functions found in wasm2c exports")

    prefix = "overlay" if overlay else "port_game"
    lines = [
        f'#include "{header.name}"',
        '#include "game_host.h"\n',
        (f"int {prefix}_call_native(void *instance, uint32_t address," if not overlay else
         "static int overlay_call(uint32_t address,"),
        "                          const uint32_t args[PORT_GAME_ARG_WORDS], uint32_t *result)",
        "{",
        "    switch (address)",
        "    {",
    ]
    if overlay:
        instance = re.search(r"typedef struct (w2c_\w+) \{", header.read_text())[1]
        wasm_type = instance.removeprefix("w2c_")
        lines[2:2] = [
            '#include <stdlib.h>',
            f"static {instance} module;",
            "static struct w2c_env environment;",
            "",
        ]
    for address, body in sorted(entries.items()):
        if overlay:
            body = body.replace("(instance", "(&module")
        lines.extend((f"        case 0x{address:08X}u:", body.rstrip(), "            return 1;"))
    lines.extend(("        default:", "            return 0;", "    }", "}", ""))
    if overlay:
        base, image = Elf(elf).image()
        prefix_size = 64
        hash_ = hash_ranges(base, image, [(base, prefix_size)])
        lines.extend((
            f"static uint32_t *overlay_stack(void) {{ return {instance}_0x5F_stack_pointer(&module); }}",
            "",
            "static void overlay_init(struct w2c_env *game)",
            "{",
            "    environment = *game;",
            f"    wasm2c_{wasm_type}_instantiate(&module, &environment);",
            "    environment.overlay_sp = overlay_stack();",
            f"    if (*{instance}_0x5F_heap_base(&module) - *{instance}_0x5F_global_base(&module) > 0x20000u)",
            "        abort();",
            "}",
            "",
            "extern wasm_rt_memory_t *port_overlay_memory(struct w2c_env *env);",
            f"wasm_rt_memory_t *w2c_{overlay}_env_memory(struct w2c_env *env)",
            "{",
            "    return port_overlay_memory(env);",
            "}",
            "",
            f"const PORT_AOT_OVERLAY port_overlay_{overlay} = {{",
            f'    "{overlay}", 0x{base:08X}u, 0x{max(entries) + 4:08X}u, 0x{hash_:016X}ull,',
            "    overlay_init, overlay_stack, overlay_call,",
            "};",
            "",
        ))
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("elf", type=Path)
    parser.add_argument("header", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--overlay", help="overlay module name")
    args = parser.parse_args()
    try:
        args.output.write_text(generate(args.header, *retail_symbols(args.elf), args.overlay, args.elf))
    except ValueError as error:
        parser.error(str(error))


if __name__ == "__main__":
    main()
