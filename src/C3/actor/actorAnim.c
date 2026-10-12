#include "C3/actor/actorAnim.h"
#include "Unknown/File_0x800b4f9c.h"
#include "Unknown/File_0x800acf14.h"
#include "C3/anim.h"
#include "C3/skinning.h"

f32 fn_800B4A44(void* obj, u16 bone) {
    Actor* actor = obj;

    struct ANIMPipe* pipe = actor->boneArray[bone]->animPipe;
    struct ANIMAnimTrack* track;

    if (pipe != NULL) {
        if (!pipe->unk17) {
            return pipe->time;
        }
        track = pipe->currentTrack;
        if (track != NULL) {
            return track->animTime - pipe->time;
        }
    }
    return 0.0f;
}

f32 scanBoneAttachmentData(void* obj) {
    Actor* actor = obj;
    u32 i;

    for (i = 0; i < actor->totalBones; i++) {
        struct ANIMPipe* pipe = actor->boneArray[i]->animPipe;
        struct ANIMAnimTrack* track;

        if (pipe != NULL) {
            if (!pipe->unk17) {
                return pipe->time;
            }
            track = pipe->currentTrack;
            if (track != NULL) {
                return track->animTime - pipe->time;
            }
        }
    }
    return 0.0f;
}

void updateBoneParam(void* obj, int flag) {
    Actor* actor = obj;
    u32 i;

    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->animPipe != NULL) {
            actor->boneArray[i]->animPipe->unk18 = flag;
        }
    }
}

void AnimateActorBones(void* obj) {
    Actor* actor = obj;
    u32 i;

    actor->unk8C += actor->unk90;
    if (actor->unk8C > 1.0f) {
        actor->unk8C = 1.0f;
    }
    for (i = 0; i < actor->totalBones; i++) {
        ANIMTick(actor->boneArray[i]->animPipe, actor->unk99);
    }
}

void setAllBoneEventFlags(void* obj, BOOL flag) {
    Actor* actor = obj;
    u32 i;

    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->animPipe != NULL) {
            actor->boneArray[i]->animPipe->unk17 = flag;
        }
    }
}

void fn_800B4C04(void* obj, f32 speed) {
    Actor* actor = obj;
    u32 i;

    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->animPipe != NULL) {
            actor->boneArray[i]->animPipe->unk08 = speed;
        }
    }
}

f32 fn_800B4C40(void* obj) {
    Actor* actor = obj;
    u32 i;

    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->animPipe != NULL && actor->boneArray[i]->animPipe->currentTrack != NULL) {
            return actor->boneArray[i]->animPipe->time;
        }
    }
    return 0.0f;
}

void setActorAnimFrame(void* obj, f32 frame) {
    Actor* actor = obj;
    u32 i;

    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->animPipe != NULL) {
            actor->boneArray[i]->animPipe->time = frame;
        }
    }
}

void fn_800B4CDC(void* obj) {
    Actor* actor = obj;
    int i;

    for (i = actor->totalBones - 1; i >= 0; i--) {
        if (actor->boneArray[i]->animPipe != NULL) {
            fn_800ACFB0(actor->boneArray[i]->animPipe);
            actor->boneArray[i]->animPipe = NULL;
        }
    }
}

void ACTSetAnimation(Actor *actor, ANIMBank *animBank, char *sequenceName, u16 seqNum, f32 startFrame, f32 time) {
    u16 i;
    ANIMSequences* sequence = ANIMGetSequence(animBank, sequenceName, seqNum);
    struct ANIMAnimTrack* track = NULL;

    for (i = 0; i < actor->totalBones; i++) {
        sBone* bone;
        BOOL blend;

        if (sequence != NULL) {
            track = ANIMGetTrackFromSequence(sequence, actor->boneArray[i]->boneID);
        }
        bone = actor->boneArray[i];
        blend = FALSE;
        if (actor->unk8C < 1.0f && bone->unk134 != 0) {
            blend = TRUE;
        }
        ACTSetBoneTrack(bone, track, startFrame, blend);
        if (actor->boneArray[i]->unk134 & 0x1C) {
            actor->boneArray[i]->unk134 |= 0x20;
        } else {
            actor->boneArray[i]->unk134 &= 0xFFDF;
        }
    }
    actor->unk8C = time ? 0.0f : 1.0f;
    actor->unk90 = time;
}
