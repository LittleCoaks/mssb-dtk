#include "Unknown/File_0x80052f98.h"
#include "Unknown/File_0x80052694.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80052968.h"
#include "static/UnknownHomes_Static.h"
#include "C3/control/frustum.h"
#include "Dolphin/mtx.h"

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
