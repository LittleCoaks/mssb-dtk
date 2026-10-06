#ifndef __GAME_HUD_REP_3448_H_
#define __GAME_HUD_REP_3448_H_

#include "mssbTypes.h"

/* Drawing-script node scratch shared by the minigame HUD scenes. */
typedef struct MinigameHudScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
    /*0x16*/ u16 handleCount;
    /*0x18*/ u16 _18;
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 _1E;
    /*0x20*/ u16 _20;
    /*0x22*/ u16 _22;
    /*0x24*/ union {
        u8 scratch[0x1C];
        s16 popupPoints[4];
        s16 shownValues[8];
        u32 sndHandle;
    };
} MinigameHudScene;

void fn_3_11EC28(void);
void fn_3_11F02C(void);
void fn_3_11F480(void);
void fn_3_11F4B4(int player, int bonus);
void fn_3_11F508(void);
void fn_3_11F778(void);
void fn_3_11FA58(void);
void fn_3_11FDB0(void);
void fn_3_12026C(void);
void fn_3_12089C(void);
int fn_3_120F5C(void);
void fn_3_120FF8(void);
void fn_3_121304(void);
void fn_3_121908(void);
void fn_3_122334(void);
void fn_3_1226D4(void);
void fn_3_122D24(void);
void fn_3_1231D4(void);
void fn_3_1235B8(void);
void fn_3_123990(void);
void fn_3_123EBC(void);
void minigameStateLogic(void);
void fn_3_124738(void);
void fn_3_124CE0(void);
u32 fn_3_12536C(void);
u32 fn_3_125424(MinigameHudScene* scene, int handle, u32 targetFrame);
u32 fn_3_125480(MinigameHudScene* scene);
void fn_3_1254F8(void);
void fn_3_125604(void);
void fn_3_125850(void);
void fn_3_1258C0(void);
void fn_3_126604(void);
void fn_3_1274B4(void);
void fn_3_127B68(void);
void fn_3_128A38(void);
void fn_3_128B90(void);
void fn_3_128C18(void);
void fn_3_129370(void);
void fn_3_1293D0(void);
void fn_3_129458(void);
void fn_3_12955C(void);
void fn_3_129A18(void);
void fn_3_129C88(void);
void fn_3_129F48(void);
void fn_3_129FF8(void);
void fn_3_12A2B8(void);
void fn_3_12A3F0(void);
void fn_3_12A6C4(void);
void fn_3_12A910(void);
void fn_3_12B7A0(void);
void fn_3_12BB64(void);
void fn_3_12BFE8(void);
void fn_3_12C1AC(void);
void fn_3_12C3F0(void);
void fn_3_12C514(void);
void fn_3_12C5CC(void);
void fn_3_12C684(void);
void fn_3_12C74C(void);
void fn_3_12C868(void);
void fn_3_12C984(void);
void fn_3_12CA90(void);
void minigameGraphics(void);

#endif // !__GAME_HUD_REP_3448_H_
