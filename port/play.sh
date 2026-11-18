#!/bin/sh
# Plays Mega Man Legends natively: builds what is missing, then runs the boot shim (Capcom logo,
# then the game) in one window. Arguments go to the game (e.g. --disc PATH, --card1 PATH,
# --config FILE, --mute; --vanilla or --mods LIST skip the start-up Vanilla/Mods menu: see
# docs/mods.md). `make play` runs this; `make install-desktop` adds a menu entry for it.
#
# Needs: the owner's disc image in disc/image/ and `make extract` done (the README), the
# matching toolchain (`make setup`), cmake, ninja, and 32-bit SDL3 (lib32-sdl3) for the window.
set -e
repo=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
cd "$repo"

say() { printf 'play: %s\n' "$*" >&2; }

if [ ! -f disc/extracted/ROCK_NEO.EXE ] || [ ! -f disc/extracted/SLUS_006.03 ]; then
    say "no extracted game files: put your disc image in disc/image/ and run 'make extract'"
    exit 1
fi

# The matching builds: the port takes every retail address from their ELFs.
for t in slus_006.03 rock_neo.exe; do
    if [ ! -f "build/$t/$t.elf" ]; then
        [ -d "asm/$t" ] || ./tools/split.sh "$t" > /dev/null
        say "building $t (matching)"
        ./tools/build.sh "$t" | tail -n 1
    fi
done
# The overlays' matching builds make their C native; without them the stages run interpreted.
if ! ls build/r3_st01/r3_st01.elf > /dev/null 2>&1; then
    say "no overlay builds (make split-overlays overlays): stage code will run on the interpreter"
fi

dir=build/port-sdl
if [ ! -f "$dir/build.ninja" ]; then
    say "configuring $dir"
    cmake -S port -B "$dir" -G Ninja -DPORT_SDL_M32=ON > /dev/null
fi
ninja -C "$dir" mml mml_boot > /dev/null || { ninja -C "$dir" mml mml_boot; exit 1; }
if ! grep -q PORT_HAVE_SDL "$dir/build.ninja"; then
    say "no 32-bit SDL3 found: install lib32-sdl3, then rm -r $dir and run this again"
    exit 1
fi

exec "$dir/mml_boot" "$@"
