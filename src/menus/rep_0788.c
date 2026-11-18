#define SQRT2_LINKAGE static
#include "menus/rep_0788.h"
#include "header_rep_data.h"
#include "game/challenge/challenge_state.h"
#include "game/challenge/star_mission_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800363d8.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "menus/rep_0DE0.h"
#include "Dolphin/GX/GXPixel.h"

#define SCENE_RECORD(scene, rec) \
    (graphicsRelatedArray[*(u16 *)((u8 *)(scene) + 0x14) + *(s16 *)((u8 *)(rec) + 0xE)].object)

/* characters[idx].inGameMissionTracker, reached by byte offset (+0x9). */
#define MISSION_TRACKER(idx) \
    ((starMissionTrackingPair *)((u8 *)&lbl_2_bss_1A8248->characters[idx] + 9))

#define SET_DIGIT(digit, value, place)   \
    switch (place) {                     \
    case 0:                              \
        (digit) = (value) / 100;         \
        break;                           \
    case 1:                              \
        (digit) = (value) / 10 % 10;     \
        break;                           \
    case 2:                              \
        (digit) = (value) % 10;          \
        break;                           \
    }

static inline void setRecordFrame(void *scene, void *rec, u32 frame) {
    ((UIRecord *)SCENE_RECORD(scene, rec))->frame = frame;
}

static inline void setRecordPlayMode(void *scene, void *rec, u8 mode) {
    ((UIRecord *)SCENE_RECORD(scene, rec))->playMode = mode;
}

static inline s16 abs16(int v) {
    return v < 0 ? -v : v;
}

void fn_80036270(void *scene, u32 element, u32 part, int frame, s16 *x, s16 *y);
void fn_2_68E68(void);
void fn_2_8FD14(void);
void fn_2_8AEE0(void);
void fn_2_47FF8(void);
void fn_2_47CFC(void);
extern DrawingSceneStruct *currentDrawingItem;
extern s16 lbl_2_data_3D30[][4];
extern u8 *lbl_2_bss_1A824C;
extern ChallengeState *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A8244;
extern s16 lbl_2_data_3714[];
extern u8 lbl_800E869C[0x20];
extern s16 lbl_2_data_38C0[];
extern s16 lbl_2_data_373C[];
extern u8 lbl_2_data_3764[];
extern u8 challengeCaptainCharIDs[];
extern int determineIfMissionDescriptionIsShown(int charID);
extern int fn_8006CDC0(int charID);
extern int fn_2_44E2C(int charIdx);
extern s32 fn_80062890(s32 arg0);
extern int fn_2_44F14(s32 charID);
extern s32 challenge_isCharRecruited(u8 arg0);

void fn_2_54354(void *arg0, int count);
void fn_2_54234(void *arg0, int count);
s16 fn_2_53BC8(void *arg0);
s16 fn_2_53AA4(void *arg0);
extern s16 lbl_2_data_1050C[4][6];
extern s16 lbl_2_data_1053C[4][6];
extern s16 lbl_2_data_1056C[4][6];
extern s16 lbl_2_data_107BC[];
extern u8 lbl_2_data_1073C[0x80];
extern u8 lbl_2_data_105FC[0x20];
extern u8 lbl_2_data_F0EC[0x13A0];
extern u8 lbl_2_data_9FC8[0x2930];
extern u8 lbl_2_data_104EC[0x20];
extern u8 lbl_2_data_1061C[0x120];
extern u8 lbl_2_data_C96C[0x2780];
extern u8 lbl_2_data_1059C[0x60];
extern u8 lbl_2_data_4C68[0x5360];
extern u8 *lbl_2_bss_1A8234;
extern u8 *lbl_2_bss_1A8230;
extern u8 lbl_2_data_1048C[0x60];
extern s16 lbl_2_data_2E44[4][4];
extern int rand(void);
extern void *memcpy(void *dst, const void *src, u32 n);
extern void fn_2_6AE08(void);
extern void fn_2_90538(void);
extern void fn_2_46ADC(void);
extern void fn_2_467FC(void);
extern void fn_2_45978(void);
extern void fn_2_45810(void);
extern void fn_2_42EB0(void);
extern void fn_2_432EC(void);
extern u8 lbl_2_data_2E40[];
extern s16 lbl_2_data_3EC8[];
extern u8 lbl_2_data_3F60[];
extern u8 lbl_2_data_3F98[];

#define CHALLENGE_BYTE(offset) (((u8 *)lbl_2_bss_1A8248)[offset])
#define CHALLENGE_S8(offset) (((s8 *)lbl_2_bss_1A8248)[offset])
#define CHALLENGE_S16(offset) (*(s16 *)((u8 *)lbl_2_bss_1A8248 + (offset)))
void fn_2_53F04(void *arg0);
void fn_2_5400C(void);
void fn_2_53CEC(void *arg0);

void fn_2_4E878(void *arg0, void *arg1);
void fn_2_53F88(void *arg0);
void fn_2_54120(void);
void fn_2_53DF8(void *arg0);
void fn_2_4E858(void *arg0);
extern u8 superstarUnlocked[];
extern u8 cardCheck[];
extern s16 lbl_2_data_38CC[];
void fn_8003BF54(int a, int b, int c, int d, int e, int f, int g, int h, int i);
void fn_2_39408(void);
void fn_2_3AF08(void);
void fn_2_439D0(void);
void fn_2_430F4(void);
void fn_2_42FC8(void);
void fn_2_3D878(void);
void fn_2_399C0(void);
void fn_2_3DDC4(void);
void fn_2_3DC60(void);
void fn_2_4C36C(void);
void fn_2_38F48(void);
void fn_2_3DAB8(void);
void fn_2_3D5C4(void);
void fn_2_460F8(void);
void fn_2_44F64(void);
extern s16 lbl_2_data_2E6C[];
void fn_2_4D378(void);
void fn_2_4C81C(void);
void fn_2_43404(void);
void fn_2_42708(void);
void fn_2_6AF80(int a, int b);
void fn_2_1C41C(void);
int fn_2_684D0(int a);
void fn_2_68654(int a, int b);
void fn_2_68638(int a, int b);
int fn_2_6AFD4(int a);
int fn_2_68690(int a);
void fn_2_40B90(void);
void fn_2_1B7B4(void);
void fn_2_4D194(void);
void fn_2_4D67C(void);
void fn_2_4C9C4(void);
void fn_2_4CEE0(void);
void fn_2_4DEE8(void);
void fn_2_4E1C0(void);
void fn_2_42EB0(void);
extern u8 fn_80062794(s32 arg0);
void unknownSettingTeamValues(void);
void changeScreenVariables(u16 screen);
void currentScreenFunctionChooser(void);
extern GXColor lbl_2_data_107C8;
extern void GXSetCopyClear(GXColor clearColor, u32 clearZ);
extern u8 lbl_2_data_3CE0[];
extern u8 lbl_8037169C[];
extern u8 lbl_800EFBA4[];
void fn_2_515DC(u8 arg0);
void fn_2_54474(void);
void fn_2_2469C(void);
void fn_2_24650(void);
void fn_2_246E0(void);
void fn_2_1B314(void);
void fn_2_1B1BC(void);
void playStream(u8 streamId);
void changeScene(u8 scene, u16 arg1);
void challenge_setTransitionScreenCharacterPortrait(u8 scene, s8 charID);
void fn_2_4358C(void);
void fn_2_42BE8(void);
void fn_2_432EC(void);
void fn_2_4B1AC(void);
void fn_2_4AEE4(void);
void fn_2_4ACF8(void);
void fn_2_422FC(int arg0);
void fn_2_42388(void);
void fn_2_38538(void);
void fn_2_1C490(void);
int fn_2_686B0(int arg0);
int fn_2_45938(void);
void sndFXStartEx(int fid, int vol, int pan, int studio);
void fn_2_46D34(s32 delta);
void fn_2_683EC(void);
void fn_2_68308(void);
void fn_2_6832C(void);
void fn_2_46C2C(s32 unused, Vec *pos);
void fn_2_1C714(s32 idx);
void fn_2_3FA14(void);
void fn_2_3F66C(void);
void fn_2_1CF94(void);
void fn_2_1C860(void);
#define SCENE_MODE (*(s16 *)&lbl_2_bss_1A823C[0x30])
#define WORK_U8(off) (lbl_2_bss_1A824C[0x190000 + (off)])
#define WORK_S16(off) (*(s16 *)&lbl_2_bss_1A824C[0x190000 + (off)])
#define WORK_S32(off) (*(s32 *)&lbl_2_bss_1A824C[0x190000 + (off)])
#define PAD_PORT ((s8)WORK_U8(0x7863))
#define PAD_PTR() ((u8 *)&AtBat_ButtonInput1 + PAD_PORT * 32)
#define PAD_RAW() (*(u16 *)PAD_PTR())
#define PAD_NEW() (*(u16 *)(PAD_PTR() + 2))
#define PAD_NEW2() (*(u16 *)((u8 *)&AtBat_ButtonInput1._02 + PAD_PORT * 32))
#define PAD_HELD() (*(u16 *)(PAD_PTR() + 4))
#define PAD_STICK_Y() (*(s8 *)(PAD_PTR() + 0x13))
#define ITEM_STATE (*(s8 *)((u8 *)item + 0x28))

extern u8 *lbl_2_bss_1A823C;
extern u8 lbl_2_data_2EA4[];
extern s16 lbl_2_data_3ED4[];
extern s16 lbl_2_data_3EE0[];
extern s16 lbl_2_data_3EEC[];
extern s16 lbl_2_data_3EF0[];
void fn_2_6ACF4(void);
void fn_2_71F60(void);
void fn_2_72054(s32 index, s32 state);
int fn_2_4C3D8(s32 index);
void fn_2_6ABFC(s32 idx, s32 which);
void fn_2_6AABC(s32 idx, Vec *src);
void fn_2_68DAC(s32 idx, Vec *dst);
s16 fn_2_689CC(s32 idx);
void fn_2_686D0(s32 idx, s32 val);
void fn_2_904A8(void);
void fn_2_9257C(void);
void fn_2_90428(int idx);
void fn_2_92654(s32 slot, s32 value);
void fn_2_94854(int value);
void menuCamera_setFollowSlot(int slot);
void menuCamera_setEyeFollowsSlot(int follows);
void menuCamera_setSpringPreset(s32 preset);
void menuCamera_snapToPreset(void);

// .text:0x000338D4 size:0x59C mapped:0x80672968
void fn_2_338D4(void *arg0, void *arg1) {
    s16 *state;
    int packed = *(s16 *)((u8 *)arg1 + 0x10);
    int part = packed & 0xF;
    s16 value;
    s16 magnitude;
    s16 which = packed >> 4;
    s16 result;
    state = (s16 *)((u8 *)arg1 + 4);
    result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 2: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        setRecordPlayMode(arg0, arg1, UI_PLAY_FORWARD);
        switch (which) {
        case 0:
            value = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7766];
            magnitude = abs16(*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7766]);
            break;
        case 1:
            value = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7768];
            magnitude = abs16(*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7768]);
            break;
        case 2:
            value = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x776A];
            magnitude = abs16(*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x776A]);
            break;
        case 3:
            value = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x776C];
            magnitude = abs16(*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x776C]);
            break;
        }
        if (magnitude == 0x2710) {
            load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x2C, 0x17);
        } else {
            switch (*(s16 *)((u8 *)arg1 + 0xA)) {
            case 0: {
                s16 digit = magnitude % 10;
                load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x2C, (which == 3) ? digit : (s16)(digit + 0xC));
                break;
            }
            case 1: {
                s16 digit = magnitude / 10 % 10;
                if (magnitude < 10) {
                    digit = 0x17;
                } else {
                    switch (which) {
                    case 3:
                        break;
                    default:
                        digit = digit + 0xC;
                        break;
                    }
                }
                load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x2C, digit);
                break;
            }
            case 2: {
                s16 digit = magnitude / 100 % 10;
                if (magnitude < 100) {
                    digit = 0x17;
                } else {
                    switch (which) {
                    case 3:
                        break;
                    default:
                        digit = digit + 0xC;
                        break;
                    }
                }
                load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x2C, digit);
                break;
            }
            case 3: {
                s16 icon;
                s16 x0;
                s16 y0;
                s16 x1;
                s16 y1;
                s16 width;
                if (value < 0) {
                    if (which == 3) {
                        icon = 0xB;
                    } else {
                        icon = 0x16;
                    }
                } else if (value > 0) {
                    if (which == 3) {
                        icon = 0xA;
                    } else {
                        icon = 0x17;
                    }
                } else {
                    icon = 0x17;
                }
                load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x2C, icon);
                fn_80036270(arg0, 0x280, 0, 0, &x0, &y0);
                fn_80036270(arg0, 0x280, 2, 0, &x0, &y0);
                fn_80036270(arg0, 0x280, 1, 0, &x1, &y1);
                width = abs16(x1 - x0);
                fn_80036270(arg0, 0x280, (s16)part, 0, &x0, &y0);
                if (magnitude == 0) {
                    x0 = 0;
                } else if (magnitude < 10) {
                    x0 = width * 2;
                } else if (magnitude < 100) {
                    x0 = width;
                } else {
                    x0 = 0;
                }
                ((UIRecord *)SCENE_RECORD(arg0, arg1))->pos.x = x0;
                break;
            }
            }
        }
        *state = 0x25;
        break;
    }
    case 5: {
        setRecordPlayMode(arg0, arg1, UI_PLAY_BACKWARD);
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00033720 size:0x1B4 mapped:0x806727B4
void fn_2_33720(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00033614 size:0x10C mapped:0x806726A8
void fn_2_33614(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        return;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        *state = 0x25;
        return;
    }
    case 5:
    case 0x25:
        return;
    }
}

// .text:0x000331C8 size:0x44C mapped:0x8067225C
void fn_2_331C8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x76DE] == 0) {
            setRecordFrame(arg0, arg1, 0);
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        } else {
            setRecordFrame(arg0, arg1, 0xF0000);
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        }
        *state = 3;
        break;
    }
    case 3: {
        TextGraphicsObject *obj;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x76DE] == 0) {
            obj = SCENE_RECORD(arg0, arg1);
            if ((((UIRecord *)obj)->frame >> 16) >= 5) {
                ((UIRecord *)obj)->frame = 0x50000;
                setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
                *state = 0x25;
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            if ((((UIRecord *)obj)->frame >> 16) <= 0xA) {
                ((UIRecord *)obj)->frame = 0xA0000;
                setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
                *state = 0x25;
            }
        }
        break;
    }
    case 0x25: {
        TextGraphicsObject *obj;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x76DE] == 0) {
            obj = SCENE_RECORD(arg0, arg1);
            if ((((UIRecord *)obj)->frame >> 16) <= 5) {
                ((UIRecord *)obj)->frame = 0x50000;
                ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            } else {
                ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            if ((((UIRecord *)obj)->frame >> 16) >= 0xA) {
                ((UIRecord *)obj)->frame = 0xA0000;
                ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            } else {
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            }
        }
        break;
    }
    case 5: {
        TextGraphicsObject *obj;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x76DE] == 0) {
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        }
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x76DE] == 0) {
            obj = SCENE_RECORD(arg0, arg1);
            if ((((UIRecord *)obj)->frame >> 16) == 0 == 0) {
                setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
                *state = 7;
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            if ((((UIRecord *)obj)->frame >> 16) >= 0xF) {
                setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
                *state = 7;
            }
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x00032F08 size:0x2C0 mapped:0x80671F9C
void fn_2_32F08(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xFF;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel((UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE), (u16) * (s16 *)((u8 *)arg1 + 0x10), 4, 0x2E0, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        switch (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x72B4]) {
        case 0:
            text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x2E0);
            break;
        case 1:
            text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x2E1);
            break;
        case 2:
            text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x2E2);
            break;
        case 3:
            text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x357);
            break;
        case 4:
            text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x2DE);
            break;
        case 5:
            text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x312);
            break;
        case 6:
            text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x313);
            break;
        case 7:
            text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x314);
            break;
        case 8:
            text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x315);
            break;
        }
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        *state = 3;
        break;
    }
    case 3: {
        *state = 0x25;
        break;
    }
    case 0x25: {
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
    {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->rgba = *(s16 *)((u8 *)arg1 + 0x12) | (((UIRecord *)obj)->rgba & 0xFFFFFF00);
    }
}

// .text:0x00032D54 size:0x1B4 mapped:0x80671DE8
void fn_2_32D54(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00032C64 size:0xF0 mapped:0x80671CF8
void fn_2_32C64(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        return;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        return;
    }
    case 5:
    case 0x25:
        return;
    }
}

// .text:0x00032A78 size:0x1EC mapped:0x80671B0C
void fn_2_32A78(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x30a, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x30a);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
    {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x000328C4 size:0x1B4 mapped:0x80671958
void fn_2_328C4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x000327D4 size:0xF0 mapped:0x80671868
void fn_2_327D4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        return;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        return;
    }
    case 5:
    case 0x25:
        return;
    }
}

// .text:0x000325E8 size:0x1EC mapped:0x8067167C
void fn_2_325E8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x30b, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, 0x30b);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
    {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x00032434 size:0x1B4 mapped:0x806714C8
void fn_2_32434(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x000322E4 size:0x150 mapped:0x80671378
void fn_2_322E4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x000320D8 size:0x20C mapped:0x8067116C
void fn_2_320D8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xFF;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel((UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE), (u16) * (s16 *)((u8 *)arg1 + 0x10), 4, lbl_2_bss_1A8248->captain + 0x30C, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, lbl_2_bss_1A8248->captain + 0x30C);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        *state = 3;
        break;
    }
    case 3: {
        *state = 0x25;
        break;
    }
    case 0x25: {
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
    {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->rgba = *(s16 *)((u8 *)arg1 + 0x12) | (((UIRecord *)obj)->rgba & 0xFFFFFF00);
    }
}

// .text:0x00031F50 size:0x188 mapped:0x80670FE4
void fn_2_31F50(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj;
            *((u8 *)SCENE_RECORD(arg0, arg1) + 0x68) = 0;
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031D94 size:0x1BC mapped:0x80670E28
void fn_2_31D94(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x83, lbl_2_data_38C0[lbl_2_bss_1A8248->captain]);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 3;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj;
            setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031BE0 size:0x1B4 mapped:0x80670C74
void fn_2_31BE0(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031A90 size:0x150 mapped:0x80670B24
void fn_2_31A90(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031880 size:0x210 mapped:0x80670914
void fn_2_31880(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x316, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        s8 *base = (s8 *)&lbl_2_bss_1A824C[0x190000];
        s8 b1 = base[0x7867];
        s8 b2 = base[b1 + 0x7868];
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, b2 + 0x316);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
    {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x000316F8 size:0x188 mapped:0x8067078C
void fn_2_316F8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj;
            *((u8 *)SCENE_RECORD(arg0, arg1) + 0x68) = 0;
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031538 size:0x1C0 mapped:0x806705CC
void fn_2_31538(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x83, ((s8 *)&WORK_U8(0x7868))[(s8)WORK_U8(0x7867)]);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 3;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj;
            setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031384 size:0x1B4 mapped:0x80670418
void fn_2_31384(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00031250 size:0x134 mapped:0x806702E4
void fn_2_31250(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 3:
    case 4:
        break;
    case 0x11:
        *state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0xe;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0003109C size:0x1B4 mapped:0x80670130
void fn_2_3109C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00030EF8 size:0x1A4 mapped:0x8066FF8C
void fn_2_30EF8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 8:
    case 0x25:
        break;
    case 2:
    case 0x11: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        setRecordFrame(arg0, arg1, 0);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x00030D80 size:0x178 mapped:0x8066FE14
void fn_2_30D80(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 2:
    case 0x11: {
        s16 idx = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7726];
        s8 flag = lbl_2_bss_1A824C[0x190000 + 0x789F + *(s16 *)((u8 *)arg1 + 0xA) + idx];
        int frame = 0x14;
        TextGraphicsObject *obj;
        if (flag != 2) {
            frame = idx;
        }
        setRecordFrame(arg0, arg1, frame << 16);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 6) = 0xE;
        *state = 6;
        break;
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x00030C4C size:0x134 mapped:0x8066FCE0
void fn_2_30C4C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 3:
    case 4:
        break;
    case 0x11:
        *state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0xe;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00030894 size:0x3B8 mapped:0x8066F928
void fn_2_30894(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 7:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        s16 idx = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x772A];
        s16 row = *(s16 *)((u8 *)arg1 + 0xA);
        if (lbl_2_bss_1A8248->_43C2[row + idx] == 1) {
            if (lbl_2_data_373C[row + idx] == 0) {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            } else if ((s8)lbl_2_bss_1A8248->_4446[5] == row + idx) {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        break;
    }
    case 8:
    case 0x11: {
        TextGraphicsObject *obj;
        s16 idx = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x772A];
        s16 row = *(s16 *)((u8 *)arg1 + 0xA);
        if (lbl_2_bss_1A8248->_43C2[row + idx] == 1) {
            if (lbl_2_data_373C[row + idx] == 0) {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            } else if ((s8)lbl_2_bss_1A8248->_4446[5] == row + idx) {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj;
        *(s16 *)((u8 *)arg1 + 6) = 0xE;
        setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x000306D8 size:0x1BC mapped:0x8066F76C
void fn_2_306D8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 7:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        int sum = *(s16 *)((u8 *)arg1 + 0xA) + *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x772A];
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x65, (s8)lbl_2_bss_1A824C[0x190000 + 0x789F + sum] == 2 ? 0x14 : sum);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 8:
    case 0x11: {
        int sum = *(s16 *)((u8 *)arg1 + 0xA) + *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x772A];
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x65, (s8)lbl_2_bss_1A824C[0x190000 + 0x789F + sum] == 2 ? 0x14 : sum);
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0xE;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x0003039C size:0x33C mapped:0x8066F430
void fn_2_3039C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 7:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        s16 value = *(s16 *)(lbl_2_data_3764 + (*(s16 *)((u8 *)arg1 + 0xA) + *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x772A]) * 8 + lbl_2_bss_1A8248->difficulty * 2);
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x66, value / 100 % 10);
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 2, 0x66, value / 10 % 10);
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 3, 0x66, value % 10);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 8:
    case 0x11: {
        s16 value = *(s16 *)(lbl_2_data_3764 + (*(s16 *)((u8 *)arg1 + 0xA) + *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x772A]) * 8 + lbl_2_bss_1A8248->difficulty * 2);
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x66, value / 100 % 10);
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 2, 0x66, value / 10 % 10);
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 3, 0x66, value % 10);
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0xE;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x000300BC size:0x2E0 mapped:0x8066F150
void fn_2_300BC(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7728] == *(s16 *)((u8 *)arg1 + 0xA)) {
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        }
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 0x11: {
        TextGraphicsObject *obj;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7728] == *(s16 *)((u8 *)arg1 + 0xA)) {
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            if ((((UIRecord *)obj)->frame >> 16) >= 0xA) {
                ((UIRecord *)obj)->frame = 0;
            }
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        }
        *state = 0x12;
        break;
    }
    case 0x12: {
        TextGraphicsObject *obj;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7728] != *(s16 *)((u8 *)arg1 + 0xA)) {
            obj = SCENE_RECORD(arg0, arg1);
            if ((((UIRecord *)obj)->frame >> 16) == 0) {
                ((UIRecord *)obj)->frame = 0;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            }
        }
        break;
    }
    case 5: {
        TextGraphicsObject *obj;
        *(s16 *)((u8 *)arg1 + 6) = 0xE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x0002FE50 size:0x26C mapped:0x8066EEE4
void fn_2_2FE50(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7728] == *(s16 *)((u8 *)arg1 + 0xA)) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        break;
    }
    case 0x11: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7728] == *(s16 *)((u8 *)arg1 + 0xA)) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        }
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0xE;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x0002FD00 size:0x150 mapped:0x8066ED94
void fn_2_2FD00(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 3:
    case 4:
        break;
    case 0x11:
        *state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0xe;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002FBCC size:0x134 mapped:0x8066EC60
void fn_2_2FBCC(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 3:
    case 4:
        break;
    case 0x11:
        *state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x19;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002FA7C size:0x150 mapped:0x8066EB10
void fn_2_2FA7C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 3:
    case 4:
        break;
    case 0x11:
        *state = 0x25;
        break;
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x19;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002F8A4 size:0x1D8 mapped:0x8066E938
void fn_2_2F8A4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 6, lbl_2_bss_1A8248->difficulty);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x0002F710 size:0x194 mapped:0x8066E7A4
void fn_2_2F710(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 0x11: {
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x0002F544 size:0x1CC mapped:0x8066E5D8
void fn_2_2F544(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        s16 list[9];
        s16 *out = list;
        s16 i;
        ChallengeState *challenge = lbl_2_bss_1A8248;
        for (i = 0; i < 9; i++) {
            if (challenge->savedLineup[i].charID != challengeCaptainCharIDs[challenge->captain]) {
                *out++ = challenge->savedLineup[i].charID;
            }
        }
        setRecordFrame(arg0, arg1, (u32)list[*(s16 *)((u8 *)arg1 + 0xA)] << 16);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0x19;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002EFCC size:0x578 mapped:0x8066E060
void fn_2_2EFCC(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    int digit;
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    SET_DIGIT(digit, *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7736], *(s16 *)((u8 *)arg1 + 0xA));
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
    case 8:
    case 19:
    case 22:
    case 31:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        SCENE_RECORD(arg0, arg1)->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->frame = 0;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7734] = CHALLENGE_S16(0x43BC);
        *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7736] = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x773C] = CHALLENGE_S16(0x43BC);
        SET_DIGIT(digit, *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7736], *(s16 *)((u8 *)arg1 + 0xA));
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0xD, digit);
        *state = 3;
        break;
    }
    case 3: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0x15) {
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x25;
        }
        break;
    }
    case 0x11: {
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7736] != *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x773C]) {
            load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0xD, digit);
            *state = 0x12;
        } else {
            *state = 0x25;
        }
        break;
    }
    case 0x12: {
        *state = 0x25;
        break;
    }
    case 0x14: {
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7736] != *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x773C]) {
            load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0xD, digit);
            *state = 0x15;
        } else {
            *state = 0x25;
        }
        break;
    }
    case 0x15: {
        *state = 0x25;
        break;
    }
    case 0x1E:
    case 0x21: {
        SET_DIGIT(digit, CHALLENGE_S16(0x43BC), *(s16 *)((u8 *)arg1 + 0xA));
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0xD, digit);
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x0002EBE4 size:0x3E8 mapped:0x8066DC78
void fn_2_2EBE4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
    case 10:
    case 23:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        s8 icon = lbl_2_bss_1A8248->_4446[5];
        if (icon == -1) {
            *state = 0x25;
            break;
        }
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 4, 0x64, icon);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 3;
        break;
    }
    case 3: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0xA) {
            ((UIRecord *)obj)->frame = 0xA0000;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x25;
        }
        break;
    }
    case 8: {
        TextGraphicsObject *obj;
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 4, 0x64, ((s8 *)lbl_2_bss_1A8248->_4446)[5]);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->frame = 0xB0000;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 9;
        break;
    }
    case 9: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0x15) {
            ((UIRecord *)obj)->frame = 0xA0000;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x25;
        }
        break;
    }
    case 0x14: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0x160000);
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x15;
        break;
    }
    case 0x15: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0x2D) {
            ((UIRecord *)obj)->frame = 0;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x16;
        }
        break;
    }
    case 0x16: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x0002E7D0 size:0x414 mapped:0x8066D864
void fn_2_2E7D0(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
    case 10:
    case 23:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        if ((s8)lbl_2_bss_1A8248->_4446[5] == -1) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            *state = 3;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            *state = 0x25;
        }
        break;
    }
    case 3: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0xE) {
            ((UIRecord *)obj)->frame = 0xE0000;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x25;
        }
        break;
    }
    case 8: {
        TextGraphicsObject *obj;
        if ((s8)lbl_2_bss_1A8248->_4446[6] == -1) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->frame = 0xF0000;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            *state = 9;
        } else {
            *state = 0x25;
        }
        break;
    }
    case 9: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0x19) {
            ((UIRecord *)obj)->frame = 0x190000;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x25;
        }
        break;
    }
    case 0x14: {
        *(s16 *)((u8 *)arg1 + 6) = 0x1E;
        *state = 0x15;
        break;
    }
    case 0x15: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj;
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->frame = 0;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            *state = 0x16;
        }
        break;
    }
    case 0x16: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0xE) {
            ((UIRecord *)obj)->frame = 0xE0000;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x25;
        }
        break;
    }
    case 5: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x0002E5C8 size:0x208 mapped:0x8066D65C
void fn_2_2E5C8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 3;
        break;
    }
    case 3: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0xC8) {
            if (lbl_2_bss_1A8248->_4446[0] != 0) {
                lbl_2_bss_1A8234[0x160000 + 0x267A] = 1;
            }
            *state = 4;
        }
    }
    case 4: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0x104) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            *state = 0x25;
        }
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002E44C size:0x17C mapped:0x8066D4E0
void fn_2_2E44C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        ((UIRecord *)SCENE_RECORD(arg0, arg1))->pos.x = 320.0f;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->pos.y = 0.0f;
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x0002E298 size:0x1B4 mapped:0x8066D32C
void fn_2_2E298(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002E17C size:0x11C mapped:0x8066D210
void fn_2_2E17C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002DFC8 size:0x1B4 mapped:0x8066D05C
void fn_2_2DFC8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002DE78 size:0x150 mapped:0x8066CF0C
void fn_2_2DE78(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x28;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002DCA8 size:0x1D0 mapped:0x8066CD3C
void fn_2_2DCA8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x43, *(s16 *)((u8 *)arg1 + 0x10));
        if (challenge_isCharRecruited(lbl_800E869C[*(s16 *)((u8 *)arg1 + 0x10)]) == 1) {
            obj = SCENE_RECORD(arg0, arg1);
            *(u32 *)((u8 *)obj + 0x5C) = 0;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            *(u32 *)((u8 *)obj + 0x5C) = 0x10000;
        }
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x28;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002DAA8 size:0x200 mapped:0x8066CB3C
void fn_2_2DAA8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        u8 charID = lbl_800E869C[*(s16 *)((u8 *)arg1 + 0x10)];
        int flag = lbl_2_bss_1A8248->charIsSuperstar[charID];
        if (challenge_isCharRecruited(charID)) {
            if (flag == 1) {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0x28;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002D8C4 size:0x1E4 mapped:0x8066C958
void fn_2_2D8C4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        u8 charID = lbl_800E869C[*(s16 *)((u8 *)arg1 + 0x10)];
        int flag = lbl_2_bss_1A8248->charIsSuperstar[charID];
        if (challenge_isCharRecruited(charID)) {
            if (flag == 1) {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0x28;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002D640 size:0x284 mapped:0x8066C6D4
void fn_2_2D640(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706] == *(s16 *)((u8 *)arg1 + 0x10)) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        }
        *state = 0x25;
        break;
    }
    case 0x25: {
        TextGraphicsObject *obj;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706] == *(s16 *)((u8 *)arg1 + 0x10)) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        }
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0x28;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x0002D508 size:0x138 mapped:0x8066C59C
void fn_2_2D508(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002D0D4 size:0x434 mapped:0x8066C168
void fn_2_2D0D4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 6:
    case 7:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->frame = 0x50000;
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x41, *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7730]);
        *state = 0x25;
        break;
    }
    case 0x1E: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0x50000);
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        *state = 0x1F;
        break;
    }
    case 0x1F: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x41, *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7730]);
            setRecordFrame(arg0, arg1, 0xA0000);
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
            *state = 0x20;
        }
        break;
    }
    case 0x20: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) <= 5) {
            ((UIRecord *)obj)->frame = 0x50000;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x26;
        }
        break;
    }
    case 0x21: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0x50000);
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x22;
        break;
    }
    case 0x22: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0xA) {
            load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x41, *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7730]);
            setRecordFrame(arg0, arg1, 0);
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            *state = 0x23;
        }
        break;
    }
    case 0x23: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 5) {
            ((UIRecord *)obj)->frame = 0x50000;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x26;
        }
        break;
    }
    case 8: {
        TextGraphicsObject *obj;
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x41, *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7730]);
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->frame = 0x50000;
        *state = 0x26;
        break;
    }
    case 5: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0x50000);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x0002CF58 size:0x17C mapped:0x8066BFEC
void fn_2_2CF58(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 8:
    case 0x1E:
    case 0x21:
        *(s16 *)((u8 *)arg1 + 0x6) = 1;
        *state = *state + 1;
        break;
    case 9:
    case 0x1F:
    case 0x22: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            *state = 0x25;
        }
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002CDA4 size:0x1B4 mapped:0x8066BE38
void fn_2_2CDA4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002CBCC size:0x1D8 mapped:0x8066BC60
void fn_2_2CBCC(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        if (lbl_2_bss_1A8248->_43C2[*(s16 *)((u8 *)arg1 + 0xA)] == 1) {
            ((UIRecord *)SCENE_RECORD(arg0, arg1))->elementIndex = 0x68;
        } else {
            ((UIRecord *)SCENE_RECORD(arg0, arg1))->elementIndex = 0x67;
        }
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0x1E;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002CA30 size:0x19C mapped:0x8066BAC4
void fn_2_2CA30(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        if (lbl_2_bss_1A8248->_43C2[*(s16 *)((u8 *)arg1 + 0xA)] == 1) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0x1E;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x0002C860 size:0x1D0 mapped:0x8066B8F4
void fn_2_2C860(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 0;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        s16 v = *(s16 *)((u8 *)arg1 + 0xA);
        s8 flag = lbl_2_bss_1A8248->_43C2[v];
        TextGraphicsObject *obj;
        if (flag == 1) {
            setRecordFrame(arg0, arg1, (u32)v << 16);
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x1e;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002C698 size:0x1C8 mapped:0x8066B72C
void fn_2_2C698(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        if (lbl_2_bss_1A8248->_43C2[*(s16 *)((u8 *)arg1 + 0xA)] == 1) {
            load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x6C, *(s16 *)((u8 *)arg1 + 0xA));
            setRecordPlayMode(arg0, arg1, UI_PLAY_FORWARD);
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0x1E;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002C4E4 size:0x1B4 mapped:0x8066B578
void fn_2_2C4E4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002C378 size:0x16C mapped:0x8066B40C
void fn_2_2C378(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 6) = 9;
        *state = 6;
        break;
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002C1A8 size:0x1D0 mapped:0x8066B23C
void fn_2_2C1A8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        u8 charID = lbl_800E869C[WORK_S16(0x7706)];
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, Static_Stats_Tables.characterStats[charID / 9][charID % 9].stats.CharacterClass << 16);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 9;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002BF20 size:0x288 mapped:0x8066AFB4
void fn_2_2BF20(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 7:
    case 0x25:
        break;
    case 2:
    case 8: {
        TextGraphicsObject *obj;
        s16 row = *(s16 *)((u8 *)arg1 + 0xA);
        s16 charRow = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706];
        if (starMissionRequirementsTable[charRow][row].type != STAR_MISSION_TYPE_NONE) {
            s16 b;
            s8 statusA;
            s16 a;
            ChallengeTrackingStruct *tracker;
            tracker = &lbl_2_bss_1A8248->characters[lbl_800E869C[charRow]];
            a = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7710];
            statusA = tracker->inGameMissionTracker[a].starMissionStatus;
            if (!(statusA < 0 && tracker->inGameMissionTracker[b = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7712]].starMissionStatus < 0 && a != b)) {
                if (statusA < 0) {
                    setRecordFrame(arg0, arg1, 0);
                    obj = SCENE_RECORD(arg0, arg1);
                    obj->flags |= UI_FLAG_VISIBLE;
                    obj = SCENE_RECORD(arg0, arg1);
                    ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
                } else {
                    obj = SCENE_RECORD(arg0, arg1);
                    obj->flags &= ~UI_FLAG_VISIBLE;
                    obj = SCENE_RECORD(arg0, arg1);
                    ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
                }
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        }
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x0002BDA4 size:0x17C mapped:0x8066AE38
void fn_2_2BDA4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *(u32 *)((u8 *)obj + 0x5C) = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7714] << 16;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 9;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x0002BB34 size:0x270 mapped:0x8066ABC8
void fn_2_2BB34(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        s16 row = *(s16 *)((u8 *)arg1 + 0xA);
        s16 charRow = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706];
        if (starMissionRequirementsTable[charRow][row].type != STAR_MISSION_TYPE_NONE) {
            if (MISSION_TRACKER(lbl_800E869C[charRow])[row].starMissionStatus < 0) {
                load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x5A, 1);
            } else {
                load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x5A, 0);
            }
        } else {
            load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x5A, 0);
        }
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x0002B884 size:0x2B0 mapped:0x8066A918
void fn_2_2B884(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 7:
    case 0x25:
        break;
    case 2:
    case 8: {
        TextGraphicsObject *obj;
        s16 charRow = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706];
        s16 row = *(s16 *)((u8 *)arg1 + 0xA);
        if (starMissionRequirementsTable[charRow][row].type != STAR_MISSION_TYPE_NONE) {
            if (MISSION_TRACKER(lbl_800E869C[charRow])[row].starMissionStatus < 0) {
                if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7710] == row) {
                    obj = SCENE_RECORD(arg0, arg1);
                    obj->flags |= UI_FLAG_VISIBLE;
                    setRecordFrame(arg0, arg1, 0);
                    obj = SCENE_RECORD(arg0, arg1);
                    ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
                } else {
                    obj = SCENE_RECORD(arg0, arg1);
                    obj->flags &= ~UI_FLAG_VISIBLE;
                    obj = SCENE_RECORD(arg0, arg1);
                    ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
                }
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        }
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x0002B654 size:0x230 mapped:0x8066A6E8
void fn_2_2B654(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        s16 row = *(s16 *)((u8 *)arg1 + 0xA);
        s16 charRow = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706];
        if (starMissionRequirementsTable[charRow][row].type != STAR_MISSION_TYPE_NONE) {
            if (MISSION_TRACKER(lbl_800E869C[charRow])[row].starMissionStatus < 0) {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002B43C size:0x218 mapped:0x8066A4D0
void fn_2_2B43C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 7:
    case 0x25:
        break;
    case 2:
    case 8: {
        TextGraphicsObject *obj;
        s16 row = *(s16 *)((u8 *)arg1 + 0xA);
        if (starMissionRequirementsTable[*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706]][row].type != STAR_MISSION_TYPE_NONE) {
            if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7710] == row) {
                setRecordFrame(arg0, arg1, 0);
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x0002B250 size:0x1EC mapped:0x8066A2E4
void fn_2_2B250(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *(s16 *)((u8 *)arg1 + 0x6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0 || (*counter)-- <= 0) {
            obj = SCENE_RECORD(arg0, arg1);
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002B064 size:0x1EC mapped:0x8066A0F8
void fn_2_2B064(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *(s16 *)((u8 *)arg1 + 0x6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0 || (*counter)-- <= 0) {
            obj = SCENE_RECORD(arg0, arg1);
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002AEDC size:0x188 mapped:0x80669F70
void fn_2_2AEDC(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        s16 val = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706];
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, (u32)val << 16);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            *state = 7;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002AD30 size:0x1AC mapped:0x80669DC4
void fn_2_2AD30(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        determineIfMissionDescriptionIsShown(lbl_800E869C[*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706]]);
        setRecordFrame(arg0, arg1, (u32) * (s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706] << 16);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            *state = 7;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002AA8C size:0x2A4 mapped:0x80669B20
void fn_2_2AA8C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *(s16 *)((u8 *)arg1 + 0x12) = 0;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel((UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE), (u16) * (s16 *)((u8 *)arg1 + 0x10), 0, 8, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, lbl_800E869C[*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706]] + 8);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 3;
        break;
    }
    case 3: {
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) + (0xFF - *(s16 *)((u8 *)arg1 + 0x12)) / 4;
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) + 1;
        if (*(s16 *)((u8 *)arg1 + 0x12) > 0xFF) {
            *(s16 *)((u8 *)arg1 + 0x12) = 0xFF;
        }
        if (*(s16 *)((u8 *)arg1 + 0x12) >= 0xFF) {
            *state = 0x25;
        }
        break;
    }
    case 0x25: {
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) + (-*(s16 *)((u8 *)arg1 + 0x12)) / 4;
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) - 1;
        if (*(s16 *)((u8 *)arg1 + 0x12) < 0) {
            *(s16 *)((u8 *)arg1 + 0x12) = 0;
        }
        if (*(s16 *)((u8 *)arg1 + 0x12) <= 0 || (*(s16 *)((u8 *)arg1 + 6))-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            *state = 7;
        }
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 0;
    {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->rgba = *(s16 *)((u8 *)arg1 + 0x12) | (((UIRecord *)obj)->rgba & 0xFFFFFF00);
    }
}

// .text:0x0002A77C size:0x310 mapped:0x80669810
void fn_2_2A77C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *(s16 *)((u8 *)arg1 + 0x12) = 0;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel((UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE), (u16) * (s16 *)((u8 *)arg1 + 0x10), 0, ((s16 *)starRankTextIDs)[0], 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        u8 charID = lbl_800E869C[*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706]];
        int rankRow = fn_2_44F14(charID);
        int rankCol = fn_8006CDC0(charID);
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, starRankByMissionCount[rankRow][rankCol] + ((s16 *)starRankTextIDs)[*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706]]);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 3;
        break;
    }
    case 3: {
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) + (0xFF - *(s16 *)((u8 *)arg1 + 0x12)) / 4;
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) + 1;
        if (*(s16 *)((u8 *)arg1 + 0x12) > 0xFF) {
            *(s16 *)((u8 *)arg1 + 0x12) = 0xFF;
        }
        if (*(s16 *)((u8 *)arg1 + 0x12) >= 0xFF) {
            *state = 0x25;
        }
        break;
    }
    case 0x25: {
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) + (-*(s16 *)((u8 *)arg1 + 0x12)) / 4;
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) - 1;
        if (*(s16 *)((u8 *)arg1 + 0x12) < 0) {
            *(s16 *)((u8 *)arg1 + 0x12) = 0;
        }
        if (*(s16 *)((u8 *)arg1 + 0x12) <= 0 || (*(s16 *)((u8 *)arg1 + 6))-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            *state = 7;
        }
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 0;
    {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->rgba = *(s16 *)((u8 *)arg1 + 0x12) | (((UIRecord *)obj)->rgba & 0xFFFFFF00);
    }
}

// .text:0x0002A338 size:0x444 mapped:0x806693CC
void fn_2_2A338(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *(s16 *)((u8 *)arg1 + 0x12) = 0;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel((UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE), (u16) * (s16 *)((u8 *)arg1 + 0x10), 0, starMissionDisplayRules[0][0].textID, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
    case 7:
        break;
    case 2:
    case 8: {
        TextGraphicsObject *obj;
        s16 charRow = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706];
        s16 row = *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7710];
        s16 textID;
        ChallengeTrackingStruct *tracker;
        s16 flags;
        s16 minRow;
        s16 mode;
        u8 difficulty;
        textID = starMissionDisplayRules[charRow][row].textID;
        mode = starMissionDisplayRules[charRow][row].mode;
        tracker = &lbl_2_bss_1A8248->characters[lbl_800E869C[charRow]];
        flags = starMissionRequirementsTable[charRow][row].flags;
        minRow = starMissionRequirementsTable[charRow][row]._6[0];
        if (mode != -1 && (s8)tracker->inGameMissionTracker[row].shownOnPauseMenu == 0) {
            difficulty = lbl_2_bss_1A8248->difficulty;
            if (difficulty < minRow) {
                text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, 0x1C6);
            } else if ((flags & 2) && difficulty < 1) {
                text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, 0x1C6);
            } else if ((flags & 4) && difficulty < 2) {
                text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, 0x1C6);
            } else if ((flags & 8) && difficulty < 3) {
                text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, 0x1C6);
            } else {
                text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, 0x1C5);
            }
        } else if (mode != -1 && (s32)tracker->inGameMissionTracker[row].shownOnPauseMenu == 1 && (s8)tracker->inGameMissionTracker[row].starMissionStatus == 0) {
            difficulty = lbl_2_bss_1A8248->difficulty;
            if (difficulty < minRow) {
                text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, 0x1C6);
            } else if ((flags & 2) && difficulty < 1) {
                text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, 0x1C6);
            } else if ((flags & 4) && difficulty < 2) {
                text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, 0x1C6);
            } else if ((flags & 8) && difficulty < 3) {
                text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, 0x1C6);
            } else {
                text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, textID);
            }
        } else {
            text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 0, textID);
        }
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 3;
        break;
    }
    case 3: {
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) + (0xFF - *(s16 *)((u8 *)arg1 + 0x12)) / 4;
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) + 1;
        if (*(s16 *)((u8 *)arg1 + 0x12) > 0xFF) {
            *(s16 *)((u8 *)arg1 + 0x12) = 0xFF;
        }
        if (*(s16 *)((u8 *)arg1 + 0x12) >= 0xFF) {
            *state = 0x25;
        }
        break;
    }
    case 0x25: {
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 9;
        *state = 6;
        break;
    }
    case 6: {
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) + (-*(s16 *)((u8 *)arg1 + 0x12)) / 4;
        *(s16 *)((u8 *)arg1 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12) - 1;
        if (*(s16 *)((u8 *)arg1 + 0x12) < 0) {
            *(s16 *)((u8 *)arg1 + 0x12) = 0;
        }
        if (*(s16 *)((u8 *)arg1 + 0x12) <= 0 || (*(s16 *)((u8 *)arg1 + 6))-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            *state = 7;
        }
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
    {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->rgba = *(s16 *)((u8 *)arg1 + 0x12) | (((UIRecord *)obj)->rgba & 0xFFFFFF00);
    }
}

// .text:0x0002A21C size:0x11C mapped:0x806692B0
void fn_2_2A21C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x0002A068 size:0x1B4 mapped:0x806690FC
void fn_2_2A068(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00029F18 size:0x150 mapped:0x80668FAC
void fn_2_29F18(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x28;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

#define RECRUIT_CHAR_ID lbl_800E869C[*(s16 *)((u8 *)arg1 + 0x10)]

#define RECRUIT_ICON(flagField)                                                                      \
    if (challenge_isCharRecruited(RECRUIT_CHAR_ID) == 1) {                                           \
        int flag = lbl_2_bss_1A8248->flagField[RECRUIT_CHAR_ID];                                      \
        if (flag == 1) {                                                                             \
            ((UIRecord *)SCENE_RECORD(arg0, arg1))->elementIndex = 0x2E;                             \
            load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x43, *(s16 *)((u8 *)arg1 + 0x10));      \
            setRecordFrame(arg0, arg1, 0);                                                           \
            setRecordPlayMode(arg0, arg1, UI_PLAY_FORWARD);                                          \
        } else {                                                                                     \
            ((UIRecord *)SCENE_RECORD(arg0, arg1))->elementIndex = 0x2D;                             \
            load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x43, *(s16 *)((u8 *)arg1 + 0x10));      \
            setRecordFrame(arg0, arg1, 0);                                                           \
            setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);                                             \
        }                                                                                            \
    } else {                                                                                         \
        ((UIRecord *)SCENE_RECORD(arg0, arg1))->elementIndex = 0x2D;                                 \
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x43, *(s16 *)((u8 *)arg1 + 0x10));          \
        setRecordFrame(arg0, arg1, 0x10000);                                                         \
        setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);                                                 \
    }

// .text:0x00029884 size:0x694 mapped:0x80668918
void fn_2_29884(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        if (*(u8 *)&lbl_2_bss_1A824C[0x190000 + 0x78F6] == 0) {
            RECRUIT_ICON(recruitedChar)
        } else {
            RECRUIT_ICON(_44B9)
        }
        *state = 0x25;
        break;
    }
    case 8: {
        RECRUIT_ICON(_44B9)
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x28;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 1:
    case 3:
    case 4:
    case 7:
    case 9:
    case 10:
    case 0x25:
        break;
    }
}

#define RECRUIT_BADGE_B(decls)                                                                      \
    if (challenge_isCharRecruited(RECRUIT_CHAR_ID) == 1) {                                          \
        decls                                                                                       \
        flag = lbl_2_bss_1A8248->_44B9[charID];                                                     \
        a = fn_8006CDC0(charID);                                                                    \
        b = fn_2_44E2C(charID);                                                                     \
        if (flag == 1 && a == b) {                                                                  \
            obj = SCENE_RECORD(arg0, arg1);                                                         \
            obj->flags |= UI_FLAG_VISIBLE;                                                          \
            setRecordPlayMode(arg0, arg1, UI_PLAY_FORWARD);                                         \
        } else if (flag == 0 && a == b) {                                                           \
            obj = SCENE_RECORD(arg0, arg1);                                                         \
            obj->flags |= UI_FLAG_VISIBLE;                                                          \
            setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);                                            \
        } else {                                                                                    \
            obj = SCENE_RECORD(arg0, arg1);                                                         \
            obj->flags &= ~UI_FLAG_VISIBLE;                                                         \
            setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);                                            \
        }                                                                                           \
    } else {                                                                                        \
        obj = SCENE_RECORD(arg0, arg1);                                                             \
        obj->flags &= ~UI_FLAG_VISIBLE;                                                             \
        setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);                                                \
    }

// .text:0x0002926C size:0x618 mapped:0x80668300
void fn_2_2926C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 2: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        if (*(u8 *)&lbl_2_bss_1A824C[0x190000 + 0x78F6] == 0) {
            ((UIRecord *)SCENE_RECORD(arg0, arg1))->elementIndex = 0x2C;
            if (challenge_isCharRecruited(RECRUIT_CHAR_ID) == 1) {
                int flag = lbl_2_bss_1A8248->recruitedChar[RECRUIT_CHAR_ID];
                if (flag == 1) {
                    obj = SCENE_RECORD(arg0, arg1);
                    obj->flags |= UI_FLAG_VISIBLE;
                    setRecordPlayMode(arg0, arg1, UI_PLAY_FORWARD);
                } else {
                    obj = SCENE_RECORD(arg0, arg1);
                    obj->flags &= ~UI_FLAG_VISIBLE;
                    setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
                }
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
                setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
            }
        } else {
            ((UIRecord *)SCENE_RECORD(arg0, arg1))->elementIndex = 0x2F;
            RECRUIT_BADGE_B(int charID = RECRUIT_CHAR_ID; int flag; int a; int b;)
        }
        *state = 0x25;
        break;
    }
    case 8: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        ((UIRecord *)SCENE_RECORD(arg0, arg1))->elementIndex = 0x2F;
        RECRUIT_BADGE_B(int flag; int charID = RECRUIT_CHAR_ID; int a; int b;)
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x28;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj;
            setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 1:
    case 3:
    case 4:
    case 7:
    case 9:
    case 10:
    case 0x25:
        break;
    }
}

// .text:0x00028EA0 size:0x3CC mapped:0x80667F34
void fn_2_28EA0(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 7:
        break;
    case 2: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        if (lbl_2_bss_1A824C[0x190000 + 0x78F6] == 0) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        } else if (challenge_isCharRecruited(lbl_800E869C[*(s16 *)((u8 *)arg1 + 0x10)]) == 1) {
            int charID = lbl_800E869C[*(s16 *)((u8 *)arg1 + 0x10)];
            int flag;
            int a;
            int b;
            flag = lbl_2_bss_1A8248->_44B9[charID];
            a = fn_8006CDC0(charID);
            b = fn_2_44E2C(charID);
            if (flag == 1 && a != b) {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            }
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        }
        *state = 0x25;
        break;
    }
    case 8: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        {
            int flag;
            int charID = lbl_800E869C[*(s16 *)((u8 *)arg1 + 0x10)];
            int a;
            int b;
            flag = lbl_2_bss_1A8248->_44B9[charID];
            a = fn_8006CDC0(charID);
            b = fn_2_44E2C(charID);
            if (flag == 1 && a != b) {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            }
        }
        *state = 0x25;
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0x28;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj;
            setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00028D24 size:0x17C mapped:0x80667DB8
void fn_2_28D24(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 0x25: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 0x28;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x00028948 size:0x3DC mapped:0x806679DC
void fn_2_28948(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 7:
        break;
    case 2: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        if (lbl_2_bss_1A824C[0x190000 + 0x78F6] == 0) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        } else {
            if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706] == *(s16 *)((u8 *)arg1 + 0x10)) {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            }
        }
        *state = 0x25;
        break;
    }
    case 8: {
        TextGraphicsObject *obj;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706] == *(s16 *)((u8 *)arg1 + 0x10)) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        }
        *state = 0x25;
        break;
    }
    case 0x25: {
        TextGraphicsObject *obj;
        if (lbl_2_bss_1A824C[0x190000 + 0x78F6] == 0) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        } else {
            if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706] == *(s16 *)((u8 *)arg1 + 0x10)) {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags |= UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            } else {
                obj = SCENE_RECORD(arg0, arg1);
                obj->flags &= ~UI_FLAG_VISIBLE;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            }
        }
        break;
    }
    case 5: {
        *(s16 *)((u8 *)arg1 + 6) = 0x28;
        *state = 6;
        break;
    }
    case 6: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj;
            setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    }
}

// .text:0x00028794 size:0x1B4 mapped:0x80667828
void fn_2_28794(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x000284B0 size:0x2E4 mapped:0x80667544
void fn_2_284B0(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 8:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        *state = 0x25;
        break;
    }
    case 0x11: {
        TextGraphicsObject *obj;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706] == *(s16 *)((u8 *)arg1 + 0x10)) {
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            *state = 0x25;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            if ((((UIRecord *)obj)->frame >> 16) >= 0xA) {
                ((UIRecord *)obj)->frame = 0xA0000;
            }
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
            *state = 0x12;
        }
        break;
    }
    case 0x12: {
        TextGraphicsObject *obj;
        if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x7706] != *(s16 *)((u8 *)arg1 + 0x10)) {
            obj = SCENE_RECORD(arg0, arg1);
            if ((((UIRecord *)obj)->frame >> 16) == 0) {
                ((UIRecord *)obj)->frame = 0;
                obj = SCENE_RECORD(arg0, arg1);
                ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
                *state = 0x25;
            }
        }
        break;
    }
    case 5: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0xA0000);
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_BACKWARD;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) == 0) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x0002835C size:0x154 mapped:0x806673F0
void fn_2_2835C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00028224 size:0x138 mapped:0x806672B8
void fn_2_28224(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00028090 size:0x194 mapped:0x80667124
void fn_2_28090(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 2:
    case 8: {
        TextGraphicsObject *obj;
        if (lbl_2_bss_1A824C[0x190000 + 0x78F6] == 0) {
            load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x41, 7);
        } else {
            load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x41, 8);
        }
        setRecordFrame(arg0, arg1, 0x50000);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x00027EDC size:0x1B4 mapped:0x80666F70
void fn_2_27EDC(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00027D8C size:0x150 mapped:0x80666E20
void fn_2_27D8C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00027B7C size:0x210 mapped:0x80666C10
void fn_2_27B7C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x35c, 0);
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        s8 *base = (s8 *)&lbl_2_bss_1A824C[0x190000];
        s8 b1 = base[0x78F0];
        s8 b2 = base[b1 + 0x78DB];
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, b2 + 0x35c);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    }
    screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
    {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x000279F4 size:0x188 mapped:0x80666A88
void fn_2_279F4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj;
            *((u8 *)SCENE_RECORD(arg0, arg1) + 0x68) = 0;
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00027824 size:0x1D0 mapped:0x806668B8
void fn_2_27824(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        s8 idx1 = lbl_2_bss_1A824C[0x190000 + 0x78F0];
        s8 idx2 = lbl_2_bss_1A824C[0x190000 + 0x78DB + idx1];
        TextGraphicsObject *obj;
        load_Icon(arg0, *(s16 *)((u8 *)arg1 + 0xE), 1, 0x83, lbl_2_data_3714[idx2]);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5:
        *(s16 *)((u8 *)arg1 + 0x6) = 3;
        *state = 6;
        break;
    case 6: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj;
            setRecordPlayMode(arg0, arg1, UI_PLAY_STOP);
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00027660 size:0x1C4 mapped:0x806666F4
void fn_2_27660(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x1c7, 0);
        practiceTextRelated(*(s16 *)((u8 *)arg1 + 0x14), 1, 0);
        *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x72A0] = *(s16 *)((u8 *)arg1 + 0x14);
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x6FB8]);
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 0x25:
        break;
    }
    {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x0002749C size:0x1C4 mapped:0x80666530
void fn_2_2749C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x1c7, 0);
        practiceTextRelated(*(s16 *)((u8 *)arg1 + 0x14), 1, 0);
        *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x72A2] = *(s16 *)((u8 *)arg1 + 0x14);
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x6FBC]);
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 0x25:
        break;
    }
    {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *(u32 *)((u8 *)obj + 0x58) = *(s16 *)((u8 *)arg1 + 0x12) | (*(u32 *)((u8 *)obj + 0x58) & 0xFFFFFF00);
    }
}

// .text:0x000272E8 size:0x1B4 mapped:0x8066637C
void fn_2_272E8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 1;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        *((u8 *)obj + 0x68) = 4;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((*(u32 *)((u8 *)obj + 0x5C) >> 16) == 0) {
            *((u8 *)obj + 0x68) = 0;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x000272BC size:0x2C mapped:0x80666350
void fn_2_272BC(void *arg0, void *arg1) {
    u16 idx = *(u16 *)((u8 *)arg0 + 0x14);
    s16 offset = *(s16 *)((u8 *)arg1 + 0xE);
    graphicsRelatedArray[idx + offset].object->flags &= ~UI_FLAG_VISIBLE;
}

// .text:0x000270B8 size:0x204 mapped:0x8066614C
void fn_2_270B8(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
    case 8:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 3;
        break;
    }
    case 3: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0xDC) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x25;
        }
        break;
    }
    case 5: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0x14A0000);
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0x140) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x00026F80 size:0x138 mapped:0x80666014
void fn_2_26F80(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 5:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, (u32)lbl_2_bss_1A8248->captain << 16);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        *state = 0x25;
        break;
    }
    }
}

// .text:0x00026C70 size:0x310 mapped:0x80665D04
void fn_2_26C70(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
    case 8:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 3;
        break;
    }
    case 3: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) == 0xDC) {
            *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A8] = fn_80062890(0xD);
        }
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0x12C) {
            ((UIRecord *)obj)->frame = 0x12C0000;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x25;
        }
        break;
    }
    case 0x11: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0x12C0000);
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x12;
        break;
    }
    case 0x12: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0x15E) {
            ((UIRecord *)obj)->frame = 0x15E0000;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x25;
        }
        break;
    }
    case 5: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0x15E0000);
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0x140) {
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x00026AF4 size:0x17C mapped:0x80665B88
void fn_2_26AF4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
    case 6:
    case 0x25:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        *(u32 *)((u8 *)obj + 0x5C) = 0;
        *(s16 *)((u8 *)arg1 + 0x6) = 0xdc;
        *state = 3;
        break;
    }
    case 3: {
        s16 *counter = (s16 *)((u8 *)arg1 + 0x6);
        if ((*counter)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            *((u8 *)obj + 0x68) = 1;
            *state = 0x25;
        }
        break;
    }
    }
}

// .text:0x00026864 size:0x290 mapped:0x806658F8
void fn_2_26864(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        setRecordFrame(arg0, arg1, 0);
        *(s16 *)((u8 *)arg1 + 6) = 0xFA;
        *state = 3;
        break;
    }
    case 3: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            *state = 0x25;
        }
        break;
    }
    case 0x25: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0x78) {
            ((UIRecord *)obj)->frame = 0x320000;
        }
        break;
    }
    case 0x11: {
        TextGraphicsObject *obj;
        setRecordFrame(arg0, arg1, 0x780000);
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x12;
        break;
    }
    case 0x12: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0x82) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x13;
        }
        break;
    }
    case 0x13: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    }
}

// .text:0x00026774 size:0xF0 mapped:0x80665808
void fn_2_26774(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        return;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        return;
    }
    case 5:
    case 0x25:
        return;
    }
}

// .text:0x00026684 size:0xF0 mapped:0x80665718
void fn_2_26684(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        return;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 0x25;
        return;
    }
    case 5:
    case 0x25:
        return;
    }
}

// .text:0x000262D0 size:0x3B4 mapped:0x80665364
void fn_2_262D0(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->frame = 0;
        *state = 3;
        break;
    }
    case 0x11: {
        u8 *flags = lbl_2_bss_1A8244;
        ChallengeState *challenge = lbl_2_bss_1A8248;
        BOOL special = FALSE;
        u8 difficulty = challenge->difficulty;
        if (flags[difficulty + 0xE4] == 0 && difficulty < 3) {
            special = TRUE;
        }
        if (special) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->elementIndex = 7;
            *(s16 *)((u8 *)arg1 + 6) = 140;
            *state = 0x12;
        } else {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->elementIndex = 8;
            *(s16 *)((u8 *)arg1 + 6) = 140;
            *state = 0x12;
        }
        break;
    }
    case 0x12: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->frame = 0;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            *state = 0x13;
        }
        break;
    }
    case 0x13: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 160) {
            ((UIRecord *)obj)->frame = 65 << 16;
        }
        break;
    }
    case 5: {
        u8 *flags = lbl_2_bss_1A8244;
        ChallengeState *challenge = lbl_2_bss_1A8248;
        BOOL special = FALSE;
        u8 difficulty = challenge->difficulty;
        if (flags[difficulty + 0xE4] == 0 && difficulty < 3) {
            special = TRUE;
        }
        if (special) {
            TextGraphicsObject *obj;
            ((UIRecord *)SCENE_RECORD(arg0, arg1))->frame = 160 << 16;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            *state = 6;
        } else {
            TextGraphicsObject *obj;
            ((UIRecord *)SCENE_RECORD(arg0, arg1))->frame = 160 << 16;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            *state = 6;
        }
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 180) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    }
}

// .text:0x00026170 size:0x160 mapped:0x80665204
void fn_2_26170(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        return;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        s16 val = ((s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x77A2))[*(s16 *)((u8 *)arg1 + 0xA)];
        TextGraphicsObject *obj;
        if (val != -1) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            *(u32 *)((u8 *)obj + 0x5C) = (u32)val << 16;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        return;
    }
    case 5:
    case 0x25:
        return;
    }
}

// .text:0x00026010 size:0x160 mapped:0x806650A4
void fn_2_26010(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        return;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        s16 val = ((s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7818))[*(s16 *)((u8 *)arg1 + 0xA)];
        TextGraphicsObject *obj;
        if (val != -1) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            *(u32 *)((u8 *)obj + 0x5C) = (u32)val << 16;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        return;
    }
    case 5:
    case 0x25:
        return;
    }
}

// .text:0x00025EB0 size:0x160 mapped:0x80664F44
void fn_2_25EB0(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        return;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        s16 val = ((s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x780E))[*(s16 *)((u8 *)arg1 + 0xA)];
        TextGraphicsObject *obj;
        if (val != -1) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            *(u32 *)((u8 *)obj + 0x5C) = (u32)val << 16;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
        }
        *state = 0x25;
        return;
    }
    case 5:
    case 0x25:
        return;
    }
}

// .text:0x00025D98 size:0x118 mapped:0x80664E2C
void fn_2_25D98(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        return;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->frame = (u32)lbl_2_bss_1A8248->captain << 16;
        *state = 0x25;
        return;
    }
    case 5:
    case 0x25:
        return;
    }
}

// .text:0x00025D6C size:0x2C mapped:0x80664E00
void fn_2_25D6C(void *arg0, void *arg1) {
    u16 idx = *(u16 *)((u8 *)arg0 + 0x14);
    s16 offset = *(s16 *)((u8 *)arg1 + 0xE);
    graphicsRelatedArray[idx + offset].object->flags &= ~UI_FLAG_VISIBLE;
}

// .text:0x00025A48 size:0x324 mapped:0x80664ADC
void fn_2_25A48(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53AA4(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj;
        ((UIRecord *)SCENE_RECORD(arg0, arg1))->elementIndex = lbl_2_data_1050C[lbl_2_bss_1A8248->difficulty][lbl_2_bss_1A8248->captain];
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->frame = 0;
        *(s16 *)((u8 *)arg1 + 6) = 30;
        *state = 3;
        break;
    }
    case 3: {
        s16 *timer = (s16 *)((u8 *)arg1 + 6);
        if ((*timer)-- <= 0) {
            TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            *state = 4;
        }
        break;
    }
    case 4: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= (u32)lbl_2_data_1053C[lbl_2_bss_1A8248->difficulty][lbl_2_bss_1A8248->captain]) {
            ((UIRecord *)obj)->frame = (u32)lbl_2_data_1053C[lbl_2_bss_1A8248->difficulty][lbl_2_bss_1A8248->captain] << 16;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 0x25;
        }
        break;
    }
    case 5: {
        TextGraphicsObject *obj;
        ((UIRecord *)SCENE_RECORD(arg0, arg1))->frame = (u32)lbl_2_data_1056C[lbl_2_bss_1A8248->difficulty][lbl_2_bss_1A8248->captain] << 16;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= 0xA1) {
            ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
            *state = 7;
        }
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00025A1C size:0x2C mapped:0x80664AB0
void fn_2_25A1C(void *arg0, void *arg1) {
    u16 idx = *(u16 *)((u8 *)arg0 + 0x14);
    s16 offset = *(s16 *)((u8 *)arg1 + 0xE);
    graphicsRelatedArray[idx + offset].object->flags &= ~UI_FLAG_VISIBLE;
}

// .text:0x0002587C size:0x1A0 mapped:0x80664910
void fn_2_2587C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->frame = 0;
        *state = 0x25;
        break;
    }
    case 5:
        *state = 6;
        break;
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        *state = 7;
        break;
    }
    case 7: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00025850 size:0x2C mapped:0x806648E4
void fn_2_25850(void *arg0, void *arg1) {
    u16 idx = *(u16 *)((u8 *)arg0 + 0x14);
    s16 offset = *(s16 *)((u8 *)arg1 + 0xE);
    graphicsRelatedArray[idx + offset].object->flags &= ~UI_FLAG_VISIBLE;
}

// .text:0x0002577C size:0xD4 mapped:0x80664810
void fn_2_2577C(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        return;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2:
        *state = 0x25;
        return;
    case 5:
        return;
    case 8:
    case 0x24:
    case 0x25:
        break;
    }
}

// .text:0x00025524 size:0x258 mapped:0x806645B8
void fn_2_25524(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x774E] = 0;
        if ((s8)lbl_2_bss_1A824C[0x190000 + 0x7857] == *(s16 *)((u8 *)arg1 + 0xA)) {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags |= UI_FLAG_VISIBLE;
            obj = SCENE_RECORD(arg0, arg1);
            ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
            *state = 3;
        } else {
            obj = SCENE_RECORD(arg0, arg1);
            obj->flags &= ~UI_FLAG_VISIBLE;
            *state = 0x25;
        }
        break;
    }
    case 3: {
        TextGraphicsObject *obj;
        (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x774E])++;
        obj = SCENE_RECORD(arg0, arg1);
        if ((((UIRecord *)obj)->frame >> 16) >= (u32)lbl_2_data_107BC[*(s16 *)((u8 *)arg1 + 0xA)]) {
            lbl_2_bss_1A824C[0x190000 + 0x7859] = TRUE;
            *state = 0x25;
        }
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x000253B0 size:0x174 mapped:0x80664444
void fn_2_253B0(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00025200 size:0x1B0 mapped:0x80664294
void fn_2_25200(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x399, 0);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x774C]);
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    }
}

// .text:0x00025050 size:0x1B0 mapped:0x806640E4
void fn_2_25050(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 0x4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj;
        *(s16 *)((u8 *)arg1 + 0x12) = 0xff;
        *(s16 *)((u8 *)arg1 + 0x14) = text_initializeNewChannel(
            (UnkText988Arg *)arg0, *(s16 *)((u8 *)arg1 + 0xE),
            (u16)(*(s16 *)((u8 *)arg1 + 0x10)), 4, 0x399, 0);
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        text_setPtrToWhereCharsAreStored(*(s16 *)((u8 *)arg1 + 0x14), 4, *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x774C]);
        screenTextArray.blocks[*(s16 *)((u8 *)arg1 + 0x14)].justify = 1;
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        *state = 3;
        break;
    }
    case 3:
        *state = 0x25;
        break;
    case 0x25:
        *state = 0x25;
        break;
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    }
}

// .text:0x00024EC4 size:0x18C mapped:0x80663F58
void fn_2_24EC4(void *arg0, void *arg1) {
    s16 *state = (s16 *)((u8 *)arg1 + 4);
    s16 result = fn_2_53BC8(arg1);
    if (result != -1) {
        *state = result;
    }
    switch (*state) {
    case 0: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        *state = 0x26;
        break;
    }
    case 1:
    case 3:
    case 4:
        break;
    case 2: {
        TextGraphicsObject *obj;
        *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x774E] = 0;
        obj = SCENE_RECORD(arg0, arg1);
        obj->flags |= UI_FLAG_VISIBLE;
        obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_FORWARD;
        *state = 0x25;
        break;
    }
    case 5: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        ((UIRecord *)obj)->playMode = UI_PLAY_STOP;
        *state = 6;
        break;
    }
    case 6: {
        TextGraphicsObject *obj = SCENE_RECORD(arg0, arg1);
        obj->flags &= ~UI_FLAG_VISIBLE;
        break;
    }
    case 0x25:
        break;
    }
}

// .text:0x00024EB0 size:0x14 mapped:0x80663F44
void fn_2_24EB0(s16 state) {
    currentDrawingItem->state = state;
}

// .text:0x00024E9C size:0x14 mapped:0x80663F30
s16 fn_2_24E9C(void) {
    return currentDrawingItem->state;
}

// .text:0x00024800 size:0x69C mapped:0x80663894
void fn_2_24800(void) {
    int i;
    int j;
    s16 mode;
    s16 sel;
    Vec pos;
    fn_2_6ACF4();
    insertGraphicDrawingFunction(fn_2_71F60, 2);
    if (SCENE_MODE == 5) {
        fn_2_72054(0, 8);
    } else {
        fn_2_72054(0, 4);
    }
    mode = SCENE_MODE;
    if (mode == 0) {
        fn_2_6ABFC(0, fn_2_4C3D8(lbl_2_bss_1A8248->captain));
    } else if (mode != 4) {
        if (lbl_2_bss_1A8248->captain == 3 && lbl_2_bss_1A8248->opponentCaptain == 1 &&
            (sel = lbl_2_bss_1A8248->_16C2) == 0xB && mode == 3) {
            memcpy(&pos, lbl_2_data_2EA4 + sel * 12, 12);
            pos.x += 0.3f;
            pos.z -= 0.3f;
            fn_2_6AABC(0, &pos);
        } else {
            fn_2_6ABFC(0, lbl_2_bss_1A8248->_16C2);
        }
    }
    if (SCENE_MODE == 4) {
        fn_2_72054(1, 3);
    } else if (SCENE_MODE == 8 || SCENE_MODE == 1) {
        if (CHALLENGE_BYTE(0x442F) == 1) {
            int v = fn_2_689CC(1);
            CHALLENGE_S16(0x179A) = v;
            CHALLENGE_S16(0x1798) = v;
            CHALLENGE_S16(0x1796) = v;
            fn_2_6ABFC(1, (s16)v);
            fn_2_72054(1, 6);
            CHALLENGE_BYTE(0x442F) = 1;
        }
    } else if (lbl_2_bss_1A8248->captain == 5) {
        fn_2_72054(1, 0);
    } else {
        int pick;
        s16 *table;
        fn_2_68DAC(0, &pos);
        pick = rand() % 2;
        if (pos.x > 0.0f) {
            table = lbl_2_data_3EEC;
            fn_2_6ABFC(1, table[pick]);
            CHALLENGE_S16(0x179A) = table[pick];
        } else {
            table = lbl_2_data_3EF0;
            fn_2_6ABFC(1, table[pick]);
            CHALLENGE_S16(0x179A) = table[pick];
        }
        fn_2_72054(1, 6);
        CHALLENGE_BYTE(0x442F) = 1;
    }
    lbl_2_bss_1A824C[0x190000 + 0x782A] = 1;
    lbl_2_bss_1A824C[0x190000 + 0x782B] = 1;
    lbl_2_bss_1A824C[0x190000 + 0x7832] = 1;
    for (i = 0; i < 5; i++) {
        lbl_2_bss_1A824C[0x190000 + 0x782D + i] = 1;
        if (SCENE_MODE == 0) {
            fn_2_6ABFC(i + 2, lbl_2_data_3ED4[i]);
            *(s16 *)((u8 *)lbl_2_bss_1A8248 + i * 0xD8 + 0x1872) = lbl_2_data_3ED4[i];
        }
        if (lbl_2_bss_1A824C[0x190000 + 0x782D + i] == 1) {
            if (SCENE_MODE == 5 && lbl_2_bss_1A8248->_4420[0] == i) {
                fn_2_72054(i + 2, 8);
                if (lbl_2_bss_1A8248->_16C2 == lbl_2_data_3EE0[i]) {
                    fn_2_6ABFC(i + 2, lbl_2_data_3ED4[i]);
                }
            } else {
                fn_2_72054(i + 2, 7);
                fn_2_686D0(i + 2, 0);
            }
        } else {
            fn_2_72054(i + 2, 0);
        }
    }
    for (i = 0; i < 6; i++) {
        fn_2_6ABFC(i + 7, 0);
    }
    fn_2_904A8();
    insertGraphicDrawingFunction(fn_2_9257C, 2);
    fn_2_90428(0);
    fn_2_92654(0, 1);
    for (j = 0; j < 6; j++) {
        fn_2_90428(j + 1);
        if (CHALLENGE_BYTE(0x440C + j) == 1) {
            fn_2_92654(j + 1, 2);
        }
    }
    fn_2_90428(7);
    if (CHALLENGE_BYTE(0x440E) == 1) {
        fn_2_92654(7, 2);
    }
    if (CHALLENGE_BYTE(0x4439) == 1) {
        fn_2_90428(8);
        fn_2_92654(8, 2);
    }
    for (j = 0; j < 6; j++) {
        fn_2_90428(j + 10);
        fn_2_90428(j + 0x10);
        if ((CHALLENGE_BYTE(fn_2_4C3D8(j) * 10 + 0x40F1) == 2 || CHALLENGE_BYTE(fn_2_4C3D8(j) * 10 + 0x40F1) == 3) &&
            lbl_2_bss_1A8248->captain != j) {
            fn_2_92654(j + 10, 2);
        }
    }
    fn_2_90428(0x16);
    fn_2_92654(0x16, 2);
    fn_2_90428(0x17);
    fn_2_92654(0x17, 1);
    if (lbl_2_bss_1A8248->_4446[0] == 0 && lbl_2_bss_1A8248->captain != 5) {
        fn_2_90428(0x18);
        fn_2_92654(0x18, 2);
    }
    if (CHALLENGE_BYTE(0x442A) == 1) {
        fn_2_90428(0x19);
        fn_2_92654(0x19, 1);
        fn_2_90428(0x1A);
        fn_2_92654(0x1A, 1);
        fn_2_90428(0x1B);
        fn_2_92654(0x1B, 2);
    }
    fn_2_94854(0xB);
    menuCamera_setFollowSlot(0);
    menuCamera_setEyeFollowsSlot(1);
    menuCamera_setSpringPreset(1);
    menuCamera_snapToPreset();
    CHALLENGE_BYTE(0x44F3) = 1;
    switch (SCENE_MODE) {
    case 0:
        CHALLENGE_BYTE(0x441B) = 1;
        break;
    }
}

// .text:0x00024728 size:0xD8 mapped:0x806637BC
BOOL fn_2_24728(s32 entry) {
    u8 *base = (u8 *)lbl_2_bss_1A8248;
    s32 i;
    for (i = 0; i < 51; i++) {
        u8 *record = base + i * 10;
        if (record[0x40F1] == 0 && record[0x40F2] == 1 &&
            record[0x40F5] == entry &&
            base[0x4431 + entry] == 1) {
            return TRUE;
        }
    }
    return FALSE;
}

// .text:0x00024724 size:0x4 mapped:0x806637B8
void fn_2_24724(void) {
    return;
}

#pragma dont_inline on
// .text:0x000246E0 size:0x44 mapped:0x80663774
void fn_2_246E0(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_2_24488, 2);
    *(s16 *)((u8 *)item + 0x1C) = 0;
    fn_2_54354(lbl_2_data_9FC8, 0x293);
}

// .text:0x0002469C size:0x44 mapped:0x80663730
void fn_2_2469C(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_2_243BC, 2);
    *(s16 *)((u8 *)item + 0x1C) = 0;
    fn_2_54354(lbl_2_data_F0EC, 0x13A);
}

// .text:0x00024650 size:0x4C mapped:0x806636E4
void fn_2_24650(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_2_242FC, 2);
    *(s16 *)((u8 *)item + 0x1C) = 0;
    *(s16 *)((u8 *)item + 0x1E) = 0;
    fn_2_54234(lbl_2_data_104EC, 2);
}

#pragma dont_inline reset

// .text:0x0002460C size:0x44 mapped:0x806636A0
void fn_2_2460C(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_2_24238, 2);
    *(s16 *)((u8 *)item + 0x1C) = 0;
    fn_2_54354(lbl_2_data_105FC, 2);
}

// .text:0x000245C8 size:0x44 mapped:0x8066365C
void fn_2_245C8(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_2_2416C, 2);
    *(s16 *)((u8 *)item + 0x1C) = 0;
    fn_2_54354(lbl_2_data_1073C, 8);
}

// .text:0x00024488 size:0x140 mapped:0x8066351C
void fn_2_24488(void) {
    u16 *item = (u16 *)currentDrawingItem;
    switch (item[14]) {
    case 0:
        fn_2_4E878(item, lbl_2_data_4C68);
        item[14] = 1;
        item[12] = 0;
        break;
    case 1:
        if ((s32)lbl_2_bss_1A824C[0x190000 + 0x78FB] == 1) {
            lbl_2_bss_1A8234[0x160000 + 0x268A] = 1;
            lbl_2_bss_1A8234[0x160000 + 0x2874] = 0;
        } else {
            lbl_2_bss_1A8234[0x160000 + 0x2874] = 1;
            lbl_2_bss_1A8234[0x160000 + 0x268A] = 0;
        }
        break;
    }
    fn_2_53F88(item);
    fn_2_54120();
    if (lbl_2_bss_1A8234[0x160000 + 0x2992] != 0) {
        text_freeAllBlocks();
        fn_2_53DF8(item);
        fn_8000F8F4(item);
        fn_2_4E858(item);
        removeCurrentDrawingItem();
        item[14] = 0;
        lbl_2_bss_1A8234[0x160000 + 0x2992] = 0;
    }
}

// .text:0x000243BC size:0xCC mapped:0x80663450
void fn_2_243BC(void) {
    u16 *item = (u16 *)currentDrawingItem;
    switch (item[14]) {
    case 1:
        break;
    case 0:
        fn_2_4E878(item, lbl_2_data_C96C);
        item[14] = 1;
        item[12] = 0;
        break;
    }
    fn_2_53F88(item);
    fn_2_54120();
    if (lbl_2_bss_1A8234[0x160000 + 0x2992] != 0) {
        text_freeAllBlocks();
        fn_2_53DF8(item);
        fn_8000F8F4(item);
        fn_2_4E858(item);
        removeCurrentDrawingItem();
        item[14] = 0;
        lbl_2_bss_1A8234[0x160000 + 0x2992] = 0;
    }
}

// .text:0x000242FC size:0xC0 mapped:0x80663390
void fn_2_242FC(void) {
    u16 *item = (u16 *)currentDrawingItem;
    switch (item[15]) {
    case 1:
        break;
    case 0:
        fn_2_4E878(item, lbl_2_data_1048C);
        item[15] = 1;
        item[13] = 0;
        break;
    }
    fn_2_53F04(item);
    fn_2_5400C();
    if (lbl_2_bss_1A8230[0x32A86] != 0) {
        fn_2_53CEC(item);
        fn_2_4E858(item);
        removeCurrentDrawingItem();
        item[15] = 0;
        lbl_2_bss_1A8230[0x32A86] = 0;
    }
}

// .text:0x00024238 size:0xC4 mapped:0x806632CC
void fn_2_24238(void) {
    u16 *item = (u16 *)currentDrawingItem;
    switch (item[14]) {
    case 1:
        break;
    case 0:
        fn_2_4E878(item, lbl_2_data_1059C);
        item[14] = 1;
        item[12] = 0;
        break;
    }
    fn_2_53F88(item);
    fn_2_54120();
    if (lbl_2_bss_1A8234[0x160000 + 0x2992] != 0) {
        text_freeAllBlocks();
        fn_2_53DF8(item);
        fn_2_4E858(item);
        removeCurrentDrawingItem();
        item[14] = 0;
        lbl_2_bss_1A8234[0x160000 + 0x2992] = 0;
    }
}

// .text:0x0002416C size:0xCC mapped:0x80663200
void fn_2_2416C(void) {
    u16 *item = (u16 *)currentDrawingItem;
    switch (item[14]) {
    case 1:
        break;
    case 0:
        fn_2_4E878(item, lbl_2_data_1061C);
        item[14] = 1;
        item[12] = 0;
        break;
    }
    fn_2_53F88(item);
    fn_2_54120();
    if (lbl_2_bss_1A8234[0x160000 + 0x2992] != 0) {
        text_freeAllBlocks();
        fn_2_53DF8(item);
        fn_8000F8F4(item);
        fn_2_4E858(item);
        removeCurrentDrawingItem();
        item[14] = 0;
        lbl_2_bss_1A8234[0x160000 + 0x2992] = 0;
    }
}

// .text:0x00020D08 size:0x3464 mapped:0x8065FD9C
#define SCENE_STATE (*(s16 *)&lbl_2_bss_1A823C[0x32])
#define NEW_CHILD(func)                                           \
    {                                                             \
        DrawingSceneStruct *child = insertGraphicDrawingFunction(func, 2); \
        *(s8 *)((u8 *)child + 0x28) = 0;                          \
        item->state = 0;                                          \
    }
#define NEW_CHILD_ONLY(func)                                                \
    {                                                                       \
        DrawingSceneStruct *child = insertGraphicDrawingFunction(func, 2);  \
        *(s8 *)((u8 *)child + 0x28) = 0;                                    \
    }
#define UI_TIMER (*(s16 *)&lbl_2_bss_1A8234[0x160000 + 0x2600])
#define CHALLENGE_REC(idx, off) CHALLENGE_BYTE((idx) * 10 + (off))
#define CHALLENGE_REC2(idx, off) (((u8 (*)[10])lbl_2_bss_1A8248->_40EE)[idx][(off) - 0x40EE])
#define PORTRAIT_OR_SCENE(captainOffset, flagOffset)                                               \
    if ((s32)CHALLENGE_BYTE(flagOffset) == 1) {                                                       \
        changeScene(3, 6);                                                                         \
    } else {                                                                                       \
        challenge_setTransitionScreenCharacterPortrait(0xC, (s8)lbl_2_data_3CE0[CHALLENGE_BYTE(captainOffset)]); \
        WORK_S16(0x76F2) = 0x78;                                                                   \
    }

void fn_2_20D08(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    GameInitVariables *settings = &g_d_GameSettings;
    u8 *card = cardCheck;
    WORK_U8(0x78FB) = 0;
    switch (SCENE_STATE) {
    case 0:
        if ((s8)CHALLENGE_BYTE(0x44F4) == 0) {
            SCENE_STATE = 1;
            break;
        }
        fn_2_515DC(4);
        lbl_2_bss_1A8234[0x160000 + 0x2992] = 0;
        lbl_2_bss_1A8230[0x30000 + 0x2A86] = 0;
        fn_2_54474();
        fn_2_2469C();
        fn_2_24650();
        WORK_U8(0x7864) = 1;
        SCENE_STATE = 0x65;
        break;
    case 1: {
        DrawingSceneStruct *child;
        WORK_S16(0x7746) = 7;
        child = insertGraphicDrawingFunction(fn_2_1B314, 2);
        *(s8 *)((u8 *)child + 0x28) = 0;
        GXSetCopyClear(lbl_2_data_107C8, 0xFFFFFF);
        item->state = 0;
        SCENE_STATE = 2;
        break;
    }
    case 2:
        if (item->state == 1) {
            SCENE_STATE = 3;
        }
        break;
    case 3:
        NEW_CHILD(fn_2_1B1BC)
        SCENE_STATE = 4;
        break;
    case 4:
        if (item->state == 1) {
            SCENE_STATE = 5;
        }
        break;
    case 5:
        fn_2_515DC(4);
        lbl_2_bss_1A8234[0x160000 + 0x2992] = 0;
        lbl_2_bss_1A8230[0x30000 + 0x2A86] = 0;
        fn_2_54474();
        fn_2_246E0();
        fn_2_24800();
        SCENE_STATE = 7;
        break;
    case 7:
        playStream(0xA);
        SCENE_STATE = 0xB;
        break;
    case 11:
        GXSetCopyClear(lbl_2_data_107C8, 0xFFFFFF);
        switch (SCENE_MODE) {
        case 0:
        case 1:
        case 2:
        case 7:
        case 8:
            changeScene(1, 6);
            break;
        case 3:
            if (CHALLENGE_S8(0x4443) == 1) {
                changeScene(1, 6);
            } else {
                challenge_setTransitionScreenCharacterPortrait(0xA, (s8)lbl_2_data_3CE0[CHALLENGE_BYTE(0x441E)]);
            }
            break;
        case 4:
            if (CHALLENGE_S8(0x443E) == 1) {
                changeScene(1, 6);
            } else {
                challenge_setTransitionScreenCharacterPortrait(0xA, (s8)lbl_2_data_3CE0[CHALLENGE_BYTE(0x441C)]);
            }
            changeScene(1, 6);
            break;
        case 5:
            if (CHALLENGE_S8(0x443C) == 1) {
                changeScene(1, 6);
            } else {
                challenge_setTransitionScreenCharacterPortrait(0xA, (s8)lbl_2_data_3CE0[CHALLENGE_BYTE(0x441C)]);
            }
            break;
        case 6:
            changeScene(1, 6);
            break;
        default:
            changeScene(1, 6);
            break;
        }
        lbl_2_bss_1A8234[0x160000 + 0x264B] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x2657] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x2659] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x265A] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x265B] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x2676] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x2677] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x2678] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x265F] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x2663] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x268A] = 1;
        SCENE_STATE = 0xC;
        break;
    case 12:
        if (lbl_8037169C[0x12] != 0) {
            switch (SCENE_MODE) {
            case 0:
                if (CHALLENGE_BYTE(0x4505) == 0) {
                    CHALLENGE_BYTE(0x4505) = 1;
                    SCENE_STATE = 0xD;
                } else {
                    SCENE_STATE = 0x12;
                }
                break;
            case 1:
                SCENE_STATE = 0x12;
                break;
            case 2:
                SCENE_STATE = 0x12;
                break;
            case 3:
                fn_2_4358C();
                fn_2_42BE8();
                fn_2_432EC();
                SCENE_STATE = 0x34;
                break;
            case 4:
                fn_2_4B1AC();
                fn_2_4358C();
                fn_2_42BE8();
                fn_2_432EC();
                SCENE_STATE = 0x36;
                break;
            case 5:
                fn_2_4AEE4();
                fn_2_4358C();
                SCENE_STATE = 0x38;
                fn_2_42BE8();
                fn_2_432EC();
                break;
            case 6:
                fn_2_4ACF8();
                fn_2_4358C();
                SCENE_STATE = 0x3A;
                fn_2_42BE8();
                fn_2_432EC();
                break;
            case 7:
                SCENE_STATE = 0x12;
                break;
            case 8:
                SCENE_STATE = 0x12;
                break;
            }
        }
        break;
    case 13:
        fn_2_422FC(0x33);
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0xE;
        break;
    case 14:
        if (item->state == 1) {
            if (WORK_U8(0x783F) == 1) {
                WORK_U8(0x783F) = 0;
                SCENE_STATE = 0x10;
            } else {
                SCENE_STATE = 0xF;
            }
        } else {
            if (PAD_NEW2() & INPUT_BUTTON_START) {
                if (WORK_U8(0x72B9) == 1) {
                    WORK_U8(0x783F) = 1;
                }
            }
        }
        break;
    case 15:
        SCENE_STATE = 0x12;
        break;
    case 16:
        lbl_2_bss_1A8234[0x160000 + 0x2842] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x2871] = 1;
        lbl_2_bss_1A8234[0x160000 + 0x2872] = 1;
        NEW_CHILD(fn_2_38538)
        SCENE_STATE = 0x11;
        break;
    case 17:
        if (item->state == 1) {
            SCENE_STATE = 0x12;
        }
        break;
    case 18:
    state18: {
        int input;
        int sel;
        CHALLENGE_BYTE(0x44F3) = 0;
        if ((s32)WORK_U8(0x789E) == 1) {
            fn_2_1C490();
            WORK_U8(0x789E) = 0;
            SCENE_STATE = 0x1E;
            break;
        }
        if (fn_2_686B0(0) == 1) {
            SCENE_STATE = 0x20;
            break;
        }
        input = fn_2_20074();
        sel = fn_2_201E4(CHALLENGE_S16(0x16C2), input);
        if (input == -1) {
            WORK_U8(0x78FB) = 1;
        }
        if (sel != -1 && (CHALLENGE_REC2(sel, 0x40F2) == 7 || CHALLENGE_REC2(sel, 0x40F2) == 8) &&
            CHALLENGE_BYTE(0x442A) == 1) {
            CHALLENGE_S16(0x16C0) = sel;
            fn_2_1C490();
            SCENE_STATE = 0x1C;
        } else if (sel != -1 && CHALLENGE_REC(sel, 0x40F1) != 1 && CHALLENGE_REC(sel, 0x40F4) == 0 &&
                   CHALLENGE_REC(sel, 0x40F2) != 7 && CHALLENGE_REC(sel, 0x40F2) != 8) {
            CHALLENGE_S16(0x16C0) = sel;
            CHALLENGE_BYTE(0x4448) = input;
            CHALLENGE_S16(0x16BE) = CHALLENGE_S16(0x16C2);
            WORK_U8(0x783D) = 0;
            fn_2_72054(0, 2);
            fn_2_1C490();
            SCENE_STATE = 0x14;
            break;
        } else {
            u16 held = PAD_RAW();
            if ((held & INPUT_BUTTON_UP) || (held & INPUT_BUTTON_DOWN) || (held & INPUT_BUTTON_LEFT) ||
                (held & INPUT_BUTTON_RIGHT)) {
                WORK_U8(0x78FB) = 1;
            }
            CHALLENGE_S8(0x4448) = -1;
        }
        if (PAD_NEW2() & INPUT_BUTTON_A) {
            ChallengeState *c = lbl_2_bss_1A8248;
            u8 *rec = (u8 *)c + c->_16C2 * 10;
            if (rec[0x40F1] == 0 && rec[0x40F2] == 0 &&
                rec[0x40F3] != c->captain && fn_2_45938() == 1) {
                CHALLENGE_BYTE(0x44EF) = 0;
                CHALLENGE_BYTE(0x44F3) = 1;
                SCENE_STATE = 0x17;
                break;
            }
            if (CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F1) == 0 && CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F2) == 0 &&
                CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F3) == CHALLENGE_BYTE(0x441C) && CHALLENGE_BYTE(0x441C) == 5 &&
                CHALLENGE_BYTE(0x4422) >= 5) {
                CHALLENGE_BYTE(0x44EF) = 1;
                CHALLENGE_BYTE(0x44F3) = 1;
                SCENE_STATE = 0x17;
                break;
            }
            if (CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F1) == 0 && CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F2) == 0 &&
                CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F3) != CHALLENGE_BYTE(0x441C) && fn_2_45938() == 0) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                break;
            }
            if (CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F1) == 0 && CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F2) == 4 &&
                CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F3) != CHALLENGE_BYTE(0x441C)) {
                CHALLENGE_BYTE(0x44EF) = 0;
                CHALLENGE_BYTE(0x44F3) = 1;
                SCENE_STATE = 0x2D;
                break;
            }
            if (CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F1) == 0 && CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F2) == 6) {
                SCENE_STATE = 0x60;
                CHALLENGE_BYTE(0x44F3) = 1;
                break;
            }
        }
        {
            int r = fn_2_684D0(0);
            if (r >= 2 && r <= 6 && (PAD_NEW2() & INPUT_BUTTON_A)) {
                fn_2_68654(0, 1);
                fn_2_68638(0, r);
                CHALLENGE_BYTE(0x44F3) = 1;
                SCENE_STATE = 0x26;
                goto state38;
            }
        }
        {
            u16 pad = PAD_NEW2();
            if (pad & INPUT_BUTTON_START) {
                CHALLENGE_BYTE(0x44F2) = 3;
                WORK_S16(0x76D8) = 0;
                item->state = 0;
                *(s16 *)&lbl_2_bss_1A8234[0x160000 + 0x2600] = 0x10;
                lbl_2_bss_1A8234[0x160000 + 0x2660] = 1;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                CHALLENGE_BYTE(0x44F3) = 1;
                SCENE_STATE = 0x40;
            } else if (pad & INPUT_TRIGGER_R) {
                CHALLENGE_BYTE(0x44F3) = 1;
                SCENE_STATE = 0x5A;
            }
        }
        break;
    }
    case 19:
    state19:
        CHALLENGE_S16(0x16BE) = CHALLENGE_S16(0x16C2);
        WORK_U8(0x783D) = 0;
        fn_2_72054(0, 2);
        SCENE_STATE = 0x14;
        break;
    case 20:
        if (fn_2_686B0(0) == 1) {
            fn_2_6AF80(0, 0);
            fn_2_1C41C();
            WORK_S16(0x76F2) = 10;
            SCENE_STATE = 0x20;
            break;
        }
        {
            int r = fn_2_684D0(0);
            if (r >= 2 && r <= 6 && (PAD_NEW2() & INPUT_BUTTON_A)) {
                fn_2_68654(0, 1);
                fn_2_68638(0, r);
                CHALLENGE_BYTE(0x44F3) = 1;
                fn_2_6AF80(0, 0);
                fn_2_1C41C();
                SCENE_STATE = 0x26;
                goto state38;
            }
        }
        if (fn_2_6AFD4(0) == 1) {
            fn_2_6AF80(0, 0);
            if (CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F6) == 0) {
                fn_2_1C41C();
                SCENE_STATE = 0x12;
                goto state18;
            }
            CHALLENGE_S16(0x16C0) = fn_2_201E4(CHALLENGE_S16(0x16C2), (s8)CHALLENGE_BYTE(0x4448));
            SCENE_STATE = 0x13;
            goto state19;
        }
        break;
    case 28:
        fn_2_422FC(0x34);
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x1D;
        break;
    case 29:
        if (item->state == 1) {
            fn_2_1C41C();
            SCENE_STATE = 0x12;
        }
        break;
    case 30:
        fn_2_422FC(0x36);
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x1F;
        break;
    case 31:
        if (item->state == 1) {
            fn_2_1C41C();
            fn_2_42EB0();
            fn_2_432EC();
            SCENE_STATE = 0x12;
        }
        break;
    case 21:
        fn_2_422FC(0x13);
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x16;
        break;
    case 22: {
        s16 v = item->state;
        if (v != 0 && WORK_S16(0x72B0) == 0) {
            SCENE_STATE = 0x17;
        } else if (v != 0 && WORK_S16(0x72B0) == 1) {
            SCENE_STATE = 0x12;
        }
        break;
    }
    case 23:
        fn_2_4E1C0();
        fn_2_422FC(2);
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x18;
        break;
    case 24: {
        s16 v = item->state;
        if (v == 1 && WORK_S16(0x76DE) == 0) {
            PORTRAIT_OR_SCENE(0x441E, 0x4443)
            WORK_S32(0x76A8) = fn_80062890(0xB);
            SCENE_STATE = 0x19;
        } else if (v == 1 && WORK_S16(0x76DE) == 1) {
            SCENE_STATE = 0x12;
        }
        break;
    }
    case 25:
        if (!(u8)fn_80062794(WORK_S32(0x76A8))) {
            SCENE_STATE = 0x1A;
        }
        break;
    case 26:
        if (CHALLENGE_S8(0x4443) == 1) {
            if (lbl_8037169C[0x13] != 0) {
                NEW_CHILD(fn_2_40B90)
                SCENE_STATE = 0x1B;
            }
        } else if (WORK_S16(0x76F2)-- == 0) {
            NEW_CHILD(fn_2_40B90)
            SCENE_STATE = 0x1B;
        }
        break;
    case 27:
        if (item->state == 1) {
            if (CHALLENGE_S8(0x4443) == 1) {
                currentDrawingItem->func = fn_2_1B7B4;
                g_MenuControl.sceneMode = 3;
                g_MenuControl.sceneState = 0;
            } else {
                fn_2_4D194();
                currentDrawingItem->func = currentScreenFunctionChooser;
                changeScreenVariables(0xA);
                g_MenuControl.sceneMode = 3;
                g_MenuControl.sceneState = 0;
            }
        }
        break;
    case 32:
        if (WORK_S16(0x76F2)-- == 0) {
            SCENE_STATE = 0x21;
        }
        break;
    case 33:
        CHALLENGE_BYTE(0x4430) = 0;
        fn_2_4DEE8();
        unknownSettingTeamValues();
        fn_2_422FC(3);
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x22;
        break;
    case 34:
        if (item->state == 1) {
            WORK_S32(0x76A8) = fn_80062890(0xB);
            SCENE_STATE = 0x23;
        }
        break;
    case 35:
        if (!(u8)fn_80062794(WORK_S32(0x76A8))) {
            PORTRAIT_OR_SCENE(0x441C, 0x443E)
            SCENE_STATE = 0x24;
        }
        break;
    case 36:
        if (CHALLENGE_S8(0x443E) == 1) {
            if (lbl_8037169C[0x13] != 0) {
                NEW_CHILD(fn_2_40B90)
                SCENE_STATE = 0x25;
            }
        } else if (WORK_S16(0x76F2)-- == 0) {
            NEW_CHILD(fn_2_40B90)
            SCENE_STATE = 0x25;
        }
        break;
    case 37:
        if (item->state == 1) {
            if (CHALLENGE_S8(0x443E) == 1) {
                currentDrawingItem->func = fn_2_1B7B4;
                g_MenuControl.sceneMode = 4;
                g_MenuControl.sceneState = 0;
            } else {
                fn_2_4CEE0();
                currentDrawingItem->func = currentScreenFunctionChooser;
                changeScreenVariables(4);
                g_MenuControl.sceneMode = 4;
                g_MenuControl.sceneState = 0;
            }
        }
        break;
    case 38:
    state38: {
        int k = fn_2_68690(0) - 2;
        switch (k) {
        case 0:
            fn_2_422FC((s8)CHALLENGE_BYTE(0x44F8 + k) + 0x14);
            break;
        case 1:
            fn_2_422FC((s8)CHALLENGE_BYTE(0x44F8 + k) + 0x18);
            break;
        case 2:
            fn_2_422FC((s8)CHALLENGE_BYTE(0x44F8 + k) + 0x1C);
            break;
        case 3:
            fn_2_422FC((s8)CHALLENGE_BYTE(0x44F8 + k) + 0x20);
            break;
        case 4:
            fn_2_422FC((s8)CHALLENGE_BYTE(0x44F8 + k) + 0x24);
            break;
        }
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x27;
        break;
    }
    case 39: {
        s16 v = item->state;
        if (v == 1 && WORK_S16(0x76DE) == 0) {
            SCENE_STATE = 0x28;
        } else if (v == 1 && WORK_S16(0x76DE) == 1) {
            fn_2_68654(0, 0);
            SCENE_STATE = 0x12;
        }
        break;
    }
    case 40:
        fn_2_4D67C();
        fn_2_422FC(4);
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x29;
        break;
    case 41:
        if (item->state == 1) {
            WORK_S32(0x76A8) = fn_80062890(6);
            SCENE_STATE = 0x2B;
        }
        break;
    case 43:
        if (!(u8)fn_80062794(WORK_S32(0x76A8))) {
            PORTRAIT_OR_SCENE(0x441C, 0x443C)
            SCENE_STATE = 0x2A;
        }
        break;
    case 42:
        if (CHALLENGE_S8(0x443C) == 1) {
            if (lbl_8037169C[0x13] != 0) {
                NEW_CHILD(fn_2_40B90)
                SCENE_STATE = 0x2C;
            }
        } else if (WORK_S16(0x76F2)-- == 0) {
            NEW_CHILD(fn_2_40B90)
            SCENE_STATE = 0x2C;
        }
        break;
    case 44:
        if (item->state == 1) {
            fn_2_68654(0, 0);
            if (CHALLENGE_S8(0x443C) == 1) {
                currentDrawingItem->func = fn_2_1B7B4;
                g_MenuControl.sceneMode = 5;
                g_MenuControl.sceneState = 0;
            } else {
                fn_2_4C9C4();
                currentDrawingItem->func = currentScreenFunctionChooser;
                changeScreenVariables(4);
                g_MenuControl.sceneMode = 5;
                g_MenuControl.sceneState = 0;
            }
        }
        break;
    case 45:
        fn_2_422FC((s8)CHALLENGE_BYTE(0x44FD) + 0x28);
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x2E;
        break;
    case 46: {
        s16 v = item->state;
        if (v == 1 && WORK_S16(0x76DE) == 0) {
            SCENE_STATE = 0x2F;
        } else if (v == 1 && WORK_S16(0x76DE) == 1) {
            SCENE_STATE = 0x12;
        }
        break;
    }
    case 47:
        fn_2_4D378();
        SCENE_STATE = 0x30;
        break;
    case 48:
        WORK_S32(0x76A8) = fn_80062890(0xB);
        SCENE_STATE = 0x31;
        break;
    case 49:
        if (!(u8)fn_80062794(WORK_S32(0x76A8))) {
            PORTRAIT_OR_SCENE(0x441C, 0x4441)
            SCENE_STATE = 0x32;
        }
        break;
    case 50:
        if (CHALLENGE_S8(0x4441) == 1) {
            if (lbl_8037169C[0x13] != 0) {
                NEW_CHILD(fn_2_40B90)
                SCENE_STATE = 0x33;
            }
        } else if (WORK_S16(0x76F2)-- == 0) {
            NEW_CHILD(fn_2_40B90)
            SCENE_STATE = 0x33;
        }
        break;
    case 51:
        if (item->state == 1) {
            if (CHALLENGE_S8(0x4441) == 1) {
                currentDrawingItem->func = fn_2_1B7B4;
                g_MenuControl.sceneMode = 6;
                g_MenuControl.sceneState = 0;
            } else {
                fn_2_4C81C();
                currentDrawingItem->func = currentScreenFunctionChooser;
                changeScreenVariables(4);
                g_MenuControl.sceneMode = 6;
                g_MenuControl.sceneState = 0;
            }
        }
        break;
    case 52: {
        s8 v = WORK_U8(0x7843);
        if (v == 0) {
            if (CHALLENGE_BYTE(0x441C) == 5) {
                fn_2_422FC(6);
            } else {
                fn_2_422FC(5);
            }
            NEW_CHILD_ONLY(fn_2_42388)
        } else if (v == 1) {
            fn_2_422FC(7);
            NEW_CHILD_ONLY(fn_2_42388)
        } else if (v == 2) {
            fn_2_422FC(8);
            NEW_CHILD_ONLY(fn_2_42388)
        }
        item->state = 0;
        SCENE_STATE = 0x35;
        break;
    }
    case 53:
        if (item->state == 1) {
            s8 v = WORK_U8(0x7843);
            if (v == 0) {
                CHALLENGE_BYTE(0x44FE + CHALLENGE_BYTE(0x441E)) = 0;
            } else if (v == 1) {
                CHALLENGE_BYTE(0x44FE + CHALLENGE_BYTE(0x441E)) = 1;
            } else {
                CHALLENGE_BYTE(0x44FE + CHALLENGE_BYTE(0x441E)) = 2;
            }
            if ((s8)CHALLENGE_BYTE(0x44EF) != 0) {
                CHALLENGE_BYTE(0x44F0) = 1;
            }
            fn_2_45978();
            SCENE_STATE = 0x12;
        }
        break;
    case 54: {
        s8 v = WORK_U8(0x7843);
        if (v == 0) {
            fn_2_422FC(9);
            NEW_CHILD_ONLY(fn_2_42388)
        } else if (v == 1) {
            fn_2_422FC(0xA);
            NEW_CHILD_ONLY(fn_2_42388)
        } else {
            fn_2_422FC(0xB);
            NEW_CHILD_ONLY(fn_2_42388)
        }
        item->state = 0;
        SCENE_STATE = 0x37;
        break;
    }
    case 55:
        if (item->state == 1) {
            s8 v;
            if (CHALLENGE_BYTE(0x442B) < 3) {
                CHALLENGE_BYTE(0x442B)++;
            }
            v = WORK_U8(0x7843);
            if (v == 0) {
                if (CHALLENGE_BYTE(0x442C) < 3) {
                    CHALLENGE_BYTE(0x442C)++;
                }
                CHALLENGE_BYTE(0x4504) = 0;
            } else if (v == 1) {
                if (CHALLENGE_BYTE(0x442D) < 3) {
                    CHALLENGE_BYTE(0x442D)++;
                }
                CHALLENGE_BYTE(0x4504) = 1;
            } else {
                if (CHALLENGE_BYTE(0x442E) < 3) {
                    CHALLENGE_BYTE(0x442E)++;
                }
                CHALLENGE_BYTE(0x4504) = 2;
            }
            fn_2_45978();
            if (CHALLENGE_REC2(CHALLENGE_S16(0x16C2), 0x40F6) == 0) {
                fn_2_1C41C();
                SCENE_STATE = 0x12;
                goto state18;
            }
            CHALLENGE_S16(0x16C0) = fn_2_201E4(CHALLENGE_S16(0x16C2), (s8)CHALLENGE_BYTE(0x4448));
            SCENE_STATE = 0x13;
            goto state19;
        }
        break;
    case 56: {
        s8 v = WORK_U8(0x7843);
        if (v == 0) {
            fn_2_422FC(0xC);
            NEW_CHILD_ONLY(fn_2_42388)
        } else if (v == 1) {
            fn_2_422FC(0xD);
            NEW_CHILD_ONLY(fn_2_42388)
        } else if (v == 2) {
            fn_2_422FC(0xE);
            NEW_CHILD_ONLY(fn_2_42388)
        }
        item->state = 0;
        SCENE_STATE = 0x39;
        break;
    }
    case 57:
        if (item->state == 1) {
            fn_2_45978();
            SCENE_STATE = 0x12;
        }
        break;
    case 58: {
        s8 v = WORK_U8(0x7843);
        if (v == 0) {
            fn_2_422FC(0xF);
            NEW_CHILD_ONLY(fn_2_42388)
        } else if (v == 1) {
            fn_2_422FC(0x10);
            NEW_CHILD_ONLY(fn_2_42388)
        } else {
            fn_2_422FC(0x11);
            NEW_CHILD_ONLY(fn_2_42388)
        }
        item->state = 0;
        SCENE_STATE = 0x3B;
        break;
    }
    case 59:
        if (item->state == 1) {
            fn_2_45978();
            fn_2_43404();
            fn_2_42708();
            fn_2_432EC();
            SCENE_STATE = 0x12;
        }
        break;
    case 60:
        changeScene(4, 6);
        SCENE_STATE = 0x3D;
        break;
    case 61:
        if (lbl_8037169C[0x13] != 0) {
            GXSetCopyClear(lbl_2_data_107C8, 0xFFFFFF);
            SCENE_STATE = 0x3E;
        }
        break;
    case 62:
        NEW_CHILD(fn_2_40B90)
        SCENE_STATE = 0x3F;
        break;
    case 63:
        if (item->state == 1) {
            changeScreenVariables(0xF);
            g_MenuControl.sceneMode = 0xA;
            g_MenuControl.sceneState = 0;
            currentDrawingItem->func = currentScreenFunctionChooser;
            SCENE_STATE = 0;
        }
        break;
    case 90:
        fn_2_422FC(0x12);
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x5B;
        break;
    case 91:
        if (item->state == 1) {
            CHALLENGE_BYTE(0x44F2) = 0;
            SCENE_STATE = 0x12;
        }
        break;
    case 92:
        if (CHALLENGE_BYTE(0x4422) >= 4) {
            fn_2_422FC(0x2D);
        } else {
            fn_2_422FC(0x2E);
        }
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x5D;
        break;
    case 93: {
        s16 v = item->state;
        if (v == 1 && CHALLENGE_BYTE(0x4422) >= 4) {
            WORK_S16(0x76E4) = lbl_2_data_2E6C[CHALLENGE_BYTE(0x4415)];
            SCENE_STATE = 0x5E;
        } else if (v == 1 && CHALLENGE_BYTE(0x4422) < 4) {
            SCENE_STATE = 0x12;
        }
        break;
    }
    case 94:
        fn_2_422FC(0x2F);
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x5F;
        break;
    case 95:
        if (item->state == 1) {
            SCENE_STATE = 0x12;
        }
        break;
    case 96:
        fn_2_422FC(0x30);
        NEW_CHILD(fn_2_42388)
        WORK_U8(0x78FA) = 1;
        WORK_S32(0x76A8) = fn_80062890(0x10);
        SCENE_STATE = 0x61;
        break;
    case 97: {
        s16 v = item->state;
        if (v == 1 && WORK_S16(0x72B0) == 0) {
            SCENE_STATE = 0x63;
        } else if (v == 1 && WORK_S16(0x72B0) == 1) {
            CHALLENGE_BYTE(0x44F2) = 0;
            SCENE_STATE = 0x12;
        }
        break;
    }
    case 98:
        if (item->state == 1) {
            CHALLENGE_BYTE(0x44F2) = 0;
            SCENE_STATE = 0x12;
        }
        break;
    case 99:
        fn_2_422FC(0x31);
        NEW_CHILD(fn_2_42388)
        SCENE_STATE = 0x64;
        break;
    case 100:
        if (item->state == 1) {
            CHALLENGE_BYTE(0x44F2) = 0;
            SCENE_STATE = 0x12;
        }
        break;
    case 101:
        fn_2_439D0();
        fn_2_430F4();
        fn_2_42FC8();
        GXSetCopyClear(lbl_2_data_107C8, 0xFFFFFF);
        settings->challengeShopItemActive[(s8)CHALLENGE_BYTE(0x444B)] = FALSE;
        CHALLENGE_S8(0x444C) = -1;
        CHALLENGE_S8(0x444B) = -1;
        changeScene(1, 6);
        item->state = 1;
        SCENE_STATE = 0x66;
        break;
    case 102:
        if (item->state == 1) {
            SCENE_STATE = 0x67;
        }
        break;
    case 103:
        NEW_CHILD(fn_2_3D878)
        SCENE_STATE = 0x68;
        break;
    case 104:
        if (item->state == 1) {
            lbl_2_bss_1A8234[0x160000 + 0x283A] = 1;
            lbl_2_bss_1A8230[0x30000 + 0x2A55] = 1;
            *(s16 *)((u8 *)item + 0x14) = 0x32;
            SCENE_STATE = 0x69;
        }
        break;
    case 105:
        if ((*(s16 *)((u8 *)item + 0x14))-- == 0) {
            SCENE_STATE = 0x6A;
        }
        break;
    case 106:
        WORK_U8(0x78F7) = 1;
        NEW_CHILD(fn_2_399C0)
        SCENE_STATE = 0x6B;
        break;
    case 107:
        if (item->state == 1) {
            SCENE_STATE = 0x6C;
        }
        break;
    case 108:
        if (lbl_2_bss_1A8244[0xF5] == 0) {
            lbl_2_bss_1A8244[0xF5] = 1;
            if (settings->_12 < 1) {
                settings->_12 = 1;
            }
            NEW_CHILD(fn_2_3DDC4)
            SCENE_STATE = 0x6D;
        } else {
            item->state = 1;
            SCENE_STATE = 0x6D;
        }
        break;
    case 109:
        if (item->state == 1) {
            SCENE_STATE = 0x6E;
        }
        break;
    case 110:
        if (lbl_2_bss_1A8244[0xE7] == 0 && CHALLENGE_BYTE(0x4415) == 3) {
            lbl_2_bss_1A8244[0xF4] = 1;
            NEW_CHILD(fn_2_3DC60)
            SCENE_STATE = 0x6F;
        } else {
            item->state = 1;
            SCENE_STATE = 0x6F;
        }
        break;
    case 111:
        if (item->state == 1) {
            SCENE_STATE = 0x70;
        }
        break;
    case 112:
        fn_2_4C36C();
        NEW_CHILD(fn_2_38F48)
        SCENE_STATE = 0x71;
        break;
    case 113:
        if (item->state == 1) {
            SCENE_STATE = 0x72;
        }
        break;
    case 114:
        NEW_CHILD(fn_2_3DAB8)
        SCENE_STATE = 0x73;
        break;
    case 115:
        if (item->state == 1) {
            SCENE_STATE = 0x74;
        }
        break;
    case 116:
        NEW_CHILD(fn_2_3D5C4)
        SCENE_STATE = 0x75;
        break;
    case 117:
        if (item->state == 1) {
            SCENE_STATE = 0x76;
        }
        break;
    case 118:
        SCENE_STATE = 0x77;
        break;
    case 119:
        fn_2_42FC8();
        fn_2_432EC();
        fn_2_460F8();
        fn_2_44F64();
        fn_2_24EB0(0);
        fn_8003BF54(0, 0, 0, 0, 1, 4, 1, superstarUnlocked[0xF6], 0);
        SCENE_STATE = 0x78;
        break;
    case 120:
        if (fn_2_24E9C()) {
            *(s16 *)((u8 *)item + 0x14) = 0x32;
            SCENE_STATE = 0x79;
        }
        break;
    case 121:
        if ((*(s16 *)((u8 *)item + 0x14))-- == 0) {
            SCENE_STATE = 0x3C;
        }
        break;
    case 64:
        if (UI_TIMER-- == 0) {
            SCENE_STATE = 0x41;
        }
        break;
    case 65: {
        u16 held = PAD_HELD();
        if (held & INPUT_BUTTON_UP) {
            WORK_S16(0x76D8) = (WORK_S16(0x76D8) + 3) % 4;
            if (card[0x47] == 1 && WORK_S16(0x76D8) == 2) {
                WORK_S16(0x76D8) = (WORK_S16(0x76D8) + 3) % 4;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (held & INPUT_BUTTON_DOWN) {
            WORK_S16(0x76D8) = (WORK_S16(0x76D8) + 1) % 4;
            if (card[0x47] == 1 && WORK_S16(0x76D8) == 2) {
                WORK_S16(0x76D8) = (WORK_S16(0x76D8) + 1) % 4;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        {
            u16 pressed = PAD_NEW2();
            if (pressed & INPUT_BUTTON_A) {
                SCENE_STATE = 0x42;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else if (pressed & (INPUT_BUTTON_B | INPUT_BUTTON_START)) {
                SCENE_STATE = 0x44;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
        }
        break;
    }
    case 66:
        SCENE_STATE = 0x43;
        break;
    case 67:
        switch (WORK_S16(0x76D8)) {
        case 0:
            SCENE_STATE = 0x44;
            break;
        case 1:
            SCENE_STATE = 0x56;
            break;
        case 2:
            SCENE_STATE = 0x46;
            break;
        case 3:
            if (card[0x47] == 1) {
                SCENE_STATE = 0x4A;
            } else {
                SCENE_STATE = 0x4E;
            }
            break;
        }
        break;
    case 68:
        UI_TIMER = 0x10;
        lbl_2_bss_1A8234[0x160000 + 0x284A] = 1;
        SCENE_STATE = 0x45;
        break;
    case 69:
        if (UI_TIMER-- == 0) {
            CHALLENGE_BYTE(0x44F2) = 0;
            SCENE_STATE = 0x12;
        }
        break;
    case 70:
        changeScene(3, 6);
        SCENE_STATE = 0x7A;
        break;
    case 71:
        if (UI_TIMER-- == 0) {
            UI_TIMER = 0x10;
            SCENE_STATE = 0x48;
        }
        break;
    case 72:
        WORK_S16(0x72B4) = 5;
        WORK_U8(0x72B6) = 0;
        WORK_U8(0x72B7) = 0;
        NEW_CHILD(fn_2_39408)
        SCENE_STATE = 0x49;
        break;
    case 73: {
        s16 v = item->state;
        if (v == 1) {
            changeScene(3, 6);
            SCENE_STATE = 0x7A;
        } else if (v == 2 || v == 3) {
            CHALLENGE_BYTE(0x44F2) = 0;
            SCENE_STATE = 0x12;
        }
        break;
    }
    case 74:
        UI_TIMER = 0x10;
        lbl_2_bss_1A8234[0x160000 + 0x284A] = 1;
        SCENE_STATE = 0x4B;
        break;
    case 75:
        if (UI_TIMER-- == 0) {
            UI_TIMER = 0x10;
            SCENE_STATE = 0x4C;
        }
        break;
    case 76:
        WORK_S16(0x72B4) = 6;
        WORK_U8(0x72B6) = lbl_2_data_38CC[6];
        WORK_U8(0x72B7) = 0;
        NEW_CHILD(fn_2_39408)
        SCENE_STATE = 0x4D;
        break;
    case 77: {
        s16 v = item->state;
        if (v == 1) {
            changeScene(3, 6);
            SCENE_STATE = 0x7E;
        } else if (v == 2 || v == 3) {
            CHALLENGE_BYTE(0x44F2) = 0;
            SCENE_STATE = 0x12;
        }
        break;
    }
    case 78:
        UI_TIMER = 0x10;
        lbl_2_bss_1A8234[0x160000 + 0x284A] = 1;
        SCENE_STATE = 0x4F;
        break;
    case 79:
        if (UI_TIMER-- == 0) {
            UI_TIMER = 0x10;
            SCENE_STATE = 0x50;
        }
        break;
    case 80:
        WORK_S16(0x72B4) = 7;
        WORK_U8(0x72B6) = lbl_2_data_38CC[7];
        WORK_U8(0x72B7) = 0;
        NEW_CHILD(fn_2_39408)
        SCENE_STATE = 0x51;
        break;
    case 81: {
        s16 v = item->state;
        if (v == 1) {
            changeScene(3, 6);
            SCENE_STATE = 0x7C;
        } else if (v == 2) {
            SCENE_STATE = 0x52;
        } else if (v == 3) {
            CHALLENGE_BYTE(0x44F2) = 0;
            SCENE_STATE = 0x12;
        }
        break;
    }
    case 82:
        WORK_S16(0x72B4) = 8;
        WORK_U8(0x72B6) = lbl_2_data_38CC[8];
        WORK_U8(0x72B7) = 1;
        NEW_CHILD(fn_2_39408)
        SCENE_STATE = 0x53;
        break;
    case 83: {
        s16 v = item->state;
        if (v == 1) {
            changeScene(4, 6);
            SCENE_STATE = 0x7E;
        } else if (v == 2 || v == 3) {
            CHALLENGE_BYTE(0x44F2) = 0;
            SCENE_STATE = 0x12;
        }
        break;
    }
    case 86:
        UI_TIMER = 0x10;
        lbl_2_bss_1A8234[0x160000 + 0x284A] = 1;
        SCENE_STATE = 0x57;
        break;
    case 87:
        if (UI_TIMER-- == 0) {
            UI_TIMER = 0x10;
            SCENE_STATE = 0x58;
        }
        break;
    case 88:
        NEW_CHILD(fn_2_3AF08)
        SCENE_STATE = 0x59;
        break;
    case 89:
        if (item->state == 1) {
            CHALLENGE_BYTE(0x44F2) = 0;
            SCENE_STATE = 0x12;
        }
        break;
    case 122:
        if (lbl_8037169C[0x13] != 0) {
            NEW_CHILD(fn_2_40B90)
            SCENE_STATE = 0x7B;
        }
        break;
    case 123:
        if (item->state == 1) {
            changeScreenVariables(0xF);
            g_MenuControl.sceneMode = 8;
            g_MenuControl.sceneState = 0;
            currentDrawingItem->func = currentScreenFunctionChooser;
            SCENE_STATE = 0;
        }
        break;
    case 124:
        if (lbl_8037169C[0x13] != 0) {
            NEW_CHILD(fn_2_40B90)
            SCENE_STATE = 0x7D;
        }
        break;
    case 125:
        if (item->state == 1) {
            changeScreenVariables(0xF);
            g_MenuControl.sceneMode = 9;
            g_MenuControl.sceneState = 0;
            currentDrawingItem->func = currentScreenFunctionChooser;
            SCENE_STATE = 0;
        }
        break;
    case 126:
        if (lbl_8037169C[0x13] != 0) {
            NEW_CHILD(fn_2_40B90)
            SCENE_STATE = 0x7F;
        }
        break;
    case 127:
        if (item->state == 1) {
            changeScreenVariables(5);
            g_MenuControl.sceneMode = 9;
            g_MenuControl.sceneState = 0;
            currentDrawingItem->func = currentScreenFunctionChooser;
            SCENE_STATE = 0;
        }
        break;
    case 130:
        NEW_CHILD(fn_2_1D440)
        SCENE_STATE = 0x83;
        break;
    case 131:
        if (item->state == 1) {
            CHALLENGE_BYTE(0x44F2) = 0;
            SCENE_STATE = 0x12;
        }
        break;
    default:
        break;
    }
    fn_2_2025C();
    settings->FrameCountWhileNotAtMainMenu += 1;
    WORK_S32(0x76C0)++;
}

// .text:0x00020CB0 size:0x58 mapped:0x8065FD44
int fn_2_20CB0(u32 x) {
    int result = 0;
    switch (x) {
        case 0:
            result = 0;
            break;
        case 4:
            result = 1;
            break;
        case 10:
            result = 2;
            break;
        case 2:
            result = 3;
            break;
        case 6:
            result = 4;
            break;
        case 9:
            result = 5;
            break;
    }
    return result;
}

// .text:0x000207FC size:0x4B4 mapped:0x8065F890
void fn_2_207FC(void) {
    int captain = 0;
    int difficulty;
    s32 i;

    switch (Static_Stats_Tables.captainSelectedID[0]) {
    case CHAR_ID_MARIO:
        break;
    case CHAR_ID_PEACH:
        captain = CHALLENGE_CAPTAIN_PEACH;
        break;
    case CHAR_ID_WARIO:
        captain = CHALLENGE_CAPTAIN_WARIO;
        break;
    case CHAR_ID_DK:
        captain = CHALLENGE_CAPTAIN_DK;
        break;
    case CHAR_ID_YOSHI:
        captain = CHALLENGE_CAPTAIN_YOSHI;
        break;
    case CHAR_ID_BOWSER:
        captain = CHALLENGE_CAPTAIN_BOWSER;
        break;
    }
    lbl_2_bss_1A8248->captain = captain;
    difficulty = Static_Stats_Tables._4711[0];
    CHALLENGE_BYTE(0x4416) = difficulty;
    lbl_2_bss_1A8248->difficulty = difficulty;
    lbl_2_bss_1A8248->captainCharID = challengeCaptainCharIDs[lbl_2_bss_1A8248->captain];
    memcpy(lbl_2_bss_1A8248->_40EE, lbl_2_data_3F98 + lbl_2_bss_1A8248->captain * 0x1FE, 0x1FE);
    memcpy(lbl_2_bss_1A8248->_440C, lbl_2_data_3F60 + lbl_2_bss_1A8248->captain * 9, 9);
    fn_2_6AE08();
    lbl_2_bss_1A8248->_16C2 = lbl_2_data_3EC8[lbl_2_bss_1A8248->captain];
    lbl_2_bss_1A8248->_16C0 = lbl_2_data_3EC8[lbl_2_bss_1A8248->captain];
    CHALLENGE_S16(0x16BE) = lbl_2_data_3EC8[lbl_2_bss_1A8248->captain];
    CHALLENGE_S16(0x1798) = -1;
    CHALLENGE_S16(0x1796) = -1;
    fn_2_90538();
    CHALLENGE_BYTE(0x4418) = lbl_2_data_2E40[0];
    CHALLENGE_BYTE(0x4419) = lbl_2_data_2E40[0];
    CHALLENGE_S16(0x43BC) = 0;
    CHALLENGE_S16(0x43BE) = 0;
    lbl_2_bss_1A8248->stage = 0;
    CHALLENGE_BYTE(0x4423) = 0;
    CHALLENGE_BYTE(0x4424) = 0;
    CHALLENGE_BYTE(0x4425) = 0;
    CHALLENGE_BYTE(0x4426) = 0;
    CHALLENGE_BYTE(0x4427) = 0;
    CHALLENGE_BYTE(0x4428) = 0;
    CHALLENGE_BYTE(0x4449) = 0;
    if (lbl_2_bss_1A8248->captain == CHALLENGE_CAPTAIN_BOWSER) {
        CHALLENGE_BYTE(0x4439) = 0;
    } else {
        CHALLENGE_BYTE(0x4439) = 1;
    }
    CHALLENGE_BYTE(0x441A) = 0;
    CHALLENGE_BYTE(0x444A) = 0;
    CHALLENGE_BYTE(0x4446) = 0;
    CHALLENGE_BYTE(0x4447) = 0;
    CHALLENGE_BYTE(0x44EF) = 0;
    CHALLENGE_BYTE(0x44F0) = 0;
    CHALLENGE_BYTE(0x44F4) = 0;
    CHALLENGE_BYTE(0x442A) = 0;
    CHALLENGE_S8(0x444C) = -1;
    CHALLENGE_S8(0x444B) = -1;
    for (i = 0; i < 20; i++) {
        lbl_2_bss_1A8248->_43C2[i] = 0;
    }
    CHALLENGE_BYTE(0x442B) = 0;
    CHALLENGE_BYTE(0x442F) = 0;
    CHALLENGE_BYTE(0x442C) = 0;
    CHALLENGE_BYTE(0x442D) = 0;
    CHALLENGE_BYTE(0x442E) = 0;
    CHALLENGE_BYTE(0x4438) = 0;
    lbl_2_bss_1A8248->resumeSavedTeams = 1;
    *(s32 *)&CHALLENGE_BYTE(0x42EC) = 0;
    CHALLENGE_BYTE(0x4431) = 0;
    CHALLENGE_BYTE(0x4432) = 0;
    CHALLENGE_BYTE(0x4433) = 0;
    CHALLENGE_BYTE(0x4434) = 0;
    CHALLENGE_BYTE(0x4435) = 0;
    fn_2_46ADC();
    fn_2_467FC();
    fn_2_45978();
    fn_2_45810();
    for (i = 0; i < 9; i++) {
        lbl_2_bss_1A8248->savedLineup[i].charID = *(s16 *)((u8 *)inMemRoster + 0x24 + i * 0xA0);
    }
    CHALLENGE_BYTE(0x44F6) = 0;
    CHALLENGE_BYTE(0x44F7) = 0;
    CHALLENGE_BYTE(0x44F8) = 3;
    CHALLENGE_BYTE(0x44F9) = 3;
    CHALLENGE_BYTE(0x44FA) = 3;
    CHALLENGE_BYTE(0x44FB) = 3;
    CHALLENGE_BYTE(0x44FC) = 3;
    CHALLENGE_BYTE(0x44FD) = 3;
    CHALLENGE_BYTE(0x44FE) = 0;
    CHALLENGE_BYTE(0x44FF) = 0;
    CHALLENGE_BYTE(0x4500) = 0;
    CHALLENGE_BYTE(0x4501) = 0;
    CHALLENGE_BYTE(0x4502) = 0;
    CHALLENGE_BYTE(0x4503) = 0;
    CHALLENGE_BYTE(0x4504) = 0;
    CHALLENGE_BYTE(0x4505) = 0;
}

// .text:0x00020328 size:0x4D4 mapped:0x8065F3BC
void fn_2_20328(void) {
    int captain = 0;
    int difficulty;
    s32 i;

    switch (Static_Stats_Tables.captainSelectedID[0]) {
    case CHAR_ID_MARIO:
        break;
    case CHAR_ID_PEACH:
        captain = CHALLENGE_CAPTAIN_PEACH;
        break;
    case CHAR_ID_WARIO:
        captain = CHALLENGE_CAPTAIN_WARIO;
        break;
    case CHAR_ID_DK:
        captain = CHALLENGE_CAPTAIN_DK;
        break;
    case CHAR_ID_YOSHI:
        captain = CHALLENGE_CAPTAIN_YOSHI;
        break;
    case CHAR_ID_BOWSER:
        captain = CHALLENGE_CAPTAIN_BOWSER;
        break;
    }
    lbl_2_bss_1A8248->captain = captain;
    difficulty = Static_Stats_Tables._4711[0];
    CHALLENGE_BYTE(0x4416) = difficulty;
    lbl_2_bss_1A8248->difficulty = difficulty;
    lbl_2_bss_1A8248->captainCharID = challengeCaptainCharIDs[lbl_2_bss_1A8248->captain];
    memcpy(lbl_2_bss_1A8248->_40EE, lbl_2_data_3F98 + lbl_2_bss_1A8248->captain * 0x1FE, 0x1FE);
    memcpy(lbl_2_bss_1A8248->_440C, lbl_2_data_3F60 + lbl_2_bss_1A8248->captain * 9, 9);
    fn_2_6AE08();
    lbl_2_bss_1A8248->_16C2 = lbl_2_data_3EC8[lbl_2_bss_1A8248->captain];
    lbl_2_bss_1A8248->_16C0 = lbl_2_data_3EC8[lbl_2_bss_1A8248->captain];
    CHALLENGE_S16(0x16BE) = lbl_2_data_3EC8[lbl_2_bss_1A8248->captain];
    CHALLENGE_S16(0x1798) = -1;
    CHALLENGE_S16(0x1796) = -1;
    fn_2_90538();
    CHALLENGE_BYTE(0x4418) = lbl_2_data_2E40[lbl_2_bss_1A8248->difficulty];
    CHALLENGE_BYTE(0x4419) = lbl_2_data_2E40[lbl_2_bss_1A8248->difficulty];
    CHALLENGE_S16(0x43BC) = 0;
    CHALLENGE_S16(0x43BE) = 0;
    lbl_2_bss_1A8248->stage = 0;
    CHALLENGE_BYTE(0x4423) = 0;
    CHALLENGE_BYTE(0x4424) = 0;
    CHALLENGE_BYTE(0x4426) = 0;
    CHALLENGE_BYTE(0x4427) = 0;
    CHALLENGE_BYTE(0x4428) = 0;
    CHALLENGE_BYTE(0x4449) = 0;
    if (lbl_2_bss_1A8248->captain == CHALLENGE_CAPTAIN_BOWSER) {
        CHALLENGE_BYTE(0x4439) = 0;
    } else {
        CHALLENGE_BYTE(0x4439) = 1;
    }
    CHALLENGE_BYTE(0x441A) = 0;
    CHALLENGE_BYTE(0x444A) = 0;
    CHALLENGE_BYTE(0x4446) = 0;
    CHALLENGE_BYTE(0x4447) = 0;
    CHALLENGE_BYTE(0x44EF) = 0;
    CHALLENGE_BYTE(0x44F0) = 0;
    CHALLENGE_BYTE(0x44F4) = 0;
    CHALLENGE_BYTE(0x442A) = 0;
    CHALLENGE_S8(0x444C) = -1;
    CHALLENGE_S8(0x444B) = -1;
    for (i = 0; i < 20; i += 5) {
        CHALLENGE_BYTE(0x43C2 + i) = CHALLENGE_BYTE(0x15F1 + i);
        CHALLENGE_BYTE(0x43C3 + i) = CHALLENGE_BYTE(0x15F2 + i);
        CHALLENGE_BYTE(0x43C4 + i) = CHALLENGE_BYTE(0x15F3 + i);
        CHALLENGE_BYTE(0x43C5 + i) = CHALLENGE_BYTE(0x15F4 + i);
        CHALLENGE_BYTE(0x43C6 + i) = CHALLENGE_BYTE(0x15F5 + i);
    }
    CHALLENGE_BYTE(0x442B) = 0;
    CHALLENGE_BYTE(0x442F) = 0;
    CHALLENGE_BYTE(0x442C) = 0;
    CHALLENGE_BYTE(0x442D) = 0;
    CHALLENGE_BYTE(0x442E) = 0;
    CHALLENGE_BYTE(0x4438) = 0;
    lbl_2_bss_1A8248->resumeSavedTeams = 1;
    *(s32 *)&CHALLENGE_BYTE(0x42EC) = 0;
    CHALLENGE_BYTE(0x4431) = 0;
    CHALLENGE_BYTE(0x4432) = 0;
    CHALLENGE_BYTE(0x4433) = 0;
    CHALLENGE_BYTE(0x4434) = 0;
    CHALLENGE_BYTE(0x4435) = 0;
    fn_2_46ADC();
    fn_2_45978();
    for (i = 0; i < 9; i++) {
        lbl_2_bss_1A8248->savedLineup[i].charID = *(s16 *)((u8 *)inMemRoster + 0x24 + i * 0xA0);
    }
    CHALLENGE_BYTE(0x44F6) = 0;
    CHALLENGE_BYTE(0x44F7) = 0;
    fn_2_42EB0();
    fn_2_432EC();
    CHALLENGE_BYTE(0x44F8) = 3;
    CHALLENGE_BYTE(0x44F9) = 3;
    CHALLENGE_BYTE(0x44FA) = 3;
    CHALLENGE_BYTE(0x44FB) = 3;
    CHALLENGE_BYTE(0x44FC) = 3;
    CHALLENGE_BYTE(0x44FD) = 3;
    CHALLENGE_BYTE(0x44FE) = 0;
    CHALLENGE_BYTE(0x44FF) = 0;
    CHALLENGE_BYTE(0x4500) = 0;
    CHALLENGE_BYTE(0x4501) = 0;
    CHALLENGE_BYTE(0x4502) = 0;
    CHALLENGE_BYTE(0x4503) = 0;
    CHALLENGE_BYTE(0x4504) = 0;
    CHALLENGE_BYTE(0x4505) = 0;
}

// .text:0x0002025C size:0xCC mapped:0x8065F2F0
void fn_2_2025C(void) {
    ChallengeState *challenge = lbl_2_bss_1A8248;
    if (challenge->_44F2 == 2) {
        hugeAnimStruct.unk307A = 0;
    } else if (lbl_2_bss_1A824C[0x190000 + 0x78F3] != 0) {
        hugeAnimStruct.unk307A = 4;
    }
    if (hugeAnimStruct.unk307A == 4 && challenge->_44F2 != 3) {
        if (challenge->_44F2 != 4) {
            fn_2_68E68();
        }
        fn_2_8FD14();
        fn_2_8AEE0();
        fn_2_47FF8();
        if (lbl_2_bss_1A8248->_44F2 != 4) {
            fn_2_47CFC();
        }
    }
    GXSetZCompLoc(FALSE);
}

// .text:0x00020258 size:0x4 mapped:0x8065F2EC
void fn_2_20258(void) {
    return;
}

// .text:0x00020218 size:0x40 mapped:0x8065F2AC
void fn_2_20218(void) {
    lbl_2_bss_1A824C[0x190000 + 0x782B] = 0;
    lbl_2_bss_1A824C[0x190000 + 0x782C] = 0;
    lbl_2_bss_1A824C[0x190000 + 0x782A] = 0;
    lbl_2_bss_1A824C[0x190000 + 0x7832] = 0;
}

#pragma dont_inline on
// .text:0x000201E4 size:0x34 mapped:0x8065F278
int fn_2_201E4(s16 row, s16 col) {
    if (col < 0) {
        return -1;
    }
    return lbl_2_data_3D30[row][col];
}

#pragma dont_inline reset

// .text:0x000200E4 size:0x100 mapped:0x8065F178
BOOL fn_2_200E4(void) {
    u8 *entry;
    s16 *base;
    int level;
    base = (s16 *)lbl_2_bss_1A8248;
    entry = (u8 *)base + base[0x16C0 / 2] * 10;

    if (entry[0x40F6] == 1) {
        return FALSE;
    }
    if (entry[0x40F0] == 5) {
        return FALSE;
    }
    level = ((u8 *)base)[0x442B];
    if (level > 3) {
        level = 3;
    }
    if (lbl_2_data_2E44[lbl_2_bss_1A8248->difficulty][level] >= rand() % 100 &&
        lbl_2_bss_1A8248->captain != 5) {
        if (lbl_2_bss_1A8248->stage == 0) {
            return FALSE;
        }
        if (((u8 *)lbl_2_bss_1A8248)[0x442B] < 3) {
            ((u8 *)lbl_2_bss_1A8248)[0x442B]++;
        }
        return TRUE;
    }
    return FALSE;
}

#pragma dont_inline on
// .text:0x00020074 size:0x70 mapped:0x8065F108
int fn_2_20074(void) {
    s8 port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    u16 value = *(u16 *)((u8 *)&AtBat_ButtonInput1 + port * 32);
    int dir;
    if (value & INPUT_BUTTON_UP) {
        dir = 0;
    } else if (value & INPUT_BUTTON_DOWN) {
        dir = 1;
    } else if (value & INPUT_BUTTON_LEFT) {
        dir = 2;
    } else if (value & INPUT_BUTTON_RIGHT) {
        dir = 3;
    } else {
        dir = -1;
    }
    return dir;
}
#pragma dont_inline reset

// .text:0x0001FFC4 size:0xB0 mapped:0x8065F058
void fn_2_1FFC4(s32 arg0) {
    u8 *base = (u8 *)&AtBat_ButtonInput1 + 4;
    s8 port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    u16 value = *(u16 *)(base + port * 32);
    if (value & 8) {
        (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0])--;
        if (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0] < 0) {
            *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0] = arg0 - 1;
        }
    }
    port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    value = *(u16 *)(base + port * 32);
    if (!(value & 4)) {
        return;
    }
    (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0])++;
    if (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0] < arg0) {
        return;
    }
    *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A0] = 0;
}

// .text:0x0001FF14 size:0xB0 mapped:0x8065EFA8
void fn_2_1FF14(s32 arg0) {
    u8 *base = (u8 *)&AtBat_ButtonInput1 + 4;
    s8 port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    u16 value = *(u16 *)(base + port * 32);
    if (value & 8) {
        (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4])--;
        if (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4] < 0) {
            *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4] = arg0 - 1;
        }
    }
    port = lbl_2_bss_1A824C[0x190000 + 0x7863];
    value = *(u16 *)(base + port * 32);
    if (!(value & 4)) {
        return;
    }
    (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4])++;
    if (*(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4] < arg0) {
        return;
    }
    *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A4] = 0;
}

// .text:0x0001FF10 size:0x4 mapped:0x8065EFA4
void fn_2_1FF10(void) {
    return;
}

// .text:0x0001FF0C size:0x4 mapped:0x8065EFA0
void fn_2_1FF0C(void) {
    return;
}

#define MENU_NAV(field, count)                                          \
    {                                                                   \
        u8 *base = (u8 *)&AtBat_ButtonInput1 + 4;                       \
        if (*(u16 *)(base + PAD_PORT * 32) & INPUT_BUTTON_UP) {         \
            WORK_S32(field)--;                                          \
            if (WORK_S32(field) < 0) {                                  \
                WORK_S32(field) = (count) - 1;                          \
            }                                                           \
        }                                                               \
        if (*(u16 *)(base + PAD_PORT * 32) & INPUT_BUTTON_DOWN) {       \
            WORK_S32(field)++;                                          \
            if (WORK_S32(field) >= (count)) {                           \
                WORK_S32(field) = 0;                                    \
            }                                                           \
        }                                                               \
    }

#define CYCLE_PAD(field, count)                                         \
    {                                                                   \
        u16 pad = PAD_NEW();                                            \
        if (pad & INPUT_BUTTON_LEFT) {                                  \
            (field) = ((field) + (count) - 1) % (count);                \
        } else if (pad & INPUT_BUTTON_RIGHT) {                          \
            (field) = ((field) + 1) % (count);                          \
        }                                                               \
    }

#define RESET_RECORDS(type, flagOffset, bit)                                                   \
    for (k = 0; k < 0x33; k++) {                                                               \
        if ((s32)CHALLENGE_BYTE(k * 10 + 0x40F0) == (s32)(type)) {                              \
            if (CHALLENGE_BYTE(k * 10 + 0x40F1) == 1 || CHALLENGE_BYTE(k * 10 + 0x40F1) == 0) { \
                if (lbl_2_bss_1A8248->captain == 5) {                                          \
                    if (CHALLENGE_BYTE(k * 10 + 0x40F2) == 1) {                                \
                        CHALLENGE_BYTE(k * 10 + 0x40F1) = 3;                                   \
                    } else {                                                                   \
                        CHALLENGE_BYTE(k * 10 + 0x40F1) = 0;                                   \
                    }                                                                          \
                } else {                                                                       \
                    CHALLENGE_BYTE(k * 10 + 0x40F1) = 0;                                       \
                }                                                                              \
            }                                                                                  \
        }                                                                                      \
    }                                                                                          \
    CHALLENGE_BYTE(flagOffset) = 1;                                                            \
    if (!(CHALLENGE_BYTE(0x4428) & (bit))) {                                                   \
        CHALLENGE_BYTE(0x4423)++;                                                              \
        CHALLENGE_BYTE(0x4428) |= (bit);                                                       \
    }

// .text:0x0001D440 size:0x2ACC mapped:0x8065C4D4
void fn_2_1D440(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    int i;
    s32 j;
    int k;
    switch (ITEM_STATE) {
    case 0:
        WORK_S32(0x76A4) = 0;
        WORK_S32(0x76A0) = 0;
        ITEM_STATE = 1;
        break;
    case 1:
        MENU_NAV(0x76A0, 0x13)
        for (i = 0; i < 0x13; i++) {
            switch (i) {
            case 0:
                if (WORK_S32(0x76A0) == i) {
                    if ((PAD_NEW() & INPUT_BUTTON_A) || PAD_STICK_Y() > 0x32) {
                        ITEM_STATE = 13;
                    }
                }
                break;
            case 1:
                if (WORK_S32(0x76A0) == i) {
                    u16 held = PAD_HELD();
                    if (held & INPUT_BUTTON_LEFT) {
                        if (CHALLENGE_S16(0x43BC) > 0) {
                            fn_80062890(0x37);
                            fn_2_46D34(-1);
                        } else {
                            fn_80062890(0x37);
                            CHALLENGE_S16(0x43BC) = 999;
                        }
                        lbl_2_bss_1A8234[0x160000 + 0x2933] = 1;
                    } else if (held & INPUT_BUTTON_RIGHT) {
                        if (CHALLENGE_S16(0x43BC) < 999) {
                            fn_80062890(0x37);
                            fn_2_46D34(1);
                        } else {
                            fn_80062890(0x37);
                            CHALLENGE_S16(0x43BC) = 0;
                        }
                        lbl_2_bss_1A8234[0x160000 + 0x2979] = 1;
                    } else if (held & INPUT_TRIGGER_L) {
                        fn_80062890(0x37);
                        CHALLENGE_S16(0x43BC) = 0;
                    } else if (held & INPUT_TRIGGER_R) {
                        fn_80062890(0x37);
                        CHALLENGE_S16(0x43BC) = 999;
                    }
                }
                break;
            case 2:
                if (WORK_S32(0x76A0) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT)) {
                        lbl_2_bss_1A8248->_44F2 ^= 1;
                    }
                }
                break;
            case 3:
                if (WORK_S32(0x76A0) == i) {
                    u16 held = PAD_HELD();
                    if (held & INPUT_BUTTON_LEFT) {
                        if (WORK_S16(0x779C) > 0) {
                            WORK_S16(0x779C)--;
                        } else {
                            WORK_S16(0x779C) = 999;
                        }
                    } else if (held & INPUT_BUTTON_RIGHT) {
                        if (WORK_S16(0x779C) < 999) {
                            WORK_S16(0x779C) = WORK_S16(0x779C) + 1;
                        } else {
                            WORK_S16(0x779C) = 0;
                        }
                    } else if (held & INPUT_TRIGGER_L) {
                        WORK_S16(0x779C) = 0;
                    } else if (held & INPUT_TRIGGER_R) {
                        WORK_S16(0x779C) = 999;
                    }
                    if (PAD_HELD() & INPUT_BUTTON_A) {
                        if (WORK_S16(0x773E) == 0) {
                            DrawingSceneStruct *child;
                            fn_2_46D34(WORK_S16(0x779C));
                            child = insertGraphicDrawingFunction(fn_2_3FA14, 2);
                            *(s8 *)((u8 *)child + 0x28) = 0;
                            item->state = 0;
                            WORK_S16(0x773E) = 1;
                        }
                    }
                }
                break;
            case 4:
                if (WORK_S32(0x76A0) == i) {
                    u16 held = PAD_HELD();
                    if (held & INPUT_BUTTON_LEFT) {
                        if (WORK_S16(0x779C) > 0) {
                            WORK_S16(0x779C)--;
                        } else {
                            WORK_S16(0x779C) = 999;
                        }
                    } else if (held & INPUT_BUTTON_RIGHT) {
                        if (WORK_S16(0x779C) < 999) {
                            WORK_S16(0x779E) = WORK_S16(0x779E) + 1;
                        } else {
                            WORK_S16(0x779E) = 0;
                        }
                    } else if (held & INPUT_TRIGGER_L) {
                        WORK_S16(0x779E) = 0;
                    } else if (held & INPUT_TRIGGER_R) {
                        WORK_S16(0x779E) = 999;
                    }
                    if (PAD_HELD() & INPUT_BUTTON_A) {
                        if (WORK_S16(0x773E) == 0) {
                            fn_2_46D34(-WORK_S16(0x779E));
                            if (CHALLENGE_S16(0x43BE) > 0) {
                                DrawingSceneStruct *child = insertGraphicDrawingFunction(fn_2_3F66C, 2);
                                *(s8 *)((u8 *)child + 0x28) = 0;
                                item->state = 0;
                            }
                            WORK_S16(0x773E) = 1;
                        }
                    }
                }
                break;
            case 5:
                if (WORK_S32(0x76A0) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        ITEM_STATE = 2;
                    }
                }
                break;
            case 6:
                if (WORK_S32(0x76A0) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        ITEM_STATE = 3;
                    }
                }
                break;
            case 7:
                if (WORK_S32(0x76A0) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        WORK_U8(0x784A) = 1;
                        WORK_U8(0x7846) = 1;
                        WORK_U8(0x7847) = 0;
                        ITEM_STATE = 4;
                    }
                }
                break;
            case 8:
                if (WORK_S32(0x76A0) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        WORK_U8(0x784A) = 1;
                        WORK_U8(0x7846) = 0;
                        WORK_U8(0x7845) = 1;
                        ITEM_STATE = 5;
                    }
                }
                break;
            case 9:
                if (WORK_S32(0x76A0) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        WORK_U8(0x784A) = 1;
                        WORK_U8(0x7846) = 2;
                        ITEM_STATE = 6;
                    }
                }
                break;
            case 10:
                if (WORK_S32(0x76A0) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        ITEM_STATE = 7;
                    }
                }
                break;
            case 11:
                if (WORK_S32(0x76A0) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT)) {
                        CHALLENGE_BYTE(0x441A) = 1;
                        CHALLENGE_BYTE(0x4439) = 0;
                        CHALLENGE_S16(0x16C2) = lbl_2_data_3EC8[5];
                        fn_2_6ABFC(0, CHALLENGE_S16(0x16C2));
                        for (j = 0; j < 5; j++) {
                            fn_2_1C714(j);
                        }
                    }
                }
                break;
            case 12:
                if (WORK_S32(0x76A0) == i) {
                    u16 pad = PAD_NEW();
                    if (pad & INPUT_BUTTON_LEFT) {
                        lbl_2_bss_1A8248->difficulty = (lbl_2_bss_1A8248->difficulty + 3) % 4;
                    } else if (pad & INPUT_BUTTON_RIGHT) {
                        lbl_2_bss_1A8248->difficulty = (lbl_2_bss_1A8248->difficulty + 1) % 4;
                    }
                }
                break;
            case 13:
                if (WORK_S32(0x76A0) == i) {
                    u16 pad = PAD_NEW();
                    if (pad & (INPUT_BUTTON_A | INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT)) {
                        fn_2_683EC();
                    } else if (pad & INPUT_BUTTON_X) {
                        fn_2_68308();
                    } else if (pad & INPUT_BUTTON_Y) {
                        fn_2_6832C();
                    }
                }
                break;
            case 14:
                if (WORK_S32(0x76A0) == i) {
                    u16 held = PAD_HELD();
                    if (held & INPUT_BUTTON_Y) {
                        WORK_U8(0x785C) = ((s8)WORK_U8(0x785C) + 1) % 2;
                    } else if (held & INPUT_BUTTON_X) {
                        WORK_U8(0x785C) = ((s8)WORK_U8(0x785C) + 1) % 2;
                    }
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        Vec zero;
                        zero.z = 0.0f;
                        zero.y = 0.0f;
                        zero.x = 0.0f;
                        fn_2_46C2C(0, &zero);
                    }
                }
                break;
            case 15:
                if (WORK_S32(0x76A0) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        ITEM_STATE = 9;
                    }
                }
                break;
            case 16:
                if (WORK_S32(0x76A0) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        ITEM_STATE = 11;
                    }
                }
                break;
            case 17:
                if (WORK_S32(0x76A0) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        for (j = 0; j < 0x14; j++) {
                            lbl_2_bss_1A8248->_43C2[j] = 1;
                        }
                    }
                }
                break;
            case 18:
                if (WORK_S32(0x76A0) == i) {
                    u16 pad = PAD_NEW();
                    if (pad & INPUT_BUTTON_LEFT) {
                        for (j = 0; j < 6; j++) {
                            CHALLENGE_BYTE(0x44F8 + j) = 0;
                        }
                    } else if (pad & INPUT_BUTTON_RIGHT) {
                        for (j = 0; j < 6; j++) {
                            CHALLENGE_BYTE(0x44F8 + j) = 3;
                        }
                    }
                }
                break;
            }
        }
        if ((PAD_NEW2() & INPUT_BUTTON_B) || PAD_STICK_Y() > 0x32) {
            ITEM_STATE = 13;
        }
        break;
    case 2:
        MENU_NAV(0x76A4, 7)
        for (i = 0; i < 7; i++) {
            switch (i) {
            case 0:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_B)) {
                        WORK_S32(0x76A4) = 0;
                        ITEM_STATE = 1;
                    }
                }
                break;
            case 1:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        fn_2_1C714(0);
                    }
                }
                break;
            case 2:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        fn_2_1C714(1);
                    }
                }
                break;
            case 3:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        fn_2_1C714(2);
                    }
                }
                break;
            case 4:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        fn_2_1C714(3);
                    }
                }
                break;
            case 5:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        fn_2_1C714(4);
                    }
                }
                break;
            case 6:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        fn_2_1C714(5);
                    }
                }
                break;
            }
        }
        if (PAD_NEW2() & (INPUT_BUTTON_B | INPUT_BUTTON_LEFT)) {
            WORK_S32(0x76A4) = 0;
            ITEM_STATE = 1;
        } else if (PAD_STICK_Y() > 0x32) {
            ITEM_STATE = 13;
        }
        break;
    case 3:
        MENU_NAV(0x76A4, 6)
        for (i = 0; i < 6; i++) {
            switch (i) {
            case 0:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_B)) {
                        WORK_S32(0x76A4) = 0;
                        ITEM_STATE = 1;
                    }
                }
                break;
            case 1:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        RESET_RECORDS(0, 0x440C, 0x1)
                    }
                }
                break;
            case 2:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        RESET_RECORDS(1, 0x440D, 0x2)
                    }
                }
                break;
            case 3:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        RESET_RECORDS(2, 0x440E, 0x4)
                    }
                }
                break;
            case 4:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        RESET_RECORDS(3, 0x440F, 0x8)
                    }
                }
                break;
            case 5:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        RESET_RECORDS(4, 0x4410, 0x10)
                    }
                }
                break;
            }
        }
        if (PAD_NEW2() & (INPUT_TRIGGER_L | INPUT_TRIGGER_R)) {
            RESET_RECORDS(0, 0x440C, 0x1)
            RESET_RECORDS(1, 0x440D, 0x2)
            RESET_RECORDS(2, 0x440E, 0x4)
            RESET_RECORDS(3, 0x440F, 0x8)
            RESET_RECORDS(4, 0x4410, 0x10)
        }
        if (PAD_NEW2() & (INPUT_BUTTON_B | INPUT_BUTTON_LEFT)) {
            WORK_S32(0x76A4) = 0;
            ITEM_STATE = 1;
        } else if (PAD_STICK_Y() > 0x32) {
            ITEM_STATE = 13;
        }
        break;
    case 4:
        MENU_NAV(0x76A4, 1)
        for (i = 0; i < 1; i++) {
            switch (i) {
            case 0:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & INPUT_TRIGGER_Z) {
                        WORK_U8(0x7847) ^= 1;
                    }
                    if (PAD_NEW() & INPUT_BUTTON_B) {
                        WORK_U8(0x784A) = 0;
                        WORK_U8(0x7846) = 0;
                        WORK_S32(0x76A4) = 0;
                        WORK_U8(0x7847) = 0;
                        fn_2_6ABFC(0, CHALLENGE_S16(0x16C2));
                        ITEM_STATE = 1;
                    }
                    if (PAD_NEW() & INPUT_BUTTON_A) {
                        Vec unused;
                        fn_2_68DAC(0, &unused);
                        WORK_S16(0x779A) = WORK_S16(0x779A) + 1;
                    }
                    if (PAD_NEW() & INPUT_BUTTON_START) {
                        WORK_S16(0x779A) = 0;
                    }
                }
                break;
            }
        }
        break;
    case 5:
        MENU_NAV(0x76A4, 1)
        for (i = 0; i < 1; i++) {
            switch (i) {
            case 0:
                if (WORK_S32(0x76A4) == i) {
                    u16 pad = PAD_NEW();
                    if ((pad & INPUT_BUTTON_LEFT) && (PAD_RAW() & INPUT_BUTTON_A)) {
                        WORK_U8(0x7849) = (WORK_U8(0x7849) + 0x13) % 0x14;
                    } else if ((pad & INPUT_BUTTON_RIGHT) && (PAD_RAW() & INPUT_BUTTON_A)) {
                        WORK_U8(0x7849) = (WORK_U8(0x7849) + 1) % 0x14;
                    }
                    pad = PAD_NEW();
                    if (pad & INPUT_BUTTON_B) {
                        WORK_U8(0x784A) = 0;
                        WORK_U8(0x7846) = 0;
                        WORK_S32(0x76A4) = 0;
                        WORK_U8(0x7845) = 0;
                        ITEM_STATE = 1;
                    } else if (pad & INPUT_BUTTON_START) {
                        menuCamera_snapToPreset();
                    }
                }
                break;
            }
        }
        break;
    case 6:
        MENU_NAV(0x76A4, 1)
        for (i = 0; i < 1; i++) {
            switch (i) {
            case 0:
                if (WORK_S32(0x76A4) == i) {
                    u8 *pad = PAD_PTR();
                    u16 pressed = *(u16 *)(pad + 2);
                    if (pressed & INPUT_BUTTON_B) {
                        WORK_U8(0x784A) = 0;
                        WORK_U8(0x7846) = 0;
                        WORK_S32(0x76A4) = 0;
                        fn_2_6ABFC(0, CHALLENGE_S16(0x16C2));
                        ITEM_STATE = 1;
                    } else if ((pressed & INPUT_TRIGGER_L) && (*(u16 *)pad & INPUT_BUTTON_A)) {
                        WORK_S16(0x72BE) = (WORK_S16(0x72BE) + 0x1C) % 0x1D;
                    } else if ((pressed & INPUT_TRIGGER_R) && (*(u16 *)pad & INPUT_BUTTON_A)) {
                        WORK_S16(0x72BE) = (WORK_S16(0x72BE) + 1) % 0x1D;
                    } else if (*(u16 *)(pad + 4) & INPUT_BUTTON_Y) {
                        *(f32 *)((u8 *)lbl_2_bss_1A8248 + WORK_S16(0x72BE) * 0xBC + 0x2208) -= 0.1f;
                    } else if (*(u16 *)(pad + 4) & INPUT_BUTTON_X) {
                        *(f32 *)((u8 *)lbl_2_bss_1A8248 + WORK_S16(0x72BE) * 0xBC + 0x2208) += 0.1f;
                    }
                }
                break;
            }
        }
        break;
    case 7:
        MENU_NAV(0x76A4, 12)
        for (i = 0; i < 12; i++) {
            switch (i) {
            case 0:
                if (WORK_S32(0x76A4) == i) {
                    if (PAD_NEW() & (INPUT_BUTTON_A | INPUT_BUTTON_B | INPUT_BUTTON_LEFT)) {
                        ITEM_STATE = 1;
                    }
                }
                break;
            case 1:
                if (WORK_S32(0x76A4) == i) {
                    CYCLE_PAD(CHALLENGE_S8(0x443B), 4)
                }
                break;
            case 2:
                if (WORK_S32(0x76A4) == i) {
                    CYCLE_PAD(CHALLENGE_S8(0x443C), 2)
                }
                break;
            case 3:
                if (WORK_S32(0x76A4) == i) {
                    CYCLE_PAD(CHALLENGE_S8(0x443D), 4)
                }
                break;
            case 4:
                if (WORK_S32(0x76A4) == i) {
                    CYCLE_PAD(CHALLENGE_S8(0x443E), 2)
                }
                break;
            case 5:
                if (WORK_S32(0x76A4) == i) {
                    CYCLE_PAD(CHALLENGE_S8(0x443F), 3)
                }
                break;
            case 6:
                if (WORK_S32(0x76A4) == i) {
                    CYCLE_PAD(CHALLENGE_S8(0x4437), 4)
                }
                break;
            case 7:
                if (WORK_S32(0x76A4) == i) {
                    CYCLE_PAD(CHALLENGE_S8(0x4440), 4)
                }
                break;
            case 8:
                if (WORK_S32(0x76A4) == i) {
                    CYCLE_PAD(CHALLENGE_S8(0x4441), 2)
                }
                break;
            case 9:
                if (WORK_S32(0x76A4) == i) {
                    CYCLE_PAD(CHALLENGE_S8(0x4442), 4)
                }
                break;
            case 10:
                if (WORK_S32(0x76A4) == i) {
                    CYCLE_PAD(CHALLENGE_S8(0x4443), 2)
                }
                break;
            case 11:
                if (WORK_S32(0x76A4) == i) {
                    CYCLE_PAD(CHALLENGE_BYTE(0x443A), 4)
                }
                break;
            }
        }
        if (PAD_NEW2() & (INPUT_BUTTON_A | INPUT_BUTTON_B)) {
            WORK_S32(0x76A4) = 0;
            ITEM_STATE = 1;
        } else if (PAD_STICK_Y() > 0x32) {
            ITEM_STATE = 13;
        }
        break;
    case 8:
        break;
    case 9: {
        DrawingSceneStruct *child = insertGraphicDrawingFunction(fn_2_1CF94, 2);
        *(s8 *)((u8 *)child + 0x28) = 0;
        item->state = 0;
        ITEM_STATE = 10;
        break;
    }
    case 10:
        if (item->state == 1) {
            ITEM_STATE = 1;
        }
        break;
    case 11: {
        DrawingSceneStruct *child = insertGraphicDrawingFunction(fn_2_1C860, 2);
        *(s8 *)((u8 *)child + 0x28) = 0;
        item->state = 0;
        ITEM_STATE = 12;
        break;
    }
    case 12:
        if (item->state == 1) {
            ITEM_STATE = 1;
        }
        break;
    case 13:
        item->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        ITEM_STATE = 0;
        break;
    }
}
