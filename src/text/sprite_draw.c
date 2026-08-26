#include "text/sprite_draw.h"
#include "text/text_channel.h"
#include "Dolphin/mtx.h"
#include "Unknown/File_0x800b1314.h"
#include "Unknown/File_0x800b1350.h"
#include "Unknown/File_0x800b2160.h"

extern f32 lbl_803CBBDC;
extern f32 lbl_803CBBE0;
extern f32 lbl_803CC490; // 0.0f
extern f32 lbl_803CC4A8; // 1.0f

void drawTransformedSprite(s32 x, s32 y, u16 s, u16 t, u16 w, u32 color, s32 style, MtxPtr mtx) {
    Quaternion c3;
    Quaternion c2;
    Quaternion c1;
    Quaternion c0;
    Mtx trans;
    Mtx m;
    SpriteVertex vtx[4];
    Vec* p1;
    Vec* p2;
    Vec* p3;
    s32 h;

    h = 0x16;
    setTextRenderingMode(1);
    if (style >= 10) {
        h = 0x14;
        w = 0x1C;
    } else if (style == 3) {
        h = 0x16;
    } else if (style == 2) {
        h = 0x12;
    } else if (style == 1) {
        h = 0x12;
    }

    if (mtx != NULL) {
        PSMTXTrans(trans, x, y, lbl_803CC490);
        PSMTXConcat(mtx, trans, m);
    } else {
        PSMTXTrans(trans, x - 320, y - 224, lbl_803CC490);
    }

    c0.x = lbl_803CC490;
    c0.y = lbl_803CC490;
    c1.x = c0.x + w;
    c1.y = c0.y;
    c2.x = c0.x;
    c2.y = c0.y + h;
    c3.x = c1.x;
    c3.y = c2.y;
    c0.z = c1.z = c2.z = c3.z = lbl_803CC490;
    p1 = (Vec*)&c1;
    p2 = (Vec*)&c2;
    p3 = (Vec*)&c3;

    if (mtx == NULL) {
        f32 k = lbl_803CBBE0 / lbl_803CBBDC;
        PSMTXScale(m, k, k, lbl_803CC4A8);
        PSMTXConcat(m, trans, m);
    }

    PSMTXMultVec(m, (Vec*)&c0, (Vec*)&c0);
    PSMTXMultVec(m, p1, p1);
    PSMTXMultVec(m, p2, p2);
    PSMTXMultVec(m, p3, p3);

    vtx[0].pos.x = c0.x;
    vtx[0].pos.y = c0.y;
    vtx[1].pos.x = c2.x;
    vtx[1].pos.y = c2.y;
    vtx[2].pos.x = c3.x;
    vtx[2].pos.y = c3.y;
    vtx[3].pos.x = c1.x;
    vtx[3].pos.y = c1.y;
    if (mtx != NULL) {
        vtx[0].pos.z = c0.z;
        vtx[1].pos.z = c2.z;
        vtx[2].pos.z = c3.z;
        vtx[3].pos.z = c1.z;
    } else {
        vtx[0].pos.z = vtx[1].pos.z = vtx[2].pos.z = vtx[3].pos.z = -lbl_803CBBE0;
    }
    vtx[0].color = vtx[1].color = vtx[2].color = vtx[3].color = color;

    if (style < 10) {
        u8 sx = screenTextArray.texCoordScaleX;
        u8 sy = screenTextArray.texCoordScaleY;
        s = s * sx;
        t = t * sy;
        w = w * sx;
        h = h * sy;
    }

    vtx[0].s = vtx[1].s = s;
    vtx[2].s = vtx[3].s = s + w;
    vtx[0].t = vtx[3].t = t;
    vtx[1].t = vtx[2].t = t + h;

    if (style >= 10) {
        vtx[0].s = vtx[1].s = 0;
        vtx[2].s = vtx[3].s = 0x400;
        vtx[0].t = vtx[3].t = 0;
        vtx[1].t = vtx[2].t = 0x400;
        DrawSprite_TexObj(vtx, screenTextArray.textBanks[style + 2], 0x400);
    } else if (style == 3) {
        renderSprite(vtx, screenTextArray.textBanks[11], 0x400, 0x400);
    } else if (style == 2) {
        renderSprite(vtx, screenTextArray.textBanks[10], 0x400, 0x400);
    } else if (style == 1) {
        renderSprite(vtx, screenTextArray.textBanks[9], 0x400, 0x400);
    } else {
        renderSprite(vtx, screenTextArray.textBanks[8], 0x400, 0x400);
    }
}
