# barrel_batter.c (Barrel Batter minigame) — match grind checkpoint

Unit: `game/game/minigame/barrel_batter` (REL, game module). Started 2026-09-24 from 30 `return;` stubs.
Split: .text 0x12E8FC-0x132EDC, .rodata 0x34B0-0x3520, .data 0x26510-0x2657C.
.rodata = repHeaderData (header_rep_data.h) + 100.0 (double), int->float bias, 0.3 (double), 0.0f, 1.0f.
.data = only jumptable_3_data_26510 (27-entry switch in barrelBatterSwitcher).

## Work order (leaf-to-root, from the in-file bl call graph)
B1: fn_3_130A80, fn_3_13128C, fn_3_13207C, fn_3_131114, fn_3_12F9D4, fn_3_1323CC, fn_3_12ED80
B2: fn_3_12EE68, fn_3_12EB10, bB_chooseBombBarrel_dropNewBarrels, fn_3_12F28C, bB_connectingBarrels, fn_3_12FD6C, fn_3_12FE84
B3: bB_likelyReplaceBlownUpBarrels, bB_checkIfBarrelHitAndCalculateScore, fn_3_12FFD4, bobombDerbyRelated, fn_3_13119C, fn_3_131EC4, fn_3_131FFC
B4: fn_3_131C88, fn_3_12FAC4, barrelBatterLiveBallSubFun, fn_3_1307D0, fn_3_1312D4
B5: bB_AtBat, bB_LoadGame; B6: barrelBatterTransitionToMainFunction; B7: barrelBatterSwitcher

## Sections
| section | baseline | current (2026-09-30/10-01, match-sonnet) |
|---|---|---|
| .text | 0.6708408 | 87.12992 |
| .rodata | 83.33333 | 80.0 |
| .data | 0.0 | 0.0 |

**2026-09-30/10-01 session note on .rodata (80.0%, down from 86.67%):** this is
a pure side-effect of the whole-TU literal-pooling issue already described
above (fresh anonymous `@NNN` constants instead of reusing
`lbl_3_rodata_351C`/`3518`/`3500`/`3508`/`3510`), now touched by *more* call
sites (every new function drafted this session that needed `1.0f`/`0.0f`/
`100.0`/`0.3` for the barrel-drop/VecXYZ-build idiom). No individual
function's own score regressed this session (verified after every single
edit) — the section number moving is an aggregate/pooling-order effect, not
a bug in any one function. Expected to self-resolve once the whole file's
near-misses close enough that MWCC's literal pool settles on the named
slots; not independently actionable per-function.

**`.data` (0.0%, jumptable):** now confirmed (not just assumed) to be purely
a function of `.text` exactness. Read `jumptable_3_data_26510`'s relocations
directly from the objdiff JSON this session (`.data` section's
`reloc_diff`, each entry `{target_symbol: barrelBatterSwitcher, addend: N}`)
— addend `N` is the exact byte offset from `barrelBatterSwitcher`'s own
start to that case's label. Our compiled table's addends are off by a few
bytes per entry (e.g. target addend 1040 vs ours 1044) because
`barrelBatterSwitcher` itself isn't byte-exact yet; this will climb toward
100% automatically as the function's remaining register-noise is ground out,
not before. **Tip for the Opus pass**: this same technique (read `.data`'s
`reloc_diff` directly) is the reliable way to recover a jump table's
case-order on any REL unit — don't guess from `.L_*` label order in the
`.s` file, which is unrelated to switch-case value order (see
`barrelBatterSwitcher`'s hypothesis log below for why).

.rodata is now ABOVE the original 83.33 baseline (was briefly 80.56 after B1, now 86.67 after B2). The literal-pooling regression from B1 (fn_3_12F9D4/fn_3_1323CC minting anonymous @NNN constants for 1.0f/0.0f instead of reusing lbl_3_rodata_351C/3518) is still present and unresolved (expected per B1 notes, needs B4/B5), but B2 fixed a *different*, actually-wrong bug that was costing more: `bB_chooseBombBarrel_dropNewBarrels`'s and `fn_3_12FE84`'s "starting Y offset when barrel drops" addition was wrongly reading a fabricated field `lbl_3_data_21788.startingYForBarrelDrop` (guessed struct offset 0 of the threshold object) — the real constant, per asm, is `lbl_3_data_21770[0]` (the same 6-float array whose `[1]` is the B1-established rise-per-frame increment). Fixing this one-line bug alone gained bB_chooseBombBarrel_dropNewBarrels +0.11pp, fn_3_12FE84 +0.18pp, and pulled `.rodata` from 80.0 to 86.67 (this constant's rodata pooling was apparently the dominant remaining rodata mismatch, bigger than the known 1.0f/0.0f issue). `lbl_3_data_21788` is now known to be used ONLY for its `+4` `s16 bombBarrelThreshold` field in this whole TU so far; offset 0 (4 bytes) is unaccounted for — left as raw padding (`u8 _00[4];`) rather than guessed.

## Status
| function | status | baseline | pct |
|---|---|---|---|
| bB_chooseBombBarrel_dropNewBarrels | pending | 0.7518797 | 94.05 |
| fn_3_12EB10 | pending | 0.64102566 | 71.80 |
| fn_3_12ED80 | pending | 1.7241379 | 99.844826 |
| fn_3_12EE68 | pending | 1.2658228 | 88.77 |
| bB_likelyReplaceBlownUpBarrels | pending | 0.53763443 | 76.4839 |
| fn_3_12F28C | pending | 0.98039216 | 83.62 |
| bB_connectingBarrels | pending | 0.78125 | 78.99 |
| bB_checkIfBarrelHitAndCalculateScore | pending | 0.42372882 | 62.1441 |
| fn_3_12F9D4 | pending | 1.6666666 | 84.03333 |
| fn_3_12FAC4 | pending | 0.5882353 | 0.5882353 |
| fn_3_12FD6C | matched | 1.4285715 | 100.0 |
| fn_3_12FE84 | pending | 1.1904762 | 91.89 |
| fn_3_12FFD4 | pending | 0.5780347 | 71.3410 |
| barrelBatterLiveBallSubFun | pending | 0.295858 | 0.295858 |
| fn_3_1307D0 | pending | 0.5813953 | 0.5813953 |
| fn_3_130A80 | matched | 5.263158 | 100.0 |
| bobombDerbyRelated | matched | 0.96153843 | 100.0 |
| bB_AtBat | pending | 0.33557048 | 0.33557048 |
| fn_3_131114 | matched | 2.9411764 | 100.0 |
| fn_3_13119C | matched | 1.6666666 | 100.0 |
| fn_3_13128C | matched | 5.5555553 | 100.0 |
| fn_3_1312D4 | pending | 0.6451613 | 0.6451613 |
| barrelBatterTransitionToMainFunction | pending | 0.21459228 | 0.21459228 |
| fn_3_131C88 | pending | 0.6993007 | 0.6993007 |
| fn_3_131EC4 | pending | 1.2820513 | 96.6667 |
| fn_3_131FFC | matched | 3.125 | 100.0 |
| fn_3_13207C | matched | 6.25 | 100.0 |
| bB_LoadGame | pending | 0.5102041 | 0.5102041 |
| fn_3_1323CC | pending | 1.4084507 | 62.366196 |
| barrelBatterSwitcher | pending | 0.15698586 | 0.15698586 |

## Prototypes / signatures found
- `SetGameStatus(GAME_STATUS status)` — shared engine function, no header declares it anywhere in the repo (only a local `extern void SetGameStatus(int status);` exists in pitcher.c). Declared locally in barrel_batter.c with the enum param type (better than pitcher.c's `int`, still correct since enum is backed by int).
- `callSfx(int soundId)` — `include/game/sound/m_sound.h` declares `void callSfx(void)`, but callSfx's own definition in `src/game/sound/m_sound.c` is *itself* still a `{ return; }` stub, so that prototype is simply wrong/unfinished, not something to trust. Every call site in this file passes an int (`0x2e4`/`0x2e5`) in r3. Declared a corrected local extern; did not touch m_sound.h.
- `fn_8004C108(VecXYZ *pos, BOOL flag)` — un-implemented `.dol`-resident engine function (`fn_8004C108 = .text:0x8004C108`, size 0xC94, in `config/GYQE01/symbols.txt`), not declared anywhere in the repo. Evidence: r3 is the address of a 3-float (x,y,z) stack scratch buffer built immediately before the call, r4 is 0 or 1. Declared locally as `extern void fn_8004C108(VecXYZ *pos, BOOL flag);`.
- `sndFXStartEx` — already correctly declared in `include/musyx/musyx.h`; just needed the include (`#include "musyx/musyx.h"`) plus the existing repo-wide `extern u8 lbl_800EFBA4[0x10];` idiom (copied from `src/menus/main_menu.c` etc.) for the per-sound-ID volume table.
- `setInMemBatterConstants(int rosterID)`, `setDefaultInMemBall/Pitcher/Batter/Runner/Fielder(void)`, `pauseAnimations(void)`, `pauseStateOnStadiums(void)` — all correctly declared already in their respective headers (`roster_init.h`, `ball_physics.h`, `pitcher.h`, `batter.h`, `runner.h`, `fielder.h`, `scene_effects.h`); just needed the `#include`s added to barrel_batter.c.
- `memset` — declared in `include/Dolphin/stl.h`; added that include (same header `sta_c6.c` relies on transitively).
- `g_UnkSimulation_31AC0` — a `.bss` object at 0x31AC0, size 0xC, `data:byte`, listed in `config/GYQE01/game/symbols.txt` but with NO struct type anywhere in the repo, and not referenced by any other src file. It is used repeatedly through this whole TU (fn_3_131114 here, and again later in fn_3_131C88/B4 and barrelBatterSwitcher/B7, always writing byte offset 5 and 6 to 0/4 alongside a `g_FieldingLogic.playOverCounter = 0` reset). Declared a *local*, minimal, evidence-only struct `UnkSimulationStruct_31AC0` in barrel_batter.c (fields `_05`, `_06` named, rest left as padding byte arrays) since this isn't shared-header material yet and I only have evidence for 2 of its 12 bytes. Flagging back: this probably deserves a proper name/struct in `UnknownHomes_Game.h` once B4 gives more field evidence — did not do that myself per the "prefer reporting back" header-edit rule.
- `lbl_3_data_21770` — `.data:0x21770`, size 0x18 (6 floats), `scope` not marked local in symbols.txt (used across essentially every function in this TU, and also apparently owned by a different/earlier unit since 0x21770 is far below this unit's own `.data` range of 0x26510-0x2657C). Only offset `[1]` (a single float, effectively a fixed "barrel rise speed" per-frame increment) was needed for B1. Declared `extern float lbl_3_data_21770[6];` locally; the other 5 floats' meanings are unknown from B1 alone.
- `lbl_3_rodata_3500` (double, 100.0), `lbl_3_rodata_3508` (double, int->float bias magic 0x4330000080000000), `lbl_3_rodata_3510` (double, 0.3) — confirmed via base64-decoding the `.rodata` DIFF_DELETE blob in the objdiff JSON; all `scope:local` compiler-emitted float/double literal pool entries, not used by any B1 function (they belong to bB_LoadGame/fn_3_1312D4, B4/B5). Do not declare externs for these — just write the literal (100.0, etc.) in the B4/B5 C code and MWCC will regenerate the same named slots once those functions are implemented.
- `lbl_3_rodata_3518` (float 0.0f) and `lbl_3_rodata_351C` (float 1.0f) — same situation: `scope:local` literal-pool floats. fn_3_12F9D4/fn_3_1323CC both need a bare `1.0f` and `0.0f` literal (not an extern) but because no other function in this TU has used those exact literals yet in this WIP build, MWCC currently pools them as fresh anonymous constants (`@202`/`@203`) rather than reusing/naming these slots, which is the source of the current 80.56% (from 83.33% baseline) `.rodata` score — expected to resolve once whichever function in B3-B5 first "claims" these exact literals is implemented in file order.
- `lbl_3_data_21770[0]` (f32) — **CORRECTION to a B1 assumption.** This, not a fabricated `lbl_3_data_21788.startingYForBarrelDrop` field, is the real "vertical offset added when a barrel starts dropping/rising" constant, confirmed by asm in `bB_chooseBombBarrel_dropNewBarrels`/`fn_3_12FE84` (`lis r6,lbl_3_data_21770@ha; ...; lfs f0,0x0(r27)` immediately before the `currentPos.y +=`). `lbl_3_data_21770` is the same 6-float array from B1 whose `[1]` is the "finish rising" per-frame increment (used in fn_3_12F9D4/fn_3_1323CC) — so at least `[0]` and `[1]` of this array are now pinned down; `[2..5]` still unknown.
- `lbl_3_data_21788` — **CORRECTION to a B1 assumption.** B1 guessed this `.data:0x21788, size:0x8` object was `{ f32 startingYForBarrelDrop; s16 bombBarrelThreshold; }`. Only the `+4` `s16 bombBarrelThreshold` field is actually read anywhere in the TU (in `bB_chooseBombBarrel_dropNewBarrels`'s charge-meter check); offset 0 is never read by any B1/B2 function. Declared locally now as `{ u8 _00[4]; s16 bombBarrelThreshold; }` — do not assume offset 0 is a float without new evidence from B3+.
- `fn_3_12EE68(int barrelIndex)` — takes the barrel index in `r3`, no return value. Checks `barrelIndex % 3 == 2` (last-of-row) and returns immediately if so (no "next" barrel in the row to affect). Otherwise operates on `barrels[barrelIndex+1]` (the next barrel in the row): if it's already `barrelState==4` (blownUp) returns; if it's `barrelState==3` (readyToBlowUp, confirmed via `bB_connectingBarrels`, see below) and the Y-distance between its `desiredPos.y` and the current barrel's `desiredPos.y` exceeds `lbl_3_data_21770[3] + 0.3`, returns without doing anything (positions too far apart to connect visually). Otherwise sets `replacingBarrelInd=1`, `velo_bounceUpOnBlowUp=lbl_3_data_21770[4]`, and sets `_28` (still-unnamed f32 field at struct offset 0x28) to a `barrelBaseCoordinates[]` Y lookup — either `barrelBaseCoordinates[barrelIndex].y` directly (if `barrelIndex` is first-of-row) or `barrelBaseCoordinates[flag].y` where `flag = (barrels[barrelIndex-1].barrelState==2) | (barrels[barrelIndex].barrelState==2)` (if `barrelIndex` is middle-of-row) — i.e. picks between the table's row-0 and row-1 Y anchor depending on whether either neighboring barrel is "settled" (`barrelState==2`). This body reappears **inlined verbatim** inside `fn_3_12F28C` (confirmed both via asm and via calling `fn_3_12EE68(barrelIndex)` there, which MWCC auto-inlined to matching size) — strong evidence the real source of `fn_3_12F28C` does call `fn_3_12EE68`, it's just always inlined by `-inline auto`. IMPORTANT: get the `|` vs `||` right for the two-flag combine — `||` short-circuits and forces branchy code (measured 62.49%); `|` (bitwise, both sides always evaluated) reproduces the target's branchless double-`cntlzw` idiom (measured 88.77% after also reordering the `barrel` pointer's declaration to *before* the early-return check, matching target's instruction order).
- `bB_connectingBarrels(int barrelNum, s16 blowUpDelay, int bombBarrelHitInd)` — confirmed via Ghidra decompile (it resolved cleanly with real enum names `enum_bb_barrelState.neutral`/`readyToBlowUp`/`blownUp`). **New evidence for `barrelState` values**: 0=empty, 1=dropping/rising (set in `bB_chooseBombBarrel_dropNewBarrels`/`fn_3_12FE84`), 2=neutral/settled (set at the end of `fn_3_12F9D4` — matches!), 3=readyToBlowUp, 4=blownUp (matches B1's `fn_3_12EB10` decompile which also names state 4 `blownUp`). No enum exists in the repo yet for this field (`barrelState` is still plain `u8`/int in `BB_barrelStruct`) — flagging back rather than inventing one, since match/label-symbols judgment on enum creation isn't this task's call, but there's now strong 5-value evidence (0/1/2/3/4) for `BB_barrelStateE`-style naming (empty/dropping/neutral/readyToBlowUp/blownUp) if the orchestrator wants to add it. Function checks the 4 neighbors of `barrelNum` in the 5-row/3-column barrel grid (above, below, left, right — where "row" = `barrelNum/3`, "column" = `barrelNum%3`) and marks any neutral same-colour (or `bombBarrelHitInd!=0`, i.e. hit-by-bomb overrides colour) non-bomb-barrel neighbor as `readyToBlowUp` with `animationCounter=0` and `delayUntilBlownUp=blowUpDelay`. Left/right (column) neighbors have no boundary check needed beyond `barrelNum/3` range checks (0 columns of 5 rows × 3 cols, but only ±3 for "left"/"right" — actually these are visually the row-to-row (vertical row index) neighbors in the 5×3 grid the checkpoint's B1 notes call "rows of 3"; despite the local variable names `barrelAbove`/`barrelBelow`/`barrelToLeft`/`barrelToRight` mirroring Ghidra's guess, the actual geometry (5 groups of 3, i.e. `barrelNum/3`=row-of-5, `barrelNum%3`=position-in-row-of-3) means `±1` neighbors are within the same "row of 3" and `±3` neighbors are in the adjacent "rows of 3" — so Ghidra's "above/below" labels apply to the `%3` axis and "left/right" to the `/3` axis, or vice versa; the exact screen-space orientation isn't determinable from this function alone). Match note: declaring `barrelColour` as `u8` compiles the `==` colour comparisons to `cmplw` (unsigned) — target uses `cmpw` (signed) for the identical comparison (functionally identical, but the register-allocator/branch encoding differs) — declaring `int barrelColour` instead reproduced `cmpw` and was the single highest-value fix (76.38%→78.99%). Also tried removing the `barrelAbove`/`barrelBelow`/`barrelToLeft` locals (inlining `barrelNum±k` everywhere) hoping to shed the extra saved register (target has literally no stack frame; ours still saves `r31`) — this consistently scored *worse* (71.6%/77.1%) both with `u8` and `int` colour, so the locals are being kept as-is.
- `fn_3_12F28C(int barrelIndex)` — confirmed via Ghidra decompile (`FUN_8076e320`). If `barrels[barrelIndex].delayUntilBlownUp <= barrels[barrelIndex].animationCounter` (i.e. the blow-up delay timer has elapsed): sets `barrelState=4` (blownUp), `animationCounter=0`, calls `fn_3_12EE68(barrelIndex)` (only if not last-of-row, matching `fn_3_12EE68`'s own internal early-return but duplicated at the call site — kept both checks since that's what target does; removing the caller-side check wasn't tried, this is the check present in Ghidra's decompile), then always calls `setCharacterAnimations(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID], 0)` (exact idiom copied from existing uses in `batter.c`/`fielder.c`).
- `fn_3_12FD6C(void)` — no params, iterates all 15 barrels; for any with `barrelState != 0` (i.e. not empty), copies `currentPos` to `posAtStartOfTurn` field-by-field (`x`/`y`/`z` individually — a `VecXYZ` struct assignment (`a = b;`) compiles to `lwz`/`stw` word-copies and does NOT match; target uses `lfs`/`stfs` per-field, only reproducible by writing `.x`/`.y`/`.z` explicitly — this cost 72.2%→100% by itself, the single highest-value fix in this batch) and sets `barrelState=1` (dropping); unconditionally (regardless of state) resets `animationCounter=0`. Reached 100.0% exactly.
- `fn_3_12FE84(void)` — no params, no return; the same 15-barrel "drop a new barrel" body as `bB_chooseBombBarrel_dropNewBarrels`'s second loop, but simpler: always resets EVERY barrel (no `barrelState==0` guard), sets `desiredPos` (not just `currentPos`) to `barrelBaseCoordinates[i]`, resets `replacingBarrelInd=0`, and has no bomb-barrel-selection logic at all. Reuses the exact same "starting Y offset + random Y jitter" formula as B1/`bB_chooseBombBarrel_dropNewBarrels` (see `lbl_3_data_21770[0]` correction above).
- `fn_3_12EB10(void)` — no params, no return, the most structurally complex function in this batch (0x270 bytes, 71.80% after 2 iterations). For each of the 5 "rows of 3" barrels, scans positions 0 and 1 (not 2, since it looks at "the next barrel") for `barrelState==4` (blownUp); on finding one at position `pos`, shifts every subsequent barrel in that row down by one slot (`barrels[k-1] = barrels[k]` for `k` from `pos+1` to `2`, copying `barrelState`/`barrelColour`/`currentPos.x/y/z` field-by-field, **and setting `barrels[k].barrelState=0` after EVERY individual copy step, not just once at the end** — this look redundant for `k<2` since it gets overwritten by the next iteration's copy, but is what the target's unrolled asm actually does, and fixing this (matching the per-step-zero pattern instead of a single final zero) was the single largest gain in this function: 60.87%→71.80%) and re-checks the SAME position again (since a different barrel now occupies it) rather than advancing — implemented as a `while(pos<2){ if(blownUp){shift-loop;} else {pos++;} }`. After the 5-row loop, unconditionally checks barrels 2/5/8/11/14 (the last-of-row positions) for `barrelState==4` and resets them to 0 if so (a final "cap-off" cleanup Ghidra's decompile shows as literal unrolled `if`s, not a loop — kept as 5 explicit `if`s to match). Remaining diff at 71.80% is almost entirely register-allocation/instruction-ordering noise in the generic unrolled shift-loop (MWCC applies a by-4-with-remainder unroll to the `for(k=pos+1;k<3;k++)` inner loop even though `pos+1..2` is at most 2 iterations, since the trip count isn't a compile-time constant) — did not find a further win in the 2 tries attempted; flagging for a future pass with more budget rather than continuing to guess blindly.

## Log
### fn_3_130A80: 100.0% — sets `g_Minigame.bB_bombBarrelID = -1`, three `g_GameLogic` transition-related BOOL flags to TRUE, calls `SetGameStatus(GAME_STATUS_TRANSITION)`. First-try match after adding the `SetGameStatus` extern.
### fn_3_13207C: 100.0% — plays sound `sndFXStartEx(0x1bd, lbl_800EFBA4[6], 0x3f, 0)` then `SetGameStatus(GAME_STATUS_TRANSITION_TO_MINIGAME_START)`. First-try match.
### fn_3_131114: 100.0% — resets in-memory batter/ball/pitcher/batter/runner/fielder state (calls into other already-declared modules), `memset`s `g_Minigame._1D7C` (the 4-element `InputStruct` array at the very end of the struct), pauses animations/stadiums, resets `g_FieldingLogic.playOverCounter` and 2 bytes of the still-mostly-unknown `g_UnkSimulation_31AC0`. First-try match. Note: this function's entire body reappears duplicated inline inside `fn_3_131C88` (B4) with one extra `memset` afterward — strong evidence `fn_3_131C88` is NOT a simple wrapper/caller of `fn_3_131114`, it duplicates the code (matches the "in-file functions get inlined into callers" pattern the task asked to watch for).
### fn_3_13128C: 100.0% — `if (Inning >= inningLimit) SetGameStatus(POSTGAME) else SetGameStatus(TO_MINIGAME_START)`. First try (with the intuitive `<` condition and swapped branch bodies) scored 99.61% with `blt`/`bge` and the two `li` constants both swapped versus target; flipping the comparison to `>=` and swapping the two branch bodies (keeping the same net semantics) reproduced target exactly. This is the same "polarity of default-then-override" idiom warning from the general instructions — measure both, don't guess.
### fn_3_12ED80: 99.84% (232/232 bytes, only `DIFF_ARG_MISMATCH`, no missing/extra instructions) — returns whether any of barrels 1,2,4,5,7,8,10,11,13,14 (i.e., the 2nd/3rd barrel of each 3-barrel row, skipping the 1st) has `replacingBarrelInd` set; if none do, returns 1. Implemented as `BB_barrelStruct *barrel = g_Minigame.barrels; for (i=0;i<5;i++,barrel+=3) { if(barrel[1]...) if(barrel[2]...) }`. Remaining diff: target folds the row-stride pointer-advance differently across the 5 unrolled iterations — after checking row 0 barrels directly off `&g_Minigame` (offsets 0x8c6/0x8fa), target does ONE `addi r3,r3,0xd0` (4 barrel-strides) then reads with LARGE immediates (0x892/0x8c6/0x92e, i.e. barrel-index-0/1/3-sized offsets reused relative to the shifted base) and only re-adds `0x9c` (3 strides) between rows; our compiled code instead keeps `barrel` pointing at the true row base and reads with SMALL immediates (0x66/0x9a, i.e. field-offset-only relative to barrel[3*row]) advancing by 0x9c each iteration. Both encode the identical final addresses (verified row-by-row) — it's a pure constant-folding/addressing-mode choice by MWCC given the exact loop induction variable in the real source, not a semantic difference. Tried: (a) the pointer-increment `for` loop above → 99.84% (kept); (b) direct `g_Minigame.barrels[row*3+1]`/`[row*3+2]` indexing with a `for(row=1;row<5;row++)` after 2 manual direct checks → 94.69% (worse, reverted). Did not find a third structural variant worth the extra build cycles; leaving at 99.84%.
### fn_3_12F9D4: 84.03% (240 target / 228 ours bytes) — per-barrel "finish rising into place" step: `barrel->currentPos.y += lbl_3_data_21770[1]`; if still short of `desiredPos.y`, clamp `currentPos.y` to `desiredPos.y`, and — only if `posAtStartOfTurn.y != desiredPos.y` (barrel actually needed to move) — build a `VecXYZ{x: currentPos.x, y: -currentPos.y, z: currentPos.z - 1.0f}` and call `fn_8004C108(&pos, near ? TRUE : FALSE)` + `callSfx(near ? 0x2e4 : 0x2e5)` where `near` is `currentPos.y <= 0.0f`; then sets `barrelState = 2`. All control flow, field accesses, and constants (1.0f/0.0f — decoded from the `.rodata` DIFF_DELETE blob, NOT a barrel-array-style table) are confirmed correct — first ~18 instructions match target byte-for-byte, and the branch/call structure at the end matches. Remaining diff is (1) the two float-literal loads (1.0f/0.0f) currently mint fresh anonymous rodata constants instead of reusing named `lbl_3_rodata_351C/3518` — a whole-TU literal-pool ordering effect described in Prototypes above, not fixable from this function alone; and (2) the exact instruction order/register choice MWCC used to build the temporary `VecXYZ` on the stack (target stores RAW `currentPos.y`/`currentPos.z` into the stack slots first as if from a struct copy, then overwrites `y` and `z` in place after computing `-y` and `z-1.0`, while `x` is stored plain partway through). Tried 3 field-initialization orderings: (a) `pos.x=..; pos.y=..; pos.z=..;` field-by-field in that order → 84.03% (best, kept); (b) `pos = barrel->currentPos; pos.y=-...; pos.z=...-1.0f;` (struct copy then override) → 82.67%, and it also degrades `x`/`z` from `lfs`/`stfs` to `lwz`/`stw` word copies; (c) `(VecXYZ){x,y,z}` compound literal → rejected by MWCC ("illegal constant expression" — the target's compiler evidently used field assignment, not an aggregate initializer, so this route isn't viable at all). Kept (a).
### fn_3_1323CC: 62.37% (284 target / 276 ours bytes) — loop over all 15 barrels; for each with `barrelState==1`, runs the exact same "finish rising" logic as `fn_3_12F9D4` inline (not a `bl` to it — see below), then continues. Wrote the loop body by hand (same logic as fn_3_12F9D4) since register allocation differs from a real call. Remaining diff: target keeps FIVE live registers across the loop via one `stmw r27,0x1c(r1)` (r27=row-counter compared with `cmplwi ...,0xf`, r28=barrel-check pointer advanced by struct stride, r29=barrel-base-for-position-fields pointer, r30=`lbl_3_data_21770` base pointer, r31=a separate accumulating byte-offset used only for the `currentPos`/`desiredPos` addressing) — i.e. TWO independent address-computation chains for what is structurally "the same barrel," one via a moving `BB_barrelStruct*` (for the `barrelState` pre-check) and one via a raw accumulated byte offset off `&g_Minigame` (for the position-update code). This is strong evidence the position-update block in the real source is a **separate, non-inlined-looking address computation** — i.e. plausibly the real source calls `fn_3_12F9D4(i)` and MWCC's `-inline auto` inlined it, reconstructing its OWN independent addressing (mulli-based) rather than reusing the loop's own `barrel` pointer. Tried calling `fn_3_12F9D4(i)` directly inside `if (g_Minigame.barrels[i].barrelState==1)` — it DID get inlined (no `bl` in the output) but scored slightly worse (59.87%) with a different, still-mismatched register layout, so kept the hand-written inline body (62.37%, using an unsigned `u32 i` loop counter to get the target's `cmplwi` rather than `int i`'s `cmpwi`, which was worth +0.79pp on its own: 61.59%→62.37%). This function may be worth revisiting once fn_3_12F9D4 itself is 100% (a correct callee may inline identically) or in a later grind pass with more build-iteration budget; flagging rather than continuing to guess further given the 5-iteration budget.

## B2 log (2026-09-24)
### bB_chooseBombBarrel_dropNewBarrels: 94.05% (532/532 bytes) — decompiled cleanly via Ghidra. Counts empty (`barrelState==0`) barrels among all 15 (only if `barrelBatterChargeMeter >= lbl_3_data_21788.bombBarrelThreshold`), rolls `random_fn_3_9EE24(emptyCount)` to pick which empty slot (in iteration order) becomes the bomb barrel, resets the charge meter, then iterates all 15 barrels: any empty one gets `barrelState=1`, `currentPos` set from `barrelBaseCoordinates[i]` + `lbl_3_data_21770[0]` Y-offset + a random jitter (`(i%3)*10 - (roll*5)/100.0`, integer `*10` not `*10.0` — this polarity was worth +4.5pp on its own since it changes float-vs-int intermediate codegen), `barrelColour=random_fn_3_9EE24(3)`, and if this is the chosen bomb-countdown slot, overrides `barrelColour=3` (brown, per Ghidra's `enum_bb_barrelColour.brown`) and sets `bB_bombBarrelID`. Iterated 5 times: (1) initial straightforward translation → 88.36% (only `DIFF_ARG_MISMATCH`, no missing/extra instrs — pure register/frame-size noise); (2) reordering local declarations (`bombBarrelChosen`/`barrelsUntilBomb`/`i`) → no change; (3) changing `(i%3)*10.0` to `(i%3)*10` (int mult, matches target's separate `mulli ...,0xa` before the double conversion instead of fusing into a float multiply) → 92.16%; (4) replacing the `BB_barrelStruct *barrel = &g_Minigame.barrels[i]` pointer-local pattern in the fill loop with direct `g_Minigame.barrels[i].field` indexing throughout (matches target keeping ONE base+large-immediate addressing style rather than a per-iteration small-offset pointer) → 93.64%; (5) swapping `BOOL bombBarrelChosen` and `int barrelsUntilBomb` declaration order → 93.94%; (6, folded into the B2 "starting Y" fix below, not a separate build) `lbl_3_data_21770[0]` correction → 94.05% (final). Remaining diff is entirely register-numbering (`r3`/`r4`/`r5` vs `r4`/`r5`/`r9` etc. in the counting loop) plus one still-anonymous rodata double literal pooling artifact (`@295`/`@298` vs `lbl_3_rodata_3500`/`3508` — same known whole-TU literal-ordering issue as B1, unrelated to this function's own code).
### fn_3_12EE68: 88.77% (316/316 bytes) — see Prototypes above for full behavior. Iterated: (1) direct translation with `||` for the two-flag combine and `barrel`/`nextBarrel` pointers declared together before the early-return → 62.49%; (2) changed `||`→`|` (branchless idiom) → still 62.49% alone... (combined with next fix below jumped much further, see next); (3) moved `BB_barrelStruct *barrel = &g_Minigame.barrels[barrelIndex];` declaration to BEFORE the `if (posInRow==2) return;` guard (matching target computing the barrel-pointer unconditionally up front) → 88.77% (huge jump, kept). Remaining diff is register renumbering plus the same rodata literal-pooling artifact for `0.3` (`@278`/`@280` vs `lbl_3_rodata_3510`).
### bB_connectingBarrels: 78.99% (skipped straight to a clean Ghidra-derived implementation, see Prototypes above for full semantics and the `barrelState` value table). Iterated 4 times: (1) direct translation with `u8 barrelColour` local and `int barrelAbove/barrelBelow/barrelToLeft` locals → 76.38% (only remaining diff was register renumbering plus ONE real semantic-adjacent issue: `cmplw` vs `cmpw` for the colour comparisons); (2) tried removing all 3 locals (direct `barrelNum±k` indexing everywhere) while still on `u8` colour → 71.58% (worse, reverted); (3) reverted to locals, changed `u8 barrelColour`→`int barrelColour` → 78.99% (best, kept — this alone fixed the `cmplw`/`cmpw` mismatch); (4) tried removing just the `barrelAbove` local (keeping `int` colour) → 77.09% (worse than keeping the local, reverted). Remaining diff at 78.99%: target has NO stack frame at all (leaf function, no `stwu`); ours still saves `r31` (needs a 7th non-volatile register), suggesting one variable is still live across more of the function than in the real source — not resolved in the 4-iteration budget.
### fn_3_12F28C: 83.62% (408/408 bytes, matches target size exactly) — see Prototypes above. First try, calling `fn_3_12EE68(barrelIndex)` (which MWCC auto-inlined, confirming the task's "try a plain call first" guidance) → 83.62% immediately (inherits `fn_3_12EE68`'s own residual register-noise diff, plus the same rodata literal-pooling artifact). Tried flipping the outer guard to `animationCounter >= delayUntilBlownUp` (algebraically identical, reversed field-load order) hoping to match target's animationCounter-loaded-first instruction order → 82.80% (worse, reverted back to `delayUntilBlownUp <= animationCounter`).
### fn_3_12FD6C: 100.0% (280/280 bytes) — see Prototypes above. First try (straightforward `for` loop, `posAtStartOfTurn = currentPos;` as a whole-struct assignment) → 72.21% (target uses `lfs`/`stfs` per-field; struct assignment compiles to `lwz`/`stw` word-copies and does not match — this is the same "field-by-field vs struct-copy" lesson as B1's `fn_3_12F9D4`). Splitting the assignment into `.x`/`.y`/`.z` individually → 100.0% immediately.
### fn_3_12FE84: 91.89% (336/336 bytes) — see Prototypes above; essentially the "unconditional" sibling of `bB_chooseBombBarrel_dropNewBarrels`'s fill loop. First try, reusing the exact same jitter formula and field-set order as the already-tuned `bB_chooseBombBarrel_dropNewBarrels` (int `*10`, direct array indexing, `lbl_3_data_21770[0]`) → 91.89% immediately, no further iteration needed. Remaining diff is register renumbering plus the same rodata literal-pooling artifact (`@304`/`@306` vs `lbl_3_rodata_3500`/`3508`).
### fn_3_12EB10: 71.80% (624/624 bytes, matches target size exactly) — see Prototypes above for the row-shift/compaction algorithm. Iterated twice: (1) direct translation, copying all fields for `k` from `pos+1` to `2` then clearing only `barrels[2].barrelState=0` once after the loop → 60.87%; (2) moved the `barrels[k].barrelState=0` clear to happen inside the loop, once per `k` iteration (redundant for `k<2` since immediately overwritten by the next copy, but matches the target's actual per-step-zero unrolled asm) → 71.80% (kept). Remaining diff is register-allocation/ordering noise in the generic by-4-with-remainder loop unroll MWCC applies to the (at-most-2-iteration, but not compile-time-constant-bounded) inner shift loop; flagged for a future pass rather than continued blind guessing.

## Header changes (Task 0, 2026-09-24)
Done by a prior worker before being cut off; verified complete this session:
- Added `BB_BARREL_STATE` (EMPTY=0/DROPPING=1/NEUTRAL=2/READY_TO_BLOW_UP=3/BLOWN_UP=4) and `BB_BARREL_COLOUR` (RED=0/BLUE=1/YELLOW=2/BROWN=3) enums to `include/game/UnknownHomes_Game.h`, matching the 5-value/4-value evidence gathered during B2 (see `bB_connectingBarrels`/`bB_chooseBombBarrel_dropNewBarrels` log entries above).
- Retyped `BB_barrelStruct::barrelState` and `::barrelColour` from bare `u8` to `E(u8, BB_BARREL_STATE)` / `E(u8, BB_BARREL_COLOUR)` (documentary only, same storage width, confirmed codegen-neutral by this session's full rebuild+diff showing every B1/B2 function's score unchanged from the last B2 log entry).
- Also present in the same uncommitted header diff (NOT part of this file's Task 0, appears to be concurrent `bobomb_derby.c` work by another agent): a `BARREL_BATTER_PITCH_NUM` enum, `bODRelated5`/`bODCharacterHRStreakTracker` reshaping, and an extension of `MiniGameStruct` past the old `0x1D7C` end out to `0x1DF6+` (new fields `isAIControlled`, `portOfAIBeingProcessed`, `ai_wbChargePower_bbSwingFrame`, `_1DEC`/`_1DF0` floats, `_1DF4` (`u8`, "// unsure"), `bODPitchType` at `0x1DF5`). Left this untouched per the "never edit bobomb_derby.c" instruction — but flagging a real conflict found while doing the Step 2 lookup for `bB_checkIfBarrelHitAndCalculateScore` below: the asm proves a 2-byte `sth` at `+0x1DF4`, which overlaps both `_1DF4` and `bODPitchType` as currently declared. See that function's log entry.

## B3 log (2026-09-24, resumed after prior worker cut off mid-batch)
### fn_3_12FFD4: 71.34% (692 target / 680 ours bytes) — checked the asm for a `bl fn_3_12EB10` inside `fn_3_12FFD4`'s body: there is none (confirmed by grepping the function's disassembly range 0x12FFD4-0x131540(...wait 0x1302A8 end) for `bl `/`blr`; only calls present are `bB_chooseBombBarrel_dropNewBarrels` and two `SetGameStatus`). Target genuinely inlines the whole `fn_3_12EB10` row-compaction body here (same structural pattern as `fn_3_1323CC` inlining `fn_3_12F9D4` in B1) — so the existing hand-copied body is correct and a plain `fn_3_12EB10();` call was NOT tried/kept (it would not match; there's no `bl` to reproduce). After it: resets `bB_bombBarrelID=-1`, calls `bB_chooseBombBarrel_dropNewBarrels()`, then `SetGameStatus(g_Minigame.pointsTargetReachedInd==0 ? GAME_STATUS_DEFAULT : GAME_STATUS_TRANSITION)`. Remaining diff is the same register-allocation/loop-unroll noise already flagged for `fn_3_12EB10` (71.80%) in its own inlined copy of this identical body — not re-attempted here for the same reason (flagged, not blindly re-guessed).
### bB_likelyReplaceBlownUpBarrels: 76.48% (744 target / 680 ours bytes) — checked the asm: no `bl fn_3_12EE68` anywhere in the function body (only `bl fn_8004C108` x2 and `bl callSfx` x2). Confirms the `next`-pointer block is a genuine inlined copy of `fn_3_12EE68`'s logic (plus the two extra guard conditions `next->barrelState != BB_BARREL_STATE_BLOWN_UP` and `next->replacingBarrelInd == 0` that `fn_3_12EE68` itself doesn't have, since here the barrel may already be bouncing) — a plain `fn_3_12EE68(barrelIndex)` call form was not tried/kept since there is no `bl` to reproduce and the extra guards aren't present in `fn_3_12EE68`'s own signature. Not modified further this pass; remaining 76.48% diff not investigated (out of task scope for this quick check).
### bB_checkIfBarrelHitAndCalculateScore: 62.14% (944 target / 956 ours bytes) — reformatted the four nested un-indented outer `if`s (framesSinceHit>0 / scoreCalculatedInd==0 / z-coordinate gate / contactType gate) to proper nested indentation; rebuilt and confirmed the score is unchanged (62.1441% before and after, floating-point-display-only difference). Looked up MiniGameStruct offset `0x1DF4`: Ghidra's own struct dump (`.ghidra_cache/in_game.types.txt` lines ~19160-19165) calls it `byte starPitchInd?/const_0?` (1 byte) immediately followed by `barrelBatterPitchNum_byte bODPitchType` at `0x1df5` — i.e. Ghidra itself only sees a 1-byte field here, contradicting our own asm which is unambiguous: `sth r4, 0x1df4(r6)` (a 2-byte halfword store) at `.text:0x12F988`. **Found a real conflict in the currently-uncommitted header**: a concurrently-edited (not by this task, appears to be `bobomb_derby.c`-related) hunk in `include/game/UnknownHomes_Game.h` extends `MiniGameStruct` out to `0x1DF6+` and declares `/*0x1DF4*/ u8 _1DF4; // unsure` followed immediately by `/*0x1DF5*/ E(u8, BARREL_BATTER_PITCH_NUM) bODPitchType;` — two 1-byte fields where the real layout needs one 2-byte field. Did NOT touch the header (per the "never edit bobomb_derby.c" instruction and the concurrent-edit risk — this region is actively being shaped by another agent's evidence, and correcting it here without seeing that agent's full picture could introduce a fresh conflict). Left `bB_checkIfBarrelHitAndCalculateScore` writing through the existing raw `*(s16 *)((u8 *)&g_Minigame + 0x1DF4)` cast, which is a correct, width-safe workaround regardless of how the surrounding bytes eventually get named. `lbl_3_common_bss_37400[0x20]` and `lbl_3_data_217A4[5]`: checked all other src users (`ball_physics.c`, `runner.c`, `fielder.c`, `fielder_ai.c`, `bobomb_derby.c`) — every one of them also accesses these via the raw index into the `s16[]`/no-struct form, not a named field (the one real struct definition, in `pitcher.c`, covers a *different* byte range — its named `scoutMissionID`/`scoutCountdown`/`scoutFlag` fields sit at byte offsets 0x42-0x4C, while index `[0x20]` used here is byte offset 0x40, inside that struct's own leading `_00[0x42]` padding — so it is NOT the same field and must not be renamed to `scoutMissionID`). Left both as raw indices, matching the established idiom.
### bobombDerbyRelated: 100.0% (416/416 bytes) — **matched**, no changes needed. Turn-over/countdown/fade-transition state machine for the minigame's end-of-turn handling; final source already correct as written by the prior worker (see the `Log` sections above this batch for other functions' style — this one has no dedicated log entry from that worker, but the score confirms it needed none).
### fn_3_13119C: 100.0% (240/240 bytes) — **matched**, first try. A `switch(g_GameLogic._125)` (`TRANSITION_CALCULATION_TYPE`) state machine for a scene-change sequence: case 0 → `changeScene(1,6)`, advance to state 1; case 1 → once `FrameCountOfCurrentPitch` clears a threshold (`lbl_3_data_18C48[1]`/`[2]`, gated by `checkForButtonPressToSkip(1,0x1100)` for the earlier threshold) → `changeScene(3,6)`, advance to state 2; case 2 → once `lbl_8037169C[0x13]!=0` → `fn_3_FBD70(); fn_3_FBD58();`, advance to state 3; case 3 → `SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY)`. This is **byte-for-byte identical logic** (down to the exact constants and helper calls) to `bobomb_derby.c`'s already-100%-matched `fn_3_111F80`; copied that function's structure directly (same `lbl_3_data_18C48`/`lbl_8037169C`/`fn_3_FBD70`/`fn_3_FBD58`/`checkForButtonPressToSkip` externs, all newly added to barrel_batter.c's top-of-file block, plus `#include "Unknown/File_0x800204cc.h"` for `changeScene`'s correct `(u8, u16)` prototype instead of guessing one).
### fn_3_131EC4: 96.67% (312 target / 312 ours bytes) — a `switch(g_GameLogic._125)` state machine that begins a batter's turn: case 0 → `rosterID = minigameControlStruct[0].aIStrength[turnNumberWithinRound+4]` (same out-of-declared-bounds `aIStrength[]` indexing idiom already established and named in `bobomb_derby.c:361`), `pre_PostMiniGameInd=1`, `miniGameTurnCounter=0`, `pointsTargetReachedInd=0`, then picks `bB_pitchesRemainingInTurn` from `cost_15_bB_pitchesPerRound_solo[soloMinigameDifficulty]` (solo) or `[4]` (multiplayer, new extern `u8 cost_15_bB_pitchesPerRound_solo[12]`), resets ball/pitcher/batter state (`resetBallValuesBetweenBatters`, `resetPitcherValuesBetweenBatters(0)`, `setPitcherStatsToInMemPitcher(-1)`, `setBatterContactConstants`, `setInMemBatterConstants(rosterID)`, `highLevelSimulationFlag[2]=0`), advances to state 1; case 1 → once `someAnimationIndFunction()!=0` → `us80893314[1]=1`, advance to state 2; default (>1) → `animRelated[0xB6]=1; SetGameStatus(GAME_STATUS_DEFAULT)`. Nearly identical in shape to `bobomb_derby.c`'s 100%-matched `fn_3_112450` (that one lacks the solo/multiplayer pitch-count branch and has one extra `bOD_HRStreak=0` field reset instead). Iterated 3 times on statement order for the 4 leading assignments in case 0 only (this is the only part with any diff — everything else matched immediately): (1) `pre_PostMiniGameInd=1; rosterID=...; miniGameTurnCounter=0; pointsTargetReachedInd=0;` (bobomb_derby's literal order) → 96.35% (2 arg-mismatches + 1 replace + 1 insert/delete pair, all in the `pre_PostMiniGameInd` store's scheduling position); (2) moved `rosterID=...` before `pre_PostMiniGameInd=1` → 96.67% (best, kept — reduced to 1 replace + 1 insert/delete pair); (3) moved `pre_PostMiniGameInd=1` to last of the four (after `pointsTargetReachedInd=0`) → 96.22% (worse, reverted back to (2)). Remaining diff at 96.67% is purely the scheduling position of a single `li r3,0x0`/`stb r4,0x12b(r31)` pair (target computes the constant-0 for the later `miniGameTurnCounter`/`pointsTargetReachedInd` stores earlier than it schedules the `pre_PostMiniGameInd=1` store; ours does the reverse) — did not find a 4th statement-order variant worth trying within budget; flagging rather than continuing to guess.
### fn_3_131FFC: 100.0% (128/128 bytes) — **matched**. End-of-round transition: `g_Scores.Inning++`, `g_Minigame.turnNumberWithinRound=0`; if solo (`multiPlayerInd==0`) → `SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY)` and return immediately; else `fn_3_10F550(4,0)`, then if `g_Scores.Inning==1` → `fn_3_10AD48()`, then `SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY)`. Similar to `bobomb_derby.c`'s `fn_3_112558` but with a different statement order in the multiplayer branch (target here calls `fn_3_10F550` *before* the `Inning==1` check and the final `SetGameStatus`, whereas `fn_3_112558` calls `SetGameStatus` then `fn_3_10F550` last) — matched the asm's actual call order directly rather than copying `fn_3_112558`'s order verbatim. First try, no iteration needed.

## Work order status
B1, B2, and B3 are now all complete. Batch B2 functions moved from 0.5-1.5% baseline stubs to 71.8%-100% (one newly matched: `fn_3_12FD6C`). B3 functions (`bB_likelyReplaceBlownUpBarrels`, `bB_checkIfBarrelHitAndCalculateScore`, `fn_3_12FFD4`, `bobombDerbyRelated` implemented by a prior worker and measured for the first time this session; `fn_3_13119C`, `fn_3_131EC4`, `fn_3_131FFC` newly implemented this session) now stand at: `bB_likelyReplaceBlownUpBarrels` 76.48%, `bB_checkIfBarrelHitAndCalculateScore` 62.14%, `fn_3_12FFD4` 71.34%, `bobombDerbyRelated` **100.0% (matched)**, `fn_3_13119C` **100.0% (matched)**, `fn_3_131EC4` 96.67%, `fn_3_131FFC` **100.0% (matched)**. B4 (`fn_3_131C88`, `fn_3_12FAC4`, `barrelBatterLiveBallSubFun`, `fn_3_1307D0`, `fn_3_1312D4`) is next and still fully at baseline stub scores. Section totals after this session: `.text` 35.18% (was 31.50% at session start, 0.67% at unit start), `.rodata` unchanged at 86.67%, `.data` unchanged at 0.0%. No B1/B2 function regressed (re-verified via full-unit diff after every change).

## Verified state at session end (2026-09-28, objdiff-cli)

Both orchestrator sessions stopped on API usage limits / stream stalls; this table supersedes the one above where they differ.

| function | status | pct |
|---|---|---|
| bB_chooseBombBarrel_dropNewBarrels | pending | 94.05% |
| fn_3_12EB10 | pending | 71.8% |
| fn_3_12ED80 | pending | 99.84% |
| fn_3_12EE68 | pending | 88.77% |
| bB_likelyReplaceBlownUpBarrels | pending | 76.48% |
| fn_3_12F28C | pending | 83.62% |
| bB_connectingBarrels | pending | 78.99% |
| bB_checkIfBarrelHitAndCalculateScore | pending | 62.14% |
| fn_3_12F9D4 | pending | 84.03% |
| fn_3_12FAC4 | pending | 87.98% |
| fn_3_12FD6C | matched | 100.0% |
| fn_3_12FE84 | pending | 91.89% |
| fn_3_12FFD4 | pending | 71.34% |
| barrelBatterLiveBallSubFun | stub | 0.3% |
| fn_3_1307D0 | stub | 0.58% |
| fn_3_130A80 | matched | 100.0% |
| bobombDerbyRelated | matched | 100.0% |
| bB_AtBat | stub | 0.34% |
| fn_3_131114 | matched | 100.0% |
| fn_3_13119C | matched | 100.0% |
| fn_3_13128C | matched | 100.0% |
| fn_3_1312D4 | stub | 0.65% |
| barrelBatterTransitionToMainFunction | stub | 0.21% |
| fn_3_131C88 | pending | 97.03% |
| fn_3_131EC4 | pending | 96.67% |
| fn_3_131FFC | matched | 100.0% |
| fn_3_13207C | matched | 100.0% |
| bB_LoadGame | stub | 0.51% |
| fn_3_1323CC | pending | 62.37% |
| barrelBatterSwitcher | stub | 0.16% |

8/30 at 100%, 7 stubs left.

## B4/B5 log (2026-09-30, match-sonnet first-pass resume)

Baseline re-measured via `report.json` at session start (objdiff-cli, after a
fresh `ninja`); differs slightly from the 2026-09-28 "Verified state" table
(different objdiff/build state, not a regression — e.g. `fn_3_12EB10` 74.1%
vs 71.8% logged, `fn_3_1323CC` 63.56% vs 62.37%). This session's own
before/after numbers below use this fresh baseline.

Drafted 4 of the 7 remaining stubs this session, all from the target asm
(`build/GYQE01/game/asm/game/minigame/barrel_batter.s`), smallest first:

### fn_3_1312D4: 0.65% -> 94.9% (matched)
Asm is `bl fn_3_DE4FC(); bl SetGameStatus(0xe); <fn_3_12FE84's body inlined>;
<fn_3_12FD6C's body inlined>` — no `bl` to either sibling anywhere in this
function. `0xe` = `GAME_STATUS_MVP_END_GAME`, confirmed by
`bobomb_derby.c:fn_3_112070` which has the exact same
`fn_3_DE4FC(); SetGameStatus(GAME_STATUS_MVP_END_GAME);` opening pair (a
shared "start next round" idiom across minigames, not barrel-batter-specific).
Wrote as plain calls `fn_3_12FE84(); fn_3_12FD6C();` (both already 100%-
matched standalone) and `-inline auto` reproduced the target exactly —
confirms the "try a plain call first, let it auto-inline" lesson from
`fn_3_12F28C`/`fn_3_12EE68` generalizes to whole-function-body reuse, not
just small leaf helpers.

### fn_3_1307D0: 0.58% -> 88.11% (pending)
Asm is `bl ballPhysica(); bl bB_checkIfBarrelHitAndCalculateScore(); <15-barrel
loop identical to fn_3_12FAC4's>; bl barrelBatterLiveBallSubFun();` — again no
`bl fn_3_12FAC4` anywhere (confirmed: grepped the whole unit's asm for `bl
fn_3_12FAC4`/`fn_3_12F9D4`/`fn_3_12F28C`, zero hits in the entire TU — these
three are never called via `bl` from inside this file, only ever inlined
duplicates; they must be called via function pointer from outside the file,
e.g. a minigame tick-function vtable). Wrote as
`ballPhysica(); fn_3_12FAC4(); barrelBatterLiveBallSubFun();` — inherits
`fn_3_12FAC4`'s own 88.56% residual mismatch (same registers/pooling noise),
nothing new introduced by this function itself. `next:` grind
`fn_3_12FAC4` first (shared block affects this function and `bB_AtBat` too);
this one should follow for free or near-free once that's fixed.

### bB_AtBat: 0.34% -> 89.46% (pending)
Largest/most structurally rich of the four. Two top-level
`if (g_Minigame.turnOverStatus == 0)` blocks (confirmed genuinely separate in
the asm, not one if/else: the asm re-tests `turnOverStatus==0` a second time
immediately after the first block instead of simply falling through, so a
human-written if/else would miss this redundant re-test — kept it as two
separate top-level `if`s to match): block 1 is the "paused?/gameplay tick"
body (`checkForPauses()`; conditional `atBat_Pitcher()`; `bB_AI()`;
`atBat_batter()`; `isAIControlled[0..3]=0` via a real `for` loop — this one
*does* have loop-control instructions in the asm, unlike the other unrolled
field-reset blocks in this batch; `running_MainFunction()`; then the same
inlined `fn_3_12FAC4` body as above, written as a call). Block 2 handles the
`pitcherActionState==PITCHER_ACTION_STATE_NO_CONTACT` transition into
`turnOverStatus=1`. The function's tail (reached whenever `turnOverStatus!=0`)
is **structurally identical** to `bobombDerbyRelated`'s entire `else` branch —
same fields in the same order (`CountdownUntilFade`, `pointsTargetReachedInd`,
the `multiPlayerInd==0 || (...)` short-circuit condition, the
`_1A37==0 && CountdownUntilFade==1` sound-effect gate, even the same
`sndFXStartEx(0x1be, lbl_800EFBA4[7], 0x3f, 0)` call) — copied that shape
directly rather than re-deriving it. New field evidence: `0x190B`=
`turnOverStatus`, `0x1912`=`pointsTargetReachedInd`, `0x1A2D`=
`miniGameTurnCounter`, `0x1A2E`=`bB_pitchesRemainingInTurn`, `0x18A2`=
`bB_bombBarrelHitInd`, `0x18A4`=`bB_bombBarrelID`, `0x1DBC`=`isAIControlled[4]`
(all already in the header from prior work — no new fields needed). New
local externs: `checkForPauses` (`config/GYQE01/game/symbols.txt:1743`,
engine-wide, not declared anywhere in the repo yet), `bB_AI`
(`symbols.txt:1965`, `.text:0x12DB80` — just before this file's own `.text`
range, so plausibly defined in whatever TU precedes this one). `next:` same
shared `fn_3_12FAC4` block as `fn_3_1307D0` above; once that's resolved,
re-check both callers for free wins before grinding anything specific to
`bB_AtBat` itself.

### bB_LoadGame: 0.51% -> 89.05% (pending)
`if (g_GameLogic._125 != TRANSITION_CALCULATION_TYPE_0) { SetGameStatus(
GAME_STATUS_GAME_START_MOVIE); return; }` guards the whole body. Then a large
straight-line (no loop control instructions at all — fully unrolled in the
target) reset of 4 "per-player" field groups
(`miniGameCurrentPoints`/`miniGameLatestPoints`/two still-unnamed halfword
pairs at `0x18BC+4p`/`0x18BE+4p` that overlap the header's existing
`s32 minigamePoints_current_Latest[4]`/`minigameFielderIndex`/`_18FC`/one
more still-unnamed byte at `0x18F4+p`/one still-unnamed byte at `0x18F0+p`),
written with raw `*((u8/s16 *)&g_Minigame + 0xNNN)` casts for the
not-yet-named pieces per the project's established idiom (same pattern as
the existing `*(s16 *)((u8 *)&g_Minigame + 0x1DF4)` in
`bB_checkIfBarrelHitAndCalculateScore`), rather than guessing a struct shape.
**Flagging for the header owner**: `minigamePoints_current_Latest[4]` (s32)
is zeroed in the target via *two* `sth` stores per element (low/high half
separately) rather than one `stw`, which strongly suggests each element is
really a packed `{s16 current; s16 latest;}` pair, not a plain `s32` — did
not retype the shared header field myself (out of scope for a single-file
first pass), left the raw-cast workaround in place and noted it here so a
grind pass (or whoever owns that struct) can decide. Also found and used a
clean enum hit: target stores literal `5` into `g_GameLogic.secondaryGameMode`
(not `_121` — that name collision was from a *different* struct earlier in
the same header file, a RunnerStruct-shaped one, caught by the compiler
erroring "not a struct/union/class member" when I grepped the wrong `_121`);
`5` = `SECONDARY_GAME_MODE_BARREL_BATTER`, an exact, obviously-correct match,
so used the enum directly in the initial draft rather than waiting for the
readability pass. Solo-vs-multiplayer branch reuses
`g_Minigame.minigameControlStruct[0].aIStrength[0..3]` (already a named
array field — offsets lined up cleanly, no raw casts needed there) and two
new small data arrays: `lbl_3_data_2127C[0x28]` (byte table indexed
`GameMode_MiniGame*5 + soloMinigameDifficulty`, and also directly at `[0x23]`
for a fixed multiplayer case) and `bB_challengePointsRequired[4]` (s16,
`.data:0x21790`, right after the already-known `lbl_3_data_21788`). Ends by
calling `fn_3_12FE84()` (again inlined, no `bl`, consistent with every other
`fn_3_12FE84`/`fn_3_12FAC4`-body reuse found this session) then resetting
`turnNumberWithinRound`/`barrelBatter_scoreCalculatedInd`/
`barrelBatterChargeMeter` and advancing `g_GameLogic._125`. `next:` the
`minigamePoints_current_Latest` half-write mismatch above is the most
promising lead; everything else is likely register noise from the long
straight-line store sequence.

Rebuilt and re-diffed the *whole unit* after each of the 4 functions above;
no other function's score moved (confirmed against the fresh baseline).

### Section scores after B4-partial (4/7 stubs drafted)
| section | B3 end | this session |
|---|---|---|
| .text | 41.58 (fresh baseline) | 57.94 |
| .rodata | 86.666664 | 86.666664 (unchanged) |
| .data | 0.0 | 0.0 (unchanged — jumptable lives in `barrelBatterSwitcher`, not yet drafted) |

Still stub (not yet drafted): `barrelBatterLiveBallSubFun`,
`barrelBatterTransitionToMainFunction`, `barrelBatterSwitcher` — these are
next, in that size order. `barrelBatterSwitcher` holds the 27-entry
`.data` jumptable that's currently at 0.0%; drafting its `switch` should
materialize it.

### barrelBatterLiveBallSubFun: 0.3% -> 82.45% (pending)
Per-frame "ball is live" tick: (1) once `g_Ball.framesSinceHit >=
lbl_3_data_217A4[4]`, sets `turnOverStatus=1` and, in the solo
below-difficulty-3 case, checks `miniGameCurrentPoints[rosterID] >=
pointsReqToWin_challenge` to set `pointsTargetReachedInd=2`,
`_1A37=1`, `challenge_minigame_haven_tWonYetIndicator=0`,
`fn_3_10F550(1, lbl_3_data_217A4[10])`; (2) bomb-barrel-hit pitch-count bonus
(`bB_pitchesRemainingInTurn += cost_15_bB_pitchesPerRound_solo[multiPlayerInd+6]`)
and a `pitchesRemainingInTurn==0 -> pointsTargetReachedInd=2` check; (3) early
return if `turnOverStatus==0` (nothing more to do this frame); (4) the same
`CountdownUntilFade`-driven transition shape as `bobombDerbyRelated`/
`bB_AtBat`'s tails, except on expiry it first checks "all barrels settled"
and if so resets the bomb barrel, compacts blown-up barrels, and starts a new
round, then sets `GAME_STATUS_TRANSITION`/`GAME_STATUS_DEFAULT`; (5) the same
`bobombDerbyRelated`-shaped sound-effect tail.

Two inline-vs-call lessons, both confirmed by reading the raw instruction
diff (`objdiff-cli diff -p . -u <unit> -o - --format json <symbol>`, then
comparing `left`/`right` symbol `instructions[]` arrays side by side — much
cheaper than reading the whole unit's asm again):
- `fn_3_12ED80()` written as a plain call **did** get auto-inlined by MWCC
  here (232-byte callee), landing almost exactly where `fn_3_12ED80`'s own
  known 99.84% residual (constant-folded addressing-mode choice, not a real
  mismatch) would predict — confirms a leaf helper this size auto-inlines
  reliably.
- `fn_3_12EB10()` written as a plain call did **not** auto-inline (624-byte
  callee) — it compiled to a real `bl fn_3_12EB10`, while the target inlines
  the whole row-compaction-plus-cap-off body here (no `bl` in the target's
  asm at all). This was the single largest contributor to the 55.6% first
  score (112 missing instructions, `DIFF_DELETE`, in one contiguous block).
  Fixed by hand-copying `fn_3_12EB10`'s current body (same text already used
  in `fn_3_12FFD4`) in place of the call: 55.60% -> 82.45%, no regressions
  elsewhere. **Lesson for future files**: `-inline auto` has a real size
  ceiling somewhere between ~230 and ~625 bytes for this project/MWCC
  version — below it, write a plain call and trust the inliner; at or above
  it, hand-copy the callee's body (checkpoint it as "known inline, not a
  real call" so a reader doesn't mistake the duplication for drift). Treat
  this as the practical cutoff when deciding whether to try a call first or
  go straight to a manual copy on the next stub.
`next:` the remaining ~17.5% is inherited residual noise from `fn_3_12ED80`
(99.84%, known constant-folding difference) and `fn_3_12EB10` (74.1%,
known register-allocation noise in its own unrolled shift loop) propagating
through this inline site, plus whatever's left in the early
`framesSinceHit`/`pointsReqToWin_challenge` block (not yet diffed in
detail). Grinding `fn_3_12EB10`/`fn_3_12ED80` to 100% directly should pay
off here too (and in `fn_3_12FFD4`, which has the same inherited-noise
situation).

### barrelBatterTransitionToMainFunction: 0.21% -> 93.35% (pending)
A `switch (g_GameLogic._125)` state machine (cases 0-3, `default:` empty) for
the post-pitch-result "continue to the next play" transition:
- case 0: `fn_3_12FD6C()` (same reset/mark-dropping body already matched
  elsewhere — auto-inlined cleanly here as a plain call, confirmed by a clean
  instruction-diff region), `turnNumberWithinRound++`,
  `g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0`, `_125++`.
- case 1: `_1A37==1` picks between `lbl_3_data_217A4[3]`/`[2]` as the
  threshold for `FrameCountOfCurrentAtBat_Copy` before advancing `_125`.
- case 2: `changeScene(3, 6); _125++`.
- case 3: guarded by `lbl_8037169C[0x13] != 0`; multiplayer branch picks
  `GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY` vs `GAME_STATUS_MINIGAME_NEW_ROUND`
  (`0x19`, already in the `GAME_STATUS` enum, flagged `// unsure` there but
  used as-is) by `turnNumberWithinRound < miniGameNumberOfParticipants`;
  solo branch is `fn_3_DE4FC(); SetGameStatus(GAME_STATUS_MVP_END_GAME);`
  followed by **both** `fn_3_12FE84` and `fn_3_12FD6C`'s full bodies
  back-to-back — i.e. this is the exact same 4-call sequence as
  `fn_3_1312D4` (`fn_3_DE4FC/SetGameStatus/fn_3_12FE84/fn_3_12FD6C`), just
  reached from a different dispatcher and with no `bl fn_3_1312D4` in sight
  (confirms `fn_3_1312D4` itself is never called from within this file
  either, same "global function used as an external callback" pattern noted
  for `fn_3_12FAC4`/`fn_3_12F9D4`/`fn_3_12F28C`). Both branches converge on
  `fn_3_14CA00(); animRelated[0xB7] = 1;`. After the whole switch
  (unconditionally, all cases and default): `bB_checkIfBarrelHitAndCalculateScore()`
  plus the familiar 15-barrel tick loop (`fn_3_12FAC4`'s body) — hand-copied,
  not called (680 bytes, confirmed too big to auto-inline, consistent with
  the `fn_3_12EB10` finding below).

Two bugs caught and fixed by re-diffing against the raw instruction list
after the first draft (`objdiff-cli diff ... <symbol>`, compare `left`
target vs `right` ours instruction-by-instruction — see
`barrelBatterLiveBallSubFun`'s entry for the technique):
1. **Ternary polarity.** First draft wrote the multiplayer branch as
   `SetGameStatus(cond ? GAME_STATUS_MINIGAME_NEW_ROUND :
   GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY)`. Target's `cmplw`+`bge`
   sequence put `GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY` as the
   straight-line (fallthrough/false) case and the enum as the branch-taken
   (true) case — same semantics, different codegen shape. A ternary compiled
   it backwards (`DIFF_OP_MISMATCH bge` vs `blt`, plus a fully missing
   `li r3,0x19` block, 77.88%). Rewriting as an explicit
   `if (turnNumberWithinRound < miniGameNumberOfParticipants) {A} else {B}`
   (mirroring the comparison's own written order) fixed it: 77.88% -> 79.06%.
   **General lesson, consistent with the `fn_3_13128C` note already in this
   file**: a ternary and the equivalent if/else are not interchangeable for
   matching purposes even though semantically identical — write the if/else
   whose condition matches the asm's compare+branch directly, don't rely on
   the ternary's own codegen to land the same way.
2. **Missed second inline.** First draft only inlined `fn_3_12FE84`'s body
   in the solo branch and omitted the trailing `fn_3_12FD6C` body entirely
   (missed it when transcribing a long, repetitive asm block — the two
   reset-loops back to back look superficially similar). This was the
   dominant remaining gap (~290 raw `DIFF_DELETE` lines, since every
   downstream register number was shifted too): adding
   `fn_3_12FD6C();` right after the hand-copied `fn_3_12FE84` body (plain
   call, auto-inlined cleanly — same callee as case 0's clean inline) fixed
   it: 79.06% -> 93.35%, no regressions. **Lesson**: when a block of asm
   looks like "the same thing happens twice in a row", check whether it's
   actually *two different* known function bodies concatenated (here:
   `fn_3_12FE84` then `fn_3_12FD6C`, exactly `fn_3_1312D4`'s own call
   sequence) rather than one loop repeated — cross-check against any
   sibling function that already does the same sequence (`fn_3_1312D4` was
   sitting right there in this same file).
`next:` remaining ~6.65% is entirely inherited noise: register renumbering
throughout the long inlined reset block, the known whole-TU rodata literal-
pooling issue (`lbl_3_rodata_351C`/`3518`/`3510` vs fresh `@636`/`@637`/`@776`
anonymous constants — same root cause logged under B1/B2 above), and one
inherited real near-miss from `fn_3_12F28C`'s own 84.39% (a `blt`/`bgt`
polarity difference in the `delayUntilBlownUp`/`animationCounter` compare,
inside the hand-copied `fn_3_12FAC4` tail loop) — fixing `fn_3_12F28C`
itself should improve this function too.

### barrelBatterSwitcher: 0.16% -> 94.50% (pending) — last stub, draft + major structural fix
The per-frame dispatcher: `switch (g_GameLogic.gameStatus)` over a 27-entry
jump table (`jumptable_3_data_26510`, the `.data` object this whole
checkpoint has tracked at 0.0% since file start). **Found the exact
case->label mapping with certainty instead of guessing from source
plausibility**, by reading the `.data` section's relocations directly out of
the objdiff JSON (`objdiff-cli diff ... -o - --format json`, then
`left.sections[] where name==".data"].reloc_diff`): each of the 27 four-byte
slots is `R_PPC_ADDR32` with `target_symbol` = `barrelBatterSwitcher` itself
and `addend` = the exact byte offset from the function's start to that
case's target label. This is strictly more reliable than reading label
order out of the `.s` file (see the bug below for why) — **recommended
technique for any REL-unit jump-table switch**, not just this one.

Mapping found (`GAME_STATUS` value -> body, all either a single `bl` to an
existing matched function, or a hand/auto-inlined copy of one):
- 0 `DEFAULT` -> `fn_3_131114()` + `fn_3_12FD6C()` (both plain calls,
  auto-inlined) + a unique tail: resets `_18A0`/`turnOverStatus`/
  `barrelBatter_scoreCalculatedInd`/`barrelBatter_hitBarrelID`/
  `barrelBatter_barrelsHit`/`bB_bombBarrelHitInd`/`g_Ball.totalFramesAtPlay`/
  `g_Ball.framesSinceHit`/two still-raw `g_Batter` offsets (`0x66`,`0x8D`,
  same raw-cast idiom as `fn_3_131C88`)/`g_Pitcher.windupCountdownUntilBallReleased`,
  then the `pre_PostMiniGameInd`-gated `minigameLastTurnSuccessInd`/
  `hudElementLoadingInd` branch, `changeScene(1,6)`,
  `SetGameStatus(GAME_STATUS_AT_BAT)`. Same *set* of operations as
  `fn_3_131C88` (itself still only 97.17%) but a **different field-write
  order** than `fn_3_131C88`'s current source — written here to match this
  call site's own asm exactly rather than copied from the sibling; flagging
  for the Opus pass in case `fn_3_131C88`'s own order is the thing that's
  actually wrong over there.
- 1 `AT_BAT` -> `bB_AtBat()` (real `bl`, too large to inline — 1176 bytes).
- 2 `LIVE_BALL` -> `ballPhysica(); fn_3_12FAC4(); barrelBatterLiveBallSubFun();`
  (`fn_3_1307D0`'s exact body — no `bl fn_3_1307D0` in the target at all,
  confirming `fn_3_1307D0` is a separate top-level duplicate, not a callee
  of this switch).
- 3 `INNING_TRANSITION` -> `fn_3_13119C()` (plain call, auto-inlined).
- 4 `LOAD_GAME` -> `bB_LoadGame()` (real `bl`, 784 bytes).
- 5 `GAME_START_MOVIE` -> no-op.
- 6 `TRANSITION_TO_MINIGAME_START` -> `fn_3_131FFC()` (plain call, auto-inlined).
- 7 `TRANSITION_PREPARE_NEXT_PLAY` -> `fn_3_131EC4()` (plain call, auto-inlined
  despite being 312 bytes — pushes the known "auto-inlines" ceiling evidence
  from this file up slightly from the previous ~280-byte data point).
- 8 `TRANSITION` -> `barrelBatterTransitionToMainFunction()` (real `bl`, 1864 bytes).
- 9, 0xA, `PAUSED`, 0xC, `HOW_TO_PLAY_SCREEN`, `MVP_END_GAME` -> no-op.
- 15 `TRANSITION_MINIGAME_POSTGAME` -> `fn_3_DE4FC(); SetGameStatus(GAME_STATUS_MVP_END_GAME);`
  + hand-copied `fn_3_12FE84` body + `fn_3_12FD6C()` call — i.e.
  `fn_3_1312D4`'s exact body a *third* time in this file (see
  `barrelBatterTransitionToMainFunction`'s case 3 for the second).
- 0x10-0x12, `HOMERUN_END`, `HOMERUN_LAP`, `BATTER_CELEBRATION`,
  `STAR_CHANCE_VS`, `CHAMPIONSHIP`, 0x18 -> no-op (9 consecutive).
- 25 `MINIGAME_NEW_ROUND` -> `fn_3_13128C()` (plain call, auto-inlined).
- 26 `TRANSITION_MINIGAME_TO_BATTING` -> `fn_3_13207C()` (plain call, auto-inlined).

**The one real bug, and the session's biggest single finding**: first draft
wrote the `switch`'s cases in `GAME_STATUS` numeric order (0,1,2,3,4,...) and
scored only 58.38%, with ~100 contiguous `DIFF_DELETE`/mismatch instructions
starting almost immediately after the `bctr` dispatch. Diffing side-by-side
showed our instruction at that position was case 0's body, but target's was
case 4's (`bl bB_LoadGame`) — **MWCC emits a jump-table switch's case bodies
in the order they're *written in the source*, not in case-value order**; the
jump table itself still dispatches correctly by value regardless. The
target's actual physical body order (recovered from the labels each
`.data` addend points to) is: 4, 26, 6, 7, 0, 1, 2, 8, 25, 3, 15 (the no-op
cases contribute no code and can go anywhere). Reordering the `switch`'s
case labels in the C source to match this exact sequence — value-correctness
is untouched since C `switch` doesn't care about case order, only MWCC's
*code layout* does — jumped the score from 58.38% to 94.50% in one change,
with the `.text` section rising from 81.98% to 87.13% unit-wide. **This is
the single most important lesson from this whole session for any future
jump-table switch in this codebase**: never assume source case order matches
enum/value order; recover the *real* order from the target's own jump-table
relocations (per the `.data` note above) before writing the switch, or
expect exactly this failure mode and its very expensive-looking but
single-root-cause symptom (a huge wall of seemingly-unrelated `DIFF_DELETE`).

`next:` remaining 5.5% is: one small statement-order diff inherited from
`fn_3_131EC4`'s own 96.67% (same `pre_PostMiniGameInd`-store scheduling note
already logged under that function, now showing up again here since it
auto-inlined), one inherited `blt`/`bgt` polarity near-miss from
`fn_3_12F28C`'s 84.39% (same as `barrelBatterTransitionToMainFunction`
above), register renumbering throughout the long inlined barrel-reset loops,
and the known whole-TU rodata pooling issue. No case-body logic errors
remain that weren't already inherited from a still-pending sibling.

## Session summary (2026-09-30/10-01, match-sonnet first-pass completion)

All 7 remaining stubs drafted this session; **0 stubs left, 8/30 matched,
22/30 pending** (handed to the Opus `match` pass). No function was left
below its pre-session baseline — re-verified via full-unit rebuild+diff
after every single edit in this session, not just at the end.

### Final status table (verified via `build/GYQE01/report.json` after a
clean `ninja`, 2026-10-01)
| function | status | before (session start) | after (session end) |
|---|---|---|---|
| bB_chooseBombBarrel_dropNewBarrels | pending | 94.13 | 94.13 (untouched) |
| fn_3_12EB10 | pending | 74.1 | 74.1 (untouched) |
| fn_3_12ED80 | pending | 99.84 | 99.84 (untouched) |
| fn_3_12EE68 | pending | 89.03 | 89.03 (untouched) |
| bB_likelyReplaceBlownUpBarrels | pending | 77.32 | 77.32 (untouched) |
| fn_3_12F28C | pending | 84.39 | 84.39 (untouched) |
| bB_connectingBarrels | pending | 79.5 | 79.5 (untouched) |
| bB_checkIfBarrelHitAndCalculateScore | pending | 62.25 | 62.25 (untouched) |
| fn_3_12F9D4 | pending | 84.37 | 84.37 (untouched) |
| fn_3_12FAC4 | pending | 88.56 | 88.56 (untouched) |
| fn_3_12FD6C | **matched** | 100.0 | 100.0 |
| fn_3_12FE84 | pending | 92.61 | 92.61 (untouched) |
| fn_3_12FFD4 | pending | 73.42 | 73.42 (untouched) |
| barrelBatterLiveBallSubFun | pending | 0.3 (stub) | **82.45** |
| fn_3_1307D0 | pending | 0.58 (stub) | **88.69** |
| fn_3_130A80 | **matched** | 100.0 | 100.0 |
| bobombDerbyRelated | **matched** | 100.0 | 100.0 |
| bB_AtBat | pending | 0.34 (stub) | **89.46** |
| fn_3_131114 | **matched** | 100.0 | 100.0 |
| fn_3_13119C | **matched** | 100.0 | 100.0 |
| fn_3_13128C | **matched** | 100.0 | 100.0 |
| fn_3_1312D4 | pending | 0.65 (stub) | **94.90** |
| barrelBatterTransitionToMainFunction | pending | 0.21 (stub) | **93.35** |
| fn_3_131C88 | pending | 97.17 | 97.17 (untouched) |
| fn_3_131EC4 | pending | 96.67 | 96.67 (untouched) |
| fn_3_131FFC | **matched** | 100.0 | 100.0 |
| fn_3_13207C | **matched** | 100.0 | 100.0 |
| bB_LoadGame | pending | 0.51 (stub) | **89.05** |
| fn_3_1323CC | pending | 63.56 | 63.56 (untouched) |
| barrelBatterSwitcher | pending | 0.16 (stub) | **94.50** |

### Section scores
| section | session start | session end |
|---|---|---|
| .text | 41.58 | **87.13** |
| .rodata | 86.67 | 80.0 (pooling side-effect, see note above; no function regressed) |
| .data | 0.0 | 0.0 (tied to `.text` exactness, see note above) |

No readability pass was due this session: no function newly reached 100%
(the mandatory pass only triggers on a fresh 100%, and the 8 `matched` rows
above were already 100% and untouched before this session started).

### Recommended order for the Opus `match` pass
Roughly closest-to-100%-first, grouped by what's likely to move together:
1. **`fn_3_12ED80` (99.84%)** — single remaining issue is a documented
   constant-folding/addressing-mode choice (see its own log entry); worth
   one more look since it's the "it's used in the biggest way" leaf.
2. **`fn_3_131C88` (97.17%) / `fn_3_131EC4` (96.67%)** — both have a single
   isolated statement-order near-miss already diagnosed (see their log
   entries and `barrelBatterSwitcher`'s case-0 note above, which found a
   *different* field order at a second call site worth comparing against).
3. **`barrelBatterSwitcher` (94.50%) / `fn_3_1312D4` (94.90%) /
   `barrelBatterTransitionToMainFunction` (93.35%)** — all three share the
   same two inherited root causes (`fn_3_12F28C`'s `blt`/`bgt` polarity,
   `fn_3_12ED80`'s addressing mode), so fixing those two leaf functions
   first should lift all three at once without touching them directly.
4. **`fn_3_12F28C` (84.39%) / `fn_3_12EE68` (89.03%) /
   `bB_connectingBarrels` (79.5%) / `bB_likelyReplaceBlownUpBarrels`
   (77.32%) / `fn_3_12EB10` (74.1%)** — the "second tier" leaves with their
   own open hypotheses already logged (stack-frame-size mystery for
   `bB_connectingBarrels`, unrolled-loop register noise for `fn_3_12EB10`).
5. **`bB_LoadGame` (89.05%)** — the flagged `minigamePoints_current_Latest`
   packed-field-vs-s32 question (see its own entry) is the most promising
   single lead; worth checking against the header owner/other TUs that use
   the same field before guessing a retype.
6. **`bB_checkIfBarrelHitAndCalculateScore` (62.25%)** and **`fn_3_12FFD4`
   (73.42%)** — both still have the bulk of their own gap undiagnosed in
   detail (only spot-checked this session/previous sessions); likely need a
   fresh hypothesis-log pass rather than inherited-fix-dependent.
7. Everything else (`bB_AtBat`, `fn_3_1307D0`, `barrelBatterLiveBallSubFun`,
   `fn_3_1323CC`, `bB_chooseBombBarrel_dropNewBarrels`, `fn_3_12F9D4`,
   `fn_3_12FAC4`, `fn_3_12FE84`) — all first-pass drafts/long-standing
   pendings whose remaining gaps are overwhelmingly inherited noise from the
   functions above; should move for free or near-free once tiers 1-4 land.

### Open questions / proposals (none applied, flagging only)
- `g_UnkSimulation_31AC0` (`.bss`, size 0xC) still only has 2 of 12 bytes
  evidenced (`_05`,`_06`); untouched this session.
- `BB_barrelStruct::barrelState`/`barrelColour` enum values now have 5/4
  confirmed members each (`BB_BARREL_STATE`/`BB_BARREL_COLOUR`, already in
  `UnknownHomes_Game.h` from a prior session) — no new values seen.
- `minigamePoints_current_Latest[4]` (s32, `UnknownHomes_Game.h`) — new
  evidence this session (`bB_LoadGame`) that it's zeroed via two separate
  `sth` stores (low/high half) rather than one `stw`, suggesting a packed
  `{s16 current; s16 latest;}` pair rather than a plain `s32`. Not retyped
  (shared header, out of this pass's scope) — flagged for whoever owns that
  struct or the Opus pass.
- No new CHAR_ID/enum-shaped literals were left un-named this session beyond
  what's already flagged above (`g_GameLogic.secondaryGameMode` *was* named
  via `SECONDARY_GAME_MODE_BARREL_BATTER`, high confidence, see
  `bB_LoadGame`'s entry).
- No file rename/reorganization considered — `barrel_batter.c` already has
  a clear, correct name and theme (confirmed by this session's own reading
  of its entire contents).
- No symbol labeling/correction proposals this session (no function newly
  reached `matched`, which is `match.md`'s precondition for that work).

**Checkpoint is current as of this edit.** Next resumed session (Opus
`match`) should start at the "Recommended order" list above, first function
`fn_3_12ED80`.

## Opus match pass (2026-10-01) — current status is in THIS section (older tables above are history)
Baseline at start (objdiff-cli diff, fresh build): same as session-summary table except
barrelBatterLiveBallSubFun 81.16, fn_3_1307D0 88.12, bB_AtBat 88.86, fn_3_1312D4 94.34,
barrelBatterTransitionToMainFunction 92.94, fn_3_131C88 97.03, bB_LoadGame 88.71, barrelBatterSwitcher 94.20.

### fn_3_12ED80: 99.84 -> 100 (matched)
  [O1] `for (i = 1; i < 15; i += 3) { if (barrels[i].r) return FALSE; if (barrels[i + 1].r) return FALSE; } return TRUE;`
       -> 100%. (`for(i=0;i<5;i++) barrels[i*3+1]/[i*3+2]` gave identical 99.84 to the pointer form.)
       Also lifted barrelBatterLiveBallSubFun 81.16->81.25 (inlines it). readability pass: done (FALSE/TRUE).

### fn_3_131C88: 97.03 -> 100 (matched); barrelBatterSwitcher 94.20 -> 94.51
  Finding: barrelBatterSwitcher's case GAME_STATUS_DEFAULT body IS fn_3_131C88 inlined (same store order).
  [O1] copy switcher case-0 store order into fn_3_131C88 (_18A0, turnOverStatus, scoreCalc, hitBarrelID, barrelsHit,
       bombBarrelHitInd, ..., swingInd(0x8D) before framesSinceStartOfSwing(0x66)) -> 98.63 (kept)
  [O2] HEADER: MiniGameStruct.barrelBatter_hitBarrelID u8 -> s8 (target shares `li r0,-1` with framesSinceHit=-1;
       -1 is a "no barrel" sentinel; bB_checkIfBarrelHit already read it via (s8) cast) -> 100 (kept).
       Also bB_checkIfBarrelHitAndCalculateScore 62.14->62.21, switcher 94.20->94.51. Field only referenced in this TU.
  [O3] switcher case 0 now just `fn_3_131C88();` (auto-inlines, identical score).
  readability pass: done (g_Batter raw 0x8D/0x66 casts -> swingInd/framesSinceStartOfSwing; TRUE/FALSE for
  minigameLastTurnSuccessInd/hudElementLoadingInd/pre_PostMiniGameInd). Left `turnOverStatus`/`scoreCalculatedInd` 0 literal (no enum).

### fn_3_131EC4 (96.67, pending)
  [O1] all 24 permutations of the 4 leading case-0 statements (roster/pre/tc/pt) -> best is current order 96.67
  [O2] pitches-remaining if/else -> ternary -> 92.69 (reverted)
  [O3] chained `pt = tc = 0` -> 96.67 identical (reverted)
  Residual: target schedules `stb pre_PostMiniGameInd` AFTER the two g_Minigame lbz's; ours before. Not a store-order issue.

### fn_3_12EE68: 88.77 -> 100 (matched)  (shared block: inlined into fn_3_12F28C, fn_3_12FAC4 tick loop, many callers)
  [O1] threshold compare uses currentPos.y, not desiredPos.y (target `lfs f3,0x4(r4)`) — real bug -> 90.06 (kept)
  [O2] neighbour-settled flag forms: `u8 f=(A)|(B)` 90.13; `(u8)((u8)A|B)` 89.62; `||` 86.39; if/flag|= 80.49;
       bitfield 77.66; `!(state-2)` ; `(u8)A|(u8)B` 88.86; s8 89.43; static inline bool/BOOL helper (no gain)
  [O3] `u8 f = 0; f |= A; f |= B;` -> 99.87 (kept). The `li rX,0; rlwimi rX,rY,27,5,31; clrlwi` signature = `u8 |= cmp`.
       Lifted fn_3_12F28C 84.6->88.3, fn_3_12FAC4 ->91.6, fn_3_1307D0 ->91.7, bB_AtBat ->90.2, switcher ->95.26.
  [O4] FILE-WIDE: `#define SQRT2_LINKAGE static` at top + function definitions reversed to reverse-address order
       (-inline deferred) -> .rodata 80 -> 100%, fn_3_12EE68 100, and +0.05..0.25 on ~12 others. No regressions.
  readability pass: done (replacingBarrelInd TRUE, flag renamed neighbourSettled with FALSE init).
  Note (not applied): Ghidra names lbl_3_data_21770[3]=const_4_5_barrelHeight, [4]=const_0_2_bounceInitialVelo,
  [5]=const_0_1_bounceVeloAdj; BB_barrelStruct._28 is the landing/rest Y for a replacing barrel.

### fn_3_12F28C: 88.44 -> 100 (matched)
  [O1] `BB_barrelStruct *barrel = &barrels[i]; if (barrel->animationCounter >= barrel->delayUntilBlownUp)` + plain
       `fn_3_12EE68(i)` with NO caller-side `% 3 != 2` guard -> 100 (keeping the guard: 99.02; indexed form w/o guard: 88.66).
       Lifted fn_3_12FAC4 ->94.01, fn_3_1307D0 ->94.08, bB_AtBat ->91.52, TransitionToMain ->94.84, switcher ->95.91.
  readability pass: done (setCharacterAnimations anim arg 0 left literal — no anim enum exists).

### fn_3_12F9D4: 84.03 -> 100 (matched)
  [O1] build the VecXYZ as a field-by-field copy of currentPos, then `pos.y = -pos.y; pos.z -= 1.0f;` -> 100
       (target stores raw y/z first then overwrites). Order y,z,x copy -> 99.25. Same result whether the overwrite
       reads pos.* or barrel->currentPos.*.
### fn_3_12FAC4: 87.98 -> 100 (matched); fn_3_1307D0: 88.12 -> 100 (matched, just calls it)
  [O1] (inherited from fn_3_12EE68/fn_3_12F28C/fn_3_12F9D4 fixes) -> 99.56
  [O2] hoist `BB_barrelStruct *barrel;` declaration ABOVE `int i;` at function top (assign inside loop) -> 100.
       (`int i; BB_barrelStruct *barrel;` order or in-loop declaration: no change.)
  readability pass: done for all three (no enum-shaped literals; 0x7ffe/0x7fff are s16 saturation bounds;
  callSfx 0x2e4/0x2e5 sound IDs have no enum in the repo).

### fn_3_12FE84: 92.01 -> 100 (matched); fn_3_1312D4: 94.37 -> 100 (matched, plain calls)
  [O1] jitter: call random_fn_3_9EE24(0x65) INSIDE the expression (no `rollY` temp):
       `currentPos.y += (i % 3) * 10 - (random_fn_3_9EE24(0x65) * 5) / 100.0;` -> 100.
       (`y = y + (...)` no change; `-(r*5/100.0) + (i%3)*10` 97.38; (f32) cast on whole 97.50)
### barrelBatterTransitionToMainFunction: 92.94 -> 100 (matched)
  [O1] replace hand-copied 15-barrel tick tail with `fn_3_12FAC4();` (it DOES auto-inline now) -> 98.08
  [O2] replace hand-copied solo-branch reset with `fn_3_1312D4();` -> 99.69 (register rotation in inlined loop);
       explicit `fn_3_DE4FC(); SetGameStatus(MVP_END_GAME); fn_3_12FE84(); fn_3_12FD6C();` -> 100 (kept).
  readability pass: done (changeScene / animRelated[0xB7] / _1A37 have no enums/names; left as is).
### barrelBatterSwitcher: 95.31 -> 99.35 (pending)
  [O1] POSTGAME case: hand copy -> `fn_3_1312D4();` (explicit 4-call form scores the same) -> 99.35.
  Only remaining diff = inlined fn_3_131EC4's pre_PostMiniGameInd store scheduling (same as fn_3_131EC4 itself).

### bB_chooseBombBarrel_dropNewBarrels: 94.13 -> 100 (matched)
  [O1] jitter random call inside the expression (same as fn_3_12FE84) -> 98.12
  [O2] count empties directly in `barrelsUntilBomb` (no separate emptyCount local; target keeps the count in r26,
       the same callee-saved reg as the countdown) -> 99.92
  [O3] `for (i = 0, barrelsUntilBomb = 0; i < 15; i++)` (i initialised first) -> 100. (`i=0; b=0; for(;;)` also 100;
       swapping decl order of i/barrelsUntilBomb: no change; moving bombBarrelChosen decl last: 99.21)
  readability pass: done (enum names already used; bombBarrelChosen BOOL TRUE/FALSE).

### bB_likelyReplaceBlownUpBarrels: 76.48 -> 100 (matched)
  [O1] rewrite: guard `next->barrelState != BLOWN_UP && next->replacingBarrelInd == FALSE` then plain
       `fn_3_12EE68(barrelIndex)` (auto-inlined; Ghidra shows the duplicated BLOWN_UP test), `% 3` recomputed inline,
       VecXYZ copy-then-overwrite tail -> 82.05
  [O2] `BB_barrelStruct *next = &g_Minigame.barrels[barrelIndex + 1];` local inside the `% 3 == 1` block -> 93.33
  [O3] tail: `pos.z -= 1.0f;` BEFORE `pos.y = -barrel->_28;` -> 96.31 (pos.y=-pos.y / -currentPos.y: 92.18)
  [O4] prev barrel `[barrelIndex - 1]` must NOT be offset-folded (target: subi; mulli; add base,off; lfs 0x864):
       any cast `(u32)/(s32)(barrelIndex - 1)` -> 99.89; static inline `bB_getBarrel(int)` returning
       `&g_Minigame.barrels[i]` -> 100 (kept; helper now at top of file). `bB_barrelY(int)` float-returning helper 96.31.
  readability pass: done (replacingBarrelInd FALSE/TRUE).

### bB_AtBat: 88.86 -> 97.08 (pending)
  [O1] inherited fixes (fn_3_12FAC4 inline etc.) -> 94.93
  [O2] isAIControlled clear: target is a real (non-unrolled) loop with `extsb`-compared counter -> `s8 i` +
       `i = 0; do { isAIControlled[i] = 0; i++; } while (i < 4);` -> 95.64. (`for` with s8/char/int: unrolled, 94.93;
       `while`/`for(;;)` w/o init: 94.93; `[i++]`: 94.45; ptr walk 96.73 rel. to 97.08 base; value via var/i*0: no change)
  [O3] tail: `turnOverStatus = 2;` BEFORE `CountdownUntilFade = lbl_3_data_217A4[0];` (bobombDerbyRelated order) -> 97.08
       (calling bobombDerbyRelated() for the tail: NOT inlined, 65.13)
  Residual: target keeps &g_Minigame from the AI-clear loop in r25 (callee-saved) and reuses it as the inlined
  fn_3_12FAC4 barrel pointer across the running_MainFunction/bB_checkIfBarrelHit calls (`mr r3,r4` const-0 copy,
  `mr r5,r25`); ours reloads the base after the calls. Not yet reproduced.

### bB_LoadGame: 88.71 -> 98.98 (pending)
  [O1] inherited (fn_3_12FE84 inline fix) -> 92.19
  [O2] guard as `if (_125 == TYPE_0) { body } else { SetGameStatus(GAME_START_MOVIE); }` -> 96.02
  [O3] write the -1 sentinels as s8 (`((s8 *)g_Minigame.minigameFielderIndex)[n] = -1` etc. — target shares one
       `li r4,-1` with rosterID/bombBarrelID; every other TU already reads these fields via (s8) casts) -> 96.61 combined
       (header NOT retyped: other TUs pass e.g. `_18FC[i]` un-cast to functions, retyping would change their codegen)
  [O4] `lbl_3_data_2127C` is `u8 [8][5]` (MINI_GAME_ID x difficulty; target: base + mode*5 then lbzx diff) -> 97.37
  [O5] `s8 value` local (int/u32: no change; s8 table: worse 97.37) -> 98.98
  [O6] tried: loop over the 4 player groups (72.27), inningLimit/value order, row-pointer local, `*(row + diff)`,
       `[0][mode*5+diff]` (96.61), const table — no gain. Residual: 1 instr — target loads soloMinigameDifficulty
       before `addi r0, lbl_3_data_2127C@l`; ours after.
  Note: 0x18F0..0x18F7 raw-cast bytes and the two s16 halves of minigamePoints_current_Latest[] remain raw (layout
  conflict with MiniGameControlStruct[1]; flagged, not resolved).

### Shared block: fn_3_12EB10 (row compaction) — inlined into fn_3_12FFD4, which is inlined into barrelBatterLiveBallSubFun
  fn_3_12EB10 71.80 -> 99.32, fn_3_12FFD4 71.34 -> 98.32, barrelBatterLiveBallSubFun 81.25 -> 99.14 (all pending)
  [O1] for(pos)+`while (state == BLOWN_UP)` (rotated, 67.96); `while(TRUE){ if(!=) break; ...}` 73.86
  [O2] shift body as `static inline void bB_shiftBarrelDown(int i)` (barrels[i-1] = barrels[i] fields; barrels[i]
       state = EMPTY) called `bB_shiftBarrelDown(row * 3 + k)` — defeats strength reduction like target (add+mulli
       per step) -> 83.98. (idx local: no change; ptr src[-1]: 67.44; per-field bB_getBarrel(): 52.31)
  [O3] last-of-row cleanup as `for (row..5) bB_getBarrel(row*3+2)` loop -> 95.67 (5 explicit ifs w/ helper: no
       change; for(i=2;i<15;i+=3): 87.49; local ptr: 95.44); then `u8 *state = &bB_getBarrel(row*3+2)->barrelState`
       -> same for fn_3_12EB10, +0.2 in fn_3_12FFD4 (kept)
  [O4] `for (;;)` instead of `while (TRUE)` (!) -> 99.32. (do{}while(TRUE) / goto-loop same 99.32; while(1) 95.67)
  [O5] fn_3_12FFD4 body = `bombBarrelID = -1; fn_3_12EB10();` (auto-inlines now) + `if (pointsTargetReachedInd != 0)
       TRANSITION else DEFAULT` -> 98.12 (fn_3_12EB10() first then -1: 94.06; ternary 95.36)
  [O6] LiveBallSubFun expiry body = `if (fn_3_12ED80()) fn_3_12FFD4();` -> 98.86; turnOverStatus=2 before
       CountdownUntilFade -> +; fn_3_12ED80 return type `E(u8, BOOL)` (caller does `clrlwi.`; header updated too) -> 99.09;
       bomb-hit / pitches==0 blocks nested inside `framesSinceHit >= thr` block -> 99.14
  Residual (same in all three): target hoists `g + off` and loads `0x890(r9)` for the state check; ours hoists
  `g + off + 0x890` (one extra addi, shifts all regs by one). Tried: volatile load, barrel ptr local, raw byte
  address, extra `||` test, getBarrel() in check, `!(==)`, `(int)` cast, `[pos + row*3]`, src/dst ptrs in helper (64.9).

### fn_3_1323CC: 62.37 -> 100 (matched)
  [O1] now that fn_3_12F9D4 is exact: `u32 i; for (i = 0; i < 15; i++) if (g_Minigame.barrels[i].barrelState ==
       DROPPING) fn_3_12F9D4(i);` -> 100 (auto-inlined). (bB_getBarrel(i) in the test: 88.09; int i: 73.23)
  readability pass: done (no literals left besides the barrel count 15 — no named constant in the repo).

### bB_connectingBarrels: 78.99 -> 100 (matched)
  [O1] static-inline-helper per neighbour: 74.31 AND it made bB_connectingBarrels small enough to auto-inline into
       bB_checkIfBarrelHit (8.6%!) — target keeps 2 real `bl`s. Rejected.
  [O2] four uniform blocks, each `int neighbour = barrelNum ± k;` local + one combined && condition; 4th block
       `barrelNum / 3 < 4` (reuses block 3's division) -> 94.65 (`% 3 != 0` CSE'd with block 1) / 95.74 with
       `barrelNum != (barrelNum / 3) * 3` (then block 3 CSEs the /3)
  [O3] block 2 `(s32)barrelNum % 3 != 0` — the redundant cast blocks CSE with block 1's `% 3`, giving the target's
       fresh `subf.` -> 100. ((u32) 98.62, (s16) 99.14, `+ 0` 94.65)
  readability pass: done (bombBarrelHitInd param -> BOOL in .c and header; test written `|| bombBarrelHitInd`).

### bB_checkIfBarrelHitAndCalculateScore: 62.21 -> 98.88 (pending)
  [O1] full rewrite from target asm: early-return guards; contact check `contactType < RIGHT_NICE || > LEFT_NICE`
       (target: cmplwi 1 / cmplwi 3); row/column searches as `for (row = 0; row < 3; row++) if (y < base[row].y + c)
       break;` and `for (col = 0; col < 15; col += 3) ...` (target is MWCC's unrolled form of exactly these);
       hitBarrelID store BEFORE the flags-clear loop, then barrelID re-read from the (now s8) field; TRUE-branch first
       for the two bB_connectingBarrels calls; points: `hits <= 1 ? c*hits : hits*((hits-1)*c)` as if/else;
       CurrentPoints += before the 0x1DF4 store; `!exhibitionMatchInd && rosterID == bss[0x20]` -> 73.49
  [O2] flags-clear loop counter must be `s32` (long): gives target's un-folded `li r4,0; cmpwi r4,15; bge` guard
       and the hitBarrelID reload -> 96.21 (u8/u16 86.65, s8/s16 89.75, u32 76.06; `counter < 15L` same as s32;
       buggy mssbTypes.h ARRAY_COUNT (divides by element VALUE) 83.61 — do not use that macro)
  [O3] `barrelBatterChargeMeter += barrelsHit - 1;` -> 97.08; x-gate as `!(x < base.x - c)` -> 97.52
  [O4] bB_connectingBarrels `blowUpDelay` param s16 -> int (target passes the int delay with no extsh; callee only
       `sth`s it, still 100) -> 98.67; `s32 counter;` declared first -> 98.88
  Residual: target stores the flags' 0 from the counter's own `li r4,0` register; ours materialises a separate
  `li r0,0`. Tried 0L/(s32)0/0U/counter-counter, flag element types int/s32/u32/BOOL, separate s32 `i` — no gain.

## CURRENT STATUS (Opus pass, 2026-10-01 — authoritative; supersedes all tables above)
| function | status | before (this pass) | pct |
|---|---|---|---|
| bB_chooseBombBarrel_dropNewBarrels | matched | 94.05 | 100 |
| fn_3_12EB10 | pending | 71.80 | 99.32 |
| fn_3_12ED80 | matched | 99.84 | 100 |
| fn_3_12EE68 | matched | 88.77 | 100 |
| bB_likelyReplaceBlownUpBarrels | matched | 76.48 | 100 |
| fn_3_12F28C | matched | 83.62 | 100 |
| bB_connectingBarrels | matched | 78.99 | 100 |
| bB_checkIfBarrelHitAndCalculateScore | pending | 62.14 | 98.88 |
| fn_3_12F9D4 | matched | 84.03 | 100 |
| fn_3_12FAC4 | matched | 87.98 | 100 |
| fn_3_12FD6C | matched | 100 | 100 |
| fn_3_12FE84 | matched | 91.89 | 100 |
| fn_3_12FFD4 | pending | 71.34 | 98.32 |
| barrelBatterLiveBallSubFun | pending | 81.16 | 99.14 |
| fn_3_1307D0 | matched | 88.12 | 100 |
| fn_3_130A80 | matched | 100 | 100 |
| bobombDerbyRelated | matched | 100 | 100 |
| bB_AtBat | pending | 88.86 | 97.08 |
| fn_3_131114 | matched | 100 | 100 |
| fn_3_13119C | matched | 100 | 100 |
| fn_3_13128C | matched | 100 | 100 |
| fn_3_1312D4 | matched | 94.34 | 100 |
| barrelBatterTransitionToMainFunction | matched | 92.94 | 100 |
| fn_3_131C88 | matched | 97.03 | 100 |
| fn_3_131EC4 | matched | 96.67 | 100 |
| fn_3_131FFC | matched | 100 | 100 |
| fn_3_13207C | matched | 100 | 100 |
| bB_LoadGame | pending | 88.71 | 98.98 |
| fn_3_1323CC | matched | 62.37 | 100 |
| barrelBatterSwitcher | matched | 94.20 | 100 |

Sections: .text 87.13 -> 99.55, .rodata 80.0 -> 100, .data 0.0 -> 100 (jumptable now exact). 24/30 matched.

### fn_3_131EC4: 96.67 -> 100 (matched); barrelBatterSwitcher: 99.35 -> 100 (matched)
  [O4] read the batting-order byte as signed: `((s8 *)g_Minigame.minigameControlStruct[0].aIStrength)[turn + 4]`
       -> 100 for both (the switcher inlines fn_3_131EC4). (`(s8)` value cast: no change; `[4 + turn]`, `&_14[turn]`:
       no change.) The bytes at 0x18E0.. are evidently an s8 array (roster order) overlapping the header's
       MiniGameControlStruct layout — header not changed (bobomb_derby.c uses the same u8 idiom at 100%).
  readability pass: done (pre_PostMiniGameInd TRUE; switcher LIVE_BALL case now `fn_3_1307D0();`, same codegen).

### Session-end notes (Opus pass, 2026-10-01)
- mw_version sweep on this unit: GC/1.3.2, 2.5, 2.6 (default), 2.7 byte-identical (plateau); 3.0a3/3.0a5.2 collapse
  (.text 45%). Compiler version is not the lever for the 6 residuals.
- `memset(&g_Minigame._1D7C, 0, sizeof(g_Minigame._1D7C))` is NOT codegen-neutral (fn_3_131114 99.97); keep 0x78.
- Full `ninja` after header edits: 4 files OK. Header changes this pass: MiniGameStruct.barrelBatter_hitBarrelID
  u8 -> s8 (only user is this TU); barrel_batter.h: fn_3_12ED80 returns E(u8, BOOL); bB_connectingBarrels(int, int,
  BOOL) (only caller is this TU).
- Remaining pending, in suggested order for a resume:
  1. fn_3_12EB10 (99.32) / fn_3_12FFD4 (98.32) / barrelBatterLiveBallSubFun (99.14): ONE shared root cause (state
     check address hoisting, see shared-block entry). Fixing fn_3_12EB10 should lift the other two.
  2. bB_checkIfBarrelHitAndCalculateScore (98.88): flags-clear zero register (`stw r4` = counter's own li 0).
  3. bB_LoadGame (98.98): one scheduling slot (difficulty load vs table addi).
  4. bB_AtBat (97.08): AI-clear loop + &g_Minigame kept in r25 across calls (same idiom appears in the still-stub
     bobomb_derby fn_3_111C5C - solve once, apply to both).
- Cross-cutting lessons recorded for docs/matching_notes.md at prune time: (a) `u8 f = 0; f |= (a==b);` signature
  `li rX,0; rlwimi rX,rY,27,5,31; clrlwi`; (b) `for (;;)` vs `while (TRUE)` codegen differs; (c) a static inline
  index helper (`bB_getBarrel(i)`) or a redundant `(s32)` cast blocks offset folding / CSE exactly like the target;
  (d) an `s32` (long) loop counter leaves MWCC's un-folded `li r,0; cmpwi r,N; bge` unroll guard; (e) VecXYZ temp
  built as field-copy then in-place overwrite; (f) a 600+ byte body that "never auto-inlines" may inline once its
  source shrinks (fn_3_12EB10, fn_3_12FAC4) - re-test plain calls after each callee rewrite.

### Cross-file lead from bobomb_derby.c (Opus pass 2026-10-01) -- for bB_AtBat's "&g_Minigame kept in r25" residual
  In bobomb_derby's twin (fn_3_111C5C, 83.40 -> 99.90) the `mr r3,r4` const-0 copy + the clear-loop base being
  kept in a callee-saved reg came from INLINE-HELPER BOUNDARIES, not statement order:
  - AI-clear loops as `s8 i; i = 0; do { isAIControlled[i] = FALSE; i++; } while (i < 4);`
  - the post-atBat_batter clear moved into `static inline void bOD_clearAIControlled(void)` (that loop, once
    inlined, produces target's `li r4,0; mr r3,r4; ... stb r3,0x1dbc(r26); addi r26,r26,1`);
  - the AI block as `static inline void bOD_AI(void)` (first clear loop written directly inside it), with the
    `i == g_Minigame.rosterID` test as `static inline BOOL bOD_isCurrentRoster(s8 i)` -- that alone moved the
    rosterID load onto its own LICM temp and fixed all register numbering.
  Also from bobOmbDerbyBatterAI (58 -> 100): a local `MiniGameStruct *mg = &g_Minigame;` is what keeps
  &g_Minigame in a callee-saved register from prologue to epilogue across calls; loads you want hoisted out of
  loops with a FRESH base must stay direct `g_Minigame.` accesses inside the loop.
  Not tested on bB_AtBat (file not touched by that session).
