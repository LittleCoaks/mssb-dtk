#include "Unknown/File_0x80021308.h"
#include "Unknown/File_0x80021410.h"
#include "musyx/musyx.h"
#include "Unknown/File_0x800219b4.h"
#include "Unknown/sound.h"
#include "Unknown/File_0x800a6304.h"
#include "Unknown/File_0x80062a94.h"
#include "Dolphin/os.h"

// 0x800211F0-0x80021AA0: the sound-setup translation unit, one unit by its .data
// order (docs/splits.md, 2026-11-21): the former File_0x80021308.c,
// File_0x80021410.c and File_0x800219b4.c plus unowned functions that have no
// C yet.

extern SND_HOOKS lbl_803CB7D8;
extern u8 lbl_80118740[0x40000];
extern void* lbl_803CBC40;

void soundOrMusicRelated(void) {
    lbl_803CBC40 = lbl_80118740;
    sndSetHooks(&lbl_803CB7D8);
    audioFileDescriptors.reverb.tempDisableFX = FALSE;
    audioFileDescriptors.reverb.time = 2.0f;
    audioFileDescriptors.reverb.preDelay = 0.1f;
    audioFileDescriptors.reverb.damping = 0.5f;
    audioFileDescriptors.reverb.coloration = 1.0f;
    audioFileDescriptors.reverb.crosstalk = 0.0f;
    audioFileDescriptors.reverb.mix = 0.8f;
    sndAuxCallbackPrepareReverbHI(&audioFileDescriptors.reverb);
    audioFileDescriptors.chorus.baseDelay = 5;
    audioFileDescriptors.chorus.variation = 0;
    audioFileDescriptors.chorus.period = 500;
    sndAuxCallbackPrepareChorus(&audioFileDescriptors.chorus);
    sndSetAuxProcessingCallbacks(SND_STUDIO_DEFAULT, sndAuxCallbackReverbHI, &audioFileDescriptors.reverb, 0xFF, 0,
                                 sndAuxCallbackChorus, &audioFileDescriptors.chorus, 0xFF, 0);
}

static inline BOOL popSoundGroup(void) {
    if (sndPopGroup() == FALSE) {
        return FALSE;
    }
    audioFileDescriptors.pushedGroupCount--;
    return TRUE;
}

BOOL maybeLoadsGameSoundFiles(void) {
    s8 i;

    for (i = (s8)audioFileDescriptors.pushedGroupCount - 1; i > 0; i--) {
        if (!popSoundGroup()) {
            return FALSE;
        }
    }
    return TRUE;
}

extern u8 lbl_80158740[0x4000];
extern u8 lbl_8015C740[0x21BE0];
extern u8 lbl_800EFBB4[0xC];

void f_initSound(void) {
    u8 mode;

    *(u32*)lbl_80158740 = 0xABF16D9C;
    lbl_80158740[0] = 'S';
    lbl_80158740[1] = 'N';
    lbl_80158740[2] = 'D';
    lbl_80158740[3] = '@';
    initSound((SndConfig*)lbl_800EFBB4, NULL, lbl_8015C740, sizeof(lbl_8015C740));
    jukeboxStop();
    fn_800A648C();
    mode = OSGetSoundMode();
    audioFileDescriptors._397 = mode == OS_SOUND_MODE_MONO ? 1 : mode;
    audioFileDescriptors.soundMode = mode;
    sndOutputMode(mode);
    OSSetSoundMode(audioFileDescriptors.soundMode != OS_SOUND_MODE_MONO);
    sndVolume(audioFileDescriptors.musicVolume, 0, SND_MUSIC_VOLGROUPS);
    sndVolume(audioFileDescriptors.fxVolume, 0, SND_FX_VOLGROUPS);
}
