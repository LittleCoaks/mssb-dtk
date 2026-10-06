#define SQRT2_LINKAGE static
#include "game/hud/rep_4138.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/gx.h"
#include "Dolphin/stl.h"
#define REP_HEADER_DATA_FN getRepHeaderData_rep4138
#include "header_rep_data.h"

extern f32 lbl_3_data_2A448[12];
extern f32 lbl_3_data_2A478[8];
extern void fn_80033B58(void*, int, int, int);
extern void fn_800A7D4C(int, void*);
extern u8 drawStadiumRelated;
extern volatile u8 hugeAnimStruct[];
extern u8 lbl_3_data_2A498[2][8];

static const u32 lbl_3_rodata_4188 = 0xffffffff;
static const f32 lbl_3_rodata_418C = 50.0f;
extern const f32 lbl_3_rodata_4190;
static const f64 lbl_3_rodata_4198 = 4503601774854144.0;
static const f32 lbl_3_rodata_41A0 = -15.438f;
static const f32 lbl_3_rodata_41A4 = -12.96f;
static const f32 lbl_3_rodata_41A8 = -10.878f;
static const f32 lbl_3_rodata_41AC = -6.318f;
static const f32 lbl_3_rodata_41B0 = -9.0f;
static const f32 lbl_3_rodata_41B4 = 1.8f;

static s32 lbl_3_bss_D6F0[9];
static u8 lbl_3_bss_D6EC;
static s32 objOrTextureCount;
static void* lbl_3_bss_D6E4;
static u8 lbl_3_bss_D6E0;

#define DRAW_SCORE_DIGIT(width, x, y) do { \
    GXColor color = *(GXColor*)&lbl_3_rodata_4188; \
    GXBegin(GX_QUADS, GX_VTXFMT0, 4); \
    GXPosition3f32(x + lbl_3_data_2A448[0], y + lbl_3_data_2A448[1], lbl_3_data_2A448[2]); \
    GXColor1u32(*(u32*)&color); \
    GXTexCoord2f32(width + lbl_3_data_2A478[0], lbl_3_data_2A478[1]); \
    GXPosition3f32(x + lbl_3_data_2A448[3], y + lbl_3_data_2A448[4], lbl_3_data_2A448[5]); \
    GXColor1u32(*(u32*)&color); \
    GXTexCoord2f32(width + lbl_3_data_2A478[2], lbl_3_data_2A478[3]); \
    GXPosition3f32(x + lbl_3_data_2A448[6], y + lbl_3_data_2A448[7], lbl_3_data_2A448[8]); \
    GXColor1u32(*(u32*)&color); \
    GXTexCoord2f32(width + lbl_3_data_2A478[4], lbl_3_data_2A478[5]); \
    GXPosition3f32(x + lbl_3_data_2A448[9], y + lbl_3_data_2A448[10], lbl_3_data_2A448[11]); \
    GXColor1u32(*(u32*)&color); \
    GXTexCoord2f32(width + lbl_3_data_2A478[6], lbl_3_data_2A478[7]); \
} while (0)

// .text:0x0016D810 size:0x1A0 mapped:0x807AC8A4
void fn_3_16D810(int digit, f32 x, f32 y) {
    f32 width = (f32)digit * lbl_3_rodata_418C * lbl_3_rodata_4190;
    DRAW_SCORE_DIGIT(width, x, y);
}

// .text:0x0016D9B0 size:0x1BC mapped:0x807ACA44
void fn_3_16D9B0(void) {
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_DISABLE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_DISABLE, GX_TEVPREV);
    GXLoadPosMtxImm(fn_80052768_getCamera(returnsCurrentMode())->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768_getCamera(returnsCurrentMode())->proj, GX_PERSPECTIVE);
    fn_80033B58(lbl_3_bss_D6E4, objOrTextureCount, 0, 0);
}

// .text:0x0016DB6C size:0x458 mapped:0x807ACC00
void fn_3_16DB6C(u8 digit) {
    f32 x;
    f32 y;
    int value;
    switch (digit) {
    case 0:
        x = lbl_3_rodata_41A0;
        y = lbl_3_rodata_41A4;
        value = lbl_3_bss_D6F0[0];
        break;
    case 1:
        x = lbl_3_rodata_41A8;
        y = lbl_3_rodata_41A4;
        value = lbl_3_bss_D6F0[2];
        break;
    case 2:
        x = lbl_3_rodata_41AC;
        y = lbl_3_rodata_41A4;
        value = lbl_3_bss_D6F0[1];
        break;
    case 3:
        x = lbl_3_rodata_41A0;
        y = lbl_3_rodata_41B0;
        value = lbl_3_bss_D6F0[4];
        break;
    case 4:
        x = lbl_3_rodata_41A8;
        y = lbl_3_rodata_41B0;
        value = lbl_3_bss_D6F0[3];
        break;
    case 5:
        x = lbl_3_rodata_41AC;
        y = lbl_3_rodata_41B0;
        value = lbl_3_bss_D6F0[5];
        break;
    default:
        return;
    }
    if ((value % 100) / 10 != 0) {

    f32 width = (f32)((value % 100) / 10) * lbl_3_rodata_418C * lbl_3_rodata_4190;
    DRAW_SCORE_DIGIT(width, x, y);
    }
    x += lbl_3_rodata_41B4;
    {
    f32 width = (f32)(value % 10) * lbl_3_rodata_418C * lbl_3_rodata_4190;
    DRAW_SCORE_DIGIT(width, x, y);
    }
}

// .text:0x0016DFC4 size:0x1DC mapped:0x807AD058
void fn_3_16DFC4(void) {
    u32 i;
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_DISABLE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_DISABLE, GX_TEVPREV);
    GXLoadPosMtxImm(fn_80052768_getCamera(returnsCurrentMode())->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768_getCamera(returnsCurrentMode())->proj, GX_PERSPECTIVE);
    fn_80033B58(lbl_3_bss_D6E4, objOrTextureCount, 0, 0);
    for (i = 0; i < 6; i++) {
        fn_3_16DB6C(i);
    }
}

// .text:0x0016E1A0 size:0x4C mapped:0x807AD234
void fn_3_16E1A0(void) {
    lbl_3_bss_D6F0[0] = g_Scores.scores[1].total;
    lbl_3_bss_D6F0[1] = g_Scores.scores[0].total;
    lbl_3_bss_D6F0[2] = g_Scores.Inning;
    lbl_3_bss_D6F0[3] = g_Strikes.strikes;
    lbl_3_bss_D6F0[4] = g_Strikes.balls;
    lbl_3_bss_D6F0[5] = g_Strikes.outs;
}

// .text:0x0016E1EC size:0x110 mapped:0x807AD280
void animateScoreBoard(void) {
    if ((hugeAnimStruct[0x3088] == FALSE) | (*(u32*)&lbl_3_bss_D6E4 == 0) | lbl_3_bss_D6EC) {
        lbl_3_bss_D6E4 = NULL;
        objOrTextureCount = -1;
        lbl_3_bss_D6EC = FALSE;
        removeCurrentDrawingItem();
    }
    if ((g_GameLogic.gameStatus != GAME_STATUS_HOMERUN_END) &
        (g_GameLogic.gameStatus != GAME_STATUS_HOMERUN_LAP)) {
        fn_3_16E1A0();
    }
    fn_800A7D4C(1, lbl_3_data_2A498[drawStadiumRelated]);
}

// .text:0x0016E2FC size:0x2C mapped:0x807AD390
void fn_3_16E2FC(void* texture, int subTexture) {
    if (texture == NULL) {
        return;
    }
    if ((int)*(u16*)texture - 1 < subTexture) {
        return;
    }
    lbl_3_bss_D6E4 = texture;
    objOrTextureCount = subTexture;
}

// .text:0x0016E328 size:0x10 mapped:0x807AD3BC
void fn_3_16E328(void) {
    lbl_3_bss_D6EC = TRUE;
}

// .text:0x0016E338 size:0x6C mapped:0x807AD3CC
void animateScoreBoardCheck(void* texture, int subTexture) {
    if (texture != NULL && (int)*(u16*)texture - 1 >= subTexture) {
        lbl_3_bss_D6E4 = texture;
        objOrTextureCount = subTexture;
        lbl_3_bss_D6EC = FALSE;
        memset(lbl_3_bss_D6F0, 0, 0x18);
        insertGraphicDrawingFunction(animateScoreBoard, 5);
    }
}


const f32 lbl_3_rodata_4190 = 0.001953125f;
