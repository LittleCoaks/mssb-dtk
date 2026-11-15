# game/game/stats/stat_lookups

Baseline: 2026-10-13 UTC. Fresh object rebuilt before diff. No prior checkpoint; complete initial draft existed.

| Function | Status | Percent |
|---|---|---|
| getAdjustedPitcherStamina | matched | 100% |
| checkFieldingStat | matched | 100% |
| calculateChemistry | exhausted | 97.41936% |

Sections: .text 99.13043%; target unit contains no .data/.bss/.rodata sections.

Target (left) and ours (right) chemistry function both 124 bytes. Target loads exhibitionMatchInd before mulli and reuses r4 for charIdA byte offset; ours multiplies first into r8, uses r4 for static table base. Remaining function body identical.

Final verified status (2026-10-13 UTC): getAdjustedPitcherStamina 100 -> 100%; checkFieldingStat 100 -> 100%; calculateChemistry 92.90323 -> 97.41936%. .text 97.608696 -> 99.13043% (368 target bytes). Target .data/.bss/.rodata absent, so no percentages apply. All target functions retain original sizes (160/84/124 bytes). Unit remains NonMatching and is not ready to flip.

Readability pass: getAdjustedPitcherStamina done; existing game-mode enumerators already used, zero is stamina floor, team 0 is an index without an existing team enum. checkFieldingStat done; TRUE/FALSE returns and E(int, FIELDING_ABILITY) documentary parameter type, storage unchanged. calculateChemistry reviewed; E(int, CHAR_ID) documentary parameters, named chemistry struct field and existing symbol retained. No established enum was found for challengeCaptainStarBought index 5, chemistry maximum 100, or the external tuning-table index 10, so these literals remain. No added source comments about matching.

The retained signed-byte exhibition flag cache preserves zero/nonzero truth over the complete original u8 range: 0 remains 0, 1..127 remain positive, 128..255 become negative and remain nonzero. This is a raw field-value cache, not a narrowed BOOL local. The function only applies a zero/nonzero test to it, and performs no signed arithmetic. s16 gives the same score; BOOL/int gives 90.96774%, and unsigned byte gives baseline 92.90323%. Keeping s8 is the best measured non-regressing result. No shared header change was made.

Residual (target left / ours right): target mulli r4,r4,0xa0 / ours mulli r8,r4,0xa0; target addi r7,r7,Static_Stats_Tables@l / ours addi r4,r7,...; target cmplwi r0,0 / ours extsb. r0,r0; target add r0,r7,r4 / ours add r0,r4,r8. The rest is identical. Original s8-cache numerical gain partly comes from restoring load schedule, and still includes the predicate-instruction mismatch.

Exhausted families: lookup inline (including argument order and casts), whole-function inline (including parameter order and cast arguments), predicate inline, pointer/index/2D views and compound byte offsets, narrow/unsigned parameter types, local widths/declaration placement, nested guards/common branch lookup, register hints, six function-scoped optimization/scheduling switches, and all 19 bundled compiler versions. Versions 1.3 through 2.7 tied the best result; older ones regressed, newer 3.0 variants improved chemistry slightly but regressed both already-matched functions and were rejected. No further structurally distinct lead remains from this session. Reopen only with new source-shape or compiler evidence. Configuration and shared symbol/split files were untouched.

Attempt 17 failed to compile because its temporary unsigned function signature conflicted with the header prototype; later attempt 40 isolated the declaration view in scratch and completed the parameter-width audit. Scratch tests compiled against the target object directly while root performed whole-build integration; every scored test had a fresh object.

## Hypothesis log

- 1. Extract indexed chemistry lookup into inline helper: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 2. Reverse inline helper parameter order: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 3. Extract challenge bonus predicate into inline: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 47.19355}; sections {'.text': 82.20652}; reverted.

- 4. Cache exhibition flag before chemistry lookup: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 90.96774}; sections {'.text': 96.95652}; reverted.

- 5. Inline lookup returns naturally byte sized: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 6. Index named first chemistry member: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 84.354836}; sections {'.text': 94.728264}; reverted.

- 7. Natural two dimensional static table index: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 42.258064}; sections {'.text': 80.54348}; reverted.

- 8. Cache static row pointer: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 9. Explicit index offset compound assignment in address: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 70.16129}; sections {'.text': 89.945656}; reverted.

- 10. Explicit flat offset with charA first: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 84.354836}; sections {'.text': 94.728264}; reverted.

- 11. Explicit flat offset with charB first: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 84.354836}; sections {'.text': 94.728264}; reverted.

- 12. Reverse commutative pointer addition: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 13. Compound offset before typed field access: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 14. Mutate charA in standalone byte offset: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 15. Cached exhibition flag width u8: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 15. Cached exhibition flag width s8: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; kept.
```c
#define SQRT2_LINKAGE static
#include "game/stats/stat_lookups.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "header_rep_data.h"

extern f32 lbl_3_data_5FC4[12];

// .text:0x0006D564 size:0xA0 mapped:0x806AC5F8
int getAdjustedPitcherStamina(int team, int rosterID, int amount) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_EXHIBITION_GAME ||
        g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (amount < 0 && PitcherStats_P1_P2[team][rosterID].stamina < -amount) {
            PitcherStats_P1_P2[team][rosterID].stamina = 0;
        } else {
            PitcherStats_P1_P2[team][rosterID].stamina += amount;
        }
    }
    return PitcherStats_P1_P2[team][rosterID].stamina;
}

// .text:0x0006D604 size:0x54 mapped:0x806AC698
BOOL checkFieldingStat(int team, int rosterID, int ability) {
    if (g_d_GameSettings.minigamesEnabled) {
        team = 0;
    }
    if ((1 << ability) & inMemRoster[team][rosterID].stats.FieldingStats) {
        return 1;
    }
    return 0;
}

// .text:0x0006D658 size:0x7C mapped:0x806AC6EC
int calculateChemistry(int team, int charIdA, int charIdB) {
    s8 exhibitionMatch = g_d_GameSettings.exhibitionMatchInd;
    int chem = ((u8*)&((CharacterStats*)Static_Stats_Tables.characterStats)[charIdA].chemistry)[charIdB];

    if (!exhibitionMatch && g_d_GameSettings.humanTeamNumber == team &&
        g_d_GameSettings.challengeCaptainStarBought[5] != 0) {
        chem += (int)lbl_3_data_5FC4[10];
    }
    if (chem > 100) {
        chem = 100;
    }
    return chem;
}

```

- 15. Cached exhibition flag width int: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 90.96774}; sections {'.text': 96.95652}; reverted.

- 16. File-local flat character table view: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 18. Declare uninitialized chemistry then set after condition read: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 19. Chemistry int result defined after row pointer: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 20. Reuse charIdA as chemistry result: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 21. Cached exhibition flag width u16: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 21. Cached exhibition flag width s16: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 21. Cached exhibition flag width u32: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 22. Lookup index cast unsigned int: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 22. Lookup index cast u32: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 22. Lookup index cast s16: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 62.258064}; sections {'.text': 87.28261}; reverted.

- 22. Lookup index cast u16: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 62.258064}; sections {'.text': 87.28261}; reverted.

- 22. Lookup index cast CHAR_ID: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 23. Cast inline lookup argument (int)charIdA: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 23. Cast inline lookup argument (u32)charIdA: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 23. Cast inline lookup argument charIdA + 0: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 23. Cast inline lookup argument (int)charIdB: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 24. Cache signed byte and test original unsigned value (u8)exhibitionMatch == 0: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 90.645164}; sections {'.text': 96.847824}; reverted.

- 24. Cache signed byte and test original unsigned value (unsigned int)(u8)exhibitionMatch == 0: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 90.645164}; sections {'.text': 96.847824}; reverted.

- 24. Cache signed byte and test original unsigned value exhibitionMatch == FALSE: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 24. Cache signed byte and test original unsigned value !(u8)exhibitionMatch: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 25. Cache negated exhibition truth value: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 26. Cache settings base pointer: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 91.77419}; sections {'.text': 97.228264}; reverted.

- 27. Cache row table pointer u8*: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 27. Cache row table pointer ChemistryTable*: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 28. Direct first row index uncached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 29. Explicit signed sizeof row offset uncached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 30. Two dimensional byte row view uncached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 31. Nested structured bonus guards uncached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 28. Direct first row index cached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 29. Explicit signed sizeof row offset cached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 30. Two dimensional byte row view cached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 31. Nested structured bonus guards cached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 32. Lookup common to exhibition and challenge branches: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 33.387096}; sections {'.text': 77.554344}; reverted.

- 33. Function scoped scheduling off baseline: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 53.225807}; sections {'.text': 84.23913}; reverted.

- 33. Function scoped peephole off baseline: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 33. Function scoped optimization_level 3 baseline: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 33. Function scoped opt_lifetimes off baseline: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 33. Function scoped opt_common_subs off baseline: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 33. Function scoped opt_propagation off baseline: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 33. Function scoped scheduling off cached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 65.645164}; sections {'.text': 88.42391}; reverted.

- 33. Function scoped peephole off cached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 33. Function scoped optimization_level 3 cached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 33. Function scoped opt_lifetimes off cached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 33. Function scoped opt_common_subs off cached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 33. Function scoped opt_propagation off cached: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 88.548386}; sections {'.text': 96.141304}; reverted.

- 34. Chemistry declaration precedes flag cache: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 35. Cache byte row offset local declaration order 0: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 35. Cache byte row offset local declaration order 1: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 35. Cache byte row offset local declaration order 2: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 36. Cached flag plus flat character table view: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 37. Cached flag plus lookup inline helper: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 38. Direct compiler 1.0: {'getAdjustedPitcherStamina': 68.375, 'checkFieldingStat': 65.2381, 'calculateChemistry': 79.22581}; {'.text': 71.315216}; diagnostic only (configuration untouched).

- 38. Direct compiler 1.1: {'getAdjustedPitcherStamina': 68.375, 'checkFieldingStat': 65.2381, 'calculateChemistry': 79.22581}; {'.text': 71.315216}; diagnostic only (configuration untouched).

- 38. Direct compiler 1.1p1: {'getAdjustedPitcherStamina': 68.375, 'checkFieldingStat': 64.52381, 'calculateChemistry': 86.0}; {'.text': 73.434784}; diagnostic only (configuration untouched).

- 38. Direct compiler 1.2.5: {'getAdjustedPitcherStamina': 68.375, 'checkFieldingStat': 65.2381, 'calculateChemistry': 79.22581}; {'.text': 71.315216}; diagnostic only (configuration untouched).

- 38. Direct compiler 1.2.5n: {'getAdjustedPitcherStamina': 68.375, 'checkFieldingStat': 65.2381, 'calculateChemistry': 86.0}; {'.text': 73.597824}; diagnostic only (configuration untouched).

- 38. Direct compiler 1.3: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; diagnostic only (configuration untouched).

- 38. Direct compiler 1.3.2: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; diagnostic only (configuration untouched).

- 38. Direct compiler 1.3.2r: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; diagnostic only (configuration untouched).

- 38. Direct compiler 2.0: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; diagnostic only (configuration untouched).

- 38. Direct compiler 2.0p1: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; diagnostic only (configuration untouched).

- 38. Direct compiler 2.5: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; diagnostic only (configuration untouched).

- 38. Direct compiler 2.6: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; diagnostic only (configuration untouched).

- 38. Direct compiler 2.7: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; diagnostic only (configuration untouched).

- 38. Direct compiler 3.0a3: {'getAdjustedPitcherStamina': 90.45, 'checkFieldingStat': 97.14286, 'calculateChemistry': 98.064514}; {'.text': 94.54348}; diagnostic only (configuration untouched).

- 38. Direct compiler 3.0a3.2: {'getAdjustedPitcherStamina': 90.45, 'checkFieldingStat': 97.14286, 'calculateChemistry': 98.064514}; {'.text': 94.54348}; diagnostic only (configuration untouched).

- 38. Direct compiler 3.0a3.3: {'getAdjustedPitcherStamina': 90.45, 'checkFieldingStat': 97.14286, 'calculateChemistry': 98.064514}; {'.text': 94.54348}; diagnostic only (configuration untouched).

- 38. Direct compiler 3.0a3.4: {'getAdjustedPitcherStamina': 90.45, 'checkFieldingStat': 97.14286, 'calculateChemistry': 98.064514}; {'.text': 94.54348}; diagnostic only (configuration untouched).

- 38. Direct compiler 3.0a5: {'getAdjustedPitcherStamina': 90.45, 'checkFieldingStat': 97.14286, 'calculateChemistry': 98.064514}; {'.text': 94.54348}; diagnostic only (configuration untouched).

- 38. Direct compiler 3.0a5.2: {'getAdjustedPitcherStamina': 90.45, 'checkFieldingStat': 97.14286, 'calculateChemistry': 98.064514}; {'.text': 94.54348}; diagnostic only (configuration untouched).

- 39. Whole chemistry inline order ('team', 'charIdA', 'charIdB') cached False cast False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 39. Whole chemistry inline order ('team', 'charIdA', 'charIdB') cached False cast True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 39. Whole chemistry inline order ('charIdA', 'charIdB', 'team') cached False cast False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 39. Whole chemistry inline order ('charIdA', 'charIdB', 'team') cached False cast True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 39. Whole chemistry inline order ('charIdB', 'charIdA', 'team') cached False cast False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 39. Whole chemistry inline order ('charIdB', 'charIdA', 'team') cached False cast True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; reverted.

- 39. Whole chemistry inline order ('team', 'charIdA', 'charIdB') cached True cast False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 39. Whole chemistry inline order ('team', 'charIdA', 'charIdB') cached True cast True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 39. Whole chemistry inline order ('charIdA', 'charIdB', 'team') cached True cast False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 39. Whole chemistry inline order ('charIdA', 'charIdB', 'team') cached True cast True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 39. Whole chemistry inline order ('charIdB', 'charIdA', 'team') cached True cast False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 39. Whole chemistry inline order ('charIdB', 'charIdA', 'team') cached True cast True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; reverted.

- 40. charIdA parameter width u8 cached False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 62.258064}; {'.text': 87.28261}; scratch diagnostic.

- 40. charIdA parameter width s8 cached False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 62.258064}; {'.text': 87.28261}; scratch diagnostic.

- 40. charIdA parameter width u16 cached False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 62.258064}; {'.text': 87.28261}; scratch diagnostic.

- 40. charIdA parameter width s16 cached False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 62.258064}; {'.text': 87.28261}; scratch diagnostic.

- 40. charIdA parameter width u32 cached False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; {'.text': 97.608696}; scratch diagnostic.

- 40. charIdA parameter width CHAR_ID cached False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; {'.text': 97.608696}; scratch diagnostic.

- 41. register parameter hint charIdA cached False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; {'.text': 97.608696}; scratch diagnostic.

- 41. register parameter hint charIdB cached False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; {'.text': 97.608696}; scratch diagnostic.

- 41. register parameter hint team cached False: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; {'.text': 97.608696}; scratch diagnostic.

- 40. charIdA parameter width u8 cached True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 72.41936}; {'.text': 90.70652}; scratch diagnostic.

- 40. charIdA parameter width s8 cached True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 72.41936}; {'.text': 90.70652}; scratch diagnostic.

- 40. charIdA parameter width u16 cached True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 72.41936}; {'.text': 90.70652}; scratch diagnostic.

- 40. charIdA parameter width s16 cached True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 72.41936}; {'.text': 90.70652}; scratch diagnostic.

- 40. charIdA parameter width u32 cached True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; scratch diagnostic.

- 40. charIdA parameter width CHAR_ID cached True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; scratch diagnostic.

- 41. register parameter hint charIdA cached True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; scratch diagnostic.

- 41. register parameter hint charIdB cached True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; scratch diagnostic.

- 41. register parameter hint team cached True: {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; {'.text': 99.13043}; scratch diagnostic.

## Final source (after readability rebuild and full unit diff)

```c
#define SQRT2_LINKAGE static
#include "game/stats/stat_lookups.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "header_rep_data.h"

extern f32 lbl_3_data_5FC4[12];

// .text:0x0006D564 size:0xA0 mapped:0x806AC5F8
int getAdjustedPitcherStamina(int team, int rosterID, int amount) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_EXHIBITION_GAME ||
        g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (amount < 0 && PitcherStats_P1_P2[team][rosterID].stamina < -amount) {
            PitcherStats_P1_P2[team][rosterID].stamina = 0;
        } else {
            PitcherStats_P1_P2[team][rosterID].stamina += amount;
        }
    }
    return PitcherStats_P1_P2[team][rosterID].stamina;
}

// .text:0x0006D604 size:0x54 mapped:0x806AC698
BOOL checkFieldingStat(int team, int rosterID, E(int, FIELDING_ABILITY) ability) {
    if (g_d_GameSettings.minigamesEnabled) {
        team = 0;
    }
    if ((1 << ability) & inMemRoster[team][rosterID].stats.FieldingStats) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x0006D658 size:0x7C mapped:0x806AC6EC
int calculateChemistry(int team, E(int, CHAR_ID) charIdA, E(int, CHAR_ID) charIdB) {
    s8 exhibitionMatch = g_d_GameSettings.exhibitionMatchInd;
    int chem = ((u8*)&((CharacterStats*)Static_Stats_Tables.characterStats)[charIdA].chemistry)[charIdB];

    if (!exhibitionMatch && g_d_GameSettings.humanTeamNumber == team &&
        g_d_GameSettings.challengeCaptainStarBought[5] != 0) {
        chem += (int)lbl_3_data_5FC4[10];
    }
    if (chem > 100) {
        chem = 100;
    }
    return chem;
}

```

## Root integration note (2026-10-13)

The shop naming pass replaced challengeCaptainStarBought[5] with challengeShopItemActive[CHALLENGE_SHOP_ITEM_BUDDY_EMBLEM]. A full dependent rebuild kept every function score unchanged and passed all four binary SHA-1 checks. The following current source supersedes the earlier source backup for an Astra resume.


#define SQRT2_LINKAGE static
#include "game/stats/stat_lookups.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "header_rep_data.h"

extern f32 lbl_3_data_5FC4[12];

// .text:0x0006D564 size:0xA0 mapped:0x806AC5F8
int getAdjustedPitcherStamina(int team, int rosterID, int amount) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_EXHIBITION_GAME ||
        g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (amount < 0 && PitcherStats_P1_P2[team][rosterID].stamina < -amount) {
            PitcherStats_P1_P2[team][rosterID].stamina = 0;
        } else {
            PitcherStats_P1_P2[team][rosterID].stamina += amount;
        }
    }
    return PitcherStats_P1_P2[team][rosterID].stamina;
}

// .text:0x0006D604 size:0x54 mapped:0x806AC698
BOOL checkFieldingStat(int team, int rosterID, E(int, FIELDING_ABILITY) ability) {
    if (g_d_GameSettings.minigamesEnabled) {
        team = 0;
    }
    if ((1 << ability) & inMemRoster[team][rosterID].stats.FieldingStats) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x0006D658 size:0x7C mapped:0x806AC6EC
int calculateChemistry(int team, E(int, CHAR_ID) charIdA, E(int, CHAR_ID) charIdB) {
    s8 exhibitionMatch = g_d_GameSettings.exhibitionMatchInd;
    int chem = ((u8*)&((CharacterStats*)Static_Stats_Tables.characterStats)[charIdA].chemistry)[charIdB];

    if (!exhibitionMatch && g_d_GameSettings.humanTeamNumber == team &&
        g_d_GameSettings.challengeShopItemActive[CHALLENGE_SHOP_ITEM_BUDDY_EMBLEM] != 0) {
        chem += (int)lbl_3_data_5FC4[10];
    }
    if (chem > 100) {
        chem = 100;
    }
    return chem;
}


[Astra flag_parameter_u8_first] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; primary source untouched, rejected/tied in build\astra_priority\flag_parameter_u8_first.

[Astra flag_parameter_u8_last] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; primary source untouched, rejected/tied in build\astra_priority\flag_parameter_u8_last.

[Astra flag_parameter_u32_first] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; primary source untouched, rejected/tied in build\astra_priority\flag_parameter_u32_first.

[Astra flag_parameter_u32_last] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; primary source untouched, rejected/tied in build\astra_priority\flag_parameter_u32_last.

[Astra flag_parameter_int_first] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 90.96774}; sections {'.text': 96.95652}; primary source untouched, rejected/tied in build\astra_priority\flag_parameter_int_first.

[Astra flag_parameter_int_last] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 90.96774}; sections {'.text': 96.95652}; primary source untouched, rejected/tied in build\astra_priority\flag_parameter_int_last.

[Astra flag_parameter_s8_first] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; primary source untouched, rejected/tied in build\astra_priority\flag_parameter_s8_first.

[Astra flag_parameter_s8_last] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; primary source untouched, rejected/tied in build\astra_priority\flag_parameter_s8_last.

[Astra row_multiply_u8_int] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; primary source untouched, rejected/tied in build\astra_priority\row_multiply_u8_int.

[Astra row_multiply_u8_unsigned_int] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; primary source untouched, rejected/tied in build\astra_priority\row_multiply_u8_unsigned_int.

[Astra row_multiply_s8_int] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; primary source untouched, rejected/tied in build\astra_priority\row_multiply_s8_int.

[Astra row_multiply_s8_unsigned_int] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; primary source untouched, rejected/tied in build\astra_priority\row_multiply_s8_unsigned_int.

[Astra row_multiply_u32_int] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; primary source untouched, rejected/tied in build\astra_priority\row_multiply_u32_int.

[Astra row_multiply_u32_unsigned_int] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; primary source untouched, rejected/tied in build\astra_priority\row_multiply_u32_unsigned_int.

[Astra compound_u8_inside] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; primary source untouched, rejected/tied in build\astra_priority\compound_u8_inside.

[Astra compound_u8_before] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; primary source untouched, rejected/tied in build\astra_priority\compound_u8_before.

[Astra compound_u8_pointerarg] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 92.90323}; sections {'.text': 97.608696}; primary source untouched, rejected/tied in build\astra_priority\compound_u8_pointerarg.

[Astra compound_s8_inside] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; primary source untouched, rejected/tied in build\astra_priority\compound_s8_inside.

[Astra compound_s8_before] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; primary source untouched, rejected/tied in build\astra_priority\compound_s8_before.

[Astra compound_s8_pointerarg] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 97.41936}; sections {'.text': 99.13043}; primary source untouched, rejected/tied in build\astra_priority\compound_s8_pointerarg.

[Astra compound_int_inside] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 90.96774}; sections {'.text': 96.95652}; primary source untouched, rejected/tied in build\astra_priority\compound_int_inside.

[Astra compound_int_before] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 90.96774}; sections {'.text': 96.95652}; primary source untouched, rejected/tied in build\astra_priority\compound_int_before.

[Astra compound_int_pointerarg] {'getAdjustedPitcherStamina': 100.0, 'checkFieldingStat': 100.0, 'calculateChemistry': 90.96774}; sections {'.text': 96.95652}; primary source untouched, rejected/tied in build\astra_priority\compound_int_pointerarg.

## Astra follow-up final (2026-10-13)

Fresh primary-source rebuild/full-unit diff remains calculateChemistry 97.41936%, other two functions 100%, .text 99.13043% (368 bytes). Source unchanged; no data/BSS/rodata sections. New combinations tested: move the flag read into an explicit inline argument (first/last, u8/u32/int/s8), isolate row multiplication in a typed helper (int/unsigned return, u8/s8/u32 flag cache), compound-mutate charIdA inside the address or before lookup with each cache width, and pass the typed row pointer into a lookup helper. All tie or regress; exact whole-unit results and candidate paths logged above. No shared-file changes. The four residual instructions described at the top remain unchanged. Exhausted for this follow-up; retain the existing source and do not flip Matching.
