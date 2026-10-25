#ifndef __UNKNOWN_GRAPHIC_H_
#define __UNKNOWN_GRAPHIC_H_

#include "mssbTypes.h"
#include "Dolphin/gx.h"

/* One entry of the draw-callback list. `link` is the next entry's address
 * with two flag bits in its low bits. */
typedef struct DrawCallbackNode {
    /* 0x0 */ u32 link;
    /* 0x4 */ void (*func)(void);
} DrawCallbackNode;

void someGFXRenderingFn(void);

void initRenderMode(GXRenderModeObj* rmode, u32 fifoSize, u16 overscan);

void fn_800A7D4C(s32 phase, DrawCallbackNode* node);
void fn_800A7D7C(DrawCallbackNode* first, s32 count);
void fn_800A7DB0(void);
void fn_800A7E00(void);
void fn_800A7F10(s32 overscan);

#endif // !__UNKNOWN_GRAPHIC_H_
