"""Give a wasm2c overlay module separate host import names."""

import argparse
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("module")
    parser.add_argument("sources", type=Path, nargs="+")
    args = parser.parse_args()
    for path in args.sources:
        source = path.read_text()
        path.write_text(source.replace("w2c_env_", f"w2c_{args.module}_env_"))


if __name__ == "__main__":
    main()
