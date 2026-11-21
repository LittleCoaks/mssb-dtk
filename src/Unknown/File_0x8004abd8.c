#include "Unknown/File_0x8004abd8.h"
#include "Unknown/File_0x8004ac00.h"
#include "Unknown/File_0x8004ad54.h"
#include "game/ball/collision_primitives.h"

// 0x8004ABD8-0x8004B284: one translation unit by its .sdata/.sbss/.sdata2/.data
// (docs/splits.md, 2026-11-21): the former File_0x8004abd8.c, File_0x8004ac00.c
// and File_0x8004ad54.c plus fn_8004ACC4 ... fn_8004B270, which have no C yet.

extern BOOL changesToZeroOnBlackTransitionScreen;
extern s32 lbl_803CBCFC;
extern BOOL setHandOnFireAsPitcher;

void Set_803cb848(BOOL value) {
    changesToZeroOnBlackTransitionScreen = value;
}

s32 fn_8004ABE0(void) {
    return lbl_803CBCFC;
}

BOOL marioHandOnFire_endFireAnimation(BOOL clear) {
    BOOL wasOnFire = setHandOnFireAsPitcher;
    if (clear) {
        setHandOnFireAsPitcher = FALSE;
    }
    return wasOnFire;
}

extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;

extern s32 lbl_803CBCF8;
extern s32 lbl_803CB850;

void fn_8004C19C(fn_80024C6C_s* obj, int arg1, int arg2, f32 frame);

void newPitcherEnteringGame(fn_80024C6C_s* obj, int arg1, int arg2, f32 frame) {
    if (lbl_80366158._28 == 1) {
        return;
    }
    if (obj->_252 == 0) {
        if (frame >= (f32)lbl_803CBCF8 && frame <= (f32)lbl_803CB850) {
            setHandOnFireAsPitcher = TRUE;
            if (frame == 0.5) {
                lbl_803CBCFC = TRUE;
            } else {
                lbl_803CBCFC = FALSE;
            }
        }
    } else if (obj->_252 == 18) {
        fn_8004C19C(obj, arg1, arg2, frame);
    }
}

int stadiumCollisionRelated(STADIUM_ID stadiumID, int collisionType) {
    int baseType = collisionType & 0x7F;
    int ret;

    switch (stadiumID) {
    case STADIUM_ID_MARIO_STADIUM:
        if (baseType == BALL_COLLISION_TYPE_GRASS) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case STADIUM_ID_BOWSERS_CASTLE:
        ret = 5;
        break;
    case STADIUM_ID_WARIO_PALACE:
        if (baseType == BALL_COLLISION_TYPE_GRASS) {
            ret = 11;
        } else {
            ret = 10;
        }
        break;
    case STADIUM_ID_YOHSI_PARK:
        if (baseType == BALL_COLLISION_TYPE_GRASS) {
            ret = 7;
        } else {
            ret = 6;
        }
        break;
    case STADIUM_ID_PEACH_GARDEN:
        if (baseType == BALL_COLLISION_TYPE_WATER) {
            ret = 4;
        } else if (baseType == BALL_COLLISION_TYPE_GRASS) {
            ret = 3;
        } else {
            ret = 2;
        }
        break;
    case STADIUM_ID_DK_JUNGLE:
        if (baseType == BALL_COLLISION_TYPE_WATER) {
            ret = 9;
        } else {
            ret = 8;
        }
        break;
    case STADIUM_ID_TOY_FIELD:
        ret = 12;
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}
