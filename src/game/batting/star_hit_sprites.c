#include "game/batting/star_hit_sprites.h"
#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_star_hit_sprites
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/batting/charge_effects.h"
#include "game/math/game_math.h"
#include "game/pitching/perfect_pitch_gfx.h"

// A star-hit marker sprite owned by the hugeAnimStruct overlay entry.
typedef struct _StarHitMarker {
    /*0x00*/ u8 _00[4];
    /*0x04*/ VecXYZ pos;
    /*0x10*/ VecXYZ pos2;
    /*0x1C*/ u8 _1C[0x26 - 0x1C];
    /*0x26*/ E(u8, BOOL) active;
    /*0x27*/ u8 _27;
} StarHitMarker;

typedef struct _StarHitOverlay {
    /*0x000*/ u8 _000[0x2A8];
    /*0x2A8*/ StarHitMarker markers[4];
} StarHitOverlay;

typedef struct _StarHitActor {
    /*0x000*/ u8 _000[0x34];
    /*0x034*/ VecXYZ pos;
    /*0x040*/ VecXYZ pos2;
    /*0x04C*/ u8 _04C[0x252 - 0x4C];
    /*0x252*/ E(s8, CHAR_ID) charId;
} StarHitActor;

typedef struct _StarSprite {
    /*0x00*/ u8 _00[0x54];
    /*0x54*/ f32 scaleA;
    /*0x58*/ u8 _58;
    /*0x59*/ u8 flagA;
    /*0x5A*/ u8 flagB;
    /*0x5B*/ u8 mode;
    /*0x5C*/ f32 scaleB;
    /*0x60*/ u8 _60[0x90 - 0x60];
} StarSprite;

typedef struct _StarSpriteTable {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ StarSprite sprites[1];
} StarSpriteTable;

extern struct {
    /*0x0000*/ u8 _0000[0x64];
    /*0x0064*/ StarSpriteTable* spriteTable;
    /*0x0068*/ u8 _0068[0x2C50 - 0x68];
    /*0x2C50*/ StarHitActor* actors[(0x2D90 - 0x2C50) / 4];
    /*0x2D90*/ StarHitOverlay* overlay;
} hugeAnimStruct;

// Phase flags of the star-hit / charge sprite effects.
typedef struct _StarHitState {
    /*0x00*/ u8 _00[0xC8];
    /*0xC8*/ u8 pitchPhase;
    /*0xC9*/ E(u8, BOOL) chargeActive;
    /*0xCA*/ u8 hitPhase;
    /*0xCB*/ u8 _CB[0xD4 - 0xCB];
    /*0xD4*/ E(u8, BOOL) markersActive;
    /*0xD5*/ u8 _D5[0x124 - 0xD5];
} StarHitState;

typedef struct _StarHitPlayState {
    /*0x00*/ u8 _00[2];
    /*0x02*/ s16 phase;
    /*0x04*/ u8 _04[6];
    /*0x0A*/ u8 type;
} StarHitPlayState;

typedef struct _StarHitCameraState {
    /*0x0*/ u8 _0[4];
    /*0x4*/ f32 angle;
} StarHitCameraState;

// The part of the shared effects block (lbl_3_common_bss_35154, used by ~30 units) that this
// unit touches.
typedef struct _StarHitSharedBlock {
    /*0x000*/ u8 _000[0x3AC];
    /*0x3AC*/ u32 flags;
    /*0x3B0*/ u8 _3B0[0x480 - 0x3B0];
} StarHitSharedBlock;

extern StarHitState animRelated;
extern StarHitPlayState lbl_3_common_bss_32220;
extern StarHitCameraState lbl_3_common_bss_3223C;
extern StarHitSharedBlock lbl_3_common_bss_35154;

extern void fn_3_BD4F0(void);
extern void animationRelated(f32 x, f32 y, f32 z, BOOL afterHit);
extern void fn_3_BD6AC(BOOL flag, f32 x, f32 y, f32 z);
extern void setContactWordSprite(int type, f32 x, f32 y, f32 z);
extern void pauseAnimations(void);
extern void fn_3_CABB4(void);
extern void fn_80011578(void);
extern void fn_3_CB344(int actorIndex, int starType);
extern void chargeAnimRelated(void);
extern void fn_3_C0770(void);
extern void fn_3_C07B0(void);

// .text:0x0006AB58 size:0x368 mapped:0x806A9BEC
void animateChargeSprites(void) {
    VecXYZ* eye = (VecXYZ*)((u8*)&g_Camera + 0x2840);
    VecXYZ* target = (VecXYZ*)((u8*)&g_Camera + 0x284C);
    int type;

    lbl_3_common_bss_3223C.angle = game_atan2(target->z - eye->z, target->x - eye->x);
    fn_3_6AA98();
    fn_3_6A9B0();
    fn_3_6A83C();
    animateStarHits_Pitches();
    fn_3_6A300();
    if (g_Ball.framesSinceHit == 0 && (lbl_3_common_bss_35154.flags & 3) == 0) {
        if (g_Batter.captainStarSwingActivated != 0 || g_Batter.didNonCaptainStarSwingConnect != 0) {
            type = 4;
        } else if (g_Batter.hitGeneralType == BAT_CONTACT_TYPE_BUNT) {
            type = 0;
        } else if (g_Batter.displayContactSprite != 0) {
            type = 3;
        } else if (g_Batter.contactType == HIT_CONTACT_TYPE_PERFECT) {
            type = 2;
        } else {
            type = 1;
        }
        if (g_Batter.batterHand == BATTING_HAND_RIGHT) {
            setContactWordSprite(type, g_Batter.hitContactPos.x, -g_Batter.hitContactPos.y, g_Batter.hitContactPos.z);
        } else {
            setContactWordSprite(type, -g_Batter.hitContactPos.x, -g_Batter.hitContactPos.y, g_Batter.hitContactPos.z);
        }
    }
}

// .text:0x0006AB30 size:0x28 mapped:0x806A9BC4
void fn_3_6AB30(void) {
    pauseAnimations();
    fn_3_CABB4();
    fn_80011578();
}

// .text:0x0006AA98 size:0x98 mapped:0x806A9B2C
void fn_3_6AA98(void) {
    u8 type;

    if (g_Batter.charID == CHAR_ID_DK || g_Batter.charID == CHAR_ID_DIDDY || g_Batter.charID == CHAR_ID_YOSHI) {
        return;
    }
    type = lbl_3_common_bss_32220.type;
    if (type != 0) {
        if (type == 3 || type == 4) {
            chargeAnimRelated();
        } else if (type == 9) {
            fn_3_C0770();
        } else if (lbl_3_common_bss_32220.phase == 2 && type == 2) {
            fn_3_C07B0();
        }
    }
}

// .text:0x0006A9B0 size:0xE8 mapped:0x806A9A44
void fn_3_6A9B0(void) {
    int actor;

    if (g_d_GameSettings.minigamesEnabled != FALSE) {
        actor = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID];
    } else {
        actor = 9;
    }
    if (g_Batter.chargeStatus == CHARGE_SWING_STAGE_CHARGEUP) {
        if (g_Batter.chargeFrames == 1) {
            maybeConfigureChargeEffectGraphics(actor);
            animRelated.chargeActive = TRUE;
        } else {
            f32 charge = 100.0f * g_Batter.chargeUp;
            f32 release = 100.0f * g_Batter.chargeDown;
            applyChargeAnimationEffect(actor, charge, release, charge >= 100.0f);
        }
    } else if (animRelated.chargeActive != FALSE) {
        fn_3_C11CC(actor, TRUE);
        animRelated.chargeActive = FALSE;
    }
}

#pragma dont_inline on
// .text:0x0006A83C size:0x174 mapped:0x806A98D0
void fn_3_6A83C(void) {
    int actor = 0;
    s16 timer = g_Pitcher.pitchTotalTimeCounter;
    VecXYZ coords;
    u8 phase;
    int anim;

    if (timer <= 0) {
        animRelated.pitchPhase = 0;
        return;
    }
    phase = animRelated.pitchPhase;
    if (phase >= 2) {
        return;
    }
    if (g_d_GameSettings.minigamesEnabled != FALSE) {
        actor = g_Minigame.minigameControlStruct[0].characterIndex[(s8)g_Minigame.minigamePlayerSelectedOrder];
    }
    if (timer < 0) {
        return;
    }
    if (g_Pitcher.TypeOfPitch != 0 || g_Pitcher.ChargePitchType != 0) {
        if (phase == 0) {
            fn_3_CB344(actor, g_Pitcher.starPitchType);
            animRelated.pitchPhase = 1;
        }
        if (animRelated.pitchPhase == 1) {
            if (g_Ball.pitchHangtimeCounter == 1 || g_GameLogic.gameStatus != GAME_STATUS_AT_BAT) {
                fn_3_CB234(actor, TRUE);
                animRelated.pitchPhase = 2;
            } else {
                anim = 0x1A;
                if (g_Pitcher.handedness != 0) {
                    anim = 0x14;
                }
                getAnimRelatedCoordinates(actor, anim, &coords);
                fn_3_CB284(actor, g_Pitcher.windupCountdownUntilBallReleased, g_Pitcher.pitchChargeUpAnimationProportion);
            }
        }
    }
}

#pragma dont_inline reset

// .text:0x0006A414 size:0x428 mapped:0x806A94A8
void animateStarHits_Pitches(void) {
    if (g_Pitcher.pitchTotalTimeCounter <= 0) {
        if (animRelated.hitPhase != 0) {
            fn_3_BD4F0();
            animRelated.hitPhase = 0;
        }
        return;
    }
    if (g_Pitcher.starPitchType != CAPTAIN_STAR_TYPE_NONE || g_Pitcher.nonCaptainStarPitchTriggeredType != 0) {
        fn_3_CB1B0(0, g_Pitcher.starPitchType, g_Pitcher.windupCountdownUntilBallReleased);
    }
    if (g_Ball.pitchHangtimeCounter == 1) {
        fn_3_BD6AC(FALSE, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
        switch (g_Pitcher.starPitchType) {
            case CAPTAIN_STAR_TYPE_MARIO:
            case CAPTAIN_STAR_TYPE_LUIGI:
                animRelated.hitPhase = 1;
                break;
            case CAPTAIN_STAR_TYPE_PEACH:
            case CAPTAIN_STAR_TYPE_DAISY:
                animRelated.hitPhase = 2;
                break;
            case CAPTAIN_STAR_TYPE_YOSHI:
            case CAPTAIN_STAR_TYPE_BIRDO:
                animRelated.hitPhase = 3;
                break;
            case CAPTAIN_STAR_TYPE_BOWSER:
            case CAPTAIN_STAR_TYPE_BOWSERJR:
                animRelated.hitPhase = 4;
                break;
        }
        return;
    }
    if (animRelated.hitPhase == 1) {
        animationRelated(g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z, g_Ball.framesSinceHit >= 1);
        if ((g_Ball.framesSinceHit >= 0 || g_Ball.postPitchResultCounter >= 0 || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT)
            && g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_MARIO && g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_LUIGI) {
            fn_3_BD4F0();
            animRelated.hitPhase = 0;
            return;
        }
    }
    if (animRelated.hitPhase == 3) {
        animationRelated(g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z, g_Ball.framesSinceHit >= 1);
        if ((g_Ball.framesSinceHit >= 0 || g_Ball.postPitchResultCounter >= 0 || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT)
            && g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_YOSHI && g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_BIRDO) {
            fn_3_BD4F0();
            animRelated.hitPhase = 0;
            return;
        }
    }
    if (g_Ball.framesSinceHit == 1) {
        switch (g_Ball.currentStarSwing) {
            case CAPTAIN_STAR_TYPE_MARIO:
            case CAPTAIN_STAR_TYPE_LUIGI:
                fn_3_BD6AC(TRUE, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
                animRelated.hitPhase = 1;
                break;
            case CAPTAIN_STAR_TYPE_PEACH:
            case CAPTAIN_STAR_TYPE_DAISY:
                fn_3_BD6AC(TRUE, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
                break;
            case CAPTAIN_STAR_TYPE_YOSHI:
            case CAPTAIN_STAR_TYPE_BIRDO:
                fn_3_BD6AC(TRUE, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
                animRelated.hitPhase = 3;
                break;
            case CAPTAIN_STAR_TYPE_BOWSER:
            case CAPTAIN_STAR_TYPE_BOWSERJR:
                fn_3_BD6AC(TRUE, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
                animRelated.hitPhase = 4;
                break;
            case CAPTAIN_STAR_TYPE_WARIO:
            case CAPTAIN_STAR_TYPE_WALUIGI:
                fn_3_BD6AC(TRUE, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
                animRelated.hitPhase = 5;
                break;
        }
    }
    if (animRelated.hitPhase != 0) {
        animationRelated(g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z, g_Ball.framesSinceHit >= 1);
        if ((g_Ball.framesSinceHit >= 0 || g_Ball.postPitchResultCounter >= 0 || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT)
            && g_Ball.currentStarSwing == 0) {
            fn_3_BD4F0();
            animRelated.hitPhase = 0;
        }
    }
}

// .text:0x0006A400 size:0x14 mapped:0x806A9494
void fn_3_6A400(void) {
    animRelated.markersActive = FALSE;
}

// .text:0x0006A300 size:0x100 mapped:0x806A9394
void fn_3_6A300(void) {
    StarHitActor* actor;
    StarHitMarker* marker;

    if (animRelated.markersActive == FALSE) {
        return;
    }
    actor = hugeAnimStruct.actors[9];
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        actor = hugeAnimStruct.actors[(s8)g_Minigame.rosterID];
    }
    if (actor->charId == CHAR_ID_DRYBONES_GRAY) {
        marker = &hugeAnimStruct.overlay->markers[0];
    } else if (actor->charId == CHAR_ID_DRYBONES_GREEN) {
        marker = &hugeAnimStruct.overlay->markers[1];
    } else if (actor->charId == CHAR_ID_DRYBONES_RED) {
        marker = &hugeAnimStruct.overlay->markers[2];
    } else {
        marker = &hugeAnimStruct.overlay->markers[3];
    }
    marker->active = TRUE;
    marker->pos.x = actor->pos.x;
    marker->pos.y = -actor->pos.y;
    marker->pos.z = actor->pos.z;
    marker->pos2.x = actor->pos2.x;
    marker->pos2.y = -actor->pos2.y;
    marker->pos2.z = actor->pos2.z;
}

// .text:0x0006A2A4 size:0x5C mapped:0x806A9338
void fn_3_6A2A4(s8 index) {
    StarSprite* sprite;

    sprite = &hugeAnimStruct.spriteTable->sprites[index - 0x1F];
    animRelated.markersActive = TRUE;
    sprite->mode = 2;
    sprite->scaleB = 0.0f;
    sprite->flagA = 1;
    sprite->scaleA = 1.0f;
    sprite->flagB = 1;
}
