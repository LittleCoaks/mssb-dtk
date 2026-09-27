#ifndef __GAME_BATTING_STAR_SWING_PEACH_DAISY_H_
#define __GAME_BATTING_STAR_SWING_PEACH_DAISY_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

// One entry of the per-side (Peach = 0, Daisy = 1) star-swing prediction tables.
typedef struct _StarSwingEntryA {
    u32 unk0;
    int unk4;
    int unk8;
    int frameCount;
    int unk10;
    int unk14;
    int unk18;
    int unk1c;
    int unk20;
    int unk24;
    int unk28;
    int unk2c;
    int unk30;
    int unk34;
    int unk38;
    int unk3c;
    int unk40;
    int unk44;
} StarSwingEntryA; // size: 0x48

// One entry of Daisy's ball-trajectory-based star-swing prediction table.
typedef struct _StarSwingEntryB {
    u32 unk0;
    int unk4;
    int unk8;
    int unkC;
    int frames;
    int unk14;
    int unk18;
    int unk1c;
    int unk20;
    int unk24;
    int unk28;
    int unk2c;
    int unk30;
    int unk34;
    int unk38;
    int unk3c;
    int unk40;
    int unk44;
    int unk48;
    int unk4c;
    int unk50;
    int unk54;
    int unk58;
    int unk5c;
    int unk60;
    int unk64;
    int unk68;
    int unk6c;
    int unk70;
    int unk74;
    int unk78;
    int unk7c;
    int unk80;
} StarSwingEntryB; // size: 0x84

void peachDaisyStarPitch_updateEffectTarget(BOOL side);
void peachDaisyStarEffect_setup(int side);
void peachDaisyStarSwingRelated2(void);
int peachDaisyStarSwingRelated(void);
void peachDaisyStarPitch_stepPhysics(VecXYZ* pos, VecXYZ* vel, VecXYZ* accel, BOOL applySteer);

#endif // !__GAME_BATTING_STAR_SWING_PEACH_DAISY_H_
