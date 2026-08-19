# Ghidra import policy

How names flow from the Ghidra project into this repo. Implemented by
`tools/ghidra_rename.py`; run `plan` to preview, `apply` to write.

## Precedence

1. **The decomp wins.** If a symbol here already has a real name, Ghidra never
   overwrites it. Ghidra is consulted *only* where this repo still has a
   placeholder. The decomp is one author with consistent conventions; the Ghidra
   project is several authors with differing ones, so the decomp's naming and
   style are the standard.

2. **`in_game` beats `AtGameSettingsScreen`.** Where both Ghidra programs name
   the same address and disagree, the match REL (`in_game`) wins -- it is the
   more developed of the two.

3. **Ambiguity is never guessed.** If two different Ghidra names sanitize to the
   same C identifier, neither takes it; both are reported in the skip list for a
   human to name.

## What counts as a placeholder

```
fn_80003458            main-DOL function, bare address
lbl_800E6600           main-DOL data, bare address
fn_3_1CE90             REL function: module + offset
lbl_3_data_1594        REL data: module + section + offset
jumptable_3_data_1864
fn_8001C67C_animation  hybrid: a hint appended to a placeholder, still a placeholder
```

## Illegal characters

Ghidra permits characters C identifiers cannot contain -- 341 of 3607 real names
use them. Mapping everything to `_` (what the old Ghidra export script did)
discards meaning and lets two distinct symbols collapse onto one identifier, so
they are translated **by meaning** instead:

| Ghidra | becomes | example |
|---|---|---|
| `?` | `_maybe` suffix (once, at the end) | `drawStadium?` → `drawStadium_maybe` |
| `<->`, `->` | `_to_` | `const_degree->radian` → `const_degree_to_radian` |
| `/` | `_or_` | `teamWhoWon(A/H)` → `teamWhoWon_A_or_H` |
| `&`, `+`, `,` | `_and_` | `turns&diamondMap` → `turns_and_diamondMap` |
| `'`, `"` | removed | `Fielder'sAutoMovement` → `FieldersAutoMovement` |
| `(` `)` `-` `.` `*` `#` | `_` | `chompState1-awake` → `chompState1_awake` |

Two rules keep this from doing damage:

- **A name that is already a legal identifier is passed through untouched.**
  Rewriting it would strip meaningful trailing underscores and merge genuinely
  distinct symbols (`__check_pad3` / `__check_pad3_`, `YUV2RGB` / `YUV2RGB_`).
- **Leading underscores are preserved** (`__start`, `__osCurrentCtx`); only
  trailing ones and runs introduced by substitution collapse.

## What is deliberately not imported

| category | count | why |
|---|---|---|
| numeric literal labels (`7.0`, `-1.0`) | 111 | `-1.0` and `1.0` both sanitize to `_1_0`, and the name carries no information anyway |
| low-information (`unused`, `unreferenced`, `pad`) | 49 | says nothing the placeholder did not; `unused?` → `unused_maybe` is caught too |
| name collisions | 56 | the sanitized name is already used elsewhere in the repo; needs a human to disambiguate |

## Verifying an import

Renaming cannot change codegen, so the check is exact: rebuild and confirm the
objdiff report is byte-identical.

```
ninja
objdiff-cli report generate -p . -o after.json -f json
```

Compare each unit's multiset of `(function size, match percent)` against the
before-report rather than comparing by name -- names changed, so a name-keyed
diff would be vacuous. The expected delta is zero.
