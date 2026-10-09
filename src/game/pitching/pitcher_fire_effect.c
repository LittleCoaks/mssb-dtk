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
    /*0x08*/ u32 _08[(0x50 - 0x8) / 4];
} FireEmitterSlot;

typedef struct _FireEmitterHeader {
    /*0x00*/ u32 texture;
    /*0x04*/ u32 _04[(0x44 - 0x4) / 4];
} FireEmitterHeader;

// Four sets of three emitter slots, three emitter headers, then the hand tracking vectors.
typedef struct _FireEmitterData {
    /*0x000*/ FireEmitterSlot slots[12];
    /*0x3C0*/ FireEmitterHeader headers[3];
    /*0x48C*/ Vec handPos;
    /*0x498*/ Vec handOffset;
    /*0x4A4*/ u32 _4A4;
} FireEmitterData;

// The 0x58-byte emitter config passed to fn_8002955C; the first word is its texture.
typedef struct _FireEmitterConfig {
    /*0x00*/ u32 texture;
    /*0x04*/ u8 _04[0x58 - 0x4];
} FireEmitterConfig;

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

static FireEmitterData lbl_3_data_17DC0 = {
    {
        {
            0x0, 0x15,
            {
                0x5, 0x445C0, 0x0, 0x0, 0x4, 0x2,
                0x1D4C0, 0x15F90, 0x0, 0x80, 0xF4240, 0xF4240,
                0xFFF85EE0, 0x7A120, 0xFFFFFF00, 0x0, 0xFFFF92A0, 0x1,
            },
        },
        {
            0x0, 0x7,
            {
                0xA, 0x130B0, 0xEA60, 0xC350, 0xC, 0x6,
                0x1A9C8, 0x18A88, 0x0, 0x28, 0x44AA20, 0x90F560,
                0xFFF0BDC0, 0x44AA20, 0xFFFFFF00, 0x0, 0x0, 0x0,
            },
        },
        {
            0x0, 0x4,
            {
                0x3, 0x15F90, 0x186A0, 0x2710, 0x14, 0xA,
                0x19258, 0x19E0F, 0x0, 0x3C, 0x989680, 0x112A880,
                0xF4240, 0xFFF0BDC0, 0x3C3C3C00, 0x0, 0x0, 0x0,
            },
        },
        {
            0x0, 0x15,
            {
                0x5, 0x445C0, 0x0, 0x0, 0x4, 0x2,
                0x1D4C0, 0x15F90, 0x0, 0x80, 0x7A120, 0xF4240,
                0xFFF85EE0, 0x7A120, 0xFFFFFF00, 0x0, 0xFFFF92A0, 0x1,
            },
        },
        {
            0x0, 0x7,
            {
                0xA, 0x130B0, 0xEA60, 0xC350, 0xC, 0x6,
                0x1A9C8, 0x18A88, 0x0, 0x28, 0x44AA20, 0x90F560,
                0xFFF0BDC0, 0x44AA20, 0xFFFFFF00, 0x0, 0x0, 0x0,
            },
        },
        {
            0x0, 0x4,
            {
                0x3, 0x15F90, 0x186A0, 0x2710, 0x14, 0xA,
                0x19258, 0x19E0F, 0x0, 0x3C, 0x989680, 0x112A880,
                0xF4240, 0xFFF0BDC0, 0x3C3C3C00, 0x0, 0x0, 0x0,
            },
        },
        {
            0x0, 0x15,
            {
                0x5, 0x55730, 0x0, 0x0, 0x4, 0x2,
                0x1D4C0, 0x15F90, 0x0, 0x3C, 0x7A120, 0xF4240,
                0xFFF85EE0, 0x7A120, 0xFFFFFF00, 0x0, 0xFFFF3CB0, 0x1,
            },
        },
        {
            0x0, 0x7,
            {
                0xA, 0x11170, 0x13880, 0xC350, 0x14, 0xA,
                0x1A9C8, 0x1ADB0, 0x0, 0x28, 0x44AA20, 0x895440,
                0xFFBB55E0, 0x44AA20, 0xFFFFFF00, 0x0, 0x0, 0x0,
            },
        },
        {
            0x0, 0x4,
            {
                0x5, 0x15F90, 0x186A0, 0x2710, 0x14, 0xA,
                0x19258, 0x19E0F, 0x0, 0x3C, 0x989680, 0x112A880,
                0x44AA20, 0xFFBB55E0, 0x3C3C3C00, 0x0, 0x0, 0x0,
            },
        },
        {
            0x0, 0x15,
            {
                0x3, 0x222E0, 0x0, 0x0, 0x10, 0x2,
                0x1D4C0, 0x15F90, 0x0, 0x80, 0xF4240, 0xF4240,
                0xFFF85EE0, 0x7A120, 0xFFFFFF00, 0x0, 0xFFFF92A0, 0x1,
            },
        },
        {
            0x0, 0x7,
            {
                0xA, 0x9858, 0x7530, 0xC350, 0xC, 0x6,
                0x1A9C8, 0x18A88, 0x0, 0x28, 0x44AA20, 0x90F560,
                0xFFF0BDC0, 0x44AA20, 0xFFFFFF00, 0x0, 0x0, 0x0,
            },
        },
        {
            0x0, 0x4,
            {
                0x3, 0xAFC8, 0xC350, 0x2710, 0x14, 0xA,
                0x19258, 0x19E0F, 0x0, 0x3C, 0x989680, 0x112A880,
                0xF4240, 0xFFF0BDC0, 0x3C3C3C00, 0x0, 0x0, 0x0,
            },
        },
    },
    {
        {
            0x0,
            {
                0x14, 0x8, 0x7, 0x3D090, 0xC350, 0x86470,
                0x0, 0x0, 0xC, 0xD, 0xE, 0xF,
                0x10, 0x11, 0x12, 0x13,
            },
        },
        {
            0x0,
            {
                0x14, 0x8, 0x7, 0x3D090, 0xC350, 0x86470,
                0x0, 0x0, 0xC, 0xD, 0xE, 0xF,
                0x10, 0x11, 0x12, 0x13,
            },
        },
        {
            0x0,
            {
                0x14, 0x8, 0x7, 0x493E0, 0x186A0, 0x86470,
                0x0, 0x0, 0xC, 0xD, 0xE, 0xF,
                0x10, 0x11, 0x12, 0x13,
            },
        },
    },
    { 0.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, -0.2f },
    { 0 },
};
static FireEmitterConfig lbl_3_data_18268 = {
    0x0,
    {
        0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x64,
        0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x3C,
        0x00, 0x00, 0x46, 0x50, 0x00, 0x00, 0x4E, 0x20,
        0xFF, 0xE1, 0x7B, 0x80, 0x00, 0x1E, 0x84, 0x80,
        0x00, 0x01, 0x38, 0x80, 0x00, 0x01, 0x86, 0xA0,
        0x00, 0x00, 0x00, 0xC8, 0xFF, 0xFF, 0xFF, 0xFF,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    },
};
extern u16 lbl_3_data_6660[];
static u32 lbl_3_bss_9FDC[0xF];

extern void fn_8002F5F4(Vec* start, Vec* dir);
extern void fn_80030D88(Vec* start, Vec* dir, FireEmitterSlot* slot, int arg);
extern void fn_80030470(Vec* start, Vec* dir, Vec* end, FireEmitterSlot* slot, int arg);
extern void fn_8002955C(Vec* pos, int arg, void* emitter);
extern void convertTextureHeader(void* tex);

// .text:0x000CB6EC size:0x4C
void fn_3_CB6EC(f32 x, f32 y, f32 z) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    lbl_3_data_18268.texture = lbl_3_common_bss_35154.burstTexture;
    fn_8002955C(&pos, 0, &lbl_3_data_18268);
}

// .text:0x000CB6B4 size:0x38
void fn_3_CB6B4(void* arg) {
    u32 texture;

    *(u32*)arg += (u32)arg;
    texture = *(u32*)arg;
    lbl_3_bss_9FDC[0] = texture;
    convertTextureHeader((void*)texture);
}

// .text:0x000CB538 size:0x17C mapped:0x8070A5CC
void fn_3_CB538(int mode) {
    Vec dir;
    Vec end;
    int set;
    FireEmitterSlot* slot;
    FireEmitterSlot* it;
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
    if (PSVECMag(&dir)) {
        slot = &lbl_3_data_17DC0.slots[set * 3];
        slot[2].texture = lbl_3_common_bss_35154.burstTexture;
        slot[1].texture = lbl_3_common_bss_35154.burstTexture;
        lbl_3_data_17DC0.headers[set].texture = lbl_3_common_bss_35154.burstTexture;
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

    if (PSVECMag(&data->handPos) && actor != NULL) {
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
