#define SQRT2_LINKAGE static
#include "game/ball/ball_fielder_collision.h"
#include "header_rep_data.h"

#include "game/UnknownHomes_Game.h"
#include "game/ball/collision_primitives.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x8001b728.h"
#include "Unknown/File_0x800527c4.h"
#include "Unknown/File_0x80033794.h"
#include "Unknown/File_0x80033f64.h"
#include "game/stadium/stadium_framework.h"
#include "musyx/musyx.h"
#include "game/sound/m_sound.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "Dolphin/rand.h"
#include "stl/math.h"
#include "stl/string.h"

extern u8 hugeAnimStruct[0x3154];

typedef struct _FielderAnimObject {
    /*0x000*/ u8 _000[0x276];
    /*0x276*/ u8 _276;
} FielderAnimObject;

#define FIELDER_ANIM_OBJECTS ((FielderAnimObject**)(hugeAnimStruct + 0x2C50))

extern u16 stadiumHazardSoundIDs[16];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 lbl_3_data_84B8[0x3C];

typedef struct _DustParticle {
    /*0x00*/ struct _DustParticle* next;
    /*0x04*/ Vec pos;
    /*0x10*/ Vec vel;
    /*0x1C*/ f32 rotSpeed;
    /*0x20*/ f32 rot;
    /*0x24*/ f32 rotLimit;
    /*0x28*/ u8 _28[0x38 - 0x28];
    /*0x38*/ f32 scaleX;
    /*0x3C*/ f32 scaleY;
    /*0x40*/ u8 color[3];
    /*0x43*/ u8 alpha;
    /*0x44*/ u8 _44[4];
    /*0x48*/ s16 rotDir;
    /*0x4A*/ s16 lifetime;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ u8 _4D;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
} DustParticle; // size: 0x50

typedef struct _DustEmitter {
    /*0x00*/ u8 _00[0x0C];
    /*0x0C*/ DustParticle* particles;
    /*0x10*/ void* texture;
    /*0x14*/ u16 flags : 4;
    /*0x14*/ u16 count : 12;
} DustEmitter;

typedef struct _DustParams {
    /*0x00*/ s32 _00;
    /*0x04*/ s32 lifetime;
    /*0x08*/ s32 _08;
    /*0x0C*/ s32 fadeFrames;
    /*0x10*/ s32 _10;
    /*0x14*/ s32 scale;
    /*0x18*/ s32 speedXZ;
    /*0x1C*/ s32 speedY;
    /*0x20*/ s32 drag;
    /*0x24*/ s32 gravity;
    /*0x28*/ s32 rotSpeed;
    /*0x2C*/ s32 rotLimit;
    /*0x30*/ s32 shadeBase;
    /*0x34*/ s32 shadeRange;
    /*0x38*/ s32 _38;
    /*0x3C*/ s32 _3C;
} DustParams; // size: 0x40

DustParams lbl_3_data_2A408 = {
    41, 120, 240, 40, 10, 80000, 10000, 15000, 10000, 300, 10, 60, 200, 55, 26, 0,
};
extern void* lbl_803CBD0C;
extern DustParticle* fn_80031F34(DustParticle* particles, int count);

// .text:0x0016D5E4 size:0x22C mapped:0x807AC678
void processBallFielderCollision(u8 source) {
    Vec pos;
    f32 threshold;
    f32 speed;
    InMemFielder* fielder;

    if (g_d_GameSettings.StadiumID == STADIUM_ID_PEACH_GARDEN) {
        threshold = 1.5f;
    } else {
        threshold = 0.07f;
    }
    if (source) {
        fielder = &g_Fielders[source - 1];
        if (!checkFielderCollisionPotential(threshold, source - 1)) {
            return;
        }
        if (fielder->currentVelocity < 0.1f) {
            return;
        }
        memcpy(&pos, &fielder->pos, sizeof(Vec));
        pos.y = threshold;
    } else {
        speed = PSVECMag((Vec*)&g_Ball.physicsSubstruct.velocity);
        if (g_Ball.AtBat_Contact_BallPos.y <= threshold) {
            if ((g_Ball.maybeCollisionRelated & 0x7F) == BALL_COLLISION_TYPE_ROUGH_TERRAIN &&
                g_Ball.pastCoordinates[0].y <= threshold) {
                return;
            }
            if (speed >= 0.05) {
                memcpy(&pos, &g_Ball.AtBat_Contact_BallPos, sizeof(Vec));
            } else {
                return;
            }
        } else {
            return;
        }
    }
    if (isWorldPosOnScreen(&pos)) {
        fn_3_16CC2C(&pos, source);
    }
}

// .text:0x0016D4D8 size:0x10C mapped:0x807AC56C
u8 checkFielderCollisionPotential(f32 height, u8 fielderIndex) {
    Vec offset = { 0.0f, 0.0f, 0.0f };
    f32 lowY;

    if (FIELDER_ANIM_OBJECTS[fielderIndex]->_276 & 6) {
        return TRUE;
    }
    getAnimationCollisionOffset(fielderIndex, 0x23, &offset);
    lowY = -offset.y;
    offset.x = offset.y = offset.z = 0.0f;
    getAnimationCollisionOffset(fielderIndex, 0x1F, &offset);
    if ((height >= lowY) | (height >= -offset.y)) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x0016CC2C size:0x8AC mapped:0x807ABCC0
void fn_3_16CC2C(Vec* pos, u8 source) {
    u8 scratch[0x60];
    int count;
    int sfx;
    DustEmitter* existing;
    DustEmitter* added;
    DustEmitter* emitter;
    DustParticle* tail;
    u8 stadiumID;
    SND_VOICEID voice;

    if (source) {
        if (g_d_GameSettings.StadiumID == STADIUM_ID_PEACH_GARDEN) {
            count = 3;
        } else {
            count = 3;
        }
    } else if (g_d_GameSettings.StadiumID == STADIUM_ID_PEACH_GARDEN) {
        count = 20;
    } else {
        count = 3;
    }
    existing = fn_800339F0(0, 0x1A);
    if (existing != NULL) {
        added = fn_800337CC(scratch, count, 1);
        if (added == NULL) {
            return;
        }
        fn_3_16C878(pos, added, count);
        tail = existing->particles;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = added->particles;
        existing->count += added->count;
    } else {
        emitter = allocParticleEffect(fn_3_16C548, 0x80, 0, count, TRUE, 0x1A);
        if (emitter != NULL) {
            emitter->count = count;
            fn_3_16C878(pos, emitter, count);
        } else {
            return;
        }
    }
    if (source) {
        if (g_d_GameSettings.StadiumID == STADIUM_ID_PEACH_GARDEN) {
            sfx = 5;
        } else {
            sfx = 14;
        }
    } else if (g_d_GameSettings.StadiumID == STADIUM_ID_PEACH_GARDEN) {
        sfx = 4;
    } else {
        sfx = 13;
    }
    stadiumID = g_d_GameSettings.StadiumID;
    if (stadiumID == STADIUM_ID_PEACH_GARDEN) {
        voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + sfx,
                             g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                                 ? lbl_3_data_84B8[sfx * 2]
                                 : stadiumHazardSoundFxRelated[stadiumID * 0x1E + sfx * 2],
                             0x3F, 0);
        sndFXCtrl(voice, 0x5B,
                  g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                      ? lbl_3_data_84B8[sfx * 2 + 1]
                      : stadiumHazardSoundFxRelated[stadiumID * 0x1E + sfx * 2 + 1]);
    }
}

// .text:0x0016C878 size:0x3B4 mapped:0x807AB90C
void fn_3_16C878(Vec* pos, DustEmitter* emitter, int count) {
    DustParticle* p = emitter->particles;
    u32 i = 0;
    f32 angle;
    f32 speed;
    int shade;

    emitter->texture = lbl_803CBD0C;
    for (; p != NULL; p = p->next) {
        p->rotDir = 0;
        p->vel.y = lbl_3_data_2A408.speedY / 100000.0f + (rand() % 100 - 50) / 1000.0;
        angle = 0.017453292f * (360.0 / count * i);
        speed = lbl_3_data_2A408.speedXZ / 100000.0f + (rand() % 100 - 50) / 1000.0;
        p->vel.x = speed * (f32)cos(angle);
        p->vel.z = speed * (f32)sin(angle);
        p->scaleX = p->scaleY = lbl_3_data_2A408.scale / 100000.0f;
        p->pos.x = pos->x;
        p->pos.y = -pos->y;
        p->pos.z = pos->z;
        p->rotSpeed = lbl_3_data_2A408.rotSpeed - (rand() % 5 + 1);
        p->rot = 0.0f;
        p->rotLimit = lbl_3_data_2A408.rotLimit - (rand() % 30 + 1);
        p->rotDir = rand() % 2 * -2 + 1;
        shade = lbl_3_data_2A408.shadeBase + (rand() % lbl_3_data_2A408.shadeRange + 1);
        i++;
        p->color[0] = p->color[1] = p->color[2] = shade;
        p->alpha = 0xFF;
        p->lifetime = lbl_3_data_2A408.lifetime;
        p->_4D = lbl_3_data_2A408._00;
        p->_4E = 0;
    }
}

// .text:0x0016C548 size:0x330 mapped:0x807AB5DC
BOOL fn_3_16C548(DustEmitter* emitter) {
    int alive = 0;
    DustParticle* p;
    DustParticle** link;
    DustParticle* deadTail;
    DustParticle* deadHead;
    int alpha;

    p = emitter->particles = fn_80031F34(emitter->particles, emitter->count);
    link = &emitter->particles;
    deadTail = NULL;
    deadHead = NULL;
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    do {
        if (p->lifetime != 0) {
            setParticleXform(p->scaleX, p->scaleY, p->rot);
            fn_80033CC8(p, (int)emitter->texture);
            if (p->lifetime < lbl_3_data_2A408.fadeFrames) {
                alpha = p->alpha - 255.0f / lbl_3_data_2A408.fadeFrames;
                if (alpha < 0) {
                    alpha = 0;
                }
                p->alpha = alpha;
            }
            p->pos.x += p->vel.x;
            p->pos.y -= p->vel.y;
            p->pos.z += p->vel.z;
            if (p->pos.y > 0.0f) {
                p->pos.y = 0.0f;
            }
            p->vel.x -= p->vel.x * (lbl_3_data_2A408.drag / 100000.0f);
            p->vel.y -= p->vel.y * (lbl_3_data_2A408.drag / 100000.0f);
            p->vel.z -= p->vel.z * (lbl_3_data_2A408.drag / 100000.0f);
            p->vel.y -= lbl_3_data_2A408.gravity / 100000.0f;
            p->rot = p->rotSpeed * p->rotDir + p->rot;
            if (p->rotLimit < p->rot * p->rotDir) {
                p->rot = p->rotLimit * p->rotDir;
                p->rotDir *= -1;
            }
            p->lifetime--;
            if (p->lifetime == 0) {
                *link = p->next;
                if (deadTail != NULL) {
                    deadTail->next = p;
                } else {
                    deadHead = p;
                }
                deadTail = p;
                p->next = NULL;
                emitter->count--;
            } else {
                link = &p->next;
                alive++;
            }
        }
        p = *link;
    } while (p != NULL);
    if (deadHead != NULL) {
        for (p = deadHead; p != NULL; p = p->next) {
            p->_4C = 0;
            p->rotDir = 0;
        }
        fn_80033794(deadHead);
    }
    return alive == 0;
}
