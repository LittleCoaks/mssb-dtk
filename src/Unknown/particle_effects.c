#include "Unknown/particle_effects.h"
#include "Dolphin/mtx.h"
#include <string.h>
#include "Dolphin/GX/GXTexture.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXPixel.h"
#include <math.h>
#include "Unknown/File_0x800b0a14.h"

extern struct {
    /*0x00*/ Mtx mtx;
    /*0x30*/ u8 _30[0x38];
} graphicRelatedStructMaybe;

extern Vec lbl_80180010[4];

extern f32 maybeCosineArray[];
extern Mtx lbl_8017FFE0;
extern Vec lbl_80180010[4];
extern u8 lbl_803CBC84[];
extern void* lbl_803CBC74;
extern u8 lbl_8017EC00[];
extern u8 lbl_80366158[];
extern char lbl_800E688C[];
extern f32 lbl_803CC5F0;
extern f32 lbl_803CC5F4;
extern f32 lbl_803CC650;
void fn_800118AC(void* a, void* b);
void fn_800C07BC(void* base, void* scratch, int count, int size, s32 (*cmp)(const f32*, const f32*));
void* _OSAllocFromHeap(s32 alignment, s32 size);
void fn_800ACFB0(void* block);
void OSReport(const char* message, ...);
s32 fn_80032038(const f32* a, const f32* b);
BOOL fn_8002AC68(u8* group, u8* item);
BOOL fn_8002A85C(u8* group, u8* item);
void fn_8002F9FC(u8* group);
BOOL fn_8002E828(u8* group);
BOOL fn_80027968(u8* group);
BOOL maybeTexOrSpriteRelated(u8* group);
extern u8 g_d_GameSettings[];
extern u8 hugeAnimStruct[];
extern f32 lbl_803CC658;
extern f32 lbl_803CC628;
extern f64 lbl_803CC660;
extern f32 lbl_800F78C0[];
extern u32 lbl_800E685C[];
extern u8 lbl_800E67C0[];
extern u8 lbl_800E67F0[];
extern f32 lbl_803CC624;
extern f32 lbl_803CC608;
extern u8 inputParams[];
extern u8 lbl_80367318[];
extern u8 lbl_803C5090[0x20];
extern s32 lbl_803CBC70;
extern f32 lbl_803CC608;
void characterLightingRelated(void* input, void* output);
extern void* lbl_803CBC80;
extern u8 startOfMinigamePtrStruct[];
extern u8 lbl_801F8040[];
extern u8 lbl_803CBC78;
extern u32 lbl_803CBC7C;
extern u8 lbl_800F7840[];
extern f64 lbl_803CC6E0;
extern f64 pi;
void SetFogNone(void);
u32 returnsCurrentMode(void);
void* returnFloatFromModeIndex(int mode);
extern f32 lbl_803CC6D0;
extern f32 lbl_803CC6D4;
BOOL fn_800328E0(u8* group);
extern u32 lbl_800F787C[];
extern u32 lbl_803CBD0C;
extern f32 lbl_803CC614;
void fn_8002A1CC();
BOOL fn_8002E3DC(u8* group);
void fn_800317C4(void* group, Vec* pos, u8* cfg);
BOOL fn_80031034(u8* group);
void fn_800297F0();
void fn_8002BC84();
BOOL fn_80028F48(u8* group);
extern u8 lbl_800F7860[];
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXTransform.h"
void fn_80027300(u8* group, s32 a0, s32 a1, u8* cfg, f32 scale);
BOOL fn_80026E58(u8* group);
extern u8 lbl_800E6778[];
extern f32 lbl_803CC654;
extern f32 lbl_803CC60C;
extern f32 lbl_803CC618;
extern f32 lbl_803CC61C;
extern f32 lbl_803CC600;
void fn_80030720(void* group, s32 a0, s32 a1, u8* cfg);
void fn_8002FDB8(void* group, s32 a0, s32 a1, s32 a2, u8* cfg);
BOOL fn_8002ECA0(u8* group);

typedef struct ParticleSortEntry {
    u8* node;
    f32 z;
} ParticleSortEntry;

BOOL maybeTexOrSpriteRelated(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    u8* node;
    u8* base = *(u8**)(group + 0x10);
    u8* tex;
    u8* prev;
    u8** link;
    u8* removedHead = NULL;
    u8* removedTail = NULL;
    ParticleSortEntry* buf;
    s32 i;
    s32 k;
    s32 n;
    s32 j;
    s32 count = *(u16*)(group + 0x14) & 0xFFF;
    s32 alive = 0;
    Vec corner[4];
    Vec eye;
    f32 w;
    f32 h;

    GXLoadPosMtxImm(*(Mtx*)(lbl_8017EC00 + 0x13E0), 0);
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 6, 0);

    if (count != 0) {
        buf = _OSAllocFromHeap(0x20, count * 0x10);
        i = 0;
        node = *(u8**)(group + 0xC);
        while (node != NULL) {
            if (i >= count) {
                OSReport(lbl_800E688C);
                break;
            }
            buf[i].node = node;
            PSMTXMultVec(*(Mtx*)(lbl_8017EC00 + 0x13E0), (Vec*)(node + 0x4), &eye);
            buf[i].z = eye.z;
            i++;
            node = *(u8**)node;
        }
        fn_800C07BC(buf, (u8*)buf + count * 8, count, 8, fn_80032038);
        for (i = 0; i < count - 1; i++) {
            *(u8**)buf[i].node = buf[i + 1].node;
        }
        *(u8**)buf[count - 1].node = NULL;
        *(u8**)(group + 0xC) = buf[0].node;
        fn_800ACFB0(buf);
    }

    node = *(u8**)(group + 0xC);
    if (base == NULL) {
        GXSetTevOrder(0, 0, 0, 4);
    } else {
        GXSetTevOrder(0, 0, 1, 4);
        if (node != NULL) {
            tex = base + (*(u16*)(base + node[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
            if (*(void**)(tex + 0x4) != NULL) {
                GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
                GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
                GXLoadTlut(&tlutObj, 0);
            } else {
                GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
            }
            GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
            GXLoadTexObj(&texObj, 1);
        }
    }

    link = (u8**)(group + 0xC);
    node = *link;
    while (node != NULL) {
        if (*(s16*)(node + 0x4A) > 0) {
            alive++;
            PSMTXMultVec(*(Mtx*)(lbl_8017EC00 + 0x1378), (Vec*)(node + 0x4), &eye);
            w = *(f32*)(node + 0x38);
            h = *(f32*)(node + 0x3C);
            corner[0].x = -w;
            corner[0].y = -h;
            corner[0].z = lbl_803CC5F4;
            corner[1].x = w;
            corner[1].y = -h;
            corner[1].z = lbl_803CC5F4;
            corner[2].x = w;
            corner[2].y = h;
            corner[2].z = lbl_803CC5F4;
            corner[3].x = -w;
            corner[3].y = h;
            corner[3].z = lbl_803CC5F4;

            GXBegin(0x80, 0, 4);
            k = 0;
            for (n = 0; n < 2; n++) {
                for (j = 0; j < 2; j++) {
                    Vec* cc = &corner[n * 2 + j];
                    u16* uv = (u16*)(lbl_800F7860 + (node[0x4E] + k) * 4);

                    GXWGFifo.f32 = eye.x + cc->x;
                    GXWGFifo.f32 = eye.y + cc->y;
                    GXWGFifo.f32 = eye.z + cc->z;
                    GXWGFifo.u32 = *(u32*)(node + 0x40);
                    GXWGFifo.f32 = (f32)uv[0];
                    GXWGFifo.f32 = (f32)uv[1];
                    k++;
                }
            }

            if (lbl_80366158[0x28] == 0) {
                *(s16*)(node + 0x4A) -= 1;
            }
            if (*(s16*)(node + 0x4A) == 0) {
                *link = *(u8**)node;
                if (removedTail == NULL) {
                    removedHead = node;
                } else {
                    *(u8**)removedTail = node;
                }
                removedTail = node;
                *(u8**)node = NULL;
                *(u16*)(group + 0x14) -= 1;
                alive--;
            } else {
                link = (u8**)node;
            }
        } else {
            link = (u8**)node;
        }
        node = *link;
    }

    if (removedHead != NULL) {
        prev = removedHead;
        while (*(u8**)prev != NULL) {
            prev = *(u8**)prev;
        }
        *(void**)prev = lbl_803CBC74;
        lbl_803CBC74 = removedHead;
    }
    GXLoadPosMtxImm(lbl_8017FFE0, 0);
    return alive <= 0;
}


void fn_80026998(u8* src) {
    u8* node = (u8*)lbl_803CBC84;
    u8* found = NULL;
    u8* temp = NULL;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* tail;
    u8* initHead = NULL;
    u8* group;
    s32 taken = 0;
    s32 remaining;
    s32 i;
    u8 tempHeader[0x20];

    if (src != NULL) {
        while (node != NULL && (node[0x17] & 0x7F) != 0xF) {
            node = *(u8**)(node + 0x4);
        }
        found = node;
    }

    remaining = *(s32*)(src + 0x8);
    list = (u8*)lbl_803CBC74;
    if (found != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining == 0) {
            temp = tempHeader;
            *(u32*)(temp + 0x10) = *(u32*)src;
            *(u16*)(temp + 0x14) = taken & 0xFFF;
            if (taken != 0) {
                *(void**)(temp + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(temp + 0xC) = NULL;
            }
            initHead = *(u8**)(temp + 0xC);
        }
    } else {
        group = (u8*)lbl_803CBC80;
        i = 0;
        if (group != NULL) {
            while (list != NULL && remaining != 0) {
                lastTaken = list;
                list = *(u8**)list;
                i++;
                remaining--;
            }
            if (remaining == 0) {
                *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (i & 0xFFF);
                if (i != 0) {
                    *(void**)(group + 0xC) = lbl_803CBC74;
                    lbl_803CBC74 = list;
                    if (lastTaken != NULL) {
                        *(void**)lastTaken = NULL;
                    }
                } else {
                    *(void**)(group + 0xC) = NULL;
                }
            } else {
                group = NULL;
            }
        }
        if (group != NULL) {
            lbl_803CBC80 = *(void**)(group + 0x4);
            *(void**)(group + 0x8) = (void*)maybeTexOrSpriteRelated;
            group[0x16] = 0x80;
            group[0x17] = (group[0x17] & ~0x7F) | 0xF;
            group[0x17] |= 0x80;
            group[0x14] &= ~0xF0;
            *(void**)(group + 0x4) = NULL;
            *(void**)(group + 0x0) = NULL;

            prev = (u8*)&lbl_803CBC84;
            while (1) {
                u8* succ = *(u8**)(prev + 0x4);

                if (succ == NULL || succ[0x16] >= group[0x16]) {
                    break;
                }
                prev = succ;
            }
            {
                u8* succ = *(u8**)(prev + 0x4);

                *(void**)(group + 0x4) = succ;
                if (succ != NULL) {
                    *(void**)succ = group;
                }
                *(void**)group = prev;
                *(void**)(prev + 0x4) = group;
            }
            *(u32*)(group + 0x10) = *(u32*)src;
            initHead = *(u8**)(group + 0xC);
        }
    }

    for (node = initHead; node != NULL; node = *(u8**)node) {
        node[0x4D] = src[0x4];
        node[0x40] = src[0x4C];
        node[0x41] = src[0x4D];
        node[0x42] = src[0x4E];
        node[0x43] = (u8)*(u32*)(src + 0x38);
        memcpy(node + 0x4, src + 0x40, 12);
        *(s16*)(node + 0x4A) = (s16)*(u32*)(src + 0xC);
        *(s16*)(node + 0x48) = 0;
        *(f32*)(node + 0x10) = *(f32*)(src + 0x10) * *(f32*)(src + 0x1C);
        *(f32*)(node + 0x14) = *(f32*)(src + 0x14) * *(f32*)(src + 0x1C);
        *(f32*)(node + 0x18) = *(f32*)(src + 0x18) * *(f32*)(src + 0x1C);
        *(f32*)(node + 0x1C) = *(f32*)(src + 0x20) * *(f32*)(src + 0x2C);
        *(f32*)(node + 0x20) = *(f32*)(src + 0x24) * *(f32*)(src + 0x2C);
        *(f32*)(node + 0x24) = *(f32*)(src + 0x28) * *(f32*)(src + 0x2C);
        *(f32*)(node + 0x3C) = *(f32*)(src + 0x30);
        *(f32*)(node + 0x38) = *(f32*)(src + 0x30);
        *(f32*)(node + 0x50) = (*(f32*)(src + 0x34) - *(f32*)(src + 0x30)) / (f32)*(u32*)(src + 0xC);
        *(s32*)(node + 0x54) = (*(s32*)(src + 0x3C) - *(s32*)(src + 0x38)) / *(s32*)(src + 0xC);
    }

    if (found != NULL && temp != NULL) {
        tail = *(u8**)(found + 0xC);
        if (tail == NULL) {
            *(void**)(found + 0xC) = *(void**)(temp + 0xC);
        } else {
            while (*(void**)tail != NULL) {
                tail = *(u8**)tail;
            }
            *(void**)tail = *(void**)(temp + 0xC);
        }
        *(u16*)(found + 0x14) = (*(u16*)(found + 0x14) & 0xF000) |
                                (((*(u16*)(found + 0x14) & 0xFFF) + (*(u16*)(temp + 0x14) & 0xFFF)) & 0xFFF);
    }
}

BOOL fn_80026E58(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    Mtx mtx;
    u8* node;
    u8* base;
    u8* tex;
    Vec* center;
    Vec local;
    Vec delta;
    s32 texIdx;
    s32 drawn = 0;
    s32 k;
    f32 zero = lbl_803CC5F4;
    f32 size;

    memcpy(mtx, lbl_800E685C, sizeof(Mtx));
    center = *(Vec**)(group + 0x18);
    local = *center;

    if (*(f32*)(group + 0x1C) > zero) {
        GXLoadPosMtxImm(mtx, 0);
        GXSetZMode(1, 7, 0);
        GXSetBlendMode(1, 4, 1, 0);
        base = *(u8**)(group + 0x10);
        texIdx = *(s16*)(group + 0x20);
        if (base == NULL) {
            GXSetTevOrder(0, 0, 0, 4);
        } else {
            GXSetTevOrder(0, 0, 1, 4);
            tex = base + (*(u16*)(base + texIdx * 0x20 + 0x20)) * 0x20 + 0x4;
            if (*(void**)(tex + 0x4) != NULL) {
                GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
                GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
                GXLoadTlut(&tlutObj, 0);
            } else {
                GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
            }
            GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
            GXLoadTexObj(&texObj, 1);
        }
    }

    node = *(u8**)(group + 0xC);
    while (node != NULL) {
        if (*(s16*)(node + 0x24) > 0) {
            if (lbl_80366158[0x28] == 0) {
                *(s16*)(node + 0x24) -= 1;
            }
        } else if (*(s16*)(node + 0x20) > 0) {
            if (lbl_80366158[0x28] == 0) {
                *(f32*)(node + 0x10) = *(f32*)(node + 0x10) + *(f32*)(node + 0x14);
                PSVECSubtract((Vec*)(node + 0x4), &local, &delta);
                PSVECScale(&delta, *(f32*)(node + 0x10), &delta);
                PSVECAdd(&local, &delta, &local);
                PSMTXMultVec(lbl_8017FFE0, (Vec*)(node + 0x4), &delta);
            }

            size = (f32)node[0x2A] * (f32)*(s16*)(node + 0x20) / (f32)*(s16*)(node + 0x26);

            GXBegin(0x80, 0, 4);
            GXWGFifo.f32 = local.x - *(f32*)(node + 0x18);
            GXWGFifo.f32 = local.y - *(f32*)(node + 0x18);
            GXWGFifo.f32 = local.z;
            GXWGFifo.u32 = *(u32*)(node + 0x1C);
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = zero;

            GXWGFifo.f32 = local.x + *(f32*)(node + 0x18);
            GXWGFifo.f32 = local.y - *(f32*)(node + 0x18);
            GXWGFifo.f32 = local.z;
            GXWGFifo.u32 = *(u32*)(node + 0x1C);
            GXWGFifo.f32 = lbl_803CC608;
            GXWGFifo.f32 = zero;

            GXWGFifo.f32 = local.x + *(f32*)(node + 0x18);
            GXWGFifo.f32 = local.y + *(f32*)(node + 0x18);
            GXWGFifo.f32 = local.z;
            GXWGFifo.u32 = *(u32*)(node + 0x1C);
            GXWGFifo.f32 = lbl_803CC608;
            GXWGFifo.f32 = lbl_803CC608;

            GXWGFifo.f32 = local.x - *(f32*)(node + 0x18);
            GXWGFifo.f32 = local.y + *(f32*)(node + 0x18);
            GXWGFifo.f32 = local.z;
            GXWGFifo.u32 = *(u32*)(node + 0x1C);
            GXWGFifo.f32 = zero;
            GXWGFifo.f32 = lbl_803CC608;

            node[0x1F] = (u8)size;
            if (lbl_80366158[0x28] == 0) {
                *(s16*)(node + 0x20) -= 1;
            }
            drawn++;
        }
        node = *(u8**)node;
    }

    GXLoadPosMtxImm(lbl_8017FFE0, 0);
    if (drawn == 0 && *(f32*)(group + 0x1C) == zero) {
        return TRUE;
    }
    return FALSE;
}

#pragma dont_inline on
void fn_80027300(u8* group, s32 a0, s32 a1, u8* cfg, f32 scale) {
    Vec* origin = (Vec*)a0;
    u8* node;
    f32 radius = (f32)*(u32*)(cfg + 0x8);
    f32 spread = (f32)*(u32*)(cfg + 0xC);
    s32 randomA;
    s32 randomB;
    s32 randomC;

    *(u32*)(group + 0x10) = *(u32*)cfg;
    *(f32*)(group + 0x1C) = lbl_803CC608;
    *(s16*)(group + 0x20) = (s16)*(u32*)(cfg + 0x4);
    *(s32*)(group + 0x18) = a1;

    node = *(u8**)(group + 0xC);
    while (node != NULL) {
        Vec* vel = (Vec*)(node + 0x4);

        PSVECScale(vel, scale, vel);
        PSVECAdd(origin, vel, vel);
        randomA = rand();
        *(f32*)(node + 0x10) = (f32)(randomA - 0x3FFF) * radius / lbl_803CC614;
        randomB = rand();
        *(f32*)(node + 0x14) = (f32)(randomB - 0x3FFF) * spread / lbl_803CC614;
        *(f32*)(node + 0x18) = lbl_803CC650;
        *(s32*)(node + 0x1C) = *(s32*)(cfg + 0x3C);
        randomC = rand();
        *(s16*)(node + 0x20) = (s16)(*(s32*)(cfg + 0x10) + (randomC % 0x7FFF));
        *(s16*)(node + 0x22) = *(s16*)(node + 0x20);
        node[0x2A] = (u8)*(u32*)(cfg + 0x30);
        *(s16*)(node + 0x26) = (s16)*(u32*)(cfg + 0x34);
        *(s16*)(node + 0x28) = (s16)*(u32*)(cfg + 0x38);
        *(s32*)(node + 0x1C) = *(s32*)(cfg + 0x3C);
        node = *(u8**)node;
    }
}
#pragma dont_inline reset

void fn_80027674(f32 scale, s32 arg0, s32 arg1, u8* arg2, u8 id) {
    u8* node = (u8*)lbl_803CBC84;
    u8* temp = NULL;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* tail;
    s32 taken = 0;
    s32 remaining;
    u8 tempHeader[0x20];

    node = *(u8**)(node + 0x4);
    while (node != NULL && (node[0x17] & 0x7F) != id) {
        node = *(u8**)(node + 0x4);
    }

    remaining = *(s32*)(arg2 + 0x8);
    list = (u8*)lbl_803CBC74;
    if (node != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining == 0) {
            temp = tempHeader;
            *(u16*)(temp + 0x14) = taken & 0xFFF;
            if (taken != 0) {
                *(void**)(temp + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(temp + 0xC) = NULL;
            }
            fn_80027300(temp, arg0, arg1, arg2, scale);
            tail = *(u8**)(node + 0xC);
            while (*(void**)tail != NULL) {
                tail = *(u8**)tail;
            }
            *(void**)tail = *(void**)(temp + 0xC);
            *(u16*)(node + 0x14) = (*(u16*)(node + 0x14) & 0xF000) |
                                   (((*(u16*)(node + 0x14) & 0xFFF) + (*(u16*)(temp + 0x14) & 0xFFF)) & 0xFFF);
        }
    } else {
        u8* group = (u8*)lbl_803CBC80;
        s32 i = 0;

        list = (u8*)lbl_803CBC74;
        lastTaken = NULL;
        remaining = *(s32*)(arg2 + 0x8);
        if (group != NULL) {
            while (list != NULL && remaining != 0) {
                lastTaken = list;
                list = *(u8**)list;
                i++;
                remaining--;
            }
            if (remaining == 0) {
                *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (i & 0xFFF);
                if (i != 0) {
                    *(void**)(group + 0xC) = lbl_803CBC74;
                    lbl_803CBC74 = list;
                    if (lastTaken != NULL) {
                        *(void**)lastTaken = NULL;
                    }
                } else {
                    *(void**)(group + 0xC) = NULL;
                }
            } else {
                group = NULL;
            }
        }
        if (group != NULL) {
            lbl_803CBC80 = *(void**)(group + 0x4);
            *(void**)(group + 0x8) = (void*)fn_80026E58;
            group[0x16] = 0x80;
            group[0x17] = (group[0x17] & ~0x7F) | id;
            group[0x17] |= 0x80;
            group[0x14] = (group[0x14] & ~0xF0) | (1 << 4);
            *(void**)(group + 0x4) = NULL;
            *(void**)(group + 0x0) = NULL;

            prev = (u8*)&lbl_803CBC84;
            while (1) {
                u8* succ = *(u8**)(prev + 0x4);

                if (succ == NULL || succ[0x16] >= group[0x16]) {
                    break;
                }
                prev = succ;
            }
            {
                u8* succ = *(u8**)(prev + 0x4);

                *(void**)(group + 0x4) = succ;
                if (succ != NULL) {
                    *(void**)succ = group;
                }
                *(void**)group = prev;
                *(void**)(prev + 0x4) = group;
            }
            fn_80027300(group, arg0, arg1, arg2, scale);
        }
    }
}

void* fn_80027918(u8 id, f32 value) {
    u8* node = *(u8**)(lbl_803CBC84 + 0x4);

    while (node != NULL) {
        if ((node[0x17] & 0x7F) == id) {
            break;
        }
        node = *(u8**)(node + 0x4);
    }
    if (node != NULL) {
        *(f32*)(node + 0x1C) = value;
    }
    return node;
}

BOOL fn_80027968(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    Mtx identity;
    u8* base = *(u8**)(group + 0x10);
    u8* node = *(u8**)(group + 0xC);
    u8* tex;
    u8* list;
    s32 texIdx;
    s32 k;
    s32 n;
    s32 j;
    s32 frame;
    s32 frames;
    s32 drawn = 0;
    Vec corner[4];
    u16* uv;
    f32 w;
    f32 h;

    if (*(u32*)(group + 0x48) != 0) {
        if (group[0x4D] == 0) {
            group[0x4D] = group[0x4C];
            frames = group[0x4E];
            frame = (group[0x4F] + 1);
            if (frames != 0) {
                frame = frame % frames;
            }
            group[0x4F] = (u8)frame;
        } else {
            group[0x4D] -= 1;
        }

        PSMTXIdentity(identity);
        GXLoadPosMtxImm(identity, 0);
        GXSetCullMode(0);
        GXSetCurrentMtx(0);
        GXSetZMode(1, 3, 0);
        GXSetBlendMode(1, 4, 1, 0);
        GXSetTevOrder(0, 0, 1, 4);

        if (base == NULL) {
            GXSetTevOrder(0, 0, 0, 4);
        } else {
            texIdx = group[0x4D];
            tex = base + (*(u16*)(base + texIdx * 0x20 + 0x20)) * 0x20 + 0x4;
            if (*(void**)(tex + 0x4) != NULL) {
                GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
                GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
                GXLoadTlut(&tlutObj, 0);
            } else {
                GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
            }
            GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
            GXLoadTexObj(&texObj, 1);
        }

        list = node;
        while (list != NULL) {
            w = *(f32*)(list + 0x38);
            h = *(f32*)(list + 0x3C);
            corner[0].x = -w;
            corner[0].y = -h;
            corner[0].z = lbl_803CC5F4;
            corner[1].x = w;
            corner[1].y = -h;
            corner[1].z = lbl_803CC5F4;
            corner[2].x = w;
            corner[2].y = h;
            corner[2].z = lbl_803CC5F4;
            corner[3].x = -w;
            corner[3].y = h;
            corner[3].z = lbl_803CC5F4;

            GXBegin(0x80, 0, 4);
            k = 0;
            for (n = 0; n < 2; n++) {
                for (j = 0; j < 2; j++) {
                    Vec* cc = &corner[n * 2 + j];
                    uv = (u16*)(lbl_800F7860 + (group[0x4F] + k) * 4);
                    GXWGFifo.f32 = *(f32*)(list + 0x4) + cc->x;
                    GXWGFifo.f32 = *(f32*)(list + 0x8) + cc->y;
                    GXWGFifo.f32 = *(f32*)(list + 0xC) + cc->z;
                    GXWGFifo.u32 = *(u32*)(list + 0x40);
                    GXWGFifo.f32 = (f32)uv[0];
                    GXWGFifo.f32 = (f32)uv[1];
                    k++;
                }
            }
            drawn++;
            list = *(u8**)list;
        }
        GXLoadPosMtxImm(lbl_8017FFE0, 0);
    }
    return drawn == 0;
}

void fn_8002852C(void) {
    u8* item = (u8*)currentDrawingItem;
    u8 remaining = item[0x23] - 1;
    u8* out;

    item[0x23] = remaining;
    if (remaining == 0) {
        u8 idx = ((u8*)&g_d_GameSettings)[0x54];

        lbl_803CBC70 = 0;
        characterLightingRelated(&inputParams[idx * 0x2C], lbl_80367318);
        removeCurrentDrawingItem();
    } else {
        item[0x1A] = item[0x1E];
        item[0x1B] = item[0x1F];
        item[0x1C] = item[0x20];
        characterLightingRelated(item + 0x14, lbl_80367318);

        out = lbl_803C5090;
        *(f32*)out = lbl_803CC608;
        *(u16*)(out + 0x14) = 0x1C0;
        out[0x18] = 1;
        out[0x19] = item[0x22];
        out[0x1A] = item[0x1E];
        out[0x1B] = item[0x1F];
        out[0x1C] = item[0x20];
        out[0x1D] = 9;
        out[0x17] = (item[0x21] * item[0x23]) / item[0x24];
    }
}

void fn_80028628(Vec* from, Vec* to, u8* desc, u16* ids, u8* a4, u8* a5, s32 a6) {
    u32* c = (u32*)desc;
    u8* group;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* node;
    s32 taken = 0;
    s32 remaining = (s32)c[0x24 / 4];
    Vec dir;
    Vec side;
    Mtx rot;
    Quaternion quat;
    f32 mag;
    f32 radius;
    f32 spread;
    f32 angle;
    s32 i;

    PSVECSubtract(to, from, &dir);
    PSVECNormalize(&dir, &dir);
    mag = PSVECMag(&dir);
    side.x = 0.0f;
    side.y = 1.0f;
    side.z = 0.0f;
    if (mag != 0.0f) {
        PSVECCrossProduct(&dir, &side, &side);
        angle = (f32)acos((f64)PSVECDotProduct(&dir, &side));
        C_QUATRotAxisRad(&quat, &side, angle);
        PSMTXQuat(rot, &quat);
    } else {
        PSMTXRotRad(rot, 'X', lbl_803CC628);
    }

    group = (u8*)lbl_803CBC80;
    list = (u8*)lbl_803CBC74;
    if (group != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining != 0) {
            group = NULL;
        } else {
            *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (taken & 0xFFF);
            if (taken != 0) {
                *(void**)(group + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(group + 0xC) = NULL;
            }
        }
    }

    if (group != NULL) {
        lbl_803CBC80 = *(void**)(group + 0x4);
        *(void**)(group + 0x8) = (void*)fn_80027968;
        group[0x16] = 0x80;
        group[0x17] = (group[0x17] & ~0x7F) | 0x12;
        group[0x17] |= 0x80;
        group[0x14] &= ~0xF0;
        *(void**)(group + 0x4) = NULL;
        *(void**)(group + 0x0) = NULL;

        prev = (u8*)&lbl_803CBC84;
        while (1) {
            u8* succ = *(u8**)(prev + 0x4);

            if (succ == NULL || succ[0x16] >= group[0x16]) {
                break;
            }
            prev = succ;
        }
        {
            u8* succ = *(u8**)(prev + 0x4);

            *(void**)(group + 0x4) = succ;
            if (succ != NULL) {
                *(void**)succ = group;
            }
            *(void**)group = prev;
            *(void**)(prev + 0x4) = group;
        }

        *(u32*)(group + 0x10) = c[0];
        memcpy(group + 0x18, from, 12);
        node = *(u8**)(group + 0xC);
        i = 0;
        while (node != NULL) {
            radius = (f32)c[0x30 / 4] / lbl_803CC614;
            spread = (f32)rand() / lbl_803CC614;
            angle = spread * radius;
            PSVECScale(&dir, angle, (Vec*)(node + 0x10));
            PSMTXMultVec(rot, (Vec*)(node + 0x10), (Vec*)(node + 0x10));
            *(f32*)(node + 0x4) = from->x;
            *(f32*)(node + 0x8) = from->y;
            *(f32*)(node + 0xC) = from->z;
            node[0x4D] = (u8)c[0x4 / 4];
            *(s16*)(node + 0x4A) = (s16)c[0x18 / 4];
            *(s16*)(node + 0x48) = 0;
            node[0x4C] = 1;
            i++;
            node = *(u8**)node;
        }
    }
    (void)ids;
    (void)a4;
    (void)a5;
    (void)a6;
}

BOOL fn_80028F48(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    Mtx mtx;
    u8* node;
    u8** link;
    u8* removedHead = NULL;
    u8* removedTail = NULL;
    u8* base = *(u8**)(group + 0x10);
    u8* tex;
    Vec pos;
    f32 angle;
    f32 c;
    f32 s;
    s32 alive = 0;
    s32 k;
    s32 n;
    s32 j;
    s32 prevTex = -1;
    s32 prevBlend = -1;
    s32 prevZ = -1;

    memcpy(mtx, lbl_800E67F0, sizeof(Mtx));
    GXLoadPosMtxImm(mtx, 0);
    GXSetZMode(1, 7, 1);

    link = (u8**)(group + 0xC);
    node = *link;
    while (node != NULL) {
        if (*(s16*)(node + 0x38) > 0) {
            if (lbl_80366158[0x28] == 0) {
                *(s16*)(node + 0x38) -= 1;
            }
        } else if (*(s16*)(node + 0x3A) > 0) {
            if (node[0x3C] != prevTex) {
                prevTex = node[0x3C];
                if (base == NULL) {
                    GXSetTevOrder(0, 0, 0, 4);
                } else {
                    GXSetTevOrder(0, 0, 1, 4);
                    tex = base + (*(u16*)(base + prevTex * 0x20 + 0x20)) * 0x20 + 0x4;
                    if (*(void**)(tex + 0x4) != NULL) {
                        GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
                        GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
                        GXLoadTlut(&tlutObj, 0);
                    } else {
                        GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
                    }
                    GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
                    GXLoadTexObj(&texObj, 1);
                }
            }
            if (node[0x41] != prevBlend) {
                prevBlend = node[0x41];
                if (prevBlend != 0) {
                    GXSetBlendMode(1, 4, 1, 0);
                } else {
                    GXSetBlendMode(1, 4, 5, 0);
                }
            }
            if (node[0x42] != prevZ) {
                prevZ = node[0x42];
                if (prevZ != 0) {
                    GXSetZMode(1, 3, 0);
                } else {
                    GXSetZMode(1, 7, 0);
                }
            }

            if (lbl_80366158[0x28] == 0) {
                PSVECAdd((Vec*)(node + 0x10), (Vec*)(node + 0x1C), (Vec*)(node + 0x10));
                PSVECAdd((Vec*)(node + 0x4), (Vec*)(node + 0x10), (Vec*)(node + 0x4));
                if (*(f32*)(node + 0x8) < -*(f32*)(node + 0x30)) {
                    *(f32*)(node + 0x8) = -*(f32*)(node + 0x30);
                    *(f32*)(node + 0x14) = *(f32*)(node + 0x14) * lbl_803CC650;
                }
                *(f32*)(node + 0x28) = *(f32*)(node + 0x28) + *(f32*)(node + 0x2C);
                if (*(f32*)(node + 0x28) > lbl_803CC654) {
                    *(f32*)(node + 0x28) = *(f32*)(node + 0x28) - lbl_803CC654;
                }
                if (*(s16*)(node + 0x3A) < node[0x3F]) {
                    node[0x37] = (u8)(node[0x37] + node[0x3E]);
                } else if (node[0x3D] != 0 && node[0x37] < node[0x40]) {
                    s32 a = node[0x37] + node[0x3D];
                    node[0x37] = (u8)(a > node[0x40] ? node[0x40] : a);
                }
            }

            PSMTXMultVec(lbl_8017FFE0, (Vec*)(node + 0x4), &pos);
            angle = *(f32*)(node + 0x28) * lbl_803CC654;
            s = maybeCosineArray[((s32)angle) & 0x7FF];
            c = maybeCosineArray[((s32)angle + 0x600) & 0x7FF];

            GXBegin(0x80, 0, 4);
            GXWGFifo.f32 = pos.x - c * *(f32*)(node + 0x30);
            GXWGFifo.f32 = pos.y - s * *(f32*)(node + 0x30);
            GXWGFifo.f32 = pos.z;
            GXWGFifo.u32 = *(u32*)(node + 0x34);
            GXWGFifo.f32 = lbl_803CC5F4;
            GXWGFifo.f32 = lbl_803CC5F4;
            GXWGFifo.f32 = pos.x + s * *(f32*)(node + 0x30);
            GXWGFifo.f32 = pos.y - c * *(f32*)(node + 0x30);
            GXWGFifo.f32 = pos.z;
            GXWGFifo.u32 = *(u32*)(node + 0x34);
            GXWGFifo.f32 = lbl_803CC608;
            GXWGFifo.f32 = lbl_803CC5F4;
            GXWGFifo.f32 = pos.x + s * *(f32*)(node + 0x30);
            GXWGFifo.f32 = pos.y + c * *(f32*)(node + 0x30);
            GXWGFifo.f32 = pos.z;
            GXWGFifo.u32 = *(u32*)(node + 0x34);
            GXWGFifo.f32 = lbl_803CC608;
            GXWGFifo.f32 = lbl_803CC608;
            GXWGFifo.f32 = pos.x - c * *(f32*)(node + 0x30);
            GXWGFifo.f32 = pos.y + s * *(f32*)(node + 0x30);
            GXWGFifo.f32 = pos.z;
            GXWGFifo.u32 = *(u32*)(node + 0x34);
            GXWGFifo.f32 = lbl_803CC5F4;
            GXWGFifo.f32 = lbl_803CC608;

            if (lbl_80366158[0x28] == 0) {
                *(s16*)(node + 0x3A) -= 1;
            }
            if (*(s16*)(node + 0x3A) == 0) {
                *link = *(u8**)node;
                if (removedTail == NULL) {
                    removedHead = node;
                } else {
                    *(u8**)removedTail = node;
                }
                removedTail = node;
                *(u8**)node = NULL;
                *(u16*)(group + 0x14) -= 1;
            } else {
                link = (u8**)node;
                alive++;
            }
            node = *link;
            continue;
        }
        link = (u8**)node;
        node = *link;
    }

    if (removedHead != NULL) {
        u8* tail = removedHead;
        while (*(u8**)tail != NULL) {
            tail = *(u8**)tail;
        }
        *(void**)tail = lbl_803CBC74;
        lbl_803CBC74 = removedHead;
    }

    GXLoadPosMtxImm(lbl_8017FFE0, 0);
    return alive == 0;
}

void fn_8002955C(s32 arg0, s32 arg1, u8* arg2) {
    u8* node = (u8*)lbl_803CBC84;
    u8* temp = NULL;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* tail;
    s32 taken = 0;
    s32 remaining;
    u8 tempHeader[0x20];

    node = *(u8**)(node + 0x4);
    while (node != NULL && (node[0x17] & 0x7F) != 0xC) {
        node = *(u8**)(node + 0x4);
    }

    remaining = *(s32*)(arg2 + 0x8);
    list = (u8*)lbl_803CBC74;
    if (node != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining == 0) {
            temp = tempHeader;
            *(u16*)(temp + 0x14) = taken & 0xFFF;
            if (taken != 0) {
                *(void**)(temp + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(temp + 0xC) = NULL;
            }
            fn_800297F0(temp, arg0, arg1);
            tail = *(u8**)(node + 0xC);
            while (*(void**)tail != NULL) {
                tail = *(u8**)tail;
            }
            *(void**)tail = *(void**)(temp + 0xC);
            *(u16*)(node + 0x14) = (*(u16*)(node + 0x14) & 0xF000) |
                                   (((*(u16*)(node + 0x14) & 0xFFF) + (*(u16*)(temp + 0x14) & 0xFFF)) & 0xFFF);
        }
    } else {
        u8* group = (u8*)lbl_803CBC80;
        s32 i = 0;

        list = (u8*)lbl_803CBC74;
        lastTaken = NULL;
        remaining = *(s32*)(arg2 + 0x8);
        if (group != NULL) {
            while (list != NULL && remaining != 0) {
                lastTaken = list;
                list = *(u8**)list;
                i++;
                remaining--;
            }
            if (remaining == 0) {
                *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (i & 0xFFF);
                if (i != 0) {
                    *(void**)(group + 0xC) = lbl_803CBC74;
                    lbl_803CBC74 = list;
                    if (lastTaken != NULL) {
                        *(void**)lastTaken = NULL;
                    }
                } else {
                    *(void**)(group + 0xC) = NULL;
                }
            } else {
                group = NULL;
            }
        }
        if (group != NULL) {
            lbl_803CBC80 = *(void**)(group + 0x4);
            *(void**)(group + 0x8) = (void*)fn_80028F48;
            group[0x16] = 0x80;
            group[0x17] = (group[0x17] & ~0x7F) | 0xC;
            group[0x17] |= 0x80;
            group[0x14] &= ~0xF0;
            *(void**)(group + 0x4) = NULL;
            *(void**)(group + 0x0) = NULL;

            prev = (u8*)&lbl_803CBC84;
            while (1) {
                u8* succ = *(u8**)(prev + 0x4);

                if (succ == NULL || succ[0x16] >= group[0x16]) {
                    break;
                }
                prev = succ;
            }
            {
                u8* succ = *(u8**)(prev + 0x4);

                *(void**)(group + 0x4) = succ;
                if (succ != NULL) {
                    *(void**)succ = group;
                }
                *(void**)group = prev;
                *(void**)(prev + 0x4) = group;
            }
            
            fn_800297F0(group, arg0, arg1);
        }
    }
}

void fn_800297F0(void* group, Vec* origin, Vec* vel, u8* cfg) {
    u8* g = (u8*)group;
    u8* node;
    u32* c = (u32*)cfg;
    f32 invRange = lbl_803CC614;
    f32 lo1 = (f32)c[0x1C / 4] / invRange;
    f32 hi1 = (f32)c[0x20 / 4] / invRange;
    f32 lo2 = (f32)c[0x14 / 4] / invRange;
    f32 hi2 = (f32)c[0x18 / 4] / invRange;
    f32 lo3 = (f32)c[0x24 / 4] / invRange;
    f32 hi3 = (f32)c[0x28 / 4] / invRange;
    f32 spanA = hi1 - lo1;
    f32 spanB = hi2 - lo2;
    f32 spanC = hi3 - lo3;
    f32 spread = lbl_803CC60C;
    s32 countCfg = (s32)c[0x38 / 4];
    s32 idx = 0;
    s32 randRange;
    f32 r;

    *(u32*)(g + 0x10) = c[0];
    node = *(u8**)(g + 0xC);
    randRange = (s32)c[0x10 / 4] - (s32)c[0xC / 4];
    while (node != NULL) {
        node[0x3C] = (u8)c[0x4 / 4];
        *(s16*)(node + 0x38) = 0;
        *(s16*)(node + 0x3A) = (s16)(c[0xC / 4] + (u32)(rand() * randRange / 0x7FFF));
        r = (f32)rand() / lbl_803CC61C;
        *(f32*)(node + 0x30) = lo2 + spanB * r;
        *(f32*)(node + 0x4) = origin->x;
        *(f32*)(node + 0x8) = origin->y - *(f32*)(node + 0x30) * lbl_803CC5F0;
        *(f32*)(node + 0xC) = origin->z;
        r = (f32)rand() / lbl_803CC61C;
        *(f32*)(node + 0x10) = (lo1 + spanA * r) * lbl_803CC60C;
        *(s16*)(node + 0x1C) = 0;
        r = (f32)rand() / lbl_803CC61C;
        *(f32*)(node + 0x14) = lo3 + spanC * r;
        *(s32*)(node + 0x18) = 0;
        *(f32*)(node + 0x2C) = spread;
        *(f32*)(node + 0x28) = spread;
        node[0x40] = (u8)c[0x30 / 4];
        *(s32*)(node + 0x34) = (s32)c[0x30 / 4];
        node[0x41] = (u8)c[0x34 / 4];
        node[0x42] = (u8)c[0x38 / 4];
        node[0x43] = (u8)countCfg;
        idx++;
        node = *(u8**)node;
    }
    (void)vel;
}

BOOL fn_80029CC8(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    Mtx mtx;
    Vec origin;
    Vec vel;
    Vec corner[4];
    u8* node;
    u8* base = *(u8**)(group + 0x10);
    u8* tex;
    s32 remaining = *(u16*)(group + 0x14) & 0xFFF;
    s32 k;
    s32 n;
    s32 j;
    f32 w;
    f32 h;

    memcpy(mtx, lbl_800E67C0, sizeof(Mtx));
    GXLoadPosMtxImm(mtx, 0);
    GXSetZMode(1, 7, 1);
    GXSetBlendMode(1, 4, 1, 0);
    PSMTXMultVec(lbl_8017FFE0, (Vec*)(group + 0x18), &origin);

    node = *(u8**)(group + 0xC);
    if (base == NULL) {
        GXSetTevOrder(0, 0, 0, 4);
    } else {
        GXSetTevOrder(0, 0, 1, 4);
        tex = base + (*(u16*)(base + node[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
        if (*(void**)(tex + 0x4) != NULL) {
            GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
            GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
            GXLoadTlut(&tlutObj, 0);
        } else {
            GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
        }
        GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
        GXLoadTexObj(&texObj, 1);
    }

    while (node != NULL) {
        if (*(s16*)(node + 0x48) > 0) {
            *(s16*)(node + 0x48) -= 1;
        } else if (*(s16*)(node + 0x4A) != 0) {
            PSVECAdd((Vec*)(node + 0x10), (Vec*)(node + 0x1C), (Vec*)(node + 0x10));
            PSVECAdd((Vec*)(node + 0x4), (Vec*)(node + 0x10), (Vec*)(node + 0x4));
            node[0x43] = (u8)((s32)node[0x44] * *(s16*)(node + 0x4A) / *(s16*)(node + 0x46));

            if (*(f32*)(node + 0x30) > lbl_803CC624) {
                PSMTXMultVec(lbl_8017FFE0, (Vec*)(node + 0x4), &vel);
                w = *(f32*)(node + 0x28) * *(f32*)(node + 0x30) / *(f32*)(node + 0x34);
                h = *(f32*)(node + 0x28) * *(f32*)(node + 0x2C) / *(f32*)(node + 0x34);
                corner[0].x = vel.x - w;
                corner[0].y = vel.y - h;
                corner[0].z = lbl_803CC5F4;
                corner[1].x = vel.x + w;
                corner[1].y = vel.y - h;
                corner[1].z = lbl_803CC5F4;
                corner[2].x = vel.x + w;
                corner[2].y = vel.y + h;
                corner[2].z = lbl_803CC5F4;
                corner[3].x = vel.x - w;
                corner[3].y = vel.y + h;
                corner[3].z = lbl_803CC5F4;

                GXBegin(0x80, 0, 4);
                k = 0;
                for (n = 0; n < 2; n++) {
                    for (j = 0; j < 2; j++) {
                        Vec* cc = &corner[n * 2 + j];
                        u16* uv = (u16*)(lbl_800F7860 + (node[0x4E] + k) * 4);

                        GXWGFifo.f32 = cc->x;
                        GXWGFifo.f32 = cc->y;
                        GXWGFifo.f32 = cc->z;
                        GXWGFifo.u32 = *(u32*)(node + 0x40);
                        GXWGFifo.f32 = (f32)uv[0];
                        GXWGFifo.f32 = (f32)uv[1];
                        k++;
                    }
                }
            }
            *(s16*)(node + 0x4A) -= 1;
        }
        remaining--;
        node = *(u8**)node;
    }

    GXLoadPosMtxImm(lbl_8017FFE0, 0);
    return remaining == 0;
}

void fn_8002A1CC(Vec* pos, u8* cfg) {
    u32* c = (u32*)cfg;
    u8* group;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* node;
    s32 taken = 0;
    s32 remaining = (s32)c[0x8 / 4];
    f32 scale = lbl_803CC5F0;
    f32 zero = lbl_803CC5F4;
    f32 rnd;
    f32 radius;
    f32 spread;
    f32 angle;
    f32 cosA;
    f32 sinA;
    f32 half;
    Vec dir;

    group = (u8*)lbl_803CBC80;
    list = (u8*)lbl_803CBC74;
    if (group != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining != 0) {
            group = NULL;
        } else {
            *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (taken & 0xFFF);
            if (taken != 0) {
                *(void**)(group + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(group + 0xC) = NULL;
            }
        }
    }

    if (group != NULL) {
        lbl_803CBC80 = *(void**)(group + 0x4);
        *(void**)(group + 0x8) = (void*)fn_80029CC8;
        group[0x16] = 0x80;
        group[0x17] = (group[0x17] & ~0x7F) | 0xB;
        group[0x17] |= 0x80;
        group[0x14] &= ~0xF0;
        *(void**)(group + 0x4) = NULL;
        *(void**)(group + 0x0) = NULL;

        prev = (u8*)&lbl_803CBC84;
        while (1) {
            u8* succ = *(u8**)(prev + 0x4);

            if (succ == NULL || succ[0x16] >= group[0x16]) {
                break;
            }
            prev = succ;
        }
        {
            u8* succ = *(u8**)(prev + 0x4);

            *(void**)(group + 0x4) = succ;
            if (succ != NULL) {
                *(void**)succ = group;
            }
            *(void**)group = prev;
            *(void**)(prev + 0x4) = group;
        }

        *(u32*)(group + 0x10) = c[0];
        memcpy(group + 0x18, pos, 12);
        *(u16*)(group + 0x48) = (u16)(c[0x8 / 4]);
        *(u16*)(group + 0x4A) = (u16)(c[0x10 / 4]);
        *(u16*)(group + 0x46) = (u16)(c[0x14 / 4]);

        node = *(u8**)(group + 0xC);
        while (node != NULL) {
            rnd = (f32)rand() / lbl_803CC614;
            radius = (f32)c[0x30 / 4] / lbl_803CC614;
            spread = (f32)c[0x34 / 4] / lbl_803CC614;
            angle = rnd * spread;
            cosA = cos(angle);
            sinA = sin(angle);
            half = (f32)c[0x38 / 4] / lbl_803CC614;
            dir.x = cosA * radius * half;
            dir.y = sinA * radius * half;
            dir.z = zero;
            PSVECScale(&dir, scale, &dir);
            *(f32*)(node + 0x10) = dir.x;
            *(f32*)(node + 0x14) = dir.y;
            *(f32*)(node + 0x18) = dir.z;
            *(f32*)(node + 0x4) = pos->x;
            *(f32*)(node + 0x8) = pos->y;
            *(f32*)(node + 0xC) = pos->z;
            *(u32*)(node + 0x40) = c[0x4C / 4];
            node[0x44] = node[0x43];
            node = *(u8**)node;
        }
    }
}

BOOL fn_8002A85C(u8* group, u8* item) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    u8* base = *(u8**)(group + 0x10);
    u8* tex;
    f32 zOff = lbl_803CC5F4;
    f32 scale = lbl_803CC5F0;
    f32 w = *(f32*)(item + 0x38) * scale;
    f32 h = *(f32*)(item + 0x3C) * scale;
    s32 alpha;
    s32 k;
    s32 n;
    s32 j;

    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 6, 0);

    lbl_80180010[0].x = -w;
    lbl_80180010[0].y = -h;
    lbl_80180010[0].z = zOff;
    lbl_80180010[1].x = w;
    lbl_80180010[1].y = -h;
    lbl_80180010[1].z = zOff;
    lbl_80180010[2].x = w;
    lbl_80180010[2].y = h;
    lbl_80180010[2].z = zOff;
    lbl_80180010[3].x = -w;
    lbl_80180010[3].y = h;
    lbl_80180010[3].z = zOff;
    for (k = 0; k < 4; k++) {
        PSMTXMultVec(graphicRelatedStructMaybe.mtx, &lbl_80180010[k], &lbl_80180010[k]);
    }

    if (base == NULL) {
        GXSetTevOrder(0, 0, 0, 4);
    } else {
        GXSetTevOrder(0, 0, 1, 4);
        tex = base + (*(u16*)(base + item[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
        if (*(void**)(tex + 0x4) != NULL) {
            GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
            GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
            GXLoadTlut(&tlutObj, 0);
        } else {
            GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
        }
        GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
        GXLoadTexObj(&texObj, 1);
    }

    GXBegin(0x80, 0, 4);
    k = 0;
    for (n = 0; n < 2; n++) {
        for (j = 0; j < 2; j++) {
            Vec* corner = &lbl_80180010[n * 2 + j];
            u16* uv = (u16*)(lbl_800F7860 + (item[0x4E] + k) * 4);

            GXWGFifo.f32 = *(f32*)(item + 0x4) + corner->x;
            GXWGFifo.f32 = *(f32*)(item + 0x8) + corner->y;
            GXWGFifo.f32 = *(f32*)(item + 0xC) + corner->z;
            GXWGFifo.u32 = *(u32*)(item + 0x40);
            GXWGFifo.f32 = (f32)uv[0];
            GXWGFifo.f32 = (f32)uv[1];
            k++;
        }
    }

    alpha = item[0x43];
    if (*(s16*)(item + 0x26) - *(s16*)(item + 0x4A) < *(s16*)(item + 0x24)) {
        *(f32*)(item + 0x38) = *(f32*)(item + 0x38) + *(f32*)(item + 0x18);
        *(f32*)(item + 0x3C) = *(f32*)(item + 0x3C) + *(f32*)(item + 0x10);
        *(f32*)(item + 0x8) = *(f32*)(item + 0x8) - *(f32*)(item + 0x10) * scale;
        alpha += *(s16*)(item + 0x20);
    } else {
        *(f32*)(item + 0x38) = *(f32*)(item + 0x38) + *(f32*)(item + 0x1C);
        *(f32*)(item + 0x3C) = *(f32*)(item + 0x3C) + *(f32*)(item + 0x14);
        *(f32*)(item + 0x8) = *(f32*)(item + 0x8) - *(f32*)(item + 0x14) * scale;
        alpha += *(s16*)(item + 0x22);
    }
    if (alpha < 0) {
        alpha = 0;
    }
    if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    item[0x43] = (u8)alpha;
    *(s16*)(item + 0x4A) -= 1;
    return *(s16*)(item + 0x4A) == 0;
}

BOOL fn_8002AC68(u8* group, u8* item) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    Vec corners[4];
    u8* base = *(u8**)(group + 0x10);
    u8* tex;
    f32 yOff = lbl_803CC5F4;
    f32 scale = lbl_803CC5F0;
    f32 hw = *(f32*)(item + 0x38) * scale;
    f32 hz = *(f32*)(item + 0x3C) * scale;
    s32 alpha;
    s32 k;
    s32 n;
    s32 j;

    corners[0].x = -hw;
    corners[0].y = yOff;
    corners[0].z = hz;
    corners[1].x = hw;
    corners[1].y = yOff;
    corners[1].z = hz;
    corners[2].x = hw;
    corners[2].y = yOff;
    corners[2].z = -hz;
    corners[3].x = -hw;
    corners[3].y = yOff;
    corners[3].z = -hz;

    if (base == NULL) {
        GXSetTevOrder(0, 0, 0, 4);
    } else {
        GXSetTevOrder(0, 0, 1, 4);
        tex = base + (*(u16*)(base + item[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
        if (*(void**)(tex + 0x4) != NULL) {
            GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
            GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
            GXLoadTlut(&tlutObj, 0);
        } else {
            GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
        }
        GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
        GXLoadTexObj(&texObj, 1);
    }

    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 6, 0);
    GXBegin(0x80, 0, 4);
    k = 0;
    for (n = 0; n < 2; n++) {
        for (j = 0; j < 2; j++) {
            Vec* corner = &corners[n * 2 + j];
            u16* uv = (u16*)(lbl_800F7860 + (item[0x4E] + k) * 4);

            GXWGFifo.f32 = *(f32*)(item + 0x4) + corner->x;
            GXWGFifo.f32 = *(f32*)(item + 0x8) + corner->y;
            GXWGFifo.f32 = *(f32*)(item + 0xC) + corner->z;
            GXWGFifo.u32 = *(u32*)(item + 0x40);
            GXWGFifo.f32 = (f32)uv[0];
            GXWGFifo.f32 = (f32)uv[1];
            k++;
        }
    }

    alpha = item[0x43];
    if (*(s16*)(item + 0x1E) - *(s16*)(item + 0x4A) < *(s16*)(item + 0x1C)) {
        *(f32*)(item + 0x38) = *(f32*)(item + 0x38) + *(f32*)(item + 0x10);
        *(f32*)(item + 0x3C) = *(f32*)(item + 0x38);
        alpha += *(s16*)(item + 0x18);
    } else {
        *(f32*)(item + 0x38) = *(f32*)(item + 0x38) + *(f32*)(item + 0x14);
        *(f32*)(item + 0x3C) = *(f32*)(item + 0x38);
        alpha += *(s16*)(item + 0x1A);
    }
    if (alpha < 0) {
        alpha = 0;
    }
    if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    item[0x43] = (u8)alpha;
    *(s16*)(item + 0x4A) -= 1;
    return *(s16*)(item + 0x4A) == 0;
}

s32 fn_8002B014(u8* group) {
    ParticleSortEntry* buf;
    u8* node;
    u8** link;
    u8* removedHead;
    u8* removedTail;
    Vec tmp;
    s32 alive = 0;
    s32 count;
    s32 i;

    count = *(u16*)(group + 0x14) & 0xFFF;
    if (count != 0) {
        buf = _OSAllocFromHeap(0x20, count * 0x10);
        i = 0;
        node = *(u8**)(group + 0xC);
        while (node != NULL) {
            if (i >= count) {
                OSReport(lbl_800E688C);
                break;
            }
            buf[i].node = node;
            PSMTXMultVec(lbl_8017FFE0, (Vec*)(node + 0x4), &tmp);
            buf[i].z = tmp.z;
            i++;
            node = *(u8**)node;
        }
        fn_800C07BC(buf, (u8*)buf + count * 8, count, 8, fn_80032038);
        for (i = 0; i < count - 1; i++) {
            *(u8**)buf[i].node = buf[i + 1].node;
        }
        *(u8**)buf[count - 1].node = NULL;
        *(u8**)(group + 0xC) = buf[0].node;
        fn_800ACFB0(buf);

        removedHead = NULL;
        removedTail = NULL;
        link = (u8**)(group + 0xC);
        node = *link;
        while (node != NULL) {
            if (*(s16*)(node + 0x4A) == 0) {
                link = (u8**)node;
            } else if (*(s16*)(node + 0x48) > 0) {
                *(s16*)(node + 0x48) -= 1;
                link = (u8**)node;
                alive++;
            } else if (!fn_8002AC68(group, node)) {
                link = (u8**)node;
                alive++;
            } else {
                *link = *(u8**)node;
                if (removedTail != NULL) {
                    *(u8**)removedTail = node;
                } else {
                    removedHead = node;
                }
                removedTail = node;
                *(u8**)node = NULL;
                *(u16*)(group + 0x14) -= 1;
            }
            node = *link;
        }

        if (removedHead != NULL) {
            for (node = removedHead; node != NULL; node = *(u8**)node) {
                node[0x4C] = 0;
                *(s16*)(node + 0x48) = 0;
            }
            removedTail = removedHead;
            while (*(u8**)removedTail != NULL) {
                removedTail = *(u8**)removedTail;
            }
            *(void**)removedTail = lbl_803CBC74;
            lbl_803CBC74 = removedHead;
        }
    }

    count = *(u16*)(group + 0x1C);
    if (count != 0) {
        buf = _OSAllocFromHeap(0x20, count * 0x10);
        i = 0;
        node = *(u8**)(group + 0x18);
        while (node != NULL) {
            if (i >= count) {
                OSReport(lbl_800E688C);
                break;
            }
            buf[i].node = node;
            PSMTXMultVec(lbl_8017FFE0, (Vec*)(node + 0x4), &tmp);
            buf[i].z = tmp.z;
            i++;
            node = *(u8**)node;
        }
        fn_800C07BC(buf, (u8*)buf + count * 8, count, 8, fn_80032038);
        for (i = 0; i < count - 1; i++) {
            *(u8**)buf[i].node = buf[i + 1].node;
        }
        *(u8**)buf[count - 1].node = NULL;
        *(u8**)(group + 0x18) = buf[0].node;
        fn_800ACFB0(buf);

        removedHead = NULL;
        removedTail = NULL;
        link = (u8**)(group + 0x18);
        node = *link;
        while (node != NULL) {
            if (*(s16*)(node + 0x4A) == 0) {
                link = (u8**)node;
            } else if (*(s16*)(node + 0x48) > 0) {
                *(s16*)(node + 0x48) -= 1;
                link = (u8**)node;
                alive++;
            } else if (!fn_8002A85C(group, node)) {
                link = (u8**)node;
                alive++;
            } else {
                *link = *(u8**)node;
                if (removedTail != NULL) {
                    *(u8**)removedTail = node;
                } else {
                    removedHead = node;
                }
                removedTail = node;
                *(u8**)node = NULL;
                *(u16*)(group + 0x1C) -= 1;
            }
            node = *link;
        }

        if (removedHead != NULL) {
            for (node = removedHead; node != NULL; node = *(u8**)node) {
                node[0x4C] = 0;
                *(s16*)(node + 0x48) = 0;
            }
            removedTail = removedHead;
            while (*(u8**)removedTail != NULL) {
                removedTail = *(u8**)removedTail;
            }
            *(void**)removedTail = lbl_803CBC74;
            lbl_803CBC74 = removedHead;
        }
    }

    return alive == 0;
}

void fn_8002B400(u8* group, u8* desc, Vec* src) {
    u8* node;
    s32 i;
    f32 angle;
    f32 t;

    node = *(u8**)(group + 0xC);
    while (node != NULL) {
        node[0x4E] = 0;
        node[0x42] = 0xFF;
        node[0x41] = 0xFF;
        node[0x40] = 0xFF;
        node[0x43] = (u8)*(u32*)(desc + 0x60);
        node[0x4C] = 2;
        node[0x4D] = (u8)*(u32*)(desc + 0x44);
        *(s16*)(node + 0x4A) = (s16)*(u32*)(desc + 0x4C);
        *(f32*)(node + 0x38) = *(f32*)(desc + 0x54);
        *(f32*)(node + 0x3C) = *(f32*)(desc + 0x54);
        *(f32*)(node + 0x4) = src->x;
        *(f32*)(node + 0x8) = (f32)(lbl_803CC660 - src->y);
        *(f32*)(node + 0xC) = src->z;
        *(s16*)(node + 0x1C) = (s16)*(u32*)(desc + 0x50);
        *(s16*)(node + 0x1E) = (s16)*(u32*)(desc + 0x4C);
        *(f32*)(node + 0x10) = (*(f32*)(desc + 0x58) - *(f32*)(desc + 0x54)) / (f32)*(s16*)(node + 0x1C);
        *(s16*)(node + 0x18) = (s16)((*(u32*)(desc + 0x64) - *(u32*)(desc + 0x60)) / *(s16*)(node + 0x1C));
        *(f32*)(node + 0x14) = (*(f32*)(desc + 0x5C) - *(f32*)(desc + 0x58)) / (f32)(*(s16*)(node + 0x1E) - *(s16*)(node + 0x1C));
        *(s16*)(node + 0x1A) = (s16)((*(u32*)(desc + 0x68) - *(u32*)(desc + 0x64)) / (*(s16*)(node + 0x1E) - *(s16*)(node + 0x1C)));
        *(s16*)(node + 0x48) = 0;
        node = *(u8**)node;
    }

    i = 0;
    node = *(u8**)(group + 0x18);
    while (node != NULL) {
        t = *(f32*)(desc + 0x40) / (f32)*(u32*)(desc + 0x8);
        t = lbl_803CC658 * t;
        t = (f32)i * t;
        angle = lbl_803CC658 * *(f32*)(desc + 0x3C) + t;

        node[0x4E] = 0;
        node[0x42] = 0xFF;
        node[0x41] = 0xFF;
        node[0x40] = 0xFF;
        node[0x43] = (u8)*(u32*)(desc + 0x2C);
        node[0x4C] = 1;
        node[0x4D] = (u8)*(u32*)(desc + 0x4);
        *(s16*)(node + 0x4A) = (s16)*(u32*)(desc + 0xC);
        *(f32*)(node + 0x38) = *(f32*)(desc + 0x20);
        *(f32*)(node + 0x3C) = *(f32*)(desc + 0x14);
        *(f32*)(node + 0x4) = *(f32*)(desc + 0x38) * (f32)cos(angle) + src->x;
        *(f32*)(node + 0x8) = (f32)(lbl_803CC660 - src->y - *(f32*)(node + 0x3C) * lbl_803CC5F0);
        *(f32*)(node + 0xC) = *(f32*)(desc + 0x38) * (f32)sin(angle) + src->z;
        *(s16*)(node + 0x24) = (s16)*(u32*)(desc + 0x10);
        *(s16*)(node + 0x26) = (s16)*(u32*)(desc + 0xC);
        *(f32*)(node + 0x10) = (*(f32*)(desc + 0x18) - *(f32*)(desc + 0x14)) / (f32)*(s16*)(node + 0x24);
        *(f32*)(node + 0x18) = (*(f32*)(desc + 0x24) - *(f32*)(desc + 0x20)) / (f32)*(s16*)(node + 0x24);
        *(s16*)(node + 0x20) = (s16)((*(u32*)(desc + 0x30) - *(u32*)(desc + 0x2C)) / *(s16*)(node + 0x24));
        *(f32*)(node + 0x14) = (*(f32*)(desc + 0x1C) - *(f32*)(desc + 0x18)) / (f32)(*(s16*)(node + 0x26) - *(s16*)(node + 0x24));
        *(f32*)(node + 0x1C) = (*(f32*)(desc + 0x28) - *(f32*)(desc + 0x24)) / (f32)(*(s16*)(node + 0x26) - *(s16*)(node + 0x24));
        *(s16*)(node + 0x22) = (s16)((*(u32*)(desc + 0x34) - *(u32*)(desc + 0x30)) / (*(s16*)(node + 0x26) - *(s16*)(node + 0x24)));
        *(s16*)(node + 0x48) = 0;
        i += 2;
        node = *(u8**)node;
    }
}

void fn_8002B7F8(Vec* src, u8* desc, u8 flag) {
    u8* node;
    u8* temp = NULL;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* tail;
    s32 taken = 0;
    s32 remaining;
    u8 tempHeader[0x20];
    u8 tempHeader2[0x20];

    if (g_d_GameSettings[0x55] != 0) {
        return;
    }

    node = (u8*)lbl_803CBC84;
    while (node != NULL && (node[0x17] & 0x7F) != 0xE) {
        node = *(u8**)(node + 0x4);
    }

    remaining = *(s32*)(desc + 0x48);
    list = (u8*)lbl_803CBC74;
    if (node != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining == 0) {
            temp = tempHeader;
            *(u16*)(temp + 0x14) = taken & 0xFFF;
            if (taken != 0) {
                *(void**)(temp + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(temp + 0xC) = NULL;
            }
            *(void**)(temp + 0x18) = NULL;
            *(u16*)(temp + 0x1C) = 0;
            if (flag != 0 && *(s32*)(desc + 0x8) != 0) {
                u8* list2 = (u8*)lbl_803CBC74;
                u8* lastTaken2 = NULL;
                s32 taken2 = 0;
                remaining = *(s32*)(desc + 0x8);
                while (list2 != NULL && remaining != 0) {
                    lastTaken2 = list2;
                    list2 = *(u8**)list2;
                    taken2++;
                    remaining--;
                }
                if (remaining == 0) {
                    *(u16*)(temp + 0x1C) = taken2 & 0xFFF;
                    if (taken2 != 0) {
                        *(void**)(temp + 0x18) = lbl_803CBC74;
                        lbl_803CBC74 = list2;
                        if (lastTaken2 != NULL) {
                            *(void**)lastTaken2 = NULL;
                        }
                    }
                }
            }
            fn_8002B400((u8*)temp, desc, src);
            tail = *(u8**)(node + 0xC);
            while (*(void**)tail != NULL) {
                tail = *(u8**)tail;
            }
            *(void**)tail = *(void**)(temp + 0xC);
            *(u16*)(node + 0x14) = (*(u16*)(node + 0x14) & 0xF000) |
                                   (((*(u16*)(node + 0x14) & 0xFFF) + (*(u16*)(temp + 0x14) & 0xFFF)) & 0xFFF);
        }
    } else {
        u8* group = (u8*)lbl_803CBC80;
        s32 i = 0;

        list = (u8*)lbl_803CBC74;
        lastTaken = NULL;
        remaining = *(s32*)(desc + 0x48);
        if (group != NULL) {
            while (list != NULL && remaining != 0) {
                lastTaken = list;
                list = *(u8**)list;
                i++;
                remaining--;
            }
            if (remaining == 0) {
                *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (i & 0xFFF);
                if (i != 0) {
                    *(void**)(group + 0xC) = lbl_803CBC74;
                    lbl_803CBC74 = list;
                    if (lastTaken != NULL) {
                        *(void**)lastTaken = NULL;
                    }
                } else {
                    *(void**)(group + 0xC) = NULL;
                }
            } else {
                group = NULL;
            }
        }
        if (group != NULL) {
            lbl_803CBC80 = *(void**)(group + 0x4);
            *(void**)(group + 0x8) = (void*)fn_8002B014;
            group[0x16] = 0x80;
            group[0x17] = (group[0x17] & ~0x7F) | 0xE;
            group[0x17] |= 0x80;
            group[0x14] &= ~0xF0;
            *(void**)(group + 0x4) = NULL;
            *(void**)(group + 0x0) = NULL;

            prev = (u8*)&lbl_803CBC84;
            while (1) {
                u8* succ = *(u8**)(prev + 0x4);

                if (succ == NULL || succ[0x16] >= group[0x16]) {
                    break;
                }
                prev = succ;
            }
            {
                u8* succ = *(u8**)(prev + 0x4);

                *(void**)(group + 0x4) = succ;
                if (succ != NULL) {
                    *(void**)succ = group;
                }
                *(void**)group = prev;
                *(void**)(prev + 0x4) = group;
            }

            *(void**)(group + 0x10) = *(void**)desc;
            if (flag != 0 && *(s32*)(desc + 0x8) != 0) {
                u8* list2 = (u8*)lbl_803CBC74;
                u8* lastTaken2 = NULL;
                s32 taken2 = 0;
                remaining = *(s32*)(desc + 0x8);
                while (list2 != NULL && remaining != 0) {
                    lastTaken2 = list2;
                    list2 = *(u8**)list2;
                    taken2++;
                    remaining--;
                }
                if (remaining == 0) {
                    *(void**)(group + 0x18) = lbl_803CBC74;
                    *(u16*)(group + 0x1C) = taken2 & 0xFFF;
                    lbl_803CBC74 = list2;
                    if (lastTaken2 != NULL) {
                        *(void**)lastTaken2 = NULL;
                    }
                }
            } else {
                *(void**)(group + 0x18) = NULL;
                *(u16*)(group + 0x1C) = 0;
            }
            fn_8002B400(group, desc, src);
        }
    }
}

void fn_8002C2D0(s32 arg0, s32 arg1, u8* arg2) {
    u8* node = (u8*)lbl_803CBC84;
    u8* temp = NULL;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* tail;
    s32 taken = 0;
    s32 remaining;
    u8 tempHeader[0x20];

    node = *(u8**)(node + 0x4);
    while (node != NULL && (node[0x17] & 0x7F) != 5) {
        node = *(u8**)(node + 0x4);
    }

    remaining = *(s32*)(arg2 + 0x8);
    list = (u8*)lbl_803CBC74;
    if (node != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining == 0) {
            temp = tempHeader;
            *(u16*)(temp + 0x14) = taken & 0xFFF;
            if (taken != 0) {
                *(void**)(temp + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(temp + 0xC) = NULL;
            }
            fn_8002BC84(temp, arg0, arg1);
            tail = *(u8**)(node + 0xC);
            while (*(void**)tail != NULL) {
                tail = *(u8**)tail;
            }
            *(void**)tail = *(void**)(temp + 0xC);
            *(u16*)(node + 0x14) = (*(u16*)(node + 0x14) & 0xF000) |
                                   (((*(u16*)(node + 0x14) & 0xFFF) + (*(u16*)(temp + 0x14) & 0xFFF)) & 0xFFF);
        }
    } else {
        u8* group = (u8*)lbl_803CBC80;
        s32 i = 0;

        list = (u8*)lbl_803CBC74;
        lastTaken = NULL;
        remaining = *(s32*)(arg2 + 0x8);
        if (group != NULL) {
            while (list != NULL && remaining != 0) {
                lastTaken = list;
                list = *(u8**)list;
                i++;
                remaining--;
            }
            if (remaining == 0) {
                *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (i & 0xFFF);
                if (i != 0) {
                    *(void**)(group + 0xC) = lbl_803CBC74;
                    lbl_803CBC74 = list;
                    if (lastTaken != NULL) {
                        *(void**)lastTaken = NULL;
                    }
                } else {
                    *(void**)(group + 0xC) = NULL;
                }
            } else {
                group = NULL;
            }
        }
        if (group != NULL) {
            lbl_803CBC80 = *(void**)(group + 0x4);
            *(void**)(group + 0x8) = (void*)fn_80031034;
            group[0x16] = 0x11;
            group[0x17] = (group[0x17] & ~0x7F) | 5;
            group[0x17] |= 0x80;
            group[0x14] &= ~0xF0;
            *(void**)(group + 0x4) = NULL;
            *(void**)(group + 0x0) = NULL;

            prev = (u8*)&lbl_803CBC84;
            while (1) {
                u8* succ = *(u8**)(prev + 0x4);

                if (succ == NULL || succ[0x16] >= group[0x16]) {
                    break;
                }
                prev = succ;
            }
            {
                u8* succ = *(u8**)(prev + 0x4);

                *(void**)(group + 0x4) = succ;
                if (succ != NULL) {
                    *(void**)succ = group;
                }
                *(void**)group = prev;
                *(void**)(prev + 0x4) = group;
            }
            group[0x18] = 0;
            fn_8002BC84(group, arg0, arg1);
        }
    }
}

void fn_8002BC84(void* group, s32 a0, s32 a1, u8* desc) {
    Vec* from = (Vec*)a0;
    Vec* to = (Vec*)a1;
    u8* g = (u8*)group;
    u8* node;
    Mtx rot;
    Vec axis;
    Vec dir;
    f32 angle;
    f32 radius;
    f32 spread;
    f32 cosA;
    f32 sinA;
    s32 randA;

    *(u32*)(g + 0x10) = *(u32*)desc;
    PSVECSubtract(to, from, &axis);
    PSVECNormalize(&axis, &axis);
    angle = (f32)acos((f64)axis.y);
    PSMTXRotAxisRad(rot, &axis, angle);

    node = *(u8**)(g + 0xC);
    while (node != NULL) {
        randA = rand();
        radius = (f32)*(u32*)(desc + 0x8) / lbl_803CC614;
        spread = (f32)*(u32*)(desc + 0xC) / lbl_803CC614;
        angle = (f32)randA / lbl_803CC614;
        cosA = cos(angle);
        sinA = sin(angle);
        dir.x = cosA * radius;
        dir.y = sinA * radius;
        dir.z = 0.0f;
        PSMTXMultVec(rot, &dir, &dir);
        PSVECScale(&dir, *(f32*)(desc + 0x38), &dir);
        PSVECAdd(from, &dir, (Vec*)(node + 0x4));
        *(f32*)(node + 0x10) = dir.x;
        *(f32*)(node + 0x14) = dir.y;
        *(f32*)(node + 0x18) = dir.z;
        randA = rand();
        *(f32*)(node + 0x1C) = (f32)randA / lbl_803CC614 * spread;
        node[0x3C] = 0;
        node = *(u8**)node;
    }
}

BOOL fn_8002C56C(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    Mtx identity;
    u8* node = *(u8**)(group + 0xC);
    u8* base = *(u8**)(group + 0x10);
    u8* tex;
    u8* sub;
    u8** link;
    u8* removedHead = NULL;
    u8* removedTail = NULL;
    s32 alive = 0;
    s32 k;
    s32 n;
    s32 j;
    f32 t;
    f32 eased;

    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, 0);
    GXSetCullMode(0);
    GXSetZMode(1, 7, 0);
    GXSetBlendMode(1, 4, 1, 0);

    if (base == NULL) {
        GXSetTevOrder(0, 0, 0, 4);
    } else {
        GXSetTevOrder(0, 0, 1, 4);
        if (node != NULL) {
            tex = base + (*(u16*)(base + node[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
            if (*(void**)(tex + 0x4) != NULL) {
                GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
                GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
                GXLoadTlut(&tlutObj, 0);
            } else {
                GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
            }
            GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
            GXLoadTexObj(&texObj, 1);
        }
    }

    link = (u8**)(group + 0xC);
    node = *link;
    while (node != NULL) {
        sub = *(u8**)(group + 0x3C);
        if (*(s16*)(node + 0x40) > 0 && lbl_80366158[0x28] == 0) {
            *(s16*)(node + 0x40) -= 1;
        }
        t = (f32)(*(s16*)(node + 0x40)) / (f32)(*(s16*)(node + 0x44) + 1);
        eased = t * t * (3.0f - 2.0f * t);
        *(f32*)(node + 0x4) = *(f32*)(node + 0x4) + *(f32*)(node + 0x10) * eased;
        *(f32*)(node + 0x8) = *(f32*)(node + 0x8) + *(f32*)(node + 0x14) * eased;
        *(f32*)(node + 0xC) = *(f32*)(node + 0x0C) + *(f32*)(node + 0x18) * eased;

        GXBegin(0x80, 0, 4);
        k = 0;
        for (n = 0; n < 2; n++) {
            for (j = 0; j < 2; j++) {
                u16* uv = (u16*)(lbl_800F78C0 + (node[0x4E] + k) * 4);

                GXWGFifo.f32 = *(f32*)(node + 0x4) + (j ? 1.0f : -1.0f) * *(f32*)(node + 0x38);
                GXWGFifo.f32 = *(f32*)(node + 0x8) + (n ? 1.0f : -1.0f) * *(f32*)(node + 0x3C);
                GXWGFifo.f32 = *(f32*)(node + 0xC);
                GXWGFifo.u32 = *(u32*)(node + 0x40);
                GXWGFifo.f32 = (f32)uv[0];
                GXWGFifo.f32 = (f32)uv[1];
                k++;
            }
        }
        if (sub != NULL) {
            node[0x43] = (u8)(node[0x43] + (u8)sub[0]);
        }

        if (*(s16*)(node + 0x40) == 0) {
            *link = *(u8**)node;
            if (removedTail == NULL) {
                removedHead = node;
            } else {
                *(u8**)removedTail = node;
            }
            removedTail = node;
            *(u8**)node = NULL;
            *(u16*)(group + 0x14) -= 1;
        } else {
            link = (u8**)node;
            alive++;
        }
        node = *link;
    }

    if (removedHead != NULL) {
        u8* tail = removedHead;
        while (*(u8**)tail != NULL) {
            tail = *(u8**)tail;
        }
        *(void**)tail = lbl_803CBC74;
        lbl_803CBC74 = removedHead;
    }
    GXLoadPosMtxImm(lbl_8017FFE0, 0);
    return alive == 0;
}

void setDaisyStarEffectTarget(Vec* target) {
    u8* effect = *(u8**)(lbl_803CBC84 + 0x4);

    while (effect != NULL) {
        if ((effect[0x17] & 0x7F) == 0xA) {
            break;
        }
        effect = *(u8**)(effect + 0x4);
    }
    if (effect != NULL && *(u16*)(effect + 0x40) != 0) {
        *(Vec*)(effect + 0x24) = *target;
        PSVECSubtract((Vec*)(effect + 0x24), (Vec*)(effect + 0x18), (Vec*)(effect + 0x30));
    }
}

void spawnDaisyStarEffect(Vec* from, Vec* to, u8* desc) {
    u32* c = (u32*)desc;
    u8* group;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* node;
    s32 taken = 0;
    s32 remaining = (s32)c[0x8 / 4];
    Vec dir;
    f32 radius;
    f32 spread;
    f32 angle;
    f32 len;

    PSVECSubtract(to, from, &dir);
    len = PSVECMag(&dir);

    group = (u8*)lbl_803CBC80;
    list = (u8*)lbl_803CBC74;
    if (group != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining != 0) {
            group = NULL;
        } else {
            *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (taken & 0xFFF);
            if (taken != 0) {
                *(void**)(group + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(group + 0xC) = NULL;
            }
        }
    }

    if (group != NULL) {
        lbl_803CBC80 = *(void**)(group + 0x4);
        *(void**)(group + 0x8) = (void*)fn_8002C56C;
        group[0x16] = 0x80;
        group[0x17] = (group[0x17] & ~0x7F) | 10;
        group[0x17] |= 0x80;
        group[0x14] &= ~0xF0;
        *(void**)(group + 0x4) = NULL;
        *(void**)(group + 0x0) = NULL;

        prev = (u8*)&lbl_803CBC84;
        while (1) {
            u8* succ = *(u8**)(prev + 0x4);

            if (succ == NULL || succ[0x16] >= group[0x16]) {
                break;
            }
            prev = succ;
        }
        {
            u8* succ = *(u8**)(prev + 0x4);

            *(void**)(group + 0x4) = succ;
            if (succ != NULL) {
                *(void**)succ = group;
            }
            *(void**)group = prev;
            *(void**)(prev + 0x4) = group;
        }

        *(u32*)(group + 0x10) = c[0];
        memcpy(group + 0x18, from, 12);
        memcpy(group + 0x24, &dir, 12);
        *(u16*)(group + 0x48) = (u16)(rand() % (s32)(c[0x1C / 4] ? c[0x1C / 4] : 1));
        *(u16*)(group + 0x4A) = (u16)(c[0x14 / 4] + rand() % (s32)(c[0x20 / 4] ? c[0x20 / 4] : 1));
        *(f32*)(group + 0x34) = len;

        node = *(u8**)(group + 0xC);
        while (node != NULL) {
            radius = (f32)c[0x30 / 4] / lbl_803CC614;
            spread = (f32)rand() / lbl_803CC614;
            angle = spread * (f32)c[0x34 / 4] / lbl_803CC614;
            PSVECScale(&dir, radius * angle, (Vec*)(node + 0x28));
            *(f32*)(node + 0x28) = *(f32*)(node + 0x28) * lbl_803CC5F0;
            PSVECAdd((Vec*)(node + 0x10), (Vec*)(node + 0x1C), (Vec*)(node + 0x10));
            *(f32*)(node + 0x34) = lbl_803CC608;
            node = *(u8**)node;
        }
    }
}

BOOL fn_8002D82C(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    Mtx identity;
    u8* base = *(u8**)(group + 0x10);
    u8* node = *(u8**)(group + 0xC);
    u8* tex;
    s32 count = 0;
    s32 c;
    s32 n;
    s32 j;
    s32 idx;
    f32 w;
    f32 h;
    f32 tx;
    f32 ty;
    f32 tz;
    Vec view;

    if (base == NULL) {
        GXSetTevOrder(0, 0, 0, 4);
    } else {
        GXSetTevOrder(0, 0, 1, 4);
        tex = base + (*(u16*)(base + node[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
        if (*(void**)(tex + 0x4) != NULL) {
            GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
            GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
            GXLoadTlut(&tlutObj, 0);
        } else {
            GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
        }
        GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
        GXLoadTexObj(&texObj, 1);
    }

    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, 0);
    GXSetCullMode(0);
    GXSetZMode(1, 7, 0);
    GXSetBlendMode(1, 4, 1, 0);

    node = *(u8**)(group + 0xC);
    while (node != NULL) {
        if (*(s16*)(node + 0x4A) != 0) {
            count++;
            if (*(s16*)(node + 0x48) != 0) {
                *(s16*)(node + 0x48) -= (lbl_80366158[0x28] == 0) ? 1 : 0;
            } else {
                PSMTXMultVec(lbl_8017FFE0, (Vec*)(node + 0x4), &view);
                tx = view.x;
                ty = view.y;
                tz = view.z;
                w = *(f32*)(node + 0x38);
                h = *(f32*)(node + 0x3C);
                idx = node[0x4F];

                GXBegin(0x80, 0, 4);
                GXWGFifo.f32 = tx - w;
                GXWGFifo.f32 = ty - h;
                GXWGFifo.f32 = tz;
                GXWGFifo.u32 = *(u32*)(node + 0x40);
                GXWGFifo.f32 = lbl_800F78C0[(idx & 3) * 2];
                GXWGFifo.f32 = lbl_800F78C0[(idx & 3) * 2 + 1];

                GXWGFifo.f32 = tx + h;
                GXWGFifo.f32 = ty - w;
                GXWGFifo.f32 = tz;
                GXWGFifo.u32 = *(u32*)(node + 0x40);
                GXWGFifo.f32 = lbl_800F78C0[((idx * 2) & 3) * 2];
                GXWGFifo.f32 = lbl_800F78C0[((idx * 2) & 3) * 2 + 1];

                GXWGFifo.f32 = tx + w;
                GXWGFifo.f32 = ty + h;
                GXWGFifo.f32 = tz;
                GXWGFifo.u32 = *(u32*)(node + 0x40);
                GXWGFifo.f32 = lbl_800F78C0[((idx * 2 + 1) & 3) * 2];
                GXWGFifo.f32 = lbl_800F78C0[((idx * 2 + 1) & 3) * 2 + 1];

                GXWGFifo.f32 = tx - h;
                GXWGFifo.f32 = ty + w;
                GXWGFifo.f32 = tz;
                GXWGFifo.u32 = *(u32*)(node + 0x40);
                GXWGFifo.f32 = lbl_800F78C0[(idx & 3) * 2];
                GXWGFifo.f32 = lbl_800F78C0[(idx & 3) * 2 + 1];

                if (lbl_80366158[0x28] == 0) {
                    *(s16*)(node + 0x4A) -= 1;
                    for (c = 0; c < 4; c++) {
                        s32 v = (s8)node[0x44 + c] + node[0x40 + c];
                        if (v < 0) {
                            v = 0;
                        } else if (v > 0xFF) {
                            v = 0xFF;
                        }
                        node[0x40 + c] = (u8)v;
                    }
                    for (n = 0; n < 3; n++) {
                        *(f32*)(node + 0x1C + n * 4) = *(f32*)(node + 0x28 + n * 4) / *(f32*)(node + 0x34);
                        *(f32*)(node + 0x10 + n * 4) = *(f32*)(node + 0x10 + n * 4) + *(f32*)(node + 0x1C + n * 4);
                        *(f32*)(node + 0x4 + n * 4) = *(f32*)(node + 0x4 + n * 4) + *(f32*)(node + 0x10 + n * 4);
                    }
                }
            }
        }
        node = *(u8**)node;
    }

    GXLoadPosMtxImm(lbl_8017FFE0, 0);
    return count == 0;
}

void setPeachStarEffectTarget(Vec* target) {
    u8* effect = *(u8**)(lbl_803CBC84 + 0x4);

    while (effect != NULL) {
        if ((effect[0x17] & 0x7F) == 0x9) {
            break;
        }
        effect = *(u8**)(effect + 0x4);
    }
    if (effect != NULL) {
        memcpy(effect + 0x24, effect + 0x18, 0xC);
        memcpy(effect + 0x18, target, 0xC);
    }
}

void spawnPeachStarEffect(Vec* from, Vec* to, u8* desc) {
    u32* c = (u32*)desc;
    u8* group;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* node;
    s32 taken = 0;
    s32 remaining = (s32)c[0x8 / 4];
    Vec dir;
    f32 radius;
    f32 spread;
    f32 angle;
    f32 len;

    PSVECSubtract(to, from, &dir);
    len = PSVECMag(&dir);

    group = (u8*)lbl_803CBC80;
    list = (u8*)lbl_803CBC74;
    if (group != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining != 0) {
            group = NULL;
        } else {
            *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (taken & 0xFFF);
            if (taken != 0) {
                *(void**)(group + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(group + 0xC) = NULL;
            }
        }
    }

    if (group != NULL) {
        lbl_803CBC80 = *(void**)(group + 0x4);
        *(void**)(group + 0x8) = (void*)fn_8002D82C;
        group[0x16] = 0x80;
        group[0x17] = (group[0x17] & ~0x7F) | 9;
        group[0x17] |= 0x80;
        group[0x14] &= ~0xF0;
        *(void**)(group + 0x4) = NULL;
        *(void**)(group + 0x0) = NULL;

        prev = (u8*)&lbl_803CBC84;
        while (1) {
            u8* succ = *(u8**)(prev + 0x4);

            if (succ == NULL || succ[0x16] >= group[0x16]) {
                break;
            }
            prev = succ;
        }
        {
            u8* succ = *(u8**)(prev + 0x4);

            *(void**)(group + 0x4) = succ;
            if (succ != NULL) {
                *(void**)succ = group;
            }
            *(void**)group = prev;
            *(void**)(prev + 0x4) = group;
        }

        *(u32*)(group + 0x10) = c[0];
        memcpy(group + 0x18, from, 12);
        memcpy(group + 0x24, &dir, 12);
        *(u16*)(group + 0x48) = (u16)(rand() % (s32)(c[0x1C / 4] ? c[0x1C / 4] : 1));
        *(u16*)(group + 0x4A) = (u16)(c[0x14 / 4] + rand() % (s32)(c[0x20 / 4] ? c[0x20 / 4] : 1));
        *(f32*)(group + 0x34) = len;

        node = *(u8**)(group + 0xC);
        while (node != NULL) {
            radius = (f32)c[0x30 / 4] / lbl_803CC614;
            spread = (f32)rand() / lbl_803CC614;
            angle = spread * (f32)c[0x34 / 4] / lbl_803CC614;
            PSVECScale(&dir, radius * angle, (Vec*)(node + 0x28));
            *(f32*)(node + 0x28) = *(f32*)(node + 0x28) * lbl_803CC5F0;
            PSVECAdd((Vec*)(node + 0x10), (Vec*)(node + 0x1C), (Vec*)(node + 0x10));
            *(f32*)(node + 0x34) = lbl_803CC608;
            node = *(u8**)node;
        }
    }
}

BOOL fn_8002E3DC(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    u8* node = *(u8**)(group + 0xC);
    u8* base;
    u8* tex;
    s32 alive = 0;
    s32 k;
    s32 n;
    s32 j;
    f32 scale = lbl_803CC5F0;
    f32 zOff = lbl_803CC5F4;
    f32 w;
    f32 h;

    GXSetZMode(1, 7, 0);
    GXSetBlendMode(1, 4, 5, 0);

    while (node != NULL) {
        if (lbl_80366158[0x28] == 0) {
            s16 life = *(s16*)(node + 0x4A);
            if (life > 0) {
                life -= 1;
            }
            *(s16*)(node + 0x4A) = life;
            node[0x43] = (u8)(node[0x43] - *(s32*)(node + 0x18) / *(s32*)(node + 0x1C));
            {
                f32 t = (f32)(*(s32*)(node + 0x1C) - life) / (f32)*(s32*)(node + 0x1C);
                *(f32*)(node + 0x3C) = *(f32*)(node + 0x10) + (*(f32*)(node + 0x14) - *(f32*)(node + 0x10)) * t;
                *(f32*)(node + 0x38) = *(f32*)(node + 0x3C);
            }
        }

        w = *(f32*)(node + 0x38);
        h = *(f32*)(node + 0x3C);
        lbl_80180010[0].x = -w * scale;
        lbl_80180010[0].y = -h * scale;
        lbl_80180010[0].z = zOff;
        lbl_80180010[1].x = w * scale;
        lbl_80180010[1].y = -h * scale;
        lbl_80180010[1].z = zOff;
        lbl_80180010[2].x = w * scale;
        lbl_80180010[2].y = h * scale;
        lbl_80180010[2].z = zOff;
        lbl_80180010[3].x = -w * scale;
        lbl_80180010[3].y = h * scale;
        lbl_80180010[3].z = zOff;
        for (k = 0; k < 4; k++) {
            PSMTXMultVec(graphicRelatedStructMaybe.mtx, &lbl_80180010[k], &lbl_80180010[k]);
        }

        base = *(u8**)(group + 0x10);
        if (base == NULL) {
            GXSetTevOrder(0, 0, 0, 4);
        } else {
            GXSetTevOrder(0, 0, 1, 4);
            tex = base + (*(u16*)(base + node[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
            if (*(void**)(tex + 0x4) != NULL) {
                GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
                GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
                GXLoadTlut(&tlutObj, 0);
            } else {
                GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
            }
            GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
            GXLoadTexObj(&texObj, 1);
        }

        GXBegin(0x80, 0, 4);
        k = 0;
        for (n = 0; n < 2; n++) {
            for (j = 0; j < 2; j++) {
                Vec* corner = &lbl_80180010[n * 2 + j];
                u16* uv = (u16*)(lbl_800F7860 + (node[0x4E] + k) * 4);

                GXWGFifo.f32 = *(f32*)(node + 0x4) + corner->x;
                GXWGFifo.f32 = *(f32*)(node + 0x8) + corner->y;
                GXWGFifo.f32 = *(f32*)(node + 0xC) + corner->z;
                GXWGFifo.u32 = *(u32*)(node + 0x40);
                GXWGFifo.f32 = (f32)uv[0];
                GXWGFifo.f32 = (f32)uv[1];
                k++;
            }
        }

        if (*(s16*)(node + 0x4A) > 0) {
            alive++;
        }
        node = *(u8**)node;
    }
    return alive == 0;
}

BOOL fn_8002E828(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    Mtx identity;
    u8* node = *(u8**)(group + 0xC);
    u8* base;
    u8* tex;
    s32 alive = 0;
    s32 k;
    s32 n;
    s32 j;
    f32 scale = lbl_803CC5F0;
    f32 zOff = lbl_803CC5F4;
    f32 w;
    f32 h;

    GXSetZMode(1, 7, 0);
    GXSetBlendMode(1, 4, 5, 0);

    while (node != NULL) {
        s16 life = *(s16*)(node + 0x4A);
        if (life > 0 && lbl_80366158[0x28] == 0) {
            life -= 1;
        }
        *(s16*)(node + 0x4A) = life;
        if (life > *(s32*)(node + 0x20)) {
            node[0x43] = (u8)((*(s32*)(node + 0x1C) - life) * *(s32*)(node + 0x18) / *(s32*)(node + 0x20));
        } else {
            node[0x43] = (u8)(*(s32*)(node + 0x18) * life / *(s32*)(node + 0x20));
        }
        {
            f32 t = (f32)(*(s32*)(node + 0x1C) - life) / (f32)*(s32*)(node + 0x1C);
            *(f32*)(node + 0x3C) = *(f32*)(node + 0x10) + (*(f32*)(node + 0x14) - *(f32*)(node + 0x10)) * t;
            *(f32*)(node + 0x38) = *(f32*)(node + 0x3C);
        }

        w = *(f32*)(node + 0x38);
        h = *(f32*)(node + 0x3C);
        lbl_80180010[0].x = -w * scale;
        lbl_80180010[0].y = -h * scale;
        lbl_80180010[0].z = zOff;
        lbl_80180010[1].x = w * scale;
        lbl_80180010[1].y = -h * scale;
        lbl_80180010[1].z = zOff;
        lbl_80180010[2].x = w * scale;
        lbl_80180010[2].y = h * scale;
        lbl_80180010[2].z = zOff;
        lbl_80180010[3].x = -w * scale;
        lbl_80180010[3].y = h * scale;
        lbl_80180010[3].z = zOff;
        for (k = 0; k < 4; k++) {
            PSMTXMultVec(graphicRelatedStructMaybe.mtx, &lbl_80180010[k], &lbl_80180010[k]);
        }

        base = *(u8**)(group + 0x10);
        if (base == NULL) {
            GXSetTevOrder(0, 0, 0, 4);
        } else {
            GXSetTevOrder(0, 0, 1, 4);
            tex = base + (*(u16*)(base + node[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
            if (*(void**)(tex + 0x4) != NULL) {
                GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
                GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
                GXLoadTlut(&tlutObj, 0);
            } else {
                GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
            }
            GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
            GXLoadTexObj(&texObj, 1);
        }

        GXBegin(0x80, 0, 4);
        k = 0;
        for (n = 0; n < 2; n++) {
            for (j = 0; j < 2; j++) {
                Vec* corner = &lbl_80180010[n * 2 + j];
                u16* uv = (u16*)(lbl_800F7860 + (node[0x4E] + k) * 4);

                GXWGFifo.f32 = *(f32*)(node + 0x4) + corner->x;
                GXWGFifo.f32 = *(f32*)(node + 0x8) + corner->y;
                GXWGFifo.f32 = *(f32*)(node + 0xC) + corner->z;
                GXWGFifo.u32 = *(u32*)(node + 0x40);
                GXWGFifo.f32 = (f32)uv[0];
                GXWGFifo.f32 = (f32)uv[1];
                k++;
            }
        }

        if (*(s16*)(node + 0x4A) > 0) {
            alive++;
        }
        node = *(u8**)node;
    }
    return alive == 0;
}

BOOL fn_8002ECA0(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    u8* node;
    u8** link;
    u8* base = *(u8**)(group + 0x10);
    u8* tex;
    u8* removedHead = NULL;
    u8* removedTail = NULL;
    Vec dir;
    f32 mag;
    s32 alive = 0;
    s32 n;
    s32 j;
    s32 k;

    GXSetBlendMode(1, 4, 5, 0);
    GXSetZMode(1, 3, 0);

    node = *(u8**)(group + 0xC);
    if (node != NULL) {
        PSVECSubtract((Vec*)(node + 0x4), (Vec*)(node + 0x10), &dir);
    }
    if (base == NULL) {
        GXSetTevOrder(0, 0, 0, 4);
    } else {
        GXSetTevOrder(0, 0, 1, 4);
        tex = base + (*(u16*)(base + node[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
        if (*(void**)(tex + 0x4) != NULL) {
            GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
            GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
            GXLoadTlut(&tlutObj, 0);
        } else {
            GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
        }
        GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
        GXLoadTexObj(&texObj, 1);
    }

    link = (u8**)(group + 0xC);
    node = *link;
    while (node != NULL) {
        PSVECSubtract((Vec*)(node + 0x4), (Vec*)(node + 0x10), &dir);
        mag = PSVECMag(&dir);
        if (mag != lbl_803CC5F4) {
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, *(f32*)(node + 0x1C) * lbl_803CC5F0, &dir);
        } else {
            dir.x = lbl_803CC5F4;
            dir.y = lbl_803CC5F4;
            dir.z = -(*(f32*)(node + 0x1C)) * lbl_803CC5F0;
        }
        node[0x43] = (u8)((s32)node[0x24] * *(s16*)(node + 0x4A) / *(s32*)(node + 0x28));

        GXBegin(0x80, 0, 8);
        k = 0;
        for (n = 0; n < 2; n++) {
            for (j = 0; j < 4; j++) {
                u16* uv = (u16*)(lbl_800F7860 + (node[0x4E] + k) * 4);
                f32 sx = (j & 1) ? 1.0f : -1.0f;
                f32 sy = (j & 2) ? 1.0f : -1.0f;
                GXWGFifo.f32 = *(f32*)(node + 0x4) + sx * dir.x;
                GXWGFifo.f32 = *(f32*)(node + 0x8) + sy * dir.y;
                GXWGFifo.f32 = *(f32*)(node + 0xC) + dir.z;
                GXWGFifo.u32 = *(u32*)(node + 0x40);
                GXWGFifo.f32 = (f32)uv[0];
                GXWGFifo.f32 = (f32)uv[1];
                k++;
            }
        }

        *(s16*)(node + 0x4A) -= 1;
        if (*(s16*)(node + 0x4A) == 0) {
            *link = *(u8**)node;
            if (removedTail == NULL) {
                removedHead = node;
            } else {
                *(u8**)removedTail = node;
            }
            removedTail = node;
            *(u8**)node = NULL;
            *(u16*)(group + 0x14) -= 1;
        } else {
            link = (u8**)node;
            alive++;
        }
        node = *link;
    }

    if (removedHead != NULL) {
        u8* tail = removedHead;
        while (*(u8**)tail != NULL) {
            tail = *(u8**)tail;
        }
        *(void**)tail = lbl_803CBC74;
        lbl_803CBC74 = removedHead;
    }
    return alive == 0;
}

BOOL fn_8002F1AC(Vec* src, s32 key) {
    u8* effect = *(u8**)(lbl_803CBC84 + 0x4);
    u8* node;

    while (effect != NULL) {
        if ((effect[0x17] & 0x7F) == 0x6) {
            break;
        }
        effect = *(u8**)(effect + 0x4);
    }
    if (effect == NULL || lbl_80366158[0x28] != 0) {
        return FALSE;
    }
    node = *(u8**)(effect + 0xC);
    while (node != NULL) {
        if (*(s32*)(node + 0x20) == key) {
            memcpy(node + 0x4, src, 0xC);
            *(s16*)(node + 0x4A) += 1;
            return TRUE;
        }
        node = *(u8**)node;
    }
    return FALSE;
}

void fn_8002F258(s32 arg0, s32 arg1, u8* arg2) {
    u8* node = (u8*)lbl_803CBC84;
    u8* temp = NULL;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* tail;
    s32 taken = 0;
    s32 remaining;
    u8 tempHeader[0x20];

    node = *(u8**)(node + 0x4);
    while (node != NULL && (node[0x17] & 0x7F) != 6) {
        node = *(u8**)(node + 0x4);
    }

    remaining = *(s32*)(arg2 + 0x8);
    list = (u8*)lbl_803CBC74;
    if (node != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining == 0) {
            temp = tempHeader;
            *(u16*)(temp + 0x14) = taken & 0xFFF;
            if (taken != 0) {
                *(void**)(temp + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(temp + 0xC) = NULL;
            }
            tail = *(u8**)(node + 0xC);
            while (*(void**)tail != NULL) {
                tail = *(u8**)tail;
            }
            *(void**)tail = *(void**)(temp + 0xC);
            *(u16*)(node + 0x14) = (*(u16*)(node + 0x14) & 0xF000) |
                                   (((*(u16*)(node + 0x14) & 0xFFF) + (*(u16*)(temp + 0x14) & 0xFFF)) & 0xFFF);
        }
    } else {
        u8* group = (u8*)lbl_803CBC80;
        s32 i = 0;

        list = (u8*)lbl_803CBC74;
        lastTaken = NULL;
        remaining = *(s32*)(arg2 + 0x8);
        if (group != NULL) {
            while (list != NULL && remaining != 0) {
                lastTaken = list;
                list = *(u8**)list;
                i++;
                remaining--;
            }
            if (remaining == 0) {
                *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (i & 0xFFF);
                if (i != 0) {
                    *(void**)(group + 0xC) = lbl_803CBC74;
                    lbl_803CBC74 = list;
                    if (lastTaken != NULL) {
                        *(void**)lastTaken = NULL;
                    }
                } else {
                    *(void**)(group + 0xC) = NULL;
                }
            } else {
                group = NULL;
            }
        }
        if (group != NULL) {
            lbl_803CBC80 = *(void**)(group + 0x4);
            *(void**)(group + 0x8) = (void*)fn_8002ECA0;
            group[0x16] = 0x10;
            group[0x17] = (group[0x17] & ~0x7F) | 6;
            group[0x17] |= 0x80;
            group[0x14] &= ~0xF0;
            *(void**)(group + 0x4) = NULL;
            *(void**)(group + 0x0) = NULL;

            prev = (u8*)&lbl_803CBC84;
            while (1) {
                u8* succ = *(u8**)(prev + 0x4);

                if (succ == NULL || succ[0x16] >= group[0x16]) {
                    break;
                }
                prev = succ;
            }
            {
                u8* succ = *(u8**)(prev + 0x4);

                *(void**)(group + 0x4) = succ;
                if (succ != NULL) {
                    *(void**)succ = group;
                }
                *(void**)group = prev;
                *(void**)(prev + 0x4) = group;
            }
        }
    }
}

void fn_8002F5F4(Vec* pos, s32 id, u8* desc) {
    u8* group;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* node;
    s32 taken = 0;
    s32 remaining;
    s32 count;
    s32 i;
    u32 color;
    f32 frac;
    f32 spread;
    Vec offs;

    count = *(u32*)(desc + 0x8);
    remaining = count * 2;
    group = (u8*)lbl_803CBC80;
    list = (u8*)lbl_803CBC74;
    if (group != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining != 0) {
            group = NULL;
        } else {
            *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (taken & 0xFFF);
            if (taken != 0) {
                *(void**)(group + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(group + 0xC) = NULL;
            }
        }
    }

    if (group != NULL) {
        lbl_803CBC80 = *(void**)(group + 0x4);
        *(void**)(group + 0x8) = (void*)fn_8002F9FC;
        group[0x16] = 0x80;
        group[0x17] = (group[0x17] & ~0x7F) | 8;
        group[0x17] |= 0x80;
        group[0x14] &= ~0xF0;
        *(void**)(group + 0x4) = NULL;
        *(void**)(group + 0x0) = NULL;

        prev = (u8*)lbl_803CBC84;
        while (1) {
            u8* succ = *(u8**)(prev + 0x4);

            if (succ == NULL || succ[0x16] >= group[0x16]) {
                break;
            }
            prev = succ;
        }
        {
            u8* succ = *(u8**)(prev + 0x4);

            *(void**)(group + 0x4) = succ;
            if (succ != NULL) {
                *(void**)succ = group;
            }
            *(void**)group = prev;
            *(void**)(prev + 0x4) = group;
        }

        color = (u32)*(u32*)(desc + 0x20);
        color = (color << 24) | (color << 16) | (color << 8) | 0xFF;
        node = *(u8**)(group + 0xC);
        for (i = 0; i < count && node != NULL; i++) {
            frac = (count > 1) ? (f32)i / (f32)(count - 1) : 0.0f;
            spread = *(f32*)(desc + 0x14) * frac;
            offs.x = *(f32*)(desc + 0x0) + spread;
            offs.y = *(f32*)(desc + 0x4) * frac;
            offs.z = *(f32*)(desc + 0x8) * frac;
            *(f32*)(node + 0x4) = pos->x + offs.x;
            *(f32*)(node + 0x8) = pos->y + offs.y;
            *(f32*)(node + 0xC) = pos->z + offs.z;
            *(f32*)(node + 0x38) = *(f32*)(desc + 0x14);
            *(f32*)(node + 0x3C) = *(f32*)(desc + 0x14);
            *(u32*)(node + 0x40) = color;
            node[0x4D] = (u8)*(u32*)(desc + 0x4);
            node[0x4E] = 0;
            node[0x4F] = 1;
            node = *(u8**)node;
        }
    }
}

void fn_8002F9FC(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    u8* node;
    u8* base;
    u8* tex;
    f32 zOff = lbl_803CC5F4;
    f32 scale = lbl_803CC5F0;
    s32 k;
    s32 n;
    s32 j;
    s32 i;

    GXSetZMode(1, 3, 0);
    node = *(u8**)(group + 0xC);
    while (node != NULL) {
        f32 w = *(f32*)(node + 0x38) * scale;
        f32 h = *(f32*)(node + 0x3C) * scale;

        lbl_80180010[0].x = -w;
        lbl_80180010[0].y = -h;
        lbl_80180010[0].z = zOff;
        lbl_80180010[1].x = w;
        lbl_80180010[1].y = -h;
        lbl_80180010[1].z = zOff;
        lbl_80180010[2].x = w;
        lbl_80180010[2].y = h;
        lbl_80180010[2].z = zOff;
        lbl_80180010[3].x = -w;
        lbl_80180010[3].y = h;
        lbl_80180010[3].z = zOff;
        for (i = 0; i < 4; i++) {
            PSMTXMultVec(graphicRelatedStructMaybe.mtx, &lbl_80180010[i], &lbl_80180010[i]);
        }

        if (node[0x4F] != 0) {
            GXSetBlendMode(3, 1, 1, 0);
        } else {
            GXSetBlendMode(1, 4, 1, 0);
        }

        base = *(u8**)(group + 0x10);
        if (base == NULL) {
            GXSetTevOrder(0, 0, 0, 4);
        } else {
            GXSetTevOrder(0, 0, 1, 4);
            tex = base + (*(u16*)(base + node[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
            if (*(void**)(tex + 0x4) != NULL) {
                GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
                GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
                GXLoadTlut(&tlutObj, 0);
            } else {
                GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
            }
            GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
            GXLoadTexObj(&texObj, 1);
        }

        GXBegin(0x80, 0, 4);
        k = 0;
        for (n = 0; n < 2; n++) {
            for (j = 0; j < 2; j++) {
                Vec* corner = &lbl_80180010[n * 2 + j];
                u16* uv = (u16*)(lbl_800F7860 + (node[0x4E] + k) * 4);

                GXWGFifo.f32 = *(f32*)(node + 0x4) + corner->x;
                GXWGFifo.f32 = *(f32*)(node + 0x8) + corner->y;
                GXWGFifo.f32 = *(f32*)(node + 0xC) + corner->z;
                GXWGFifo.u32 = *(u32*)(node + 0x40);
                GXWGFifo.f32 = (f32)uv[0];
                GXWGFifo.f32 = (f32)uv[1];
                k++;
            }
        }

        node = *(u8**)node;
    }
    GXSetZMode(1, 3, 1);
}

void fn_8002FDB8(void* group, s32 a0, s32 a1, s32 a2, u8* cfg) {
    u8* g = (u8*)group;
    Vec* pos = (Vec*)a0;
    Vec* dir = (Vec*)a1;
    Vec* scale = (Vec*)a2;
    u8* node;
    u32* c = (u32*)cfg;
    Vec axis;
    Vec up;
    Vec cross;
    Mtx rot;
    Mtx xform;
    Quaternion quat;
    f32 mag;
    f32 radius;
    f32 spread;
    f32 angle;
    f32 cosA;
    f32 sinA;

    *(u32*)(g + 0x10) = c[0];
    PSVECNormalize(dir, &axis);
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    PSVECCrossProduct(&axis, &up, &cross);
    mag = PSVECMag(&cross);

    node = *(u8**)(g + 0xC);
    while (node != NULL) {
        if (mag == 0.0f) {
            PSMTXIdentity(xform);
        } else {
            radius = (f32)c[0x38 / 4] / lbl_803CC614;
            angle = (f32)rand() / lbl_803CC614 * radius;
            C_QUATRotAxisRad(&quat, &cross, angle);
            PSMTXQuat(xform, &quat);
        }

        radius = (f32)c[0x34 / 4] / lbl_803CC614;
        angle = (f32)rand() / lbl_803CC614;
        PSMTXRotRad(rot, 'Y', angle * radius);
        PSMTXConcat(xform, rot, xform);
        PSMTXMultVec(lbl_8017FFE0, &axis, &axis);

        *(f32*)(node + 0x4) = pos->x;
        *(f32*)(node + 0x8) = pos->y;
        *(f32*)(node + 0xC) = pos->z;

        *(f32*)(node + 0x10) = scale->x * ((f32)c[0x10 / 4] / lbl_803CC614);
        *(f32*)(node + 0x14) = scale->y * ((f32)c[0x10 / 4] / lbl_803CC614);
        *(f32*)(node + 0x18) = scale->z * ((f32)c[0x10 / 4] / lbl_803CC614);
        *(f32*)(node + 0x34) = lbl_803CC5F4;

        angle = (f32)rand() / lbl_803CC614 * (f32)c[0x30 / 4];
        sinA = sin(angle);
        cosA = cos(angle);
        spread = (f32)c[0x34 / 4] / lbl_803CC614;
        *(f32*)(node + 0x38) = (sinA - cosA) * spread;
        *(f32*)(node + 0x3C) = (sinA + cosA) * spread;
        *(f32*)(node + 0x1C) = (f32)rand() / lbl_803CC614;
        *(f32*)(node + 0x20) = (f32)c[0x20 / 4] / lbl_803CC614;
        *(f32*)(node + 0x24) = (f32)c[0x24 / 4] / lbl_803CC614;
        *(s32*)(node + 0x2C) = (s32)c[0x18 / 4] - (s32)c[0x1C / 4];
        *(f32*)(node + 0x28) = (f32)rand() / lbl_803CC614;
        *(u32*)(node + 0x40) = c[0x40 / 4];
        *(u32*)(node + 0x30) = c[0x2C / 4];
        node[0x44] = (u8)c[0x4C / 4];
        *(s16*)(node + 0x4A) = (s16)c[0x18 / 4];
        *(s16*)(node + 0x48) = (s16)c[0x18 / 4];
        node[0x4C] = 1;
        node[0x4E] = 0;
        node[0x4D] = (u8)c[0x4 / 4];
        node[0x4F] = (u8)c[0x28 / 4];
        node = *(u8**)node;
    }
}

void fn_80030470(s32 arg0, s32 arg1, s32 arg2, u8* arg3, u8 id) {
    u8* node = (u8*)lbl_803CBC84;
    u8* temp = NULL;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* tail;
    s32 taken = 0;
    s32 remaining;
    u8 tempHeader[0x20];

    node = *(u8**)(node + 0x4);
    while (node != NULL && (node[0x17] & 0x7F) != id) {
        node = *(u8**)(node + 0x4);
    }

    remaining = *(s32*)(arg3 + 0x8);
    list = (u8*)lbl_803CBC74;
    if (node != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining == 0) {
            temp = tempHeader;
            *(u16*)(temp + 0x14) = taken & 0xFFF;
            if (taken != 0) {
                *(void**)(temp + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(temp + 0xC) = NULL;
            }
            fn_8002FDB8(temp, arg0, arg1, arg2, arg3);
            tail = *(u8**)(node + 0xC);
            while (*(void**)tail != NULL) {
                tail = *(u8**)tail;
            }
            *(void**)tail = *(void**)(temp + 0xC);
            *(u16*)(node + 0x14) = (*(u16*)(node + 0x14) & 0xF000) |
                                   (((*(u16*)(node + 0x14) & 0xFFF) + (*(u16*)(temp + 0x14) & 0xFFF)) & 0xFFF);
        }
    } else {
        u8* group = (u8*)lbl_803CBC80;
        s32 i = 0;

        list = (u8*)lbl_803CBC74;
        lastTaken = NULL;
        remaining = *(s32*)(arg3 + 0x8);
        if (group != NULL) {
            while (list != NULL && remaining != 0) {
                lastTaken = list;
                list = *(u8**)list;
                i++;
                remaining--;
            }
            if (remaining == 0) {
                *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (i & 0xFFF);
                if (i != 0) {
                    *(void**)(group + 0xC) = lbl_803CBC74;
                    lbl_803CBC74 = list;
                    if (lastTaken != NULL) {
                        *(void**)lastTaken = NULL;
                    }
                } else {
                    *(void**)(group + 0xC) = NULL;
                }
            } else {
                group = NULL;
            }
        }
        if (group != NULL) {
            lbl_803CBC80 = *(void**)(group + 0x4);
            *(void**)(group + 0x8) = (void*)fn_80031034;
            group[0x16] = 0x11;
            group[0x17] = (group[0x17] & ~0x7F) | id;
            group[0x17] |= 0x80;
            group[0x14] &= ~0xF0;
            *(void**)(group + 0x4) = NULL;
            *(void**)(group + 0x0) = NULL;

            prev = (u8*)&lbl_803CBC84;
            while (1) {
                u8* succ = *(u8**)(prev + 0x4);

                if (succ == NULL || succ[0x16] >= group[0x16]) {
                    break;
                }
                prev = succ;
            }
            {
                u8* succ = *(u8**)(prev + 0x4);

                *(void**)(group + 0x4) = succ;
                if (succ != NULL) {
                    *(void**)succ = group;
                }
                *(void**)group = prev;
                *(void**)(prev + 0x4) = group;
            }
            group[0x18] = 0;
            fn_8002FDB8(group, arg0, arg1, arg2, arg3);
        }
    }
}

void fn_80030720(void* group, s32 a0, s32 a1, u8* cfg) {
    u8* g = (u8*)group;
    Vec* pos = (Vec*)a0;
    Vec* dir = (Vec*)a1;
    u8* node;
    u32* c = (u32*)cfg;
    Vec axis;
    Vec up;
    Vec cross;
    Mtx rot;
    Mtx xform;
    Quaternion quat;
    f32 mag;
    f32 radius;
    f32 spread;
    f32 angle;
    f32 cosA;
    f32 sinA;

    *(u32*)(g + 0x10) = c[0];
    PSVECNormalize(dir, &axis);
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    PSVECCrossProduct(&axis, &up, &cross);
    mag = PSVECMag(&cross);

    node = *(u8**)(g + 0xC);
    while (node != NULL) {
        if (mag == 0.0f) {
            PSMTXIdentity(xform);
        } else {
            radius = (f32)c[0x38 / 4] / lbl_803CC614;
            angle = (f32)rand() / lbl_803CC614 * radius;
            C_QUATRotAxisRad(&quat, &cross, angle);
            PSMTXQuat(xform, &quat);
        }

        radius = (f32)c[0x34 / 4] / lbl_803CC614;
        angle = (f32)rand() / lbl_803CC614;
        PSMTXRotRad(rot, 'Y', angle * radius);
        PSMTXConcat(xform, rot, xform);
        PSMTXMultVec(xform, &axis, &axis);

        *(f32*)(node + 0x4) = pos->x;
        *(f32*)(node + 0x8) = pos->y;
        *(f32*)(node + 0xC) = pos->z;

        radius = (f32)c[0x10 / 4] / lbl_803CC614;
        spread = (f32)rand() / lbl_803CC614;
        *(f32*)(node + 0x10) = axis.x * radius * spread;
        *(f32*)(node + 0x14) = axis.y * radius * spread;
        *(f32*)(node + 0x18) = axis.z * radius * spread;
        *(f32*)(node + 0x34) = lbl_803CC5F4;

        angle = (f32)rand() / lbl_803CC614 * (f32)c[0x30 / 4];
        sinA = sin(angle);
        cosA = cos(angle);
        *(f32*)(node + 0x38) = (sinA - cosA) * radius;
        *(f32*)(node + 0x3C) = (sinA + cosA) * radius;
        *(f32*)(node + 0x1C) = (f32)rand() / lbl_803CC614;
        *(f32*)(node + 0x20) = (f32)c[0x20 / 4] / lbl_803CC614;
        *(f32*)(node + 0x24) = (f32)c[0x24 / 4] / lbl_803CC614;
        *(s32*)(node + 0x2C) = (s32)c[0x18 / 4] - (s32)c[0x1C / 4];
        *(f32*)(node + 0x28) = (f32)rand() / lbl_803CC614;
        *(u32*)(node + 0x40) = c[0x40 / 4];
        *(u32*)(node + 0x30) = c[0x2C / 4];
        *(f32*)(node + 0x34) = (f32)c[0x48 / 4] / lbl_803CC614;
        node[0x44] = (u8)c[0x4C / 4];
        *(s16*)(node + 0x4A) = (s16)c[0x18 / 4];
        *(s16*)(node + 0x48) = (s16)c[0x18 / 4];
        node[0x4C] = 1;
        node[0x4E] = 0;
        node[0x4D] = (u8)c[0x4 / 4];
        node[0x4F] = (u8)c[0x28 / 4];
        node = *(u8**)node;
    }
}

void fn_80030D88(s32 arg0, s32 arg1, u8* arg2, u8 id) {
    u8* node = (u8*)lbl_803CBC84;
    u8* temp = NULL;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* tail;
    s32 taken = 0;
    s32 remaining;
    u8 tempHeader[0x20];

    if (*(s32*)(arg2 + 0x8) <= 0) {
        return;
    }

    node = *(u8**)(node + 0x4);
    while (node != NULL && (node[0x17] & 0x7F) != id) {
        node = *(u8**)(node + 0x4);
    }

    remaining = *(s32*)(arg2 + 0x8);
    list = (u8*)lbl_803CBC74;
    if (node != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining == 0) {
            temp = tempHeader;
            *(u16*)(temp + 0x14) = taken & 0xFFF;
            if (taken != 0) {
                *(void**)(temp + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(temp + 0xC) = NULL;
            }
            fn_80030720(temp, arg0, arg1, arg2);
            tail = *(u8**)(node + 0xC);
            while (*(void**)tail != NULL) {
                tail = *(u8**)tail;
            }
            *(void**)tail = *(void**)(temp + 0xC);
            *(u16*)(node + 0x14) = (*(u16*)(node + 0x14) & 0xF000) |
                                   (((*(u16*)(node + 0x14) & 0xFFF) + (*(u16*)(temp + 0x14) & 0xFFF)) & 0xFFF);
        }
    } else {
        u8* group = (u8*)lbl_803CBC80;
        s32 i = 0;

        list = (u8*)lbl_803CBC74;
        lastTaken = NULL;
        remaining = *(s32*)(arg2 + 0x8);
        if (group != NULL) {
            while (list != NULL && remaining != 0) {
                lastTaken = list;
                list = *(u8**)list;
                i++;
                remaining--;
            }
            if (remaining == 0) {
                *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (i & 0xFFF);
                if (i != 0) {
                    *(void**)(group + 0xC) = lbl_803CBC74;
                    lbl_803CBC74 = list;
                    if (lastTaken != NULL) {
                        *(void**)lastTaken = NULL;
                    }
                } else {
                    *(void**)(group + 0xC) = NULL;
                }
            } else {
                group = NULL;
            }
        }
        if (group != NULL) {
            lbl_803CBC80 = *(void**)(group + 0x4);
            *(void**)(group + 0x8) = (void*)fn_80031034;
            group[0x16] = 0x11;
            group[0x17] = (group[0x17] & ~0x7F) | id;
            group[0x17] |= 0x80;
            group[0x14] &= ~0xF0;
            *(void**)(group + 0x4) = NULL;
            *(void**)(group + 0x0) = NULL;

            prev = (u8*)&lbl_803CBC84;
            while (1) {
                u8* succ = *(u8**)(prev + 0x4);

                if (succ == NULL || succ[0x16] >= group[0x16]) {
                    break;
                }
                prev = succ;
            }
            {
                u8* succ = *(u8**)(prev + 0x4);

                *(void**)(group + 0x4) = succ;
                if (succ != NULL) {
                    *(void**)succ = group;
                }
                *(void**)group = prev;
                *(void**)(prev + 0x4) = group;
            }
            group[0x18] = 0;
            fn_80030720(group, arg0, arg1, arg2);
        }
    }
}

BOOL fn_80031034(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    u8* node;
    u8* base = *(u8**)(group + 0x10);
    u8* tex;
    u8* prev;
    u8** link;
    u8* removedHead = NULL;
    u8* removedTail = NULL;
    s32 alive = 0;
    s32 k;
    s32 n;
    s32 j;
    s32 count = *(u16*)(group + 0x14) & 0xFFF;
    Vec corner[4];
    Vec eye;
    f32 w;
    f32 h;

    GXLoadPosMtxImm(*(Mtx*)(lbl_8017EC00 + 0x13E0), 0);
    GXSetZMode(1, 3, group[0x18]);

    node = *(u8**)(group + 0xC);
    if (base == NULL) {
        GXSetTevOrder(0, 0, 0, 4);
    } else {
        GXSetTevOrder(0, 0, 1, 4);
        if (node != NULL) {
            tex = base + (*(u16*)(base + node[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
            if (*(void**)(tex + 0x4) != NULL) {
                GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
                GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
                GXLoadTlut(&tlutObj, 0);
            } else {
                GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
            }
            GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
            GXLoadTexObj(&texObj, 1);
        }
    }

    link = (u8**)(group + 0xC);
    node = *link;
    while (node != NULL) {
        if (*(s16*)(node + 0x4A) > 0) {
            alive++;
            PSMTXMultVec(*(Mtx*)(lbl_8017EC00 + 0x1378), (Vec*)(node + 0x4), &eye);
            w = *(f32*)(node + 0x38);
            h = *(f32*)(node + 0x3C);
            corner[0].x = -w;
            corner[0].y = -h;
            corner[0].z = lbl_803CC5F4;
            corner[1].x = w;
            corner[1].y = -h;
            corner[1].z = lbl_803CC5F4;
            corner[2].x = w;
            corner[2].y = h;
            corner[2].z = lbl_803CC5F4;
            corner[3].x = -w;
            corner[3].y = h;
            corner[3].z = lbl_803CC5F4;

            GXBegin(0x80, 0, 4);
            k = 0;
            for (n = 0; n < 2; n++) {
                for (j = 0; j < 2; j++) {
                    Vec* cc = &corner[n * 2 + j];
                    u16* uv = (u16*)(lbl_800F7860 + (node[0x4E] + k) * 4);

                    GXWGFifo.f32 = eye.x + cc->x;
                    GXWGFifo.f32 = eye.y + cc->y;
                    GXWGFifo.f32 = eye.z + cc->z;
                    GXWGFifo.u32 = *(u32*)(node + 0x40);
                    GXWGFifo.f32 = (f32)uv[0];
                    GXWGFifo.f32 = (f32)uv[1];
                    k++;
                }
            }

            if (lbl_80366158[0x28] == 0) {
                *(s16*)(node + 0x4A) -= 1;
            }
            if (*(s16*)(node + 0x4A) == 0) {
                *link = *(u8**)node;
                if (removedTail == NULL) {
                    removedHead = node;
                } else {
                    *(u8**)removedTail = node;
                }
                removedTail = node;
                *(u8**)node = NULL;
                *(u16*)(group + 0x14) -= 1;
                alive--;
            } else {
                link = (u8**)node;
            }
        } else {
            link = (u8**)node;
        }
        node = *link;
    }

    if (removedHead != NULL) {
        prev = removedHead;
        while (*(u8**)prev != NULL) {
            prev = *(u8**)prev;
        }
        *(void**)prev = lbl_803CBC74;
        lbl_803CBC74 = removedHead;
    }
    GXLoadPosMtxImm(*(Mtx*)(lbl_8017EC00 + 0x13E0), 0);
    return count == 0 || alive == 0;
}

void fn_800317C4(void* group, Vec* pos, u8* cfg) {
    u8* g = (u8*)group;
    u8* node;
    u32* c = (u32*)cfg;
    s32 count = *(u16*)(g + 0x14) & 0xFFF;
    s32 i = 0;
    f32 cosAngle;
    f32 sinAngle;
    f32 speed;
    f32 rnd;
    s32 angle;
    s32 idxA;

    *(u32*)(g + 0x10) = c[0];
    node = *(u8**)(g + 0xC);
    while (node != NULL && i < count) {
        angle = rand();
        idxA = (angle & 0x7FF);
        if (idxA >= 0x401) {
            idxA = 0x800 - idxA;
            cosAngle = -maybeCosineArray[idxA];
        } else {
            cosAngle = maybeCosineArray[idxA];
        }
        *(f32*)(node + 0x4) = pos->x;
        *(f32*)(node + 0x8) = pos->y;
        *(f32*)(node + 0xC) = pos->z;

        rnd = (f32)rand() / lbl_803CC614;
        speed = (f32)c[0x10 / 4] / lbl_803CC614;
        *(f32*)(node + 0x10) = speed * rnd * cosAngle;
        *(f32*)(node + 0x14) = lbl_803CC608;
        *(f32*)(node + 0x18) = speed * rnd * sinAngle;
        *(f32*)(node + 0x34) = lbl_803CC608;

        sinAngle = (f32)rand() / lbl_803CC614;
        cosAngle = (f32)c[0x30 / 4] / lbl_803CC614;
        *(f32*)(node + 0x38) = cosAngle * sinAngle;
        *(f32*)(node + 0x3C) = cosAngle * (1.0f - sinAngle);

        rnd = (f32)rand() / lbl_803CC614;
        *(f32*)(node + 0x1C) = rnd * lbl_803CC618;
        *(f32*)(node + 0x20) = (f32)c[0x20 / 4] / lbl_803CC614;
        *(f32*)(node + 0x24) = (f32)c[0x24 / 4] / lbl_803CC614;
        *(s32*)(node + 0x2C) = (s32)c[0x18 / 4] - (s32)c[0x1C / 4];

        angle = rand();
        *(f32*)(node + 0x28) = (f32)c[0x14 / 4] / lbl_803CC614;
        *(u32*)(node + 0x40) = c[0x40 / 4];
        *(u32*)(node + 0x30) = c[0x2C / 4];
        *(f32*)(node + 0x34) = (f32)c[0x48 / 4] / lbl_803CC614;
        node[0x44] = (u8)c[0x4C / 4];
        *(s16*)(node + 0x4A) = (s16)c[0x18 / 4];
        *(s16*)(node + 0x48) = (s16)c[0x18 / 4];
        node[0x4C] = 1;
        node[0x4E] = 0;
        node[0x4D] = (u8)c[0x4 / 4];
        node[0x4F] = (u8)c[0x28 / 4];

        i++;
        node = *(u8**)node;
    }
}

void fn_80031CA4(s32 arg0, u8* arg1) {
    u8* node = (u8*)lbl_803CBC84;
    u8* temp = NULL;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* tail;
    s32 taken = 0;
    s32 remaining;
    u8 tempHeader[0x20];

    node = *(u8**)(node + 0x4);
    while (node != NULL && (node[0x17] & 0x7F) != 5) {
        node = *(u8**)(node + 0x4);
    }

    remaining = *(s32*)(arg1 + 0x8);
    list = (u8*)lbl_803CBC74;
    if (node != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining == 0) {
            temp = tempHeader;
            *(u16*)(temp + 0x14) = taken & 0xFFF;
            if (taken != 0) {
                *(void**)(temp + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(temp + 0xC) = NULL;
            }
            fn_800317C4(temp, (Vec*)arg0, arg1);
            tail = *(u8**)(node + 0xC);
            while (*(void**)tail != NULL) {
                tail = *(u8**)tail;
            }
            *(void**)tail = *(void**)(temp + 0xC);
            *(u16*)(node + 0x14) = (*(u16*)(node + 0x14) & 0xF000) |
                                   (((*(u16*)(node + 0x14) & 0xFFF) + (*(u16*)(temp + 0x14) & 0xFFF)) & 0xFFF);
        }
    } else {
        u8* group = (u8*)lbl_803CBC80;
        s32 i = 0;

        list = (u8*)lbl_803CBC74;
        lastTaken = NULL;
        remaining = *(s32*)(arg1 + 0x8);
        if (group != NULL) {
            while (list != NULL && remaining != 0) {
                lastTaken = list;
                list = *(u8**)list;
                i++;
                remaining--;
            }
            if (remaining == 0) {
                *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (i & 0xFFF);
                if (i != 0) {
                    *(void**)(group + 0xC) = lbl_803CBC74;
                    lbl_803CBC74 = list;
                    if (lastTaken != NULL) {
                        *(void**)lastTaken = NULL;
                    }
                } else {
                    *(void**)(group + 0xC) = NULL;
                }
            } else {
                group = NULL;
            }
        }
        if (group != NULL) {
            lbl_803CBC80 = *(void**)(group + 0x4);
            *(void**)(group + 0x8) = (void*)fn_80031034;
            group[0x16] = 0x11;
            group[0x17] = (group[0x17] & ~0x7F) | 5;
            group[0x17] |= 0x80;
            group[0x14] &= ~0xF0;
            *(void**)(group + 0x4) = NULL;
            *(void**)(group + 0x0) = NULL;

            prev = (u8*)&lbl_803CBC84;
            while (1) {
                u8* succ = *(u8**)(prev + 0x4);

                if (succ == NULL || succ[0x16] >= group[0x16]) {
                    break;
                }
                prev = succ;
            }
            {
                u8* succ = *(u8**)(prev + 0x4);

                *(void**)(group + 0x4) = succ;
                if (succ != NULL) {
                    *(void**)succ = group;
                }
                *(void**)group = prev;
                *(void**)(prev + 0x4) = group;
            }
            group[0x18] = 0;
            fn_800317C4(group, (Vec*)arg0, arg1);
        }
    }
}

void* fn_80031F34(void* head, s32 count) {
    void* result = head;

    if (count != 0) {
        u8* buf = _OSAllocFromHeap(0x20, count * 16);
        u8* cursor = buf;
        u8* node = head;
        s32 i = 0;
        Vec tmp;
        u8* p;
        s32 k;

        while (node != NULL) {
            if (i < count) {
                *(u8**)cursor = node;
                PSMTXMultVec(lbl_8017FFE0, (Vec*)(node + 0x4), &tmp);
                *(f32*)(cursor + 0x4) = tmp.z;
                cursor += 0x8;
                i++;
            } else {
                OSReport(lbl_800E688C);
                break;
            }
            node = *(u8**)node;
        }
        fn_800C07BC(buf, buf + count * 8, count, 8, fn_80032038);
        result = *(void**)buf;

        p = buf;
        k = count;
        while (--k != 0) {
            *(u8**)(*(u8**)p) = *(u8**)(p + 0x8);
            p += 0x8;
        }
        *(void**)(*(u8**)p) = NULL;
        fn_800ACFB0(buf);
    }
    return result;
}

s32 fn_80032038(const f32* a, const f32* b) {
    f32 fa = a[1];
    f32 fb = b[1];

    if (fa > fb) {
        return 1;
    }
    if (fa < fb) {
        return -1;
    }
    return 0;
}

void fn_80032064(Vec* pos) {
    u8* cfg = (u8*)lbl_800F787C;
    u8* group;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* node;
    s32 taken = 0;
    s32 remaining = 1;
    s32 cfgWord;

    lbl_800F787C[0] = lbl_803CBD0C;
    group = (u8*)lbl_803CBC80;
    list = (u8*)lbl_803CBC74;

    if (group != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining != 0) {
            group = NULL;
        } else {
            *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (taken & 0xFFF);
            if (taken != 0) {
                *(u8**)(group + 0xC) = (u8*)lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(group + 0xC) = NULL;
            }
        }
    }

    if (group != NULL) {
    lbl_803CBC80 = *(void**)(group + 0x4);
    *(void**)(group + 0x8) = (void*)fn_8002E828;
    group[0x16] = 0x80;
    group[0x17] = (group[0x17] & ~0x7F) | 6;
    group[0x17] |= 0x80;
    group[0x14] &= ~0xF0;
    *(void**)(group + 0x4) = NULL;
    *(void**)(group + 0x0) = NULL;

    prev = (u8*)&lbl_803CBC84;
    while (1) {
        u8* succ = *(u8**)(prev + 0x4);

        if (succ == NULL || succ[0x16] >= group[0x16]) {
            break;
        }
        prev = succ;
    }
    {
        u8* succ = *(u8**)(prev + 0x4);

        *(void**)(group + 0x4) = succ;
        if (succ != NULL) {
            *(void**)succ = group;
        }
        *(void**)group = prev;
        *(void**)(prev + 0x4) = group;
    }

    node = *(u8**)(group + 0xC);
    *(u32*)(group + 0x10) = *(u32*)cfg;
    ((f32*)node)[1] = pos->x;
    ((f32*)node)[2] = pos->y;
    ((f32*)node)[3] = pos->z;
    *(s32*)(node + 0x40) = -0x100;
    *(u32*)(node + 0x18) = *(u32*)(cfg + 0x10);
    cfgWord = *(s32*)(cfg + 0x14);
    *(s16*)(node + 0x4A) = (s16)cfgWord;
    *(s32*)(node + 0x1C) = (s16)cfgWord;
    *(s32*)(node + 0x20) = cfgWord / 2;
    *(f32*)(node + 0x10) = (f32)*(u32*)(cfg + 0x8) / lbl_803CC614;
    *(f32*)(node + 0x3C) = *(f32*)(node + 0x10);
    *(f32*)(node + 0x38) = *(f32*)(node + 0x10);
    *(f32*)(node + 0x14) = (f32)*(u32*)(cfg + 0xC) / lbl_803CC614;
    node[0x4D] = (u8)*(u32*)(cfg + 0x4);
    }

    fn_8002A1CC(pos, cfg);
}

void fn_80032284(Vec* pos) {
    u32 cfg[0x11];
    u8* group;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* node;
    s32 taken = 0;
    s32 remaining = 1;

    memcpy(cfg, lbl_800F787C, 0x44);
    cfg[0] = lbl_803CBD0C;
    cfg[2] = 500000;
    cfg[3] = 714720;
    cfg[4] = 0xFF;
    cfg[5] = 0x20;

    group = (u8*)lbl_803CBC80;
    list = (u8*)lbl_803CBC74;
    if (group != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining != 0) {
            group = NULL;
        } else {
            *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (taken & 0xFFF);
            if (taken != 0) {
                *(void**)(group + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(group + 0xC) = NULL;
            }
        }
    }

    if (group != NULL) {
        lbl_803CBC80 = *(void**)(group + 0x4);
        *(void**)(group + 0x8) = (void*)fn_8002E3DC;
        group[0x16] = 0;
        group[0x17] = (group[0x17] & ~0x7F) | 7;
        group[0x17] |= 0x80;
        group[0x14] &= ~0xF0;
        *(void**)(group + 0x4) = NULL;
        *(void**)(group + 0x0) = NULL;

        prev = (u8*)&lbl_803CBC84;
        while (1) {
            u8* succ = *(u8**)(prev + 0x4);

            if (succ == NULL || succ[0x16] >= group[0x16]) {
                break;
            }
            prev = succ;
        }
        {
            u8* succ = *(u8**)(prev + 0x4);

            *(void**)(group + 0x4) = succ;
            if (succ != NULL) {
                *(void**)succ = group;
            }
            *(void**)group = prev;
            *(void**)(prev + 0x4) = group;
        }

        node = *(u8**)(group + 0xC);
        *(u32*)(group + 0x10) = cfg[0];
        ((f32*)node)[1] = pos->x;
        ((f32*)node)[2] = pos->y;
        ((f32*)node)[3] = pos->z;
        *(s32*)(node + 0x40) = -0x100;
        node[0x43] = (u8)cfg[4];
        *(u32*)(node + 0x18) = cfg[4];
        *(s16*)(node + 0x4A) = (s16)cfg[5];
        *(s32*)(node + 0x1C) = (s16)cfg[5];
        *(s32*)(node + 0x20) = (s32)cfg[5] / 2;
        *(f32*)(node + 0x10) = (f32)cfg[2] / lbl_803CC614;
        *(f32*)(node + 0x3C) = *(f32*)(node + 0x10);
        *(f32*)(node + 0x38) = *(f32*)(node + 0x10);
        *(f32*)(node + 0x14) = (f32)cfg[3] / lbl_803CC614;
        node[0x4D] = (u8)cfg[1];
    }
}

void fn_800324EC(u16 id, s32 kind, s32 kind2, Vec* extra) {
    Vec pos;
    Vec pos2;
    u8* group;
    u8* list;
    u8* lastTaken = NULL;
    u8* prev;
    u8* node;
    s32 taken = 0;
    s32 remaining = 1;

    if (kind < 0 || kind >= 13 || *(u32*)(hugeAnimStruct + 0x2C50 + kind * 4) == 0) {
        return;
    }
    getAnimRelatedCoordinates(kind, id, &pos);
    if (kind2 >= 0 && kind2 < 13 && *(u32*)(hugeAnimStruct + 0x2C50 + kind2 * 4) != 0) {
        getAnimRelatedCoordinates(kind2, id, &pos2);
        PSVECSubtract(&pos2, &pos, &pos2);
        PSVECScale(&pos2, lbl_803CC5F0, &pos2);
        PSVECAdd(&pos, &pos2, &pos);
    }

    lbl_800F787C[0] = lbl_803CBD0C;

    group = (u8*)lbl_803CBC80;
    list = (u8*)lbl_803CBC74;
    if (group != NULL) {
        while (list != NULL && remaining != 0) {
            lastTaken = list;
            list = *(u8**)list;
            taken++;
            remaining--;
        }
        if (remaining != 0) {
            group = NULL;
        } else {
            *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (taken & 0xFFF);
            if (taken != 0) {
                *(void**)(group + 0xC) = lbl_803CBC74;
                lbl_803CBC74 = list;
                if (lastTaken != NULL) {
                    *(void**)lastTaken = NULL;
                }
            } else {
                *(void**)(group + 0xC) = NULL;
            }
        }
    }

    if (group != NULL) {
        lbl_803CBC80 = *(void**)(group + 0x4);
        *(void**)(group + 0x8) = (void*)fn_8002E828;
        group[0x16] = 0x80;
        group[0x17] = (group[0x17] & ~0x7F) | 6;
        group[0x17] |= 0x80;
        group[0x14] &= ~0xF0;
        *(void**)(group + 0x4) = NULL;
        *(void**)(group + 0x0) = NULL;

        prev = (u8*)lbl_803CBC84;
        while (1) {
            u8* succ = *(u8**)(prev + 0x4);

            if (succ == NULL || succ[0x16] >= group[0x16]) {
                break;
            }
            prev = succ;
        }
        {
            u8* succ = *(u8**)(prev + 0x4);

            *(void**)(group + 0x4) = succ;
            if (succ != NULL) {
                *(void**)succ = group;
            }
            *(void**)group = prev;
            *(void**)(prev + 0x4) = group;
        }

        node = *(u8**)(group + 0xC);
        *(u32*)(group + 0x10) = lbl_800F787C[0];
        ((f32*)node)[1] = pos.x;
        ((f32*)node)[2] = pos.y;
        ((f32*)node)[3] = pos.z;
        *(s32*)(node + 0x40) = -0x100;
        *(u32*)(node + 0x18) = lbl_800F787C[4];
        *(s16*)(node + 0x4A) = (s16)lbl_800F787C[5];
        *(s32*)(node + 0x1C) = (s16)lbl_800F787C[5];
        *(s32*)(node + 0x20) = (s32)lbl_800F787C[5] / 2;
        *(f32*)(node + 0x10) = (f32)lbl_800F787C[2] / lbl_803CC614;
        *(f32*)(node + 0x3C) = *(f32*)(node + 0x10);
        *(f32*)(node + 0x38) = *(f32*)(node + 0x10);
        *(f32*)(node + 0x14) = (f32)lbl_800F787C[3] / lbl_803CC614;
        node[0x4D] = (u8)lbl_800F787C[1];
    }

    if (extra != NULL) {
        fn_8002A1CC(&pos, (u8*)extra);
    }
}

BOOL fn_800328E0(u8* group) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    Mtx rot;
    Vec axis;
    Vec side;
    Vec* corner = (Vec*)(lbl_8017EC00 + 0x1410);
    Quaternion quat;
    u8* node;
    u8* base = *(u8**)(group + 0x10);
    u8* tex;
    u8* removedHead = NULL;
    u8* removedTail = NULL;
    u8** link;
    f32 w;
    f32 h;
    f32 angle;
    s32 alive = 0;
    s32 k;
    s32 n;
    s32 j;
    s32 i;

    corner[0].x = -(*(f32*)(group + 0x38)) * lbl_803CC5F0;
    corner[0].y = -(*(f32*)(group + 0x3C)) * lbl_803CC5F0;
    corner[0].z = lbl_803CC5F4;
    corner[1].x = (*(f32*)(group + 0x38)) * lbl_803CC5F0;
    corner[1].y = -(*(f32*)(group + 0x3C)) * lbl_803CC5F0;
    corner[1].z = lbl_803CC5F4;
    corner[2].x = (*(f32*)(group + 0x38)) * lbl_803CC5F0;
    corner[2].y = (*(f32*)(group + 0x3C)) * lbl_803CC5F0;
    corner[2].z = lbl_803CC5F4;
    corner[3].x = -(*(f32*)(group + 0x38)) * lbl_803CC5F0;
    corner[3].y = (*(f32*)(group + 0x3C)) * lbl_803CC5F0;
    corner[3].z = lbl_803CC5F4;
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(*(Mtx*)(lbl_8017EC00 + 0x1378), &corner[i], &corner[i]);
    }

    PSVECSubtract((Vec*)(group + 0x24), (Vec*)(group + 0x24), &side);
    PSVECCrossProduct(&side, &side, &axis);
    angle = (f32)acos((f64)PSVECDotProduct(&side, &side)) * lbl_803CC5F0;
    PSVECScale(&axis, sin(angle), &axis);
    quat.x = axis.x;
    quat.y = axis.y;
    quat.z = axis.z;
    quat.w = (f32)cos(angle);
    PSMTXQuat(rot, &quat);

    node = *(u8**)(group + 0xC);
    if (base == NULL) {
        GXSetTevOrder(0, 0, 0, 4);
    } else {
        GXSetTevOrder(0, 0, 1, 4);
        if (node != NULL) {
            tex = base + (*(u16*)(base + node[0x4D] * 0x20 + 0x20)) * 0x20 + 0x4;
            if (*(void**)(tex + 0x4) != NULL) {
                GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
                GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
                GXLoadTlut(&tlutObj, 0);
            } else {
                GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
            }
            GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
            GXLoadTexObj(&texObj, 1);
        }
    }

    link = (u8**)(group + 0xC);
    node = *link;
    while (node != NULL) {
        if (*(s16*)(node + 0x4A) != 0) {
            if (lbl_80366158[0x28] == 0) {
                for (n = 0; n < 3; n++) {
                    *(f32*)(node + 0x1C + n * 4) = *(f32*)(node + 0x28 + n * 4) / *(f32*)(node + 0x34);
                    *(f32*)(node + 0x10 + n * 4) = *(f32*)(node + 0x10 + n * 4) + *(f32*)(node + 0x1C + n * 4);
                    *(f32*)(node + 0x4 + n * 4) = *(f32*)(node + 0x4 + n * 4) + *(f32*)(node + 0x10 + n * 4);
                }
            }
            alive++;
            w = *(f32*)(node + 0x38);
            h = *(f32*)(node + 0x3C);
            GXBegin(0x80, 0, 4);
            k = 0;
            for (n = 0; n < 2; n++) {
                for (j = 0; j < 2; j++) {
                    Vec* cc = &corner[n * 2 + j];
                    u16* uv = (u16*)(lbl_800F7860 + (node[0x4E] + k) * 4);

                    GXWGFifo.f32 = *(f32*)(node + 0x4) + cc->x * w;
                    GXWGFifo.f32 = *(f32*)(node + 0x8) + cc->y * h;
                    GXWGFifo.f32 = *(f32*)(node + 0xC) + cc->z;
                    GXWGFifo.u32 = *(u32*)(node + 0x40);
                    GXWGFifo.f32 = (f32)uv[0];
                    GXWGFifo.f32 = (f32)uv[1];
                    k++;
                }
            }
            if (lbl_80366158[0x28] == 0) {
                *(s16*)(node + 0x4A) -= 1;
            }
            if (*(s16*)(node + 0x4A) == 0) {
                *link = *(u8**)node;
                if (removedTail == NULL) {
                    removedHead = node;
                } else {
                    *(u8**)removedTail = node;
                }
                removedTail = node;
                *(u8**)node = NULL;
                *(u16*)(group + 0x14) -= 1;
                alive--;
            } else {
                link = (u8**)node;
            }
        } else {
            link = (u8**)node;
        }
        node = *link;
    }

    if (removedHead != NULL) {
        u8* tail = removedHead;
        while (*(u8**)tail != NULL) {
            tail = *(u8**)tail;
        }
        *(void**)tail = lbl_803CBC74;
        lbl_803CBC74 = removedHead;
    }
    return alive <= 0;
}

void* fn_800330CC(s32 count, void* owner, Vec* pos, Vec* vel, s32 a7, u32 a8, f32 f1, f32 f2) {
    u8* group = (u8*)lbl_803CBC80;
    u8* list = (u8*)lbl_803CBC74;
    u8* lastTaken = NULL;
    u8* prev;
    s32 taken = 0;
    s32 remaining = count;

    if (group == NULL) {
        return NULL;
    }
    while (list != NULL && remaining != 0) {
        lastTaken = list;
        list = *(u8**)list;
        taken++;
        remaining--;
    }
    if (remaining != 0) {
        return NULL;
    }
    *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (taken & 0xFFF);
    if (taken != 0) {
        *(u8**)(group + 0xC) = (u8*)lbl_803CBC74;
        lbl_803CBC74 = list;
        if (lastTaken != NULL) {
            *(void**)lastTaken = NULL;
        }
    } else {
        *(void**)(group + 0xC) = NULL;
    }

    lbl_803CBC80 = *(void**)(group + 0x4);
    *(void**)(group + 0x8) = (void*)fn_800328E0;
    group[0x16] = 0x80;
    group[0x17] = (group[0x17] & ~0x7F) | 1;
    group[0x17] |= 0x80;
    group[0x14] &= ~0xF0;
    *(void**)(group + 0x4) = NULL;
    *(void**)(group + 0x0) = NULL;

    prev = (u8*)&lbl_803CBC84;
    while (1) {
        u8* succ = *(u8**)(prev + 0x4);

        if (succ == NULL || succ[0x16] >= group[0x16]) {
            break;
        }
        prev = succ;
    }
    {
        u8* succ = *(u8**)(prev + 0x4);

        *(void**)(group + 0x4) = succ;
        if (succ != NULL) {
            *(void**)succ = group;
        }
        *(void**)group = prev;
        *(void**)(prev + 0x4) = group;
    }

    *(u32*)(group + 0x10) = a8;
    memcpy(group + 0x18, pos, 0xC);
    memcpy(group + 0x24, vel, 0xC);
    *(f32*)(group + 0x30) = f1;
    *(s32*)(group + 0x34) = a7;
    *(f32*)(group + 0x38) = lbl_803CC6D0;
    *(f32*)(group + 0x3C) = lbl_803CC6D4;
    *(void**)(group + 0x40) = owner;
    *(f32*)(group + 0x44) = f2;
    return group;
}

void fn_800332B8(Vec* in, Vec* out, f32 lo1, f32 hi1, f32 lo2, f32 hi2) {
    Vec axis;
    Vec cross;
    Quaternion quat;
    f32 angle;
    s32 a;
    s32 b;
    s32 idx;
    s32 span;

    if (in != NULL) {
        memcpy(&axis, in, 0xC);
    } else {
        memcpy(&axis, lbl_800E6778, 0xC);
    }

    a = (s32)(lbl_803CC654 * (lo1 / lbl_803CC60C) + lbl_803CC5F0);
    if (hi1 != lo1) {
        span = (s32)(lbl_803CC654 * ((hi1 - lo1) / lbl_803CC60C) + lbl_803CC5F0);
        a += rand() % span;
    }
    idx = a & 0x7FF;
    if (idx >= 0x401) {
        idx = 0x800 - idx;
    }
    out->x = maybeCosineArray[idx];
    idx = (a + 0x600) & 0x7FF;
    if (idx >= 0x401) {
        idx = 0x800 - idx;
    }
    out->y = maybeCosineArray[idx];

    b = (s32)(lbl_803CC654 * (lo2 / lbl_803CC60C) + lbl_803CC5F0);
    if (hi2 != lo2) {
        span = (s32)(lbl_803CC654 * ((hi2 - lo2) / lbl_803CC60C) + lbl_803CC5F0);
        b += rand() % span;
    }
    idx = b & 0x7FF;
    if (idx >= 0x401) {
        idx = 0x800 - idx;
    }
    angle = maybeCosineArray[idx];
    out->x *= angle;
    out->z = angle;

    if (in != NULL && PSVECMag(&axis) != lbl_803CC5F4) {
        PSVECCrossProduct(&axis, out, &cross);
        if (PSVECMag(&cross) != lbl_803CC5F4) {
            C_QUATRotAxisRad(&quat, &cross, angle);
        }
    }
}

f32 fn_800335BC(s32 angle) {
    s32 idx = angle;
    s32 sign = idx >> 31;

    idx = (idx ^ sign) - sign;
    idx &= 0x7FF;
    if (idx >= 0x401) {
        idx = 0x800 - idx;
    }
    return maybeCosineArray[idx];
}

f32 fn_800335EC(s32 angle) {
    s32 idx = angle + 0x600;

    if (idx < 0) {
        idx = -idx;
    }
    idx &= 0x7FF;
    if (idx >= 0x401) {
        idx = 0x800 - idx;
    }
    return maybeCosineArray[idx];
}

void fn_80033620(u8* base) {
    u8* node = *(u8**)(base + 0xC);
    s32 count = 0;

    while (node != NULL && (*(u16*)(base + 0x14) & 0xFFF) > count) {
        u8* next = *(u8**)node;

        if (*(s16*)(node + 0x48) <= 0 && *(s16*)(node + 0x4A) != 0) {
            Vec tmp;
            Vec cand;
            f32 bestZ;
            u8* best = NULL;
            u8* q;
            void* nodeNext;
            void* bestNext;
            u8 saved[0x60];

            PSMTXMultVec(lbl_8017FFE0, (Vec*)(node + 0x4), &tmp);
            bestZ = tmp.z;
            for (q = next; q != NULL; q = *(u8**)q) {
                if (*(s16*)(q + 0x48) <= 0 && *(s16*)(q + 0x4A) != 0) {
                    PSMTXMultVec(lbl_8017FFE0, (Vec*)(q + 0x4), &cand);
                    if (bestZ > cand.z) {
                        best = q;
                        bestZ = cand.z;
                    }
                }
            }
            if (best != NULL) {
                nodeNext = *(void**)node;
                bestNext = *(void**)best;
                memcpy(saved, node, 0x60);
                memcpy(node, best, 0x60);
                memcpy(best, saved, 0x60);
                *(void**)node = nodeNext;
                *(void**)best = bestNext;
            }
        }
        node = next;
        count++;
    }
}

void fn_80033794(void* particles) {
    void** node = particles;

    if (node == NULL) {
        return;
    }
    while (*node != NULL) {
        node = *node;
    }
    *node = lbl_803CBC74;
    lbl_803CBC74 = particles;
}

void* fn_800337CC(void* buf, int count, int arg2) {
    u8* node;
    u8* lastTaken = NULL;
    s32 taken = 0;
    s32 remaining = count;

    if (buf == NULL) {
        return NULL;
    }
    node = (u8*)lbl_803CBC74;
    while (node != NULL && remaining != 0) {
        lastTaken = node;
        node = *(u8**)node;
        taken++;
        remaining--;
    }
    if (arg2 != 0 && remaining != 0) {
        return NULL;
    }
    *(u16*)((u8*)buf + 0x14) = (*(u16*)((u8*)buf + 0x14) & 0xF000) | (taken & 0xFFF);
    if (taken != 0) {
        *(void**)((u8*)buf + 0xC) = lbl_803CBC74;
        lbl_803CBC74 = node;
        if (lastTaken != NULL) {
            *(void**)lastTaken = NULL;
        }
    } else {
        *(void**)((u8*)buf + 0xC) = NULL;
    }
    return buf;
}

void pitchingMachinePitching(u8 arg0) {
    u8* node = *(u8**)(lbl_803CBC84 + 0x4);
    u8* next;
    u8* prev;
    u8* succ;
    u8* tail;

    while (node != NULL) {
        next = *(u8**)(node + 0x4);
        if ((node[0x17] & 0x7F) == arg0 && *(void**)(node + 0x8) != NULL) {
            prev = *(u8**)node;
            succ = *(u8**)(node + 0x4);
            if (prev != NULL) {
                *(void**)(prev + 0x4) = succ;
            }
            if (succ != NULL) {
                *(void**)succ = prev;
            }
            *(void**)(node + 0x8) = NULL;

            tail = *(u8**)(node + 0xC);
            if (tail != NULL) {
                while (*(void**)tail != NULL) {
                    tail = *(u8**)tail;
                }
                *(void**)tail = lbl_803CBC74;
                lbl_803CBC74 = *(void**)(node + 0xC);
            }
            *(void**)node = NULL;
            *(void**)(node + 0x4) = lbl_803CBC80;
            lbl_803CBC80 = node;
        }
        node = next;
    }
}

BOOL fn_80033928(u8 id) {
    u8* node = *(u8**)(lbl_803CBC84 + 0x4);

    while (node != NULL) {
        if ((node[0x17] & 0x7F) == id) {
            return TRUE;
        }
        node = *(u8**)(node + 0x4);
    }
    return FALSE;
}

void fn_80033964(void* effect) {
    u8* node = effect;
    u8* prev;
    u8* succ;
    u8* sub;
    u8* tail;

    if (*(void**)(node + 0x8) == NULL) {
        return;
    }
    prev = *(u8**)node;
    succ = *(u8**)(node + 0x4);
    if (prev != NULL) {
        *(void**)(prev + 0x4) = succ;
    }
    if (succ != NULL) {
        *(void**)succ = prev;
    }
    *(void**)(node + 0x8) = NULL;

    sub = *(u8**)(node + 0xC);
    tail = sub;
    while (tail != NULL && *(void**)tail != NULL) {
        tail = *(u8**)tail;
    }
    if (tail != NULL) {
        *(void**)tail = lbl_803CBC74;
        lbl_803CBC74 = sub;
    }
    *(void**)node = NULL;
    *(void**)(node + 0x4) = lbl_803CBC80;
    lbl_803CBC80 = node;
}

void* fn_800339F0(int arg0, u8 arg1) {
    u8* node = (u8*)arg0;

    if (node == NULL) {
        node = lbl_803CBC84;
    }
    node = *(u8**)(node + 0x4);
    while (node != NULL) {
        if ((node[0x17] & 0x7F) == arg1) {
            return node;
        }
        node = *(u8**)(node + 0x4);
    }
    return NULL;
}

void* allocParticleEffect(void* func, int arg1, int arg2, int arg3, int arg4, u8 arg5) {
    u8* group = (u8*)lbl_803CBC80;
    u8* list = (u8*)lbl_803CBC74;
    u8* lastTaken = NULL;
    u8* prev;
    s32 taken = 0;
    s32 remaining = arg3;

    if (group == NULL) {
        return NULL;
    }
    while (list != NULL && remaining != 0) {
        lastTaken = list;
        list = *(u8**)list;
        taken++;
        remaining--;
    }
    if (arg4 != 0 && remaining != 0) {
        return NULL;
    }
    *(u16*)(group + 0x14) = (*(u16*)(group + 0x14) & 0xF000) | (taken & 0xFFF);
    if (taken != 0) {
        *(void**)(group + 0xC) = lbl_803CBC74;
        lbl_803CBC74 = list;
        if (lastTaken != NULL) {
            *(void**)lastTaken = NULL;
        }
    } else {
        *(void**)(group + 0xC) = NULL;
    }

    lbl_803CBC80 = *(void**)(group + 0x4);
    *(void**)(group + 0x8) = func;
    group[0x16] = arg1;
    group[0x17] = (group[0x17] & ~0x7F) | (arg5 & 0x7F);
    group[0x17] |= 0x80;
    group[0x14] = (group[0x14] & ~0xF0) | ((arg2 & 0xF) << 4);
    *(void**)(group + 0x4) = NULL;
    *(void**)(group + 0x0) = NULL;

    prev = (u8*)&lbl_803CBC84;
    while (1) {
        u8* succ = *(u8**)(prev + 0x4);

        if (succ == NULL || succ[0x16] >= group[0x16]) {
            break;
        }
        prev = succ;
    }
    {
        u8* succ = *(u8**)(prev + 0x4);

        *(void**)(group + 0x4) = succ;
        if (succ != NULL) {
            *(void**)succ = group;
        }
        *(void**)group = prev;
        *(void**)(prev + 0x4) = group;
    }
    return group;
}

void fn_80033B58(u8* base, s32 idx, s32 wrapS, s32 wrapT) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    u8* tex;

    if (base == NULL) {
        GXSetTevOrder(0, 0, 0, 4);
        return;
    }
    GXSetTevOrder(0, 0, 1, 4);
    tex = base + (*(u16*)(base + idx * 0x20 + 0x20)) * 0x20 + 0x4;
    if (*(void**)(tex + 0x4) != NULL) {
        GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), wrapS, wrapT, 0, 0);
        GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
        GXLoadTlut(&tlutObj, 0);
    } else {
        GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), wrapS, wrapT, 0);
    }
    GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
    GXLoadTexObj(&texObj, 1);
}

void fn_80033CC8(u8* item, u8* base) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    u8 texIdx = item[0x4D];
    u8* tex;
    s32 k;
    s32 n;
    s32 j;

    if (base == NULL) {
        GXSetTevOrder(0, 0, 0, 4);
    } else {
        GXSetTevOrder(0, 0, 1, 4);
        tex = base + (*(u16*)(base + texIdx * 0x20 + 0x20)) * 0x20 + 0x4;
        if (*(void**)(tex + 0x4) != NULL) {
            GXInitTexObjCI(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0, 0);
            GXInitTlutObj(&tlutObj, *(void**)(tex + 0x4), *(u8*)(tex + 0x1A), *(u16*)(tex + 0x18));
            GXLoadTlut(&tlutObj, 0);
        } else {
            GXInitTexObj(&texObj, *(void**)tex, *(u16*)(tex + 0xA), *(u16*)(tex + 0x8), *(u8*)(tex + 0x17), 0, 0, 0);
        }
        GXInitTexObjLOD(&texObj, 1, 1, (f32)tex[0x15], (f32)tex[0x16], *(f32*)(tex + 0x10), 0, 0, 0);
        GXLoadTexObj(&texObj, 1);
    }

    GXBegin(0x80, 0, 4);
    k = 0;
    for (n = 0; n < 2; n++) {
        for (j = 0; j < 2; j++) {
            f32* corner = &lbl_80180010[n * 2 + j].x;
            u16* uv = (u16*)(lbl_800F7860 + (item[0x4E] + k) * 4);

            GXWGFifo.f32 = *(f32*)(item + 0x4) + corner[0];
            GXWGFifo.f32 = *(f32*)(item + 0x8) + corner[1];
            GXWGFifo.f32 = *(f32*)(item + 0xC) + corner[2];
            GXWGFifo.u32 = *(u32*)(item + 0x40);
            GXWGFifo.f32 = (f32)uv[0];
            GXWGFifo.f32 = (f32)uv[1];
            k++;
        }
    }
}

void setParticleXform(f32 scaleX, f32 scaleY, f32 rot) {
    Mtx xform;
    Mtx rotMtx;
    int i;

    lbl_80180010[0].x = 0.5f * -scaleX;
    lbl_80180010[0].y = 0.5f * -scaleY;
    lbl_80180010[0].z = 0.0f;
    lbl_80180010[1].x = 0.5f * scaleX;
    lbl_80180010[1].y = 0.5f * -scaleY;
    lbl_80180010[1].z = 0.0f;
    lbl_80180010[2].x = 0.5f * scaleX;
    lbl_80180010[2].y = 0.5f * scaleY;
    lbl_80180010[2].z = 0.0f;
    lbl_80180010[3].x = 0.5f * -scaleX;
    lbl_80180010[3].y = 0.5f * scaleY;
    lbl_80180010[3].z = 0.0f;
    PSMTXRotRad(rotMtx, 'z', MTXDegToRad(rot));
    PSMTXConcat(graphicRelatedStructMaybe.mtx, rotMtx, xform);
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(xform, &lbl_80180010[i], &lbl_80180010[i]);
    }
}

void fn_8003403C(f32 x, f32 y) {
    f32 k = lbl_803CC5F0;
    s32 i;

    lbl_80180010[0].x = k * -x;
    lbl_80180010[0].y = k * -y;
    lbl_80180010[0].z = lbl_803CC5F4;
    lbl_80180010[1].x = k * x;
    lbl_80180010[1].y = k * -y;
    lbl_80180010[1].z = lbl_803CC5F4;
    lbl_80180010[2].x = k * x;
    lbl_80180010[2].y = k * y;
    lbl_80180010[2].z = lbl_803CC5F4;
    lbl_80180010[3].x = k * -x;
    lbl_80180010[3].y = k * y;
    lbl_80180010[3].z = lbl_803CC5F4;
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(graphicRelatedStructMaybe.mtx, &lbl_80180010[i], &lbl_80180010[i]);
    }
}

void fn_800340F4(Mtx dest) {
    PSMTXCopy(graphicRelatedStructMaybe.mtx, dest);
}

void fn_80034120(Mtx dest) {
    PSMTXCopy(lbl_8017FFE0, dest);
}

void fn_8003414C(Mtx src) {
    u8* base = lbl_8017EC00;
    f32* quad = (f32*)(base + 0x1410);
    s32 i;

    PSMTXCopy(src, (void*)(base + 0x13E0));
    fn_800118AC(src, base + 0x13A8);
    PSMTXCopy((void*)(base + 0x13A8), (void*)(base + 0x1378));
    ((f32*)(base + 0x1378))[3] = lbl_803CC5F4;
    ((f32*)(base + 0x1378))[7] = lbl_803CC5F4;
    ((f32*)(base + 0x1378))[11] = lbl_803CC5F4;

    quad[0] = lbl_803CC650;
    quad[1] = lbl_803CC650;
    quad[2] = lbl_803CC5F4;
    quad[3] = lbl_803CC5F0;
    quad[4] = lbl_803CC650;
    quad[5] = lbl_803CC5F4;
    quad[6] = lbl_803CC5F0;
    quad[7] = lbl_803CC5F0;
    quad[8] = lbl_803CC5F4;
    quad[9] = lbl_803CC650;
    quad[10] = lbl_803CC5F0;
    quad[11] = lbl_803CC5F4;

    for (i = 0; i < 4; i++) {
        PSMTXMultVec((void*)(base + 0x1378), (Vec*)&quad[i * 3], (Vec*)&quad[i * 3]);
    }
}

void minigamesSetSomePointers(void) {
    s32 i;

    lbl_803CBC78 = 1;
    memset(startOfMinigamePtrStruct, 0, 0x78000);
    for (i = 0; i < 0x13FF; i++) {
        *(u8**)(startOfMinigamePtrStruct + i * 0x60) = startOfMinigamePtrStruct + (i + 1) * 0x60;
    }
    lbl_803CBC74 = startOfMinigamePtrStruct;
    lbl_803CBC78 = 0;
    *(void**)lbl_803CBC84 = NULL;
    *(void**)(lbl_803CBC84 + 0x4) = NULL;
    memset(lbl_801F8040, 0, 0x600);
    for (i = 0; i < 0xF; i++) {
        *(u8**)(lbl_801F8040 + i * 0x60 + 0x4) = lbl_801F8040 + (i + 1) * 0x60;
    }
    lbl_803CBC80 = lbl_801F8040;
    for (i = 0; i <= 0x400; i++) {
        maybeCosineArray[i] = (f32)cos(pi * (double)i / lbl_803CC6E0);
    }
    lbl_803CBC7C = 0;
}

void minigamesGXStuff(void) {
    u8* node;
    u8* next;
    u8* prev;
    u8* sub;
    u8* tail;
    BOOL result;
    GXTexObj texObj;

    if (lbl_803CBC78 != 0) {
        lbl_803CBC78 = 0;
        node = *(u8**)(lbl_803CBC84 + 0x4);
        while (node != NULL) {
            next = *(u8**)(node + 0x4);
            if (*(void**)(node + 0x8) != NULL) {
                prev = *(u8**)(node + 0x0);
                if (prev != NULL) {
                    *(u8**)(prev + 0x4) = next;
                }
                if (next != NULL) {
                    *(u8**)(next + 0x0) = prev;
                }
                *(void**)(node + 0x8) = NULL;
                sub = *(u8**)(node + 0xC);
                tail = sub;
                if (tail != NULL) {
                    while (*(u8**)tail != NULL) {
                        tail = *(u8**)tail;
                    }
                    *(void**)tail = lbl_803CBC74;
                    lbl_803CBC74 = sub;
                }
                *(void**)(node + 0x0) = NULL;
                *(void**)(node + 0x4) = lbl_803CBC80;
                lbl_803CBC80 = node;
            }
            node = next;
        }
        *(void**)(lbl_803CBC84 + 0x4) = NULL;
        return;
    }

    node = *(u8**)(lbl_803CBC84 + 0x4);
    if (node == NULL) {
        return;
    }

    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetCullMode(0);
    GXInitTexObj(&texObj, lbl_800F7840, 4, 4, 4, 0, 0, 0);
    GXInitTexObjLOD(&texObj, 1, 1, lbl_803CC5F4, lbl_803CC5F4, lbl_803CC5F4, 0, 0, 0);
    GXLoadTexObj(&texObj, 0);
    GXSetTevColorIn(0, 0xF, 0xA, 8, 0xF);
    GXSetTevAlphaIn(0, 7, 5, 4, 7);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetProjection((void*)returnFloatFromModeIndex(returnsCurrentMode()), 0);
    GXLoadPosMtxImm(lbl_8017FFE0, 0);
    GXSetCurrentMtx(0);
    SetFogNone();

    node = *(u8**)(lbl_803CBC84 + 0x4);
    while (node != NULL) {
        result = FALSE;
        if (*(void**)(node + 0x8) != NULL) {
            result = ((BOOL (*)(u8*))*(void**)(node + 0x8))(node);
        }
        next = *(u8**)(node + 0x4);
        if (result != FALSE && *(void**)(node + 0x8) != NULL) {
            prev = *(u8**)(node + 0x0);
            if (prev != NULL) {
                *(u8**)(prev + 0x4) = next;
            }
            if (next != NULL) {
                *(u8**)(next + 0x0) = prev;
            }
            *(void**)(node + 0x8) = NULL;
            sub = *(u8**)(node + 0xC);
            tail = sub;
            if (tail != NULL) {
                while (*(u8**)tail != NULL) {
                    tail = *(u8**)tail;
                }
                *(void**)tail = lbl_803CBC74;
                lbl_803CBC74 = sub;
            }
            *(void**)(node + 0x0) = NULL;
            *(void**)(node + 0x4) = lbl_803CBC80;
            lbl_803CBC80 = node;
        }
        node = next;
    }
}

void minigamesSetSomePointers2(void) {
    s32 i;

    memset(startOfMinigamePtrStruct, 0, 0x78000);
    for (i = 0; i < 0x13FF; i++) {
        *(u8**)(startOfMinigamePtrStruct + i * 0x60) = startOfMinigamePtrStruct + (i + 1) * 0x60;
    }
    lbl_803CBC74 = startOfMinigamePtrStruct;
    lbl_803CBC78 = 0;
    *(void**)lbl_803CBC84 = NULL;
    *(void**)(lbl_803CBC84 + 0x4) = NULL;
    memset(lbl_801F8040, 0, 0x600);
    for (i = 0; i < 0xF; i++) {
        *(u8**)(lbl_801F8040 + i * 0x60 + 0x4) = lbl_801F8040 + (i + 1) * 0x60;
    }
    lbl_803CBC80 = lbl_801F8040;
    for (i = 0; i <= 0x400; i++) {
        maybeCosineArray[i] = (f32)cos(pi * (double)i / lbl_803CC6E0);
    }
    lbl_803CBC7C = 0;
}
