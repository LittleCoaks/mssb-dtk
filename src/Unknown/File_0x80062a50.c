#include "Unknown/File_0x80062a50.h"
#include "Unknown/File_0x80062a94.h"
#include "static/UnknownHomes_Static.h"

void initializeUnknown(void) {
    Static_Stats_Tables.unk48B3 = 0;
    menuMusic.handle = 0;
    menuMusic.stopping = 0;
    menuMusic.playing = 0;
}

void fn_80062A74(void) {
    menuMusic.stopping = 1;
    Static_Stats_Tables.unk48B3 = 1;
}
