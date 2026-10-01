#ifndef __UNKNOWN_FILE_0X800BEB3C_H_
#define __UNKNOWN_FILE_0X800BEB3C_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

void fn_800BEB3C(void);
MtxPtr returnMtxPtr(u8 index);
u8 returnDrawShadows(void);
u8 GetDrawShadows(void);
void DrawShadows(u8 enable);
void updateVectorInArray(u8 index, Vec v);
void fn_800BEC00(BOOL flag);

#endif // !__UNKNOWN_FILE_0X800BEB3C_H_
