#include "Unknown/File_0x80052968.h"
#include "Unknown/File_0x80052f98.h"
#include "Unknown/File_0x80052694.h"
#include "Unknown/File_0x800b0724.h"
#include "static/UnknownHomes_Static.h"
#include "C3/control/frustum.h"
#include "Dolphin/mtx.h"
#include "Dolphin/stl.h"

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
