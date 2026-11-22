# menus/menus/rep_0B08 checkpoint

Baseline (session 1 start): report fuzzy 73.70%, 46/132 at 100%; objdiff .text 73.14, .rodata 89.49, .data 0.0
After session 1 (commit 3eaa4de2): report fuzzy 91.17%, 90/132 at 100%; .text 91.00, .rodata 89.49, .data 0.0

## File-wide findings (session 1)
- Slot table at lbl_2_bss_1A8248 + 0x1610 (stride 0xD8): access via `Rep0B08Slot` struct
  through a CAST of the `u8 *` global (`MENU->slots[i].f`). A typed `Rep0B08Menu *` extern
  gives the folded `lwz @l` form instead of the target's `addi;lwz 0;addi idx;lbzx` form.
  Exceptions: `SLOTS[i].f` (array view based at +0x1610) gives folded displacements
  (fn_2_6A5A8, one line in fn_2_6BCAC-area); a `Rep0B08Menu *menu = MENU;` local gives
  base-kept folded accesses (fn_2_683EC, fn_2_6A628); the enable helper uses
  `idx * sizeof(Rep0B08Slot)` (unsigned product, not CSE'd with idx*0xD8).
- Animation table at lbl_2_bss_1A824C + 0x197756: typed `Rep0B08Anim *` extern
  (`ANIM->curAnim[n]`) gives the target's `addis; add; lha 0x7756`; a cast gives lhax.
- The draft hand-copied many in-file functions; the target inlines the real ones:
  fn_2_68FBC (set anim state), fn_2_68F24, fn_2_68C80 (range check), fn_2_68B54,
  fn_2_6A450 (set walk target), fn_2_698EC (bounce), fn_2_68F08/68D90 setters,
  fn_2_68670/68690 getters (read into locals before testing), rep0B08TransitionSlot
  (== text_71EC4's fn_2_72054; other unit, kept as static helper here).
- Return types: fn_2_68B54/68C80 return u8; 684D0/68670/68690/686B0 return s32 of s8 field.
- Many drafts misread `fcmpo; cror eq,lt,eq; bne` (body runs when x <= 0) as `x > 0`.
  Tool: scratch fcmp.py lists functions whose fcmpo branch sequence differs from target.
- Turn-toward handlers: dead-zone test `(r < 0.02 && r > 0) || (r > -0.02 && r < 0)` first.

## Status (non-100% functions, pct)
pending: fn_2_709A0 53.26, fn_2_6FE6C 73.88, fn_2_705C0 74.82, fn_2_70110 79.41,
fn_2_6DB30 81.36, fn_2_6F104 82.30, fn_2_6E1D0 82.68, fn_2_6EA74 85.31, fn_2_6DE54 85.91,
fn_2_6ACF4 86.72, fn_2_6ED30 88.65, fn_2_6B744 90.43, fn_2_6C988 91.94, fn_2_6E88C 91.96,
fn_2_69E1C 85.5, fn_2_699D4 83.9, fn_2_6A87C 75.6, fn_2_6A708 72.3, fn_2_69554 91.7,
fn_2_69710 95.2, fn_2_6AB3C 91.3, fn_2_6AE08 95.67, fn_2_68A88 94.4, fn_2_68E68 96.95,
fn_2_6B238 95.72, fn_2_6CDD4 97.77, fn_2_71098 98.38, fn_2_692D0 99.29
near-miss (register swaps only): fn_2_698EC 99.66 (+ inlined copies 6B024/6B120/6B4FC/6B620
~99.5), fn_2_71A70/71B80/6CBB0 ~99.2 (frameA/frameB regs), fn_2_6FB0C 99.36,
fn_2_6BC0C/6BDE0 99.75, fn_2_689CC 99.15, fn_2_69070 99.80, fn_2_687A4 99.77

## Leads
- fcmp.py still flags 699D4, 69E1C (dead-zone pattern + one `eq,beq`), 692D0, 709A0,
  6A708/6A87C (fcmpu then stw: target stores before compare).
- 6E88C/6ED30/6EA74/6DE54/6DB30/6E1D0/6F104/705C0/70110/6FE6C are 40-120 bytes short:
  look for more inlined helper calls (68C80/684D0/fn_2_689CC nearest point/6A450).
- rep0B08NearestSlotZeroPoint may be fn_2_689CC inlined.

## Hypothesis log
fn_2_698EC 99.66: f2/f3 swap around fneg/fmuls. Tried `1.6f * -(f32)sin(x)` (best),
  split statements (rodata order broke), `-(f32)sin(x) * 1.6f` (identical). exhausted-ish.
fn_2_71B80 99.15: start/frameA/frameB register permutation; declaration-order sweep
  (720 perms) too slow, aborted.
fn_2_6F88C: `fn_2_68670(0)==1 && fn_2_68690(0)==idx` in one condition hoists badly;
  reading both into locals inside `if (idx >= 2 && idx <= 6)` matched (applied to 7 copies).

## Session 2 (Opus)
Start 91.17% (90/132). Commits 8ba7674b, 3de0854a -> 94.90% (94/132).
- fn_2_4A2C4 returns s32 (real def rep_08E8.c); s16 local prototype cost extsh in 69E1C/69710.
- Turn-step ladder ends `else if (a < 0.0174533f)` (no plain else); squared terms as two
  statements (`f32 squaredX = dx*dx; f32 squaredZ = dz*dz;`) avoid fmadds; PSMTXRotRad before v init.
- `cror eq,lt,eq; beq skip` => `if (!(x <= 0.0f))`; plain `blt skip` for `!(x < k)`.
- Inlined helpers in 709A0: fn_2_68C80 (BOOL hit = ...; clrlwi then cmpwi), fn_2_689CC(0),
  rep0B08TransitionSlot, new static inlines rep0B08TurnToSlot / rep0B08FacingTarget.
- 6A87C == {unkBB=0; fn_2_6A708(); fn_2_6A628();}. 6A708: input as
  `(s8)AtBat_ButtonInput1[(s8)ANIM->unk197863 * 0x20 + 0x10]`, cached slot pointer.
- fn_2_689CC: declare `s32 i;` before `s32 bestIdx = 0;`.
REAL BUGS fixed: 69710 swapped clamp arms; 709A0 swapped 699D4/69E1C call, waypoint flag read
 from lbl_2_bss_1A8248+0x783D instead of ANIM->unk19783D and arms swapped.
fn_2_69E1C 99.55: unk9E decrement `cmpwi` vs our `extsh.`; switch case 4/8 reloads unkBA
 (tried +=, REP_SLOT(idx)->, MENU->slots[idx]. : no change).
fn_2_6A708 98.67 / 6A87C 99.13: f1/f2 swap of -1.0 const vs v.x (tried *=, -1*v, z first(kept), comma).
fn_2_709A0 99.75: kind-block register naming (tried base local variants, direct expr).

## Session 2 end state (Opus): report 99.88% (127/132), .text 99.88, .rodata 100, .data 100
| function   | status    | pct    |
|------------|-----------|--------|
| fn_2_68E68 | exhausted | 96.95% |
| fn_2_6F104 | pending   | 98.45% |
| fn_2_6A708 | exhausted | 98.67% |
| fn_2_6A87C | exhausted | 99.13% (inherits 6A708 inline) |
| fn_2_6E1D0 | pending   | 99.50% |
All other functions matched (readability pass: done for the functions touched this session;
`kind == 5` (bss+0x441C) and fn_80062890's 0/1 argument are enum/bool-shaped but unproven).
Additional findings (session 2, later):
- `x / 2.0f` emits `fmuls x, 0.5` with x as first operand (68A88); `0.5f * x` / `x * 0.5f` both emit const-first.
- `obj->unk8C += 0.1` (no cast) vs `= (f32)(obj->unk8C + 0.1)`: different fp reg order (6BC0C).
- Reusing float params for the offsets (`x = pos.x - x`) or `x -= pos.x` fixed 69070/69554.
- 698EC: `f32 s = (f32)sin(a); f32 out = 1.6f * -s;` matches standalone + 4 inlined callers.
- rep0B08EnableObj(obj) (reads obj->index inside) reproduces the `lwz r8; ...; mr r28, r8` index copy.
- unkC6/unkCF are s8 sentinels (-1).
fn_2_68E68 log: decl order of slot/dst (3 perms) worse; typed actor struct cast 79.6%; reverted.
fn_2_6A708: `/ -1.0f` 82%; Vec types = same; f2/f8 vs f1/f7 register naming remains.
fn_2_6E1D0: n/row/chosen register naming (target coalesces row with chosen); tried decl orders,
 s32 n/chosen/pick, no chosen local (98.1), compare order: no gain.
fn_2_6F104: idx copy (mr r28) + j counter r9 order; EnableSlot vs EnableObj same; zero-init order kept.
