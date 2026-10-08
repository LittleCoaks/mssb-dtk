#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_toyFieldHud
#include "game/minigame/toy_field_hud.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/camera/camera.h"
#include "game/hud/rep_3448.h"
#include "game/hud/hud_gauges.h"
#include "game/hud/hud_scoreboard.h"
#include "game/hud/toyfield_score_update.h"
#include "game/match_setup/match_scene.h"
#include "game/sound/m_sound.h"
#include "musyx/musyx.h"
#include "text/text_channel.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8004cc18.h"

extern u16 lbl_3_data_81FC[];
extern u8 animRelated[0x124];
extern u8 pauseControl[0x264];
extern u8 menuNumber[0x28];
extern u8 lbl_3_data_84B8[];
extern u16 stadiumHazardSoundIDs[16];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 lbl_800EFBA4[];
extern u8 lbl_8037169C[];
extern s16 lbl_80109410[];
extern struct {
    u8 _0[8];
    u16 label;
    u8 _A[6];
} lbl_800FEF70[];
extern s16 lbl_3_data_189C4[3][7];
extern s16 lbl_3_data_D638[8];
extern u16 lbl_3_data_91AC[8];
extern UIRecordDescriptor lbl_3_data_8E68[];
extern s16 lbl_3_data_8EA8[];
extern UIRecordDescriptor lbl_3_data_8EC4[];
extern u16 lbl_3_data_8FC4[];
extern UIRecordDescriptor lbl_3_data_8F24[];
extern UIRecordDescriptor lbl_3_data_8F64[];
extern UIRecordDescriptor lbl_3_data_8FCC[];
extern UIRecordDescriptor lbl_3_data_900C[];

extern void minigame_rankPlayers(u8 (*order)[2], int mode);
extern u32 minigame_pointsAllTied(void);
extern int minigame_displayedPointsAllTied(void);
extern int minigame_getLeadingPlayer(void);
extern void fn_80053FE8(void);
extern void fn_80051D00(void);
extern void fn_80050F78(int arg0);
extern void fn_8004D0F0(void);

#define MG_BYTE(off) (((u8*)&g_Minigame)[off])
#define SET_MENU(id)               \
    menuNumber[0] = (id);          \
    menuNumber[9] = menuNumber[8]; \
    menuNumber[8] = lbl_800FEF70[(id)].label

#define UI_DESC(element, mode, layer, parent, tag, anchorSub) \
    { 0, element, { 0 }, 0xFFFFFFFF, mode, layer, parent, tag, { 0 }, 1, anchorSub }

#define OFFSCREEN_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)
#define OFFSCREEN_RECORD_AT(scene, base, i) \
    ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (base) + (i)].object)

// clang-format off
static UIRecordDescriptor lbl_3_data_19770[6] = {
    UI_DESC(0xA, 1, 9, UI_NO_PARENT, 14, 0),
    UI_DESC(0xB, 0, 7, UI_NO_PARENT, 14, 0),
    UI_DESC(0xC, 0, 7, UI_NO_PARENT, 14, 0),
    UI_DESC(0xD, 0, 7, UI_NO_PARENT, 14, 0),
    UI_DESC(0xE, 0, 7, UI_NO_PARENT, 14, 0),
    { UI_DESC_END },
};

static UIRecordDescriptor lbl_3_data_19830[7] = {
    UI_DESC(0x1, 1, 9, UI_NO_PARENT, 14, 0),
    UI_DESC(0x67, 0, 7, UI_NO_PARENT, 3, 0),
    UI_DESC(0x2, 1, 7, 1, 14, 3),
    UI_DESC(0x2, 1, 7, 1, 14, 2),
    UI_DESC(0x2, 1, 7, 1, 14, 1),
    UI_DESC(0x2, 1, 7, 1, 14, 0),
    { UI_DESC_END },
};

static UIRecordDescriptor lbl_3_data_19910[3] = {
    UI_DESC(0x11, 1, 7, UI_NO_PARENT, 14, 0),
    UI_DESC(0xF, 1, 7, 0, 14, 0),
    { UI_DESC_END },
};

static u16 lbl_3_data_19970[4] = { 0x11, 0x12, 0x13, 0x14 };

static u16 lbl_3_data_19978[4] = { 0x87, 0x87, 0x87, 0x87 };

static u16 lbl_3_data_19980[4] = { 0xBE, 0xBE, 0xBE, 0xBE };

static UIRecordDescriptor lbl_3_data_19988[16] = {
    UI_DESC(0x1B, 1, 7, UI_NO_PARENT, 14, 0),
    UI_DESC(0x1E, 0, 7, 0, 14, 2),
    UI_DESC(0x1E, 0, 7, 0, 14, 1),
    UI_DESC(0x1E, 0, 7, 0, 14, 0),
    UI_DESC(0x1C, 1, 7, UI_NO_PARENT, 14, 0),
    UI_DESC(0x1A, 0, 7, 1, 14, 0),
    UI_DESC(0x1A, 0, 7, 2, 14, 0),
    UI_DESC(0x1A, 0, 7, 3, 14, 0),
    UI_DESC(0x1A, 0, 7, 1, 14, 1),
    UI_DESC(0x1A, 0, 7, 2, 14, 1),
    UI_DESC(0x1A, 0, 7, 3, 14, 1),
    UI_DESC(0x1D, 1, 7, UI_NO_PARENT, 14, 0),
    UI_DESC(0x17, 1, 7, UI_NO_PARENT, 14, 0),
    UI_DESC(0x19, 0, 7, UI_NO_PARENT, 14, 0),
    UI_DESC(0x18, 0, 7, 13, 14, 0),
    { UI_DESC_END },
};

static u16 lbl_3_data_19B88[8] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x6, 0x7, 0x5 };

static UIRecordDescriptor lbl_3_data_19B98[46] = {
    UI_DESC(0x71, 0, 7, UI_NO_PARENT, 3, 0),
    UI_DESC(0x4B, 0, 7, 0, 3, 3),
    UI_DESC(0x4B, 0, 7, 0, 3, 2),
    UI_DESC(0x4B, 0, 7, 0, 3, 1),
    UI_DESC(0x4B, 0, 7, 0, 3, 0),
    UI_DESC(0x5C, 0, 7, 1, 3, 0),
    UI_DESC(0x5C, 0, 7, 2, 3, 0),
    UI_DESC(0x5C, 0, 7, 3, 3, 0),
    UI_DESC(0x5C, 0, 7, 4, 3, 0),
    UI_DESC(0x60, 0, 7, 1, 3, 1),
    UI_DESC(0x60, 0, 7, 2, 3, 1),
    UI_DESC(0x60, 0, 7, 3, 3, 1),
    UI_DESC(0x60, 0, 7, 4, 3, 1),
    UI_DESC(0x83, 0, 7, 9, 1, 0),
    UI_DESC(0x83, 0, 7, 10, 1, 0),
    UI_DESC(0x83, 0, 7, 11, 1, 0),
    UI_DESC(0x83, 0, 7, 12, 1, 0),
    UI_DESC(0x62, 0, 7, 1, 3, 2),
    UI_DESC(0x62, 0, 7, 2, 3, 2),
    UI_DESC(0x62, 0, 7, 3, 3, 2),
    UI_DESC(0x62, 0, 7, 4, 3, 2),
    UI_DESC(0x5F, 0, 7, 1, 3, 3),
    UI_DESC(0x5F, 0, 7, 2, 3, 3),
    UI_DESC(0x5F, 0, 7, 3, 3, 3),
    UI_DESC(0x5F, 0, 7, 4, 3, 3),
    UI_DESC(0x64, 1, 7, 1, 3, 4),
    UI_DESC(0x64, 1, 7, 1, 3, 5),
    UI_DESC(0x64, 1, 7, 1, 3, 6),
    UI_DESC(0x64, 1, 7, 1, 3, 7),
    UI_DESC(0x64, 1, 7, 2, 3, 4),
    UI_DESC(0x64, 1, 7, 2, 3, 5),
    UI_DESC(0x64, 1, 7, 2, 3, 6),
    UI_DESC(0x64, 1, 7, 2, 3, 7),
    UI_DESC(0x64, 1, 7, 3, 3, 4),
    UI_DESC(0x64, 1, 7, 3, 3, 5),
    UI_DESC(0x64, 1, 7, 3, 3, 6),
    UI_DESC(0x64, 1, 7, 3, 3, 7),
    UI_DESC(0x64, 1, 7, 4, 3, 4),
    UI_DESC(0x64, 1, 7, 4, 3, 5),
    UI_DESC(0x64, 1, 7, 4, 3, 6),
    UI_DESC(0x64, 1, 7, 4, 3, 7),
    UI_DESC(0x5D, 1, 7, 0, 3, 3),
    UI_DESC(0x5D, 1, 7, 0, 3, 2),
    UI_DESC(0x5D, 1, 7, 0, 3, 1),
    UI_DESC(0x5D, 1, 7, 0, 3, 0),
    { UI_DESC_END },
};

static u16 lbl_3_data_1A158[8] = { 0x6C, 0x6B, 0x6E, 0x6D, 0x70, 0x6F, 0x72, 0x71 };

static UIRecordDescriptor lbl_3_data_1A168[46] = {
    UI_DESC(0x67, 1, 7, UI_NO_PARENT, 3, 0),
    UI_DESC(0x63, 0, 7, 0, 3, 3),
    UI_DESC(0x63, 0, 7, 0, 3, 2),
    UI_DESC(0x63, 0, 7, 0, 3, 1),
    UI_DESC(0x63, 0, 7, 0, 3, 0),
    UI_DESC(0x55, 0, 7, 1, 3, 0),
    UI_DESC(0x55, 0, 7, 2, 3, 0),
    UI_DESC(0x55, 0, 7, 3, 3, 0),
    UI_DESC(0x55, 0, 7, 4, 3, 0),
    UI_DESC(0x5C, 0, 7, 5, 3, 0),
    UI_DESC(0x5C, 0, 7, 6, 3, 0),
    UI_DESC(0x5C, 0, 7, 7, 3, 0),
    UI_DESC(0x5C, 0, 7, 8, 3, 0),
    UI_DESC(0x60, 0, 7, 5, 3, 1),
    UI_DESC(0x60, 0, 7, 6, 3, 1),
    UI_DESC(0x60, 0, 7, 7, 3, 1),
    UI_DESC(0x60, 0, 7, 8, 3, 1),
    UI_DESC(0x83, 0, 7, 13, 1, 0),
    UI_DESC(0x83, 0, 7, 14, 1, 0),
    UI_DESC(0x83, 0, 7, 15, 1, 0),
    UI_DESC(0x83, 0, 7, 16, 1, 0),
    UI_DESC(0x62, 0, 7, 5, 3, 2),
    UI_DESC(0x62, 0, 7, 6, 3, 2),
    UI_DESC(0x62, 0, 7, 7, 3, 2),
    UI_DESC(0x62, 0, 7, 8, 3, 2),
    UI_DESC(0x5F, 0, 7, 5, 3, 3),
    UI_DESC(0x5F, 0, 7, 6, 3, 3),
    UI_DESC(0x5F, 0, 7, 7, 3, 3),
    UI_DESC(0x5F, 0, 7, 8, 3, 3),
    UI_DESC(0x64, 1, 7, 5, 3, 4),
    UI_DESC(0x64, 1, 7, 5, 3, 5),
    UI_DESC(0x64, 1, 7, 5, 3, 6),
    UI_DESC(0x64, 1, 7, 6, 3, 4),
    UI_DESC(0x64, 1, 7, 6, 3, 5),
    UI_DESC(0x64, 1, 7, 6, 3, 6),
    UI_DESC(0x64, 1, 7, 7, 3, 4),
    UI_DESC(0x64, 1, 7, 7, 3, 5),
    UI_DESC(0x64, 1, 7, 7, 3, 6),
    UI_DESC(0x64, 1, 7, 8, 3, 4),
    UI_DESC(0x64, 1, 7, 8, 3, 5),
    UI_DESC(0x64, 1, 7, 8, 3, 6),
    UI_DESC(0x5D, 1, 7, 1, 3, 0),
    UI_DESC(0x5D, 1, 7, 2, 3, 0),
    UI_DESC(0x5D, 1, 7, 3, 3, 0),
    UI_DESC(0x5D, 1, 7, 4, 3, 0),
    { UI_DESC_END },
};

static u16 lbl_3_data_1A728[4] = { 0x67, 0x68, 0x69, 0x6A };

static UIRecordDescriptor lbl_3_data_1A730[22] = {
    UI_DESC(0x67, 0, 7, UI_NO_PARENT, 3, 0),
    UI_DESC(0x57, 0, 7, 0, 3, 3),
    UI_DESC(0x57, 0, 7, 0, 3, 2),
    UI_DESC(0x57, 0, 7, 0, 3, 1),
    UI_DESC(0x57, 0, 7, 0, 3, 0),
    UI_DESC(0x56, 0, 7, 1, 3, 0),
    UI_DESC(0x56, 0, 7, 1, 3, 1),
    UI_DESC(0x56, 0, 7, 1, 3, 2),
    UI_DESC(0x56, 0, 7, 1, 3, 3),
    UI_DESC(0x56, 0, 7, 2, 3, 0),
    UI_DESC(0x56, 0, 7, 2, 3, 1),
    UI_DESC(0x56, 0, 7, 2, 3, 2),
    UI_DESC(0x56, 0, 7, 2, 3, 3),
    UI_DESC(0x56, 0, 7, 3, 3, 0),
    UI_DESC(0x56, 0, 7, 3, 3, 1),
    UI_DESC(0x56, 0, 7, 3, 3, 2),
    UI_DESC(0x56, 0, 7, 3, 3, 3),
    UI_DESC(0x56, 0, 7, 4, 3, 0),
    UI_DESC(0x56, 0, 7, 4, 3, 1),
    UI_DESC(0x56, 0, 7, 4, 3, 2),
    UI_DESC(0x56, 0, 7, 4, 3, 3),
    { UI_DESC_END },
};

static UIRecordDescriptor lbl_3_data_1A9F0[44] = {
    UI_DESC(0x21, 1, 7, UI_NO_PARENT, 3, 0),
    UI_DESC(0x25, 1, 7, UI_NO_PARENT, 3, 0),
    UI_DESC(0x2A, 1, 7, UI_NO_PARENT, 3, 0),
    UI_DESC(0x29, 0, 7, 2, 3, 3),
    UI_DESC(0x29, 0, 7, 2, 3, 2),
    UI_DESC(0x29, 0, 7, 2, 3, 1),
    UI_DESC(0x29, 0, 7, 2, 3, 0),
    UI_DESC(0x2E, 0, 7, 3, 3, 0),
    UI_DESC(0x2E, 0, 7, 4, 3, 0),
    UI_DESC(0x2E, 0, 7, 5, 3, 0),
    UI_DESC(0x2E, 0, 7, 6, 3, 0),
    UI_DESC(0x62, 0, 7, 3, 3, 1),
    UI_DESC(0x62, 0, 7, 4, 3, 1),
    UI_DESC(0x62, 0, 7, 5, 3, 1),
    UI_DESC(0x62, 0, 7, 6, 3, 1),
    UI_DESC(0x53, 0, 7, 3, 3, 2),
    UI_DESC(0x53, 0, 7, 4, 3, 2),
    UI_DESC(0x53, 0, 7, 5, 3, 2),
    UI_DESC(0x53, 0, 7, 6, 3, 2),
    UI_DESC(0x17E, 1, 7, 3, 3, 3),
    UI_DESC(0x17F, 1, 7, 4, 3, 3),
    UI_DESC(0x180, 1, 7, 5, 3, 3),
    UI_DESC(0x181, 1, 7, 6, 3, 3),
    UI_DESC(0x5F, 0, 7, 3, 3, 4),
    UI_DESC(0x5F, 0, 7, 4, 3, 4),
    UI_DESC(0x5F, 0, 7, 5, 3, 4),
    UI_DESC(0x5F, 0, 7, 6, 3, 4),
    UI_DESC(0x64, 1, 7, 3, 3, 5),
    UI_DESC(0x64, 1, 7, 3, 3, 6),
    UI_DESC(0x64, 1, 7, 3, 3, 7),
    UI_DESC(0x64, 1, 7, 3, 3, 8),
    UI_DESC(0x64, 1, 7, 4, 3, 5),
    UI_DESC(0x64, 1, 7, 4, 3, 6),
    UI_DESC(0x64, 1, 7, 4, 3, 7),
    UI_DESC(0x64, 1, 7, 4, 3, 8),
    UI_DESC(0x64, 1, 7, 5, 3, 5),
    UI_DESC(0x64, 1, 7, 5, 3, 6),
    UI_DESC(0x64, 1, 7, 5, 3, 7),
    UI_DESC(0x64, 1, 7, 5, 3, 8),
    UI_DESC(0x64, 1, 7, 6, 3, 5),
    UI_DESC(0x64, 1, 7, 6, 3, 6),
    UI_DESC(0x64, 1, 7, 6, 3, 7),
    UI_DESC(0x64, 1, 7, 6, 3, 8),
    { UI_DESC_END },
};

static u16 lbl_3_data_1AF70[8] = { 0x21, 0x1B, 0x1C, 0x1D, 0x1F, 0x1E, 0x20, 0x0 };

static u16 lbl_3_data_1AF80[4] = { 0x25, 0x26, 0x27, 0x28 };

static u16 lbl_3_data_1AF88[4] = { 0x22, 0x23, 0x24, 0x0 };

static u16 lbl_3_data_1AF90[4] = { 0x2A, 0x2B, 0x2C, 0x2D };

static u16 lbl_3_data_1AF98[4] = { 0x6, 0x0, 0x1, 0x2 };

static u16 lbl_3_data_1AFA0[4] = { 0x4, 0x3, 0x5, 0x0 };

static u16 lbl_3_data_1AFA8[4] = { 0x17E, 0x17F, 0x180, 0x181 };

static UIRecordDescriptor lbl_3_data_1AFB0[65] = {
    UI_DESC(0x16F, 1, 7, UI_NO_PARENT, 3, 0),
    UI_DESC(0x16E, 1, 7, UI_NO_PARENT, 3, 0),
    UI_DESC(0x183, 0, 7, UI_NO_PARENT, 3, 0),
    UI_DESC(0x182, 0, 7, 2, 3, 3),
    UI_DESC(0x182, 0, 7, 2, 3, 2),
    UI_DESC(0x182, 0, 7, 2, 3, 1),
    UI_DESC(0x182, 0, 7, 2, 3, 0),
    UI_DESC(0x17C, 0, 7, 3, 3, 0),
    UI_DESC(0x17C, 0, 7, 4, 3, 0),
    UI_DESC(0x17C, 0, 7, 5, 3, 0),
    UI_DESC(0x17C, 0, 7, 6, 3, 0),
    UI_DESC(0x17D, 1, 7, 3, 3, 1),
    UI_DESC(0x17D, 1, 7, 4, 3, 1),
    UI_DESC(0x17D, 1, 7, 5, 3, 1),
    UI_DESC(0x17D, 1, 7, 6, 3, 1),
    UI_DESC(0x83, 0, 7, 11, 1, 0),
    UI_DESC(0x83, 0, 7, 11, 1, 1),
    UI_DESC(0x83, 0, 7, 12, 1, 0),
    UI_DESC(0x83, 0, 7, 12, 1, 1),
    UI_DESC(0x83, 0, 7, 13, 1, 0),
    UI_DESC(0x83, 0, 7, 13, 1, 1),
    UI_DESC(0x83, 0, 7, 14, 1, 0),
    UI_DESC(0x83, 0, 7, 14, 1, 1),
    UI_DESC(0x177, 1, 7, 3, 3, 2),
    UI_DESC(0x178, 1, 7, 4, 3, 2),
    UI_DESC(0x179, 1, 7, 5, 3, 2),
    UI_DESC(0x175, 1, 7, 6, 3, 2),
    UI_DESC(0x176, 1, 7, 3, 3, 3),
    UI_DESC(0x17E, 1, 7, 3, 3, 4),
    UI_DESC(0x17F, 1, 7, 4, 3, 4),
    UI_DESC(0x180, 1, 7, 5, 3, 4),
    UI_DESC(0x181, 1, 7, 6, 3, 4),
    UI_DESC(0x62, 0, 7, 3, 3, 5),
    UI_DESC(0x62, 0, 7, 4, 3, 5),
    UI_DESC(0x62, 0, 7, 5, 3, 5),
    UI_DESC(0x62, 0, 7, 6, 3, 5),
    UI_DESC(0x64, 0, 7, 3, 3, 6),
    UI_DESC(0x64, 0, 7, 3, 3, 7),
    UI_DESC(0x64, 0, 7, 3, 3, 8),
    UI_DESC(0x64, 0, 7, 4, 3, 6),
    UI_DESC(0x64, 0, 7, 4, 3, 7),
    UI_DESC(0x64, 0, 7, 4, 3, 8),
    UI_DESC(0x64, 0, 7, 5, 3, 6),
    UI_DESC(0x64, 0, 7, 5, 3, 7),
    UI_DESC(0x64, 0, 7, 5, 3, 8),
    UI_DESC(0x64, 0, 7, 6, 3, 6),
    UI_DESC(0x64, 0, 7, 6, 3, 7),
    UI_DESC(0x64, 0, 7, 6, 3, 8),
    UI_DESC(0x17A, 1, 7, 3, 3, 9),
    UI_DESC(0x17A, 1, 7, 4, 3, 9),
    UI_DESC(0x17A, 1, 7, 5, 3, 9),
    UI_DESC(0x17A, 1, 7, 6, 3, 9),
    UI_DESC(0x17B, 1, 7, 3, 3, 10),
    UI_DESC(0x17B, 1, 7, 4, 3, 10),
    UI_DESC(0x17B, 1, 7, 5, 3, 10),
    UI_DESC(0x17B, 1, 7, 6, 3, 10),
    UI_DESC(0x172, 0, 7, 2, 3, 3),
    UI_DESC(0x172, 0, 7, 2, 3, 2),
    UI_DESC(0x172, 0, 7, 2, 3, 1),
    UI_DESC(0x172, 0, 7, 2, 3, 0),
    UI_DESC(0x173, 0, 7, 2, 3, 3),
    UI_DESC(0x173, 0, 7, 2, 3, 2),
    UI_DESC(0x173, 0, 7, 2, 3, 1),
    UI_DESC(0x173, 0, 7, 2, 3, 0),
    { UI_DESC_END },
};

static u16 lbl_3_data_1B7D0[4] = { 0x177, 0x178, 0x179, 0x175 };
// clang-format on

static inline BOOL toyFieldRecordDone(UIRecord* rec) {
    return rec->unk69[0] == 2 ? TRUE : FALSE;
}

static inline SND_VOICEID toyFieldPlayHazardSound(int idOffset, int fxOffset) {
    int stadium = g_d_GameSettings.StadiumID;
    SND_VOICEID voice = sndFXStartEx(stadiumHazardSoundIDs[stadium] + idOffset,
                                     g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                                         ? lbl_3_data_84B8[fxOffset]
                                         : stadiumHazardSoundFxRelated[stadium * 0x1E + fxOffset],
                                     0x3F, 0);
    sndFXCtrl(voice, 0x5B,
              g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[fxOffset + 1]
                  : stadiumHazardSoundFxRelated[stadium * 0x1E + fxOffset + 1]);
    return voice;
}

// .text:0x000EDD10 size:0x29C
void toyfield_drawHud(void) {
    if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_SELECT ||
        (u8)(g_GameLogic.gameStatus - GAME_STATUS_TOY_STADIUM_LOAD) <= 3 ||
        g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_READY) {
        fn_3_EDA3C();
        return;
    }
    animRelated[0xDA] = 0;
    manageEventStates();
    toyfield_hud_turns_diamondMap();
    toyField_hud_scores_BallsStrikesOuts();
    hud_ScoreUpdate_ToyFieldOffScreenPlayers();
    if (g_Minigame.framesSincePanelHit == 1) {
        insertGraphicDrawingFunction(fn_3_ED784, 2);
    }
    if (g_Minigame.panelHitInd != 0 && animRelated[0xD6] == 0 && g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
        ((MinigameHudScene*)insertGraphicDrawingFunction(fn_3_EA8FC, 2))->_18 = 1;
        insertGraphicDrawingFunction(fn_3_EAEF4, 2);
    }
    if (g_Minigame.toyField_turnEndState != 0 && g_Minigame._19BA == 1) {
        insertGraphicDrawingFunction(fn_3_ED2A8, 2);
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME ||
        g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_POST_MENU) {
        fn_3_129458();
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_GAME_START_MOVIE) {
        if (g_Minigame.startMovieHudInd == 0) {
            insertGraphicDrawingFunction(fn_3_1254F8, 2);
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_POST_MENU) {
        if (pauseControl[0x1D2] == 1) {
            insertGraphicDrawingFunction(pauseOptionList_init, 2);
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION) {
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_0 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            ((MinigameHudScene*)insertGraphicDrawingFunction(minigame_pointsTally, 2))->_18 = 0;
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_0x24) {
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_5 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            insertGraphicDrawingFunction(fn_3_1274B4, 2);
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_END_OF_GAME) {
    } else if (g_GameLogic.gameStatus == GAME_STATUS_HOW_TO_PLAY_SCREEN) {
        if (pauseControl[0x1D2] == 2) {
            insertGraphicDrawingFunction(fn_3_128B90, 2);
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
        if (pauseControl[0x1D2] == 8 && pauseControl[0x1D4] == 2) {
            insertGraphicDrawingFunction(fn_3_126604, 2);
        }
    }
}

// .text:0x000EDA3C size:0x2D4
void fn_3_EDA3C(void) {
    if (g_GameLogic.gameStatus >= GAME_STATUS_MINIGAME_SELECT && g_GameLogic.gameStatus <= GAME_STATUS_0x20 &&
        animRelated[0xD9] == 0 && g_GameLogic.framesOfExitingToMenu == 0) {
        insertGraphicDrawingFunction(fn_3_12C3F0, 2);
        insertGraphicDrawingFunction(fn_80053FE8, 2);
        SET_MENU(0x2E);
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT) {
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            if (animRelated[0xDC] == 0) {
                insertGraphicDrawingFunction(fn_80051D00, 2);
                animRelated[0xDC] = 1;
            }
            if (animRelated[0xDA] != 1) {
                insertGraphicDrawingFunction(fn_3_12B7A0, 2);
            }
        }
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_2) {
            if (animRelated[0xDC] == 0 && g_Minigame.charSelectState != 5 && g_Minigame.charSelectState != 8) {
                insertGraphicDrawingFunction(fn_80051D00, 2);
                animRelated[0xDC] = 1;
            }
            if (g_Minigame.charSelectState == 1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
                insertGraphicDrawingFunction(fn_3_12A6C4, 2);
            }
        }
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_7) {
            fn_80050F78(1);
            animRelated[0xDC] = 0;
        }
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_3 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            fn_8004CC4C(0, 1, 1, 0, 0x89);
            insertGraphicDrawingFunction(fn_8004D0F0, 2);
        }
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_5) {
            fn_80050F78(1);
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_READY) {
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_2 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            insertGraphicDrawingFunction(fn_3_126604, 2);
            SET_MENU(0x32);
            if (g_d_GameSettings.exhibitionMatchInd == 0 && animRelated[0xD9] == 0) {
                insertGraphicDrawingFunction(fn_3_12C3F0, 2);
            }
        }
    }
}

// .text:0x000ED818 size:0x224
void toyField_hud_scores_BallsStrikesOuts(void) {
    if (g_GameLogic.hudElementLoadingInd != 0 && animRelated[0xA5] == 0) {
        animRelated[0xA5] = 1;
        animRelated[0xA6] = 0;
        animRelated[0xA7] = 0xFF;
        insertGraphicDrawingFunction(init_BallStrikeOutHud, 2);
        ((MinigameHudScene*)insertGraphicDrawingFunction(fn_3_EA8FC, 2))->_18 = 0;
        insertGraphicDrawingFunction(fn_3_EB6E0, 2);
    }
    if (g_Ball.totalFramesAtPlay == 0xF && g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd == 0 &&
        g_Minigame.toyField_pointMultiplier > 1 && g_Pitcher.nPitchesThisAB == 0) {
        insertGraphicDrawingFunction(toyField_draw_theCoinsBesideThe_CoinsX2_Graphic, 2);
    }
    if (animRelated[0xA5] != 0 && animRelated[0xA6] < 0xFF) {
        if (animRelated[0xA6] < 0xF0) {
            animRelated[0xA6] += 0x10;
        } else {
            animRelated[0xA6] = 0xFF;
        }
    }
    if (animRelated[0xA7] != 0 && animRelated[0xA7] < 0xFF) {
        if (animRelated[0xA7] <= 0x10) {
            animRelated[0xA7] = 0;
            animRelated[0xA5] = 0;
        } else {
            animRelated[0xA7] -= 0x10;
        }
    } else if (animRelated[0xA5] != 0) {
        if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION) {
            animRelated[0xA7] = 0;
            animRelated[0xA5] = 0;
        } else if (g_GameLogic.gameStatus != GAME_STATUS_AT_BAT && g_GameLogic.gameStatus != GAME_STATUS_DEFAULT &&
                   g_GameLogic.gameStatus != GAME_STATUS_PAUSED &&
                   g_GameLogic.gameStatus != GAME_STATUS_HOW_TO_PLAY_SCREEN) {
            animRelated[0xA7] = 0xF0;
        }
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED && pauseControl[0x1D2] == 1) {
        insertGraphicDrawingFunction(pauseOptionList_init, 2);
        if (animRelated[0xAA] == 0) {
            insertGraphicDrawingFunction(pauseSubPanel_init, 2);
        }
    }
}

// .text:0x000ED784 size:0x94
void fn_3_ED784(void) {
    DrawingSceneStruct* scene = currentDrawingItem;
    int element;

    if (g_Minigame.toyFieldBallStateResult2 == 0xB) {
        scene->func = fn_3_EC014;
    } else {
        element = lbl_3_data_8EA8[g_Minigame.toyFieldBallStateResult2];
        if (element < 0) {
            removeCurrentDrawingItem();
        } else {
            lbl_3_data_8E68[0].elementIndex = element;
            addGraphicsElementToScene(scene, lbl_3_data_8E68);
            currentDrawingItem->func = fn_3_ED6E0;
        }
    }
}

// .text:0x000ED6E0 size:0xA4
void fn_3_ED6E0(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;

    if (animRelated[0x96] != 0 || OFFSCREEN_RECORD(scene, 0)->unk69[0] == 2 ||
        g_GameLogic.gameStatus == GAME_STATUS_TRANSITION) {
        if (g_Minigame.toyField_runsScored != 0) {
            insertGraphicDrawingFunction(fn_3_ED0F4, 2);
        }
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x000ED574 size:0x16C
void toyFieldDrawRelated_miniMap(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int turn;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_8EC4);
    load_Icon(scene, 1, 6, 0x4A, g_Minigame.toyField_selectedTurns % 10);
    load_Icon(scene, 1, 5, 0x4A, g_Minigame.toyField_selectedTurns / 10);
    turn = g_Minigame.toyField_turnNumber;
    if (turn > g_Minigame.toyField_selectedTurns) {
        turn = g_Minigame.toyField_selectedTurns;
    }
    load_Icon(scene, 1, 2, 0x4A, turn % 10);
    if (turn >= 10) {
        load_Icon(scene, 1, 1, 0x4A, turn / 10);
    } else {
        load_Icon(scene, 1, 1, 0x4A, 10);
    }
    currentDrawingItem->func = fn_3_ED4FC;
}

// .text:0x000ED4FC size:0x78
void fn_3_ED4FC(void) {
    DrawingSceneStruct* scene = currentDrawingItem;

    if (animRelated[0x96] != 0 || g_GameLogic.hudLoadingRelated != 0 ||
        g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION || g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME ||
        g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU) {
        removeGraphicsElementFromScene(scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x000ED490 size:0x6C
void toyField_draw_theCoinsBesideThe_CoinsX2_Graphic(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_8F24);
    g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd = 1;
    scene->state = 0;
    currentDrawingItem->func = fn_3_ED2F4;
}

// .text:0x000ED2F4 size:0x19C
void fn_3_ED2F4(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;

    if (animRelated[0x96] == 0) {
        if (g_UnkSound_32718._07 == 0) {
            OFFSCREEN_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
            if (scene->state == 0) {
                if (audioFileDescriptors.enableMusic == TRUE) {
                    toyFieldPlayHazardSound(0x1B, 0x36);
                }
                scene->state = 1;
            }
        } else {
            OFFSCREEN_RECORD(scene, 0)->playMode = UI_PLAY_STOP;
        }
        if (OFFSCREEN_RECORD(scene, 0)->unk69[0] != 2) {
            return;
        }
    }
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd = 0;
}

// .text:0x000ED2A8 size:0x4C
void fn_3_ED2A8(void) {
    addGraphicsElementToScene(currentDrawingItem, lbl_3_data_8FCC);
    currentDrawingItem->func = fn_3_ED244;
}

// .text:0x000ED244 size:0x64
void fn_3_ED244(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;

    if (animRelated[0x96] != 0 || OFFSCREEN_RECORD(scene, 0)->unk69[0] == 2) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x000ED0F4 size:0x150
void fn_3_ED0F4(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_8F64);
    OFFSCREEN_RECORD(scene, 1)->elementIndex = lbl_3_data_8FC4[g_Minigame.toyField_runsScored - 1];
    toyFieldPlayHazardSound(0x1C, 0x38);
    scene->_18 = 0;
    g_Minigame._19CD = 1;
    currentDrawingItem->func = fn_3_ED058;
}

// .text:0x000ED058 size:0x9C
void fn_3_ED058(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;

    scene->_18++;
    if (animRelated[0x96] != 0 ||
        (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL && g_GameLogic.gameStatus != GAME_STATUS_AT_BAT) ||
        OFFSCREEN_RECORD(scene, 0)->unk69[0] == 2) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        g_Minigame._19CD = 3;
    }
}

// .text:0x000ECD48 size:0x310
void fn_3_ECD48(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u8* flags = g_Minigame.hudPulseInd;
    u32 i;

    if (animRelated[0x96] != 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else {
        switch (scene->state) {
            case 0:
                addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_19770);
                toyFieldPlayHazardSound(0x11, 0x22);
                scene->state = 1;
                scene->_1E = 0;
                break;
            case 1:
                if ((OFFSCREEN_RECORD(scene, 0)->frame >> 16) == 0xA0) {
                    i = 0;
                    do {
                        OFFSCREEN_RECORD_AT(scene, 1, (s8)g_Minigame.toyField_eventPlayers[i + 1])->playMode = UI_PLAY_FORWARD;
                        i++;
                    } while (i < g_Minigame.miniGameNumberOfParticipants - 1);
                    scene->state = 2;
                }
                scene->_1E++;
                if (scene->_1E == 0x3C) {
                    toyFieldPlayHazardSound(0x12, 0x24);
                }
                break;
            case 2:
                if ((OFFSCREEN_RECORD_AT(scene, 1, (s8)g_Minigame.toyField_eventVictim)->frame >> 16) >= 6) {
                    i = 0;
                    do {
                        flags[(s8)g_Minigame.toyField_eventPlayers[i + 1]] = 2;
                        i++;
                    } while (i < g_Minigame.miniGameNumberOfParticipants - 1);
                    g_Minigame.toyField_slotStage = 2;
                    scene->state = 3;
                }
                break;
            case 3:
                break;
        }
    }
}

// .text:0x000ECBB0 size:0x198
void fn_3_ECBB0(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u8* flags = g_Minigame.hudPulseInd;
    u32 i;

    if (animRelated[0x96] != 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else {
        switch (scene->state) {
            case 0:
                addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_19830);
                OFFSCREEN_RECORD(scene, 1)->frame = 0xA0000;
                i = 0;
                do {
                    OFFSCREEN_RECORD_AT(scene, 2, i)->flags &= ~UI_FLAG_VISIBLE;
                    i++;
                } while (i < 4);
                OFFSCREEN_RECORD_AT(scene, 2, g_Minigame.toyField_eventActor)->flags |= UI_FLAG_VISIBLE;
                OFFSCREEN_RECORD_AT(scene, 2, g_Minigame.toyField_eventVictim)->flags |= UI_FLAG_VISIBLE;
                flags[g_Minigame.toyField_eventActor] = 1;
                flags[g_Minigame.toyField_eventVictim] = 1;
                scene->state = 1;
                break;
            case 1:
                g_Minigame.toyField_slotStage = 2;
                scene->state = 2;
                break;
            case 2:
                break;
        }
    }
}

// .text:0x000EC804 size:0x3AC
void fn_3_EC804(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u8* flags = g_Minigame.hudPulseInd;

    if (animRelated[0x96] != 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else {
        switch (scene->state) {
            case 0:
                addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_19910);
                OFFSCREEN_RECORD(scene, 0)->elementIndex = lbl_3_data_19970[(s8)g_Minigame.toyField_eventVictim];
                OFFSCREEN_RECORD(scene, 1)->elementIndex = (scene->_18 != 0) + 0xF;
                scene->_1E = lbl_3_data_19978[(s8)g_Minigame.toyField_eventVictim];
                scene->_20 = lbl_3_data_19980[(s8)g_Minigame.toyField_eventVictim];
                toyFieldPlayHazardSound(0x10, 0x20);
                scene->state = 1;
                break;
            case 1:
                if (scene->_1E == (OFFSCREEN_RECORD(scene, 0)->frame >> 16)) {
                    if (scene->_18 != 0) {
                        toyFieldPlayHazardSound(7, 0xE);
                    } else {
                        toyFieldPlayHazardSound(6, 0xC);
                    }
                }
                if ((OFFSCREEN_RECORD(scene, 0)->frame >> 16) >= scene->_20) {
                    flags[(s8)g_Minigame.toyField_eventVictim] = 2;
                    g_Minigame.toyField_slotStage = 2;
                    scene->state = 2;
                }
                break;
            case 2:
                break;
        }
    }
}

// .text:0x000EC014 size:0x7F0
void fn_3_EC014(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 i;
    u32 count;

    if (animRelated[0x96] != 0 || g_GameLogic.gameStatus == GAME_STATUS_TRANSITION || scene->state == 7) {
        if (scene->state != 0 && scene->sndHandle != SND_ID_ERROR) {
            sndFXKeyOff(scene->sndHandle);
            sndFXCtrl(scene->sndHandle, 7, 0);
            scene->sndHandle = SND_ID_ERROR;
        }
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    if (g_Minigame.toyField_turnEndState != 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
        case 0:
            addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_19988);
            i = 0;
            do {
                g_Minigame.toyField_reelHudStage[i] = 0;
                i++;
            } while (i < 3);
            scene->sndHandle = SND_ID_ERROR;
            scene->state = 1;
            break;
        case 1:
            if (toyFieldRecordDone(OFFSCREEN_RECORD(scene, 0)) && OFFSCREEN_RECORD(scene, 12)->unk69[0] == 2) {
                i = 0;
                do {
                    OFFSCREEN_RECORD_AT(scene, 1, i)->playMode = UI_PLAY_FORWARD;
                    i++;
                } while (i < 3);
                OFFSCREEN_RECORD(scene, 13)->playMode = UI_PLAY_FORWARD;
                OFFSCREEN_RECORD(scene, 14)->playMode = UI_PLAY_FORWARD;
                scene->sndHandle = toyFieldPlayHazardSound(2, 4);
                scene->state = 2;
            }
            break;
        case 2:
            i = 0;
            do {
                if (toyFieldRecordDone(OFFSCREEN_RECORD_AT(scene, 1, i))) {
                    OFFSCREEN_RECORD_AT(scene, 1, i)->frame = 0;
                    g_Minigame.toyField_reelPos[i]++;
                    if (g_Minigame.toyField_reelPos[i] >= 7) {
                        g_Minigame.toyField_reelPos[i] = 0;
                    }
                    switch (g_Minigame.toyField_reelHudStage[i]) {
                        case 0:
                            if (g_Minigame.toyField_reelState[i] >= 1) {
                                OFFSCREEN_RECORD_AT(scene, 1, i)->elementIndex = 0x1F;
                                g_Minigame.toyField_reelHudStage[i] = 1;
                            }
                            break;
                        case 1:
                            if (g_Minigame.toyField_reelState[i] >= 2 &&
                                g_Minigame.toyField_reelTarget[i] == lbl_3_data_189C4[i][(g_Minigame.toyField_reelPos[i] + 1) % 7]) {
                                OFFSCREEN_RECORD_AT(scene, 1, i)->elementIndex = 0x20;
                                g_Minigame.toyField_reelHudStage[i] = 2;
                            }
                            break;
                        case 2:
                            if (g_Minigame.toyField_reelTarget[i] == lbl_3_data_189C4[i][g_Minigame.toyField_reelPos[i]]) {
                                OFFSCREEN_RECORD_AT(scene, 1, i)->playMode = UI_PLAY_STOP;
                                g_Minigame.toyField_reelState[i] = 3;
                                toyFieldPlayHazardSound(3, 6);
                                if (i == 2) {
                                    sndFXKeyOff(scene->sndHandle);
                                    sndFXCtrl(scene->sndHandle, 7, 0);
                                    scene->sndHandle = SND_ID_ERROR;
                                }
                                g_Minigame.toyField_reelHudStage[i] = 3;
                            }
                            break;
                        case 3:
                            break;
                    }
                }
                i++;
            } while (i < 3);
            count = 0;
            i = 0;
            do {
                if (g_Minigame.toyField_reelHudStage[i] == 3) {
                    count++;
                }
                i++;
            } while (i < 3);
            if (count >= 3) {
                scene->state = 3;
            }
            break;
        case 3:
            i = 0;
            do {
                OFFSCREEN_RECORD_AT(scene, 5, i)->playMode = UI_PLAY_FORWARD;
                i++;
            } while (i < 3);
            switch (g_Minigame.toyField_slotEvent) {
                case 0:
                case 3:
                case 4:
                case 5:
                    g_Minigame.toyField_slotStage = 1;
                    scene->state = 4;
                    break;
                case 1:
                case 2:
                case 6:
                case 7:
                case 8:
                    g_Minigame.toyField_slotStage = 2;
                    scene->state = 8;
                    break;
            }
            break;
        case 4:
            if (OFFSCREEN_RECORD(scene, 5)->unk69[0] == 2) {
                scene->state = 5;
            }
            break;
        case 5:
            OFFSCREEN_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
            OFFSCREEN_RECORD(scene, 12)->playMode = UI_PLAY_BACKWARD;
            OFFSCREEN_RECORD(scene, 13)->playMode = UI_PLAY_BACKWARD;
            scene->state = 6;
            break;
        case 6:
            if ((OFFSCREEN_RECORD(scene, 0)->frame >> 16) == 0 && (OFFSCREEN_RECORD(scene, 12)->frame >> 16) == 0 &&
                (OFFSCREEN_RECORD(scene, 13)->frame >> 16) == 0) {
                switch (g_Minigame.toyField_slotEvent) {
                    case 0:
                        insertGraphicDrawingFunction(fn_3_ECD48, 2);
                        break;
                    case 3:
                        ((MinigameHudScene*)insertGraphicDrawingFunction(fn_3_EC804, 2))->_18 = 0;
                        break;
                    case 4:
                        ((MinigameHudScene*)insertGraphicDrawingFunction(fn_3_EC804, 2))->_18 = 1;
                        break;
                    case 5:
                        insertGraphicDrawingFunction(fn_3_ECBB0, 2);
                        break;
                }
                scene->state = 7;
            }
            break;
        case 7:
            break;
        case 8:
            break;
    }
    i = 0;
    do {
        int frame = lbl_3_data_189C4[i][g_Minigame.toyField_reelPos[i]];

        load_Icon(scene, 5 + i, 1, 0x21, lbl_3_data_19B88[frame]);
        load_Icon(scene, 5 + i, 2, 0x22, lbl_3_data_19B88[frame]);
        frame = lbl_3_data_189C4[i][(g_Minigame.toyField_reelPos[i] + 1) % 7];
        load_Icon(scene, 8 + i, 1, 0x21, lbl_3_data_19B88[frame]);
        load_Icon(scene, 8 + i, 2, 0x22, lbl_3_data_19B88[frame]);
        i++;
    } while (i < 3);
}

// .text:0x000EBFD4 size:0x40
u32 fn_3_EBFD4(void) {
    if (animRelated[0x96] != 0 || g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL ||
        g_GameLogic.gameStatus == GAME_STATUS_TRANSITION) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000EB6E0 size:0x8F4
void fn_3_EB6E0(void) {
    DrawingSceneStruct* node = currentDrawingItem;
    MinigameHudScene* scene = (MinigameHudScene*)node;
    u32 changed = FALSE;
    u32 i;
    u32 count;

    if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_NONE) {
        if (fn_3_12536C()) {
            removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
            removeCurrentDrawingItem();
            return;
        }
    } else if (fn_3_EBFD4()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
        case 0:
            addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_19B98);
            if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_NONE) {
                i = 0;
                do {
                    OFFSCREEN_RECORD_AT(scene, 1, i)->frame = 0;
                    i++;
                } while (i < 4);
            } else {
                i = 0;
                do {
                    OFFSCREEN_RECORD_AT(scene, 1, i)->frame = 0x10000;
                    i++;
                } while (i < 4);
            }
            i = 0;
            do {
                OFFSCREEN_RECORD_AT(scene, 0x29, i)->flags &= ~UI_FLAG_VISIBLE;
                i++;
            } while (i < 4);
            scene->_1E = g_Minigame.turnNumberWithinRound;
            OFFSCREEN_RECORD(scene, 0)->elementIndex =
                lbl_3_data_1A158[g_Batter.batterHand + (g_Minigame.miniGameNumberOfParticipants - 1) * 2];
            scene->_20 = 0;
            if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_NONE &&
                (g_Scores.Inning != 1 || g_Minigame.turnNumberWithinRound != 0)) {
                scene->_1E--;
                OFFSCREEN_RECORD(scene, 0)->frame = 0xA0000;
                scene->_20 = 1;
            }
            scene->state = 1;
            break;
        case 1:
            g_Minigame.toyField_pointsCountingInd = 0;
            i = 0;
            do {
                int slot = g_Minigame.playerSlots.playOrder[(scene->_1E + i) % g_Minigame.miniGameNumberOfParticipants];
                int diff = g_Minigame.miniGameCurrentPoints[slot] - g_Minigame.minigamePoints_current_Latest[slot][0];
                if (diff < 0) {
                    int step = diff / 8;
                    g_Minigame.toyField_pointsCountingInd = 1;
                    if (step != 0) {
                        g_Minigame.minigamePoints_current_Latest[slot][0] += step;
                    } else {
                        g_Minigame.minigamePoints_current_Latest[slot][0] += diff / ABS(diff);
                    }
                    changed = TRUE;
                }
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            if (g_Minigame.toyField_pointsCountingInd == 0) {
                i = 0;
                do {
                    if (g_Minigame.miniGameCurrentPoints[i] != g_Minigame.minigamePoints_current_Latest[i][0]) {
                        g_Minigame.toyField_pointsCountingInd = 1;
                        scene->state = 2;
                    }
                    i++;
                } while (i < g_Minigame.miniGameNumberOfParticipants);
            }
            break;
        case 2:
            g_Minigame.toyField_pointsCountingInd = 0;
            i = 0;
            do {
                int slot = g_Minigame.playerSlots.playOrder[(scene->_1E + i) % g_Minigame.miniGameNumberOfParticipants];
                int diff = g_Minigame.miniGameCurrentPoints[slot] - g_Minigame.minigamePoints_current_Latest[slot][0];
                if (diff > 0) {
                    int step = diff / 8;
                    g_Minigame.toyField_pointsCountingInd = 1;
                    ((u8*)node)[0x24 + slot] = 1;
                    if (step != 0) {
                        g_Minigame.minigamePoints_current_Latest[slot][0] += step;
                    } else {
                        g_Minigame.minigamePoints_current_Latest[slot][0] += diff / ABS(diff);
                    }
                    changed = TRUE;
                } else if (diff == 0) {
                    g_Minigame.minigamePoints_current_Latest[slot][0] = g_Minigame.miniGameCurrentPoints[slot];
                    if (((u8*)node)[0x24 + slot] != 0) {
                        ((u8*)node)[0x24 + slot] = 0;
                        OFFSCREEN_RECORD_AT(scene, 0x15, i)->frame = 0;
                        OFFSCREEN_RECORD_AT(scene, 0x15, i)->playMode = UI_PLAY_FORWARD;
                        OFFSCREEN_RECORD_AT(scene, 0x19, i * 4)->frame = 0;
                        OFFSCREEN_RECORD_AT(scene, 0x1A, i * 4)->frame = 0;
                        OFFSCREEN_RECORD_AT(scene, 0x1B, i * 4)->frame = 0;
                        OFFSCREEN_RECORD_AT(scene, 0x1C, i * 4)->frame = 0;
                    }
                }
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            if (g_Minigame.toyField_pointsCountingInd == 0) {
                i = 0;
                do {
                    if (g_Minigame.miniGameCurrentPoints[i] != g_Minigame.minigamePoints_current_Latest[i][0]) {
                        g_Minigame.toyField_pointsCountingInd = 1;
                    }
                    i++;
                } while (i < g_Minigame.miniGameNumberOfParticipants);
                scene->state = 1;
            }
            break;
    }
    switch (scene->_20) {
        case 0:
            if (fn_3_125424(scene, 0, 10)) {
                scene->_20 = 2;
            }
            break;
        case 1:
            if (lbl_8037169C[0x10] == 0) {
                OFFSCREEN_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                if (toyFieldRecordDone(OFFSCREEN_RECORD(scene, 0))) {
                    OFFSCREEN_RECORD(scene, 0)->playMode = UI_PLAY_STOP;
                    OFFSCREEN_RECORD(scene, 0)->frame = 0xA0000;
                    scene->_1E++;
                    scene->_20 = 2;
                }
            }
            break;
        case 2:
            if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
                if (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT || g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
                    fn_3_125424(scene, 0, 10);
                } else {
                    int leader;
                    u32 tied;

                    fn_3_125424(scene, 0, 0);
                    leader = minigame_getLeadingPlayer();
                    tied = minigame_displayedPointsAllTied();
                    i = 0;
                    do {
                        int slot =
                            g_Minigame.playerSlots.playOrder[(scene->_1E + i) % g_Minigame.miniGameNumberOfParticipants];
                        int character = g_Minigame.minigameControlStruct[0].characterIndex[slot];
                        u32 points;

                        load_Icon(scene, 5 + i, 1, 0x65, character);
                        OFFSCREEN_RECORD_AT(scene, 0xD, i)->frame = inMemRoster[0][character].stats.CharID << 16;
                        points = g_Minigame.minigamePoints_current_Latest[slot][0];
                        if ((OFFSCREEN_RECORD_AT(scene, 1, i)->frame >> 16) == 0) {
                            if (points > 9999) {
                                points = 9999;
                            }
                        } else if (points > 999) {
                            points = 999;
                        }
                        load_Icon(scene, 0x19 + i * 4, 1, 0x66, points % 10000 / 1000);
                        load_Icon(scene, 0x1A + i * 4, 1, 0x66, points % 1000 / 100);
                        load_Icon(scene, 0x1B + i * 4, 1, 0x66, points % 100 / 10);
                        load_Icon(scene, 0x1C + i * 4, 1, 0x66, points % 10);
                        if (tied == 0 && g_Minigame.minigamePoints_current_Latest[slot][0] ==
                                             g_Minigame.minigamePoints_current_Latest[leader][0]) {
                            OFFSCREEN_RECORD_AT(scene, 0x29, i)->flags |= UI_FLAG_VISIBLE;
                        } else {
                            OFFSCREEN_RECORD_AT(scene, 0x29, i)->flags &= ~UI_FLAG_VISIBLE;
                        }
                        i++;
                    } while (i < g_Minigame.miniGameNumberOfParticipants);
                }
            }
            break;
    }
    if (changed && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_NONE) {
        sndFXStartEx(0x1C0, lbl_800EFBA4[9], 0x3F, 0);
    }
}

// .text:0x000EB684 size:0x5C
u32 fn_3_EB684(void) {
    if (animRelated[0x96] != 0 || animRelated[0xB7] != 0) {
        return TRUE;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_AT_BAT && g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL &&
        g_GameLogic.gameStatus != GAME_STATUS_PAUSED) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000EAEF4 size:0x790
void fn_3_EAEF4(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    MiniGameStruct* mg = &g_Minigame;
    BOOL changed = FALSE;
    u32 i;
    int leader;
    int tied;

    if (fn_3_EB684()) {
        animRelated[0xD6] = 0;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
        case 0: {
            u8* p = mg->hudPulseInd;
            i = 0;
            do {
                *p = 0;
                p++;
                i++;
            } while (i < 4);
        }
            animRelated[0xD6] = 1;
            animRelated[0xB7] = 0;
            addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_1A168);
            i = 0;
            do {
                int character = g_Minigame.minigameControlStruct[0].characterIndex[i];

                load_Icon(scene, 9 + i, 1, 0x65, character);
                OFFSCREEN_RECORD_AT(scene, 0x11, i)->frame = inMemRoster[0][character].stats.CharID << 16;
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            i = 0;
            do {
                OFFSCREEN_RECORD_AT(scene, 0x29, i)->flags &= ~UI_FLAG_VISIBLE;
                i++;
            } while (i < 4);
            scene->state = 1;
            break;
        case 1:
            g_Minigame.toyField_pointsCountingInd = 0;
            i = 0;
            do {
                int diff = g_Minigame.miniGameCurrentPoints[i] - g_Minigame.minigamePoints_current_Latest[i][0];
                if (diff < 0) {
                    g_Minigame.toyField_pointsCountingInd = 1;
                    if ((OFFSCREEN_RECORD(scene, 0)->frame >> 16) >= 10) {
                        int step = diff / 8;
                        if (step != 0) {
                            g_Minigame.minigamePoints_current_Latest[i][0] += step;
                        } else {
                            g_Minigame.minigamePoints_current_Latest[i][0] += diff / ABS(diff);
                        }
                        changed = TRUE;
                    }
                }
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            if (g_Minigame.toyField_pointsCountingInd == 0) {
                i = 0;
                do {
                    if (g_Minigame.miniGameCurrentPoints[i] != g_Minigame.minigamePoints_current_Latest[i][0]) {
                        g_Minigame.toyField_pointsCountingInd = 1;
                        scene->state = 2;
                    }
                    i++;
                } while (i < g_Minigame.miniGameNumberOfParticipants);
            }
            break;
        case 2:
            g_Minigame.toyField_pointsCountingInd = 0;
            i = 0;
            do {
                int diff = g_Minigame.miniGameCurrentPoints[i] - g_Minigame.minigamePoints_current_Latest[i][0];
                if (diff > 0) {
                    g_Minigame.toyField_pointsCountingInd = 1;
                    scene->scratch[i] = 1;
                    if ((OFFSCREEN_RECORD(scene, 0)->frame >> 16) >= 10) {
                        int step = diff / 8;
                        if (step != 0) {
                            g_Minigame.minigamePoints_current_Latest[i][0] += step;
                        } else {
                            g_Minigame.minigamePoints_current_Latest[i][0] += diff / ABS(diff);
                        }
                        changed = TRUE;
                    }
                } else if (diff == 0 && scene->scratch[i] != 0) {
                    scene->scratch[i] = 0;
                    OFFSCREEN_RECORD_AT(scene, 0x19, i)->frame = 0;
                    OFFSCREEN_RECORD_AT(scene, 0x19, i)->playMode = UI_PLAY_FORWARD;
                    OFFSCREEN_RECORD_AT(scene, 0x1D, i * 3)->frame = 0;
                    OFFSCREEN_RECORD_AT(scene, 0x1E, i * 3)->frame = 0;
                    OFFSCREEN_RECORD_AT(scene, 0x1F, i * 3)->frame = 0;
                }
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            if (g_Minigame.toyField_pointsCountingInd == 0) {
                i = 0;
                do {
                    if (g_Minigame.miniGameCurrentPoints[i] != g_Minigame.minigamePoints_current_Latest[i][0]) {
                        g_Minigame.toyField_pointsCountingInd = 1;
                    }
                    i++;
                } while (i < g_Minigame.miniGameNumberOfParticipants);
                scene->state = 1;
            }
            break;
    }
    if (g_UnkSound_32718._07 == 5) {
        scene->_22 = 1;
    }
    OFFSCREEN_RECORD(scene, 0)->elementIndex = lbl_3_data_1A728[(s8)g_Minigame.toyField_turnPlayer];
    if (scene->_22 != 0) {
        OFFSCREEN_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
    } else {
        fn_3_125424(scene, 0, 10);
    }
    leader = minigame_getLeadingPlayer();
    tied = minigame_displayedPointsAllTied();
    i = 0;
    do {
        u32 points = g_Minigame.minigamePoints_current_Latest[i][0];

        if (points > 999) {
            points = 999;
        }
        load_Icon(scene, 0x1D + i * 3, 1, 0x66, points % 1000 / 100);
        load_Icon(scene, 0x1E + i * 3, 1, 0x66, points % 100 / 10);
        load_Icon(scene, 0x1F + i * 3, 1, 0x66, points % 10);
        if (tied == 0 &&
            g_Minigame.minigamePoints_current_Latest[i][0] == g_Minigame.minigamePoints_current_Latest[leader][0]) {
            OFFSCREEN_RECORD_AT(scene, 0x29, i)->flags |= UI_FLAG_VISIBLE;
        } else {
            OFFSCREEN_RECORD_AT(scene, 0x29, i)->flags &= ~UI_FLAG_VISIBLE;
        }
        i++;
    } while (i < g_Minigame.miniGameNumberOfParticipants);
    i = 0;
    do {
        u8 state = mg->hudPulseInd[i];

        if (state != 0) {
            switch (state) {
                case 1:
                    OFFSCREEN_RECORD_AT(scene, 0xD, i)->elementIndex = 0x60;
                    break;
                case 2:
                    OFFSCREEN_RECORD_AT(scene, 0xD, i)->elementIndex = 0x61;
                    break;
            }
            OFFSCREEN_RECORD_AT(scene, 0xD, i)->frame = 0;
            OFFSCREEN_RECORD_AT(scene, 0xD, i)->playMode = UI_PLAY_FORWARD;
            mg->hudPulseInd[i] = 0;
        }
        i++;
    } while (i < g_Minigame.miniGameNumberOfParticipants);
    if (changed && g_Minigame.toyField_coinsRemaining == 0) {
        sndFXStartEx(0x1C0, lbl_800EFBA4[9], 0x3F, 0);
    }
}

// .text:0x000EA8FC size:0x5F8
void fn_3_EA8FC(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int slot;
    int points;
    int icon;
    u32 i;

    if (scene->_18 != 0) {
        if (fn_3_EB684()) {
            animRelated[0xD6] = 0;
            removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
            removeCurrentDrawingItem();
            return;
        }
    } else if (fn_3_EBFD4()) {
        animRelated[0xD6] = 0;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
        case 0:
            addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_1A730);
            if (scene->_18 != 0) {
                OFFSCREEN_RECORD(scene, 0)->frame = 0xA0000;
            } else {
                OFFSCREEN_RECORD(scene, 0)->elementIndex =
                    lbl_3_data_1A158[g_Batter.batterHand + (g_Minigame.miniGameNumberOfParticipants - 1) * 2];
                OFFSCREEN_RECORD(scene, 0)->frame = 0xA0000;
                OFFSCREEN_RECORD(scene, 1)->elementIndex = 0x58;
                OFFSCREEN_RECORD(scene, 2)->elementIndex = 0x58;
                OFFSCREEN_RECORD(scene, 3)->elementIndex = 0x58;
                OFFSCREEN_RECORD(scene, 4)->elementIndex = 0x58;
            }
            scene->state = 1;
            break;
        case 1:
            i = 0;
            do {
                if (scene->_18 != 0) {
                    slot = i;
                } else {
                    slot = g_Minigame.playerSlots
                               .playOrder[(g_Minigame.turnNumberWithinRound + i) % g_Minigame.miniGameNumberOfParticipants];
                }
                points = g_Minigame.minigamePoints_current_Latest[slot][1];
                if (points != 0) {
                    if (points < 0) {
                        points *= -1;
                        icon = 0x59;
                    } else {
                        icon = 0x5A;
                    }
                    if (points > 999) {
                        points = 999;
                    }
                    if (scene->_18 != 0) {
                        if (points >= 100) {
                            OFFSCREEN_RECORD_AT(scene, 1, i)->frame = 2 << 16;
                        } else if (points >= 10) {
                            OFFSCREEN_RECORD_AT(scene, 1, i)->frame = 1 << 16;
                        } else {
                            OFFSCREEN_RECORD_AT(scene, 1, i)->frame = 0;
                        }
                    } else if (points >= 100) {
                        OFFSCREEN_RECORD_AT(scene, 1, i)->frame = ((g_Batter.batterHand != 0 ? 0 : 3) + 2) << 16;
                    } else if (points >= 10) {
                        OFFSCREEN_RECORD_AT(scene, 1, i)->frame = ((g_Batter.batterHand != 0 ? 0 : 3) + 1) << 16;
                    } else {
                        OFFSCREEN_RECORD_AT(scene, 1, i)->frame = (g_Batter.batterHand != 0 ? 0 : 3) << 16;
                    }
                    load_Icon(scene, 5 + i * 4, 1, icon, 0xB);
                    load_Icon(scene, 6 + i * 4, 1, icon, points % 1000 / 100);
                    load_Icon(scene, 7 + i * 4, 1, icon, points % 100 / 10);
                    load_Icon(scene, 8 + i * 4, 1, icon, points % 10);
                    if (g_Minigame.toyField_pointsCountingInd != 0) {
                        fn_3_125424(scene, 5 + i * 4, 8);
                        fn_3_125424(scene, 6 + i * 4, 8);
                        fn_3_125424(scene, 7 + i * 4, 8);
                        fn_3_125424(scene, 8 + i * 4, 8);
                    } else {
                        OFFSCREEN_RECORD_AT(scene, 5, i * 4)->playMode = UI_PLAY_FORWARD;
                        OFFSCREEN_RECORD_AT(scene, 6, i * 4)->playMode = UI_PLAY_FORWARD;
                        OFFSCREEN_RECORD_AT(scene, 7, i * 4)->playMode = UI_PLAY_FORWARD;
                        OFFSCREEN_RECORD_AT(scene, 8, i * 4)->playMode = UI_PLAY_FORWARD;
                    }
                }
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            break;
    }
}

// .text:0x000EA454 size:0x4A8
void fn_3_EA454(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u8 order[4][2];
    u32 i;
    u32 j;

    if (animRelated[0x96] != 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && pauseControl[0x1D2] == 5) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_POST_MENU &&
               (pauseControl[0x1D2] == 7 || g_GameLogic.framesOfExitingToMenu != 0)) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus == GAME_STATUS_0x26) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else if (g_GameLogic.gameStatus == GAME_STATUS_0x24) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else {
        switch (scene->state) {
            case 0:
                addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_1A9F0);
                OFFSCREEN_RECORD(scene, 0)->elementIndex = lbl_3_data_1AF70[g_Minigame.GameMode_MiniGame];
                if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_NONE && g_Minigame.multiPlayerInd == 0 &&
                    g_Minigame.grandPrixInd == 0) {
                    if (g_Minigame.challengeModeInd != 0) {
                        OFFSCREEN_RECORD(scene, 1)->elementIndex = lbl_3_data_1AF88[g_Minigame.soloMinigameDifficulty];
                    } else {
                        OFFSCREEN_RECORD(scene, 1)->elementIndex = lbl_3_data_1AF80[g_Minigame.soloMinigameDifficulty];
                    }
                } else {
                    OFFSCREEN_RECORD(scene, 1)->elementIndex = 0x175;
                }
                minigame_rankPlayers(order, 0);
                OFFSCREEN_RECORD(scene, 2)->elementIndex =
                    lbl_3_data_1AF90[g_Minigame.miniGameNumberOfParticipants - 1];
                i = 0;
                do {
                    int character = g_Minigame.minigameControlStruct[0].characterIndex[i];

                    OFFSCREEN_RECORD_AT(scene, 3, i)->frame = lbl_3_data_1AF98[g_Minigame.GameMode_MiniGame] << 16;
                    OFFSCREEN_RECORD_AT(scene, 7, i)->frame = character << 16;
                    if (minigame_pointsAllTied()) {
                        OFFSCREEN_RECORD_AT(scene, 0x13, i)->elementIndex = 0x175;
                    } else {
                        j = 0;
                        do {
                            if (i == order[j][0]) {
                                OFFSCREEN_RECORD_AT(scene, 0x13, i)->elementIndex = lbl_3_data_1AFA8[order[j][1]];
                                break;
                            }
                            j++;
                        } while (j < g_Minigame.miniGameNumberOfParticipants);
                    }
                    {
                        s16 points = g_Minigame.miniGameCurrentPoints[i];
                        s16 limit = lbl_80109410[g_Minigame.GameMode_MiniGame];
                        int value;

                        if (points > limit) {
                            points = limit;
                        }
                        value = points;
                        load_Icon(scene, 0x1B + i * 4, 1, 0x66, value % 10000 / 1000);
                        load_Icon(scene, 0x1C + i * 4, 1, 0x66, value % 1000 / 100);
                        load_Icon(scene, 0x1D + i * 4, 1, 0x66, value % 100 / 10);
                        load_Icon(scene, 0x1E + i * 4, 1, 0x66, value % 10);
                    }
                    i++;
                } while (i < g_Minigame.miniGameNumberOfParticipants);
                scene->state = 1;
                break;
            case 1:
                break;
        }
    }
}

// .text:0x000EA340 size:0x114
void toyfield_offScreenCharacterImage_loadFn(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int i;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_900C);
    for (i = 0; i < 3; i++) {
        int slot = g_Minigame.minigameControlStruct[1].aIStrength[2 + i];

        if ((s8)slot >= 0) {
            int frame = g_Minigame.minigameControlStruct[0].characterIndex[(s8)slot] << 16;

            OFFSCREEN_RECORD_AT(scene, 3, i)->frame = frame;
            OFFSCREEN_RECORD_AT(scene, 6, i)->frame = frame;
            OFFSCREEN_RECORD_AT(scene, 9, i)->frame =
                inMemRoster[0][(s8)g_Minigame.minigameControlStruct[1].aIStrength[2 + i]].stats.CharID << 16;
        }
    }
    scene->_18 = 0;
    currentDrawingItem->func = toyfield_offScreenCharacterImage;
}

// .text:0x000E9D30 size:0x610 mapped:0x80728DC4
void toyfield_offScreenCharacterImage(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    VecXYZ pos;
    int sx;
    int sy;
    int px;
    int py;
    int alphaX;
    int alphaY;
    int i;
    int dir;
    int k;
    int dx;
    int dz;
    int slot;

    if (animRelated[0x96] == 0 && g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_Minigame.toyField_turnEndState == 0 &&
        g_Minigame.turnOverStatus == 0) {
        s16* bounds = lbl_3_data_D638;

        for (i = 0; i < 3; i++) {
            slot = g_Minigame.minigameControlStruct[1].aIStrength[2 + i];
            if ((s8)slot < 0) {
                continue;
            }
            dir = -1;
            alphaX = 0xFF;
            alphaY = 0xFF;
            getAnimRelatedCoordinates(g_Minigame.minigameControlStruct[0].characterIndex[(s8)slot], 4, &pos);
            if (!fn_3_1650C(&sx, &sy, FALSE, pos.x, pos.y, pos.z)) {
                for (k = 0; k < 3; k++) {
                    dx = g_pCamera->_284C.x - pos.x;
                    dz = g_pCamera->_284C.z - pos.z;
                    dx *= 0.2f;
                    dz *= 0.2f;
                    pos.x += dx;
                    pos.z += dz;
                    if (fn_3_1650C(&sx, &sy, FALSE, pos.x, pos.y, pos.z)) {
                        break;
                    }
                }
            }

            if (sx <= (px = bounds[1])) {
                dir = 2;
                if (sx > lbl_3_data_D638[0]) {
                    alphaX = 255.0f * (1.0f - (f32)(sx - lbl_3_data_D638[0]) / (f32)(px - lbl_3_data_D638[0]));
                }
            } else if (sx >= (px = bounds[3])) {
                dir = 5;
                if (sx < bounds[2]) {
                    alphaX = 255.0f * (1.0f - (f32)(sx - bounds[2]) / (f32)(px - bounds[2]));
                }
            } else {
                px = sx;
            }
            if (alphaX > 0xFF) {
                alphaX = 0xFF;
            }

            if (sy <= (py = bounds[5])) {
                dir += 1;
                if (sy > bounds[4]) {
                    alphaY = 255.0f * (1.0f - (f32)(sy - bounds[4]) / (f32)(py - bounds[4]));
                }
            } else if (sy >= (py = bounds[7])) {
                dir += 2;
                if (sy < bounds[6]) {
                    alphaY = 255.0f * (1.0f - (f32)(sy - bounds[6]) / (f32)(py - bounds[6]));
                }
            } else {
                py = sy;
            }
            if (alphaY > 0xFF) {
                alphaY = 0xFF;
            }

            if (dir < 0 || alphaX <= 0 || alphaY <= 0) {
                OFFSCREEN_RECORD(scene, i)->flags &= ~UI_FLAG_VISIBLE;
                continue;
            }
            OFFSCREEN_RECORD(scene, i)->flags |= UI_FLAG_VISIBLE;
            OFFSCREEN_RECORD(scene, i)->pos.x = px;
            OFFSCREEN_RECORD(scene, i)->pos.y = py;
            if (dir == 2 || dir == 5) {
                OFFSCREEN_RECORD(scene, i)->rgba = alphaX | (OFFSCREEN_RECORD(scene, i)->rgba & ~0xFF);
            } else if (dir >= 2) {
                if (alphaX > alphaY) {
                    OFFSCREEN_RECORD(scene, i)->rgba = alphaX | (OFFSCREEN_RECORD(scene, i)->rgba & ~0xFF);
                } else {
                    OFFSCREEN_RECORD(scene, i)->rgba = alphaY | (OFFSCREEN_RECORD(scene, i)->rgba & ~0xFF);
                }
            } else {
                OFFSCREEN_RECORD(scene, i)->rgba = alphaY | (OFFSCREEN_RECORD(scene, i)->rgba & ~0xFF);
            }
            OFFSCREEN_RECORD(scene, i)->frame = lbl_3_data_91AC[dir] << 16;
        }
    } else {
        animRelated[0x97] = 0;
        removeGraphicsElementFromScene(currentDrawingItem);
        removeCurrentDrawingItem();
    }
}

// .text:0x000E911C size:0xC14
#define NODE_SHOWN(i) (((u16*)node)[0x12 + (i)])
void minigame_pointsTally(void) {
    DrawingSceneStruct* node = currentDrawingItem;
    MinigameHudScene* scene = (MinigameHudScene*)node;
    u8 order[8][2];
    u32 tick = FALSE;
    u32 i;
    u32 j;
    u32 count;

    if (scene->_18 != 0) {
        if (animRelated[0x96] != 0 || g_GameLogic.gameStatus != GAME_STATUS_0x26) {
            removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
            removeCurrentDrawingItem();
            return;
        }
    } else if (animRelated[0x96] != 0 || g_GameLogic.gameStatus != GAME_STATUS_INNING_TRANSITION) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
        case 0:
            addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_1AFB0);
            if (scene->_18 != 0) {
                if (g_Minigame.grandPrixRound >= 6) {
                    OFFSCREEN_RECORD(scene, 0)->elementIndex = 0x170;
                    callSfx(lbl_3_data_81FC[0x36]);
                } else {
                    OFFSCREEN_RECORD(scene, 0)->elementIndex = 0x16F;
                    callSfx(lbl_3_data_81FC[0x25]);
                }
            } else {
                if (g_Minigame.toyField_turnNumber == 0) {
                    OFFSCREEN_RECORD(scene, 0)->elementIndex = 0x171;
                } else {
                    OFFSCREEN_RECORD(scene, 0)->elementIndex = 0x16F;
                }
                toyFieldPlayHazardSound(0xE, 0x1C);
            }
            if (scene->_18 != 0) {
                scene->_1E = 0;
            } else {
                scene->_1E = 2;
            }
            i = 0;
            do {
                OFFSCREEN_RECORD_AT(scene, 0x38, i)->flags &= ~UI_FLAG_VISIBLE;
                i++;
            } while (i < 4);
            if (scene->_1E == 2 && g_Minigame.toyField_turnNumber == 0) {
                OFFSCREEN_RECORD(scene, 0x1B)->flags &= ~UI_FLAG_VISIBLE;
                i = 0;
                do {
                    OFFSCREEN_RECORD_AT(scene, 0x1C, i)->flags &= ~UI_FLAG_VISIBLE;
                    i++;
                } while (i < 4);
            }
            scene->state = 1;
            break;
        case 1:
            if (scene->_18 != 0) {
                if (scene->_20 != 0) {
                    minigame_rankPlayers(order, 1);
                } else {
                    minigame_rankPlayers(order, 2);
                }
            } else {
                minigame_rankPlayers(order, 0);
            }
            if (scene->_18 == 0 && g_Minigame.toyField_turnNumber == 0) {
                OFFSCREEN_RECORD(scene, 2)->elementIndex = 0x183;
            } else {
                OFFSCREEN_RECORD(scene, 2)->elementIndex = 0x184;
            }
            OFFSCREEN_RECORD(scene, 2)->frame = 0;
            OFFSCREEN_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
            i = 0;
            do {
                int player = order[i][0];
                int slot = g_Minigame.playerSlots.characterIndex[player];

                OFFSCREEN_RECORD_AT(scene, 3, i)->frame = scene->_1E << 16;
                OFFSCREEN_RECORD_AT(scene, 7, i)->frame = slot << 16;
                OFFSCREEN_RECORD_AT(scene, 0xF, i * 2)->frame = inMemRoster[0][slot].stats.CharID << 16;
                OFFSCREEN_RECORD_AT(scene, 0x10, i * 2)->frame = inMemRoster[0][slot].stats.CharID << 16;
                OFFSCREEN_RECORD_AT(scene, 0x17, i)->elementIndex = lbl_3_data_1B7D0[order[i][1]];
                OFFSCREEN_RECORD_AT(scene, 0x1C, i)->elementIndex = lbl_3_data_1AFA8[order[i][1]];
                if (scene->_18 != 0) {
                    if (scene->_20 != 0) {
                        NODE_SHOWN(i) = g_Minigame.grandPrixTotals[player];
                    } else {
                        NODE_SHOWN(i) = g_Minigame.grandPrixPrevTotals[player];
                    }
                } else {
                    NODE_SHOWN(i) = g_Minigame.miniGameCurrentPoints[player];
                }
                OFFSCREEN_RECORD_AT(scene, 0x24, i * 3)->frame = 0;
                OFFSCREEN_RECORD_AT(scene, 0x25, i * 3)->frame = 0;
                OFFSCREEN_RECORD_AT(scene, 0x26, i * 3)->frame = 0;
                OFFSCREEN_RECORD_AT(scene, 0x24, i * 3)->playMode = UI_PLAY_FORWARD;
                OFFSCREEN_RECORD_AT(scene, 0x25, i * 3)->playMode = UI_PLAY_FORWARD;
                OFFSCREEN_RECORD_AT(scene, 0x26, i * 3)->playMode = UI_PLAY_FORWARD;
                if (scene->_18 != 0 && scene->_20 == 0) {
                    NODE_SHOWN(4 + i) = g_Minigame.grandPrixTotals[player] - g_Minigame.grandPrixPrevTotals[player];
                    count = NODE_SHOWN(4 + i);
                    if (count > 99) {
                        count = 99;
                    }
                    if (count >= 10) {
                        load_Icon(scene, 0x3C + i, 1, 0x174, 0xB);
                    } else {
                        load_Icon(scene, 0x3C + i, 1, 0x174, 0xA);
                    }
                    if (count >= 10) {
                        load_Icon(scene, 0x3C + i, 2, 0x174, (count % 100) / 10);
                    } else {
                        load_Icon(scene, 0x3C + i, 2, 0x174, 0xB);
                    }
                    load_Icon(scene, 0x3C + i, 3, 0x174, count % 10);
                }
                OFFSCREEN_RECORD_AT(scene, 0x3C, i)->frame = 0;
                OFFSCREEN_RECORD_AT(scene, 0x3C, i)->playMode = UI_PLAY_STOP;
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            scene->state = 2;
        case 2:
            switch (scene->_1E) {
                case 0:
                case 1:
                    if (scene->_20 != 0) {
                        if (g_GameLogic._125 >= TRANSITION_CALCULATION_TYPE_5) {
                            scene->state = 7;
                        }
                    } else if (OFFSCREEN_RECORD(scene, 2)->unk69[0] == 2) {
                        scene->state = 5;
                    }
                    break;
                case 2:
                    if (g_Minigame.toyField_turnNumber == 0) {
                        if (OFFSCREEN_RECORD(scene, 2)->unk69[0] == 2) {
                            scene->_22 = 0;
                            scene->state = 3;
                        }
                    }
                    break;
            }
            break;
        case 3:
            scene->_22++;
            if (scene->_22 >= 4) {
                scene->_22 = 0;
                scene->scratch[0x10]++;
                if (scene->scratch[0x10] >= 4) {
                    scene->scratch[0x10] = 0;
                }
                j = 0;
                do {
                    if (j == scene->scratch[0x10]) {
                        OFFSCREEN_RECORD_AT(scene, 0x38, j)->flags |= UI_FLAG_VISIBLE;
                    } else {
                        OFFSCREEN_RECORD_AT(scene, 0x38, j)->flags &= ~UI_FLAG_VISIBLE;
                    }
                    j++;
                } while (j < 4);
                if (scene->scratch[0x10] == g_Minigame.rosterID) {
                    scene->scratch[0x11]++;
                    if (scene->scratch[0x11] >= 5) {
                        OFFSCREEN_RECORD_AT(scene, 0x38, g_Minigame.rosterID)->playMode = UI_PLAY_FORWARD;
                        scene->state = 4;
                    }
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            break;
        case 5:
            i = 0;
            do {
                if (NODE_SHOWN(4 + i) != 0) {
                    UIRecord* rec = OFFSCREEN_RECORD_AT(scene, 0x3C, i);

                    if ((rec->frame >> 16) >= 9) {
                        rec->playMode = UI_PLAY_STOP;
                        scene->_22 = 0;
                        scene->state = 6;
                    } else {
                        rec->playMode = UI_PLAY_FORWARD;
                    }
                }
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            break;
        case 6:
            scene->_22++;
            if (scene->_22 >= 4) {
                i = 0;
                do {
                    if (NODE_SHOWN(4 + i) != 0) {
                        NODE_SHOWN(i)++;
                        tick = TRUE;
                        NODE_SHOWN(4 + i)--;
                    }
                    i++;
                } while (i < g_Minigame.miniGameNumberOfParticipants);
                scene->_22 = 0;
            }
            i = 0;
            do {
                if (NODE_SHOWN(4 + i) != 0) {
                    break;
                }
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            if (i >= g_Minigame.miniGameNumberOfParticipants) {
                if (g_GameLogic._125 >= TRANSITION_CALCULATION_TYPE_3) {
                    scene->state = 7;
                }
            }
            break;
        case 7:
            if (fn_3_125424(scene, 2, 0)) {
                switch (scene->_1E) {
                    case 0:
                        if (scene->_20 == 0) {
                            if (g_Minigame.grandPrixRound >= 6) {
                                scene->_1E = 1;
                            }
                            scene->_20 = 1;
                            scene->state = 1;
                        }
                        break;
                }
            }
            break;
    }
    if (scene->state >= 1) {
        i = 0;
        do {
            count = NODE_SHOWN(i);
            if (scene->_18 != 0) {
                if (count > 99) {
                    count = 99;
                }
            } else if (count > 999) {
                count = 999;
            }
            load_Icon(scene, 0x24 + i * 3, 1, 0x66, (count % 1000) / 100);
            load_Icon(scene, 0x25 + i * 3, 1, 0x66, (count % 100) / 10);
            load_Icon(scene, 0x26 + i * 3, 1, 0x66, count % 10);
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
    }
    if (tick != FALSE) {
        sndFXStartEx(0x1C1, lbl_800EFBA4[0xA], 0x3F, 0);
    }
}
#undef NODE_SHOWN
