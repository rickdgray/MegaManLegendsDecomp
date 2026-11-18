#!/usr/bin/env python3
"""Write the Teleport mod's destination list (port/mods/mod_teleport_dests.c) from the game's own
room exits.

Every stage module sets the scratchpad's exit-list pointer (*0x1F800050) from a table indexed by
room (`STAGE_MAP_WORK_PTR->exits = D_xxx[Game_work.value_51]` in src/r3_stXX/). Each list holds
0x18-byte records (CODE486_EXIT, include/rock_neo.exe/code_80048620.h), ended by id -1:

  +0 id, +2, +4, +6 stage, +7 room, +8 x y z rot (the exit cell), +0x10 x y z rot (arrival)

func_80050C2C copies a door's arrival position and facing into the room-entry request
(D_800C3558), so every record's arrival point is a place the game itself puts Mega Man when he
enters that room. This script reads each stage's original module (build/r3_stXX/original/, made
by tools/split.sh), collects every record's target stage/room and arrival point, drops the
placeholder records (target 00/00 with a zero arrival), merges duplicates, and writes them grouped
by stage with the names below. It writes coordinates only, never game data.

Usage: tools/teleport_dests.py [--list]   (--list prints the table instead of writing the file)
"""
import glob
import os
import re
import struct
import sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
OUT = os.path.join(ROOT, 'port', 'mods', 'mod_teleport_dests.c')
BASE = 0x80100000
STAGES = 0x1F

# Area names by stage, in the page's order (roughly the island's, town first). Capcom's debug list
# of stage names (in ROCK_NEO.EXE's data, unused by the game: "SHOPPING", "MAYOR", "KOYA MORI",
# "MOGU CHIKA", ...) gave the hints; each was checked by a headless teleport there and a look at
# the picture. Where only the debug name says what a place is, the name keeps it in brackets.
# Names: at most 22 characters.
AREAS = {
    0x04: 'Apple Market',
    0x05: 'City streets',
    0x08: 'Downtown',
    0x1C: 'Museum',
    0x0D: 'Harbour and boat',
    0x06: 'City Hall square',
    0x0F: 'City Hall buildings',
    0x19: 'Old City (factory)',
    0x1D: 'Uptown (night attack)',
    0x03: 'Cardon Forest, Flutter',
    0x1B: 'Cardon Forest 2',
    0x0C: 'Forest north',
    0x10: 'Huts (Koya Mori)',
    0x11: 'River forest',
    0x0A: 'Field (Mogura)',
    0x0B: 'Lake (Frog)',
    0x12: 'Main Gate',
    0x00: 'Opening ruin',
    0x09: 'Underground ruins',
    0x0E: 'Underground ruins 2',
    0x13: 'Ruins (Mogu Chika)',
    0x14: 'Ruins (Frog Chika)',
    0x1A: 'Main Gate ruins',
}

# Short area names for "from ..." (at most 12 characters); the area name when absent.
SHORT = {
    0x04: 'Apple Market',
    0x05: 'City streets',
    0x06: 'City Hall',
    0x0F: 'City Hall 2',
    0x19: 'Old City',
    0x1D: 'Uptown',
    0x03: 'Cardon',
    0x1B: 'Cardon 2',
    0x0C: 'Forest north',
    0x10: 'Huts',
    0x11: 'River forest',
    0x0A: 'Mogura',
    0x0B: 'Lake',
    0x09: 'Underground',
    0x0E: 'Underground2',
    0x13: 'Mogu Chika',
    0x14: 'Frog Chika',
    0x1A: 'Gate ruins',
}

# Rooms with a name of their own (stage, room) -> name (at most 13 characters).
ROOMS = {
    (0x03, 0x05): 'Cabin 1',
    (0x03, 0x06): 'Cabin 2',
    (0x03, 0x07): 'Flutter hall',
    (0x03, 0x08): 'Lounge',
    (0x1B, 0x05): 'Cabin 1',
    (0x1B, 0x06): 'Cabin 2',
    (0x1B, 0x07): 'Flutter hall',
    (0x1B, 0x08): 'Lounge',
    (0x04, 0x01): 'Shop 1',
    (0x04, 0x02): 'Shop 2',
    (0x04, 0x03): 'Shop 3',
    (0x04, 0x04): 'Shop 4',
    (0x04, 0x05): 'Shop 5',
    (0x05, 0x02): 'Shop',
    (0x05, 0x04): 'Restaurant',
    (0x08, 0x01): 'Hospital hall',
    (0x08, 0x05): 'Ward',
    (0x0D, 0x00): 'Harbour',
    (0x0D, 0x01): 'Boat cabin',
    (0x10, 0x01): 'Hut 1',
    (0x10, 0x02): 'Hut 2',
    (0x10, 0x03): 'Hut 3',
    (0x10, 0x04): 'Hut 4',
    (0x10, 0x05): 'Hut 5',
}

# Destinations that loaded in the sweep but do something else (stage, room) -> a note for the page
# (at most 30 characters). The sweep started from the opening ruin, the earliest story state.
UNSTABLE = {
    (0x03, 0x01): 'Early on a story scene plays',
    (0x05, 0x00): 'Early on a story scene plays',
    (0x1D, 0x00): 'A story battle (night attack)',
    (0x1D, 0x01): 'A story battle (night attack)',
    (0x1D, 0x02): 'A story battle (night attack)',
}

# Arrival points left out: (stage, room, x, z) -> why.
SKIP = {
    # City streets room 1's exit to the Apple Market at the Downtown gate's cell: Mega Man
    # arrives over no floor and falls out of the world (sweep, 2026-11-17).
    (0x04, 0x00, -3584, 512): 'no floor',
}


def area_name(stage):
    return AREAS.get(stage, 'Stage %02X' % stage)


def room_name(stage, room):
    return ROOMS.get((stage, room), 'Room %02X' % room)


def table_addr(stage):
    for path in glob.glob(os.path.join(ROOT, 'src', 'r3_st%02x' % stage, '*.c')):
        m = re.search(r'(?:exits|EXITS)\s*=\s*D_([0-9A-F]+)\[', open(path).read())
        if m:
            return int(m.group(1), 16)
    sys.exit('stage %02X: no exit table found in src/' % stage)


def table_len(stage, addr):
    for path in glob.glob(os.path.join(ROOT, 'asm', 'r3_st%02x' % stage, 'data', '*.s')):
        m = re.search(r'dlabel D_%X\n(.*?)enddlabel' % addr, open(path).read(), re.S)
        if m:
            return len(re.findall(r'\.word', m.group(1)))
    sys.exit('stage %02X: table D_%X not in asm/ (run tools/split.sh)' % (stage, addr))


def exits():
    """Yields (from stage, from room, record dict) for every exit record of every stage."""
    for stage in range(STAGES):
        path = os.path.join(ROOT, 'build', 'r3_st%02x' % stage, 'original', 'r3_st%02x.bin' % stage)
        data = open(path, 'rb').read()
        addr = table_addr(stage)
        for room in range(table_len(stage, addr)):
            p = struct.unpack_from('<I', data, addr - BASE + 4 * room)[0] - BASE
            while True:
                f = struct.unpack_from('<hhhBBhhhhhhhh', data, p)
                if f[0] == -1:
                    break
                yield stage, room, dict(stage=f[3], room=f[4], x=f[9], y=f[10], z=f[11], rot=f[12] & 0xFFF)
                p += 0x18


def collect():
    dests = {}
    for fs, fr, e in exits():
        if e['stage'] == 0 and e['room'] == 0 and e['x'] == 0 and e['z'] == 0:
            continue  # placeholder (falls and other cells handled elsewhere)
        if (e['stage'], e['room'], e['x'], e['z']) in SKIP:
            continue
        key = (e['stage'], e['room'], e['x'], e['y'], e['z'])
        for k in dests:
            # Two doors of one doorway (a wide door has an exit per cell) arrive a cell apart.
            if k[:2] == key[:2] and abs(k[2] - key[2]) <= 512 and abs(k[4] - key[4]) <= 512 and \
                    abs(k[3] - key[3]) <= 256:
                key = k
                break
        if key not in dests:
            dests[key] = dict(e, sources=[])
        if (fs, fr) not in dests[key]['sources']:
            dests[key]['sources'].append((fs, fr))
    return dests


def label(d):
    fs, fr = d['sources'][0]
    if fs == d['stage']:
        src = room_name(fs, fr)
    else:
        src = SHORT.get(fs, area_name(fs))
    return '%s from %s' % (room_name(d['stage'], d['room']), src)


def main():
    dests = collect()
    by_stage = {}
    for d in dests.values():
        by_stage.setdefault(d['stage'], []).append(d)
    named = list(AREAS)
    order = sorted(by_stage, key=lambda s: (named.index(s) if s in named else len(named), s))
    lines = []
    areas = []
    for s in order:
        first = len(lines)
        rows = sorted(by_stage[s], key=lambda d: (d['room'], label(d), d['x'], d['z']))
        seen = {}
        for d in rows:
            # Several doors between the same two rooms: number them (west to east, then north).
            name = label(d)
            seen[name] = seen.get(name, 0) + 1
            if seen[name] > 1 or sum(1 for e in rows if label(e) == name) > 1:
                name = '%s #%d' % (name, seen[name])
            note = UNSTABLE.get((d['stage'], d['room']))
            lines.append('    {0x%02X, 0x%02X, %d, %d, %d, 0x%03X, "%s", %s},' % (
                d['stage'], d['room'], d['x'], d['y'], d['z'], d['rot'], name,
                '"%s"' % note if note else 'NULL'))
        areas.append('    {"%s", 0x%02X, %d, %d},' % (area_name(s), s, first, len(lines) - first))
    if '--list' in sys.argv:
        print('\n'.join(areas))
        print('\n'.join(lines))
        return
    with open(OUT, 'w') as f:
        f.write('// Generated by tools/teleport_dests.py from the stage modules\' room exits; do not edit.\n')
        f.write('// Each line: stage, room, arrival x, y, z, facing, name, warning (NULL: none).\n')
        f.write('#include "mod_teleport.h"\n\n#include <stddef.h>\n\n')
        f.write('const TP_DEST tp_dests[] = {\n%s\n};\n\n' % '\n'.join(lines))
        f.write('const TP_AREA tp_areas[] = {\n%s\n};\n\n' % '\n'.join(areas))
        f.write('const int tp_area_count = %d;\n' % len(areas))
    print('%s: %d destinations in %d areas' % (os.path.relpath(OUT, ROOT), len(lines), len(areas)))


if __name__ == '__main__':
    main()
