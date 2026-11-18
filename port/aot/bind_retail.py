#!/usr/bin/env python3
"""Bind LLVM data symbols to addresses in a matching PS-X EXE."""

import argparse
import re
from pathlib import Path

from game_dispatch import lower_calls
from gen_link import retail_address, retail_symbols


DISPATCH_TARGETS = (
    "cd_cmd_nop",
    "cd_cmd_play_movie",
    "intro_copyright",
    "intro_wait_idle",
    "intro_play_movie",
    "intro_launch_game",
)
CALLBACKS = ("Vsync_handler", "Movie_dct_out_callback", "Cd_sync_cb", "Movie_sector_cb")
CHECK_ROUTINES = (
    "Pad_update_all", "Cd_read_sync2", "Cd_cmd_set_movie", "Cd_cmd_exec", "Intro_task", "Intro_init",
)
RETAIL_IMPORTS = (
    "VSync", "SetDispMask", "PutDispEnv", "PutDrawEnv", "DrawOTag", "ClearOTag",
    "DrawSync", "ResetCallback", "SsInit", "ResetGraph", "DecDCTReset",
    "SetVideoMode", "InitPAD", "StartPAD", "ChangeClearPAD", "ClearImage",
    "VSyncCallback", "SsSetSerialAttr", "SsSetSerialVol", "SetDefDrawEnv",
    "SetDefDispEnv", "CdInit", "CdReadyCallback", "CdReset", "DecDCTvlc",
    "DecDCToutCallback", "DecDCTin", "DecDCTout", "LoadImage", "CdSyncCallback",
    "CdMix", "CdIntToPos", "CdGetSector", "CdSync", "CdControl", "CdControlB",
    "SetDrawMode", "SsQuit", "StopPAD", "_96_init", "LoadExec",
)
HOST_IMPORTS = (*RETAIL_IMPORTS, "port_vblank_idle", "port_spin_pause")
LIBRARY_SYMBOLS = (
    "InterruptCallback", "DMACallback", "OpenEvent", "EnableEvent", "CloseEvent",
    "DisableEvent", "DeliverEvent", "SetDrawEnv2",
)


def bind_imports(ir):
    # Fail the link on any unspecified import instead of silently stubbing it.
    for name in HOST_IMPORTS:
        declaration = re.compile(rf"^(declare [^\n]* @{name}\([^\n]*\))[^\n]*$", re.MULTILINE)
        ir, count = declaration.subn(
            rf'\1 "wasm-import-module"="host" "wasm-import-name"="{name}"', ir
        )
        if count != 1:
            raise ValueError(f"missing LLVM declaration for {name}")
    return ir


def bind_dispatch(ir, addresses):
    # The retail tables contain PS1 code addresses. Wasm function pointers are table indices,
    # so turn the two shim dispatch sites into a switch keyed by the original PS1 address.
    call = re.compile(r"^( +)call void (%\d+)\(\)(?: #\d+)?$", re.MULTILINE)
    ir, count = call.subn(r"\1call void @port_shim_dispatch(ptr \2)", ir)
    if count != 2 or re.search(r"\bcall [^\n]* %\d+\(", ir):
        raise ValueError("unexpected indirect call in the shim")
    labels = {name: f"target_{index}" for index, name in enumerate(DISPATCH_TARGETS)}
    cases = "\n".join(f"    i32 {addresses[name]}, label %{label}" for name, label in labels.items())
    blocks = "\n".join(
        f"{label}:\n  call void @{name}()\n  ret void" for name, label in labels.items()
    )
    return ir + f"""
define internal void @port_shim_dispatch(ptr %target) {{
entry:
  %address = ptrtoint ptr %target to i32
  switch i32 %address, label %invalid [
{cases}
  ]
{blocks}
invalid:
  call void @llvm.trap()
  unreachable
}}

declare void @llvm.trap()
"""


def bind_data(ir, symbols, locals_, game):
    symbol_token = r'("[^"\n]+"|[\w.$]+)'
    declarations = re.compile(r"^@" + symbol_token + r" = (.+)\n", re.MULTILINE)
    addresses = {}
    for name, declaration in declarations.findall(ir):
        external = declaration.startswith("external ")
        if not external and not game:
            continue
        if name.startswith((".", "__const.", "llvm.")) or ".port_asm_prog" in name:
            # Clang literals, aggregates and the inline-assembly runtime's cache
            # are private to the compiled module.
            continue
        address = retail_address(name, symbols, want_func=False)
        if not external and declaration.startswith("internal "):
            address = retail_address(name, locals_, want_func=False) or address
        if address is None:
            alias = re.fullmatch(r'"([\w.$]+)\+(0x[0-9A-Fa-f]+)"', name)
            if alias:
                address = retail_address(alias[1], symbols, want_func=False)
                if address is not None:
                    address += int(alias[2], 16)
        if address is None:
            raise ValueError(f"no retail data address for {name}")
        addresses[name] = address

    ir = declarations.sub(lambda match: "" if match[1] in addresses else match[0], ir)
    # LLVM assumes some arrays have 16-byte alignment on wasm32. The retail linker
    # follows the PS1 ABI. Keep the access widths and remove those alignment promises.
    ir = re.sub(r"(, align )\d+", r"\g<1>1", ir)
    ir = re.sub(r"\b(align )\d+(?= (?:inttoptr|@))", r"\g<1>1", ir)
    ir = re.sub(
        r"@" + symbol_token,
        lambda match: (
            f"inttoptr (i32 {addresses[match[1]]} to ptr)"
            if match[1] in addresses
            else match[0]
        ),
        ir,
    )
    return ir, addresses


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("elf", type=Path)
    parser.add_argument("source", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("header", type=Path, nargs="?")
    parser.add_argument("--game", action="store_true", help="bind game data and lower indirect calls")
    parser.add_argument("--main-elf", type=Path, help="base-game symbols referenced by an overlay")
    args = parser.parse_args()
    if args.main_elf is not None and not args.game:
        parser.error("--main-elf requires --game")
    if not args.game and args.header is None:
        parser.error("the shim requires an output header path")
    symbols, locals_ = retail_symbols(args.elf)
    if args.main_elf is not None:
        main_symbols, _ = retail_symbols(args.main_elf)
        # Overlay link scripts also contain base-game aliases as NOTYPE.
        # Keep the function's type from the base ELF when the addresses agree.
        symbols = {
            **main_symbols,
            **{name: value for name, value in symbols.items()
               if value[1] != "NOTYPE" or name not in main_symbols or value[0] != main_symbols[name][0]},
        }
    try:
        ir, addresses = bind_data(args.source.read_text(), symbols, locals_, args.game)
    except ValueError as error:
        parser.error(str(error))

    if args.game:
        try:
            args.output.write_text(lower_calls(ir, symbols, locals_))
        except ValueError as error:
            parser.error(f"{args.source}: {error}")
        return

    for name in (*CALLBACKS, *CHECK_ROUTINES, *DISPATCH_TARGETS, *RETAIL_IMPORTS, *LIBRARY_SYMBOLS):
        address = retail_address(name, symbols, want_func=True)
        if address is None:
            parser.error(f"no retail function address for {name}")
        addresses[name] = address
    for name in CALLBACKS:
        ir, count = re.subn(
            rf"(?<=ptr noundef )@{name}\b",
            f"inttoptr (i32 {addresses[name]} to ptr)",
            ir,
        )
        if count != 1:
            parser.error(f"unexpected number of registrations for {name}: {count}")
    try:
        ir = bind_imports(bind_dispatch(ir, addresses))
    except ValueError as error:
        parser.error(str(error))
    args.output.write_text(ir)
    args.header.write_text(
        "/* Symbol addresses from the matching boot shim ELF. */\n"
        "#pragma once\n"
        + "".join(f"#define RETAIL_{name} 0x{addr:08X}u\n" for name, addr in sorted(addresses.items()))
    )


if __name__ == "__main__":
    main()
