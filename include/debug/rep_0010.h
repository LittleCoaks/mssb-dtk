#ifndef __UNUSED_REL_REP_0010_H_
#define __UNUSED_REL_REP_0010_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXEnum.h"

struct ANIMBank;
struct RepPackedFile;

void fn_1_0(struct ANIMBank *bank);
void fn_1_20(struct RepPackedFile *file);
void fn_1_E8(struct RepPackedFile *file);
void fn_1_1B0(u32 *table, s32 count);
void fn_1_1E0(void);
void fn_1_568(void);
void fn_1_58C(void);
void fn_1_5E8(void);
void fn_1_5EC(void);
void fn_1_AF4(s32 zCells, s32 xCells, f32 scale);
void fn_1_F2C(GXTevMode mode, s32 texFrac, BOOL hasNormals);
void _epilog(void);
void _unresolved(void);
void _prolog(void);
void fn_1_1148(void);
void fn_1_11D0(void);
struct RepQuad;
void fn_1_1538(void);
void fn_1_15CC(void);
void fn_1_1634(void);
void fn_1_16A0(void);
void fn_1_1948(void);
void fn_1_1240(struct RepQuad *quad);

#endif // !__UNUSED_REL_REP_0010_H_
