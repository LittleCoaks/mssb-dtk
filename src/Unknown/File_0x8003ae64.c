#include "Unknown/File_0x8003ae64.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/mcard.h"
#include "Dolphin/ar.h"
#include "Dolphin/os.h"
#include "string.h"
#include "text/text.h"

/* Scene node used by the memory-card drawing script (currentDrawingItem). */
typedef struct SceneNode {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ struct SceneNode* prev;
    /* 0x08 */ struct SceneNode* next;
    /* 0x0C */ struct SceneNode* parent;
    /* 0x10 */ s16 state;
    /* 0x12 */ u16 priority;
    /* 0x14 */ u8 step;
    /* 0x15 */ u8 slot;
    /* 0x16 */ u8 arg16;
    /* 0x17 */ u8 chan;
    /* 0x18 */ u8 flag18;
    /* 0x19 */ u8 _19;
    /* 0x1A */ u8 mode1A;
    /* 0x1B */ u8 mode1B;
    /* 0x1C */ u8 result1C;
    /* 0x1D */ u8 flag1D;
    /* 0x1E */ u8 flag1E;
    /* 0x1F */ u8 _1F;
    /* 0x20 */ u8 idx20;
    /* 0x21 */ u8 _21;
} SceneNode;

/* Mirror of McardState (private to mcard.c). */
typedef struct SceneMcardChannel {
    /* 0x00 */ u64 serialNo;
    /* 0x08 */ s32 probeResult;
    /* 0x0C */ s32 memSize;
    /* 0x10 */ s32 sectorSize;
    /* 0x14 */ s32 freeBlocks;
    /* 0x18 */ s32 freeBytes;
    /* 0x1C */ s32 freeFiles;
    /* 0x20 */ s32 userBlocks;
    /* 0x24 */ u8 _24[4];
} SceneMcardChannel;

typedef struct SceneMcardState {
    /* 0x00 */ SceneMcardChannel chan[2];
    /* 0x50 */ s32 result;
    /* 0x54 */ u8 status;
    /* 0x55 */ u8 operation;
    /* 0x56 */ u8 hasBanner;
    /* 0x57 */ u8 iconCount;
    /* 0x58 */ s32 bytesTransferred;
    /* 0x5C */ u8 progress;
    /* 0x5D */ u8 _5D[3];
} SceneMcardState;

extern SceneMcardState mcardState;
extern u8 cardCheck[0x5C];
extern u8 lbl_802D4B00[0x10000];
extern u8 lbl_80354768[0xCF64];
extern u8 lbl_80366158[0x30];
extern u8 lbl_800F7B00[0x32A0];
extern u8 lbl_803616CC[0x454];
extern u8 superstarUnlocked[0x130];
extern u8 audioFileDescriptors[0x39C];
extern u8 g_d_GameSettings[0x58];
extern u8 g_Challenge[0x4508];
extern u64 lbl_802D4AE0[4];
extern ARQRequest lbl_802D4AC0;
extern u16 lbl_803CB830[4];
extern u32 lbl_803CBCB8;
extern u32 lbl_803CBCBC;
extern u32 lbl_803CBC48;
extern u32 lbl_803CBC4C;
extern u32 lbl_803CBC50;
extern const char lbl_800E6910[];

void fn_8004A34C(void* base, u32 slot, u32 msg, u32 a, u32 b);
void fn_800415A0(u32 arg);
u32 fn_8004157C(void);
u8 fn_80041348(void);
void fn_80041150(u32 a, u32 b);
void fn_8003E8D8(void);
u32 fn_800A6418(u32 size);
void fn_800A63C8(void);
u32 fn_80040FE0(void* buffer, s32 size, u32 arg);
void mcardCheckSpace(u8 chan, u8 async, s16 blocksNeeded, const char* fileName, u64 serialNo);
void mcardStartProbe(void);
void mcardStopProbe(void);
void fn_8003F2B8(void);
void fn_8004053C(void);
void fn_80040C14(void);
void fn_80041150(u32 a, u32 b);
void fn_8003AE64(u32 task);
u8 fn_8003AE70(s32 which);
#define MCARD_STATUS_FROM_PROBE(probe, status)    \
    do {                                          \
        if ((probe) == -1) {                      \
            (status) = 0xF;                       \
        } else if ((probe) >= 0) {                \
            (status) = ((probe) < 1) ? 0x11 : -1; \
        } else if ((probe) == -3) {               \
            (status) = 0;                         \
        } else if ((probe) > -3) {                \
            (status) = 4;                         \
        } else {                                  \
            (status) = -1;                        \
        }                                         \
    } while (0)

void fn_8003AE64(u32 task) {
    lbl_803CBCB8 = 0;
}

u8 fn_8003AE70(s32 which) {
    u8 value = 0;

    switch (which) {
    case 0:
        value = lbl_802D4B00[0x95];
        break;
    case 1:
        value = lbl_802D4B00[0x94];
        break;
    case 2:
        value = lbl_802D4B00[0x96];
        break;
    }
    return value;
}

void fn_8003AECC(void) {
    SceneNode* node = (SceneNode*)currentDrawingItem;
    SceneNode* newNode;
    s32 probe;
    s32 status;
    u8 s21;
    u8 s1B;
    u8 s1A;
    u8 sChan;
    u8 s16v;
    u8 sSlot;

    probe = mcardState.chan[node->chan].probeResult;
    if (probe == -1) {
        status = 0xF;
    } else if (probe >= 0) {
        status = (probe < 1) ? 0x11 : -1;
    } else if (probe == -3) {
        status = 0;
    } else if (probe > -3) {
        status = 4;
    } else {
        status = -1;
    }
    if (status == 4 || status == 0x11) {
        node->flag1E = 1;
    } else if (status == 0) {
        node->flag1D = 1;
    }

    switch (node->step) {
    case 0:
        mcardStartProbe();
        node->step = 1;
        break;
    case 1:
        node->flag1D = 0;
        s21 = node->_21;
        s1B = node->mode1B;
        s1A = node->mode1A;
        sChan = node->chan;
        s16v = node->arg16;
        sSlot = node->slot;
        newNode = (SceneNode*)insertGraphicDrawingFunction(fn_8004053C, 0x8000);
        newNode->step = 0;
        newNode->slot = sSlot;
        newNode->arg16 = s16v;
        newNode->chan = sChan;
        newNode->flag18 = 1;
        newNode->mode1A = s1A;
        newNode->mode1B = s1B;
        newNode->flag1D = 0;
        newNode->_21 = s21;
        ((SceneNode*)currentDrawingItem)->state = 0;
        node->step++;
        break;
    case 2:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            node->flag1D = 0;
            switch (((SceneNode*)currentDrawingItem)->state) {
            case 1:
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                fn_8004A34C(cardCheck, node->slot, 0x1E, 0, 0);
                node->step = 8;
                break;
            case 6:
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                node->step = 5;
                break;
            case 7:
                node->step = 0xD;
                node->result1C = 0xC;
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                break;
            case 9:
                lbl_802D4AE0[node->chan] = 0;
                node->step = 3;
                break;
            case 10:
                node->step = 0xD;
                node->result1C = 0xC;
                lbl_802D4AE0[node->chan] = 0;
                break;
            }
        }
        break;
    case 3:
        fn_8004A34C(cardCheck, node->slot, 1, 0, 0);
        fn_800415A0(0x46);
        node->flag1D = 0;
        node->flag1E = 0;
        lbl_802D4AE0[node->chan] = 0;
        node->step++;
        break;
    case 4:
        if (node->flag1E) {
            if (((SceneNode*)currentDrawingItem)->state != 0) {
                node->step = 0xD;
                node->result1C = 2;
            }
        } else if (((SceneNode*)currentDrawingItem)->state != 0) {
            node->step = 0xD;
            node->result1C = 2;
        }
        break;
    case 5:
        if (node->flag1D) {
            node->step = 3;
        } else {
            fn_8004A34C(cardCheck, node->slot, 0x10, 0, 0);
            fn_800415A0(0xB4);
            node->step++;
        }
        break;
    case 6:
        if ((u16)fn_8004157C() != 0) {
            break;
        }
        newNode = (SceneNode*)insertGraphicDrawingFunction(fn_80040C14, 0x8000);
        newNode->step = 0;
        newNode->slot = node->slot;
        newNode->arg16 = node->arg16;
        newNode->chan = node->chan;
        newNode->flag18 = node->flag18;
        newNode->mode1A = node->mode1A;
        newNode->flag1D = 0;
        newNode->idx20 = node->idx20;
        newNode->mode1B = node->mode1B;
        ((SceneNode*)currentDrawingItem)->state = 0;
        node->step++;
        break;
    case 7:
        switch (((SceneNode*)currentDrawingItem)->state) {
        case 1:
            fn_80041150(node->mode1B, node->idx20);
            node->result1C = 1;
            node->step = 0xC;
            break;
        case 9:
            fn_8004A34C(cardCheck, node->slot, 0x21, 0, 0);
            fn_800415A0(0x46);
            node->flag1D = 1;
            node->step = 8;
            lbl_802D4AE0[node->chan] = 0;
            break;
        case 2:
        case 8:
            fn_8004A34C(cardCheck, node->slot, 0x21, 0, 0);
            fn_800415A0(0x46);
            node->step = 8;
            lbl_802D4AE0[node->chan] = 0;
            break;
        case 4:
            fn_8004A34C(cardCheck, node->slot, 0x25, 0, 0);
            fn_800415A0(0x46);
            node->step = 8;
            break;
        }
        break;
    case 8:
        if ((u16)fn_8004157C() == 0) {
            node->flag1E = 0;
            node->step++;
        }
        break;
    case 9:
        if (node->flag1D) {
            if (node->flag1E) {
                if (((SceneNode*)currentDrawingItem)->state != 0) {
                    node->step = 1;
                    lbl_802D4AE0[node->chan] = 0;
                }
            } else if (((SceneNode*)currentDrawingItem)->state != 0) {
                node->step = 0xD;
                node->result1C = 0xC;
            }
        } else {
            node->step = 0xD;
            node->result1C = 0xC;
        }
        break;
    case 10:
        node->flag1E = 0;
        node->step = 0xB;
    case 11:
        if (node->flag1D) {
            if (node->flag1E) {
                if (((SceneNode*)currentDrawingItem)->state != 0) {
                    node->step = 0xD;
                }
            } else if (((SceneNode*)currentDrawingItem)->state != 0) {
                node->step = 0xD;
            }
        } else if (((SceneNode*)currentDrawingItem)->state != 0) {
            node->step = 0xD;
        }
        break;
    case 12:
        node->step = 0xD;
        break;
    case 13:
        mcardStopProbe();
        node->step++;
        break;
    case 14:
        ((SceneNode*)currentDrawingItem)->parent->state = node->result1C;
        text_freeAllBlocks();
        removeCurrentDrawingItem();
        break;
    }
}

void fn_8003B5B0(void) {
    SceneNode* node = (SceneNode*)currentDrawingItem;
    McardRequest req;
    OSCalendarTime calTime;
    s32 probe;
    s32 status;
    u32 bits;

    probe = mcardState.chan[node->chan].probeResult;
    if (probe == -1) {
        status = 0xF;
    } else if (probe >= 0) {
        status = (probe < 1) ? 0x11 : -1;
    } else if (probe == -3) {
        status = 0;
    } else if (probe > -3) {
        status = 4;
    } else {
        status = -1;
    }
    if (status == 4 || status == 0x11) {
        node->flag1E = 1;
    } else if (status == 0) {
        node->flag1D = 1;
    }

    switch (node->step) {
    case 0:
        node->flag1E = 0;
        node->flag1D = 0;
        node->step = 1;
        break;
    case 1:
        mcardCheckSpace(node->chan, node->flag18, (s16)lbl_803CBC48, lbl_800E6910, lbl_802D4AE0[node->chan]);
        node->step++;
        break;
    case 2:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            if (node->flag1D) {
                node->step = 0xA;
            } else {
                switch (mcardState.status) {
                case 5:
                    fn_8004A34C(cardCheck, node->slot, 0xE, 0, 0);
                    node->step++;
                    break;
                case 6:
                    fn_8004A34C(cardCheck, node->slot, 0xF, 0, 0);
                    node->step++;
                    break;
                case 0x10:
                    node->step = 0xE;
                    break;
                case 0x11:
                    node->step = 5;
                    break;
                case 3:
                case 0xD:
                    node->step = 0xC;
                    break;
                default:
                    node->step = 0xA;
                    break;
                }
            }
        }
        break;
    case 3:
        if (node->flag1D) {
            if (cardCheck[0x45] != 0) {
                node->step = 0x10;
                node->result1C = 9;
            }
        } else {
            switch (cardCheck[0x45]) {
            case 2:
                lbl_80366158[0x21] = 1;
                node->step = 4;
                break;
            case 1:
            case 3:
            case 4:
                node->step = 0x10;
                node->result1C = 2;
                break;
            }
        }
        break;
    case 5:
        if (node->flag1D) {
            node->step = 0xA;
        } else {
            fn_8004A34C(cardCheck, node->slot, 0xC, 0, 0);
            fn_800415A0(0x32);
            node->step++;
        }
        break;
    case 6:
        if ((u16)fn_8004157C() != 0) {
            break;
        }
        OSTicksToCalendarTime(OSGetTime(), &calTime);
        processBannerImage(lbl_800E6910, lbl_800F7B00 + 0x23C0, lbl_803CBC4C, lbl_800F7B00 + 0x40, lbl_803CBC50, 3, 0,
                           (const char*)(lbl_800F7B00 + 0x3280), (const char*)(lbl_800F7B00 + 0x3240), lbl_803CBC48);
        req.fileName = NULL;
        req.buffer = lbl_802D4B00;
        req.size = 0x10000;
        req.chan = node->chan;
        req.async = node->flag18;
        req.attr = 4;
        req.callback = fn_80040FE0;
        bits = 0;
        if ((node->mode1B & 7) == 7) {
            bits = 0xF;
        } else if (node->mode1B & 2) {
            if (node->idx20 == 3) {
                bits |= 3;
            } else {
                bits = 1 << (node->idx20 + 1);
            }
        }
        req.callbackArg = bits;
        req.flags = 1;
        memoryCardRelatedFunction(&req, 1, lbl_802D4AE0[node->chan]);
        node->step++;
        break;
    case 7:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            switch (mcardState.status) {
            case 0x11:
                if (node->mode1A == 0) {
                    node->step = 0x10;
                    node->result1C = 1;
                } else {
                    node->step = 8;
                }
                break;
            case 0x10:
                node->step = 0xE;
                break;
            case 3:
            case 0xD:
                node->step = 0xC;
                break;
            default:
                node->step = 0xA;
                break;
            }
        }
        break;
    case 8:
        fn_8004A34C(cardCheck, node->slot, 0x18, 0, 0);
        node->step++;
        break;
    case 9:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            node->step = 0x10;
            node->result1C = 1;
        }
        break;
    case 0xA:
        node->step = 0x10;
        node->result1C = 2;
        break;
    case 0xC:
        node->step = 0x10;
        node->result1C = 5;
        break;
    case 0xE:
        if (node->flag1D) {
            node->step = 0x10;
            node->result1C = 9;
        } else {
            fn_8004A34C(cardCheck, node->slot, 0x13, 0, 0);
            node->step++;
        }
        break;
    case 0xF:
        if (node->flag1D) {
            if (((SceneNode*)currentDrawingItem)->state != 0) {
                node->step = 0x10;
                node->result1C = 9;
            }
        } else if (((SceneNode*)currentDrawingItem)->state != 0) {
            node->step = 0x10;
            node->result1C = 8;
        }
        break;
    case 0x10:
        ((SceneNode*)currentDrawingItem)->parent->state = node->result1C;
        text_freeAllBlocks();
        removeCurrentDrawingItem();
        break;
    }
}

void mcardFormat(u8 chan, u8 async, u64 serialNo);

void fn_8003BB90(void) {
    SceneNode* node = (SceneNode*)currentDrawingItem;
    s32 probe;
    s32 status;

    probe = mcardState.chan[node->chan].probeResult;
    if (probe == -1) {
        status = 0xF;
    } else if (probe >= 0) {
        status = (probe < 1) ? 0x11 : -1;
    } else if (probe == -3) {
        status = 0;
    } else if (probe > -3) {
        status = 4;
    } else {
        status = -1;
    }
    if (status == 4 || status == 0x11) {
        node->flag1E = 1;
    } else if (status == 0) {
        node->flag1D = 1;
    }

    switch (node->step) {
    case 0:
        fn_8004A34C(cardCheck, node->slot, 8, 0, 0);
        node->flag1D = 0;
        fn_800415A0(0x32);
        node->step++;
        break;
    case 1:
        if ((u16)fn_8004157C() != 0) {
            break;
        }
        if (node->flag1D) {
            node->flag1E = 0;
            node->result1C = 9;
            node->step = 3;
        } else {
            mcardFormat(node->chan, node->flag18, lbl_802D4AE0[node->chan]);
            node->step = 2;
        }
        break;
    case 2:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            if (mcardState.status == 0x11) {
                ((SceneNode*)currentDrawingItem)->parent->state = 1;
                text_freeAllBlocks();
                removeCurrentDrawingItem();
            } else {
                node->step = 3;
                if (node->flag1D) {
                    node->result1C = 9;
                } else {
                    switch (mcardState.status) {
                    case 0xD:
                        node->result1C = 5;
                        node->step = 4;
                        break;
                    case 0x10:
                        node->result1C = 8;
                        break;
                    case 0:
                        node->result1C = 9;
                        break;
                    default:
                        node->result1C = 2;
                        break;
                    }
                }
            }
            node->flag1E = 0;
        }
        break;
    case 3:
        fn_8004A34C(cardCheck, node->slot, 0xA, 0, 0);
        node->step = 5;
        break;
    case 4:
        fn_8004A34C(cardCheck, node->slot, 9, 0, 0);
        node->step = 5;
        break;
    case 5:
        if (node->flag1D) {
            if (node->flag1E) {
                switch (cardCheck[0x45]) {
                case 1:
                case 2:
                    node->result1C = 7;
                    node->step = 6;
                    break;
                case 3:
                case 4:
                    node->result1C = 2;
                    node->step = 6;
                    break;
                }
            } else {
                switch (cardCheck[0x45]) {
                case 1:
                case 2:
                    node->result1C = 7;
                    node->step = 6;
                    break;
                case 3:
                case 4:
                    node->result1C = 2;
                    node->step = 6;
                    break;
                }
            }
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->result1C = 7;
                node->step = 6;
                break;
            case 3:
            case 4:
                node->result1C = 2;
                node->step = 6;
                break;
            }
        }
        break;
    case 6:
        ((SceneNode*)currentDrawingItem)->parent->state = node->result1C;
        text_freeAllBlocks();
        removeCurrentDrawingItem();
        break;
    }
}

void fn_8003BF54(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h, u8 i) {
    SceneNode* item = (SceneNode*)insertGraphicDrawingFunction(sceneDrawingLogic, 0x8000);

    item->step = 0;
    item->slot = a;
    item->arg16 = b;
    item->chan = c;
    item->flag18 = d;
    item->_19 = e;
    item->mode1A = f;
    item->mode1B = g;
    item->flag1D = 0;
    item->idx20 = h;
    item->_21 = i;
    lbl_802D4AE0[c] = 0;
    item->_1F = 2;
    ((SceneNode*)currentDrawingItem)->state = 0;
}

void sceneDrawingLogic(void) {
    SceneNode* node = (SceneNode*)currentDrawingItem;
    s32 probe;
    s32 status;
    s32 msg;
    s32 c45;
    s32 c52;
    s32 i;
    McardRequest req;
    OSCalendarTime calTime;
    SceneNode* newNode;
    u8* base;
    u8* dst;
    u8* src;

    /* Map the memory-card probe result of this node's channel to a status code. */
    probe = mcardState.chan[node->chan].probeResult;
    if (probe == -1) {
        status = 0xF;
    } else if (probe >= 0) {
        status = (probe < 1) ? 0x11 : -1;
    } else if (probe == -3) {
        status = 0;
    } else if (probe > -3) {
        status = 4;
    } else {
        status = -1;
    }
    if (status == 4 || status == 0x11) {
        node->flag1E = 1;
    } else if (status == 0) {
        node->flag1D = 1;
    }

    switch (node->step) {
    case 0:
        if (cardCheck[0x47] == 0) {
            mcardStartProbe();
            lbl_80366158[0x20] = 1;
            node->step = 1;
        } else {
            node->step = 0x2D;
            node->result1C = 0xB;
        }
        break;

    case 1:
        if (node->mode1A == 1) {
            c52 = cardCheck[0x52];
            if (c52 == 1 || c52 == 3) {
                fn_8004A34C(cardCheck, node->slot, 0x1B, 0, 0);
            }
            node->step++;
        } else {
            node->step = 8;
            lbl_802D4AE0[node->chan] = 0;
        }
        break;

    case 2:
        if (node->mode1A == 1) {
            c52 = cardCheck[0x52];
            if (c52 == 1 || c52 == 3) {
                c45 = cardCheck[0x45];
                if (c45 == 2) {
                    node->step = 8;
                    lbl_802D4AE0[node->chan] = 0;
                } else if (c45 >= 3 && c45 < 5) {
                    node->step = 0x2D;
                    node->result1C = 0xB;
                }
            } else {
                node->step = 8;
                lbl_802D4AE0[node->chan] = 0;
            }
        }
        break;

    case 3:
        fn_8004A34C(cardCheck, node->slot, (u8)lbl_803CB830[3 + node->_1F], 1, 0);
        node->step++;
        break;

    case 4:
        if (currentDrawingItem->state == 2) {
            node->step = 0x2D;
            node->result1C = 0xB;
        } else if (currentDrawingItem->state == 3 || currentDrawingItem->state == 4) {
            node->step = 1;
        }
        break;

    case 5:
        {
            u8 msg5 = 0;
            lbl_80366158[0x20] = 1;
            if (node->mode1A == 4 && node->_21 != 4) {
                msg5 = 0x12;
            } else if (cardCheck[0x52] != 1) {
                switch (node->_21) {
                case 0: msg5 = 0x1D; break;
                case 1: msg5 = 0x21; break;
                case 2: msg5 = 0x2B; break;
                case 3: msg5 = 0x30; break;
                case 4: msg5 = 0x12; break;
                }
            }
            fn_8004A34C(cardCheck, node->slot, msg5, 1, 0);
            if (node->_21 == 2 || node->_21 == 3) {
                node->step = 7;
            } else {
                node->step++;
            }
        }
        break;

    case 6:
        if (cardCheck[0x52] == 1) {
            node->step = 0x2D;
            node->result1C = 1;
        } else {
            c45 = cardCheck[0x45];
            if (c45 == 2) {
                node->step = 0x2D;
                node->result1C = (cardCheck[0x52] == 3) ? 1 : 0xB;
            } else if (c45 == 3 || c45 == 4) {
                node->step = (cardCheck[0x52] == 2) ? 0x2D : 1;
                node->result1C = 7;
            }
        }
        break;

    case 7:
        c45 = cardCheck[0x45];
        if (c45 == 2) {
            node->step = 8;
        } else if (c45 == 3 || c45 == 4) {
            node->step = (cardCheck[0x52] == 2) ? 0x2D : 1;
            node->result1C = 7;
        }
        break;

    case 8:
        newNode = (SceneNode*)insertGraphicDrawingFunction(fn_8004053C, 0x8000);
        newNode->step = 0;
        newNode->slot = node->slot;
        newNode->arg16 = node->arg16;
        newNode->chan = node->chan;
        newNode->flag18 = 1;
        newNode->mode1A = node->mode1A;
        newNode->mode1B = node->mode1B;
        newNode->flag1D = 0;
        newNode->_21 = node->_21;
        currentDrawingItem->state = 0;
        node->step++;
        break;

    case 9:
        if (currentDrawingItem->state != 0) {
            node->flag1D = 0;
            switch (currentDrawingItem->state) {
            case 1:
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                node->step = 0xA;
                break;
            case 6:
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                node->step = (node->_21 == 2) ? 0x29 : 0x1B;
                break;
            case 7:
                c52 = cardCheck[0x52];
                if (c52 == 2) {
                    node->step = 0x2D;
                    node->result1C = 7;
                } else if (c52 == 4 || c52 == 5) {
                    node->step = 0x2D;
                    node->result1C = 0xB;
                } else {
                    node->step = 1;
                }
                break;
            case 8:
                node->step = 5;
                break;
            case 9:
                lbl_802D4AE0[node->chan] = 0;
                node->step = 0xC;
                break;
            case 10:
                node->step = 5;
                break;
            case 11:
                node->step = 0x2D;
                if (node->mode1A == 4 || cardCheck[0x52] == 2) {
                    node->result1C = 0xB;
                } else {
                    node->result1C = 0xC;
                }
                break;
            case 13:
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                node->step = 0x10;
                break;
            }
        }
        break;

    case 10:
        mcardCheckSpace(node->chan, node->flag18, (s16)lbl_803CBC48, lbl_800E6910,
                        lbl_802D4AE0[node->chan]);
        node->step++;
        break;

    case 11:
        if (currentDrawingItem->state != 0) {
            switch (mcardState.status) {
            case 0:
                lbl_802D4AE0[node->chan] = 0;
                node->step = 0xC;
                break;
            case 1:
                fn_8004A34C(cardCheck, node->slot, 0x15, 0, 0);
                node->step = 0x25;
                break;
            case 5:
                fn_8004A34C(cardCheck, node->slot, 0x40, 0, 0);
                node->step = 0x25;
                break;
            case 6:
                fn_8004A34C(cardCheck, node->slot, 0x3F, 0, 0);
                node->step = 0x27;
                break;
            case 8:
                node->step = 0x1B;
                break;
            case 14:
            case 17:
                node->step = 0x12;
                break;
            case 16:
                fn_8004A34C(cardCheck, node->slot, 0x13, 0, 0);
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                node->step = 0x25;
                break;
            default:
                /* Status values 2, 3, 4, 7, 9..13 and 15 (and out-of-range) share this path. */
                if (node->_21 == 3) {
                    msg = 0x30;
                } else if (node->_21 == 2) {
                    msg = 0x2B;
                } else {
                    msg = 0x17;
                }
                fn_8004A34C(cardCheck, node->slot, msg, 0, 0);
                node->step = 0x25;
                break;
            }
            node->flag1E = 0;
        }
        break;

    case 12:
        lbl_80366158[0x20] = 1;
        fn_8004A34C(cardCheck, node->slot, 1, 0, 0);
        node->flag1D = 0;
        node->flag1E = 0;
        lbl_802D4AE0[node->chan] = 0;
        node->step++;
        break;

    case 13:
        c45 = cardCheck[0x45];
        if (c45 == 1 || c45 == 2) {
            node->step = 8;
        } else if (c45 == 3 || c45 == 4) {
            node->step = 0x2D;
            node->result1C = (node->mode1A == 4 || cardCheck[0x52] == 2) ? 0xB : 0xC;
        }
        break;

    case 14:
        if (node->flag1D != 0) {
            cardCheck[0x46] = 1;
            node->step = 0xC;
        } else {
            node->step = 0x10;
        }
        break;

    case 15:
        if (node->flag1D != 0) {
            cardCheck[0x46] = 1;
            node->step = 0xC;
        } else {
            c45 = cardCheck[0x45];
            if (c45 == 1 || c45 == 2) {
                node->step = 0x10;
            } else if (c45 == 3 || c45 == 4) {
                node->step = 5;
            }
        }
        break;

    case 16:
        /* Clear the work buffer, then load the save image from the global copies. */
        memset(lbl_802D4B00, 0, 0xD51C);
        memset(lbl_802D4B00 + 0xD51C, 0xEE, 0x2AE4);
        base = lbl_802D4B00;
        src = audioFileDescriptors;
        base[0x94] = src[0x397];
        base[0x95] = src[0x398];
        base[0x96] = lbl_80366158[0x1F];
        memcpy(base + 0x97, superstarUnlocked, 0xF7);
        memcpy(base + 0x190, lbl_803616CC, 0x454);
        base[0x5E4] = g_d_GameSettings[0x12];
        memcpy(base + 0x5E5, g_d_GameSettings + 0x14, 6);
        memcpy(base + 0x5EB, g_d_GameSettings + 0x1A, 6);
        *(u32*)(base + 0x5F4) = *(u32*)g_d_GameSettings;
        memcpy(base + 0x48, lbl_80354768 + 0xCF18, 0x36);
        memcpy(base + 0x7E, lbl_80354768 + 0xCF4E, 0x10);
        *(u16*)(base + 0x46) = 0x5B4;
        lbl_80366158[0x20] = 0;
        {
            s32 bit = node->mode1B & 2;
            for (i = 0; i < 3; i++) {
                if (bit != 0 && i == node->idx20) {
                    memcpy(lbl_80354768 + i * 0x4508, g_Challenge, 0x4508);
                    lbl_80354768[0xCF5E + node->idx20] = 1;
                    base[0x8E + node->idx20] = 1;
                }
                memcpy(base + 0x5FC + i * 0x450C, lbl_80354768 + i * 0x4508, 0x4508);
                *(u16*)(base + 0x5FA + i * 0x450C) = 0x450C;
            }
            memcpy(base + 0x8E, lbl_80354768 + 0xCF5E, 3);
        }
        lbl_80366158[0x20] = 0;
        newNode = (SceneNode*)insertGraphicDrawingFunction(fn_8003B5B0, 0x8000);
        newNode->step = 0;
        newNode->slot = node->slot;
        newNode->arg16 = node->arg16;
        newNode->chan = node->chan;
        newNode->flag18 = 1;
        newNode->mode1A = node->mode1A;
        newNode->mode1B = node->mode1B;
        newNode->flag1D = 0;
        currentDrawingItem->state = 0;
        fn_8004A34C(cardCheck, node->slot, 0x16, 0, 0);
        node->step++;
        break;

    case 17:
        if (currentDrawingItem->state != 0) {
            cardCheck[0x46] = 1;
            node->flag1D = 0;
            switch (currentDrawingItem->state) {
            case 1:
                fn_8004A34C(cardCheck, node->slot, 0x18, 0, 0);
                node->step = 0x2D;
                node->result1C = 1;
                break;
            case 2:
            case 3:
                lbl_802D4AE0[node->chan] = 0x0000000100000001ULL;
                fn_8004A34C(cardCheck, node->arg16, 0x44, 0, 0);
                node->step = 7;
                break;
            case 8:
                node->result1C = 8;
                node->step = 0x2D;
                break;
            case 9:
                lbl_802D4AE0[node->chan] = 0x0000000100000001ULL;
                node->step = 0xC;
                break;
            }
        }
        break;

    case 18:
        if (node->flag1D != 0) {
            cardCheck[0x46] = 1;
            node->step = 0xC;
        } else {
            fn_8004A34C(cardCheck, node->slot, 0x3E, 0, 0);
            node->step++;
        }
        break;

    case 19:
        if (node->flag1D != 0) {
            cardCheck[0x46] = 1;
            node->step = 0xC;
        } else {
            c45 = cardCheck[0x45];
            if (c45 == 1 || c45 == 2) {
                node->step = 0x14;
            }
        }
        break;

    case 20:
        lbl_803CBCB8 = 1;
        lbl_803CBCBC = fn_800A6418(0x10000);
        DCFlushRange(lbl_802D4B00, 0x10000);
        ARQPostRequest(&lbl_802D4AC0, 0x4000, 0, 0, (u32)lbl_802D4B00, lbl_803CBCBC, 0x10000, fn_8003AE64);
        node->step++;
        break;

    case 21:
        if (lbl_803CBCB8 != 0) {
            break;
        }
        if (node->flag1D != 0) {
            cardCheck[0x46] = 1;
            node->step = 0xC;
            break;
        }
        if (node->_21 == 3) {
            /* Clear the slot's g_Challenge image and the matching flags. */
            base = lbl_802D4B00;
            dst = lbl_80354768 + node->idx20 * 0x4508;
            memset(dst, 0, 0x4508);
            memcpy(base + node->idx20 * 0x450C + 0x5FC, dst, 0x4508);
            lbl_80354768[0xCF5E + node->idx20] = 0;
            base[0x8E + node->idx20] = 0;
            *(u16*)(base + node->idx20 * 0x450C + 0x5FA) = 0x450C;
            *(u16*)(base + 0x46) = 0x5B4;
        } else {
            /* Same load as state 16, using the slot's current gallery index. */
            base = lbl_802D4B00;
            src = audioFileDescriptors;
            base[0x94] = src[0x397];
            base[0x95] = src[0x398];
            base[0x96] = lbl_80366158[0x1F];
            memcpy(base + 0x97, superstarUnlocked, 0xF7);
            memcpy(base + 0x190, lbl_803616CC, 0x454);
            base[0x5E4] = g_d_GameSettings[0x12];
            memcpy(base + 0x5E5, g_d_GameSettings + 0x14, 6);
            memcpy(base + 0x5EB, g_d_GameSettings + 0x1A, 6);
            *(u32*)(base + 0x5F4) = *(u32*)g_d_GameSettings;
            memcpy(base + 0x48, lbl_80354768 + 0xCF18, 0x36);
            memcpy(base + 0x7E, lbl_80354768 + 0xCF4E, 0x10);
            *(u16*)(base + 0x46) = 0x5B4;
            {
                s32 bit = node->mode1B & 2;
                for (i = 0; i < 3; i++) {
                    if (bit != 0 && i == node->idx20) {
                        memcpy(lbl_80354768 + i * 0x4508, g_Challenge, 0x4508);
                        lbl_80354768[0xCF5E + node->idx20] = 1;
                        base[0x8E + node->idx20] = 1;
                    }
                    memcpy(base + 0x5FC + i * 0x450C, lbl_80354768 + i * 0x4508, 0x4508);
                    *(u16*)(base + 0x5FA + i * 0x450C) = 0x450C;
                }
                memcpy(base + 0x8E, lbl_80354768 + 0xCF5E, 3);
            }
        }
        /* Shared tail: queue the scene that owns the save image. */
        lbl_80366158[0x20] = 0;
        newNode = (SceneNode*)insertGraphicDrawingFunction(fn_8003B5B0, 0x8000);
        newNode->step = 0;
        newNode->slot = node->slot;
        newNode->arg16 = node->arg16;
        newNode->chan = node->chan;
        newNode->flag18 = 1;
        newNode->mode1A = node->mode1A;
        newNode->mode1B = node->mode1B;
        newNode->flag1D = 0;
        currentDrawingItem->state = 0;
        fn_8004A34C(cardCheck, node->slot, 0xC, 0, 0);
        node->step++;
        break;

    case 22:
        if (currentDrawingItem->state == 0) {
            break;
        }
        if (mcardState.status == 0x11) {
            node->step = 0x18;
        } else {
            node->step = 0x17;
        }
        /* falls through */
    case 23:
        if (node->step == 0x17) {
            lbl_803CBCB8 = 2;
            DCInvalidateRange(lbl_802D4B00, 0x10000);
            ARQPostRequest(&lbl_802D4AC0, 0x4000, 1, 0, (u32)lbl_802D4B00, lbl_803CBCBC, 0x10000, fn_8003AE64);
            node->step = 0x18;
        }
        /* falls through */
    case 24:
        if (lbl_803CBCB8 != 0) {
            break;
        }
        if (mcardState.status != 0x11) {
            fn_80041150(7, 3);
        }
        if (lbl_803CBCBC != 0) {
            fn_800A63C8();
            lbl_803CBCBC = 0;
        }
        node->step = 0x19;
        /* falls through */
    case 25:
        node->flag1D = 0;
        switch (currentDrawingItem->state) {
        case 1:
            cardCheck[0x46] = 1;
            node->step = 0x2B;
            node->result1C = 1;
            break;
        case 5:
            fn_8004A34C(cardCheck, node->slot, 0x45, 0, 0);
            node->step = 0x1A;
            break;
        default:
            fn_8004A34C(cardCheck, node->slot, 0x44, 0, 0);
            lbl_802D4AE0[node->chan] = 0;
            node->step = 0x1A;
            break;
        }
        break;

    case 26:
        c45 = cardCheck[0x45];
        if (c45 == 1 || c45 == 2) {
            node->step = 8;
        } else if (c45 == 3 || c45 == 4) {
            if (node->mode1A == 0) {
                node->step = 5;
            } else {
                c52 = cardCheck[0x52];
                if (c52 == 3) {
                    node->result1C = 1;
                    node->step = 0x2D;
                } else {
                    node->result1C = (node->mode1A == 4 || c52 == 2) ? 0xB : 0xC;
                    node->step = 0x2D;
                }
            }
        }
        break;

    case 27:
        newNode = (SceneNode*)insertGraphicDrawingFunction(fn_80040C14, 0x8000);
        newNode->step = 0;
        newNode->slot = node->slot;
        newNode->arg16 = node->arg16;
        newNode->chan = node->chan;
        newNode->flag18 = node->flag18;
        newNode->mode1A = node->mode1A;
        newNode->flag1D = 0;
        newNode->idx20 = node->idx20;
        newNode->mode1B = node->mode1B;
        currentDrawingItem->state = 0;
        node->step++;
        break;

    case 28:
        if (currentDrawingItem->state > 9) {
            break;
        }
        switch (currentDrawingItem->state) {
        case 1:
            if (node->mode1B & 2) {
                node->step = (lbl_802D4B00[0x8E + node->idx20] != 0) ? 0x1D : 0x1F;
            } else {
                node->step = 0x1F;
            }
            break;
        case 2:
            if (node->_21 == 2) {
                cardCheck[0x45] = 2;
            } else {
                fn_8004A34C(cardCheck, node->slot, (node->mode1A == 5) ? 0x30 : 0x17, 0, 0);
            }
            fn_800415A0(0x32);
            node->step = 0x25;
            break;
        case 4:
            node->step = 0x1D;
            break;
        case 8:
            lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
            fn_8004A34C(cardCheck, node->slot, 0x13, 0, 0);
            node->step = 0x25;
            break;
        case 9:
            fn_8004A34C(cardCheck, node->slot, (node->mode1A == 5) ? 0x30 : 0x17, 0, 0);
            fn_800415A0(0x32);
            lbl_802D4AE0[node->chan] = 0;
            node->step = 0x25;
            break;
        }
        break;

    case 29:
        if (node->mode1A != 4) {
            if (node->flag1D != 0) {
                cardCheck[0x46] = 1;
                node->step = 0xC;
            } else {
                node->step = 0x1F;
            }
        } else {
            node->step = 0x1F;
        }
        break;

    case 30:
        if (node->flag1D != 0) {
            if (cardCheck[0x45] != 0) {
                cardCheck[0x46] = 1;
                node->step = 0xC;
            }
        } else {
            c45 = cardCheck[0x45];
            if (c45 == 2) {
                node->step = 0x1F;
            } else if (c45 == 3 || c45 == 4) {
                node->step = 0x2D;
                node->result1C = 7;
            }
        }
        break;

    case 31:
        lbl_80366158[0x20] = 0;
        if (node->flag1D != 0) {
            fn_8004A34C(cardCheck, node->slot, (node->mode1A == 5) ? 0x30 : 0x17, 0, 0);
            fn_800415A0(0x32);
            lbl_802D4AE0[node->chan] = 0;
            node->step = 0x25;
            break;
        }
        if (node->_21 == 3) {
            fn_8004A34C(cardCheck, node->slot, 0x32, 0, 0);
        } else if (node->_21 == 2) {
            fn_8004A34C(cardCheck, node->slot, 0x2C, 0, 0);
        } else {
            fn_8004A34C(cardCheck, node->slot, 0x16, 0, 0);
        }
        if (node->mode1A == 4) {
            /* Same image load as state 21. */
            base = lbl_802D4B00;
            src = audioFileDescriptors;
            base[0x94] = src[0x397];
            base[0x95] = src[0x398];
            base[0x96] = lbl_80366158[0x1F];
            memcpy(base + 0x97, superstarUnlocked, 0xF7);
            memcpy(base + 0x190, lbl_803616CC, 0x454);
            base[0x5E4] = g_d_GameSettings[0x12];
            memcpy(base + 0x5E5, g_d_GameSettings + 0x14, 6);
            memcpy(base + 0x5EB, g_d_GameSettings + 0x1A, 6);
            *(u32*)(base + 0x5F4) = *(u32*)g_d_GameSettings;
            memcpy(base + 0x48, lbl_80354768 + 0xCF18, 0x36);
            memcpy(base + 0x7E, lbl_80354768 + 0xCF4E, 0x10);
            *(u16*)(base + 0x46) = 0x5B4;
            {
                s32 bit = node->mode1B & 2;
                for (i = 0; i < 3; i++) {
                    if (bit != 0 && i == node->idx20) {
                        memcpy(lbl_80354768 + i * 0x4508, g_Challenge, 0x4508);
                        lbl_80354768[0xCF5E + node->idx20] = 1;
                        base[0x8E + node->idx20] = 1;
                    }
                    memcpy(base + 0x5FC + i * 0x450C, lbl_80354768 + i * 0x4508, 0x4508);
                    *(u16*)(base + 0x5FA + i * 0x450C) = 0x450C;
                }
                memcpy(base + 0x8E, lbl_80354768 + 0xCF5E, 3);
            }
        } else {
            /* Same image load without the per-slot bit test. */
            base = lbl_802D4B00;
            src = audioFileDescriptors;
            base[0x94] = src[0x397];
            base[0x95] = src[0x398];
            base[0x96] = lbl_80366158[0x1F];
            memcpy(base + 0x97, superstarUnlocked, 0xF7);
            memcpy(base + 0x190, lbl_803616CC, 0x454);
            base[0x5E4] = g_d_GameSettings[0x12];
            memcpy(base + 0x5E5, g_d_GameSettings + 0x14, 6);
            memcpy(base + 0x5EB, g_d_GameSettings + 0x1A, 6);
            *(u32*)(base + 0x5F4) = *(u32*)g_d_GameSettings;
            memcpy(base + 0x48, lbl_80354768 + 0xCF18, 0x36);
            memcpy(base + 0x7E, lbl_80354768 + 0xCF4E, 0x10);
            *(u16*)(base + 0x46) = 0x5B4;
            for (i = 0; i < 3; i++) {
                memcpy(base + 0x5FC + i * 0x450C, lbl_80354768 + i * 0x4508, 0x4508);
                *(u16*)(base + 0x5FA + i * 0x450C) = 0x450C;
            }
            memcpy(base + 0x8E, lbl_80354768 + 0xCF5E, 3);
        }
        fn_800415A0(0x32);
        node->step++;
        break;

    case 32:
        lbl_803CBCB8 = 1;
        lbl_803CBCBC = fn_800A6418(0x10000);
        DCFlushRange(lbl_802D4B00, 0x10000);
        ARQPostRequest(&lbl_802D4AC0, 0x4000, 0, 0, (u32)lbl_802D4B00, lbl_803CBCBC, 0x10000, fn_8003AE64);
        node->step++;
        break;

    case 33:
        if (lbl_803CBCB8 != 0) {
            break;
        }
        if (fn_8004157C() & 0xFFFF) {
            break;
        }
        if (node->flag1D != 0) {
            cardCheck[0x46] = 1;
            node->step = 0xC;
            break;
        }
        if (node->mode1A == 5) {
            base = lbl_802D4B00;
            dst = lbl_80354768 + node->idx20 * 0x4508;
            memset(dst, 0, 0x4508);
            memcpy(base + node->idx20 * 0x450C + 0x5FC, dst, 0x4508);
            lbl_80354768[0xCF5E + node->idx20] = 0;
            base[0x8E + node->idx20] = 0;
            *(u16*)(base + node->idx20 * 0x450C + 0x5FA) = 0x450C;
            *(u16*)(base + 0x46) = 0x5B4;
        } else {
            base = lbl_802D4B00;
            src = audioFileDescriptors;
            base[0x94] = src[0x397];
            base[0x95] = src[0x398];
            base[0x96] = lbl_80366158[0x1F];
            memcpy(base + 0x97, superstarUnlocked, 0xF7);
            memcpy(base + 0x190, lbl_803616CC, 0x454);
            base[0x5E4] = g_d_GameSettings[0x12];
            memcpy(base + 0x5E5, g_d_GameSettings + 0x14, 6);
            memcpy(base + 0x5EB, g_d_GameSettings + 0x1A, 6);
            *(u32*)(base + 0x5F4) = *(u32*)g_d_GameSettings;
            memcpy(base + 0x48, lbl_80354768 + 0xCF18, 0x36);
            memcpy(base + 0x7E, lbl_80354768 + 0xCF4E, 0x10);
            *(u16*)(base + 0x46) = 0x5B4;
            {
                s32 bit = node->mode1B & 2;
                for (i = 0; i < 3; i++) {
                    if (bit != 0 && i == node->idx20) {
                        memcpy(lbl_80354768 + i * 0x4508, g_Challenge, 0x4508);
                        lbl_80354768[0xCF5E + node->idx20] = 1;
                        base[0x8E + node->idx20] = 1;
                    }
                    memcpy(base + 0x5FC + i * 0x450C, lbl_80354768 + i * 0x4508, 0x4508);
                    *(u16*)(base + 0x5FA + i * 0x450C) = 0x450C;
                }
                memcpy(base + 0x8E, lbl_80354768 + 0xCF5E, 3);
            }
        }
        /* Banner and memory-card write for the saved slot. */
        OSTicksToCalendarTime(OSGetTime(), &calTime);
        processBannerImage(lbl_800E6910, lbl_800F7B00 + 0x23C0, lbl_803CBC4C, lbl_800F7B00 + 0x40,
                           lbl_803CBC50, 3, 0, (const char*)(lbl_800F7B00 + 0x3280), (const char*)(lbl_800F7B00 + 0x3240), lbl_803CBC48);
        {
            u32 flagBits = 0;
            if ((node->mode1B & 7) == 7) {
                flagBits = 0xF;
            } else if (node->mode1B & 2) {
                if (node->idx20 == 3) {
                    flagBits = 3;
                } else {
                    flagBits = 1 << (node->idx20 + 1);
                }
            }
            req.fileName = NULL;
            req.buffer = lbl_802D4B00;
            req.size = 0x10000;
            req.chan = node->chan;
            req.async = node->flag18;
            req.attr = 4;
            req.callback = fn_80040FE0;
            req.callbackArg = flagBits;
            req.flags = 1;
            memoryCardRelatedFunction(&req, 1, lbl_802D4AE0[node->chan]);
        }
        node->step++;
        break;

    case 34:
        if (currentDrawingItem->state == 0) {
            break;
        }
        if (mcardState.status == 0x11) {
            node->step = 0x24;
        } else {
            node->step = 0x23;
        }
        /* falls through */
    case 35:
        if (node->step == 0x23) {
            lbl_803CBCB8 = 2;
            DCInvalidateRange(lbl_802D4B00, 0x10000);
            ARQPostRequest(&lbl_802D4AC0, 0x4000, 1, 0, (u32)lbl_802D4B00, lbl_803CBCBC, 0x10000, fn_8003AE64);
            node->step = 0x24;
        }
        /* falls through */
    case 36:
        if (lbl_803CBCB8 != 0) {
            break;
        }
        if (mcardState.status != 0x11) {
            fn_80041150(7, 3);
        }
        if (lbl_803CBCBC != 0) {
            fn_800A63C8();
            lbl_803CBCBC = 0;
        }
        {
            /* Load the save image for the non-zero slots (the second load variant). */
            base = lbl_802D4B00;
            src = audioFileDescriptors;
            base[0x94] = src[0x397];
            base[0x95] = src[0x398];
            base[0x96] = lbl_80366158[0x1F];
            memcpy(base + 0x97, superstarUnlocked, 0xF7);
            memcpy(base + 0x190, lbl_803616CC, 0x454);
            base[0x5E4] = g_d_GameSettings[0x12];
            memcpy(base + 0x5E5, g_d_GameSettings + 0x14, 6);
            memcpy(base + 0x5EB, g_d_GameSettings + 0x1A, 6);
            *(u32*)(base + 0x5F4) = *(u32*)g_d_GameSettings;
            memcpy(base + 0x48, lbl_80354768 + 0xCF18, 0x36);
            memcpy(base + 0x7E, lbl_80354768 + 0xCF4E, 0x10);
            *(u16*)(base + 0x46) = 0x5B4;
            for (i = 0; i < 3; i++) {
                if (i == 3) {
                    memcpy(lbl_80354768 + i * 0x4508, g_Challenge, 0x4508);
                    lbl_80354768[0xCF61] = 1;
                    base[0x91] = 1;
                }
                memcpy(base + 0x5FC + i * 0x450C, lbl_80354768 + i * 0x4508, 0x4508);
                *(u16*)(base + 0x5FA + i * 0x450C) = 0x450C;
            }
            memcpy(base + 0x8E, lbl_80354768 + 0xCF5E, 3);
        }
        switch (mcardState.status) {
        case 0:
            lbl_802D4AE0[node->chan] = 0;
            node->step = 0xC;
            break;
        case 3:
        case 13:
            if (node->_21 == 2) {
                fn_8004A34C(cardCheck, node->slot, 0x47, 0, 0);
            } else if (node->mode1A == 5) {
                fn_8004A34C(cardCheck, node->slot, 0x48, 0, 0);
            } else {
                fn_8004A34C(cardCheck, node->slot, 0x46, 0, 0);
            }
            fn_800415A0(0x32);
            node->step = 0x25;
            break;
        case 12:
        case 16:
            lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
            node->step = 0x25;
            break;
        case 17:
            node->result1C = 1;
            node->step = 0x2B;
            break;
        default:
            /* Statuses 1, 2, 4..11, 14, 15 and anything above 0x11. */
            if (node->_21 == 2) {
                fn_8004A34C(cardCheck, node->slot, 0x2B, 0, 0);
            } else {
                fn_8004A34C(cardCheck, node->slot, (node->mode1A == 5) ? 0x30 : 0x17, 0, 0);
            }
            node->step = 0x25;
            fn_800415A0(0x32);
            break;
        }
        break;

    case 37:
        node->flag1E = 0;
        node->step++;
        /* falls through */
    case 38:
        lbl_80366158[0x20] = 1;
        if (fn_8004157C() & 0xFFFF) {
            break;
        }
        if (node->flag1D != 0 && node->flag1E != 0) {
            cardCheck[0x46] = 1;
            node->step = 1;
        } else {
            c45 = cardCheck[0x45];
            if (c45 == 1 || c45 == 2) {
                node->step = 8;
            } else if (c45 == 3 || c45 == 4) {
                node->step = 0x2D;
                c52 = cardCheck[0x52];
                if (c52 == 3) {
                    node->result1C = 1;
                } else {
                    node->result1C = (node->mode1A == 4 || c52 == 2) ? 0xB : 0xC;
                }
            }
        }
        break;

    case 39:
        node->flag1E = 0;
        node->step++;
        /* falls through */
    case 40:
        if (node->flag1D != 0 && node->flag1E != 0) {
            cardCheck[0x46] = 1;
            node->step = 1;
        } else {
            c45 = cardCheck[0x45];
            if (c45 == 1 || c45 == 2) {
                node->step = 8;
            } else if (c45 == 3 || c45 == 4) {
                node->step = 0x2D;
                c52 = cardCheck[0x52];
                if (c52 == 3) {
                    node->result1C = 1;
                } else {
                    node->result1C = (node->mode1A == 4 || c52 == 2) ? 0xB : 0xC;
                }
            }
        }
        break;

    case 41:
        if (fn_80041348() & 0xFF) {
            node->step = 0x1B;
            break;
        }
        fn_8004A34C(cardCheck, node->slot, 0x36, 0, 0);
        node->step = 0x2A;
        break;

    case 42:
        c45 = cardCheck[0x45];
        if (c45 == 1 || c45 == 2) {
            node->step = 5;
        }
        break;

    case 43:
        switch (node->_21) {
        case 2:
            fn_8004A34C(cardCheck, node->slot, 0x2D, 0, 0);
            break;
        case 3:
            fn_8004A34C(cardCheck, node->slot, 0x33, 0, 0);
            break;
        case 5:
            cardCheck[0x45] = 2;
            break;
        default:
            fn_8004A34C(cardCheck, node->slot, 0x18, 0, 0);
            break;
        }
        fn_800415A0(0x32);
        lbl_80366158[0x20] = 1;
        node->step++;
        break;

    case 44:
        if (fn_8004157C() & 0xFFFF) {
            break;
        }
        if (cardCheck[0x45] == 0) {
            break;
        }
        node->step++;
        break;

    case 45:
        mcardStopProbe();
        node->step++;
        break;

    case 46:
        lbl_80366158[0x20] = 1;
        if (cardCheck[0x44] == 0) {
            break;
        }
        if (cardCheck[0x49] != 0) {
            cardCheck[0x48] = 1;
            fn_8004A34C(cardCheck, node->slot, 0x4D, 0, 0);
        }
        ((SceneNode*)currentDrawingItem->currentDrawingItem)->state = node->result1C;
        text_freeAllBlocks();
        removeCurrentDrawingItem();
        break;

    default:
        break;
    }
}

void fn_8003E8D8(void) {
    SceneNode* node = (SceneNode*)currentDrawingItem;
    SceneNode* newNode;
    s32 probe;
    s32 status;
    u8 s21;
    u8 s1B;
    u8 s1A;
    u8 sChan;
    u8 s16v;
    u8 sSlot;

    probe = mcardState.chan[node->chan].probeResult;
    MCARD_STATUS_FROM_PROBE(probe, status);
    if (status == 4 || status == 0x11) {
        node->flag1E = 1;
    } else if (status == 0) {
        node->flag1D = 1;
    }

    switch (node->step) {
    case 0:
        if (cardCheck[0x47] != 0) {
            node->step = 0x12;
            node->result1C = 0xB;
        } else {
            mcardStartProbe();
            node->step = 1;
        }
        break;
    case 1:
        node->step = 4;
        break;
    case 2:
        switch (cardCheck[0x45]) {
        case 1:
        case 2:
            lbl_802D4AE0[node->chan] = 0;
            node->step = 4;
            break;
        case 3:
        case 4:
            node->step = 0x12;
            node->result1C = 0xC;
            break;
        }
        break;
    case 4:
        node->flag1D = 0;
        s21 = node->_21;
        s1B = node->mode1B;
        s1A = node->mode1A;
        sChan = node->chan;
        s16v = node->arg16;
        sSlot = node->slot;
        newNode = (SceneNode*)insertGraphicDrawingFunction(fn_8004053C, 0x8000);
        newNode->step = 0;
        newNode->slot = sSlot;
        newNode->arg16 = s16v;
        newNode->chan = sChan;
        newNode->flag18 = 1;
        newNode->mode1A = s1A;
        newNode->mode1B = s1B;
        newNode->flag1D = 0;
        newNode->_21 = s21;
        ((SceneNode*)currentDrawingItem)->state = 0;
        node->step++;
        break;
    case 5:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            node->flag1D = 0;
            switch (((SceneNode*)currentDrawingItem)->state) {
            case 1:
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                fn_8004A34C(cardCheck, node->slot, 0x1E, 0, 0);
                node->step = 0xC;
                break;
            case 6:
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                node->step = 8;
                break;
            case 10:
                fn_8004A34C(cardCheck, node->slot, 0x21, 0, 0);
                node->step = 0xC;
                node->result1C = 0xC;
                lbl_802D4AE0[node->chan] = 0;
                break;
            case 7:
                node->step = 0x12;
                node->result1C = 0xC;
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                break;
            case 8:
                node->step = 0x12;
                node->result1C = 0xC;
                break;
            case 9:
                lbl_802D4AE0[node->chan] = 0;
                node->step = 6;
                break;
            }
        }
        break;
    case 6:
        fn_8004A34C(cardCheck, node->slot, 1, 0, 0);
        node->flag1D = 0;
        node->flag1E = 0;
        lbl_802D4AE0[node->chan] = 0;
        node->step++;
        break;
    case 7:
        if (node->flag1E) {
            if (((SceneNode*)currentDrawingItem)->state != 0) {
                node->step = 1;
            }
        } else if (((SceneNode*)currentDrawingItem)->state != 0) {
            node->step = 0x12;
            node->result1C = 0xC;
        }
        break;
    case 8:
        if (node->flag1D) {
            node->step = 6;
        } else {
            fn_8004A34C(cardCheck, node->slot, 0x22, 0, 0);
            fn_800415A0(0xB4);
            node->step++;
        }
        break;
    case 9:
        if ((u16)fn_8004157C() != 0) {
            break;
        }
        newNode = (SceneNode*)insertGraphicDrawingFunction(fn_80040C14, 0x8000);
        newNode->step = 0;
        newNode->slot = node->slot;
        newNode->arg16 = node->arg16;
        newNode->chan = node->chan;
        newNode->flag18 = node->flag18;
        newNode->mode1A = node->mode1A;
        newNode->flag1D = 0;
        newNode->idx20 = node->idx20;
        newNode->mode1B = node->mode1B;
        ((SceneNode*)currentDrawingItem)->state = 0;
        node->step++;
        break;
    case 10:
        switch (((SceneNode*)currentDrawingItem)->state) {
        case 1:
            if ((node->mode1B & 2) && lbl_802D4B00[node->idx20 + 0x8E] == 0) {
                fn_8004A34C(cardCheck, node->slot, 0x1E, 0, 0);
                node->step = 0xF;
                node->result1C = 0xC;
            } else {
                fn_80041150(node->mode1B, node->idx20);
                node->result1C = 1;
                node->step = 0x11;
            }
            break;
        case 9:
            fn_8004A34C(cardCheck, node->slot, 0x21, 0, 0);
            node->flag1D = 1;
            node->step = 0xC;
            lbl_802D4AE0[node->chan] = 0;
            break;
        case 8:
            fn_8004A34C(cardCheck, node->slot, 0x13, 0, 0);
            lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
            node->step = 0xC;
            break;
        case 2:
            fn_8004A34C(cardCheck, node->slot, 0x21, 0, 0);
            node->step = 0xC;
            lbl_802D4AE0[node->chan] = 0;
            break;
        case 4:
            fn_8004A34C(cardCheck, node->slot, 0x25, 0, 0);
            node->step = 0xE;
            break;
        }
        break;
    case 11:
        if (node->flag1D) {
            cardCheck[0x46] = 1;
            node->step = 6;
            lbl_802D4AE0[node->chan] = 0;
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->step = 1;
                break;
            }
        }
        break;
    case 12:
        node->flag1E = 0;
        node->step++;
        break;
    case 13:
        if (node->flag1D) {
            if (node->flag1E) {
                switch (cardCheck[0x45]) {
                case 1:
                case 2:
                    node->step = 1;
                    lbl_802D4AE0[node->chan] = 0;
                    break;
                }
            } else {
                switch (cardCheck[0x45]) {
                case 1:
                case 2:
                    node->step = 0x12;
                    node->result1C = 0xC;
                    break;
                }
            }
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->step = 0x12;
                node->result1C = 0xC;
                break;
            }
        }
        break;
    case 14:
        switch (cardCheck[0x45]) {
        case 1:
        case 2:
            fn_8004A34C(cardCheck, node->slot, 0x21, 0, 0);
            node->step = 0xC;
            break;
        }
        break;
    case 15:
        node->flag1E = 0;
        node->step = 0x10;
    case 16:
        if (node->flag1D) {
            if (node->flag1E) {
                if (((SceneNode*)currentDrawingItem)->state != 0) {
                    node->step = 1;
                }
            } else if (((SceneNode*)currentDrawingItem)->state != 0) {
                node->step = 0x12;
            }
        } else if (((SceneNode*)currentDrawingItem)->state != 0) {
            node->step = 0x12;
        }
        break;
    case 17:
        if ((u16)fn_8004157C() == 0) {
            node->step = 0x12;
        }
        break;
    case 18:
        mcardStopProbe();
        node->step++;
        break;
    case 19:
        if (cardCheck[0x49] != 0) {
            cardCheck[0x48] = 1;
            fn_8004A34C(cardCheck, node->slot, 0x4D, 0, 0);
        }
        ((SceneNode*)currentDrawingItem)->parent->state = node->result1C;
        text_freeAllBlocks();
        removeCurrentDrawingItem();
        break;
    }
}

void startMemoryCardCheck(void) {
    SceneNode* item = (SceneNode*)insertGraphicDrawingFunction(fn_8003F2B8, 0x8000);

    item->step = 0;
    item->slot = 0;
    item->arg16 = 0;
    item->chan = 0;
    item->flag18 = 0;
    item->mode1A = 0;
    item->mode1B = 7;
    item->flag1D = 0;
    item->_21 = 0;
    ((SceneNode*)currentDrawingItem)->state = 0;
    lbl_802D4AE0[3] = 0;
    lbl_802D4AE0[2] = 0;
    lbl_802D4AE0[1] = 0;
    lbl_802D4AE0[0] = 0;
}

void mcardCheckFile(u8 chan, u8 async, const char* fileName, u64 serialNo, u8 flag);

#define MCARD_SPAWN_CHECK_NODE(taskFn)                          \
    do {                                                        \
        newNode = (SceneNode*)insertGraphicDrawingFunction(taskFn, 0x8000); \
        newNode->step = 0;                                      \
        newNode->slot = node->slot;                             \
        newNode->arg16 = node->arg16;                           \
        newNode->chan = node->chan;                             \
        newNode->flag18 = node->flag18;                         \
        newNode->mode1A = node->mode1A;                         \
        newNode->flag1D = 0;                                    \
        newNode->idx20 = node->idx20;                           \
        newNode->mode1B = node->mode1B;                         \
        ((SceneNode*)currentDrawingItem)->state = 0;            \
        node->step++;                                           \
    } while (0)

void mcardDelete(u8 chan, u8 async, u64 serialNo);
void fn_8004A328(void* base);

void fn_8003F2B8(void) {
    SceneNode* node = (SceneNode*)currentDrawingItem;
    SceneNode* newNode;
    s32 probe;
    s32 status;
    u8 s21;
    u8 s1B;
    u8 s1A;
    u8 sChan;
    u8 s16v;
    u8 sSlot;
    u8* base;
    s32 i;
    s32 a;
    s32 b;
    s32 ok;
    u8* rec;
    u32 bits;
    u8 v;

    probe = mcardState.chan[node->chan].probeResult;
    MCARD_STATUS_FROM_PROBE(probe, status);
    if (status == 4 || status == 0x11) {
        node->flag1E = 1;
    } else if (status == 0) {
        node->flag1D = 1;
    }

    switch (node->step) {
    case 0:
        if (cardCheck[0x47] != 0) {
            node->step = 0x22;
            node->result1C = 0xB;
        } else if (cardCheck[0] != 0) {
            node->step = 0x22;
            node->result1C = 1;
        } else {
            mcardStartProbe();
            lbl_80366158[0x20] = 1;
            node->step = 1;
        }
        break;
    case 1:
        node->flag1D = 0;
        s21 = node->_21;
        s1B = node->mode1B;
        s1A = node->mode1A;
        sChan = node->chan;
        s16v = node->arg16;
        sSlot = node->slot;
        newNode = (SceneNode*)insertGraphicDrawingFunction(fn_8004053C, 0x8000);
        newNode->step = 0;
        newNode->slot = sSlot;
        newNode->arg16 = s16v;
        newNode->chan = sChan;
        newNode->flag18 = 1;
        newNode->mode1A = s1A;
        newNode->mode1B = s1B;
        newNode->flag1D = 0;
        newNode->_21 = s21;
        ((SceneNode*)currentDrawingItem)->state = 0;
        node->step++;
        break;
    case 2:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            node->flag1D = 0;
            switch (((SceneNode*)currentDrawingItem)->state) {
            case 1:
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                node->step = 0xB;
                break;
            case 6:
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                node->step = 0x10;
                break;
            case 10:
                node->step = 3;
                break;
            case 7:
            case 8:
                lbl_802D4AE0[node->chan] = 0;
                node->step = 1;
                break;
            case 9:
                cardCheck[0x44] = 1;
                node->step = 5;
                break;
            case 13:
                lbl_802D4AE0[node->chan] = mcardState.chan[node->chan].serialNo;
                node->step = 0xB;
                break;
            }
        }
        break;
    case 3:
        lbl_802D4AE0[node->chan] = 0;
        node->result1C = 0xA;
        node->step++;
        fn_8004A34C(cardCheck, node->slot, 2, 0, 0);
        break;
    case 4:
        switch (cardCheck[0x45]) {
        case 1:
        case 2:
            cardCheck[0x47] = 1;
            node->step = 0x21;
            node->result1C = 0xB;
            break;
        case 3:
        case 4:
            node->step = 1;
            break;
        }
        break;
    case 5:
        if (cardCheck[0x44] != 0) {
            lbl_802D4AE0[node->chan] = 0;
            fn_8004A34C(cardCheck, node->slot, 1, 0, 0);
            node->flag1D = 0;
            node->flag1E = 0;
            node->step++;
        }
        break;
    case 6:
        switch (cardCheck[0x45]) {
        case 1:
        case 2:
            node->step = 1;
            lbl_802D4AE0[node->chan] = 0;
            break;
        case 3:
        case 4:
            node->step = 3;
            break;
        }
        break;
    case 7:
        if ((u16)fn_8004157C() == 0) {
            mcardCheckSpace(node->chan, node->flag18, (s16)lbl_803CBC48, lbl_800E6910, lbl_802D4AE0[node->chan]);
            node->step++;
        }
        break;
    case 8:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            switch (mcardState.status) {
            case 0:
            case 8:
            case 0x10:
                node->step = 5;
                break;
            case 5:
                fn_8004A34C(cardCheck, node->slot, 0xF, 0, 0);
                node->step = 9;
                break;
            case 6:
                fn_8004A34C(cardCheck, node->slot, 0xE, 0, 0);
                node->step = 9;
                break;
            case 0x11:
                node->step = 0xD;
                break;
            default:
                lbl_802D4AE0[node->chan] = 0;
                node->step = 1;
                break;
            }
        }
        break;
    case 9:
        if (node->flag1D) {
            cardCheck[0x46] = 1;
            node->step = 5;
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                lbl_80366158[0x21] = 1;
                node->step = 0xA;
                break;
            case 3:
            case 4:
                node->step = 3;
                break;
            }
        }
        break;
    case 11:
        if (node->flag1D) {
            node->step = 5;
        } else {
            node->step++;
            fn_8004A34C(cardCheck, node->slot, 0xB, 0, 0);
        }
        break;
    case 12:
        if (node->flag1D) {
            cardCheck[9] = 1;
            if (((SceneNode*)currentDrawingItem)->state != 0) {
                cardCheck[0x46] = 1;
                cardCheck[9] = 0;
                node->step = 5;
            }
        } else if (node->flag1E) {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                fn_8004A34C(cardCheck, node->slot, 0, 0, 0);
                node->step = 7;
                fn_800415A0(0x32);
                break;
            case 3:
            case 4:
                node->step = 3;
                break;
            }
        } else {
            cardCheck[0x46] = 1;
            node->step = 5;
        }
        break;
    case 13:
        if ((u16)fn_8004157C() != 0) {
            break;
        }
        base = lbl_802D4B00;
        lbl_80366158[0x20] = 0;
        memset(base, 0, 0x10000 - 0x2AE4);
        memset(lbl_802D4B00 + 0x10000 - 0x2AE4, 0xEE, 0x2AE4);
        base[0x94] = audioFileDescriptors[0x397];
        base[0x95] = audioFileDescriptors[0x398];
        base[0x96] = lbl_80366158[0x1F];
        memcpy(base + 0x97, superstarUnlocked, 0xF7);
        memcpy(base + 0x190, lbl_803616CC, 0x454);
        base[0x5E4] = g_d_GameSettings[0x12];
        memcpy(base + 0x5E5, g_d_GameSettings + 0x14, 6);
        memcpy(base + 0x5EB, g_d_GameSettings + 0x1A, 6);
        *(u32*)(base + 0x5F4) = *(u32*)g_d_GameSettings;
        *(u16*)(lbl_802D4B00 + 0x46) = 0x5B4;
        for (i = 2; i >= 0; i--) {
            *(u16*)(lbl_802D4B00 + i * 0x450C + 0x5FA) = 0x450C;
        }
        newNode = (SceneNode*)insertGraphicDrawingFunction(fn_8003B5B0, 0x8000);
        newNode->step = 0;
        newNode->slot = node->slot;
        newNode->arg16 = node->arg16;
        newNode->chan = node->chan;
        newNode->flag18 = 1;
        newNode->mode1A = node->mode1A;
        newNode->mode1B = node->mode1B;
        newNode->flag1D = 0;
        ((SceneNode*)currentDrawingItem)->state = 0;
        node->step++;
        break;
    case 14:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            node->flag1D = 0;
            switch (((SceneNode*)currentDrawingItem)->state) {
            case 1:
                node->step = 0x21;
                node->result1C = 1;
                break;
            case 8:
                node->step = 3;
                break;
            case 5:
                fn_8004A34C(cardCheck, node->slot, 0x45, 0, 0);
                node->step = 0xF;
                break;
            case 2:
            case 3:
                fn_8004A34C(cardCheck, node->slot, 0x44, 0, 0);
                node->step = 0xF;
                break;
            case 9:
                node->step = 5;
                break;
            }
            lbl_80366158[0x20] = 1;
        }
        break;
    case 15:
        if (node->flag1D) {
            cardCheck[0x46] = 1;
            node->step = 5;
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->step = 1;
                break;
            case 3:
            case 4:
                node->step = 3;
                break;
            }
        }
        break;
    case 16:
        if (node->flag1D) {
            node->step = 5;
        } else {
            fn_8004A34C(cardCheck, node->slot, node->mode1A == 0 ? 0x10 : 0x22, 0, 0);
            fn_800415A0(0xB4);
            node->step++;
        }
        break;
    case 17:
        if ((u16)fn_8004157C() == 0) {
            MCARD_SPAWN_CHECK_NODE(fn_80040C14);
        }
        break;
    case 18:
        switch (((SceneNode*)currentDrawingItem)->state) {
        case 1:
            ok = 1;
            for (i = 0; i < 3 && ok; i++) {
                rec = lbl_802D4B00 + 0x5F8 + i * 0x450C;
                v = lbl_802D4B00[0x8E + i];
                if (v > 1) {
                    ok = 0;
                    break;
                }
                if ((s8)rec[0x160A] != 0 || rec[0x441F] != 0) {
                    for (a = 0; a < 9; a++) {
                        for (b = 0; b < 9; b++) {
                            if (*(s16*)(rec + 0x40BC + a * 6) == *(s16*)(rec + 0x40BC + b * 6) && a != b) {
                                ok = 0;
                            }
                        }
                    }
                    if (rec[0x4419] >= 4) {
                        ok = 0;
                    } else if (*(s16*)(rec + 0x43C0) < 0 || *(s16*)(rec + 0x43C0) > 1000) {
                        ok = 0;
                    }
                }
            }
            if (!ok) {
                node->step = 0x14;
            } else {
                fn_80041150(node->mode1B, 3);
                node->step = 0x21;
                node->result1C = 1;
            }
            break;
        case 2:
        case 4:
            node->step = 0x14;
            break;
        case 5:
            fn_8004A34C(cardCheck, node->slot, 0x11, 0, 0);
            node->step = 0x20;
            lbl_802D4AE0[node->chan] = 0;
            fn_8004A34C(cardCheck, node->slot, 0x11, 0, 0);
            node->step = 0x20;
            node->flag1E = 0;
            break;
        case 9:
            lbl_802D4AE0[node->chan] = 0;
            fn_8004A34C(cardCheck, node->slot, 0x11, 0, 0);
            node->step = 0x20;
            node->flag1E = 0;
            break;
        case 8:
            fn_8004A34C(cardCheck, node->slot, 0x11, 0, 0);
            node->step = 0x20;
            node->flag1E = 0;
            break;
        default:
            node->flag1E = 0;
            break;
        }
        break;
    case 19:
        if (node->flag1D) {
            if (((SceneNode*)currentDrawingItem)->state != 0) {
                node->step = 1;
                lbl_802D4AE0[node->chan] = 0;
            }
        } else if (((SceneNode*)currentDrawingItem)->state != 0) {
            node->step = 1;
            lbl_802D4AE0[node->chan] = 0;
        }
        break;
    case 20:
        fn_8004A34C(cardCheck, node->slot, 0x27, 0, 0);
        node->step = 0x15;
        break;
    case 21:
        if (node->flag1D) {
            cardCheck[0x46] = 1;
            node->step = 5;
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->step = 0x16;
                break;
            case 3:
            case 4:
                node->step = 3;
                break;
            }
        }
        break;
    case 22:
        if (cardCheck[0x44] != 0) {
            if (node->flag1D) {
                node->step = 5;
            } else {
                fn_8004A34C(cardCheck, node->slot, 0x28, 0, 0);
                node->step = 0x17;
            }
        }
        break;
    case 23:
        if (node->flag1D) {
            cardCheck[0x46] = 1;
            node->step = 5;
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->step = 0x18;
                fn_800415A0(0x32);
                break;
            }
        }
        break;
    case 24:
        if (node->flag1D) {
            node->step = 5;
        } else {
            mcardDelete(node->chan, node->flag18, lbl_802D4AE0[node->chan]);
            node->step = 0x19;
        }
        break;
    case 25:
        if (((SceneNode*)currentDrawingItem)->state != 0 && cardCheck[0x44] != 0) {
            node->step = 0xD;
        }
        break;
    case 26:
        fn_8004A34C(cardCheck, node->slot, 0x39, 0, 0);
        node->step = 0x1B;
        break;
    case 27:
        if (node->flag1D) {
            cardCheck[0x46] = 1;
            node->step = 5;
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                fn_8004A34C(cardCheck, node->slot, 0x3A, 0, 0);
                fn_800415A0(0x64);
                node->step = 0x1C;
                break;
            case 3:
            case 4:
                node->step = 3;
                break;
            }
        }
        break;
    case 28:
        if ((u16)fn_8004157C() != 0) {
            break;
        }
        newNode = (SceneNode*)insertGraphicDrawingFunction(sceneDrawingLogic, 0x8000);
        newNode->step = 0;
        newNode->slot = 0;
        newNode->arg16 = 0;
        newNode->chan = 0;
        newNode->flag18 = 0;
        newNode->_19 = 1;
        newNode->mode1A = 1;
        newNode->mode1B = 7;
        newNode->flag1D = 0;
        newNode->idx20 = 3;
        newNode->_21 = 5;
        lbl_802D4AE0[0] = 0;
        newNode->_1F = 2;
        ((SceneNode*)currentDrawingItem)->state = 0;
        node->step = 0x1D;
        break;
    case 29:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            if (((SceneNode*)currentDrawingItem)->state == 1) {
                fn_8004A34C(cardCheck, node->slot, 0x3B, 0, 0);
                node->step = 0x1E;
            } else {
                fn_8004A34C(cardCheck, node->slot, 0x3C, 0, 0);
                node->step = 0x1F;
            }
        }
        break;
    case 30:
        if (node->flag1D) {
            cardCheck[0x46] = 1;
            node->step = 5;
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->result1C = 1;
                node->step = 0x22;
                break;
            }
        }
        break;
    case 31:
        if (node->flag1D) {
            cardCheck[0x46] = 1;
            node->step = 5;
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->step = 3;
                break;
            }
        }
        break;
    case 32:
        if (node->flag1D) {
            cardCheck[0x46] = 1;
            node->step = 5;
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->step = 1;
                break;
            case 3:
            case 4:
                node->step = 3;
                break;
            }
        }
        break;
    case 33:
        fn_8004A328(cardCheck);
        mcardStopProbe();
        node->step++;
        break;
    case 34:
        if (cardCheck[0x49] != 0) {
            cardCheck[0x48] = 1;
            fn_8004A34C(cardCheck, node->slot, 0x4D, 0, 0);
        }
        ((SceneNode*)currentDrawingItem)->parent->state = node->result1C;
        text_freeAllBlocks();
        removeCurrentDrawingItem();
        break;
    }
}

void fn_8004053C(void) {
    SceneNode* node = (SceneNode*)currentDrawingItem;
    SceneNode* newNode;
    s32 probe;
    s32 status;
    s32 msg = 0;
    u8 savedSlot;
    u8 saved16;
    u8 savedChan;
    u8 saved18;
    u8 saved1A;

    probe = mcardState.chan[node->chan].probeResult;
    if (probe == -1) {
        status = 0xF;
    } else if (probe >= 0) {
        status = (probe < 1) ? 0x11 : -1;
    } else if (probe == -3) {
        status = 0;
    } else if (probe > -3) {
        status = 4;
    } else {
        status = -1;
    }
    if (status == 4 || status == 0x11) {
        node->flag1E = 1;
    } else if (status == 0) {
        node->flag1D = 1;
    }

    switch (node->step) {
    case 0:
        node->flag1D = 0;
        fn_8004A34C(cardCheck, node->slot, 0, 0, 0);
        fn_800415A0(0x64);
        node->step++;
        break;
    case 1:
        if ((u16)fn_8004157C() == 0) {
            node->step++;
        }
        break;
    case 2:
        if (node->flag1D) {
            node->step = 3;
        } else {
            node->step = 5;
        }
        break;
    case 3:
        node->flag1D = 0;
        node->flag1E = 0;
        node->step++;
        break;
    case 4:
        if (node->flag1E) {
            node->step = 0xE;
            node->result1C = 7;
        } else {
            node->step = 0xE;
            node->result1C = 9;
        }
        break;
    case 5:
        node->flag1D = 0;
        mcardCheckFile(node->chan, node->flag18, lbl_800E6910, lbl_802D4AE0[node->chan], node->mode1A == 0);
        node->step++;
        break;
    case 6:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            if (node->flag1D) {
                node->step = 3;
            } else {
                switch (mcardState.status) {
                case 0:
                    node->step = 3;
                    break;
                case 0x10:
                    node->step = 7;
                    break;
                case 1:
                    if (node->mode1A != 0) {
                        node->step = 7;
                    } else {
                        node->step = 0xA;
                    }
                    break;
                case 2:
                    if (node->mode1A != 0) {
                        node->step = 7;
                    } else {
                        node->step = 9;
                    }
                    break;
                case 3:
                case 4:
                case 7:
                    node->step = 7;
                    break;
                case 8:
                    node->step = 0xE;
                    node->result1C = 6;
                    break;
                case 0x11:
                    node->step = 0xE;
                    node->result1C = 1;
                    break;
                }
            }
        }
        break;
    case 7:
        switch (mcardState.status) {
        case 1:
            msg = (u8)(node->mode1A != 0 ? 0x15 : 6);
            break;
        case 2:
            msg = (u8)(node->mode1A != 0 ? 0x14 : 5);
            break;
        case 3:
            msg = 0x42;
            break;
        case 4:
            msg = 0x41;
            break;
        case 7:
            msg = 0x43;
            break;
        case 0x10:
            if (node->_21 == 3) {
                msg = 0x31;
            } else if (node->_21 == 2) {
                msg = 0x2A;
            } else if (node->mode1A == 2) {
                msg = 0x20;
            } else {
                msg = 0x13;
            }
            break;
        }
        fn_8004A34C(cardCheck, node->slot, msg, 0, 0);
        fn_800415A0(0x64);
        node->step++;
        break;
    case 8:
        if ((u16)fn_8004157C() != 0) {
            break;
        }
        if (node->flag1D) {
            cardCheck[0x46] = 1;
            node->step = 3;
        } else if (cardCheck[0x3F] == 5 || cardCheck[0x3F] == 6) {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->step = 0xC;
                break;
            case 3:
            case 4:
                node->step = 0xE;
                node->result1C = 0xA;
                break;
            }
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->step = 0;
                break;
            case 3:
            case 4:
                node->step = 0xE;
                if (node->mode1A == 0) {
                    node->result1C = 0xA;
                } else {
                    node->result1C = 0xB;
                }
                break;
            }
        }
        break;
    case 9:
        if (node->flag1D) {
            node->step = 3;
        } else {
            fn_8004A34C(cardCheck, node->slot, 5, 1, 0);
            node->step = 0xB;
        }
        break;
    case 0xA:
        if (node->flag1D) {
            node->step = 3;
        } else {
            fn_8004A34C(cardCheck, node->slot, 6, 1, 0);
            node->step = 0xB;
        }
        break;
    case 0xB:
        if (node->flag1D) {
            cardCheck[0x46] = 1;
            node->step = 3;
        } else {
            switch (cardCheck[0x45]) {
            case 1:
            case 2:
                node->step = 0xC;
                break;
            case 3:
            case 4:
                node->step = 0xE;
                node->result1C = 0xA;
                break;
            }
        }
        break;
    case 0xC:
        saved1A = node->mode1A;
        saved18 = node->flag18;
        savedChan = node->chan;
        saved16 = node->arg16;
        savedSlot = node->slot;
        newNode = (SceneNode*)insertGraphicDrawingFunction(fn_8003BB90, 0x8000);
        newNode->step = 0;
        newNode->slot = savedSlot;
        newNode->arg16 = saved16;
        newNode->chan = savedChan;
        newNode->flag18 = saved18;
        newNode->mode1A = saved1A;
        newNode->flag1D = 0;
        ((SceneNode*)currentDrawingItem)->state = 0;
        node->step++;
        break;
    case 0xD:
        switch (((SceneNode*)currentDrawingItem)->state) {
        case 1:
            node->step = 0xE;
            node->result1C = 0xD;
            break;
        case 2:
        case 5:
        case 9:
            node->step = 0xE;
            node->result1C = 0xA;
            break;
        case 8:
            node->step = 0xE;
            node->result1C = 7;
            break;
        case 7:
            node->step = 0;
            node->result1C = 7;
            break;
        }
        break;
    case 0xE:
        ((SceneNode*)currentDrawingItem)->parent->state = node->result1C;
        text_freeAllBlocks();
        removeCurrentDrawingItem();
        break;
    }
}

void mcardLoad(McardRequest* req, u64 serialNo);
u32 fn_80041074(void* buffer, s32 size, u32 arg);

void fn_80040C14(void) {
    SceneNode* node = (SceneNode*)currentDrawingItem;
    McardRequest req;
    s32 probe;
    s32 status;
    u32 bits;
    u32 found;
    u32 mask;
    s32 k;
    u16 value;

    probe = mcardState.chan[node->chan].probeResult;
    if (probe == -1) {
        status = 0xF;
    } else if (probe >= 0) {
        status = (probe < 1) ? 0x11 : -1;
    } else if (probe == -3) {
        status = 0;
    } else if (probe > -3) {
        status = 4;
    } else {
        status = -1;
    }
    if (status == 4 || status == 0) {
        node->flag1D = 1;
    }

    switch (node->step) {
    case 0:
        node->flag1D = 0;
        req.fileName = lbl_800E6910;
        req.buffer = lbl_802D4B00;
        req.size = 0x10000;
        req.chan = node->chan;
        req.async = node->flag18;
        req.attr = 0;
        req.callback = fn_80041074;
        bits = 0;
        if ((node->mode1B & 7) == 7) {
            bits = 0xF;
        } else if (node->mode1B & 2) {
            if (node->idx20 == 3) {
                bits |= 3;
            } else {
                bits = 1 << (node->idx20 + 1);
            }
        }
        req.callbackArg = bits;
        req.flags = 1;
        mcardLoad(&req, lbl_802D4AE0[node->chan]);
        node->step++;
        break;
    case 1:
        if (((SceneNode*)currentDrawingItem)->state != 0) {
            if (node->flag1D) {
                node->result1C = 9;
            } else {
                switch (mcardState.status) {
                case 0x11:
                    bits = 0;
                    if ((node->mode1B & 7) == 7) {
                        bits = 0xF;
                    } else if (node->mode1B & 2) {
                        if (node->idx20 == 3) {
                            bits |= 3;
                        } else {
                            bits = 1 << (node->idx20 + 1);
                        }
                    }
                    found = 0;
                    for (k = 0; k < 4; k++) {
                        mask = 1 << k;
                        if (bits & mask) {
                            if (k == 0) {
                                value = *(u16*)(lbl_802D4B00 + 0x46);
                                if (value != 0x5B4) {
                                    found = mask;
                                }
                            } else {
                                value = *(u16*)(lbl_802D4B00 + (k - 1) * 0x450C + 0x5FA);
                                if (value != 0x450C) {
                                    found |= mask;
                                }
                            }
                        }
                    }
                    if (found == 0) {
                        node->result1C = 1;
                    } else {
                        node->result1C = 4;
                    }
                    break;
                case 0:
                    node->result1C = 9;
                    break;
                case 0x10:
                    node->result1C = 8;
                    break;
                case 0xB:
                    node->result1C = 4;
                    break;
                case 3:
                    node->result1C = 5;
                    break;
                default:
                    node->result1C = 2;
                    break;
                }
            }
            node->step = 2;
        }
        break;
    case 2:
        ((SceneNode*)currentDrawingItem)->parent->state = node->result1C;
        text_freeAllBlocks();
        removeCurrentDrawingItem();
        break;
    }
}

