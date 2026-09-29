#include "Unknown/File_0x800b2c44.h"

/* MSSB's actor is larger than the SDK's `Actor` in C3/actor.h; the
 * per-bone forward matrix array sits at 0x60 here. */
typedef struct {
    /* 0x00 */ u8 _00[0x60];
    /* 0x60 */ Mtx* forwardMtxArray;
} ActorBoneMtxView;

void maybeTransformVectorByAnimationMatrix(void* actor, u16 boneIndex, Vec* out) {
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;
    PSMTXMultVec(((ActorBoneMtxView*)actor)->forwardMtxArray[boneIndex], out, out);
}
