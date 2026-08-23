# Source file map

What each translation unit in `src/game` is for. **`src/game` is the match REL**
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

## match_setup/ — 10 files, 41 fns (25 named)

Not gameplay itself: the glue that stands a match up and tears it down —
roster construction, loading and transition state, controller input, and the
screens either side of play (versus, championship, home-run trot).

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
| `menus` | menu REL | 42 | `src/menus/**` | stubs for all 42 units, 532 functions; 207 carry real names from Ghidra |
| `unused_rel` | an unused REL | 13 | `src/unused_rel/**` | stubs for all 13 units, 307 functions |

### The menu and unused RELs

Both are known but unwritten, and until recently neither had anywhere to be
written. `configure.py` declared `Object(NonMatching, "menus/rep_XXXX.c")` for
every menu unit and the splits gave each one its address range, but not one of
those files existed — the link consumed objects extracted from the original REL
instead. `unused_rel` was worse off: splits and 2353 symbols, but no entry in
`configure.py` at all.

Both now have a source tree in the `src/game` style — one `.c` per unit with a
`return;` stub per function, one `.h` of prototypes, the `.text` offset, size and
(for menus) mapped address on every stub. That is what makes a unit *scoreable*:
objdiff can diff the compiled stub against the original, so progress on these
RELs is now visible instead of invisible. The four menu units that were in the
splits but missing from `configure.py` (`rep_0398`, `rep_03E8`, `rep_0438`,
`rep_04B0`) are wired in, and `unused_rel` has a `Rel()` entry.

**On the name.** The disc file is `challenge.rel`, but research on this REL
found nothing connecting it to Challenge Mode -- it appears to be genuinely
unused -- so the repo's folders call it `unused_rel`. The disc filename is left
as it is (`orig/GYQE01/files/challenge.rel`, `decompress.py`, `build.sha1`), and
because dtk takes a module's name from its object filename, objdiff units still
read `challenge/unused_rel/rep_XXXX`: the module keeps the game's name, the
folder says what it is.

The mapped addresses are not assumed. The menu REL loads at `0x8063F094`, the
same slot as the match REL, and every generated address was checked against the
`AtGameSettingsScreen` snapshot — `rep_01A0`'s four functions land on
`FUN_8063fb04`, `FUN_8063fbcc`, `FUN_8063fcac`, `FUN_8063fd08` with matching
sizes. The unused REL is resident in neither snapshot, so its load address is
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

## Outside `src/game`

| tree | files | contents |
|---|---|---|
| `src/Dolphin` | 189 | GameCube SDK, organised by library: `os` (24), `MSL_C` (59), `TRK_MINNOW_DOLPHIN` (28), `card` (16), `gx` (15), `dvd` (8), `mtx` (7), `Runtime` (6), `gba` (4), `dsp` (3), plus `ai`/`ar`/`exi`/`si`/`vi`/`pad`/`thp`/`gd`/`db`/`base`. |
| `src/Musyx` | 26 | MusyX audio engine — synth (`synth*.c`, `seq*.c`), hardware/DSP (`hw_*.c`), effects (`reverb*.c`, `chorus_fx.c`), streaming. |
| `src/C3/control` | 1 | `control.c` — the CTRL actor/transform layer stadium and minigame code calls into (`CTRLSetScale`, `CTRLSetRotation`, `CTRLSetQuat`). |
| `src/Unknown` | 283 | DOL translation units named by address because their role is not yet identified. Two were written by hand (`File_0x800a6304.c`, a small ring-buffer/accumulator with 3/5 functions matched, and `File_0x800a64e0.c`); the other 281 were promoted from `auto_*` — see below. |
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
`minigame/rep_3880.c` (123 fns, 4 named), `math/rep_3090.c` (49/2),
`hud/rep_3448.c` (38/1), `minigame/pitching_machine.c` (55/2) and
`minigame/star_dash.c` (69/5).

Four of those five are also the weakest-evidence rows in this document — the
uncertainty and the work have the same cause, and naming them would firm up the
map as much as it would advance the decomp.
