#include "Unknown/File_0x8001a6b0.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800bde8c.h"
#include "Unknown/File_0x8003a538.h"
#include "Unknown/File_0x8001f4c0.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

/* Node of the challenge map drawing script (the object currentDrawingItem points at). */
typedef struct ChallengeMapNode {
    /* 0x00 */ u8 _00[0x0C];
    /* 0x0C */ DrawingSceneStruct *child;
    /* 0x10 */ u8 _10[0x14 - 0x10];
    /* 0x14 */ u8 step;
    /* 0x15 */ u8 _15;
    /* 0x16 */ u8 _16;
    /* 0x17 */ u8 _17;
    /* 0x18 */ u8 _18;
} ChallengeMapNode;

/* This unit's view of hugeAnimStruct (0x3154 bytes). */
extern struct {
    /* 0x0000 */ u8 _0000[0x2C84];
    /* 0x2C84 */ u32 *offsetTable;
    /* 0x2C88 */ u8 _2C88[0x2D77 - 0x2C88];
    /* 0x2D77 */ u8 _2D77;
    /* 0x2D78 */ u8 _2D78[0x2D7A - 0x2D78];
    /* 0x2D7A */ u8 _2D7A;
    /* 0x2D7B */ u8 _2D7B;
    /* 0x2D7C */ u8 _2D7C;
    /* 0x2D7D */ u8 _2D7D[0x307B - 0x2D7D];
    /* 0x307B */ u8 _307B;
    /* 0x307C */ u8 _307C;
    /* 0x307D */ u8 _307D;
    /* 0x307E */ u8 _307E[0x3082 - 0x307E];
    /* 0x3082 */ u8 _3082;
    /* 0x3083 */ u8 _3083[0x3086 - 0x3083];
    /* 0x3086 */ u8 _3086;
    /* 0x3087 */ u8 _3087;
} hugeAnimStruct;

extern Vec lbl_80367318;

void challengeMapRelated(void) {
    ChallengeMapNode *node;
    Vec dir;
    f32 len;
    s32 i;
    s32 k;
    Vec copy;

    if (hugeAnimStruct._3082 != 0) {
        return;
    }

    node = (ChallengeMapNode *)currentDrawingItem;
    switch (node->step) {
    case 0:
        hugeAnimStruct._2D77 = 0;
        hugeAnimStruct._2D7B = 0;
        hugeAnimStruct._2D7C = 0;
        hugeAnimStruct._2D7A = 0;
        node->_16 = 0;
        node->_18 = 0;
        node->step = 1;
        break;
    case 1:
        if (practice_loadAllGraphics(g_d_GameSettings.home_AwaySetting ^ 1) != FALSE) {
            node->step = 2;
        }
        break;
    case 2: {
        ChallengeMapNode *fresh =
            (ChallengeMapNode *)insertGraphicDrawingFunction(fn_800188C0, 0);

        fresh->step = 0;
        fresh->_16 = 0;
        fresh->_17 = 0xFF;
        hugeAnimStruct._307B = 1;
        node->step++;
        break;
    }
    case 3:
        if (hugeAnimStruct._307B == 0) {
            node->step = 6;
        }
        break;
    case 6:
        dir.x = -lbl_80367318.x;
        dir.y = -lbl_80367318.y;
        dir.z = -lbl_80367318.z;
        len = dolsqrtf2((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));
        hugeAnimStruct._3087 = 1;
        dir.x /= len;
        dir.y /= len;
        dir.z /= len;
        fn_8003A540(0);
        hugeAnimStruct._3086 = 1;
        DrawShadows(1);
        copy = dir;
        updateVectorInArray(0, copy);
        fn_800BF048(fn_8001AAF0);
        fn_800BF058(fn_8001AB10);
        for (i = 0; i < 80; i += 8) {
            for (k = 0; k < 8; k++) {
                hugeAnimStruct.offsetTable[i + k] += (u32)hugeAnimStruct.offsetTable;
            }
        }
        hugeAnimStruct._3082 = 0;
        hugeAnimStruct._307C = 0;
        hugeAnimStruct._307D = 0;
        fn_8001F8A4();
        node->step++;
        break;
    case 7:
        challengeMapMaybe();
        node->step++;
        break;
    case 8:
        hugeAnimStruct._307C = 1;
        node->child->state = 1;
        removeCurrentDrawingItem();
        break;
    default:
        break;
    }
}
