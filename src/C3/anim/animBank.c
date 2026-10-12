#include "C3/anim/animBank.h"
#include "C3/unktypes.h"
#include "charPipeline/structures/dolphinString.h"

void ANIMGetKeyFrameFromTrack(struct ANIMAnimTrack* animTrack, f32 time, KeyFrame** currentFrame, KeyFrame** nextFrame,
                              u16* cachedFrame) {
    KeyFrame* frame;
    u16 i;
    u16 count;

    i = animTrack->keyFrames[*cachedFrame].time <= time ? *cachedFrame : 0;
    count = animTrack->totalFrames;
    while (count--) {
        frame = &animTrack->keyFrames[i];
        if (frame->time <= time) {
            if (i < animTrack->totalFrames - 1) {
                if (animTrack->keyFrames[i + 1].time > time) {
                    if (currentFrame) {
                        *currentFrame = frame;
                    }
                    if (nextFrame) {
                        *nextFrame = &animTrack->keyFrames[i + 1];
                    }
                    *cachedFrame = i;
                    return;
                }
            } else {
                if (currentFrame) {
                    *currentFrame = frame;
                }
                if (nextFrame) {
                    *nextFrame = animTrack->keyFrames;
                }
                *cachedFrame = i;
                return;
            }
        }
        i = (i + 1) % animTrack->totalFrames;
    }
}

struct ANIMAnimTrack* ANIMGetTrackFromSequence(ANIMSequences* animSeq, u16 animTrackID) {
    u32 i;

    for (i = 0; i < animSeq->totalTracks; i++) {
        if (animSeq->trackArray[i].trackID == animTrackID) {
            return &animSeq->trackArray[i];
        }
    }
    return NULL;
}

ANIMSequences* ANIMGetSequence(ANIMBank* animBank, char* sequenceName, u16 seqNum) {
    u32 i;

    if (sequenceName != NULL) {
        for (i = 0; i < animBank->numSequences; i++) {
            if (Strcmp(animBank->animSequences[i].sequenceName, sequenceName) == 0) {
                return &animBank->animSequences[i];
            }
        }
    } else if (animBank == NULL) {
        return NULL;
    }
    return &animBank->animSequences[seqNum];
}

void ANIMGet(ANIMBank* animBank) {
    ANIMSequences* sequences;
    struct ANIMAnimTrack* tracks;
    KeyFrame* keyFrames;
    u32 i;

    if (animBank->userDataSize && animBank->userData) {
        animBank->userData = (void*)((u32)animBank->userData + (u32)animBank);
    }
    sequences = (ANIMSequences*)((u32)animBank + sizeof(ANIMBank));
    tracks = (struct ANIMAnimTrack*)((u32)sequences + animBank->numSequences * sizeof(ANIMSequences));
    keyFrames = (KeyFrame*)((u32)tracks + animBank->numTracks * sizeof(struct ANIMAnimTrack));
    animBank->animSequences = (ANIMSequences*)((u32)animBank->animSequences + (u32)animBank);

    for (i = 0; i < animBank->numSequences; i++) {
        sequences[i].sequenceName = (char*)((u32)animBank + (u32)sequences[i].sequenceName);
        sequences[i].trackArray = (struct ANIMAnimTrack*)((u32)animBank + (u32)sequences[i].trackArray);
    }
    for (i = 0; i < animBank->numTracks; i++) {
        tracks[i].keyFrames = (KeyFrame*)((u32)animBank + (u32)tracks[i].keyFrames);
    }
    for (i = 0; i < animBank->numKeyFrames; i++) {
        keyFrames[i].setting = (char*)((u32)animBank + (u32)keyFrames[i].setting);
        keyFrames[i].interpolation = (char*)((u32)animBank + (u32)keyFrames[i].interpolation);
    }
}
