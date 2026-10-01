#include "Unknown/File_0x8004ad54.h"
#include "game/ball/collision_primitives.h"

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
