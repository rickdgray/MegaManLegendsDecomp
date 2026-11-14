#ifndef SOUND_H
#define SOUND_H

#include "common.h"
#include "psyq/libsnd.h"
#include "psyq/libcd.h"
#include "psyq/libgte.h"

#define SOUND_FLAG_MONO   0x0001
#define SOUND_FLAG_CD_OFF 0x8000

#define SOUND_DATA_BUF ((uint8 *)0x8013B000) // sound data loaded by comb reads (types 7, 8)
#define VAB_HEAD_BUF   ((uint8 *)0x8014B000) // VAB headers, one per Game_work.vab slot
#define VAB_HEAD_SIZE  0x1820

#define SOUND_CALL_MAX 24 // entries in the sound call queue (Sound_call_queue)

// SOUND_CALL.mode: what arg1/arg2 hold (calc_vol, voice_check)
#define SOUND_MODE_PAN 0 // Sound_call: arg1 = pan (-0x80..0x80), arg2 = attenuation (0..0x80)
#define SOUND_MODE_POS 1 // Sound_call2: arg1/arg2 = x/z of the source, panned against the player

// Sound_fade_flags: two bits per volume (1 = fade out, 2 = fade in), stepped by volume_update
#define SOUND_FADE_MVOL   0x03 // Sound_work.mvol_fade
#define SOUND_FADE_SE     0x0C // Sound_work.se_fade
#define SOUND_FADE_SEQ    0x30 // Sound_work.seq_fade
#define SOUND_FADE_SERIAL 0xC0 // Sound_work.serial_fade (fade out also pauses the CD: Cd_subcmd(0, 1, 0))

// CD/sound mixer state at 0x800AD140..0x800AD163 (0x24 bytes; 0x800AD164..67 is never accessed,
// and 0x800AD168 starts an unrelated buffer). Widths and signedness are from the load/store
// instructions. Each volume is scaled by its fade (0..0x7F, stepped by fade_step) in volume_update.
typedef struct
{
    uint8 unk00[2]; // 0x00: never accessed
    uint16 flags;   // 0x02: bit 0 = mono (see Cd_set_volume); bit 15 set by Cd_stop/cd_subcmd_mute.
        //       lhu/andi 0x8000 in volume_update, B644/B6FC/B89C/B7B4/CB7C, Cd_set_volume
    sint16 mvol;                     // 0x04: master volume (SsSetMVol)
    sint16 serial_vol;               // 0x06: CD input volume (SsSetSerialVol)
    sint16 se_vol;                   // 0x08: sound effect volume (calc_vol); init 0x40 in Sound_init
    sint16 seq_vol;                  // 0x0A: sequence volume (SsSeqSetVol/SsSepSetVol); init 0x64 in Sound_init
    sint16 mvol_fade;                // 0x0C: fade of mvol (SOUND_FADE_MVOL)
    sint16 serial_fade;              // 0x0E: fade of serial_vol (SOUND_FADE_SERIAL); also set by cd_cmd_xa_play
    sint16 se_fade;                  // 0x10: fade of se_vol (SOUND_FADE_SE)
    sint16 seq_fade;                 // 0x12: fade of seq_vol (SOUND_FADE_SEQ); set to 0x7F by Sound_seq_play/Sound_sep_play
    CdlATV atv;                      // 0x14: CD audio volume (val0..val3, bytes), applied with CdMix; Cd_set_volume
    sint8 reserved_voice;            // 0x18: voices for SsSetReservedVoice; init 0xF in Sound_init
    sint8 reserved_voice_set;        // 0x19: reserved_voice as last applied by volume_update
    uint8 reverb_state;              // 0x1A: volume_update: 0 = idle, 1 = waiting for reverb_timer
    uint8 reverb_timer;              // 0x1B: frames before the reverb depth is set (0x1E)
    struct SOUND_REVERB *reverb;     // 0x1C: reverb wanted (Sound_init, Sound_reverb_set)
    struct SOUND_REVERB *reverb_set; // 0x20: reverb as last applied by volume_update
} SOUND_WORK;

// A reverb preset of Sound_reverb_tbl, applied by volume_update.
typedef struct SOUND_REVERB
{
    uint8 type;  // 0x0: SsUtSetReverbType; 0 = off
    uint8 vol;   // 0x1: SsSetRVol
    uint8 depth; // 0x2: SsUtSetReverbDepth
    uint8 pad3;
} SOUND_REVERB;

// An entry of Sound_seq_tbl, filled by cd_cmd_read_comb's types 7 and 8.
typedef struct
{
    uint8 num;       // 0x0: number of the data loaded; a new number reloads it
    uint8 sep_count; // 0x1: type 8 (SEP) only: number of sequences, for SsSepOpen
    uint8 pad2[2];
    uint8 *data; // 0x4: in SOUND_DATA_BUF
} SOUND_DATA;

// A queued sound call, 0x14 bytes; Sound_call and Sound_call2 append one at Sound_call_ptr.
typedef struct
{
    uint8 mode; // 0x0: SOUND_MODE_PAN or SOUND_MODE_POS
    uint8 pad1;
    sint16 id;     // 0x2: index of Sound_call_info_tbl
    sint32 arg1;   // 0x4: see SOUND_MODE_*
    sint32 arg2;   // 0x8
    uint8 unkC[8]; // 0xC: untouched by the sound code
} SOUND_CALL;

// A sequence channel, an entry of Sound_seq_chan_tbl (8 bytes).
typedef struct
{
    sint16 access;  // 0x0: SsSeqOpen/SsSepOpen access number; -1 when unused
    sint8 kind;     // 0x2: 0 = SEQ, 1 = SEP, -1 = unused
    sint8 priority; // 0x3: priority of the sequence playing (low nibble of SOUND_CALL_INFO.unk2)
    uint8 seq_num;  // 0x4: SEP only: sequence number in the SEP
    uint8 playing;  // 0x5: SsIsEos result, stored by Sound_update
    sint16 id;      // 0x6: id of the SOUND_CALL playing
} SOUND_SEQ_CHAN;

// An entry of the table at Sound_call_info_tbl, 4 bytes.
typedef struct
{
    uint8 type; // 0x0: bits 0-5 = bank number (vab_find), bits 6-7 select the handler in Sound_call_func_tbl
    uint8 unk1; // 0x1: bits 0-6 = program number (tones) or sequence data number (seq_find); bit 7 = loop (SEP)
    uint8 unk2; // 0x2: high nibble = tone offset in the program or channel; low nibble = priority
    uint8 unk3; // 0x3: bits 0-4 = SPU voice or SEP sequence number, bits 5-6 = extra tones to play
} SOUND_CALL_INFO;

// One VAB header slot in VAB_HEAD_BUF, VAB_HEAD_SIZE bytes: VabHdr, 128 ProgAtr, then the tones (0x820)
typedef struct
{
    VabHdr hdr;         // 0x000
    ProgAtr prog[128];  // 0x020
    VagAtr tone[8][16]; // 8 programs of 16 tones
} VAB_HEAD;

typedef void (*SOUND_FUNC)(sint32);
typedef void (*SOUND_CALL_FUNC)(SOUND_CALL *call);

extern SOUND_WORK Sound_work;
extern SOUND_DATA Sound_seq_tbl[5];
extern SOUND_REVERB Sound_reverb_tbl[2]; // reverb presets selected by Sound_reverb_set
extern SOUND_FUNC Sound_stage_func_tbl[];
extern SOUND_SEQ_CHAN Sound_seq_chan_tbl[4];
extern SOUND_CALL *Sound_call_ptr;                  // next free sound call entry
extern SOUND_CALL Sound_call_queue[SOUND_CALL_MAX]; // the queue; Sound_call_ptr points into it
extern sint32 Sound_pitch_tbl_up[12];               // pitch_scale: scale table, positive exponents
extern sint32 Sound_pitch_tbl_down[12];             // pitch_scale: scale table, negative exponents
extern uint8 Sound_fade_step_size;                  // step used by fade_step
extern uint16 *Sound_stage_id_tbl[];                // per-stage sound call id lists, indexed by Game_work.unk051
extern SOUND_CALL_INFO Sound_call_info_tbl[];       // per-call-id info, indexed by SOUND_CALL.id
extern SOUND_CALL_FUNC Sound_call_func_tbl[3];
extern uint8 Sound_voice_priority[24]; // per-voice priority of the sound playing (low nibble of SOUND_CALL_INFO.unk2)
extern uint16 Sound_stage_slot_tbl[];  // Sound_stage_slot_set: per-stage sound ids
extern uint8 Sound_fade_flags;         // fade requests (SOUND_FADE_*); set by Sound_fade_start

// Per-stage sound call id lists (entries of Sound_stage_id_tbl, indexed by Game_work.unk051),
// rewritten by the stage's Sound_stage_func_tbl function.
extern uint16 D_8008220C[]; // stages 3 and 27
extern uint16 D_80082220[]; // stage 4
extern uint16 D_8008222C[]; // stage 5
extern uint16 D_80082274[]; // stage 10
extern uint16 D_80082278[]; // stage 12
extern uint16 D_8008229C[]; // stage 16
extern uint16 D_800822A8[]; // stage 17
extern uint16 D_800822C0[]; // stage 19
extern uint16 D_800822F0[]; // stage 25

// Unknown
extern uint32 D_80098958; // flags; 0x800 forces cd_cmd_read_comb to reload VAB bank 4
extern uint8 D_800C356E;  // like Game_work.unk050; stage whose sound is loaded?
extern uint8 D_800C356F;  // like Game_work.unk051
extern char D_800C1010[]; // SsSetTableSize work area

void Sound_stage_slot_set(sint32 which);
void Sound_stage_check(void);
void Sound_stage_play(void);
void Sound_init(void);
void Sound_reverb_set(sint32 idx);
void func_80019FB4(void);
void Sound_call(sint16 id, sint32 arg1, sint32 arg2);
void Sound_call2(sint16 id, SVECTOR *pos);
sint32 Sound_seq_is_eos(sint32 idx);
void Sound_update(void);
void Sound_call_play(SOUND_CALL *call);
void Sound_seq_play(SOUND_CALL *call);
void Sound_sep_play(SOUND_CALL *call);
void Sound_key_off_voice(sint16 voice);
void func_8001B314(void);
void Sound_seq_stop_all(void);

#endif // SOUND_H
