# MSSB Decomp

## Matching a file

When asked to match a source file, pick the agent from the file's state:

- **No checkpoint, or the `.c` still has `return;` stubs** → `match-sonnet`
  (first pass: draft every function, fix data sections, take cheap wins).
- **A checkpoint exists with `pending` functions** → `match` (Opus second
  pass: grind the near-misses).

The checkpoint is `build/.match_grind/<objdiff-unit-name-with-slashes-as-underscores>.md`,
e.g. unit `game/game/batting/charge_effects` →
`game_game_batting_charge_effects.md`. Both agents do their own edits,
builds and diffs; there are no worker agents. Never run both on the same
file at once.
