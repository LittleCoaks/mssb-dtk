#include "Unknown/File_0x800219b4.h"
#include "Unknown/File_0x800b0834.h"
#include "Unknown/File_0x800a6304.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x80062a94.h"
#include "Dolphin/os.h"

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
    initSound(lbl_800EFBB4, NULL, lbl_8015C740, sizeof(lbl_8015C740));
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
