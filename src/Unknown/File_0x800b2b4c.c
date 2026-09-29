#include "Unknown/File_0x800b2b4c.h"

void fn_800B2B4C(UnkB2B4C* obj, f32 value) {
    obj->value90 = value;
}

void fn_800B2B54(UnkB2B4C* obj, u16 index, u8 value) {
    obj->entries[index]->value134 = value;
}

void Set_FUN_800b2b6c(UnkB2B4C* obj, s32 value) {
    obj->value88 = value;
}
