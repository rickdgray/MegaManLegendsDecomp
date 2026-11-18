"""Lower the base game's indirect calls to an import that accepts a PS1 address."""

import re

from asm_rewrite import split_top
from gen_link import retail_address

CALL = re.compile(
    r"^( +)(?:(%\d+) = )?call (void|i32) (%\d+)\((.*)\)(?: #\d+)?$",
    re.MULTILINE,
)
VALUE = re.compile(r"\bptr (?:noundef )?@([\w.$]+)(?![\w.$(])")
IMPORT = (
    '\ndeclare i32 @port_game_dispatch(i32, i32, i32, i32) '
    '"wasm-import-module"="env" "wasm-import-name"="port_game_dispatch"\n'
)


def lower_calls(ir, globals_, locals_):
    # A function address stored in an object must agree with the addresses in
    # retail tables and overlays, even though wasm's own table uses dense indices.
    names = set(re.findall(r"^(?:define|declare) [^\n@]+ @([\w.$]+)\(", ir, re.MULTILINE))

    def bind_pointer(match):
        name = match[1]
        if name not in names:
            return match[0]
        address = retail_address(name, globals_, want_func=True)
        if address is None:
            address = retail_address(name, locals_, want_func=True)
        if address is None and re.fullmatch(r"D_[0-9A-Fa-f]{8}", name):
            alias = name.replace("D_", "func_", 1)
            if globals_.get(alias, (None, None))[1] == "FUNC":
                address = globals_[alias][0]
        if address is None:
            raise ValueError(f"no retail address for function pointer {name}")
        return match[0].replace(f"@{name}", f"inttoptr (i32 {address} to ptr)")

    ir = VALUE.sub(bind_pointer, ir)
    next_value = 0

    def lower_call(match):
        nonlocal next_value
        indent, result, _, target, args = match.groups()
        instructions = []
        words = []

        def convert(instruction):
            nonlocal next_value
            value = f"%port.dispatch.{next_value}"
            next_value += 1
            instructions.append(f"{value} = {instruction}")
            return f"i32 {value}"

        words.append(convert(f"ptrtoint ptr {target} to i32"))
        for arg in split_top(args, ",") if args else ():
            operand = re.fullmatch(
                r"(ptr|i32|i16|i8) noundef (?:(zeroext|signext) )?(.+)", arg.strip()
            )
            if operand is None:
                raise ValueError(f"unsupported dispatch operand {arg}")
            ty, extension, value = operand.groups()
            if ty == "ptr":
                words.append(convert(f"ptrtoint ptr {value} to i32"))
            elif ty == "i32":
                words.append(f"i32 {value}")
            else:
                if extension is None:
                    raise ValueError(f"missing extension attribute on dispatch argument {arg}")
                op = "sext" if extension == "signext" else "zext"
                words.append(convert(f"{op} {ty} {value} to i32"))

        if len(words) > 4:
            raise ValueError(f"too many parameters in {match[0].strip()}")
        words.extend(["i32 0"] * (4 - len(words)))
        call = f"call i32 @port_game_dispatch({', '.join(words)})"
        if result is None:
            # Even discarded non-void call results use an LLVM value number.
            # Use a named result so the original value numbering stays intact.
            convert(call)
        else:
            instructions.append(f"{result} = {call}")
        return "\n".join(indent + instruction for instruction in instructions)

    ir, lowered = CALL.subn(lower_call, ir)
    if re.search(r"\bcall [^\n]* %\d+\(", ir):
        raise ValueError("unsupported indirect call in the base game")
    return ir + IMPORT if lowered else ir
