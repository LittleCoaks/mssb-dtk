#define SQRT2_LINKAGE static
#include "game/minigame/toy_field_offscreen.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/camera/camera.h"
#include "text/text_channel.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"

// The scene node's view of its record span in graphicsRelatedArray.
typedef struct _ToyOffscreenScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
} ToyOffscreenScene;

// Screen-edge bounds for the arrows: x {fadeLeft, left, fadeRight, right},
// y {fadeTop, top, fadeBottom, bottom}.
extern s16 lbl_3_data_D638[8];
// Arrow animation frame for each edge direction.
extern u16 lbl_3_data_91AC[8];
extern u8 animRelated[0x124];

#define OFFSCREEN_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)

// .text:0x000E9D30 size:0x610 mapped:0x80728DC4
void toyfield_offScreenCharacterImage(void) {
    ToyOffscreenScene* scene = (ToyOffscreenScene*)currentDrawingItem;
    VecXYZ pos;
    int sx;
    int sy;
    int px;
    int py;
    int dir;
    int alphaX;
    int alphaY;
    int i;
    int k;
    int dx;
    int dz;

    if (animRelated[0x96] == 0 && g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_Minigame._19CE == 0 &&
        g_Minigame.turnOverStatus == 0) {
        s16* bounds = lbl_3_data_D638;

        for (i = 0; i < 3; i++) {
            if ((s8)g_Minigame.minigameControlStruct[1].aIStrength[2 + i] < 0) {
                continue;
            }
            dir = -1;
            alphaX = 0xFF;
            alphaY = 0xFF;
            getAnimRelatedCoordinates(g_Minigame.minigameControlStruct[0].characterIndex[(s8)g_Minigame.minigameControlStruct[1].aIStrength[2 + i]], 4, &pos);
            if (!fn_3_1650C(&sx, &sy, FALSE, pos.x, pos.y, pos.z)) {
                for (k = 0; k < 3; k++) {
                    dx = g_pCamera->_284C.x - pos.x;
                    dz = g_pCamera->_284C.z - pos.z;
                    dx *= 0.2f;
                    dz *= 0.2f;
                    pos.x += dx;
                    pos.z += dz;
                    if (fn_3_1650C(&sx, &sy, FALSE, pos.x, pos.y, pos.z)) {
                        break;
                    }
                }
            }

            px = bounds[1];
            if (sx <= px) {
                dir = 2;
                if (sx > lbl_3_data_D638[0]) {
                    alphaX = 255.0f * (1.0f - (f32)(sx - lbl_3_data_D638[0]) / (f32)(px - lbl_3_data_D638[0]));
                }
            } else {
                px = bounds[3];
                if (sx >= px) {
                    dir = 5;
                    if (sx < bounds[2]) {
                        alphaX = 255.0f * (1.0f - (f32)(sx - bounds[2]) / (f32)(px - bounds[2]));
                    }
                } else {
                    px = sx;
                }
            }
            if (alphaX > 0xFF) {
                alphaX = 0xFF;
            }

            py = bounds[5];
            if (sy <= py) {
                dir += 1;
                if (sy > bounds[4]) {
                    alphaY = 255.0f * (1.0f - (f32)(sy - bounds[4]) / (f32)(py - bounds[4]));
                }
            } else {
                py = bounds[7];
                if (sy >= py) {
                    dir += 2;
                    if (sy < bounds[6]) {
                        alphaY = 255.0f * (1.0f - (f32)(sy - bounds[6]) / (f32)(py - bounds[6]));
                    }
                } else {
                    py = sy;
                }
            }
            if (alphaY > 0xFF) {
                alphaY = 0xFF;
            }

            if (dir < 0 || alphaX <= 0 || alphaY <= 0) {
                OFFSCREEN_RECORD(scene, i)->flags &= ~UI_FLAG_VISIBLE;
                continue;
            }
            OFFSCREEN_RECORD(scene, i)->flags |= UI_FLAG_VISIBLE;
            OFFSCREEN_RECORD(scene, i)->pos.x = px;
            OFFSCREEN_RECORD(scene, i)->pos.y = py;
            if (dir == 2 || dir == 5) {
                OFFSCREEN_RECORD(scene, i)->rgba = alphaX | (OFFSCREEN_RECORD(scene, i)->rgba & ~0xFF);
            } else if (dir >= 2) {
                if (alphaX > alphaY) {
                    OFFSCREEN_RECORD(scene, i)->rgba = alphaX | (OFFSCREEN_RECORD(scene, i)->rgba & ~0xFF);
                } else {
                    OFFSCREEN_RECORD(scene, i)->rgba = alphaY | (OFFSCREEN_RECORD(scene, i)->rgba & ~0xFF);
                }
            } else {
                OFFSCREEN_RECORD(scene, i)->rgba = alphaY | (OFFSCREEN_RECORD(scene, i)->rgba & ~0xFF);
            }
            OFFSCREEN_RECORD(scene, i)->frame = lbl_3_data_91AC[dir] << 16;
        }
    } else {
        animRelated[0x97] = 0;
        removeGraphicsElementFromScene(currentDrawingItem);
        removeCurrentDrawingItem();
    }
}
