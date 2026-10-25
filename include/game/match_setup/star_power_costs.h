#ifndef __GAME_MATCH_SETUP_STAR_POWER_COSTS_H_
#define __GAME_MATCH_SETUP_STAR_POWER_COSTS_H_

#include "mssbTypes.h"

typedef struct {
    /* 0x0 */ u8 moonShotCost;
    /* 0x1 */ u8 captainStarCost;
    /* 0x2 */ u8 nonCaptain_CaptainStarCost;
    /* 0x3 */ u8 regularStarCost;
} StarPowerCosts;

extern StarPowerCosts starPowerCosts;

#endif
