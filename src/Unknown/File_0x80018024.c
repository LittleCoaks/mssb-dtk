#include "Unknown/File_0x80018024.h"
#include "Unknown/File_0x800acf14.h"
#include "static/UnknownHomes_Static.h"

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x04];
    /*0x04*/ u32 _04;
    /*0x08*/ u8 _08[0x08];
} CompressedFileEntry;

extern CompressedFileEntry* lbl_803CB790;

typedef struct AnimModelMemory {
    /*0x0000*/ u8 _0000[0x0C0C];
    /*0x0C0C*/ u8* _0C0C;
    /*0x0C10*/ u8* _0C10;
    /*0x0C14*/ u8 _0C14[0x0C30 - 0x0C14];
    /*0x0C30*/ u8* _0C30;
    /*0x0C34*/ u8* _0C34;
    /*0x0C38*/ u8 _0C38[0x0E88 - 0x0C38];
    /*0x0E88*/ u8* _0E88;
    /*0x0E8C*/ u8* _0E8C;
    /*0x0E90*/ u8 _0E90[0x0EAC - 0x0E90];
    /*0x0EAC*/ u8* _0EAC;
    /*0x0EB0*/ u8* _0EB0;
    /*0x0EB4*/ u8 _0EB4[0x1104 - 0x0EB4];
    /*0x1104*/ u8* _1104;
    /*0x1108*/ u8* _1108;
    /*0x110C*/ u8 _110C[0x1128 - 0x110C];
    /*0x1128*/ u8* _1128;
    /*0x112C*/ u8* _112C;
    /*0x1130*/ u8 _1130[0x1380 - 0x1130];
    /*0x1380*/ u8* _1380;
    /*0x1384*/ u8* _1384;
    /*0x1388*/ u8 _1388[0x13A4 - 0x1388];
    /*0x13A4*/ u8* _13A4;
    /*0x13A8*/ u8* _13A8;
    /*0x13AC*/ u8 _13AC[0x1620 - 0x13AC];
    /*0x1620*/ u8* _1620;
    /*0x1624*/ u8* _1624;
    /*0x1628*/ u8 _1628[0x189C - 0x1628];
    /*0x189C*/ u8* _189C;
    /*0x18A0*/ u8* _18A0;
    /*0x18A4*/ u8 _18A4[0x1B18 - 0x18A4];
    /*0x1B18*/ u8* _1B18;
    /*0x1B1C*/ u8* _1B1C;
    /*0x1B20*/ u8 _1B20[0x1D94 - 0x1B20];
    /*0x1D94*/ u8* _1D94;
    /*0x1D98*/ u8* _1D98;
    /*0x1D9C*/ u8 _1D9C[0x2C8C - 0x1D9C];
    /*0x2C8C*/ u8* _2C8C;
    /*0x2C90*/ u8 _2C90[0x2D64 - 0x2C90];
    /*0x2D64*/ u32 _2D64;
} AnimModelMemory;

extern AnimModelMemory hugeAnimStruct;

void setupAnimationModelMemory(void) {
    s32 i;
    s32 entry;
    u32 maxA;
    u32 maxB;
    u32 v;
    u32 sizeA;
    u32 sizeB;
    u8* p;

    maxA = 0;
    maxB = 0;
    entry = 0;
    p = (u8*)lbl_803CB790;
    for (i = 0; i < 18; i++) {
        v = ((CompressedFileEntry*)p)[0]._04 & 0x0FFFFFFF;
        if (maxA < v) {
            maxA = v;
        }
        v = ((CompressedFileEntry*)p)[1]._04 & 0x0FFFFFFF;
        if (maxB < v) {
            maxB = v;
        }
        v = ((CompressedFileEntry*)p)[19]._04 & 0x0FFFFFFF;
        if (maxA < v) {
            maxA = v;
        }
        v = ((CompressedFileEntry*)p)[20]._04 & 0x0FFFFFFF;
        if (maxB < v) {
            maxB = v;
        }
        v = ((CompressedFileEntry*)p)[38]._04 & 0x0FFFFFFF;
        if (maxA < v) {
            maxA = v;
        }
        v = ((CompressedFileEntry*)p)[39]._04 & 0x0FFFFFFF;
        if (maxB < v) {
            maxB = v;
        }
        p += 57 * 16;
    }

    sizeA = (maxA + 0x1F) & ~0x1F;
    sizeB = (maxB + 0x1F) & ~0x1F;
    hugeAnimStruct._2D64 = sizeA;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        hugeAnimStruct._2C8C = _OSAllocFromHeap(0x20, (sizeA + sizeB) * 4);
    } else {
        hugeAnimStruct._2C8C = _OSAllocFromHeap(0x20, sizeA * 4);
    }

    p = hugeAnimStruct._2C8C;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        hugeAnimStruct._0C0C = p;
        p += sizeA;
        hugeAnimStruct._0C30 = 0;
        hugeAnimStruct._0C34 = 0;
        hugeAnimStruct._0C10 = p;
        p += sizeB;
        hugeAnimStruct._1620 = 0;
        hugeAnimStruct._1624 = 0;
        hugeAnimStruct._0E88 = p;
        p += sizeA;
        hugeAnimStruct._0EAC = 0;
        hugeAnimStruct._0EB0 = 0;
        hugeAnimStruct._0E8C = p;
        p += sizeB;
        hugeAnimStruct._189C = 0;
        hugeAnimStruct._18A0 = 0;
        hugeAnimStruct._1104 = p;
        p += sizeA;
        hugeAnimStruct._1128 = 0;
        hugeAnimStruct._112C = 0;
        hugeAnimStruct._1108 = p;
        p += sizeB;
        hugeAnimStruct._1B18 = 0;
        hugeAnimStruct._1B1C = 0;
        hugeAnimStruct._1380 = p;
        p += sizeA;
        hugeAnimStruct._13A4 = 0;
        hugeAnimStruct._13A8 = 0;
        hugeAnimStruct._1384 = p;
        hugeAnimStruct._1D94 = 0;
        hugeAnimStruct._1D98 = 0;
    } else {
        hugeAnimStruct._0C0C = p;
        p += sizeA;
        hugeAnimStruct._0C30 = 0;
        hugeAnimStruct._0C34 = 0;
        hugeAnimStruct._0E88 = p;
        p += sizeA;
        hugeAnimStruct._0EAC = 0;
        hugeAnimStruct._0EB0 = 0;
        hugeAnimStruct._1104 = p;
        p += sizeA;
        hugeAnimStruct._1128 = 0;
        hugeAnimStruct._112C = 0;
        hugeAnimStruct._1380 = p;
        hugeAnimStruct._13A4 = 0;
        hugeAnimStruct._13A8 = 0;
    }
}
