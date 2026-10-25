#ifndef __UNKNOWN_FILE_0X8004B7F4_H_
#define __UNKNOWN_FILE_0X8004B7F4_H_

#include "mssbTypes.h"

typedef struct _CharacterStateActor {
    /*0x000*/ u8 _000[0x30];
    /*0x030*/ u8* _030;
    /*0x034*/ u8 _034[0x62 - 0x34];
    /*0x062*/ s16 _062;
    /*0x064*/ u8 _064[0x252 - 0x64];
    /*0x252*/ s8 _252;
    /*0x253*/ u8 _253;
    /*0x254*/ s8 _254;
    /*0x255*/ u8 _255[0x25A - 0x255];
    /*0x25A*/ u8 _25A;
    /*0x25B*/ u8 _25B;
    /*0x25C*/ u8 _25C[0x278 - 0x25C];
    /*0x278*/ u8 _278;
} CharacterStateActor;

extern u16 specialBatAttachSlots[4][2];

u32 getHandTrackFlags(void* hand);

void processCharacterStateBasedOnGameMode(CharacterStateActor* a);

#endif // !__UNKNOWN_FILE_0X8004B7F4_H_
