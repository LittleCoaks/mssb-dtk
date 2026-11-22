# m_sound.c grind checkpoint

unit: `game/game/sound/m_sound`  (src/game/sound/m_sound.c)
baseline (session 1 start): .text 0.478%, 38 functions, 21756 bytes, 0 at 100%
sections at baseline: .text 0.478%  |  .rodata 46.51% (264 B)  |  .bss 0.00% (152 B target, 0 B ours)

after session 1 batch A (5-function cluster: fn_3_8B7DC, fn_3_8B964, fn_3_8B804,
fn_3_8B9BC, fn_3_8B718): .text 3.26%, 3 functions at 100%, 2 functions at
99.39%. .rodata 50.00% (264 B), .bss unchanged at 0.00%.

after session 1 batch B (rodata extern fix + 7-function cluster:
fn_3_8B2E4, fn_3_902FC, fn_3_906FC, initializeSounds, fn_3_8F1C8,
newAtBatPlaySound, transitionToReplay): .text 5.46%, 9 functions matched,
3 functions pending (fn_3_8B718 99.59%, transitionToReplay 95.29%,
fn_3_906FC 0.00% — full-unroll mismatch, see hypothesis log).
.rodata 48.28% (264 B, dropped slightly due to a literal-pool naming
side effect described below), .bss 89.47% (136 of 152 B; lbl_3_bss_1760,
_1764, _176C are still undeclared/unused by any implemented function).

NOTE: 12 of the 38 functions were entirely absent from the .c file at session 1 start.
All 12 are now present (7 implemented this batch, 5 in a prior batch by another
worker/pass — check the table for exact per-function status).
Unit .bss (152 B) is all file-local: lbl_3_bss_1760(4), _1764(4,float), _1768(4,
now declared as `static DrawingSceneStruct*`), _176C(8,float), _1774(0xC, now
declared as `static s32[3]`, only index 0 used), _1780(0x78, now declared as
`static s32[30]`, only index 0 used). _1760/_1764/_176C remain undeclared
(no function in this unit reads/writes them yet).

session 2 resume (after commit 2c9365b): .text 6.08%, 9 matched

session 2 batch D (Task 1 exhausted, no change; Task 2: 5 absent functions
implemented): .text 9.05%, 15 functions matched (up from 11 at the start
of this batch), .rodata 46.51% (264 B, unchanged), .bss 89.47% (unchanged).
`playSoundEffect`'s declaration in `include/game/UnknownHomes_Game.h` was
corrected from `extern void playSoundEffect(int);` to
`extern u32 playSoundEffect(u16);` (see hypothesis log) — full `ninja`
(no target) rebuilt exactly the 4 dependent units and finished clean; all
4 units' own match% verified unchanged from their last-committed values.

## status

| function                           | bytes | status    | pct    |
|------------------------------------|-------|-----------|--------|
| fn_3_8B7DC                         |    40 | matched   |100.00% |
| fn_3_902FC                         |    44 | matched   |100.00% |
| fn_3_8B2E4                         |    52 | matched   |100.00% |
| initializeSounds                   |    68 | matched   |100.00% |
| fn_3_8F1C8                         |    84 | matched   |100.00% |
| fn_3_906FC                         |    88 | matched   |100.00% |
| fn_3_8B964                         |    88 | matched   |100.00% |
| playSoundEffect                    |   104 | matched   |100.00% |
| playCharacterSound                 |   116 | pending   | 77.03% |
| newAtBatPlaySound                  |   116 | matched   |100.00% |
| fn_3_903B8                         |   124 | matched   |100.00% |
| fn_3_90674                         |   136 | matched   |100.00% |
| transitionToReplay                 |   136 | pending   | 95.15% |
| fn_3_8B804                         |   140 | matched   |100.00% |
| addToCircularBuffer                |   140 | pending   | 96.43% |
| playOverSounds                     |   144 | matched   |100.00% |
| fn_3_8BDF4                         |   152 | pending   | 83.13% |
| fn_3_8B9BC                         |   164 | matched   |100.00% |
| fn_3_8D9C0                         |   192 | pending   | 98.96% |
| fn_3_8B718                         |   196 | matched   |100.00% |
| fn_3_90150                         |   208 | pending   | 46.92% |
| updateAndRemoveStadiumEmitter      |   212 | pending   |  1.89% |
| fn_3_8C4F0                         |   216 | pending   |  1.85% |
| callSfx                            |   236 | pending   |  1.69% |
| fn_3_9056C                         |   264 | absent    |  0.00% |
| animateThrownBall                  |   264 | pending   |  1.52% |
| fn_3_90434                         |   312 | absent    |  0.00% |
| updateOrRemoveEmitter              |   356 | pending   |  1.12% |
| fn_3_8C104                         |   472 | pending   |  0.85% |
| initializeCamera                   |   496 | pending   |  0.81% |
| fn_3_8C2DC                         |   532 | pending   |  0.75% |
| initializeStadiumObjectEmitter     |   560 | pending   |  0.71% |
| adjustBallSoundEffectBasedOnHeight |   664 | pending   |  0.60% |
| stadiumMusic                       |  1024 | absent    |  0.00% |
| makeSoundOfBallBouncing            |  1964 | pending   |  0.20% |
| soundFxRelated                     |  2544 | pending   |  0.16% |
| handleGameSound                    |  3148 | pending   |  0.13% |
| soundControl                       |  5960 | pending   |  0.07% |

## data sections

.text: 5.46% (of 21756 B)
.rodata: 48.28% (264 B) — `lbl_3_rodata_157C`/`lbl_3_rodata_1580` are now
declared `extern const f32` (not defined) since this TU only references
them; both affected functions improved (see hypothesis log). Remaining gap
is other not-yet-authored rodata (strings/floats) belonging to unimplemented
functions.
.bss: 89.47% (136 of 152 B) — lbl_3_bss_1768 (DrawingSceneStruct*), _1774
(s32[3], only [0] used), _1780 (s32[30], only [0] used) now declared and
byte-matching. lbl_3_bss_1760 (4B), _1764 (4B, float), _176C (8B, float)
remain undeclared — no function in this unit's currently-implemented set
touches them.

## hypothesis log

Session 1 batch A (cluster: fn_3_8B7DC, fn_3_8B964, fn_3_8B804, fn_3_8B9BC, fn_3_8B718):
(see prior log entries below, unchanged)

- `sndEmitter` (.bss:0x00032B20, size 0x2138, listed in symbols.txt, NOT part of
  this unit's own 152-byte .bss) is a composite object: an embedded SND_LISTENER
  at offset 0x0 (size 0x90, matches `sizeof(SND_LISTENER)` exactly), followed by
  `SND_EMITTER emitters[100]` at 0x90 (stride 0x50 == `sizeof(SND_EMITTER)`
  exactly, verified via fn_3_8B804's loop), an unproven 0x64-byte gap at 0x1FD0,
  a `u8 emitterActive[100]` flag array at 0x2034 (verified: byte-indexed,
  0/nonzero only), and an unproven 0xA0-byte tail at 0x2098. 0x90+100*0x50+0x64+
  100+0xA0 = 0x2138 exactly, so the two gaps' *sizes* are proven even though
  their *contents* are not — do not assume they are unused/padding.
  Declared `extern` in m_sound.c (owned by a different, not-yet-decompiled TU).
- musyx.h declares the SND_LISTENER/SND_EMITTER/SND_FVECTOR/SND_ROOM struct
  types but does NOT declare prototypes for `sndRemoveListener`,
  `sndUpdateListener`, `sndAddListener`, `sndCheckEmitter`, `sndRemoveEmitter`
  (only their definitions exist in src/Musyx/snd3d.c). Had to add local
  prototypes directly in m_sound.c (not touching musyx.h, per task scope).
- `lbl_3_data_8D70` (.data, size 0xC) and `lbl_3_data_88AC` (.data, size 0xC)
  are foreign globals (owned elsewhere, referenced but not defined here).
  Declared `extern SND_FVECTOR lbl_3_data_8D70;` and `extern f32
  lbl_3_data_88AC;` (only element 0 of the latter is read).
- `returnFloatFromModeIndex(0)` (already implemented elsewhere) returns
  `camera_803c639c_s*`; fields used here: `eye` (Vec, offset 0x70) and
  `target` (Vec, offset 0x7C), both already named in
  include/static/UnknownHomes_Static.h.
- Field-by-field float copy (`pos->x = cam->eye.x; ...`) was required for
  fn_3_8B718 instead of `*pos = cam->eye;` — the latter compiles to a
  raw word (lwz/stw) struct copy while the target uses per-field float
  loads/stores (lfs/stfs); this is a real, reproducible codegen difference
  for `Vec`-sized struct assignment vs. field-by-field, not a numeric one.
- In fn_3_8B9BC, local variable declaration order (`heading` before `dir`)
  had to match the *reverse* of first-use order to get the target's stack
  slot layout (heading at sp+0x14, dir at sp+0x8) and store order.

Session 1 batch B (rodata extern fix; fn_3_8B2E4, fn_3_902FC, fn_3_906FC,
initializeSounds, fn_3_8F1C8, newAtBatPlaySound, transitionToReplay):

- [1] `lbl_3_rodata_157C`/`lbl_3_rodata_1580`: changed `static const f32 x =
  <lit>;` (definition form, DISPROVEN per docs/matching_notes.md) to `extern
  const f32 x;` (declaration only, no definition in this TU) -> fn_3_8B9BC
  99.39% -> 100.00% (kept). fn_3_8B718 99.39% -> 99.39% unchanged by the
  extern switch alone (one of its two `lbl_3_rodata_157C` references still
  folds to an anonymous literal-pool symbol `@204` even with the extern
  form; the other resolved to the named symbol — same anonymous-pool
  artifact documented in the prior session, not fully explained).
- [2] fn_3_8B718: flipped `PSVECMag(lookDir) != 0.0f` to use the named
  constant, `lbl_3_rodata_157C != PSVECMag(lookDir)` -> 99.39% -> 99.59%
  (kept). The remaining diff is a single `fcmpu cr0,f1,f0` vs our `f0,f1`
  operand-order mismatch tied to the same literal-pool identity question.
- [3] fn_3_8B718: tried both comparison operand orders,
  `PSVECMag(lookDir) != lbl_3_rodata_157C` and
  `lbl_3_rodata_157C != PSVECMag(lookDir)` -> both scored identically
  99.59% (kept the `PSVECMag(...) != lbl_3_rodata_157C` form as more
  idiomatic). Not chasing the residual fcmpu-operand/anonymous-pool
  artifact further without a repo-wide precedent (per prior session's
  note).
- `sound_crowd_EffectsStruct` (declared in include/game/UnknownHomes_Game.h
  as an anonymous struct typedef'd to a global of the same name, fields
  named `_00`.._34) is the struct behind Ghidra's synthetic field names in
  this cluster. Field-offset map resolved from target asm (see below).
  NOTE: the header has a pre-existing offset-comment bug — both `_08` and
  `_0C` are commented `/* 0x08 */`; `_0C`'s comment should read `/* 0x0C */`.
  Not fixed this session (out of scope: task said report, don't touch the
  header). All widths (u32 for `_00`.._1C, s16 for `_20`/`_22`/`_24`, u8 for
  `_26`..`_34`) match the access opcodes seen (lwz/stw, lhz/sth, lbz/stb)
  and were NOT changed.
- Ghidra field-name -> struct-offset -> width -> repo field map (all
  resolved from this cluster's target asm, cross-checked against two or
  more call sites where possible):
  - `field1_0x4`         -> 0x04 -> u32 -> `_04`
  - `field2_0x8`         -> 0x08 -> u32 -> `_08`
  - `field3_0xc`         -> 0x0C -> u32 -> `_0C`
  - `field4_0x10`        -> 0x10 -> u32 -> `_10`  (a synth voice id; passed to `sndFXKeyOff`)
  - `field5_0x14`        -> 0x14 -> u32 -> `_14`  (a synth voice id; passed to `sndFXKeyOff`)
  - `currentSfx`         -> 0x18 -> u32 -> `_18`
  - `chargeSoundRelated` -> 0x1C -> u32 -> `_1C`
  - `field8_0x20`        -> 0x20 -> s16 -> `_20`
  - `field9_0x22`        -> 0x22 -> s16 -> `_22`
  - `field11_0x26`       -> 0x26 -> u8  -> `_26`
  - `field13_0x28`       -> 0x28 -> u8  -> `_28`
  - `field14_0x29`       -> 0x29 -> u8  -> `_29`
  - `playSoundInd_`      -> 0x2A -> u8  -> `_2A`
  - `field20_0x2f`       -> 0x2F -> u8  -> `_2F`
  - `someCountDown`      -> 0x33 -> u8  -> `_33`  (order-inferred from
    initializeSounds' store sequence: the 10th and final -1/0 stores map
    1:1 onto `_04,_08,_2F,_33` in that exact instruction order)
  - `field0_0x0` (fn_3_906FC only) -> 0x00 -> u32 -> `_00` (holds a raw
    address value, used both as a base pointer for a relocation-style loop
    and copied verbatim into `lbl_3_bss_1774[0]`)
- `PTR_DSS_Head2_31__aFunctionPointer_80862848` (Ghidra) is `lbl_3_bss_1768`,
  declared `static DrawingSceneStruct*` (from include/Unknown/File_0x800b0a14.h).
  `FUN_806ca128` (the callback Ghidra shows going into
  `insertGraphicDrawingFunction`) is `fn_3_8B094`, the last function of the
  *preceding* unit (`game/baserunning/runner.c`, ends exactly at this unit's
  `.text` start 0x8B094) — it has no header prototype yet (not implemented
  there), so a local `extern void fn_3_8B094(void);` was added in m_sound.c.
  `INT_80862860` (Ghidra) is `lbl_3_bss_1780[0]`; `PTR_PTR_DAT_80862854`
  (Ghidra) is `lbl_3_bss_1774[0]`.
- [4] initializeSounds: first attempt wrote `lbl_3_bss_1780[0] = -1;` as the
  FIRST statement (source order matching the target's store-order, which
  stores to the bss scalar before any struct field) -> 95.59% with r3/r4
  swapped throughout every instruction (pure register-naming mismatch,
  target: struct base=r4, bss base=r3; ours: struct base=r3, bss base=r4).
  [5] moved the bss store to be the SECOND statement (struct field `_0C`
  first) -> 100.00% (kept). Register-allocation for two independent global
  base-address materializations in the same block is sensitive to which
  one is referenced first in source, but not in the direction one would
  naively guess (first-referenced got the HIGHER register number here).
- fn_3_8F1C8, newAtBatPlaySound: matched 100% on the first attempt, direct
  field writes/calls in target instruction order, no register-allocation
  surprises.
- fn_3_8B2E4: matched 100% on the first attempt; identical body shape to
  the tail of fn_3_8F1C8 (`lbl_3_bss_1768 = insertGraphicDrawingFunction(
  fn_3_8B094, 0);`) but as a whole standalone function.
- fn_3_902FC: matched 100% on the first attempt; single call
  `sndVolume(0, 10, 0xff);` (musyx.h already declares `sndVolume(u8,u16,u8)`).
- transitionToReplay: [1] cached the global pointer into a local `u8*
  scratch` and a combined `entry` pointer for the three trailing byte
  stores -> 62.71%, with the target showing it re-reads
  `lbl_3_bss_1768`'s VALUE from memory via a cached ADDRESS-of-the-global
  register on every use instead of caching the pointer's value in a local.
  [2] rewrote every access as `((u8*)lbl_3_bss_1768)[literal]` directly
  (no local caching of the pointer value) -> 95.29% (kept). Matches the
  target's repeated-global-reload pattern exactly except for: (a) internal
  register-numbering in the `(index+1)%14` magic-number division sequence
  (target keeps the running temp and final result in r0, ours in r3 — a
  pure temp-register-naming difference with no correctness difference),
  and (b) `add rD, r0, r7` vs our `add rD, r7, r0` operand order on the
  three trailing pointer+offset computations (also purely commutative/
  register-naming). [3] tried `next` declared `u32` with an explicit
  `(u8)next` cast at the store site (Ghidra types `uVar2` as `uint`) ->
  92.65% (reverted — this DROPPED the target's `clrlwi` truncation
  instruction entirely, which only reproduces from an actual `u8`-typed
  local). [4] tried computing `next` via `(u32)(index + 1) % 14` (explicit
  widen-then-mod) with `next` still `u8` -> 83.03% (reverted — much worse,
  extra widening instructions). [5] tried reordering the local variable
  declarations (`u8 index; s32 offset; u8 next;`) -> 95.29%, no change.
  [6] tried expressing the trailing stores as `*((u8*)lbl_3_bss_1768 +
  offset + literal) = val;` (pointer-arithmetic-first) instead of array
  subscript `[offset + literal]` -> 95.29%, no change (kept the array-
  subscript form as more idiomatic). Stopping at 95.29%; the residual is
  pure register/operand-order noise in a magic-number division sequence,
  not a structural difference.
- fn_3_906FC: [1] direct translation of Ghidra's `for (i=0; i<count; i++)`
  with `count` set via a ternary based on
  `g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE`, with the
  `lbl_3_bss_1774[0] = base;` store placed FIRST (matching Ghidra's
  displayed statement order) -> 0.00%; MWCC auto-unrolled the loop into an
  8x-unrolled `mtctr`-based body (target has NO `mtctr`/`bdnz` at all — a
  plain `cmpw`/`blt` loop). [2] replaced the ternary with an explicit
  `if/else`-shaped assignment (`count = 0x14; if (...) count = 1;`) ->
  still 0.00%, still fully unrolled — no change. [3] added
  `#pragma opt_unroll_factor_limit` (seen used once elsewhere in the
  codebase, `src/Unknown/File_0x800a64e0.c`) immediately before the
  function -> no effect, still unrolled, 0.00%. [4] moved the
  `lbl_3_bss_1774[0] = base;` store to AFTER the loop (target's asm
  actually places this store at the very end of the function, not the
  start — Ghidra's displayed statement order does not match the real
  instruction order here) -> still 0.00%, still unrolled, but is the
  logically-correct statement order and was kept regardless of score.
  [5] rewrote the `for` as an explicit `i = 0; while (i < count) { ...;
  i++; }` per the "for+break -> 5x-unrolled, while -> mtctr=trip, no
  unroll" pattern documented elsewhere in this repo -> still 0.00%, still
  8x-unrolled the same way. Exhausted 5 structurally distinct attempts
  without suppressing the auto-unroll; kept the version with the
  logically-correct (post-loop) store order as the final state. The
  target's failure to unroll a loop whose trip count MWCC can clearly
  bound to [1,20] (same range our code exposes) remains unexplained; likely
  needs a different loop-bound representation (not a plain `int` count
  variable) that this session did not find.

## Session 2

- fn_3_906FC: [1] rewrote the loop bound as an inline ternary evaluated
  directly in the `for` condition (`for (i = 0; i < (g_d_GameSettings.
  GameModeSelected == GAME_TYPE_PRACTICE ? 1 : 0x14); i++)`) instead of
  hoisting it into a `count` local before the loop, body `*p = base + *p;`
  -> 99.55%, one instruction mismatch: `add r0, r0, r6` (target) vs
  `add r0, r6, r0` (ours) — pure commutative operand order. Because the
  bound expression is re-evaluated from source on every iteration (rather
  than being a loop-invariant local), MWCC could no longer prove the trip
  count constant across the pointer-store aliasing the loop and stopped
  auto-unrolling entirely — this alone fixed the 0.00% structural
  mismatch from session 1. [2] flipped the add operand order to `*p +=
  base;` (loads `*p` first, matching target's `lwz r0,0(r5)` then
  `add r0,r0,r6`) -> 100.00% (kept). Final form keeps the post-loop
  `lbl_3_bss_1774[0] = base;` store from session 1's [4].
- addToCircularBuffer: tried removing the `goto` per the readability rule
  before touching anything else.
  [1] structured nesting, no goto (`if (lbl_3_bss_1768 != NULL) { ...
  if (tail != next) { ...; return TRUE; } } return FALSE;`) -> 84.43%
  (transitionToReplay 95.00%, unchanged) — the target has ONE shared
  `li r3,0; blr` exit block reached from both the null-check and the
  tail-check; the goto-free nested form does not merge these and instead
  DUPLICATES `li r3,0; blr` at the very end of the function (visible as a
  `DIFF_INSERT` of a second `li r3,0x0 / blr` pair with no matching
  target instructions) — this is the exit-block-threading case the
  project's goto guidance describes, so the goto stays.
  [2] same nested form but with `if (q->tail != (u8)((head+1)%CAP))` and
  no `next` local, storing `(head+1)%CAP` again inline for `q->head = ...`
  -> 87.71% (worse than [1] — the modulo chain is now duplicated in the
  compiled code since nothing forces CSE across the branch, in addition to
  the same duplicated-exit problem). Both goto-free attempts reverted;
  goto form restored (matches session 1's structure exactly).
  [3] on top of the restored goto form: added a `u8 tail` local read
  immediately before the comparison, still `if (tail == next)` — 96.29%,
  no change from session 1's baseline (register-allocation in the modulo
  chain unaffected). [4] reverted the `tail` local, instead just swapped
  the comparison operand order at the same call site: `if (next == lbl_3_
  bss_1768->tail)` instead of `if (lbl_3_bss_1768->tail == next)` ->
  96.43% (kept; transitionToReplay 95.15%, both up slightly from session
  1's 96.29%/95.00%). Diff after this change is a single-instruction
  register-naming cluster in the `(head+1)%14` magic-constant division
  (target keeps the whole chain in r0 and `tail` in r8; ours keeps the
  chain in r6 and reads `tail` into r0) — tried explicit `tail`/`next`
  local declared before vs after `head`, `tail` read before vs after
  `head`, and `(1 + head) % CAP` vs `(head + 1) % CAP`; none of these
  moved the register allocator off r6/r0, all scored 96.43% identically.
  Stopping at 96.43%/95.15% — residual is pure register-naming noise in
  a magic-number division sequence with no source-level lever found this
  session, not a structural difference. addToCircularBuffer is 96.43%
  (pending), transitionToReplay is 95.15% (pending) — the goto in
  addToCircularBuffer is kept, evidenced measurably better than every
  goto-free structured alternative tried.
- fn_3_8B718: [1] fixed the `dir->x/y/z = 0.0f;` stores to load from
  `lbl_3_rodata_157C` (the file's existing zero-constant symbol, already
  used the same way in `fn_3_8B9BC`) instead of an anonymous `0.0f`
  literal that the compiler pooled separately -> 99.80%, single remaining
  mismatch: `fcmpu cr0, f1, f0` (target, magnitude-then-constant) vs
  `fcmpu cr0, f0, f1` (ours). Reordering the source comparison operands
  (`lbl_3_rodata_157C != PSVECMag(lookDir)`) had no effect on the emitted
  compare order. [2] introduced an explicit `f32 mag = PSVECMag(lookDir);`
  local, then `if (mag != lbl_3_rodata_157C)` -> 100.00% (kept) — forcing
  the call result into a named local before the comparison, rather than
  comparing the call expression directly, made the compiler load `mag`
  into f1 first and put it as the fcmpu's first operand, matching target.

Session 2, batch D:

Task 1 (addToCircularBuffer inlining hypothesis). All variants measured
against both addToCircularBuffer and transitionToReplay, `--fresh` each
time:
- [1] `static inline u8 nextCircularBufferIndex(u8 i)` helper wrapping
  `(i+1) % SOUND_REPLAY_QUEUE_CAPACITY`, called as `next =
  nextCircularBufferIndex(head);` -> 96.43% / 95.15% (unchanged, reverted).
- [2] same helper with `s32`/`s32` signature instead of `u8`/`u8` -> 96.43%
  / 95.15% (unchanged, reverted).
- [3] hoisted `tail` into its own local read before the modulo computation
  (`tail = lbl_3_bss_1768->tail; next = (head+1)%CAP; if (next == tail)`)
  -> 96.43% / 95.15% (unchanged, reverted) — confirmed via `asm` listing
  that the instruction sequence is byte-for-byte identical to the
  pre-change baseline; source-level statement reordering has zero effect
  on this specific register-color assignment.
- [4] `static inline BOOL circularBufferIsFull(u8 head, u8* nextOut)`
  computing `next` via an out-parameter and returning the tail comparison,
  called as `if (circularBufferIsFull(head, &next))` -> 96.43% / 95.15%
  (unchanged, reverted).
- [5] verified full revert to the exact prior text; `asm addToCircularBuffer
  --fresh` and `asm transitionToReplay --fresh` byte-identical to the
  pre-Task-1 listings, `git diff` shows only the pre-existing (already in
  working tree before this session) `next == tail` operand-order and
  `fn_3_8B718`/`fn_3_906FC` edits, nothing from Task 1 survives.
- Conclusion: standing prior (register mismatch => try inlining) does not
  apply here; MWCC's register allocator assigns r0 vs r6 for this specific
  16-way-unsigned-division-by-14 magic-constant sequence based on something
  not reachable from any of the four structural variants tried. Kept the
  original (pre-session) source unchanged; addToCircularBuffer stays at
  96.43%, transitionToReplay stays at 95.15%, both still pending.

Task 2 (five absent functions). Ghidra fetched for playCharacterSound,
playSoundEffect, playOverSounds (saved sessions ago); fn_3_903B8 and
fn_3_90674 could not be fetched this session (Ghidra HTTP endpoint at
127.0.0.1:8080 was unreachable — connection refused on every retry), so
both were written directly from the target `asm --fresh` listing instead
(no Ghidra source available/saved for these two).

- playOverSounds(int param): matched 100.00% on the first attempt —
  `if (param < 0) param = 3000;` then two `sndSeqGetValid`/`sndSeqVolume`
  guarded calls against `sound_crowd_EffectsStruct._04`/`_08`, final arg
  `SND_SEQVOL_STOP`.
- fn_3_903B8: matched 100.00% on the first attempt — same shape as
  playOverSounds but with a fixed `0xa0` time argument instead of a
  parameter (no existing named constant found for `0xa0` in this
  context; grepped all `sndSeqVolume(` call sites in the repo, none use a
  named constant for the time argument either).
- fn_3_90674(int index): [1] initial version stored `sndSeqPlayEx(...)`'s
  result into a local `SND_VOICEID vid` used both for the
  `sound_crowd_EffectsStruct._04` store and the following
  `sndSeqVolume` call -> 84.12%, single remaining register-order mismatch
  around the store/`mr` sequence (register-only, not structural — same
  general class as the Task 1 residuals). [2] removed the `vid` local
  entirely: `sound_crowd_EffectsStruct._04 = sndSeqPlayEx(...); sndSeqVolume(...,
  sound_crowd_EffectsStruct._04, ...);`, reading the field back out of the
  struct for the second call instead of keeping the call result in a named
  local -> 100.00% (kept). Needed new types/externs: `SeqPlayEntry` (6-byte
  stride: `u16 sgid; u16 sid; u16 _04;`) over `lbl_3_data_88E0[]`; the
  existing `lbl_3_bss_1774[0]` (declared `s32` elsewhere in this file)
  reinterpreted here via `(void**)lbl_3_bss_1774[0]` as a pointer to an
  array of `void*`, one per `index`; `extern u8 lbl_3_data_830C[]`, a
  2-byte-stride table indexed `[index*2]` for the volume byte (only the
  first byte of each 2-byte entry is read by this function; the second
  byte's meaning is unproven).
- playSoundEffect(u16 soundNumber): stuck at 71.54% after 5 structurally
  distinct attempts, all measured via `asm --fresh`:
  [1] `u16` param, single `u8* entry = (u8*)lbl_3_data_8338 +
  soundNumber*2;` local, `entry[-0x2A2]`/`entry[-0x2A1]` indexing ->
  71.54% (best found; kept).
  [2] `int` param instead of `u16`, same body -> 62.08% (worse; reverted).
  [3] `SfxParam{u8 vol; u8 ctrl;}` struct-typed `lbl_3_data_8338[]` indexed
  by element (`&lbl_3_data_8338[soundNumber - 0x151]`, exploiting
  0x2A2/2==0x151) instead of raw byte-pointer arithmetic -> 58.81% (worse;
  reverted).
  [4] `int` param with a separate `SND_FXID fid = soundNumber;` local
  passed to `sndFXStartEx`, keeping `soundNumber` raw for the pointer
  arithmetic -> 62.08% (same as [2]; reverted).
  [5] `u16` param, `entry` recomputed twice (once per read, no shared
  local) instead of reused -> 71.54% (identical to [1]; compiler CSEs it
  back to the same code either way).
  Remaining diff at 71.54% is `clrlslwi r5,r3,16,1` (mask+shift fused into
  one instruction) where target has an unmasked `slwi r31,r3,1` followed
  by a separately-scheduled `clrlwi r3,r3,16` right before the call — i.e.
  target's parameter behaves as if raw/unmasked for the pointer arithmetic
  but gets explicitly masked only at the `sndFXStartEx` call site. No
  variant of parameter width/cast placement tried reproduced that specific
  split. Kept variant [1] (71.54%, pending) since it strictly beats every
  other attempt tried.
- playCharacterSound(int charID, int soundCode): stuck at 67.21% after 4
  structurally distinct attempts:
  [1] `ctrlPtr` computed first, then `fid`, then `vol`, then `ctrlValue =
  *ctrlPtr;`, `vid = sndFXStartEx(fid, vol, 0x3f, 0);` -> 67.21%.
  [2] same but `vol` read before `fid` (matching target's
  lhzx-then-lbzx-then-add read order) -> 67.21% (byte-identical asm to
  [1]; no effect).
  [3] removed the `fid`/`vol`/`ctrlValue` locals entirely, inlining all
  three expressions directly into the `sndFXStartEx`/`sndFXCtrl` calls,
  keeping only `ctrlPtr` and `vid` -> 52.76% (worse; reverted — the
  compiler deferred `ctrlPtr`'s address computation to after the
  `sndFXStartEx` call instead of hoisting it, unlike target).
  [4] verified revert to variant [1]/[2]'s text (identical either way) ->
  67.21% (kept, pending).
  Remaining diff is charSoundFxVol/characterSoundArray base-address
  register numbers (target: r7/r6 fixed early and reused as r8; ours:
  r6/r5 reused as r6) — same unresolved register-color class as Task 1 and
  playSoundEffect's residual; no source-level lever found this session.
- New externs/types added (foreign data, none owned by this TU):
  `u16 characterSoundArray[54]`, `u8 charSoundFxVol[12]`,
  `u8 lbl_3_data_8338[]` (anonymous target-side symbol, addressed via
  fixed negative byte offsets `-0x2A2`/`-0x2A1` from a co-located, unnamed
  2-byte-stride table — same "anonymous literal-pool" class documented in
  session 1's rodata notes, just for `.data` instead of `.rodata`),
  `SeqPlayEntry` struct + `lbl_3_data_88E0[]`, `u8 lbl_3_data_830C[]`,
  local prototype `bool32 sndSeqGetValid(s32 unk);` (declared in
  `src/Musyx/seq_api.c`, not in any header, same pattern as the existing
  `sndRemoveListener`/`sndAddListener`/etc. local prototypes in this file).
  Added `#include "musyx/seq.h"` for `sndSeqVolume`/`sndSeqPlayEx`/
  `SND_SEQVOL_STOP`/`SND_SEQVOL_CONTINUE`.
- `playSoundEffect` signature correction: was `extern void playSoundEffect(int);`
  at `include/game/UnknownHomes_Game.h:2874` (a real, pre-existing
  declaration used by ~25 call sites across the repo, not a placeholder).
  Target asm proves it returns the `sndFXStartEx` voice id and the
  parameter is used unmasked for pointer arithmetic before being masked to
  16 bits only at the call site (see variant notes above) — changed to
  `extern u32 playSoundEffect(u16);`, matched identically in
  `include/game/sound/m_sound.h`. All existing call sites pass integer
  literals and discard the return value, so this is a narrowing
  return-type/param-type correction, not a behavior change; ran the full
  `ninja` build afterward (no target given) — it rebuilt exactly the 4
  files that include `m_sound.h` transitively via `UnknownHomes_Game.h`
  (`pitcher.o`, `stadium_bowser_castle.o`, `stadium_framework.o`,
  `stadium_wario_palace.o`) and finished clean. Cross-checked each of
  those four units' own `.text` match% via `objdiff-cli diff` directly
  (not `report generate`, which this repo's instructions flag as
  sometimes broken) and confirmed all four are unchanged from their
  last-committed values: pitcher 97.82%, stadium_framework 99.21%,
  stadium_wario_palace 93.81% (all three match the exact percentages in
  their respective commit messages), stadium_bowser_castle 9.19% (WIP,
  no prior committed baseline to compare against, but no crash/error).

Session 2, batch E:
- playSoundEffect: replaced the raw `u8*`/negative-offset-into-lbl_3_data_8338
  form with a `SoundEffectMix{u8 volume; u8 reverb;}` struct-typed
  `lbl_3_data_8338[]` extern indexed by `soundNumber - SOUND_EFFECT_MIX_FIRST_ID`
  (0x151, the table's first covered sound id) and changed the parameter from
  `u16` to `int` (matching target's unmasked-until-call-site use).
  [1] struct-indexed form, `int` param -> 100.00% (kept).
- playCharacterSound: removed the `ctrlPtr`/`fid`/`vol`/`ctrlValue` locals,
  rewrote plain, then tried orderings/expression forms:
  [1] `vid = sndFXStartEx(soundCode + characterSoundArray[charID],
  charSoundFxVol[soundCode], 0x3f, 0); sndFXCtrl(vid, SND_MIDICTRL_REVERB,
  charSoundFxVol[CHAR_SOUND_REVERB_OFFSET + soundCode]);` (no locals,
  reverb read inline as 2nd call's arg) -> 52.76% (worse than the prior
  67.21% baseline; compiler deferred the reverb-table address computation
  to after the first call instead of hoisting it; reverted).
  [2] `u8 reverb = charSoundFxVol[CHAR_SOUND_REVERB_OFFSET + soundCode];`
  hoisted before the calls, volume/fid still inlined into the call ->
  67.21% (matches old baseline exactly, byte-identical asm).
  [3] same as [2] plus an explicit `u8 vol = charSoundFxVol[soundCode];`
  local -> 67.21% (identical asm to [2]).
  [4] introduced `u8* p = charSoundFxVol + soundCode;` and read reverb via
  `p[CHAR_SOUND_REVERB_OFFSET]`, volume via `charSoundFxVol[soundCode]`
  (kept as a separate array-index expression, not `*p`) -> 77.03%
  (improvement; compiler CSEs the volume read onto the same pointer
  regardless of whether it's spelled `*p` or `charSoundFxVol[soundCode]` or
  where the statement is ordered — all four sub-variants of this pointer
  approach produced byte-identical asm).
  [5] reordered the four locals every way tried (`fid` before/after `p`,
  `vol` before/after `fid`, `reverb` last vs. second) -> 77.03% every time
  (statement order had no effect once the pointer local exists; MWCC's CSE
  is order-independent here).
  Kept variant [4]/[5] (`reverbTable` pointer + `vol`/`fid`/`reverb`
  locals) at 77.03% — strictly better than every other attempt and than
  the prior 67.21% baseline. Remaining diff: target loads the volume byte
  via indexed addressing (`lbzx r0,r8,r4`, reusing the same base+index
  registers used to form the reverb pointer) where ours emits a
  direct-offset `lbz r4,0x0(r3)` off the already-materialized pointer;
  every C-level spelling tried collapses to the same address in MWCC's
  optimizer, so this residual could not be resolved from source alone this
  session.
- Full `ninja` (no target) ran clean (all objects rebuilt, report/progress
  steps completed, no compiler errors). Re-checked the three other
  m_sound.h-dependent units via `objdiff-cli diff -u <unit> --format json`
  (`.text` `match_percent`, not `report generate`): pitcher 97.82423%,
  stadium_framework 99.21016%, stadium_wario_palace 93.80906% — all
  unchanged from their pre-batch values.

Session 2, batch F: (baseline this batch: 18 at 100%, playCharacterSound
77.03%, addToCircularBuffer 96.43%, transitionToReplay 95.15%, fn_3_8BDF4/
fn_3_8D9C0/fn_3_90150 absent/stub)

Task 1 (playCharacterSound, target 77.03%, 3 more attempts, all reverted,
no net change):
[1] Kept the reverbTable-pointer form but added an explicit
`int csEntry = characterSoundArray[charID];` local read before `vol`,
matching target's lhzx-before-lbzx read order -> 77.03% (byte-identical
asm to the pre-existing kept variant; reordering that read had no effect,
confirming the prior session's finding that MWCC's CSE here is
order-independent).
[2] Replaced `extern u8 charSoundFxVol[12]` with a
`CharacterSoundMix{u8 volume[0x180]; u8 reverb[0x1FC];}` struct extern (the
approach suggested by the task) and rewrote as
`charSoundFxVol.reverb[soundCode]` / `charSoundFxVol.volume[soundCode]`,
no locals -> 67.21% (worse; regressed to the same asm as the no-locals
inline attempts from batch E — reverted, struct removed).
[3] `u8* reverbTable = (u8*)&charSoundFxVol + soundCode;` (address-of a
scalar-typed extern, cast to byte pointer) plus a matching cast for `vol`
-> 67.21% (worse; reverted).
Reverted fully to the pre-batch 77.03% source (`u8* reverbTable =
charSoundFxVol + soundCode; u8 vol = charSoundFxVol[soundCode]; int fid =
soundCode + characterSoundArray[charID]; u8 reverb =
reverbTable[CHAR_SOUND_REVERB_OFFSET];`). Confirmed byte-identical to
session start. No lever found this session either; residual is still the
vol-load addressing-mode split (target: `lbzx r0,r8,r4` indexed off the
base register also used to form the reverb pointer; ours: direct-offset
load off the already-materialized pointer) that MWCC's optimizer produces
regardless of how the two reads are spelled in C.

Task 2 stub fn_3_8BDF4 (152 B, FUN_806cae88) -> 83.13% (pending, kept,
best found):
Ghidra decomp showed this is exactly fn_3_8B804's `emitterActive`/
`sndCheckEmitter`/`sndRemoveEmitter` loop (already 100% in this file) plus
a trailing `sndRemoveListener(&sndEmitter.listener);` call — confirming
the "check whether the target reuses an already-written helper" prior;
here it's inlined body reuse, not a call.
[1] `for` loop identical to fn_3_8B804's body, followed by the
`sndRemoveListener` call -> 83.13% (kept).
[2] same logic as a `while` loop -> 83.13% (byte-identical asm to [1]; no
effect). Kept the `for` form (matches this file's established style for
fn_3_8B804).
Residual: target colors the three loop-carried registers as
r29(emitterActive walk)/r28(emitters walk)/r30(counter), while ours (and
fn_3_8B804's own 100%-matching target) uses r30/r29/r28 for the same three
roles — MWCC picked a different register-coloring for this larger,
5-saved-register function than for the standalone 4-saved-register
fn_3_8B804, despite identical C source for that portion. Purely a
register-allocation-graph difference from the extra trailing call; no
source-level lever found.
Final kept source:
```c
void fn_3_8BDF4(void) {
    int i;

    for (i = 0; i < 100; i++) {
        if (sndEmitter.emitterActive[i]) {
            if (sndCheckEmitter(&sndEmitter.emitters[i])) {
                sndRemoveEmitter(&sndEmitter.emitters[i]);
            }
            sndEmitter.emitterActive[i] = FALSE;
        }
    }
    sndRemoveListener(&sndEmitter.listener);
}
```

Task 2 stub fn_3_8D9C0 (192 B, FUN_806cca54) -> 98.96% (pending, kept,
best found):
Ghidra decomp showed this calls `handleGameSound()` then inlines
fn_3_8B718's pos/dir/lookDir body (unconditionally, using local stack
vectors instead of pointer params with NULL checks) and fn_3_8B964's body
(the `sndUpdateListener` call guarded on `sndEmitter.listener.room`).
[1] Tried calling `fn_3_8B718`/`fn_3_8B964` directly with addresses of
local `SND_FVECTOR`s -> 70.58%; target has no NULL-check branches (`beq`)
since the locals are never NULL, so the real target inlines both bodies
rather than calling them.
[2] Rewrote inlined (no calls to fn_3_8B718/fn_3_8B964), locals typed
`Vec` (not `SND_FVECTOR`, since `PSVECSubtract`/`PSVECMag`/
`PSVECNormalize` require `Vec*` and MWCC rejected the implicit
`SND_FVECTOR*`-to-`Vec*` conversion), cast to `SND_FVECTOR*` only at the
`sndUpdateListener` call site -> 92.60%. Remaining gap at this point was
entirely that `handleGameSound()`'s call got optimized away: `-inline
auto` was inlining the empty-bodied (`{ return; }`) `handleGameSound` even
though it's non-static, since target still emits a real `bl
handleGameSound` for a function whose true 3148-byte body isn't written
yet.
[3] Wrapped `handleGameSound`'s definition in
`#pragma dont_inline on` / `#pragma dont_inline reset` (existing idiom
already used elsewhere in this repo, e.g. `src/Dolphin/os/OSExec.c`) ->
98.96% (kept). This also fixed the call-then-stack-slot-store
interleaving, since the real call now anchors that ordering.
[4]/[5] Tried swapping declaration order of `pos`/`dir` (both as
`dir; pos; lookDir;` and reordering the `dir.x=...` assignment to before
`pos.x=...`) -> 86.40%/98.79% respectively (both worse than 98.96%;
reverted to `pos; dir; lookDir;` declaration order with `pos` fully
assigned before `dir`).
Residual at 98.96%: `f0`/`f1` register-color swap on the `cam->eye.x`
load vs. the `lbl_3_rodata_157C` constant load — a single floating-point
register-coloring difference, no source-level lever found.
Full final kept source:
```c
void fn_3_8D9C0(void) {
    camera_803c639c_s* cam;
    Vec pos;
    Vec dir;
    Vec lookDir;
    f32 mag;

    handleGameSound();
    cam = returnFloatFromModeIndex(0);

    pos.x = cam->eye.x;
    pos.y = cam->eye.y;
    pos.z = cam->eye.z;

    dir.x = lbl_3_rodata_157C;
    dir.y = lbl_3_rodata_157C;
    dir.z = lbl_3_rodata_157C;

    PSVECSubtract(&cam->target, &cam->eye, &lookDir);
    mag = PSVECMag(&lookDir);
    if (mag != lbl_3_rodata_157C) {
        PSVECNormalize(&lookDir, &lookDir);
    }

    if (sndEmitter.listener.room != NULL) {
        sndUpdateListener(&sndEmitter.listener, (SND_FVECTOR*)&pos, (SND_FVECTOR*)&dir,
                           (SND_FVECTOR*)&lookDir, &lbl_3_data_8D70, 0x7f, NULL);
    }
}
```
`handleGameSound`'s own body is unchanged (`{ return; }`); only the
`#pragma dont_inline on`/`reset` wrapping it changed. This pragma also
protects any other future caller of `handleGameSound` in this file from
having the call inlined away before that function gets a real body.

Task 2 stub fn_3_90150 (208 B, FUN_806cf1e4) -> 46.92% (pending, kept,
best found):
Ghidra decomp showed the same `fid`/`vol`/`reverb` shape as
playCharacterSound, but `vol`/`reverb` go through a `(u8)((f32)byte *
scale)` conversion before use (the ghidra "CONCAT44(0x43300000, byte ^
0x80000000) - tfd" text is MWCC's standard unsigned-byte-to-double bias
trick for an ordinary `(float)someU8` cast, not literal source). Also
discovered via address arithmetic (existing `unkCharacterArray` symbol at
.data 0x8148, size 0x20, immediately followed by `characterSoundArray` at
0x8168) that target's relocations for this function all resolve to offsets
from `unkCharacterArray`, not to `characterSoundArray`/`charSoundFxVol`
directly — i.e. `characterSoundArray` is at `unkCharacterArray+0x20`,
`charSoundFxVol` is at `unkCharacterArray+0x3e8`, and a new scale-factor
float lives at `unkCharacterArray+0x6e8` (0x300 bytes into charSoundFxVol's
already-declared-but-oversized span).
[1] Flat externs (`charSoundFxVol`, `characterSoundArray`, a new
`extern f32 lbl_3_data_8830;` for the scale factor at charSoundFxVol+0x300),
`u8* reverbTable` pointer + `u8 vol`/`int fid`/`u8 reverb` locals in
playCharacterSound's exact order, each cast through `(f32)...*
lbl_3_data_8830` -> 46.92% (kept, best).
[2] Same but split into two extra locals (`u8 volByte`/`u8 reverbByte`
holding the raw bytes, converted to float in two subsequent statements)
-> 46.92% (byte-identical asm to [1]; MWCC's cast scheduling is
order-independent here too).
[3] Same as [2] but with explicit `f32 volF = (f32)charSoundFxVol[...]`
locals instead of casting inline at the multiply -> 46.92% (identical).
[4] Modeled the suspected true layout as a single
`CharacterSoundTable{u8 unk_00[0x20]; u16 soundArray[54]; u8 unk_8C[...];
u8 volume[0x180]; u8 reverb[0x180]; f32 volumeScale;}` extern at
`unkCharacterArray`, accessed as `unkCharacterArray.volume[soundCode]`/
`.reverb[soundCode]`/`.soundArray[charID]`/`.volumeScale` -> 43.83% (worse
than [1]; single-base addressing did appear in the asm as hoped, but
instruction scheduling around the float-bias trick got worse overall;
reverted, struct definition removed).
[5] Same struct, but with an explicit `u8* volPtr =
unkCharacterArray.volume + soundCode;` pointer reused for both volume and
`volPtr[CHAR_SOUND_REVERB_OFFSET]` (mirroring playCharacterSound's
pointer idiom) -> 43.83% (identical to [4]; MWCC still collapsed both
field accesses onto one base+soundCode pointer either way; reverted).
[6] `reverbF` read via `charSoundFxVol[soundCode + CHAR_SOUND_REVERB_OFFSET]`
(no separate pointer local) instead of through `reverbTable` -> 33.75%
(worse; reverted).
Kept variant [1]/[2]/[3] (byte-identical, kept as written in [1]'s form)
at 46.92%. Residual is structural: target computes ALL relocations
relative to a single `unkCharacterArray` base register reused across three
different field offsets (0x20/0x3e8/0x568/0x6e8), where our flat-extern
model necessarily emits separate `lis`/`addi` pairs per symbol
(`charSoundFxVol`, `characterSoundArray`, `lbl_3_data_8830`) — modeling it
as one combined struct (attempts [4]/[5]) got the single-base addressing
but scored worse due to float-bias-trick scheduling changes elsewhere in
the function; no combination tried recovered both properties at once.
Final kept source:
```c
extern f32 lbl_3_data_8830;

SND_VOICEID fn_3_90150(int charID, int soundCode) {
    SND_VOICEID vid;
    u8* reverbTable = charSoundFxVol + soundCode;
    f32 volF = (f32)charSoundFxVol[soundCode];
    f32 reverbF = (f32)reverbTable[CHAR_SOUND_REVERB_OFFSET];
    int fid = soundCode + characterSoundArray[charID];
    u8 vol = (u8)(volF * lbl_3_data_8830);
    u8 reverb = (u8)(reverbF * lbl_3_data_8830);

    vid = sndFXStartEx(fid, vol, 0x3f, 0);
    sndFXCtrl(vid, SND_MIDICTRL_REVERB, reverb);
    return vid;
}
```
`fn_3_90150`'s prototype in `include/game/sound/m_sound.h` was changed
from `void fn_3_90150(void);` to
`u32 fn_3_90150(int charID, int soundCode);` (return type/params derived
from the asm signature match with `playCharacterSound`/`sndFXStartEx`'s
return value, same `u32`-typed `SND_VOICEID`). No other file references
`fn_3_90150` yet (grepped `src/`, `include/`), so no other unit was
affected; ran a full `ninja` (no target) afterward anyway since this was a
header change — it rebuilt `pitcher.o`, `stadium_framework.o`,
`stadium_wario_palace.o`, and (already up to date from a concurrent
session) `stadium_bowser_castle.o`, finished clean, and `objdiff-cli diff`
confirmed pitcher/stadium_framework/stadium_wario_palace unchanged at
97.82423%/99.21016%/93.80906%.

Batch F end state: .text 11.09% (of 21756 B), .rodata 50.00% (264 B, up
from 46.51% — a side effect of `lbl_3_rodata_157C` now being referenced
from fn_3_8D9C0's inlined body too), .bss 89.47% (unchanged). 20 of 36
functions at 100% (unchanged from batch E's 18 matched + fn_3_8BDF4/
fn_3_8D9C0/fn_3_90150 newly present but not yet at 100%). playCharacterSound
still 77.03%, addToCircularBuffer still 96.43%, transitionToReplay still
95.15% (none touched this batch, confirmed unchanged via `msdiff.py all
--fresh`).
