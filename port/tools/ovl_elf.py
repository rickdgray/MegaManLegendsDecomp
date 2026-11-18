"""Minimal ELF32 little-endian reader for the overlay tools (no third-party modules).

Reads the matching build's overlay ELFs (build/r3_*/r3_*.elf): symbols with their values, sizes,
types and sections, and the bytes of the allocated section that holds the overlay image.
"""

import struct

STT = {0: "NOTYPE", 1: "OBJECT", 2: "FUNC", 3: "SECTION", 4: "FILE"}
STB = {0: "LOCAL", 1: "GLOBAL", 2: "WEAK"}
SHN_ABS = 0xFFF1


class Elf:
    def __init__(self, path):
        with open(path, "rb") as f:
            self.data = f.read()
        d = self.data
        if d[:4] != b"\x7fELF" or d[4] != 1 or d[5] != 1:
            raise ValueError("%s: not a 32-bit little-endian ELF" % path)
        shoff, = struct.unpack_from("<I", d, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 0x2E)
        self.sections = []
        for i in range(shnum):
            name, kind, flags, addr, off, size, link, info, align, entsize = struct.unpack_from(
                "<IIIIIIIIII", d, shoff + i * shentsize)
            self.sections.append({"name_off": name, "type": kind, "flags": flags, "addr": addr,
                                  "off": off, "size": size, "link": link, "entsize": entsize})
        strtab = self.sections[shstrndx]
        for s in self.sections:
            s["name"] = self._str(strtab["off"], s["name_off"])
        self.symbols = []
        for s in self.sections:
            if s["type"] != 2:  # SHT_SYMTAB
                continue
            names = self.sections[s["link"]]
            for j in range(s["size"] // 16):
                name, value, size, info, other, shndx = struct.unpack_from(
                    "<IIIBBH", d, s["off"] + j * 16)
                self.symbols.append({
                    "name": self._str(names["off"], name),
                    "value": value,
                    "size": size,
                    "type": STT.get(info & 0xF, str(info & 0xF)),
                    "bind": STB.get(info >> 4, str(info >> 4)),
                    "abs": shndx == SHN_ABS,
                    "shndx": shndx,
                })

    def _str(self, base, off):
        end = self.data.index(b"\0", base + off)
        return self.data[base + off:end].decode("latin-1")

    def image(self):
        """(load address, bytes) of the one allocated PROGBITS section (the overlay image)."""
        progbits = [s for s in self.sections if s["type"] == 1 and s["flags"] & 2]
        if len(progbits) != 1:
            raise ValueError("expected one allocated section, found %d" % len(progbits))
        s = progbits[0]
        return s["addr"], self.data[s["off"]:s["off"] + s["size"]]


FNV_OFFSET = 0xCBF29CE484222325
FNV_PRIME = 0x100000001B3


def hash_ranges(image_base, image, ranges):
    """64-bit FNV-1a over little-endian words of each (addr, size) range, in order.

    port/runtime/overlay.c computes the same over PS1 RAM; sizes are multiples of 4."""
    h = FNV_OFFSET
    for addr, size in ranges:
        off = addr - image_base
        if off < 0 or off + size > len(image):
            return None
        for i in range(0, size, 4):
            w, = struct.unpack_from("<I", image, off + i)
            h = ((h ^ w) * FNV_PRIME) & 0xFFFFFFFFFFFFFFFF
    return h
