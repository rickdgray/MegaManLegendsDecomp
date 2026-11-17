#ifndef PAD_WORK_H
#define PAD_WORK_H

// ROCK_NEO's PAD_WORK: the shim's layout (include/slus_006.03/pad_work.h) with the auto-repeat
// state inserted at 0x38, which is why Joy1 and Joy2 are 0x168 apart here and 0x158 in the shim.
// Included by pad.h, after PAD_FLAGS; include pad.h, not this file.

// Per-controller state. The first 8 bytes are the raw buffer given to InitPAD. All bytes, as in
// the shim. Wider fields are read through the PAD_* accessors in pad.h.
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
    uint8 rep_state[8];  // 0x38 per button (Pad_repeat_update): 0 idle, 1 first press, 2 repeating
    uint8 rep_count[8];  // 0x40 frames held
} PAD_WORK;              // 0x48 (Joy1 and Joy2 are 0x168 apart)

#define PAD_REP_OUT(p) (*(uint16 *)(p)->unk2E) // auto-repeat output bits

#endif // PAD_WORK_H
