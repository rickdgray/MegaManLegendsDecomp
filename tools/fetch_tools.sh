#!/usr/bin/env bash
# Fetch pinned third-party tools into tools/vendor/ (gitignored).
# Safe to re-run: anything already fetched is skipped. Delete a folder to re-fetch it.
set -euo pipefail
cd "$(dirname "$0")/.."

VENDOR=tools/vendor

# --- Pins -------------------------------------------------------------------
# Compiler: decompals/old-gcc release tarball, pinned by sha256.
GCC_URL=https://github.com/decompals/old-gcc/releases/download/0.17/gcc-2.7.2-psx.tar.gz
GCC_SHA256=500a459b3485e885a8d302cac23c2a4632f3900e03a09153f6190699fd723571

# Python tools: pinned by git commit (a commit hash is itself a content checksum).
# To pick a commit:  git ls-remote https://github.com/mkst/maspsx HEAD
MASPSX_REPO=https://github.com/mkst/maspsx
MASPSX_COMMIT=4ffa8b5106f9780d5d4aa7609f184949433ddbbc
M2C_REPO=https://github.com/matt-kempster/m2c
M2C_COMMIT=c632946b8cfbe8fce442b522dba92dfa72f1f317
ASMDIFF_REPO=https://github.com/simonlindholm/asm-differ
ASMDIFF_COMMIT=0dd09af8f8008f1f880327cf0aca3b26d2562ea2
# ----------------------------------------------------------------------------

mkdir -p "$VENDOR"

fetch_tarball() {   # name url sha256 dest
    local name=$1 url=$2 sha=$3 dest=$4
    if [[ -e "$dest/.fetched" ]]; then echo "$name: present"; return; fi
    local tmp; tmp=$(mktemp)
    echo "$name: downloading"
    wget -q -O "$tmp" "$url"
    local got; got=$(sha256sum "$tmp" | cut -d' ' -f1)
    if [[ "$got" != "$sha" ]]; then
        echo "$name: SHA-256 MISMATCH (expected $sha, got $got)" >&2
        rm -f "$tmp"; exit 1
    fi
    rm -rf "$dest"; mkdir -p "$dest"
    tar xzf "$tmp" -C "$dest"
    rm -f "$tmp"; touch "$dest/.fetched"
    echo "$name: ok"
}

fetch_commit() {    # name repo commit dest
    local name=$1 repo=$2 commit=$3 dest=$4
    if [[ -z "$commit" ]]; then
        echo "$name: no commit pinned. Run: git ls-remote $repo HEAD  and set it in $0" >&2
        exit 1
    fi
    if [[ -e "$dest/.fetched" ]] && [[ "$(git -C "$dest" rev-parse HEAD)" == "$commit" ]]; then
        echo "$name: present ($commit)"; return
    fi
    echo "$name: fetching $commit"
    rm -rf "$dest"; mkdir -p "$dest"
    git -C "$dest" init -q
    git -C "$dest" fetch -q --depth 1 "$repo" "$commit"
    git -C "$dest" checkout -q FETCH_HEAD
    touch "$dest/.fetched"
    echo "$name: ok"
}

fetch_tarball gcc-2.7.2-psx "$GCC_URL" "$GCC_SHA256" "$VENDOR/gcc-2.7.2-psx"
fetch_commit  maspsx "$MASPSX_REPO" "$MASPSX_COMMIT" "$VENDOR/maspsx"
fetch_commit  m2c    "$M2C_REPO"    "$M2C_COMMIT"    "$VENDOR/m2c"
fetch_commit  asm-differ "$ASMDIFF_REPO" "$ASMDIFF_COMMIT" "$VENDOR/asm-differ"

rm -f "$VENDOR/asm-differ/diff_settings.py"

echo "asm-differ: install its dependencies into your venv with:"
echo "  pip install colorama watchdog levenshtein cxxfilt"

if [[ -f "$VENDOR/m2c/requirements.txt" ]]; then
    echo "m2c: install its dependencies into your venv with:"
    echo "  pip install -r $VENDOR/m2c/requirements.txt"
fi