#include "Unknown/File_0x80033f64.h"
#include "Dolphin/mtx.h"

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
