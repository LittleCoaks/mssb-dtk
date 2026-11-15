# MSSB Decomp

## Matching a file

When asked to match a source file, pick the agent from the file's state:

- **No checkpoint, or the `.c` still has `return;` stubs** → `match-sonnet`
  (first pass: draft every function, fix data sections, take cheap wins).
- **A checkpoint exists with `pending` functions** → `match` (Opus second
  pass: grind the near-misses).

The checkpoint is `docs/match_grind/<objdiff-unit-name-with-slashes-as-underscores>.md`,
e.g. unit `game/game/batting/charge_effects` →
`game_game_batting_charge_effects.md`. Both agents do their own edits,
builds and diffs; there are no worker agents. Never run both on the same
file at once.

Checkpoints are tracked in git so the record of what has already been tried
survives between sessions, machines and clones. Commit a file's checkpoint
together with the source changes it describes, and keep it once the file
reaches 100% (mark it `Status: complete`) rather than deleting it. Only
throwaway artifacts -- source backups, diff JSON, trial scripts -- belong in
the gitignored `build/.match_grind/`.

## After a function reaches 100%

Matching is not the finish line. Both agents must run a readability pass over
each function once it is 100% (the "Post-match readability pass" section of
`.claude/agents/match.md`): replace bare values with the game's enums and
symbols -- `CHAR_ID` / `CHAR_ID_NONE`, `INPUT_BUTTON` and the other
`E(storage, ENUM)` types, `TRUE`/`FALSE` for booleans, named sentinels and
struct fields -- including initialised data tables, then re-diff to confirm
it is still 100%. Only use a name when the evidence supports it; if a value
looks enum-shaped but no enum exists, note it in the checkpoint rather than
inventing one.
