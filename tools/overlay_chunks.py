#!/usr/bin/env python3
"""List or extract the chunks of a CDDATA/DAT/*.BIN archive.

Each chunk starts on a 0x800 boundary with a one-sector header:
  +0x00 type (0 = raw data loaded at +0x0C, code chunks included; 0xFFFFFFFF = end of archive)
  +0x04 size of the contents in bytes
  +0x08 sectors from this header to the next one (header included)
  +0x0C load address (type 0) or type-specific value
  +0x10 type-specific words (TIM: VRAM placement; VAB: SPU parameters)
  +0x40 source file name, null-terminated
Some types don't follow +0x08 when walking the archive:
  - 9 and 0xA are header-only entries (one sector, no contents follow), although +0x08 holds
    the sector count of the image they describe;
  - 4 (CLUT, .CLT) is header-only too: its colors sit inside the header sector;
  - 1 (TIM image) keeps its CLUT inside the header sector (at +0x100; +0x14 colors per CLUT,
    +0x18 CLUT count), and only the pixel data follows: size - 0x20 - CLUT bytes.

Usage:
  overlay_chunks.py list <file.BIN> [...]          one line per chunk
  overlay_chunks.py code <file.BIN> [...]          code chunks only (name under progbin)
  overlay_chunks.py extract <file.BIN> <index|name> <out>
Output paths must be under build/ or a scratch folder: chunk contents are game data.
"""
import hashlib
import os
import struct
import sys

SECTOR = 0x800
END = 0xFFFFFFFF
HEADER_ONLY = (4, 9, 0xA)


class Chunk:
    def __init__(self, index, offset, ctype, size, sectors, addr, extra, name):
        self.index = index
        self.offset = offset
        self.type = ctype
        self.size = size
        self.sectors = sectors
        self.addr = addr
        self.extra = extra
        self.name = name

    @property
    def is_code(self):
        return self.type == 0 and "progbin" in self.name.lower()

    @property
    def body_size(self):
        """Bytes that follow the header sector."""
        if self.type in HEADER_ONLY:
            return 0
        if self.type == 1:
            return self.size - 0x20 - self.extra[1] * self.extra[2] * 2
        return self.size

    @property
    def step(self):
        """Sectors from this header to the next."""
        if self.type in (1,) + HEADER_ONLY:
            return 1 + (self.body_size + SECTOR - 1) // SECTOR
        return self.sectors

    def contents(self, data):
        start = self.offset + SECTOR
        return data[start : start + self.body_size]


def read_chunks(data):
    chunks = []
    offset = 0
    while offset + SECTOR <= len(data):
        ctype, size, sectors, addr = struct.unpack_from("<4I", data, offset)
        if ctype == END:
            break
        extra = struct.unpack_from("<12I", data, offset + 0x10)
        name = data[offset + 0x40 : offset + SECTOR].split(b"\0")[0].decode("latin-1")
        chunks.append(Chunk(len(chunks), offset, ctype, size, sectors, addr, extra, name))
        if chunks[-1].step == 0:
            raise ValueError("chunk at 0x%X has a zero sector count" % offset)
        offset += chunks[-1].step * SECTOR
    else:
        raise ValueError("no end marker")
    return chunks, offset


def cmd_list(paths, code_only):
    for path in paths:
        data = open(path, "rb").read()
        chunks, end = read_chunks(data)
        print("%s  (%d chunks, end marker at 0x%X, file 0x%X)" % (path, len(chunks), end, len(data)))
        for c in chunks:
            if code_only and not c.is_code:
                continue
            body = c.contents(data)
            sha = hashlib.sha1(body).hexdigest() if c.is_code else ""
            line = "  %3d  0x%06X  type %-2X size 0x%06X  sectors %3d  addr 0x%08X  %s  %s" % (
                c.index, c.offset, c.type, c.size, c.sectors, c.addr, c.name, sha)
            print(line.rstrip())


def cmd_extract(path, which, out):
    data = open(path, "rb").read()
    chunks, _ = read_chunks(data)
    if which.isdigit():
        chunk = chunks[int(which)]
    else:
        matches = [c for c in chunks if c.name.lower().endswith(which.lower())]
        if len(matches) != 1:
            sys.exit("%s: %d chunks match %r" % (path, len(matches), which))
        chunk = matches[0]
    os.makedirs(os.path.dirname(out) or ".", exist_ok=True)
    with open(out, "wb") as f:
        f.write(chunk.contents(data))
    print("%s: chunk %d (%s, 0x%X bytes, addr 0x%08X) -> %s"
          % (path, chunk.index, chunk.name, chunk.size, chunk.addr, out))


def main():
    if len(sys.argv) >= 3 and sys.argv[1] in ("list", "code"):
        cmd_list(sys.argv[2:], sys.argv[1] == "code")
    elif len(sys.argv) == 5 and sys.argv[1] == "extract":
        cmd_extract(*sys.argv[2:])
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main()
