#include "C3/anim/animPipe.h"
#include "C3/charPipeline.h"

static void slerpQuat(const f32* a, const f32* b, f32 t, f32* out) {
    f32 dot;
    f32 theta;
    f32 sinTheta;
    f32 wa;
    f32 wb;
    f32 bSign;
    s32 i;

    dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
    bSign = 1.0f;
    if (dot < 0.0f) {
        dot = -dot;
        bSign = -1.0f;
    }

    if (1.0f - dot > 0.000001f) {
        theta = acos(dot);
        sinTheta = sin(theta);
        wa = sin((1.0f - t) * theta) / sinTheta;
        wb = sin(t * theta) / sinTheta;
    } else {
        wa = 1.0f - t;
        wb = t;
    }

    for (i = 0; i < 4; i++) {
        out[i] = wa * a[i] + wb * (bSign * b[i]);
    }
}

void Squad(const f32* q0, f32 t, const f32* s0, const f32* s1, const f32* q1, f32* out) {
    f32 a[4];
    f32 b[4];
    f32 h;

    slerpQuat(q0, q1, t, a);
    slerpQuat(s0, s1, t, b);
    h = 2.0f * t * (1.0f - t);
    slerpQuat(a, b, h, out);
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

void DoScaleAnimation(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame, u8 unk) {
    return;
}

static f32 keyFraction(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame) {
    f32 elapsed = animPipe->time - currentFrame->time;
    f32 span;

    if (elapsed == 0.0f) {
        return 0.0f;
    }
    if (nextFrame->time > currentFrame->time) {
        span = nextFrame->time - currentFrame->time;
    } else {
        span = animPipe->currentTrack->animTime - currentFrame->time;
        if (animPipe->currentTrack->animTime >= currentFrame->time) {
            return 1.0f;
        }
    }
    return elapsed / span;
}

static u32 keyElementSize(u8 type) {
    switch (type) {
    case 0:
    case 1:
        return 1;
    case 2:
    case 3:
        return 2;
    case 4:
        return 4;
    default:
        return 0;
    }
}

static s32 evaluateKeyVector(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame, s32 wrapAngles, f32* out) {
    struct ANIMAnimTrack* track = animPipe->currentTrack;
    u8 type = track->quantizeInfo >> 4;
    f32 scale = 1.0f / (f32)(1u << (track->quantizeInfo & 0xF));
    u32 vecSize = keyElementSize(type) * 3;
    u32 offset = (track->animType & 2) ? vecSize : 0;
    f32 cur[3];
    f32 next[3];
    f32 t;
    s32 i;

    GetData(type, (u8*)currentFrame->setting + offset, cur, scale, 3);
    GetData(type, (u8*)nextFrame->setting + offset, next, scale, 3);
    t = keyFraction(animPipe, currentFrame, nextFrame);

    switch ((track->interpolationType >> 4) & 7) {
    case 0:
        for (i = 0; i < 3; i++) {
            out[i] = cur[i];
        }
        break;
    case 1:
        for (i = 0; i < 3; i++) {
            f32 d = cur[i] - next[i];

            if (wrapAngles && d > 180.0f) {
                cur[i] -= 360.0f;
            } else if (wrapAngles && d < -180.0f) {
                next[i] -= 360.0f;
            }
            out[i] = (1.0f - t) * cur[i] + t * next[i];
        }
        break;
    case 2: {
        f32 tanOut[3];
        f32 tanIn[3];
        f32 t2 = t * t;
        f32 t3 = t2 * t;
        f32 h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
        f32 h10 = t3 - 2.0f * t2 + t;
        f32 h01 = -2.0f * t3 + 3.0f * t2;
        f32 h11 = t3 - t2;

        GetData(type, (u8*)currentFrame->interpolation + vecSize + offset, tanOut, scale, 3);
        GetData(type, (u8*)nextFrame->interpolation + offset, tanIn, scale, 3);
        for (i = 0; i < 3; i++) {
            out[i] = h00 * cur[i] + h10 * tanOut[i] + h01 * next[i] + h11 * tanIn[i];
        }
        break;
    }
    default:
        return;
    }

    return TRUE;
}

void DoEulerAnimation(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame) {
    f32 out[3];

    if (evaluateKeyVector(animPipe, currentFrame, nextFrame, TRUE, out)) {
        CTRLSetRotation(animPipe->control, out[0], out[1], out[2]);
    }
}

void DoTranslationAnimation(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame, u8 unk) {
    f32 out[3];

    if (evaluateKeyVector(animPipe, currentFrame, nextFrame, FALSE, out)) {
        CTRLSetTranslation(animPipe->control, out[0], out[1], out[2]);
    }
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
