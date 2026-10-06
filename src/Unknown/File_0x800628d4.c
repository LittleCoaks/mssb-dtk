#include "Unknown/File_0x800628d4.h"
#include "Unknown/mb_subfunc.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_80108B18[0x24];
extern u16 lbl_80108DF4[0x22];

static inline SND_VOICEID startMenuVoice(u8* vol, u16 id) {
    SND_VOICEID voice = sndFXStartEx(id, *vol, 0x3F, 0);
    sndFXCtrl(voice, 0x5B, 0);
    return voice;
}

SND_VOICEID playPlayerSelectedSound(int charID) {
    Static_Stats_Tables.unk48AE = 1;
    return startMenuVoice(lbl_80108B18, lbl_80108DF4[findCharacterID(charID)]);
}
