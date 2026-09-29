#include "Unknown/File_0x80063958.h"
#include "Dolphin/stl.h"

void maybeUpdateFielderTerrainStatus(s8 fielderIndex) {
    FielderTerrainState* state = &lbl_802E4BC0[fielderIndex];

    memset(&state->pos0, 0, sizeof(Vec));
    memset(&state->pos1, 0, sizeof(Vec));
    state->unk18 = 0;
    state->unk1C = 0;
}
