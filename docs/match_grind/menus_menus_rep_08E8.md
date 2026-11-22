# menus/menus/rep_08E8 (src/menus/rep_08E8.c)

Baseline (session 1 start): unit 84.45%, .text 83.79%, .rodata 79.07%.

| function    | status  | pct    |
|-------------|---------|--------|
| fn_2_4AEE4  | matched | 100% (report; diff view shows only literal-name relocs) |
| fn_2_4ACF8  | matched | 100%   |
| fn_2_47CFC  | matched | 100%   |
| fn_2_47B24  | matched | 100%   |
| fn_2_48DB4  | matched | 100% (report) |
| fn_2_47FF8  | matched | 100% (report) |
| fn_2_4A340  | pending | 99.40% |
| fn_2_4A234  | pending | 99.58% (untouched) |
| fn_2_49F7C  | pending | 98.28% |
| fn_2_4917C  | pending | 96.36% |
| fn_2_487A0  | pending | 94.90% (untouched) |
| fn_2_481F4  | pending | 95.31% |
| fn_2_477C0  | pending | 90.65% |
| fn_2_46D94  | pending | 90.39% (untouched) |
| fn_2_48A1C  | pending | 89.92% |
| fn_2_4AB1C  | pending | 89.03% |
| fn_2_472C4  | pending | 88.25% (untouched) |
| fn_2_478F4  | pending | 96.19% |
| fn_2_48BE0  | matched | 100% (report) |
| fn_2_47540  | pending | 86.85% (untouched) |
| fn_2_4906C  | pending | 57.43% |

Session 1 end: unit 84.45 -> 95.75%, .text 95.16%, .rodata 76.11% (literal conversions add our own pool entries; whole file needs literals in target order before .rodata can match).

## Hypothesis log

fn_2_4A340 (debug stats-screen fill)
  baseline: 55.55%
  [1] rewrite with real structs (StatsScreenScoresStruct, StatisticsBatter/Pitcher, StatsTableEntryB bitfields), include static/UnknownHomes_Static.h -> same size
  [2] store order: maybeHomeAway[1] + inning=9 at top, bitfield e before d -> 99.40% (kept)
  [3] inner-loop statement orders (4 perms), expression shapes (j+j, (1-i)*12, operand swaps), decl orders -> no gain
  note: draft stored the low byte of &g_d_GameSettings + s*10 into outsAsPitcher (behaviour bug); target stores s*10 + 3*j.

fn_2_4906C
  baseline: 52.53%
  [1] store via ((u16**)base)[i + 0x6550B] -> store side matches; load side via ((TextBank*)((u8*)bank + i*4))->strings[0] -> 57.43% (kept)
  [2] load-side forms strings[i], ((u16**)bank)[i+1], (strings+i)[0], *(u16**)((u8*)bank+4+i*4) -> no better
  next: target loads bank+i*4 then lwz 4(..), no induction var on load side; ours makes 5 extra IVs (304 vs 272 bytes)

fn_2_4AEE4 / fn_2_4ACF8 / fn_2_4AB1C (challenge coin tally siblings)
  baselines: 56.29 / 91.37 / 68.44
  [1] read every global directly (no cached st/b locals), mode byte as *(s8 *)(lbl_2_bss_1A824C + 0x197843) in every test
      (re-emits extsb per test), cache `GameInitVariables *gs = &g_d_GameSettings` before the first call -> 4AEE4 99.94, 4ACF8 97.7
  [2] 4ACF8: the 0x44FD decrement + 0x4429 flag sit after the if-chain, not inside mode 2 (draft behaviour bug) -> 100%
  4AB1C: only residual is the target's dead score clamps (lhz both totals, clamp 0..99 into r0/r4, never used).
    Tried: plain s32 locals, static inline clamp helper, empty inline sink, `if (debug)` dead call, local array -> all DCE'd (88.95 diff view).
    volatile locals (draft) keep it but add stack stores. readability pass: n/a (not matched)

fn_2_47CFC (per-character CTRL transform + pose refresh loop)
  baseline: 73.63%
  [1] both pose blocks are one inline helper applyAnimPose(sub, pose): state = sub + 0xC NULL-checked twice
      (frame store, 1-bit `apply` bitfield at state+0x11 -> rlwimi), fn_80024DB0(state), fn_80024FA4(pose, sub+0x2C, sub + 0xC)
      (re-derived, not the local) -> 93.7
  [2] sub = entry + 0xC04 base pointer for rot (0x40..) / obj (0x30) / flag (0x25D); obj re-read from sub+0x30 at each use -> 98.5
  [3] pose computed by the caller as the 2nd inline arg -> 99.74
  [4] float constants are literals (0.5f, 57.295776f = 0x42652EE0), not the lbl_2_rodata_968/970 externs -> 100% (report)
  readability pass: done (no enum-shaped literals; offsets unnamed - no struct for hugeAnimStruct entries yet)
  NOTE: switching those two to literals adds our own pool entries; unit .rodata% 79.07 -> 73.30 until the whole file uses literals.

fn_2_47B24 (actor anim apply + per-viewport visibility bits)
  baseline: 81.93%
  [1] re-read the actor pointer *(void **)obj at every call (no cached local) -> 96.2
  [2] one `root = *(u8 **)obj` local only for the 0x98 bit RMW; mask as (u8)~(3 << k*3), return as (u8) -> same
  [3] decl order cam/root first -> 98.1
  [4] updateBoneParam flag through a u8 local (s32/BOOL local = 98.1, bitfield struct = 97.6) -> 100%
  readability pass: done

fn_2_49F7C (u16 string insert)
  baseline: 81.12%
  [1] three early returns -> one `||` condition -> 89.40 (kept)
  [2] loop shapes (pointer walk, while, pos <= i, if/else wrap, positive condition) -> no gain
  residual: target puts the copy-loop pointer init (&str[len]) in an out-of-line block after the blr and
            branches back to the unrolled-loop guard; ours inlines it. Looks like an edge-split preheader.

fn_2_48A1C (stick-driven position nudge)
  baseline: 82.53%
  [1] target tests delta twice: outer `0.0f != x || 0.0f != z`, then an inlined guarded atan2 whose
      zero path stores 0.0f -> static inline safeAtan2 (`if (0 == x && 0 == y) return 0; return atan2`) -> 88.4
      (|| / if-else / ternary forms of the inline: 87.4 / 87.4 / 82.4)
  [2] -1.0f / 768.0f literals instead of lbl_2_rodata_9A0/9A4 -> 88.65 diff view, 89.92 report
  [3] stick pointer inline vs local, `+=`, statement placement -> no gain / worse
  residual: scheduling - target materialises &AtBat_ButtonInput1 after both delta stores; FPR numbering follows.

fn_2_49F7C (continued)
  [3] count down with `len` itself (`for (; len >= pos; len--)`) -> 95.8: reproduces the out-of-line preheader
  [4] length walk as static inline glyphStrLen(str) -> 98.28
  [5] str = NULL / if-else / positive-nested returns with [3]+[4] -> no gain
  residual: ours emits one extra unreachable trailing `blr` after the out-of-line preheader (236 vs 232 bytes).

fn_2_4917C (number -> glyph string formatter)
  baseline: 83.12%
  [1] call fn_2_49F7C instead of the hand-copied static inline insertNumberGlyph (MWCC inlines it) -> 86.0
  [2] no cached glyphs local (buffer->glyphs each use), `width = 3` duplicated under `if (value < 0)`/else,
      separate (flags&0x20)||(0x40)||(0x80) tests, s32 loop counter (restores decimal zero-trip guard),
      separator copied into a local before the glyph loop, fullWidth computed first and reused for `space` -> 91.4
  [3] fn_2_49F7C fixes above -> 96.36
  tried: `value * -1` / `-1 * value` (target has mulli -1, ours neg), glyphs local for the terminator,
         inline-arg forms (&glyphs[0], cast, dst =) -> no gain
  residual: inlined insert keeps `str` as its own register (r31+0x10, walked by the copy loop) where ours
            folds it into r31-relative offsets; terminator store `sthx` vs our `add; sth 0x10`.

fn_2_481F4 (character-select scene setup state machine)
  baseline: 84.60%
  [1] case 0 LIT block is fn_2_48DB4 -> call it (inlined by MWCC) -> 83.2 until 48DB4 itself fixed
  [2] fn_2_48DB4: three GXColor locals (declared color2, color1, color0 -> standalone/inline stack slots both match),
      LITInitColor colour passed BY VALUE via static inline setLightColor (light.h has the pointer prototype; see rep_0138.c),
      LITInitAttn args as 1.0f/0.0f literals -> 48DB4 100% report
  [3] case 1 position reset is fn_2_48D08 -> call it (inlined); 48D08 now uses 0.0f literal (still 100% report)
  [4] slot init as loops with s8 -1 sentinels + static inline resetSelectionSlots -> 91.7
  [5] alloc block is fn_2_477C0 -> call it (inlined) -> 93.77
  residual: target 9x6 alloc-size loop carries two dead IVs (+5 / +0x5F per outer iteration) we do not reproduce
            (same in fn_2_477C0 standalone: nested 9x6 forms score lower than the flat 54 loop); minor store scheduling in resetSelectionSlots.

fn_2_47FF8
  baseline: 85.07%
  [1] LITXForm loop -> call fn_2_48D54 (inlined); no cached base local; 0x7847 test duplicates fn_2_6A87C() in both arms -> 98.2
  [2] PSMTXCopy direction: target copies lbl_2_bss_1A81D4 INTO the camera matrix (draft had src/dst swapped: behaviour bug) -> 100% report

fn_2_478F4 (scene re-init: same tail as fn_2_481F4 case 0)
  baseline: 87.89%
  [1] body = fn_2_477C0(); fn_2_47540(); ... slot loops; resetSelectionSlots() -> 96.19
      (resetSelectionSlots order is -1 x4, 0x2D77, 0x2D7B, 0x2D7C; fn_2_481F4 then stores 0x2D77 again after it)
  residual: the inlined fn_2_477C0 alloc-size loop's dead IVs (see fn_2_481F4).

fn_2_48BE0
  [1] same guarded-atan2 inline as fn_2_48A1C + -1.0f literal -> 100% report
