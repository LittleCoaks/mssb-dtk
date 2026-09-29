#include "Unknown/File_0x800506e8.h"

void addOrRemoveCharacterToTeam(int team, int charID, BOOL add) {
    int i;
    int id = characterStaticIndexes[charID * 6 + 1];

    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        if (characterIconsOnCSS[i] == id) {
            if (add) {
                charSelectStruct.slotTeam[i] = team;
            } else {
                charSelectStruct.slotTeam[i] = -1;
            }
            return;
        }
    }
}
