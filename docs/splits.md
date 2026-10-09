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
| `rep_1BC8` | `0xB3B70-0xB5E7C` | `practice/practice_menu.c` (owns the four jump tables at `.data 0x10A08-0x10A90`) |
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
`fn_3_1695A4` is declared `(s8 charID, u8 alt)` in `star_dash.c` but defined
`(void* model, u8 alt)` in `kinoko.c`; the first argument is really a player ID.

Still open, as of 2026-10-08:

| header-only unit(s) | `.text` window | contents |
|---|---|---|
| `rep_CC8`, `rep_D18`, `rep_D68`, `rep_DB8` | `0x5985C` gap (2 fns) plus, by position, part of `fielding/fielder.c` | 4 TUs sit between fielder.c's rodata and match_loading's, so `fielder.c`'s 214 KB `.text` range probably spans several original TUs |

Where several header-only units share one window, split the window at
function boundaries so that each TU's functions stay contiguous; the call
graph and function names usually show where the themes change.
