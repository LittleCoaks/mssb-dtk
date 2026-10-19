#include "Unknown/File_0x80009180.h"
#include "Unknown/File_0x80008fd0.h"
#include "Unknown/graphic.h"

extern void fn_800BEC30(s32 a);
extern void somethingSetTexturePointer(void);
extern void fn_800A7AD8(void);
extern void initializeDVDSystem(void);
extern void fn_800A6870(s32 a, s32 b);
extern void StartThreadForReadingFromDisk(void);
extern void f_initSound(void);
extern void initInputDevices(void);
extern void resetAllDrawingStructs_tonop(void);
extern void fn_80021AA0(void);
extern void fn_80036A3C(void);
extern void fn_800356B8(void);
extern void VIFlush(void);
extern void VIWaitForRetrace(void);
extern u32 OSGetResetCode(void);
extern s32 OSGetResetButtonState(void);
extern void minigamesSetSomePointers2(void);
extern void fn_8003A2EC(void);
extern void fn_8004B270(void);
extern void fn_80052188(void);
extern void fn_80064534(void);
extern s32 OSWaitSemaphore(void *sem);
extern void *GXSetCurrentGXThread(void);
extern void GXFlush(void);
extern void GXSetDrawSync(u16 token);
extern u16 GXReadDrawSync(void);
extern void fn_800A7BAC(s32 a);
extern void fn_8001F16C(void);
extern void fn_8001AF98(void);
extern void fn_8001E784(void);
extern void fn_800A9520(void);
extern s32 fn_80021188(void (*fn)(void));
extern s32 fn_800211BC(void (*fn)(void));
extern void fn_80008E08(void);
extern u32 fn_800AD490(void *p);
extern void fn_800AD914(void *p);
extern void fn_800AD95C(void *p, u8 b);
extern void fn_8000F3E8(s32 a);
extern void RunDrawScripts_with_stack_variables(void);
extern void fn_800B251C(void);
extern void fn_8003A090(void);
extern u8 GetDrawShadows(void);
extern void DrawShadows(u8 enable);
extern void fn_800A7DB0(void);
extern s32 fn_80023D3C(void);
extern void DVDDumpWaitingQueue(void);
extern s32 rand(void);
extern void AIRegisterStreamCallback(s32 cb);
extern void AIResetStreamSampleCount(void);
extern void AISetStreamPlayState(u32 state);
extern void soundQuit(void);
extern void fn_800A94C4(void);
extern void PADControlMotor(s32 chan, u32 command);
extern void OSResetSystem(s32 reset, u32 code, s32 doForceMenu);
extern s32 DVDCheckDisk(void);

extern u8 drawStadiumRelated;
extern u8 AtBat_ButtonInput1[0x80];
extern u8 lbl_801181A0[0x80];
extern u8 lbl_803C7420[0x398];
extern u8 lbl_803C6CF8[0x708];
extern u8 lbl_80366158[0x30];
extern u8 lbl_803CBBC1;
extern u8 lbl_803CBBC2;
extern u8 lbl_803CBBA4;
extern u8 lbl_803CBBB4;
extern s32 lbl_803CBBA0;
extern s32 lbl_803CBBA8;
extern s32 lbl_803CBBAC;
extern s32 lbl_803CBBB0;
extern void *lbl_803CBBBC;
extern void (*lbl_803CBBB8)(void);
extern u32 lbl_803CD300;

void main(void) {
    u32 mode = 0;
    s32 ret;
    s32 done;
    s32 v;
    u16 token;
    u8 cur;

    initRenderMode(NULL, 0x40000, 0x10);
    fn_800BEC30(1);
    somethingSetTexturePointer();
    fn_800A7AD8();
    initializeDVDSystem();
    fn_800A6870(1, 0x438);
    StartThreadForReadingFromDisk();
    f_initSound();
    initInputDevices();
    resetAllDrawingStructs_tonop();
    fn_800A7D7C((DrawCallbackNode *)(lbl_801181A0 + (drawStadiumRelated << 6)), 0x10);
    fn_80021AA0();
    DrawShadows(0);
    fn_80036A3C();
    fn_800356B8();
    lbl_803CBBC2 = 0;
    lbl_803CBBC1 = 0;
    VISetPostRetraceCallback(PostRetraceCallback);
    lbl_80366158[0x20] = 0;
    lbl_80366158[0x23] = 0;
    lbl_80366158[0x21] = 0;
    *(u32 *)(lbl_80366158 + 0xC) = OSGetResetCode();
    minigamesSetSomePointers2();
    fn_8003A2EC();
    fn_8004B270();
    lbl_80366158[0x28] = 0;
    fn_80052188();
    fn_80064534();

    do {
        if (mode == 0) {
            fn_8001F16C();
            fn_8001AF98();
        }
        fn_800A7BAC(1);
        OSWaitSemaphore(lbl_803C7420 + 0x388);
        GXSetCurrentGXThread();
        if (mode == 0) {
            fn_8001E784();
        }
        fn_800A7BAC(0);
        drawStadiumRelated ^= 1;
        fn_800A9520();
        fn_800A7D7C((DrawCallbackNode *)(lbl_801181A0 + (drawStadiumRelated << 6)), 0x10);

        v = (s8)lbl_803C6CF8[0x722];
        if (v == 0) {
            lbl_803CBBA4 = 0;
        } else if (v == -1 || v == 4 || v == 5 || v == 6 || v == 11) {
            lbl_803CBBA0 = v;
            lbl_803CBBA4 = 1;
        }

        cur = lbl_803CBBA4;
        if (mode != cur) {
            if (cur == 0) {
                ret = fn_80021188(fn_80008E08);
                lbl_803CBBA8 = 0;
            } else {
                ret = fn_800211BC(fn_80008E08);
                lbl_803CBBA8 = 1;
            }
            if (ret != 0) {
                break;
            }
        }
        mode = cur;

        if (lbl_803CBBBC != NULL) {
            ret = fn_800AD490(lbl_803CBBBC);
            if (cur == 0) {
                if (fn_800AD490(lbl_803CBBBC) == 2) {
                    fn_800AD95C(lbl_803CBBBC, ((u8 *)lbl_803CBBBC)[0x1B9]);
                }
            } else if (ret == 1 || (ret & 0x80000000) != 0) {
                fn_800AD914(lbl_803CBBBC);
            }
        }

        if (cur != 0) {
            fn_8000F3E8(lbl_803CBBA0);
        } else {
            RunDrawScripts_with_stack_variables();
            fn_800B251C();
        }

        OSWaitSemaphore(lbl_803C7420 + 0x388);
        GXSetCurrentGXThread();
        fn_8003A090();
        while (*(volatile u8 *)(lbl_803C7420 + 0x396) != 0) {
        }
        GXSetCurrentGXThread();
        GXFlush();
        if (GetDrawShadows() != 0) {
            GXColor clear = *(GXColor *)&lbl_803CD300;
            GXSetCopyClear(clear, 0x00FFFFFF);
        }

        fn_800A7DB0();
        if (lbl_803CBBB8 != NULL) {
            VISetBlack(1);
            VIFlush();
            VIWaitForRetrace();
            fn_80023D3C();
            lbl_803CBBB8();
            VISetBlack(0);
            VIFlush();
            VIWaitForRetrace();
        }

        v = lbl_803CBBAC;
        lbl_803CBBB8 = NULL;
        if (v != 0) {
            if ((*(u16 *)AtBat_ButtonInput1 & 0x1600) == 0x1600) {
                if (lbl_80366158[0x20] != 0 && lbl_80366158[0x23] != 0) {
                    lbl_803CBBB4 = 0;
                    lbl_803CBBB0 = lbl_803CBBB0 + 1;
                }
            } else {
                if (lbl_80366158[0x20] == 0 || lbl_80366158[0x23] == 0) {
                    if (lbl_803CBBB4 >= 5) {
                        lbl_80366158[0x23] = 1;
                    }
                }
                lbl_803CBBB0 = 0;
                lbl_803CBBB4 = lbl_803CBBB4 + 1;
            }
            if ((u32)lbl_803CBBB0 >= 0x1E) {
                lbl_803CBBC1 = 1;
            }
        }

        done = 0;
        if (lbl_80366158[0x21] != 0) {
            done = 1;
        } else if (lbl_803CBBC2 != 0 || lbl_803CBBC1 != 0) {
            if (OSGetResetButtonState() == 0 &&
                !(cur != 0 && (s8)lbl_803C6CF8[0x722] == -1)) {
                done = lbl_80366158[0x20] != 0;
            }
        }
    } while (done == 0);

    DVDDumpWaitingQueue();
    GXSetCurrentGXThread();
    token = (u16)rand();
    GXSetDrawSync(token);
    GXFlush();
    while (GXReadDrawSync() != token) {
    }
    AIRegisterStreamCallback(0);
    AIResetStreamSampleCount();
    AISetStreamPlayState(0);
    soundQuit();
    VISetBlack(1);
    VIFlush();
    VIWaitForRetrace();
    fn_800A94C4();

    if (lbl_80366158[0x21] != 0) {
        PADControlMotor(0, 2);
        PADControlMotor(1, 2);
        PADControlMotor(2, 2);
        PADControlMotor(3, 2);
        OSResetSystem(1, 0, 1);
    } else {
        mode = 0;
        if (DVDCheckDisk() != 0 && lbl_803CBBA8 == 0) {
            mode = 1;
        }
        mode = (mode == 0);
        PADControlMotor(0, 2);
        PADControlMotor(1, 2);
        PADControlMotor(2, 2);
        PADControlMotor(3, 2);
        ret = fn_80023D3C();
        OSResetSystem(mode, ((ret != 0) ? 2 : 0) | 1, 0);
    }
}
