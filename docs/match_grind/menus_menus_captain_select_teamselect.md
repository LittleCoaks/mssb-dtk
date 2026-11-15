# teamselect first and second passes

Unit: menus/menus/captain_select/teamselect. Target=left, ours=right. Baseline rebuilt; all10 stubs. Baseline JSON/source/header saved under build/codex_teamselect_initial.*.

| function | status | initial | pass1 | current |
|---|---|---:|---:|---:|
| challengeCaptainRelated | exhausted | 0.990099% | 86.78218% | 97.821785% |
| captainSelectDefaultProcess | exhausted | 0.27247956% | 94.79836% | 99.14169% |
| fn_2_12988 | matched | 11.111111% | 100.0% | 100.0% |
| fn_2_129AC | matched | 11.111111% | 100.0% | 100.0% |
| fn_2_129D0 | matched | 2.5% | 95.1% | 100.0% |
| fn_2_12A70 | matched | 1.6666666% | 100.0% | 100.0% |
| fn_2_12B60 | exhausted | 1.8867924% | 44.11321% | 97.07547% |
| fn_2_12C34 | matched | 2.4390244% | 86.585365% | 100.0% |
| fn_2_12CD8 | exhausted | 0.5813953% | 92.73256% | 97.18023% |
| captainSelectScreen_manager | exhausted | 0.12903225% | 96.51742% | 98.42065% |

## Hypothesis log

## Open questions

- All ten void signatures and full assembly logic audited. REL deferred emission order verified; no compiler changes. Natural .rodata content matches at configured100%; target120/source116 differ by4-byte trailing alignment gap. The48-byte switch table was re-assigned from auto_data to this unit, preserving the separate4-byte gap19E4; its branch addends remain unmatched.
- Remaining unknowns: original scalar/global declaration shape for gameSetUpStep byte0 and lbl_803CBBC2+2; roster-loop alias/inlining register lifetimes; model-call narrow-port cast lifetime. No new names proposed: matched helpers lack independent naming evidence.
- No BSS/extab/extabindex section belongs to this unit; exceptions remain off as configured. Split emits natural4-byte alignment (DTK warns because module default is8); no artificial alignment/padding was added.

- [S1] fn_2_12988: allocator snapshot using named MemoryStack low/high fields and existing static-table pointer slots ->100%. Saved immediately. Readability pass: done; slots2/3 have no established names, retained existing array representation. Subsequent whole-unit rebuild confirms100%; no sibling regression. First compile needed the established menus/yd_step.h for menuControlStruct, repaired before any diff. Completed1/10.

- [S1] fn_2_129AC: second allocator snapshot ->100%, saved immediately. Readability pass: done; slots0/1 retained as existing unnamed array. Whole-unit rebuild/rediff confirms previous12988 remains100%. Completed2/10.

- [S1] fn_2_129D0: complete reset of both counted arrays, two-byte sentinel range and individual state bytes/word ->95.1%, target160/source164. CHAR_ID_NONE cast removal95.1% (neutral); opaque sentinel fields need semantic type confirmation in pass2. next: inspect global-base reuse and shared -1 constant/register lifetime. Completed3/10.

- [S1] fn_2_12C34: full timer rollover/increment conditions and target retained cursor-wrap loop ->86.585365%, target/source164. Named challenge game-mode used; timer limit60000/cursor interval5..20 lack existing named constants. next: declaration/initialization and count-width scheduling. Completed4/10.

- [S1] fn_2_12B60: full prior-captain snapshots, one/two-player input dispatch and model-retry loop ->44.11321%, target212/source216. All sibling scores retained. next: target pointer induction over cursor/state arrays and loop nesting/register lifetime. Completed5/10.

- [S1] fn_2_12A70: full two voice-trigger clears and confirmed-selection transition ->100%, saved immediately. Readability pass: done; GAME_TYPE_CHALLENGE/P2_CPU enums, named captain IDs and TRUE used. Raw bytes have no shared established fields; original state code4 retained. Whole-unit rediff follows. Completed6/10.

- [S1] challengeCaptainRelated: full six-captain search/assert, saved fielding order and roster/mapping seed, logo update ->86.78218%, target/source404. Both panic strings emit naturally; whole .rodata120 bytes now100%. No data tables/padding fabricated. next: search/address induction and field-store scheduling. Completed7/10.

- [S1] fn_2_12CD8: full screen-entry cursor/reset, allocator checkpoint, graphics load, challenge roster seeding and challenge model setup ->92.73256%, target688/source692. Compiler naturally inlines129AC and challengeCaptainRelated, consistent with target. next: initial allocator/state-store scheduling and shared search differences. Completed8/10.

- [S1] captainSelectDefaultProcess: full entry/resume paths including reset, controller layout arrays, captain/model restoration and process transitions ->94.79836%, target1468/source1472. State reset helper inlines naturally; no missing assembly logic known. Re-read model retry target and corrected12B60 retry flag polarity to !=0 (score unchanged44.11321%). next: named controller-layout helper/inline boundaries and startup register lifetimes. Completed9/10.

- [S1] captainSelectScreen_manager: all12 dispatch states (including empty3/7), helper inlining, entry wait, ready transitions, both cleanup branches, roster reset and exit-menu subdispatch ->96.51742%, target3100/source3096. Full assembly audit complete; natural switch emits48-byte .data table currently outside target unit split. Root notified with exact table ownership evidence; no shared edit performed. All10 bodies now complete. Deferred REL source definitions reordered in reverse target address order; mandatory sibling measurement follows.

## Pass1 completion and pass2 start

[S1] Complete10/10, three100 functions with readability checks and whole-unit rediff. .text93.29994%, .rodata100%, ours natural .data48 pending coordinated target split. Pass1 source/JSON preserved. Effective GC2.6 compiler: -inline deferred, -Cpp_exceptions off, -sdata0/-sdata2 0, -requireprotos. Source reversed address order produces ascending target emission; all per-function scores unchanged. No actual target parameters found for these10 routines; existing void signatures confirmed. Ghidra not needed; authoritative assembly supplied every draft.

[S2] Now assessing all seven pending functions smallest-to-largest plus verifying three matches. No first-pass attempt cap applied; preserve all per-function bests.

- [S2] fn_2_129D0: literal -1 alone stayed95.1%; signed-byte views for sentinel slots21/22 permit the target shared -1 constant ->100%, target/source160 (kept, saved immediately). Also improves inlined default process94.79836 ->94.85831%. Readability pass: done; these are opaque slot/state sentinels, not proven CHAR_ID fields, so -1 is appropriate and named CHAR_ID_NONE was removed. Entire unit rediff verifies prior matches and new100. Pass2 assessments4/10 including three verified matches.

- [S2] fn_2_12C34: move count/cursor initialization after exit and timer guards ->100%, target/source164 (kept, saved immediately). Readability pass: done; GAME_TYPE_CHALLENGE used, timer60000 and cursor range5..20 have no established enum; retained evidence-backed constants. Whole-unit rediff verifies all five100s. Pass2 assessments5/10.

- [S2] 12B60 exit-guarded infinite loop64.09434%/208 bytes but manager94.89032% regressed; reverted. Narrow u8 slot76%/216 bytes but manager95.17548% regressed; not retained alone. Coordinated root notification; testing explicit prior int-counter body expansion in manager to preserve its original inlined form while tuning standalone helper.

- [S2] 12B60 manual expansion of prior int-counter body in manager still regressed manager95.285164%; reverted. Small inline model-call wrapper is codegen-neutral44.11321% and manager96.51742%; removed. Next probe uses explicit natural cursor/old/state pointer induction, matching target loop-base lifetimes.

- [S2] 12B60 explicit pointer induction32.81132%, source212 and manager95.021935% both regressed; reverted. Inspected model callee: int port with low-byte extraction internally, shared prototype evidence remains consistent; no header change justified. A compile-time int*/s32* mismatch in the experiment was repaired before measurement.

- [S2] 12B60 signed-byte loop counter42.226414%/220 bytes and manager96.381935% regressed; reverted. Retained original complete int-counter loop44.11321% (manager96.51742%). Pointer induction, loop exit structure, signed/unsigned widths, inline call boundary and manual caller expansion have all been measured; no higher-scoring sibling-safe variant found. Supported stop: exhausted for this pass, target hoists no slot-cast register while ours does; original loop/inlining phase evidence needed. Pass2 assessments6/10, five100s.

- [S2] challengeCaptainRelated: two-dimensional array expression alone86.78218% (neutral); explicit row-base and character-read temporaries97.821785% (kept), and inlined12CD897.18023%/manager97.50452% both improve. First search block now instruction-identical; residual loop address/register allocation under investigation.

- [S2] challenge explicit roster/cursor/challenge base pointers76.95049% and caller84.75/94.745804% regressions (reverted); pointer offsets changed induction rather than matching target.

- [S2] challenge enum-width temporary97.27723% regressed helper despite improving callers (reverted). Separate static-inline seed helper97.376236% and both callers regressed (reverted). Retained explicit row/read temporaries97.821785% with E(u8,CHAR_ID) documentation, size exact404. Exhausted current lookup/induction/temp/inline hypotheses; remaining differences are roster-loop register/base scheduling and equivalent add operands. Parent12CD897.18023%, manager97.50452% preserved. Pass2 assessments7/10, five100s.

- [S2] Default state-mode range replaced by target-faithful0..4 switch ->95.866486%, source1476 (kept). Remaining8-byte gap: indexed model-loop slot cast is hoisted into an extra live register, and external lbl_803CBBC2+2 byte emits an extra base addi. Inspecting explicit widths/inline boundaries rather than changing shared symbols speculatively.

- [S2] Default int-vs-s32 loop types and tighter variable scope were neutral95.866486%; dedicated static-inline controller-layout helper also neutral, retained for clear shared intent. u8 outer slot86.043594%, source1388 (reverted). Testing removal of redundant slot narrowing at an int-parameter model call in both retry loops; slot is proven0/1 by bound.

[S2] Removed redundant slot casts in both retry loops: 12B60 44.11321 ->97.07547%, default95.866486 ->99.14169%, manager96.51742 ->97.7071%, no sibling regression. Reopens earlier12B60 stop with new width evidence; remaining mr/clrlwi and register lifetimes at exact212 bytes. Testing entry scalar byte dereference spelling for the observed extra base addi.

[S2] Entry scalar-dereference spelling97.18023%/692 bytes (neutral); restored clearer array notation. Target is688; remaining extra array-base addi plus inherited roster-loop register scheduling. Next hypothesis isolates allocator/store startup inline lifetime.

[S2] Manager explicit exitMenu case0 and target physical case order1/3/2/4 ->98.42065%,3096 bytes, retained with all siblings unchanged. Target .data table now assigned precisely19B4..19E4 (48 bytes); natural table has differing branch addends while code near-matches. Local game-setup layout experiment reuses captain_select.c evidenced0x55/0x59 fields and exposes byte0 scalar, without changing shared headers.

[S2] Evidenced local game-setup struct (matching captain_select.c fields) is codegen-neutral for all ten functions, retained for named field readability; byte0 still emits addi. Entry next probe manually expands allocator checkpoint to test deferred-inlining boundary.

[S2] Entry allocator manual expansion97.18023%/692 bytes (neutral), reverted to shared129AC call. Together with scalar expression, local layout and inherited challenge seed inline/temp/induction experiments, no further distinct evidence-backed startup/lookup avenue improves it. Readability pass: done; existing named game/P2 fields used; opaque setup byte0 and static bytes4755/4701 have no proven semantic names. Entry stops at97.18023%.

[S2] Manager manual entry-helper expansion98.42065%/3096 bytes (neutral), reverted to shared call. Full helper-boundary probes, state/exit-switch shapes and width/induction experiments across inlined callees leave only base/register scheduling and global byte addressing. No missing target logic known. Readability pass: done; named aiPosSwapInputs._CF5F array replaces raw offset; helper indentation normalized. State/scene/process IDs remain literals because no governing enum is established. Stop supported at98.42065%, with no sibling regression.

## Final second-pass resolution

[S2] Complete10/10 assessments, five matched/five exhausted for this pass. Each retained change was measured across all ten functions; all initial/pass1 and intermediate per-function best scores are preserved. 12B60 earlier44.11321 stop was explicitly reopened on new cast-lifetime evidence; final97.07547%. Readability pass: done for12B60 and default; existing BOOL, game/P2/CHAR_ID enums, allocator fields and game-setup port fields used. Remaining opaque flags/controller-layout codes/state/scene/process IDs lack governing shared enums; no arbitrary enum or symbol rename invented.

[S2] Default final99.14169%, target1468/source1472: range-to-switch, narrower slot, model-call conversion, local scope/type, controller inline and global addressing investigated. Remaining one extra global-base addi and loop register/clrlwi differences; no evidence to split shared globals or alter prototype/compiler settings. Supported stop for this pass. Challenge final97.821785%, target/source404: lookup block exact, remaining roster-loop register/base scheduling; explicit base-pointer, width and inline hypotheses regressed and were undone. Entry final97.18023%, target688/source692: scalar spelling, evidenced layout and checkpoint expansion neutral; remaining inherited seed scheduling and one extra game-setup base instruction. Manager final98.42065%, target3100/source3096: target-faithful exit switch retained, manual helper expansion neutral, no target logic missing; inherited seed/global-base scheduling and equivalent branch layout remain. Retry final97.07547%, target/source212: exact logic and size, narrowed-port argument/live-base registers remain.

[S2] Data completeness: .rodata target120/source116, configured objdiff100% (target has4-byte trailing alignment gap); .data target/source48,0% because natural switch relocations have different branch addends (no fabricated table). Only precise config/GYQE01/menus/splits.txt ownership range19B4..19E4 changed; auto_data no longer owns it and19E4 gap remains separate. Split regeneration itself improved manager97.7071->97.72645% by resolving table reference ownership. No shared headers, symbols, compiler flags, other source bodies or function names changed. Owned header unchanged, so no dependent-header change to validate.

[S2] Validation: full ninja succeeds,4 files OK SHA1 check; source object build and configured per-unit diff verify.text98.525505%,.rodata100%,.data0%; five100 functions remain100 after readability edits. Native git diff --check passes. Source function emission order verified reverse definition/ascending target; no extra emitted inline function. This remains NonMatching, so full-build SHA1 confirms target-backed build integrity, not runtime execution of the new source. No runtime game test performed. All10 complete drafts remain readable. Final source/header, JSON and per-function snapshots preserved in build/codex_teamselect_final* and *_best.c. Both passes are finished; stop without proceeding to another unit.


[S2] Final raw-section size audit: left target.text6508/right ours6512; left.rodata120/right116 (configured score100%, target trailing4-byte alignment gap not emitted by our constants); both.data48. The100% rodata score does not imply identical raw section size. No padding fabricated; unit remains NonMatching. This corrects earlier pass notes that inferred120 source bytes from the target section size.
