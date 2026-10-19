#include "Unknown/File_0x80013680.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x80021ca4.h"
#include "Unknown/File_0x80025c58.h"
#include "Unknown/File_0x80025ddc.h"
#include "C3/actor/act.h"
#include "C3/geoPalette/geoPalette.h"

extern void fn_800238E0(void* entries, s32 slot, s32 slot2, void* layout);

extern u8 lbl_803CBBFB;
extern u8 lbl_803CBBFC;
extern u8 lbl_803CBBFD;
extern u32 lbl_803CBC00;
extern u8 lbl_803CBC0C;
extern u8* lbl_803CBC1C;
extern u8* lbl_803CBC20;
extern u8 lbl_803CB7C4[4];
extern u8 handAttachBoneIDs[8];
extern s16 lbl_800EEAAC[0x36];
extern u8 hugeAnimStruct[0x3154];
extern u8 lbl_803716B8[0x578];

#define FIELD_U8(p, off) (*(u8*)((u8*)(p) + (off)))
#define FIELD_S8(p, off) (*(s8*)((u8*)(p) + (off)))
#define FIELD_U16(p, off) (*(u16*)((u8*)(p) + (off)))
#define FIELD_U32(p, off) (*(u32*)((u8*)(p) + (off)))
#define FIELD_PTR(p, off) (*(u8**)((u8*)(p) + (off)))

#define RECORD_COUNT 13
#define RECORD_STRIDE 0xD4
#define RECORD(i) (hugeAnimStruct + (i) * RECORD_STRIDE)
#define OBJECT_TABLE_OFFSET 0x2C50
#define ENTRY_TABLE_OFFSET 0x13C
#define ENTRY_STRIDE 0x90
#define NO_BONE 0xFFFF

static u8* getObject(s32 slot) {
    return ((u8**)(hugeAnimStruct + OBJECT_TABLE_OFFSET))[slot];
}

static u16 getHandAttachBone(u8* obj, s32 which) {
    if (obj == NULL) {
        return NO_BONE;
    }
    return FIELD_U16(obj, 0x162 + handAttachBoneIDs[which] * 2);
}

static void clearBoneSlot(u8* obj, u16 bone, s32 subIndexOffset) {
    s16 val = lbl_800EEAAC[FIELD_S8(obj, 0x252)];
    u8* sub;
    u8* list;
    u8* bonePtr;
    u8* entry;
    u8* data;
    u8* arr;
    u32 count;
    u32 i;

    if (val < 0) {
        return;
    }
    sub = FIELD_PTR(obj, 0x30);
    if (sub == NULL) {
        return;
    }
    list = FIELD_PTR(FIELD_PTR(obj, 0), 0x18);
    bonePtr = ((u8**)list)[bone];
    entry = FIELD_PTR(hugeAnimStruct, ENTRY_TABLE_OFFSET) + FIELD_U8(sub, subIndexOffset) * ENTRY_STRIDE;
    data = FIELD_PTR(entry, 0x34);
    if (data == NULL) {
        return;
    }
    count = FIELD_U16(data, 0x6);
    arr = FIELD_PTR(data, 0x18);
    for (i = count; i != 0; i--) {
        u8* item = ((u8**)arr)[i - 1];
        u32 v = FIELD_U32(item, 0x14);
        if (v != 0) {
            FIELD_U32(bonePtr, 0x14) = v;
            return;
        }
    }
}

static BOOL attachHandModelTail(void) {
    u8* p;
    u8* h;
    u8* table;
    u8* entry;
    u8* a;
    u8* b;
    u8* f;
    u32 off;
    s32 idx;

    if (FIELD_U8(lbl_803716B8, 0x1E8) != 0) {
        return FALSE;
    }
    p = lbl_803CBC1C;
    lbl_803CBC0C = 0;
    h = FIELD_PTR(p, 0);
    for (off = 0; off < 0x10; off += 4) {
        u32 v = FIELD_U32(h, off);
        if (v != 0) {
            FIELD_U32(h, off) = (u32)h + v;
        }
    }

    idx = FIELD_U8(p, 0x60);
    table = FIELD_PTR(hugeAnimStruct, ENTRY_TABLE_OFFSET);
    entry = table + idx * ENTRY_STRIDE;
    a = ((u8**)h)[lbl_803CB7C4[0]];
    b = ((u8**)h)[lbl_803CB7C4[1]];
    f = entry + 0x34;

    LoadActorLayout(a);
    convertGeometryAndSknHeader(b, NULL);
    haveActLayoutPointToGeoHeader(a, b);
    UpdateTexturePalettePointers((UnkTexPalGeo*)b, (void*)lbl_803CBC00);
    fn_800238E0(table, idx, idx, a);
    if (FIELD_PTR(h, 0x8) != NULL) {
        adjustInternalPointers(((u8**)h)[lbl_803CB7C4[2]]);
        ACTActorRelated(((u8**)h)[lbl_803CB7C4[2]], f);
    }
    FIELD_PTR(p, 0x4) = ((u8**)h)[lbl_803CB7C4[3]];
    actRelated(((u8**)h)[lbl_803CB7C4[2]], p + 0x4);
    lbl_803CBC1C = NULL;
    return TRUE;
}

BOOL animateModelArmsGlovesBats(void* actorPtr) {
    u8* actor = actorPtr;
    s8 charSlot = FIELD_S8(actor, 0x252);
    s8 part = FIELD_S8(actor, 0x254);
    BOOL lowPart;
    BOOL flagsMatch;
    BOOL placed;
    u8 sel;
    s32 i;
    s32 k;
    u8* rec;

    if (lbl_803CBBFB == 0) {
        lbl_803CBBFB = 1;
        lbl_803CBC00 = FIELD_U32(FIELD_PTR(actor, 0x8), 0);

        for (i = 0; i < RECORD_COUNT; i++) {
            rec = RECORD(i);
            if (FIELD_S8(rec, 0x20F) != charSlot) {
                continue;
            }
            if (FIELD_U8(rec, 0x20D) != FIELD_U8(actor, 0x25A)) {
                continue;
            }
            if (FIELD_U8(rec, 0x20E) != FIELD_U8(actor, 0x25B)) {
                continue;
            }
            if (FIELD_S8(rec, 0x210) != -1) {
                continue;
            }
            if (FIELD_U32(rec, 0x208) != lbl_803CBC00) {
                continue;
            }
            if ((part >= 9) != (FIELD_S8(rec, 0x211) >= 9)) {
                continue;
            }

            FIELD_U8(rec, 0x210) = (u8)part;
            FIELD_PTR(actor, 0x30) = rec + 0x140;
            FIELD_U8(FIELD_PTR(actor, 0x30), 0xCC) = TRUE;
            {
                u8* obj = getObject(part);
                u16 bone = getHandAttachBone(obj, 0);
                if (bone != NO_BONE) {
                    clearBoneSlot(obj, bone, 0x60);
                }
                obj = getObject(part);
                bone = getHandAttachBone(obj, 1);
                if (bone != NO_BONE) {
                    clearBoneSlot(obj, bone, 0xC4);
                }
            }
            lbl_803CBBFD = 0;
            lbl_803CBBFC = 0;
            lbl_803CBBFB = 0;
            lbl_803CBC00 = 0;
            return TRUE;
        }

        if (lbl_803CBBFC == 0 && lbl_803CBBFD == 0) {
            for (i = 0; i < RECORD_COUNT; i++) {
                rec = RECORD(i);
                if (FIELD_S8(rec, 0x210) == part && part < 9) {
                    FIELD_S8(rec, 0x210) = -1;
                    break;
                }
            }

            placed = FALSE;
            for (i = 0; i < RECORD_COUNT; i++) {
                rec = RECORD(i);
                if (FIELD_S8(rec, 0x210) == -1) {
                    lbl_803CBC20 = rec + 0x140;
                    FIELD_U32(rec, 0x208) = lbl_803CBC00;
                    FIELD_S8(rec, 0x20F) = charSlot;
                    FIELD_U8(rec, 0x211) = FIELD_U8(rec, 0x210);
                    FIELD_U8(rec, 0x210) = (u8)part;
                    FIELD_U8(rec, 0x20D) = FIELD_U8(actor, 0x25A);
                    FIELD_U8(rec, 0x20E) = FIELD_U8(actor, 0x25B);
                    placed = TRUE;
                    break;
                }
            }

            if (!placed) {
                for (i = 0; i < RECORD_COUNT; i++) {
                    u8* sub;
                    rec = RECORD(i);
                    sub = rec + 0x140;
                    lbl_803CBC20 = sub;
                    for (k = 0; k < RECORD_COUNT; k++) {
                        u8* obj = getObject(k);
                        if (obj == NULL) {
                            continue;
                        }
                        if (FIELD_S8(sub, 0xCF) == FIELD_S8(obj, 0x252)) {
                            break;
                        }
                    }
                    if (k == RECORD_COUNT) {
                        FIELD_U32(sub, 0xC8) = lbl_803CBC00;
                        FIELD_S8(rec, 0x20F) = charSlot;
                        FIELD_U8(rec, 0x211) = FIELD_U8(rec, 0x210);
                        FIELD_U8(rec, 0x210) = (u8)part;
                        FIELD_U8(rec, 0x20D) = FIELD_U8(actor, 0x25A);
                        FIELD_U8(rec, 0x20E) = FIELD_U8(actor, 0x25B);
                        break;
                    }
                }
            }
        }

        FIELD_U8(lbl_803CBC20, 0xC1) = 0;
        FIELD_U8(lbl_803CBC20, 0x5D) = 0;
    }

    if (lbl_803CBBFB == 0) {
        return FALSE;
    }

    lowPart = part < 9;
    sel = lowPart ? FIELD_U8(actor, 0x25A) : FIELD_U8(actor, 0x25B);
    flagsMatch = ((sel != 0) == lowPart);

    if (lbl_803CBBFC == 0) {
        if (lbl_803CBC0C == 0 && FIELD_U8(&lbl_803C6CF8, 0x715) == 1) {
            u8* sub = lbl_803CBC20;
            s32 r4;
            if (lowPart && FIELD_U8(sub, 0xCD) != 0) {
                r4 = 3;
            } else if (flagsMatch) {
                r4 = 5;
            } else {
                r4 = 1;
            }
            lbl_803CBC1C = sub + 0x64;
            lbl_803CBC0C = 1;
            loadCharacterHandItem(FIELD_S8(sub, 0xCF), r4, FIELD_PTR(sub, 0x64));
        }
        if (!attachHandModelTail()) {
            return FALSE;
        }
        lbl_803CBBFC = 1;
    }

    if (lbl_803CBBFD == 0) {
        if (lbl_803CBC0C == 0 && FIELD_U8(&lbl_803C6CF8, 0x715) == 1) {
            u8* sub = lbl_803CBC20;
            s32 r4;
            if (lowPart && FIELD_U8(sub, 0xCD) != 1) {
                r4 = 2;
            } else if (flagsMatch) {
                r4 = 4;
            } else {
                r4 = 0;
            }
            lbl_803CBC1C = sub;
            lbl_803CBC0C = 1;
            loadCharacterHandItem(FIELD_S8(sub, 0xCF), r4, FIELD_PTR(sub, 0x0));
        }
        if (!attachHandModelTail()) {
            return FALSE;
        }
        lbl_803CBBFD = 1;
    }

    if (lbl_803CBBFC == 0 || lbl_803CBBFD == 0) {
        return FALSE;
    }

    FIELD_PTR(actor, 0x30) = lbl_803CBC20;
    {
        u8* obj = getObject(part);
        u16 bone = getHandAttachBone(obj, 0);
        if (bone != NO_BONE) {
            clearBoneSlot(obj, bone, 0x60);
        }
        obj = getObject(part);
        bone = getHandAttachBone(obj, 1);
        if (bone != NO_BONE) {
            clearBoneSlot(obj, bone, 0xC4);
        }
    }
    FIELD_U8(FIELD_PTR(actor, 0x30), 0xCC) = TRUE;
    lbl_803CBC20 = NULL;
    lbl_803CBBFD = 0;
    lbl_803CBBFC = 0;
    lbl_803CBBFB = 0;
    lbl_803CBC00 = 0;
    return TRUE;
}
