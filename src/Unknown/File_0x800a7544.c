#include "Unknown/File_0x800a7544.h"
#include "Dolphin/dvd.h"

s32 ConvertPathToEntryNum(char** path) {
    return DVDConvertPathToEntrynum(*path);
}
