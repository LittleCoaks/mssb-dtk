#include "Unknown/File_0x8004b7f4.h"
#include "Unknown/File_0x8001d180.h"
#include "static/UnknownHomes_Static.h"

void processCharacterStateBasedOnGameMode(CharacterStateActor* a) {
    s32 idx;
    s32 i;
    BOOL flag;
    u16 slots[2];
    void* handPtrs[2];
    void* hand;
    s8 kind;
    u32 mode;

    kind = a->_252;
    switch (kind) {
    case 0x28:
        idx = 1;
        break;
    case 0x29:
        idx = 2;
        break;
    }

    if ((a->_062 >= 0x69 && a->_062 < 0x75) || a->_062 == -1) {
        setHandModelAttached(a->_254, specialBatAttachSlots[idx][0], FALSE);
        setHandModelAttached(a->_254, specialBatAttachSlots[idx][1], FALSE);
        setHandModelAttached(a->_254, 0, FALSE);
        setHandModelAttached(a->_254, 1, FALSE);
        return;
    }

    mode = g_d_GameSettings.GameModeSelected;
    if (mode == GAME_TYPE_TOY_FIELD) {
        if (a->_278 == 0) {
            flag = !a->_25A;
            setHandModelAttached(a->_254, !flag, TRUE);
        } else {
            flag = !a->_25B;
            setHandModelAttached(a->_254, !flag, FALSE);
        }
    } else if (mode == GAME_TYPE_MINIGAMES) {
        flag = !a->_25B;
        setHandModelAttached(a->_254, !flag, FALSE);
    } else if (a->_254 >= 9) {
        flag = !a->_25B;
        setHandModelAttached(a->_254, !flag, FALSE);
    } else {
        flag = !a->_25A;
        setHandModelAttached(a->_254, !flag, TRUE);
    }

    setHandModelAttached(a->_254, flag, FALSE);

    slots[flag] = specialBatAttachSlots[idx][0];
    slots[!flag] = specialBatAttachSlots[idx][1];

    hand = a->_030;
    if (hand == NULL) {
        return;
    }

    if (a->_278 == 0) {
        setHandModelAttached(a->_254, slots[0], FALSE);
        setHandModelAttached(a->_254, slots[1], FALSE);
        return;
    }

    handPtrs[flag] = (u8*)hand + 0x10;
    handPtrs[!flag] = (u8*)hand + 0x74;

    i = 1;
    do {
        if (getHandTrackFlags(handPtrs[i]) & 0x20000000) {
            setHandModelAttached(a->_254, slots[i], TRUE);
        } else {
            setHandModelAttached(a->_254, slots[i], FALSE);
        }
    } while (i-- != 0);
}
