#include "text/text_init.h"
#include "text/text_channel.h"

// Glyph remap table, filled at init from bank 0's string 7.
extern u16 glyphRemapTable[];

void initTextRendering(void) {
    u16* src;
    s32 i;

    screenTextArray.textBanks[7] = (TextBank*)screenTextArray.textBanks[0]->strings;
    screenTextArray.digitGlyphs = screenTextArray.textBanks[0]->strings[1];
    screenTextArray.unk7F0 = screenTextArray.textBanks[0]->strings[2];
    screenTextArray.unk7F8 = screenTextArray.textBanks[0]->strings[6];
    screenTextArray.glyphBase = screenTextArray.textBanks[0]->strings[5];

    src = screenTextArray.textBanks[7]->strings[6];
    i = 0;
    while (1) {
        if (src[i] == 0x4001) {
            return;
        }
        glyphRemapTable[i] = src[i];
        i++;
    }
}
