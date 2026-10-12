#ifndef _C3_SKINNING_SKNCONTROL_H_
#define _C3_SKINNING_SKNCONTROL_H_

#include "mssbTypes.h"
#include "Dolphin/PPCArch.h"
#include "Dolphin/OS/OSCache.h"
#include "C3/actor.h"
#include "C3/skinning.h"

void SKNLoadFile(void* sknFile, void* pal);

void SKNFlushByIndex1(u16* indices, u32 count, void* base);
void SKNFlushByIndex2(u16* indices, u32 count, void* base);
void SKNBzero32B(void* base, u32 size);

void SKNInit(void);

void processModelDataRelated(sBone** bones, sHdr* hdr);


#endif // _C3_SKINNING_SKNCONTROL_H_
