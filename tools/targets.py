"""The project's targets, and the default when a tool is run without one."""

import sys

TARGETS = ["slus_006.03", "rock_neo.exe"]
DEFAULT = "rock_neo.exe"


def default_target(argv=None):
    """Insert DEFAULT as the first argument unless the command line already starts with a target
    (in place on sys.argv by default). Call before parsing arguments."""
    argv = sys.argv if argv is None else argv
    if len(argv) < 2 or argv[1] not in TARGETS:
        argv.insert(1, DEFAULT)
    return argv
