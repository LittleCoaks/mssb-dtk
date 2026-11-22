# menus/menus/text_3C03C checkpoint (Opus pass)

Unit fuzzy 76.51 -> 99.13. .text 76.3 -> 99.1 (objdiff diff). .data 0% (jump tables; see below).

| function    | status    | pct              |
|-------------|-----------|------------------|
| fn_2_3E058  | matched   | 97.04 -> 100     |
| fn_2_3DF28  | matched   | 98.95 -> 100     |
| fn_2_3DDC4  | matched   | 99.10 -> 100     |
| fn_2_3DC60  | matched   | 99.10 -> 100     |
| fn_2_3DAB8  | exhausted | 93.16 -> 99.24   |
| fn_2_3D878  | matched   | 84.44 -> 100     |
| fn_2_3D5C4  | matched   | 97.53 -> 100     |
| fn_2_3CD34  | exhausted | 47.40 -> 99.97   |
| fn_2_3C7DC  | exhausted | 55.88 -> 94.54   |
| fn_2_3C53C  | matched   | 92.94 -> 100     |
| fn_2_3C3EC  | matched   | 100              |
| fn_2_3C168  | matched   | 76.75 -> 100     |
| fn_2_3C03C  | matched   | 100              |

readability pass: done for all matched functions (INPUT_BUTTON_A/B/UP/DOWN, CHAR_ID_* in fn_2_3C7DC,
FLAGS/WORK macros). Left alone (enum-shaped, no enum): slot state byte at work+0x789F (0 open, 1 cleared,
2 locked); TextItem.state 0/1 handshake; FLAGS[] bytes are per-message "shown" flags (names unknown).

## Data
.data = the 6 jump tables only. Scores 0% while fn_2_3C7DC is 24 bytes long (the .rel targets shift);
functions are already in descending address order so table order matches.

## Hypothesis log
fn_2_3C7DC (55.88)
  [1] index form WB(0x19789F + i) on the raw pointer, cases reordered 6,8,10,12,14,16,7,9,11,13,15,17,18 (code order), CHAR_IDs -> 79.1 kept
  [2] 19-flag all-set check written as an explicit && chain of s8 lvalues (target fully unrolled, extsb.) -> 94.5 kept
  [3] flag compares in the per-i path via (s8) cast on u8 (index form p[i+0x43C2]) -> kept (s8* lvalue there gives base+const form)
  [4] first clear loop: WB(i+const), inline helper, setSlotState(i,0) inline, s8 store, counter type s16/u8/u32/s8 -> no gain (s8 store/other types worse)
  left: only the unrolled clear loop (target holds 0 in r10 and precomputes 5 addresses; ours uses mr copies, +24 bytes)
fn_2_3CD34 (47.40)
  [1] full redraft: case order 0,1,2,7,8,3,4,5,6,9..12 (target code order); fn_2_46D94 takes 5 args (…, 6, 9) -> 99.39
      REAL BUG fixed: old draft called fn_2_46D94 with 3 args (garbage r6/r7). Also (s8)ctx[0x444B] == slot (old draft compared (u8)slot).
  [2] case 2 work pointer local `u8 *w` for the slot-state read -> 99.84
  [3] PadInput struct array for AtBat_ButtonInput1 (fixes lis order of the pad base) -> 99.97
  [4] slot state as u8 v/(s8) compares, s8 v implicit, inline reads, s8* lvalue (worse 99.78) -> no gain
  left: lbz into r3 + two extsb (target) vs lbz r0 (ours) for the slot state value.
fn_2_3C168: count loop of 0x33 over 10-byte entries (MWCC unrolls x3), 2D s16 table [][6], s8 store of -1, s32 setFollowSlot proto -> 100
fn_2_3D878: lbl_2_bss_1A8230 is a pointer (u8 *), 1056C is s16[][6], two separate `timer == 0x32` ifs -> 100
fn_2_3E058: original has empty else-if branches for counter 0x146/0x10A/0x16E before 0x13C -> 100
fn_2_3D5C4: `== 0` polarity in case 0, s8 lvalue for ctx[0x44F4], `<=` in case 5 -> 100
fn_2_3C53C: timer store before sndFXStartEx; re-read work after ++ -> 100
fn_2_3DAB8 (93.16)
  [1] PadInput struct -> 97.26 (with cast macro) / settings pointer hoisted u8 *settings -> 98.02
  [2] flag = base+idx; flag += 0x1A -> 98.68 kept
  [3] repeated global expr, fake struct field, &struct.characterUnlocked[idx], function-scope pointer -> 98.68 (no change)
  [4] including static/UnknownHomes_Static.h for GameInitVariables conflicts with the PadInput AtBat_ButtonInput1 decl; cast macro loses the pad lis order
  left: target `lbzu r0,0x1a(r4)` + `stb 0(r4)`; ours lbz 0x1a / stb 0x1a; g_d_GameSettings vs currentDrawingItem lis order.
