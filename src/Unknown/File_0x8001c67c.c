#include "Unknown/File_0x8001c67c.h"

#include "C3/actor.h"
#include "C3/anim.h"
#include "Unknown/dvdsys.h"
#include "Unknown/File_0x800a7568.h"
#include "static/UnknownHomes_Static.h"

extern u8 hugeAnimStruct[0x3154];
extern u8 highLevelSimulationFlag[4];
extern u32 lbl_803CB790;
extern f32 lbl_803CC4B8;
extern f32 lbl_803CC4F0;

int loadAndAnimateCharacter(int charSlot, int objSlot) {
    if (highLevelSimulationFlag[2] == 0) {
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            return 0;
        }
        {
            u8* charObj = *(u8**)(hugeAnimStruct + 0x64);
            Actor* actor = *(Actor**)(charObj + 0x274);
            u8* firstBoneExtra = *(u8**)((u8*)actor->boneArray[0] + 0xE8);

            if (firstBoneExtra != NULL && *(u32*)(firstBoneExtra + 0xC) != 0) {
                s32 i;
                f32 threshold = lbl_803CC4F0;
                for (i = 0; i < actor->totalBones; i++) {
                    ACTSetBoneTrack(actor->boneArray[i], NULL, lbl_803CC4B8, actor->unk8C < threshold);
                }
                charObj[0x2CC] = 0;
                charObj[0x2CD] = 0;
                charObj[0x2CE] = 0;
                *(f32*)(charObj + 0x2D4) = lbl_803CC4B8;
            }
        }
        highLevelSimulationFlag[2] = 1;
    }

    if (highLevelSimulationFlag[2] == 1) {
        if (g_d_GameSettings.minigamesEnabled) {
            s32 idx;
            if (g_d_GameSettings.GameModeSelected == 7) {
                idx = charSlot * 0x13 + 9;
            } else {
                idx = charSlot * 0x13 + 2;
            }
            ARAMTransfer((void*)(lbl_803CB790 + (idx << 4)), *(s32*)(hugeAnimStruct + 0x2CF8), 0, 0);
        } else if (charSlot == *(s16*)(hugeAnimStruct + 0x2D50)) {
            memcpy(*(void**)(hugeAnimStruct + 0x2CAC), *(void**)(hugeAnimStruct + 0x2D48), *(u32*)(hugeAnimStruct + 0x2D4C));
            ANIMGet(*(ANIMBank**)(hugeAnimStruct + 0x2CAC));
            {
                u8* obj = ((u8**)(hugeAnimStruct + 0x2C50))[objSlot];
                if (*(void**)(obj + 0x10) == NULL) {
                    *(void**)(obj + 0x10) = *(void**)(hugeAnimStruct + 0x2CAC);
                }
            }
            *(s16*)(hugeAnimStruct + 0x2D68) = (s16)charSlot;
            return 1;
        } else {
            s32 idx;
            if (g_d_GameSettings.GameModeSelected == 2) {
                idx = charSlot * 0x13 + 10;
            } else {
                idx = charSlot * 0x13 + 2;
            }
            ARAMTransfer((void*)(lbl_803CB790 + (idx << 4)), *(s32*)(hugeAnimStruct + 0x2CAC), 0, 0);
        }
        highLevelSimulationFlag[2] = 2;
    } else if (highLevelSimulationFlag[2] == 2 && lbl_803C6CF8.cancel.bytes[1] == 1) {
        if (g_d_GameSettings.minigamesEnabled) {
            ANIMGet(*(ANIMBank**)(hugeAnimStruct + 0x2CF8));
            {
                u8* obj = ((u8**)(hugeAnimStruct + 0x2C50))[objSlot];
                if (*(void**)(obj + 0x10) == NULL) {
                    *(void**)(obj + 0x10) = *(void**)(hugeAnimStruct + 0x2CF8);
                }
            }
        } else {
            ANIMGet(*(ANIMBank**)(hugeAnimStruct + 0x2CAC));
            {
                u8* obj = ((u8**)(hugeAnimStruct + 0x2C50))[objSlot];
                if (*(void**)(obj + 0x10) == NULL) {
                    *(void**)(obj + 0x10) = *(void**)(hugeAnimStruct + 0x2CAC);
                }
            }
        }
        *(s16*)(hugeAnimStruct + 0x2D68) = (s16)charSlot;
        return 1;
    }

    highLevelSimulationFlag[0] = 0;
    return 0;
}
