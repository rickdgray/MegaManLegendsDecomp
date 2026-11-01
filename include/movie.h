#ifndef MOVIE_H
#define MOVIE_H

// Movie (STR) playback: sectors read from the disc, decoded by the MDEC, uploaded to VRAM.

#include "common.h"
#include "psyq/libgpu.h"

// Fixed RAM areas used by movie (STR) playback.
#define STR_SECTOR_BUF 0x800F0000 // one raw sector, read with CdGetSector
#define MOVIE_RING_BUF 0x80100000 // 4 slots of 0x8000 bytes, one frame each
#define MOVIE_VLC_BUF 0x80120000  // 2 buffers of 0x10000 bytes, DecDCTvlc output
#define MOVIE_IMG_BUF 0x80140000  // 2 buffers of 0x25800 bytes, decoded 320x240 image

// A raw movie sector (0x200 words): 32-byte header, then 0x7E0 bytes of payload.
typedef struct
{
    u_long id;
    u_short sector_no;    // index of this sector within the frame
    u_short sector_count; // number of sectors in the frame
    u_long frame_no;
    u_long unk0C[5];
    u_long data[0x1F8];
} STR_SECTOR;

// Movie table entry (12 bytes). Proposed name for Movie_tbl: Movie_tbl.
typedef struct
{
    sint32 pos;       // disc position, as a sector number
    sint32 end_frame; // default for D_80059BB0
    sint32 unk8;
} MOVIE_INFO;

extern MOVIE_INFO Movie_tbl[];

extern uint8 Movie_buf_ready[4];
extern sint32 Movie_buf_idx;
extern sint32 Movie_frame_idx;
extern RECT Movie_rect_tbl[2][20];
extern sint32 Movie_sector_wait;
extern uint32 Movie_slice_count;
extern u_long *Movie_slice_ptr;
extern u_long *Movie_write_ptr;
extern sint32 Movie_write_idx;

// Unknown
extern sint32 D_80059BA4;
extern sint32 D_80059BB0; // end frame, defaults from Movie_tbl[].end_frame
extern sint32 D_80059C2C;

void Movie_start(sint32 movie);
sint32 Movie_buf_get(u_long **end, u_long **base);
void Movie_buf_release(void);
void Movie_sector_cb(u_char status, u_char *result);
void Movie_dct_out_callback(void);
void Movie_frame_upload(void);

#endif // MOVIE_H
