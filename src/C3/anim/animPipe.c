#include "C3/anim/animPipe.h"
#include "C3/charPipeline.h"

void Squad(void) {
    return;
}

void GetData(u8 type, void* src, f32* dst, f32 scale, u8 count) {
    u8 i;

    switch (type) {
    case 0:
        for (i = 0; i < count; i++) {
            dst[i] = (f32)((u8*)src)[i] * scale;
        }
        break;
    case 1:
        for (i = 0; i < count; i++) {
            dst[i] = (f32)((s8*)src)[i] * scale;
        }
        break;
    case 2:
        for (i = 0; i < count; i++) {
            dst[i] = (f32)((u16*)src)[i] * scale;
        }
        break;
    case 3:
        for (i = 0; i < count; i++) {
            dst[i] = (f32)((s16*)src)[i] * scale;
        }
        break;
    case 4:
        for (i = 0; i < count; i++) {
            dst[i] = ((f32*)src)[i];
        }
        break;
    }
}

void DoTranslationAnimation(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame, u8 unk) {
    return;
}

void DoScaleAnimation(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame, u8 unk) {
    return;
}

void DoEulerAnimation(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame) {
    return;
}

void DoQuatAnimation(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame) {
    return;
}

void ANIMTick(struct ANIMPipe* animPipe, u8 unk) {
    struct ANIMAnimTrack* track;
    KeyFrame* currentFrame;
    KeyFrame* nextFrame;
    f32* values;
    f32 scale;
    s32 i;

    if (animPipe == NULL) {
        return;
    }
    track = animPipe->currentTrack;
    if (track == NULL) {
        return;
    }

    ANIMGetKeyFrameFromTrack(track, animPipe->time, &currentFrame, &nextFrame, &animPipe->unk14);

    if (track->animType & 0x10) {
        values = (f32*)currentFrame->setting;
        scale = 1.0f / (f32)(1u << (track->quantizeInfo & 0xF));
        for (i = 0; i < 12; i++) {
            values[i] *= scale;
        }
        CTRLSetMatrix(animPipe->control, (MtxPtr)values);
    } else {
        if (track->animType & 2) {
            DoScaleAnimation(animPipe, currentFrame, nextFrame, unk);
        }
        if (track->animType & 8) {
            DoQuatAnimation(animPipe, currentFrame, nextFrame);
        } else if (track->animType & 4) {
            DoEulerAnimation(animPipe, currentFrame, nextFrame);
        }
        if (track->animType & 1) {
            DoTranslationAnimation(animPipe, currentFrame, nextFrame, unk);
        }
    }

    animPipe->unk04 = animPipe->time;

    if (animPipe->unk17 == 1) {
        animPipe->time += animPipe->unk08;
        if (animPipe->time > track->animTime) {
            if (animPipe->unk18 != 0) {
                animPipe->time -= track->animTime;
            } else {
                animPipe->time = track->animTime;
            }
        }
    } else {
        animPipe->time -= animPipe->unk08;
        if (animPipe->time < 0.0f) {
            if (animPipe->unk18 != 0) {
                animPipe->time += track->animTime;
            } else {
                animPipe->time = 0.0f;
            }
        }
    }
}

void ANIMBind(struct ANIMPipe* animPipe, Control* control, struct ANIMAnimTrack* animTrack, f32 time) {
    if (animTrack == NULL) {
        return;
    }
    control->type = 0;
    animPipe->control = control;
    animPipe->currentTrack = animTrack;
    animPipe->time = time;
    animPipe->unk04 = time;
    animPipe->replaceHierarchyCtrl = animTrack->replaceHierarchyCtrl;
    animPipe->unk14 = 0;
}
