#include "menus/rep_01A0.h"
#include "header_rep_data.h"
#include "menus/yd_step.h"
#include "Unknown/File_0x800b0a14.h"
#include "musyx/musyx.h"
#include "musyx/seq.h"

#pragma inline_max_auto_size(1024)

extern DrawingSceneStruct *currentDrawingItem;
extern bool32 sndSeqGetValid(s32 seqId);

extern f32 menuSoundEffectVolume;
extern u8 menuSoundEffectFadeActive;
extern MenuSongEntry lbl_2_data_128[];
extern SND_VOICEID currentMenuSoundEffectVoice;
extern s16 lbl_2_bss_D958[];
extern u32 menuMusicSequenceIds[];
extern void **lbl_2_bss_D984;

// NOTE: -inline deferred makes MWCC emit functions in REVERSE source order,
// so definitions below are written in reverse of their final .text addresses.

// .text:0x000010AC size:0x50 mapped:0x80640140
void fn_2_10AC(void **arg0) {
    arg0[0] = (void *)((u32)arg0[0] + (u32)arg0);
    arg0[1] = (void *)((u32)arg0[1] + (u32)arg0);
    menuMusicSequenceIds[0] = -1;
    lbl_2_bss_D958[0] = -1;
    menuMusicSequenceIds[1] = -1;
    lbl_2_bss_D958[1] = -1;
    menuMusicSequenceIds[2] = -1;
    lbl_2_bss_D958[2] = -1;
    menuMusicSequenceIds[3] = -1;
    lbl_2_bss_D958[3] = -1;
    lbl_2_bss_D984 = arg0;
}

// .text:0x00001018 size:0x94 mapped:0x806400AC
void stopMenuMusicSlot(u16 slot) {
    if (menuMusicSequenceIds[slot] != -1) {
        if (sndSeqGetValid(menuMusicSequenceIds[slot])) {
            sndSeqVolume(0, 0, menuMusicSequenceIds[slot], 1);
            sndSeqStop(menuMusicSequenceIds[slot]);
        }
        menuMusicSequenceIds[slot] = -1;
        lbl_2_bss_D958[slot] = -1;
    }
}

// .text:0x00000F64 size:0xB4 mapped:0x8063FFF8
void stopAllMenuMusic(void) {
    u16 i;

    for (i = 0; i < 4; i++) {
        stopMenuMusicSlot(i);
    }
}

// .text:0x00000E84 size:0xE0 mapped:0x8063FF18
void fn_2_E84(u16 slot, s16 song) {
    MenuSongEntry *entry = &lbl_2_data_128[song];

    stopMenuMusicSlot(slot);
    menuMusicSequenceIds[slot] = sndSeqPlayEx(entry->sgid, entry->sid,
                                        lbl_2_bss_D984[entry->arr], NULL, 0);
    lbl_2_bss_D958[slot] = song;
}

// .text:0x00000D88 size:0xFC mapped:0x8063FE1C
void fn_2_D88(u16 slot, s16 song) {
    if (song == lbl_2_bss_D958[slot] && sndSeqGetValid(menuMusicSequenceIds[slot])) {
        return;
    }
    fn_2_E84(slot, song);
}

// .text:0x00000D08 size:0x80 mapped:0x8063FD9C
void fn_2_D08(u16 slot, u16 time, u8 mode) {
    if (menuMusicSequenceIds[slot] != -1) {
        if (sndSeqGetValid(menuMusicSequenceIds[slot])) {
            sndSeqVolume(0, time, menuMusicSequenceIds[slot], mode);
        }
    }
}

// .text:0x00000C74 size:0x94 mapped:0x8063FD08
void setMenuSoundEffectVolume(u8 volume) {
    if (currentMenuSoundEffectVoice != -1 && sndFXCheck(currentMenuSoundEffectVoice) == currentMenuSoundEffectVoice) {
        sndFXCtrl(currentMenuSoundEffectVoice, 7, volume);
    } else {
        menuSoundEffectVolume = volume;
    }
}

// .text:0x00000C18 size:0x5C mapped:0x8063FCAC
void stopMenuSoundEffect(void) {
    if (currentMenuSoundEffectVoice != -1 && sndFXCheck(currentMenuSoundEffectVoice) == currentMenuSoundEffectVoice) {
        sndFXKeyOff(currentMenuSoundEffectVoice);
        currentMenuSoundEffectVoice = -1;
    }
}

// .text:0x00000B38 size:0xE0 mapped:0x8063FBCC
void menuSoundEffectFadeStep(void) {
    menuSoundEffectVolume += currentDrawingItem->unk_14;
    if (menuSoundEffectVolume < 0.0f) {
        menuSoundEffectVolume = 0.0f;
    }
    sndFXCtrl(currentMenuSoundEffectVoice, 7, menuSoundEffectVolume);
    if (menuSoundEffectVolume == 0.0f) {
        menuSoundEffectFadeActive = 0;
        stopMenuSoundEffect();
        removeCurrentDrawingItem();
    }
}

// .text:0x00000A70 size:0xC8 mapped:0x8063FB04
void startMenuSoundEffectFadeOut(u16 frames) {
    DrawingSceneStruct *item;

    if (menuSoundEffectFadeActive == 0 && currentMenuSoundEffectVoice != -1 &&
        sndFXCheck(currentMenuSoundEffectVoice) == currentMenuSoundEffectVoice) {
        item = insertGraphicDrawingFunction(menuSoundEffectFadeStep, 0x8000);
        if (frames == 0) {
            frames = 1;
        }
        item->unk_14 = -menuSoundEffectVolume / frames;
        menuSoundEffectFadeActive = 1;
    }
}
