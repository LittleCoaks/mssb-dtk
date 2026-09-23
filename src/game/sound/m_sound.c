#include "game/sound/m_sound.h"
#include "header_rep_data.h"
#include "musyx/musyx.h"
#include "musyx/seq.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800b0a14.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"

extern void fn_3_8B094(void);

// Composite listener/emitter object used by the stadium 3D sound code:
// a listener, an array of emitters, an active-flag byte per emitter, and
// two regions whose contents are unknown.
typedef struct SoundEmitterState {
    SND_LISTENER listener;         // 0x0000, size 0x90
    SND_EMITTER emitters[100];     // 0x0090, stride 0x50
    u8 unk_1FD0[0x64];             // 0x1FD0, unproven
    E(u8, BOOL) emitterActive[100]; // 0x2034
    u8 unk_2098[0xA0];             // 0x2098, unproven
} SoundEmitterState; // size 0x2138

extern SoundEmitterState sndEmitter;

unsigned long sndRemoveListener(SND_LISTENER* li);
unsigned long sndUpdateListener(SND_LISTENER* li, SND_FVECTOR* pos, SND_FVECTOR* dir,
                                 SND_FVECTOR* heading, SND_FVECTOR* up, u8 vol, SND_ROOM* room);
unsigned long sndAddListener(SND_LISTENER* li, SND_FVECTOR* pos, SND_FVECTOR* dir,
                              SND_FVECTOR* heading, SND_FVECTOR* up, f32 front_sur, f32 back_sur,
                              f32 soundSpeed, unsigned long flags, unsigned char vol,
                              SND_ROOM* room);
bool32 sndCheckEmitter(SND_EMITTER* em);
unsigned long sndRemoveEmitter(SND_EMITTER* em);
bool32 sndUpdateEmitter(SND_EMITTER* em, SND_FVECTOR* pos, SND_FVECTOR* dir, u8 maxVol,
                         SND_ROOM* room);
bool32 sndSeqGetValid(s32 unk);

extern SND_FVECTOR lbl_3_data_8D70;
extern f32 lbl_3_data_88AC;

extern const f32 lbl_3_rodata_157C;
extern const f32 lbl_3_rodata_1580;

extern u16 characterSoundArray[54];
extern u8 charSoundFxVol[12];

// Per-sound volume/reverb mix table, indexed by soundNumber - SOUND_EFFECT_MIX_FIRST_ID.
typedef struct SoundEffectMix {
    u8 volume;
    u8 reverb;
} SoundEffectMix;

extern SoundEffectMix lbl_3_data_8338[];
#define SOUND_EFFECT_MIX_FIRST_ID 0x151

typedef struct SeqPlayEntry {
    u16 sgid;
    u16 sid;
    u16 _04;
} SeqPlayEntry;

extern SeqPlayEntry lbl_3_data_88E0[];
extern u8 lbl_3_data_830C[];

static s32 lbl_3_bss_1774[0xC / sizeof(s32)];
static s32 lbl_3_bss_1780[0x78 / sizeof(s32)];

// A DrawingSceneStruct whose scratch region (0x14..0x40) is used by this
// file's callback as a 14-entry circular queue of 3-byte replay records.
typedef struct SoundReplayEventRecord {
    u8 arg1;
    u8 arg2;
    u8 arg3;
} SoundReplayEventRecord;

typedef struct SoundReplayQueue {
    u8 nodeHeader[0x14];
    u8 head;
    u8 tail;
    SoundReplayEventRecord entries[14];
} SoundReplayQueue; // overlays DrawingSceneStruct, size 0x40

#define SOUND_REPLAY_QUEUE_CAPACITY \
    ((int)(sizeof(((SoundReplayQueue*)0)->entries) / sizeof(SoundReplayEventRecord)))

static SoundReplayQueue* lbl_3_bss_1768;

// .text:0x0008B258 size:0x8C mapped:0x806CA2EC
BOOL addToCircularBuffer(u8 arg1, u8 arg2, u8 arg3) {
    u8 head;
    u8 next;

    if (lbl_3_bss_1768 == NULL) {
        goto fail;
    }

    head = lbl_3_bss_1768->head;
    next = (head + 1) % SOUND_REPLAY_QUEUE_CAPACITY;
    if (next == lbl_3_bss_1768->tail) {
fail:
        return FALSE;
    }

    lbl_3_bss_1768->head = next;
    lbl_3_bss_1768->entries[head].arg1 = arg2;
    lbl_3_bss_1768->entries[head].arg2 = arg1;
    lbl_3_bss_1768->entries[head].arg3 = arg3;
    return TRUE;
}

// .text:0x0008B2E4 size:0x34 mapped:0x806CA378
void fn_3_8B2E4(void) {
    lbl_3_bss_1768 = (SoundReplayQueue*)insertGraphicDrawingFunction(fn_3_8B094, 0);
}

// .text:0x0008B718 size:0xC4 mapped:0x806CA7AC
void fn_3_8B718(Vec* pos, Vec* dir, Vec* lookDir) {
    camera_803c639c_s* cam = returnFloatFromModeIndex(0);

    if (pos != NULL) {
        pos->x = cam->eye.x;
        pos->y = cam->eye.y;
        pos->z = cam->eye.z;
    }

    if (dir != NULL) {
        dir->x = lbl_3_rodata_157C;
        dir->y = lbl_3_rodata_157C;
        dir->z = lbl_3_rodata_157C;
    }

    if (lookDir != NULL) {
        f32 mag;

        PSVECSubtract(&cam->target, &cam->eye, lookDir);
        mag = PSVECMag(lookDir);
        if (mag != lbl_3_rodata_157C) {
            PSVECNormalize(lookDir, lookDir);
        }
    }
}

// .text:0x0008B7DC size:0x28 mapped:0x806CA870
void fn_3_8B7DC(void) {
    sndRemoveListener(&sndEmitter.listener);
}

// .text:0x0008B804 size:0x8C mapped:0x806CA898
void fn_3_8B804(void) {
    int i;

    for (i = 0; i < 100; i++) {
        if (sndEmitter.emitterActive[i]) {
            if (sndCheckEmitter(&sndEmitter.emitters[i])) {
                sndRemoveEmitter(&sndEmitter.emitters[i]);
            }
            sndEmitter.emitterActive[i] = FALSE;
        }
    }
}

extern SND_FVECTOR emitterPosX;
extern SND_FVECTOR emitterDirX;

// .text:0x0008B890 size:0xD4 mapped:0x806CA924
void updateAndRemoveStadiumEmitter(int emitterID) {
    SND_EMITTER* em;
    SND_FVECTOR pos;
    SND_FVECTOR dir;

    if (emitterID >= 0 && emitterID < 100) {
        if (sndEmitter.emitterActive[emitterID]) {
            em = &sndEmitter.emitters[emitterID];
            if (sndCheckEmitter(em)) {
                pos = emitterPosX;
                dir = emitterDirX;
                sndUpdateEmitter(em, &pos, &dir, 0, NULL);
                sndRemoveEmitter(em);
            }
        }
    }
}

// .text:0x0008B964 size:0x58 mapped:0x806CA9F8
void fn_3_8B964(SND_FVECTOR* pos, SND_FVECTOR* dir, SND_FVECTOR* heading) {
    if (sndEmitter.listener.room != NULL) {
        sndUpdateListener(&sndEmitter.listener, pos, dir, heading, &lbl_3_data_8D70, 0x7f, NULL);
    }
}

// .text:0x0008B9BC size:0xA4 mapped:0x806CAA50
void fn_3_8B9BC(SND_FVECTOR* pos) {
    SND_FVECTOR heading;
    SND_FVECTOR dir;

    heading.x = lbl_3_rodata_157C;
    heading.y = lbl_3_rodata_157C;
    heading.z = lbl_3_rodata_1580;
    dir.x = lbl_3_rodata_157C;
    dir.y = lbl_3_rodata_157C;
    dir.z = lbl_3_rodata_157C;

    sndRemoveListener(&sndEmitter.listener);
    sndAddListener(&sndEmitter.listener, pos, &dir, &heading, &lbl_3_data_8D70, lbl_3_data_88AC,
                   lbl_3_data_88AC, lbl_3_data_88AC, SND_LISTENER_DOPPLERFX, 0x7f, NULL);
}

// .text:0x0008BA60 size:0x164 mapped:0x806CAAF4
void updateOrRemoveEmitter(int emitterID, Vec* pos, Vec* vel) {
    return;
}

// .text:0x0008BBC4 size:0x230 mapped:0x806CAC58
int initializeStadiumObjectEmitter(int soundId, Vec* pos, Vec* vel, int arg) {
    return 0;
}

// .text:0x0008BDF4 size:0x98 mapped:0x806CAE88
void fn_3_8BDF4(void) {
    fn_3_8B804();
    fn_3_8B7DC();
}

// .text:0x0008BE8C size:0x1F0 mapped:0x806CAF20
void initializeCamera(void) {
    return;
}

// .text:0x0008C07C size:0x88 mapped:0x806CB110
void transitionToReplay(void) {
    addToCircularBuffer(4, 0, 0);
}

// .text:0x0008C104 size:0x1D8 mapped:0x806CB198
void fn_3_8C104(void) {
    return;
}

// .text:0x0008C2DC size:0x214 mapped:0x806CB370
void fn_3_8C2DC(void) {
    return;
}

// Base of a foreign region; only the flag byte at +0x1 and the averaged
// hi/lo bytes at +0x10/+0x11 (used by fn_3_8C4F0) are proven.
extern u8 lbl_3_bss_1760[0x14];

extern u16 fn_800A8864(u32 arg1, u32 arg2);
extern void fn_800A8878(u8 arg1, u8 arg2);

// .text:0x0008C4F0 size:0xD8 mapped:0x806CB584
BOOL fn_3_8C4F0(u32 arg1, u32 arg2) {
    u8* state = lbl_3_bss_1760;
    u16 packed = fn_800A8864(arg1, arg2);
    u8 hi = (u8)(packed >> 8);
    u8 lo = (u8)packed;
    u8 avgHi;
    s16 diff;

    sound_crowd_EffectsStruct._2F = 0;

    if (state[1] == 0) {
        state[1] = 1;
        state[0x11] = (u8)(hi / arg1);
        state[0x10] = (u8)(lo / arg1);
    }

    avgHi = state[0x11];
    diff = (s16)(hi - avgHi);

    if (diff <= (s16)(u8)arg2 || arg1 == 1) {
        state[1] = 0;
        fn_800A8878((u8)arg2, (u8)arg2);
        return FALSE;
    }

    fn_800A8878((u8)diff, (u8)(lo - state[0x10]));
    return TRUE;
}

// .text:0x0008C5C8 size:0x7AC mapped:0x806CB65C
void makeSoundOfBallBouncing(void) {
    return;
}

// .text:0x0008CD74 size:0xC4C mapped:0x806CBE08
#pragma dont_inline on
void handleGameSound(void) {
    return;
}
#pragma dont_inline reset

// .text:0x0008D9C0 size:0xC0 mapped:0x806CCA54
void fn_3_8D9C0(void) {
    camera_803c639c_s* cam;
    Vec pos;
    Vec dir;
    Vec lookDir;
    f32 mag;

    handleGameSound();
    cam = returnFloatFromModeIndex(0);

    pos.x = cam->eye.x;
    pos.y = cam->eye.y;
    pos.z = cam->eye.z;

    dir.x = lbl_3_rodata_157C;
    dir.y = lbl_3_rodata_157C;
    dir.z = lbl_3_rodata_157C;

    PSVECSubtract(&cam->target, &cam->eye, &lookDir);
    mag = PSVECMag(&lookDir);
    if (mag != lbl_3_rodata_157C) {
        PSVECNormalize(&lookDir, &lookDir);
    }

    if (sndEmitter.listener.room != NULL) {
        sndUpdateListener(&sndEmitter.listener, (SND_FVECTOR*)&pos, (SND_FVECTOR*)&dir,
                           (SND_FVECTOR*)&lookDir, &lbl_3_data_8D70, 0x7f, NULL);
    }
}

// .text:0x0008DA80 size:0x1748 mapped:0x806CCB14
void soundControl(void) {
    return;
}

// .text:0x0008F1C8 size:0x54 mapped:0x806CE25C
void fn_3_8F1C8(void) {
    sound_crowd_EffectsStruct._20 = -1;
    sound_crowd_EffectsStruct._22 = -1;
    sound_crowd_EffectsStruct._29 = 0;
    sound_crowd_EffectsStruct._2A = 0;
    lbl_3_bss_1768 = (SoundReplayQueue*)insertGraphicDrawingFunction(fn_3_8B094, 0);
}

// .text:0x0008F21C size:0x9F0 mapped:0x806CE2B0
void soundFxRelated(void) {
    return;
}

// .text:0x0008FC0C size:0x74 mapped:0x806CECA0
void newAtBatPlaySound(void) {
    sound_crowd_EffectsStruct._26 = 0;

    if (sound_crowd_EffectsStruct._10 != -1) {
        sndFXKeyOff(sound_crowd_EffectsStruct._10);
        sound_crowd_EffectsStruct._10 = -1;
    }

    if (sound_crowd_EffectsStruct._14 != -1) {
        sndFXKeyOff(sound_crowd_EffectsStruct._14);
        sound_crowd_EffectsStruct._14 = -1;
    }
}

// .text:0x0008FC80 size:0x298 mapped:0x806CED14
void adjustBallSoundEffectBasedOnHeight(void) {
    return;
}

// .text:0x0008FF18 size:0x44 mapped:0x806CEFAC
void initializeSounds(void) {
    sound_crowd_EffectsStruct._0C = -1;
    lbl_3_bss_1780[0] = -1;
    sound_crowd_EffectsStruct._10 = -1;
    sound_crowd_EffectsStruct._14 = -1;
    sound_crowd_EffectsStruct._18 = -1;
    sound_crowd_EffectsStruct._1C = -1;
    sound_crowd_EffectsStruct._28 = 0;
    sound_crowd_EffectsStruct._04 = -1;
    sound_crowd_EffectsStruct._08 = -1;
    sound_crowd_EffectsStruct._2F = 0;
    sound_crowd_EffectsStruct._33 = 0;
}

// .text:0x0008FF5C size:0x108 mapped:0x806CEFF0
void animateThrownBall(int objId, f32 x, f32 y, f32 z) {
    return;
}

// .text:0x00090064 size:0xEC mapped:0x806CF0F8
void callSfx(void) {
    return;
}

// The reverb bytes for a character's sound codes live 0x180 bytes after
// charSoundFxVol in .data, in an otherwise unnamed foreign table.
#define CHAR_SOUND_REVERB_OFFSET 0x180

// A scale factor embedded in the same unnamed foreign table as
// charSoundFxVol, 0x300 bytes past its start.
extern f32 lbl_3_data_8830;

// .text:0x00090150 size:0xD0 mapped:0x806CF1E4
SND_VOICEID fn_3_90150(int charID, int soundCode) {
    SND_VOICEID vid;
    u8* reverbTable = charSoundFxVol + soundCode;
    f32 volF = (f32)charSoundFxVol[soundCode];
    f32 reverbF = (f32)reverbTable[CHAR_SOUND_REVERB_OFFSET];
    int fid = soundCode + characterSoundArray[charID];
    u8 vol = (u8)(volF * lbl_3_data_8830);
    u8 reverb = (u8)(reverbF * lbl_3_data_8830);

    vid = sndFXStartEx(fid, vol, 0x3f, 0);
    sndFXCtrl(vid, SND_MIDICTRL_REVERB, reverb);
    return vid;
}

// .text:0x00090220 size:0x74 mapped:0x806CF2B4
SND_VOICEID playCharacterSound(int charID, int soundCode) {
    SND_VOICEID vid;
    u8* reverbTable = charSoundFxVol + soundCode;
    u8 vol = charSoundFxVol[soundCode];
    int fid = soundCode + characterSoundArray[charID];
    u8 reverb = reverbTable[CHAR_SOUND_REVERB_OFFSET];

    vid = sndFXStartEx(fid, vol, 0x3f, 0);
    sndFXCtrl(vid, SND_MIDICTRL_REVERB, reverb);
    return vid;
}

// .text:0x00090294 size:0x68 mapped:0x806CF328
SND_VOICEID playSoundEffect(int soundNumber) {
    SND_VOICEID vid;

    vid = sndFXStartEx(soundNumber, lbl_3_data_8338[soundNumber - SOUND_EFFECT_MIX_FIRST_ID].volume, 0x3f, 0);
    sndFXCtrl(vid, SND_MIDICTRL_REVERB, lbl_3_data_8338[soundNumber - SOUND_EFFECT_MIX_FIRST_ID].reverb);
    return vid;
}

// .text:0x000902FC size:0x2C mapped:0x806CF390
void fn_3_902FC(void) {
    sndVolume(0, 10, 0xff);
}

// .text:0x00090328 size:0x90 mapped:0x806CF3BC
void playOverSounds(int param) {
    if (param < 0) {
        param = 3000;
    }

    if (sndSeqGetValid(sound_crowd_EffectsStruct._04)) {
        sndSeqVolume(0, param, sound_crowd_EffectsStruct._04, SND_SEQVOL_STOP);
    }

    if (sndSeqGetValid(sound_crowd_EffectsStruct._08)) {
        sndSeqVolume(0, param, sound_crowd_EffectsStruct._08, SND_SEQVOL_STOP);
    }
}

// .text:0x000903B8 size:0x7C mapped:0x806CF44C
void fn_3_903B8(void) {
    if (sndSeqGetValid(sound_crowd_EffectsStruct._04)) {
        sndSeqVolume(0, 0xa0, sound_crowd_EffectsStruct._04, SND_SEQVOL_STOP);
    }

    if (sndSeqGetValid(sound_crowd_EffectsStruct._08)) {
        sndSeqVolume(0, 0xa0, sound_crowd_EffectsStruct._08, SND_SEQVOL_STOP);
    }
}

// .text:0x00090674 size:0x88 mapped:0x806CF708
void fn_3_90674(int index) {
    SeqPlayEntry* entry = &lbl_3_data_88E0[index];
    void** arrTable = (void**)lbl_3_bss_1774[0];

    sound_crowd_EffectsStruct._04 = sndSeqPlayEx(entry->sgid, entry->sid, arrTable[index], NULL, 0);
    sndSeqVolume(lbl_3_data_830C[index * 2], 0, sound_crowd_EffectsStruct._04, SND_SEQVOL_CONTINUE);
}

// .text:0x000906FC size:0x58 mapped:0x806CF790
void fn_3_906FC(void) {
    s32* p;
    s32 base;
    s32 i;

    base = sound_crowd_EffectsStruct._00;
    p = (s32*)base;

    for (i = 0; i < (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE ? 1 : 0x14); i++) {
        *p += base;
        p++;
    }

    lbl_3_bss_1774[0] = base;
}

