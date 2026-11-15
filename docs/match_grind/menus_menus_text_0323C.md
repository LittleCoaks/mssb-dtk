# text_0323C second pass

Current verified state: .text80.51268% (baseline73.60118%). 19/66 matched (15 pre-existing +86EC/6884/B508/C698),42 functions improved; 87A8 exhausted99.30693%,46 pending. All51 initially unmatched functions have assessment/experiment entries, but full-file grind is not complete. Full ninja build and native git diff --check pass. No header/config changes or commits.

Baseline: configured per-unit objdiff, left target / right ours; rebuild succeeded. Source/header saved in text_0323C_second_pass/baseline.c and baseline.h. Full instruction baseline baseline.json.

.text: 73.60118%; no owned .data/.bss/.rodata sections in this split. Compiler GC/2.6 REL flags -O4,p -inline deferred -sdata 0 -sdata2 0. Source is an address-window split; no speculative split/rename.

| Function | Status | Baseline % | Current % |
|---|---|---:|---:|
| cssTransitionToNewScreen_maybe | pending | 87.572914 | 93.114586 |
| fn_2_33BC | pending | 78.34615 | 97.48077 |
| fn_2_348C | pending | 94.25926 | 94.25926 |
| stopShowingCaptainProfile | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_3624 | pending | 62.496357 | 65.49879 |
| fn_2_4970 | pending | 57.669247 | 57.70793 |
| fn_2_5184 | pending | 88.87805 | 95.30488 |
| fn_2_52CC | pending | 86.64893 | 86.64893 |
| teamReady1 | pending | 85.56223 | 87.87983 |
| fn_2_57E8 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_57F0 | pending | 92.78306 | 93.733475 |
| fn_2_5F80 | pending | 65.11429 | 94.14286 |
| fn_2_6098 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_60D4 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_6138 | matched (pre-existing) | 100.0 | 100.0 |
| cssChangeScreens | pending | 90.73514 | 93.437836 |
| cssSelectCPUDifficulty | matched (pre-existing) | 100.0 | 100.0 |
| characterSelectScreenControlable | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_6784 | pending | 85.3125 | 85.3125 |
| fn_2_6884 | matched | 93.24359 | 100.0 |
| fn_2_6AF4 | pending | 91.08219 | 94.79452 |
| cssUnloadScreen | pending | 76.62852 | 76.62852 |
| cssResetRosterStruct | pending | 49.06818 | 86.79735 |
| fn_2_7D44 | matched (pre-existing) | 100.0 | 100.0 |
| cssLoadingScreenRelated | pending | 79.751724 | 92.24138 |
| fn_2_86EC | matched | 91.35135 | 100.0 |
| fn_2_8780 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_8794 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_87A8 | exhausted | 98.11881 | 99.30693 |
| fn_2_893C | matched (pre-existing) | 100.0 | 100.0 |
| copyInfoToInMemRoster | pending | 76.10084 | 98.27311 |
| fn_2_8CF8 | pending | 73.52817 | 77.61268 |
| fn_2_95D8 | pending | 78.52051 | 79.36278 |
| fn_2_9ACC | pending | 85.31313 | 88.88216 |
| fn_2_9F70 | pending | 97.78846 | 97.78846 |
| fn_2_A040 | pending | 91.13636 | 91.64773 |
| fn_2_A1A0 | pending | 89.206894 | 90.155174 |
| fn_2_A288 | pending | 72.527954 | 72.534164 |
| fn_2_A50C | pending | 87.638885 | 98.541664 |
| fn_2_A62C | pending | 91.666664 | 91.666664 |
| fn_2_A6E0 | pending | 49.455128 | 89.42308 |
| fn_2_ABC0 | pending | 69.49505 | 74.19802 |
| fn_2_AEE8 | pending | 81.1107 | 82.52399 |
| fn_2_B324 | pending | 71.79339 | 76.66942 |
| fn_2_B508 | matched | 99.10112 | 100.0 |
| fn_2_B66C | pending | 64.17341 | 80.68786 |
| fn_2_B920 | pending | 65.20388 | 67.10922 |
| challengeSetRoster | pending | 85.43668 | 91.05677 |
| fn_2_C324 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_C484 | pending | 92.06015 | 95.48872 |
| fn_2_C698 | matched | 94.0 | 100.0 |
| fn_2_C7DC | pending | 65.7764 | 76.639755 |
| fn_2_CA60 | pending | 79.27152 | 79.27152 |
| fn_2_CCBC | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_CCE0 | pending | 93.93259 | 93.93259 |
| cssReturnToCapSelect_maybe | pending | 65.29713 | 65.29713 |
| characterSelectAPress | pending | 69.13668 | 75.196655 |
| fn_2_EAE0 | pending | 70.117645 | 73.882355 |
| fn_2_EC34 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_EC54 | matched (pre-existing) | 100.0 | 100.0 |
| characterSelectABDirectionInputs | pending | 41.113075 | 81.96466 |
| randCharBasedOnClass | pending | 76.94203 | 83.18841 |
| randCharacter1 | pending | 76.51128 | 90.86466 |
| randCharAlgo2 | pending | 68.15167 | 82.63239 |
| starHitSetting_Unused_maybe | pending | 74.82269 | 77.758865 |
| characterSelectControls | pending | 71.2016 | 71.67023 |

## Hypothesis log

No prior checkpoint present at session start. Existing drafts audited against actual 66 target functions; 15 are pre-existing 100%. No return-only missing-logic stub except the actual 4-byte target fn_2_893C.

fn_2_33BC
  baseline: 78.34615%
  [1] Target has eight comparisons; draft skipped slot 3. Restored the complete structured slots 1..8 loop -> 97.48077% kept. Target reuses Challenge base as walking pointer; ours retains separate base and walk; investigate byte view.

fn_2_B508
  [1] Explicit u8 cast on charID argument hoists cached byte outside inner loop -> 97.05618%, reverted.
  [2] Correct local addRemoveCharVariantRelated prototype to existing mb_subfunc.h u8/u8/u8 -> 99.77528%, but regresses 8 siblings, reverted. Target calls narrow ABI. Remaining compare operand order and playerNumber load register.

fn_2_9F70
  [1] s32 input with narrow indexing, s32 xor result -> 94.23077%, reverted. Removes extra extsb but loses shared slot base.
  [2] Named s8 port index -> identical 94.23077%, reverted.
  [3] Named slot-table pointer -> 91.92308%, reverted.
  next: target preserves original incoming r3 for return while narrowing index into r0.

fn_2_A62C
  [1] Load val before inner pointer init -> 91.55556%, reverted.
  [2] Inner scan inline helper -> 73.977776%, reverted; introduces local result tests absent in target.
  [3] Explicit outer pointer walk -> 90.55556%, reverted.
  next: target has same operations but swapped value/inner pointer registers; investigate actual cursor struct fields/view. Note target compares signed s8 against 255, so do not silently change this to -1.

fn_2_33BC continued
  [2] Byte view with unsigned offset arithmetic completely folds walk -> 88.32692%, reverted. Signed offset restores same 97.48077%; named struct-index loop preferred.
  [3] Explicit pointer advance after body -> 96.76923%, reverted; before body -> 91.42308%, reverted.
  [4] Named SavedChallengeSlot array pointer -> 96.76923%, reverted.
  [5] Loop 0..8 skipping slot0 -> 45.673077%, reverted.
  next: retained complete structured loop. Exact target pointer progression unresolved.

fn_2_348C / cssLoadingScreenRelated
  [1] u8 flag -> 91.17284%, reverted (adds bit extraction); flag is BOOL/int.
  [2] Target-before-flag declaration order -> 93.950615%, reverted.
  [3] Top-level locals, target-first comparison and named struct fields -> codegen identical 94.25926%; readability retained.
  [4] cssLoadingScreenRelated calls existing fn_2_348C instead of copied body -> 80.4069%, kept; compiler auto-inlines. Target has no bl to fn_2_348C anywhere in menus.
  [5] Inner availability inline helper -> standalone98.27161%, caller80.31207%; reverted because caller regressed its new best. Swapped helper parameters codegen identical.
  [6] Exhaustive 24 local declaration permutations with helper: standalone98.27161/98.51852, caller80.31207/80.34655. All rejected against caller80.4069 floor. Full results decl_sweep.json.
  next: caller still 248 bytes short; do not accept a standalone gain at its expense.

copyInfoToInMemRoster
  baseline76.10084%
  [1] s8 charId local -> identical, reverted.
  [2] Existing CharacterStats copy helper from mb_subfunc/orderchange, typed fields -> codegen identical; retained readability.
  [3] Target tail contains two separate 9-character copy loops rather than draft's manually expanded merged loads. Restored via copyRosterCharacterIDs helper ->80.2437%, kept; no siblings moved.
  [4] Plain static vs static inline helper, while vs for loop -> identical80.2437%; retain static inline for loop.
  next: target tail has redundant initial count guards, absent in ours; source947? current932 bytes vs target952. Target packed FieldingArm extraction is 8 bits versus ours7, indicating a missing/incorrect packed-byte view. Main remaining register allocation is outer/inner loop live ranges.

fn_2_86EC
  baseline91.35135%
  [1] Correct portrait helper declaration to actual u8 scene/s8 charID prototype ->100%; kept using existing File_0x800203e0.h header.
  readability pass: done. Uses SceneChangeState._12[0] preserving byte width, GAME_TYPE_CHALLENGE. Scene10/menu-state2 have no established enum; unknown _12 and F468 flags retain literal0 because boolean domains unproven.
  final source:
```c
void fn_2_86EC(void) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && lbl_8037169C._12[0] == 0) {
        challenge_setTransitionScreenCharacterPortrait(10, (s8)lbl_2_data_3CE0[g_Challenge.opponentCaptain]);
    }
    cssLoadingScreenRelated();
    cssResetRosterStruct();
    lbl_2_bss_F468[0x56] = 0;
    menuControlVariables->currentState = 2;
}

```

Current .text73.78949%; 15 pre-existing100s preserved, one newly100. Whole-unit scores and source saved best.json/best.c.

copyInfoToInMemRoster continued
  [5] Widen packed byte local from u8 to int with /2 ->78.4874%, rejected. Arithmetic shift + explicit 0xFF mask matches target extrwi8 (target consumes packed bits1..8) and signed remainder ->80.28571%, kept.
  [6] Hoist inner pointer declarations before outer pointers ->81.54622%; move src declaration after outer pointer declarations ->82.5126%, kept.
  [7] Replace tail helper with ordinary 9-slot for loops using existing player counter ->94.033615%; named reusable match/cursor pointers ->96.55462%; restore enclosing two-team loop ->97.52521%. Target redundant inner guards arise from outer-loop unrolling, not an inline helper. Kept nested loops; helper now unused and to be removed.
  [8] Relocate pointer increments into for clauses ->identical, reverted to simpler body increments.
  [9] Compute dst/lineup via team indexing instead of explicit outer base pointers ->98.231094%; s8 cursor pointer ->98.27311%, kept. CharacterStats destination pointer + field names ->neutral, kept.
  next: target and ours have the same core copy, but register allocation/loop increment scheduling remain. Target's outer bases in r21/r20 vs ours r26/r25; tail pointer increments scheduled in opposite order. Avoid redoing hypotheses above.

fn_2_5F80
  baseline65.11429%
  [1] Restore ordinary nine-slot scan and reload aliased source lineup byte after each possible cursor store (draft cached it across all nine). ->90.6%, kept.
  [2] Hoist pointers and counters to function scope in target access order ->90.88571%; scalar order team/player/g ->90.74286 rejected alone. Compute outer bases from team index with this order ->94.14286%, kept.
  next: register/scheduling only, target280 bytes vs current276; target direct outer pointer bases use extra different registers. Target really reloads each byte because cursor/lineup may alias; do not cache it.

fn_2_A62C continued
  [4] Signed cursor view + pointer/value local reorder ->91.55556%, reverted.

fn_2_6784 / cssUnloadScreen
  [1] Move random table+0xC pointer initialization outside do loop, BOOL flag ->74.84375%; narrow u8 flag ->75.78125%, rejected. Target narrow flag width preserved (do not blindly widen this one).
  [2] Replace cssUnloadScreen's duplicate Bowser roster body with fn_2_6784 call ->68.425705% vs76.62852 baseline, rejected. Compiler does not produce the right inline. Original retained.

fn_2_5184
  baseline88.87805%
  [1] Target stores F468[port+0x43]=1 at completion; draft omitted it. Restore plus CHAR_ID_NONE ->95.04878%, kept.
  [2] Unsigned raw ID temp with signed comparisons/call casts ->94.98781%, rejected.
  [3] Signed cursor byte view ->95.30488%, kept; matches target -1 sentinel load.
  next: target keeps separate raw byte and signed temporary across captain comparison and call; ours collapses it. Saved-register ordering also differs.

fn_2_52CC
  target audited: first constant count store is indexed stwx from unfolded index1; source fixed offset store folds it. No omitted logic found. Pending inline-boundary hypothesis, not exhausted.

cssTransitionToNewScreen_maybe
  baseline87.572914%
  [1] Separate cases1 and2 around case3 (target keeps two physical set803c5f77 calls) ->91.447914%, kept.
  [2] Cached global state pointer ->82.0625%, rejected; local case4 pointer neutral, rejected as unnecessary.
  [3] Use actual controllerInputs[port].newInput field ->93.114586%, kept. Temporary wrong member spelling failed build; no stale diff consumed; corrected from header.
  [4] Use aiPosSwapInputs._CF5F[0] named field ->neutral, kept.
  next: only case4 remaining; target materializes state base with addi and schedules stores before the aiPosSwapInputs access, ours emits direct @l store with different scheduling. No speculative volatile.

randCharacter1
  baseline76.51128%
  [1] Target caches captainSelectedID/chemistry base before roster loop; draft reloaded after external calls. Hoist teamBase ->90.86466%, kept. Declaration position neutral.
  next: remaining differences in preheader scheduling, settings/stats base register swap, u8 call-argument materialisation and signed player load. Target and ours main/tail loop logic now agree.

randCharAlgo2
  baseline68.15167%
  [1] Target reloads aliased roster-order byte after each selected-flag store; draft cached it. Use byte pointer ->75.16196%, kept.
  [2] Target buffer accesses use extsb and -1 sentinel, not unsigned255. Preserve s8 CHAR_ID buffer ->75.344475%, kept.
  [3] Restore nested four-variant loop instead of handwritten conditions; target has lhau iteration ->79.982%, kept.
  [4] Cache u8 port index for all indexing (draft incorrectly used full-width port in roster loop) and initialize empty count before first calls ->82.63239%, kept.
  [5] Cached stats byte-base inside first-loop scope ->79.05656%, rejected.
  next: first-loop global address pooling / source views still differ; target1556 bytes vs ours at current snapshot (see current.json). Remaining tail and sorting structure need audit.

cssLoadingScreenRelated continued
  [7] Whole-unit call audit found one missing addRemoveCharVariantRelated call site. Target asm proves an entire missing Challenge roster reconciliation loop after recruitment flags: mark slot selected, addOrRemove(0,id,1), addRemoveVariant(0,(u8)id,2), then scan all 9x5 pair entries, mark group members until -1 sentinel. Restored structured multi-loop stop flag ->87.89483%, kept as intermediate.
  [8] Five sentinel exits share the physical outer-slot continuation in target; measured structured flag adds tests. Shared continuation label ->92.24138%, kept. Goto justified by three-level exit threading, measured alternative above. Missing-loop fix is semantic, not just allocation.

cssResetRosterStruct
  baseline49.06818%
  [1] Target inlines fn_2_33BC; draft's pasted copy skipped slot3 and read slot9. Replace with existing function call ->51.844696%, kept and auto-inlined; fn_2_33BC sibling remains97.48077.
  [2] Target previousScreen9 loop preserves captain slot0 and clears slots1..8; draft inverted condition. Correct j!=0, CHAR_ID_NONE. Score neutral, semantic fix retained.
  [3] Target's stat-row pack loop unrolls eight iterations. Draft duplicates row indexing twice, exceeding pre-CSE unroll budget. Single typed CharacterStats* row local ->69.195076%, kept.
  [4] Replace nine manual handedness assignments and impossible if(0>=9) guard with ordinary loop. u16 character index ->67.132576 rejected; target uses lha, so correct signed existing charID ->71.429924%, kept.
  [5] Restore target physical branch order: main previousScreen!=9 branch first, reset in else ->82.42424%, kept.
  [6] Restore one-player positive flag branch and zero-arm store order ->82.469696%, kept. Target final no-available-character test is ==0, draft !=0; correct ->82.479164%, kept.
  [7] Target availability loop is6x8=48 (no remainder), draft54. Correct bound48 ->80.916664% intermediate regression; move zeroCharCount initialization to function entry (target keeps it live in r31 across calls) ->86.79735%, kept, all prior best floors preserved.
  next: target and ours now contain correct full branches and signed indices. Remaining register/scheduling mismatches; inspect per-function diff. Literal48 has no established named character subset constant, preserve exact observed bound.

Current verified .text76.71911%; all15 pre-existing100s and new fn_2_86EC100 preserved. 66 target symbols total. Current build succeeded; current/best snapshots retained under text_0323C_second_pass.

characterSelectABDirectionInputs
  baseline41.113075%
  [1] Target handles movement/profile-disabled branch first, source reversed both large regions. Restore equivalent structured if/else in target order ->78%, kept.
  [2] Target tail narrows profile-dismiss result to u8; actual standalone stopShowingCaptainProfile has that exact contract. Replace two handwritten toggle copies with existing call, automatically inlined ->79.024734%, kept; standalone remains100.
  [3] Signed s8 computed port for charSelectStruct, signed playerNumber load before zero comparison ->79.947%, kept.
  [4] Actual cursor helper input arguments are narrow16 (target passes original u16 values without integer extension); correct local prototype ->81.96466%. Initially regresses characterSelectControls, withheld until caller fixes below preserve its baseline. Kept after caller review.
  next: profile-side state pointer lifetimes, cached controller cursor pointer versus indexed store, original four saved registers versus ours six. No repeated tail-toggle/branch reordering experiments.

characterSelectControls
  baseline71.2016%
  [1] Target disables input when gameSetUpStep[team+0x5D] !=0; draft test inverted. Corrected.
  [2] Use existing inlined stopShowingCaptainProfile for trigger dismissal; cursor-helper narrow16 declaration with current s32 input locals ->70.8745%, not accepted alone.
  [3] Preserve actual u16 held/pressed/repeat local widths from lhz loads ->71.67023%, kept, allows AB sibling81.96466% without any best regression.
  next: bulk variant handling source remains pasted in caller; inspect target control flow and lost reloads. Input-disable correction is semantic.

fn_2_A1A0 / fn_2_B66C
  baseline A1A0 89.206894%; B66C64.17341%
  [1] Target B66C empty slot block is A1A0(i,1); draft inverted CPU condition and used wrong second cursor offset9 vs11. Plain function call does not inline (ours536 bytes vs target692), B66C59.404625%, rejected.
  [2] Explicit inline shared body required after measured plain-call refusal; copy existing A1A0 body as fillUnassignedRosterSlot ->B66C71.68208%. Existing standalone delegates to same body ->A1A090.155174%, kept, no extra object symbol emitted.
  [3] Restore switch physical case order0/1/-1, target's two distinct addOrRemove calls rather than collapsed ternary, and valid slot branch before empty branch with u8 index ->B66C80.68786%, kept.
  next: caller source index/pointer lifetime still differs. Shared body now removes duplicate logic; no speculative ABI changes. Actual target wait loop exists, so do not 'fix' infinite wait semantics without evidence.

challengeSetRoster
  baseline85.43668%
  [1] Target initializes missing captain row to signed -1 before memset and truncates only successful assignments. Draft u8 last silently made sentinel255. Correct s32 last=-1 and assignment(u8)i ->91.05677%, kept.
  [2] Shared empty-slot inline helper from A1A0 ->87.187775%, rejected against91.05677 best; original explicit body retained. Same behavior can need different inline/source shape per caller.
  next: remaining pointer/register scheduling; target916 bytes. Preserve correct signed default.

teamReady1
  baseline85.56223%
  [1] Target reuses function-level loop index in Challenge copy and compares CPU mode unsigned. Reuse i instead of block idx, u8 mode ->87.70815%, kept.
  [2] Replace duplicated setup block with existing fn_2_52CC call; compiler auto-inlines ->87.87983%, kept, standalone remains86.64893 baseline.
  next: Challenge pointer/local declaration lifetime and unfolded indexed state-store (shared with52CC) remain. No evidence for omitted calls.

Latest verified whole unit: .text77.88867%. 15 pre-existing100s + fn_2_86EC100 preserved. All functions at or above session baseline and accepted sibling bests. No config/shared-header changes; owned header restored byte-equivalent baseline.


Resume reconciliation: verified .text79.38962%, all accepted bests and sixteen100 functions preserved. The prior latest text score77.88867 above is historical.

randCharBasedOnClass
  [1] Signed CHARACTER_CLASS buffer, switch reload from buffer, E(u8,BOOL) full flags (target truncates), and unsigned grid-byte candidate IDs widened to s16 ->77.978264%, kept.
  [2] Restore physical switch order0/1/2/3 ->78.00543%. Incorrect3/0/1/2 order77.42029 rejected.
  [3] Class counts/flags order1/2/3/0 and delay cursor initialization until after memset ->80.804344%, kept.
  [4] Second-loop walking cursor ->82.672104%; first-loop walking cursor/class pointers ->83.18841%, kept.
  [5] Remove cached narrow port ->80.679344%; shared candidate collection helper ->80.41848%; rejected.
  next: candidate write pointer and register lifetime differ; signed byte-buffer semantics now correct.

characterSelectAPress
  [1] Target has one common cursor sound after auto-inlined fn_2_5184. Replace copied block with actual helper call ->71.26499%, kept.
  [2] Draft compared slot position to captain character ID and chose last match. Target compares to signed current state position and stops at first of nine matches. Restore correct position load and structured loop ->75.196655%, kept.
  [3] Existing fn_2_60D4 getter replaces duplicate three-way captain selection, auto-inlines neutrally, kept.
  next: large variant body still needs flow/alias audit.

fn_2_EAE0
  [1] Draft flag uninitialized on inactive port. Target initializes from signed playerNumberByPort then conditionally substitutes port0-is-team0. Correct ->73.882355%, kept.
  next: repeated global reloads and pointer alias lifetime differ. Target really has the infinite active-port loop; do not invent an exit.

fn_2_A50C / fn_2_A6E0
  [1] Whole-body overlap helper shared by target A50C and two A6E0 expansions. Explicit static inline findRosterOverlap with public tail-return wrapper ->A50C98.541664%, A6E079.753204%, kept. Inner-only helper experiments in A62C were a distinct rejected boundary.
  [2] A6E0 second branch target uses A62C sentinel-aware scan, compares signed byte to255, and loops physical state indices1..2. Replace incorrect pasted -1 tests with existing auto-inlined A62C calls and explicit boolean stores ->88.56731%, kept.
  [3] Initialize count at entry and conditionally increment first slot; state array target uses signed -1 sentinel. Correct owned extern to s8 and sentinel stores to-1 ->A6E089.42308%, kept; A28872.534164% side gain, no sibling loss.
  [4] Swap overlap val/inner initialization ->A50C unchanged, A6E089.39103%, rejected and restored. Whole-unit rebuild confirms best79.38962%.
  next: A50C residual base/value register allocation; A6E0 remaining scheduling and indexed state access. No new emitted helper symbol.

fn_2_C698 / fn_2_C7DC
  [1] C698 target explicitly truncates idx and variant charID, but casts in flattened source shift allocation ->84.07407% vs94 baseline, rejected.
  [2] C7DC existing C698 call for entire duplicate tail auto-inlines but65.72671% vs65.7764 baseline, rejected.
  [3] C7DC target uses one incrementing roster pointer across both team checks. Replace indexed draft loads with explicit pointer walk ->71.82609%, kept. Whole-unit79.45803%, no sibling loss.
  next: C698 needs inline/context boundary rather than independent ABI casting; C7DC preheader register lifetimes and intertwined lineup stores still differ.

fn_2_CCE0
  [1] Whole-body inline boundary ->93.93259% unchanged, removed unnecessary helper. Target duplicates narrow port conversion at outgoing call while ours shares earlier conversion; remaining type/context issue, not missing scan logic.
fn_2_CA60
  [1] Replace duplicate selection tail with existing C698 ->69.80132% vs79.27152 baseline, rejected. Target shares pointer/index from first block across tail, helper hides that lifetime. Preserve original.
fn_2_C484
  [1] Replace duplicate variant search with existing matched fn_2_C324; auto-inline ->95.48872%, kept. Whole-unit79.49006%, no sibling loss.
  next: target raw ID/result lifetimes and register allocation remain.

fn_2_6884
  [1] Existing C324 helper replaces duplicate variant search ->99.63461%, kept. Whole-unit79.56009%. Remaining only two outer base registers swapped (cursor vs lineup).
  [2] Explicit initialized cursor/lineup bases ->91.95513%, rejected. Keep compiler-generated loop induction bases99.63461.

fn_2_6AF4 [1] Typed CharacterStats row pointer with explicit team/slot indexing ->94.79452% vs91.08219. Kept, whole-unit79.59816. Target additive addressing restored; remaining induction-base register scheduling.

fn_2_B324 [1] Target increments two captain IDs across loop, rather than adding i each iteration. Restore induction variables ->76.66942%, kept; whole-unit79.6396. Target intentionally retains unreachable trailing fill loop; preserve it.
  [2] Explicit roster pointer in first loop ->76.264465%, rejected against76.66942. Remaining interleaved store scheduling and shared base lifetimes.

fn_2_ABC0 [1] Target stores value buffer at stack8/order40 and caches u8 current maximum across inner sort. Restore buffer declaration order and cached best ->73.376236%, kept. Whole-unit79.69467; sorting pointer and first copy induction still differ.

fn_2_AEE8 [1] Same target cached u8 current maximum in inner sort ->82.52399%, kept. Whole-unit79.72157. Remaining outer-team addressing and induction scheduling.

fn_2_ABC0 [2] Restored original array declaration order after measured MWCC reverse stack placement; typed CharacterStats indexing ->74.19802%, kept. Prior buffer-order claim was inference corrected by instruction diff.
  [3] Explicit first-loop walking source + byte load before order store ->58.683167%, rejected. Source pointer aliasing changes unroll/scheduling drastically.

fn_2_9ACC [1] Replace two handwritten CharacterStats field-copy blocks with existing typed copyCharacterStats helper; actual auto-inline ->88.88216% vs85.31313, kept. Whole-unit79.807686. Remaining snapshot/lineup store interleaving and outer registers differ.

fn_2_8CF8 [1] Four handwritten stats-copy expansions replaced with existing typed helper, preserving snapshot/lineup writes ->77.61268% vs73.52817, kept. Whole-unit79.97064. Target helper interleaving remains source-context dependent.

fn_2_4970 [1] Restore ordinary nine-slot last-match scan instead of handwritten independent ifs. Narrow slotIndex experiment56.373306 rejected; retain s32 ->57.70793%, kept. Target scan really has no early break (unlike APress). Remaining variant reconciliation and pointer reloads need audit.

fn_2_B920 [1] Shared empty-slot body fillUnassignedRosterSlot(i,0) replaces pasted scan with inverted mode predicate, matching confirmed A1A0 body ->67.10922%, kept. Whole-unit80.02718. Remaining roster state initialization and outer table pointer scheduling.

fn_2_95D8 [1] Target second hover branch writes status[1], default writes both; draft wrote only status[0]. Correct stores, u32 status comparison and u8 mode widths ->79.36278%, kept. Whole-unit80.04594. Tail target contains no calls or stores, but retains state comparisons absent in ours; no fabricated side effects added. First-loop helper/source scope and final empty tail comparisons remain.

fn_2_A288 [1] Restore nested eight-byte scan loop ->66.7205% vs72.534164 current best, rejected. Target bound8 confirmed, no omitted ninth slot. Remaining pointer view/state byte alias scheduling.

starHitSetting_Unused_maybe [1] Restore walking three-by-three cursor scan from indexed hand expansion; preserve target extra counter increment per group ->77.758865%, kept. Whole-unit80.07501. Remaining header scopes and dispatch register assignment.

fn_2_3624 [1] Target checks disabled state after memset before reading controller input. Move input copy after guard ->63.413765%, kept. Whole-unit80.154594. Draft cached global views span large control regions unlike target reloads.

fn_2_3624 [2] Remove cached whole-function state/cursor pointers; direct global views let target-style reloads stay within branches ->65.49879%, kept. Whole-unit80.335464. Further branch/case and inline toggle audit pending.

cssReturnToCapSelect_maybe [1] Extract Challenge lock test to BOOL inline returning normalized comparison ->65.29713 unchanged, removed unnecessary helper. Target normalizes result despite branch use; original helper return type remains uncertain.
  [2] Remove s8 captain comparison cast and shifted pointer ->64.75494%; original pointer only64.81598%; nested3x3 scan65.04398% (outer index stride2 neutral). All below65.29713, rejected. Target compares full captain word, but draft cast removal changes broader allocation; unresolved, retain baseline until combined fix preserves best.

cssChangeScreens [1] Remove cached whole-function state pointer, use direct global state fields after calls ->93.437836% vs90.73514, kept. Whole-unit80.37058. Remaining store address materialization and reset loops.

fn_2_57F0 [1] Target reloads backup state slot at comparisons, draft retained scalar across potential state alias writes. Use pointer to stored backup ->93.733475%, kept. Whole-unit80.40289. Remaining narrow parameter lifetime and physical switch block order.

fn_2_87A8
  [1] Explicit signed player local ->98.11881% unchanged.
  [2] Explicit setting pointer ->98.11881% unchanged. Both removed; target/ours identical opcode/order with register permutation. No omitted logic. Remaining probable local/header inline context; no speculative helper emitted.

fn_2_A040 [1] Eliminate temporary pair pointer, direct variantPairs accesses ->90.85227% vs91.13636, rejected. Main scan opcode/order matches except compare operand/base register permutation; tail index scheduling differs. Full loop/fallback logic audited, no missing operation found.
fn_2_B920 [2] Target switch order0/1/-1 ->67.101944%, rejected against67.10922. s32 row indices plus unsigned table comparison66.72573%, rejected as combination.
fn_2_B920 [3] Unsigned table comparison alone66.68689%, rejected. Full best restored.

Readability cleanup: repaired nesting indentation in Reset/AB direction/class selector; named class enums, TRUE and established CHAR_ID sentinels. Whole-unit rebuild/rediff neutral80.40289, all best floors preserved.

fn_2_B508 [3] New local ABI experiment: function-type cast at this call to authoritative u8(u8,u8,u8), avoiding global-prototype sibling regressions. MWCC still emits direct bl;99.77528%, kept, all sibling floors preserved. Commuting source equality neutral. Remaining compare operand orientation and signed player load register. Cast is transitional readability limitation until all callers support correct global declaration.

fn_2_B508 [4] Preserve signed playerNumber in explicit block-local s8 before team call ->99.88764%, kept. Only compare operand order remains.

fn_2_B508 [5] Explicit signed character ID local before equality preserves target compare operand orientation ->100%. Saved immediately; mandatory readability follows. All sibling bests preserved, whole-unit80.408516.

fn_2_B508 readability pass: done. E(s8,CHAR_ID), named rosterCharID/rosterSpotFilledInd/charOnCharacterGridSelected fields, NUM_CHOOSABLE_CHARACTERS and FALSE replace raw values; whole-unit neutral80.408516 and function100. Lineup slot indices remain numeric (array indices), team1 retained (no proven team enum). Purpose: clear second-team noncaptain slots/variant selection; possible name resetSecondTeamRoster is medium confidence, left unchanged.

fn_2_A040 [2] B508 comparison-local finding applied on new evidence: explicit signed ID local fixes compare operand orientation ->91.64773%, kept. Remaining cursor/target register swap and tail index scheduling.

fn_2_6884 [3] Named cursor roster fields ->99.63461% unchanged, kept for readability; no width or alias change.

fn_2_6884 [4] Store cursor ID before lineup assignment in source; scheduler still emits target lineup store first but now allocates cursor base first ->100%. Saved immediately; mandatory readability follows.

fn_2_6884 readability pass: done. Removed unused copied-search declarations; E(s16/u8,CHAR_ID), TRUE, CHAR_ID_NONE, ARRAY_COUNT with preserved signed bound, named roster/grid fields. Whole-unit rebuild neutral80.41568 and function100. -1 variant-row result remains numeric because it is an index sentinel, not a character ID. Purpose restore saved Challenge lineup and mark variants; suggested restoreSavedChallengeLineup medium confidence only, no rename.

fn_2_A50C / A6E0 continued
  [5] Explicit signed comparison local plus loop-local outer val ->A50C87.638885 (regression), A6E090.0641 (gain), rejected as combination. Retain function-level val; explicit other local alone codegen-neutral. Boolean helper returns named TRUE/FALSE and address annotation moved to public function.

Overlap helper readability cleanup verified neutral80.41568; accepted per-function floors unchanged.

fn_2_C698 [2] New B508 ABI evidence: correct call-site function type only ->94.49383%, kept, all siblings neutral. Existing earlier failed cast experiment also changed idx width; isolated correct ABI now gains.

fn_2_C698 [3] Structured if/else with per-branch narrow ID ->90.27161%, rejected alone. Shared function-level s32 signed ID (target preserves signed full value across calls then truncates variant arg), explicit narrow idx and block-local signed player ->100%, kept. This also removes all draft gotos. Whole-unit80.449814, all sibling floors preserved. Saved before readability.

fn_2_C698 readability pass: done. Structured flow removes gotos; E(s32,CHAR_ID) preserves evidenced signed register width, named roster/grid/player fields, TRUE, GAME_TYPE_CHALLENGE, P2_CPU_CODE_1_PLAYER_GAME. Team numbers retain numeric values without proven enum. Whole-unit neutral80.449814, function100. Purpose mark selected roster slot and variants, candidate markRosterSlotSelected medium confidence, no rename.

fn_2_C7DC [4] Retest existing C698 call on new evidence: its body is now100% with corrected signed register/ABI semantics. Replaces duplicate tail ->76.639755%, kept vs71.82609 best. Whole-unit80.50425; earlier old-body call rejection remains valid history.

fn_2_CA60 [2] New100 C698 tail call71.5894% vs79.27152 baseline, rejected. Shared first-block cursor index still lost; target value must remain in full signed register, testing width separately.
  [3] CA60 signed full-register charId alone78.013245 rejected alone; correct local variant ABI together restores79.27152 baseline exactly, no sibling regressions. Both kept as evidenced signed/ABI correction; header parameter width hypothesis pending coordination.

Latest whole-unit80.50425; corrected C698100 helper raises C7DC76.639755, CA60 width+local ABI combination neutral at original79.27152. All19 matched functions and all accepted floors preserved.

Unused pasted-search/old tail declarations removed from C484/C7DC; rebuilt whole-unit neutral80.50425. Full ninja build succeeded exit0; native git diff --check clean. Owned header/config remain unchanged.

fn_2_87A8 [3] B508-style block-scoped player temp tested on new evidence ->98.11881 unchanged, removed. AtBat header has no +4 input field; raw access remains justified.

fn_2_87A8 [4] After inline/temp/width hypotheses, move initial cursor value declaration after pad and held ->99.0099%, kept. No statement or lifetime semantic change; remaining input registers only.
  [5] Swap pad/held declaration order after value declaration fix ->99.0099 unchanged, removed.
  [6] Commute pointer-add operands ->99.0099 unchanged, discarded.
  [7] Typed u16 input pointer ->99.0099 unchanged, removed.

fn_2_87A8 [8] Widen loaded input local to u32 while preserving lhz access ->99.30693%, kept. Matches target pointer/result register reuse; remaining player/address preheader only.
  [9] Full-register block-local player temp after held width correction ->99.30693 unchanged, removed.
  [10] Inline pointer-getter boundary (common PAD-record chain also present in menus/rep_1028.c and rep_0788.c) ->99.30693 unchanged, removed. Supported stop: same instructions/order/widths, residual player-address preheader register permutation; direct-expression, temp scopes, pointer view, declaration grouping, input width and plausible getter boundary all measured. Mark exhausted until new inline/TU evidence.

Final current checkpoint reconciliation: .text80.51268%,19/66 matched,42/51 initially unmatched improved, no original or accepted-best regression. 87A8 supported exhausted99.30693;46 other functions remain pending, so this is resumable work, not full-file completion. Header parameter-width hypothesis still coordinated with root; no header/config edits.
