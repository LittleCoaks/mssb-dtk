#ifndef __MENUS_REP_01A0_H_
#define __MENUS_REP_01A0_H_

#include "mssbTypes.h"

typedef struct MenuSongEntry {
    /* 0x00 */ u16 sgid;
    /* 0x02 */ u16 sid;
    /* 0x04 */ u16 arr;
} MenuSongEntry; // size 0x6

void startMenuSoundEffectFadeOut(u16 frames);
void menuSoundEffectFadeStep(void);
void stopMenuSoundEffect(void);
void setMenuSoundEffectVolume(u8 volume);
void fn_2_D08(u16 slot, u16 time, u8 mode);
void fn_2_D88(u16 slot, s16 song);
void fn_2_E84(u16 slot, s16 song);
void stopAllMenuMusic(void);
void stopMenuMusicSlot(u16 slot);
void fn_2_10AC(void **arg0);

#endif // !__MENUS_REP_01A0_H_
