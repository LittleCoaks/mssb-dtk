#include "menus/text_94854.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/orderchange.h"
#include "text/text.h"

extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_2_bss_1033C[0x10];
extern UIRecordDescriptor lbl_2_data_30D04[];
extern UIRecordDescriptor lbl_2_data_311E4[];
extern u8 gameSetUpStep[0x64];
extern u8 menuNumber[0x28];
extern u8 lbl_800FEF70[0x5D0];
extern void fn_80053FE8(void);
void load_Icon(void *scene, int handle, u32 part, u32 element, int frame);

typedef struct MenuFlowState {
    /* 0x00 */ u8 unk0[0x2];
    /* 0x02 */ s16 selected;
    /* 0x04 */ s16 pending;
    /* 0x06 */ s8 active;
    /* 0x07 */ s8 unk7;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ s8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC[0x2];
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
} MenuFlowState;

static UIRecord *sceneRecord(MenuScene *scene, s32 index) {
    return (UIRecord *)graphicsRelatedArray[scene->firstHandle + index].object;
}

// .text:0x00094854 size:0x18 mapped:0x806D38E8
void fn_2_94854(u8 value) {
    *(lbl_2_bss_1A824C + 0x197849) = value;
}

// .text:0x0009486C size:0x4C mapped:0x806D3900
void fn_2_9486C(void) {
    DrawingSceneStruct *node = currentDrawingItem;

    if (lbl_2_bss_1033C[0xF] != 0) {
        lbl_2_bss_1033C[0xF] = 0;
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}

// .text:0x000948B8 size:0x84 mapped:0x806D394C
void fn_2_948B8(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    MenuScene *scene;

    lbl_2_bss_1033C[0xF] = 0;
    addGraphicsElementToScene(node, lbl_2_data_311E4);
    scene = (MenuScene *)node;
    sceneRecord(scene, 0)->frame = 0x280000;
    currentDrawingItem->func = fn_2_9486C;
}

// .text:0x0009493C size:0x150 mapped:0x806D39D0
static inline void gate9493C(MenuScene *scene) {
    MenuFlowState *flow = (MenuFlowState *)lbl_2_bss_1033C;
    BOOL gate = FALSE;
    BOOL wanted = FALSE;

    if (gameSetUpStep[0x4F] == 1) {
        if (flow->active != 0 && flow->selected == 0 && flow->unkB == 0) {
            wanted = TRUE;
            gate = maybeCheckAndResetGrapicsElement(scene, 0x13, 0) != 0;
        }
        if (gate == wanted) {
            if (flow->active != 0 && flow->selected == 0 && flow->unkB == 0) {
                sceneRecord(scene, 19)->frame = 0;
                sceneRecord(scene, 22)->frame = 0;
                sceneRecord(scene, 19)->elementIndex = 0x1A;
                sceneRecord(scene, 22)->elementIndex = 0x10;
            }
            makeCursorMovable(0);
            gameSetUpStep[0x4F] = 2;
        }
    }
}

void fn_2_9493C(MenuScene *scene) {
    gate9493C(scene);
}

// .text:0x00094A8C size:0xB78 mapped:0x806D3B20
void fn_2_94A8C(MenuScene *scene) {
    MenuFlowState *flow = (MenuFlowState *)lbl_2_bss_1033C;
    s16 sel = flow->selected;
    s32 i;

    if (gameSetUpStep[0x4F] == 0) {
        if (flow->unkB != 0) {
            switch (sel) {
            case 0:
                sceneRecord(scene, 24)->frame = 0;
                sceneRecord(scene, 25)->frame = 0;
                if (flow->active != 0) {
                    sceneRecord(scene, 24)->elementIndex = 0x18;
                    sceneRecord(scene, 25)->elementIndex = 0x15;
                    sceneRecord(scene, 24)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(scene, 25)->playMode = UI_PLAY_STOP;
                    sceneRecord(scene, 31)->rgba = (sceneRecord(scene, 31)->rgba & ~0xFF) | 0xFF;
                } else {
                    sceneRecord(scene, 24)->elementIndex = 0x15;
                    sceneRecord(scene, 25)->elementIndex = 0x18;
                    sceneRecord(scene, 24)->playMode = UI_PLAY_STOP;
                    sceneRecord(scene, 25)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(scene, 32)->rgba = (sceneRecord(scene, 32)->rgba & ~0xFF) | 0xFF;
                }
                break;
            case 1:
                for (i = 0; i < 3; i++) {
                    sceneRecord(scene, i + 26)->frame = 0;
                    if (flow->unk7 == i) {
                        sceneRecord(scene, i + 26)->elementIndex = 0x18;
                        sceneRecord(scene, i + 26)->playMode = UI_PLAY_FORWARD;
                        sceneRecord(scene, i + 33)->rgba = (sceneRecord(scene, i + 33)->rgba & ~0xFF) | 0xFF;
                    } else {
                        sceneRecord(scene, i + 26)->elementIndex = 0x15;
                        sceneRecord(scene, i + 26)->playMode = UI_PLAY_STOP;
                    }
                }
                break;
            case 2:
                sceneRecord(scene, 29)->frame = 0;
                sceneRecord(scene, 30)->frame = 0;
                if (flow->unk8 != 0) {
                    sceneRecord(scene, 29)->elementIndex = 0x18;
                    sceneRecord(scene, 30)->elementIndex = 0x15;
                    sceneRecord(scene, 29)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(scene, 30)->playMode = UI_PLAY_STOP;
                    sceneRecord(scene, 36)->rgba = (sceneRecord(scene, 36)->rgba & ~0xFF) | 0xFF;
                } else {
                    sceneRecord(scene, 29)->elementIndex = 0x15;
                    sceneRecord(scene, 30)->elementIndex = 0x18;
                    sceneRecord(scene, 29)->playMode = UI_PLAY_STOP;
                    sceneRecord(scene, 30)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(scene, 37)->rgba = (sceneRecord(scene, 37)->rgba & ~0xFF) | 0xFF;
                }
                break;
            default:
                break;
            }
            sceneRecord(scene, sel + 18)->frame = 0xA0000;
            sceneRecord(scene, sel + 18)->playMode = UI_PLAY_BACKWARD;
            sceneRecord(scene, sel + 15)->frame = 0xA0000;
            sceneRecord(scene, sel + 15)->playMode = UI_PLAY_BACKWARD;
            sceneRecord(scene, sel + 12)->rgba = sceneRecord(scene, sel + 12)->rgba & ~0xFF;
            sceneRecord(scene, sel + 21)->frame = 0;
            sceneRecord(scene, sel + 21)->playMode = UI_PLAY_FORWARD;
        } else {
            switch (sel) {
            case 0:
                sceneRecord(scene, 24)->frame = 0;
                sceneRecord(scene, 25)->frame = 0;
                if (flow->active != 0) {
                    sceneRecord(scene, 7)->frame = 0xF0000;
                    sceneRecord(scene, 7)->playMode = UI_PLAY_STOP;
                    sceneRecord(scene, 24)->elementIndex = 0x18;
                    sceneRecord(scene, 25)->elementIndex = 0x15;
                    sceneRecord(scene, 24)->playMode = UI_PLAY_STOP;
                    sceneRecord(scene, 25)->playMode = UI_PLAY_STOP;
                    sceneRecord(scene, 31)->rgba = sceneRecord(scene, 31)->rgba & ~0xFF;
                    sceneRecord(scene, 32)->rgba = sceneRecord(scene, 32)->rgba & ~0xFF;
                    for (i = 0; i < 3; i++) {
                        sceneRecord(scene, i + 26)->frame = 0;
                        sceneRecord(scene, i + 26)->elementIndex = (flow->unk7 == i) ? 0x19 : 0x17;
                        sceneRecord(scene, i + 26)->playMode = UI_PLAY_BACKWARD;
                    }
                    sceneRecord(scene, 22)->elementIndex = 0x11;
                    sceneRecord(scene, 22)->playMode = UI_PLAY_BACKWARD;
                    sceneRecord(scene, 19)->elementIndex = 0x1B;
                    sceneRecord(scene, 19)->playMode = UI_PLAY_BACKWARD;
                } else {
                    sceneRecord(scene, 7)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(scene, 24)->elementIndex = 0x15;
                    sceneRecord(scene, 25)->elementIndex = 0x18;
                    sceneRecord(scene, 24)->playMode = UI_PLAY_STOP;
                    sceneRecord(scene, 25)->playMode = UI_PLAY_STOP;
                    sceneRecord(scene, 31)->rgba = sceneRecord(scene, 31)->rgba & ~0xFF;
                    sceneRecord(scene, 32)->rgba = sceneRecord(scene, 32)->rgba & ~0xFF;
                    for (i = 0; i < 3; i++) {
                        sceneRecord(scene, i + 26)->elementIndex = (flow->unk7 == i) ? 0x19 : 0x17;
                        sceneRecord(scene, i + 26)->playMode = UI_PLAY_FORWARD;
                    }
                    sceneRecord(scene, 22)->elementIndex = 0x11;
                    sceneRecord(scene, 22)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(scene, 19)->elementIndex = 0x1B;
                    sceneRecord(scene, 19)->playMode = UI_PLAY_FORWARD;
                }
                break;
            case 1:
                for (i = 0; i < 3; i++) {
                    sceneRecord(scene, i + 26)->frame = 0;
                    if (flow->unk7 == i) {
                        sceneRecord(scene, i + 26)->elementIndex = 0x18;
                        sceneRecord(scene, i + 26)->playMode = UI_PLAY_STOP;
                        sceneRecord(scene, 33)->rgba = sceneRecord(scene, 33)->rgba & ~0xFF;
                        sceneRecord(scene, 34)->rgba = sceneRecord(scene, 34)->rgba & ~0xFF;
                        sceneRecord(scene, 35)->rgba = sceneRecord(scene, 35)->rgba & ~0xFF;
                    } else {
                        sceneRecord(scene, i + 26)->elementIndex = 0x15;
                        sceneRecord(scene, i + 26)->playMode = UI_PLAY_STOP;
                    }
                }
                break;
            case 2:
                sceneRecord(scene, 29)->frame = 0;
                sceneRecord(scene, 30)->frame = 0;
                if (flow->unk8 != 0) {
                    sceneRecord(scene, 29)->elementIndex = 0x18;
                    sceneRecord(scene, 30)->elementIndex = 0x15;
                } else {
                    sceneRecord(scene, 29)->elementIndex = 0x15;
                    sceneRecord(scene, 30)->elementIndex = 0x18;
                }
                sceneRecord(scene, 29)->playMode = UI_PLAY_STOP;
                sceneRecord(scene, 30)->playMode = UI_PLAY_STOP;
                sceneRecord(scene, 36)->rgba = sceneRecord(scene, 36)->rgba & ~0xFF;
                sceneRecord(scene, 37)->rgba = sceneRecord(scene, 37)->rgba & ~0xFF;
                break;
            default:
                break;
            }
            sceneRecord(scene, sel + 18)->frame = 0;
            sceneRecord(scene, sel + 18)->playMode = UI_PLAY_FORWARD;
            sceneRecord(scene, sel + 15)->frame = 0;
            sceneRecord(scene, sel + 15)->playMode = UI_PLAY_FORWARD;
            sceneRecord(scene, sel + 12)->rgba = sceneRecord(scene, sel + 12)->rgba & ~0xFF;
            sceneRecord(scene, sel + 21)->frame = 0xA0000;
            sceneRecord(scene, sel + 21)->playMode = UI_PLAY_BACKWARD;
        }
        makeCursorUnmovable(0);
        gameSetUpStep[0x4F] = 1;
    }
}

// .text:0x00095604 size:0x50 mapped:0x806D4698
static inline void cursorFinishGate(void) {
    if (gameSetUpStep[0x4F] == 1) {
        makeCursorMovable(0);
        gameSetUpStep[0x4F] = 2;
    }
}

void fn_2_95604(void) {
    cursorFinishGate();
}

// .text:0x00095654 size:0x4D4 mapped:0x806D46E8
void fn_2_95654(MenuScene *scene) {
    MenuFlowState *flow = (MenuFlowState *)lbl_2_bss_1033C;
    s32 i;

    if (gameSetUpStep[0x4F] == 0) {
        switch (flow->selected) {
        case 0:
            sceneRecord(scene, 24)->elementIndex = 0x15;
            sceneRecord(scene, 25)->elementIndex = 0x15;
            if (flow->active != 0) {
                sceneRecord(scene, 24)->frame = 0;
                sceneRecord(scene, 25)->frame = 0xF0000;
                sceneRecord(scene, 24)->playMode = UI_PLAY_FORWARD;
                sceneRecord(scene, 25)->playMode = UI_PLAY_BACKWARD;
                sceneRecord(scene, 31)->rgba = (sceneRecord(scene, 31)->rgba & ~0xFF) | 0xFF;
                sceneRecord(scene, 32)->rgba &= ~0xFF;
            } else {
                sceneRecord(scene, 24)->frame = 0xF0000;
                sceneRecord(scene, 25)->frame = 0;
                sceneRecord(scene, 24)->playMode = UI_PLAY_BACKWARD;
                sceneRecord(scene, 25)->playMode = UI_PLAY_FORWARD;
                sceneRecord(scene, 31)->rgba &= ~0xFF;
                sceneRecord(scene, 32)->rgba = (sceneRecord(scene, 32)->rgba & ~0xFF) | 0xFF;
            }
            break;
        case 1:
            sceneRecord(scene, 26)->elementIndex = 0x15;
            sceneRecord(scene, 27)->elementIndex = 0x15;
            sceneRecord(scene, 28)->elementIndex = 0x15;
            for (i = 0; i < 3; i++) {
                if (flow->active == 0) {
                    continue;
                }
                if (flow->unk7 == i) {
                    sceneRecord(scene, i + 26)->frame = 0;
                    sceneRecord(scene, i + 26)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(scene, i + 33)->rgba = (sceneRecord(scene, i + 33)->rgba & ~0xFF) | 0xFF;
                } else {
                    if (flow->unk9 == i) {
                        sceneRecord(scene, i + 26)->frame = 0xF0000;
                        sceneRecord(scene, i + 26)->playMode = UI_PLAY_BACKWARD;
                    } else {
                        sceneRecord(scene, i + 26)->frame = 0;
                        sceneRecord(scene, i + 26)->playMode = UI_PLAY_STOP;
                    }
                    sceneRecord(scene, i + 33)->rgba &= ~0xFF;
                }
            }
            break;
        case 2:
            sceneRecord(scene, 29)->elementIndex = 0x15;
            sceneRecord(scene, 30)->elementIndex = 0x15;
            if (flow->unk8 != 0) {
                sceneRecord(scene, 29)->frame = 0;
                sceneRecord(scene, 30)->frame = 0xF0000;
                sceneRecord(scene, 29)->playMode = UI_PLAY_FORWARD;
                sceneRecord(scene, 30)->playMode = UI_PLAY_BACKWARD;
                sceneRecord(scene, 36)->rgba = (sceneRecord(scene, 36)->rgba & ~0xFF) | 0xFF;
                sceneRecord(scene, 37)->rgba &= ~0xFF;
            } else {
                sceneRecord(scene, 29)->frame = 0xF0000;
                sceneRecord(scene, 30)->frame = 0;
                sceneRecord(scene, 29)->playMode = UI_PLAY_BACKWARD;
                sceneRecord(scene, 30)->playMode = UI_PLAY_FORWARD;
                sceneRecord(scene, 36)->rgba &= ~0xFF;
                sceneRecord(scene, 37)->rgba = (sceneRecord(scene, 37)->rgba & ~0xFF) | 0xFF;
            }
            break;
        default:
            break;
        }
        makeCursorUnmovable(0);
        gameSetUpStep[0x4F] = 1;
    }
}

// .text:0x00095B28 size:0x50 mapped:0x806D4BBC
void fn_2_95B28(void) {
    cursorFinishGate();
}

// .text:0x00095B78 size:0x308 mapped:0x806D4C0C
void fn_2_95B78(MenuScene *scene) {
    MenuFlowState *flow = (MenuFlowState *)lbl_2_bss_1033C;
    s32 i;

    if (gameSetUpStep[0x4F] == 0) {
        for (i = 0; i < 3; i++) {
            if (i == flow->selected) {
                sceneRecord(scene, i + 15)->frame = 0;
                sceneRecord(scene, i + 15)->playMode = UI_PLAY_FORWARD;
                sceneRecord(scene, i + 18)->frame = 0;
                sceneRecord(scene, i + 18)->playMode = UI_PLAY_FORWARD;
                sceneRecord(scene, i + 6)->playMode = UI_PLAY_BACKWARD;
            } else if (i == flow->pending) {
                sceneRecord(scene, i + 15)->frame = 0xA0000;
                sceneRecord(scene, i + 15)->playMode = UI_PLAY_BACKWARD;
                sceneRecord(scene, i + 18)->frame = 0xA0000;
                sceneRecord(scene, i + 18)->playMode = UI_PLAY_BACKWARD;
                sceneRecord(scene, i + 6)->playMode = UI_PLAY_FORWARD;
            } else if (flow->active != 0 || i != 1) {
                sceneRecord(scene, i + 15)->frame = 0;
                sceneRecord(scene, i + 15)->playMode = UI_PLAY_STOP;
                sceneRecord(scene, i + 18)->frame = 0;
                sceneRecord(scene, i + 18)->playMode = UI_PLAY_STOP;
                sceneRecord(scene, i + 6)->frame = 0xF0000;
                sceneRecord(scene, i + 6)->playMode = UI_PLAY_STOP;
            }
        }
        sceneRecord(scene, 3)->frame = 0;
        sceneRecord(scene, 3)->playMode = UI_PLAY_FORWARD;
        load_Icon(scene, 3, 1, 4, flow->selected);
        sceneRecord(scene, 4)->playMode = UI_PLAY_FORWARD;
        sceneRecord(scene, 4)->frame = 0;
        load_Icon(scene, 4, 1, 3, flow->selected);
        sceneRecord(scene, 4)->playMode = UI_PLAY_FORWARD;
        makeCursorUnmovable(0);
        gameSetUpStep[0x4F] = 1;
    }
}

// .text:0x00095E80 size:0xBC mapped:0x806D4F14
static inline void gate95E80(MenuScene *scene) {
    if (gameSetUpStep[0x4F] == 1) {
        BOOL found = maybeCheckAndResetGrapicsElement(scene, 0, 0) != 0;

        if ((sceneRecord(scene, 0)->frame >> 16) == 3) {
            changeScene(3, 6);
        }
        if (found) {
            lbl_2_bss_1033C[0xE] = 1;
            makeCursorMovable(0);
            gameSetUpStep[0x4F] = 2;
        }
    }
}

void fn_2_95E80(MenuScene *scene) {
    gate95E80(scene);
}

// .text:0x00095F3C size:0xA4 mapped:0x806D4FD0
static inline void gate95F3C(MenuScene *scene) {
    if (!gameSetUpStep[0x4F]) {
        sceneRecord(scene, 0)->playMode = UI_PLAY_BACKWARD;
        sceneRecord(scene, 1)->playMode = UI_PLAY_BACKWARD;
        sceneRecord(scene, 3)->playMode = UI_PLAY_BACKWARD;
        sceneRecord(scene, 4)->playMode = UI_PLAY_BACKWARD;
        makeCursorUnmovable(0);
        gameSetUpStep[0x4F] = 1;
    }
}

void fn_2_95F3C(MenuScene *scene) {
    gate95F3C(scene);
}

// .text:0x00095FE0 size:0x138 mapped:0x806D5074
static inline void gate95FE0(MenuScene *scene) {
    MenuFlowState *flow = (MenuFlowState *)lbl_2_bss_1033C;
    s32 hits;
    s32 total;
    s32 i;

    if (gameSetUpStep[0x4F] == 1) {
        total = 1;
        hits = maybeCheckAndResetGrapicsElement(scene, 0, 0xF) != 0;
        for (i = 0; i < 3; i++) {
            if (i != flow->selected) {
                total++;
                hits += maybeCheckAndResetGrapicsElement(scene, i + 6, 0xF) != 0;
            }
        }
        if (hits == total) {
            changeScene(1, 6);
            sceneRecord(scene, 6)->rgba = (sceneRecord(scene, 6)->rgba & ~0xFF) | 0xFF;
            sceneRecord(scene, 7)->rgba = (sceneRecord(scene, 7)->rgba & ~0xFF) | 0xFF;
            sceneRecord(scene, 8)->rgba = (sceneRecord(scene, 8)->rgba & ~0xFF) | 0xFF;
            makeCursorMovable(0);
            gameSetUpStep[0x4F] = 2;
        }
    }
}

void fn_2_95FE0(MenuScene *scene) {
    gate95FE0(scene);
}

// .text:0x00096118 size:0x580 mapped:0x806D51AC
void fn_2_96118(MenuScene *scene) {
    MenuFlowState *flow = (MenuFlowState *)lbl_2_bss_1033C;
    s32 i;
    s32 j;

    if (gameSetUpStep[0x4F] == 0) {
        sceneRecord(scene, 0)->playMode = UI_PLAY_FORWARD;
        for (i = 0; i < 3; i++) {
            if (i == flow->selected) {
                sceneRecord(scene, i + 15)->frame = 0;
                sceneRecord(scene, i + 15)->playMode = UI_PLAY_FORWARD;
                sceneRecord(scene, i + 18)->frame = 0;
                sceneRecord(scene, i + 18)->playMode = UI_PLAY_FORWARD;
            } else if (flow->active != 0 || i != 1) {
                sceneRecord(scene, i + 15)->frame = 0;
                sceneRecord(scene, i + 15)->playMode = UI_PLAY_STOP;
                sceneRecord(scene, i + 18)->frame = 0;
                sceneRecord(scene, i + 18)->playMode = UI_PLAY_STOP;
                sceneRecord(scene, i + 6)->frame = 0;
                sceneRecord(scene, i + 6)->playMode = UI_PLAY_FORWARD;
            }

            switch (i) {
            case 0:
                sceneRecord(scene, 24)->frame = 0;
                sceneRecord(scene, 25)->frame = 0;
                if (flow->active != 0) {
                    sceneRecord(scene, 24)->elementIndex = 0x18;
                    sceneRecord(scene, 25)->elementIndex = 0x15;
                } else {
                    sceneRecord(scene, 24)->elementIndex = 0x15;
                    sceneRecord(scene, 25)->elementIndex = 0x18;
                }
                sceneRecord(scene, 24)->playMode = UI_PLAY_STOP;
                sceneRecord(scene, 25)->playMode = UI_PLAY_STOP;
                break;
            case 1:
                for (j = 0; j < 3; j++) {
                    sceneRecord(scene, j + 26)->frame = 0;
                    if (flow->active != 0) {
                        if (flow->unk7 == j) {
                            sceneRecord(scene, j + 26)->elementIndex = 0x18;
                        } else {
                            sceneRecord(scene, j + 26)->elementIndex = 0x15;
                        }
                        sceneRecord(scene, j + 26)->playMode = UI_PLAY_STOP;
                    } else {
                        sceneRecord(scene, 7)->playMode = UI_PLAY_FORWARD;
                        if (flow->unk7 == j) {
                            sceneRecord(scene, j + 26)->elementIndex = 0x19;
                        } else {
                            sceneRecord(scene, j + 26)->elementIndex = 0x17;
                        }
                        sceneRecord(scene, j + 26)->playMode = UI_PLAY_FORWARD;
                    }
                }
                break;
            case 2:
                sceneRecord(scene, 29)->frame = 0;
                sceneRecord(scene, 30)->frame = 0;
                if (flow->unk8 != 0) {
                    sceneRecord(scene, 29)->elementIndex = 0x18;
                    sceneRecord(scene, 30)->elementIndex = 0x15;
                } else {
                    sceneRecord(scene, 29)->elementIndex = 0x15;
                    sceneRecord(scene, 30)->elementIndex = 0x18;
                }
                sceneRecord(scene, 29)->playMode = UI_PLAY_STOP;
                sceneRecord(scene, 30)->playMode = UI_PLAY_STOP;
                break;
            default:
                break;
            }

            sceneRecord(scene, i + 12)->rgba &= ~0xFF;
            sceneRecord(scene, i + 21)->frame = 0;
            sceneRecord(scene, i + 21)->playMode = UI_PLAY_STOP;
        }
        makeCursorUnmovable(0);
        gameSetUpStep[0x4F] = 1;
    }
}

// .text:0x00096698 size:0x43C mapped:0x806D572C
void fn_2_96698(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    MenuScene *scene = (MenuScene *)node;
    MenuFlowState *flow = (MenuFlowState *)lbl_2_bss_1033C;
    s32 i;

    switch (gameSetUpStep[0x5D]) {
    case 0x59:
        fn_2_96118(scene);
        gate95FE0(scene);
        break;
    case 0x5A:
        gate95F3C(scene);
        gate95E80(scene);
        break;
    case 0x5B:
        if (flow->unkB != 0) {
            fn_2_95654(scene);
        } else {
            fn_2_95B78(scene);
        }
        cursorFinishGate();
        break;
    case 0x5C:
        fn_2_94A8C(scene);
        gate9493C(scene);
        break;
    default:
        break;
    }
    if (flow->unkE != 0) {
        flow->unkE = 0;
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}

// .text:0x00096AD4 size:0x24C mapped:0x806D5B68
void fn_2_96AD4(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    MenuScene *scene = (MenuScene *)node;
    MenuFlowState *flow = (MenuFlowState *)lbl_2_bss_1033C;
    s32 i;

    addGraphicsElementToScene(node, lbl_2_data_30D04);
    for (i = 0; i < 3; i++) {
        load_Icon(node, i + 15, 1, 0, i);
        load_Icon(node, i + 15, 2, 0, i);
        load_Icon(node, i + 21, 1, 1, i);
        load_Icon(node, i + 21, 2, 1, i);
        if (i == 0) {
            load_Icon(node, 0x18, 1, 2, 0);
            load_Icon(node, 0x19, 1, 2, 1);
        } else if (i == 1) {
            load_Icon(node, 0x1A, 1, 2, 3);
            load_Icon(node, 0x1B, 1, 2, 2);
            load_Icon(node, 0x1C, 1, 2, 4);
        } else if (i == 2) {
            load_Icon(node, 0x1D, 1, 2, 0);
            load_Icon(node, 0x1E, 1, 2, 1);
        }
    }
    load_Icon(node, 4, 1, 3, 0);
    load_Icon(node, 3, 1, 4, 0);
    if (flow->active == 0) {
        sceneRecord(scene, 19)->frame = 0;
        sceneRecord(scene, 16)->playMode = UI_PLAY_STOP;
        sceneRecord(scene, 19)->elementIndex = 0x1B;
        sceneRecord(scene, 22)->elementIndex = 0x11;
    }
    currentDrawingItem->func = fn_2_96698;
}

// .text:0x00096D20 size:0x74 mapped:0x806D5DB4
void fn_2_96D20(void) {
    u8 previous;

    insertGraphicDrawingFunction(fn_80053FE8, 0x3000);
    previous = menuNumber[8];
    menuNumber[9] = previous;
    menuNumber[0] = 0x5B;
    menuNumber[8] = (u8)*(u16 *)(lbl_800FEF70 + 0x5B8);
    insertGraphicDrawingFunction(fn_2_948B8, 0x3000);
    insertGraphicDrawingFunction(fn_2_96AD4, 0x3000);
}
