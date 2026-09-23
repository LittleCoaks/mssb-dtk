#include "game/stadium/stadium_star.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/animation/scene_effects.h"
#include "game/sound/m_sound.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800b0a14.h"

// The part of the shared effects block (lbl_3_common_bss_35154, used by ~30 units) that the
// stadium star effect owns.
typedef struct _StadiumStarState {
    /*0x000*/ u8 _000[0x3AC];
    /*0x3AC*/ u32 flags;
    /*0x3B0*/ u8 _3B0[0x3E8 - 0x3B0];
    /*0x3E8*/ Vec starPos;
    /*0x3F4*/ Vec starRot;
    /*0x400*/ u8 _400[4];
    /*0x404*/ s16 starFrames;
    /*0x406*/ u8 _406[4];
    /*0x40A*/ u8 starActive;
    /*0x40B*/ u8 _40B[0x479 - 0x40B];
    /*0x479*/ u8 _479;
    /*0x47A*/ u8 _47A[0x480 - 0x47A];
} StadiumStarState; // size: 0x480

#define STADIUM_STAR_FRAMES 80
#define STADIUM_STAR_MAX_STARS 5
#define SFX_STAR_AWARDED 0x19D

extern StadiumStarState lbl_3_common_bss_35154;

// .text:0x000CB738 size:0x9C mapped:0x8070A7CC
void stadiumStarAnimation(void) {
    StadiumStarState* star = &lbl_3_common_bss_35154;

    if (g_d_GameSettings._55 != 0 || star->_479 != 0 || star->starFrames-- == 0) {
        star->starActive = FALSE;
        removeCurrentDrawingItem();
    } else {
        fn_3_BD8D8();
        star->starPos.y += -0.03125f;
        star->starRot.y += 0.15707964f;
    }
}

// .text:0x000CB7D4 size:0x14 mapped:0x8070A868
void fn_3_CB7D4(void) {
    lbl_3_common_bss_35154.starFrames = 0;
}

// .text:0x000CB7E8 size:0xC0 mapped:0x8070A87C
void stadiumStarAwarded(f32 x, f32 y, f32 z) {
    lbl_3_common_bss_35154.starPos.x = x;
    lbl_3_common_bss_35154.starPos.y = y;
    lbl_3_common_bss_35154.starPos.z = z;
    lbl_3_common_bss_35154.starRot.z = 0.0f;
    lbl_3_common_bss_35154.starRot.y = 0.0f;
    lbl_3_common_bss_35154.starRot.x = 0.0f;
    lbl_3_common_bss_35154.starFrames = STADIUM_STAR_FRAMES;
    lbl_3_common_bss_35154.starActive = TRUE;
    lbl_3_common_bss_35154.flags |= 4;
    insertGraphicDrawingFunction(stadiumStarAnimation, (u16)(currentDrawingItem->priority + 1));
    playSoundEffect(SFX_STAR_AWARDED);
    if (g_GameLogic.TeamStars[g_GameLogic.teamBatting] < STADIUM_STAR_MAX_STARS) {
        g_GameLogic.TeamStars[g_GameLogic.teamBatting]++;
    }
    g_GameLogic.stadiumStarObtained = TRUE;
}
