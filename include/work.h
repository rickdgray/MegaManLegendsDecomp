#ifndef WORK_H
#define WORK_H

// The header shared by every work pool slot (ROCK_NEO's pools, Work_pools_init in code_8002E7A8.c)
// and the player's PL_WORK, in ROCK_NEO's structs and in every overlay's views of them. Capcom's
// names where known (em1c in eve19.c, the shot 0x38 code):
// - 0x00 be_flag (Capcom's): status bits, below. Bit 6: Model_parts_draw and func_8002831C skip
//   their distance cull while the object is nearer than Scratch_fog_0; bit 7: set by W48_80_WORK's
//   variant_E.
// - 0x01 work_id (Capcom's): pool kind (0x10 * pool number) | slot index.
// - 0x02 id (Capcom's): the kind, the first index of the pool's handler table.
// - 0x03 type (Capcom's): the kind's variant.
// - 0x06 flags: set to 3 on open, bits 0-1 changed by func_8002F3A8, bit 5 keeps the slot alive in
//   func_8002F420 (moved instead of closed), bit 6 set by func_80033500/func_8003354C.
// - 0x08 routine_0 to routine_3 (Capcom's): the state, cleared by one word store on open. Some
//   kinds also use routine_2 or routine_3 as a timer or value (see each struct).
// - 0x0C work_0 to work_3 (Capcom's): the kind's bytes, set from the spawn record.

// Bits of be_flag (Capcom's names). MOVE: live, the pool update runs the slot (with bit 0 of
// flags). MODEL: a model, so the slot's EFC is EFC_MODEL (Capcom sets TRANS | MODEL before
// Model_work_init).
#define MOVE  0x01
#define TRANS 0x02
#define MODEL 0x04

#endif
