#ifndef _C3_SKINNING_GQRSETUP_H_
#define _C3_SKINNING_GQRSETUP_H_

#include "mssbTypes.h"

void __MTGQR5(register u32 val);
void __MTGQR6(register u32 val);
void __MTGQR7(register u32 val);

void GQRSetup7(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType);

void GQRSetup6(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType);

void GQRSetup5(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType);

#endif // _C3_SKINNING_GQRSETUP_H_
