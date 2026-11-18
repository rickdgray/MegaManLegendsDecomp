# Mega Man Legends (USA, SLUS-00603) matching decompilation.
# The scripts in tools/ do the work; these targets run them in order. See README.md.

TARGETS := slus_006.03 rock_neo.exe
# One target per unique overlay code chunk, listed by tools/overlay_gen.py.
OVERLAYS := $(shell grep -vP '^\x23' tools/overlays.txt | cut -d' ' -f1)
CUE    := disc/image/Mega Man Legends (USA).cue
PY      := .venv/bin/python
# dumpsxiso from PATH, else one unpacked into tools/vendor/ (e.g. from a built AUR package)
DUMPSXISO ?= $(shell command -v dumpsxiso || echo tools/vendor/mkpsxiso/usr/bin/dumpsxiso)

.PHONY: all setup extract split build rebuild split-overlays overlays rebuild-overlays clean port-smoke port-compare \
	play install-desktop uninstall-desktop

all: split build

setup:
	./tools/fetch_tools.sh
	test -x $(PY) || uv venv .venv
	uv pip install --python .venv 'splat64[mips]' pyyaml colorama watchdog levenshtein cxxfilt \
		pynacl toml graphviz   # graphviz: m2c's one dependency (its pyproject.toml)
	@test -x "$(DUMPSXISO)" || echo "dumpsxiso missing: yay -S mkpsxiso-git"

# Extract the disc and check the two executables against retail.
extract:
	test -f "$(CUE)" || { echo "put your dump in disc/image/ (see README)"; exit 1; }
	$(DUMPSXISO) -x disc/extracted/ -s disc/mml.xml "$(CUE)"
	cd disc/extracted && sha1sum -c ../../checksums.sha1

split:
	for t in $(TARGETS); do ./tools/split.sh $$t || exit 1; done

# Each target must print MATCH.
build:
	for t in $(TARGETS); do ./tools/build.sh $$t || exit 1; done

# Split, build and refresh expected/ (after a rename or yaml change).
rebuild:
	for t in $(TARGETS); do ./tools/rebuild.sh $$t || exit 1; done

# The overlays. `make overlays` builds each one, stops at the first that doesn't print MATCH,
# then checks that the archives with a duplicate code chunk (ST03B, SUPPORT2, ...) hold the same
# bytes as the built target. Run `make split-overlays` first.
split-overlays:
	for t in $(OVERLAYS); do ./tools/split.sh $$t > /dev/null || exit 1; done

overlays:
	@for t in $(OVERLAYS); do \
		r=$$(./tools/build.sh $$t | tail -n 1); echo "$$t: $$r"; \
		[ "$$r" = MATCH ] || exit 1; \
	done
	$(PY) tools/overlay_gen.py check

rebuild-overlays:
	for t in $(OVERLAYS); do ./tools/rebuild.sh $$t > /dev/null || exit 1; done

# The native port: builds what is missing and starts the game in a
# window. ARGS go to the game, e.g. make play ARGS="--card1 ~/saves/mml.mcd".
play:
	./port/play.sh $(ARGS)

# The long headless smoke test (port/tests/smoke.script) on the game-paced clock: a new game by
# scripted input with memory checkpoints. Needs `make extract` and build/port.
# Settings and the memory card go to a temporary directory, never your own.
port-smoke:
	cmake -S port -B build/port -G Ninja >/dev/null && ninja -C build/port mml
	./port/tests/smoke.sh $(ARGS)

# The same script with the native overlay code and with every overlay function interpreted
# (PORT_OVERLAY_NATIVE=0): checkpoints, VRAM at fixed blanks and the sound must agree.
port-compare:
	cmake -S port -B build/port -G Ninja >/dev/null && ninja -C build/port mml
	./port/tests/compare.sh $(ARGS)

# A menu entry for `make play` (only when you run this; nothing installs it otherwise).
APPS := $(or $(XDG_DATA_HOME),$(HOME)/.local/share)/applications
install-desktop:
	mkdir -p "$(APPS)"
	sed -e 's|@PLAY@|$(CURDIR)/port/play.sh|' -e 's|@REPO@|$(CURDIR)|' \
		port/megaman-legends.desktop.in > "$(APPS)/megaman-legends.desktop"
	@echo "installed $(APPS)/megaman-legends.desktop"

uninstall-desktop:
	rm -f "$(APPS)/megaman-legends.desktop"

clean:
	rm -rf asm build expected
