#include "Unknown/File_0x800aaee4.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/os.h"

/* This unit's view of the drawing-script node scratch area. */
typedef struct McardTaskNode {
    /* 0x00 */ u8 _00[0x2C];
    /* 0x2C */ u32 unk2C;
    /* 0x30 */ s32 saveSize;
    /* 0x34 */ u8 _34[4];
    /* 0x38 */ u8 slot;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
} McardTaskNode;

extern struct {
    /* 0x00 */ u8 _00[0x55];
    /* 0x55 */ u8 unk55;
} lbl_803C7838;

extern u64 lbl_802EF2C0[2];
extern u32 lbl_803CC158;
extern u32 lbl_803CC15C;
extern u32 lbl_803CC160;

void fn_800AAFEC(void);


void memoryCardRelatedFunction(McardSaveRequest* req, int arg1, u64 slotData) {
    McardTaskNode* node;
    u8 value;

    if (req->saveSize % 512 != 0) {
        OSPanic("mcard.c", 0x822, "MemoryCard SaveSize Error!!");
    }
    lbl_803C7838.unk55 = 1;
    node = (McardTaskNode*)insertGraphicDrawingFunction(fn_800AAFEC, 0xFF);
    node->slot = req->unk0C;
    node->unk39 = req->unk0D;
    node->unk2C = req->unk04;
    node->saveSize = req->saveSize;
    value = req->unk0E;
    if (value == 0) {
        value = 4;
    }
    node->unk3A = value;
    lbl_802EF2C0[node->slot] = slotData;
    lbl_803CC15C = req->unk10;
    lbl_803CC158 = req->unk14;
    lbl_803CC160 = req->unk18;
    currentDrawingItem->state = 0;
}
