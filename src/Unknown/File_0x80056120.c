#include "Unknown/File_0x80056120.h"

#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x8004a2bc.h"
#include "text/text.h"
#include "static/UnknownHomes_Static.h"
#include "game/challenge/challenge_state.h"

#define SCENE_FIRST_HANDLE(s) (*(u16 *)((u8 *)(s) + 0x14))
#define GRA_OBJECT(idx) (graphicsRelatedArray[(idx)].object)
#define OBJ_U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define OBJ_U32(o, off) (*(u32 *)((u8 *)(o) + (off)))

extern u8 lbl_803C5EE0[0x18];
extern u8 lbl_802E4BB0[0x10];
extern UIRecordDescriptor lbl_800FF540[];

void newMenuRelated(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u8 *gs = (u8 *)&gameSettings;
    u8 *gameInit = (u8 *)&g_d_GameSettings;
    u8 *statics = (u8 *)&Static_Stats_Tables;
    s16 *shorts = (s16 *)lbl_803C5EE0;
    u8 *icons = lbl_802E4BB0;
    s32 i;
    s32 k;
    s32 j;
    s32 t;
    s32 r29;
    s32 r31;
    s32 src;
    s32 v;
    s32 base;
    s32 frame;

    shorts[0] = (s8)gs[0x65];
    for (i = 0; i < 0x10; i++) {
        icons[i] = gs[0x45 + i];
    }
    icons[2] = gs[0x3D];
    icons[3] = gs[0x3E];
    icons[4] = gs[0x3F];
    shorts[1] = (s8)gs[0x66];
    shorts[2] = (s8)gs[0x67];
    shorts[3] = (s8)gs[0x68];

    addGraphicsElementToScene(item, lbl_800FF540);

    for (i = 1; i < 5; i++) {
        load_Icon(item, i + 1, 1, 0x110, i - 1);
        if (i > 1) {
            TextGraphicsObject *obj = GRA_OBJECT(SCENE_FIRST_HANDLE(item) + i + 0x1B);
            OBJ_U32(obj, 0x5C) = (u32)(i - 2) << 16;
            OBJ_U32(obj, 0x54) &= ~2;
        }
    }

    OBJ_U16(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + (s8)gs[0x3C] + 0xC), 0x64) = 0x107;
    OBJ_U16(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + ((s8)gs[0x3D] ^ 1) + 0xE), 0x64) = 0x107;
    load_Icon(item, 0x20, 1, 0xF9, (s8)gs[0x3D] ^ 1);
    OBJ_U16(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + (s8)gs[0x3E] + 0x10), 0x64) = 0x109;
    load_Icon(item, 0x21, 1, 0xF9, (s8)gs[0x3E] + 2);
    OBJ_U16(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + ((s8)gs[0x3F] ^ 1) + 0x15), 0x64) = 0x107;
    load_Icon(item, 0x22, 1, 0xF9, (s8)gs[0x3F] ^ 1);

    for (k = 0; k < 2; k++) {
        if (gameInit[0x10] == 0 && k != 0) {
            load_Icon(item, k + 0xC, 1, 0x116, 0xD);
        } else {
            load_Icon(item, k + 0xC, 1, 0x116, (s8)statics[0x46F8 + k] + 9);
        }
        load_Icon(item, k + 0xE, 1, 0x116, k + 2);
        load_Icon(item, k + 0x15, 1, 0x116, k + 2);
    }

    for (j = 0; j < 5; j++) {
        load_Icon(item, j + 0x10, 1, 0x116, j + 4);
    }

    OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + 0x18), 0x5C) = (u32)statics[0x470D] << 16;
    OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + 0x19), 0x5C) = (u32)statics[0x470E] << 16;

    for (r31 = 0; r31 < 2; r31++) {
        if (gameInit[0x10] == 0 && r31 != 0) {
            if ((s8)statics[0x46F8] != 0) {
                frame = 4;
            } else {
                frame = 5;
            }
            load_Icon(item, r31 + 0x27, 1, 0x46, frame);
        } else {
            load_Icon(item, r31 + 0x27, 1, 0x46, (s8)statics[0x46F8 + r31]);
        }

        if (gameInit[7] == 5 && r31 != 0) {
            v = (s8)((u8 *)&g_Challenge)[0x441F];
        } else {
            v = *(s32 *)(statics + 0x46E0 + 4 * r31);
        }
        OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + r31 + 0x3D), 0x5C) = (u32)v << 16;

        for (t = 0; t < 4; t++) {
            load_Icon(item, 0x2B + 4 * r31 + t, 1, 0x11A, t);
        }

        for (r29 = 0; r29 < 4; r29++) {
            s32 e = 0x33 + 4 * r31 + r29;
            src = (s8)gs[0x45 + 4 * r31 + r29];

            if (r29 == 0) {
                load_Icon(item, e, 1, 0x116, 1);
                load_Icon(item, e, 2, 0x116, 0);
                OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + e), 0x5C) = (u32)(src * 0xA0000);
            } else if (r29 == 3) {
                load_Icon(item, e, 1, 0x116, 2);
                load_Icon(item, e, 2, 0x116, 3);
                OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + e), 0x5C) = (u32)((src ^ 1) * 0xA0000);
            } else {
                load_Icon(item, e, 1, 0x116, 1);
                load_Icon(item, e, 2, 0x116, 0xE);
                OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + e), 0x5C) = (u32)(src * 0xA0000);
            }

            base = SCENE_FIRST_HANDLE(item) + 4 * r29 + r31;
            if (src != 0) {
                if (r29 == 3) {
                    OBJ_U32(GRA_OBJECT(base + 0x47), 0x54) &= ~2;
                    OBJ_U32(GRA_OBJECT(base + 0x49), 0x54) |= 2;
                } else {
                    OBJ_U32(GRA_OBJECT(base + 0x47), 0x54) |= 2;
                    OBJ_U32(GRA_OBJECT(base + 0x49), 0x54) &= ~2;
                }
            } else {
                if (r29 == 3) {
                    OBJ_U32(GRA_OBJECT(base + 0x47), 0x54) |= 2;
                    OBJ_U32(GRA_OBJECT(base + 0x49), 0x54) &= ~2;
                } else {
                    OBJ_U32(GRA_OBJECT(base + 0x47), 0x54) &= ~2;
                    OBJ_U32(GRA_OBJECT(base + 0x49), 0x54) |= 2;
                }
            }
        }
    }

    if (gameInit[7] == 5) {
        load_Icon(item, 0x57, 1, 0x20, gameInit[9]);
    } else {
        OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + 0x57), 0x54) &= ~2;
    }

    lbl_803C5EE0[0x15] = 0;
    currentDrawingItem->func = fn_800559EC;
}
