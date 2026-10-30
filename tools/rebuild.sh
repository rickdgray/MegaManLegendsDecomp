rm -rf asm build
set -e
./tools/split.sh
./tools/build.sh
./tools/make_expected.sh
