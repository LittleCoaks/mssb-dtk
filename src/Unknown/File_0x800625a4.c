#include "Unknown/File_0x800625a4.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/os.h"

extern struct {
    /*0x00*/ u8 _00;
    /*0x01*/ u8 stepFlags[14][6];
    /*0x55*/ u8 preventCursorMovement[4];
    /*0x59*/ u8 portCaptainSlot[4];
    /*0x5D*/ u8 currentCharacterSelectProcess[4];
    /*0x61*/ u8 _61[3];
} gameSetUpStep;

void updateCharacterSelectProcessCode(int port, u8 process) {
    s32 i;
    int reportPort = g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME ? 0 : port;

    if (gameSetUpStep.preventCursorMovement[reportPort]) {
        OSReport("パッド処理拒否中にムービー再生要求あり(%d) Step No %d \n", reportPort,
                 gameSetUpStep.currentCharacterSelectProcess[reportPort]);
    }
    gameSetUpStep.currentCharacterSelectProcess[port] = process;
    for (i = 0; i < 14; i++) {
        gameSetUpStep.stepFlags[i][port] = 0;
    }
}
