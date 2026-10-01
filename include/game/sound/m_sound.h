#ifndef __GAME_SOUND_M_SOUND_H_
#define __GAME_SOUND_M_SOUND_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"

BOOL addToCircularBuffer(u8 arg1, u8 arg2, u8 arg3);
void fn_3_8B2E4(void);
void stadiumMusic(int stadiumID);
void fn_3_8B718(Vec* pos, Vec* dir, Vec* lookDir);
void fn_3_8B7DC(void);
void fn_3_8B804(void);
void updateAndRemoveStadiumEmitter(int emitterID);
void fn_3_8B964(struct SND_FVECTOR* pos, struct SND_FVECTOR* dir, struct SND_FVECTOR* heading);
void fn_3_8B9BC(struct SND_FVECTOR* pos);
void updateOrRemoveEmitter(int emitterID, Vec* pos, Vec* vel);
int initializeStadiumObjectEmitter(int soundId, Vec* pos, Vec* vel, int arg);
void fn_3_8BDF4(void);
void initializeCamera(void);
void transitionToReplay(void);
void fn_3_8C104(int arg0);
BOOL fn_3_8C2DC(u32 arg1, u32 arg2);
BOOL fn_3_8C4F0(u32 arg1, u32 arg2);
void makeSoundOfBallBouncing(void);
void handleGameSound(void);
void fn_3_8D9C0(void);
void soundControl(void);
void fn_3_8F1C8(void);
void soundFxRelated(void);
void newAtBatPlaySound(void);
void adjustBallSoundEffectBasedOnHeight(void);
void initializeSounds(void);
u32 animateThrownBall(int soundNumber, f32 x, f32 y, f32 z);
u32 callSfx(int soundId);
u32 fn_3_90150(int charID, int soundCode);
u32 playCharacterSound(int charID, int soundCode);
u32 playSoundEffect(int soundNumber);
void fn_3_902FC(void);
void playOverSounds(int param);
void fn_3_903B8(void);
void fn_3_90434(void);
BOOL fn_3_9056C(int index);
void fn_3_90674(int index);
void fn_3_906FC(void);

#endif // !__GAME_SOUND_M_SOUND_H_
