#include "Unknown/File_0x80024bb4.h"
#include "static/UnknownHomes_Static.h"

extern u8 characterStaticIndexes[0x144];
extern u8 unlockableCharacter_noDupeNoGapCharID[8];

f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax) {
    f32 t;
    f32 span;
    f32 range = prevMax - prevMin;

    if (range == 0.0f) {
        t = 1.0f;
    } else {
        t = (value - prevMin) / range;
        t = t > 1.0f ? 1.0f : t < 0.0f ? 0.0f : t;
    }
    span = nextMax - nextMin;
    return span * t + nextMin;
}

BOOL isCharacterUnlocked(int charID) {
    int i;

    for (i = 0; i < 6; i++) {
        if (unlockableCharacter_noDupeNoGapCharID[i] == characterStaticIndexes[charID * 6 + 2]) {
            if (!g_d_GameSettings.characterUnlocked[i]) {
                return FALSE;
            }
            break;
        }
    }
    return TRUE;
}

int fn_80024C6C(fn_80024C6C_s* obj, int arg1) {
    if (!obj->_274) {
        return -1;
    }
    if (obj->_254 >= 9) {
        return -1;
    }
    if (obj->_25A != arg1) {
        switch (obj->_252) {
        case 38:
        case 40:
        case 41:
            return -1;
        case 14:
        case 16:
        case 37:
        case 44:
        case 45:
        case 46:
        case 47:
            return 2;
        }
        return 2;
    }
    switch (obj->_252) {
    case 18:
    case 38:
    case 40:
    case 41:
        return -1;
    case 14:
    case 16:
    case 37:
    case 44:
    case 45:
    case 46:
    case 47:
        return 0;
    }
    return 1;
}
