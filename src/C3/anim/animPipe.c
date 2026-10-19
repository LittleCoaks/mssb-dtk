#include "Dolphin/os.h"
#include "math.h"
#include "C3/anim/animPipe.h"
#include "C3/charPipeline.h"

static const Quaternion sIdentityQuat0 = {0.0f, 0.0f, 0.0f, 1.0f};
static const Quaternion sIdentityQuat1 = {0.0f, 0.0f, 0.0f, 1.0f};
static const Quaternion sIdentityQuat2 = {0.0f, 0.0f, 0.0f, 1.0f};

f32 lbl_803CBB48 = 1.0f / 16384.0f;
f32 lbl_803CBB4C = 1.0f / 16384.0f;
u8 lbl_803CBB50 = 3;
u8 lbl_803CBB51 = 3;
static inline void SlerpQuat(f32* p, f32* q, f32 t, f32* r) {
    f32 cosom;
    f32 omega;
    f32 tOmega;
    f32 inv;
    f32 scale0;
    f32 scale1;

    cosom = p[0] * q[0] + p[1] * q[1] + p[2] * q[2] + p[3] * q[3];
    if (1.0f + cosom > 0.000001f) {
        if (1.0f - cosom > 0.000001f) {
            omega = acos(cosom);
            tOmega = t * omega;
            inv = 1.0f / (f32)sin(omega);
            scale0 = inv * (f32)sin(omega - tOmega);
            scale1 = inv * (f32)sin(tOmega);
        } else {
            scale0 = 1.0f - t;
            scale1 = t;
        }
        r[0] = scale0 * p[0] + scale1 * q[0];
        r[1] = scale0 * p[1] + scale1 * q[1];
        r[2] = scale0 * p[2] + scale1 * q[2];
        r[3] = scale0 * p[3] + scale1 * q[3];
    } else {
        r[0] = -q[1];
        r[1] = q[0];
        r[2] = -q[3];
        r[3] = q[2];
        tOmega = 1.5707964f * t;
        scale0 = sin(1.5707964f - tOmega);
        scale1 = sin(tOmega);
        r[0] = scale0 * p[0] + scale1 * r[0];
        r[1] = scale0 * p[1] + scale1 * r[1];
        r[2] = scale0 * p[2] + scale1 * r[2];
        r[3] = scale0 * p[3] + scale1 * r[3];
    }
}
void Squad(f32* q0, f32 t, f32* a, f32* b, f32* q1, f32* out) {
    f32 tmp0[4];
    f32 tmp1[4];
    f32 h;

    h = 2.0f * (1.0f - t) * t;
    SlerpQuat(q0, q1, t, tmp0);
    SlerpQuat(a, b, t, tmp1);
    SlerpQuat(tmp0, tmp1, h, out);
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
static inline u32 GetTypeSize(u8 type) {
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

static inline f32 GetFraction(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame) {
    f32 elapsed = animPipe->time - currentFrame->time;

    if (!elapsed) {
        return 0.0f;
    }
    if (nextFrame->time > currentFrame->time) {
        return elapsed / (nextFrame->time - currentFrame->time);
    }
    if (animPipe->currentTrack->animTime >= currentFrame->time) {
        return 1.0f;
    }
    return elapsed / (animPipe->currentTrack->animTime - currentFrame->time);
}

static inline f32 EaseTime(f32 t, f32 easeOut, f32 easeIn) {
    f32 sum = easeOut + easeIn;
    f32 inv;
    f32 k;

    if (t == 0.0f || t == 1.0f || sum == 0.0f) {
        return t;
    }
    if (sum > 1.0f) {
        inv = 1.0f / sum;
        easeOut *= inv;
        easeIn *= inv;
        k = 0.5f - inv;
    } else {
        k = 0.5f - 1.0f / sum;
    }
    if (t < easeOut) {
        return t * (t * (k / easeOut));
    }
    if (t < 1.0f - easeIn) {
        return k * (2.0f * t - easeOut);
    }
    t = 1.0f - t;
    return 1.0f - t * (t * (k / easeIn));
}

static inline void LerpVec(f32 t, f32* a, f32* b, f32* out) {
    s32 i;

    for (i = 0; i < 3; i++) {
        out[i] = t * b[i] + (1.0f - t) * a[i];
    }
}

static inline void BezierVec(f32 t, f32* p0, f32* tan0, f32* tan1, f32* p1, f32* out) {
    f32 tt = t * t;
    f32 t3 = 3.0f * t;
    f32 ttt = t * tt;
    f32 omt = 1.0f - t;
    f32 tt3 = 3.0f * tt;
    f32 f;
    s32 i;

    for (i = 0; i < 3; i++) {
        f = omt * p0[i] + t3 * (tan0[i] + p0[i]);
        f = tt3 * (tan1[i] + p1[i]) + omt * f;
        out[i] = omt * f + ttt * p1[i];
    }
}

static inline void HermiteVec(f32 t, f32* p0, f32* tan0, f32* tan1, f32* p1, f32* out) {
    f32 tt = t * t;
    f32 ttt = tt * t;
    f32 a = 2.0f * ttt - 3.0f * tt;
    f32 h00 = a + 1.0f;
    f32 h01 = -a;
    f32 h10 = ttt + (t - 2.0f * tt);
    f32 h11 = -tt + ttt;
    s32 i;

    for (i = 0; i < 3; i++) {
        out[i] = h00 * p0[i] + h01 * p1[i] + h10 * tan0[i] + h11 * tan1[i];
    }
}
void DoTranslationAnimation(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame) {
    f32 v[5][3];
    f32 easeOut;
    f32 easeIn;
    u32 vecSize;
    f32 scale;
    u8 type;
    u32 offset;
    f32 t;
    u8 mode;
    char* data;

    scale = 1.0f / (f32)(1 << (animPipe->currentTrack->quantizeInfo & 0xF));
    type = animPipe->currentTrack->quantizeInfo >> 4;
    vecSize = GetTypeSize(type) * 3;

    offset = 0;
    if (animPipe->currentTrack->animType & 2) {
        offset = GetTypeSize(type) * 3;
        if (animPipe->currentTrack->animType & 0x20) {
            offset += GetTypeSize(type) * 4;
        }
    }
    if (animPipe->currentTrack->animType & 4) {
        offset += vecSize;
    }
    if (animPipe->currentTrack->animType & 8) {
        offset += 8;
    }
    GetData(type, (u8*)currentFrame->setting + offset, v[4], scale, 3);
    GetData(type, (u8*)nextFrame->setting + offset, v[3], scale, 3);

    t = GetFraction(animPipe, currentFrame, nextFrame);

    offset = 0;
    if (animPipe->currentTrack->animType & 2) {
        mode = (animPipe->currentTrack->interpolationType >> 2) & 3;
        if (mode == 2) {
            offset = vecSize * 2;
        }
        if (mode == 3) {
            offset = vecSize * 2 + 4;
        }
    }
    if (animPipe->currentTrack->animType & 8) {
        mode = (animPipe->currentTrack->interpolationType >> 4) & 7;
        if (mode == 4) {
            offset += 0x10;
        }
        if (mode == 5) {
            offset += 0x14;
        }
    } else if (animPipe->currentTrack->animType & 4) {
        mode = (animPipe->currentTrack->interpolationType >> 4) & 7;
        if (mode == 2) {
            offset += vecSize * 2;
        }
        if (mode == 3) {
            offset += vecSize * 2 + 4;
        }
    }

    switch (animPipe->currentTrack->interpolationType & 3) {
    case 0:
        v[2][0] = v[4][0];
        v[2][1] = v[4][1];
        v[2][2] = v[4][2];
        break;
    case 1:
        LerpVec(t, v[4], v[3], v[2]);
        break;
    case 2:
        GetData(type, currentFrame->interpolation + offset + vecSize, v[1], scale, 3);
        GetData(type, nextFrame->interpolation + offset, v[0], scale, 3);
        BezierVec(t, v[4], v[1], v[0], v[3], v[2]);
        break;
    case 3:
        data = currentFrame->interpolation + offset + vecSize;
        GetData(type, data, v[1], scale, 3);
        GetData(lbl_803CBB51, data + vecSize + 2, &easeOut, lbl_803CBB4C, 1);
        data = nextFrame->interpolation + offset;
        GetData(type, data, v[0], scale, 3);
        GetData(lbl_803CBB51, data + vecSize * 2, &easeIn, lbl_803CBB4C, 1);

        t = EaseTime(t, easeOut, easeIn);

        HermiteVec(t, v[4], v[1], v[0], v[3], v[2]);
        break;
    default:
        OSPanic("animPipe.c", 546, "Unknown pInterpolation pSetting!(未知の補間タイプが指定されています)");
        break;
    }

    CTRLSetTranslation(animPipe->control, v[2][0], v[2][1], v[2][2]);
}
void DoScaleAnimation(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame, u8 unk) {
    f32 cur[3];
    f32 next[3];
    f32 result[3];
    f32 tanOut[3];
    f32 tanIn[3];
    Quaternion curQuat = sIdentityQuat0;
    Quaternion nextQuat = sIdentityQuat1;
    Quaternion resultQuat = sIdentityQuat2;
    f32 easeOut;
    f32 easeIn;
    u32 vecSize;
    f32 scale;
    u8 type;
    f32 t;
    char* data;

    scale = 1.0f / (f32)(1 << (animPipe->currentTrack->quantizeInfo & 0xF));
    type = animPipe->currentTrack->quantizeInfo >> 4;
    vecSize = GetTypeSize(type) * 3;

    GetData(type, currentFrame->setting, cur, scale, 3);
    GetData(type, nextFrame->setting, next, scale, 3);
    if (animPipe->currentTrack->animType & 0x20) {
        GetData(type, currentFrame->setting + vecSize, (f32*)&curQuat, scale, 4);
        GetData(type, nextFrame->setting + vecSize, (f32*)&nextQuat, scale, 4);
    }

    t = GetFraction(animPipe, currentFrame, nextFrame);

    switch ((animPipe->currentTrack->interpolationType & 0xC) >> 2) {
    case 0:
        result[0] = cur[0];
        result[1] = cur[1];
        result[2] = cur[2];
        if (animPipe->currentTrack->animType & 0x20) {
            resultQuat.x = curQuat.x;
            resultQuat.y = curQuat.y;
            resultQuat.z = curQuat.z;
            resultQuat.w = curQuat.w;
        }
        break;
    case 1:
        LerpVec(t, cur, next, result);
        if (animPipe->currentTrack->animType & 0x20) {
            SlerpQuat((f32*)&curQuat, (f32*)&nextQuat, t, (f32*)&resultQuat);
        }
        break;
    case 2:
        GetData(type, currentFrame->interpolation + vecSize, tanOut, scale, 3);
        GetData(type, nextFrame->interpolation, tanIn, scale, 3);
        BezierVec(t, cur, tanOut, tanIn, next, result);
        if (animPipe->currentTrack->animType & 0x20) {
            SlerpQuat((f32*)&curQuat, (f32*)&nextQuat, t, (f32*)&resultQuat);
        }
        break;
    case 3:
        data = currentFrame->interpolation + vecSize;
        GetData(type, data, tanOut, scale, 3);
        GetData(lbl_803CBB51, data + vecSize + 2, &easeOut, lbl_803CBB4C, 1);
        GetData(type, nextFrame->interpolation, tanIn, scale, 3);
        GetData(lbl_803CBB51, nextFrame->interpolation + vecSize * 2, &easeIn, lbl_803CBB4C, 1);
        t = EaseTime(t, easeOut, easeIn);
        HermiteVec(t, cur, tanOut, tanIn, next, result);
        if (animPipe->currentTrack->animType & 0x20) {
            SlerpQuat((f32*)&curQuat, (f32*)&nextQuat, t, (f32*)&resultQuat);
        }
        break;
    default:
        OSPanic("animPipe.c", 424, "Unknown pInterpolation pSetting!(未知の補間タイプが指定されています)");
        break;
    }

    CTRLSetScale(animPipe->control, result[0], result[1], result[2]);
    CTRL_SetQuatUnk(animPipe->control, resultQuat.x, resultQuat.y, resultQuat.z, resultQuat.w);
}
void DoEulerAnimation(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame) {
    f32 cur[3];
    f32 next[3];
    f32 result[3];
    f32 tanOut[3];
    f32 tanIn[3];
    u32 vecSize;
    f32 scale;
    u8 type;
    u32 offset;
    f32 t;
    u8 mode;
    f32 tt;
    f32 t3;
    f32 ttt;
    f32 omt;
    f32 tt3;
    s32 i;

    scale = 1.0f / (f32)(1 << (animPipe->currentTrack->quantizeInfo & 0xF));
    type = animPipe->currentTrack->quantizeInfo >> 4;
    vecSize = GetTypeSize(type) * 3;

    offset = 0;
    if (animPipe->currentTrack->animType & 2) {
        offset = vecSize;
    }
    GetData(type, (u8*)currentFrame->setting + offset, cur, scale, 3);
    GetData(type, (u8*)nextFrame->setting + offset, next, scale, 3);

    t = GetFraction(animPipe, currentFrame, nextFrame);

    offset = 0;
    if (animPipe->currentTrack->animType & 2) {
        mode = (animPipe->currentTrack->interpolationType & 0xC) >> 2;
        if (mode == 2) {
            offset = vecSize * 2;
        }
        if (mode == 3) {
            offset = vecSize * 2 + 4;
        }
    }

    switch ((animPipe->currentTrack->interpolationType & 0x70) >> 4) {
    case 0:
        result[0] = cur[0];
        result[1] = cur[1];
        result[2] = cur[2];
        break;
    case 1:
        for (i = 0; i < 3; i++) {
            if (cur[i] - next[i] > 180.0f) {
                cur[i] -= 360.0f;
            } else if (cur[i] - next[i] < -180.0f) {
                next[i] -= 360.0f;
            }
            result[i] = t * next[i] + (1.0f - t) * cur[i];
        }
        break;
    case 2:
        GetData(type, currentFrame->interpolation + offset + vecSize, tanOut, scale, 3);
        GetData(type, (u8*)nextFrame->interpolation + offset, tanIn, scale, 3);
        tt = t * t;
        t3 = 3.0f * t;
        ttt = t * tt;
        omt = 1.0f - t;
        tt3 = 3.0f * tt;
        for (i = 0; i < 3; i++) {
            result[i] = omt * (tt3 * (tanIn[i] + next[i]) + omt * (omt * cur[i] + t3 * (tanOut[i] + cur[i]))) + ttt * next[i];
        }
        break;
    case 3:
        OSPanic("animPipe.c", 301, "Hermite pInterpolation not yet supported for Euler angles(Hermite補間はオイラー角制御ではサポートされていません)");
        break;
    default:
        OSPanic("animPipe.c", 304, "Unknown pInterpolation pSetting!(未知の補間タイプが指定されています)");
        break;
    }

    CTRLSetRotation(animPipe->control, result[0], result[1], result[2]);
}
void DoQuatAnimation(struct ANIMPipe* animPipe, KeyFrame* currentFrame, KeyFrame* nextFrame) {
    f32 result[4];
    f32 cur[4];
    f32 next[4];
    f32 tanOut[4];
    f32 tanIn[4];
    f32 easeIn;
    f32 easeOut;
    u32 vecSize;
    u8 type;
    u32 offset;
    f32 t;
    u8 mode;

    type = animPipe->currentTrack->quantizeInfo >> 4;
    vecSize = GetTypeSize(type) * 3;

    offset = 0;
    if (animPipe->currentTrack->animType & 2) {
        offset = GetTypeSize(type) * 3;
        if (animPipe->currentTrack->animType & 0x20) {
            offset += GetTypeSize(type) * 4;
        }
    }
    GetData(lbl_803CBB50, (u8*)currentFrame->setting + offset, cur, lbl_803CBB48, 4);
    GetData(lbl_803CBB50, (u8*)nextFrame->setting + offset, next, lbl_803CBB48, 4);

    t = GetFraction(animPipe, currentFrame, nextFrame);

    offset = 0;
    if (animPipe->currentTrack->animType & 2) {
        mode = (animPipe->currentTrack->interpolationType & 0xC) >> 2;
        if (mode == 2) {
            offset = vecSize * 2;
        }
        if (mode == 3) {
            offset = vecSize * 2 + 4;
        }
    }

    switch ((animPipe->currentTrack->interpolationType & 0x70) >> 4) {
    case 0:
        result[0] = cur[0];
        result[1] = cur[1];
        result[2] = cur[2];
        result[3] = cur[3];
        break;
    case 5:
        GetData(lbl_803CBB51, nextFrame->interpolation + offset + 0x10, &easeIn, lbl_803CBB4C, 1);
        GetData(lbl_803CBB51, currentFrame->interpolation + offset + 0x12, &easeOut, lbl_803CBB4C, 1);
        t = EaseTime(t, easeOut, easeIn);
    case 4:
        GetData(lbl_803CBB50, currentFrame->interpolation + offset + 8, tanOut, lbl_803CBB48, 4);
        GetData(lbl_803CBB50, nextFrame->interpolation + offset, tanIn, lbl_803CBB48, 4);
        Squad(cur, t, tanOut, tanIn, next, result);
        break;
    case 6:
        SlerpQuat(cur, next, t, result);
        break;
    default:
        OSPanic("animPipe.c", 225, "Unknown pInterpolation pSetting!");
        break;
    }

    CTRLSetQuat(animPipe->control, result[0], result[1], result[2], result[3]);
}
void ANIMTick(struct ANIMPipe* animPipe, u8 unk) {
    KeyFrame* currentFrame;
    KeyFrame* nextFrame;
    KeyFrame* frame;
    f32 scale;

    if (animPipe == NULL || animPipe->currentTrack == NULL) {
        return;
    }

    ANIMGetKeyFrameFromTrack(animPipe->currentTrack, animPipe->time, &currentFrame, &nextFrame, &animPipe->unk14);

    if (animPipe->currentTrack->animType & 0x10) {
        frame = currentFrame;
        scale = 1.0f / (f32)(1 << (animPipe->currentTrack->quantizeInfo & 0xF));
        ((f32*)frame->setting)[0] *= scale;
        ((f32*)frame->setting)[1] *= scale;
        ((f32*)frame->setting)[2] *= scale;
        ((f32*)frame->setting)[3] *= scale;
        ((f32*)frame->setting)[4] *= scale;
        ((f32*)frame->setting)[5] *= scale;
        ((f32*)frame->setting)[6] *= scale;
        ((f32*)frame->setting)[7] *= scale;
        ((f32*)frame->setting)[8] *= scale;
        ((f32*)frame->setting)[9] *= scale;
        ((f32*)frame->setting)[10] *= scale;
        ((f32*)frame->setting)[11] *= scale;
        CTRLSetMatrix(animPipe->control, (MtxPtr)frame->setting);
        return;
    }

    if (animPipe->currentTrack->animType & 2) {
        DoScaleAnimation(animPipe, currentFrame, nextFrame, unk);
    }
    if (animPipe->currentTrack->animType & 8) {
        DoQuatAnimation(animPipe, currentFrame, nextFrame);
    } else if (animPipe->currentTrack->animType & 4) {
        DoEulerAnimation(animPipe, currentFrame, nextFrame);
    }
    if (animPipe->currentTrack->animType & 1) {
        DoTranslationAnimation(animPipe, currentFrame, nextFrame);
    }

    animPipe->unk04 = animPipe->time;

    if (animPipe->unk17 == 1) {
        animPipe->time += animPipe->unk08;
        if (animPipe->time > animPipe->currentTrack->animTime) {
            if (animPipe->unk18 != 0) {
                animPipe->time -= animPipe->currentTrack->animTime;
            } else {
                animPipe->time = animPipe->currentTrack->animTime;
            }
        }
    } else {
        animPipe->time -= animPipe->unk08;
        if (animPipe->time < 0.0f) {
            if (animPipe->unk18 != 0) {
                animPipe->time += animPipe->currentTrack->animTime;
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
