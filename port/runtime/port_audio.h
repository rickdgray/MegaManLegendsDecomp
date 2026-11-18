// Sound output of the running game: the SPU's samples (spu.c) to the window's audio device and
// to an optional WAV file.
//
// The SPU is run from the vertical-blank signal: port_audio_tick() mixes one blank's worth of
// game time (735 frames at 44.1 kHz; 1/60 s) after the blank's interrupt work (the CD drive,
// which feeds XA and CD-DA into the SPU, then the VSync callbacks and libsnd's sequencer tick).
// With --fast the blanks come faster and so does the sound: a WAV file then still holds the
// game's sound at its own pace. Nothing in the signal handler calls into SDL or stdio: the mix
// goes to lock-free rings, which SDL's audio thread and port_audio_flush() (main thread) drain.
#ifndef PORT_AUDIO_H
#define PORT_AUDIO_H

#include <stdint.h>

// Starts writing a 16-bit stereo 44.1 kHz WAV file. Returns 0, or -1 with a message.
int port_audio_wav_open(const char *path);

// Opens the audio device (SDL builds with a window). Returns 0, or -1.
int port_audio_device_open(void);

// Output volume of the device, 0-100 (the WAV file is not scaled).
void port_audio_set_volume(int percent);

// Moves the device ring into memory shared with another process (port_remote.h): the game
// fills it (`producer`) and the window host's device drains it.
void port_audio_use_shared(uint32_t *head, uint32_t *tail, int16_t (*buf)[2], uint32_t size,
                           int producer);

// One vertical blank of sound (signal context).
void port_audio_tick(void);

// Writes pending WAV data (main thread); port_audio_close also finishes the header.
void port_audio_flush(void);
void port_audio_close(void);

#endif
