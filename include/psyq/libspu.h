#ifndef PSYQ_LIBSPU_H
#define PSYQ_LIBSPU_H

/*
 * Self-written declarations for the PsyQ libspu types and functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

#define SPU_OFF 0
#define SPU_ON  1

#define SPU_ENV_EVENT_QUEUEING (1 << 0)

// SpuVoiceAttr.mask bits
#define SPU_VOICE_VOLL        (1 << 0)
#define SPU_VOICE_VOLR        (1 << 1)
#define SPU_VOICE_VOLMODEL    (1 << 2)
#define SPU_VOICE_VOLMODER    (1 << 3)
#define SPU_VOICE_PITCH       (1 << 4)
#define SPU_VOICE_NOTE        (1 << 5)
#define SPU_VOICE_SAMPLE_NOTE (1 << 6)
#define SPU_VOICE_WDSA        (1 << 7)
#define SPU_VOICE_ADSR_AMODE  (1 << 8)
#define SPU_VOICE_ADSR_SMODE  (1 << 9)
#define SPU_VOICE_ADSR_RMODE  (1 << 10)
#define SPU_VOICE_ADSR_AR     (1 << 11)
#define SPU_VOICE_ADSR_DR     (1 << 12)
#define SPU_VOICE_ADSR_SR     (1 << 13)
#define SPU_VOICE_ADSR_RR     (1 << 14)
#define SPU_VOICE_ADSR_SL     (1 << 15)
#define SPU_VOICE_LSAX        (1 << 16)
#define SPU_VOICE_ADSR_ADSR1  (1 << 17)
#define SPU_VOICE_ADSR_ADSR2  (1 << 18)

typedef struct
{
    short left;
    short right;
} SpuVolume;

// 0x40 bytes (0x3E of members, padded to u_long alignment)
typedef struct
{
    u_long voice;        // 0x00: voice bit mask
    u_long mask;         // 0x04: which of the fields below are valid
    SpuVolume volume;    // 0x08
    SpuVolume volmode;   // 0x0C
    SpuVolume volumex;   // 0x10
    u_short pitch;       // 0x14
    u_short note;        // 0x16
    u_short sample_note; // 0x18
    short envx;          // 0x1A
    u_long addr;         // 0x1C: waveform start address
    u_long loop_addr;    // 0x20
    long a_mode;         // 0x24
    long s_mode;         // 0x28
    long r_mode;         // 0x2C
    u_short ar;          // 0x30
    u_short dr;          // 0x32
    u_short sr;          // 0x34
    u_short rr;          // 0x36
    u_short sl;          // 0x38
    u_short adsr1;       // 0x3A
    u_short adsr2;       // 0x3C
} SpuVoiceAttr;

typedef struct
{
    u_long mask;
    u_long queueing;
} SpuEnv;

void SpuInit(void);
void SpuQuit(void);
void SpuSetEnv(SpuEnv *env);
long SpuGetKeyStatus(unsigned long voice_bit);
void SpuSetKeyOnWithAttr(SpuVoiceAttr *attr);
void SpuSetKey(long on_off, u_long voice_bit);

#endif // PSYQ_LIBSPU_H
