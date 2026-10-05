#ifndef __UNKNOWN_FILE_0X8001FC4C_H_
#define __UNKNOWN_FILE_0X8001FC4C_H_

#include "mssbTypes.h"

#define SHORT_TABLE_COUNT 120
#define SHORT_TABLE_END 0xFFFF

typedef struct {
    /*0x000*/ u8 _000[0x72];
    /*0x072*/ u16 order[SHORT_TABLE_COUNT];
    /*0x162*/ u16 slot[SHORT_TABLE_COUNT];
    /*0x252*/ E(s8, CHAR_ID) charId;
} ShortsTableOwner;

void initShortsHandleCompressedDiskReads(ShortsTableOwner* owner);

#endif // !__UNKNOWN_FILE_0X8001FC4C_H_
