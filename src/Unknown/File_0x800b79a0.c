#include "Unknown/File_0x800b79a0.h"
#include "C3/charPipeline.h"

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
