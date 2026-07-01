#include "game/rep_720.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_3090.h"
#include "game/rep_1838.h"
#include "Dolphin/gx.h"
#include "Dolphin/rand.h"

extern u32 lbl_3_bss_44;
extern f32 lbl_3_data_1348[12][12];
extern s16 lbl_3_data_16C0;
extern s16 lbl_3_data_A38[2];
typedef struct {
    /* 0x00 */ VecXYZ _00;
    /* 0x0C */ f32 _0C;
    /* 0x10 */ s16 _10[2];
} lbl_3_data_A40_s; // size 0x14
extern lbl_3_data_A40_s lbl_3_data_A40[89];
extern lbl_3_data_A40_s lbl_3_data_16AC[1];

extern struct {
    /* 0x00 */ f32 velocityMult;
    /* 0x04 */ f32 maxVelocity;
    /* 0x08 */ f32 specializedMaxVelocity;
    /* 0x0C */ f32 yOffset;
    /* 0x10 */ f32 maxYOffset;
    /* 0x14 */ f32 heightMult;
    /* 0x18 */ f32 defaultVel;
} lbl_3_data_132C;

typedef struct {
    /* 0x0 */ f32 _0;
    /* 0x4 */ f32 _4;
    /* 0x8 */ f32 _8;
    /* 0xC */ s16 _C;
} lbl_3_data_16C4_s;

extern lbl_3_data_16C4_s lbl_3_data_16C4[];

// .text:0x0001CE90 size:0x9DC mapped:0x8065BF24
void fn_3_1CE90(void) {
    return;
}

// .text:0x0001CCC8 size:0x1C8 mapped:0x8065BD5C
void fn_3_1CCC8(void) {
    g_pCamera = &g_Camera;
    g_pCamera->_28A6 = 0;
    g_pCamera->_0000 = 0;
    g_pCamera->_287C = 0.f;
    g_pCamera->_2880 = 0.f;
    g_pCamera->_283E = 0;
    fn_3_1CBCC();
    g_pCamera->_030 = 0.f;
    g_pCamera->_034 = 0.f;
    g_pCamera->_038 = 0.f;
    g_pCamera->_0C0 = 0.f;
    g_pCamera->_0D0 = 1.f;
    g_pCamera->_0E2 = 0;
    g_pCamera->_0E0 = -1;
    g_pCamera->_0D4 = 0.f;
    g_pCamera->_0D8 = 0.f;
    g_pCamera->_0DC = 0.f;
    g_pCamera->_0E3 = 0;
    g_Camera._2818 = 0;
    g_Camera._2819 = 0;
    fn_3_106BA0();
    fn_3_FC448();
}

// .text:0x0001CBCC size:0xFC mapped:0x8065BC60
void fn_3_1CBCC(void) {
    g_GameLogic.sceneID = SCENE_ID_AT_BAT;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
        g_pCamera->_28A7 = lbl_3_data_A38[1];
    } else {
        g_pCamera->_28A7 = lbl_3_data_A38[0];
    }
    g_pCamera->_118 = 0;
    g_pCamera->_11C = 0;
    g_pCamera->_030 = 0.f;
    g_pCamera->_034 = 0.f;
    g_pCamera->_038 = 0.f;
    g_pCamera->_0C0 = 0.f;
    g_pCamera->_0D0 = 1.f;
    g_pCamera->_0E2 = 0;
    g_pCamera->_0E0 = -1;
    g_pCamera->_0D4 = 0.f;
    g_pCamera->_0D8 = 0.f;
    g_pCamera->_0DC = 0.f;
    g_pCamera->_0E3 = 0;
}

// .text:0x0001CAC0 size:0x10C mapped:0x8065BB54
void fn_3_1CAC0(void) {
    camera_803c639c_s* p = fn_80052768_getCamera(g_pCamera->_28A8);
    p->eye.x = g_pCamera->_2840.x;
    p->eye.y = -g_pCamera->_2840.y;
    p->eye.z = g_pCamera->_2840.z;

    p->target.x = g_pCamera->_284C.x;
    p->target.y = -g_pCamera->_284C.y;
    p->target.z = g_pCamera->_284C.z;

    if (lbl_3_common_bss_DE94._0000->_09AC == 0) {
        p->zoom = g_pCamera->_2878;
    } else {
        p->zoom =
            36.0 / tan(lbl_3_common_bss_DE94._0000->_00A0 * (1.f / (PI / 180.f)) / (2.f * (180.f / PI))) / 2.0 / 74.0;
    }
}

// .text:0x0001C8AC size:0x214 mapped:0x8065B940
void fn_3_1C8AC(BOOL b) {
    f32 f5;
    f32 f31;
    f32 f30;
    f32 f29;
    f32 f28;
    f32 f3;
    f32 f2;
    if (b) {
        f29 = fn_3_9FEA8(g_pCamera->_2874);
    } else {
        f29 = shortAngleToRad_Capped(g_pCamera->_289E);
    }
    f28 = COSF(f29) * 20.f;
    f30 = SINF(f29) * 20.f;
    if (b) {
        f29 = fn_3_9FEA8(g_pCamera->_2870);
    }else {
        f29 = shortAngleToRad_Capped(g_pCamera->_289C);
    }
    f31 = COSF(f29);
    f5 = SINF(f29);
    f3 = f31 * f28;
    f2 = f5 * f28;
    g_pCamera->_2890 = g_pCamera->_2840.x;
    g_pCamera->_2894 = g_pCamera->_2840.y;
    g_pCamera->_2898 = g_pCamera->_2840.z;

    g_pCamera->_2858 += f31 * g_pCamera->_287C;
    g_pCamera->_2860 += f5 * g_pCamera->_287C;

    g_pCamera->_2858 += f5 * g_pCamera->_2880;
    g_pCamera->_2860 -= f31 * g_pCamera->_2880;

    g_pCamera->_284C.x = f3 + g_pCamera->_2858;
    g_pCamera->_284C.y = f30 + g_pCamera->_285C;
    g_pCamera->_284C.z = f2 + g_pCamera->_2860;

    g_pCamera->_2840.x = g_pCamera->_2858;
    g_pCamera->_2840.y = g_pCamera->_285C;
    g_pCamera->_2840.z = g_pCamera->_2860;
    g_pCamera->_287C = 0.0f;
    g_pCamera->_2880 = 0.0f;
}

// .text:0x0001C8A8 size:0x4 mapped:0x8065B93C
void fn_3_1C8A8(void) {
    return;
}

// .text:0x0001C898 size:0x10 mapped:0x8065B92C
u8 fn_3_1C898(void) {
    return g_GameLogic.sceneID;
}

// .text:0x0001C684 size:0x214 mapped:0x8065B718
void fn_3_1C684(void) {
    f32 _f31;
    f32 f30;
    f32 _f30;
    f32 _f29;
    f32 _f28;
    f32 _f6;
    f32 _f4;
    f32 _f3;
    f32 _f2;

    lbl_3_data_A40_s* p = &lbl_3_data_A40[g_pCamera->_0000];
    g_pCamera->_2858 = p->_00.x;
    g_pCamera->_285C = p->_00.y;
    g_pCamera->_2860 = p->_00.z;
    g_pCamera->_289C = p->_10[0];
    g_pCamera->_289E = p->_10[1];
    g_pCamera->_2878 = p->_0C;

    _f30 = shortAngleToRad_Capped(g_pCamera->_289E);
    f30 = COSF(_f30) * 20.f;
    _f29 = SINF(_f30);

    _f28 = shortAngleToRad_Capped(g_pCamera->_289C);
    _f31 = COSF(_f28);
    _f6 = SINF(_f28);
    
    _f4 = _f31 * f30;
    _f2 = _f6 * f30;
    _f3 = _f29 * 20.f;
    g_pCamera->_2890 = g_pCamera->_2840.x;
    g_pCamera->_2894 = g_pCamera->_2840.y;
    g_pCamera->_2898 = g_pCamera->_2840.z;

    g_pCamera->_2858 += _f31 * g_pCamera->_287C;
    g_pCamera->_2860 += _f6 * g_pCamera->_287C;

    g_pCamera->_2858 += _f6 * g_pCamera->_2880;
    g_pCamera->_2860 -= _f31 * g_pCamera->_2880;

    g_pCamera->_284C.x = _f4 + g_pCamera->_2858;
    g_pCamera->_284C.y = _f3 + g_pCamera->_285C;
    g_pCamera->_284C.z = _f2 + g_pCamera->_2860;

    g_pCamera->_2840.x = g_pCamera->_2858;
    g_pCamera->_2840.y = g_pCamera->_285C;
    g_pCamera->_2840.z = g_pCamera->_2860;
    g_pCamera->_287C = 0.0f;
    g_pCamera->_2880 = 0.0f;
}

// .text:0x0001C1B0 size:0x4D4 mapped:0x8065B244
void fn_3_1C1B0(void) {
    return;
}

// .text:0x0001C130 size:0x80 mapped:0x8065B1C4
void fn_3_1C130(void) {
    g_pCamera->_030 = 0.f;
    g_pCamera->_034 = 0.f;
    g_pCamera->_038 = 0.f;
    g_pCamera->_0C0 = 0.f;
    g_pCamera->_0D0 = 1.f;
    g_pCamera->_0E2 = 0;
    g_pCamera->_0E0 = -1;
    g_pCamera->_0D4 = 0.f;
    g_pCamera->_0D8 = 0.f;
    g_pCamera->_0DC = 0.f;
    g_pCamera->_0E3 = 0;
}

// .text:0x0001C0B0 size:0x80 mapped:0x8065B144
void fn_3_1C0B0(void) {
    g_pCamera->_030 = 0.f;
    g_pCamera->_034 = 0.f;
    g_pCamera->_038 = 0.f;
    g_pCamera->_0C0 = 0.f;
    g_pCamera->_0D0 = 1.f;
    g_pCamera->_0E2 = 0;
    g_pCamera->_0E0 = -1;
    g_pCamera->_0D4 = 0.f;
    g_pCamera->_0D8 = 0.f;
    g_pCamera->_0DC = 0.f;
    g_pCamera->_0E3 = 0;
}

// .text:0x0001BA18 size:0x698 mapped:0x8065AAAC
void fn_3_1BA18(void) {
    return;
}

// .text:0x0001B370 size:0x6A8 mapped:0x8065A404
void fn_3_1B370(void) {
    return;
}

// .text:0x0001B17C size:0x1F4 mapped:0x8065A210
void fn_3_1B17C(void) {
    f32 vel;
    f32 deltaVelocity;
    int r0 = FALSE;
    if (g_pCamera->_0E2 != 0) {
        return;
    }

    if (g_Ball.ballState == BALL_STATE_HELD) {
        vel = lbl_3_data_132C.defaultVel;
    } else {
        f32 yOffset;
        vel = 1.f + g_Ball.ballVelocity * lbl_3_data_132C.velocityMult;
        if (vel > lbl_3_data_132C.maxVelocity) {
            vel = lbl_3_data_132C.maxVelocity;
        }
        if ((g_Ball.ballState == BALL_STATE_THROWN || g_Ball.ballState == BALL_STATE_LOOSE) &&
            vel > lbl_3_data_132C.specializedMaxVelocity) {
            vel = lbl_3_data_132C.specializedMaxVelocity;
        }
        yOffset = g_Ball.AtBat_Contact_BallPos.y - lbl_3_data_132C.yOffset;
        if (yOffset < 0.0f) {
            yOffset = 0.0f;
        }
        if (yOffset > lbl_3_data_132C.maxYOffset){
            yOffset = lbl_3_data_132C.maxYOffset;
        }

        if (1.f + yOffset * lbl_3_data_132C.heightMult >= vel) {
            vel = 1.f + yOffset * lbl_3_data_132C.heightMult;
            r0 = TRUE;
        }
    }

    deltaVelocity = vel - g_pCamera->_0D0;
    if (vel == 1.0f && g_pCamera->_0D0 > 1.0f && g_pCamera->_0D0 < 1.2f && deltaVelocity < -0.002f) {
        deltaVelocity = (1.0f - g_pCamera->_0D0) * 0.01f;
    }
    if (vel == 0.9f && g_pCamera->_0D0 > 0.9f && g_pCamera->_0D0 < 1.f && deltaVelocity < -0.002f){
        deltaVelocity = (0.9f - g_pCamera->_0D0) * 0.01f;
    }
    if (deltaVelocity > 0.02f){
        deltaVelocity = 0.02f;
    }

    if (r0) {
        if (deltaVelocity < -0.001f) {
            deltaVelocity = -0.001f;
        }
    } else {
        if (deltaVelocity < -0.003f) {
            deltaVelocity = -0.003f;
        }
    }
    g_pCamera->_0D0 += deltaVelocity;
}

// .text:0x0001AEB8 size:0x2C4 mapped:0x80659F4C
void fn_3_1AEB8(void) {
    lbl_3_data_16C4_s* p = &lbl_3_data_16C4[g_pCamera->_283F];
    if (g_pCamera->_283C > 0) {
        g_pCamera->_283C--;
        return;
    } 
    
    if (g_pCamera->_2838 == 0) {
        Vec v;
        f32 f28;
        v.x = g_pCamera->_284C.x - g_pCamera->_2840.x;
        v.y = g_pCamera->_284C.y - g_pCamera->_2840.y;
        v.z = g_pCamera->_284C.z - g_pCamera->_2840.z;
        f28 = RandomF32_UNK_Range(p->_0, p->_4) / dolsqrtf2(SQ(v.x) + SQ(v.y) + SQ(v.z));
        v.x *= f28;
        v.y *= f28;
        v.z *= f28;
        g_pCamera->_281C = g_pCamera->_2828 - v.x;
        g_pCamera->_2820 = g_pCamera->_282C - v.y;
        g_pCamera->_2824 = g_pCamera->_2830 - v.z;
        g_pCamera->_2834 = p->_8;
        g_pCamera->_283A = p->_C;
    }
    
    if (g_pCamera->_2838 < S16_MAX - 1) {
        g_pCamera->_2838++;
    } else{
        g_pCamera->_2838 = S16_MAX;
    }

    g_pCamera->_284C.x = g_pCamera->_2828;
    g_pCamera->_284C.y = g_pCamera->_282C;
    g_pCamera->_284C.z = g_pCamera->_2830;

    g_pCamera->_2840.x = g_pCamera->_281C;
    g_pCamera->_2840.y = g_pCamera->_2820;
    g_pCamera->_2840.z = g_pCamera->_2824;

    g_pCamera->_2878 = g_pCamera->_2834;
    if (g_pCamera->_2838 > g_pCamera->_283A) {
        g_pCamera->_283E = 0;
    }
}

// .text:0x0001AE44 size:0x74 mapped:0x80659ED8
void fn_3_1AE44(u8 arg4, u16 arg5, f32 arg1, f32 arg2, f32 arg3) {
    if (g_Stats.replayInd == 0 && g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
        g_pCamera->_2828 = arg1;
        g_pCamera->_282C = arg2;
        g_pCamera->_2830 = arg3;
        g_pCamera->_2838 = 0;
        g_pCamera->_283C = arg5;
        g_pCamera->_283E = 1;
        g_pCamera->_283F = arg4;
    }
}

// .text:0x00019FA4 size:0xEA0 mapped:0x80659038
void fn_3_19FA4(void) {
    return;
}

// .text:0x00019CB0 size:0x2F4 mapped:0x80658D44
void fn_3_19CB0(void) {
    return;
}

// .text:0x00019B3C size:0x174 mapped:0x80658BD0
void fn_3_19B3C(int arg, f32* arg2) {
    int sp8[4];
    int i;
    
    for (i = 0; i < g_pCamera->_0012; i++) {
        sp8[i] = lbl_3_data_A40[g_pCamera->_0004[i]]._10[arg];
    }

    if (arg != 0) {
        for (i = 0; i < g_pCamera->_0012; i++) {
            arg2[i] = sp8[i];
        }
    } else {
        int total = sp8[0];

        arg2[0] = total;
        for (i = 1; i < g_pCamera->_0012; i++) {
            if (sp8[i] - sp8[i - 1] > 0x800) {
                total -= 0x1000 - (sp8[i] - sp8[i - 1]);
            } else if (sp8[i] - sp8[i - 1] < -0x800) {
                total += 0x1000 + (sp8[i] - sp8[i - 1]);
            } else {
                total += (sp8[i] - sp8[i - 1]);
            }
            arg2[i] = total;
        }
    }
}

// .text:0x000197E8 size:0x354 mapped:0x8065887C
void fn_3_197E8(void) {
    return;
}

// .text:0x00019770 size:0x78 mapped:0x80658804
void fn_3_19770(void) {
    int i;
    inMemCamera* cam = g_pCamera;
    f32* p = lbl_3_data_1348[cam->_11C];
    for (i = 0; i < 3; i++) {
        cam->_0E4[i] = p[i];
        cam->_0F0[i] = p[3 + i];
        cam->_108[i] = 0.0f;
    }
    cam->_114 = p[6];
    cam->_11A = 1;
}

// .text:0x000195BC size:0x1B4 mapped:0x80658650
void fn_3_195BC(void) {
    int j;
    int i;
    inMemCamera* cam = g_pCamera;
    const int count = 10;
    f32 sp8[3];
    sp8[0] = sp8[1] = sp8[2] = 0.f;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < count; j++) {
            if (i == 1 && (&g_Ball.pastCoordinates[j].x)[i] < 1.f) {
                sp8[i] += 1.f;
            } else {
                sp8[i] += (&g_Ball.pastCoordinates[j].x)[i];
            }
        }
        sp8[i] *= (1.f / count);
    }

    cam->_0FC[0] = sp8[0];
    cam->_0FC[1] = sp8[1] * 0.85f;
    cam->_0FC[2] = sp8[2];

    if (g_pCamera->_11A == 1) {
        cam->_0F0[0] = cam->_0FC[0];
        cam->_0F0[1] = cam->_0FC[1];
        cam->_0F0[2] = cam->_0FC[2];
    } else {
        sp8[0] = (cam->_0FC[0] - cam->_0F0[0]) * 0.2f;
        sp8[1] = (cam->_0FC[1] - cam->_0F0[1]) * 0.2f;
        sp8[2] = (cam->_0FC[2] - cam->_0F0[2]) * 0.2f;
        
        VEC_ADD((Vec*)&cam->_0F0, (Vec*)&cam->_0F0, (Vec*)&sp8);
    }
}

// .text:0x000193E8 size:0x1D4 mapped:0x8065847C
void fn_3_193E8(void) {
    inMemCamera* cam = g_pCamera;
    f32* f = lbl_3_data_1348[g_pCamera->_11C];
    f32 d = dolsqrtf2(SQ(g_pCamera->_0F0[0] - g_pCamera->_0E4[0]) + SQ(g_pCamera->_0F0[2] - g_pCamera->_0E4[2]));
    f32 x;
    f32 y;
    f32 d2;

    if (d < f[10]) {
        d = f[10];
    }
    if (d > f[11]) {
        d = f[11];
    }

    d = (d - f[10]) / (f[11] - f[10]);
    if (g_Ball.fielderWBallIndex >= 0) {
        x = f[8];
        y = f[9];
    } else {
        x = f[6];
        y = f[7];
    }

    d2 = d * (y - x) + x;
    if (g_pCamera->_11A == 1) {
        cam->_114 = d2;
    } else {
        d = d2 - cam->_114;
        d *= (1 / 10.f);
        cam->_114 += d;
    }
}

// .text:0x00018FF8 size:0x3F0 mapped:0x8065808C
void fn_3_18FF8(void) {
    return;
}

// .text:0x0001850C size:0xAEC mapped:0x806575A0
void fn_3_1850C(void) {
    return;
}

// .text:0x00017DA0 size:0x76C mapped:0x80656E34
void fn_3_17DA0(void) {
    return;
}

// .text:0x00017B2C size:0x274 mapped:0x80656BC0
void fn_3_17B2C(void) {
    return;
}

// .text:0x00017AF0 size:0x3C mapped:0x80656B84
void fn_3_17AF0(void) {
    if (g_GameLogic.sceneID == SCENE_ID_REPLAY_LIVE_BALL) {
        fn_3_197E8();
    } else {
        fn_3_1C1B0();
    }
}

// .text:0x0001785C size:0x294 mapped:0x806568F0
void fn_3_1785C(void) {
    return;
}

// .text:0x00017804 size:0x58 mapped:0x80656898
void fn_3_17804(void) {
    g_pCamera->_2840.x = 0.0f;
    g_pCamera->_2840.y = 0.0f;
    g_pCamera->_2840.z = 0.0f;
    g_pCamera->_284C.x = 0.0f;
    g_pCamera->_284C.y = 0.0f;
    g_pCamera->_284C.z = 1.0f;
    g_pCamera->_2878 = 1.0f;
}

// .text:0x00017760 size:0xA4 mapped:0x806567F4
void fn_3_17760(void) {
    if (g_Camera._2819 == 1) {
        g_Camera._2819 = 0;
        g_Camera._2816 = lbl_3_data_16C0;
        g_Camera._2818 = 1;
        g_Camera._281A = 0;
        g_Camera._2812 = 0;
        g_Camera._2814 = 0;
    } else if (g_Camera._2819 == 2) {
        g_Camera._2819 = 0;
        g_Camera._2816 = lbl_3_data_16C0;
        g_Camera._281A = 2;
        g_Camera._2814 = 0;
    }
    if (g_Camera._2818 != 0) {
        fn_3_1731C();
    }
}

// .text:0x0001731C size:0x444 mapped:0x806563B0
void fn_3_1731C(void) {
    lbl_3_data_A40_s* r30 = &lbl_3_data_16AC[g_Camera._2810];
    if (g_Camera._2812 < S16_MAX - 1) {
        g_Camera._2812++;
    } else {
        g_Camera._2812 = S16_MAX;
    }

    if (g_Camera._2814 < S16_MAX - 1) {
        g_Camera._2814++;
    } else {
        g_Camera._2814 = S16_MAX;
    }

    {
        Vec _V;
        f32 dist = VEC_DISTANCE(&g_pCamera->_284C, &g_pCamera->_2840);
        f32 c_x;
        f32 angxRad;
        f32 angyRad = shortAngleToRad_Capped(r30->_10[1]);
        f32 f28 = COSF(angyRad) * dist;
        f32 s_x;
        _V.y = SINF(angyRad) * dist;
        angxRad = shortAngleToRad_Capped(r30->_10[0]);
        c_x = COSF(angxRad);
        s_x = SINF(angxRad);
        _V.x = c_x * f28;
        _V.z = s_x * f28;
        if (g_Camera._281A == 1) {
            VEC_COPY(&g_pCamera->_2840, &r30->_00);
            VEC_ADD(&g_pCamera->_284C, &r30->_00, &_V);
            g_pCamera->_2878 = r30->_0C;
        } else {
            Vec v;
            f32 tmp;
            f32 ratio = (f32)g_Camera._2814 / (f32)g_Camera._2816;
            if (g_Camera._281A == 2) {
                ratio = 1.f - ratio;
            }
            VEC_SUB(&v, &r30->_00, &g_pCamera->_2840);
            VEC_SCALE(&v, &v, ratio);
            VEC_ADD(&g_pCamera->_2840, &g_pCamera->_2840, &v);

            VEC_ADD(&v, &_V, &r30->_00);
            VEC_SUB(&v, &v, &g_pCamera->_284C);
            VEC_SCALE(&v, &v, ratio);
            VEC_ADD(&g_pCamera->_284C, &g_pCamera->_284C, &v);

            tmp = r30->_0C - g_pCamera->_2878;
            g_pCamera->_2878 += tmp * ratio;

            if (g_Camera._2814 >= g_Camera._2816) {
                if (g_Camera._281A == 0) {
                    g_Camera._281A = 1;
                    g_Camera._2814 = 0;
                } else {
                    g_Camera._2818 = 0;
                }
            }
        }
    }
}

// .text:0x00017110 size:0x20C mapped:0x806561A4
void fn_3_17110(void) {
    f32 _f31;
    f32 f30;
    f32 _f30;
    f32 _f29;
    f32 _f28;
    f32 _f6;
    f32 _f4;
    f32 _f3;
    f32 _f2;

    g_pCamera->_2858 = lbl_3_data_A40[87]._00.x;
    g_pCamera->_285C = lbl_3_data_A40[87]._00.y;
    g_pCamera->_2860 = lbl_3_data_A40[87]._00.z;
    g_pCamera->_289C = lbl_3_data_A40[87]._10[0];
    g_pCamera->_289E = lbl_3_data_A40[87]._10[1];
    g_pCamera->_2878 = lbl_3_data_A40[87]._0C;

    _f30 = shortAngleToRad_Capped(g_pCamera->_289E);
    f30 = COSF(_f30) * 20.f;
    _f29 = SINF(_f30);

    _f28 = shortAngleToRad_Capped(g_pCamera->_289C);
    _f31 = COSF(_f28);
    _f6 = SINF(_f28);
    
    _f4 = _f31 * f30;
    _f2 = _f6 * f30;
    _f3 = _f29 * 20.f;
    g_pCamera->_2890 = g_pCamera->_2840.x;
    g_pCamera->_2894 = g_pCamera->_2840.y;
    g_pCamera->_2898 = g_pCamera->_2840.z;

    g_pCamera->_2858 += _f31 * g_pCamera->_287C;
    g_pCamera->_2860 += _f6 * g_pCamera->_287C;

    g_pCamera->_2858 += _f6 * g_pCamera->_2880;
    g_pCamera->_2860 -= _f31 * g_pCamera->_2880;

    g_pCamera->_284C.x = _f4 + g_pCamera->_2858;
    g_pCamera->_284C.y = _f3 + g_pCamera->_285C;
    g_pCamera->_284C.z = _f2 + g_pCamera->_2860;

    g_pCamera->_2840.x = g_pCamera->_2858;
    g_pCamera->_2840.y = g_pCamera->_285C;
    g_pCamera->_2840.z = g_pCamera->_2860;
    g_pCamera->_287C = 0.0f;
    g_pCamera->_2880 = 0.0f;
}

// .text:0x00016F04 size:0x20C mapped:0x80655F98
void fn_3_16F04(void) {
    if (g_GameLogic.bOD_framesInLiveBallScene < 0) {
        g_GameLogic.bOD_framesInLiveBallScene = 0;
    }
    if (g_GameLogic.bOD_framesInLiveBallScene < S16_MAX - 1) {
        g_GameLogic.bOD_framesInLiveBallScene++;
    } else {
        g_GameLogic.bOD_framesInLiveBallScene = S16_MAX;
    }
    // TODO: figure out how this first func is not inlined but the second is
    fn_3_16D6C();
    fn_3_16BA0();
}

#pragma dont_inline on
// .text:0x00016D6C size:0x198 mapped:0x80655E00
void fn_3_16D6C(void) {
    if (g_Minigame.bOD_hitFinishedInd != 0) {
        VEC_SCALE(&g_pCamera->_2884, &g_pCamera->_2884, 0.95f);
        VEC_ADD(&g_pCamera->_284C, &g_pCamera->_284C, &g_pCamera->_2884);
    } else {
        Vec v;
        Vec b;
        VEC_COPY(&g_pCamera->_2884, &g_pCamera->_284C);
        VEC_COPY(&b, &g_Ball.AtBat_Contact_BallPos);

        b.y *= 0.75f;
        
        if (b.y < 0) {
            b.y = 0.f;
        }

        VEC_COPY(&v, &g_pCamera->_284C);
        VEC_SCALE(&v, &v, 9.f);

        g_pCamera->_284C.x = (b.x + v.x) * 0.1f;
        g_pCamera->_284C.y = (b.y + v.y) * 0.1f;
        g_pCamera->_284C.z = (b.z + v.z) * 0.1f;

        VEC_SUB(&g_pCamera->_2884, &g_pCamera->_284C, &g_pCamera->_2884);
    }
}
#pragma dont_inline reset

// .text:0x00016BA0 size:0x1CC mapped:0x80655C34
void fn_3_16BA0(void) {
    f32 x, z;
    f32 _x,  _z;
    f32 d;
    if (g_pCamera->_2840.y > 2.f) {
        g_pCamera->_2840.y *= (1.f - (1.f / 200));
    }
    getComponentsFromSAng(g_Ball.Hit_HorizontalAngle, &x, &z);
    d = dolsqrtf2(SQ(g_pCamera->_2840.x) + SQ(g_pCamera->_2840.z));
    x *= -d;
    z *= -d;
    _x = x;
    _z = z;
    
    _x -= g_pCamera->_2840.x;
    _z -= g_pCamera->_2840.z;
    _x *= (1.f / 200);
    _z *= (1.f / 200);
    g_pCamera->_2840.x += _x;
    g_pCamera->_2840.z += _z;
}

// .text:0x00016900 size:0x2A0 mapped:0x80655994
void fn_3_16900(void) {
    return;
}

// .text:0x000166F4 size:0x20C mapped:0x80655788
void fn_3_166F4(void) {
    f32 _f31;
    f32 f30;
    f32 _f30;
    f32 _f29;
    f32 _f28;
    f32 _f6;
    f32 _f4;
    f32 _f3;
    f32 _f2;

    g_pCamera->_2858 = lbl_3_data_A40[88]._00.x;
    g_pCamera->_285C = lbl_3_data_A40[88]._00.y;
    g_pCamera->_2860 = lbl_3_data_A40[88]._00.z;
    g_pCamera->_289C = lbl_3_data_A40[88]._10[0];
    g_pCamera->_289E = lbl_3_data_A40[88]._10[1];
    g_pCamera->_2878 = lbl_3_data_A40[88]._0C;

    _f30 = shortAngleToRad_Capped(g_pCamera->_289E);
    f30 = COSF(_f30) * 20.f;
    _f29 = SINF(_f30);

    _f28 = shortAngleToRad_Capped(g_pCamera->_289C);
    _f31 = COSF(_f28);
    _f6 = SINF(_f28);
    
    _f4 = _f31 * f30;
    _f2 = _f6 * f30;
    _f3 = _f29 * 20.f;
    g_pCamera->_2890 = g_pCamera->_2840.x;
    g_pCamera->_2894 = g_pCamera->_2840.y;
    g_pCamera->_2898 = g_pCamera->_2840.z;

    g_pCamera->_2858 += _f31 * g_pCamera->_287C;
    g_pCamera->_2860 += _f6 * g_pCamera->_287C;

    g_pCamera->_2858 += _f6 * g_pCamera->_2880;
    g_pCamera->_2860 -= _f31 * g_pCamera->_2880;

    g_pCamera->_284C.x = _f4 + g_pCamera->_2858;
    g_pCamera->_284C.y = _f3 + g_pCamera->_285C;
    g_pCamera->_284C.z = _f2 + g_pCamera->_2860;

    g_pCamera->_2840.x = g_pCamera->_2858;
    g_pCamera->_2840.y = g_pCamera->_285C;
    g_pCamera->_2840.z = g_pCamera->_2860;
    g_pCamera->_287C = 0.0f;
    g_pCamera->_2880 = 0.0f;
}

// .text:0x0001650C size:0x1E8 mapped:0x806555A0
BOOL fn_3_1650C(int* outX, int* outY, BOOL behindCameraOK, f32 pX, f32 pY, f32 pZ) {
    Mtx44 frust;
    f32 proj[7];
    f32 viewport[6];
    Vec posInCam;
    f32 x, y, z;
    f32 f28 = 1.f / fn_80052768_getCamera(0)->zoom;
    posInCam.x = pX;
    posInCam.y = pY;
    posInCam.z = pZ;
    PSMTXMultVec(fn_80052768_getCamera(0)->view, &posInCam, &posInCam);
    if (posInCam.z >= 0.f && !behindCameraOK) {
        return FALSE;
    }

    C_MTXFrustum(frust, -0.175f * f28, 0.175f * f28, 0.25f * f28, -0.25f * f28, 1.f, 512.f);
    proj[0] = 0.f;
    proj[1] = frust[0][0];
    proj[2] = frust[2][0];
    proj[3] = frust[1][1];
    proj[4] = frust[2][1];
    proj[5] = frust[2][2];
    proj[6] = frust[3][2];
    GXGetViewportv(viewport);
    GXProject(pX, pY, pZ, fn_80052768_getCamera(0)->view, proj, viewport, &x, &y, &z);
    *outX = x;
    *outY = y;
    return TRUE;
}

// .text:0x000164A8 size:0x64 mapped:0x8065553C
int fn_3_164A8(void) {
    switch (g_Minigame.GameMode_MiniGame) {
        case MINI_GAME_ID_NONE:
            return 6;
        case MINI_GAME_ID_BOBOMB_DERBY:
            return 0;
        case MINI_GAME_ID_WALLBALL:
            return 4;
        case MINI_GAME_ID_BARREL_BATTER:
            return 5;
        case MINI_GAME_ID_CHAINCHOMP_SPRINT:
            return 2;
        case MINI_GAME_ID_PIRANHA_PANIC:
            return 3;
        case MINI_GAME_ID_STAR_DASH:
            return 1;
    }
}

// .text:0x00016328 size:0x180 mapped:0x806553BC
void fn_3_16328(void) {
    GameInitVariables* settings = &g_d_GameSettings;

    if (g_GameLogic.FrameCountOfCurrentPitch <= 1) {
        if (settings->GameModeSelected == GAME_TYPE_CHALLENGE) {
            fn_3_FBDAC(settings->StadiumID + 0x39);
        } else if (settings->GameModeSelected == GAME_TYPE_MINIGAMES) {
            fn_3_FBDAC(random_fn_3_9EE24(0) + 0x24 + fn_3_164A8());
        } else if (settings->GameModeSelected == GAME_TYPE_TOY_FIELD) {
            fn_3_FBDAC(random_fn_3_9EE24(0) + 0x24 + fn_3_164A8());
        } else {
            fn_3_FBDAC(random_fn_3_9EE24(0) + 8 + settings->StadiumID);
        }
    }
    fn_3_FD670();
}

// .text:0x000161C0 size:0x168 mapped:0x80655254
void fn_3_161C0(void) {    
    if (g_GameLogic.FrameCountOfCurrentPitch == 0) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
            fn_3_FBDAC(random_fn_3_9EE24(0) + 0x2b + fn_3_164A8());
        } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            fn_3_FBDAC(random_fn_3_9EE24(0) + 0x2b + fn_3_164A8());
        } else {
            fn_3_FBDAC(random_fn_3_9EE24(0) + 0xf + g_d_GameSettings.StadiumID);
        }
    }
    fn_3_FD670();
}

// .text:0x00016058 size:0x168 mapped:0x806550EC
void fn_3_16058(void) {
    if (g_GameLogic.FrameCountOfCurrentPitch <= 1) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
            fn_3_FBDAC(random_fn_3_9EE24(0) + 0x32 + fn_3_164A8());
        } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            fn_3_FBDAC(random_fn_3_9EE24(0) + 0x32 + fn_3_164A8());
        } else {
            fn_3_FBDAC(random_fn_3_9EE24(0) + 0x16 + g_d_GameSettings.StadiumID);
        }
    }
    fn_3_FD670();
}

// .text:0x00016034 size:0x24 mapped:0x806550C8
void fn_3_16034(void) {
    fn_3_FBDAC(0x68);
}

// .text:0x00016014 size:0x20 mapped:0x806550A8
void fn_3_16014(void) {
    fn_3_FD670();
}

// .text:0x00015FF0 size:0x24 mapped:0x80655084
void fn_3_15FF0(void) {
    fn_3_FBDAC(0x69);
}

// .text:0x00015FD0 size:0x20 mapped:0x80655064
void fn_3_15FD0(void) {
    fn_3_FD670();
}

// .text:0x00015F94 size:0x3C mapped:0x80655028
void fn_3_15F94(void) {
    fn_3_FBDAC(0x1d + random_fn_3_9EE24(0) + g_d_GameSettings.StadiumID);
}

// .text:0x00015F74 size:0x20 mapped:0x80655008
void fn_3_15F74(void) {
    fn_3_FD670();
}

// .text:0x00015F38 size:0x3C mapped:0x80654FCC
void fn_3_15F38(void) {
    if (g_pCamera->_AD8 == 1) {
        fn_3_FBE24();
    }
    fn_3_FD670();
}

// .text:0x00015F18 size:0x20 mapped:0x80654FAC
void fn_3_15F18(void) {
    fn_3_FD670();
}

// .text:0x00015D90 size:0x188 mapped:0x80654E24
void fn_3_15D90(void) {
    int i;
    g_pCamera->_AC8 = 0;
    g_pCamera->_A74 = 0;
    g_pCamera->_A76 = 0;
    g_pCamera->_A78 = 0;
    g_pCamera->_A7A = 0;
    g_pCamera->_A7C = 0;
    g_pCamera->_A7E = 0;
    g_pCamera->_A80 = 0;
    g_pCamera->_A82 = 0;
    for (i = 0; i < 4; i++) {
        g_pCamera->_A84[i] = 0;
    }
    g_pCamera->_AA6 = -1;
    g_pCamera->_A50 = -1;
    g_pCamera->_AB5 = 0;
    g_pCamera->_AB6 = 0;
    g_pCamera->_AB7 = 0;
    g_pCamera->_AB8 = 0;
    g_pCamera->_AC6 = 0;
    g_pCamera->_AB9 = 0;
    g_pCamera->_ABA = 0;
    g_pCamera->_AC4 = 0;
    g_pCamera->_ACA = 0;

    for (i = 0; i < 4; i++) {
        g_pCamera->_ABB[i] = 0;
        g_pCamera->_A8C[i] = 0;
        g_pCamera->_AC0[i] = 0;
    }

    g_pCamera->_A9E = -1;
    g_pCamera->_AA0 = -1;
    g_pCamera->_AA2 = -1;

    g_pCamera->_AD8 = 0;
    g_pCamera->_A94 = 0;
    g_pCamera->_ABF = 0;
    g_pCamera->_A96 = 0;
    g_pCamera->_A98 = 0;
    g_pCamera->_A9C = 0;
    g_pCamera->_AA4 = 0;
    g_pCamera->_A9A = -1;
}

// .text:0x00015D7C size:0x14 mapped:0x80654E10
void fn_3_15D7C(u8 b) {
    g_pCamera->_AC5 = b;
}

// .text:0x00015D64 size:0x18 mapped:0x80654DF8
void fn_3_15D64(void) {
    g_pCamera->_AD8 = 1;
}

// .text:0x00015D28 size:0x3C mapped:0x80654DBC
void fn_3_15D28(void) {
    if (g_pCamera->_AD8 == 1) {
        fn_3_FBE24();
    }
    fn_3_FD670();
}

// .text:0x00015A98 size:0x290 mapped:0x80654B2C
void fn_3_15A98(void) {
    return;
}

// .text:0x00015524 size:0x574 mapped:0x806545B8
void fn_3_15524(void) {
    return;
}

// .text:0x000154C4 size:0x60 mapped:0x80654558
void fn_3_154C4(int arg) {
    if (g_Pitcher.windupCountdownUntilBallReleased == 1) {
        if (arg == 0) {
            g_pCamera->_AB4 = 1;
        } else if (g_Stats.replayInd == 0) {
            g_pCamera->_A74 = g_Stats.playFrameCounter;
        }
    }
}

// .text:0x00015458 size:0x6C mapped:0x806544EC
void fn_3_15458(int arg) {
    if (g_Batter.swingInd != 0 && g_Batter.framesSinceStartOfSwing == 1) {
        if (arg == 0) {
            g_pCamera->_AB5 = 1;
        } else if (g_Stats.replayInd == 0) {
            g_pCamera->_A76 = g_Stats.playFrameCounter;
        }
    }
}

// .text:0x000153F0 size:0x68 mapped:0x80654484
void fn_3_153F0(int arg) {
    if (g_Batter.swingInd != 0 && g_Batter.contactMadeInd == 1) {
        if (arg == 0) {
            g_pCamera->_AB6 = 1;
        } else if (g_pCamera->_A78 == 0) {
            g_pCamera->_A78 = g_Stats.playFrameCounter;
        }
    }
}

// .text:0x0001537C size:0x74 mapped:0x80654410
void fn_3_1537C(int arg) {
    if (g_Batter.hitTrajectory != HIT_TRAJECTORY_0) {
        g_pCamera->_A7C++;
    }
    if (g_pCamera->_A7C > 40){        
        if (arg == 0) {
            g_pCamera->_AB7 = 1;
        } else if (g_pCamera->_A7A == 0) {
            g_pCamera->_A7A = g_Stats.playFrameCounter;
        }
    }
}

// .text:0x000152E8 size:0x94 mapped:0x8065437C
void fn_3_152E8(int arg) {
    if (g_Ball.deadBallReason != 0) {
        g_pCamera->_AB8 = 1;
        g_pCamera->_AC6 = g_Ball.deadBallReason;
    }
    if (g_Ball.deadBallReason == 1){        
        if (arg == 0) {
            g_pCamera->_AB8 = 1;
            g_pCamera->_AC6 = g_Ball.deadBallReason;
        } else if (g_pCamera->_A7E == 0) {
            g_pCamera->_A7E = g_Stats.playFrameCounter;
        }
    }
}

// .text:0x0001527C size:0x6C mapped:0x80654310
void fn_3_1527C(int arg) {
    if (g_Ball.ballState == BALL_STATE_HELD) {        
        if (arg == 0) {
            g_pCamera->_AB9 = 1;
        } else if (g_pCamera->_A80 == 0) {
            g_pCamera->_A9A = g_Ball.fielderWBallIndex;
            g_pCamera->_A80 = g_Stats.playFrameCounter;
        }
    }
}

// .text:0x00015220 size:0x5C mapped:0x806542B4
void fn_3_15220(int arg) {
    if (g_FieldingLogic._13F != 0) {
        if (arg == 0) {
            g_pCamera->_ABA = 1;
        } else if (g_pCamera->_A82 == 0) {
            g_pCamera->_A82 = g_Stats.playFrameCounter;
        }
    }
}

// .text:0x00015144 size:0xDC mapped:0x806541D8
void fn_3_15144(int arg) {
    int i;
    for (i = 0; i < ARRAY_SIZE(g_Runners); i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored != 1 && g_Runners[i].runnerOnFieldOrOutOrScored != 2 &&
            g_Runners[i].runnerOnFieldOrOutOrScored != 4) {
            break;
        }

        if (g_Runners[i].groundVelocity[0] > 0.0f &&
            (int)g_Runners[i].fractionalBasesRan > (int)g_Runners[i].fractionalBasesRan_stored) {
            if (arg == 0) {
                g_pCamera->_ABB[i] = 1;
            } else if (g_pCamera->_ABB[i] == 0) {
                g_pCamera->_A84[i] = g_Stats.playFrameCounter;
            }
        }
    }
}

// .text:0x000150C0 size:0x84 mapped:0x80654154
void fn_3_150C0(void) {
    int i;
    for (i = 0; i < ARRAY_SIZE(g_Runners); i++) {
        if (g_Runners[i].baseStandingOn == 3) {
            g_pCamera->_A8C[i] = g_Stats.playFrameCounter;
        }
    }
}

// .text:0x00015004 size:0xBC mapped:0x80654098
void fn_3_15004(void) {
    int i;
    for (i = 0; i < ARRAY_SIZE(g_Runners); i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 3 && g_pCamera->_AC0[i] == 0) {
            g_pCamera->_ABF = i;
            g_pCamera->_AC0[i] = 1;
            g_pCamera->_A94 = g_Stats.playFrameCounter;
        }
    }
}

// .text:0x00014FC8 size:0x3C mapped:0x8065405C
void fn_3_14FC8(void) {
    if (lbl_3_common_bss_32A94._4 == 0xe && g_pCamera->_A96 == 0) {
        g_pCamera->_A96 = g_Stats.playFrameCounter;
    }
}

// .text:0x00014F68 size:0x60 mapped:0x80653FFC
void fn_3_14F68(void) {
    if (g_FieldingLogic._133 != 2) {
        return;
    }
    if (g_pCamera->_AC4 != 0) {
        return;
    }
    g_pCamera->_AC4 = g_FieldingLogic._114;
    g_pCamera->_A9A = g_Ball.fielderWBallIndex;
    g_pCamera->_A98 = g_Stats.playFrameCounter;
}
// .text:0x00014F24 size:0x44 mapped:0x80653FB8
void fn_3_14F24(void) {
    if (lbl_3_common_bss_32A94._2 >= 36 && lbl_3_common_bss_32A94._2 <= 38 && g_pCamera->_A9C == 0) {
        g_pCamera->_A9C = g_Stats.playFrameCounter;
    }
}
// .text:0x00014EE8 size:0x3C mapped:0x80653F7C
void fn_3_14EE8(void) {
    if (g_Batter.contactMadeInd == 1 && g_pCamera->_AA6 == -1) {
        g_pCamera->_AA6 = g_Ball.Hit_HorizontalAngle;
    }
}

// .text:0x00014EC0 size:0x28 mapped:0x80653F54
void fn_3_14EC0(void) {
    if (g_pCamera->_A50 == -1) {
        g_pCamera->_A50 = g_Strikes.storedOuts;
    }
}

// .text:0x00014E84 size:0x3C mapped:0x80653F18
void fn_3_14E84(void) {
    if (g_FieldingLogic._133 == 2 && g_pCamera->_AA4 == 0) {
        g_pCamera->_AA4 = g_Stats.playFrameCounter;
    }
}

// .text:0x00014E50 size:0x34 mapped:0x80653EE4
void fn_3_14E50(void) {
    lbl_3_bss_44 = 5;
    
    fn_800528AC(&fn_3_14BB4);
}

// .text:0x00014E1C size:0x34 mapped:0x80653EB0
void fn_3_14E1C(void) {
    lbl_3_bss_44 = 0;

    fn_800528AC(NULL);
}

// .text:0x00014BB4 size:0x268 mapped:0x80653C48
void fn_3_14BB4(camera_803c639c_s* arg) {
    if (lbl_3_bss_44 == 0) {
        lbl_3_bss_44 = 0;
        fn_3_14E1C();
        return;
    } else {
        Mtx sp14;
        Vec sp8;
        sp8.x = ((rand() / 32767.f) * 0.02 + 0.02) * (-(rand() % 2 * 2) + 1);
        sp8.y = ((rand() / 32767.f) * 0.05 + 0.05) * (-(rand() % 2 * 2) + 1);
        sp8.z = ((rand() / 32767.f) * 0.0f + 0.0f) * (-(rand() % 2 * 2) + 1);
        PSMTXInverse(arg->view, sp14);
        PSMTXMultVecSR(sp14, &sp8, &sp8);
        lbl_3_bss_44--;
    }
}
