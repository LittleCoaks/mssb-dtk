#include <string.h>
#include "Unknown/File_0x8000d164.h"
#include "Unknown/File_0x8000d838.h"
#include "Unknown/File_0x8000a1e8.h"

typedef struct UIKeyEntry {
    /* 0x0 */ u16 key;
    /* 0x2 */ u16 value;
    /* 0x4 */ u8 payload[8];
} UIKeyEntry; // size 0xC

typedef struct UIPartHeader {
    /* 0x0 */ u16 count;
    /* 0x2 */ u16 subSize;
} UIPartHeader;

typedef struct UIPartList {
    /* 0x0 */ u32 count;
    /* 0x4 */ u32 unk4;
    /* 0x8 */ UIPartHeader* parts[1];
} UIPartList;

typedef struct UIAnimRecord {
    /* 0x00 */ u8 kind;        // hi nibble: text rendering mode; lo nibble: draw op
    /* 0x01 */ u8 flags;       // bits 0x20 / 0x08 / 0x04 are tested
    /* 0x02 */ u16 elementIndex;
    /* 0x04 */ u8 unk04[8];
    /* 0x0C */ u16 key;
    /* 0x0E */ u8 unk0E[6];
    /* 0x14 */ s16 x;
    /* 0x16 */ s16 y;
    /* 0x18 */ u8 unk18[0x10];
} UIAnimRecord; // size 0x28

typedef struct UIDrawBlock {
    /* 0x00 */ f32 mtxRows[2][4];
    /* 0x20 */ u32 colors[4];
    /* 0x30 */ f32 extraF;
    /* 0x34 */ u16 extraH;
    /* 0x36 */ u8 extraB;
} UIDrawBlock;

typedef u32 (*SpriteCallback)(u8* sprite);

extern u8 lbl_80366188[]; // SpriteRectBuf, see File_0x8000e900.c
extern u32 lbl_803CBBD8;
extern f32 lbl_803CC458;
extern f32 lbl_803CC47C;
extern f32 lbl_803CC484;

u32 fn_8000AF1C(void* mtxA, void* block, UIAnimRecord* rec, UIAnimRecord* next, u32 unkC, s16* bezierOut, f32 t);
void fn_8000E7BC(UIAnimRecord* rec, void* mtxA, void* block, u32 arg4);
void fn_8000E2D4(UIAnimRecord* rec, void* mtxA, void* block);
void fn_8000DC9C(UIAnimRecord* rec, void* mtxA, void* block);
void fn_8000EC0C(UIAnimRecord* rec, TextureHeader* textures, void* mtxA, void* block, u32 arg4);
void fn_800B1388(u8* sprite);
void DrawSprite_TexObj(u8* sprite, u32 texObj);
void setTextRenderingMode(s32 mode);

s32 triggerDefaultHUDAction(u32* frame, struct UILayout* layout, int elementIndex, Mtx mtx, u32 arg4, u32 arg5, u32* arg6, TextureHeader* textures) {
    s32 rc = 0;
    u8* sprite = lbl_80366188;
    Mtx mtxA;
    UIDrawBlock block;
    s16 bezierOut[8];
    u32 frameCopy;
    u32 localC;
    u32 frameVal = *frame;
    UIPartList* elem = *(UIPartList**)(layout->elementTable + elementIndex * 4 + 8);
    u32 unkC = *(u32*)((u8*)layout + 0xC);
    UIPartHeader* part0 = elem->parts[0];
    s32 partIdx;
    s32 drawRet;

    if (part0->count != 0) {
        UIKeyEntry* e = (UIKeyEntry*)((u8*)part0 + 4 + part0->count * 12);
        u32 ctr;

        for (ctr = part0->count; ctr != 0; ctr--) {
            e--;
            if (frameVal >= ((u32)e->key << 16)) {
                *arg6 = (u32)((u8*)e + 4);
                rc = e->value + 1;
                if (e->value == 0) {
                    frameVal %= (u32)e->key << 16;
                } else if (e->value == 2) {
                    u32 a = (u32)*(u16*)((u8*)e + 4) << 16;
                    u32 b = (u32)e->key << 16;
                    frameVal = a + ((frameVal - a) % (b - a));
                }
                *frame = frameVal;
                break;
            }
        }
    }

    sprite[0x7f] = 0;
    partIdx = (s32)elem->count - 1;

    do {
        UIPartHeader* part = elem->parts[partIdx];
        UIAnimRecord* base = (UIAnimRecord*)((u8*)part + 4);
        UIAnimRecord* rec;
        UIAnimRecord* last = base + part->count - 1;
        s32 idx;

        for (idx = part->count; idx != 0;) {
            idx--;
            rec = base + idx;
            if (frameVal < ((u32)rec->key << 16)) {
                last = rec;
                continue;
            }

            {
                u32 chosenKey = rec->key;
                u32 curKey = rec->key;
                s32 c;

                if ((rec->flags & 0x20) && idx != 0) {
                    UIAnimRecord* prev = rec;
                    for (c = idx; c != 0; c--) {
                        prev--;
                        if (!((c != 1) && (prev->flags & 0x20))) {
                            chosenKey = prev->key;
                        }
                    }
                }

                if ((last->kind & 0xF) == 0) {
                    last = rec;
                }
                if ((rec->kind & 0xF) == 0) {
                    goto nextPart;
                }

                {
                    u32 nextKey = last->key;
                    u32 cur = frameVal - (curKey << 16);
                    u32 span = (nextKey - curKey) << 16;
                    f32 t = lbl_803CC458;
                    s32 hi;
                    s32 lo;
                    u32* colors = block.colors;
                    u32 i;

                    if (cur < span) {
                        t = (f32)cur / (f32)span;
                    }

                    if (rec->flags & 0x08) {
                        if (idx != 0 && ((rec - 1)->flags & 0x08)) {
                            if ((rec + 1)->flags & 0x08) {
                                interpolatePointsBezier_Vec2s(bezierOut, (s16*)(rec - 1), (s16*)rec, (s16*)(rec + 1), (s16*)(rec + 2), 1, t);
                            } else {
                                interpolatePointsBezier_Vec2s(bezierOut, (s16*)(rec - 1), (s16*)(rec - 1), (s16*)rec, (s16*)(rec + 1), 2, t);
                            }
                        } else if (idx != 0) {
                            interpolatePointsBezier_Vec2s(bezierOut, (s16*)rec, (s16*)(rec + 1), (s16*)(rec + 2), (s16*)(rec + 2), 0, t);
                        } else {
                            interpolatePointsBezier_Vec2s(bezierOut, (s16*)rec, (s16*)(rec + 1), (s16*)(rec + 1), (s16*)(rec + 2), 0, t);
                        }
                    }

                    arg4 |= fn_8000AF1C(mtxA, &block, rec, last, unkC, bezierOut, t);
                    PSMTXConcat(mtx, mtxA, mtxA);

                    for (i = 0; i < 4; i++) {
                        u32 w = colors[i];
                        u32 r = ((arg5 >> 24) * (w >> 24)) / 255;
                        u32 g = (((arg5 >> 16) & 0xFF) * ((w >> 16) & 0xFF)) / 255;
                        u32 b = (((arg5 >> 8) & 0xFF) * ((w >> 8) & 0xFF)) / 255;
                        u32 a = ((arg5 & 0xFF) * (w & 0xFF)) / 255;
                        colors[i] = (r << 24) | (g << 16) | (b << 8) | a;
                    }

                    hi = (rec->kind >> 4) & 0xF;
                    if (hi == 0) {
                        setTextRenderingMode(1);
                    } else if (hi == 1) {
                        setTextRenderingMode(2);
                    } else if (hi == 2) {
                        setTextRenderingMode(3);
                    }

                    lo = rec->kind & 0xF;
                    if (lo == 1 || lo == 2) {
                        fn_8000E7BC(rec, mtxA, &block, arg4);
                        drawRet = 1;
                        if (*(SpriteCallback*)(sprite + 0x84) != NULL && (rec->flags & 0x04)) {
                            drawRet = (*(SpriteCallback*)(sprite + 0x84))(sprite);
                        }
                        if (drawRet != 0) {
                            fn_800B1388(sprite);
                        }
                    } else if (lo == 3) {
                        drawRet = 1;
                        if (*(SpriteCallback*)(sprite + 0x84) != NULL && (rec->flags & 0x04)) {
                            *(UIAnimRecord**)(sprite + 0x78) = rec;
                            *(void**)(sprite + 0x70) = NULL;
                            *(u16*)(sprite + 0x7c) = 1;
                            sprite[0x7e] = 1;
                            memcpy(sprite, mtxA, 0x30);
                            *(u32*)(sprite + 0x48) = colors[0];
                            *(u32*)(sprite + 0x4c) = colors[1];
                            *(f32*)(sprite + 0x40) = lbl_803CC484;
                            *(s16*)(sprite + 0x50) = rec->x;
                            *(f32*)(sprite + 0x44) = block.extraF;
                            *(s16*)(sprite + 0x52) = rec->y;
                            sprite[0x54] = (u8)block.extraH;
                            sprite[0x55] = block.extraB;
                            drawRet = (*(SpriteCallback*)(sprite + 0x84))(sprite);
                        }
                        if (drawRet != 0) {
                            if (lbl_803CC47C == block.extraF) {
                                fn_8000E2D4(rec, mtxA, &block);
                            } else {
                                fn_8000DC9C(rec, mtxA, &block);
                            }
                        }
                    } else if (lo == 4) {
                        fn_8000EC0C(rec, textures, mtxA, &block, arg4);
                        drawRet = 1;
                        if (*(SpriteCallback*)(sprite + 0x84) != NULL && (rec->flags & 0x04)) {
                            drawRet = (*(SpriteCallback*)(sprite + 0x84))(sprite);
                        }
                        if (drawRet != 0) {
                            DrawSprite_TexObj(sprite, lbl_803CBBD8);
                        }
                    } else if (lo == 5) {
                        frameCopy = frameVal - (chosenKey << 16);
                        localC = 0;
                        triggerDefaultHUDAction(&frameCopy, (struct UILayout*)layout, rec->elementIndex, mtxA, arg4, colors[0], &localC, textures);
                    }
                }
            }
            break;
        }

nextPart:
        partIdx--;
    } while (partIdx != 0);

    return rc;
}
