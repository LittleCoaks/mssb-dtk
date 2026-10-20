#ifndef __MENUS_TEXT_194BC_H_
#define __MENUS_TEXT_194BC_H_

#include "mssbTypes.h"

typedef struct {
    /* 0x00 */ u16 mode;
    /* 0x02 */ s16 cursor;
    /* 0x04 */ s16 prevCursor;
    /* 0x06 */ s8 flag06;
    /* 0x07 */ s8 flag07;
    /* 0x08 */ s8 flag08;
    /* 0x09 */ s8 flag09;
    /* 0x0A */ u8 flag0A;
    /* 0x0B */ u8 active;
    /* 0x0C */ u8 _0C;
    /* 0x0D */ u8 flag0D;
    /* 0x0E */ u8 _0E;
    /* 0x0F */ u8 flag0F;
} SettingsScreenState; // size: 0x10

extern SettingsScreenState lbl_2_bss_1033C;

void fn_2_194BC(void *self);
void fn_2_194E8(void);
void fn_2_19520(void);
s8 fn_2_19554(void);
void fn_2_195D8(void);
void fn_2_195DC(void);
void fn_2_19778(void);
void fn_2_197AC(u8 slot);
void optionsScreen(void);
void settingValuesTo0(void);
void challengeFileSelect(void);
void fn_2_1A2AC(void);
BOOL fn_2_1A420(void);

#endif // !__MENUS_TEXT_194BC_H_
