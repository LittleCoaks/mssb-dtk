# Source file map

What each translation unit is most likely *for*. The `rep_*.c` names come from
the split tool (`rep_<hex .text offset>`) and carry no meaning, so this is the
missing index.

## How each entry was derived, and how much to trust it

Three kinds of evidence, in descending strength:

1. **Named functions in the file.** After the Ghidra name import, 667 of 1769
   `src/game` functions (38%) carry real names. Where most of a file is named
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
| **inferred** | no names at all; purpose read off the call graph or section layout |

`inferred` rows are genuinely a guess. They are the ones to re-check first when
more names land.

---

## Ball

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `rep_540.c` | 40 (32) | Core ball physics and state machine: bounce/roll, air→landed, fair/foul, dead ball, ground-rule double, hit classification, throw-time estimation. The heart of ball simulation. | high |
| `rep_EA0.c` | 15 (9) | Ball visuals — trail effect, spin, animation sub-passes. | high |
| `rep_17E0.c` | 1 (1) | `categorizeBallTrajectory` only. | high |
| `rep_1CB8.c` | 7 (5) | Foul determination and terrain/fielder catchability tests. | high |
| `rep_4090.c` | 5 (2) | Ball↔fielder collision detection. | med |
| `rep_D0.c` | 4 (4) | Generic collision primitives: bounding boxes, triangles, stadium hazards. | high |

## Batting

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `game_batter.c` | 28 (27) | Batter at-bat: swing/bunt decisions, contact and hit-type calculation, launch angle and power, star swings. Nearly fully named. | high |
| `rep_8C8.c` | 14 (9) | Batter AI — swing timing, stick input, ball tracking, RNG. | high |
| `rep_3AE8.c` | 5 (2) | Peach/Daisy star-swing special case. | med |
| `rep_F80.c` | 9 (2) | Star-hit and charge sprite animation. | med |
| `rep_1F58.c` | 12 (2) | Charge animation graphics config. | med |

## Pitching

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `rep_1200.c` | 41 (22) | Pitcher at-bat loop: windup, release, curve, physics constants, pickoffs, count/at-bat reset. | high |
| `rep_940.c` | 8 (7) | Pitcher AI — pitch selection, curve direction, mound movement. | high |
| `rep_2390.c` | 2 (1) | Pitcher hand-on-fire effect. | med |
| `rep_2308.c` | 6 (1) | Perfect-pitch graphics. | med |

## Baserunning

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `rep_13B8.c` | 78 (48) | Baserunning, human and AI: direction input, base rounding, overrun, slide/body-check, position and RBI tracking. | high |
| `rep_140.c` | 9 (2) | Base-rounding position helper. | med |
| `rep_12D0.c` | 8 (7) | Post-play bookkeeping: stats, errors, forced-out targeting, total bases. | high |

## Fielding

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `rep_AC8.c` | 223 (162) | Largest gameplay unit (214,648 B of functions). Fielder catch behaviour end to end: diving/running/jumping catches, bobbles, knockouts, wall jumps, clambers, catch animation progression. | high |
| `rep_18E8.c` | 59 (31) | Fielder AI strategy: which runner to target, throw-vs-chase, tag plays, throw/run timing estimates. | high |
| `rep_FE0.c` | 2 (2) | Fielder orientation + `animateDefence`. | high |
| `rep_1090.c` | 1 (1) | `animateOffence`. | high |

## Camera

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `rep_720.c` | 79 (15) | All in-match camera work: live-ball tracking, replay cameras, fielder-action zoom, pause-menu angles, Bob-omb Derby camera. | high |

## Animation dispatch

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `rep_E08.c` | 28 (15) | Central animation dispatcher — per-role entry points for fielder, runner, batter, pitcher, minigame, match. | high |
| `rep_1E08.c` | 47 (12) | Scene effects: sprites, dust clouds, sun, fireworks, contact-word sprites, pause-state visuals. | med |
| `rep_3E58.c` | 11 (2) | Magikoopa animation, star transforms. | med |
| `rep_3F60.c` | 7 (2) | Actor transform/animation update, chemistry-link graphics. | med |

## HUD and UI

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `rep_16B8.c` | 43 (11) | Scoreboard, RBI score updates, star-chance HUD, diamond minimap, end-of-game animation. | high |
| `rep_1770.c` | 14 (8) | Star gauge, score/inning HUD, ball-strike-out counter, on-base chemistry links. | high |
| `rep_1C0.c` | 14 (3) | Stadium and stadium-object drawing, inning score display. | med |
| `rep_3448.c` | 38 (1) | Icon/graphics-element management — 181 `load_Icon`, 30 each add/remove `GraphicsElementFromScene`. Almost certainly the HUD icon layer. | inferred |
| `rep_1610.c` | 1 (0) | One function calling `setIndicatorSlotState` + `addGraphicsElementToScene`. | inferred |
| `rep_4138.c` | 3 (0) | Immediate-mode GX primitive drawing (`GXBegin`, vtx/Tev/projection setup). | inferred |
| `rep_21F8.c` | 2 (0) | Small matrix + blend/Z-mode render helper. | inferred |

## Math, RNG, geometry

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `rep_1838.c` | 27 (24) | Angle and vector math library: short-angle↔radian conversion, `atan2`, normalisation, line intersection, clamping, game RNG. | high |
| `rep_3090.c` | 49 (2) | Vector/matrix geometry — heavy `PSVEC*`/`PSMTX44*` and `memcpy`, no GX calls, so transform math rather than rendering. | inferred |

## Sound

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `m_sound.c` | 26 (14) | Game sound: stadium emitters, ball-bounce SFX, height-based adjustment, at-bat cues, replay transition. | high |

## Match flow and setup

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `rep_1188.c` | 7 (6) | Roster setup for a match — stats into the in-memory batter/pitcher/fielder structs. | high |
| `rep_868.c` | 1 (1) | `setDefaultAIValues`. | high |
| `rep_60.c` | 1 (1) | `manageLoadingState`. | high |
| `rep_1038.c` | 7 (4) | Transition initialisation, inning-end reset, non-minigame graphics. | med |
| `rep_1B70.c` | 1 (1) | `transitionToPlayerControl`. | high |
| `rep_1330.c` | 1 (1) | `useReplayInputs`. | high |
| `rep_10E8.c` | 2 (2) | Controller input reading and magnitude interpretation. | high |
| `rep_A00.c` | 20 (8) | Versus screen, championship screen, home-run trot, post-replay celebrations. | high |
| `rep_3DA8.c` | 1 (1) | Star-mission tracking (offensive / double play). | high |
| `rep_0.c` | — | 1268 B of un-decompiled `.text`; calls `memcpy`, `ARAMTransfer`, `maybeUpdateFunctionPointer`. REL entry/setup. | inferred |

## Stadiums

Two live in `rep_*` files rather than `sta_*`, which is worth knowing.

| file | fns (named) | stadium | conf |
|---|---|---|---|
| `sta_c0.c` | 7 (3) | Mario Stadium (`loadMarioStadium`, fan animation). | high |
| `sta_c2.c` | 88 (23) | Wario Palace — chain chomp state machine, sand/star hazards, haze texture. | high |
| `sta_c4.c` | 24 (2) | Peach Garden (`loadPeachGarden`). | med |
| `sta_c5.c` | 71 (23) | DK Jungle — Klaptrap AI (roam/chase/launched), barrel cannon, barrel physics. | high |
| `sta_c6.c` | 30 (2) | Toy Field (`loadToyField`, object collisions). | med |
| `rep_1FD8.c` | 47 (12) | **Bowser Castle** — thwomps, fireballs, star pads, screen shake. | high |
| `rep_2998.c` | 29 (11) | **Yoshi Park** — piranha plants (catch/spit/aim), nado. | high |
| `rep_1D58.c` | 36 (20) | Shared stadium framework: object/hazard loading, bounding boxes, collision triangles, lighting. Used by all stadiums. | high |
| `kinoko.c` | 9 (0) | Sits at the very end of `.text` (0x807A8694–0x807AA918); references `g_Minigame`, `g_d_GameSettings`, `drawStadiumRelated`; heavy `getAnimationCollisionOffset` and GX Tev setup. Named "kinoko" (Japanese for mushroom) by an earlier contributor — the subject is not confirmed by anything I can see. | inferred |

## Minigames

| file | fns (named) | purpose | conf |
|---|---|---|---|
| `rep_28A8.c` | 23 (8) | Toy Field gameplay — points, ball state, inning transitions, pause. | high |
| `rep_2BF8.c` | 1 (1) | Toy Field off-screen character indicator. | high |
| `rep_31F0.c` | 26 (9) | Bob-omb Derby — scoring, batter AI, pitch transitions, load. | high |
| `rep_3290.c` | 13 (7) | Wall Ball — wall breaking/replacement, AI pitching, pitcher rotation. | high |
| `rep_34B0.c` | 30 (10) | Barrel Batter — barrel selection/replacement, hit scoring. | high |
| `rep_3520.c` | 69 (5) | Star Dash. | med |
| `rep_36D8.c` | 34 (4) | Chain Chomp Sprint. | med |
| `rep_37A8.c` | 33 (5) | Piranha Panic. | med |
| `rep_2940.c` | 4 (1) | Minigame fielder animations. | med |
| `rep_3310.c` | 55 (2) | Pitching machine — model loading plus actor transform/animation (`CTRLSetTranslation`/`Rotation`, `ActorObjectInitTable`). | med |
| `rep_3880.c` | 123 (4) | Shared minigame effects and pitching-machine animation: 187 `rand`, `allocParticleEffect`, `GXSetBlendMode`/`ZMode`, `sin`/`cos`, and 17 calls to `pitchingMachinePitching`. Named functions span Barrel Batter, Wall Ball and Bob-omb Derby, so this looks like common effect code rather than one minigame. | inferred |

## Data-only units (18 files)

`rep_1668`, `rep_1720`, `rep_1A80`, `rep_1AD0`, `rep_1B20`, `rep_1BC8`, `rep_1C18`,
`rep_1C68`, `rep_31A0`, `rep_3A48`, `rep_3A98`, `rep_3BD8`, `rep_9B0`, `rep_A78`,
`rep_CC8`, `rep_D18`, `rep_D68`, `rep_DB8`

All have `text=0, rodata=80, data=0, bss=0` — **no code whatsoever**. The 80 bytes
are `repHeaderData`, a 20-float table (`1.0, π/2, 1.0, -1.0, 3π/2, π, -1.0, 0.0,
-1.0, 1.0`, repeated twice — a trig-quadrant / axis-direction table) that a shared
header emits into all 92 units.

So these are translation units from the original source whose every function was
inlined or dropped, leaving only the shared table. **They need no decompilation
work and should not be counted as unfinished.**

Six more files are near-empty for the same reason and hold only one or two small
functions: `rep_3B70`, `rep_3C28`, `rep_3C80`, `rep_3CE0`, `rep_3D50`, `rep_3E00`.

---

## Outside `src/game`

| tree | files | contents |
|---|---|---|
| `src/Dolphin` | 189 | Nintendo GameCube SDK, already organised by library: `os` (24), `MSL_C` (59, C standard library), `TRK_MINNOW_DOLPHIN` (28, debug stub), `card` (16), `gx` (15), `dvd` (8), `mtx` (7), `Runtime` (6), `gba` (4), `dsp` (3), plus `ai`/`ar`/`exi`/`si`/`vi`/`pad`/`thp`/`gd`/`db`/`base`. Purpose is given by the SDK itself. |
| `src/Musyx` | 26 | MusyX audio engine — synth (`synth*.c`, `seq*.c`), hardware/DSP (`hw_*.c`), effects (`reverb*.c`, `chorus_fx.c`), streaming. |
| `src/C3/control` | 1 | `control.c` — the CTRL actor/transform layer the stadium and minigame code calls into (`CTRLSetTranslation`, `CTRLSetRotation`). |
| `src/Unknown` | 2 | `File_0x800a6304.c` (a small ring-buffer/accumulator, 3/5 functions matched) and `File_0x800a64e0.c`. Named by address because their role is not yet identified. |
| `src/executor.c` | 1 | REL glue: `_prolog`, `_epilog`, `_unresolved`. |

---

## Where the unfinished work actually is

Ranked by un-decompiled bytes in files that *do* contain code, the largest gaps
are `rep_3880` (123 fns, 4 named), `rep_3090` (49/2), `rep_3448` (38/1),
`rep_3310` (55/2) and `rep_3520` (69/5). These are also the five weakest rows in
this document — the two facts have the same cause, and naming them would firm up
the map as much as it would advance the decomp.
