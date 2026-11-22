# game/game/ball/ball_fielder_collision checkpoint

| function                        | status  | pct     |
|---------------------------------|---------|---------|
| fn_3_16C548                     | pending | 93.18%  |
| fn_3_16C878                     | pending | 98.84%  |
| fn_3_16CC2C                     | pending | 98.90%  |
| checkFielderCollisionPotential  | matched | 100.00% |
| processBallFielderCollision     | pending | 97.73%  |

Baseline (all stubs): .text 0.42%, .rodata 64.52%. No .data/.bss in unit.
After this session: .text 8.72% (fuzzy), .rodata 84.87% (both unowned/anonymous rodata symbols, not yet split into this unit).

## Notes
- fn_3_16C548 = particle update callback (passed to allocParticleEffect by fn_3_16CC2C).
- fn_3_16C878 = particle init; no callers, body inlined twice into fn_3_16CC2C (MWCC auto-inline of an earlier-defined function, same as sta_c5 fn_3_F3EFC -> fn_3_F42A0).
- checkFielderCollisionPotential is inlined into processBallFielderCollision.
- Rodata order: 40E0 = 12-byte zero Vec aggregate initializer, then 255f,0f,100000f,int-magic (update fn), 1000.0,deg2rad,360.0,uint-magic (init), 1.5f,0.07f,0.1f,0.05 (processBall).
- Remaining diff in processBallFielderCollision is structural/unavoidable for now: fn_3_16CC2C is still a stub (`{ return; }`), so MWCC's inliner determines the "if (isWorldPosOnScreen(&pos)) fn_3_16CC2C(&pos, source);" block has no observable effect beyond the isWorldPosOnScreen call itself, and folds/removes the branch and the fn_3_16CC2C call entirely, along with the register (`source`) that would otherwise need to stay live across all the calls to reach that final call. This also explains why our build only needs 2 callee-saved GPRs (r30/r31) where target needs 3 (r29/r30/r31 - one dedicated to holding `source`/fielderIndex separately across the whole function). This should resolve on its own once fn_3_16CC2C gets a real (non-trivial) body in a future task.
- Also remaining: the inlined copy of checkFielderCollisionPotential's boolean combine (inside processBallFielderCollision's `if (!checkFielderCollisionPotential(...))`) uses target's `or. r0,r3,r0; beq; li r0,1; b; li r0,0` idiom (NOT the full `neg;or;srwi` normalize), while our standalone function needs the full normalize to score 100%. Same source, same expression, different codegen depending on whether MWCC is looking at the real out-of-line function vs. inlining it directly into an `if` (it can skip full 0/1 normalization when the value only feeds a zero/nonzero test). This is an MWCC-inliner-context difference, not something fixable by picking a different source form without regressing the standalone function's now-100% score.
- Rodata labels differ between target (`lbl_3_rodata_XXXX`) and ours (`@75`, `@122`, etc.) throughout both functions' DIFF_ARG_MISMATCH entries - this unit doesn't yet own/split that rodata (still anonymous/unlabeled), out of scope for this task.

## Part A diagnostics (session: rodata/text-order investigation)
- Confirmed via `dtk elf info` + a manual ELF32-BE `.rodata` byte dump that this unit's `.text` symbol *address* order is the exact reverse of target's: ours is processBallFielderCollision, checkFielderCollisionPotential, fn_3_16CC2C, fn_3_16C878, fn_3_16C548 (reverse of source-declaration order); target's is fn_3_16C548, fn_3_16C878, fn_3_16CC2C, checkFielderCollisionPotential, processBallFielderCollision (matches source-declaration order exactly). This matches the unit's `reverse_fn_order: true` metadata flag.
- This reversed compile order also reverses the literal-pool constant emission order in `.rodata`: ours emits processBallFielderCollision's floats (1.5f/0.07f/0.1f/double 0.05) FIRST (right after the shared `repHeaderData`), then fn_3_16C878's (100000.0f/1000.0/deg2rad/360.0 doubles), then the two float<->int magic-number doubles, then fn_3_16C548's 255.0f LAST - the reverse of target's order (255f/0f/100000f/int-magic, then 1000/deg2rad/360/uint-magic, then 1.5f/0.07f/0.1f/pad+0.05).
- Ours also contains two extra 8-byte doubles (`_half$localstatic3$dolsqrtf2` = 0.5, `_three$localstatic4$dolsqrtf2` = 3.0) interleaved right after `repHeaderData` and before the zero-Vec - these are MWCC-internal constants for the `dolsqrtf2`/`PSVECMag` sqrt routine referenced from processBallFielderCollision, and don't appear anywhere in target's per-unit rodata (188 bytes ours vs 168 target - the extra 20 bytes is these two constants plus alignment padding).
- Net effect: this unit's rodata is not yet "owned"/split (all symbols are anonymous `@N` on our side vs `lbl_3_rodata_XXXX` on target's), and the physical byte order differs from target due to the reversed-compile-order literal pool. This is a structural/ownership issue, out of scope for this task (per existing checkpoint note), and is the root cause of essentially all `DIFF_ARG_MISMATCH` rows that reference a rodata symbol in every function in this unit.
- A3 (fn_3_16C548 prologue, target asm lines ~14-26): confirmed the previous source form (`emitter->particles = fn_80031F34(...); p = emitter->particles;`, two separate statements) forces MWCC to `stw r3,0xc(r25)` then reload with a fresh `lwz r29,0xc(r25)` for `p`, instead of target's single `mr r30,r3` copy-propagation after the call - directly motivating and confirming H5.
- A3 (fn_3_16C548 alpha block, target asm lines ~47-77): beyond the expected rodata-label mismatches, there is a real instruction-order difference in the int-to-double bit-trick sequence around the `alpha - 255.0f/fadeFrames` conversion (some loads/stores swap position, e.g. target's `stw r4,0x10(r1)` / `lis r3,lbl_3_rodata_40EC@ha` / `xoris r0,r0,0x8000` / `lfd f0,0x10(r1)` become `DIFF_DELETE`d while ours has different-but-equivalent instructions in different slots). This is most likely a downstream effect of the unowned-rodata/reversed-pool-order issue above (different constant pool layout changes MWCC's load scheduling), not a separate source-level bug.

## Hypothesis log
- checkFielderCollisionPotential return expr variants (measured together with processBallFielderCollision, since the former is inlined into the latter):
  - `return height >= lowY || height >= -offset.y;` (original `||`): checkFielderCollisionPotential 1.49% -> not directly tested alone; combined baseline before any variant work was much lower (see below).
  - (a) `return (height >= lowY) | (height >= -offset.y);`: checkFielderCollisionPotential 96.79%, processBallFielderCollision 79.56% (sum 176.35).
  - (b) `return ((height >= lowY) | (height >= -offset.y)) != 0;`: checkFielderCollisionPotential 100.0%, processBallFielderCollision 81.29% (sum 181.29). BEST for checkFielderCollisionPotential; adopted.
  - (c) BOOL return type + original `||`: checkFielderCollisionPotential 88.36%, processBallFielderCollision 77.26% (sum 165.6). Worse than (b), reverted.
  - Also tried using `&&` vs nested-if for the `(collision&0x7F)==ROUGH_TERRAIN && pastCoordinates[0].y<=threshold` condition: no measurable difference either way; kept `&&` (simpler).
- processBallFielderCollision structure:
  - Introducing a local `InMemFielder* fielder = &g_Fielders[fielderIndex];` computed before the `checkFielderCollisionPotential` call (instead of repeated `g_Fielders[fielderIndex]` indexing) matched the target's instruction ordering/register-hoisting for the fielder-branch and jumped the function from 30.05% (initial naive impl) to 76.94%.
  - Restructuring the ball branch (source==0) from three independent early-return guard clauses into a single nested positive form (see Step 3 in the task) improved processBallFielderCollision from 81.29% to 83.34% (adopted, final).
- Initial implementation of fn_3_16C548/fn_3_16C878/fn_3_16CC2C from Ghidra+asm -> fn_3_16C548 92.10%, fn_3_16C878 98.04%, fn_3_16CC2C 97.86%; processBallFielderCollision rose to 89.84% now that fn_3_16CC2C has a real body; checkFielderCollisionPotential dropped 100.0% -> 99.40% (DIFF_ARG_MISMATCH only, on the shared zero-Vec rodata reference, caused by this unit's now-much-larger unowned/unsplit rodata pool shifting anonymous-symbol resolution - not an instruction or value difference).

### fn_3_16CC2C
  [H1] alloc-path else-branch restructured to positive `if (emitter != NULL) { ...; ... } else { return; }` (matching target's polarity) instead of the early-return `if (emitter == NULL) return;` -> fn_3_16CC2C: 97.86% -> 98.22% (kept)
  [H2] removed `u8 stadiumID` local, used `g_d_GameSettings.StadiumID` directly at each use site -> fn_3_16CC2C: 98.22% -> 97.50% (reverted, regression)

### fn_3_16C878 (and its two inlined copies inside fn_3_16CC2C)
  [H3a] `p->rotDir = rand() % 2 * -2 + 1;` (was `1 - rand() % 2 * 2`) -> fn_3_16C878: 98.04% -> 98.71%, fn_3_16CC2C: 98.22% -> 98.79% (kept)
  [H3b] `p->rotDir = -(rand() % 2 * 2) + 1;` -> identical scores to H3a (fn_3_16C878 98.71%, fn_3_16CC2C 98.79%); kept H3a form (simpler)
  [H4a] `shade` local widened from `u8` to `int`, expression unchanged -> no change (fn_3_16C878 98.71%, fn_3_16CC2C 98.79%); kept (int is also the technically-correct type for a locals per project convention, free)
  [H4b] reordered to `shade = rand() % shadeRange + 1 + shadeBase;` -> no change vs H4a; reverted to original operand order (`shadeBase + (rand()%shadeRange + 1)`) since it's no worse and closer to the field's natural role as a base+offset
  [H4c] removed the `shade` local entirely, wrote directly into `p->color[0..2]` -> fn_3_16C878: 98.71% -> 97.87%, fn_3_16CC2C: 98.79% -> 98.07% (reverted, regression on both)

### fn_3_16C548
  [H5] `p = emitter->particles = fn_80031F34(emitter->particles, emitter->count);` replacing the two separate statements -> fn_3_16C548: 92.10% -> 93.06% (kept)

### processBallFielderCollision / checkFielderCollisionPotential
  [H6] dropped `u8 fielderIndex` local, indexed with `source - 1` directly (with `InMemFielder* fielder = &g_Fielders[source - 1];` kept) -> processBallFielderCollision: 89.84% -> 95.07% (kept)
  [H6-nofielder] same but also dropping the `fielder` local (`g_Fielders[source - 1].currentVelocity`, `&g_Fielders[source - 1].pos`) -> processBallFielderCollision: 95.07% -> 85.35% (reverted, much worse; kept the `fielder`-local version from H6)
  [H7] `checkFielderCollisionPotential`'s return rewritten from `return ((height >= lowY) | (height >= -offset.y)) != 0;` to an explicit `if (...) return TRUE; return FALSE;` -> processBallFielderCollision: 95.07% -> 97.16% (kept); checkFielderCollisionPotential unchanged at 99.40% (both forms produce the identical standalone-function encoding; only the inlined copy inside processBallFielderCollision benefited)

Final state after this session: fn_3_16C548 93.06%, fn_3_16C878 98.71%, fn_3_16CC2C 98.79%, checkFielderCollisionPotential 99.40% (unchanged), processBallFielderCollision 97.16%.

Remaining diffs, by function (rodata-label-only `DIFF_ARG_MISMATCH` counted separately from all other diff rows):
- fn_3_16C548: 72 ARG_MISMATCH rows total (8 are pure rodata-label, 64 are register-number differences from register-allocation divergence, likely downstream of the reversed/unowned rodata pool - see Part A notes above), plus 5 INSERT/4 DELETE/2 REPLACE rows in the alpha-fade int/double conversion sequence (see A3 notes).
- fn_3_16C878: 21 ARG_MISMATCH (14 rodata-label, 7 register), 1 INSERT/1 DELETE.
- fn_3_16CC2C: 42 ARG_MISMATCH (28 rodata-label, 14 register - inherits both its own and both inlined fn_3_16C878 copies' mismatches), 2 INSERT/2 DELETE/1 REPLACE.
- processBallFielderCollision: 16 ARG_MISMATCH (12 rodata-label, 4 register), 2 OP_MISMATCH, 1 DELETE/2 INSERT - all consistent with the rodata-ownership gap; no other identified source-level issue remains.

## Session: SQRT2_LINKAGE / function-order / data-ownership

  [H8] added `#define SQRT2_LINKAGE static` as the first line of the .c (removes the two extra dolsqrtf2 local-static doubles, 0.5/3.0, from this unit's .rodata) -> fn_3_16C548 93.06% (unchanged), fn_3_16C878 98.71% (unchanged), fn_3_16CC2C 98.79% (unchanged), checkFielderCollisionPotential 99.40% -> 99.78%, processBallFielderCollision 97.16% -> 97.34%; .text 97.65% -> 97.69%, .rodata 80.90% -> 84.71% (kept, no regressions)
  [H9] reordered the five function *definitions* in the .c into reverse address order (processBallFielderCollision, checkFielderCollisionPotential, fn_3_16CC2C, fn_3_16C878, fn_3_16C548) with no body changes, matching this unit's `reverse_fn_order` compile-order flag -> fn_3_16C548 93.06% -> 93.18%, fn_3_16C878 98.71% -> 98.84%, fn_3_16CC2C 98.79% -> 98.90%, checkFielderCollisionPotential 99.78% -> 100.00%, processBallFielderCollision 97.34% -> 97.73%; .text 97.69% -> 97.84%, .rodata 84.71% -> 95.24% (kept; sum improved, confirmed fn_3_16C878 still double-inlined into fn_3_16CC2C and checkFielderCollisionPotential still inlined into processBallFielderCollision - no `bl` to either in our disassembly)
  [H10] gave this unit ownership of `lbl_3_data_2A408` (DustParams, 0x40 bytes) by adding a `.data start:0x0002A408 end:0x0002A448` split entry and replacing the `extern DustParams lbl_3_data_2A408;` declaration with a full initialized definition (16 field values from target's `.data` bytes) -> all 5 functions unchanged from H9 (93.18/98.84/98.90/100.00/97.73), new `.data` section now reports 100.00% match, full `report.json`/link/`build.sha1` all still succeed, unit still `NonMatching` in configure.py (kept)

## Data
- `lbl_3_data_2A408` (DustParams, dust-particle-effect tuning table) is now owned/defined in this unit (H10); `.data` section match is 100.00%.
