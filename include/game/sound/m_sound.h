#ifndef __GAME_SOUND_M_SOUND_H_
#define __GAME_SOUND_M_SOUND_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"

BOOL addToCircularBuffer(u8 arg1, u8 arg2, u8 arg3);
void fn_3_8B2E4(void);
void fn_3_8B718(Vec* pos, Vec* dir, Vec* lookDir);
void fn_3_8B7DC(void);
void fn_3_8B804(void);
void updateAndRemoveStadiumEmitter(int emitterID);
void fn_3_8B964(struct SND_FVECTOR* pos, struct SND_FVECTOR* dir, struct SND_FVECTOR* heading);
void fn_3_8B9BC(struct SND_FVECTOR* pos);
void updateOrRemoveEmitter(void);
void initializeStadiumObjectEmitter(int soundId, Vec* pos, Vec* vel, int arg);
void fn_3_8BDF4(void);
void initializeCamera(void);
void transitionToReplay(void);
void fn_3_8C104(void);
void fn_3_8C2DC(void);
void fn_3_8C4F0(void);
void makeSoundOfBallBouncing(void);
void handleGameSound(void);
void fn_3_8D9C0(void);
void soundControl(void);
void fn_3_8F1C8(void);
void soundFxRelated(void);
void newAtBatPlaySound(void);
void adjustBallSoundEffectBasedOnHeight(void);
void initializeSounds(void);
void animateThrownBall(void);
void callSfx(void);
void fn_3_90150(void);
void fn_3_902FC(void);
void fn_3_906FC(void);

#endif // !__GAME_SOUND_M_SOUND_H_
