# Source file map

What each translation unit in `src/game` — and each named unit in `src/menus` — is for. **`src/game` is the match REL**
— one of the game's four modules; see [Modules](#modules) for the other three and
for where their code does (and does not) live. Since the reorganisation the
**folder is the category**, so this document is mostly a record of *why* each
file sits where it does, and how much that placement is worth trusting.

## How each entry was derived, and how much to trust it

Three kinds of evidence, in descending strength:

1. **Named functions in the file.** After the Ghidra name import, 663 of 1769
   `src/game` functions (37%) carry real names. Where most of a file is named
   and the names agree on a theme, the purpose is not really in doubt.
2. **Call graph.** For files that are still mostly placeholders, what they call
   is very diagnostic — 181 calls to `load_Icon` says "icon/HUD management"
   regardless of what the functions are called.
3. **Section layout.** A unit with `text=0` has no code at all and cannot be a
   gameplay file whatever its neighbours do.

Every row is tagged:

| tag | meaning |
|---|---|
| **high** | most functions named, names agree on one theme |
| **med** | a minority named, but consistent and corroborated by the call graph |
| **inferred** | no names at all; placement read off the call graph or section layout |

Files at `high`/`med` confidence were given real names. **`inferred` files keep
their original `rep_*` names** — the evidence supports a folder but not a name,
and inventing one would bury a guess in something that reads like a fact.

The **was** column carries each file's original split-tool name, so anything
that still refers to a file as `rep_720` -- Ghidra, older commits, notes --
can be looked up here. Counts are `functions (named)` and total function bytes.

---

## ball/ — 6 files, 72 fns (53 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `ball_physics.c` | `rep_540` | 40 (32) | 39,452 | Core ball state machine: bounce/roll, air→landed, fair/foul, dead ball, ground-rule double, hit classification, throw-time estimation. | high |
| `ball_visuals.c` | `rep_EA0` | 15 (9) | 11,348 | Trail effect, spin, animation sub-passes. | high |
| `foul_detection.c` | `rep_1CB8` | 7 (5) | 1,348 | Foul determination and terrain/fielder catchability tests. | high |
| `collision_primitives.c` | `rep_D0` | 4 (4) | 2,960 | Bounding boxes, triangles, stadium hazards. | high |
| `ball_fielder_collision.c` | `rep_4090` | 5 (2) | 4,808 | Ball↔fielder collision detection. | med |
| `ball_trajectory.c` | `rep_17E0` | 1 (1) | 672 | `categorizeBallTrajectory` only. | high |

## batting/ — 6 files, 85 fns (55 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `batter.c` | `game_batter` | 28 (27) | 16,184 | Batter at-bat: swing/bunt decisions, contact and hit-type calculation, launch angle and power, star swings. Nearly fully named. | high |
| `batter_ai.c` | `rep_8C8` + `auto_00_00020A60` | 19 (14) | 10,292 | Swing timing, stick input, ball tracking, RNG; tail: pre-at-bat batter/last-pitch resets, AI pickoff roll and execution (`pitcherAIDecidePickoff`, `aIPickoff`). The tail was folded in because it shares this unit's pooled float constants (`.rodata` 0x930–0x93C). | high |
| `charge_effects.c` | `rep_1F58` | 12 (2) | 4,316 | Charge animation graphics. | med |
| `star_hit_sprites.c` | `rep_F80` | 9 (2) | 3,100 | Star-hit and charge sprites. | med |
| `star_swing_peach_daisy.c` | `rep_3AE8` | 5 (2) | 2,708 | Peach/Daisy star-swing special case. | med |
| `at_bat_results.c` | `auto_00_0009CD90` | 17 (13) | 7,508 | At-bat result codes: outs, strikeouts/walks, bunts, forced runners; `setAtBatResult`, `iterateBatter`; array shuffles and weighted random picks. | high |

## pitching/ — 5 files, 62 fns (35 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `pitcher.c` | `rep_1200` | 41 (22) | 25,328 | Windup, release, curve, physics constants, pickoffs, count/at-bat reset. | high |
| `pitcher_ai.c` | `rep_940` | 8 (7) | 3,296 | Pitch selection, curve direction, mound movement. | high |
| `perfect_pitch_gfx.c` | `rep_2308` | 6 (1) | 1,876 | Perfect-pitch graphics. | med |
| `pitcher_fire_effect.c` | `rep_2390` | 2 (1) | 776 | Hand-on-fire effect. | med |
| `pitcher_stamina.c` | `auto_00_0001D86C` | 5 (4) | 1,612 | Reliever swap on low stamina (`staminaRelated`), lineup copy, `trackLastPitchInfo`, AI urgency tracker. | med |

## baserunning/ — 3 files, 95 fns (56 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `runner.c` | `rep_13B8` | 78 (48) | 55,544 | Human and AI baserunning: direction input, base rounding, overrun, slide/body-check, position and RBI tracking. | high |
| `play_result_tracking.c` | `rep_12D0` | 8 (7) | 7,768 | Post-play bookkeeping: stats, errors, forced-out targeting, total bases. | high |
| `runner_base_rounding.c` | `rep_140` | 9 (1) | 8,496 | Base-rounding position helper. | med |

## fielding/ — 4 files, 285 fns (196 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `fielder.c` | `rep_AC8` | 223 (162) | 214,648 | Largest gameplay unit. Fielder behaviour end to end: per-frame movement and position, the 29-entry `autoMovement` dispatch table, fielder selection, catches (dive/run/jump/bobble), throw interception and cutoff positioning, wall jumps and clambers, knockouts, minigame fielding. | high |
| `fielder_ai.c` | `rep_18E8` | 59 (31) | 51,548 | Which runner to target, throw-vs-chase, tag plays, throw/run timing estimates. | high |
| `fielder_orientation.c` | `rep_FE0` | 2 (2) | 1,324 | Orientation + `animateDefence`. | high |
| `offence_animation.c` | `rep_1090` | 1 (1) | 900 | `animateOffence`. | high |

## camera/ — 1 file, 79 fns (12 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `camera.c` | `rep_720` | 79 (12) | 36,024 | All in-match camera work: live-ball tracking, replay cameras, fielder-action zoom, pause-menu angles, Bob-omb Derby camera. | high |

## animation/ — 4 files, 93 fns (31 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `animation_dispatch.c` | `rep_E08` | 28 (15) | 28,024 | Central dispatcher — per-role entry points for fielder, runner, batter, pitcher, minigame, match. | high |
| `scene_effects.c` | `rep_1E08` | 47 (12) | 25,144 | Sprites, dust clouds, sun, fireworks, contact-word sprites, pause-state visuals. | med |
| `magikoopa_star_anim.c` | `rep_3E58` | 11 (2) | 5,652 | Magikoopa animation, star transforms. | med |
| `actor_transform.c` | `rep_3F60` | 7 (2) | 3,244 | Actor transform/animation update, chemistry-link graphics. | med |

## hud/ — 7 files, 115 fns (23 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `hud_scoreboard.c` | `rep_16B8` | 43 (11) | 23,588 | Scoreboard, RBI score updates, star-chance HUD, diamond minimap, end-of-game animation. | high |
| `hud_gauges.c` | `rep_1770` | 14 (8) | 12,752 | Star gauge, score/inning HUD, ball-strike-out counter, on-base chemistry links. | high |
| `stadium_draw.c` | `rep_1C0` | 14 (3) | 9,564 | Stadium and stadium-object drawing, inning score display. | med |
| `minigame_hud.c` | `hud/rep_3448` | 38 (1) | 42,920 | The minigame HUD (`minigameGraphics`, `minigameStateLogic`): score panels, timers, intro/result banners and per-minigame icons; 337 `g_Minigame` references. Moved from `hud/` because it sits inside the minigame block. | high |
| `rep_4138.c` | *(unchanged)* | 3 (0) | 1,972 | Immediate-mode GX primitive drawing (`GXBegin`, vtx/Tev/projection setup). | inferred |
| `rep_21F8.c` | *(unchanged)* | 2 (0) | 952 | Small matrix + blend/Z-mode render helper. | inferred |
| `rep_1610.c` | *(unchanged)* | 1 (0) | 392 | One function calling `setIndicatorSlotState` + `addGraphicsElementToScene`. | inferred |
| `toyfield_score_update.c` | `rep_1668` + `auto_00_0009143C` | 1 (1) | 228 | `hud_ScoreUpdate_ToyFieldOffScreenPlayers`: queues the off-screen-player and RBI score-update drawing functions. Matching. | high |

## math/ — 2 files, 76 fns (26 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `game_math.c` | `rep_1838` | 27 (24) | 5,524 | Angle and vector library: short-angle↔radian conversion, `atan2`, normalisation, line intersection, clamping, game RNG. | high |
| `rep_3090.c` | *(unchanged)* | 49 (2) | 43,444 | Heavy `PSVEC*`/`PSMTX44*` and `memcpy`, no GX calls — transform math rather than rendering. | inferred |

## sound/ — 1 file, 26 fns (14 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `m_sound.c` | *(unchanged)* | 26 (14) | 19,208 | Stadium emitters, ball-bounce SFX, height-based adjustment, at-bat cues, replay transition. | high |

## match_setup/ — 22 files, 174 fns (131 named)

The glue that stands a match up and tears it down — roster construction,
loading and transition state, controller input, and the screens either side of
play (versus, championship, home-run trot) — plus the match state machine that
drives play itself (`match_flow.c`) and its bookkeeping: at-bat and in-play
stats, results and MVP, and replay record/playback.

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `versus_screens.c` | `rep_A00` | 20 (8) | 11,608 | Versus screen, championship screen, home-run trot, post-replay celebrations. | high |
| `roster_init.c` | `rep_1188` | 7 (6) | 7,700 | Roster setup — stats into the in-memory batter/pitcher/fielder structs. | high |
| `transition_init.c` | `rep_1038` | 7 (4) | 1,388 | Transition initialisation, inning-end reset, non-minigame graphics. | med |
| `star_missions.c` | `rep_3DA8` + `auto_00_001658F0` | 20 (13) | 19,160 | Challenge-mode star missions (quantity-based, offensive, whole-game, per-pitch tracking, mercy recruiting) and scout-flag missions (`shouldScoutMissionBeEnabled`, `decideScoutFlagMission`, reward assignment). | high |
| `stat_book.c` | `rep_3BD8` + `auto_00_0015C5F4` | 11 (11) | 12,160 | Post-game stat book: `compileStatsForBook` (per-player batting/pitching page totals), `drawBookNumbers`, the page/team/scroll state machine (`statBook_init`/`_update`), MVP banner and MVP scoreboard scenes, `animateMVP_GameEnd`. `rep_3BD8` owned only the repHeaderData .rodata block; this code-only gap sits at the matching place in .text order and uses no float constants, so it is that TU's code. | high |
| `match_scene.c` | `rep_1720` + `auto_00_00097144` | 15 (15) | 8,804 | In-match scene orchestration: `manageEventStates` (event/text queue), `animateMatchScene` (per-frame HUD, pause, MVP and scoreboard dispatch), `initAnimStruct`, HUD teardown, and the pause menu (controls screen, option list, sub-panel, page indicator, team management). Code-only gap adopted by the header-only `rep_1720` TU. | high |
| `scene_skip.c` | `auto_00_0006C854` | 3 (3) | 1,332 | `checkForButtonPressToSkip` (first player to press a skip button, human/CPU and minigame-slot aware), its inlined per-player test `isSkipButtonPressedForPlayer`, and `setCharacterAnimations`. No .rodata of its own, so it may originally belong to a neighbouring TU. | med |
| `controller_input.c` | `rep_10E8` | 2 (2) | 1,816 | Controller input reading and magnitude interpretation. | high |
| `loading_state.c` | `rep_60` | 1 (1) | 632 | `manageLoadingState`. | high |
| `replay_inputs.c` | `rep_1330` | 4 (4) | 3,220 | Replay playback: restore the `g_Stats` snapshot, save live structs, per-frame input playback (`useReplayInputs`). | high |
| `ai_defaults.c` | `rep_868` | 1 (1) | 668 | `setDefaultAIValues`. | high |
| `player_control_transition.c` | `rep_1B70` | 1 (1) | 292 | `transitionToPlayerControl`. | high |
| `rep_0.c` | *(unchanged)* | 0 (0) | — | 1268 B of un-decompiled `.text`; calls `memcpy`, `ARAMTransfer`, `maybeUpdateFunctionPointer`. REL entry/setup. | inferred |
| `match_flow.c` | `auto_00_0005985C` | 47 (37) | 24,804 | The match state machine: `baseballMatchSimulation`, `newPitch`, `checkIfPlayOver`, `handleDeadBall`, `processScoreChanges`, `inningChange`, `switchHalfInning`, end-of-game and challenge-mode flow. | high |
| `match_flow_data.c` | `auto_00_0005985C (.data)` | 0 (0) | 0 | Initialised data for `match_flow.c` (challenge coin tables, `CommonUIFiles_matchEnd`, star power costs). Separate unit because the target references each object by symbol. | inferred |
| `match_loading.c` | `auto_00_0005985C` | 9 (3) | 3,436 | Step-wise in-game / match-end file and ARAM loaders keyed on game mode; `QueueTextToDisplay` event queue; Toy Field character files. | med |
| `stat_tracking.c` | `auto_00_0007976C` | 23 (17) | 10,896 | In-play stat bookkeeping: pitch counts, total bases, forced outs, save situations, new-inning resets, `initializeStats`, replay trigger (`determineIfReplayShouldPlay`). | high |
| `result_stats.c` | `auto_00_000759BC` | 6 (5) | 8,024 | Stats per at-bat result, steals/pickoffs, MVP calculation, winning/losing/save pitcher. | high |
| `replay_state.c` | `auto_00_0007CE90` | 6 (4) | 2,316 | Pre-play snapshot of every game struct into `g_Stats`, last-play stats, per-frame replay input recording. | high |
| `at_bat_setup.c` | `auto_00_0001E154` | 4 (4) | 868 | Between-at-bat setup: `betweenABSetPitcherBatter`, lineup/batting-order snapshot (`someRosterMemoryManagement`), `initializeAIConstants`, AI pre-at-bat bunt roll (`batterAIRollBuntIntent`). No shared data ties it to a neighbour, so it is its own unit. | med |
| `stat_lookups.c` | `auto_00_0006D4A0` | 4 (4) | 564 | Per-player stat lookups: `getAdjustedPitcherStamina`, `checkFieldingStat`, `calculateChemistry`; plus `resetInputTrackers`. | high |
| `run_scoring.c` | `auto_00_0009C578` | 2 (2) | 1,400 | `runScored` (score, go-ahead/comeback, pitcher runs-allowed bookkeeping) and `matchHudDrawingControl`. | high |

## stadium/ — 9 files, 335 fns (98 named)

**The five `sta_c*.c` filenames are CONFIRMED original filenames, not
inferences.** Each of those units emits its own source filename as an
`OSPanic`/assert `__FILE__` string in its own `.rodata` — `"sta_c0.c"` in
`.rodata:0x64` of the Mario Stadium unit, and likewise `"sta_c2.c"`,
`"sta_c4.c"`, `"sta_c5.c"`, `"sta_c6.c"` in the Wario Palace, Peach Garden, DK
Jungle and Toy Field units. That is the same evidence tier as `yd_step.c` and
`teamselect.c` in the menu REL (see below): direct evidence from the shipped
binary rather than any inference tier in this document, so these files were
renamed from their earlier descriptive repo labels (`stadium_mario.c`,
`stadium_wario_palace.c`, `stadium_peach_garden.c`, `stadium_dk_jungle.c`,
`stadium_toy_field.c`) to the names the developers actually used, per the
"official/known names beat repo-invented labels" rule. `stadium_framework.c` has
**no** such string in its own `.rodata`, so it keeps its descriptive repo name.

**`sta_c1.c` (Bowser Castle) and `sta_c3.c` (Yoshi Park) are INFERRED names, not
confirmed.** Neither unit contains a `__FILE__` string (no assert calls), and
`sta_c1`/`sta_c3` appear nowhere in `game.rel` or `main.dol`. The names follow
from the pattern of the five confirmed files: each is `sta_c<N>.c` where `N` is
the stadium's `STADIUM_ID` (Mario 0, Bowser 1, Wario 2, Yoshi 3, Peach 4, DK 5,
Toy 6), which leaves exactly 1 and 3 for these two. They were previously
`stadium_bowser_castle.c` / `stadium_yoshi_park.c` (originally `rep_1FD8` /
`rep_2998`). If a filename string for either ever turns up, it overrides this.

| file | was | fns (named) | bytes | stadium | conf |
|---|---|---|---|---|---|
| `sta_c2.c` | `sta_c2` | 88 (23) | 53,608 | Wario Palace — chain chomp state machine, sand/star hazards, haze texture. | high |
| `sta_c5.c` | `sta_c5` | 71 (23) | 41,796 | DK Jungle — Klaptrap AI (roam/chase/launched), barrel cannon, barrel physics. | high |
| `sta_c1.c` | `rep_1FD8` | 47 (12) | 31,156 | Bowser Castle — thwomps, fireballs, star pads, screen shake. Filename inferred from the `sta_c<STADIUM_ID>` pattern. | high (name: inferred) |
| `stadium_framework.c` | `rep_1D58` | 36 (20) | 8,584 | Shared framework: object/hazard loading, bounding boxes, collision triangles, lighting. Used by all stadiums. | high |
| `sta_c6.c` | `sta_c6` | 30 (2) | 14,184 | Toy Field (`loadToyField`, object collisions). | med |
| `sta_c3.c` | `rep_2998` | 29 (11) | 14,548 | Yoshi Park — piranha plants (catch/spit/aim), nado. Filename inferred from the `sta_c<STADIUM_ID>` pattern. | high (name: inferred) |
| `sta_c4.c` | `sta_c4` | 24 (2) | 14,252 | Peach Garden (`loadPeachGarden`). | med |
| `sta_c0.c` | `sta_c0` | 7 (3) | 4,924 | Mario Stadium (`loadMarioStadium`, fan animation). | high |
| `stadium_star.c` | `rep_23E8` | 3 (2) | 368 | The stadium star: `stadiumStarAwarded` (called by every hazard stadium — Wario Palace, Peach Garden, DK Jungle, Bowser Castle, Yoshi Park) spawns the star at the hit position, plays the star sound and gives the batting team a star (max 5); `stadiumStarAnimation` drifts and spins it for 80 frames. No filename string in the binary, so the name is descriptive. | high |

## minigame/ — 12 files, 425 fns (56 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `star_dash.c` | `rep_3520` | 69 (5) | 38,288 | Star Dash. | med |
| `kinoko.c` | `stadium/kinoko.c` | 14 (0) | 11,668 | The power-up ribbon effect: six colour-cycling ribbons trail from a powered-up minigame player's hands, torso, head and feet, plus a pulsing TEV glow layer. Called only by Star Dash and Chain Chomp Sprint. | high |
| `chain_chomp_sprint.c` | `rep_36D8` | 34 (4) | 21,104 | Chain Chomp Sprint. | med |
| `piranha_panic.c` | `rep_37A8` | 33 (5) | 21,812 | Piranha Panic. | med |
| `barrel_batter.c` | `rep_34B0` | 30 (10) | 17,888 | Barrel selection/replacement, hit scoring. | high |
| `bobomb_derby.c` | `rep_31F0` + 2 fns from `minigame_framework.c` | 28 (9) | 12,016 | Scoring, batter AI (incl. its clear-AI and AI-input routines at `0x1104A8`), pitch transitions, load. | high |
| `toy_field.c` | `rep_28A8` | 23 (8) | 19,696 | Toy Field gameplay — points, ball state, inning transitions, pause. | high |
| `wall_ball.c` | `rep_3290` | 13 (7) | 7,164 | Wall breaking/replacement, AI pitching, pitcher rotation. | high |
| `minigame_models.c` | `rep_3310`, then `pitching_machine.c` | 55 (2) | 27,500 | The minigame model layer (`mm_` prefix): loads, updates and unloads every minigame's models (piranhas, Thwomps, fire bars, barrels, blocks, coins, the pitching machine), the shared archive, and the result-code HUD. Only 4 of its functions are pitching-machine specific. | med |
| `minigame_fielder_anim.c` | `rep_2940` | 4 (1) | 1,924 | Minigame fielder animations. | med |
| `toy_field_hud.c` | `rep_2BF8` | 1 (1) | 1,552 | Toy Field off-screen character indicator. | high |
| `minigame_effects.c` | *(unchanged)* | 123 (4) | 68,156 | Shared effects and pitching-machine animation: 187 `rand`, `allocParticleEffect`, `GXSetBlendMode`/`ZMode`, `sin`/`cos`, 17 calls to `pitchingMachinePitching`. Named functions span Barrel Batter, Wall Ball and Bob-omb Derby, so this is common effect code rather than one minigame. | inferred |

## practice/ — 7 files, 112 fns

Every practice function is now in a practice unit: menus, the three
practice modes (batting/fielding, pitching, baserunning, free fielding),
guided instructions and pause handling, and the scene/HUD code.

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `practice_modes.c` | `rep_1AD0` + unassigned `.text` | 28 (27) | 7,920 | Batting and fielding practice state machines, AI input, play setup and completion tracking. | high |
| `guided_practice.c` | `rep_1B20` + unassigned `.text` | 15 (15) | 7,580 | Guided instructions, practice pause/menu controls, input reset and CPU input playback. | high |
| `baserunning_practice.c` | `rep_1C68` + unassigned `.text` | 6 (4) | 2,352 | Baserunning practice setup, control, level completion and transition helpers. The contiguous code and header table support this grouping; the original TU boundary is inferred. | med |
| `practice_menu.c` | `rep_1BC8` + unassigned `.text` | 21 (17) | 8,972 | Practice state reset, character loading, practice screen load, main/sub menu state handling. | med |
| `pitching_practice.c` | `rep_1C18` + unassigned `.text` | 14 (3) | 4,608 | Pitching practice ball control and state machine. | med |
| `practice_scene.c` | `rep_3A48` + unassigned `.text` | 20 (20) | 12,140 | Practice instructions, goal HUD, menus' scene updates and HUD drawing. | high |
| `free_fielding_practice.c` | `rep_3A98` + tail of old `practice_scene.c` | 8 (8) | 2,568 | Free fielding practice: load, switcher, control, memory reset. | high |

## data_only/ — 15 files, 7 fns

These kept their original names, so there is nothing to look up.

As of 2026-10-08, `rep_CC8`, `rep_D18`, `rep_D68`, `rep_DB8` — all `text=0, rodata=80, data=0, bss=0`,
**no code split yet**. The 80 bytes are `repHeaderData`, a 20-float table
(`1.0, π/2, 1.0, -1.0, 3π/2, π, -1.0, 0.0, -1.0, 1.0`, twice — a trig-quadrant /
axis-direction table) that a shared header emits into all 92 units. Each of
these is an original TU whose code is still an un-split `.text` gap at the
same position: see [Game REL: pairing header-only units with un-split
`.text` gaps](splits.md#game-rel-pairing-header-only-units-with-un-split-text-gaps).
`rep_3BD8`, `rep_1720` and `rep_1668` were paired this way and moved out of
this folder (`stat_book.c`, `match_scene.c`, `toyfield_score_update.c`).
The latest main also pairs `rep_1A80`, `rep_1AD0`, `rep_1B20`, and `rep_31A0`
with `pause_menu.c`, `practice_modes.c`, `guided_practice.c`, and
`minigame_framework.c`. `rep_3A48` is now `practice_scene.c`, `rep_3A98`
`free_fielding_practice.c`, `rep_1BC8` `practice_menu.c`, `rep_1C18`
`pitching_practice.c`, `rep_1C68` `baserunning_practice.c`, `rep_9B0`
`hud/runner_items.c` and `rep_A78` `animation/animation_init.c`.

Plus `rep_3B70`, `rep_3C28`, `rep_3C80`, `rep_3CE0`, `rep_3D50`, `rep_3E00`, which
hold one or two reconstructed functions each. Their matching checkpoints
track the remaining instruction differences; they are not code-free units.

A header table alone does not prove that all of a unit's functions were inlined
or dropped. The unassigned code and section ownership still need to be checked
before declaring such a unit complete. The folder records current split ownership,
not a shared gameplay purpose.

## src/menus — the menu REL

The menu REL's 42 units were all stubs (see [Modules](#modules)), so nearly all of
them still carry their `rep_XXXX` split-tool names. A unit takes a real name only
once its evidence clears the same bar used for `src/game` above, and moves into a
category folder only once that category has more than one member -- `yd_step.c`
below is named but unfoldered because the module has exactly one scene dispatcher.

Of the 42 units, **26 are pure `.rodata`** (no `.text` at all -- each one is a
single 0x50-byte `repHeaderData` table slot with no code to decompile) and
**16 hold actual code**. The 26 rodata-only units are filler: `rep_0010,
rep_0060, rep_00B0, rep_0100, rep_0150, rep_0278, rep_02C8, rep_0318,
rep_0398, rep_03E8, rep_05F0, rep_0640, rep_0690, rep_06E0, rep_07F0,
rep_0898, rep_09B8, rep_0A08, rep_0C50, rep_0CA0, rep_0CF0, rep_0D40,
rep_0D90, rep_0F10, rep_0FD8, rep_11C0`. All 16 code units are already
100% matched or already have a file below except these 9, still fully
`fn_2_*`/unnamed and ranked here by current fuzzy-match % (2026-08 objdiff
report) as a decompilation priority list for this module:

| unit | fuzzy % | fns | notes |
|---|---|---|---|
| `rep_1028` | 2.72% | 88 | large, unnamed |
| `rep_0B08` | 1.33% | 132 | large, 1/132 named (`checkForButtonPressToSkip_maybe`) |
| `rep_08E8` | 1.02% | 45 | unnamed |
| `rep_0DE0` | 0.78% | 17 | unnamed |
| `rep_0568` | 0.74% | 20 | 1/20 named (`captainSelectLoadScreen`), see captain_select note below |
| `rep_0788` | 0.65% | 150 | unnamed; likely the character-select engine (its largest function calls `changeScreenVariables` with team-select/challenge-map/main-menu targets, the css transition set) |
| `rep_0F60` | 0.61% | 25 | unnamed |
| `rep_0840` | 0.58% | 1 | unnamed, single function |
| `rep_10C0` | 0.53% | 11 | unnamed |
| `rep_0AB0` | 0.23% | 12 | 1/12 named (`recordsScreen`) |
| `rep_0730` | 0.12% | 1 | unnamed, single function |

`rep_01A0` (98.50% fuzzy, 9/10 fns matched -- the menu sound layer: BGM/SFX
`sndFX*`/`sndSeq*` calls) is one function short of closing out; that
function (`fn_2_E84`) is confirmed-exhausted (see `matching_notes.md`), so
it isn't a live target without new information.

The former ~69 KB unclaimed block (`.text:0x1254`-`0x12238`) that held most of
the menu REL's well-known named functions -- `mainMenuScreen`, `optionsScreen`
callers, `teamSelectScreenMain`, `selectStadiumScreen`, `stadiumRandomizer`, and
the whole `css*` family -- was chunked into three stub units so it could be
scored (2026-09). `tools/augment_splits.py`'s rodata-correlation heuristic
could not split it (no rodata references at all), so the chunks were
address-window cuts at named-function family boundaries, **not** recovered
TU boundaries, named by `.text` offset rather than a `repHeaderData` slot to
make that explicit. Once fully implemented, one of the three cuts (`text_01254.c`)
turned out to straddle a real boundary and was split again -- see below; the
other two are still address-window cuts, unconfirmed as real TUs:

| unit | .text | fns (named) | bytes | what the names say |
|---|---|---|---|---|
| `text_01254.c` | `0x1254`-`0x1578` | 11 (0) | 660 | generic utility grab-bag: saturating-add helpers, a wide-string compare, an insertion sort, an LCG. No data references, no theme, no callers/callees outside the unit. |
| `main_menu.c` | `0x1578`-`0x323C` | 15 (4) | 7,508 | `cursorSndFx`, `mainMenuRelated`, `mainMenuScreen`, `loadDemoMatch` -- a two-level main-menu state machine (`mainMenuScreen` drives states 0-12 and delegates to `mainMenuRelated`, states 0-10) |
| `text_0323C.c` | `0x323C`-`0x110B0` | 66 (21) | 56,948 | the character-select engine: every `css*`/`characterSelect*`/`randChar*` symbol |
| `text_110B0.c` | `0x110B0`-`0x12238` | 7 (4) | 4,488 | `teamSelectScreenMain`, `stadiumSelectControls`, `selectStadiumScreen` |

`text_01254.c` / `main_menu.c` split at `0x1578` (2026-09), once four grind
sessions confirmed the boundary directly: everything below it has zero data
references and no relationship to anything above it (and vice versa), while
everything from `0x1578` on shares state through `mainMenuScreen`. This is a
real, evidence-backed split rather than a guess, unlike the original
address-window cuts -- see `main_menu.c`'s own entry below for the naming
rationale.

One thing a future split-fixer should know: the five rodata-only units
between `yd_step.c` (rodata `0x200`) and `captain_select/teamselect.c`
(rodata `0x438`) -- `rep_0278`, `rep_02C8`, `rep_0318`, `rep_0398`,
`rep_03E8` -- are almost certainly the `repHeaderData` slots of the TUs
that make up this block, in order, so the block is probably five original
TUs (now six, counting the `text_01254`/`main_menu` split), not three; the
`text_0323C.c`/`text_110B0.c` cuts above are still coarser than the truth.

`text_110B0.c` sits immediately before `captain_select/teamselect.c`
(`rep_0438`, renamed 2026-09 -- see below), whose own `OSPanic` calls name
the source file `"teamselect.c"`. `teamSelectScreenMain`, at the start of
`text_110B0.c`, may belong to that same original TU; that guess was not
baked into the split and is cheap to act on once matched code gives
evidence.

### top level — 3 files, 23 fns (7 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `yd_step.c` | `rep_0200` | 7 (3) | 344 | Scene-dispatch state machine for the whole menu REL. `currentScreenFunctionChooser` steps the active screen by indexing the 18-entry `pCurrentScreenControlFunction` table (`.data:0x138`) with the current screen ID; `changeScreenVariables` performs a transition by shifting the current screen/state into the previous screen/state slots and resetting the state. Also holds the small step stubs the table points at, including `removedStep`, the panic stub wired into the two table slots whose screens were cut. | high |
| `main_menu.c` | `text_01254.c` (`0x1578` half) | 15 (4) | 7,508 | The main-menu screen (screen-table slot 5). `mainMenuScreen` is a 13-state dispatcher over the menu's top-level options (start/records/options/etc.); `mainMenuRelated` is an 11-state sub-dispatcher it delegates to. Also holds `loadDemoMatch` (attract-mode demo playback) and `cursorSndFx` (cursor-move sound effect, called from both dispatchers). | med |
| `dictionary.c` | `rep_0A58` | 1 (0) | 3,532 | The Dictionary/Glossary screen (screen-table slot 7): a Japanese-release feature cut from GYQE01. A single 21-state function (`fn_2_54BB0`, still unnamed) implements 11 kana-row tabs (A/K/S/T/N/H/M/Y/R/W/D, the gojuon alphabetization scheme) over 231 entries, each with a 43-widget row-rendering system. See "Naming note" below. | high (external verification) |

`yd_step.c` is the one file in the tree whose name is not an inference at all: the
original filename survives verbatim in the shipped binary, as the first argument of
this unit's own `OSPanic("yd_step.c", 76, "Removed step was called.\n")`. That is
direct evidence rather than the strongest tier of inference, so it sits above even
the `high` bar the tag denotes. The same trick should name more menu units as they
are split -- panic and assert strings are the cheapest source of original filenames
in this REL.

**`dictionary.c`'s naming note.** This screen was initially misread from internal
evidence alone as a developer settings/parameter editor -- the 11-tab/231-row
structure and the fact that it directly touches `starMissionCompletionTracker`,
`superstarUnlocked`, and other global progress state all looked consistent with a
dev tool. That conclusion was wrong. The user built and ran a Gecko code (derived
from this session's addressing work: `changeScreenVariables(7)` hooked in from the
main menu) on real hardware/an emulator, and it launched a screen the user
independently recognised: the Dictionary/Glossary, a known Japanese-release
feature absent from the USA disc. This is stronger evidence than any internal
inference tier in this document, since it is direct behavioural confirmation
rather than a read of the code -- every other piece of evidence (the kana tabs,
the progress-state reads/writes as likely unlock-gating rather than editing) is
consistent with it in hindsight. `src/menus/rep_1028.c` shares this screen's
`lbl_2_bss_1A8230-1A8250` object-array neighbourhood, which briefly looked like
it might connect the two (a dictionary screen paired with a 3D model-viewer
pane, which `rep_1028.c`'s "29-object animation state machine with lighting
fade and stick-driven anchor movement" resembles) -- **checked and refuted**:
neither `dictionary.c` nor its 43 row-widget callbacks reference any of
`rep_1028.c`'s functions or data, so the two are not directly wired together;
the shared scratch-memory neighbourhood is real but unexplained (REL `.bss` is
commonly time-shared between screens that are never simultaneously active).
See `rep_1028.c`'s own checkpoint for the full test. `menuControlVariables->currentState` value 9 in
`src/menus/main_menu.c` (`mainMenuRelated`) is the only place anywhere in the
menu REL that transitions into this screen, and no code path anywhere in the
decompiled USA build reaches that state -- so the screen is compiled in,
correctly wired to the dispatch table, and unreachable in retail, consistent
with a menu item that existed in the Japanese build and was removed (rather
than the underlying screen code being stripped) for the USA release.

`main_menu.c` sits at `med`, not `high`: 4 of its 15 functions are named and they
agree on one theme (corroborated by the call graph -- `mainMenuScreen` is
screen-table slot 5 in `yd_step.c`'s dispatch table, and its case bodies are
verbatim copies of `mainMenuRelated`'s and `cursorSndFx`'s own bodies, confirming
the relationship), but it is still one piece of a three-way address-window cut
(see `src/menus — the menu REL` above) rather than a filename-confirmed or
fully-named TU, so it stays unfoldered at top level like `yd_step.c` rather than
getting a `menus/main_menu/` folder of its own.

### captain_select/ — 2 files, 27 fns (13 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `captain_select.c` | `rep_04B0` | 17 (10) | 8,956 | Captain Select screen: per-port cursor movement, A/B press handling, new-player/controller detection, swapping the displayed captain model as the cursor moves, and initial port activation on first load of the screen. | high |
| `teamselect.c` | `rep_0438` | 10 (3) | 6,508 | Captain-select support functions still all stubs: `challengeCaptainRelated`, `captainSelectDefaultProcess`, `captainSelectScreen_manager` (the menu REL's screen-table slot 9 main loop), plus 7 unnamed helpers. | high (filename) |

`captainSelect*` is a distinct symbol family from the much larger
`characterSelect*`/`css*` one — `cssReturnToCapSelect_maybe` returns *to* captain
select *from* the character select screen, so those are two adjacent screens
rather than one category.

`teamselect.c` (renamed from `rep_0438`, 2026-09) is the module's second
`yd_step.c`-style case: its own `OSPanic` calls
(`challengeCaptainRelated`, `fn_2_12CD8`, `captainSelectScreen_manager`)
all pass the literal string `"teamselect.c"` as `__FILE__`, which is
direct evidence of the original filename rather than an inference -- the
same standard `yd_step.c` was named under, confirmed by a sweep of every
`OSPanic`/`OSReport` call in the whole menu REL (only these two filenames
turned up anywhere in it). It is filed under `captain_select/` rather than
kept at top level because, unlike `yd_step.c`'s dispatcher, its functions
are all `captainSelect*`-family code and belong with that category; the
original developer filename and the repo's category-folder convention
are two different, non-conflicting things. Two further menu units hold
`captainSelect*` symbols and would belong in this folder once their own
evidence supports a name: `rep_0568` (`captainSelectLoadScreen`), and
whichever unit holds `captainSelectUnloadCSSLoadRelated` at
`.text:0x000800B0`.

---

## Modules

The disc has one DOL and three RELs. The DOL is always resident; it loads exactly
one REL at a time, and the match and menu RELs occupy the same arena slot
(both based at `0x8063F094`), so their code can never be co-resident. Measured on
the symbol tables: of 2406 `game` `.text` functions and 1233 `menus` functions,
only 12 share an offset and **none** share offset *and* size — the two images are
completely disjoint, with nothing shared or common between them.

| module | what it is | units | source tree | state |
|---|---|---|---|---|
| `main` | the DOL | 480 named + ~600 `auto_*` | `src/Dolphin`, `src/Musyx`, `src/C3`, `src/Unknown` | SDK libraries decompiled; every DOL unit holding a hand-named function now has a source file (see below) |
| `game` | match REL | 92 | `src/game/**` | all 92 units have a file, sorted into the 14 folders documented above |
| `menus` | menu REL | 46 | `src/menus/**` | 46 units, 631 functions; 207 carry real names from Ghidra. 1 unit fully matched (`yd_step.c`, 7/7 functions); named files so far: `yd_step.c`/`main_menu.c`/`dictionary.c` at top level, `captain_select/` (2 files) |
| `debug` | the game's unused developer debug menu | 13 | `src/debug/**` | stubs for all 13 units, 307 functions |

### The menu REL and debug.rel

Both are known but unwritten, and until recently neither had anywhere to be
written. `configure.py` declared `Object(NonMatching, "menus/rep_XXXX.c")` for
every menu unit and the splits gave each one its address range, but not one of
those files existed — the link consumed objects extracted from the original REL
instead. `debug.rel` was worse off: splits and 2353 symbols, but no entry in
`configure.py` at all.

Both now have a source tree in the `src/game` style — one `.c` per unit with a
`return;` stub per function, one `.h` of prototypes, the `.text` offset, size and
(for menus) mapped address on every stub. That is what makes a unit *scoreable*:
objdiff can diff the compiled stub against the original, so progress on these
RELs is now visible instead of invisible. The four menu units that were in the
splits but missing from `configure.py` (`rep_0398`, `rep_03E8`, `rep_0438`,
`rep_04B0`) are wired in, and `debug.rel` has a `Rel()` entry.

**On the name.** This REL was called `challenge.rel` from early in the
project's history, on the theory that it was tied to Challenge Mode. That name
was never authoritative: it came from `decompress.py`'s own hardcoded output
filename when splitting the raw archive `aaaa.dat` by byte offset — there is no
filename table in that archive, so nothing about the string "challenge" ever
came from the game's data. The "official name always wins" rule that used to
be invoked here does not apply, because there was no official name to defer
to. Research has since independently identified this REL as the game's unused
developer debug menu, and the module has been renamed to `debug` throughout
the repo (`src/debug/`, `config/*/debug/`, and the disc-extracted file is now
written as `debug.rel`) to reflect that. Nothing here ties it to Challenge
Mode, and it may still be dead/unused code in the sense that it never shipped
active, but its identity as a debug menu is no longer in question the way its
name once implied.

**Why it's invisible in retail.** `debug.rel` is genuinely the developer
debug menu — it is force-loadable via Gecko and, once loaded, its
input-handling and menu-dispatch machinery runs correctly (cursor
movement, submenu entry, sound triggering are all wired up). But nothing
ever draws its menu-item text on screen in a retail build, and live
hardware testing plus DOL analysis has now confirmed why: its per-row
menu-text renderer is DOL function `fn_80048BEC`, and in the retail DOL
that function is a **compiled-out stub** — the shell (prologue/epilogue
and an empty countdown loop) survives, but the loop body that would
actually draw anything was physically stripped at build time. A sibling
DOL function, `0x80026130`, is likewise reduced to a bare `blr` stub.
Both are called from real, live call sites inside `debug.rel` (three for
`fn_80048BEC`, two for `0x80026130`) — the REL is functional, it is only
the DOL-side developer-only renderers it depends on that were removed
from the shipped game. See `build/.match_grind/debug_debug_rep_7BF0.md`
for the full finding, exact call-site offsets, and the renderer's
struct-argument layout.

Debug menu entry 3 (`rep_7A28.c`) is a particle/effect parameter editor
(fire/smoke/fireball/tail presets across 4 tunable-field tables), not a
camera viewer; its grid+sphere 3D view is a live preview pane for whichever
preset is being edited.

The mapped addresses are not assumed. The menu REL loads at `0x8063F094`, the
same slot as the match REL, and every generated address was checked against the
`AtGameSettingsScreen` snapshot — `rep_01A0`'s four functions land on
`FUN_8063fb04`, `FUN_8063fbcc`, `FUN_8063fcac`, `FUN_8063fd08` with matching
sizes. `debug.rel` is resident in neither snapshot, so its load address is
unknown and its stubs carry offset and size but **no** `mapped:` comment; add it
to `REL_LOAD` in `tools/cvt_rel_addr_to_mapped_addr.py` once it can be measured.
That unsolved base is also why its symbols are the only ones absent from the
modding address reference -- `SyncFromDecomp.py` never guesses a base.

What else is known about the menu REL:

- **Ghidra** — the `AtGameSettingsScreen` snapshot (cached in
  `.ghidra_cache/AtGameSettingsScreen.symbols.txt`) has 1011 functions in the menu
  REL's text range `0x8063F094`–`0x806D5E30`, 77 of them with real names.
- **The decomp** — those names are already imported into
  `config/GYQE01/menus/symbols.txt` at matching offsets (`bPressOnStadSelectScreen`
  at Ghidra `0x8063F370` = REL offset `0x2DC`), covering `mainMenuScreen`,
  `characterSelectScreenControlable`, `cssChangeScreens`, `cssUnloadScreen`,
  `stadiumRandomizer`, `loadDemoMatch` and the rest of the `css*` family.

A consequence worth knowing when reading `src/game`: because no menu code is
decompiled, anything in the match REL that sounds menu-ish
(`versus_screens.c`, `pauseMenuCameraAngle`, the `PracticeStruct` pause/practice
menu fields in `include/game/UnknownHomes_Game.h`) is genuinely match-REL code —
in-match screens, the pause menu, practice mode — not menu-REL code that ended up
in the wrong folder. The split config assigns every one of those units to the
`game` module, and no split path is declared by two modules.

`src/executor.c` is declared by no module at all: `_prolog`/`_epilog` exist in both
the `game` and `menus` symbol tables, but the file itself is not in any splits file
or in `configure.py`.

## src/text — the DOL text engine (8 files, 13 fns, 13 named)

The pool of 30 `ScreenText` blocks at `0x80366B18` and everything that fills,
measures, draws and frees them (main.dol `.text` 0x8000F988-0x80011000).
Identified from the Ghidra-named functions, the shared `screenTextArray`
accesses, and Rio's live-RE documentation of the engine; five units are
fully matched and all five link from source.

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `text_channel.c` | `File_0x8000f988.c` | 1 (1) | 276 | `text_initializeNewChannel` — claims a block for a graphics object's glyph string; its header defines the engine's core types (`ScreenText`, `ScreenTextPool`, `TextChannel`, `TextBank`). Matched 100%. | high |
| `text_width.c` | `File_0x8000fa9c.c` | 1 (1) | 696 | `calculateTextBlockWidth` — glyph-string width measurement. | high |
| `text_block.c` | `File_0x8000fd54.c` | 6 (6) | 432 | Per-block field setters: substring indices (control codes 0x4019-0x401C / 0x4023-0x4026), inserted values (control codes 0x400F-0x4012), bank string pointer, max-letters/typewriter state; free one (`text_freeBlock`) or all 30 (`text_freeAllBlocks`) blocks. Matched 100%. | high |
| `text_alloc.c` | `File_0x8000ff04.c` | 1 (1) | 416 | `initializeTextParameters` — scans the pool for a free block, claims and initializes it. Matched 100%. | high |
| `sprite_draw.c` | `File_0x800100a4.c` | 1 (1) | 1012 | `drawTransformedSprite` — textured quad rendering used by the glyph draw pass. | high |
| `text_draw.c` | `File_0x80010498.c` | 1 (1) | 2708 | `DrawText` — renders one block's glyph string (control codes, palette recolor, typewriter effect). | high |
| `text_draw_conditional.c` | `File_0x80010f2c.c` | 1 (1) | 116 | `DrawTextOnCondition` — gating wrapper around the draw pass. | high |
| `text_init.c` | `File_0x80010fa0.c` | 1 (1) | 96 | `initTextRendering`. | high |

## Outside `src/game`

| tree | files | contents |
|---|---|---|
| `src/Dolphin` | 189 | GameCube SDK, organised by library: `os` (24), `MSL_C` (59), `TRK_MINNOW_DOLPHIN` (28), `card` (16), `gx` (15), `dvd` (8), `mtx` (7), `Runtime` (6), `gba` (4), `dsp` (3), plus `ai`/`ar`/`exi`/`si`/`vi`/`pad`/`thp`/`gd`/`db`/`base`. |
| `src/Musyx` | 26 | MusyX audio engine — synth (`synth*.c`, `seq*.c`), hardware/DSP (`hw_*.c`), effects (`reverb*.c`, `chorus_fx.c`), streaming. |
| `src/C3/control` | 1 | `control.c` — the CTRL actor/transform layer stadium and minigame code calls into (`CTRLSetScale`, `CTRLSetRotation`, `CTRLSetQuat`). |
| `src/Unknown` | 275 | DOL translation units named by address because their role is not yet identified. Two were written by hand (`File_0x800a6304.c`, a small ring-buffer/accumulator with 3/5 functions matched, and `File_0x800a64e0.c`); the other 281 were promoted from `auto_*` — see below. The text engine's 8 units moved to `src/text` (see above). |
| `src/executor.c` | 1 | REL glue: `_prolog`, `_epilog`, `_unresolved`. |

---

### The DOL

The DOL is 916,032 bytes of text across `.init` (`0x80003100`) and `.text`
(`0x80008E00`). Every byte of it is claimed by a unit — the report accounts for
915,824 of them — so nothing is missing from the repo; the question was only how
much had a *source file*.

Originally 40% did (the SDK: `Dolphin`, `Musyx`, `C3`, and two hand-written
`Unknown/File_0x*.c`). The remaining 60% sat in `auto_*` units, dtk's
automatically-generated splits for unclaimed ranges, which have no source file at
all. **281 of those units contained at least one hand-named function** —
`main`, `handleLoadingProcess`, `PostRetraceCallback`, `BezierInterpolate` and 329
others — so they were promoted into real split units under the existing
`Unknown/File_0xADDR.c` convention: 207,844 bytes, 382 functions, 333 of them
named.

The ~600 remaining `auto_*` code units hold only placeholder-named functions and
were deliberately **left as auto**. Promoting them would freeze dtk's guessed
boundaries into `splits.txt` as though they were real translation-unit
boundaries, and unlike the RELs there is nothing to derive real ones from: the
40-byte `repHeaderData` signature that gives the RELs their `rep_XXXX` boundaries
occurs 184 times in `game.rel` and **zero** times in `main.dol`. They are already
fully accounted for in the build and the report, so a stub file would add a
frozen guess and no information.

### Ghidra has nothing left to give the DOL

Measured against the `in_game` snapshot, the decomp is ahead, not behind:

| DOL text range | functions | hand-named |
|---|---|---|
| Ghidra `in_game` | 2,504 | 1,758 |
| decomp `symbols.txt` | 2,490 | **1,781** |

Of the 64 addresses Ghidra has that the decomp lacks, 40 are labels *inside*
functions the decomp already has (`__DBVECTOR`, `__OSEVSetNumber` and `__OSEVEnd`
inside `OSExceptionVector`, and so on) and the other 24 are all `FUN_*`
placeholders. Exactly **two** real name upgrades exist — `fn_800111FC` →
`animationRelated` and `fn_8001DB74` → `animRelated`. On the data side Ghidra has
786 hand-named DOL variables to the decomp's 605, and 377 of the 563-symbol
difference are field-level labels inside objects the decomp already has, which
belong in struct definitions rather than in `symbols.txt`.

So a Ghidra import is not the way to more DOL addresses. The addresses are
already here.

## Where the unfinished work actually is

Ranked by un-decompiled bytes in files that contain code, the largest gaps are
`minigame/minigame_effects.c` (123 fns, 4 named), `math/rep_3090.c` (49/2),
`minigame/minigame_hud.c` (38/1), `minigame/minigame_models.c` (55/2) and
`minigame/star_dash.c` (69/5).

Four of those five are also the weakest-evidence rows in this document — the
uncertainty and the work have the same cause, and naming them would firm up the
map as much as it would advance the decomp.
