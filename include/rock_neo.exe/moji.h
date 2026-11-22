#ifndef MOJI_H
#define MOJI_H

#include "common.h"
#include "psyq/libgte.h"

// Number of Moji_work entries (MojiTaskKill clears 5 entries of 0xC4 bytes).
#define MOJI_WORK_MAX 5

// One entry of the message (text) work array Moji_work (0xC4 bytes each: func_80053B40 walks the
// array in 0xC4 steps, func_80058788 takes its entry's index from the pointer). Each entry has
// two read pointers with their own call stacks: mes_ptr_14 (message text, read by the control-
// code handlers in the tables at 0x8008A91C and later) and cmd_ptr_6C (a command stream, read by
// handlers that return 1). D_8008AB08 holds handlers of both kinds. Partial.
typedef struct
{
    uint32 flags_0;  // 0x00: flag bits (func_80054B88 sets 0x08000000, func_8005563C 0x20000000)
    sint16 timer_4;  // 0x04: wait countdown: func_80054700 loads it from its command's 16-bit
                     // argument (flags_0 bit 0x01000000 while waiting) and counts it down to 0;
                     // func_800546B0 sets it with unk_3F
    sint16 no_6;     // 0x06: the entry's own index in Moji_work (set by Moji_init)
    uint16 base_x_8; // 0x08: line start x; func_8005459C (new line) resets pos_x_10 to it
    sint16 unk_A;    // 0x0A: lh (func_8005A874); set with base_x_8 from a command's second 16-bit argument (func_80054798)
    uint8 pad_C[0x4];
    uint16 pos_x_10;       // 0x10: text cursor x; func_8005A858 adds 12 (one character's width?)
    uint16 pos_y_12;       // 0x12: text cursor y; func_8005459C (new line) adds 12
    uint8 *mes_ptr_14;     // 0x14: read pointer into the message byte stream
    uint8 *call_stk_18[8]; // 0x18: return addresses (func_80054A04 pushes, func_80054AB4 pops);
                           // depth not confirmed
    uint16 scroll_38;      // 0x38: scroll offset: func_800554E4 moves it by unk_3A per frame, then
                           // by the rest of unk_3B lines of 12
    sint8 unk_3A;          // 0x3A: lb; func_800554E4's scroll step per frame
    sint8 unk_3B;          // 0x3B: line counter, incremented by func_8005457C and func_80056128;
                           // lb in func_800554E4, which clears it
    uint8 unk_3C;          // 0x3C: cleared with unk_3E and unk_72 on a jump to a new message (func_80057744)
    uint8 unk_3D;          // 0x3D: set from a command's argument byte (func_80058C08)
    uint8 unk_3E;          // 0x3E: set from a control code's argument byte (func_80054694)
    uint8 unk_3F;          // 0x3F: set from a command's 16-bit argument (func_800546B0)
    uint32 money_40;       // 0x40: copy of Game_work.money (func_80057124)
    uint8 *mes_file_44;    // 0x44: message file: uint16 offsets from its start, one per message,
                           // then the messages (func_80058740 calls into message mes_no_C2); when
                           // NULL, func_80054A04 and func_8005497C call into D_8008CACC instead
    uint8 *cmd_top_48;     // 0x48: start of the current command message; func_80055A78 and
                           // func_8005A598 set it with cmd_ptr_6C to message mes_no_C2
    uint8 *call_stk_4C[8]; // 0x4C: return addresses (func_8005497C pushes, func_80054A84 pops)
    uint8 *cmd_ptr_6C;     // 0x6C: read pointer into the command byte stream
    uint8 unk_70;          // 0x70: copied to unk_3E at each new line (func_8005459C)
    sint8 unk_71;          // 0x71: added to D_8009899C to index D_800BE2F8 (func_8005721C)
    sint8 unk_72;          // 0x72: counter, incremented by func_80054BB4, func_80055CC4 and func_80058788;
                           // added to D_8009899C to index D_800BE2F8 (func_800594CC); func_80055304 skips
                           // this many bytes plus 2
    sint8 unk_73;          // 0x73: added to D_8009899C to index D_800BE2F8 (func_80059530)
    uint8 pad_74[0x4];
    uint8 unk_78; // 0x78: set from a control code's argument byte (func_80056180)
    uint8 pad_79[0x3];
    uint8 unk_7C;  // 0x7C: index into D_8008AB08 (func_80054B4C) and D_8008AAC0 (func_80054ADC sets
                   // it from a command's argument byte, func_80055BB0)
    uint8 unk_7D;  // 0x7D: state of func_8005AB78 (0 opens, 2 closes); cleared by func_80054ADC
                   // with flags_0 bit 0x02000000
    uint8 unk_7E;  // 0x7E: set from a command's argument byte (func_80054798); width in 12-pixel
                   // characters (func_8005AB78)
    uint8 unk_7F;  // 0x7F: set from a command's argument byte (func_80054798); height in 12-pixel
                   // lines (func_8005AB78)
    uint32 unk_80; // 0x80: flags_0 bit 0x08000000 saved by func_8005A874 while its window opens
    uint8 pad_84;
    uint8 unk_85; // 0x85: func_8005A874's opening/closing step per frame (8)
    uint8 pad_86[0x2];
    DVECTOR corner_88[4]; // 0x88: window corners relative to the text origin, set by
                          // func_8005AB78: -unk_B4/-unk_B6 to unk_B4/unk_B6 past unk_7E/unk_7F * 12;
                          // func_8005ACA8 copies each x, y into the primitives at 0xA0-0xAC
    uint8 pad_98[0x18];
    uint8 r_B0; // 0xB0: colour of func_8005B5D8's semi-transparent POLY_F4 (r0, g0, b0);
    uint8 g_B1; // func_8005B454 fades all three from 0 up to 0x80 and back by 8 per frame
    uint8 b_B2;
    uint8 pad_B3;
    uint16 unk_B4;     // 0xB4: window margin x (func_8005AB78, from a command's argument byte)
    uint16 unk_B6;     // 0xB6: window margin y (set with unk_B4)
    uint16 unk_B8;     // 0xB8: lhu; cleared with unk_BA (func_80056820); some code loads both as one word
    uint16 unk_BA;     // 0xBA: lhu; bits 0x4000 and 0x1000 tested by func_80058AEC and func_80054BEC;
                       // func_80055CFC clears 0x4000
    uint16 unk_BC;     // 0xBC: cleared by func_80054BB4, func_80055CC4 and func_80058788
    uint16 call_sp_BE; // 0xBE: depth of call_stk_18
    uint16 call_sp_C0; // 0xC0: depth of call_stk_4C
    uint16 mes_no_C2;  // 0xC2: message number in mes_file_44
} MOJI_WORK;

typedef void (*MOJI_FUNC)(MOJI_WORK *mp);

// The message work entries (see MOJI_WORK).
extern MOJI_WORK Moji_work[MOJI_WORK_MAX];

// Message pointers; func_80054A04 and func_8005497C call into entry n (the argument byte) when
// the entry has no message file.
extern uint8 *D_8008CACC[];

// Font codes of the digits 0 to 9 (0x00-0x09; two_digit_set).
extern uint8 D_8008D028[];

// Powers of ten from 100000 down to 1: the digit places of six_digit_set's six-digit numbers.
extern uint32 D_8008AF24[6];

// Six signed words (500, 200, 250, 200, 180, 150); func_80059D20 prints entry D_800BE2F8[n] less a
// Game_work word (times a Game_work byte for entries 4 and 5).
extern sint32 D_8008AF00[6];

// Font codes six_digit_set writes for leading zeros, chosen by its first argument.
extern uint8 D_8008AF3C[];

// Halfword table, row D_800989D4 (13 rows of 5 entries of 4; 0x208 bytes). func_8005861C picks
// its message by entry [row][n]: [0] zero, or [Player_work[0].rec[..].idx[n]] zero, or neither.
// Defining file unknown: it sits in sub_scrn's .data range, but moji's code is its only user.
extern uint16 D_8008D8EC[13][5][4];

// Eight-byte font strings in .sdata (0x80097FDC-0x80097FF3) that func_8005851C copies into its
// command: D_80097FEC when D_8008D8EC's entry [0] is zero, D_80097FE4 when the level's entry is,
// else D_80097FDC with the level digit (level + 1) stored in D_80097FE2, its seventh byte.
// Reached with lui + %lo, each by its own label; moji's code is their only user.
extern uint8 D_80097FDC[6];
extern uint8 D_80097FE2[2];
extern uint8 D_80097FE4[8];
extern uint8 D_80097FEC[8];

// Two eight-byte "hh:mm:ss" font strings in the same .sdata, on either side of those (0x13 is the
// colon): func_800679B8 writes Game_work.timer_0c's digits into the first, func_80067B7C
// timer_14's into the second, which func_80057E50 reads. Each digit is reached by its own label.
extern uint8 D_80097FD4; // hours, tens
extern uint8 D_80097FD5; // hours, ones
extern uint8 D_80097FD7; // minutes, tens
extern uint8 D_80097FD8; // minutes, ones
extern uint8 D_80097FDA; // seconds, tens
extern uint8 D_80097FDB; // seconds, ones
extern uint8 D_80097FF4;
extern uint8 D_80097FF5;
extern uint8 D_80097FF7;
extern uint8 D_80097FF8;
extern uint8 D_80097FFA;
extern uint8 D_80097FFB;

// Message pointers; func_80057708 calls into entry D_80098830 as a sub-message.
extern uint8 *D_8008CBA4[];

// Message pointer tables; func_80057D60 and func_80059E24 call into entry D_800BE2F8[n], n from
// the control code's argument byte; func_80059530 calls into D_8008CCA4[D_800BE2F8[...]].
extern uint8 *D_8008CCA4[];
extern uint8 *D_8008CE10[];
extern uint8 *D_8008CE5C[];

// func_80058C28 and func_80058CC8 call into D_8008BAA4[flag] when scene flag `flag` (the code's
// 16-bit argument) is set, and into message D_8008CE58 otherwise. D_8008BAA4 is indexed by the
// flag number itself (its label holds text bytes); typed by that use.
extern uint8 *D_8008BAA4[];
extern uint8 *D_8008CE58;

// Pointers to byte variables (game flags and work fields); func_80055C80 stores a command's
// argument byte through entry n.
extern uint8 *D_8008D0D4[];

// Handler table that func_80054B4C indexes with MOJI_WORK.unk_7C. It holds both message-text and
// command handlers (Moji_skip_*, func_800543B0, ...); typed by func_80054B4C's use.
extern MOJI_FUNC D_8008AB08[];

// Handler table that func_80054ADC and func_80055BB0 index with MOJI_WORK.unk_7C (func_8005A874,
// ...); splat splits it into several labels. Return value unused by both callers.
extern MOJI_FUNC D_8008AAC0[];

// Byte table (0x80 entries: func_80058DB4 fills them); func_80057DB8 replaces Moji_flag's low byte with entry [low byte].
// Defining file unknown; moji's code is its only user.
extern uint8 D_800BE2F8[];

// Pool variable (0x80098A58), defined tentatively in moji.c.
extern uint32 Moji_flag;

// Pool variable (0x8009899C), defined tentatively in moji.c; func_80059530 adds it to
// MOJI_WORK.unk_73 to index D_800BE2F8. func_80058DB4 clears it.
extern uint8 D_8009899C;

// Pool variable (0x80098B30), defined tentatively in moji.c; func_80058788 clears bit
// 17 + (Moji_work entry index).
extern uint32 Moji_flag3;

// Halfword table in the tail of small tables (0x8008FD3C); func_8005721C tests whether the money
// covers entry D_80098930 (a price).
extern uint16 D_8008FD3C[];

// Halfword table right after D_8008FD3C (0x40 bytes on); func_80057574 prints its entry instead
// of D_8008FD3C's when D_80098850 is set (both divided by 4 when scene flag 0x2EE is set).
extern uint16 D_8008FD7C[];

// Pool variables (0x80098930, 0x80098B6C), defined tentatively in moji.c. func_8005721C sets
// D_80098930 to D_800BE2F8[D_8009899C + unk_71] plus its command's argument byte, and
// D_80098B6C to 1 when scene flag 0x2EE is clear and the money doesn't cover D_8008FD3C[D_80098930].
extern uint8 D_80098930;
extern uint8 D_80098B6C;

// Pool variables, defined tentatively in moji.c. D_8008D0D4 (pointers to byte variables) points
// to D_800987F8 and D_80098850. func_80056778 copies D_800987F8 into its command and adds 0x20 to
// the D_800BE2F8 entry it stores to D_80098830 when D_80098850 is set; func_80058EA0 sets
// D_80098851 to 0xFF.
extern uint8 D_800987F8;
extern uint8 D_80098850;
extern uint8 D_80098851;

// Loads file 30 and resets the message entries, Moji_flag and the module's pool counters.
void Moji_init(void);

// Kills every message entry: clears their flags (stopping XA audio if one was playing it) and
// Moji_flag.
void MojiTaskKill(void);

// Runs every message entry; called once per frame by main.
void func_80053B40(void);

#endif
