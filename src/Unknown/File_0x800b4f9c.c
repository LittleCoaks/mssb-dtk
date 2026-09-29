#include "Unknown/File_0x800b4f9c.h"

struct ANIMAnimTrack* ANIMGetTrackFromSequence(ANIMSequences* animSeq, u16 animTrackID) {
    u32 i;

    for (i = 0; i < animSeq->totalTracks; i++) {
        if (animSeq->trackArray[i].trackID == animTrackID) {
            return &animSeq->trackArray[i];
        }
    }
    return NULL;
}
