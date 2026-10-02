#include "Unknown/File_0x800698f8.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/os.h"

extern u8 mainCharArray[];
extern u8 secondaryCharacterArray[];

int findCharacterID(int charID) {
    int i;

    for (i = 0; i < 32; i++) {
        if (mainCharArray[i] == charID) {
            if (i == 17 && Static_Stats_Tables.unk48AE) {
                i = 32;
            }
            Static_Stats_Tables.unk48AE = 0;
            return i;
        }
    }

    if (i == 32) {
        for (i = 0; i < 22; i++) {
            if (secondaryCharacterArray[i] == charID) {
                switch (i) {
                case 0:
                case 1:
                    charID = 21;
                    break;
                case 2:
                case 3:
                    charID = 22;
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                    charID = 13;
                    break;
                case 8:
                case 9:
                case 10:
                    charID = 25;
                    break;
                case 11:
                    charID = 12;
                    break;
                case 12:
                    charID = 20;
                    break;
                case 13:
                case 14:
                case 15:
                case 16:
                    charID = 16;
                    break;
                case 17:
                case 18:
                case 19:
                    charID = 31;
                    break;
                case 20:
                case 21:
                    charID = 23;
                    break;
                }
                Static_Stats_Tables.unk48AE = 0;
                return charID;
            }
        }
        if (i == 22) {
            OSPanic("mb_subfunc.c", 149, "The character doesn't exist");
        }
    }
    /* Shift-JIS: "//OZ modorichi ga arimasen" (no return value) */
    OSPanic("mb_subfunc.c", 153, "//OZ \x96\xdf\x82\xe8\x92\x6c\x82\xaa\x82\xa0\x82\xe8\x82\xdc\x82\xb9\x82\xf1\n");
    return 0;
}
