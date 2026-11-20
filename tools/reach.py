#!/usr/bin/env python3
"""Which targets a change can reach, so you know what to build (CLAUDE.md, "The one rule").

Usage:
    .venv/bin/python tools/reach.py               the working tree's uncommitted changes
    .venv/bin/python tools/reach.py PATH [...]    these files (repo-relative)
    add --command to print the build line instead: ./tools/build.sh <targets>

The rules are tools/targets.py's reached_by: config/<t>/ and src/<t>/ reach t (ROCK_NEO's registry
also reaches every overlay, which link against it); src/stage_common/<f>.c reaches the overlays
that link it; a header reaches the targets whose C includes it; tools/ and include/*.inc reach
everything; notes/ and documents reach nothing.
"""

import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import targets  # noqa: E402  (tools/targets.py)


def uncommitted():
    """Paths git reports as changed, added or deleted (read-only: git status)."""
    out = subprocess.run(["git", "status", "--porcelain", "--untracked-files=all"], cwd=targets.ROOT,
                         capture_output=True, text=True, check=True).stdout
    paths = []
    for line in out.splitlines():
        path = line[3:]
        if " -> " in path:                          # a rename: both sides count
            paths += path.split(" -> ")
        else:
            paths.append(path)
    return [p.strip('"') for p in paths]


def main():
    args = [a for a in sys.argv[1:] if a != "--command"]
    paths = args or uncommitted()
    reached = targets.reached_by(paths)
    if "--command" in sys.argv:
        print(f"./tools/build.sh {' '.join(reached)}" if reached else "# nothing to build")
    elif reached:
        print(" ".join(reached))
    else:
        print("(no target)")


if __name__ == "__main__":
    main()
