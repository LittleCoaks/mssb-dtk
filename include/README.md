# `include/` layout

What's in each folder here and why, so you know where to look when writing a mod.
Mirrors `src/`'s organization — see [`docs/file_map.md`](../docs/file_map.md) for the
full per-file writeup this is condensed from. This is also the tree
`SyncFromDecomp.py` mirrors into the ASM repo's `Include/`, so paths match 1:1
between the two.

## `game/` — the match REL (what most mods touch)

One header per `src/game/*.c` translation unit, sorted into these subfolders by
gameplay category. If a mod is about actual gameplay, it starts here.

| folder | covers |
|---|---|
| `ball/` | Ball physics — bounce/roll, air↔landed, fair/foul, hit classification, collision, trajectory. |
| `batting/` | Batter at-bat: swing/bunt, contact/hit-type calc, charge and star swings. |
| `pitching/` | Windup, release, curve, pickoffs, pitch selection AI. |
| `baserunning/` | Runner control, base rounding, slides, stats/error bookkeeping. |
| `fielding/` | Catch behavior (diving/running/jumping, bobbles, wall jumps), fielder AI targeting/throw decisions. |
| `camera/` | All in-match camera work: live-ball tracking, replays, pause-menu angles. |
| `animation/` | Central animation dispatch, scene effects/sprites, per-character special animations. |
| `hud/` | Scoreboard, star/score gauges, stadium HUD drawing, icon layer. |
| `math/` | Angle/vector helpers, general transform math. |
| `sound/` | Stadium emitters, ball SFX, at-bat/replay audio cues. |
| `match_setup/` | Not gameplay itself — roster construction, load/transition state, controller input, versus/championship screens. |
| `stadium/` | Per-stadium hazard/gimmick logic (one file per stadium) plus the shared stadium framework. |
| `minigame/` | Per-minigame logic (Star Dash, Chain Chomp Sprint, Bob-omb Derby, etc.) plus shared minigame effects. |
| `data_only/` | Units with no real code, just a shared trig-table constant. Nothing to look at here. |

`UnknownHomes_Game.h` is the catch-all for match-REL globals whose **type** is
known but whose owning file isn't — often the first place to check for game
state you want to read or modify.

Confidence varies per file (`docs/file_map.md` tags each `high`/`med`/`inferred`).
Files still under their original `rep_XXXX` name are `inferred` — the category
is trustworthy, the boundary/name is a guess.

## `menus/`, `unused_rel/` — the other two RELs

Stub headers only — these RELs aren't decompiled, just split into units with
real addresses. Useful for symbol/address lookups (menu screens, the unused
`challenge.rel`), not for reading actual logic.

## `static/`

`UnknownHomes_Static.h` — same idea as `UnknownHomes_Game.h` but for globals
that live in the main DOL rather than the match REL.

## Outside `game/` — the DOL (`main.dol`)

| folder | contents |
|---|---|
| `Dolphin/` | GameCube SDK headers (OS, GX, pad, DVD, card, audio interface, etc.) — the actual console API. |
| `musyx/` | MusyX audio engine (synth, sequencer, DSP, effects). |
| `C3/` | Actor/transform layer (`CTRLSetScale`, `CTRLSetRotation`, ...) that stadium and minigame code calls into. |
| `charPipeline/` | Character rendering pipeline — texture palettes, file cache, plus generic container helpers in `structures/` (`HTable`, `List`, `Tree`, `dolphinString`). |
| `PowerPC_EABI_Support/` | Compiler/runtime support: `MSL_C` (standard C lib), `MetroTRK` (debug stub), `Runtime` (PPC EABI exception/init helpers). Rarely relevant to gameplay mods. |
| `stl/` | Metrowerks-era STL-ish headers (`algorithm`, `functional`, `iterator`, ...) used internally by the SDK/runtime code above. |
| `Unknown/` | DOL functions not yet identified — named by address (`File_0xADDR.h`) rather than purpose. Grep here if you have an address but no name. |

## Root files

| file | purpose |
|---|---|
| `mssbTypes.h` | Core game-specific struct/type definitions. Likely your most-included header. |
| `types.h` | Base typedefs (`u8`, `s32`, `f32`, etc.). |
| `executor.h` | REL entry/exit glue (`_prolog`, `_epilog`, `_unresolved`). |
| `header_rep_data.h` | The shared trig-table constant emitted into empty `rep_*` units — not meaningful on its own. |
| `BuildSettings.h` | Template for build-time flags/tunables; mostly commented out, a reference for what mods might want to toggle. |
