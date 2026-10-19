#include "Unknown/File_0x80035168.h"
#include "Unknown/File_0x8000d838.h"
#include "Unknown/File_0x80009e94.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/sprt.h"
#include "text/text_draw_conditional.h"
#include "game/UnknownHomes_Game.h"

extern u8 lbl_800F78E0[0xC0];
extern u8 lbl_801F8640[0x40];
extern u8 lbl_801F8680[0x40];
extern UIRecord* lbl_803CBC9C;
extern f32 lbl_803CBBE0;
extern u8 lbl_803CBBE4;
extern f32 lbl_803CC6E8;
extern f32 lbl_803CC6EC;
extern f32 lbl_803CC6F0;
extern f32 lbl_803CC6F4;
extern f32 lbl_803CC6F8;

void fn_80034BCC(void);
void fn_8000F534(UIRecord* rec, s32 arg);
void fn_8000CC4C(void* layout, void* part, u16* override, s32 arg4, s32 arg5);
void fn_800B24D4(s32 arg);
void fn_800B27DC(void* proj, s32 arg);

void maybeProcessUIUpdates(void) {
    UIRecord* rec;
    s32 i;
    s32 j;
    s32 k;
    u16 held;
    Mtx mtxA;
    Mtx mtxB;
    u32 arg6;
    void* baseMtx;
    f32 scale;
    Vec* trans;
    TextureContainerSlot* slot;
    u32* elementTable;
    u32* element;
    u32 part;
    u32 rgba;
    u8 result;

    if (AtBat_ButtonInput1._00 & INPUT_BUTTON_START) {
        held = *(u16*)((u8*)&AtBat_ButtonInput1 + 0x64);
        if (held & 1) {
            if ((s32)uiDrawLoopEnd > (s32)uiDrawLoopStart) {
                uiDrawLoopEnd--;
            }
        } else if (held & 2) {
            if ((s32)uiDrawLoopEnd < 0x360) {
                uiDrawLoopEnd++;
            }
        }
        if (held & 4) {
            if ((s32)uiDrawLoopStart > 0) {
                uiDrawLoopStart--;
            }
        } else if (held & 8) {
            if ((s32)uiDrawLoopStart < (s32)uiDrawLoopEnd) {
                uiDrawLoopStart++;
            }
        }
    }

    fn_8000A094((u32)fn_80034BCC);

    i = (s32)uiDrawLoopStart;
    rec = &menuGraphicsStructures[i];

    for (; i < (s32)uiDrawLoopEnd; i++, rec++) {
        if (rec->flags == 0) {
            continue;
        }
        if (!(rec->flags & UI_FLAG_VISIBLE) || (rec->parent != NULL && rec->attachedThisFrame == 0)) {
            if (rec->flags & UI_FLAG_TEXT) {
                fn_8000F534(rec, 0);
            }
            continue;
        }

        fn_800B24D4(rec->layer);

        if (rec->playMode != UI_PLAY_STOP) {
            fn_800B27DC(lbl_801F8640, 0);
            fn_800B21A8(rec->unk69[8]);
            baseMtx = lbl_800F78E0;
        } else {
            fn_800B27DC(lbl_801F8680, 0);
            if (rec->layer == 0x15) {
                baseMtx = (u8*)lbl_800F78E0 + 0x90;
                lbl_803CBBE0 = lbl_803CC6EC;
                fn_800B216C(GX_TRUE, GX_LEQUAL, GX_FALSE);
            } else {
                if (rec->layer >= 0xf && rec->layer <= 0x16) {
                    lbl_803CBBE0 = lbl_803CC6F0;
                    baseMtx = (u8*)lbl_800F78E0 + 0x30;
                } else {
                    lbl_803CBBE0 = lbl_803CC6F4;
                    baseMtx = (u8*)lbl_800F78E0 + 0x60;
                }
                fn_800B21A8(rec->unk69[8]);
            }
        }

        trans = (Vec*)&rec->unkC[0x30];
        trans->x = rec->pos.x;
        trans->y = rec->pos.y;
        trans->z = rec->pos.z;

        if (rec->playMode != UI_PLAY_STOP) {
            scale = *(f32*)&rec->unk69[3];
            PSMTXScale((void*)rec->unkC, -scale, scale, lbl_803CC6F8);
            PSMTXInverse(returnFloatFromModeIndex(0)->view, mtxB);
            mtxB[0][3] = lbl_803CC6E8;
            mtxB[1][3] = lbl_803CC6E8;
            mtxB[2][3] = lbl_803CC6E8;
            PSMTXConcat(mtxB, (void*)rec->unkC, (void*)rec->unkC);
            PSMTXTrans(mtxB, trans->x, trans->y, trans->z);
            PSMTXConcat(mtxB, (void*)rec->unkC, (void*)rec->unkC);
            PSMTXConcat(returnFloatFromModeIndex(0)->view, (void*)rec->unkC, (void*)rec->unkC);
            *(u32*)rec->unk74 = rec->rgba;
        } else {
            if (rec->parent == NULL) {
                slot = &textureContainerSlots[rec->textureSlot];
                trans->x = trans->x - (f32)(((u16*)slot->layout)[0] >> 1);
                trans->y = trans->y - (f32)(((u16*)slot->layout)[1] >> 1);
                *(u32*)rec->unk74 = rec->rgba;
                PSMTXIdentity(rec->anchor);
            }
            trans->z = lbl_803CC6E8;
            PSMTXTrans((void*)rec->unkC, trans->x, trans->y, lbl_803CC6E8);
            PSMTXConcat(rec->anchor, (void*)rec->unkC, (void*)rec->unkC);
        }

        lbl_803CBBE4 = rec->playMode;
        rgba = *(u32*)rec->unk74;

        for (j = 0; j < 10; j++) {
            if (rec->textureOverride[j] != UI_NO_OVERRIDE) {
                slot = &textureContainerSlots[rec->textureSlot];
                elementTable = *(u32**)((u8*)slot->layout + 8);
                element = (u32*)elementTable[2 + rec->elementIndex];
                part = element[2 + j];
                fn_8000CC4C(slot->layout, (void*)part, &rec->textureOverride[j], 6, 2);
            }
        }

        if (rec->parent == NULL) {
            PSMTXConcat(baseMtx, (void*)rec->unkC, mtxA);
        } else {
            PSMTXCopy((void*)rec->unkC, mtxA);
        }

        lbl_803CBC9C = rec;
        if (!(rec->flags & UI_FLAG_TEXT)) {
            slot = &textureContainerSlots[rec->textureSlot];
            result = handleUIAction(&rec->frame, slot->layout, rec->elementIndex, mtxA, 0, rgba, &arg6,
                                    slot->textures);
            rec->unk69[0] = result;
        }

        rec->attachedThisFrame = 0;
        if (rec->playMode == UI_PLAY_FORWARD) {
            result = rec->unk69[0];
            if (result == 1) {
                rec->frame = 0;
            } else if (result != 2 && result != 3) {
                rec->frame += rec->rate;
            }
        } else if (rec->playMode == UI_PLAY_BACKWARD) {
            if (rec->frame > rec->rate) {
                rec->frame -= rec->rate;
            } else {
                rec->frame = 0;
            }
        }

        if (rec->flags & UI_FLAG_TEXT) {
            fn_8000F534(rec, 1);
        }
    }

    k = 1;
    do {
        fn_800B24D4(k);
        fn_800B21A8(0);
        DrawTextOnCondition(k);
        k++;
    } while (k < 9);
    fn_800B24D4(2);
}
