#include "C3/actor/boneAnim.h"
#include "C3/skinning.h"

void ACTSetBoneTrack(sBone* bone, struct ANIMAnimTrack* track, f32 time, BOOL blend) {
    struct ANIMPipe* pipe;
    Control* orientation = &bone->orientationCtrl;
    Control* animation = &bone->animationCtrl;
    u8 flags;
    f32 x;
    f32 y;
    f32 z;
    f32 w;

    if (track == NULL) {
        pipe = bone->animPipe;
        if (pipe != NULL && pipe->control != NULL) {
            pipe->control->type = 0;
            pipe->currentTrack = NULL;
        }
        return;
    }

    pipe = bone->animPipe;
    if (pipe == NULL) {
        pipe = (struct ANIMPipe*)_OSAllocFromHeap(0x20, sizeof(struct ANIMPipe));
        bone->animPipe = pipe;
        pipe->time = 0.0f;
        pipe->unk04 = 0.0f;
        pipe->unk08 = 1.0f;
        pipe->currentTrack = NULL;
        pipe->control = NULL;
        pipe->replaceHierarchyCtrl = 0;
        pipe->unk17 = 1;
        pipe->unk18 = 1;
    }
    pipe->unk14 = 0;

    if (blend != FALSE) {
        if (pipe->control != NULL && pipe->control->type == 0) {
            bone->unkA4 = bone->orientationCtrl;
        } else {
            bone->unkA4 = bone->animationCtrl;
        }
    }

    ANIMBind(pipe, animation, track, time);

    if (bone->unk136 != 0) {
        pipe->currentTrack->interpolationType &= ~3;
    }

    flags = orientation->type;

    if ((flags & CTRL_TRANS) && !(track->animType & 1)) {
        CTRLGetTranslation(orientation, &x, &y, &z);
        CTRLSetTranslation(animation, x, y, z);
    }

    if ((flags & CTRL_SCALE) && !(track->animType & 2)) {
        CTRLGetScale(orientation, &x, &y, &z);
        CTRLSetScale(animation, x, y, z);

        if ((flags & CTRL_SCALE_QUAT) && !(track->animType & 0x20)) {
            CTRL_GetQuatUnk(orientation, &x, &y, &z, &w);
        } else {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
            w = 1.0f;
        }
        CTRL_SetQuatUnk(animation, x, y, z, w);
    }

    if ((flags & CTRL_ROT_EULER) && !(track->animType & 4)) {
        CTRLGetRotation(orientation, &x, &y, &z);
        CTRLSetRotation(animation, x, y, z);
    }

    if ((flags & CTRL_ROT_QUAT) && !(track->animType & 8)) {
        CTRLGetQuat(orientation, &x, &y, &z, &w);
        CTRLSetQuat(animation, x, y, z, w);
    }

    if (blend == FALSE) {
        bone->unkA4 = bone->animationCtrl;
    }
}
