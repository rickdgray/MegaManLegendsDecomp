"""Apply PS1 RAM aliasing to the memory helpers emitted by wasm2c."""

import argparse
import re
from pathlib import Path


def alias_memory(source):
    marker = "#define DEF_MEM_CHECKS0("
    if source.count(marker) != 1:
        raise ValueError("wasm2c memory helper format has changed")
    alias = """// PS1 KUSEG/24-bit addresses and KSEG1 alias the KSEG0 RAM window.
static inline u64 psx_wasm_ram_alias(u64 addr) {
  if (addr < 0x01000000u)
    return addr + 0x80000000u;
  if (addr >= 0xA0000000u && addr < 0xA1000000u)
    return addr - 0x20000000u;
  return addr;
}

"""
    source = source.replace(marker, alias + marker)
    # Rewrite the address before both the bounds check and the actual access.
    checks = r"^(    MEMCHECK_(?:DEFAULT32|GENERAL)\([^\n]+)$"
    source, count = re.subn(
        checks, lambda m: "    addr = psx_wasm_ram_alias(addr); \\\n" + m[0], source, flags=re.MULTILINE
    )
    if count != 6:
        raise ValueError("expected six wasm2c scalar memory helpers")

    for line, variables in (
        ("  RANGE_CHECK(mem, d, n);", ("d",)),
        ("  RANGE_CHECK(dest, dest_addr, n);\n  RANGE_CHECK(src, src_addr, n);", ("dest_addr", "src_addr")),
        ("  LOAD_DATA((*dest), dest_addr, src + src_addr, n);", ("dest_addr",)),
    ):
        if source.count(line) != 1:
            raise ValueError("wasm2c bulk memory helper format has changed")
        normalize = "".join(f"  {var} = psx_wasm_ram_alias({var});\n" for var in variables)
        source = source.replace(line, normalize + line)
    return source


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    args = parser.parse_args()
    try:
        args.source.write_text(alias_memory(args.source.read_text()))
    except ValueError as error:
        parser.error(str(error))


if __name__ == "__main__":
    main()
