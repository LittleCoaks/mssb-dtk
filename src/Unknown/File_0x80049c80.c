#include "Unknown/File_0x80049c80.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80049878.h"
#include "Unknown/File_0x800569c8.h"
#include "Unknown/File_0x800625a4.h"
#include "static/UnknownHomes_Static.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"

extern struct {
    /* 0x00 */ u8 _00[0x55];
    /* 0x55 */ u8 unk55[4];
} gameSetUpStep;

extern u8 lbl_8037169C[0x1C];
extern u16 lbl_803C5EE0[11];

void stadiumSelect(void) {
    if (gameSetUpStep.unk55[0] != 0 || gameSetUpStep.unk55[1] != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && lbl_8037169C[0x12] == 0) {
        changeScene(1, 6);
    }
    g_MatchInfo.unk36 = 1;
    g_MatchInfo.unk37 = g_MatchInfo.unk38;
    g_MatchInfo.unk38 = 3;
    possiblyTransferDataBetweenDifferentRels();
    memset(lbl_803C5EE0, 0, sizeof(lbl_803C5EE0));
    updateMenuNumbers();
    updateCharacterSelectProcessCode(0, 0x29);
}
