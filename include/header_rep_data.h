#include <types.h>

/* This 20-float table (1, pi/2, 1, -1, 3pi/2, pi, -1, 0, -1, 1 -- twice) shows
 * up at the head of virtually every translation unit's .rodata in the original
 * binary, which is the signature of a function-local `static const` belonging
 * to a non-static `inline` helper defined in a widely-included header: MWCC
 * materialises such a local static (as a weak `$localstatic$` symbol) in every
 * TU that merely *sees* the inline definition, even when the function is never
 * called and no out-of-line body is emitted.
 *
 * Keeping that exact shape matters for codegen, not just for data layout: when
 * the first object in a TU's .rodata is a weak (linker-dedupable) symbol, MWCC
 * cannot assume the section's internal offsets survive linking, so it drops its
 * section-base-relative constant-pool addressing and emits a separate
 * `lis/addi` relocation per pool constant. Declaring this table as a plain
 * file-scope `static const` instead makes the first .rodata object stable,
 * which flips MWCC to the shorter base-register form and de-matches every
 * float-heavy function in the unit. */

/* The local static below is a weak symbol named after its enclosing function.
 * When two units of the same REL module are linked from our own objects
 * (Object(Matching)), mwld folds identically named weak symbols into one copy,
 * leaving the module's .rodata 0x50 bytes short. Each such unit therefore
 * defines REP_HEADER_DATA_FN to a unique name before including this header. */
#ifndef REP_HEADER_DATA_FN
#define REP_HEADER_DATA_FN getRepHeaderData
#endif

inline const f32 *REP_HEADER_DATA_FN(void) {
    static const f32 repHeaderData[] = {
        1.f, 1.5707964f, 1.f, -1.f, 4.712389f, 3.1415927f, -1.f, 0.f, -1.f, 1.f,
        1.f, 1.5707964f, 1.f, -1.f, 4.712389f, 3.1415927f, -1.f, 0.f, -1.f, 1.f,
    };
    return repHeaderData;
}
