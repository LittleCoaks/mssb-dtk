#define SQRT2_LINKAGE static
#include "game/match_setup/stat_book.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "text/text_channel.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800363d8.h"
#define REP_HEADER_DATA_FN getRepHeaderData_statBook
#include "header_rep_data.h"

extern u8 animRelated[0x124];
extern u8 pauseControl[0x264];
extern u8 lineUpInfoStruct[2][9][4];
extern UIRecordDescriptor lbl_3_data_273E0[];
extern UIRecordDescriptor lbl_3_data_27420[];
extern UIRecordDescriptor lbl_3_data_274E0[];
extern u8 lbl_3_data_27C40[2][6];
extern u8 lbl_3_data_27C4C[];
extern UIRecordDescriptor lbl_3_data_27C54[];
extern u8 lbl_3_data_F430[][2];

void fn_800362F0(void* scene);
void fn_8004D0F0(void);
void manageScoreboardGraphic(void);

#define REC(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)
#define REC_AT(scene, i, off) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i) + (off)].object)

// .text:0x0015F410 size:0x164 mapped:0x8079E4A4
void animateMVP_GameEnd(void) {
    if (g_GameLogic._125 >= 3) {
        if (g_GameLogic._125 == 3) {
            animRelated[0xCF] = g_Scores.Inning;
            animRelated[0xD0] = g_Scores.halfInning;
            insertGraphicDrawingFunction(gameEndScene_init, 2);
        }
        if (g_GameLogic._125 == 4 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            insertGraphicDrawingFunction(mvpBanner_init, 2);
        }
        if (g_GameLogic._125 == 7) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
                if (pauseControl[0x1D8] == 0 && g_GameLogic._11A != 0) {
                    insertGraphicDrawingFunction(manageScoreboardGraphic, 2);
                    insertGraphicDrawingFunction(mvpScoreboard_init, 2);
                    g_GameLogic._11A = 0;
                } else if (g_GameLogic._11A != 1) {
                    insertGraphicDrawingFunction(statBook_init, 2);
                    g_GameLogic._11A = 1;
                }
            }
        } else if (g_GameLogic._125 == 5) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
                insertGraphicDrawingFunction(fn_8004D0F0, 2);
            }
        }
    }
}

// .text:0x0015F3C4 size:0x4C mapped:0x8079E458
void gameEndScene_init(void) {
    addGraphicsElementToScene(currentDrawingItem, lbl_3_data_273E0);
    currentDrawingItem->func = gameEndScene_update;
}

// .text:0x0015F380 size:0x44 mapped:0x8079E414
void gameEndScene_update(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    if (g_GameLogic._125 == 10) {
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}

// .text:0x0015F220 size:0x160 mapped:0x8079E2B4
void mvpScoreboard_init(void) {
    StatBookScene* scene = (StatBookScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_27420);
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        REC(scene, 1)->elementIndex = 0xE;
    }
    if (StatsScreenScores.mvpKind == 3) {
        REC(scene, 3)->elementIndex = 0xCC;
        REC(scene, 4)->elementIndex = 0xD0;
    } else if (StatsScreenScores.mvpKind == 2) {
        REC(scene, 3)->elementIndex = 0xCD;
        REC(scene, 4)->elementIndex = 0xD1;
    }
    if (g_d_GameSettings.exhibitionMatchInd == 0 && g_GameLogic.playOverFadeOutStarted >= 0) {
        REC(scene, 1)->elementIndex = 0x10;
    }
    scene->state = 0;
    currentDrawingItem->func = mvpScoreboard_update;
}

// .text:0x0015F088 size:0x198 mapped:0x8079E11C
void mvpScoreboard_update(void) {
    StatBookScene* scene = (StatBookScene*)currentDrawingItem;

    if (g_GameLogic._125 == 10) {
        goto remove;
    }
    if ((s8)pauseControl[0x1DA] == 0) {
        REC(scene, 1)->playMode = UI_PLAY_FORWARD;
        REC(scene, 2)->playMode = UI_PLAY_BACKWARD;
        if ((REC(scene, 2)->frame >> 16) > 10) {
            REC(scene, 2)->frame = 10 << 16;
        }
    } else {
        REC(scene, 1)->playMode = UI_PLAY_BACKWARD;
        if ((REC(scene, 1)->frame >> 16) > 10) {
            REC(scene, 1)->frame = 10 << 16;
        }
        REC(scene, 2)->playMode = UI_PLAY_FORWARD;
    }
    if (animRelated[0xCE] != 0) {
        REC(scene, 0)->playMode = UI_PLAY_BACKWARD;
        REC(scene, 3)->playMode = UI_PLAY_BACKWARD;
        REC(scene, 4)->flags &= ~UI_FLAG_VISIBLE;
        scene->state++;
        if (scene->state >= 0x2D) {
            goto remove;
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

// .text:0x0015EE2C size:0x25C mapped:0x8079DEC0
void statBook_init(void) {
    StatBookScene* scene = (StatBookScene*)currentDrawingItem;
    int team;
    int i;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_274E0);
    REC(scene, 55)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[0].captain][0];
    REC(scene, 56)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[1].captain][0];
    REC(scene, 55)->frame = g_GameLogic.logo[0].variationID << 16;
    REC(scene, 56)->frame = g_GameLogic.logo[1].variationID << 16;
    if (g_GameLogic.scoreBook_teamDisplayed == 0) {
        REC(scene, 56)->flags &= ~UI_FLAG_VISIBLE;
    } else {
        REC(scene, 55)->flags &= ~UI_FLAG_VISIBLE;
    }
    team = g_GameLogic.homeTeamInd ^ g_GameLogic.scoreBook_teamDisplayed;
    if (g_GameLogic.teamIsCPU[team] != 0) {
        load_Icon(scene, 0x39, 1, 3, g_GameLogic.teams[team] + 4);
    } else {
        load_Icon(scene, 0x39, 1, 3, g_GameLogic.teams[team]);
    }
    for (i = 0; i < 6; i++) {
        load_Icon(scene, i + 0x2B, 1, 0xF, lbl_3_data_27C40[g_GameLogic.scoreBook_batter_pitcherStatsDisplayed][i]);
    }
    if (g_GameLogic.scoreBook_batter_pitcherStatsDisplayed == 0) {
        REC(scene, 53)->frame = 5 << 16;
    } else {
        REC(scene, 53)->frame = 0x33 << 16;
    }
    animRelated[0xD2] = 0;
    scene->timer = 0;
    scene->state = 0;
    scene->teamDisplayed = g_GameLogic.scoreBook_teamDisplayed;
    scene->statsDisplayed = g_GameLogic.scoreBook_batter_pitcherStatsDisplayed;
    scene->scrollIndex = g_GameLogic.scoreBook_scrollIndex;
    compileStatsForBook(scene);
    currentDrawingItem->func = statBook_update;
}

// .text:0x0015DB44 size:0x12E8 mapped:0x8079CBD8
void statBook_update(void) {
    StatBookScene* scene = (StatBookScene*)currentDrawingItem;
    long i;
    int j;

    if (scene->timer < 0xFFFE) {
        scene->timer++;
    } else {
        scene->timer = 0xFFFF;
    }
    animRelated[0xD2] = 0;
    if (g_GameLogic._125 == 10) {
        goto remove;
    }

    if (scene->state == 0) {
        animRelated[0xD2] = 1;
        scene->state++;
    } else if (scene->state == 1) {
        animRelated[0xD2] = 1;
        if (scene->statsDisplayed == 0) {
            if ((REC(scene, 49)->frame >> 16) >= 10) {
                REC(scene, 49)->playMode = UI_PLAY_STOP;
            }
            if ((REC(scene, 50)->frame >> 16) >= 5) {
                REC(scene, 50)->playMode = UI_PLAY_STOP;
            }
        } else {
            if ((REC(scene, 49)->frame >> 16) >= 5) {
                REC(scene, 49)->playMode = UI_PLAY_STOP;
            }
            if ((REC(scene, 50)->frame >> 16) >= 10) {
                REC(scene, 50)->playMode = UI_PLAY_STOP;
            }
        }
        if ((REC(scene, 54)->frame >> 16) >= 10) {
            REC(scene, 54)->playMode = UI_PLAY_STOP;
        }
        if (scene->timer >= 30) {
            REC(scene, 0)->playMode = UI_PLAY_STOP;
            scene->state++;
        }
    } else if (scene->state == 2) {
        if (scene->scrollIndex != g_GameLogic.scoreBook_scrollIndex) {
            animRelated[0xD2] = 1;
            scene->timer = 0;
            scene->state = 7;
        } else if (scene->teamDisplayed != g_GameLogic.scoreBook_teamDisplayed) {
            animRelated[0xD2] = 1;
            scene->timer = 0;
            scene->state = 3;
        } else if (scene->statsDisplayed != g_GameLogic.scoreBook_batter_pitcherStatsDisplayed) {
            animRelated[0xD2] = 1;
            scene->timer = 0;
            scene->state = 5;
        } else if (g_GameLogic._125 == 8) {
            animRelated[0xD2] = 1;
            scene->timer = 0;
            scene->state = 9;
        }
    } else if (scene->state == 3) {
        int wrapped = 0;

        animRelated[0xD2] = 1;
        if (g_GameLogic.scoreBook_logoFadeDirectionLeft_Right == 0) {
            if (scene->timer == 1) {
                REC(scene, 54)->frame = 0x15 << 16;
                REC(scene, 54)->playMode = UI_PLAY_FORWARD;
            }
            if ((REC(scene, 54)->frame >> 16) >= 0x1F) {
                REC(scene, 54)->playMode = UI_PLAY_STOP;
                wrapped = 1;
            }
        } else {
            if (scene->timer == 1) {
                REC(scene, 54)->frame = 10 << 16;
                REC(scene, 54)->playMode = UI_PLAY_FORWARD;
            }
            if ((REC(scene, 54)->frame >> 16) >= 0x14) {
                REC(scene, 54)->playMode = UI_PLAY_STOP;
                wrapped = 1;
            }
        }
        for (i = 2; i <= 0x2A; i++) {
            REC(scene, i)->playMode = UI_PLAY_BACKWARD;
        }
        if (wrapped) {
            scene->state = 4;
            scene->timer = 0;
        }
    } else if (scene->state == 4) {
        int done = 0;

        animRelated[0xD2] = 1;
        if (scene->timer == 1) {
            int team;

            scene->teamDisplayed = g_GameLogic.scoreBook_teamDisplayed;
            if (scene->teamDisplayed == 0) {
                REC(scene, 55)->flags |= UI_FLAG_VISIBLE;
                REC(scene, 56)->flags &= ~UI_FLAG_VISIBLE;
            } else {
                REC(scene, 55)->flags &= ~UI_FLAG_VISIBLE;
                REC(scene, 56)->flags |= UI_FLAG_VISIBLE;
            }
            team = g_GameLogic.homeTeamInd ^ scene->teamDisplayed;
            if (g_GameLogic.teamIsCPU[team] != 0) {
                load_Icon(scene, 0x39, 1, 3, g_GameLogic.teams[team] + 4);
            } else {
                load_Icon(scene, 0x39, 1, 3, g_GameLogic.teams[team]);
            }
            compileStatsForBook(scene);
        }
        if (g_GameLogic.scoreBook_logoFadeDirectionLeft_Right == 1) {
            if (scene->timer == 1) {
                REC(scene, 54)->frame = 0x1F << 16;
                REC(scene, 54)->playMode = UI_PLAY_BACKWARD;
            }
            if ((REC(scene, 54)->frame >> 16) <= 0x15) {
                REC(scene, 54)->frame = 10 << 16;
                done = 1;
                REC(scene, 54)->playMode = UI_PLAY_STOP;
            }
        } else {
            if (scene->timer == 1) {
                REC(scene, 54)->frame = 0x14 << 16;
                REC(scene, 54)->playMode = UI_PLAY_BACKWARD;
            }
            if ((REC(scene, 54)->frame >> 16) <= 10) {
                REC(scene, 54)->frame = 10 << 16;
                done = 1;
                REC(scene, 54)->playMode = UI_PLAY_STOP;
            }
        }
        for (i = 2; i <= 0x2A; i++) {
            REC(scene, i)->playMode = UI_PLAY_FORWARD;
        }
        if (done) {
            scene->state = 2;
            scene->timer = 0;
        }
    } else if (scene->state == 5) {
        animRelated[0xD2] = 1;
        if (scene->timer == 1) {
            for (i = 7; i <= 0x30; i++) {
                REC(scene, i)->playMode = UI_PLAY_BACKWARD;
            }
        }
        if (scene->statsDisplayed == 0) {
            if ((REC(scene, 49)->frame >> 16) <= 5) {
                REC(scene, 49)->playMode = UI_PLAY_STOP;
            } else {
                REC(scene, 49)->playMode = UI_PLAY_BACKWARD;
            }
            if ((REC(scene, 50)->frame >> 16) >= 10) {
                REC(scene, 50)->playMode = UI_PLAY_STOP;
            } else {
                REC(scene, 50)->playMode = UI_PLAY_FORWARD;
            }
        } else {
            if ((REC(scene, 50)->frame >> 16) <= 5) {
                REC(scene, 50)->playMode = UI_PLAY_STOP;
            } else {
                REC(scene, 50)->playMode = UI_PLAY_BACKWARD;
            }
            if ((REC(scene, 49)->frame >> 16) >= 10) {
                REC(scene, 49)->playMode = UI_PLAY_STOP;
            } else {
                REC(scene, 49)->playMode = UI_PLAY_FORWARD;
            }
        }
        if (scene->timer >= 8) {
            scene->state = 6;
            scene->timer = 0;
        }
    } else if (scene->state == 6) {
        animRelated[0xD2] = 1;
        if (scene->timer == 1) {
            scene->statsDisplayed = g_GameLogic.scoreBook_batter_pitcherStatsDisplayed;
            for (i = 7; i <= 0x30; i++) {
                REC(scene, i)->playMode = UI_PLAY_FORWARD;
            }
            for (i = 0; i < 6; i++) {
                load_Icon(scene, i + 0x2B, 1, 0xF, lbl_3_data_27C40[scene->statsDisplayed][i]);
            }
            if (scene->statsDisplayed == 0) {
                REC(scene, 53)->frame = 5 << 16;
            } else {
                REC(scene, 53)->frame = 0x33 << 16;
            }
            compileStatsForBook(scene);
        }
        if (scene->timer >= 8) {
            scene->state = 2;
            scene->timer = 0;
        }
    } else if (scene->state == 7) {
        animRelated[0xD2] = 1;
        if (scene->timer == 1) {
            for (i = 2; i <= 0x2A; i++) {
                if (i != 0xC && i != 0x12 && i != 0x18 && i != 0x1E && i != 0x24 && i != 0x2A) {
                    REC(scene, i)->playMode = UI_PLAY_BACKWARD;
                }
            }
        }
        if (scene->timer >= 8) {
            scene->state = 8;
            scene->timer = 0;
        }
    } else if (scene->state == 8) {
        animRelated[0xD2] = 1;
        if (scene->timer == 1) {
            scene->scrollIndex = g_GameLogic.scoreBook_scrollIndex;
            for (i = 2; i <= 0x2A; i++) {
                REC(scene, i)->playMode = UI_PLAY_FORWARD;
            }
            compileStatsForBook(scene);
        }
        if (scene->timer >= 8) {
            scene->state = 2;
            scene->timer = 0;
        }
    } else {
        int frame;

        animRelated[0xD2] = 1;
        REC(scene, 0)->playMode = UI_PLAY_BACKWARD;
        frame = REC(scene, 0)->frame >> 16;
        if (frame == 10) {
            REC(scene, 54)->playMode = UI_PLAY_BACKWARD;
            REC(scene, 51)->playMode = UI_PLAY_BACKWARD;
            if (scene->statsDisplayed == 0) {
                REC(scene, 53)->frame = 5 << 16;
                REC(scene, 53)->playMode = UI_PLAY_BACKWARD;
            } else {
                REC(scene, 53)->frame = 0x33 << 16;
                REC(scene, 53)->playMode = UI_PLAY_FORWARD;
            }
        }
        if (frame <= lbl_3_data_27C4C[0] + 5) {
            if (scene->statsDisplayed == 0) {
                REC(scene, 49)->playMode = UI_PLAY_FORWARD;
                REC(scene, 50)->playMode = UI_PLAY_BACKWARD;
            } else {
                REC(scene, 49)->playMode = UI_PLAY_BACKWARD;
                REC(scene, 50)->playMode = UI_PLAY_FORWARD;
            }
        }
        for (i = 0; i < 5; i++) {
            if (frame <= lbl_3_data_27C4C[i] + 5) {
                REC(scene, 2 + i)->playMode = UI_PLAY_BACKWARD;
            }
        }
        for (i = 0; i < 6; i++) {
            if (frame <= lbl_3_data_27C4C[i] + 5) {
                REC_AT(scene, 0x2B, i)->playMode = UI_PLAY_BACKWARD;
            }
        }
        for (i = 0; i < 6; i++) {
            if (frame <= lbl_3_data_27C4C[i] + 5) {
                for (j = 0; j < 6; j++) {
                    REC_AT(scene, 7 + j, i * 6)->playMode = UI_PLAY_BACKWARD;
                }
            }
        }
        if ((REC(scene, 0)->frame >> 16) == 0) {
            goto remove;
        }
    }

    if (scene->state >= 2) {
        if (scene->statsDisplayed == 0) {
            if ((REC(scene, 53)->frame >> 16) >= 0x2D) {
                REC(scene, 53)->frame = 5 << 16;
            }
        } else {
            if ((REC(scene, 53)->frame >> 16) >= 0x5D) {
                REC(scene, 53)->frame = 0x33 << 16;
            }
        }
    }
    if (scene->scrollIndex == 0) {
        if ((REC(scene, 52)->frame >> 16) >= 0x12E || (REC(scene, 52)->frame >> 16) < 0xCA) {
            REC(scene, 52)->frame = 0xCA << 16;
        }
    } else if (scene->scrollIndex == 4) {
        if ((REC(scene, 52)->frame >> 16) >= 0xC9 || (REC(scene, 52)->frame >> 16) < 0x65) {
            REC(scene, 52)->frame = 0x65 << 16;
        }
    } else {
        if ((REC(scene, 52)->frame >> 16) >= 0x64) {
            REC(scene, 52)->frame = 0;
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

// .text:0x0015D1D8 size:0x96C mapped:0x8079C26C
void compileStatsForBook(StatBookScene* scene) {
    int order[5];
    int team;
    int i;
    int j;
    int sum;
    long k;
    int sumAtBats;
    int avg;
    StatisticsBatter* batting;
    StatisticsPitcher* pitching;

    team = scene->teamDisplayed ^ g_GameLogic.homeTeamInd;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 9; j++) {
            if (i + scene->scrollIndex == (s8)lineUpInfoStruct[team][j][1]) {
                order[i] = j;
                load_Icon(scene, i + 2, 1, 0xD, inMemRoster[team][j].stats.CharID);
                break;
            }
        }
    }

    if (scene->statsDisplayed == 0) {
        batting = BatterStats_P1_P2[team];
        for (i = 0; i < 5; i++) {
            StatisticsBatter* b = &batting[order[i]];

            drawBookNumbers(scene, i + 7, b->Hits, 3);
            drawBookNumbers(scene, i + 0xD, b->RBI, 3);
            drawBookNumbers(scene, i + 0x13, b->HomeRuns, 3);
            drawBookNumbers(scene, i + 0x19, b->BasesStolen, 3);
            drawBookNumbers(scene, i + 0x1F, b->StarHitsActivated, 3);
            if (b->AtBats == 0) {
                drawBookNumbers(scene, i + 0x25, 0, 0x16);
            } else {
                avg = b->Hits * 10000 / b->AtBats;
                if (avg % 10 >= 5) {
                    avg += 10;
                }
                drawBookNumbers(scene, i + 0x25, avg / 10, 10);
            }
        }
        sum = 0;
        for (k = 0; k < 9; k++) {
            sum += batting[k].Hits;
        }
        drawBookNumbers(scene, 0xC, sum, 3);
        sum = 0;
        for (k = 0; k < 9; k++) {
            sum += batting[k].RBI;
        }
        drawBookNumbers(scene, 0x12, sum, 3);
        sum = 0;
        for (k = 0; k < 9; k++) {
            sum += batting[k].HomeRuns;
        }
        drawBookNumbers(scene, 0x18, sum, 3);
        sum = 0;
        for (k = 0; k < 9; k++) {
            sum += batting[k].BasesStolen;
        }
        drawBookNumbers(scene, 0x1E, sum, 3);
        sum = 0;
        for (k = 0; k < 9; k++) {
            sum += batting[k].StarHitsActivated;
        }
        drawBookNumbers(scene, 0x24, sum, 3);
        sum = 0;
        sumAtBats = 0;
        for (k = 0; k < 9; k++) {
            sum += batting[k].Hits;
            sumAtBats += batting[k].AtBats;
        }
        avg = sum * 10000 / sumAtBats;
        if (avg % 10 >= 5) {
            avg += 10;
        }
        drawBookNumbers(scene, 0x2A, avg / 10, 10);
    } else {
        batting = BatterStats_P1_P2[team];
        pitching = PitcherStats_P1_P2[team];
        for (i = 0; i < 5; i++) {
            StatisticsBatter* b = &batting[order[i]];
            StatisticsPitcher* p = &pitching[order[i]];

            drawBookNumbers(scene, i + 7, b->BigPlays, 3);
            if (p->_00 == 0) {
                drawBookNumbers(scene, i + 0xD, 0, 0x15);
                drawBookNumbers(scene, i + 0x13, 0, 0x15);
                drawBookNumbers(scene, i + 0x19, 0, 0x15);
                drawBookNumbers(scene, i + 0x1F, 0, 0x15);
            } else {
                drawBookNumbers(scene, i + 0xD, p->_0A, 3);
                drawBookNumbers(scene, i + 0x13, p->_1C, 3);
                drawBookNumbers(scene, i + 0x19, p->runsAllowed, 3);
                drawBookNumbers(scene, i + 0x1F, p->starPitchesThrown, 3);
            }
            if (p->outsAsPitcher != 0) {
                avg = p->earnedRunsAllowed * 27000 / p->outsAsPitcher;
                if (avg % 10 >= 5) {
                    avg += 10;
                }
                avg = avg / 10;
            } else if (p->_00 != 0) {
                avg = 9999;
            } else {
                avg = 0;
            }
            if (p->_00 == 0) {
                drawBookNumbers(scene, i + 0x25, 0, 0x16);
            } else {
                drawBookNumbers(scene, i + 0x25, avg, 0xB);
            }
        }
        sum = 0;
        for (k = 0; k < 9; k++) {
            sum += batting[k].BigPlays;
        }
        drawBookNumbers(scene, 0xC, sum, 3);
        sum = 0;
        for (k = 0; k < 9; k++) {
            sum += pitching[k]._0A;
        }
        drawBookNumbers(scene, 0x12, sum, 3);
        sum = 0;
        for (k = 0; k < 9; k++) {
            sum += pitching[k]._1C;
        }
        drawBookNumbers(scene, 0x18, sum, 3);
        sum = 0;
        for (k = 0; k < 9; k++) {
            sum += pitching[k].runsAllowed;
        }
        drawBookNumbers(scene, 0x1E, sum, 3);
        sum = 0;
        for (k = 0; k < 9; k++) {
            sum += pitching[k].starPitchesThrown;
        }
        drawBookNumbers(scene, 0x24, sum, 3);
        sum = 0;
        sumAtBats = 0;
        for (k = 0; k < 9; k++) {
            sum += pitching[k].earnedRunsAllowed;
            sumAtBats += pitching[k].outsAsPitcher;
        }
        if (sumAtBats == 0) {
            avg = 9999;
        } else {
            avg = sum * 27000 / sumAtBats;
            if (avg % 10 >= 5) {
                avg += 10;
            }
            avg = avg / 10;
        }
        drawBookNumbers(scene, 0x2A, avg, 0xB);
    }
}

// .text:0x0015C6E4 size:0xAF4 mapped:0x8079B778
void drawBookNumbers(StatBookScene* scene, int handle, int value, int type) {
    fn_800362F0(scene);
    if (type == 0x15) {
        REC(scene, handle)->elementIndex = 0x10;
        load_Icon(scene, handle, 1, 0x1A, 0xE);
        load_Icon(scene, handle, 2, 0x1A, 0xE);
    } else if (type == 0x16) {
        REC(scene, handle)->elementIndex = 0x15;
        load_Icon(scene, handle, 3, 0x1A, 0xE);
        load_Icon(scene, handle, 2, 0x1A, 0xE);
        load_Icon(scene, handle, 1, 0x1A, 0xE);
        load_Icon(scene, handle, 6, 0x1A, 0xE);
        load_Icon(scene, handle, 5, 0x1A, 0xE);
        load_Icon(scene, handle, 4, 0x1A, 0xE);
    } else if (type == 10) {
        if (value >= 1000) {
            REC(scene, handle)->elementIndex = 0x18;
            load_Icon(scene, handle, 1, 0x1A, 1);
            load_Icon(scene, handle, 3, 0x1A, 0);
            load_Icon(scene, handle, 4, 0x1A, 0);
            load_Icon(scene, handle, 5, 0x1A, 0);
            load_Icon(scene, handle, 6, 0x1A, 1);
            load_Icon(scene, handle, 8, 0x1A, 0);
            load_Icon(scene, handle, 9, 0x1A, 0);
            load_Icon(scene, handle, 10, 0x1A, 0);
        } else {
            int hundreds;
            int tens;

            REC(scene, handle)->elementIndex = 0x19;
            hundreds = value / 100;
            load_Icon(scene, handle, 2, 0x1A, hundreds);
            tens = value / 10 % 10;
            load_Icon(scene, handle, 3, 0x1A, tens);
            value = value % 10;
            load_Icon(scene, handle, 4, 0x1A, value);
            load_Icon(scene, handle, 6, 0x1A, hundreds);
            load_Icon(scene, handle, 7, 0x1A, tens);
            load_Icon(scene, handle, 8, 0x1A, value);
        }
    } else if (type == 11) {
        if (value >= 1000) {
            int thousands;
            int hundreds;
            int tens;

            if (value >= 10000) {
                value = 9999;
            }
            REC(scene, handle)->elementIndex = 0x17;
            thousands = value / 1000;
            load_Icon(scene, handle, 1, 0x1A, thousands);
            hundreds = value / 100 % 10;
            load_Icon(scene, handle, 2, 0x1A, hundreds);
            tens = value / 10 % 10;
            load_Icon(scene, handle, 4, 0x1A, tens);
            value = value % 10;
            load_Icon(scene, handle, 5, 0x1A, value);
            load_Icon(scene, handle, 6, 0x1A, thousands);
            load_Icon(scene, handle, 7, 0x1A, hundreds);
            load_Icon(scene, handle, 9, 0x1A, tens);
            load_Icon(scene, handle, 10, 0x1A, value);
        } else {
            int hundreds;
            int tens;

            REC(scene, handle)->elementIndex = 0x16;
            hundreds = value / 100 % 10;
            load_Icon(scene, handle, 1, 0x1A, hundreds);
            tens = value / 10 % 10;
            load_Icon(scene, handle, 3, 0x1A, tens);
            value = value % 10;
            load_Icon(scene, handle, 4, 0x1A, value);
            load_Icon(scene, handle, 5, 0x1A, hundreds);
            load_Icon(scene, handle, 7, 0x1A, tens);
            load_Icon(scene, handle, 8, 0x1A, value);
        }
    } else {
        if (type == 12) {
            int rem = value % 3;
            int whole = value / 3;

            if (value == 0) {
                REC(scene, handle)->elementIndex = 0x11;
                load_Icon(scene, handle, 1, 0x1A, 0xB);
                load_Icon(scene, handle, 2, 0x1A, 0xB);
                return;
            }
            if (rem != 0) {
                if (whole >= 10) {
                    int tens;
                    int ones;

                    REC(scene, handle)->elementIndex = 0x14;
                    tens = whole / 10;
                    load_Icon(scene, handle, 1, 0x1A, tens);
                    ones = whole % 10;
                    load_Icon(scene, handle, 2, 0x1A, ones);
                    load_Icon(scene, handle, 3, 0x1A, rem + 0xB);
                    load_Icon(scene, handle, 4, 0x1A, tens);
                    load_Icon(scene, handle, 5, 0x1A, ones);
                    load_Icon(scene, handle, 6, 0x1A, rem + 0xB);
                } else if (whole != 0) {
                    REC(scene, handle)->elementIndex = 0x12;
                    load_Icon(scene, handle, 1, 0x1A, whole);
                    load_Icon(scene, handle, 2, 0x1A, rem + 0xB);
                    load_Icon(scene, handle, 3, 0x1A, whole);
                    load_Icon(scene, handle, 4, 0x1A, rem + 0xB);
                } else {
                    REC(scene, handle)->elementIndex = 0x11;
                    load_Icon(scene, handle, 1, 0x1A, rem + 0xB);
                    load_Icon(scene, handle, 2, 0x1A, rem + 0xB);
                }
                return;
            }
            value = whole;
        }
        if (value < 10) {
            REC(scene, handle)->elementIndex = 0x10;
            load_Icon(scene, handle, 1, 0x1A, value);
            load_Icon(scene, handle, 2, 0x1A, value);
        } else if (type == 2 || value < 100) {
            int ones;
            int tens;

            if (value >= 100) {
                value = 99;
            }
            REC(scene, handle)->elementIndex = 0x13;
            ones = value % 10;
            load_Icon(scene, handle, 2, 0x1A, ones);
            tens = value / 10;
            load_Icon(scene, handle, 1, 0x1A, tens);
            load_Icon(scene, handle, 4, 0x1A, ones);
            load_Icon(scene, handle, 3, 0x1A, tens);
        } else {
            int ones;
            int tens;
            int hundreds;

            if (value >= 1000) {
                value = 999;
            }
            REC(scene, handle)->elementIndex = 0x15;
            ones = value % 10;
            load_Icon(scene, handle, 3, 0x1A, ones);
            tens = value / 10 % 10;
            load_Icon(scene, handle, 2, 0x1A, tens);
            hundreds = value / 100;
            load_Icon(scene, handle, 1, 0x1A, hundreds);
            load_Icon(scene, handle, 6, 0x1A, ones);
            load_Icon(scene, handle, 5, 0x1A, tens);
            load_Icon(scene, handle, 4, 0x1A, hundreds);
        }
    }
}

// .text:0x0015C638 size:0xAC mapped:0x8079B6CC
void mvpBanner_init(void) {
    StatBookScene* scene = (StatBookScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_27C54);
    if (StatsScreenScores.mvpKind == 2) {
        REC(scene, 0)->elementIndex = 0xD3;
    } else if (StatsScreenScores.mvpKind == 3) {
        REC(scene, 0)->elementIndex = 0xC0;
    }
    currentDrawingItem->func = mvpBanner_update;
}

// .text:0x0015C5F4 size:0x44 mapped:0x8079B688
void mvpBanner_update(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    if (g_GameLogic._125 == 7) {
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}
