#ifndef __GAME_MATCH_SETUP_STAT_BOOK_H_
#define __GAME_MATCH_SETUP_STAT_BOOK_H_

#include "mssbTypes.h"

/* The stat book's drawing-script node: firstHandle/handleCount span its
 * records in graphicsRelatedArray (see Unknown/File_0x80034e20.h); the rest is
 * the page state statBook_update animates between frames. */
typedef struct StatBookScene {
    /* 0x00 */ u8 _00[0x14];
    /* 0x14 */ u16 firstHandle;
    /* 0x16 */ u16 handleCount;
    /* 0x18 */ u16 timer;           // frames spent in the current state
    /* 0x1A */ u16 state;
    /* 0x1C */ u16 teamDisplayed;   // g_GameLogic.scoreBook_teamDisplayed as last compiled
    /* 0x1E */ u16 statsDisplayed;  // 0 = batting page, 1 = pitching page
    /* 0x20 */ u16 scrollIndex;     // first lineup slot shown
} StatBookScene;

void mvpBanner_update(void);
void mvpBanner_init(void);
void drawBookNumbers(StatBookScene* scene, int handle, int value, int type);
void compileStatsForBook(StatBookScene* scene);
void statBook_update(void);
void statBook_init(void);
void mvpScoreboard_update(void);
void mvpScoreboard_init(void);
void gameEndScene_update(void);
void gameEndScene_init(void);
void animateMVP_GameEnd(void);

#endif // !__GAME_MATCH_SETUP_STAT_BOOK_H_
