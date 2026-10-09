#ifndef __GAME_ANIMATION_ANIMATION_INIT_H_
#define __GAME_ANIMATION_ANIMATION_INIT_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

#define ANIM_SLOT_COUNT 13

/* One row of the setup tables (lbl_3_data_1E434, lbl_3_data_1F090, lbl_3_data_1D28). */
typedef struct AnimSetupEntry {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ f32 _0C;
    /*0x10*/ s16 animId;
    /*0x12*/ s16 _12;
    /*0x14*/ u8 slot;
    /*0x15*/ u8 _15;
    /*0x16*/ u8 _16;
    /*0x17*/ u8 _17;
    /*0x18*/ u8 _18;
    /*0x19*/ u8 _19;
    /*0x1A*/ u8 _1A[2];
} AnimSetupEntry; // size: 0x1C

/* Per-slot record inside AnimScreenState, 0x2C bytes each. */
typedef struct AnimStateSlot {
    /*0x00*/ u8 _00[0x0C];
    /*0x0C*/ f32 _0C;
    /*0x10*/ u8 _10[0x2C - 0x10];
} AnimStateSlot;

/* Entry of the hugeAnimStruct object table at +0x2C50, one per slot. */
typedef struct AnimObject {
    /*0x000*/ u8 _000[0x34];
    /*0x034*/ VecXYZ pos;
    /*0x040*/ f32 _40;
    /*0x044*/ f32 _44;
    /*0x048*/ f32 _48;
    /*0x04C*/ u8 _04C[0x257 - 0x4C];
    /*0x257*/ s8 _257;
    /*0x258*/ u8 _258[0x25D - 0x258];
    /*0x25D*/ u8 _25D;
    /*0x25E*/ u8 _25E[0x279 - 0x25E];
    /*0x279*/ u8 _279;
} AnimObject;

typedef struct AnimActorView {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ AnimObject *objects[ANIM_SLOT_COUNT];
} AnimActorView;

/* The block pointed to by lbl_3_common_bss_1323C. */
typedef struct AnimScreenState {
    /*0x000*/ AnimStateSlot slots[ANIM_SLOT_COUNT];
    /*0x23C*/ s16 _23C;
    /*0x23E*/ s16 _23E;
    /*0x240*/ s16 _240[ANIM_SLOT_COUNT];
    /*0x25A*/ s16 _25A;
    /*0x25C*/ u8 _25C;
    /*0x25D*/ u8 _25D;
    /*0x25E*/ u8 _25E;
    /*0x25F*/ u8 _25F;
    /*0x260*/ u8 _260;
    /*0x261*/ u8 _261[ANIM_SLOT_COUNT];
    /*0x26E*/ u8 _26E[ANIM_SLOT_COUNT];
    /*0x27B*/ u8 _27B;
    /*0x27C*/ u8 _27C;
    /*0x27D*/ u8 _27D;
    /*0x27E*/ u8 _27E;
    /*0x27F*/ u8 _27F;
    /*0x280*/ u8 _280;
    /*0x281*/ u8 _281[0x288 - 0x281];
} AnimScreenState;

void fn_3_249E8(int setupIndex);
void fn_3_24ADC(int setupIndex, int queueAnim);
void fn_3_24DBC(int value);
void fn_3_24EA0(void);
void fn_3_24F20(void);
void fn_3_24F24(int scriptIndex);
void initializeAnimations(void);

#endif // !__GAME_ANIMATION_ANIMATION_INIT_H_
