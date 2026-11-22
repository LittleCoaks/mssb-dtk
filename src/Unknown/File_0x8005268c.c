#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052694.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
#include "Unknown/File_0x80052734.h"
#include "Dolphin/mtx.h"
#include "Dolphin/mtxext.h"
#include "stl/math.h"
#include "Unknown/File_0x80052968.h"
#include "Unknown/File_0x80052f98.h"
#include "Unknown/File_0x800b0724.h"
#include "C3/control/frustum.h"
#include "Dolphin/stl.h"
#include "Unknown/File_0x800b0a14.h"

u32 returnsCurrentMode(void) {
    return currentMode;
}

void setScissorAndProjection(int mode) {
    if (mode < 0) {
        mode = 0;
    } else if (mode >= 2) {
        mode = 1;
    }
    currentMode = mode;
    GXSetProjection((&cameras[2])[mode].proj, GX_PERSPECTIVE);
    if (scissorMode == 1) {
        GXSetScissor(0, 0, 640, 448);
    } else if (scissorMode == 2) {
        GXSetScissor(mode * 320, 0, 320, 448);
    }
}

camera_803c639c_s* returnFloatFromModeIndex(int mode) {
    if (mode < 0) {
        mode = 0;
    } else if (mode >= 2) {
        mode = 1;
    }
    return &cameras[mode] + 2;
}

camera_803c639c_s* fn_80052768_getCamera(int mode) {
    if (mode < 0) {
        mode = 0;
    } else if (mode >= 2) {
        mode = 1;
    }
    return &cameras[mode];
}

void setScissorMode(int mode) {
    if (mode < 1) {
        mode = 1;
    } else if (mode > 2) {
        mode = 2;
    }
    scissorMode = mode;
}

int returnScissorMode(void) {
    return scissorMode;
}

/* Defined with an int-width result, while every caller (via
 * Unknown/File_0x800527c4.h) sees a u8 return and truncates it; the header is
 * deliberately not included here so both views can coexist. */
BOOL isWorldPosOnScreen(Vec* pos) {
    Vec v;

    v.x = pos->x;
    v.y = -fabs(pos->y);
    v.z = pos->z;
    PSMTXMultVec(cameras[0].view, &v, &v);
    PSMTX44MultVec(cameras[0].proj, &v, &v);
    return !(v.x > 1.0f | v.x < -1.0f | v.y > 1.0f | v.y < -1.0f | v.z > 0.0f | v.z < -1.0f);
}

void graphics_relatedToVsScreen(void) {
    camera_803c639c_s* cam;
    Mtx* view;
    f32 scale;

    if (scissorMode == 1) {
        cam = &cameras[0];
        if (lbl_803CBD10 != 0) {
            ((fn_800528AC_parameter)lbl_803CBD10)(cam);
        }
        view = &cam->view;
        makeLookAtMatrix(*view, &cam->eye, &cam->Up, &cam->target);

        scale = lbl_803CC87C / cam->zoom;
        C_MTXFrustum(cam->proj, lbl_803CC888 * scale, lbl_803CC88C * scale, lbl_803CC874 * scale,
                     lbl_803CC890 * scale, lbl_803CC87C, lbl_803CC894);
        fn_800B806C(0, lbl_803CC898 * scale, lbl_803CC89C * scale, lbl_803CC8A0 * scale,
                    lbl_803CC880 * scale, lbl_803CC8A4, lbl_803CC878, lbl_803CC8A8);
        fn_80011640(*view, *view);

        scale = lbl_803CC87C / cam->zoom;
        C_MTXFrustum(cam->proj, lbl_803CC888 * scale, lbl_803CC88C * scale, lbl_803CC874 * scale,
                     lbl_803CC890 * scale, lbl_803CC87C, lbl_803CC894);
        fn_800B806C(0, lbl_803CC898 * scale, lbl_803CC89C * scale, lbl_803CC8A0 * scale,
                    lbl_803CC880 * scale, lbl_803CC8A4, lbl_803CC878, lbl_803CC8A8);
    } else if (scissorMode == 2) {
        cam = &cameras[1];
        if (lbl_803CBD10 != 0) {
            ((fn_800528AC_parameter)lbl_803CBD10)(cam);
        }
        view = &cam->view;
        makeLookAtMatrix(*view, &cam->eye, &cam->Up, &cam->target);

        scale = lbl_803CC87C / cam->zoom;
        C_MTXFrustum(cam->proj, lbl_803CC888 * scale, lbl_803CC88C * scale, lbl_803CC874 * scale,
                     lbl_803CC890 * scale, lbl_803CC87C, lbl_803CC894);
        fn_800B806C(0, lbl_803CC898 * scale, lbl_803CC89C * scale, lbl_803CC8A0 * scale,
                    lbl_803CC880 * scale, lbl_803CC8A4, lbl_803CC878, lbl_803CC8A8);
        fn_80011640(*view, *view);

        scale = lbl_803CC87C / cam->zoom;
        C_MTXFrustum(cam->proj, lbl_803CC888 * scale, lbl_803CC88C * scale, lbl_803CC8AC * scale,
                     lbl_803CC8B0 * scale, lbl_803CC87C, lbl_803CC894);
        fn_800B806C(1, lbl_803CC898 * scale, lbl_803CC89C * scale, lbl_803CC8B4 * scale,
                    lbl_803CC8B8 * scale, lbl_803CC8A4, lbl_803CC878, lbl_803CC8A8);

        cam = &cameras[0];
        if (lbl_803CBD10 != 0) {
            ((fn_800528AC_parameter)lbl_803CBD10)(cam);
        }
        view = &cam->view;
        makeLookAtMatrix(*view, &cam->eye, &cam->Up, &cam->target);

        scale = lbl_803CC87C / cam->zoom;
        C_MTXFrustum(cam->proj, lbl_803CC888 * scale, lbl_803CC88C * scale, lbl_803CC874 * scale,
                     lbl_803CC890 * scale, lbl_803CC87C, lbl_803CC894);
        fn_800B806C(0, lbl_803CC898 * scale, lbl_803CC89C * scale, lbl_803CC8A0 * scale,
                    lbl_803CC880 * scale, lbl_803CC8A4, lbl_803CC878, lbl_803CC8A8);
        fn_80011640(*view, *view);

        scale = lbl_803CC87C / cam->zoom;
        C_MTXFrustum(cam->proj, lbl_803CC888 * scale, lbl_803CC88C * scale, lbl_803CC8BC * scale,
                     lbl_803CC8C0 * scale, lbl_803CC87C, lbl_803CC894);
        fn_800B806C(0, lbl_803CC898 * scale, lbl_803CC89C * scale, lbl_803CC8B4 * scale,
                    lbl_803CC8B8 * scale, lbl_803CC8A4, lbl_803CC878, lbl_803CC8A8);
    }

    memcpy(&cameras[2], cameras, 0x150);
    fn_800369DC(cameras[0].zoom);
}

void possiblyTransitionBlackScreen(void) {
    camera_803c639c_s* cam;
    s32 i;
    f32 scale;
    f32 c870 = lbl_803CC870;
    f32 c878 = lbl_803CC878;
    f32 c87C = lbl_803CC87C;
    f32 c880 = lbl_803CC880;
    f32 c888 = lbl_803CC888;
    f32 c88C = lbl_803CC88C;
    f32 c890 = lbl_803CC890;
    f32 c898 = lbl_803CC898;
    f32 c89C = lbl_803CC89C;
    f32 c8A0 = lbl_803CC8A0;
    f32 c874 = lbl_803CC874;
    f32 c8C4 = lbl_803CC8C4;
    f32 c8C8 = lbl_803CC8C8;

    scissorMode = 1;
    cam = cameras;
    for (i = 0; i < 2; i++, cam++) {
        cam->eye.x = c870;
        cam->eye.y = c878;
        cam->eye.z = c8C4;
        cam->target.x = c870;
        cam->target.y = c878;
        cam->target.z = c8C8;
        cam->Up.x = c870;
        cam->Up.y = c87C;
        cam->Up.z = c870;
        cam->zoom = c87C;
        scale = c87C / cam->zoom;
        C_MTXFrustum(cam->proj, c888 * scale, c88C * scale, c874 * scale, c890 * scale, c87C,
                     lbl_803CC894);
        fn_800B806C(0, c898 * scale, c89C * scale, c8A0 * scale, c880 * scale, lbl_803CC8A4,
                    lbl_803CC878, lbl_803CC8A8);
    }

    lbl_803C60BC._00 = c870;
    lbl_803C60BC._04 = c878;
    lbl_803C60BC._08 = c870;
    lbl_803C60BC._0C = c870;
    lbl_803C60BC._10 = c878;
    lbl_803C60BC._14 = c87C;
    lbl_803C60BC._24 = lbl_803CC8CC;
    lbl_803C60BC._28 = c870;
    lbl_803C60BC._2C = c870;
    lbl_803C60BC._3C = 1;
    lbl_803C60BC._3D = 0;
    lbl_803CBD10 = 0;
    currentDrawingItem->func = graphics_relatedToVsScreen;
}
