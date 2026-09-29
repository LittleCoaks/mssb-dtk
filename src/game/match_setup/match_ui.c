#define SQRT2_LINKAGE static
#include "game/match_setup/match_ui.h"
#include "game/match_setup/loading_state.h"
#include "game/match_setup/match_flow.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "text/text_channel.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80035838.h"
#include "Unknown/File_0x800a70dc.h"

typedef struct {
    /* 0x000 */ u8 _000[0xC];
    /* 0x00C */ void* _00C;
    /* 0x010 */ u8 _010[0x242];
    /* 0x252 */ s8 charID;
    /* 0x253 */ u8 _253[0x29];
} HugeAnimPlayer; // size: 0x27C

extern struct {
    u8 _0000[0xC04];
    HugeAnimPlayer players[4];
    u8 _15F4[0x2D7D - 0x15F4];
    u8 _2D7D;
    u8 _2D7E[0x3154 - 0x2D7E];
} hugeAnimStruct;

extern struct {
    u8 _00[4];
    u8 step;
    u8 _05[7];
} g_UnkSimulation_31AC0;

extern u8 animRelated[0x124];
extern u8 lbl_8037169C[0x1C];
extern s8 lbl_803C6CF8[0x708];
extern u8 lbl_3_common_bss_35154[0x480];
extern u8 FrameCountOfEntireGame[0x14];
extern u8 audioFileDescriptors[0x39C];
extern MatchFileDescriptor CharacterFiles[];

extern void fn_80017D28(int);
extern int fn_80022B68(void);
extern void fn_80022CB4(void* file, u32 arg1, int arg2, int arg3, void (*callback)(), void* arg5);
extern void fn_8001AAA4(void);
extern void fn_3_6AEC0(void);
extern void fn_800216F8(int id, void (*callback)(void));
extern void fn_3_90764(void);
extern void fn_3_90798(void);
extern void fn_3_90F48(void);
extern void fn_3_910AC(void);
extern void fn_3_91064(void);
extern void fn_3_906FC(void);
extern int fn_3_90928(void);
extern void stadiumSetupRelated(void);
extern void practice_loadCharacterData(void);
extern void fn_8001A3FC(int);
extern void fn_80019A60(void);
extern void fn_8001A25C(void);
extern int fn_3_1665E4(void);
extern void loadSomeDataFile(void);
extern void someAllocFunction(void);
extern int maybeLoadHUDObjectFromMemory(void);
extern int fn_3_11D6A0(void);
extern void fn_800111B4(TextBank* bank);
extern int calledWhenStartingMatch(void);
extern int fn_80020218(void);
extern int fn_80020278(int);
extern int findCharacterID(s16);
extern int fn_80069B68(void);

MatchFileDescriptor sequencedSongsFileDescriptor[1] = { { 0x0000040B, 0x400098A0, 0x0773D800, 0x00003C88 } };

MatchFileDescriptor lbl_3_data_3D70 = { 0x0000040B, 0x40000970, 0x07741800, 0x00000368 };

MatchFileDescriptor CommonUIFiles_inGame[0x43] = {
    { 0x0000040B, 0x4013764C, 0x1A635000, 0x0007DB48 },
    { 0x0000040B, 0x4003E3DC, 0x1A6B3000, 0x00021420 },
    { 0x0000040B, 0x4002EC10, 0x1A6D4800, 0x00013108 },
    { 0x0000040B, 0x400E72C0, 0x1A6E8000, 0x00060768 },
    { 0x0000040B, 0x40049404, 0x1A748800, 0x00020E34 },
    { 0x0000040B, 0x40076AE0, 0x18ED7000, 0x00036BC8 },
    { 0x0000040B, 0x4010FD70, 0x1A769800, 0x0005E284 },
    { 0x0000040B, 0x400DB738, 0x1A7C8000, 0x00049AB4 },
    { 0x0000040B, 0x400E9864, 0x1A812000, 0x00059DC0 },
    { 0x0000040B, 0x400B7718, 0x1A86C000, 0x00050288 },
    { 0x0000040B, 0x400D87FC, 0x1A8BC800, 0x00047BC4 },
    { 0x0000040B, 0x400D643C, 0x1A904800, 0x0004E3AC },
    { 0x0000040B, 0x400D5C7C, 0x1A953000, 0x00048D9C },
    { 0x0000040B, 0x400B767C, 0x1A99C000, 0x00047518 },
    { 0x0000040B, 0x400441F8, 0x1A9E3800, 0x0001AA84 },
    { 0x0000040B, 0x40106568, 0x1A9FE800, 0x00068C10 },
    { 0x0000040B, 0x4010E5A0, 0x0E97A800, 0x0009BCAC },
    { 0x0000040B, 0x40016980, 0x0EA16800, 0x0000D6C4 },
    { 0x0000040B, 0x40016980, 0x0EA24000, 0x0000C944 },
    { 0x0000040B, 0x40016980, 0x0EA31000, 0x0000E700 },
    { 0x0000040B, 0x40016980, 0x0EA3F800, 0x0000D64C },
    { 0x0000040B, 0x40016980, 0x0EA4D000, 0x0000C900 },
    { 0x0000040B, 0x40016980, 0x0EA5A000, 0x0000CFFC },
    { 0x0000040B, 0x40016980, 0x0EA67000, 0x0000D720 },
    { 0x0000040B, 0x40016980, 0x0EA74800, 0x0000D6CC },
    { 0x0000040B, 0x40016980, 0x0EA82000, 0x0000D21C },
    { 0x0000040B, 0x40016980, 0x0EA8F800, 0x0000D0BC },
    { 0x0000040B, 0x40016980, 0x0EA9D000, 0x0000B544 },
    { 0x0000040B, 0x40016980, 0x0EAA8800, 0x0000C4F8 },
    { 0x0000040B, 0x400ADFFC, 0x18AEE800, 0x0004BAB0 },
    { 0x0000040B, 0x4037CF5C, 0x18B3A800, 0x00208AF0 },
    { 0x0000040B, 0x4000A820, 0x18ED3800, 0x00003758 },
    { 0x0000040B, 0x4011EC24, 0x18F0E000, 0x000D8818 },
    { 0x0000040B, 0x400193E8, 0x191B8800, 0x000089D8 },
    { 0x0000040B, 0x4006C850, 0x06C96000, 0x0002C884 },
    { 0x0000040B, 0x4005B178, 0x06CC3000, 0x0003555C },
    { 0x0000040B, 0x401EB174, 0x18D43800, 0x000FB220 },
    { 0x0000040B, 0x4001ED60, 0x1AA67800, 0x0000CFF0 },
    { 0x0000040B, 0x4000BF30, 0x1AA74800, 0x000026E0 },
    { 0x0000040B, 0x40003498, 0x1AA77000, 0x00000E28 },
    { 0x0000040B, 0x4000BDE0, 0x1AA78000, 0x000024F4 },
    { 0x0000040B, 0x40006088, 0x1AA7A800, 0x00001290 },
    { 0x0000040B, 0x400049F0, 0x1AA7C000, 0x000018F4 },
    { 0x0000040B, 0x40005ECC, 0x1AA7E000, 0x00001D38 },
    { 0x0000040B, 0x40002670, 0x1AA80000, 0x00000BE8 },
    { 0x00000000, 0x00028240, 0x1AA81000, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AAA9800, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AAD2000, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AAFA800, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AB23000, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AB4B800, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AB74000, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AB9C800, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1ABC5000, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1ABED800, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AC16000, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AC3E800, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AC67000, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AC8F800, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1ACB8000, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1ACE0800, 0x00028240 },
    { 0x00000000, 0x00028240, 0x1AD09000, 0x00028240 },
    { 0x0000040B, 0x40001640, 0x08EB4800, 0x00000C38 },
    { 0x0000040B, 0x400B2D00, 0x08EB5800, 0x0006A948 },
    { 0x00000000, 0x00000686, 0x08F20800, 0x00000688 },
    { 0x00000000, 0x00003C98, 0x08F21000, 0x00003C98 },
    { 0x0000040B, 0x4000EBBC, 0x08F25000, 0x00009570 },
};

// .text:0x0005A28C size:0x3F8 mapped:0x80699320
void fn_3_5A28C(void) {
    DrawingSceneStruct* item = currentDrawingItem;

    switch (g_UnkSimulation_31AC0.step) {
    case 0:
        lbl_8037169C[0x1B] = calledWhenStartingMatch();
        g_UnkSimulation_31AC0.step++;
        // fallthrough
    case 1:
        animRelated[0xA4] = 0;
        if (fn_80020218()) {
            if (fn_80020278(lbl_8037169C[0x1B])) {
                animRelated[0xA4] = 1;
                g_UnkSimulation_31AC0.step++;
            }
        } else {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 2:
        item->state = 0;
        fn_800216F8(1, fn_3_910AC);
        g_UnkSimulation_31AC0.step++;
        break;
    case 3:
        if (item->state != 0) {
            item->state = 0;
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 4: {
        u8 idx = audioFileDescriptors[0x39A];
        s16 charID = findCharacterID(inMemRoster[idx / PLAYERS_PER_TEAM][idx % PLAYERS_PER_TEAM].stats.CharID);
        fn_800216F8((u8)(charID + 5), fn_3_90F48);
        g_UnkSimulation_31AC0.step++;
        break;
    }
    case 5:
        if (item->state != 0) {
            if (audioFileDescriptors[0x39A] != 0x11) {
                audioFileDescriptors[0x39A]++;
                g_UnkSimulation_31AC0.step = 4;
            } else {
                audioFileDescriptors[0x39A] = 0;
                item->state = 0;
                g_UnkSimulation_31AC0.step++;
            }
        }
        break;
    case 6:
        fn_800216F8((u8)(g_d_GameSettings.StadiumID + 0x27), fn_3_90798);
        g_UnkSimulation_31AC0.step++;
        break;
    case 7:
        if (item->state != 0) {
            item->state = 0;
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 8:
        FrameCountOfEntireGame[0x10] = 0;
        insertGraphicDrawingFunction(manageLoadingState, 0);
        g_UnkSimulation_31AC0.step++;
        break;
    case 9:
        if (FrameCountOfEntireGame[0x10] != 0) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 10:
        if (diskReadRelated(&CommonUIFiles_inGame[0], 2)) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 11:
        if (diskReadRelated(&CommonUIFiles_inGame[g_GameLogic.logo[0].ID / 4 + 0x11], 0xF)) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 12:
        if (diskReadRelated(&CommonUIFiles_inGame[g_GameLogic.logo[1].ID / 4 + 0x11], 0x10)) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 13:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO) {
            if (fn_80069B68() == 0) {
                break;
            }
        }
        g_UnkSimulation_31AC0.step++;
        // fallthrough
    case 14:
        stadiumSetupRelated();
        fn_8001A3FC(0);
        g_UnkSimulation_31AC0.step = 0x11;
        break;
    case 17:
        sound_crowd_EffectsStruct._00 = (u32)ARAMTransfer(sequencedSongsFileDescriptor, 0, 0, 0);
        g_UnkSimulation_31AC0.step++;
        break;
    case 18:
        if (lbl_803C6CF8[0x715] == 1) {
            fn_3_906FC();
            g_UnkSimulation_31AC0.step++;
        }
        break;
    default:
        item->func = fn_3_5AE0C;
        break;
    }
}

// .text:0x00059F40 size:0x34C mapped:0x80698FD4
void fn_3_59F40(void) {
    MatchFileDescriptor* files = sequencedSongsFileDescriptor;
    DrawingSceneStruct* item = currentDrawingItem;

    switch (g_UnkSimulation_31AC0.step) {
    case 0:
        item->state = 0;
        animRelated[0xD8] = 0;
        g_UnkSimulation_31AC0.step++;
        break;
    case 1:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            fn_800216F8(0x2D, fn_3_90798);
        } else {
            fn_800216F8(0x2E, fn_3_90764);
        }
        g_UnkSimulation_31AC0.step++;
        break;
    case 2:
        if (item->state != 0) {
            item->state = 0;
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 3:
        sound_crowd_EffectsStruct._00 = (u32)ARAMTransfer(files, 0, 0, 0);
        g_UnkSimulation_31AC0.step++;
        break;
    case 4:
        if (lbl_803C6CF8[0x715] == 1) {
            fn_3_906FC();
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 5:
        stadiumSetupRelated();
        hugeAnimStruct._2D7D = 0;
        fn_8001A25C();
        g_UnkSimulation_31AC0.step++;
        break;
    case 6:
        if (hugeAnimStruct._2D7D != 0) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 7:
        if (maybeLoadHUDObjectFromMemory()) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 8:
        if (lbl_3_common_bss_35154[0x3B0] == 0) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 9:
        if (fn_3_11D6A0()) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 10:
        loadSomeDataFile();
        g_UnkSimulation_31AC0.step++;
        break;
    case 11:
        if (lbl_803C6CF8[0x715] == 1) {
            someAllocFunction();
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 12:
        screenTextArray.textBanks[6] = (TextBank*)ARAMTransfer(&files[0x42], 0, 1, 0);
        g_UnkSimulation_31AC0.step++;
        break;
    case 13:
        if (lbl_803C6CF8[0x715] == 1) {
            fn_800111B4(screenTextArray.textBanks[6]);
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 14:
        if (diskReadRelated(&files[2], 2)) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 15:
        if (diskReadRelated(&files[5], 3)) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                g_UnkSimulation_31AC0.step = 0x10;
            } else {
                g_UnkSimulation_31AC0.step = 0x11;
            }
        }
        break;
    case 16:
        if (diskReadRelated(&files[6], 0xE)) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 17:
        if (diskReadRelated(&files[7], 0x14)) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 18:
        item->func = fn_3_5AE0C;
        break;
    }
}

// .text:0x00059C2C size:0x314 mapped:0x80698CC0
void fn_3_59C2C(void) {
    DrawingSceneStruct* item = currentDrawingItem;

    switch (g_UnkSimulation_31AC0.step) {
    case 0:
        item->state = 0;
        fn_800216F8(3, fn_3_91064);
        g_UnkSimulation_31AC0.step++;
        break;
    case 1:
        if (item->state != 0) {
            item->state = 0;
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 2:
        fn_800216F8((u8)(g_d_GameSettings.StadiumID + 0x27), fn_3_90798);
        g_UnkSimulation_31AC0.step++;
        break;
    case 3:
        if (item->state != 0) {
            item->state = 0;
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 4:
        FrameCountOfEntireGame[0x10] = 0;
        insertGraphicDrawingFunction(manageLoadingState, 0);
        g_UnkSimulation_31AC0.step++;
        break;
    case 5:
        if (FrameCountOfEntireGame[0x10] == 1) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 6:
        if (diskReadRelated(&CommonUIFiles_inGame[0], 2)) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 7:
        if (diskReadRelated(&CommonUIFiles_inGame[14], 0xB)) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 8:
        if (diskReadRelated(&CommonUIFiles_inGame[29], 9)) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 9:
        sound_crowd_EffectsStruct._00 = (u32)ARAMTransfer(&lbl_3_data_3D70, 0, 0, 0);
        g_UnkSimulation_31AC0.step++;
        break;
    case 10:
        if (lbl_803C6CF8[0x715] == 1) {
            fn_3_906FC();
            sound_crowd_EffectsStruct._2C = 0;
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 11:
        if (fn_3_90928()) {
            sound_crowd_EffectsStruct._2C = 0;
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 12:
        stadiumSetupRelated();
        practice_loadCharacterData();
        fn_8001A3FC(2);
        hugeAnimStruct._2D7D = 0;
        fn_80019A60();
        g_UnkSimulation_31AC0.step++;
        break;
    case 13:
        if (hugeAnimStruct._2D7D != 0) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 14:
        if (fn_3_1665E4()) {
            g_UnkSimulation_31AC0.step++;
        }
        break;
    case 15:
        loadSomeDataFile();
        g_UnkSimulation_31AC0.step++;
        break;
    case 16:
        if (lbl_803C6CF8[0x715] == 1) {
            someAllocFunction();
            g_UnkSimulation_31AC0.step++;
        }
        break;
    default:
        item->func = fn_3_5AE0C;
        break;
    }
}

// .text:0x00059BCC size:0x60 mapped:0x80698C60
int fn_3_59BCC(int arg0) {
    DrawingSceneStruct* item = currentDrawingItem;

    if (arg0 < 1) {
        return 0;
    }
    if (arg0 == 1) {
        fn_8001AAA4();
    }
    if (item->state != 0) {
        fn_3_6AEC0();
        return 1;
    }
    return 0;
}

// .text:0x00059B20 size:0xAC mapped:0x80698BB4
void fn_3_59B20(void) {
    int i;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        for (i = 0; i < 4; i++) {
            HugeAnimPlayer* player = &hugeAnimStruct.players[i];
            fn_80022CB4(&CharacterFiles[player->charID * 0x13 + 1], (u32)player->_00C, 0, 0, (void (*)())fn_3_59AC0, player);
        }
    }
}

// .text:0x00059AE4 size:0x3C mapped:0x80698B78
int fn_3_59AE4(void) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        return fn_80022B68();
    }
    return 1;
}

// .text:0x00059AC0 size:0x24 mapped:0x80698B54
void fn_3_59AC0(int arg0, int arg1, int arg2) {
    fn_80017D28(arg2);
}

// .text:0x00059A90 size:0x30 mapped:0x80698B24
void initializeSomethingDuringTransition(void) {
    int i;

    for (i = 0; i < 5; i++) {
        g_UnkSound_32718.queue[i] = 0;
    }
    g_UnkSound_32718._00 = 0;
    g_UnkSound_32718._07 = 0;
    g_UnkSound_32718._08 = 0;
}

// .text:0x00059918 size:0x178 mapped:0x806989AC
void QueueTextToDisplay(int arg0) {
    int i;

    if (g_Stats.replayInd != 0) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY && g_Ball.deadBallReason != 2) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE &&
        (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6)) {
        if (arg0 == 5) {
            return;
        }
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice._186 != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && arg0 == 5) {
        if (animRelated[0xD3] != 0) {
            return;
        }
        animRelated[0xD3] = 1;
    }
    if (g_GameLogic.playOver != 0) {
        return;
    }
    if (g_Scores._C5 != 0) {
        return;
    }
    if (arg0 == 4) {
        if (g_Scores._C4 != 0) {
            return;
        }
        g_Scores._C4 = 1;
    }
    if (arg0 == 0xD || arg0 == 0x11) {
        if (g_Scores._C5 != 0) {
            return;
        }
        g_Scores._C5 = 1;
        g_GameLogic.gameOverInd = 1;
    }
    for (i = 0; i < 5; i++) {
        if (g_UnkSound_32718.queue[i] == 0) {
            g_UnkSound_32718.queue[i] = arg0;
            return;
        }
    }
}
