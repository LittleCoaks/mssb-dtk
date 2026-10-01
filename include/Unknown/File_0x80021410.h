#ifndef __UNKNOWN_FILE_0X80021410_H_
#define __UNKNOWN_FILE_0X80021410_H_

#include "mssbTypes.h"

typedef struct {
    /* 0x000 */ void* files[0x390 / 4];
    /* 0x390 */ u8 pushedGroupCount;
    /* 0x391 */ u8 _391[0x396 - 0x391];
    /* 0x396 */ u8 _396;
    /* 0x397 */ u8 _397;
    /* 0x398 */ u8 _398;
    /* 0x399 */ u8 _399[0x39C - 0x399];
} AudioFileDescriptors; // size: 0x39C

extern AudioFileDescriptors audioFileDescriptors;

BOOL maybeLoadsGameSoundFiles(void);

#endif // !__UNKNOWN_FILE_0X80021410_H_
