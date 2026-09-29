#include "Unknown/File_0x8004e5b4.h"
#include "static/UnknownHomes_Static.h"

void add_or_RemoveCharToATeam(int team, int charID, BOOL add) {
    int i;
    int id = characterStaticIndexes[charID * 6 + 1];

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
