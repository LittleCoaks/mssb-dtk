#include "Unknown/particle_effects.h"
#include "Dolphin/mtx.h"

void maybeTexOrSpriteRelated(void) {
    return;
}

void fn_80033794(void* particles) {
    return;
}

void* fn_800337CC(void* buf, int count, int arg2) {
    return NULL;
}

void pitchingMachinePitching(u8 arg0) {
    return;
}

BOOL fn_80033928(u8 id) {
    return FALSE;
}

void fn_80033964(void* effect) {
    return;
}

void* fn_800339F0(int arg0, u8 arg1) {
    return NULL;
}

void* allocParticleEffect(void* func, int arg1, int arg2, int arg3, int arg4, u8 arg5) {
    return NULL;
}

extern struct {
    /*0x00*/ Mtx mtx;
    /*0x30*/ u8 _30[0x38];
} graphicRelatedStructMaybe;

extern Vec lbl_80180010[4];

void setParticleXform(f32 scaleX, f32 scaleY, f32 rot) {
    Mtx xform;
    Mtx rotMtx;
    int i;

    lbl_80180010[0].x = 0.5f * -scaleX;
    lbl_80180010[0].y = 0.5f * -scaleY;
    lbl_80180010[0].z = 0.0f;
    lbl_80180010[1].x = 0.5f * scaleX;
    lbl_80180010[1].y = 0.5f * -scaleY;
    lbl_80180010[1].z = 0.0f;
    lbl_80180010[2].x = 0.5f * scaleX;
    lbl_80180010[2].y = 0.5f * scaleY;
    lbl_80180010[2].z = 0.0f;
    lbl_80180010[3].x = 0.5f * -scaleX;
    lbl_80180010[3].y = 0.5f * scaleY;
    lbl_80180010[3].z = 0.0f;
    PSMTXRotRad(rotMtx, 'z', MTXDegToRad(rot));
    PSMTXConcat(graphicRelatedStructMaybe.mtx, rotMtx, xform);
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(xform, &lbl_80180010[i], &lbl_80180010[i]);
    }
}

void minigamesSetSomePointers(void) {
    return;
}

void minigamesGXStuff(void) {
    return;
}

void minigamesSetSomePointers2(void) {
    return;
}
