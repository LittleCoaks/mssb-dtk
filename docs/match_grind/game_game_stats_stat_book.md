# stat_book checkpoint
| function | status | pct |
|---|---|---|
| statBook_update | pending | 99.55% |
| compileStatsForBook | pending | 98.15% |

statBook_update (target: state-4 `done` lives in r30, initialised to 0 before the first `animRelated[0xD2] = 0` store, and r30 is reused for every constant-0 store in states 0-2 (animRelated, playMode STOP, timer); ours inits done in the state-4 block -> 4 bytes longer)
  [1] done (and/or wrapped) moved to function scope with initializer, any decl position -> unchanged (init sunk)
  [2] `animRelated[0xD2] = done = 0;` chained -> 99.43: r30 used for that first store only, later zero stores still li r0
  [3] wrapped/done merged into one top-level var -> 99.07; storing `done` instead of UI_PLAY_STOP -> 99.54
  lead: [2] is the right mechanism; need the later 0-stores to see r30 too
