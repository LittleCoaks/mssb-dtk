#include "Unknown/File_0x8001cbd4.h"
#include "Unknown/File_0x80023b90.h"
#include "Unknown/File_0x800beb3c.h"
#include "static/UnknownHomes_Static.h"

typedef struct {
    /* 0x00 */ u8 data[0xA];
} LightInput;

/* Per-stadium light settings; the mini-game variants follow the six stadiums. */
typedef struct {
    /* 0x00 */ LightInput lights[4];
    /* 0x28 */ u8 _28[4];
} StadiumLightInput; // size: 0x2C

typedef struct {
    /* 0x00 */ Vec dir;
    /* 0x0C */ u8 _0C[4];
} LightState; // size: 0x10

extern StadiumLightInput inputParams[];
extern LightState lbl_80367318[4];

static inline void setLightDirection(LightState* light) {
    Vec dir;

    dir.x = light->dir.x;
    dir.y = light->dir.y;
    dir.z = light->dir.z;
    PSVECNormalize(&dir, &dir);
    updateVectorInArray(0, dir);
}

static inline void loadStadiumLights(u8 stadium) {
    int i;

    for (i = 0; i < 4; i++) {
        characterLightingRelated(&inputParams[stadium].lights[i], &lbl_80367318[i]);
    }
}

void initStadiumLighting(void) {
    int stadium;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        stadium = g_d_GameSettings.StadiumID + 7;
    } else {
        stadium = g_d_GameSettings.StadiumID;
    }
    g_d_GameSettings._54 = stadium;
    loadStadiumLights(stadium);
    setLightDirection(&lbl_80367318[0]);
}
