# Matching priority list

A snapshot audit of which files are cheapest to finish matching and which
carry the most placeholder symbols, to give `/match-function` (and the
`match` agent) a starting order instead of picking targets ad hoc.
Numbers below are from `objdiff-cli report generate` at the time this was
written — regenerate before trusting them for anything but rough triage; see
[Regenerating this list](#regenerating-this-list).

## Repo-wide

**1,515 / 4,503** functions matched (33.6%) across `src/`. **2,026**
functions (45%) still carry placeholder names (`fn_...`/`lbl_...`/
`jumptable_...`).

## Tier 1 — near-complete, high-value files (do these first)

Large, already-understood files a handful of functions away from 100%:

| file | unit % | unmatched/total | remaining bytes |
|---|---|---|---|
| `src/game/batting/batter.c` | 99.6% → in progress | 5/25 | 84 |
| `src/Musyx/synth.c` | 99.3% | 2/27 | 88 |
| `src/game/math/game_math.c` | 99.3% | 6/27 | 37 |
| `src/Musyx/hw_dolphin.c` | 91.7% | 3/18 | 113 |
| `src/Musyx/hardware.c` | 90.4% | 4/43 | 404 |
| `src/Musyx/synthdata.c` | 90.1% | 9/27 | 736 |
| `src/Musyx/s_data.c` | 86.6% | 6/6 | 408 |

Great `/match-function` candidates in order — small remaining byte counts
mean the leftover mismatches are almost certainly `SYMBOL_NAME`/
`REGISTER_ALLOC`, not fresh implementations.

**`batter.c` status:** set aside for now at 21/25 (see
[Active work](#active-work-batterc) below) — its 4 remaining functions
needed real REGISTER_ALLOC/LOGIC grinding, not quick fixes, which is what
prompted building the `match` agent in the first place. 9 sessions across
several distinct techniques (source restructuring, compiler flags/version,
pragmas, function ordering) all confirmed-exhausted; see
`docs/matching_notes.md` for the reusable findings and
`build/.match_grind/game_game_batting_batter.md` (gitignored, local) for
the full trace.

## Tier 2 — small quick-wins with real context

Single/few-function named files (excluding anonymous `src/Unknown/File_0x*`
stubs, which have no naming evidence and are likely obscure OS/library
thunks — low value to prioritize):

- `src/menus/rep_0200.c` — 1 unmatched fn, 52 bytes, 1 placeholder
- `src/Musyx/hw_volconv.c` — 97.8%, 1 fn, 39 bytes left
- `src/Dolphin/os/OSExec.c` — 97.5%, 1/8 unmatched, 60 bytes

(There are ~30 `src/Unknown/File_0x...` files at "1 unmatched fn, <100
bytes" too — cheap in isolation, but unnamed/no-evidence per
[file_map.md](file_map.md)'s philosophy, so treat them as filler, not
priority.)

## Most placeholder symbols (candidates for `/label-symbols`, separately)

| file | placeholders/total | named % | match % |
|---|---|---|---|
| `src/menus/rep_0788.c` | 150/150 | 0% | 0.6% |
| `src/menus/rep_0B08.c` | 131/132 | 1% | 1.3% |
| `src/game/minigame/rep_3880.c` | 119/123 | 3% | 0.7% |
| `src/game/fielding/fielder_catch.c` | 61/223 | 73% | 0.4% |
| `src/game/camera/camera.c` | 64/76 | 16% | **72.0%** |
| `src/game/baserunning/runner.c` | 30/78 | 62% | 0.6% |
| `src/game/fielding/fielder_ai.c` | 28/59 | 53% | 0.5% |

**Notable anomaly:** `fielder_catch.c`, `runner.c`, and `fielder_ai.c` are
53–73% *named* (strong evidence of what each function does) but almost
nothing in them is *matched* (0.4–0.6%). That combination — well-understood
but essentially untouched — makes them the highest-leverage gameplay targets
once tier 1 is cleared, even though individual functions there are large
(`fielder_catch.c` is the repo's biggest single file at 223 functions).
`camera.c` is the interesting exception: already 72% matched despite only
16% naming, so it's mid-stream, not untouched.

## Suggested order

1. Burn down tier 1 (`batter.c`, `synth.c`, `game_math.c`, `hw_dolphin.c`,
   `hardware.c`, `synthdata.c`, `s_data.c`) — cheap, closes whole files.
2. Sweep the small named quick-wins (`rep_0200.c`, `hw_volconv.c`,
   `OSExec.c`).
3. Start deliberately on `fielder_catch.c`/`runner.c`/`fielder_ai.c` —
   biggest gameplay payoff, but budget real time per function.
4. Run `/label-symbols` on the placeholder-heavy files only after their
   functions get matched (per that command's own precondition).

## Active work: `batter.c`

`batter.c` looked like a tier-1 quick win by byte count, but its 5 remaining
functions turned out to be a useful stress test:

- `calculateBallHorizontalAngleHit` (99.66%), `calculateBuntHorizontalAngle`
  (99.38%), and `batterInBoxMovement` (99.13%) all fail in the *same* shared
  code block — a `g_Minigame._1D7C[...]` lookup — where target and our build
  use the same three registers (r27/r28/r30) for the same three live values
  but in a different rotation. Pure REGISTER_ALLOC, no logic difference.
- `calculateHitVariables` (97.80%) and `calculateContactAndHitType` (97.40%)
  have real LOGIC differences on top of the same register issue.

This cross-function coupling (a fix to the shared block affects three
functions at once) is why single-function `/match-function` runs weren't a
good fit here, and is what motivated the `match` agent design
(`.claude/agents/match.md`, `.claude/agents/match-worker.md`) — a
file-scoped, checkpointed orchestrator instead of one-shot per-function
passes. Progress/hypothesis log for this file lives at
`build/.match_grind/game_game_batting_batter.md` once a grind has started —
gitignored local scratch, pruned once the file hits 100%. Durable
cross-file findings get promoted out of it into
[matching_notes.md](matching_notes.md) instead.

A first grind pass exhausted the register-rotation block (8 hypotheses,
none improved it — likely a genuine CodeWarrior allocator quirk, not
reachable from source shape) and left `calculateHitVariables`/
`calculateContactAndHitType` pending with real LOGIC content, including an
apparent miscompile in the former (a literal `0` stored where target stores
`captainStarSwingActivated`'s value). The grind also surfaced a theory that
`batterInBoxMovement`/`calculateHitVariables`/`calculateContactAndHitType`'s
CONST_POOL noise came from `UnknownHomes_Game.h`'s `#define SQRT2_LINKAGE
extern` making mwcc materialize an unused `dolsqrtf2` instantiation (plus
its local statics) at the start of `.rodata`, shifting every later symbol by
16 bytes.

**That theory was tested and disproven.** Removing `SQRT2_LINKAGE`'s
`extern` (reverting `dolsqrtf2` to plain `static inline`) made things
*worse*: two of the three flagged functions were unaffected, the third
dropped 97.93% → 80.07%, and even files that never call `dolsqrtf2` at all
(`game_math.c`, `camera.c`, `runner_base_rounding.c`) regressed hard —
`game_math.c` alone lost 51 points of code-match. Repo-wide matched
functions dropped 1515 → 1489. The change was fully reverted (verified back
to exact baseline). Conclusion: `extern` linkage is load-bearing for how
MWCC pools/reuses float literals project-wide (`-str reuse,readonly`), not
an unwanted leak — and at least one non-caller file (`stadium/kinoko.c`)
already carries the same materialized statics in the *retail* binary, so the
original "target has zero residue, we have extra" premise doesn't fully
hold either. **Don't re-attempt this specific fix without new evidence** —
the actual CONST_POOL root cause in these functions is still unresolved.

## Tooling notes relevant to this list

- The repo's pinned `build/tools/objdiff-cli.exe` was bumped from v3.4.0 to
  v3.7.3 to fix exactly this: v3.4.0 had no `diff -o --format json` support
  at all (it was removed after v3.4.0 and restored in v3.6.0), and v3.8.0's
  `report generate` crashes project-wide
  (`Failed to find right side symbol for paired left side symbol`) —
  confirmed via a bisect of every tag between v3.4.0 and v3.8.0. v3.7.3 is
  the latest tag where both `report generate` and `diff -o - --format json`
  work correctly on this project, so both `match_progress.py` and
  `tools/match_classify.py` now work off the single pinned binary; the
  `MSSB_OBJDIFF_CLI` override is no longer needed for this reason (it's
  still useful for testing other builds).
- `tools/match_classify.py`'s `cmd_scan`/`cmd_fix`/`units` all call
  `generate_report()` unconditionally (even `--unit`-scoped runs), so they
  inherit whichever binary's `report generate` bug is currently live. Drive
  `objdiff_unit()`/`classify_function()` directly when that matters.

## Regenerating this list

```
build/tools/objdiff-cli.exe report generate -p . -o <tmp>.json -f json
```

then group `units[].functions[]` by `metadata.source_path`, using
`fuzzy_match_percent < 100` to find unmatched functions and a placeholder
regex (`^(fn_[0-9A-Fa-f]{6,8}$|fn_\d+_[0-9A-Fa-f]+$|lbl_[0-9A-Fa-f]{8}$|
lbl_\d+_[0-9A-Fa-f]+$|jumptable_)`) against function names for the
placeholder counts. Filter to `source_path` starting with `src/` and drop
units with `metadata.auto_generated: true`.
