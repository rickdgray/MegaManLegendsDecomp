# Settings for asm-differ (tools/vendor/asm-differ/diff.py). Run from the repo root.
# Use it through tools/diff.sh <target> <Func>, which exports the target's paths below.
# -o compares the function in build/<target>/ against the known-good snapshot in
# expected/<target>/ (made by tools/make_expected.sh <target> from a matching build).

import os


def apply(config, args):
    def env(name):
        value = os.environ.get(name)
        if not value:
            raise SystemExit(f"diff_settings.py: {name} not set; run asm-differ through tools/diff.sh <target>")
        return value

    config["arch"] = "mips"
    config["objdump_executable"] = "mips-linux-gnu-objdump"
    config["mapfile"] = env("DIFF_MAP")
    config["baseimg"] = env("DIFF_ORIGINAL")
    config["myimg"] = env("DIFF_BINARY")
    config["expected_dir"] = env("DIFF_EXPECTED")
    config["source_directories"] = [env("DIFF_SRC"), "include"]
    config["makeflags"] = []
