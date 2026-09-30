#include "Unknown/File_0x80057c08.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x800576f0.h"
#include "Unknown/File_0x800b0a14.h"
#include "text/text_channel.h"
#include "game/UnknownHomes_Game.h"

extern UIRecordDescriptor lbl_80108048[];

void starMenu(void) {
    MenuScene* scene = (MenuScene*)currentDrawingItem;
    int i;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_80108048);
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        ((UIRecord*)graphicsRelatedArray[scene->firstHandle + 12 + i].object)->frame = i << 16;
        load_Icon(scene, i + 21, 1, 0x83, inMemRoster[0][i].stats.CharID);
    }
    currentDrawingItem->func = challengeCheckStarsMenuLoading;
}
