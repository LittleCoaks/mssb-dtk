#include "Unknown/File_0x8004e504.h"
#include "Unknown/File_0x8004e5b4.h"
#include "static/UnknownHomes_Static.h"

void storeCursorLocOrCharIDs(BOOL isCharID, int port0, int port1, int port2, int port3) {
    int values[4];
    int i;
    int charID;
    int slot;

    values[0] = port0;
    values[1] = port1;
    values[2] = port2;
    values[3] = port3;
    for (i = 0; i < 4; i++) {
        if (charSelectStruct.cursorPos[i] >= 0 && values[i] >= 0) {
            if (!isCharID) {
                charSelectStruct.cursorPos[i] = values[i];
            } else {
                charID = characterStaticIndexes[values[i] * 6 + 1];
                for (slot = 0; slot < CHAR_SELECT_GRID_SLOTS; slot++) {
                    if (charID == mapCaptainCursorPositionToCharID[slot]) {
                        charSelectStruct.cursorPos[i] = slot;
                        break;
                    }
                }
            }
        }
    }
}
