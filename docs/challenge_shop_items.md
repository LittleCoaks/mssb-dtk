# Challenge shop item flags

`GameInitVariables.challengeShopItemActive` occupies bytes `0x3C..0x4F`
of `g_d_GameSettings`. These are runtime item-enable flags, not just captain
Star Skill purchases. The original `challengeCaptainStarBought[18]`, `_4E`,
and `_4F` declarations described one 20-byte block as three separate members.
The storage remains signed bytes and `GameInitVariables` remains 0x58 bytes.

Use `CHALLENGE_SHOP_ITEM` from `game/challenge/challenge_items.h` to index it.

| Index | Item | Observed gameplay use |
|---|---|---|
| 0 | Nice Bat | Contact sizes multiplied by 1.5 |
| 1 | Power Bat | Hit powers multiplied by 1.5 |
| 2 | Super Ball | Pitch speeds increased by 10; curve multiplied by 1.5 |
| 3 | Lucky Glove | Throwing arm multiplied by 1.5; bobble threshold multiplied by 0.9 |
| 4 | Dash Spikes | Speed multiplied by 1.5 |
| 5 | Buddy Emblem | Chemistry increased by 50, capped at 100 |
| 6 | Red Fireball | Mario's captain Star Skill |
| 7 | Green Fireball | Luigi's captain Star Skill |
| 8 | Lovely Heart | Peach's captain Star Skill |
| 9 | Pretty Flowers | Daisy's captain Star Skill |
| 10 | Gnarly Garlic | Wario's captain Star Skill |
| 11 | Whiskered Eggplant | Waluigi's captain Star Skill |
| 12 | Egg | Yoshi's captain Star Skill |
| 13 | Pink Egg | Birdo's captain Star Skill |
| 14 | King Banana | Donkey Kong's captain Star Skill |
| 15 | Chimp Banana | Diddy Kong's captain Star Skill |
| 16 | Bullet Bill | Bowser's captain Star Skill |
| 17 | Jr. Mask | Bowser Jr.'s captain Star Skill |
| 18 | Secret Map | Remaining permanent shop item; no gameplay reader currently implemented |
| 19 | Superstar | Enables the combined stat boosts; formerly `_4F` |

## Evidence

- `src/game/match_setup/roster_init.c` maps indices 0..4 to stat boosts and
  6..17 to specific captain Star Skill types. Its duplicate check of index 2
  is preserved; this naming pass does not change that existing logic.
- `src/game/stats/stat_lookups.c` reads index 5 and adds element 10 of
  `lbl_3_data_5FC4`: `50.0f`, also verified in the original game REL.
- `src/game/fielding/fielder.c` reads index 3 or the former `_4F` for the
  fielding bonus.
- The original menus function `fn_2_4C6A8` clears **20** bytes starting at
  settings offset `0x3C`. It enables permanent items from Challenge-state
  flags at `0x43C2`, then enables the selected one-game item indexed by the
  signed byte at Challenge-state offset `0x444B` (`-1` means none).
- The menu table `lbl_2_data_373C` has 20 signed-short entries:
  `{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1}`. Together with the stat
  readers and the shop inventory, this identifies the last two slots as
  Secret Map and Superstar. Secret Map's identification is by elimination;
  it has not yet been corroborated by an implemented Toy Field access reader.
- Item names and captain associations are corroborated by the
  [shop inventory](https://www.mariowiki.com/Mario_Superstar_Baseball#Items).

The enclosing type also holds mode, stadium, input-port, unlock and transition
settings, so `GameSettings` would be a clearer future name than
`GameInitVariables`. Its other unknown members remain unnamed pending evidence.
