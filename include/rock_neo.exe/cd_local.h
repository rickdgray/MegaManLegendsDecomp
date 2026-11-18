#ifndef CD_LOCAL_H
#define CD_LOCAL_H

// rock_neo.exe-specific: CD variables with no name yet. Included at the end of cd.h.
// The slus_006.03 counterparts (shim names in comments) are in include/slus_006.03/cd_local.h.

#include "common.h"
#include "psyq/libcd.h"
#include "psyq/libgpu.h"

#define CD_CMD_TIMEOUT       150
#define CD_ERR_CMD_TIMEOUT   0x02
#define CD_ERR_FILE_ID       0x20
#define CD_ERR_SECTOR        0x40
#define CD_ERR_BUFFER_FULL   0x01
#define CD_SECTOR_BYTES      2048
#define CD_SECTOR_WORDS      512
#define CD_READ_BUFFER_COUNT 10

typedef struct
{
    uint32 offset; // sector offset within the file (low 24 bits)
    uint32 unk4;
} CD_POS;

// A command slot with its three arguments as words (a struct field, unlike a cast of args.arg3).
typedef struct
{
    sint32 type;
    uint32 arg[3];
} CD_CMD_RAW;

extern uint8 D_800988D0;         // D_80059BC9
extern uint8 D_800988DC;         // D_80059BCA
extern sint32 D_80098998;        // D_80059C00
extern sint32 D_800989C8;        // D_80059C24
extern uint8 D_80098AA0;         // D_80059C48
extern uint8 D_80098B42;         // D_80059C74
extern CD_CMD_FUNC D_80087670[]; // run by func_8001B858, indexed by the command's arg2

// Read setup and callbacks; widths verified against the read-ready handlers.
extern uint8 *D_800987A4;                      // next destination byte
extern CdlLOC D_80098814;                      // requested sector in BCD
extern sint32 D_8009881C;                      // bytes remaining
extern sint32 D_80098A7C;                      // next expected absolute sector
extern uint8 D_80098B38[CD_READ_BUFFER_COUNT]; // ten sector-buffer occupancy flags

extern uint8 D_800B5DB0[]; // sector header scratch and buffered sector data

// Packed playback references and command-dispatch state.
extern uint32 D_800989B0;   // playback end sector
extern uint32 D_800989B8;   // packed reference retained for repeat playback
extern uint32 D_800989BC;   // saved command argument 2
extern uint32 D_800989C0;   // saved final command word, including repeat bit
extern uint32 D_800989D8;   // current playback sector
extern uint8 D_80098A9D[3]; // absolute M:S:F bytes at Cd_result + 5
extern CD_CMD_FUNC D_80087680[];

// Unknown
extern uint16 D_80098994;
extern uint8 D_80098AB8;
extern sint32
    *D_80088F9C[16]; // file index tables, selected by the top nibble of func_8001D648's argument
extern CD_POS **D_80088EF8[16]; // matching sector offset tables

void Cd_set_volume(uint8 vol);
void Cd_pause(void);
void Cd_stop(void);
void Cd_read_sync(void);

// Unknown
void func_8001C7F0(u_char status, u_char *result);
void func_8001CC7C(sint32 index, uint8 *dest);
void func_8001CD60(u_char status, u_char *result);
void func_8001CF98(sint32 index);
void func_8001D078(u_char status, u_char *result);
void func_8001B7B4(void);
void func_8001D58C(uint32 arg);
void func_8001D648(uint32 arg);
void func_8001D6D8(sint32 sector);
void func_8001D7AC(sint32 index);

// Buffered asset records (func_8001BB4C). Each 0x800-byte buffer starts with a record header;
// record data begins at +0x100.
typedef struct
{
    sint32 type;       // 0x00: -1 ends the list
    uint32 size;       // 0x04: bytes of data that follow
    sint32 count;      // 0x08: sectors the record spans
    uint32 arg[61];    // 0x0C: meaning depends on the type
    uint8 data[0x700]; // 0x100
} CD_ASSET_REC;

// The record being loaded: header words copied from the buffer, then load progress.
typedef struct
{
    uint32 size;  // 0x00: bytes left
    sint32 count; // 0x04: sectors left
    union
    {
        uint8 *dest; // type 0: raw copy
        struct
        {
            sint32 clut_x, clut_y, clut_w, clut_h;
            sint32 x, y, w, h;
        } tim; // type 1: image streamed as 32x32 tiles
        struct
        {
            sint32 x, y, cols, rows;
        } tiles; // type 3
        struct
        {
            sint32 slot;
            sint32 id;
            sint32 arg;
            sint32 size;
            uint8 *head;
            uint8 load;
        } vab; // type 5: sound bank
        struct
        {
            sint32 slot;
            sint32 id;
            uint8 *dest;
            uint8 load;
        } seq; // type 7
        struct
        {
            sint32 slot;
            sint32 id;
            sint32 sub;
            uint8 *dest;
            uint8 load;
        } sep; // type 8
    } u;
    uint8 reserved28[8];
    sint32 col; // 0x30
    sint32 row; // 0x34
} CD_ASSET_WORK;

extern sint32 D_800987A8; // current sector buffer
extern sint32 D_80098A54; // type of the record being loaded
extern CD_ASSET_WORK D_800C5604;

#define CD_SECTOR_BUF(i) (&D_800B5DB0[(i) << 11]) // sector buffer i (0x800 bytes)
extern RECT D_8009BE48[];
extern uint16 D_800AD168[]; // shadow copy of the texture pages
extern uint32 D_80098868;   // shadow rows touched

void func_8001B33C(void);
void func_80017684(void *src, void *dst, sint32 count);
void func_800176A4(void *src, void *dst, sint32 count);
void func_800176DC(void *src, void *dst, sint32 count);

#endif // CD_LOCAL_H
