#ifndef __GAME_STADIUM_STADIUM_DRAW_H_
#define __GAME_STADIUM_STADIUM_DRAW_H_

#include "mssbTypes.h"
#include "Dolphin/gx.h"

void fn_3_3904(int x, int y, int textIndex, const GXColor* foreground,
                  const GXColor* background, u8 alternate);
void fn_3_3BE8(void* textureRecord, s16 left, s16 top, s16 right, s16 bottom,
                  s16 textureX, s16 textureY, s16 textureWidth, s16 textureHeight);
void fn_3_3EE8(void* textureRecord, s16 left, s16 top, s16 right, s16 bottom,
                  s16 textureX, s16 textureY, s16 textureWidth, s16 textureHeight);
void fn_3_42CC(GXTexObj* texture, s16 left, s16 top, s16 right, s16 bottom,
                  s16 textureX, s16 textureY, s16 textureWidth, s16 textureHeight,
                  GXColor foreground, GXColor background, u8 alternate);
void fn_3_4984(void);
void inningScoreDisplayRelated(int stadiumID);
void fn_3_4F90(GXTexObj* texture, s16 x, s16 y, s16 value, u8 digitSlots,
                  GXColor foreground, GXColor background, u8 outline);
void fn_3_53E0(const u16* encoded, s16* column, s16* row, s16* width, s16* height, s16* page);
void fn_3_5518(void);
void drawStadiumObjects(void);
void drawStadium(void);
void fn_3_5BCC(void* context);
void fn_3_5BF0(void);
void fn_3_5C68(void* context);
void* setFanObjPtr(void);
void CTRLBuildMatrixRelated(void* object);
void fn_3_35F0(void);
void fn_3_3818(void);
void fn_3_5E60(void);
s16 fn_3_6424(void* base, void*** tableOut);
void fn_3_64DC(void);
void updateStadiumFileHeaders(void* file);

#endif // !__GAME_STADIUM_STADIUM_DRAW_H_
