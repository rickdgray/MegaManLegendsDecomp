// PsyQ library routines that the port runs from the retail image.
//
// These touch only memory and the GTE, so the MIPS interpreter (port/runtime/mips_cpu.c) runs the
// retail code itself, with the software GTE: libgte's matrix, vector, lighting and trig routines
// (exact, with PsyQ's own tables), the pure libgpu packet builders, the CD position conversions,
// SetVideoMode and rand. Each entry below is a native function of the PsyQ name that hands its
// arguments to that code.
//
// This file is linked but not placed (port/tools/gen_link.py --scan): the retail bytes at these
// addresses must stay MIPS, so no jump is written over them, and the native symbol keeps its host
// address. Nothing in retail data points at these routines.
//
// Arguments: up to eight words are passed on (i386 cdecl puts every argument in its own stack
// word, and the MIPS ABI takes a0-a3 then sp+0x10..). Reading the words after a shorter
// argument list only reads the caller's frame.
#include "mips_cpu.h"
#include "psyq_alias.h"

#include <stdint.h>

#define EMULATED(name, addr)                                                                       \
    uint32_t name(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5,    \
                  uint32_t a6, uint32_t a7)                                                        \
    {                                                                                              \
        uint32_t args[8] = {a0, a1, a2, a3, a4, a5, a6, a7};                                       \
        return mips_call(addr, args);                                                              \
    }

// libgte: matrices and vectors
EMULATED(ApplyMatrix, 0x8007AD38)
EMULATED(ApplyMatrixLV, 0x8007A9B8)
EMULATED(ApplyMatrixSV, 0x8007AD88)
EMULATED(MulMatrix, 0x8007AB18)
EMULATED(MulMatrix0, 0x8007A8A8)
EMULATED(RotMatrix, 0x8007B5A8)
EMULATED(RotMatrixY, 0x8007BC68)
EMULATED(RotMatrixYXZ, 0x8007B838)
EMULATED(RotTrans, 0x8007B538)
EMULATED(ScaleMatrix, 0x8007ADE8)
EMULATED(TransposeMatrix, 0x8007B568)
EMULATED(OuterProduct0, 0x8007B4C4)
EMULATED(OuterProduct12, 0x8007B46C)
EMULATED(VectorNormal, 0x8007A6A8)
EMULATED(VectorNormalS, 0x8007A694)
EMULATED(SquareRoot0, 0x8007A578)
// libgte: GTE register setup and lighting
EMULATED(SetRotMatrix, 0x8007AF18)
EMULATED(SetTransMatrix, 0x8007AFA8)
EMULATED(SetLightMatrix, 0x8007AF48)
EMULATED(SetColorMatrix, 0x8007AF78)
EMULATED(SetBackColor, 0x8007B0D8)
EMULATED(SetFarColor, 0x8007B0F8)
EMULATED(SetFogNear, 0x8007A1CC)
EMULATED(SetGeomOffset, 0x8007B118)
EMULATED(SetGeomScreen, 0x8007B138)
EMULATED(NormalColorCol, 0x8007B24C)
// libgte: trigonometry with PsyQ's tables
EMULATED(rsin, 0x8007A060)
EMULATED(rcos, 0x8007A12C)
EMULATED(ccos, 0x8007A230)
EMULATED(catan, 0x8007A414)
EMULATED(ratan2, 0x8007BFA8)
// libgpu: packet and environment builders (they read the GPU type that ResetGraph stores)
EMULATED(GetTPage, 0x8007C478)
EMULATED(GetClut, 0x8007C4B4)
EMULATED(AddPrim, 0x8007C5A4)
EMULATED(SetDrawMode, 0x8007DF38)
EMULATED(SetDrawArea, 0x8007DE44)
EMULATED(SetDefDrawEnv, 0x8007C384)
EMULATED(SetDefDispEnv, 0x8007C43C)
// libetc
EMULATED(SetVideoMode, 0x80077748)
// libcd: position conversions
EMULATED(CdIntToPos, 0x80077E88)
EMULATED(CdPosToInt, 0x80077F8C)
// libc: PsyQ's generator, seed in retail data (renamed from rand by gen_link.py)
EMULATED(psyq_rand, 0x8007FE50)

PSYQ_SPLAT_ALIAS(func_8007B118, SetGeomOffset);
PSYQ_SPLAT_ALIAS(func_8007B138, SetGeomScreen);
PSYQ_SPLAT_ALIAS(func_80077748, SetVideoMode);

// Internal entries the native libgpu calls.
EMULATED(psyq_SetDrawEnv2, 0x8007E1A8)
