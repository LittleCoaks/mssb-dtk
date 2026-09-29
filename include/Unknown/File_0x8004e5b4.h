#ifndef __UNKNOWN_FILE_0X8004E5B4_H_
#define __UNKNOWN_FILE_0X8004E5B4_H_

#include "mssbTypes.h"

#define CHAR_SELECT_GRID_SLOTS 0x24

/* charSelectStruct (0x803C6028) as the team add/remove helpers see it. The
 * menus REL still addresses the rest of the object as a raw byte array. */
typedef struct CharSelectState {
    /* 0x00 */ u8 unk0[0x28];
    /* 0x28 */ s8 slotTeam[CHAR_SELECT_GRID_SLOTS]; // owning team per grid slot, -1 = free
    /* 0x4C */ u8 unk4C[0x48];
} CharSelectState; // size 0x94

extern CharSelectState charSelectStruct;
extern u8 characterStaticIndexes[0x144];

void add_or_RemoveCharToATeam(int team, int charID, BOOL add);

#endif // !__UNKNOWN_FILE_0X8004E5B4_H_
