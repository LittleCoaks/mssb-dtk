#ifndef __UNKNOWN_FILE_0X8004A2BC_H_
#define __UNKNOWN_FILE_0X8004A2BC_H_

#include "mssbTypes.h"

typedef struct GameSettingsScreenState {
    /* 0x00 */ u8 unk0[0x2C];
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u8 unk2E[0x42];
} GameSettingsScreenState; // size 0x70

extern GameSettingsScreenState gameSettings;

void gameSettingsScreen(void);

#endif // !__UNKNOWN_FILE_0X8004A2BC_H_
