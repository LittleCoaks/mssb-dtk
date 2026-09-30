#ifndef __UNKNOWN_FILE_0X8004CC18_H_
#define __UNKNOWN_FILE_0X8004CC18_H_

#include "mssbTypes.h"

// lbl_803C5F74 (0xB4 bytes of .bss); only the fields these setters touch.
typedef struct Unk803C5F74 {
    /* 0x00 */ u8 unk00;        // fn_8004CC4C does nothing while nonzero
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 state;        // 0 on setup, 3 via set803c5f77 (unless already 4), 4 via fn_8004CC18
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 _05;
    /* 0x06 */ u16 unk06[4];
    /* 0x0E */ s16 unk0E[4];
    /* 0x16 */ u16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ s8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 _1D;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 _1F[0xB4 - 0x1F];
} Unk803C5F74; // size 0xB4

void fn_8004CC18(void);
void set803c5f77(void);
void fn_8004CC4C(u8 arg0, u8 arg1, u8 arg2, int arg3, u16 arg4);

#endif // !__UNKNOWN_FILE_0X8004CC18_H_
