#include "game/pitching/pitcher_fire_effect.h"
#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_pitcher_fire_effect
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"

// One 0x50-byte particle emitter slot.
typedef struct _FireEmitterSlot {
    /*0x00*/ u32 texture;
    /*0x04*/ s32 effectId;
    /*0x08*/ u8 _08[0x50 - 0x8];
} FireEmitterSlot;

// Four sets of three emitter slots, followed by the hand tracking vectors.
typedef struct _FireEmitterData {
    /*0x000*/ FireEmitterSlot slots[12];
    /*0x3C0*/ u8 _3C0[0x48C - 0x3C0];
    /*0x48C*/ Vec handPos;
    /*0x498*/ Vec handOffset;
} FireEmitterData;

typedef struct _FireEmitterHeader {
    /*0x00*/ u32 texture;
    /*0x04*/ u8 _04[0x44 - 0x4];
} FireEmitterHeader;

// The part of the shared effects block (lbl_3_common_bss_35154, used by ~30 units) that this
// unit touches.
typedef struct _FireSharedBlock {
    /*0x000*/ u8 _000[0x4];
    /*0x004*/ u32 burstTexture;
    /*0x008*/ u8 _008[0x440 - 0x8];
    /*0x440*/ Vec trailStart;
    /*0x44C*/ Vec trailEnd;
    /*0x458*/ u8 _458[0x480 - 0x458];
} FireSharedBlock;

typedef struct _FireAnimActor {
    /*0x000*/ u8 _000[0x25A];
    /*0x25A*/ u8 mirrored;
} FireAnimActor;

extern FireSharedBlock lbl_3_common_bss_35154;
extern struct {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ FireAnimActor* actors[(0x3154 - 0x2C50) / 4];
} hugeAnimStruct;
extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;

extern FireEmitterData lbl_3_data_17DC0;
extern FireEmitterHeader lbl_3_data_18180[];
extern u16 lbl_3_data_6660[];

extern void fn_8002F5F4(Vec* start, Vec* dir);
extern void fn_80030D88(Vec* start, Vec* dir, FireEmitterSlot* slot, int arg);
extern void fn_80030470(Vec* start, Vec* dir, Vec* end, FireEmitterSlot* slot, int arg);

// .text:0x000CB538 size:0x17C mapped:0x8070A5CC
void fn_3_CB538(int mode) {
    Vec dir;
    Vec end;
    int set;
    FireEmitterSlot* slot;
    FireEmitterSlot* it;
    FireEmitterHeader* hdr;
    Vec* start;
    Vec* last;
    int i;

    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        set = 2;
    } else {
        set = g_Ball.framesSinceHit > 0;
    }
    last = &lbl_3_common_bss_35154.trailEnd;
    start = &lbl_3_common_bss_35154.trailStart;
    PSVECSubtract(last, start, &dir);
    if (PSVECMag(&dir) != 0.0f) {
        slot = &lbl_3_data_17DC0.slots[set * 3];
        slot[2].texture = lbl_3_common_bss_35154.burstTexture;
        slot[1].texture = lbl_3_common_bss_35154.burstTexture;
        hdr = &lbl_3_data_18180[set];
        hdr->texture = lbl_3_common_bss_35154.burstTexture;
        slot[0].texture = lbl_3_common_bss_35154.burstTexture;
        if (mode == 2) {
            slot[0].effectId = 0x1B;
            slot[1].effectId = 0x1C;
        } else {
            slot[0].effectId = 0x15;
            slot[1].effectId = 7;
        }
        fn_8002F5F4(start, &dir);
        if (lbl_80366158._28 == 0) {
            it = &slot[1];
            i = 1;
            do {
                fn_80030D88(start, &dir, it, 5);
                i++;
                it++;
            } while (i < 3);
            PSVECNormalize(&dir, &dir);
            PSVECSubtract(start, last, &end);
            fn_80030470(start, &dir, &end, slot, 5);
        }
    }
}

// .text:0x000CB3AC size:0x18C mapped:0x8070A440
void animatePitchersHandOnFire(void) {
    FireEmitterData* data = &lbl_3_data_17DC0;
    FireAnimActor* actor = hugeAnimStruct.actors[0];
    FireEmitterSlot* slots;
    FireEmitterSlot* slot0;
    FireEmitterSlot* slot1;
    FireEmitterSlot* slot2;
    Vec pos;
    int i;
    u16 anim;

    if (PSVECMag(&data->handPos) != 0.0f && actor != NULL) {
        slots = data->slots;
        slot0 = &slots[9];
        slot1 = &slots[10];
        slot2 = &slots[11];
        slot2->texture = lbl_3_common_bss_35154.burstTexture;
        slot1->texture = lbl_3_common_bss_35154.burstTexture;
        slot0->texture = lbl_3_common_bss_35154.burstTexture;
        slot0->effectId = 0x15;
        slot1->effectId = 7;
        anim = 0x1A;
        if (actor->mirrored != 0) {
            i = 0;
            do {
                if (lbl_3_data_6660[i * 2] == 0x1A) {
                    anim = lbl_3_data_6660[i * 2 + 1];
                    break;
                }
                if (lbl_3_data_6660[i * 2 + 1] == 0x1A) {
                    anim = lbl_3_data_6660[i * 2];
                    break;
                }
                i++;
            } while (lbl_3_data_6660[i * 2] != 0xFFFF);
        }
        getAnimRelatedCoordinates(0, anim, (VecXYZ*)&pos);
        PSVECAdd(&pos, &data->handOffset, &pos);
        if (lbl_80366158._28 == 0) {
            fn_80030D88(&pos, &data->handPos, slot1, 5);
            fn_80030D88(&pos, &data->handPos, slot2, 5);
            fn_80030470(&pos, &data->handPos, &data->handPos, slot0, 5);
        }
    }
}
