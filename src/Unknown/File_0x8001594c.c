#include "Unknown/File_0x8001594c.h"
#include "game/UnknownHomes_Game.h"

extern u8 hugeAnimStruct[0x3154];
extern u8 lineUpInfoStruct[];
extern u8 lbl_80118220[0x520];
extern s16 lbl_800EEB18[];
extern u8 lbl_803C6CF8[0x708];
extern u8 lbl_803CB7C2;
extern u8 lbl_803CBC34[3];
extern u8 lbl_803CBC2C;
extern u8 lbl_803CBBF8;
extern u8 lbl_803CBBF9;
extern u8 lbl_803CBBFA;
extern s32 lbl_803CBBF0;
extern s32 lbl_803CBC28;

int fn_80015468(int team);
int fn_80014A18(int team);
int fn_80017098(int a, int b, int c, int d, int e, int f);
void fn_80021ADC(int value, void *entry);
BOOL animateModelArmsGlovesBats(void *object);
void actRelated(void *file, void *effect);

#define OBJ_SLOT(anim, i) (*(u8 **)((anim) + 0x2C50 + (i) * 4))

#define PRACTICE_LOAD_BC_STEPS() \
    if (anim[0x2D7B] == 0xB) { \
        if (lbl_803CB7C2 != 0) { \
            u8 flag0 = lbl_803CBC34[0]; \
            lbl_803CB7C2 = 0; \
            if (flag0 != 0) { \
                lbl_803CBC2C = 0; \
                lbl_803CBBF8 = 9; \
            } else { \
                if (lbl_803CBC34[1] != 0) { \
                    u8 count = lbl_803CBBF8; \
                    lbl_803CBC2C = 0; \
                    lbl_803CBBF8 = count + 1; \
                } \
                if (lbl_803CBC34[2] != 0) { \
                    lbl_803CBBF8 = lbl_803CBBF8 + 1; \
                    if (lbl_803CBC34[1] == 0) { \
                        lbl_803CBC2C = 1; \
                    } \
                } \
            } \
        } \
\
        if (lbl_803CBBF8 == 0) { \
            ok = TRUE; \
        } else { \
            int idx = lbl_803CBBF0 + lbl_803CBC2C; \
            u8 *obj = OBJ_SLOT(anim, idx); \
            u8 typeId = obj[0x252]; \
            u8 idxByte = (u8)idx; \
            int stepped = 0; \
\
            if (lbl_803CBBF9 == 0) { \
                u8 *p = lbl_80118220; \
                int found = 0; \
\
                while ((s8)p[0x61] != -2) { \
                    if ((s8)p[0x60] == typeId && (s8)p[0x61] == -1) { \
                        found = 1; \
                        break; \
                    } \
                    p += 0x64; \
                } \
\
                if (found) { \
                    u8 *sub = *(u8 **)(obj + 0x08); \
                    p[0x60] = typeId; \
                    p[0x61] = idxByte; \
                    *(u8 **)(obj + 0x2C) = p; \
                    *(u32 *)(p + 0x30) = *(u32 *)(sub + 0x10); \
                    stepped = 1; \
                } else { \
                    int count = 0; \
                    u8 *q = lbl_80118220; \
                    lbl_803CBBF9 = 1; \
                    while ((s8)q[0x61] != -2 && (s8)q[0x61] != -1) { \
                        q += 0x64; \
                        count++; \
                    } \
                    lbl_803CBC28 = count; \
                } \
            } \
\
            if (!stepped) { \
                int r3val; \
                u8 *entry = lbl_80118220 + lbl_803CBC28 * 0x64; \
                u8 *sub = *(u8 **)(obj + 0x08); \
                entry[0x5D] = 0; \
                if (lbl_800EEB18[typeId] == -1 || *(u32 *)(sub + 0x10) == 0) { \
                    *(u8 **)(obj + 0x2C) = NULL; \
                    r3val = 1; \
                } else { \
                    if (lbl_803CBBFA == 0) { \
                        fn_80021ADC(lbl_800EEB18[typeId], *(void **)entry); \
                        lbl_803CBBFA = 1; \
                    } \
                    if (lbl_803C6CF8[0x715] == 1) { \
                        entry[0x60] = typeId; \
                        entry[0x61] = idxByte; \
                        *(u32 *)(entry + 4) = *(u32 *)entry; \
                        actRelated(*(void **)(sub + 0x10), entry + 4); \
                        *(u8 **)(obj + 0x2C) = entry; \
                        lbl_803CBBFA = 0; \
                        r3val = 1; \
                    } else { \
                        r3val = 0; \
                    } \
                } \
                if (r3val) { \
                    lbl_803CBBF9 = 0; \
                    stepped = 1; \
                } \
            } \
\
            if (stepped) { \
                lbl_803CBBF0 = lbl_803CBBF0 + 1; \
            } \
            if ((u32)lbl_803CBBF8 == (u32)lbl_803CBBF0) { \
                lbl_803CBBF0 = 0; \
                ok = TRUE; \
            } else { \
                ok = FALSE; \
            } \
        } \
\
        if (!ok) { \
            return FALSE; \
        } \
        anim[0x2D7B] = 0xC; \
    } \
\
    if (anim[0x2D7B] == 0xC) { \
        int ret = animateModelArmsGlovesBats(OBJ_SLOT(anim, lbl_803CBBF0)); \
        if ((u8)ret != 0) { \
            lbl_803CBBF0 = lbl_803CBBF0 + 1; \
        } \
        if (lbl_803CBBF0 == 9) { \
            lbl_803CBBF0 = 0; \
            return TRUE; \
        } \
        return FALSE; \
    }

BOOL practice_loadAllGraphics(int team)
{
    u8 *anim = hugeAnimStruct;
    u8 *lineUp;
    int i;
    int k;
    int ok;

    if (anim[0x2D77] == 1) {
        return FALSE;
    }

    if (anim[0x2D77] == 2) {
        u8 srcSlot = anim[0x2D79];
        u8 dstSlot = anim[0x2D7B];
        OBJ_SLOT(anim, dstSlot) = anim + srcSlot * 0x27C + 0xC04;
        anim[0x2D77] = 0;
        anim[0x2D7B] = dstSlot + 1;
    }

    if (anim[0x2D7B] == 9) {
        anim[0x2D8E] = 0;
        anim[0x2D7B] = 0xA;
    }

    if (anim[0x2D7C] == 0) {
        if (anim[0x2D7B] == 0xA) {
            if (!fn_80015468(team)) {
                return FALSE;
            }
            anim[0x2D7B] = 0xB;
        }
        PRACTICE_LOAD_BC_STEPS()
    } else {
        if (anim[0x2D7B] == 0xA) {
            if (!fn_80014A18(team)) {
                return FALSE;
            }
            anim[0x2D7B] = 0xB;
        }
        PRACTICE_LOAD_BC_STEPS()
    }

    lineUp = lineUpInfoStruct + team * 0x24;

    for (i = 0; i < 9; i++) {
        u8 *obj = OBJ_SLOT(anim, i);
        if (obj == NULL) {
            continue;
        }

        for (k = 0; k < 9; k++) {
            if (inMemRoster[team][(s8)lineUp[k * 4]].stats.CharID == (s8)obj[0x252]) {
                break;
            }
        }

        if (k == 9) {
            u8 *entry = *(u8 **)(obj + 0x2C);
            u8 *sub;
            if (entry != NULL) {
                entry[0x61] = 0xFF;
                entry[0x5C] = 0xFE;
                *(u8 **)(obj + 0x2C) = NULL;
            }

            sub = *(u8 **)(obj + 0x30);
            if (sub != NULL) {
                sub[0xD1] = sub[0xD0];
                sub[0xD0] = 0xFF;
                sub[0x5C] = 0xFE;
                sub[0xC0] = 0xFE;
                *(u8 **)(obj + 0x30) = NULL;
            }

            obj[0x25C] = 0;
            OBJ_SLOT(anim, i) = NULL;
            {
                int j;
                for (j = 0; j < 13; j++) {
                    if ((s8)anim[0x2D6A + j] == i) {
                        anim[0x2D6A + j] = 0xFF;
                    }
                }
            }
        }
    }

    {
        u8 state = anim[0x2D7B];
        int idx = 9;
        for (k = 0; k < 9; k++) {
            if ((s8)state == (s8)lineUp[2 + k * 4]) {
                idx = k;
                break;
            }
        }
        if (fn_80017098(team, idx, 0, state, 0, -1)) {
            anim[0x2D77] = 2;
        }
    }

    return FALSE;
}
