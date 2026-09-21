#define SQRT2_LINKAGE static
#include "game/stadium/stadium_bowser_castle.h"
#include "header_rep_data.h"
#include "game/stadium/stadium_framework.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "Dolphin/gx.h"
#include "stl/math.h"
#include "Dolphin/rand.h"
#include "game/math/game_math.h"
#include "game/ball/collision_primitives.h"
#include "Dolphin/mtxext.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Dolphin/stl.h"
#include "C3/control.h"
#include "Dolphin/os.h"
#include "game/fielding/fielder.h"
#include "Unknown/File_0x800b4b38.h"
#include "text/text_channel.h"
#include "Unknown/File_0x80025ddc.h"
#include "Unknown/File_0x80033794.h"
#include "Unknown/File_0x8004c094.h"
#include "Unknown/File_0x800b4bc8.h"
#include "Unknown/File_0x80034cec.h"
#include "game/stadium/rep_23E8.h"
#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"
#include "game/ball/ball_physics.h"
#include "game/sound/m_sound.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x80025c58.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"

typedef struct _CastleMaterialFlags {
    /*0x00*/ u8 _00[4];
    /*0x04*/ u32 animState;
    /*0x08*/ u8 _08[0x74 - 0x08];
    /*0x74*/ u32 flags;
} CastleMaterialFlags;

typedef struct _CastleModelLevel4 {
    /*0x00*/ u8 _00[4];
    /*0x04*/ CastleMaterialFlags* next;
} CastleModelLevel4;

typedef struct _CastleModelLevel3 {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ CastleModelLevel4* next;
} CastleModelLevel3;

typedef struct _CastleModelLevel2 {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ CastleModelLevel3* next;
} CastleModelLevel2;

typedef struct _CastleModelLevel1 {
    /*0x00*/ u8 _00[4];
    /*0x04*/ CastleModelLevel2* flameMat;
    /*0x08*/ u8 _08[0x34 - 0x08];
    /*0x34*/ CastleModelLevel2* thwompMat;
} CastleModelLevel1;

typedef struct _CastleModelRoot {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ CastleModelLevel1* next;
} CastleModelRoot;

typedef struct _CastleHazardObj {
    /*0x00*/ u8 _00[0xA9];
    /*0xA9*/ u8 hazardType;
    /*0xAA*/ u8 _AA[0xB0 - 0xAA];
    /*0xB0*/ u8 hasBounced;
} CastleHazardObj;

static u8 lbl_3_bss_9D82;
static u32 lbl_3_bss_9D84;
static u32 lbl_3_bss_9D98;
static u32 lbl_3_bss_9D9C;
static u8 lbl_3_bss_9DE7;

// .text:0x000C1964 size:0x10 mapped:0x807009F8
void fn_3_C1964(void) {
    lbl_3_bss_9D9C = 1;
}

// .text:0x000C1974 size:0x54 mapped:0x80700A08
void fn_3_C1974(int offset) {
    DrawingSceneStruct* item = insertGraphicDrawingFunction(fn_3_C2644, 4);
    item->state = 0;
    lbl_3_bss_9D98 = offset + 0x3C4;
    lbl_3_bss_9D9C = 0;
}

// .text:0x000C19C8 size:0x250 mapped:0x80700A5C
void fn_3_C19C8(void) {
    return;
}

// .text:0x000C1C18 size:0x62C mapped:0x80700CAC
void fn_3_C1C18(void) {
    return;
}

// .text:0x000C2244 size:0xCC mapped:0x807012D8
void fn_3_C2244(void) {
    return;
}

// .text:0x000C2310 size:0xD0 mapped:0x807013A4
void fn_3_C2310(void) {
    return;
}

// .text:0x000C23E0 size:0xC0 mapped:0x80701474
void fn_3_C23E0(void) {
    return;
}

// .text:0x000C24A0 size:0x1A4 mapped:0x80701534
void fn_3_C24A0(void) {
    return;
}

// .text:0x000C2644 size:0x330 mapped:0x807016D8
void fn_3_C2644(void) {
    return;
}

// .text:0x000C2974 size:0x18 mapped:0x80701A08
void fn_3_C2974(void) {
    lbl_3_bss_9DE7 = 1;
    lbl_3_bss_9D82 = 1;
}

// .text:0x000C298C size:0x114 mapped:0x80701A20
void fn_3_C298C(void) {
    return;
}

// .text:0x000C2AA0 size:0x1E0 mapped:0x80701B34
void fn_3_C2AA0(void) {
    return;
}

// .text:0x000C2C80 size:0x25C mapped:0x80701D14
void fn_3_C2C80(void) {
    return;
}

// .text:0x000C2EDC size:0x214 mapped:0x80701F70
void fn_3_C2EDC(void) {
    return;
}

// .text:0x000C30F0 size:0x57C mapped:0x80702184
void fn_3_C30F0(void) {
    return;
}

// .text:0x000C366C size:0x35C mapped:0x80702700
void fn_3_C366C(void* handle, u8 idx) {
    return;
}

// .text:0x000C39C8 size:0x70 mapped:0x80702A5C
void bowserCastleSomething(void) {
    u32 i;

    for (i = 0; i < 6; i++) {
        void* handle = allocParticleEffect(fn_3_C30F0, 0x80, 0, 0x15, TRUE, 0);
        if (handle != NULL) {
            fn_3_C366C(handle, i);
        }
    }
}

// .text:0x000C3A38 size:0x1F4 mapped:0x80702ACC
void thwomp_screenShake(void) {
    return;
}

// .text:0x000C3C2C size:0x268 mapped:0x80702CC0
void fn_3_C3C2C(void) {
    return;
}

// .text:0x000C3E94 size:0xDC mapped:0x80702F28
void fn_3_C3E94(void) {
    return;
}

// .text:0x000C3F70 size:0xF8 mapped:0x80703004
void fn_3_C3F70(void) {
    return;
}

// .text:0x000C4068 size:0x84 mapped:0x807030FC
void fn_3_C4068(StadiumObject* obj) {
    CastleModelRoot* root = (CastleModelRoot*)obj->model->root;
    CastleMaterialFlags* mat = root->next->flameMat->next->next->next;
    u16 value = mat->animState & 0x1FFF;

    if (lbl_3_bss_9D84++ > 4) {
        value++;
        if (value > 0x13) {
            value = 4;
        }
        lbl_3_bss_9D84 = 0;
    }
    mat->animState &= ~0x1FFF;
    mat->animState |= value;
}

// .text:0x000C40EC size:0x60 mapped:0x80703180
void fn_3_C40EC(StadiumObject* obj) {
    CastleModelRoot* root = (CastleModelRoot*)obj->model->root;
    CastleMaterialFlags* mat = root->next->flameMat->next->next->next;

    if (((CastleHazardObj*)obj)->hazardType != 6) {
        mat->animState &= ~0x1FFF;
        mat->animState |= 0x19;
    } else {
        mat->animState &= ~0x1FFF;
        mat->animState |= 0x1A;
    }
}

// .text:0x000C414C size:0x158 mapped:0x807031E0
void bowserCastleStarPadsContaactFn(void) {
    return;
}

// .text:0x000C42A4 size:0x1A8 mapped:0x80703338
void stadiumObjCollision_Castle(void) {
    return;
}

// .text:0x000C444C size:0x2D8 mapped:0x807034E0
void fn_3_C444C(void) {
    return;
}

// .text:0x000C4724 size:0x1AC mapped:0x807037B8
void fn_3_C4724(void) {
    return;
}

// .text:0x000C48D0 size:0x2B0 mapped:0x80703964
void fn_3_C48D0(void) {
    return;
}

// .text:0x000C4B80 size:0x174 mapped:0x80703C14
void fn_3_C4B80(void) {
    return;
}

// .text:0x000C4CF4 size:0x20C mapped:0x80703D88
void fn_3_C4CF4(void) {
    return;
}

// .text:0x000C4F00 size:0x404 mapped:0x80703F94
void fn_3_C4F00(void) {
    return;
}

// .text:0x000C5304 size:0x1CC mapped:0x80704398
void fn_3_C5304(void) {
    return;
}

// .text:0x000C54D0 size:0x218 mapped:0x80704564
void fn_3_C54D0(void) {
    return;
}

// .text:0x000C56E8 size:0x294 mapped:0x8070477C
void fn_3_C56E8(void) {
    return;
}

// .text:0x000C597C size:0x364 mapped:0x80704A10
void fn_3_C597C(void) {
    return;
}

// .text:0x000C5CE0 size:0xFC mapped:0x80704D74
void castleFireballMaybe(void) {
    return;
}

// .text:0x000C5DDC size:0x480 mapped:0x80704E70
void bowserCastleRelated(void) {
    return;
}

// .text:0x000C625C size:0x174 mapped:0x807052F0
void fn_3_C625C(void) {
    return;
}

// .text:0x000C63D0 size:0xDFC mapped:0x80705464
void flameControl(void) {
    return;
}

// .text:0x000C71CC size:0x278 mapped:0x80706260
void stadiumObjRelated_Castle(void) {
    return;
}

// .text:0x000C7444 size:0x58 mapped:0x807064D8
void fn_3_C7444(StadiumObject* obj) {
    CastleModelRoot* root = (CastleModelRoot*)obj->model->root;
    CastleMaterialFlags* mat = root->next->thwompMat->next->next->next;
    BOOL hasBounced = ((CastleHazardObj*)obj)->hasBounced;

    switch (hasBounced) {
    case 0:
        mat->animState &= ~0x1FFF;
        mat->animState |= 2;
        break;
    default:
        mat->animState &= ~0x1FFF;
        break;
    }
}

// .text:0x000C749C size:0x11C mapped:0x80706530
void thwomp_bounceOffSoundAndVisualFx(void) {
    return;
}

// .text:0x000C75B8 size:0x1F4 mapped:0x8070664C
void thwomp_smokeRelated(void) {
    return;
}

// .text:0x000C77AC size:0x260 mapped:0x80706840
void fn_3_C77AC(void) {
    return;
}

// .text:0x000C7A0C size:0x650 mapped:0x80706AA0
void thwomp_slamControl(void) {
    return;
}

// .text:0x000C805C size:0x1E0 mapped:0x807070F0
void fn_3_C805C(void) {
    return;
}

// .text:0x000C823C size:0x78 mapped:0x807072D0
TriangleGroup* fn_3_C823C(int offset, Mtx m) {
    StadiumObject* obj = &stadiumObjectCollision.objects[offset];

    CTRLBuildMatrix((Control*)obj, m);
    if (((CastleHazardObj*)obj)->hazardType == 5) {
        m[1][3] = 0.002f;
    }
    return stadiumObjectCollision.objects[offset].triangles;
}

// .text:0x000C82B4 size:0x39C mapped:0x80707348
void fn_3_C82B4(void) {
    return;
}

// .text:0x000C8650 size:0xD2C mapped:0x807076E4
void loadBowserCastle(void) {
    return;
}

