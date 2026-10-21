#define REP_HEADER_DATA_FN getRepHeaderData_menus_settings_reset
#include "header_rep_data.h"
#include "menus/settings_reset.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"

#define RESET_SLOT_COUNT 13
#define RESET_SLOT_SIZE 0x27C

typedef struct {
    /* 0x0000 */ s32 _0000;
    /* 0x0004 */ u8 _0004[4];
    /* 0x0008 */ s32 _0008;
    /* 0x000C */ s32 _000C[21];
    /* 0x0060 */ s32 _0060[7];
    /* 0x007C */ u8 _007C[0xAC - 0x7C];
    /* 0x00AC */ s32 _00AC[3];
    /* 0x00B8 */ s32 _00B8;
    /* 0x00BC */ s32 _00BC[21];
    /* 0x0110 */ s32 _0110;
    /* 0x0114 */ u8 _0114[0xC04 - 0x114];
    /* 0x0C04 */ u8 slots[RESET_SLOT_COUNT][RESET_SLOT_SIZE];
    /* 0x2C50 */ void *objects[RESET_SLOT_COUNT];
    /* 0x2C84 */ s32 _2C84[3];
    /* 0x2C90 */ u8 _2C90[0x2CAC - 0x2C90];
    /* 0x2CAC */ s32 _2CAC[16];
    /* 0x2CEC */ u8 _2CEC[0x2D90 - 0x2CEC];
    /* 0x2D90 */ s32 _2D90[3];
    /* 0x2D9C */ s32 _2D9C;
    /* 0x2DA0 */ s32 _2DA0[0xB4];
    /* 0x3070 */ s32 _3070[2];
    /* 0x3078 */ u8 _3078[0x3154 - 0x3078];
} SettingsResetView; // size: 0x3154

extern SettingsResetView hugeAnimStruct;

static inline void clearWords(s32 *p, int count) {
    int i;

    for (i = 0; i < count; i++) {
        p[i] = 0;
    }
}

// .text:0x00019F2C size:0x288 mapped:0x80658FC0
void settingValuesTo0(void) {
    int i;

    hugeAnimStruct._0000 = 0;
    hugeAnimStruct._2D9C = 0;
    clearWords(hugeAnimStruct._2DA0, 0xB4);
    hugeAnimStruct._0008 = 0;
    clearWords(hugeAnimStruct._000C, 21);
    clearWords(hugeAnimStruct._0060, 7);
    clearWords(hugeAnimStruct._00AC, 3);
    hugeAnimStruct._00B8 = 0;
    clearWords(hugeAnimStruct._00BC, 21);
    hugeAnimStruct._0110 = 0;
    for (i = 0; i < RESET_SLOT_COUNT; i++) {
        memset(hugeAnimStruct.slots[i], 0, RESET_SLOT_SIZE);
    }
    clearWords(hugeAnimStruct._2C84, 3);
    clearWords(hugeAnimStruct._2CAC, 16);
    clearWords(hugeAnimStruct._2D90, 3);
    clearWords(hugeAnimStruct._3070, 2);
}
