#include "Unknown/File_0x80021ca4.h"
#include "Unknown/dvdsys.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80022634.h"
#include "game/match_setup/match_loading.h"

// 0x80021AC8-0x80022DAC: the character / stadium file-loading translation unit,
// one unit by its .data order (docs/splits.md, 2026-11-21): the former
// File_0x80021ca4.c and File_0x80022634.c plus unowned functions that have no
// C yet.

typedef void (*HandItemCallback)(void* src, void* dest, u32 key);

typedef struct HandItemLoad {
    /* 0x00 */ void* src;
    /* 0x04 */ void* dest;
    /* 0x08 */ s32 kind;
    /* 0x0C */ u32 param;
    /* 0x10 */ HandItemCallback callback;
    /* 0x14 */ u32 key;
} HandItemLoad;

typedef struct HandItemQueue {
    /* 0x000 */ HandItemLoad current;
    /* 0x018 */ HandItemLoad ring[18];
    /* 0x1C8 */ s8 head;
    /* 0x1C9 */ s8 tail;
    /* 0x1CA */ s8 busy;
    /* 0x1CB */ u8 _1CB[0x1DC - 0x1CB];
    /* 0x1DC */ u32* paramTable;
    /* 0x1E0 */ u8 _1E0[0x1E8 - 0x1E0];
    /* 0x1E8 */ u8 unk1E8;
    /* 0x1E9 */ u8 _1E9;
    /* 0x1EA */ u8 flags1EA;
} HandItemQueue;

extern u8 StadiumFiles[];
extern HandItemQueue lbl_803716B8;
extern void fn_8002244C(void* src, void* dest, u32 key);
extern void fn_80022620(void* src, void* dest, u32 key);

static inline u32 alignedSize(u32 word) {
    return ((word & 0x0FFFFFFF) + 0x1F) & ~0x1F;
}

void* loadCharacterHandItem(s32 charSlot, s32 part, void* dest) {
    MatchFileDescriptor* aramFiles = (MatchFileDescriptor*)(StadiumFiles + 0x150);
    MatchFileDescriptor* discFiles = (MatchFileDescriptor*)(StadiumFiles + 0x61B0);
    s8 handIdx;
    s32 aramA;
    s32 aramB;
    HandItemQueue* q;
    HandItemLoad* slot;
    s8 head;
    s8 next;

    if (charSlot < 0 || charSlot >= 0x36) {
        return NULL;
    }
    if (part < 0 || part >= 6) {
        return NULL;
    }

    handIdx = (s8)StadiumFiles[0x7854 + charSlot];
    aramA = charSlot * 7 + (s8)StadiumFiles[0x783C + handIdx * 12 + part * 2];
    aramB = charSlot * 7 + (s8)StadiumFiles[0x783C + handIdx * 12 + part * 2 + 1];

    if (dest == NULL) {
        dest = _OSAllocFromHeap(0x20, alignedSize(aramFiles[aramA + 0x36]._4) + alignedSize(aramFiles[aramB + 0x36]._4));
    }

    q = &lbl_803716B8;
    if (q->flags1EA & 2) {
        head = q->head;
        next = (head + 1) % 18;
        if (next != q->tail && (dest != NULL || fn_8002244C != NULL)) {
            q->busy = 1;
            slot = &q->ring[head];
            slot->src = &aramFiles[aramA + 0x36];
            slot->dest = dest;
            slot->kind = 3;
            slot->param = q->paramTable[aramA];
            slot->callback = fn_8002244C;
            slot->key = (aramA << 16) | aramB;
            q->head = next;
        }
    } else {
        head = q->head;
        next = (head + 1) % 18;
        if (next != q->tail && (dest != NULL || fn_80022620 != NULL)) {
            q->busy = 1;
            slot = &q->ring[head];
            slot->src = &discFiles[charSlot * 6 + part];
            slot->dest = dest;
            slot->kind = 0;
            slot->param = 0;
            slot->callback = fn_80022620;
            slot->key = 0;
            q->head = next;
        }
    }

    q->unk1E8 = 1;
    insertGraphicDrawingFunction(maybe_somethingAnimRelated, 0);

    if (q->busy != 0 && lbl_803C6CF8.cancel.bytes[1] == 1) {
        if (q->current.callback != NULL) {
            q->current.callback(q->current.src, q->current.dest, q->current.key);
        }
        if (q->tail != q->head) {
            slot = &q->ring[q->tail];
            slot->dest = ARAMTransfer(slot->src, (s32)slot->dest, slot->kind, slot->param);
            q->current = *slot;
            q->tail = (q->tail + 1) % 18;
        } else {
            q->current.callback = NULL;
            q->busy = 0;
        }
    }

    return dest;
}

#define ARAM_QUEUE_LEN 18

typedef void (*AramTransferCallback)(void* file, s32 dest, s32 userData);

typedef struct AramTransferRequest {
    /*0x00*/ void* file;
    /*0x04*/ s32 dest;
    /*0x08*/ s32 arg2;
    /*0x0C*/ s32 arg3;
    /*0x10*/ AramTransferCallback callback;
    /*0x14*/ s32 userData;
} AramTransferRequest;

/* File_0x80022634.c viewed lbl_803716B8 (declared above as HandItemQueue) as
 * its ARAM transfer queue. */
typedef struct {
    /*0x000*/ AramTransferRequest current;
    /*0x018*/ AramTransferRequest queue[ARAM_QUEUE_LEN];
    /*0x1C8*/ s8 tail;
    /*0x1C9*/ s8 head;
    /*0x1CA*/ s8 active;
    /*0x1CB*/ u8 _1CB[0x1E8 - 0x1CB];
    /*0x1E8*/ u8 unk1E8;
    /*0x1E9*/ u8 _1E9[0x578 - 0x1E9];
} AramQueue_80022634;
#define lbl_803716B8 (*(AramQueue_80022634*)&lbl_803716B8)

static inline BOOL advanceAramQueue(void) {
    AramTransferRequest* req;

    if (!lbl_803716B8.active) {
        return TRUE;
    }
    if (lbl_803C6CF8.cancel.bytes[1] != 1) {
        return FALSE;
    }
    if (lbl_803716B8.current.callback != NULL) {
        lbl_803716B8.current.callback(lbl_803716B8.current.file, lbl_803716B8.current.dest,
                                      lbl_803716B8.current.userData);
    }
    if (lbl_803716B8.head != lbl_803716B8.tail) {
        req = &lbl_803716B8.queue[lbl_803716B8.head];
        req->dest = (s32)ARAMTransfer(req->file, req->dest, req->arg2, req->arg3);
        lbl_803716B8.current = *req;
        lbl_803716B8.head = (lbl_803716B8.head + 1) % ARAM_QUEUE_LEN;
    } else {
        lbl_803716B8.current.callback = NULL;
        lbl_803716B8.active = FALSE;
        return TRUE;
    }
    return FALSE;
}

void maybe_somethingAnimRelated(void) {
    if (advanceAramQueue() && lbl_803716B8.unk1E8 == 0) {
        removeCurrentDrawingItem();
    }
}

#undef lbl_803716B8
