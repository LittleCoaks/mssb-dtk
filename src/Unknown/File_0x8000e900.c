#include "Unknown/File_0x8000e900.h"
#include "Unknown/File_0x8000ef1c.h"

typedef struct SpriteVertex {
    f32 pos[3];
    u32 color;
    s16 u;
    s16 v;
} SpriteVertex;

typedef struct SpriteRectBuf {
    SpriteVertex verts[4];
    u8 unk50[0x20];
    u8* base;
    u8 unk74[8];
    u16 flags;
    u8 unk7e;
    u8 unk7f[0x11];
} SpriteRectBuf;

extern u32 lbl_803CBBD8;
extern SpriteRectBuf lbl_80366188;

static void SetVertexPos(SpriteVertex* vtx, const f32* corner) {
    vtx->pos[0] = corner[0];
    vtx->pos[1] = corner[1];
    vtx->pos[2] = corner[2];
}

void SetSpriteRect(u8* sprite, u8* base, Mtx mtx, s32* vec2i, u16 flagBits) {
    f32 quad[16];
    u8* entry;
    u8* rect;
    f32 sizeX;
    f32 sizeY;
    u8 flags;
    SpriteRectBuf* buf;

    entry = base + *(u16*)(sprite + 6) * 0x20;
    rect = base + *(u16*)(entry + 0x20) * 0x20 + 4;
    lbl_803CBBD8 = (u32)rect;

    quad[0] = 0.0f;
    quad[1] = 0.0f;
    sizeX = 0.0f + (f32)*(u16*)(rect + 0xA);
    quad[3] = 0.0f;
    quad[4] = 0.0f;
    quad[2] = sizeX;
    quad[6] = sizeX;
    sizeY = 0.0f + (f32)*(u16*)(rect + 8);
    quad[5] = sizeY;
    quad[7] = sizeY;

    AddVec2iToQuad(quad, mtx, vec2i);

    buf = &lbl_80366188;
    flags = sprite[8];
    if ((flags & 0x80) && (flags & 0x40)) {
        SetVertexPos(&buf->verts[0], &quad[12]);
        SetVertexPos(&buf->verts[1], &quad[4]);
        SetVertexPos(&buf->verts[2], &quad[0]);
        SetVertexPos(&buf->verts[3], &quad[8]);
    } else if (flags & 0x80) {
        SetVertexPos(&buf->verts[0], &quad[4]);
        SetVertexPos(&buf->verts[1], &quad[12]);
        SetVertexPos(&buf->verts[2], &quad[8]);
        SetVertexPos(&buf->verts[3], &quad[0]);
    } else if (flags & 0x40) {
        SetVertexPos(&buf->verts[0], &quad[8]);
        SetVertexPos(&buf->verts[1], &quad[0]);
        SetVertexPos(&buf->verts[2], &quad[4]);
        SetVertexPos(&buf->verts[3], &quad[12]);
    } else {
        SetVertexPos(&buf->verts[0], &quad[0]);
        SetVertexPos(&buf->verts[1], &quad[8]);
        SetVertexPos(&buf->verts[2], &quad[12]);
        SetVertexPos(&buf->verts[3], &quad[4]);
    }

    buf->unk7e = 0;
    buf->verts[0].color = vec2i[8];
    buf->verts[1].color = vec2i[9];
    buf->verts[2].color = vec2i[10];
    buf->verts[3].color = vec2i[11];

    buf->verts[0].u = 0;
    buf->verts[0].v = 0;
    buf->verts[1].u = 0;
    buf->verts[1].v = 0x400;
    buf->verts[2].u = 0x400;
    buf->verts[2].v = 0x400;
    buf->verts[3].u = 0x400;
    buf->verts[3].v = 0;

    buf->base = base;
    buf->flags = flagBits | ((flags >> 5) & 1);
}
