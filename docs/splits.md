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

By rule 2, gap `0x20A60-0x20CEC` was folded into `batting/batter_ai.c`,
since it shares batter_ai's pooled constants at `.rodata` 0x930-0x93C.

Boundary fixes from the 2026-10-08 gap review (every function's local
`.rodata`/`.data`/`.bss` references were checked against its unit; only
`fn_3_C1930` disagreed):

- `0x1104A8-0x110634` (`minigameClearAIControlled`, `unusedBattingSomething`)
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
  `data_only/rep_3E00.c` with `.data 0x284E8-0x28508`.
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
`rep_21F8.c` (one 0x300-byte `lbl_3_data_17898`; the seven sub-symbols were
merged because `fn_3_C937C`'s codegen depends on the full size),
`0x2A448-0x2A4A8` -> `rep_4138.c`, `0x10AB0-0x111A8` (per-stadium tables) ->
`stadium_framework.c`, `0xF4A4-0xF4E0` -> `hud_gauges.c`, and `.bss
0x9FDC-0xA018` -> `pitcher_fire_effect.c`.

Four large shared tables have no code unit between their link-order
neighbours, so each is a data-only unit (like `match_flow_data.c`), named by
address: `data_only/data_1880.c` (AI and versus tables, after `camera.c`),
`data_428C.c` (field coordinates, hit and fielding constants, after
`match_loading.c`), `data_69C0.c` (batter/fielder hitboxes, runner constants,
after `ball_visuals.c`), `data_8D88.c` (HUD layouts, after `m_sound.c`).
All are 100%.

Left unowned on purpose: common `.bss` from `0xD714` (shared globals used by
almost every unit), the 4-byte alignment gaps, `0x228`
`FrameCountOfEntireGame` (no clear owner), `0x6804-0x6820` and `0x27EAC`.

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

Kept on purpose: `kinoko.c`, `m_sound.c` and `sta_c0/2/4/5/6.c` are original
filenames (their `OSPanic` `__FILE__` strings are in the binary).

TU-count check: the target REL holds exactly **92** `repHeaderData` tables,
and every unit with `.rodata` has exactly one. So `fielder.c` (214 KB),
`match_scene.c`, `versus_screens.c` and `star_missions.c` are each one
original TU, and the theme-based splits proposed for them were not made: the pause UI half of `match_scene.c`
(`0x978DC-0x993A8`), the home-run celebrations in `versus_screens.c`
(`0x23890-0x24598`), scout flags out of `star_missions.c` (from `0x163948`).
Thirteen code units have no table and no `.rodata` at all, and use no float
constants, so the test cannot place them: `at_bat_results`, `at_bat_setup`,
`character_loading`, `match_flow`, `match_loading`, `match_transitions`,
`scene_skip`, `pitcher_stamina`, `replay_state`, `result_stats`,
`run_scoring`, `stat_lookups`, `stat_tracking`. Each is either a TU that never
included the shared header or the tail of its link-order predecessor; all
were cut from unowned gaps.
`kinoko_startPulseGlow` is declared `(s8 charID, u8 alt)` in `star_dash.c` but defined
`(void* model, u8 alt)` in `kinoko.c`; the first argument is really a player ID.

Still open, as of 2026-10-08:

| header-only unit(s) | `.text` window | contents |
|---|---|---|
| `rep_CC8`, `rep_D18`, `rep_D68`, `rep_DB8` | `0x5985C` gap (2 fns) plus, by position, part of `fielding/fielder.c` | 4 TUs sit between fielder.c's rodata and match_loading's, so `fielder.c`'s 214 KB `.text` range probably spans several original TUs |

Where several header-only units share one window, split the window at
function boundaries so that each TU's functions stay contiguous; the call
graph and function names usually show where the themes change.

## Main DOL: the Challenge translation unit (2026-10-12)

Main-DOL code has no `repHeaderData` signature, so the boundaries below come
from how the linker lays the unit's data out (`.data` objects are 4-aligned
inside a unit but every unit's `.data` starts 8-aligned; MWCC emits functions
in source order and does not share literal pools between units).

`challenge/challenge_progress.c` replaces five `Unknown/` units:

| section | range | was |
|---|---|---|
| `.text` | `0x8006C48C-0x8006CEBC` | `File_0x8006c48c` (`0x8006C48C-0x8006C5CC`), unowned gap `0x8006C5CC-0x8006C7C4` (`fn_8006C5CC`, `fn_8006C6C4`, `fn_8006C79C`), `File_0x8006c7c4`, `File_0x8006c9d8`, `File_0x8006cbe4`, `File_0x8006cca4` |
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
- **Gap functions.** `fn_8006C5CC`, `fn_8006C6C4` and `fn_8006C79C` only read
  `g_Challenge` (they count characters whose recruitment byte
  is 1) and sit between two members of the unit, so they belong to it.

Left out on purpose: `fn_8006CEBC`/`fn_8006CF6C` (`0x8006CEBC-0x8006D024`,
menu-graphics load/unload pair; `fn_8006CF6C` is installed by `SetMenuNumber`
and reads `lbl_801075A8` from the menu `.data` block, so it is menu glue, not
Challenge logic), and `fn_8006C488` (empty function, no evidence either way).

The unit is `NonMatching` for now: `fn_8006C5CC` (87%) and `fn_8006C6C4`
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
| `C3/actor/actorAnim.c` | `0x800B4A44-0x800B4E9C` | `.sdata2 0x803CCF78-0x803CCF80` | its pool is `0.0f` (`0x803CCF78`) and `1.0f` (`0x803CCF7C`); `act.c` already pooled both at `0x803CCF58`/`0x803CCF5C`, and MWCC pools a literal once per unit, so the two pools belong to different units. First user of the second pool is `fn_800B4A44` (bone time), which starts the per-bone animation functions (`AnimateActorBones`, `setActorAnimFrame`, `ACTSetAnimation`) |

The boundary between `act.c` and `actorAnim.c` can sit anywhere in `0x800B4724-0x800B4A44`
(`renderingRelated`, `haveActLayoutPointToGeoHeader`, `LoadActorLayout`, `AdjustActorPointers` have no
constants of their own); it was put after `AdjustActorPointers`, i.e. as late as the pools allow, because
those four are layout/render code, not animation. The file names are the SDK's (`actor.c`/`actorAnim.c`
in `include/C3/actor.h`) except that the binary's own `__FILE__` string says `act.c`. The start at
`0x800B2AC8` is the first `Actor`-field accessor after the sprite unit's last data user
(`fn_800B2854`, `.sdata2 0x803CCF38`).

`actorAnim.c` links as `Matching` (it was the 99.7% `File_0x800b4908` minus `LoadActorLayout`, which
is 98% and went to `act.c`). `act.c` is `NonMatching`: it holds eleven functions that have no C yet
(`fn_800B2BA8`..`fn_800B2C10`, `fn_800B2C88`, `fn_800B2D5C`, `fn_800B2DD0`, `fn_800B313C`, `fn_800B3A78`,
`fn_800B3C04`, `fn_800B3F20`, `fn_800B4278`, `fn_800B4724`) and five stubs. Five previously `Matching`
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
