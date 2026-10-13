#include "C3/actor/boneAnim.h"
#include "C3/skinning.h"

void ACTSetBoneTrack(sBone* bone, struct ANIMAnimTrack* track, f32 time, BOOL blend) {
    Quaternion q;
    u8 flags;

    if (track == NULL) {
        if (bone->animPipe != NULL && bone->animPipe->control != NULL) {
            bone->animPipe->control->type = 0;
            bone->animPipe->currentTrack = NULL;
        }
        return;
    }

    if (bone->animPipe == NULL) {
        bone->animPipe = (struct ANIMPipe*)_OSAllocFromHeap(0x20, sizeof(struct ANIMPipe));
        bone->animPipe->time = 0.0f;
        bone->animPipe->unk04 = 0.0f;
        bone->animPipe->unk08 = 1.0f;
        bone->animPipe->currentTrack = NULL;
        bone->animPipe->control = NULL;
        bone->animPipe->replaceHierarchyCtrl = 0;
        bone->animPipe->unk17 = 1;
        bone->animPipe->unk18 = 1;
    }
    bone->animPipe->unk14 = 0;

    if (blend != FALSE) {
        if (bone->animPipe->control != NULL) {
            if (bone->animPipe->control->type != 0) {
                bone->unkA4 = bone->animationCtrl;
            } else {
                bone->unkA4 = bone->orientationCtrl;
            }
        } else {
            bone->unkA4 = bone->animationCtrl;
        }
    }

    ANIMBind(bone->animPipe, &bone->animationCtrl, track, time);

    if (bone->unk136 != 0) {
        bone->animPipe->currentTrack->interpolationType &= ~3;
    }

    flags = bone->orientationCtrl.type;

    if ((flags & CTRL_TRANS) && !(track->animType & 1)) {
        CTRLGetTranslation(&bone->orientationCtrl, &q.x, &q.y, &q.z);
        CTRLSetTranslation(&bone->animationCtrl, q.x, q.y, q.z);
    }

    if ((flags & CTRL_SCALE) && !(track->animType & 2)) {
        CTRLGetScale(&bone->orientationCtrl, &q.x, &q.y, &q.z);
        CTRLSetScale(&bone->animationCtrl, q.x, q.y, q.z);

        if ((flags & CTRL_SCALE_QUAT) && !(track->animType & 0x20)) {
            CTRL_GetQuatUnk(&bone->orientationCtrl, &q.x, &q.y, &q.z, &q.w);
        } else {
            q.x = 0.0f;
            q.y = 0.0f;
            q.z = 0.0f;
            q.w = 1.0f;
        }
        CTRL_SetQuatUnk(&bone->animationCtrl, q.x, q.y, q.z, q.w);
    }

    if ((flags & CTRL_ROT_EULER) && !(track->animType & 4)) {
        CTRLGetRotation(&bone->orientationCtrl, &q.x, &q.y, &q.z);
        CTRLSetRotation(&bone->animationCtrl, q.x, q.y, q.z);
    } else if ((flags & CTRL_ROT_QUAT) && !(track->animType & 8)) {
        CTRLGetQuat(&bone->orientationCtrl, &q.x, &q.y, &q.z, &q.w);
        CTRLSetQuat(&bone->animationCtrl, q.x, q.y, q.z, q.w);
    }

    if (blend == FALSE) {
        bone->unkA4 = bone->animationCtrl;
    }
}
