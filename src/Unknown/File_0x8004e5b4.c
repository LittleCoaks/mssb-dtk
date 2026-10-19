#include "Unknown/File_0x8004e5b4.h"
#include "game/challenge/star_mission_data.h"
#include "static/UnknownHomes_Static.h"

void add_or_RemoveCharToATeam(int team, int charID, BOOL add) {
    int i;
    int id = characterStaticIndexes[charID].trackerIdx;

    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        if (mapCaptainCursorPositionToCharID[i] == id) {
            if (add) {
                charSelectStruct.slotTeam[i] = team;
            } else {
                charSelectStruct.slotTeam[i] = -1;
            }
            return;
        }
    }
}
