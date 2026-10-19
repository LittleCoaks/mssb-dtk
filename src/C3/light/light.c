#include "C3/light/light.h"
#include "C3/charPipeline.h"
#include "Unknown/File_0x800acf14.h"

static GXColor lightingDataArray __attribute__((aligned(4)));
static u8 maybeDoLighting;

u8 lightingRelated(GXColor* color) {
    if (maybeDoLighting) {
        *color = lightingDataArray;
    }
    return maybeDoLighting;
}

void adjustLightingParams(u8 enable, GXColor color) {
    maybeDoLighting = enable;
    lightingDataArray = color;
}

void fn_800BD2DC(void) {
    maybeDoLighting = 0;
    lightingDataArray.r = 0;
    lightingDataArray.b = 0;
    lightingDataArray.g = 0;
    lightingDataArray.a = 0xFF;
}

void LITXForm(void* arg0, void* arg1) {
    Light* light = arg0;
    MtxPtr camera = arg1;
    Mtx m;

    CTRLBuildMatrix(&light->control, m);
    if (light->parent) {
        PSMTXConcat(light->parent, m, m);
    }
    PSMTXConcat(camera, m, m);
    PSMTXMultVec(m, &light->position, &light->worldPosition);
    PSMTXInverse(m, m);
    PSMTXTranspose(m, m);
    PSMTXMultVec(m, &light->direction, &light->worldDirection);
}

void LITInitColor(void* light, GXColor* color) {
    ((Light*)light)->color = *color;
}

void LITInitDir(void* light, f32 x, f32 y, f32 z) {
    ((Light*)light)->direction.x = x;
    ((Light*)light)->direction.y = y;
    ((Light*)light)->direction.z = z;
}

void LITInitPos(void* light, f32 x, f32 y, f32 z) {
    ((Light*)light)->position.x = x;
    ((Light*)light)->position.y = y;
    ((Light*)light)->position.z = z;
}

void LITInitAttn(void* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2) {
    GXInitLightAttn(&((Light*)light)->lt_obj, a0, a1, a2, k0, k1, k2);
}

void LITAlloc(void** light) {
    *light = _OSAllocFromHeap(0x20, sizeof(Light));
    ((Light*)*light)->position.x = ((Light*)*light)->position.y = ((Light*)*light)->position.z = 0.0f;
    ((Light*)*light)->direction.x = ((Light*)*light)->direction.y = 0.0f;
    ((Light*)*light)->direction.z = 1.0f;
    ((Light*)*light)->parent = NULL;
    ((Light*)*light)->animPipe = NULL;
    ((Light*)*light)->control.type = 0;
}
