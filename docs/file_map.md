# Source file map

What each translation unit in `src/game` is for. Since the reorganisation the
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

## batting/ — 5 files, 68 fns (42 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `batter.c` | `game_batter` | 28 (27) | 16,184 | Batter at-bat: swing/bunt decisions, contact and hit-type calculation, launch angle and power, star swings. Nearly fully named. | high |
| `batter_ai.c` | `rep_8C8` | 14 (9) | 9,640 | Swing timing, stick input, ball tracking, RNG. | high |
| `charge_effects.c` | `rep_1F58` | 12 (2) | 4,316 | Charge animation graphics. | med |
| `star_hit_sprites.c` | `rep_F80` | 9 (2) | 3,100 | Star-hit and charge sprites. | med |
| `star_swing_peach_daisy.c` | `rep_3AE8` | 5 (2) | 2,708 | Peach/Daisy star-swing special case. | med |

## pitching/ — 4 files, 57 fns (31 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `pitcher.c` | `rep_1200` | 41 (22) | 25,328 | Windup, release, curve, physics constants, pickoffs, count/at-bat reset. | high |
| `pitcher_ai.c` | `rep_940` | 8 (7) | 3,296 | Pitch selection, curve direction, mound movement. | high |
| `perfect_pitch_gfx.c` | `rep_2308` | 6 (1) | 1,876 | Perfect-pitch graphics. | med |
| `pitcher_fire_effect.c` | `rep_2390` | 2 (1) | 776 | Hand-on-fire effect. | med |

## baserunning/ — 3 files, 95 fns (56 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `runner.c` | `rep_13B8` | 78 (48) | 55,544 | Human and AI baserunning: direction input, base rounding, overrun, slide/body-check, position and RBI tracking. | high |
| `play_result_tracking.c` | `rep_12D0` | 8 (7) | 7,768 | Post-play bookkeeping: stats, errors, forced-out targeting, total bases. | high |
| `runner_base_rounding.c` | `rep_140` | 9 (1) | 8,496 | Base-rounding position helper. | med |

## fielding/ — 4 files, 285 fns (196 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `fielder_catch.c` | `rep_AC8` | 223 (162) | 214,648 | Largest gameplay unit. Catch behaviour end to end: diving/running/jumping catches, bobbles, knockouts, wall jumps, clambers, catch animation progression. | high |
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
| `rep_3448.c` | *(unchanged)* | 38 (1) | 42,920 | 181 `load_Icon`, 30 each add/remove `GraphicsElementFromScene`. Almost certainly the HUD icon layer. | inferred |
| `rep_4138.c` | *(unchanged)* | 3 (0) | 1,972 | Immediate-mode GX primitive drawing (`GXBegin`, vtx/Tev/projection setup). | inferred |
| `rep_21F8.c` | *(unchanged)* | 2 (0) | 952 | Small matrix + blend/Z-mode render helper. | inferred |
| `rep_1610.c` | *(unchanged)* | 1 (0) | 392 | One function calling `setIndicatorSlotState` + `addGraphicsElementToScene`. | inferred |

## math/ — 2 files, 76 fns (26 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `game_math.c` | `rep_1838` | 27 (24) | 5,524 | Angle and vector library: short-angle↔radian conversion, `atan2`, normalisation, line intersection, clamping, game RNG. | high |
| `rep_3090.c` | *(unchanged)* | 49 (2) | 43,444 | Heavy `PSVEC*`/`PSMTX44*` and `memcpy`, no GX calls — transform math rather than rendering. | inferred |

## sound/ — 1 file, 26 fns (14 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `m_sound.c` | *(unchanged)* | 26 (14) | 19,208 | Stadium emitters, ball-bounce SFX, height-based adjustment, at-bat cues, replay transition. | high |

## match/ — 10 files, 41 fns (25 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `versus_screens.c` | `rep_A00` | 20 (8) | 11,608 | Versus screen, championship screen, home-run trot, post-replay celebrations. | high |
| `roster_init.c` | `rep_1188` | 7 (6) | 7,700 | Roster setup — stats into the in-memory batter/pitcher/fielder structs. | high |
| `transition_init.c` | `rep_1038` | 7 (4) | 1,388 | Transition initialisation, inning-end reset, non-minigame graphics. | med |
| `star_missions.c` | `rep_3DA8` | 1 (1) | 2,632 | Star-mission tracking (offensive / double play). | high |
| `controller_input.c` | `rep_10E8` | 2 (2) | 1,816 | Controller input reading and magnitude interpretation. | high |
| `loading_state.c` | `rep_60` | 1 (1) | 632 | `manageLoadingState`. | high |
| `replay_inputs.c` | `rep_1330` | 1 (1) | 712 | `useReplayInputs`. | high |
| `ai_defaults.c` | `rep_868` | 1 (1) | 668 | `setDefaultAIValues`. | high |
| `player_control_transition.c` | `rep_1B70` | 1 (1) | 292 | `transitionToPlayerControl`. | high |
| `rep_0.c` | *(unchanged)* | 0 (0) | — | 1268 B of un-decompiled `.text`; calls `memcpy`, `ARAMTransfer`, `maybeUpdateFunctionPointer`. REL entry/setup. | inferred |

## stadium/ — 10 files, 344 fns (98 named)

Two stadiums were originally in `rep_*` files rather than `sta_*`, which is why
Bowser Castle and Yoshi Park do not follow the `sta_c*` numbering.

| file | was | fns (named) | bytes | stadium | conf |
|---|---|---|---|---|---|
| `stadium_wario_palace.c` | `sta_c2` | 88 (23) | 53,608 | Wario Palace — chain chomp state machine, sand/star hazards, haze texture. | high |
| `stadium_dk_jungle.c` | `sta_c5` | 71 (23) | 41,796 | DK Jungle — Klaptrap AI (roam/chase/launched), barrel cannon, barrel physics. | high |
| `stadium_bowser_castle.c` | `rep_1FD8` | 47 (12) | 31,156 | Bowser Castle — thwomps, fireballs, star pads, screen shake. | high |
| `stadium_framework.c` | `rep_1D58` | 36 (20) | 8,584 | Shared framework: object/hazard loading, bounding boxes, collision triangles, lighting. Used by all stadiums. | high |
| `stadium_toy_field.c` | `sta_c6` | 30 (2) | 14,184 | Toy Field (`loadToyField`, object collisions). | med |
| `stadium_yoshi_park.c` | `rep_2998` | 29 (11) | 14,548 | Yoshi Park — piranha plants (catch/spit/aim), nado. | high |
| `stadium_peach_garden.c` | `sta_c4` | 24 (2) | 14,252 | Peach Garden (`loadPeachGarden`). | med |
| `stadium_mario.c` | `sta_c0` | 7 (3) | 4,924 | Mario Stadium (`loadMarioStadium`, fan animation). | high |
| `rep_23E8.c` | *(unchanged)* | 3 (2) | 368 | `stadiumStarAnimation`, `stadiumStarAwarded`. Placed here on those two names alone; small enough that the theme could still be wrong, so it kept its original name. | med |
| `kinoko.c` | *(unchanged)* | 9 (0) | 11,668 | Sits at the very end of `.text` (0x807A8694–0x807AA918); references `g_Minigame`, `g_d_GameSettings`, `drawStadiumRelated`; heavy `getAnimationCollisionOffset` and GX Tev setup. Named "kinoko" (Japanese for mushroom) by an earlier contributor — the subject is not confirmed by anything I can see. | inferred |

## minigame/ — 11 files, 411 fns (56 named)

| file | was | fns (named) | bytes | purpose | conf |
|---|---|---|---|---|---|
| `star_dash.c` | `rep_3520` | 69 (5) | 38,288 | Star Dash. | med |
| `chain_chomp_sprint.c` | `rep_36D8` | 34 (4) | 21,104 | Chain Chomp Sprint. | med |
| `piranha_panic.c` | `rep_37A8` | 33 (5) | 21,812 | Piranha Panic. | med |
| `barrel_batter.c` | `rep_34B0` | 30 (10) | 17,888 | Barrel selection/replacement, hit scoring. | high |
| `bobomb_derby.c` | `rep_31F0` | 26 (9) | 11,620 | Scoring, batter AI, pitch transitions, load. | high |
| `toy_field.c` | `rep_28A8` | 23 (8) | 19,696 | Toy Field gameplay — points, ball state, inning transitions, pause. | high |
| `wall_ball.c` | `rep_3290` | 13 (7) | 7,164 | Wall breaking/replacement, AI pitching, pitcher rotation. | high |
| `pitching_machine.c` | `rep_3310` | 55 (2) | 27,500 | Model loading plus actor transform/animation (`CTRLSetTranslation`/`Rotation`, `ActorObjectInitTable`). | med |
| `minigame_fielder_anim.c` | `rep_2940` | 4 (1) | 1,924 | Minigame fielder animations. | med |
| `toy_field_offscreen.c` | `rep_2BF8` | 1 (1) | 1,552 | Toy Field off-screen character indicator. | high |
| `rep_3880.c` | *(unchanged)* | 123 (4) | 68,156 | Shared effects and pitching-machine animation: 187 `rand`, `allocParticleEffect`, `GXSetBlendMode`/`ZMode`, `sin`/`cos`, 17 calls to `pitchingMachinePitching`. Named functions span Barrel Batter, Wall Ball and Bob-omb Derby, so this is common effect code rather than one minigame. | inferred |

## data_only/ — 24 files, 7 fns

These kept their original names, so there is nothing to look up.

`rep_1668`, `rep_1720`, `rep_1A80`, `rep_1AD0`, `rep_1B20`, `rep_1BC8`, `rep_1C18`,
`rep_1C68`, `rep_31A0`, `rep_3A48`, `rep_3A98`, `rep_3BD8`, `rep_9B0`, `rep_A78`,
`rep_CC8`, `rep_D18`, `rep_D68`, `rep_DB8` — all `text=0, rodata=80, data=0, bss=0`,
**no code whatsoever**. The 80 bytes are `repHeaderData`, a 20-float table
(`1.0, π/2, 1.0, -1.0, 3π/2, π, -1.0, 0.0, -1.0, 1.0`, twice — a trig-quadrant /
axis-direction table) that a shared header emits into all 92 units.

Plus `rep_3B70`, `rep_3C28`, `rep_3C80`, `rep_3CE0`, `rep_3D50`, `rep_3E00`, which
are near-empty for the same reason and hold only one or two small functions.

These are translation units whose every function was inlined or dropped, leaving
only the shared table. **They need no decompilation work and should not be
counted as unfinished.** They live in their own folder because no gameplay
category applies, not because they belong together functionally.

---

## Outside `src/game`

| tree | files | contents |
|---|---|---|
| `src/Dolphin` | 189 | GameCube SDK, organised by library: `os` (24), `MSL_C` (59), `TRK_MINNOW_DOLPHIN` (28), `card` (16), `gx` (15), `dvd` (8), `mtx` (7), `Runtime` (6), `gba` (4), `dsp` (3), plus `ai`/`ar`/`exi`/`si`/`vi`/`pad`/`thp`/`gd`/`db`/`base`. |
| `src/Musyx` | 26 | MusyX audio engine — synth (`synth*.c`, `seq*.c`), hardware/DSP (`hw_*.c`), effects (`reverb*.c`, `chorus_fx.c`), streaming. |
| `src/C3/control` | 1 | `control.c` — the CTRL actor/transform layer stadium and minigame code calls into (`CTRLSetScale`, `CTRLSetRotation`, `CTRLSetQuat`). |
| `src/Unknown` | 2 | `File_0x800a6304.c` (a small ring-buffer/accumulator, 3/5 functions matched) and `File_0x800a64e0.c`. Named by address because their role is not yet identified. |
| `src/executor.c` | 1 | REL glue: `_prolog`, `_epilog`, `_unresolved`. |

---

## Where the unfinished work actually is

Ranked by un-decompiled bytes in files that contain code, the largest gaps are
`minigame/rep_3880.c` (123 fns, 4 named), `math/rep_3090.c` (49/2),
`hud/rep_3448.c` (38/1), `minigame/pitching_machine.c` (55/2) and
`minigame/star_dash.c` (69/5).

Four of those five are also the weakest-evidence rows in this document — the
uncertainty and the work have the same cause, and naming them would firm up the
map as much as it would advance the decomp.
