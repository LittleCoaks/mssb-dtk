# Sweep log: game/game/stadium/sta_c5

Written by tools/match_sweep.py. One line per variant it built; the id in
brackets is what stops a later run repeating it. Hand-made attempts belong in
the unit's checkpoint, not here.

## fn_3_F1750 (2026-11-15): no improvement
baseline: 97.52% [REORDER/OPCODE]
  [sweep 3f2d3c04] decl: swap declarations `DKJungleActor* actor = ...` / `f32 angle;` -> 97.52% (same)
  [sweep c0aa310e] decl: swap declarations `f32 angle;` / `f32 scan;` -> 97.52% (same)
  [sweep fe647c93] decl: reverse all declarations -> 97.52% (same)
  [sweep 28cdde8e] decl: move `DKJungleActor* actor = ...` last -> 97.52% (same)
  [sweep fd13bc4e] decl: move `f32 scan;` first -> 97.52% (same)
  [sweep bf72ab3d] deinit: L1: `actor` initialiser -> assignment after the declarations -> 97.52% (same)
  [sweep 7bc485b7] cast: L20: (u8*)hugeAnimStruct.acto...[..] -> ((u8**)hugeAnimStruct.acto...)[..] -> 97.52% (same)
  [sweep 0636ebdc] invert: L7: invert if (!scan) / else -> 90.34% (regresses handleDKJungleBarrel)

## jungleStadiumObjectRelated (2026-11-15): 97.41% -> 100.00% (not applied)
baseline: 97.41% [REORDER/OPCODE]
  [sweep 9957b129] decl: swap declarations `DKJungleKlaptrapData* d...` / `Vec toTarget;` -> 97.41% (same)
  [sweep 39a0bb7a] decl: swap declarations `Vec toTarget;` / `Vec heading;` -> 97.27% (worse)
  [sweep 2c895caa] decl: swap declarations `Vec heading;` / `Vec cross;` -> 97.32% (worse)
  [sweep 8ad0b44e] decl: swap declarations `Vec cross;` / `f32 rad;` -> 97.41% (same)
  [sweep b42603cf] decl: swap declarations `f32 rad;` / `f32 dot;` -> 97.41% (same)
  [sweep 3d8a87d3] decl: reverse all declarations -> 97.32% (worse)
  [sweep cfae04fc] decl: move `DKJungleKlaptrapData* d...` last -> 97.41% (same)
  [sweep 7a0a1ebe] decl: move `Vec toTarget;` last -> 97.25% (worse)
  [sweep ab68bb52] decl: move `Vec heading;` first -> 97.27% (worse)
  [sweep beff2957] decl: move `Vec heading;` last -> 97.32% (worse)
  [sweep cf173bfc] decl: move `Vec cross;` first -> 97.25% (worse)
  [sweep b1859683] decl: move `Vec cross;` last -> 97.41% (same)
  [sweep 98bedc8f] decl: move `f32 rad;` first -> 97.41% (same)
  [sweep 251f79d4] decl: move `f32 dot;` first -> 97.41% (same)
  [sweep e1e67b71] inline: L1: fold single-use local `data` into its use -> 100.00% (better)
  kept after round 1: inline: L1: fold single-use local `data` into its use -> 100.00%

## fn_3_F2FFC (2026-11-15): no improvement
baseline: 99.79% [REG:fv]
  [sweep 15807223] decl: swap declarations `Vec dir;` / `s8 sign;` -> 99.79% (same)
  [sweep 3bdf59ed] decl: swap declarations `s8 sign;` / `f32 diff;` -> 99.79% (same)
  [sweep ff47c419] decl: reverse all declarations -> 99.79% (same)
  [sweep 16827ff1] decl: move `Vec dir;` last -> 99.79% (same)
  [sweep e5393982] decl: move `f32 diff;` first -> 99.79% (same)
  [sweep d67eede4] type: L2: `s8 sign;` s8 -> int -> 69.19% (regresses dkBarrelLaunch)

## jungleStadiumObjectRelated (2026-11-15): 97.41% -> 100.00%
baseline: 97.41% [REORDER/OPCODE]
  [sweep e1e67b71] inline: L1: fold single-use local `data` into its use -> 100.00% (better)
  kept after round 1: inline: L1: fold single-use local `data` into its use -> 100.00%

## fn_3_F2724 (2026-11-15): no improvement
baseline: 99.85% [REG:fv]
  [sweep e06054a8] decl: swap declarations `Vec v;` / `f32 cosA;` -> 99.85% (same)
  [sweep b6eaf886] decl: swap declarations `f32 cosA;` / `f32 sinA;` -> 99.70% (regresses dkBarrelAdvanceMotion)
  [sweep 9e2a0dda] decl: swap declarations `f32 sinA;` / `f32 sinB;` -> 99.70% (regresses dkBarrelAdvanceMotion)
  [sweep 487d402c] decl: swap declarations `f32 sinB;` / `f32 cosB;` -> 99.85% (same)
  [sweep b0374c2e] decl: swap declarations `f32 cosB;` / `f32 alongX;` -> 99.85% (same)
  [sweep f84a514d] decl: swap declarations `f32 alongX;` / `f32 alongZ;` -> 99.85% (same)
  [sweep dfaae429] decl: swap declarations `f32 alongZ;` / `f32 absX;` -> 99.85% (same)
  [sweep 6b5867da] decl: swap declarations `f32 absX;` / `f32 absZ;` -> 99.85% (same)
  [sweep 9c48fbf5] decl: reverse all declarations -> 99.70% (worse)
  [sweep db1ee6ba] decl: move `Vec v;` last -> 99.85% (same)
  [sweep d2c6b711] decl: move `f32 cosA;` last -> 99.85% (same)
  [sweep 21ff988f] decl: move `f32 sinA;` first -> 99.70% (regresses dkBarrelAdvanceMotion)
  [sweep dfcf658d] decl: move `f32 sinA;` last -> 99.70% (regresses dkBarrelAdvanceMotion)
  [sweep 643e5a37] decl: move `f32 sinB;` first -> 99.62% (worse)
  [sweep 92c85324] decl: move `f32 sinB;` last -> 99.85% (same)
  [sweep d2acf04a] decl: move `f32 cosB;` first -> 99.85% (same)
  [sweep b0b546ff] decl: move `f32 cosB;` last -> 99.85% (same)
  [sweep 5c6f8405] decl: move `f32 alongX;` first -> 99.85% (same)
  [sweep 9df6c837] decl: move `f32 alongX;` last -> 99.85% (same)
  [sweep 5f369189] decl: move `f32 alongZ;` first -> 99.85% (same)
  [sweep 59aa11a4] decl: move `f32 alongZ;` last -> 99.85% (same)
  [sweep 61b4f0d4] decl: move `f32 absX;` first -> 99.85% (same)
  [sweep 58ea5d54] decl: move `f32 absZ;` first -> 99.85% (same)

## isPosOutsideKlaptrapZone (2026-11-15): no improvement
baseline: 99.55% [REG+imm+stack]
  [sweep 89ea4bf9] decl: swap declarations `u8 orderAlt[4] = {1, 3,...` / `u8 order[4] = {0, 1, 2,...` -> 99.53% (worse)
  [sweep afabd5ed] decl: swap declarations `u8 order[4] = {0, 1, 2,...` / `const DKJungleZoneCorne...` -> 99.55% (same)
  [sweep bcc61679] decl: swap declarations `const DKJungleZoneCorne...` / `Vec toPos;` -> 99.55% (same)
  [sweep ea54d2ee] decl: swap declarations `Vec toPos;` / `Vec edge;` -> 99.47% (worse)
  [sweep ddd64115] decl: swap declarations `Vec edge;` / `Vec cross;` -> 99.47% (worse)
  [sweep 2987dbf1] decl: swap declarations `Vec cross;` / `u32 i;` -> 99.55% (same)
  [sweep 97011dfb] decl: swap declarations `u32 i;` / `s8 sign;` -> 99.48% (worse)
  [sweep e244cb85] decl: reverse all declarations -> 99.39% (worse)
  [sweep db309172] decl: move `u8 orderAlt[4] = {1, 3,...` last -> 99.53% (worse)
  [sweep 74221193] decl: move `u8 order[4] = {0, 1, 2,...` last -> 99.55% (same)
  [sweep 7e119977] decl: move `const DKJungleZoneCorne...` first -> 99.55% (same)
  [sweep fe2c69f3] decl: move `const DKJungleZoneCorne...` last -> 99.55% (same)
  [sweep d8096d47] decl: move `Vec toPos;` first -> 99.55% (same)
  [sweep 7bdb86b3] decl: move `Vec toPos;` last -> 99.43% (worse)
  [sweep 05756a9d] decl: move `Vec edge;` first -> 99.47% (worse)
  [sweep ac04bf38] decl: move `Vec edge;` last -> 99.47% (worse)
  [sweep bcb1d64b] decl: move `Vec cross;` first -> 99.43% (worse)
  [sweep df946263] decl: move `Vec cross;` last -> 99.55% (same)
  [sweep b12c27e5] decl: move `u32 i;` first -> 99.55% (same)
  [sweep 5b497e62] decl: move `s8 sign;` first -> 99.48% (worse)
  [sweep cadb2f44] type: L1: `u8 orderAlt[4] = {1, 3, 0, 2};` u8 -> int -> 92.88% (regresses fn_3_EE100 +47)
  [sweep adaeca57] type: L2: `u8 order[4] = {0, 1, 2, 3};` u8 -> int -> 93.31% (regresses fn_3_EE100 +47)
  [sweep b40c0c85] type: L7: `u32 i;` u32 -> s32 -> 98.75% (worse)
  [sweep 40e30217] type: L7: `u32 i;` u32 -> int -> 98.75% (worse)
  [sweep ea613787] type: L8: `s8 sign;` s8 -> int -> 95.51% (worse)
  [sweep 6ead410f] loop: L15: for (sign = -1, ...; i < 2; ...) -> while -> 99.55% (same)
  [sweep 0db39060] loop: L15: for (sign = -1, ...; i < 2; ...) -> do/while -> 99.55% (same)
  [sweep e65be15c] loop: L29: for (sign = -1, ...; i < 2; ...) -> while -> 99.55% (same)
  [sweep f388c3e6] loop: L29: for (sign = -1, ...; i < 2; ...) -> do/while -> 96.61% (worse)

## fn_3_EDFAC (2026-11-15): no improvement
baseline: 97.49% [SIZE_DIFF]
  [sweep e906175d] decl: swap declarations `u8* base = (u8*)&lbl_3_...` / `int* emitters = (int*)(...` -> - (build failed)
  [sweep 0fd5cbe3] deinit: L1: `base` initialiser -> assignment after the declarations -> 86.65% (worse)
  [sweep a59b27c2] deinit: L2: `emitters` initialiser -> assignment after the declarations -> 97.49% (same)
