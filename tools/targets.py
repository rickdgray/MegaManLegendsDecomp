"""The project's targets, what each one is built from, and which targets a change can reach.

Executables: slus_006.03 (the boot shim) and rock_neo.exe (the main game, the default target).
Overlays: the code chunks of CDDATA/DAT/*.BIN (r3_st05, r3_shl0d, r3_sup, ...), listed in
tools/overlays.txt. They link against rock_neo.exe's registry (HOST), and the shared stage code in
src/stage_common/ is compiled into every overlay whose yaml lists it.
"""

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

EXECUTABLES = ["slus_006.03", "rock_neo.exe"]
HOST = "rock_neo.exe"              # the program the overlays are loaded into and link against
DEFAULT = "rock_neo.exe"
SHARED_SRC = "src/stage_common"    # stage code compiled into several overlays


def _read_overlays():
    """({target: (archive, load address, size)}, {archive stem: target}) from tools/overlays.txt,
    in file order. The archive map includes the duplicate archives (ST03B, ...) that carry the
    same code chunk as a target's."""
    info, archives = {}, {}
    path = ROOT / "tools" / "overlays.txt"
    if not path.exists():
        return info, archives
    for line in path.read_text().splitlines():
        parts = line.split()
        if parts and not parts[0].startswith("#"):
            info[parts[0]] = (parts[1], int(parts[2], 16), int(parts[3], 16))
            for archive in [parts[1]] + parts[7:]:
                archives[Path(archive).stem] = parts[0]
    return info, archives


OVERLAY_INFO, ARCHIVE_TARGET = _read_overlays()
OVERLAYS = list(OVERLAY_INFO)
TARGETS = EXECUTABLES + OVERLAYS

# Where each executable's image (code, data and BSS) lives; anything outside is absolute.
_EXECUTABLE_IMAGE = {
    "slus_006.03": (0x80010000, 0x8005DA40),
    "rock_neo.exe": (0x80010000, 0x800D9000),
}


def default_target(argv=None):
    """Insert DEFAULT as the first argument unless the command line already starts with a target
    (in place on sys.argv by default). Call before parsing arguments."""
    argv = sys.argv if argv is None else argv
    # Something shaped like a target but not one (a typo such as r3_st5) is an error, not a
    # reason to fall back to the default target.
    if len(argv) >= 2 and argv[1] not in TARGETS and re.fullmatch(r"r3_\w+|\w+\.(exe|\d\d)", argv[1]):
        sys.exit(f"unknown target {argv[1]!r}: one of {', '.join(EXECUTABLES)}, or an overlay "
                 f"from tools/overlays.txt ({OVERLAYS[0]} ... {OVERLAYS[-1]})")
    if len(argv) < 2 or argv[1] not in TARGETS:
        argv.insert(1, DEFAULT)
    return argv


def is_overlay(target):
    return target in OVERLAY_INFO


def image(target):
    """(first address, end address) of the target's own code, data and BSS."""
    if is_overlay(target):
        _, load, size = OVERLAY_INFO[target]
        return load, load + size
    return _EXECUTABLE_IMAGE[target]


def registry(target):
    return ROOT / "config" / target / "symbol_addrs.txt"


def shared_files(target):
    """Stems of the src/stage_common/ files the overlay's yaml links (stcom01, ...)."""
    if not is_overlay(target):
        return []
    yaml = ROOT / "config" / target / f"{target}.yaml"
    return sorted(set(re.findall(r"name:\s*(\w+),\s*dir:\s*\.\./stage_common", yaml.read_text())))


def sources(target):
    """Every C file compiled into the target: its own, then the shared stage code it links."""
    own = sorted((ROOT / "src" / target).glob("**/*.c"))
    shared = [ROOT / SHARED_SRC / f"{s}.c" for s in shared_files(target)]
    return own + [p for p in shared if p.exists()]


def text_dirs(target):
    """Folders whose C and headers can name the target's symbols."""
    dirs = [f"src/{target}", f"include/{target}"]
    if is_overlay(target):
        dirs += [SHARED_SRC, "include/stage_common", "include/shl"]
    return dirs


def overlays_using(shared_stem):
    """Overlays whose yaml links src/stage_common/<shared_stem>.c."""
    return [t for t in OVERLAYS if shared_stem in shared_files(t)]


_INCLUDE = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)


def _includes(path, target, seen):
    """Headers `path` pulls in, transitively, resolved like tools/cc.sh does:
    the file's own folder, then include/<target>/, then include/."""
    try:
        text = path.read_text()
    except (OSError, UnicodeDecodeError):
        return
    for name in _INCLUDE.findall(text):
        for base in (path.parent, ROOT / "include" / target, ROOT / "include"):
            hit = (base / name).resolve()
            if hit.is_file():
                if hit not in seen:
                    seen.add(hit)
                    _includes(hit, target, seen)
                break


_header_cache = {}


def headers(target):
    """Every header (absolute path) any of the target's C files includes, directly or not."""
    if target not in _header_cache:
        seen = set()
        for c in sources(target):
            _includes(c, target, seen)
        _header_cache[target] = seen
    return _header_cache[target]


def reached_by(paths):
    """Targets a change to these files (repo-relative or absolute) can affect, in TARGETS order.

    config/<t>/ reaches t, and rock_neo.exe's registry also reaches every overlay (they link
    against it). src/<t>/ reaches t; src/stage_common/<f>.c the overlays that link it. A header
    reaches the targets whose C includes it; assembly includes (*.inc) and tools/ reach everything.
    notes/, CLAUDE.md and other documents reach nothing."""
    hit = set()
    for p in paths:
        p = Path(p)
        rel = p.resolve().relative_to(ROOT) if p.is_absolute() else p
        parts = rel.parts
        if not parts:
            continue
        top = parts[0]
        if top == "config" and len(parts) > 1:
            hit.add(parts[1])
            if parts[1] == HOST and rel.name == "symbol_addrs.txt":
                hit.update(OVERLAYS)
        elif top == "src" and len(parts) > 1:
            if "/".join(parts[:2]) == SHARED_SRC:
                hit.update(overlays_using(rel.stem))
            else:
                hit.add(parts[1])
        elif top == "include":
            if rel.suffix == ".inc":
                hit.update(TARGETS)
            else:
                full = (ROOT / rel).resolve()
                hit.update(t for t in TARGETS if full in headers(t))
                if len(parts) > 2 and parts[1] in TARGETS:
                    hit.add(parts[1])   # a target's own header, even before anything includes it
        elif top == "tools":
            hit.update(TARGETS)
    return [t for t in TARGETS if t in hit]
