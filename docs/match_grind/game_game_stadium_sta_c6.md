# sta_c6.c (Toy Field) — match grind checkpoint

Unit: `game/game/stadium/sta_c6`
Module: game (REL)
Baseline at session start (2026-09-23): all 30 functions bare `return;` stubs (every function
already present in the .c), unit .text 0.86%.
Working mode (user request): write one function at a time, checkpoint after each.

rodata: 1, 340, 20, 420, 60, 0, u32->double bias, "sta_c6.c", and a Shift-JIS panic string
"参照するディスプレイステートがTEV設定部分じゃないです" ("the referenced display state is not the
TEV-settings part").
bss (0xAE50..0xAEE0): AE50 (2), AE52 (0x2E), AE80 (8), AE88 (0x24), AEAC (1), AEAD (7), AEB4 (0x2C).
Split change (2026-09-23): .text start 0xE59B4 -> 0xE587C (fn_3_E587C and fn_3_E5924, which
use this unit's data, sat unowned just before the split) and a new .data range 0x19018..0x19770.
fn_3_E6A48 reaches lbl_3_data_1963F/196B4/1972C as lbl_3_data_19018 + offset, which MWCC only does
within one TU (same situation as kinoko.c). The data is defined as statics in address order;
lbl_3_data_19024 (0x5EC, colours + placement tables) is still a raw byte array until the loader shows
its layout. .data 100% after the move. Data after 0x19770 belongs to other code (0xE911C.. text).
Sibling units: game/minigame/toy_field.c, game/minigame/toy_field_offscreen.c.

## Status

From report.json, updated after every function (2026-09-22 session).

| function                           | status    | pct |
|------------------------------------|-----------|-----|
| loadToyField                       | matched   | 100.0% |
| fn_3_E8AC8                         | matched   | 100.0% |
| fn_3_E7B20                         | exhausted | 92.6268% |
| fn_3_E7A2C                         | matched   | 100.0% |
| fn_3_E763C                         | exhausted | 97.8532% |
| fn_3_E751C                         | matched   | 100.0% |
| fn_3_E7424                         | matched   | 100.0% |
| processToyFieldObjectCollisions    | exhausted | 83.9744% |
| fn_3_E7364                         | matched   | 100.0% |
| fn_3_E7350                         | matched   | 100.0% |
| fn_3_E6D90                         | exhausted | 99.9321% |
| fn_3_E6A48                         | exhausted | 99.8809% |
| fn_3_E698C                         | matched   | 100.0% |
| fn_3_E68A8                         | exhausted | 95.7018% |
| fn_3_E67F4                         | matched   | 100.0% |
| fn_3_E6798                         | matched   | 100.0% |
| fn_3_E671C                         | matched   | 100.0% |
| fn_3_E6684                         | matched   | 100.0% |
| fn_3_E6638                         | matched   | 100.0% |
| fn_3_E6578                         | matched   | 100.0% |
| fn_3_E6528                         | matched   | 100.0% |
| fn_3_E64A8                         | matched   | 100.0% |
| fn_3_E6410                         | matched   | 100.0% |
| fn_3_E5FEC                         | matched   | 100.0% |
| fn_3_E5E70                         | exhausted | 98.3158% |
| fn_3_E5E14                         | matched   | 100.0% |
| fn_3_E5CBC                         | matched   | 100.0% |
| fn_3_E5A84                         | exhausted | 99.7887% |
| fn_3_E5A1C                         | matched   | 100.0% |
| fn_3_E59B4                         | matched   | 100.0% |
| fn_3_E5924                         | matched   | 100.0% |
| fn_3_E587C                         | matched   | 100.0% |

24/32 at 100%.

## Log

### fn_3_E59B4: animation loop (next frame > 340 -> frame 20) -> 100%.

### fn_3_E5A1C: animation loop (next frame > 420 -> frame 60) -> 100%.

### fn_3_E5A84 (99.79%): two-actor pre-draw (placement table or home table transform). Only the epilogue order differs (target restores r28-r31 before lwz r0). Tried: explicit return, mode local, decl order - no change.

### fn_3_E5CBC: colour fade (t clamped to [0,1]; color = (1-t)*from + t*to, f32). `from` declared before `to` -> 100%.

### fn_3_E5E14: GX colour-format byte size (switch: 565/RGBA4 -> 2, RGBA8 -> 4, RGB8/RGBX8/RGBA6 -> 3, cases in that order) -> 100%.

### fn_3_E5E70 (98.32%): decode one GX colour into RGBA8 (cases in body order 565, RGBA4, RGBA8, RGB8/RGBX8, RGBA6). Remaining: target's RGBA6 red channel is lhz + rlwinm 16,24,29 (a real rotate of the u16); `(*(u16*)src >> 16) & 0xFC` folds to 0 here. Probably a bitfield read in the original.

### fn_3_E5FEC: write obj->color into the extra model's node-1 colour attribute and obj->bodyColor into the model's node-0 one, per GX colour format; show/hide extra node 2 via altDispObj. Both encodes written out (target reloads obj->bodyColor per byte, so no helper), each packed field as `(u16)(c >> n) & mask` (keeps the srawi separate from the mask) -> 100%. Note: RGBA6 case overwrites rather than ORs, as in the binary.

### fn_3_E6410: pick a random target colour from lbl_3_data_19018's three, skipping colorFrom (loop over the table collecting 2 candidates) -> 100%.

### fn_3_E64A8: random colour from lbl_3_data_19018 (switch on (u8)(rand() % 3), return from each case; a local + break gave an extra mr) -> 100%.

### fn_3_E6528: colour reset (color = *baseColor, bodyColor = lbl_3_data_19024 + 0x64, showMarker = 0) -> 100%.

### fn_3_E6578: checks the extra model's node-1 display state is the TEV-settings kind (type 3, else OSPanic with the Shift-JIS message; the UTF-8 literal is converted by sjiswrap), then TEV mode = 1 (state 2) / 0 (state 10) / 4 -> 100%.

### fn_3_E6638: show model nodes 0-2 (dispObj = altDispObj, full chain each time) -> 100%.

### fn_3_E6684: show/hide model nodes 0-2 from lbl_3_bss_AE80[1..3]; written as a 3-iteration loop (target is the compiler's unrolling, node loaded before the flag test) -> 100%.

### fn_3_E671C: show model nodes 0-6 (root cached, 7-iteration loop) -> 100%.

### fn_3_E6798: show/hide model nodes 0-6 from lbl_3_data_196B4[i] (root cached, loop) -> 100%.

### fn_3_E67F4: reset the 7 props in anim slots 16-22 (flag = 0, frame 20, apply, animate). Reads via a ToyAnimSlot array (strength-reduced i*0x90+0x934), write via an inline toyActSetFrame(ptr-math slot, 20.0f), `u32 i` declared first -> 100%.

### fn_3_E68A8 (95.70%): sync the extra model to the main one (frame = main frame - animSpeed clamped at 0; copy obj's 0x44-byte control to extra+0x10; setActorAnimFrame, fn_800BDA24, cull, sknRelated). Remaining: obj/extraRoot register swap (r31/r30). Tried: frame decl first, void* root, split assignments, ToyModel* extra local, decl order - all 95.70.

### fn_3_E698C: prop animation by flag (flag clear: rewind to 0 and animate; flag set and frame <= 60: animate). frame computed from the full obj->model->root expression, not the actor local -> 100%.

### split + data move: .text from 0xE587C, .data 0x19018..0x19770 defined in C (.data 100%); all earlier matches unchanged.

### fn_3_E587C: index of the single set prop flag in lbl_3_data_196B4, else -1 (7-iteration loop) -> 100%.

### fn_3_E5924: TRUE when all 7 prop flags are set (loop with break, then i >= 7) -> 100%.

### fn_3_E6A48 (99.88%): fn_3_E5A84 + fn_3_E6578 (auto-inlined), fn_3_E5FEC + sknRelated when the extra model exists, then mark prop hit during a live ball when the Toy Field result matches lbl_3_data_1972C[state] and lbl_3_data_1963F == slot. Remaining: two prologue instructions swapped (data base vs PSMTXIdentity arg), scheduling.

### fn_3_E6D90 (99.93%): per-frame prop update (pre-draw, reset colours at play start via fn_3_E6528, live-ball hit colours + sounds 0x14/0x17 via an inline toyPlaySound(sfx, slot), fn_3_E5FEC, fn_3_E6578, skin + show node 2). The helper took 99.82 -> 99.93. Remaining: same two-instruction prologue swap as fn_3_E6A48.

### fn_3_E7350: lbl_3_data_1963F = lbl_3_data_19640 -> 100%.

### fn_3_E7364: lbl_3_data_19640 = objects[idx].slot -> 100%.

### processToyFieldObjectCollisions (83.97%): draw order (hidden objects front with index, visible from the back with depth 1.0; do/while (i-- != 0) loops like the framework's fn_3_B867C). Structure matches; target copies the counter (mr r8, r3) and computes back before obj in loop 2. Tried: separate obj index expr, back-first, obj via index (worse), 6 declaration orders - no change.

### fn_3_E7424: pre-update (on at-bat/default: roundCount++, AE80 flags = g_Minigame._1914.._1917 != 0, 1963F/19640 = -1; every frame prev/last Toy Field result + unpaused frame count, AE51 = 0) -> 100%.
    bss finding: MWCC aligns every array and struct (even all-u8 ones) to 4 here, so the byte-granular
    target layout (AE52 flag, AE7B/AE7C results at odd offsets) only comes out with individual u8
    statics. AE50..AE7C and AEAD..AEB3 are declared byte by byte; unnamed ones are placeholders. Layout
    verified against the .o symbol table (all offsets match). lbl_3_data_19640 is s8 (-1), like 1963F.

### fn_3_E751C: collision matrix for object idx (placement or home transform at height -0.04, `state <= 7` form), returns its triangles -> 100%.

### fn_3_E763C (97.85%, first pass): bounding boxes. Pass 1: 10 groups x 15 placed props (debug skip: pad Y held and group != 0, or pad X held and the previous group's inner counter != 0; that counter is uninitialised on group 0, as in the binary). Pass 2: 10 groups x 7 home objects (index j + firstHomeObj, home Vec/angle tables), boundingBoxCount stored inside the loop. Remaining: register numbering only.

### fn_3_E7A2C: install callbacks by object state (0-15 placed props: func E7364 + preDraw E6D90, placedPropCount++; 16-22: E698C/E68A8; 23: E6798/E671C; 24: E6684/E6638; 26: E59B4; 25: E5A1C - case bodies in that order) -> 100%.

### fn_3_E7B20 (92.63%, first pass + 3 fixes): object-layout builder. Layout chosen by participant count (switch: 2 -> layouts[0], 3 -> [1], default [2]; _19A6 > 1 -> [3] and hitAll), 15 placed props, 7 home objects (firstHomeObj), 7 animated props (states 16-22), singles 23/24/26/25 via last[1..4], empty filler, fn_3_E763C, fn_3_E67F4 on the start movie. Inlines fn_3_E6528, fn_3_E7A2C, fn_3_E67F4.
    lbl_3_data_19024 is now typed ToyFieldData {colors[9][3][4] (miss/base/hit per state), layouts[4][16], homeTypes[4][8]} (.data still 100%). 91.20 -> 91.55 (switch, u8 done, last[] singles) -> 92.63 (colors[9][3], o/last copies). Remaining: register/scheduling across the big body; revisit.

### fn_3_E8AC8: on the Toy Field stadium, rebuild the layout (fn_3_E7B20(stadiumData, _34) != FALSE), else FALSE. fn_3_E7B20 returns E(u8, BOOL) (the caller clrlwi's it) -> 100%.

### loadToyField: 30 anim slots (0-15 ids[k+1], props 16-22 ids[17+k] + banks, 23-29 ids[24..30], banks on 25/28/29, slot 28 at frame 20 and 29 at frame 60 via toyActSetFrame), fn_800BD478 + lighting per slot, 32 objects, fn_3_E7B20, roundCount = 0. `ids = _34 = _OSAllocFromHeap(...)` chained and the object allocation sized from objectCount -> 100%.

## Session summary (2026-09-23)
All 32 functions written (fn_3_E587C / fn_3_E5924 added by the split change), one at a time with a
checkpoint after each. 24/32 at 100%, unit .text 97.51%, .data 100% (0x758 bytes defined in C),
.bss layout verified symbol-by-symbol against the .o (score low only because of symbol names).
Near misses: fn_3_E6D90 99.93, fn_3_E6A48 99.88, fn_3_E5A84 99.79 (the same prologue/epilogue
ordering issue in all three), fn_3_E5E70 98.32 (RGBA6 bitfield read), fn_3_E763C 97.85,
fn_3_E68A8 95.70, fn_3_E7B20 92.63, processToyFieldObjectCollisions 83.97.
Next session: fn_3_E7B20 (biggest remaining), processToyFieldObjectCollisions (counter copy),
fn_3_E68A8 (obj/extraRoot register swap).
