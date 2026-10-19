#include "menus/rep_0568.h"
#include "header_rep_data.h"

#include "Unknown/File_0x800b0a14.h"
#include "static/UnknownHomes_Static.h"
#include "menus/yd_step.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800bd8c4.h"
#include "C3/actor.h"
#include "C3/actor/actorAnim.h"
#include "C3/actor/act.h"
#include "Dolphin/gx.h"
#include "Unknown/File_0x800bda94.h"

extern u8 hugeAnimStruct[0x3154];
extern u8 lbl_2_bss_100B8[0x54];
extern DrawingSceneStruct *lbl_2_bss_1224;
extern menuControlStruct *menuControlVariables;
extern int menuCursors[0x16];
extern u8 challengeCaptainCharIDArray[0xC];
extern u8 superstarUnlocked[0x130];
extern u8 lbl_2_bss_100B4[2];
extern u8 lbl_2_data_241C[0x360];
extern u8 lbl_803C6CF8[0x800];
extern u8 gameSetUpStep[0x64];
extern u8 lbl_2_data_2794[0x3C8];
extern u8 inMemRoster[];
void *getAnimObjectActor(void *obj);
void fn_80014204(s32 count);
u32 fn_80023AA4(void);
void initActorArray(int count);
void actorRelated(void *effect, int arg1, int arg2);
extern void *lbl_2_data_2780;
void *ARAMTransfer(void *file, s32 arg1, s32 arg2, s32 arg3);
void fn_2_14BB8(int port, int state);
extern void *lbl_2_bss_122C;
extern u8 lbl_2_bss_101AC[0x190];
void *_OSAllocFromHeap(s32 alignment, s32 size);
extern void *memset(void *dest, int val, size_t count);
extern void setLITLightPtr(void *light);

// .text:0x00016A98 size:0x248 mapped:0x80655B2C
void fn_2_16A98(s32 slot, s32 mode, u8 flagA, u8 valB, s16 frame, s32 unused, u8 speedFlag) {
    u8 *obj = ((u8 **)(hugeAnimStruct + 0x2C50))[slot];
    u8 *slotObj;
    u8 *actor;
    f32 blendTime = 0.0f;
    s32 phase;
    s32 idx;
    u8 value;
    BOOL runTail = TRUE;

    if (obj != NULL) {
        actor = getAnimObjectActor(obj);
        if (speedFlag != 0) {
            blendTime = 1.0f / (f32)speedFlag;
        }
        slotObj = ((u8 **)(hugeAnimStruct + 0x2C50))[slot];
        fn_800B2B54((UnkB2B4C *)*(void **)obj,
                    slotObj != NULL ? *(u16 *)(slotObj + 0x16A) : 0xFFFF,
                    obj[0x26C] == 0 ? 0xD : 1);

        if (mode < 3) {
            phase = 5;
            idx = mode;
        }
        value = lbl_2_data_2794[idx];
        if (*(u8 **)(obj + 0x2C) != NULL) {
            actorRelated(*(u8 **)(obj + 0x2C) + 4, 5, value);
        }
        if (*(u8 **)(obj + 0x30) != NULL && (*(u8 **)(obj + 0x30))[0xCC] != 0) {
            actorRelated(*(u8 **)(obj + 0x30) + 0x68, 5, value);
            actorRelated(*(u8 **)(obj + 0x30) + 4, 5, value);
        }

        if (slot < lbl_2_bss_100B8[0x2D]) {
            u8 *entry = *(u8 **)(obj + phase * 4 + 0x10);
            if (entry != NULL) {
                if (idx >= *(u16 *)(entry + 0xA)) {
                    runTail = FALSE;
                } else {
                    *(u8 **)(actor + 4) = entry;
                    *(s16 *)(actor + 0xE) = idx;
                    *(f32 *)(actor + 0x5C) = 0.0f;
                    actor[0x58] = TRUE;
                    actor[0x59] = TRUE;
                    actor[0x5A] = TRUE;
                    *(f32 *)(actor + 0x60) = blendTime;
                }
            }
        }

        if (runTail) {
            actor[0x5B] = flagA != 0 ? 3 : 2;
            *(f32 *)(actor + 0x5C) = (f32)frame * *(f32 *)(obj + 0x4C);
            actor[0x59] = TRUE;
            obj[0x268] = valB;
        }
    }
}

// .text:0x00016CE0 size:0x58 mapped:0x80655D74
void fn_2_16CE0(void) {
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        void *obj = ((void **)(hugeAnimStruct + 0x2C50))[i];
        if (obj != NULL && *(s16 *)((u8 *)obj + 0x62) == 0x6B) {
            lbl_2_bss_100B8[0x40 + i] = TRUE;
        }
    }
}

// .text:0x00016D38 size:0x70 mapped:0x80655DCC
void fn_2_16D38(void) {
    s32 i;
    u8 *slot = hugeAnimStruct;
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        memset(*(void **)(slot + 0xC0C), 0, 0x5C);
        slot += 0x27C;
    }
}

// .text:0x00016DA8 size:0x164 mapped:0x80655E3C
void fn_2_16DA8(void) {
    s32 i;
    s32 count = lbl_2_bss_100B8[0x2D];

    *(s16 *)(hugeAnimStruct + 0x3078) = 0;
    for (i = 0; i < count; i++) {
        ((void **)(hugeAnimStruct + 0x2C50))[i] = hugeAnimStruct + i * 0x27C + 0xC04;
    }
    for (i = 3; i > 0; i--) {
        lbl_2_bss_100B8[0x42 + i] = 0;
    }
    if (menuControlVariables->previousScreen == 5 || g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        lbl_2_bss_100B8[0x46] = TRUE;
        lbl_2_bss_100B8[0x47] = FALSE;
    } else {
        lbl_2_bss_100B8[0x46] = TRUE;
        lbl_2_bss_100B8[0x47] = TRUE;
    }
}

// .text:0x00016F0C size:0x6C mapped:0x80655FA0
void fn_2_16F0C(u8 slot) {
    u8 *slotData = hugeAnimStruct + slot * 0x27C;
    if ((s8)hugeAnimStruct[slot * 0xD4 + 0x210] == -1) {
        hugeAnimStruct[slot * 0xD4 + 0x20F] = slotData[0xE56];
        hugeAnimStruct[slot * 0xD4 + 0x211] = hugeAnimStruct[slot * 0xD4 + 0x210];
        hugeAnimStruct[slot * 0xD4 + 0x210] = slotData[0xE58];
        hugeAnimStruct[slot * 0xD4 + 0x20D] = slotData[0xE69];
    }
    *(u8 **)(slotData + 0xC34) = hugeAnimStruct + slot * 0xD4 + 0x140;
}

// .text:0x00016F78 size:0x6D0 mapped:0x8065600C
void fn_2_16F78(u8 idx) {
    return;
}

// .text:0x00017648 size:0x470 mapped:0x806566DC
void fn_2_17648(void) {
    return;
}

// .text:0x00017AB8 size:0x1D0 mapped:0x80656B4C
void fn_2_17AB8(void) {
    u32 *header = (u32 *)lbl_2_data_2780;
    u32 stride = ((header[1] & 0x0FFFFFFF) + 0x1F) & ~0x1F;
    s32 count = lbl_2_bss_100B8[0x2D];
    u8 *buffer = _OSAllocFromHeap(32, stride * count);
    s32 i;

    lbl_2_bss_122C = buffer;
    for (i = 0; i < count; i++) {
        u8 *entry = lbl_2_bss_101AC + i * 0x64;
        *(u8 **)entry = buffer + i * stride;
        entry[0x60] = -1;
        entry[0x61] = -1;
    }
}

// .text:0x00017C88 size:0x250 mapped:0x80656D1C
void fn_2_17C88(void) {
    u32 maxSize = 0;
    u32 stride;
    s32 charId;
    s32 i;
    s32 count;
    u8 *buffer;

    for (charId = 0; charId < 0x35; charId++) {
        s16 index = *(s16 *)((u8 *)&Static_Stats_Tables + charId * 0xA0 + 0x24);
        u32 size = *(u32 *)(lbl_2_data_241C + index * 0x10 + 4) & 0x0FFFFFFF;
        if (maxSize < size) {
            maxSize = size;
        }
    }

    stride = (maxSize + 0x1F) & ~0x1F;
    count = lbl_2_bss_100B8[0x2D];
    buffer = _OSAllocFromHeap(32, stride * count);
    *(u8 **)(hugeAnimStruct + 0x2C8C) = buffer;
    for (i = 0; i < count; i++) {
        *(u8 **)(hugeAnimStruct + i * 0x27C + 0xC0C) = buffer + i * stride;
    }
}

// .text:0x00017ED8 size:0x270 mapped:0x80656F6C
void fn_2_17ED8(void) {
    u32 maxSize = 0;
    u32 stride;
    s32 charId;
    s32 i;
    s32 count;
    u8 *buffer;

    for (charId = 0; charId < 0x35; charId++) {
        s16 index = *(s16 *)((u8 *)&Static_Stats_Tables + charId * 0xA0 + 0x24);
        u32 size = *(u32 *)(lbl_2_data_241C + index * 0x10 + 4) & 0x0FFFFFFF;
        if (maxSize < size) {
            maxSize = size;
        }
    }

    stride = (maxSize + 0x1F) & ~0x1F;
    count = lbl_2_bss_100B8[0x2D];
    buffer = _OSAllocFromHeap(32, stride * count);
    *(u8 **)(hugeAnimStruct + 0x2C8C) = buffer;
    for (i = 0; i < count; i++) {
        *(u8 **)(hugeAnimStruct + i * 0x27C + 0xC0C) = buffer + i * stride;
    }

    fn_80014204(lbl_2_bss_100B8[0x2D]);
    *(u32 *)(hugeAnimStruct + 0x13C) = fn_80023AA4();
    initActorArray(4);
}

// .text:0x00018148 size:0x250 mapped:0x806571DC
void fn_2_18148(DrawingSceneStruct *item) {
    u8 *d = (u8 *)item;
    s32 idx;

    if (d[0x21] == 0) {
        idx = d[0x1E];
        *(u8 **)(d + 0x14) = hugeAnimStruct + idx * 0x27C + 0xC04;
        (*(u8 **)(d + 0x14))[0x252] = d[0x18 + idx];
        d[0x20] = lbl_2_bss_100B8[0x46 + idx];
        hugeAnimStruct[idx * 0x27C + 0xE61] = FALSE;
        *(s16 *)(*(u8 **)(d + 0x14) + 0x68) = -1;
        lbl_2_bss_100B4[1] = TRUE;
        d[0x21]++;
    } else if (d[0x21] == 1) {
        idx = d[0x1E];
        ARAMTransfer(lbl_2_data_241C + (s8)d[0x18 + idx] * 0x10,
                     ((u32 *)*(u8 **)(d + 0x14))[2], 0, 0);
        d[0x21]++;
    } else if (d[0x21] == 2) {
        if (lbl_803C6CF8[0x715] == 1) {
            fn_2_16F78(d[0x1E]);
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && gameSetUpStep[0x59] == 0 &&
                d[0x1E] == 1) {
                hugeAnimStruct[1 * 0x27C + 0xE61] = FALSE;
            } else {
                hugeAnimStruct[d[0x1E] * 0x27C + 0xE61] = d[0x20] != 0;
            }
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE ||
                g_d_GameSettings.p2_CPU_match_code != P2_CPU_CODE_1_PLAYER_GAME ||
                menuControlVariables->previousScreen == 5) {
                fn_2_14BB8(d[0x1E], TRUE);
            } else if (lbl_2_bss_100B8[0x10] != 0) {
                fn_2_14BB8(d[0x1E], d[0x1E] != 0);
            }
        }
        d[0x21] = 0;
        lbl_2_bss_100B4[1] = FALSE;
        lbl_2_bss_100B8[0x32] = TRUE;
        lbl_2_bss_100B8[0x18] = TRUE;
        lbl_2_bss_100B8[0x42 + d[0x1E]] = FALSE;
    }
}

// .text:0x00018398 size:0x2B8 mapped:0x8065742C
void fn_2_18398(void) {
    u8 *item = (u8 *)currentDrawingItem;
    u8 *bss = lbl_2_bss_100B8;
    s8 ring;
    s32 idx;

    if (item[0x1D] == 0) {
        ring = (s8)bss[1];
        if ((s8)bss[2 + ring] == -1) {
            bss[0x18] = FALSE;
            bss[0x1B] = TRUE;
            bss[0x1A] = FALSE;
            bss[0x32] = FALSE;
            lbl_2_bss_1224 = NULL;
            removeCurrentDrawingItem();
            return;
        }
        idx = bss[2 + ring];
        item[0x1E] = idx;
        bss[2 + ring] = -1;
        bss[1] = (ring + 1) % 10;
        bss[0x1A] = TRUE;
        bss[0x1B] = FALSE;
        bss[0x27 + idx] = idx;
        item[0x1D] = 1;
        *(s16 *)(item + 0x10) = 0;

        if (((u8 *)&Static_Stats_Tables)[0x4755] == 0) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                item[0x18 + idx] = challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6 + menuCursors[idx + 4]];
            } else {
                item[0x18 + idx] = mapCaptainCursorPositionToCharID[menuCursors[idx + 4]];
            }
            if (item[0x1E] == 2) {
                item[0x1E] = 0;
            }
        } else if (((u8 *)&Static_Stats_Tables)[0x4755] == 1) {
            if (idx < 2) {
                item[0x18 + idx] = (u8)*(s16 *)(inMemRoster + idx * 0x5A0 +
                                                (menuCursors[idx + 12] - (idx * 11 + 2)) * 0xA0 + 0x24);
            } else if (idx < 4) {
                item[0x18 + idx] = menuCursors[idx + 6];
            }
        }
    } else if (item[0x1D] != 1) {
        return;
    }

    fn_2_18148(currentDrawingItem);
    if (lbl_2_bss_100B4[0] != 0 && lbl_2_bss_100B4[1] == 0) {
        lbl_2_bss_1224 = NULL;
        bss[0x18] = FALSE;
        bss[0x1B] = TRUE;
        bss[0x1A] = FALSE;
        bss[0x32] = FALSE;
        item[0x1D] = 0;
        removeCurrentDrawingItem();
    } else if (bss[0x18] != 0) {
        bss[0x18] = FALSE;
        bss[0x1A] = FALSE;
        item[0x1D] = 0;
    }
}

// .text:0x00018650 size:0xF8 mapped:0x806576E4
BOOL fn_2_18650(s32 slot) {
    s32 newHead = ((s8)lbl_2_bss_100B8[0] + 1) % 10;
    if (newHead == (s8)lbl_2_bss_100B8[1]) {
        return FALSE;
    }
    if (lbl_2_bss_1224 == NULL) {
        lbl_2_bss_1224 = insertGraphicDrawingFunction(fn_2_18398, 0xFFFF);
        if (lbl_2_bss_1224 == NULL) {
            return FALSE;
        }
        ((u8 *)lbl_2_bss_1224)[0x1C] = 0;
        ((u8 *)lbl_2_bss_1224)[0x1D] = 0;
    }
    lbl_2_bss_100B8[(s8)lbl_2_bss_100B8[0] + 2] = slot;
    lbl_2_bss_100B8[0] = newHead;
    lbl_2_bss_100B8[slot + 0x42] = TRUE;
    return TRUE;
}

// .text:0x00018748 size:0x1A4 mapped:0x806577DC
void fn_2_18748(void) {
    u8 *item = (u8 *)currentDrawingItem;
    s32 i;

    if (item[0x1D] == 0) {
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                item[0x18 + i] = challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6 + menuCursors[item[0x1E] + 4]];
            } else {
                item[0x18 + i] = mapCaptainCursorPositionToCharID[menuCursors[item[0x1E] + 4]];
            }
            if (item[0x1E] == 2) {
                item[0x1E] = 0;
            }
        }
        *(s16 *)(item + 0x10) = 0;
        item[0x21] = 0;
        item[0x1D]++;
    } else if (item[0x1D] != 1) {
        return;
    }

    fn_2_18148(currentDrawingItem);
    if (lbl_2_bss_100B8[0x18] != 0) {
        lbl_2_bss_100B8[0x18] = 0;
        lbl_2_bss_100B8[0x32] = 0;
        item[0x21] = 0;
        *(s16 *)(item + 0x10) = 0;
        item[0x1E]++;
        if (item[0x1E] < lbl_2_bss_100B8[0x2D]) {
            item[0x1D] = 0;
        } else {
            item[0x1E] = 0;
            item[0x1D] = 0;
            lbl_2_bss_100B8[0x19] = TRUE;
            removeCurrentDrawingItem();
        }
    } else if (lbl_2_bss_100B4[0] != 0) {
        item[0x1E] = 0;
        item[0x1D] = 0;
        removeCurrentDrawingItem();
    }
}

// .text:0x000188EC size:0x6D0 mapped:0x80657980
void fn_2_188EC(void) {
    return;
}

// .text:0x00018FBC size:0xFC mapped:0x80658050
void captainSelectLoadScreen(void) {
    DrawingSceneStruct *drawing = insertGraphicDrawingFunction(fn_2_188EC, 0x6000);
    s32 i;

    lbl_2_bss_100B8[0x19] = 0;
    lbl_2_bss_100B8[0x1B] = TRUE;
    if (((u8 *)&Static_Stats_Tables)[0x4701] == 0) {
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            lbl_2_bss_100B8[0x27 + i] = -1;
        }
    } else {
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            lbl_2_bss_100B8[0x14 + i] = 0;
        }
    }
    ((u8 *)drawing)[0x1C] = 0;
    lbl_2_bss_100B8[0] = 0;
    lbl_2_bss_100B8[1] = 0;
    for (i = 2; i < 12; i++) {
        lbl_2_bss_100B8[i] = -1;
    }
}

// .text:0x000190B8 size:0x24 mapped:0x8065814C
void fn_2_190B8(void *obj) {
    setLITLightPtr(*(void **)((u8 *)obj + 0x70));
}

// .text:0x000190DC size:0x148 mapped:0x80658170
void fn_2_190DC(ActorObjectTable *table) {
    s32 i;
    for (i = 0; i < table->count; i++) {
        if (*(u8 **)(hugeAnimStruct + 0x2D94) + i * 0x28 != NULL) {
            ActorObjectEntry *entry = &table->entries[i];
            if (entry->actor != NULL) {
                if (entry->animPending) {
                    ACTSetAnimation(entry->actor, entry->anim, NULL, entry->seqNum, 0.0f, entry->blendTime);
                }
                if (entry->framePending) {
                    setActorAnimFrame(entry->actor, entry->frame);
                }
                if (entry->speedPending) {
                    ACTSetSpeed(entry->actor, entry->speed);
                }
                if (entry->boneParam & 2) {
                    updateBoneParam(entry->actor, entry->boneParam & 1);
                }
                Set_FUN_800b2b6c((UnkB2B4C *)entry->actor, entry->unk68);
                if (entry->applyControl) {
                    fn_800BDA24(entry);
                }
                ((u8 *)entry->actor)[0x98] = TRUE;
                entry->animPending = FALSE;
                entry->framePending = FALSE;
                entry->speedPending = FALSE;
                entry->boneParam &= 1;
            }
        }
    }
}

// .text:0x00019224 size:0x158 mapped:0x806582B8
void fn_2_19224(ActorObjectTable *table) {
    s32 i;
    for (i = 0; i < table->count; i++) {
        u8 *obj = ((u8 **)(hugeAnimStruct + 0x2C50))[i];
        if (obj != NULL && obj[0x25D] != 0) {
            ActorObjectEntry *entry = &table->entries[i];
            if (entry->actor != NULL) {
                if (entry->animPending) {
                    ACTSetAnimation(entry->actor, entry->anim, NULL, entry->seqNum, 0.0f, entry->blendTime);
                }
                if (entry->framePending) {
                    setActorAnimFrame(entry->actor, entry->frame);
                }
                if (entry->speedPending) {
                    ACTSetSpeed(entry->actor, entry->speed);
                }
                if (entry->boneParam & 2) {
                    updateBoneParam(entry->actor, entry->boneParam & 1);
                }
                Set_FUN_800b2b6c((UnkB2B4C *)entry->actor, entry->unk68);
                if (entry->applyControl) {
                    fn_800BDA24(entry);
                }
                ((u8 *)entry->actor)[0x98] = TRUE;
                entry->animPending = FALSE;
                entry->framePending = FALSE;
                entry->speedPending = FALSE;
                entry->boneParam &= 1;
            }
        }
    }
}

// .text:0x0001937C size:0x140 mapped:0x80658410
void fn_2_1937C(ActorObjectTable *table, Mtx m) {
    Mtx44 projection;
    s32 i;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < table->count; i++) {
        u8 *obj = ((u8 **)(hugeAnimStruct + 0x2C50))[i];
        ActorObjectEntry *entry = &table->entries[i];
        if (obj != NULL && entry->actor != NULL && entry->applyControl) {
            f32 width = *(f32 *)(obj + 0x34);
            f32 height = *(f32 *)(obj + 0x38);
            C_MTXFrustum(projection,
                         -0.175f + height / 1280.0f,
                         0.175f + height / 1280.0f,
                         0.25f + width / 1280.0f,
                         -0.25f + width / 1280.0f,
                         1.0f,
                         512.0f);
            GXSetProjection(projection, GX_PERSPECTIVE);
            sknRelated(entry, m);
        }
    }
}
