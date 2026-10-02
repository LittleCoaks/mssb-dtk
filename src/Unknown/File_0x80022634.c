#include "Unknown/File_0x80022634.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800b0a14.h"

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

extern struct {
    /*0x000*/ AramTransferRequest current;
    /*0x018*/ AramTransferRequest queue[ARAM_QUEUE_LEN];
    /*0x1C8*/ s8 tail;
    /*0x1C9*/ s8 head;
    /*0x1CA*/ s8 active;
    /*0x1CB*/ u8 _1CB[0x1E8 - 0x1CB];
    /*0x1E8*/ u8 unk1E8;
    /*0x1E9*/ u8 _1E9[0x578 - 0x1E9];
} lbl_803716B8;

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
