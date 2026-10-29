# Settings for asm-differ (tools/vendor/asm-differ/diff.py). Run from the repo root.
# Typical use:  python3 tools/vendor/asm-differ/diff.py -o FunctionName
# -o compares the function in build/ against the known-good snapshot in expected/
# (made by tools/make_expected.sh from a matching build).

def apply(config, args):
    config["arch"] = "mips"
    config["objdump_executable"] = "mips-linux-gnu-objdump"
    config["mapfile"] = "build/slus_006.03.map"
    config["baseimg"] = "disc/extracted/SLUS_006.03"
    config["myimg"] = "build/SLUS_006.03"
    config["expected_dir"] = "expected/"
    config["source_directories"] = ["src", "include"]
    config["makeflags"] = []