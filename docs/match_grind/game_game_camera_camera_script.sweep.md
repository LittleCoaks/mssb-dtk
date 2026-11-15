# Sweep log: game/game/camera/camera_script

Written by tools/match_sweep.py. One line per variant it built; the id in
brackets is what stops a later run repeating it. Hand-made attempts belong in
the unit's checkpoint, not here.

## fn_3_105C28 (2026-11-15): no improvement
baseline: 97.61% [REG:gv]
  [sweep 2fc334ac] decl: swap declarations `u32 frame = time >> 16;` / `u16* last;` -> 97.61% (same)
  [sweep a16f7b30] decl: swap declarations `u16* last;` / `u32 found = 0;` -> 97.61% (same)
  [sweep dc6d759b] decl: swap declarations `u32 found = 0;` / `u32 frac = time & 0xFFFF;` -> 96.96% (worse)
  [sweep 876d896f] decl: swap declarations `u32 frac = time & 0xFFFF;` / `u16* e = (u16*)(*(u8**)...` -> 96.52% (worse)
  [sweep db23135a] decl: swap declarations `u16* e = (u16*)(*(u8**)...` / `u16 n = *e;` -> - (build failed)
  [sweep ac5e512c] decl: reverse all declarations -> - (build failed)
  [sweep bbbf748f] decl: move `u32 frame = time >> 16;` last -> 95.65% (regresses fn_3_FD670)
  [sweep 1ec6f581] decl: move `u16* last;` last -> 96.96% (worse)
  [sweep 3dd7fb8f] decl: move `u32 found = 0;` first -> 97.61% (same)
  [sweep d9cc3df8] decl: move `u32 found = 0;` last -> 95.87% (worse)
  [sweep 21a6d8ae] decl: move `u32 frac = time & 0xFFFF;` first -> 96.09% (worse)
  [sweep 0917b1d4] decl: move `u32 frac = time & 0xFFFF;` last -> 96.52% (worse)
  [sweep 4ecc0648] decl: move `u16* e = (u16*)(*(u8**)...` first -> 95.87% (regresses fn_3_FD670)
  [sweep fb7753b1] decl: move `u16 n = *e;` first -> - (build failed)
  [sweep d075c4d1] type: L1: `u32 frame = time >> 16;` u32 -> s32 -> 92.39% (regresses fn_3_FD670)
  [sweep 56cc2d79] type: L1: `u32 frame = time >> 16;` u32 -> int -> 92.39% (regresses fn_3_FD670)
  [sweep b31201a3] type: L3: `u32 found = 0;` u32 -> s32 -> 97.61% (same)
  [sweep aef2e54d] type: L3: `u32 found = 0;` u32 -> int -> 97.61% (same)
  [sweep eb6ba80e] type: L4: `u32 frac = time & 0xFFFF;` u32 -> s32 -> 95.22% (worse)
  [sweep c8853c89] type: L4: `u32 frac = time & 0xFFFF;` u32 -> int -> 95.22% (worse)
  [sweep 59294201] type: L6: `u16 n = *e;` u16 -> int -> 91.30% (regresses fn_3_FD670)
  [sweep 8c8dad03] compound: L8: e += ... -> = e + ... -> 97.61% (same)
  [sweep dda3bc46] compound: L14: e += ... -> = e + ... -> 97.61% (same)
  [sweep ebcd5f50] deinit: L1: `frame` initialiser -> assignment after the declarations -> 95.87% (worse)
  [sweep 8f331100] deinit: L3: `found` initialiser -> assignment after the declarations -> 97.61% (same)
  [sweep 39d86a2e] deinit: L4: `frac` initialiser -> assignment after the declarations -> 97.61% (same)
  [sweep d7db2aee] deinit: L5: `e` initialiser -> assignment after the declarations -> 80.87% (regresses fn_3_FD670)
  [sweep a14e27c2] deinit: L6: `n` initialiser -> assignment after the declarations -> 97.61% (same)
