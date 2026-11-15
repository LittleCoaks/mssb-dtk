#define REP_HEADER_DATA_FN getRepHeaderData_menus_settings_reset
#include "header_rep_data.h"
#include "menus/settings_reset.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "HugeAnimStruct.h"

#define RESET_SLOT_COUNT 13
#define RESET_SLOT_SIZE 0x27C


static void resetAnimPrimary(void) {
    s32 i;
    hugeAnimStruct._0000 = 0;
    hugeAnimStruct.archive = 0;
    for (i = 0; i < 0xB4; i++) {
        hugeAnimStruct.sourceWords[i] = 0;
    }
}

static void resetAnimHeader(void) {
    s32 i;
    hugeAnimStruct.stadiumObjectLoading = 0;
    for (i = 0; i < 21; i++) {
        hugeAnimStruct._000C[i] = 0;
    }
}

static void resetAnimSecondary(void) {
    s32 i;
    hugeAnimStruct.actorTables[0] = 0;
    hugeAnimStruct.actorTables[1] = 0;
    hugeAnimStruct.actorTables[2] = 0;
    hugeAnimStruct.actorTables[3] = 0;
    hugeAnimStruct.actorTables[4] = 0;
    hugeAnimStruct.actorTables[5] = 0;
    hugeAnimStruct.actorTables[6] = 0;
    hugeAnimStruct.lights[0] = 0;
    hugeAnimStruct.lights[1] = 0;
    hugeAnimStruct.lights[2] = 0;
    hugeAnimStruct.lights[3] = 0;
    for (i = 0; i < 21; i++) {
        hugeAnimStruct._00BC[i] = 0;
    }
}

static void resetAnimTail(void) {
    s32 i;
    hugeAnimStruct.words2C84[0] = 0;
    hugeAnimStruct.words2C84[1] = 0;
    hugeAnimStruct.words2C84[2] = 0;
    for (i = 0; i < 16; i++) {
        hugeAnimStruct.animBanks[i] = 0;
    }
}

static void resetAnimFinal(void) {
    ((s32*)&hugeAnimStruct.starAnimRelated)[0] = 0;
    ((s32*)&hugeAnimStruct.starAnimRelated)[1] = 0;
    ((s32*)&hugeAnimStruct.starAnimRelated)[2] = 0;
    ((s32*)&hugeAnimStruct.hookA)[0] = 0;
    ((s32*)&hugeAnimStruct.hookA)[1] = 0;
}

// .text:0x00019F2C size:0x288 mapped:0x80658FC0
void settingValuesTo0(void) {
    s32 i;
    resetAnimPrimary();
    resetAnimHeader();
    resetAnimSecondary();
    hugeAnimStruct._0110 = 0;
    for (i = 0; i < RESET_SLOT_COUNT; i++) {
        memset(hugeAnimStruct.pool[i], 0, RESET_SLOT_SIZE);
    }
    resetAnimTail();
    resetAnimFinal();
}
