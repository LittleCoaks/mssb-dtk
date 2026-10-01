#include "Unknown/File_0x80021308.h"
#include "Unknown/File_0x80021410.h"

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
