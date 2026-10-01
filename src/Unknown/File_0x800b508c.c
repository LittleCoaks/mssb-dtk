#include "Unknown/File_0x800b508c.h"
#include "C3/unktypes.h"

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
