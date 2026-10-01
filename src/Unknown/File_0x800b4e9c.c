#include "Unknown/File_0x800b4e9c.h"
#include "C3/unktypes.h"

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
