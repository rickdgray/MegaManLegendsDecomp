// PsyQ libsnd and libspu for the native port: the retail library itself.
//
// The sound library is pure software on top of the SPU's registers and DMA channel 4, so the
// port runs the retail code from the image with the MIPS interpreter (port/runtime/mips_cpu.c),
// and the interpreter's hardware-register accesses go to the software SPU (port/runtime/spu.c,
// via psx_io.c). Everything libsnd does is then exactly the console's: VAB headers and bodies
// (SsVabOpenHeadSticky, SsVabTransBodyPartly by DMA), voice allocation, the SEQ/SEP sequencer and
// its tick (hooked to the vertical blank by SsStart through InterruptCallback, port/psyq/libetc.c),
// reverb set-up, and the key-on/key-off calls the game makes for its sound effects.
//
// Like psyq_emulated.c, this file is linked but not placed: the retail bytes stay MIPS, and each
// entry below is a native function of the library's name that hands its arguments over. The
// parameters are typed so a narrow argument reaches the MIPS code extended as the MIPS ABI would.
#include "mips_cpu.h"
#include "psyq_alias.h"

#include <stdint.h>

#define ARGS(...) uint32_t a[8] = {__VA_ARGS__}

#define CALL(addr) mips_call((addr), a)

#define S(x) ((uint32_t)(int32_t)(x))   // signed narrow argument
#define U(x) ((uint32_t)(x))            // unsigned argument
#define P(x) ((uint32_t)(uintptr_t)(x)) // pointer argument

// libspu
void SpuSetEnv(void *env)
{
    ARGS(P(env));
    CALL(0x80069994);
}
void SpuSetKey(int32_t on, uint32_t voices)
{
    ARGS(S(on), U(voices));
    CALL(0x8006A724);
}
void SpuSetKeyOnWithAttr(void *attr)
{
    ARGS(P(attr));
    CALL(0x8006A9B4);
}
int32_t SpuGetKeyStatus(uint32_t voice)
{
    ARGS(U(voice));
    return (int32_t)CALL(0x8006A920);
}

// libsnd: set-up
void SsInit(void)
{
    ARGS(0);
    CALL(0x8006B594);
}
void SsSetTableSize(void *table, int32_t s_max, int32_t t_max)
{
    ARGS(P(table), S(s_max), S(t_max));
    CALL(0x80070264);
}
void SsSetTickMode(int32_t mode)
{
    ARGS(S(mode));
    CALL(0x8007043C);
}
void SsStart(void)
{
    ARGS(0);
    CALL(0x8006EC6C);
}
void SsSetReservedVoice(uint8_t voices)
{
    ARGS(U(voices));
    CALL(0x80075AC8);
}
void SsSetMVol(int16_t l, int16_t r)
{
    ARGS(S(l), S(r));
    CALL(0x8006E8B4);
}
void SsSetRVol(int16_t l, int16_t r)
{
    ARGS(S(l), S(r));
    CALL(0x8006E904);
}
void SsSetSerialAttr(int8_t s, int8_t attr, int8_t mode)
{
    ARGS(S(s), S(attr), S(mode));
    CALL(0x8006E48C);
}
void SsSetSerialVol(int8_t s, int16_t l, int16_t r)
{
    ARGS(S(s), S(l), S(r));
    CALL(0x80070168);
}
void SsUtSetReverbType(int16_t type)
{
    ARGS(S(type));
    CALL(0x80071FE0);
}
void SsUtSetReverbDepth(int16_t l, int16_t r)
{
    ARGS(S(l), S(r));
    CALL(0x80071F48);
}
void SsUtReverbOn(void)
{
    ARGS(0);
    CALL(0x800721C4);
}
void SsSetMono(void)
{
    ARGS(0);
    CALL(0x80075AA4);
}
void SsSetStereo(void)
{
    ARGS(0);
    CALL(0x80075AB8);
}
void SsUtAllKeyOff(int16_t mode)
{
    ARGS(S(mode));
    CALL(0x80070974);
}

// libsnd: sound banks
int16_t SsVabOpenHeadSticky(uint8_t *head, int16_t vab, uint32_t sbaddr)
{
    ARGS(P(head), S(vab), U(sbaddr));
    return (int16_t)CALL(0x80075F30);
}
int16_t SsVabTransBodyPartly(uint8_t *buf, uint32_t size, int16_t vab)
{
    ARGS(P(buf), U(size), S(vab));
    return (int16_t)CALL(0x80076634);
}
int16_t SsVabTransCompleted(int16_t mode)
{
    ARGS(S(mode));
    return (int16_t)CALL(0x800768AC);
}
void SsVabClose(int16_t vab)
{
    ARGS(S(vab));
    CALL(0x80075AF8);
}
uint32_t SsUtGetVagAddr(int16_t vab, int16_t vag)
{
    ARGS(S(vab), S(vag));
    return CALL(0x80070DD8);
}
void SsUtKeyOffV(int16_t voice)
{
    ARGS(S(voice));
    CALL(0x80071220);
}

// libsnd: sequences
int16_t SsSeqOpen(uint32_t *addr, int16_t vab)
{
    ARGS(P(addr), S(vab));
    return (int16_t)CALL(0x8006DC94);
}
int16_t SsSepOpen(uint32_t *addr, int16_t vab, int16_t seps)
{
    ARGS(P(addr), S(vab), S(seps));
    return (int16_t)CALL(0x8006B664);
}
void SsSeqPlay(int16_t seq, int8_t mode, int16_t count)
{
    ARGS(S(seq), S(mode), S(count));
    CALL(0x8006E300);
}
void SsSepPlay(int16_t seq, int16_t sep, int8_t mode, int16_t count)
{
    ARGS(S(seq), S(sep), S(mode), S(count));
    CALL(0x8006E338);
}
void SsSeqClose(int16_t seq)
{
    ARGS(S(seq));
    CALL(0x8006B464);
}
void SsSepClose(int16_t seq)
{
    ARGS(S(seq));
    CALL(0x8006B488);
}
void SsSeqStop(int16_t seq)
{
    ARGS(S(seq));
    CALL(0x80070114);
}
void SsSepStop(int16_t seq, int16_t sep)
{
    ARGS(S(seq), S(sep));
    CALL(0x8007013C);
}
void SsSeqSetVol(int16_t seq, int16_t l, int16_t r)
{
    ARGS(S(seq), S(l), S(r));
    CALL(0x80070634);
}
void SsSepSetVol(int16_t seq, int16_t sep, int16_t l, int16_t r)
{
    ARGS(S(seq), S(sep), S(l), S(r));
    CALL(0x80070694);
}
int16_t SsIsEos(int16_t seq, int16_t sep)
{
    ARGS(S(seq), S(sep));
    return (int16_t)CALL(0x8006B624);
}

PSYQ_SPLAT_ALIAS(func_8006B594, SsInit);
PSYQ_SPLAT_ALIAS(func_800721C4, SsUtReverbOn);
PSYQ_SPLAT_ALIAS(func_80075AA4, SsSetMono);
PSYQ_SPLAT_ALIAS(func_80075AB8, SsSetStereo);
PSYQ_SPLAT_ALIAS(func_80070974, SsUtAllKeyOff);
PSYQ_SPLAT_ALIAS(func_80070114, SsSeqStop);
PSYQ_SPLAT_ALIAS(func_8007013C, SsSepStop);
PSYQ_SPLAT_ALIAS(func_80070634, SsSeqSetVol);
PSYQ_SPLAT_ALIAS(func_80070694, SsSepSetVol);
