#ifndef __UNKNOWN_FILE_0X80062A94_H_
#define __UNKNOWN_FILE_0X80062A94_H_

#include "mssbTypes.h"

/* ---- menu music (0x803C6714) -------------------------------------------
 * startMenuMusic is a drawing-script function main_menu inserts (priority
 * 0x1000) while menuMusic.playing == 0. It reads audioFileDescriptors[0x398]
 * (enableMusic), starts sfx 484 (0x1E4) as a looping FX voice at
 * menuMusicStartVolume through sndFXStartEx, keeps the voice handle here and
 * sets playing = 1. Setting fade (0x803C671A) is the STOP path: it
 * sndFXCtrl's the volume down, sndFXKeyOff's the voice and removes itself.
 * Traced by ProjectRio-ASM (Gecko Codes/Menu/Dictionary Replaces Menu Music.c,
 * RioModPack/Custom Music.c). */
typedef struct MenuMusicState {
    /* 0x00 */ u32 handle;      // sndFXStartEx result for sfx 484
    /* 0x04 */ u8 playing;      // the "already playing" guard (0x803C6718)
    /* 0x05 */ u8 stopping;
    /* 0x06 */ u8 fade;         // set to fade out and stop (0x803C671A)
    /* 0x07 */ u8 fadeStep;
    /* 0x08 */ u8 unk8[0x8];
} MenuMusicState; // size 0x10

extern MenuMusicState menuMusic;
extern u8 menuMusicStartVolume;   // 0x803CB888 (.sdata)

/* ---- audio file / stream tables ------------------------------------------
 * audioFileTable (0x800EF508): 16 bytes per audio file index, handed to
 * ARAMTransfer by audioFileLoaderTask (0x80021758); index 4 is the
 * Dictionary's set. audioFileDescriptors (0x800EF808): descriptor pointer per
 * file at +4 + index*4 (so file 4 is at 0x800EF81C, the group id
 * pushDictionaryAudioGroup pushes), then u8 enableMusic at +0x398.
 * streamDescriptors (0x800E87B4): 16 bytes per DTK stream id
 * {char* path; u32 size; u32; u32 size}, resolved through the disc FST at
 * runtime by playStream (0x8006877C), which works in jukeboxWork
 * (0x8034E478, 0x50 bytes per stream id). jukeboxCmd(4) cancels the DVD
 * stream; jukeboxStop halts AI streaming. */
typedef struct StreamDescriptor {
    /* 0x00 */ const char* path;
    /* 0x04 */ u32 size;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u32 sizeC;
} StreamDescriptor; // size 0x10

extern StreamDescriptor streamDescriptors[15];   // 0x800E87B4, 0xF0 bytes

void startMenuMusic(void);
void playStream(u8 streamId);
void jukeboxCmd(u32 cmd);
void jukeboxStop(void);

#endif // !__UNKNOWN_FILE_0X80062A94_H_
