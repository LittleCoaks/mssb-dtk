#include "C3/anim/animPipe.h"
#include "C3/charPipeline.h"

void Squad(void) {
    return;
}

void GetData(void) {
    return;
}

void DoTranslationAnimation(void) {
    return;
}

void DoScaleAnimation(void) {
    return;
}

void DoEulerAnimation(void) {
    return;
}

void DoQuatAnimation(void) {
    return;
}

void ANIMTick(struct ANIMPipe* animPipe, u8 unk) {
    return;
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
