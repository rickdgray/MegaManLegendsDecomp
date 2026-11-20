# Mega Man Legends (USA, SLUS-00603) decompilation.
# The scripts in tools/ do the work; these targets run them. See README.md.
# Each tool also takes a single target or a group: tools/build.sh r3_st05, tools/split.sh overlays.

.PHONY: all setup extract split build rebuild

all: split build

# The pinned third-party tools (tools/vendor/).
setup:
	bash tools/fetch_tools.sh

# Once, in a fresh clone: the disc's files, the overlays' code chunks, and a check of every hash.
extract:
	bash tools/extract.sh

# Every target: the two executables and the 44 overlays.
split:
	bash tools/split.sh all

# One MATCH line per target; fails if any doesn't match.
build:
	bash tools/build.sh all

# Split, build and refresh expected/ for every target (after a rename or yaml change).
rebuild:
	bash tools/rebuild.sh all
