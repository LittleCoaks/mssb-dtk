#ifndef __HUGE_ANIM_STRUCT_H_
#define __HUGE_ANIM_STRUCT_H_

#include "mssbTypes.h"
#include "Unknown/File_0x800bdd74.h"

/*
 * hugeAnimStruct (DOL .bss 0x8036E548, size 0x3154): the actor / model /
 * animation bookkeeping block shared by the DOL and every REL.
 *
 * This is the one definition. Do not declare a per-file view of it: include
 * this header and name the member. Offsets and sizes are cross-checked against
 * symbols.txt and Ghidra's layout; a member only has a real name where a use
 * in the tree supports one, otherwise it keeps its offset.
 *
 * Several members are deliberately untyped (`void*`, `u8[]`) because the files
 * that use them still each have a private struct for what they point at. The
 * big one is the 0x27C-byte animation object behind `pool` / `objects`. Until
 * those are unified in their own right, a file casts at the point of use,
 * normally through one local accessor macro, e.g.
 *
 *     #define ANIM_OBJ(i) ((AnimObject*)hugeAnimStruct.objects[i])
 */

#define HUGE_ANIM_OBJECT_COUNT 13
#define HUGE_ANIM_OBJECT_SIZE 0x27C
#define HUGE_ANIM_ACTOR_TABLE_COUNT 7
#define HUGE_ANIM_LIGHT_COUNT 4
#define HUGE_ANIM_BANK_COUNT 16
#define HUGE_ANIM_LOAD_SLOT_COUNT 3
#define HUGE_ANIM_MODEL_SOURCE_COUNT 60

/* One of the three records at +0x2D3C. */
typedef struct HugeAnimLoadSlot {
    /*0x0*/ void* _0;
    /*0x4*/ u32 _4;
    /*0x8*/ s16 _8;
    /*0xA*/ u8 state;
    /*0xB*/ u8 _B;
} HugeAnimLoadSlot; // size: 0xC

/* One record of the loaded-file table at +0x2DA0. */
typedef struct HugeAnimModelSource {
    /*0x0*/ void* layout;
    /*0x4*/ void* geometry;
    /*0x8*/ void* texture;
} HugeAnimModelSource; // size: 0xC

typedef struct HugeAnimStruct {
    /*0x0000*/ s32 _0000;
    /*0x0004*/ void* stadiumFileHeader;
    /*0x0008*/ void* stadiumObjectLoading;
    /*0x000C*/ s32 _000C[21];
    /* Actor object tables, one per category of thing drawn. [0] holds the
     * characters, [2] the minigame / practice models, [3] the stadium objects. */
    /*0x0060*/ ActorObjectTable* actorTables[HUGE_ANIM_ACTOR_TABLE_COUNT];
    /*0x007C*/ u8 _007C[0xAC - 0x7C];
    /*0x00AC*/ void* lights[HUGE_ANIM_LIGHT_COUNT];
    /*0x00BC*/ s32 _00BC[21];
    /*0x0110*/ s32 _0110;
    /*0x0114*/ u8 _0114[0x13C - 0x114];
    /*0x013C*/ void* _013C;
    /*0x0140*/ u8 _0140[0xC04 - 0x140];
    /* The animation objects themselves, and a pointer to each. */
    /*0x0C04*/ u8 pool[HUGE_ANIM_OBJECT_COUNT][HUGE_ANIM_OBJECT_SIZE];
    /*0x2C50*/ void* objects[HUGE_ANIM_OBJECT_COUNT];
    /*0x2C84*/ void* actLayout;
    /*0x2C88*/ void* animBank;
    /*0x2C8C*/ void* modelData;
    /*0x2C90*/ u32 _2C90;
    /*0x2C94*/ s32 _2C94[6];
    /*0x2CAC*/ void* animBanks[HUGE_ANIM_BANK_COUNT];
    /*0x2CEC*/ s32 _2CEC[20];
    /*0x2D3C*/ HugeAnimLoadSlot loadSlots[HUGE_ANIM_LOAD_SLOT_COUNT];
    /*0x2D60*/ s32 _2D60;
    /*0x2D64*/ u32 _2D64;
    /*0x2D68*/ s16 _2D68;
    /* Byte flags at +0x2D6A .. +0x2D8F; index with HUGE_ANIM_FLAG(offset). */
    /*0x2D6A*/ u8 flags[0x2D90 - 0x2D6A];
    /*0x2D90*/ void* starAnimRelated;
    /*0x2D94*/ void* actorEntries;
    /*0x2D98*/ s32 _2D98;
    /*0x2D9C*/ u32* archive;
    /*0x2DA0*/ HugeAnimModelSource sources[HUGE_ANIM_MODEL_SOURCE_COUNT];
    /*0x3070*/ void (*hookA)(void);
    /*0x3074*/ void (*hookB)(void);
    /*0x3078*/ u16 actorCount;
    /*0x307A*/ u8 _307A;
    /*0x307B*/ u8 _307B;
    /*0x307C*/ u8 _307C;
    /*0x307D*/ u8 _307D;
    /*0x307E*/ u8 _307E;
    /*0x307F*/ u8 _307F;
    /*0x3080*/ u8 _3080;
    /*0x3081*/ u8 _3081;
    /*0x3082*/ u8 _3082;
    /*0x3083*/ u8 _3083;
    /*0x3084*/ u8 _3084;
    /*0x3085*/ u8 _3085;
    /*0x3086*/ u8 _3086;
    /*0x3087*/ u8 _3087;
    /*0x3088*/ u8 _3088;
    /*0x3089*/ u8 _3089[3];
    /*0x308C*/ s32 _308C;
    /*0x3090*/ u8 _3090[0x3154 - 0x3090];
} HugeAnimStruct; // size: 0x3154

extern HugeAnimStruct hugeAnimStruct;

/* The byte flag at absolute offset `offset` (0x2D6A .. 0x2D8F). */
#define HUGE_ANIM_FLAG(offset) (hugeAnimStruct.flags[(offset) - 0x2D6A])
/* Runners are not drawn while this is set. */
#define HUGE_ANIM_HIDE_RUNNERS HUGE_ANIM_FLAG(0x2D77)

#endif // __HUGE_ANIM_STRUCT_H_
