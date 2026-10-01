#ifndef __UNKNOWN_FILE_0X80021410_H_
#define __UNKNOWN_FILE_0X80021410_H_

#include "mssbTypes.h"
#include "musyx/musyx.h"

typedef struct {
    /* 0x000 */ void* files[0xC4 / 4];
    /* 0x0C4 */ SND_AUX_REVERBHI reverb;
    /* 0x2A4 */ SND_AUX_CHORUS chorus;
    /* 0x340 */ u8 _340[0x390 - 0x340];
    /* 0x390 */ u8 pushedGroupCount;
    /* 0x391 */ u8 musicVolume; // sndVolume level for SND_MUSIC_VOLGROUPS
    /* 0x392 */ u8 fxVolume;    // sndVolume level for SND_FX_VOLGROUPS
    /* 0x393 */ u8 _393[0x396 - 0x393];
    /* 0x396 */ u8 soundMode;   // OSGetSoundMode() at boot
    /* 0x397 */ u8 _397;
    /* 0x398 */ E(u8, BOOL) enableMusic; // 0 stops menu music and crowd sequences
    /* 0x399 */ u8 _399[0x39C - 0x399];
} AudioFileDescriptors; // size: 0x39C

extern AudioFileDescriptors audioFileDescriptors;

BOOL maybeLoadsGameSoundFiles(void);

#endif // !__UNKNOWN_FILE_0X80021410_H_
