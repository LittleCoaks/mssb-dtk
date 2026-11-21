# `splits.txt`

This file contains file splits for a module.

Example:

```yaml
path/to/file.cpp:
	.text       start:0x80047E5C end:0x8004875C
	.ctors      start:0x803A54C4 end:0x803A54C8
	.data       start:0x803B1B40 end:0x803B1B60
	.bss        start:0x803DF828 end:0x803DFA8C
	.bss        start:0x8040D4AC end:0x8040D4D8 common
```

## Format

```yaml
path/to/file.cpp: [file attributes]
    section     [section attributes]
    ...
```

- `path/to/file.cpp` The name of the source file, usually relative to `src`. The file does **not** need to exist to start.  
  This corresponds to an entry in `configure.py` for specifying compiler flags and other options.

### File attributes

- `comment:` Overrides the `mw_comment_version` setting in [`config.yml`](/config/GAMEID/config.example.yml) for this file. See [Comment section](comment_section.md).  

`comment:0` is used to disable `.comment` section generation for a file that wasn't compiled with `mwcc`.  
Example: `TRK_MINNOW_DOLPHIN/ppc/Export/targsupp.s: comment:0`  
This file was assembled and only contains label symbols. Generating a `.comment` section for it will crash `mwld`.

### Section attributes

- `start:` The start address of the section within the file. For DOLs, this is the absolute address (e.g. `0x80001234`). For RELs, this is the section-relative address (e.g. `0x1234`).
- `end:` The end address of the section within the file.
- `align:` Specifies the alignment of the section. If not specified, the default alignment for the section is used.
- `rename:` Writes this section under a different name when generating the split object. Used for `.ctors$10`, etc.
- `common` Only valid for `.bss`. See [Common BSS](common_bss.md).
- `skip` Skips this data when writing the object file. Used for ignoring data that's linker-generated.

## Game REL: pairing header-only units with un-split `.text` gaps

In the game REL (and likely the other RELs), every original translation unit
that includes `header_rep_data.h` begins its `.rodata` with the same 80-byte
(0x50) `repHeaderData` block. That block turns the `.rodata` layout into a map
of TU boundaries, and two consequences follow:

1. **A `data_only/rep_*` unit that owns exactly 0x50 bytes of `.rodata` and no
   `.text` is a TU whose code has not been split yet.** Because units appear
   in the same order in every section, its code is the un-split `.text` gap
   (`auto_00_*_text`) between the text of its rodata-order neighbours. If that
   gap references no `lbl_3_rodata_*` at all, the pairing is consistent: a
   header-only TU has no float constants of its own. Give the unit that
   `.text` range (and rename it once its functions say what it is).
2. **A `.text` gap that references no `.rodata` of its own is not a TU by
   itself.** It belongs to an adjacent unit, or to a header-only unit as
   above. A gap that does reference `.rodata` ties itself to whichever unit
   owns those constants: MWCC pools float constants per TU, so shared
   constants mean the same TU.

Done so far with this method:

| header-only unit | `.text` gap | became |
|---|---|---|
| `rep_3BD8` | `0x15C5F4-0x15F574` | `match_setup/stat_book.c` |
| `rep_1720` | `0x97144-0x993A8` | `match_setup/match_scene.c` |
| `rep_1668` | `0x9143C-0x91520` | `hud/toyfield_score_update.c` |
| `rep_1A80` | `0xAC9F8-0xAFDC0` | `match_setup/pause_menu.c` |
| `rep_1AD0` | `0xAFDC0-0xB1CB0` | `practice/practice_modes.c` |
| `rep_1B20` | `0xB1CB0-0xB3A4C` | `practice/guided_practice.c` |
| `rep_31A0` | `0x106DFC-0x110634` | `minigame/minigame_framework.c` |
| `rep_1C68` | `0xB707C-0xB79AC` | `practice/baserunning_practice.c` (grouping supported by names/call graph and section order; original TU boundary inferred) |
| `rep_1BC8` | `0xB3B70-0xB5E7C` | two TUs: `practice/practice_simulation.c` (`0xB3B70-0xB49D4`, `.rodata`, `.data 0x10A08-0x10A30`) and `practice/practice_menu.c` (`0xB49D4-0xB5E7C`, `.data 0x10A30-0x10A90`). The `.data` shows it: tables are 0x24 | 4-byte pad | 0x1C, 0x20, 0x24, and the pad is exactly the linker's 8-byte alignment of a one-table unit (cf. `ball_physics`, `loading_state`). Compiling the two halves separately gives `.data` 0x24 and 0x60 and 100% `.data` in both. The boundary between the two jump-table functions is `practiceSimulation` (last of the first) / `practiceRelatedMenu` (first table of the second); `fn_3_B49D4`, the char-select cursor helper called only by `practiceRelatedMenu`, was put with the menu. |
| `rep_1C18` | `0xB5E7C-0xB707C` | `practice/pitching_practice.c` (owns the jump table at `.data 0x10A90`; boundary after `practiceMenu`, where the pitching-practice state references begin) |
| `rep_3A98` | `0x15AD94-0x15B79C` | `practice/free_fielding_practice.c`, split off the tail of `practice_scene.c` (owns the three jump tables at `.data 0x26F00-0x26F78`) |
| `rep_CC8`, `rep_D18`, `rep_D68`, `rep_DB8` | `0x59918-0x60768` | `match_setup/match_loading.c`, `match_main.c`, `match_end.c`, `match_flow.c`: the old `match_flow.c` was three TUs (see [the 2026-10-18 section](#the-match-units-between-fielderc-and-animation_dispatchc-2026-10-18)) |

By rule 2, gap `0x20A60-0x20CEC` was folded into `batting/batter_ai.c`,
since it shares batter_ai's pooled constants at `.rodata` 0x930-0x93C.

Boundary fixes from the 2026-10-08 gap review (every function's local
`.rodata`/`.data`/`.bss` references were checked against its unit; only
`fn_3_C1930` disagreed):

- `0x1104A8-0x110634` (`minigameClearAIControlled`, `bOD_UpdateBatterAIInputs`)
  moved from `minigame_framework.c` to the start of `bobomb_derby.c`.
  bobomb_derby already inlines both bodies, and every minigame TU opens with
  its own clear-AI routine (cf. `wallBallClearAIControlled`).
- Gap `0x1608F0-0x161588` (`starMissionsMinigamesSpecialAction`,
  `starMissionsMinigamesTotalPoints`) folded into `match_setup/star_missions.c`.
- Gap `0xC1930-0xC1964` (`fn_3_C1930`) folded into `batting/charge_effects.c`;
  it references charge_effects' `.data` 0x17260.

Later on 2026-10-08:

- `rep_9B0` paired with `0x219CC-0x21C90` as `hud/runner_items.c` (the name
  is provisional; its functions may sit closer to animation or the versus
  screens). `rep_A78` paired with `0x249E8-0x251E4` as
  `animation/animation_init.c`.
- New code-only units (no rodata of their own): `match_setup/match_transitions.c`
  (`0x6B4C8-0x6BEA4`) and `match_setup/character_loading.c` (`0x90754-0x912B4`).
- Gap `0xFBD58-0xFC448` (camera scene switching) joined `math/rep_3090.c`,
  which also takes `.data 0x1C0A8-0x21268`. That data is only used by the
  camera functions and rep_3090, and sits between its neighbours' data, so
  both belong to one TU.
- Gap `0x167CC4-0x168414` (`fieldingRelatedAnimations` and helpers) joined
  `animation/magikoopa_star_anim.c` for the same data-contiguity reason
  (`.data 0x28508-0x285A8`). `fn_3_1665E4` (`0x1665E4-0x1666B0`) joined
  `data_only/rep_3E00.c` (now `practice/practice_model_load.c`) with `.data 0x284E8-0x28508`.
- Small gaps folded into the unit before them: `0xFF4C` -> `ball_physics.c`,
  `0x8B094` -> `m_sound.c`, `0xBA150` -> `scene_effects.c`; `0x6F4E8` into
  `pitcher.c` as its start.
- The last tiny gaps had no local data references, so the call graph decided,
  and a gap next to a Matching unit went to the other side:
  `0x5985C` -> `fielder.c`, `0x674E0` -> `animation_dispatch.c`, `0x6A160` ->
  `ball_visuals.c`, `0x6AEC0` -> `fielder_orientation.c`, `0x6C410` ->
  `offence_animation.c` (whose functions call these animation resets),
  `0xB7EF0` (`vecDotProduct`, `CrossProduct`, `rng`) -> `stadium_framework.c`,
  `0xCABB4` and `0xCB344` -> `perfect_pitch_gfx.c`, `0xCB6B4` ->
  `pitcher_fire_effect.c`, `0x16C410` -> `kinoko.c`, `0xC0810` ->
  `scene_effects.c`. No game REL `.text` is unowned any more.

### Unowned game REL `.data` (2026-10-08)

Data sections link in splits.txt order, so an unowned `.data` block belongs to
a unit that sits between its neighbours in link order. Blocks used by exactly
one unit went to that unit: `0x118-0x1D0` -> `rep_0.c`, `0x273DC-0x27C98` ->
`stat_book.c`, `0x281F0-0x28418` -> `rep_3D50.c`, `0x17898-0x17B98` ->
`rep_21F8.c` (now `animation/keyframed_sprite_effect.c`; one 0x300-byte `lbl_3_data_17898`; the seven sub-symbols were
merged because `fn_3_C937C`'s codegen depends on the full size),
`0x2A448-0x2A4A8` -> `rep_4138.c`, `0x10AB0-0x111A8` (per-stadium tables) ->
`stadium_framework.c`, `0xF4A4-0xF4E0` -> `hud_gauges.c`, and `.bss
0x9FDC-0xA018` -> `pitcher_fire_effect.c`.

Four large shared tables have no code unit between their link-order
neighbours, so each became a data-only unit (two were later found to be code
units' `.data`; see the 2026-10-15 entry below), named by
address: `data_only/data_1880.c` (pitcher/batter AI tables, after `camera.c`; now
`match_setup/ai_tables.c`),
`gameplay_tables.c` (field coordinates, hit and fielding constants, after
`match_loading.c`; it also owns `0x5FF4-0x6510`, the challenge and match-end
tables formerly in `match_flow_data.c`: an object at the 4-aligned `0x5FF4`
cannot start a unit, since MWCC 8-aligns every unit's `.data`), `data_69C0.c` (batter/fielder hitboxes, runner constants,
after `ball_visuals.c`; now `match_setup/character_constants.c`), `data_8D88.c` (HUD layouts, after `m_sound.c`; now
part of `hud_scoreboard.c`).
All are 100%.

Left unowned on purpose: common `.bss` from `0xD714` (shared globals used by
almost every unit), the 4-byte alignment gaps, `0x228`
`FrameCountOfEntireGame` (no clear owner), `0x6804-0x6820` and `0x27EAC`.

### Data-only units that were really a code unit's `.data` (2026-10-15)

A pooled `.data` base cannot span translation units: MWCC addresses a TU's own
`.data` objects off one `lis/addi` of the TU's first object plus an offset,
and a reference from another TU goes through the object's own symbol. So every
offset a function reaches off one base belongs to the unit that owns the
function.

- `data_1880.c` -> `versus_screens.c` (`.data 0x1D28-0x3C40`).
  `chooseVsScreenSituation` reaches `+0x228`, `+0x670`, `+0xEB0` and
  `postReplayBatterCelebration` `+0x3AC`, `+0x488`, `+0x564` off one
  `lbl_3_data_1D28` base, so `0x1D28` up to `versus_screens`'s old start
  `0x3A40` is its `.data`. The 0x37AC/0x3888/0x3964 tables are 0xDC `s32[55]`
  like 0x3A40. `animation_init.c` and `camera_script.c` reach
  `lbl_3_data_1D28`, `lbl_3_data_1F40`, `vsSituations` and 0x37AC-0x3964 by
  symbol, so those stay global. `0x1880-0x1D28` stays in `data_1880.c` (now
  `match_setup/ai_tables.c`): it is
  referenced only by symbol (no pooled base), from `pitcher_ai.c`
  (`0x1880-0x1934`), `batter_ai.c` and `ai_defaults.c` (`0x193C-0x1D10`). The
  pitcher tables come before the batter tables although `batter_ai.c` links
  first, so they are not in their code units' own `.data`.
  Blobs split at the pooled offsets: `homerun_cameraSceneIDs` (0x370) into four
  `s32[55]` (`0x1FF8`, `0x20D4`, `0x21B0`, `0x228C`); `vsSituations` (0x1414)
  into `VsSituation[33]` (0x840) and `u8 lbl_3_data_2BD8[55][55]`;
  `lbl_3_data_1F40` (0x34) into `u8 *[4]` and `s8 lbl_3_data_1F50[33]`.
  Objects are defined in address order (`.data` keeps declaration order) and
  our object's offsets equal the target's.
- `data_8D88.c` -> `hud_scoreboard.c` (`.data 0x8D88-0xF4A4`; `data_8D88.c`
  removed). `handleInGameEventsAndSoundEffects` reaches `+0x30C8`-`+0x31A4`
  and `manageScoreboardGraphic` `+0x60D4`-`+0x66A8` off one `lbl_3_data_8D88`
  base. The units between (`character_loading`, `outs_indicator`,
  `toyfield_score_update`) have no `.data`. The minigame, practice and HUD
  tables in the range stay global: `minigame_hud.c`, `practice_scene.c`,
  `toy_field_hud.c`, `match_scene.c`, `hud_gauges.c`, `outs_indicator.c` and
  `stat_book.c` reach them by symbol. Blobs split at the pooled offsets:
  `lbl_3_data_BE50` (0x11C) into `HudEventTiming[25]` (0xC8),
  `u16 lbl_3_data_BF18[10]` and `UIRecordDescriptor lbl_3_data_BF2C[2]`;
  `lbl_3_data_EC1C` (0x5E4) into `UIRecordDescriptor[18]`,
  `UIRecordDescriptor lbl_3_data_EE5C[29]` and `u16 lbl_3_data_F1FC[2]`;
  `lbl_3_data_F200` (0x24) into `u8[12]` and `u8 lbl_3_data_F20C[24]`. The
  `HudEventData` overlay is gone.

### Reorganisation after full `.text` ownership (2026-10-08)

With every game REL `.text` byte owned, each unit was reviewed against what
its code does. Links in older text above refer to the names before this pass.

Edge functions moved into the adjacent unit they serve (only boundaries
between link-order neighbours can move; each moved function was already
100%, and its data either stays global or moves with it):

| functions | from -> to | evidence |
|---|---|---|
| `aIPickoff`, `pitcherAIDecidePickoff` (`0x20B30`) | `batter_ai` -> `pitcher_ai` | pitcher pickoff state and `pickOffProb`, also rolled by `pitcherAINewBatter`; no batter rodata |
| `batterAIRollBuntIntent` (`0x1E3EC`) | `at_bat_setup` -> `batter_ai` | sets the flag `batterAIBuntDecision` reads; shares `lbl_3_data_1C10` with `batterAIRNGValueSetting` |
| `resetInputTrackers` (`0x6D4A0`) | `stat_lookups` -> `controller_input` | clears `g_Controls` |
| `determineIfReplayShouldPlay`, `fn_3_7C190`, `checkReplaySkipButton` (`0x7BC20`) + `.data 0x8110` jump table | `stat_tracking` -> `replay_inputs` | replay trigger; the jump table is its switch |
| `fn_3_910F4`, `fn_3_911A8` (`0x910F4`) | `character_loading` -> `outs_indicator` | outs-lamp update, installed as the per-frame func by `fn_3_912B4` |
| `matchHudDrawingControl` (`0x9C578`) | `run_scoring` -> `hud_gauges` | only registers `hud_gauges`' own draw functions |
| `parkPlantsTevSetup`, `drawParkPlants` (`0xE1C60`) | `minigame_fielder_anim` -> `sta_c3` | only data is `sta_c3`'s `parkPlantData` |
| `loadSomeDataFile`, `someAllocFunction` (`0x106DFC`) | `minigame_framework` -> `camera_script` | camera-script heap and its data file (`cameraDataFileDescriptor`) |

Considered and **rejected** because the data says otherwise: the charge-glow
tail of `scene_effects.c` (`0xC0134-0xC0854`; its `.bss` is at the *start* of
`scene_effects`' range and it shares pooled floats with `drawSun`), and the
Toy Field coin functions at the start of `minigame_fielder_anim.c` (their
data is shared with `toyFieldInitCoinModels` in the same unit).

Units renamed or re-foldered (link order unchanged):

| was | now |
|---|---|
| `math/rep_3090.c` | `camera/camera_script.c` |
| `hud/rep_1610.c` | `hud/outs_indicator.c` |
| `baserunning/runner_base_rounding.c` | `math/spline.c` |
| `data_only/rep_3C80.c` | `ball/ball_contact_burst.c` |
| `data_only/rep_3C28.c` | `batting/star_swing_bowser.c` |
| `data_only/rep_3D50.c` | `batting/star_swing_wario_waluigi.c` |
| `hud/rep_4138.c` | `stadium/stadium_scoreboard_digits.c` |
| `hud/stadium_draw.c` | `stadium/stadium_draw.c` |
| `match_setup/rep_0.c` | `match_setup/game_rel_entry.c` |
| `match_setup/player_control_transition.c` | `practice/player_control_transition.c` |
| `fielding/fielder_orientation.c` | `animation/defence_animation.c` |
| `fielding/offence_animation.c` | `animation/offence_animation.c` |
| `animation/magikoopa_star_anim.c` | `animation/star_sparks.c` |
| `practice/practice_modes.c` | `practice/batting_fielding_practice.c` |
| `match_setup/replay_inputs.c`, `replay_state.c` | `replay/` |
| `match_setup/stat_tracking.c`, `stat_book.c`, `result_stats.c`, `stat_lookups.c`, `run_scoring.c` | `stats/` |
| `match_setup/star_missions.c` | `challenge/star_missions.c` |
| `data_only/data_1880.c` | `match_setup/ai_tables.c` (2026-10-18) |
| `data_only/data_69C0.c` | `match_setup/character_constants.c` (2026-10-18) |
| `data_only/rep_3B70.c` | `batting/star_effect_glow.c` (2026-10-18) |
| `data_only/rep_3CE0.c` | `minigame/minigame_winner_spotlight.c` (2026-10-18) |
| `data_only/rep_3E00.c` | `practice/practice_model_load.c` (2026-10-18) |
| `hud/rep_21F8.c` | `animation/keyframed_sprite_effect.c` (2026-10-18) |

Kept on purpose: `kinoko.c`, `m_sound.c` and `sta_c0/2/4/5/6.c` are original
filenames (their `OSPanic` `__FILE__` strings are in the binary).

TU-count check: the target REL holds exactly **92** `repHeaderData` tables,
and every unit with `.rodata` has exactly one. So `fielder.c` (214 KB),
`match_scene.c`, `versus_screens.c` and `star_missions.c` are each one
original TU, and the theme-based splits proposed for them were not made: the pause UI half of `match_scene.c`
(`0x978DC-0x993A8`), the home-run celebrations in `versus_screens.c`
(`0x23890-0x24598`), scout flags out of `star_missions.c` (from `0x163948`).
Eleven code units have no table and no `.rodata` at all, and use no float
constants, so the test cannot place them: `at_bat_results`, `at_bat_setup`,
`character_loading`, `match_transitions`,
`scene_skip`, `pitcher_stamina`, `replay_state`, `result_stats`,
`run_scoring`, `stat_lookups`, `stat_tracking`. Each is either a TU that never
included the shared header or the tail of its link-order predecessor; all
were cut from unowned gaps.
(`match_loading` and
`match_flow` were on this list until 2026-10-18, when they took the last four
header-only tables; see below.)
`kinoko_startPulseGlow` is declared `(s8 charID, u8 alt)` in `star_dash.c` but defined
`(void* model, u8 alt)` in `kinoko.c`; the first argument is really a player ID.

Where several header-only units share one window, split the window at
function boundaries so that each TU's functions stay contiguous; the call
graph and function names usually show where the themes change.

Nothing is open any more: the last four header-only units were paired on
2026-10-18 (next section).

### The match units between `fielder.c` and `animation_dispatch.c` (2026-10-18)

The 2026-10-08 table guessed that `rep_CC8`, `rep_D18`, `rep_D68` and `rep_DB8`
(`.rodata 0xCC8-0xE08`) held part of `fielder.c`, so that its 214 KB `.text` would be
several TUs. It is not:

- **`fielder.c` is one TU, up to `0x59918`.** Its `.rodata 0xAC8-0xCC8` holds one table
  (at `0xAC8`) and a float pool that runs right up to `0xCC4`. The last pool user is
  `initFielders` (`0x596F8`); `initializeFielderConstants` reads `0xCC4`. The two
  functions after it belong to fielder by other evidence: `ifCurrentFielderIsTakingOverBaseCovering`
  (`0x5985C`) reads `autoMovementFunctions`, the first object of fielder's `.data`
  and used by no other unit, and `fielderMainFunction` (`0x598D0`) uses no constants
  and only calls fielder functions. (It does not read fielder's `.rodata`.) So no
  other TU's code is in fielder's range.
- **The four tables belong to the code after it:** `match_loading.c` (`0x59918`) and
  the old `match_flow.c` (`0x5A684-0x60768`), which had no `.rodata`, include the
  header like almost every unit, and come next in link order (`.data`: fielder
  `0x3C40`, match_loading `0x3D60`, `gameplay_tables` `0x4290`, match_flow `0x6510`,
  animation_dispatch `0x65F0`).
- **`match_flow.c` was three TUs.** *(a)* In the whole game REL, no leaf function of 40
  instructions or less is called with `bl` from its own unit (MWCC's
  `-inline deferred` inlines them), except `resetCount` (7 instructions) and
  `SetGameStatus` (10) in `match_flow`, which needed `#pragma dont_inline` scaffolding.
  (The only other case is fielder's one-instruction `updateFielderValuesSubFunction3_empty`.)
  Their callers (`matchEndGameScreenFunction`, `inningChange`, `switchHalfInning`,
  `initNewInning`, `exhibitionGameTransitionCalculations`, ...) are therefore in another TU.
  *(b)* Inlined copies tie functions together: `configureTeamsForGame_Unused` (`0x5A6A0`)
  is inlined into `gameInitRelated` (`0x5A87C`), so the first TU runs at least to `0x5ACA0`.
  `fn_3_5B220` and `fn_3_5B41C` are inlined into `matchEndGameScreenFunction`
  (`0x5BD40`), so its TU starts at `0x5B220` or earlier. `fn_3_5C418` is inlined into
  `baseballMatchSimulation`, and so are `settingGameStatus`, `fn_3_5D9F8`,
  `freePracticeSomething` and `fn_3_5FE88`, so `0x5C418-0x60768` is one TU. *(c)* That
  makes four TUs with four tables. `gameplay_tables.c` gets none, like the other two
  shared-table blobs `ai_tables.c` and `character_constants.c` (then `data_1880.c` and `data_69C0.c`): every table in their stretches
  of `.rodata` belongs to a code unit. *(d)* The `.data` is consistent. A unit's
  data objects always come before its jump tables (true in all 19 game units that have
  both), so `gameplay_tables` (`0x4290`) cannot be `match_loading`'s. The new
  `match_end`/`match_flow` boundary `0x6540` is 8-aligned. `jumptable_3_data_6510` is one
  12-entry table (`cmplwi r6, 0xb`), so its size was fixed to 0x30 (dtk had cut it into
  `0xC` plus a `gap_04_0000651C_data`, which scored `.data` 40% once it was in its own unit).

| unit | `.text` | `.rodata` | `.data` | evidence / confidence |
|---|---|---|---|---|
| `match_setup/match_loading.c` (+`rep_CC8`) | `0x59918-0x5A684` | `0xCC8-0xD18` | `0x3D60-0x4290` | next TU after fielder in every section; high |
| `data_only/gameplay_tables.c` (unchanged) | — | — | `0x4290-0x6510` | no table (see (c)); medium |
| `match_setup/match_main.c` (+`rep_D18`) | `0x5A684-0x5B220` | `0xD18-0xD68` | — | (a), (b): high that it is its own TU; the end could be anywhere in `0x5ACA0-0x5B220` (call chain `gameSimulationFunction` -> `simulate1FrameOfTheGame` -> `exitToMenuControl` and `fn_3_5AE0C` -> `gameInitRelated` keeps the whole top level together); medium |
| `match_setup/match_end.c` (+`rep_D68`) | `0x5B220-0x5C418` | `0xD68-0xDB8` | `0x6510-0x6540` | (a), (b) fix it as separate from `match_main`; its separation from `match_flow` rests on the table count (c) and the theme change; medium |
| `match_setup/match_flow.c` (+`rep_DB8`) | `0x5C418-0x60768` | `0xDB8-0xE08` | `0x6540-0x65EC` | (b); high |

`match_main.c` is 100% and `Matching`; the `dont_inline` pragmas are gone (nothing in
it calls `SetGameStatus` or `resetCount`). Every moved function kept its score.

Left open:

- **The alternative count.** If `gameplay_tables` did carry a table, `match_end` and
  `match_flow` would be one TU (nothing inlines across `0x5C418`, and neither half calls
  a small function of the other). The table rule (c) is the only argument against that.
- **Who owns `gameplay_tables`.** It may be `match_main`'s `.data`: that unit has none, and in
  link order its `.data` would sit exactly at `0x4290`. Or the match-end tail may be
  `match_end`'s own data: `CommonUIFiles_matchEnd` (`0x6130`, 8-aligned) is used only by
  `matchEndGameScreenFunction`, much as `match_loading` owns `CommonUIFiles_inGame`, and
  `lbl_3_data_5FF4`/`6074` only by `startChallengeModeMatch`. But all of these are globals
  read by symbol (no pooled base), the rest of the tail (`starPowerCosts`, `0x60F8`, `0x610C`)
  is read by other units, and `0x5FF4` cannot start a unit. So `gameplay_tables` stays one data-only unit.

## Main DOL: the Challenge translation unit (2026-10-12)

Main-DOL code has no `repHeaderData` signature, so the boundaries below come
from how the linker lays the unit's data out (`.data` objects are 4-aligned
inside a unit but every unit's `.data` starts 8-aligned; MWCC emits functions
in source order and does not share literal pools between units).

`challenge/challenge_progress.c` replaces five `Unknown/` units:

| section | range | was |
|---|---|---|
| `.text` | `0x8006C48C-0x8006CEBC` | `File_0x8006c48c` (`0x8006C48C-0x8006C5CC`), unowned gap `0x8006C5CC-0x8006C7C4` (`challenge_hasRecruitedEnoughNonBowserCharacters`, `challenge_countRecruitedCharacters`, `fn_8006C79C`), `File_0x8006c7c4`, `File_0x8006c9d8`, `File_0x8006cbe4`, `File_0x8006cca4` |
| `extab` / `extabindex` | `0x800065B0-0x800065C8` / `0x800083E8-0x8000840C` | the three units that had any |
| `.data` | `0x80109420-0x8010B610` | `File_0x8006c48c` + `File_0x8006c9d8` |
| `.sdata` | `0x803CB8F0-0x803CB8F8` | `File_0x8006c7c4` |

Evidence:

- **`.data` is one 8-aligned run.** Inside `0x80109420-0x8010B610` the objects
  `starMenuSizes` (`0x8010B42C`), `starRankByMissionCount` (`0x8010B444`) and
  `challengeIntermediateStarBuffs` (`0x8010B4B4`) start on 4-aligned,
  non-8-aligned addresses, so no unit boundary can be there. The old
  `File_0x8006c9d8` split started its `.data` at `0x8010B4B4`, which no real
  unit can do. The table order also reverses the text order
  (`starRankByMissionCount` at `0xB444`, used by `challenge_getStarRank`
  `0x8006CBE4`, sits *below* `challengeIntermediateStarBuffs` at `0xB4B4`,
  used by `intermediateStatBuffForCompletedMissions` `0x8006CAC8`), which two
  units in text order could not produce. Everything from the first Challenge
  function to `challenge_getStarRank` is therefore one unit.
- **Neighbours.** The `.data` run begins where the title-screen unit's data
  ends (`lbl_80109410`, `0x80109420`; its code `0x80069AD4-0x8006C488`, which
  also owns `.sdata 0x803CB8D8-0x803CB8F0` and `.sbss 0x803CBD30-0x803CBD40`)
  and ends at the 4-byte pad after `challengeInnings` (`0x8010B60C`), where
  `Dolphin/os/OS.c` starts. `.sdata` begins at `challengeCaptainCharIDs`
  (`0x803CB8F0`) and ends 2 bytes of pad before `__OSVersion`. The unit has no
  `.sdata2`, `.sbss` or `.rodata`.
- **Gap functions.** `challenge_hasRecruitedEnoughNonBowserCharacters`, `challenge_countRecruitedCharacters` and `fn_8006C79C` only read
  `g_Challenge` (they count characters whose recruitment byte
  is 1) and sit between two members of the unit, so they belong to it.

Left out on purpose: `fn_8006CEBC`/`fn_8006CF6C` (`0x8006CEBC-0x8006D024`,
menu-graphics load/unload pair; `fn_8006CF6C` is installed by `SetMenuNumber`
and reads `lbl_801075A8` from the menu `.data` block, so it is menu glue, not
Challenge logic), and `fn_8006C488` (empty function, no evidence either way).

The unit is `NonMatching` for now: `challenge_hasRecruitedEnoughNonBowserCharacters` (87%) and `challenge_countRecruitedCharacters`
(91%) are drafts whose loop unroll factor differs from the target, the two
`File_0x8006cca4` functions are still stubs, and
`challenge_leftoverTeammatesJoinBowserJr` is at 96.9%. `fn_8006C79C` is 100%
and renamed `challenge_isCharRecruited` (it returns whether
`characters[charID]._31` is `CHALLENGE_RECRUITMENT_CD_RECRUITED`; the menu REL
calls it with fixed character IDs). Before the merge
`File_0x8006c48c` and `File_0x8006cbe4` were `Matching`; every function's score
is unchanged.

### What sits next to the Challenge unit, and what does not belong to it (2026-10-12)

- **`mb_subfunc.c`** (`0x80064754-0x80069A68`) is a real original filename: the
  string `"mb_subfunc.c"` opens its `.rodata` (`0x800E69B8`) and
  `findCharacterID`, its last function, asserts with it. Its code is
  main-menu support (character select, rosters, team logos, draft demo), not
  Challenge. Its `.data` ends with `findCharacterID`'s jump table at
  `0x8010924C`, followed by the 4-byte pad to the next unit's 8-aligned start
  (`0x80109250`), and its `.sbss` ends at `0x803CBD30`.
- **`endDemo`** (`0x80069A98`) is not `mb_subfunc`'s: it shares `.sbss
  0x803CBD30` with `fn_80069B68`, which reads
  `titleScreenTexturesFileDescriptor`. It belongs to the title/boot-screen
  code `0x80069A68-0x8006C488` (data `0x8010924C-0x80109420`, `.sdata
  0x803CB8D8-0x803CB8F0`, `.sdata2 0x803CC8F8-0x803CC940`, `.sbss
  0x803CBD30-0x803CBD40`), which ends where Challenge starts. That unit is
  still unsplit.
- **`maybeUpdateFielderTerrainStatus`, `handleBallRollInWater`,
  `spawnDustPuff`** (`0x80063958-0x80064534`) sit in front of `mb_subfunc`.
  They share `.sbss 0x803CBD0C` with `fn_800639BC` and `fn_80062BE4`/`C60`/`D94`
  and read the small `.data` tables `0x80108D30-0x80108DB8`; they are
  field-terrain effects with no Challenge links. Left as they are.
- **Challenge menu functions** (`0x80056AE4-0x80059B38`: `drawStarProgressionMenu`,
  `someChallengeStarFunction`/`2`, `challengeCheckStarsMenuLoading`, `starMenu`,
  `scoutFlagMenu`, `zMenuLoadGraphics`, `starMissionRelated1`) do **not** form a
  Challenge-only unit; they are part of a much larger menu unit, and no split was made.
  Why: (1) `jumptable_80108AA8` (`fn_80059458`) and `jumptable_80108ADC`
  (`teamManagementGraphics_steadyState`, `0x80060184`) are adjacent and the
  second starts on a 4-aligned address, so everything from `0x80059458` through
  `0x80060184` (including `starMissionRelated1`, `battingOrderProcessInputs` and
  the `teamManagementGraphics_*` functions) is one unit; (2) the tables read by
  `scoutFlagMenu` (`lbl_80107688`) and `starMenu` (`lbl_80108048`) lie *after*
  the ones read by `teamManagementGraphics_initialLoad` (`0x801000A8`,
  `0x801041C8`) although their code lies before it, which units in text order
  could not produce, so `0x80057C08-0x8006236C` is one unit; (3)
  `lbl_800FEF70` is read by `fn_800531D0`, `fn_80053810`, `fn_80053FE8`,
  `fn_80055374`, `controlOptionsScreen`, `gameSettingsControllerInputs`,
  `startGameRelated`, `updateMenuNumbers` and `SetMenuNumber`, which stretches
  the same unit back to the options screens at `0x800531D0`. The star and
  scout screens are therefore one slice of a shared menu unit that also holds
  non-Challenge screens, and its start and end are not pinned down.
  `fn_8006CEBC`/`fn_8006CF6C` (`0x8006CEBC-0x8006D024`) are menu glue of the
  same family (`SetMenuNumber` installs `fn_8006CF6C`, which loads
  `lbl_801075A8` from this menu data block), which is why they stay out of
  `challenge_progress.c`.

## Main DOL: the charPipeline (C3) translation units (2026-10-12)

The Dolphin SDK "Character Pipeline" code in the main DOL sits in two places: the `structures`
and `texPalette` modules at `0x80091450` (inside the SDK libraries, between `GXPerf` and
`TRK_MINNOW_DOLPHIN`) and the rest of the pipeline at `0x800B2AC8-0x800C0770`, interleaved with
the game's own engine code (sound, draw list, sprites, shadows). Boundaries below come from
how the linker laid out each section; SDK file names (from the headers in `include/C3/` and
`include/charPipeline/`) are used for pieces that carry no data of their own and are marked
"SDK layout" where the binary gives no further evidence.

Evidence used, in decreasing order of strength:

- **Duplicate `.sdata2` constants.** MWCC pools each literal once per translation unit, so the
  same value (`1.0f`, `0.0f`, ...) appearing twice in `.sdata2` means a unit boundary lies between
  the two copies. `.sdata2` starts every unit 8-aligned, so a 4-byte hole before an 8-aligned
  constant is a boundary too (`0x803CCF14`, between `makeLookAtMatrix` and the sound unit).
- **`__FILE__` strings** the code passes to `OSPanic`: `"sound.c"` (`.sdata2 0x803CCF28`),
  `"sprt.c"` (`0x803CCF40`), `"act.c"` (`0x803CCF70`), `"animPipe.c"` (`.rodata 0x800E7D88`),
  `"DisplayObject.c"` (inside the warning at `0x800E7F20`).
- **Which functions touch which data object**, laid out in link order in every section
  (`.data`, `.rodata`, `.sdata`, `.sbss`, `.bss`).
- **`extab`/`extabindex`** rows only exist for non-leaf functions of a `-cpp_exceptions on` unit, and
  the hand-written asm skinning routines have none.
- For text-only runs with no data of their own, the SDK file layout decides.

### Structures and texPalette (`0x80091450-0x80091608`)

`Unknown/File_0x80091450.c` (6 functions, all 100% under `mw_version="GC/1.2.5n"`) is four SDK
translation units. No data, so this follows the SDK file layout only (the header names in
`include/charPipeline/structures/` are the SDK's file names):

| new unit | `.text` | functions |
|---|---|---|
| `C3/texPalette/texPalette.c` | `0x80091450-0x80091460` | `TEXGet` |
| `C3/structures/List.c` | `0x80091460-0x8009150C` | `DSInitList`, `DSInsertListObject` |
| `C3/structures/dolphinString.c` | `0x8009150C-0x8009155C` | `Strcmp` (the SDK declares it in `dolphinString.h`; `Strcat`/`Strcpy`/`Strlen` were dead-stripped) |
| `C3/structures/Tree.c` | `0x8009155C-0x80091608` | `DSInitTree`, `DSInsertBranchBelow` |

All four are `Matching` (the old unit was one `Matching` file, so the linked count goes up by 3).

### Actor: `act.c` and `actorAnim.c` (`0x800B2AC8-0x800B4E9C`)

Twelve `Unknown/File_0x800b2ac8 ... 4908` units plus six unowned gaps become two translation units.

| unit | `.text` | other sections | boundary evidence |
|---|---|---|---|
| `C3/actor/act.c` | `0x800B2AC8-0x800B4A44` | `.rodata 0x800E7D28-0x800E7D58`, `.data 0x80111640-0x80111670`, `.sdata2 0x803CCF58-0x803CCF78`, extab `0x80006990-0x80006A28` | the `"act.c"` string (`0x803CCF70`) is the `OSPanic` file name of `maybeProcessActLayout` ("Incorrect number of bones in actor", `.rodata 0x800E7D34`); the `.rodata` run `0x800E7D28-0x800E7D58` starts where the sprite unit's `"SPRITE BUFFER OVERFLOW"` ends and ends 8-aligned; `.data 0x80111640` (a 0x30 matrix) is read by `fn_800B313C` and `fn_800B3F20` only |
| `C3/actor/actorAnim.c` | `0x800B4A44-0x800B4E9C` | `.sdata2 0x803CCF78-0x803CCF80` | its pool is `0.0f` (`0x803CCF78`) and `1.0f` (`0x803CCF7C`); `act.c` already pooled both at `0x803CCF58`/`0x803CCF5C`, and MWCC pools a literal once per unit, so the two pools belong to different units. First user of the second pool is `getActorBoneAnimTime` (bone time), which starts the per-bone animation functions (`AnimateActorBones`, `setActorAnimFrame`, `ACTSetAnimation`) |

The boundary between `act.c` and `actorAnim.c` can sit anywhere in `0x800B4724-0x800B4A44`
(`renderingRelated`, `haveActLayoutPointToGeoHeader`, `LoadActorLayout`, `AdjustActorPointers` have no
constants of their own); it was put after `AdjustActorPointers`, i.e. as late as the pools allow, because
those four are layout/render code, not animation. The file names are the SDK's (`actor.c`/`actorAnim.c`
in `include/C3/actor.h`) except that the binary's own `__FILE__` string says `act.c`. The start at
`0x800B2AC8` is the first `Actor`-field accessor after the sprite unit's last data user
(`fn_800B2854`, `.sdata2 0x803CCF38`).

`actorAnim.c` links as `Matching` (it was the 99.7% `File_0x800b4908` minus `LoadActorLayout`, which
is 98% and went to `act.c`). `act.c` is `NonMatching`: it holds six functions that have no C yet
(`fn_800B2DD0`, `fn_800B313C`, `ACTRender`, `fn_800B3C04`, `fn_800B3F20`, `fn_800B4278`) and five stubs. The
eight small gap functions (`fn_800B2BA8`, `fn_800B2BE4`, `fn_800B2BFC`, `fn_800B2C08`, `fn_800B2C10`,
`fn_800B2C88`, `fn_800B2D5C` (the skinning step: `GQRSetup5`, then `SKNIt` or `processModelDataRelated` on
the skin object's position array) and `fn_800B4724`) were written in this pass and are 100%; `SKNIt`
and `processModelDataRelated` therefore take the vertex array as a third argument. Five previously `Matching`
units became part of it (`ProcessActorBonesForShadows`, `fn_800B2B4C`/`54`/`6C`, `callDSInsertListObject`,
`ACTSort`, `maybeBallRelated`).

`.sbss 0x803CC1E8` (8 bytes) is written by `fn_800B313C` (`act.c`) and read by `fn_800B84AC` (`control.c`);
which of the two units defines it is not decidable from the binary, so it stays unowned.

### Anim: `animBank.c`, `animPipe.c` and `boneAnim.c` (`0x800B4E9C-0x800B7D3C`)

| unit | `.text` | other sections | evidence |
|---|---|---|---|
| `C3/anim/animBank.c` | `0x800B4E9C-0x800B516C` | extab `0x80006A28-0x80006A38` | no data of its own, so SDK layout (`include/C3/anim.h` lists `ANIMGet`, `ANIMGetSequence`, `ANIMGetTrackFromSeq`, `ANIMGetKeyFrameFromTrack` under `animBank.c`). The edges are fixed by neighbours: `actorAnim.c`'s last constant user is `ACTSetAnimation` (ends `0x800B4E9C`), `animPipe.c`'s first is `Squad` (`0x800B516C`) |
| `C3/anim/animPipe.c` | `0x800B516C-0x800B79D0` | `.rodata 0x800E7D58-0x800E7E78`, `.sdata 0x803CBB48-0x803CBB58`, `.sdata2 0x803CCF80-0x803CCFB8` | the string `"animPipe.c"` (`.rodata 0x800E7D88`) is the `OSPanic` file name of `DoTranslationAnimation` and `DoQuatAnimation`; the `.sdata2` pool `0x803CCF80-0x803CCFB4` is shared by `Squad`, `GetData`, the four `Do*Animation` functions and `ANIMTick`. `ANIMBind` (`0x800B79A0`) is the SDK's `animPipe.c` too and ends the unit |
| `C3/actor/boneAnim.c` | `0x800B79D0-0x800B7D3C` | `.sdata2 0x803CCFB8-0x803CCFC0` | `ACTSetBoneTrack` pools `0.0f`/`1.0f` at `0x803CCFB8`/`0x803CCFBC`; the anim pool already holds both (`0x803CCF90`, `0x803CCF84`) and the frustum unit after it holds another `1.0f`, so a unit boundary lies on each side of this pair |

`animBank.c` links `Matching` (four `Matching` units merged, all 100%). `animPipe.c` is `NonMatching`
(seven stubs; `ANIMBind` was `Matching` before) and so is `boneAnim.c` (`ACTSetBoneTrack` stub; the
stub now has the real 4-parameter prototype from `C3/actor.h`). The order of files matches the SDK
(`actor.c`, `actorAnim.c`, `animBank.c`, `animPipe.c`, `boneAnim.c`, `control.c`: case-insensitive
alphabetical, with the frustum unit sitting between `boneAnim` and `control`).

### Frustum culling is not part of `control.c` (`0x800B7D3C-0x800B845C`)

`C3/control/control.c` was cut as `0x800B7D3C-0x800B993C` and held three stubs
(`checkObjectVisibility`, `fn_800B806C`, `checkPlaneIntersection`) at the start of its `.text`. Their
data does not belong to the CTRL functions:

- Their `.sdata2` pool is `-1.0f, 1.0f, 2.0f, 0.0f, -2.0f` at `0x803CCFC0-0x803CCFD4`; the CTRL pool at
  `0x803CCFD8` repeats `1.0f`, `0.0f`, `-1.0f`, and the `boneAnim.c` pool at `0x803CCFB8` repeats `1.0f`
  and `0.0f`. One unit pools a literal once, so both boundaries are certain.
- `.bss 0x803CB1FC-0x803CB49C` (four 0xA8-byte frustums, written by `fn_800B806C`, read by
  `checkObjectVisibility`) and `.data 0x80111670-0x801116A0` (two 0x18-byte tables read by
  `checkPlaneIntersection` / `checkObjectVisibility`) are touched by nothing in the CTRL group; the CTRL
  `.data` starts at `flipYMatrix` (`0x801116A0`).

`control.c` is now `0x800B845C-0x800B993C` (`CTRL_GetQuatUnk` through `CTRLSetScale`), with
`.data 0x801116A0-0x80111700` and `.sdata2 0x803CCFD8-0x803CCFF8`; it has no `.bss`. The 16 functions
that have C are 100%; only `fn_800B84AC` (the quaternion blend helper, which reads the `.sbss
0x803CC1E8` flag that `act.c`'s `fn_800B313C` writes) is a stub. The new
`C3/control/frustum.c` (`.text 0x800B7D3C-0x800B845C`, `.data 0x80111670-0x801116A0`, `.bss
0x803CB1FC-0x803CB49C`, `.sdata2 0x803CCFC0-0x803CCFD8`) is a stub unit.

**Name is a proposal.** `fn_800B806C(slot, ...)` fills a frustum from seven floats and
`checkObjectVisibility(slot, corners, mtx)` tests eight corners against it, hence `frustum.c`. The
binary gives no file name. Link order puts the unit between `boneAnim.c` and `control.c`; if the SDK
list is case-insensitive alphabetical (as `act`, `actorAnim`, `animBank`, `animPipe`, `boneAnim`,
`control` are), the real name sorts in `bo...-co...`, so `frustum.c` is likely not it (`clip...`,
`cam...`, `collision...` would fit).

### DisplayObject and normalTable (`0x800B993C-0x800BCB44`)

`Unknown/DisplayObject.c` moved to `C3/geoPalette/DisplayObject.c` (the SDK keeps `displayObject.c`
in the geoPalette module, `include/C3/geoPalette.h`; the binary's file name, from the warning
`"Warning: DisplayObject.c: User TevMode %d not handled."`, is `DisplayObject.c`). Its split is unchanged
and it still builds with `mw_version="GC/2.6"`: a sweep over the range showed only `SetFog` and
`updateVectorInArray` (the latter in the shadow unit) change under `GC/1.3.2` (`SetFog` 100% -> 77%),
while `CTRL_GetQuatUnk` in `control.c` needs `GC/1.3.2` (75% under 2.6). So the pipeline code is not one
compiler: `control.c` is 1.3.2 and `DisplayObject.c` is 2.6. The other pipeline units (act, anim, geo,
light) are insensitive to the version.

`C3/geoPalette/normalTable.c` is the data-only unit that follows it: `.data 0x80111750-0x80112338`
(the 0xBE8-byte table of 254 unit normals, which `DOVARender` hands to `GXSetArray`) and `.sdata
0x803CBB60-0x803CBB68` (`normalTableQuantizeInfo`, the byte `DOVARender` reads; dtk sizes it 8 because of
the 7 pad bytes). Both directly continue `DisplayObject.c`'s own `.data`/`.sdata`, and no text
function touches them except through `DOVARender`. It is `Matching` (data 99.7%: the 7 `.sdata` pad
bytes). The table has 254 entries; the SDK header declared 252.

### geoPalette, GQRSetup and light (`0x800BCB44-0x800BD478`)

| unit | `.text` | other sections | evidence |
|---|---|---|---|
| `C3/geoPalette/geoPalette.c` | `0x800BCB44-0x800BD1F0` | extab `0x80006B48-0x80006B68` | no data; SDK layout (`geoPalette.c` holds `GEOGetPalette` = `LoadGeoPalette` and its pointer-fixup helpers) and the neighbours: `DisplayObject.c` ends at `DOGet` (its string at `.rodata 0x800E7F8C` is 4-aligned directly after `DOVARender`'s, which a new unit could not do, see `DisplayObject.c` above) and `GQRSetup.c` starts at the first asm helper. `fn_800BD1E8` (a setter for `DisplayObject.c`'s `.sbss 0x803CC20C` callback) sits at its end |
| `C3/skinning/GQRSetup.c` | `0x800BD1F0-0x800BD2B0` | - | SDK layout (`GQRSetup.c`, `include/C3/skinning.h`): `__MTGQR5/6/7` (asm) then `GQRSetup7/6/5`; the SDK's `GQRSetup0-4` were dead-stripped |
| `C3/light/light.c` | `0x800BD2B0-0x800BD478` | `.sbss 0x803CC220-0x803CC228`, `.sdata2 0x803CD058-0x803CD060` | `LITAlloc` pools `0.0f`/`1.0f` at `0x803CD058`, a pool that `DisplayObject.c` (`0x803CCFFC`, `0x803CD004`) and the next unit (`0x803CD060`, `0x803CD064`) repeat. The `.sbss` pair is the `lightingRelated`/`adjustLightingParams`/`fn_800BD2DC` ambient-colour override (the engine's addition in front of the SDK `LIT*` functions) |

`light.c` and `GQRSetup.c` link `Matching`. `LITXForm` was a stub; its body is the SDK one
(`CTRLBuildMatrix`, `PSMTXConcat` with parent and camera, `PSMTXMultVec`, `PSMTXInverse`,
`PSMTXTranspose`, `PSMTXMultVec`) and came out 100% first try. `maybeDoLighting` and
`lightingDataArray` are now `static` definitions in the unit; the colour needs
`__attribute__((aligned(4)))` (the target keeps it in a 4-aligned word at `0x803CC224`) and must be
declared before the flag so the flag lands at `0x803CC220`. `geoPalette.c` is `NonMatching`
(`LoadGeoPalette` and `AdjustGPLDataPointers` are stubs; `fn_800BCDBC` has no C yet). Merging
`LoadGeoPalette` into the same unit as `convertGeometryAndSknHeader` let the stub inline into it
(`convertGeometryAndSknHeader` fell from 100% to 44%); the stub is marked `dont_inline`.

### Skinning: `SKNControl.c` and `SKNAsm.c` (`0x800BF074-0x800C0770`)

| unit | `.text` | other sections | evidence |
|---|---|---|---|
| `C3/skinning/SKNControl.c` | `0x800BF074-0x800BFE90` | `.bss 0x803CB6FC-0x803CB734`, extab `0x80006C20-0x80006C40` | `SKNInit`, `SKNIt` and `processModelDataRelated` are the only users of `SKAccBuffers` (`0x803CB6FC`, 0x28) and `SKBuffers` (`0x803CB724`, 0x10); `SKNLoadFile` calls `SKNInit`, and `SKNFlushByIndex1/2`/`SKNBzero32B` (`asm`) are `SKNIt`'s helpers. `include/C3/skinning.h` files `SKNIt`, `SKNInit` and `SKNBzero32B` under `SKNControl.c` |
| `C3/skinning/SKNAsm.c` | `0x800BFE90-0x800C0770` | - | the six vertex kernels `SKN1Vecs16Norms16`, `SKN2Vecs16Norms16NoTouch`, `SKNAccVecs16Norms16Iu16` and their second copies (`fn_800BFF9C`, `fn_800C02C8`, `SKNAccVecs16Norms16Iu162`). **Name and the boundary are proposals**: the kernels carry no data, and `asm` functions also sit inside `SKNControl.c` (`SKNFlushByIndex1/2`), so extab absence proves nothing. They come in X/Y pairs in the order 1V, 2V, Acc, while the two C drivers come Y, X (`processModelDataRelated` calls `GQRSetup6` and the `fn_800BFF9C`/`fn_800C02C8` copies, `SKNIt` calls `GQRSetup7` and the others), which looks like two different generators, so they were kept apart |

`convertTextureHeader` (`0x800C0770-0x800C07BC`), which used to be the tail of
`File_0x800bfe90.c`, is a C function (a header fixup loop with a 0x20 stride) that has nothing to do with
the kernels; it became `Unknown/File_0x800c0770.c`. The merge sort `fn_800C07BC` after it
(`0x800C07BC-0x800C0A8C`) is still an unowned gap.

`SKNControl.c` is `NonMatching` (the two driver copies are stubs, now with the SDK's
`(sBone**, sHdr*)` signature); `SKNLoadFile`, the three flush/zero helpers and `SKNInit` are 100% but
four `Matching` units were absorbed. `SKNAsm.c` is six stubs.

### The game's sound wrapper: `Unknown/sound.c` (`0x800B07FC-0x800B0A14`)

`File_0x800b07fc` (`soundQuit`), `File_0x800b0834` (`initSound`, was a stub), the unowned `fn_800B0934`
(an empty function) and `File_0x800b0938` (`SndFree`, `SndAlloc`) are one unit; the binary names it:
`initSound` passes `"sound.c"` (`.sdata2 0x803CCF28`) to `OSPanic`.

- `.sdata2 0x803CCF18-0x803CCF30`: `soundQuit` and `initSound` each copy a two-pointer `SND_HOOKS`
  aggregate out of the pool (`{SndAlloc, fn_800B0934}` at `0x803CCF20`, `{SndAlloc, SndFree}` at
  `0x803CCF18`) and the file name string follows. The pool holds initSound's table *first* although
  `soundQuit` comes first in `.text`; building the unit with `-inline deferred` and defining the
  functions in reverse address order (helpers first, which is also what lets `initSound` use `SndAlloc`
  and `SndFree` without prototypes) reproduces that, the same way `control.c` is written. The two 4-byte
  labels `lbl_803CCF18`/`lbl_803CCF1C` were merged into one 8-byte local object.
- `.sdata 0x803CBB10` (pointer to the sound heap descriptors) is read by `initSound`, `SndFree` and
  `SndAlloc`; `.data 0x801112F0` is `initSound`'s default `sndInit` configuration (the `0x40, 0x30,
  0x10, 1` voice counts and an 8 MB ARAM size); `.rodata 0x800E7CB0-0x800E7D10` are the three panic
  messages (`0x800E7CB0` was unowned before).
- Boundaries: `makeLookAtMatrix` (`0x800B0724`) is a separate unit, since its `.sdata2` (`0x803CCF08-0x803CCF14`)
  ends with a 4-byte hole before this unit's 8-aligned pool, and the draw-list unit starts at
  `removeCurrentDrawingItem` (`0x800B0A14`), the first user of `.sbss 0x803CC1B0`.
- The heap descriptors (`lbl_802FE8A0`, 0x18 bytes) cannot be claimed in `.bss`: the unowned `.bss`
  between `SIBios` and `File_0x800a6304` is a single auto object, and splitting it for one unit makes
  dtk's link-order resolution cyclic (every unit between has its `.bss` elsewhere). The symbol stays
  `extern` in the unit.

The unit links as `Matching`. `initSound` was written from the asm (100% on the first structural
attempt after the register order of the parameter reuse): the default config is the `config == NULL`
fallback, `sndInit` takes the config fields in order, and the failure path is `OSPanic("sound.c", 278, ...)`.
`fn_800B0934` is the empty free hook that `soundQuit` installs. Two `Matching` units became one; linked
DOL units 265 -> 264.

### The sprite renderer: `Unknown/sprt.c` (`0x800B0D28-0x800B2AC8`)

Six `Unknown` units and fifteen unowned functions (`fn_800B0D28`, `fn_800B0D38`, `fn_800B117C`,
`fn_800B1188`, `fn_800B12DC`, `fn_800B1388`, `fn_800B13C0`, `fn_800B1468`, `fn_800B1EBC`, `fn_800B2240`,
`fn_800B24D4`, `fn_800B251C`, `fn_800B27A4`, `fn_800B27DC`, `fn_800B2854`) form one unit, again named by
its own `OSPanic` string: `DrawSprite` and `fn_800B1EBC` both pass `"sprt.c"` (`.sdata2 0x803CCF40`)
with the message `"SPRITE BUFFER OVERFLOW\n"` (`.rodata 0x800E7D10`).

- One `.sdata2` pool spans the whole range: `1.0f` (`0x803CCF30`, `fn_800B1188`), the int-to-float
  magic double (`0x803CCF38`, `fn_800B27DC`/`fn_800B2854`), the file name, `0.0f` (`0x803CCF48`, shared by
  `DrawSprite` and `fn_800B2240`) and the unsigned magic double (`0x803CCF50`, `DrawSprite`/`fn_800B1EBC`).
  `fn_800B2240` and the functions after it share these with `DrawSprite`, so there is no unit boundary in
  `0x800B1500-0x800B2AC8`; the start is fixed from below by the draw-list unit's last function
  (`RunDrawScripts_with_stack_variables`, ends `0x800B0D28`) and `fn_800B0D28`/`fn_800B0D38` (the
  per-slot setters for `.data 0x80111340` and `.sbss 0x803CC1D8`), which belong to the sprite arrays.
- `.sdata 0x803CBB18-0x803CBB48` (the sprite buffer pointers, `lbl_803CBB34` is read by nearly every
  function), `.sbss 0x803CC1C0-0x803CC1E8` and `.data 0x80111340-0x80111640` (the per-slot tables; their
  ends meet `act.c`'s `0x80111640`) are used by these functions only.
- The sprite buffers in `.bss` (`0x802FE8B8-0x803009F8`, and `0x803C8A24`) are not claimed: like the
  sound heap, they sit in the big unowned `.bss` objects that dtk cannot split without a cycle.

`NonMatching`: `AllocateSprite` and `DrawSprite` are stubs and eleven functions have no C (four small ones, `fn_800B0D28`, `fn_800B117C`, `fn_800B12DC` and `fn_800B1388`, were written in this pass and are 100%). Four
previously `Matching` units (`DrawNullSprite`, `renderSprite`, `DrawSprite_TexObj` and the three
`setTextRenderingMode` helpers) were absorbed; linked DOL units 264 -> 260. They were only `Matching`
because nothing else of the unit was in front of them; the pool evidence makes them part of it.
The draw-list functions before it (`0x800B0A14-0x800B0D28`) share `.data 0x80111300` and `.sbss
0x803CC1B0` among themselves but no pool with `sprt.c`, so they were left as they are.

### The shadow pass: `Unknown/File_0x800bde8c.c` (`0x800BDE8C-0x800BF074`)

`File_0x800bea04` (`setVectors`), `File_0x800beb3c`, `File_0x800bf008` (`loadTlutRelated`),
`File_0x800bf038` (`ShouldDrawShadows` and the callback setters) and the unowned `fn_800BDE8C`,
`fn_800BDEA0`, `fn_800BDF70`, `fn_800BDFE0`, `fn_800BE09C`, `fn_800BE158`, `fn_800BE498` and
`fn_800BEC30` are one unit: every one of them reads or writes the 0x50-byte `drawShadows` state
(`.bss 0x803009F8`) and the `.sdata2` pool `0x803CD068-0x803CD0E0` runs through `fn_800BDEA0`,
`fn_800BE09C`, `fn_800BE158`, `fn_800BE498`, `fn_800BEB3C` and `fn_800BEC30` (`0.0f` at `0x803CD070` is
shared by five of them, `1.0f` at `0x803CD07C` by three). Its `1e8`/`-1e8` bounds, `0.0f` and `1.0f`
repeat the previous unit's pool (`0x803CD060`/`0x803CD064`), which is what fixes the boundary with
`File_0x800bd8c4.c`; the other end is `ShouldDrawShadows` (`0x800BF068`), directly followed by
`SKNLoadFile`. Other data: `.rodata 0x800E8030-0x800E8060` (six floats read by `fn_800BEC30`) and
`.sdata 0x803CBB68-0x803CBB70` (`fn_800BE158`).

The role (a shadow-map pass: `GXCopyTex`, `GXInitTexObjCI` with a TLUT, ortho/light matrices and the
min/max point accumulator `setVectors`) is clear, the file name is not, so the unit keeps an
address name. `drawShadows` itself (`.bss`) stays unowned for the same reason as the sound heap.

`NonMatching`: eight functions (about 0x1600 bytes) have no C yet. Three `Matching` units were
absorbed (`setVectors`, `loadTlutRelated`, the four `File_0x800bf038` helpers); `File_0x800beb3c` was
already `NonMatching` although all its functions are 100%. Linked DOL units 260 -> 257.

Not merged (considered): the actor-object unit `File_0x800bd8c4.c` (`0x800BD8C4-0x800BDE8C`,
`.rodata 0x800E7FC8`, `.data 0x80112380`, `.sdata2 0x803CD060`) keeps its split, and the three
functions in front of it (`fn_800BD478`, `fn_800BD548`, `fn_800BD670`, `0x800BD478-0x800BD8C4`, jump
tables `0x80112338` and `0x8011235C`) stay unowned: the tables are 4-aligned, so those two functions share a
unit, but nothing in the data says whether that unit is `File_0x800bd8c4.c`'s, `light.c`'s or its own, and
merging them would turn a `Matching` unit into a `NonMatching` one for a guess.

### Renames

Only placeholders whose function, signature and place in the module all agree with the SDK were renamed
(`config/GYQE01/symbols.txt` and every use; the demo configs are untouched):

| was | now | evidence |
|---|---|---|
| `fn_800B3A78` | `ACTRender` | collects a `va_list` (`stfd f1-f8` behind the `bne cr1`, `r3-r10` spilled) and forwards it to `DOVARender`/`DOVARenderSkin` after `SKNIt`; every caller passes `(actor, camera, numLights, extra args...)`, which is `ACTRender(Actor *actor, MtxPtr camera, u8 numLights, ...)` in `include/C3/actor.h` |
| `fn_800B4C04` | `ACTSetSpeed` | writes `ANIMPipe::unk08` for every bone; its callers pass the literal `1.0f` or a field named `animSpeed`; in `actorAnim.c` the functions run `ACTSetAnimation`, `setActorAnimFrame` (= `ACTSetTime`), `fn_800B4C04`, `AnimateActorBones` (= `ACTTick`) in reverse address order, which is exactly the SDK's source order `ACTSetAnimation, ACTSetTime, ACTSetSpeed, ACTTick` with the engine's extras interleaved |

`setActorAnimFrame` and `AnimateActorBones` already carry descriptive names and were left alone. Their
callers needed `(Actor*)` casts at the eight `ACTSetSpeed` sites because `include/C3/actor.h` declares the SDK
prototype.

Candidates that were **not** renamed for lack of evidence: `fn_800B313C` (looks like `ACTBuildMatrices`:
`CTRLBuildMatrix`, `DOSetWorldMatrix`, `PSMTXInverse`/`PSMTXTranspose`, one actor argument; but it also
does the engine's bone blending), `fn_800B2D5C` (a 0x74-byte loop, perhaps `ACTSetAmbientPercentage`),
`fn_800B3C04` (frustum test plus shadow bounds, an engine function), `processModelDataRelated` (the second
`SKNIt` copy, selected when the skin header's shift byte is not `0x40`), `LoadGeoPalette` (the SDK's
`GEOGetPalette` takes a name, this one takes the loaded file), and the `DisplayObject.c` placeholders
(`fn_800B9950` writes two floats under a mask like `DOOverrideTextureState`, but with a different
signature).

### Summary of the charPipeline pass (2026-10-12)

Main-DOL linked (`Matching`) units 280 -> 257, no function score fell (15 functions that were stubs
or had no C are now 100%: `initSound`, `fn_800B0934`, `LITXForm` and the small `act.c` and `sprt.c` gap
functions; `checkObjectVisibility` rose from 0.5% to 0.7% with its real prototype). Old unit -> new unit:

| new unit | status | replaces |
|---|---|---|
| `C3/texPalette/texPalette.c`, `C3/structures/List.c`, `dolphinString.c`, `Tree.c` | all `Matching` | `File_0x80091450` |
| `Unknown/sound.c` | `Matching` | `File_0x800b07fc`, `0834`, `0938`, `fn_800B0934` |
| `Unknown/sprt.c` | `NonMatching` | `File_0x800b0d68`, `12a4`, `1314`, `1350`, `1500`, `2160` + 15 gap functions |
| `C3/actor/act.c` | `NonMatching` | `File_0x800b2ac8`, `2b4c`, `2b74`, `2c44`, `2cbc`, `34b4`, `37a4`, `4048`, `4084`, `43a0`, `472c`, `4908` (first part) + gaps |
| `C3/actor/actorAnim.c` | `Matching` | `File_0x800b4908` (second part) |
| `C3/anim/animBank.c` | `Matching` | `File_0x800b4e9c`, `4f9c`, `4fec`, `508c` |
| `C3/anim/animPipe.c` | `NonMatching` | `File_0x800b516c`, `560c`, `5da8`, `63dc`, `6e0c`, `71c0`, `7718`, `79a0` |
| `C3/actor/boneAnim.c` | `NonMatching` | `File_0x800b79d0` |
| `C3/control/frustum.c` | `NonMatching` | first 0x720 bytes of `C3/control/control.c` |
| `C3/control/control.c` | `NonMatching` | (shrunk to `0x800B845C-0x800B993C`) |
| `C3/geoPalette/DisplayObject.c`, `normalTable.c` | `Matching` | `Unknown/DisplayObject.c` (moved), new data-only unit |
| `C3/geoPalette/geoPalette.c` | `NonMatching` | `File_0x800bcb44`, `bcd60`, `bce38`, `bcef8`, `bd190` (first part) + gap |
| `C3/skinning/GQRSetup.c` | `Matching` | `File_0x800bd190` (second part), `bd208`, `bd240`, `bd278` |
| `C3/light/light.c` | `Matching` | `File_0x800bd2b0`, `bd300`, `bd3a0`, `bd3cc`, `bd3ec` |
| `Unknown/File_0x800bde8c.c` | `NonMatching` | `File_0x800bea04`, `beb3c`, `bf008`, `bf038` + 8 gap functions |
| `C3/skinning/SKNControl.c`, `SKNAsm.c` | `NonMatching` | `File_0x800bf074`, `bf1a4`, `bf204`, `bf2a8`, `bf89c`, `bfe90` |
| `Unknown/File_0x800c0770.c` | `NonMatching` | tail of `File_0x800bfe90` |

`Matching` units that became part of a `NonMatching` unit: `ProcessActorBonesForShadows`,
`fn_800B2B4C`/`54`/`6C`, `callDSInsertListObject`, `ACTSort`, `maybeBallRelated` (act.c); `ANIMBind`
(animPipe.c); `convertGeometryAndSknHeader`, `AdjustGEOPalettePointers`, `UpdateTexturePalettePointers`
with `fn_800BD1E8` (geoPalette.c); `SKNLoadFile`, the flush/zero helpers, `SKNInit` (SKNControl.c);
`DrawNullSprite`, `renderSprite`, `DrawSprite_TexObj`, `setTextRenderingMode` with its two helpers
(sprt.c); `setVectors`, `loadTlutRelated`, the `File_0x800bf038` helpers (`File_0x800bde8c.c`).

Left in `Unknown/` on purpose:

- `File_0x800b0724` (`makeLookAtMatrix`): its own unit by the `.sdata2` hole at `0x803CCF14`; game math,
  not charPipeline.
- `File_0x800b0a14` + `File_0x800b0cb8` (draw list, `0x800B0A14-0x800B0D28`): the boundaries on both
  sides are fixed (sound unit before, sprite unit after) but nothing says whether the seven functions are
  one unit or two (they share `.data 0x80111300` and `.sbss 0x803CC1B0`, which are globals, not pooled
  literals); merging would also cost a `Matching` unit.
- `File_0x800bd8c4` and the unowned `0x800BD478-0x800BD8C4` (the actor-object functions): see the shadow
  section above.
- `File_0x800c0770` (`convertTextureHeader`) and the merge sort `fn_800C07BC` (`0x800C07BC-0x800C0A8C`,
  unowned): no data, and nothing ties them to a neighbour.

Open questions: who defines `.sbss 0x803CC1E8` (written by `act.c`, read by `control.c`); the real file
name of the frustum unit and of the six skinning kernels; whether the draw-list functions are one unit; whether
`0x800BD478-0x800BD8C4` belongs to `File_0x800bd8c4.c`; the `.bss` of the sound heap, sprite buffers and
`drawShadows` (low `.bss`, unowned auto object) would need the whole auto object split before any
unit can claim it.

## Main DOL: Unknown units merged on linker evidence (2026-10-14)

Same method as the Challenge and charPipeline passes above: the main DOL has no
`repHeaderData` signature, so a unit boundary can only be proved wrong when two
`Unknown/` units (or an unowned gap function) share something a single
translation unit would own: a `.sdata2` literal pool (MWCC pools a literal once
per unit, so one pool with no repeated values is one unit), a string whose
`__FILE__`-style name matches, a `.data` run with 4-aligned object starts, or a
jump table that is not 8-aligned. The unowned gap functions between the units
are part of the unit by the same argument. Gap functions have no C yet; the
merged units are `NonMatching` and link from the original asm, so only the
functions that already had C are scored.

### `Unknown/objinit.c` (`0x80022DAC-0x80023AA4`)

| section | range | was |
|---|---|---|
| `.text` | `0x80022DAC-0x80023AA4` | `File_0x80022dac` (`f_InitBone`), gap `fn_80023078`, `File_0x800232e0` (`f_InitActorWithLayout`), `File_0x8002360c` (`BuildBoneSkinOrientationMatrix`), gap `fn_800238E0`, `File_0x8002399c` (`characterAndBallDisplayRelated`) |
| `extab` / `extabindex` | `0x80005B08-0x80005B38` / `0x800073EC-0x80007434` | the four units' entries plus the two gap functions' |
| `.rodata` | `0x800E6698-0x800E6708` | unowned (`lbl_800E6698`, 0x70 bytes) |
| `.sdata2` | `0x803CC560-0x803CC568` | unowned (`0.0f`, `1.0f`) |

Evidence:

- **The binary names the unit.** `lbl_800E6698` is a string pool that holds
  `"objinit.c"` at `+0x3C` between its two panic messages ("Display object id %d
  is greater than number of objects %d" and "Incorrect number of bones in
  actor"), and both `f_InitBone` and `f_InitActorWithLayout` read it.
- **One `.sdata2` pool.** `f_InitBone`, `f_InitActorWithLayout`,
  `fn_800238E0` and `characterAndBallDisplayRelated` read only
  `0x803CC560`/`0x803CC564`, with no repeated value. The next unit
  (`File_0x80023b90`, `0x803CC568`) repeats `0.0f`, so the pool ends here.
- **Boundaries.** `File_0x80023b04` (`initActorArray`, `Matching`) is not
  part of it: it has no constants of its own, and the unowned gap function
  `fn_80023AA4` between them is left alone. `File_0x80023b90` has its own
  pool and `.rodata`.

`.sbss 0x803CBC58`/`actorSize (0x803CBC5C)` is read by both `fn_800238E0`/
`characterAndBallDisplayRelated` and `initActorArray` (`Matching`, outside the
unit), so no `.sbss` is claimed. The `f_InitActorWithLayout` stub is wrapped in
`#pragma dont_inline`: the old one-function unit saw it as an external call, and
a visible `return NULL` body would be inlined into
`characterAndBallDisplayRelated`.

Four `NonMatching` units became one; no function score changed
(`characterAndBallDisplayRelated` stays 100%). Linked DOL units 260 -> 260.

### `Unknown/particle_effects.c` (`0x800263FC-0x80034BCC`)

Six `Unknown/` units (`File_0x800263fc`, `33794`, `33f64`, `34220`, `3452c`,
`348c8`) and 57 unowned functions between them form one unit. The name is a
proposal: the range holds `allocParticleEffect`, `setParticleXform`,
`spawnDaisyStarEffect`, `spawnPeachStarEffect`, `setDaisyStarEffectTarget` and
`setPeachStarEffectTarget`, plus the minigame setup helpers
(`minigamesSetSomePointers`, `minigamesGXStuff`, `minigamesSetSomePointers2`)
that sit at its end; the binary carries no file name for it.

| section | range | was |
|---|---|---|
| `.text` | `0x800263FC-0x80034BCC` | the six units and the gaps `0x80026998-0x80033794` (51 functions), `0x80033B58-0x80033F64` (`fn_80033B58`, `fn_80033CC8`), `0x8003403C-0x80034220` (`fn_8003403C`, `fn_800340F4`, `fn_80034120`, `fn_8003414C`) |
| `extab` / `extabindex` | `0x80005BC8-0x80005D98` / `0x8000750C-0x800077C4` | the entries of every function in the range (the small leaf functions have none) |
| `.rodata` | `0x800E6778-0x800E68A8` | unowned: eleven float vectors and the `"...particle err."` string |
| `.data` | `0x800F7840-0x800F78E0` | unowned (`lbl_800F7840`, `7860`, `787C`, `78C0`) |
| `.sdata` | `0x803CB7F8-0x803CB810` | unowned (six 4-byte constants read by `fn_800328E0`, `fn_80030720`, `fn_800317C4`, `fn_8002FDB8`, `fn_8002C56C`, `fn_8002BC84`) |
| `.sbss` | `0x803CBC70-0x803CBC90` | unowned (`lbl_803CBC70-lbl_803CBC84`) |
| `.sdata2` | `0x803CC5F0-0x803CC6E8` | unowned (50 literals) |

Evidence:

- **One `.sdata2` pool, no duplicates.** `0x803CC5F0-0x803CC6E8` is read by
  functions from `maybeTexOrSpriteRelated` to `minigamesSetSomePointers2`
  and holds each value once (`0.5f` at `0x803CC5F0`, `0.0f` at `0x803CC5F4`,
  the two magic doubles, ..., `pi`, `1025.0`). The pool before it
  (`0x803CC5D8-0x803CC5F0`, `fn_80026134`) already holds `0.0f` and `0.5f`, and
  the one after it (`0x803CC6E8`, `allocateGraphicsSlot`) starts with `0.0f`
  again, so a boundary lies on each side and none inside.
- **`.rodata` runs in reverse function order.** `lbl_800E6778` is read by
  `fn_800332B8`, `lbl_800E6784` by `fn_800328E0`, ... `lbl_800E685C` by
  `fn_80026E58` and the string at `0x800E688C` by
  `maybeTexOrSpriteRelated` (first function of the unit) and its later users
  `fn_8002B014`, `fn_80031034` and `fn_80031F34`; each function's vector was
  emitted when the function was compiled and the objects are laid out last to
  first, which only one unit produces. The range ends with the 8-alignment pad
  after the 0x15-byte string.
- **`.sbss 0x803CBC70-0x803CBC90`** (`lbl_803CBC74`, `lbl_803CBC80`,
  `lbl_803CBC84` are read by dozens of functions across the range, including
  four of the six former units, `lbl_803CBC78`/`7C` by the three minigame helpers).
- **`.data` and `.sdata`** objects are read by gap functions of this range
  only (`lbl_800F7860` by `maybeTexOrSpriteRelated` and five gap functions,
  `lbl_800F787C` by `fn_80032064/284/4EC`, `lbl_800F7840` by
  `minigamesGXStuff`).

The unit is compiled with `-cpp_exceptions on`: `setParticleXform` (the only
function with C beyond stubs, 100%) needed it, and a unit has one flag set. 58 of the
69 functions have an `extabindex` entry, the others are small and sit between
functions that do. All six former units were
`NonMatching`; `setParticleXform` stays 100%, nothing else changed. The 21 files
that include the old headers now include `Unknown/particle_effects.h`.
Linked DOL units 260 -> 260 (the merged unit is `NonMatching`, like all of its parts).

### `Unknown/graphic.c` (`0x800A7C08-0x800A84C4`)

| section | range | was |
|---|---|---|
| `.text` | `0x800A7C08-0x800A84C4` | `File_0x800a7c08` (`someGFXRenderingFn`), gap `fn_800A7D4C`, `fn_800A7D7C`, `fn_800A7DB0`, `fn_800A7E00`, `fn_800A7F10`, `File_0x800a80e8` (`initRenderMode`) |
| `extab` / `extabindex` | `0x80006698-0x800066C0` / `0x80008544-0x80008580` | the two units' entries plus the gap functions' |
| `.rodata` | `0x800E77C8-0x800E7800` | unowned (`"graphic.c"` and the `"sNp_InitRenderMode: invalid TV format"` message) |
| `.sdata` | `0x803CBAD0-0x803CBAD8` | unowned (read by `initRenderMode` only) |
| `.sdata2` | `0x803CCED0-0x803CCEE0` | unowned |

Evidence:

- **The binary names the unit.** `lbl_800E77C8` is the string `"graphic.c"`,
  read by `initRenderMode`, directly followed by its panic message.
- **One `.sdata2` pool** (`0x803CCED0` the int-to-float magic double,
  `0x803CCED8` `0.0f`, `0x803CCEDC` `1.0f`) is read by `someGFXRenderingFn`,
  `fn_800A7E00`, `fn_800A7F10` and `initRenderMode`, so the unowned functions
  between the two units belong to it. The pool ends 8-aligned where `mcard.c`'s
  `"mcard.c"` string starts (`0x803CCEE0`).
- **Not included:** `fn_800A7AD8` reads `0x803CCEC8` (its own `0.0f`, a different
  pool, with `.data 0x8010F460`), so the unit starts at `someGFXRenderingFn`.
  `fn_800A7BAC` (before) and `fn_800A84C4` (after) read only the shared `.bss`
  object `0x803C7420` and carry no constants; they were left unowned.

The unit is compiled with `-cpp_exceptions on` (what `File_0x800a7c08` used; the
stub `initRenderMode` is flag-independent). Two `NonMatching` units became one; no
score changed. Linked DOL units 260 -> 260.

### `Unknown/dvdsys.c` (`0x800A6900-0x800A750C`, core only)

| section | range | was |
|---|---|---|
| `.text` | `0x800A6900-0x800A750C` | `File_0x800a6900` (`manageFileReadingProcess`), gaps `fn_800A6C80`, `fn_800A6D10`, `fn_800A6E24`, `fn_800A6F94`, `File_0x800a70dc` (`ARAMTransfer`) |
| `extab` / `extabindex` | `0x80006618-0x80006648` / `0x80008484-0x800084CC` | the two units' entries plus the gap functions' |
| `.rodata` | `0x800E7730-0x800E77C8` | unowned (`lbl_800E7730`, 0x98 bytes) |

Evidence:

- **The binary names the unit.** `lbl_800E7730` is one string pool holding
  `"Decode Error Retry : EntryNo%d %x Err:%d"`, `"dvdsys.c"` and the two Shift-JIS
  ARAM address messages. Both `manageFileReadingProcess` and `ARAMTransfer`
  read the pool, so one unit owns it.
- **Shared `.bss`:** both functions and all four gap functions between them use
  `lbl_803C6CF8` (0x708 bytes; unowned like the other big `.bss` objects).

Not included (suggestive only): `File_0x800a7544`, `7568`, `75ec` and `7670`
(`Matching`) also touch `lbl_803C6CF8`, but share no pool with the core, so
they stay separate units, as does the one-function gap `fn_800A750C`. The merge
costs no `Matching` unit. Compile flag `-cpp_exceptions on` was taken from the
former units' extab (both have entries; both were stubs). Linked DOL units
260 -> 260. The 19 files that include the old headers now include
`Unknown/dvdsys.h`.

### `Unknown/movie.c` (`0x800AD070-0x800B0724`)

The widest range the evidence supports; `makeLookAtMatrix` (`File_0x800b0724`,
`Matching`) starts the next unit and `File_0x800acf14` (`0x800ACF14-0x800AD070`,
98%) the previous one, so no `Matching` unit is absorbed.

| section | range | was |
|---|---|---|
| `.text` | `0x800AD070-0x800B0724` | `File_0x800adf60` (`YUV2RGB`), `File_0x800ae298` (`YUV2RGB_`), `File_0x800aeb18` (`MovStreamThread`), `File_0x800aed34` (`MovDecodeThread`) and 32 unowned functions (`fn_800AD070` ... `fn_800B05E4`) |
| `extab` / `extabindex` | `0x80006808-0x800068E8` / `0x8000876C-0x800088BC` | entries of the functions that have one (28 of 36) |
| `.rodata` | `0x800E7B50-0x800E7CB0` | unowned: the two `"YUV->RGB Conv ... Addr"` strings and the 0x118-byte `lbl_800E7B98` |
| `.data` | `0x801101C0-0x801112F0` | unowned: `lbl_801101C0` (0x100), `lbl_801102C0` (0x1000), `lbl_801112C0`, `lbl_801112E0` |
| `.sdata` | `0x803CBAD8-0x803CBB10` | unowned: nine small tables (`yuv2rgbConverters`, `lbl_803CBAD8`...`lbl_803CBB00`) |
| `.sbss` | `0x803CC170-0x803CC1B0` | unowned: the movie state (`lbl_803CC170`...`lbl_803CC1AC`) |
| `.sdata2` | `0x803CCEE8-0x803CCF08` | unowned: the YUV constants and the `"movie.c"` string |

Evidence:

- **The binary names the unit.** `"movie.c"` (`.sdata2 0x803CCF00`) is read by
  `fn_800AE8B8`, `MovStreamThread` and `MovDecodeThread`, i.e. by gap and `Unknown` code
  alike.
- **One error-string pool.** The two YUV strings at `0x800E7B50`/`0x800E7B74`
  are shared by `YUV2RGB`, `YUV2RGB_` and `MovStreamThread`; `lbl_800E7B98` is
  read by `fn_800AE8B8` and `MovDecodeThread`. The three objects end exactly at
  `sound.c`'s `.rodata` (`0x800E7CB0`) and start where `mcard.c`'s ends (`0x800E7B50`).
- **`.data` in reverse code order**: `lbl_801112E0` (`fn_800AD070`), `lbl_801112C0`
  (`fn_800ADD70`), `lbl_801102C0` (`YUV2RGB_`), `lbl_801101C0` (`fn_800AE5B8`),
  contiguous from `mcard.c`'s last jump table to `sound.c`'s `.data` (`0x801112F0`).
- **`.sbss 0x803CC170-0x803CC1B0`** is the shared movie state:
  `lbl_803CC170` is read by `fn_800AD070`, `fn_800AD780`, `fn_800AD830`,
  `MovDecodeThread`..., `lbl_803CC1AC` by `fn_800ADB04`, `fn_800AF9B4` and the last
  gap functions up to `fn_800B05E4`. It starts where `mcard.c`'s ends and the
  draw-list unit (`File_0x800b0a14`, `0x803CC1B0`) takes over.
- **`.sdata` / `.sdata2` pools** are contiguous between the neighbours:
  `.sdata` from `graphic.c`'s end (`0x803CBAD8`) to `sound.c` (`0x803CBB10`),
  `.sdata2` from `mcard.c`'s `"mcard.c"` (`0x803CCEE0`) to `makeLookAtMatrix`'s pool.

Compile flag `-cpp_exceptions on` was taken from the extab entries (the four
former units were stubs). Linked DOL units 260 -> 260.

### `Unknown/team_management_screens.c` (`0x80059458-0x80061B9C`)

The team-management / batting-order / fielding-alignment screens. The name is a
proposal (from `battingOrderProcessInputs`, `teamManagementGraphics_*` and
`challengeTeamManagementRelated`); the binary carries no file name.

| section | range | was |
|---|---|---|
| `.text` | `0x80059458-0x80061B9C` | `File_0x80059b38` (`starMissionRelated1`), `5a350` (`battingOrderProcessInputs`), `5af68` / `5bf40` (`teamManagementGraphics_fieldingAlignmentScreen` / `Info`), `5b298` / `5c2b0` (`..._battingOrderScreen` / `Info`), `5bb5c` (`challengeTeamManagementRelated`), `60184` (`teamManagementGraphics_steadyState`) and 13 unowned functions (`fn_80059458`, `fn_800596D4`, `fn_8005B760`, `fn_8005C5C4` ... `fn_8005FCA0`) |
| `extab` / `extabindex` | `0x800062D8-0x80006380` / `0x80007FA4-0x800080A0` | all 21 functions have an entry |
| `.data` | `0x80108AA8-0x80108B18` | unowned: `jumptable_80108AA8` (0x34) and `jumptable_80108ADC` (0x3C) |

Evidence:

- **Two jump tables, one unit.** `jumptable_80108AA8` (0x34 bytes) is read by the
  unowned `fn_80059458`; the very next object, `jumptable_80108ADC`, starts at the
  non-8-aligned `0x80108ADC` and is read by `teamManagementGraphics_steadyState`
  (`File_0x80060184`). Objects only start 4-aligned inside a unit, never at a
  unit's first `.data` byte (MWCC 8-aligns every unit's `.data`), so both
  functions lie in one unit and so does everything between them: the seven
  `Unknown/` units `59b38`-`5c2b0` and the gap functions around them. The
  table run ends where `lbl_80108B18` (`playPlayerSelectedSound`, `Matching`
  `File_0x800628d4`) begins.
- **Not in the unit:** the `.text` before `fn_80059458` (`fn_80058644`,
  `fn_80058B20`, `fn_80058E0C`) and `File_0x80057c08` (`Matching`) have no
  evidence tying them in, and `File_0x80061b9c` (`0x80061B9C`, next) starts the
  following unit.

The task description gave the range as ending at `0x80060184`; since
`jumptable_80108ADC` belongs to `File_0x80060184`, that whole function
(`0x1A18` bytes) is part of the unit and the end is `0x80061B9C`. No `Matching`
unit is absorbed; all eight former units were `NonMatching` stubs. The unit
uses `-cpp_exceptions on` (all 21 functions have extab entries). Linked DOL
units 260 -> 260.

### The text engine is one unit: `text/text.c` (`0x8000F150-0x80010F2C`)

`File_0x8000f48c`, `text_channel`, `text_width`, `text_block`, `text_alloc`,
`sprite_draw` and `text_draw` were cut as separate units, each starting at its
first named function; the five unowned functions in front of them (`fn_8000F150`,
`fn_8000F3E8`, `fn_8000F4B8`, `fn_8000F534`, `fn_8000F8F4`) have no `.data`
of their own to go by. The linker evidence says they are one translation unit
(`text_draw_conditional` and `text_init` are not part of it, see below).

| section | range | was |
|---|---|---|
| `.text` | `0x8000F150-0x80010F2C` | the seven units and the five gap functions |
| `extab` / `extabindex` | `0x800056D8-0x80005720` / `0x80006DA4-0x80006E10` | the entries of the units plus the gap functions' |
| `.data` | `0x800EE6A0-0x800EE800` | `text_draw.c` had `0x800EE6D4-0x800EE800`; `jumptable_800EE6A0` (0x34 bytes, `fn_8000F3E8`) was unowned |
| `.sdata` | `0x803CB760-0x803CB790` | unowned (`lbl_803CB760`, `lbl_803CB780`/`784`/`788`, read by `fn_8000F3E8` and `fn_8000F150` only) |
| `.sbss` | `0x803CBBE8-0x803CBBF0` | unowned (`lbl_803CBBE8`) |
| `.sdata2` | `0x803CC490-0x803CC4B8` | unowned (seven literals) |

Evidence:

- **One `.sdata2` pool.** `fn_8000F150` reads `0x803CC490-0x803CC4A0` (`0.0f`,
  the constants `448.0f`, `640.0f`, `2.0f`, and the int-to-float magic double at
  `0x803CC4A0`) and `drawTransformedSprite` reads `0x803CC490` (`0.0f`),
  `0x803CC4A0` (the same double), `0x803CC4A8` (`1.0f`) and `0x803CC4B0` (the
  unsigned magic double). Each value appears once, so the gap function and the
  sprite function were compiled in the same unit. The pool ends at
  `0x803CC4B8`, where the next pool starts with `0.0f` again (`fn_800116DC`), and
  begins after a pool (`0x803CC458-0x803CC490`, `updateHUDRelatedUI` and its
  neighbours) that already holds `0.0f` (`0x803CC47C`): a boundary on each side.
- **Jump tables.** `jumptable_800EE6A0` (`fn_8000F3E8`) is directly followed by
  `jumptable_800EE6D4` (`DrawText`). The second starts at a 4-aligned, non-8-aligned
  address, which no unit's first `.data` byte can be, so the old `text_draw.c`
  `.data` start was impossible: `fn_8000F3E8` and `DrawText` are one unit and
  so is everything in between.
- **`.sbss`.** `lbl_803CBBE8` (the texture-header pointer) is written by
  `somethingSetTexturePointer` and read by `fn_8000F150`.

Left out on purpose: `text_draw_conditional` (`DrawTextOnCondition`) and
`text_init` (`initTextRendering`) are `Matching`, share no pool with the engine and
only touch `screenTextArray`; `fn_80011000`/`fn_80011140` next to them likewise.

Cost: `File_0x8000f48c`, `text_channel`, `text_block` and `text_alloc` were
`Matching`, so linked DOL units 260 -> 256 (the merged unit is `NonMatching`: `calculateTextBlockWidth`
93.3%, `drawTransformedSprite` 99.4%, `DrawText` 88.2%, five gap functions have no C).
Every function that had C keeps exactly its old score, including the nine at 100%.

Source notes: sources are in address order (the unit's literal pool is in ascending order).
The units differed in flags: `text_block.c` was built without `-cpp_exceptions on` and
the other six with it; the merged unit uses `-cpp_exceptions on`, and the six
`text_block` functions, which are frameless leaves, still compile to the same bytes (no
extab entries, 100%). `text_width.c` and `text_draw.c` declared `lbl_800E8F60` with different types
(`u8[][4]` and `FontMetricsTables`); the merged file uses the struct, and
`calculateTextBlockWidth` reads `lbl_800E8F60.altWidths[(u16)glyph][style]`, which
generates the same code. `somethingSetTexturePointer` no longer includes
`C3/skinning/SKNAsm.h`, which redeclared `LCStoreBlocks` against `OSCache.h` in the merged
translation unit and was not needed. The seven headers became `include/text/text.h`
(37 files include it).

## Main DOL: units merged on shared literal pools (2026-11-20)

A union-find over every main-DOL function's `@sda21`/`@ha`/`@l` references to
`.sdata2` and `.rodata` symbols (functions joined when they read the same
address) gave sixteen groups that touch unsplit (`auto_*`) code. MWCC pools a
TU's float literals once, in first-use order, and the linker never merges two
TUs' pools, so two functions that read the same anonymous literal were compiled
together. Each shared symbol below was checked to be an anonymous literal (an
`lbl_` float/double, a magic int-to-float double, or a `__FILE__`/message string
read by `OSPanic`-style calls) rather than a named table, and each pool was
checked for repeated values: a repeated `0.0f` or `1.0f` means a second pool, so
the pool boundaries are where a value comes back. The other sections were then
checked for TU order (each unit's `.rodata`/`.data`/`.sdata`/`.sbss`/`.bss` must
sit between its neighbours' and start 8-aligned) and for jump tables that start
4-aligned (never a unit's first `.data` byte).

As in the 2026-10-14 pass, gap functions keep no C: a merged unit is
`NonMatching` unless all its parts were `Matching`, and links from the original
asm. Merged sources keep their functions in address order. Unless noted, every
function that had C keeps its score.

### `Unknown/File_0x8000a0ac.c` (`0x8000A0AC-0x8000B9C8`)

| section | range | was |
|---|---|---|
| `.text` | `0x8000A0AC-0x8000B9C8` | `File_0x8000a1e8` (`interpolatePointsBezier_Vec2s`) and the unowned `fn_8000A0AC`, `fn_8000A3EC`, `fn_8000AF1C` |
| `extab` / `extabindex` | `0x80005640-0x80005660` / `0x80006CC0-0x80006CF0` | the four functions' entries |
| `.sdata2` | `0x803CC420-0x803CC458` | unowned |

- **One pool.** The int-to-float magic double at `0x803CC420` is read by all four
  functions; `fn_8000A3EC` and `fn_8000AF1C` also share `1.0f`, `0.0f`, `1/1024`,
  `4096.0f` and the unsigned magic double. The pool (`magic, 1, 0, 1/1024, 4096,
  2pi, umagic, 360, 0.5, pi/2, pi/180`) holds no value twice.
- **Boundaries.** The pool before it (`0x803CC400-0x803CC420`,
  `File_0x80009e94`'s `interpolatePointsUnknown`/`BezierInterpolate`) already
  holds `1.0f` (`0x803CC418`), and the next one starts with `1.0f` again
  (`0x803CC458`), so `File_0x80009e94` is its own TU and the unit ends with the
  pool. `fn_8000B9C8` (a frameless pointer-fixup leaf, no constants, no extab,
  called from `fn_80035750` and `diskReadRelated`) is left unowned.

The file is renamed to its new start address (`File_0x8000a1e8.c/.h` ->
`File_0x8000a0ac.c/.h`). Units 1030 -> 1028 in the report.

### `Unknown/File_0x8000ba3c.c` (`0x8000BA3C-0x8000F150`)

| section | range | was |
|---|---|---|
| `.text` | `0x8000BA3C-0x8000F150` | `File_0x8000ba3c` (`updateMenuOrBackgroundUI`), `c194` (`updateHUDRelatedUI`), `d164` (`triggerDefaultHUDAction`), `d838` (`handleUIAction`, `Matching`), `e900` (`SetSpriteRect`), `ef1c` (`AddVec2iToQuad`) and nine unowned functions (`fn_8000CC4C`, `fn_8000CEF0`, `fn_8000D8A4`, `fn_8000DC9C`, `fn_8000E030`, `fn_8000E2D4`, `fn_8000E764`, `fn_8000E7BC`, `fn_8000EC0C`) |
| `extab` / `extabindex` | `0x80005660-0x800056D8` / `0x80006CF0-0x80006DA4` | all 15 functions have an entry |
| `.rodata` | `0x800E65D0-0x800E6600` | unowned (`lbl_800E65D0`, a 0x30-byte matrix read by `updateHUDRelatedUI`) |
| `.sbss` | `0x803CBBD8-0x803CBBDC` | unowned (`lbl_803CBBD8`, read by `updateHUDRelatedUI`, `triggerDefaultHUDAction`, `SetSpriteRect`, `fn_8000EC0C` only) |
| `.sdata2` | `0x803CC458-0x803CC490` | unowned |

- **One pool, read across the whole range.** `0x803CC458-0x803CC490` holds
  `1, magic, umagic, 1280, 1/1280, -1, 0, 256, 128, 2pi/65536` once each.
  `IntToDouble` (`0x803CC460`) is the pool's int-to-float double that someone
  named; it is read only by functions of this range. Sharers:
  `updateMenuOrBackgroundUI`, `updateHUDRelatedUI`, `triggerDefaultHUDAction`,
  `fn_8000D8A4`...`fn_8000E7BC`, `SetSpriteRect`, `fn_8000EC0C` and
  `AddVec2iToQuad` (the last function before `text.c`).
- **The functions in between** (`fn_8000CC4C`, `fn_8000CEF0`, `handleUIAction`,
  `fn_8000E764`) read no constants; they sit between pool users, so the
  contiguous unit includes them. `handleUIAction` was `Matching` and stays 100%.
- **Order.** `.rodata 0x800E65D0` sits between `handleLoadingProcess`'s strings
  and the next unit's `identityMtx`; `.sbss 0x803CBBD8` precedes `text.c`'s
  `0x803CBBE8`; the pool runs from the previous unit's pool to `text.c`'s
  (`0x803CC490`). `.bss lbl_80366188` (the UI sprite buffer) is shared with
  `File_0x80009e94` and later code and is not claimed.

Source notes: the six files declared the sprite buffer `lbl_80366188` as
`u8[]`, `HUDSprite` and `SpriteRectBuf`; the merged file declares `u8[]` and
casts where a struct view is used. `fn_8000A0AC`/`fn_8000A3EC` had two
prototypes (`Vec*` / `f32*` context); the merged one takes `void*`.
`triggerDefaultHUDAction` called `DrawSprite_TexObj` with two arguments through
a private prototype while `sprt.h` declares three; the call now goes through a
cast function pointer, which emits the same `bl`. `updateHUDRelatedUI` rose
39.68% -> 41.52% (the struct accesses through the cast compile closer to the
target); nothing dropped. The six headers became `Unknown/File_0x8000ba3c.h`.
One `Matching` unit (`File_0x8000d838`) is absorbed. Units 1028 -> 1015.

### `Unknown/File_0x80024d2c.c` (`0x80024D2C-0x80026134`)

| section | range | was |
|---|---|---|
| `.text` | `0x80024D2C-0x80026134` | the unowned `getHandTrackFlags`, `fn_80024DB0`, `fn_80024FA4`, then `File_0x80025c58` (`ACTActorRelated`, `Matching`) and `File_0x80025ddc` (`adjustInternalPointers`, `actorRelated`, `actRelated`, `fn_80026130`) |
| `extab` / `extabindex` | `0x80005BA0-0x80005BC0` / `0x800074D0-0x80007500` | the four functions that have an entry (`File_0x80025ddc`'s are frameless) |
| `.sdata` | `0x803CB7F0-0x803CB7F8` | unowned (read by `actorRelated`/`actRelated` only) |
| `.sbss` | `0x803CBC68-0x803CBC70` | unowned (`fn_80024FA4`) |
| `.sdata2` | `0x803CC5A8-0x803CC5D8` | unowned |

- **One pool.** `0x803CC5A8-0x803CC5D8` (`umagic, 0, 1, 100, 2^24, 65536, magic,
  0.5`) holds each value once. `0.0f` (`0x803CC5B0`) is read by `fn_80024DB0`,
  `fn_80024FA4`, `actorRelated` and `actRelated`; the unsigned magic double by
  the three gap functions. `sub.c`'s pool ends at `0x803CC5A8` (it already has
  `0.0f`/`1.0f`), and `fn_80026134`'s pool starts with `0.0f` at `0x803CC5D8`,
  so `fn_80026134` (with `.rodata 0x800E6768`) is the next TU and stays unowned.
- `ACTActorRelated` reads no constants but sits between pool users.
- **Order.** `.sdata`/`.sbss` sit between `sub.c`/objinit's objects and
  `particle_effects.c`'s (`0x803CB7F8`, `0x803CBC70`).

`File_0x80025ddc` was built without `-cpp_exceptions on`; its functions have no
extab entries and compile to the same code with it. The two headers became
`Unknown/File_0x80024d2c.h`. One `Matching` unit is absorbed.

### `Unknown/spani_default.c` (`0x80034BCC-0x80036C88`)

| section | range | was |
|---|---|---|
| `.text` | `0x80034BCC-0x80036C88` | `File_0x80034cec` (`removeGraphicsElementFromScene`, `Matching`), `34e20` (`addGraphicsElementToScene`), `34f50` (`allocateGraphicsSlot`), `35168` (`maybeProcessUIUpdates`), `35838` (`diskReadRelated`), `35ca4` (`unregisterObjectByID`, `Matching`), `363d8` (`load_Icon`, `Matching`), `3649c` (`setIndicatorSlotState`) and 18 unowned functions (`fn_80034BCC`, `fn_800356B8`, `fn_80035750`, `fn_80035A00` ... `fn_80036A3C`) |
| `extab` / `extabindex` | `0x80005D98-0x80005E40` / `0x800077C4-0x800078C0` | every function's entry (the leaves have none) |
| `.rodata` | `0x800E68A8-0x800E6910` | unowned: `" SabNo = %d not to add"`, then `"spani_default.c"` + `"gasSpani No Empty"` and `"It is a number not registered."` |
| `.data` | `0x800F78E0-0x800F79A0` | unowned (`lbl_800F78E0`, `maybeProcessUIUpdates`) |
| `.bss` | `0x801F8640-0x8023DD80` | unowned (`lbl_801F8640`, `lbl_801F8680`, `lbl_801F86C0`, `textureContainerTags`) |
| `.sdata` | `0x803CB810-0x803CB818` | unowned (`diskReadRelated`, `uiDrawLoopEnd`) |
| `.sbss` | `0x803CBC90-0x803CBCA0` | unowned (`diskReadState` ... `lbl_803CBC9C`) |
| `.sdata2` | `0x803CC6E8-0x803CC720` | unowned |

- **The binary names the unit.** `lbl_800E68C4` is `"spani_default.c"`
  followed by `"gasSpani No Empty \n"`, read by `fn_80035F20`, `fn_8003664C` and
  `fn_80036824`, all inside the pool span below.
- **One pool.** `0x803CC6E8-0x803CC720` (`0, 256.5, 511, 2, 1, magic, -0.175,
  0.175, 0.25, -0.25, 512, 1280`) has no repeated value; its readers run from
  `allocateGraphicsSlot` to `fn_80036A3C`. The next pool repeats `0.0f`
  (`0x803CC728`).
- **`.rodata` and `.bss` in TU order.** `lbl_800E68A8` is read by `fn_80035750`
  and `diskReadRelated`, the `spani_default.c` strings by the later functions;
  the run starts where `particle_effects.c`'s ends. `.bss` follows
  `particle_effects.c`'s minigame buffer (`0x801F8040`); `textureContainerTags`
  is read only by functions of this range.
- **The head, `0x80034BCC-0x80034F50`.** `fn_80034BCC` is called only by
  `maybeProcessUIUpdates`, and its one data object, `.sbss lbl_803CBC9C`, sits
  in this unit's `.sbss` run after `diskReadState` and `uiDrawLoopStart`, where
  an earlier TU's object cannot be. So it is in the unit and so are the two
  graphics-element functions between it and `allocateGraphicsSlot`. The unit
  starts where `particle_effects.c` ends.
- **Not included:** `fn_80036C88` (no data; called from the game and menus REL
  entry points) is left unowned.

The eight headers are kept; `Unknown/spani_default.h` includes them (merging
them made 85 includers see each other's prototypes, which clash with local
redeclarations in a dozen REL files). Three `Matching` units are absorbed.

### `Unknown/File_0x80037054.c` (`0x80037054-0x80039AA8`)

Fifteen unowned functions and no source: a new `NonMatching` unit with an empty
source file.

| section | range |
|---|---|
| `.text` | `0x80037054-0x80039AA8` (`fn_80037054` ... `fn_80039A4C`) |
| `extab` / `extabindex` | `0x80005E48-0x80005EE8` / `0x800078CC-0x800079BC` |
| `.data` | `0x800F79A0-0x800F7A40` (`lbl_800F79A0`, `lbl_800F79B8`) |
| `.sdata` | `0x803CB818-0x803CB828` |
| `.sbss` | `0x803CBCA0-0x803CBCA8` |
| `.sdata2` | `0x803CC720-0x803CC7A0` |

- **One pool, no repeats** (`1/60, 100000, 0, 0.5, magic, -9.80665, 1, 0.25,
  12, 9.80665, 10, 20, 2, 60, -1, 0.8, ...`). `0.0f` (`0x803CC728`) alone is read
  by eleven functions from `fn_80037054` to `fn_80039310`.
- **`fn_80039A4C` closes the unit:** it reads both `.data` objects (with
  `fn_80038F08`/`fn_80038EC4`), `.sdata 0x803CB818/0x803CB820` and `.sbss
  0x803CBCA1` (with `fn_80039310`).
- **Order.** Every section starts exactly where `spani_default.c`'s ends
  (`.data 0x800F79A0`, `.sdata 0x803CB818`, `.sbss 0x803CBCA0`, `.sdata2
  0x803CC720`) and ends where `File_0x80039aa8`'s `UITexture` user
  `lbl_800F7A40`, and the next pool (`0x803CC7A0`, `fn_80039AC0`), begin.

Units 1015 -> 970 in the report after these three.

### `Unknown/File_0x8003ae64.c` (`0x8003AE64-0x80040FE0`)

The memory-card / save screen TU. No literal pool: the evidence is a shared
string plus the `.data`, `.bss` and `.sbss` layout.

| section | range | was |
|---|---|---|
| `.text` | `0x8003AE64-0x80040FE0` | `File_0x8003c00c` (`sceneDrawingLogic`) and the unowned `fn_8003AE64`, `fn_8003AE70`, `fn_8003AECC`, `fn_8003B5B0`, `fn_8003BB90`, `fn_8003BF54`, `fn_8003E8D8`, `startMemoryCardCheck`, `fn_8003F2B8`, `fn_8004053C`, `fn_80040C14` |
| `extab` / `extabindex` | `0x80005F60-0x80005FB0` / `0x80007A70-0x80007AE8` | the entries from `fn_8003AECC` to `fn_80040C14` |
| `.rodata` | `0x800E6910-0x800E6920` | unowned (`"MarioBaseball"`) |
| `.data` | `0x800F7B00-0x800FB3F8` | unowned: `lbl_800F7B00` (0x32A0) and 25 jump tables |
| `.bss` | `0x802D4AC0-0x802E4B00` | unowned (`lbl_802D4AC0`, `lbl_802D4AE0`, `lbl_802D4B00`) |
| `.sdata` | `0x803CB830-0x803CB838` | unowned (`sceneDrawingLogic`) |
| `.sbss` | `0x803CBCB8-0x803CBCC0` | unowned (`fn_8003AE64` + `sceneDrawingLogic`, `sceneDrawingLogic`) |

- **One string literal.** `"MarioBaseball"` (`.rodata 0x800E6910`, the card file
  name) is read by `fn_8003B5B0`, `sceneDrawingLogic`, `fn_8003F2B8`,
  `fn_8004053C` and `fn_80040C14`. It sits between `spani_default.c`'s strings
  and `orderchange.c`'s `"orderchange.c"` (`0x800E6920`).
- **One `.data` run.** `lbl_800F7B00` (read by `fn_8003B5B0` and
  `sceneDrawingLogic`) is followed directly by the jump tables of `fn_8003AECC`,
  `fn_8003B5B0`, `fn_8003BB90`, `sceneDrawingLogic`, `fn_8003E8D8`,
  `fn_8003F2B8`, `fn_8004053C` and `fn_80040C14`, in that order, up to
  `orderchange.c`'s first table at `0x800FB3F8`. Several start 4-aligned
  (`0x800FAF14` after `fn_8003BB90`'s, `0x800FB164` after `fn_8003E8D8`'s). The
  object comes first and the tables follow in function order, as in the other
  units (an earlier TU's tables cannot come after a later TU's object), so
  `fn_8003AECC` is in the unit.
- **`.bss` and `.sbss` place the head.** `.bss` runs `lbl_802D4AC0`
  (`sceneDrawingLogic`), `lbl_802D4AE0` (`fn_8003AECC` and nine others) and
  `lbl_802D4B00` (`fn_8003AE70` and six others), directly after
  `File_0x8003a688`'s `lbl_802D3D80`. In `.sbss`, `File_0x8003a688`'s
  `fn_8003AC90` shares `lbl_803CBCB4` with `fn_8003AE54`/`fn_8003AE5C`, and the
  next object, `lbl_803CBCB8`, is shared by `fn_8003AE64` and
  `sceneDrawingLogic`. So the unit starts at `fn_8003AE64`; `fn_8003AE54` and
  `fn_8003AE5C` stay unowned (they belong with `File_0x8003a688`, which this pass
  does not change).
- **Not included:** `0x80040FE0-0x8004207C` (`fn_80040FE0` ... `fn_800415A8`)
  has no object of its own in these runs; `lbl_803CBCC0` (`fn_8004157C`,
  `fn_800415A0`) directly follows the unit's `.sbss`, which fits either side.

The file is renamed `File_0x8003c00c` -> `File_0x8003ae64` (`.c` and `.h`).

### `Unknown/File_0x8005268c.c` (`0x8005268C-0x800531D0`)

The camera / scissor / projection TU.

| section | range | was |
|---|---|---|
| `.text` | `0x8005268C-0x800531D0` | `File_0x8005268c` (`returnsCurrentMode`), `52694` (`setScissorAndProjection`), `52734` (`returnFloatFromModeIndex`, `fn_80052768_getCamera`, `setScissorMode`, `returnScissorMode`), all `Matching`; `527c4` (`isWorldPosOnScreen`), `52968` (`graphics_relatedToVsScreen`), `52f98` (`possiblyTransitionBlackScreen`), and the unowned `fn_800528AC`, `fn_800528B4`, `fn_800528C0`, `fn_80052D70` |
| `extab` / `extabindex` | `0x800061F8-0x80006228` / `0x80007E54-0x80007E9C` | |
| `.sdata` | `0x803CB880-0x803CB888` | unowned (`scissorMode`) |
| `.sbss` | `0x803CBD10-0x803CBD18` | unowned (`lbl_803CBD10`, `currentMode`) |
| `.sdata2` | `0x803CC870-0x803CC8D0` | unowned |

- **One pool, no repeats** (`0, 0.25, -1, 1, 320, 224, -0.175, 0.175, -0.25, 512,
  -240, 240, -320, -512, 1280, 0.375, -0.125, -160, 160, 0.125, -0.375, -5, -4,
  -pi`), read by `isWorldPosOnScreen`, `fn_800528C0`,
  `graphics_relatedToVsScreen`, `fn_80052D70` and `possiblyTransitionBlackScreen`.
  `fn_800528AC`/`fn_800528B4` share `.sbss lbl_803CBD10` with the last three.
- **The head.** `.sbss` holds `lbl_803CBD10` (the pool functions) and then
  `currentMode` (read only by `returnsCurrentMode` and `setScissorAndProjection`).
  If `0x8005268C-0x800527C4` were its own earlier TU, `currentMode` would come
  before `lbl_803CBD10`; so the three small `Matching` units are the head of this
  unit. `scissorMode` (`.sdata`) is read by both halves.
- `.bss` (`lbl_803C60BC`, `cameras`) lies in the block after the SDK's `.bss`;
  claiming it creates a link-order cycle, so it is left unowned (the 2026-10-14
  units leave their late `.bss` objects alone for the same reason).

The headers are kept; the merged source includes them. `File_0x80052694.h`
declares `currentMode` as `int`, so the duplicate `extern u32` went.
Three `Matching` units are absorbed (all nine functions keep their scores).

### Four new units for gap-only TUs

| unit | `.text` | other sections | evidence |
|---|---|---|---|
| `Unknown/File_0x800521b0.c` | `0x800521B0-0x80052634` (`fn_800521B0`, `fn_8005240C`) | `extab 0x800061E0-0x800061F0`, `extabindex 0x80007E30-0x80007E48`, `.data 0x800FEB08-0x800FEB30`, `.sdata2 0x803CC860-0x803CC870` | both read `255.0f` and the magic double at `0x803CC860/0x803CC868` and the `.data` object `lbl_800FEB08` |
| `Unknown/File_0x80063028.c` | `0x80063028-0x80063718` (`fn_80063028`, `fn_800633AC`) | `extab 0x80006418-0x80006428`, `extabindex 0x80008184-0x8000819C`, `.sdata2 0x803CC8D8-0x803CC8F0` | both read the whole pool (`1, -1, pi, 0, pi/180`); `fn_80062C60`'s `0.5f` (`0x803CC8D0`) is before it and `fn_800639BC`'s `0.0f` (`0x803CC8F0`) after it |
| `Unknown/File_0x80069b68.c` | `0x80069B68-0x8006C0D0` (`fn_80069B68` ... `fn_8006C088`, 16 functions) | `extab 0x80006510-0x80006580`, `extabindex 0x800082F8-0x800083A0`, `.data 0x80109250-0x801093E8`, `.sdata 0x803CB8D8-0x803CB8E0`, `.sbss 0x803CBD34-0x803CBD38`, `.sdata2 0x803CC8F8-0x803CC938` | one pool with no repeats (`0, 608, 448, -1, 1, 255, umagic, 220, -23, -100, 100, 640, -0.5, 30`) read from `fn_80069BDC` to `fn_8006BB60`; `.data lbl_80109250` is read by `fn_80069BDC`...`fn_8006A824`, `fn_8006BE00` and `fn_8006C088`, and the run continues with `BootSequenceFiles` (`fn_8006AF9C`), `titleScreenTexturesFileDescriptor` and `lbl_80109378` (`fn_80069B68`), `lbl_801092F8` (`fn_8006B668`) and ends with `fn_8006B78C`'s jump table |
| `Unknown/File_0x8006c100.c` | `0x8006C100-0x8006C398` (`fn_8006C100`, `fn_8006C13C`, `fn_8006C268`, `fn_8006C2B4`) | `extab 0x80006588-0x80006598`, `extabindex 0x800083AC-0x800083C4`, `.data 0x801093E8-0x80109420`, `.sdata 0x803CB8E0-0x803CB8F0`, `.sdata2 0x803CC938-0x803CC940` | `fn_8006C13C`/`fn_8006C2B4` share the magic double `0x803CC938`, `.data lbl_801093E8`/`lbl_80109410` and both `.sdata` objects; `fn_8006C100`'s `lbl_80109400` sits between their two `.data` objects. The run starts 8-aligned after the previous unit's jump table, and ends at `challenge_progress.c` (`0x80109420`) |

Left out at the edges: `endDemo` (`File_0x80069a98`, `Matching`) shares `.sbss
lbl_803CBD30` with `fn_80069B68`, which fits both "same TU" and "global of the
next TU", so it and the unowned `fn_80069AD4`/`fn_80069B08` stay as they are;
`fn_8006C0D0` (between the two new units, no data), `fn_80052634` and
`fn_8006C398` are unowned.

### `Unknown/model.c` (`0x80011468-0x8001FE00`)

The character model / animation / stadium-load TU, 58 KB and 102 functions: the
27 `Unknown/File_0x800127f8` ... `File_0x8001fc4c` units and 75 unowned
functions between them. The binary names it.

| section | range | was |
|---|---|---|
| `.text` | `0x80011468-0x8001FE00` | `File_0x800127f8` (`LoadModel`), `13680`, `14d4c`, `14e50`, `14f40`, `1594c`, `18024`, `18270`, `1a6b0`, `1b2d0`, `1b728`, `1b80c`, `1b918`, `1c588`, `1c67c`, `1c920`, `1cbd4`, `1ce74`, `1d0d0`, `1d110`, `1d148`, `1d180`, `1e460`, `1f228`, `1f4c0`, `1f5e8`, `1fc4c` (`initShortsHandleCompressedDiskReads`) and the gaps `fn_80011468` ... `fn_8001FDD4` |
| `extab` / `extabindex` | `0x80005740-0x800059D0` / `0x80006E40-0x80007218` | |
| `.rodata` | `0x800E6600-0x800E6698` | unowned: `identityMtx`, `lbl_800E6630` (`fn_80011640`), `LoadModel`'s two "Character ... Data None" messages |
| `.data` | `0x800EE800-0x800EEFD0` | unowned: `lbl_800EE800`, `BallModelFiles`, `MinigameCommonFiles`, ..., `lbl_800EEB18`, then 14 jump tables |
| `.sdata` | `0x803CB790-0x803CB7C8` | unowned |
| `.sbss` | `0x803CBBF0-0x803CBC40` | unowned (`lbl_803CBBF0` ... `highLevelSimulationFlag`) |
| `.sdata2` | `0x803CC4B8-0x803CC530` | unowned |

- **The binary names the unit.** The pool holds `"model.c"` (`0x803CC4C8`,
  read by `LoadModel`'s panic call) between its floats.
- **One pool, no repeats:** `0, umagic, "model.c", 0.5f, 0.5, 3.0, 0.0, 1, 2,
  -30, -0.5, 30, 0.125, magic, 180/pi, 1280, -0.175, 0.175, 0.25, -0.25, 512`
  (float and double zero/half are different literals). `0.0f` alone is read
  from `fn_800116DC` to `fn_8001F8A4`; `1.0f`, `0.5f` and the three doubles tie
  `fn_80017814`, `fn_800196D8`, `challengeMapRelated`, `fn_8001B35C` and
  `challengeMapMaybe` together. `text.c`'s pool ends right before it; the next
  pool (`fn_8001FE00`, `0x803CC530`) repeats `0.0f` and `1.0f`.
- **One `.data` run.** It starts at `text.c`'s end with `lbl_800EE800`, which
  `initShortsHandleCompressedDiskReads` (the last unit, `File_0x8001fc4c`)
  addresses as the base of its unit's `.data` (its source already defined the
  objects ahead of its tables for that reason). The file-scope objects
  (`BallModelFiles` for `fn_800188C0`, `MinigameCommonFiles` for `fn_80019C00`,
  `lbl_800EEAAC` for `LoadModel` and five others) come first, then the jump
  tables of `fn_80011468`, `fn_80012B90`, `fn_80017814`, ... `fn_8001E784` and
  `initShortsHandleCompressedDiskReads` in function order, eight of them
  starting 4-aligned. The last one ends at `CommonUIFiles_main` (`0x800EEFD0`,
  next unit).
- **`.sdata`, `.sbss`, `.rodata`** are contiguous runs read only by functions of
  this range (`lbl_803CBC18` by `fn_80011570` and `fn_8001E0D8`, the far ends),
  each between `text.c`'s objects and the next unit's.
- **Edges.** The unit starts at `fn_80011468`, the first function whose data
  (its jump table) is in the run. `fn_80011000` ... `fn_80011358` (after
  `text_init.c`) use only `screenTextArray` and the common `hugeAnimStruct`, so
  they stay unowned. `fn_8001FDD4` (no data) is included: it is called only by
  `fn_8001758C` and `fn_80017D28` and sits before the next pool's first user.
  `.sbss2 0x803CD308-0x803CD30E` (read only by `fn_80011CA8`) is left unowned.

Source notes. The 27 sources were concatenated in address order; their headers
are kept and included. They declared nine globals with clashing types, above
all `hugeAnimStruct` (17 different views). The merged file declares each global
once; a former unit whose view differs gets a typedef and a `#define NAME
(*(View*)&NAME)` for its stretch, `#undef`'d at its end. Two kinds of change
were needed to keep codegen: the cast changes MWCC's operand order for indexed
struct members, so the declared `HugeAnimStruct` carries the fields the
`Matching` users index directly (`actorTable`, `modelEntries`, `objects`) and
their element casts move to the loaded value; and a view of an `.sdata` scalar
through a cast changes addressing, so identical declarations are never viewed.
`stadiumSetupRelated`'s light types are declared once at the top.
`initShortsHandleCompressedDiskReads`'s `.data` objects go first in the file
(before any jump table). Duplicate typedefs were dropped, differing ones renamed
with the former unit's address, and each former unit's macros are `#undef`'d at
its end. `getAnimRelatedCoordinates` now takes `VecXYZ*`, the type
`UnknownHomes_Game.h` gives it. 14 `Matching` units are absorbed; every function
keeps its score and `LoadModel` rises 76.43% -> 80.22%. Units 941 -> 848.

### Groups not applied

- **`0x8004AE18-0x8004B1B8` and `0x8004C19C-0x8004C5F8`.** Each pair shares a
  pool (`0x803CC80C-0x803CC818`, `0x803CC840-0x803CC850`), but the region
  `0x8004AC00-0x8004C9FC` contradicts itself: the pools of `fn_8004AE18`,
  `fn_8004B284`, `fn_8004BEB0`, `fn_8004C19C` and `fn_8004C5F8` each repeat
  `0.0f` and the magic double (four TUs by the pool rule), while the `.data` run
  `0x800FB798-0x800FC0FC` interleaves those same functions' objects
  (`fn_8004B284` x12, `fn_8004BEB0`, `fn_8004C510`, `fn_8004B208`,
  `fn_8004ACF4`, `fn_8004AFA8`, `fn_8004AE18`, `stadiumCollisionRelated`'s jump
  table, `fn_8004B284` again), which only one TU produces. Until that is
  resolved no boundary here can be trusted, so neither pair became a unit.

Units 970 -> 941 after this batch; `Matching` units 313 -> 310.

## Main DOL: library tails and leftover gaps (2026-11-21)

A follow-up to the 2026-11-20 pass, aimed at the ~117 KB of main-DOL code still
in `auto_*` units. Evidence per group is given as in the earlier sections:
shared anonymous literals, section order (a TU's objects start where the
previous unit's end and are read only by its code), embedded file names, and
known SDK layouts. No function gained C; every check below is "build `ok`,
report has every function of `rep_c19` at the same or a higher score".

### SDK `.init` code: `Dolphin/os/__start.c` and `TRK_MINNOW_DOLPHIN/__exception.s`

Both sources were already in `src/` but not split, so `.init`
`0x80003100-0x80003400` and `0x800034AC-0x800053E0` were the units
`auto_00_80003100_init` and `auto_00_800034AC_init`.

| unit | sections | evidence |
|---|---|---|
| `Dolphin/os/__start.c` (`Matching`) | `.init 0x80003100-0x80003400` (`__check_pad3`, `__set_debug_bba`, `__get_debug_bba`, `__start`, `__init_registers`, `__init_data`), `.sbss 0x803CBE10-0x803CBE18` (`Debug_BBA`) | the SDK file, in the SDK's `os` order: `OSTime.c` -> `__start.c` -> `__ppc_eabi_init.cpp`; `Debug_BBA` sits in the 8-byte `.sbss` slot between `OSThread.c` and `db.c` that `OSTime.c`/`__ppc_eabi_init.cpp` (no `.sbss`) leave. |
| `Dolphin/TRK_MINNOW_DOLPHIN/__exception.s` (`Matching`) | `.init 0x800034AC-0x800053E0` (`gTRKInterruptVectorTable` .. `gTRKInterruptVectorTableEnd`) | the TRK vector table, between `mem_TRK.c`'s `.init` (`TRK_memset`/`TRK_memcpy`) and `dolphin_trk.c`'s (`__TRK_reset`); split directly before `dolphin_trk.c`. |

Both match byte for byte as written. `__exception.s` gained three `.set`
labels (`lbl_80003800`, `lbl_80004400`, `lbl_80004800`, at table offsets
`0x354`/`0xF54`/`0x1354`) because dtk resolves pointer-shaped words in
`auto_08_800E8F08_data` to them. Seven functions rise to 100%.

### The HVQM4 movie decoder: `Unknown/File_0x800dfdd4.c`

`.text 0x800DFDD4-0x800E6330` (33 functions, `auto_03_800DFDD4_text`) is the
last code in the DOL, after `Musyx/chorus_fx.c`. It calls nothing outside
itself and is called only from `Unknown/movie.c` (`MovStreamThread`,
`fn_800AD500`, `fn_800AF1A8`, `fn_800AF5FC`, ...), whose strings check an
`"HVQM4 1.3"` header, so it is Hudson's HVQM4 decoder. One unit:

- **Section order.** Its data is the tail of every data section, starting
  exactly where the last MusyX unit's ends: `.rodata lbl_800E82D8` (read by
  `fn_800E423C`) at `Musyx/hardware.c`'s end `0x800E82D8`; `.data
  lbl_80117FE0`/`lbl_80118020` (read by `fn_800DFDD4`) at `chorus_fx.c`'s end
  `0x80117FE0`; `.sbss lbl_803CC3F8`/`lbl_803CC3FC` at `hw_dolphin.c`'s end
  `0x803CC3F8`. No other code reads any of them.
- **Shared statics.** The two `.sbss` words are read by `fn_800E0904` and by
  `fn_800E4FF4`/`fn_800E5940` at the other end of the range; `.bss
  lbl_80328DA0` by `fn_800E0488`, `fn_800E156C`, `fn_800E2580` and
  `fn_800E3860`.
- No extab, no `.sdata2`. The `.bss` objects (`lbl_80328DA0`,
  `lbl_80328FA0`) sit in the block after the SDK `.bss` and stay unowned, as in
  the earlier passes.

The binary gives no file name, so the unit is address-named (empty source,
links from the original asm). It may be more than one file of the HVQM4
library; nothing here can split it further.

### `0x80039AA8-0x8003AE64`: two units on data order

The stretch between `File_0x80037054.c` and `File_0x8003ae64.c` was three small
`Matching` units (`File_0x80039aa8`: `GetUITexture`/`returnTexture`;
`File_0x8003a538`: `fn_8003A538`/`fn_8003A540`/`updateFunctionPtr`;
`File_0x8003a688`) and twelve unowned functions. Its objects, in section
order:

| section | objects (reader) |
|---|---|
| `.data` | `0x800F7A40` (`returnTexture`, `fn_80039AC0`, `fn_80039FF8`, `fn_8003A090`, `fn_8003A144`, `fn_8003A1D0`), `0x800F7A60` (`fn_8003A1D0`), `0x800F7AC0` (`GXTexObjRelated`), `0x800F7AE0` (`fn_8003A37C`), then `File_0x8003ae64` at `0x800F7B00` |
| `.sdata` | `0x803CB828` (`fn_8003A848`), `0x803CB82C` (`fn_8003A550`), then `File_0x8003ae64` |
| `.sbss` | `0x803CBCA8` (`updateFunctionPtr`, `fn_8003A8A0`), `0x803CBCAC` (`GXTexObjRelated`), `0x803CBCB0` (`fn_8003A538`/`fn_8003A540`), `0x803CBCB4` (`fn_8003AC90`, `fn_8003AE54`, `fn_8003AE5C`), then `File_0x8003ae64` |
| `.sdata2` | `0x803CC7A0-0x803CC7D0` (`fn_80039AC0`: `640, 1280, 0.5, 0.125, 448, 255, 0, -1`, both magic doubles), `0x803CC7D0` (`fn_8003A2EC`: `30, 1`), `0x803CC7D8-0x803CC7E8` (`fn_8003A688`/`fn_8003A6B0`/`GXTexObjRelated`: `0.5`, magic) |

- **Two pools.** `0.5f` and the magic double come back at `0x803CC7D8`, so the
  `File_0x8003a688` functions are not in `fn_80039AC0`'s TU; `0.5f`
  (`0x803CC72C`) also separates `fn_80039AC0`'s pool from
  `File_0x80037054`'s.
- **The second TU starts at `fn_8003A37C`.** An object read by an earlier TU
  cannot come after a later TU's object, yet `fn_8003A538`'s `.sbss` word
  follows `GXTexObjRelated`'s, `fn_8003A550`'s `.sdata` byte follows
  `fn_8003A848`'s, and `fn_8003A37C`'s `.data` object follows
  `GXTexObjRelated`'s. So `fn_8003A37C` ... `fn_8003AE5C` are one TU (with
  `updateFunctionPtr`, whose word is the TU's first `.sbss` object, and
  `fn_8003AE54`/`fn_8003AE5C`, which share `fn_8003AC90`'s). `fn_8003A37C`
  and `fn_8003A4C8` reach `UITexture` through `GetUITexture()`, while
  `fn_80039FF8` ... `fn_8003A2EC` read it directly.
- **The first TU** runs from `GetUITexture` to `fn_8003A2EC`: `returnTexture`
  returns the `.data` object the gap functions read, and `fn_8003A2EC`'s
  `30, 1` cannot be in the next pool's TU (it reads `UITexture` and
  `lbl_803C5090` directly, like `fn_8003A090`).

| unit | sections | was |
|---|---|---|
| `Unknown/File_0x80039aa8.c` (now `NonMatching`) | `.text 0x80039AA8-0x8003A37C`, `extab 0x80005EE8-0x80005F20`, `extabindex 0x800079BC-0x80007A10`, `.data 0x800F7A40-0x800F7AC0`, `.sdata2 0x803CC7A0-0x803CC7D8` | `File_0x80039aa8` (`Matching`) + `fn_80039AC0` ... `fn_8003A2EC` |
| `Unknown/File_0x8003a37c.c` (`NonMatching`) | `.text 0x8003A37C-0x8003AE64`, `extab 0x80005F20-0x80005F60`, `extabindex 0x80007A10-0x80007A70`, `.data 0x800F7AC0-0x800F7B00`, `.sdata 0x803CB828-0x803CB830`, `.sbss 0x803CBCA8-0x803CBCB8`, `.sdata2 0x803CC7D8-0x803CC7E8` | `File_0x8003a538` + `File_0x8003a688` (both `Matching`) + `fn_8003A37C`, `fn_8003A4C8`, `fn_8003A550`, `fn_8003AE54`, `fn_8003AE5C` |

The merged source is the two old files in address order (their headers are
kept and included; a duplicate `extern` dropped). Three `Matching` units are
absorbed; every function keeps its score.

### `Unknown/File_0x800a1a70.c` (`0x800A1A70-0x800A2B5C`)

Eleven functions between `Dolphin/OdemuExi2/DebuggerDriver.c` and
`Dolphin/exi/EXIBios.c` (`auto_03_800A1A70_text`). They call nothing outside
the range and are called only from `Unknown/sprt.c` (`DrawSprite`,
`fn_800B1EBC`, `fn_800B2854`); all but `fn_800A1A70` read `.sbss
lbl_803CC0F0`, and eight call the helper `fn_800A1B80`. Their objects fill
exactly the unowned slots between the two SDK units in every section:
`.data 0x8010F158-0x8010F160` (`fn_800A1F40`), `.sdata 0x803CBA98-0x803CBAC0`
(five 8-byte objects of `fn_800A1F40`, `fn_800A2194`, `fn_800A2294`,
`fn_800A237C`), `.sbss 0x803CC0F0-0x803CC0F8`, `.sdata2
0x803CCEC0-0x803CCEC8` (`32.0f`, `16.0f`, `fn_800A1F40`; the next float,
`0x803CCEC8`, is `fn_800A7AD8`'s). One gap-only unit, empty source.

### Data for existing units

- `Unknown/File_0x8004207c.c` gets `.sdata2 0x803CC7E8-0x803CC7F8` (`100.0f`
  and the magic double, read only by its `capApplicationFunction`, between
  `File_0x8003a37c`'s pool and `File_0x8004ac00`'s).
- `.sbss2`: `0x803CD300-0x803CD308` (read only by `main`) goes to
  `main`'s unit (now `File_0x80008e00.c`, below) and `0x803CD308-0x803CD30E` (read only by
  `fn_80011CA8`) to `Unknown/model.c`, in their `.text` order.

### A rule used below: a unit's data starts 8-aligned

Of the 300-odd `.data`/`.rodata`/`.sdata`/`.sbss`/`.sdata2` ranges in
`splits.txt` before this batch, all but three start on an 8-byte boundary,
and 4-byte holes sit at the boundaries (`0x803CC8D4`, `0x80108D2C`). A run of
objects that has no 8-aligned break (an object starting at `4 mod 8`, or a
byte object) therefore cannot be split between two TUs. The three exceptions
are each wrong or doubtful: `File_0x8004ad54`'s `.data` (`0x800FBEF4`, in the
contradictory `0x8004AC00` region), `Musyx/hardware.c`'s `.sdata2`
(`0x803CD27C`) and `File_0x80069b68`'s `.sbss` (fixed below).

### `0x80062764-0x80064534`: three units

| unit | sections | was | evidence |
|---|---|---|---|
| `Unknown/File_0x80062764.c` (`NonMatching`) | `.text 0x80062764-0x80062948`, `extab 0x80006398-0x800063D8`, `extabindex 0x800080C4-0x80008124`, `.data 0x80108B18-0x80108B90` | `File_0x800628d4` (`playPlayerSelectedSound`, `Matching`) + `fn_80062764`, `fn_80062794`, `pushDictionaryAudioGroup`, `fn_800627F8`, `fn_8006282C`, `fn_8006285C`, `fn_80062890` | the `.data` run after `team_management_screens.c`'s (`0x80108B18`) is `lbl_80108B18` (`playPlayerSelectedSound`), `lbl_80108B3C` (`fn_80062890`), `lbl_80108B84` (`fn_80062764`): the reverse of their readers' order, with no 8-aligned break before `0x80108B90`, so one TU holds all three readers and the sound helpers between them |
| `Unknown/File_0x80062be4.c` (`NonMatching`) | `.text 0x80062BE4-0x80062F38`, `extab 0x800063E8-0x80006410`, `extabindex 0x8000813C-0x80008178`, `.data 0x80108B90-0x80108D30`, `.sdata2 0x803CC8D0-0x803CC8D8` | `fn_80062BE4`, `fn_80062C24`, `fn_80062C60`, `fn_80062D94`, `fn_80062E6C`, `fn_80062ED4` | the rest of that `.data` run, up to the 4-byte hole at `0x80108D2C`, is read only by this code: `lbl_80108B90` (`fn_80062BE4`, `fn_80062C60`, `fn_80062D94`), `lbl_80108BE0` (`fn_80062C60`, `fn_80062D94`), `lbl_80108BF0` (`fn_80062E6C`) and `fn_80062ED4`'s jump table last; `fn_80062C60`'s `0.5f` is the 8-byte pool between `File_0x8005268c`'s and `File_0x80063028`'s. `fn_80062F38`/`fn_80063010` (no data) stay unowned: they may open `File_0x80063028`'s TU |
| `Unknown/File_0x800639bc.c` (`NonMatching`) | `.text 0x800639BC-0x80064534`, `extab 0x80006448-0x80006460`, `extabindex 0x800081CC-0x800081F0`, `.data 0x80108D30-0x80108DB8`, `.sdata 0x803CB898-0x803CB8D0`, `.sdata2 0x803CC8F0-0x803CC8F8` | `fn_800639BC` + `File_0x80064344` (`handleBallRollInWater`) + `File_0x80064430` (`spawnDustPuff`, `Matching`) | the pool `0x803CC8F0` (`0.0f`, `fn_800639BC`), `0x803CC8F4` (`3.0f`, `handleBallRollInWater`) is followed by `File_0x80069b68`'s at `0x803CC8F8`; `0x803CC8F4` cannot start a TU, so both readers share one; `.data lbl_80108D48` is read by `handleBallRollInWater` and `spawnDustPuff`, after `fn_800639BC`'s `lbl_80108D30` and before `mb_subfunc.c`'s `0x80108DB8`; the `.sdata` run `0x803CB898-0x803CB8D0` is read only by `fn_800639BC` and ends at `mb_subfunc.c`'s |

`File_0x80063958` (`maybeUpdateFielderTerrainStatus`) and `fn_800638CC` share
only the `.bss` object `lbl_802E4BC0` with `fn_800639BC`, so they stay out;
`fn_80064534` (globals only) stays unowned. Two `Matching` units are absorbed.

### `File_0x80069b68.c`'s `.sbss` starts at `0x803CBD30`

The 2026-11-20 unit started its `.sbss` at `0x803CBD34` (`lbl_803CBD34`,
`fn_8006C088`), which no TU can. `lbl_803CBD30` (read by `fn_80069B68` and by
`endDemo`) is the unit's first `.sbss` word. `endDemo`, `fn_80069AD4` and
`fn_80069B08` still stay out: `endDemo` may read the word as an `extern`.

`mb_subfunc.c`'s `.sbss` (`0x803CBD18-0x803CBD30`) and `.bss`
(`0x802E4CE8-0x802E5200`) are read only by its code too, but it is
`Matching` and declares them `extern`; claiming them needs the definitions in
C first (tried: the link fails with the objects undefined).

### `Unknown/File_0x80008e00.c`: `main`'s TU (`0x80008E00-0x800096DC`)

The first `.text` TU. The `.sbss` section opens with a packed run that only
this code reads:

| object | readers |
|---|---|
| `0x803CBBA0`, `0x803CBBA4` (byte) | `fn_80008E08`, `fn_80009028`, `fn_800090B4`, `main` |
| `0x803CBBA8`, `0x803CBBAC` | `main`; `fn_80008E08`, `PostRetraceCallback`, `fn_8000900C`, `main` |
| `0x803CBBB0`, `0x803CBBB4` (byte) | `fn_80008E08`, `main` |
| `0x803CBBB8`, `0x803CBBBC` | `fn_80008E00`, `main`; `fn_80009018`, `main` |
| `0x803CBBC0` (byte, `drawStadiumRelated`), `0x803CBBC1`, `0x803CBBC2`, `0x803CBBC4`, `0x803CBBCC` (`menuControlVariables`) | many; `fn_80008E08`, `main`; `fn_80008E08`, `PostRetraceCallback`, `main`; none; many |

Each 8-byte slot pairs a `main`-only (or `main` + helper) word with a helper
word, and the byte objects cannot start a TU, so `main` and the helpers before
it share the run (`fn_80009144` calls `fn_80009094` and `fn_800090B4`, `main`
calls `fn_80008E08` and `PostRetraceCallback`). `.bss lbl_801181A0` (read only
by `main`) is the first `.bss` object; `.sbss2 0x803CD300` (read only by
`main`, claimed for `File_0x80009180` earlier today) moves with it.
`s32DataId`/`s32ProgId` (`0x803CBBD0`, read by `PrepFilesToBeLoaded` and
`handleLoadingProcess`) start the next TU and stay unowned.

| section | range |
|---|---|
| `.text` | `0x80008E00-0x800096DC` (`File_0x80008fd0` (`PostRetraceCallback`, `Matching`) + `File_0x80009180` (`main`) + `fn_80008E00`, `fn_80008E08`, `fn_8000900C`, `fn_80009018`, `fn_80009028`, `fn_80009094`, `fn_800090B4`, `fn_80009144`) |
| `extab` / `extabindex` | `0x80005600-0x80005630` / `0x80006C60-0x80006CA8` |
| `.bss` / `.sbss` / `.sbss2` | `0x801181A0-0x80118220` / `0x803CBBA0-0x803CBBD0` / `0x803CD300-0x803CD308` |

Source: the two files in address order; `File_0x80008fd0.c`'s
`Dolphin/OS/OSReset.h` include clashed with `main`'s own `extern`s for
`OSGetResetButtonState`/`OSResetSystem`, so it was dropped and
`PostRetraceCallback` uses `main`'s `extern s32 OSGetResetButtonState(void)`
(same code, still 100%).

### `Unknown/File_0x800a8518.c`: the jukebox (`0x800A8518-0x800A94C4`)

`LoadFile` (`File_0x800a8cbc`, `Matching`) and the 18 unowned functions around
it (`fn_800A8518`, `jukeboxCmd`, ..., `jukeboxStop`, ..., `fn_800A94A8`) all
work the DVD-stream queue in `.sbss 0x803CC128-0x803CC158`, which sits exactly
between `SISamplingRate.c`'s `.sbss` and `mcard.c`'s and is read by nothing
else: `jukeboxQueueHead`, `lbl_803CC14C` and `lbl_803CC154` by `LoadFile`,
`fn_800A8AB8`, `fn_800A8B78`, `fn_800A8E30`, `jukeboxStop`, `fn_800A90E4`,
...; the bytes `0x803CC134`/`0x803CC135` (which cannot start a TU) by
`fn_800A8864`, `fn_800A8878`, `fn_800A88D8`, `jukeboxStop` and `fn_800A9424`.
The unit takes `extab 0x800066C8-0x80006750`, `extabindex
0x8000858C-0x80008658` and that `.sbss`. Left out: `fn_800A84C4` (reads only
`lbl_803C7420`, like `graphic.c` and `fn_800A7BAC`), and the PAD functions
`fn_800A94C4` ... `fn_800A97EC` (`AtBat_ButtonInput1`, `.data
lbl_80110080`, which `PrepFilesToBeLoaded` also reads) before
`initInputDevices`. One `Matching` unit is absorbed.

### `Unknown/File_0x8004c9fc.c`: the character-select TU (`0x8004C9FC-0x80052188`)

The `.data` run `0x800FCA60-0x800FEB08` and the `.sdata` run
`0x803CB870-0x803CB880` are read only by the character-select code between
`fn_8004C5F8` and `File_0x800521b0`, and their small objects come in the
*reverse* of their readers' `.text` order:

| `.data` object | reader |
|---|---|
| `0x800FCA60` (0x1400) | `fn_8004D0F0`, `fn_8004E2EC`, `captainSelect_processCursorMovement_getCharID`, `fn_8004F964`, `charGrid_moveCursor`, `fn_80051D00` |
| `0x800FDE60`, `0x800FDE84` (`characterIconsOnCSS`) | `fn_8005138C`; `fn_8004FD64` ... `fn_8005138C` |
| `0x800FE5C8`, `0x800FE5D4` (`mapCaptainCursorPositionToCharID`), `0x800FE924` | `fn_8004F10C`; `storeCursorLocOrCharIDs`, `add_or_RemoveCharToATeam`, `fn_8004EEF4`; `fn_8004DB90` |
| `0x800FE930` (`challengeCaptainCharIDArray`), `0x800FE93C` (`variantCharIDs`), `0x800FEAAC` | `fn_8004D460` ... `fn_8004D990`; `challengeCaptainSelect_returnsCharID`; `fn_8004CCC0` |

`.sdata`: `0x803CB870` (`fn_8004E2EC`) before `0x803CB874`/`0x803CB878`
(`fn_8004C9FC`, `fn_8004CA08`, `exitMenu`).

Within each row the later objects start at `4 mod 8` (`0x800FDE84`,
`0x800FE5D4`, `0x800FE924`, `0x800FE93C`, `0x800FEAAC`, `0x803CB874`), so
each row is one TU's data, and the rows run backwards against `.text`
(`fn_8005138C` > `fn_8004F10C` > `fn_8004DB90` > `fn_8004CCC0`;
`fn_8004E2EC` > `fn_8004C9FC`). Separate TUs would put them in ascending
order, so `fn_8004C9FC` ... `fn_8005138C` is one TU. Its ends:
`fn_8004C5F8`'s jump table (`0x800FCA28`) and a 4-byte hole come right before
`0x800FCA60`, so the previous TU ends at `0x8004C9FC`; `File_0x800521b0`'s
`.data` follows at `0x800FEB08`. `fn_80051D00` (reads `0x800FCA60`) is the
last reader; `fn_80052188` (reads only `charSelectStruct`) stays unowned.

| section | range |
|---|---|
| `.text` | `0x8004C9FC-0x80052188`: `File_0x8004ca6c` (`exitMenu`), `8004cc18`, `8004d57c`, `8004d93c`, `8004e504`, `8004e5b4`, `8004e62c`, `8004ee84`, `80050138`, `800506e8`, `80050760`, `80050fe8` and 18 unowned functions (`fn_8004C9FC`, `fn_8004CA08`, `fn_8004CA14`, `fn_8004CA48`, `fn_8004CCC0`, `fn_8004D0F0`, `fn_8004D460`, `fn_8004D4F0`, `fn_8004DB90`, `fn_8004E2EC`, `fn_8004F10C`, `fn_8004F964`, `fn_8004FD64`, `fn_8004FDA0`, `fn_8004FDE8`, `fn_80050F78`, `fn_8005138C`, `fn_80051D00`) |
| `extab` / `extabindex` | `0x80006150-0x800061E0` / `0x80007D58-0x80007E30` |
| `.data` / `.sdata` | `0x800FCA60-0x800FEB08` / `0x803CB870-0x803CB880` |

Source: the twelve files concatenated in address order (headers kept and
included, duplicate `extern`s dropped). `File_0x80050fe8.c` declared
`charSelectStruct` as `s8[0x94]` against the `CharSelectState` of
`File_0x8004e5b4.h`; its stretch now reads it through `#define
charSelectStruct (*(s8(*)[0x94])&charSelectStruct)`, `#undef`'d at the end.
Five of the units were built without `-cpp_exceptions on`; the merged unit
uses it. Five `Matching` units are absorbed; every function keeps its score.

## The options / settings gap in the menus REL (2026-10-21)

`.text` `0x194BC-0x1A4C8` (13 functions, `auto_00_000194BC_text`) sat between
`captain_select/captain_model_load.c` (`.rodata 0x568-0x5F0`) and `rep_0730.c` (`.rodata 0x730-`).
Between them are four header-only units, `rep_05F0`, `rep_0640`, `rep_0690` and `rep_06E0` (one 0x50
`repHeaderData` table each, no `.text`), so by the method above the gap holds up to four TUs. The gap
references no `.rodata` of its own (no float constants), so the test cannot place a boundary by
constants; the boundaries come from the call graph, the `.data` ownership and the inlining pattern.

Result: **three code units and one code-less table**, paired in order.

| header-only unit | `.text` | `.data` | became |
|---|---|---|---|
| `rep_05F0` | `0x194BC-0x19F2C` | `0x2798-0x2B78` (debug-menu table, labels, jump table) | `options_screen.c` |
| `rep_0640` | `0x19F2C-0x1A1B4` | none | `settings_reset.c` |
| `rep_0690` | `0x1A1B4-0x1A4C8` | `0x2B78-0x2E40` | `challenge_file_select.c` |
| `rep_06E0` | none | none | stays a header-only unit (the code-less TU) |

Evidence, in the order it carries weight:

- **`0x194BC-0x19F2C` is one TU.** `fn_2_197AC` and `optionsScreen` contain, expanded inline, the bodies of
  `fn_2_194E8`, `fn_2_19520`, `fn_2_19554` and `fn_2_19778`; none of those four, nor `fn_2_194BC` or the empty
  `fn_2_195D8`, is called or referenced by name anywhere in the REL. They are the out-of-line copies of inlined
  helpers (the "inlined and also kept standalone" case in `matching_notes.md`), and a helper can only be inlined
  where its definition is visible, so the callers and the helpers are one TU. The unit's only `.data` is the
  jump table of `optionsScreen`'s switch (`jumptable_2_data_2B5C`, targets `optionsScreen+0x38..0x1E0`), which is
  the last object before the next debug-menu table.
- **`settingValuesTo0` and `challengeFileSelect` are different TUs from the options screen.** The 0x2C4-byte
  debug-menu text table at `.data 0x2B78` follows the jump table directly, and `challengeFileSelect` reads
  `lbl_2_data_2E3C`, the first object after that table (a zero `GXColor`, the `GXSetCopyClear` colour). So the
  options jump table ends one TU's `.data` and `challengeFileSelect` starts the next one's. `.data 0x2E40` onward
  is read by units far later in the REL (`0x4C9E0`, `0x6826C`), so the new unit takes `0x2B78-0x2E40` only; the
  rest stays unowned.
- **`settingValuesTo0` is a TU of its own (weak).** It is the only function in the gap that is called from other
  units (`main_menu.c`, `teamselect.c`, `text_0323C.c`, always as a plain `bl`), uses no `.data` and shares no
  inlined helper with either neighbour. Merging it into `challenge_file_select.c` would leave two code-less tables
  instead of one; there is no evidence either way beyond that count.
- **`challengeFileSelect`, `fn_2_1A2AC`, `fn_2_1A420`** share `changeScene(3, 6)`, `lbl_8037169C`,
  `lbl_2_bss_1A82xx` (the challenge screen's working blocks) and the file-select state; kept together.

### Settled later the same day: the options screen is its own TU

The first pass left open whether `0x194BC-0x19F2C` was the tail of `captain_model_load.c`. It is not:

- **dtk had merged three objects into `lbl_2_data_2794` (0x3C8).** Its first 4 bytes (`00 01 02 00`) are
  the table `fn_2_16A98` indexes. At `0x2798`, which is 8-aligned, a byte-identical copy of the 0x2C4-byte
  debug-menu table begins (the same bytes as the copy at `0x1E28`). Then come 0x100 bytes of
  options labels, `char[8][0x20]` = "MUSIC", "SOUND", "VIBRATION", "MONAURAL", "STEREO", "SURROUND", "ON",
  "OFF": exactly the options screen's three items and their values. The jump table at `0x2B5C` follows.
- **A debug-menu table always opens a TU's `.data` in this block.** That holds at `0x180` (main_menu), `0x720`
  (character select), `0x1000` (stadium select), `0x15C8` (teamselect), `0x19E8` (captain_select), `0x1E28`
  (captain_model_load), `0x2798` (options) and `0x2B78` (challenge file select). Every one of these addresses is
  8-aligned, and MWCC gives every object's `.data` 8-byte alignment (checked on our objects). Where the end of
  the previous TU is not 8-aligned, there is a pad (`0x1E24`, `0x19E4`). Code never reads the table's
  own contents. Its address appears only as the pooled base for the statics after it (`main_menu` at
  `lbl_2_data_180 + 0x2C4..`, `captain_select` at `lbl_2_data_19E8 + 0x418..`). So it is most likely a static from a
  header that each of these TUs includes, emitted whether or not it is used.
- So `.data 0x2798-0x2B78` is one TU: table, its own option labels, then its jump table. Its code is the options
  screen, and `captain_model_load.c`'s `.data` ends at `0x2798`. That settles the question with high confidence.
  The jump-table placement alone (4-aligned `0x2B5C`, directly after another unit's statics) was misleading:
  the "statics" before it were the options TU's own.
- The other three kinds of evidence asked for agree, but none of them would decide it alone. *Inlining:* nothing
  is inlined across `0x194BC`. The options code inlines only its own helpers (`fn_2_194E8`/`19520`/`19554`/`19778`).
  captain_model_load's uncalled `fn_2_16CE0`/`fn_2_18650`/`fn_2_16870` are inlined into its own functions, and its uncalled
  `fn_2_19224`/`fn_2_1937C` read its float pool, while the options code uses no `.rodata` at all. *Pooled bases:* neither side reads the other's `.data` or `.bss` (`lbl_2_bss_1033C` against
  `lbl_2_bss_100B8`/`1224`/`1228`/`122C`), and neither uses pooled offsets into the other. *Call graph:* no call
  crosses the boundary in either direction.
- **Changes:** `options_screen.c` `.data` became `0x2798-0x2B78`, and it defines the table and the labels (`lbl_2_data_2798`,
  `lbl_2_data_2A5C`). `captain_model_load.c` got `.data 0x1E28-0x2798`, defined in C. `lbl_2_data_20F8` (0x324) was
  also two objects: the two team model positions (`f32[2][3]`), then an unreferenced 0x30C-byte table of u16/u8
  indices and f32 scales (`lbl_2_data_2110`, kept as raw words). Both `.data` sections are 100%.

**Which table is code-less, and `settings_reset.c`.** Options keeps `rep_05F0`: it is the first TU after
captain_model_load (`0x568`-`0x5F0`, which closes with that unit's float pool), and the options TU is now confirmed.
Two code units remain, `settingValuesTo0` (`0x19F2C`) and the challenge file select (`0x1A1B4`), and three tables
(`0x640`, `0x690`, `0x6E0`). None of the three code units uses a `.rodata` constant, and a code-less TU leaves
nothing in `.text` or `.data`. So which table is the code-less one cannot be read from the binary.
`rep_06E0` stays header-only by convention (it is last), at low confidence. `settings_reset.c` stays its own TU
(weak, unchanged). It has no `.data`, inlines nothing and is inlined nowhere, and it is called with `bl` from
`challengeFileSelect`. In this REL, single-call functions of `0x19C` bytes and more stay out of line even
within one TU (`fn_2_195DC` and `fn_2_197AC` in `optionsScreen`), so that call does not show it is in another
TU. Folding it into `options_screen.c` or `challenge_file_select.c` would be equally consistent. In that case two
of the three tables would be code-less.

## The character-select / stadium boundary, and teamselect / captain_model_load (2026-10-21)

**`text_110B0.c` was two TUs.**

- `teamSelectScreenMain` (`0x110B0-0x112F4`) belongs to the character-select TU (`text_0323C.c`). The evidence is
  high. *(a)* Its jump table `0xFDC` is the last of that TU's `.data` run. That run is the debug-menu table at
  `0x720`, `MenuCommonTexFiles_text0323C`, `lbl_2_data_E14`/`E64`/`E88`, then the jump tables of `fn_2_3624`
  (`EAC`-`F20`), `fn_2_57F0` (`F44`-`FB8`) and `teamSelectScreenMain` (`FDC`), ending at `0x1000`. A new TU's
  debug-menu table starts at `0x1000`. *(b)* Its case 1 is instruction for instruction the body of `fn_2_86EC`, a css function
  that nothing calls. That function is the standalone copy of an inlined helper, so the two are in one TU. Written as
  a plain `fn_2_86EC()` call, MWCC inlines it and the function is 100%. *(c)* It shares the global `.bss`
  (`lbl_2_bss_F468`, `100B4`) with the css code. In our build, its five single-call callees
  (`cssTransitionToNewScreen_maybe`, `cssChangeScreens`, `cssSelectCPUDifficulty`,
  `characterSelectScreenControlable`, `cssUnloadScreen`) get inlined unless they carry `#pragma dont_inline`. The
  target keeps them out of line, as it does with other single-call css functions of that size (`fn_2_87A8`, 0x194,
  is `bl`'d from css code), so the pragma is scaffolding rather than evidence against the TU.
- **`stadium_select.c`** (`0x112F4-0x12238`) takes `.data 0x1000-0x15C8`: debug-menu table, a 0x28-byte table and a
  0x20-byte object, `cursorToStadIDMapping` (6 bytes), 16 stadium file descriptors, twelve stadium/scene names, and the
  jump table of `selectStadiumScreen`. It also takes `.rodata 0x3E8-0x438`, the former `rep_03E8`: it is the last
  table before teamselect's `0x438`, and the stadium code uses no constants, so only order places it (medium).
  `.data` and `.rodata` are 100%. `.text` is 98.66% (`stadiumSelectControls` 93.9, register colouring, see the
  checkpoint), so the unit is not flipped. It reads only global `.bss`.
- **The other tables in this stretch.** `rep_0318` belongs to the css TU (high). Its 0x30 bytes after the table are
  ten short strings, and the only pointers to them are in `lbl_2_data_E14`, inside the css TU's `.data`. That fits:
  the menu REL builds with `-str readonly`, so string literals go to `.rodata`. It is not yet merged into
  `text_0323C.c`, which would need that unit's whole `.data 0x720-0x1000` defined: `lbl_2_data_720` is read
  through a pooled base, so its layout would have to be reproduced exactly. `rep_0398` is unexplained. It is either
  code-less or the table of a second TU inside `0x323C-0x112F4` that has neither a debug-menu table nor a `switch`.

**`teamselect.c` owns `.data 0x15C8-0x19E4`** (high): the debug-menu table at the 8-aligned `0x15C8`, a 0x28-byte
table, the same 16 stadium file descriptors, then its jump table `0x19B4`, followed by the pad to captain_select's `0x19E8`.
It had only the jump table and scored 0%. It is now 95.44%; the rest is that table's targets in the unmatched
`captainSelectScreen_manager`.

**`.text 0x16870-0x16A98` is the head of `captain_model_load.c`** (high). `fn_2_16870` is uncalled. It is the
out-of-line copy of the block that `fn_2_188EC` runs `if (STATE[0x19])`, and it contains inlined copies of `fn_2_18650`
and `fn_2_16CE0`, both captain_model_load functions. Calling it from `fn_2_188EC` reproduces the target's inlining
(99.44 -> 99.68). The four leaf accessors after it (`captainSelect_getShowModelOnLoad`, `captainSelect_setShowModelOnLoad`, `captainSelect_isModelVisible`, `captainSelect_setModelVisible`, 5-9
instructions) are `bl`'d from `captain_select.c`, `teamselect.c` and `text_0323C.c`. By the leaf rule
(`-inline deferred` inlines such leaves within their own TU), that keeps them out of `captain_select`'s TU, so they
stay with `fn_2_16870`. All five are drafted: four at 100%, `fn_2_16870` at 99.51%.

**Left open.** `.text 0x13BA4-0x14574` is still unowned. It holds the captain-select debug menu: `fn_2_14220`, a
five-state dispatcher called only from `captain_select.c`, `fn_2_13D70`, and four uncalled item handlers that it
inlines (two toggle `superstarUnlocked` flags). They plausibly implement the items the debug table names ("STAR PLAYER
SET", "KOOPA STA FLAG SET", ...). No `.rodata` table is free for it (teamselect's `0x438-0x4B0` and captain_select's
`0x4B0-0x568` each hold one table and their own constants), so it is the tail of `teamselect.c` or the head of
`captain_select.c`. No inlining, data or leaf-call evidence picks between the two.
