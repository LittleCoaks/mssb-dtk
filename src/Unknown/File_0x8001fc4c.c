#include "Unknown/File_0x8001fc4c.h"
#include "game/match_setup/match_loading.h"

/* This file's statics are addressed as offsets from the start of the original
 * translation unit's .data, which begins at lbl_800EE800; the objects ahead of
 * the swap tables are defined here so those offsets come out right. */

u8 lbl_800EE800[0x110] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

MatchFileDescriptor BallModelFiles[2] = {
    { 0x0000040B, 0x40093FF8, 0x0E581000, 0x0005F484 },
    { 0x0000040B, 0x40095BB8, 0x0E5E0800, 0x0006053C },
};

MatchFileDescriptor MinigameCommonFiles[3] = {
    { 0x0000040B, 0x40001640, 0x08EB4800, 0x00000C38 },
    { 0x0000040B, 0x400B2D00, 0x08EB5800, 0x0006A948 },
    { 0x00000000, 0x00000686, 0x08F20800, 0x00000688 },
};

static u16 lbl_800EE960[][2] = {
    {0x16, 0x10}, {0x17, 0x11}, {0x18, 0x12}, {0x19, 0x13}, {0x1A, 0x14},
    {0x1B, 0x15}, {0x20, 0x1C}, {0x21, 0x1D}, {0x22, 0x1E}, {0x23, 0x1F},
    {0x26, 0x25}, {0x28, 0x27}, {0x3D, 0x3C}, {SHORT_TABLE_END, 0},
};

static u16 lbl_800EE998[][2] = {
    {0x2F, 0x34}, {0x30, 0x35}, {0x31, 0x36}, {0x32, 0x37}, {0x33, 0x38},
    {SHORT_TABLE_END, 0},
};

static u16 lbl_800EE9B0[][2] = {
    {0x41, 0x47}, {0x42, 0x48}, {0x43, 0x49}, {0x44, 0x4A}, {0x45, 0x4B},
    {0x46, 0x4C}, {SHORT_TABLE_END, 0},
};

static u16 lbl_803CB798[][2] = {
    {0x4A, 0x4B}, {SHORT_TABLE_END, 0},
};

static u16 lbl_803CB7A0[][2] = {
    {0x2F, 0x34}, {SHORT_TABLE_END, 0},
};

static inline void swapShortPair(ShortsTableOwner* owner, u16 first, u16 second) {
    u16 b;
    u16 a;

    a = owner->slot[first];
    b = owner->slot[second];
    if (a != SHORT_TABLE_END && b != SHORT_TABLE_END) {
        owner->order[a] = b;
        owner->order[b] = a;
    }
}

static inline void swapShortPairs(ShortsTableOwner* owner, u16 (*pairs)[2]) {
    for (; (*pairs)[0] != SHORT_TABLE_END; pairs++) {
        swapShortPair(owner, (*pairs)[0], (*pairs)[1]);
    }
}

static inline void swapShortPairsNonEmpty(ShortsTableOwner* owner, u16 (*pairs)[2]) {
    s32 i;
    u16(*p)[2];

    p = pairs;
    i = 0;
    do {
        swapShortPair(owner, (*p)[0], (*p)[1]);
        p++;
    } while (pairs[++i][0] != SHORT_TABLE_END);
}

void initShortsHandleCompressedDiskReads(ShortsTableOwner* owner) {
    s32 i;
    u16(*pairs)[2];

    for (i = 0; i < SHORT_TABLE_COUNT; i++) {
        owner->order[i] = i;
    }

    swapShortPairsNonEmpty(owner, lbl_800EE960);

    switch (owner->charId) {
    case CHAR_ID_PARATROOPA_RED:
    case CHAR_ID_PARATROOPA_GREEN:
        pairs = lbl_803CB798;
        break;
    case CHAR_ID_PARAGOOMBA:
        pairs = lbl_800EE998;
        break;
    case CHAR_ID_BIRDO:
        pairs = lbl_803CB7A0;
        break;
    case CHAR_ID_SHYGUY_RED:
    case CHAR_ID_SHYGUY_BLUE:
    case CHAR_ID_SHYGUY_YELLOW:
    case CHAR_ID_SHYGUY_GREEN:
    case CHAR_ID_SHYGUY_BLACK:
        pairs = lbl_800EE9B0;
        break;
    default:
        pairs = NULL;
        break;
    }

    if (pairs != NULL) {
        swapShortPairs(owner, pairs);
    }
}
