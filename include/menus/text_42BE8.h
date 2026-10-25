#ifndef __MENUS_TEXT_42BE8_H_
#define __MENUS_TEXT_42BE8_H_

#include "mssbTypes.h"

// Element of the saved-lineup style sort in fn_2_44414.
typedef struct _SortEntry {
    /*0x0*/ s32 key;
    /*0x4*/ s32 value;
} SortEntry; // size: 0x8

void fn_2_42BE8(void);
void fn_2_42EB0(void);
void fn_2_42FC8(void);
void fn_2_430F4(void);
void fn_2_432EC(void);
void fn_2_43404(void);
void fn_2_4358C(void);
void fn_2_439D0(void);
void fn_2_43E8C(void);
void fn_2_44014(void);
void fn_2_44184(void);
BOOL fn_2_44238(int charID);
BOOL fn_2_442E8(void);
BOOL fn_2_44368(void);
void fn_2_44414(SortEntry *entries);
void fn_2_44504(void);
int fn_2_44E2C(int charIdx);

#endif // !__MENUS_TEXT_42BE8_H_
