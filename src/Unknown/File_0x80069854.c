#include "Unknown/File_0x80069854.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

void setCaptainLocInRoster(void) {
    int team;
    int i;

    for (team = 0; team < TEAMS_PER_GAME; team++) {
        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
            if (Static_Stats_Tables.captainSelectedID[team] == inMemRoster[team][i].stats.CharID) {
                Static_Stats_Tables.capLocationInOrder[team] = i;
            }
        }
    }
}
