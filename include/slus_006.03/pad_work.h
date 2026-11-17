#ifndef PAD_WORK_H
#define PAD_WORK_H

// The shim's PAD_WORK (ROCK_NEO's adds the auto-repeat state: include/rock_neo.exe/pad_work.h).
// Included by pad.h, after PAD_FLAGS; include pad.h, not this file.

// Per-controller state. The first 8 bytes are the raw buffer given to InitPAD.
// Every member is a byte (or a bit field): the target copies the struct with lwl/lwr and reaches
// the flag bits with byte accesses, which a 2-aligned struct would not give. Wider fields are
// read through the PAD_* accessors in pad.h.
typedef struct
{
    uint8 status;        // 0x00 0xFF = no controller
    uint8 id;            // 0x01 high nibble = controller type
    uint8 raw[2];        // 0x02 buttons, active low
    uint8 analog[4];     // 0x04
    uint8 unk08[0x1C];   // 0x08
    uint8 type;          // 0x24 0xFF = no controller
    PAD_FLAGS flags;     // 0x25
    uint8 now[2];        // 0x26 buttons held this frame
    uint8 old[2];        // 0x28 buttons held last frame
    uint8 on[2];         // 0x2A buttons pressed this frame
    uint8 off[2];        // 0x2C buttons released this frame
    uint8 unk2E[2];      // 0x2E
    uint8 analog_cpy[4]; // 0x30
    uint8 unk34[2];      // 0x34 InitPAD's caller stores 0x4001 here with one word store
    uint8 unk36;         // 0x36
    uint8 unk37;         // 0x37
} PAD_WORK;              // 0x38 (Joy1 and Joy2 are 0x158 apart)

#endif // PAD_WORK_H
