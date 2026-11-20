# Mega Man Legends (USA, SLUS-00603) decompilation.
# The scripts in tools/ do the work; these targets run them in order. See README.md.

TARGETS  := slus_006.03 rock_neo.exe
# One target per unique overlay code chunk (tools/overlays.txt, from tools/overlay_gen.py).
OVERLAYS := $(shell grep -v '^\#' tools/overlays.txt | cut -d' ' -f1)
CUE      := disc/image/Mega Man Legends (USA).cue
PY       := .venv/bin/python
DUMPSXISO ?= dumpsxiso

.PHONY: all setup extract split build rebuild split-overlays overlays rebuild-overlays

all: split build

setup:
	bash tools/fetch_tools.sh

# Extract the disc into disc/extracted/ (game data, gitignored).
extract:
	test -f "$(CUE)" || { echo "put your dump in disc/image/ (see README)"; exit 1; }
	$(DUMPSXISO) -x disc/extracted/ -s mml.xml "$(CUE)"

split:
	for t in $(TARGETS); do bash tools/split.sh $$t || exit 1; done

# Each target must print MATCH.
build:
	for t in $(TARGETS); do bash tools/build.sh $$t || exit 1; done

# Split, build and refresh expected/ (after a rename or yaml change).
rebuild:
	for t in $(TARGETS); do bash tools/rebuild.sh $$t || exit 1; done

# The overlays (stage, weapon and shop code in CDDATA/DAT/*.BIN). `make overlays` builds each one,
# stops at the first that doesn't print MATCH, then checks that the archives holding a duplicate
# code chunk (ST03B, SUPPORT2, ...) contain the same bytes as the built target.
split-overlays:
	for t in $(OVERLAYS); do bash tools/split.sh $$t > /dev/null || exit 1; done

overlays:
	@for t in $(OVERLAYS); do \
		r=$$(bash tools/build.sh $$t | tail -n 1); echo "$$t: $$r"; \
		[ "$$r" = MATCH ] || exit 1; \
	done
	$(PY) tools/overlay_gen.py check

rebuild-overlays:
	for t in $(OVERLAYS); do bash tools/rebuild.sh $$t > /dev/null || exit 1; done
