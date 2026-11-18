#!/usr/bin/env bash
# Builds the Apple TV app on a Mac and installs it on an Apple TV.
#
#   port/appletv/deploy.sh            export, build, install and launch
#   port/appletv/deploy.sh --build    export and build only, unsigned (a compile check)
#
# Needs the Linux 64-bit build configured and built first (build/port64-all): the Mac compiles its
# exported C and needs only Xcode, CMake and a static SDL3 for tvOS in $MAC_DIR/deps/sdl3-tvos.
#
# Settings come from the environment or from .env in the repository root (git-ignored):
#   MAC          the Mac's ssh host (required)
#   MAC_DIR      where the sources go on the Mac, relative to its home (default Projects/mml-appletv)
#   TV           the Apple TV's identifier in `xcrun devicectl list devices` (required to install)
#   TEAM         the Apple development team ID that signs the app (required to install)
#   BUNDLE       the app's bundle identifier (default com.example.megamanlegends)
#   MAC_ROOT     the Mac's login password, to unlock its keychain for signing; or
#   MAC_ROOT_ENV a file to read MAC_ROOT= from. Without either it asks in a terminal.
set -euo pipefail
cd "$(dirname "$0")/../.."
[[ -f .env ]] && set -a && . ./.env && set +a
: "${MAC:?set MAC, the ssh host of the Mac, in .env}"
MAC_DIR=${MAC_DIR:-Projects/mml-appletv}
BUNDLE=${BUNDLE:-com.example.megamanlegends}

python3 port/appletv/export.py --out build/appletv
mkdir -p build/appletv/game/disc
cp -p disc/extracted/ROCK_NEO.EXE disc/extracted/SLUS_006.03 build/appletv/game/
cp -p disc/image/*.cue disc/image/*.bin build/appletv/game/disc/
cp -p port/appletv/CMakeLists.txt port/appletv/Info.plist build/appletv/
rm -rf build/appletv/Assets.xcassets && cp -rp port/appletv/Assets.xcassets build/appletv/

ssh "$MAC" "mkdir -p $MAC_DIR/app"
rsync -a --delete --exclude '/build*/' --exclude '/scratch/' build/appletv/ "$MAC:$MAC_DIR/app/"

CONFIGURE="export PATH=/opt/homebrew/bin:\$PATH && cd $MAC_DIR/app \
    && cmake -S . -B build -G Xcode -DCMAKE_SYSTEM_NAME=tvOS -DCMAKE_OSX_ARCHITECTURES=arm64 \
       -DCMAKE_OSX_DEPLOYMENT_TARGET=17.0 -DSDL3_DIR=\$HOME/$MAC_DIR/deps/sdl3-tvos/lib/cmake/SDL3 \
       -DMML_TEAM='${TEAM:-}' -DMML_BUNDLE_ID='$BUNDLE' >/dev/null"
APP=build/Release-appletvos/MegaManLegends.app

if [[ "${1:-}" == "--build" ]]; then
    ssh "$MAC" "$CONFIGURE && cmake --build build --config Release -- -quiet CODE_SIGNING_ALLOWED=NO 2>&1 \
        | { grep -E 'error|BUILD|warning: .*(implicit|incompatible)' || true; } | sort -u | head -60; ls -d $APP"
    exit
fi

: "${TV:?set TV, the devicectl identifier of the Apple TV, in .env}"
: "${TEAM:?set TEAM, the Apple development team ID, in .env}"
[[ -z "${MAC_ROOT:-}" && -n "${MAC_ROOT_ENV:-}" && -f "${MAC_ROOT_ENV/#\~/$HOME}" ]] && \
    MAC_ROOT=$(sed -n 's/^MAC_ROOT=//p' "${MAC_ROOT_ENV/#\~/$HOME}")

BUILD="$CONFIGURE && cmake --build build --config Release -- -quiet -allowProvisioningUpdates 2>&1 \
        | { grep -E 'error|BUILD' || true; } | sort -u | head -40 \
    && echo 'built and signed' \
    && xcrun devicectl device install app --device '$TV' $APP \
    && { xcrun devicectl device process launch --terminate-existing --device '$TV' $BUNDLE >/dev/null 2>&1 \
         && echo launched || echo 'installed; not launched (the Apple TV is probably asleep)'; }"

if [[ -n "${MAC_ROOT:-}" ]]; then
    # The password goes over ssh's stdin, never in an argument.
    printf '%s\n' "$MAC_ROOT" | ssh "$MAC" "set -o pipefail \
        && IFS= read -r P && security unlock-keychain -p \"\$P\" ~/Library/Keychains/login.keychain-db && unset P \
        && $BUILD"
else
    # One ssh session for all of it: an unlock in another session doesn't carry over.
    ssh -t "$MAC" "set -o pipefail \
        && { security show-keychain-info ~/Library/Keychains/login.keychain-db >/dev/null 2>&1 \
             || security unlock-keychain ~/Library/Keychains/login.keychain-db; } \
        && $BUILD"
fi
