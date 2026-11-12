#ifndef __MENUS_MENU_CAMERA_H_
#define __MENUS_MENU_CAMERA_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"
#include "Dolphin/mtx.h"
#include "menus/menu_work.h"

/* Fields of the menus work area (lbl_2_bss_1A824C + 0x190000) owned by the menu camera.
 * Vec fields hold x, y, z at +0, +4, +8. */
#define MENU_CAM_EYE                0x7608 /* Vec: current (spring-smoothed) eye */
#define MENU_CAM_TARGET             0x7614 /* Vec: current (spring-smoothed) look-at target */
#define MENU_CAM_EYE_PREV           0x7620 /* Vec: eye spring, previous position */
#define MENU_CAM_EYE_SPRING         0x762C /* Vec: eye spring, current output */
#define MENU_CAM_TARGET_PREV        0x7638 /* Vec: target spring, previous position */
#define MENU_CAM_TARGET_SPRING      0x7644 /* Vec: target spring, current output */
#define MENU_CAM_CLAMPED_EYE        0x7650 /* Vec: eye after the scene-bounds clamp (snap only) */
#define MENU_CAM_IN_BOUNDS_TARGET   0x765C /* Vec: look-at x/z, updated only while inside the bounds */
#define MENU_CAM_EYE_SPRING_K       0x7668 /* f32: eye spring stiffness */
#define MENU_CAM_EYE_SPRING_DAMP    0x766C /* f32: eye spring damping */
#define MENU_CAM_EYE_SPRING_REST    0x7670 /* f32: eye spring rest length */
#define MENU_CAM_TARGET_SPRING_K    0x7674 /* f32: target spring stiffness */
#define MENU_CAM_TARGET_SPRING_DAMP 0x7678 /* f32: target spring damping */
#define MENU_CAM_TARGET_SPRING_REST 0x767C /* f32: target spring rest length */
#define MENU_CAM_FOLLOW_SLOT        0x774A /* s16: character slot the camera follows, -1 = none */
#define MENU_CAM_MODE               0x7845 /* u8: MENU_CAM_MODE_* */
#define MENU_CAM_UNBOUNDED          0x7848 /* u8: nonzero skips the scene-bounds clamps */
#define MENU_CAM_PRESET             0x7849 /* u8: index into menuCameraPresets */
#define MENU_CAM_SPRING_ENABLED     0x7855 /* u8: springs on (set by menuCamera_setSpringPreset) */
#define MENU_CAM_EYE_FOLLOWS_SLOT   0x7856 /* u8: 1 = eye is offset by the followed slot too */

#define MENU_CAM_MODE_PRESET          0
#define MENU_CAM_MODE_DEBUG_FREE_LOOK 1

void menuCamera_springTarget(void *arg0, Vec *arg1);
void menuCamera_springTarget2D(void *arg0, Vec *arg1);
void menuCamera_springEye(void *arg0, Vec *arg1);
void menuCamera_updateDebugFreeLook(Mtx arg0);
void menuCamera_updatePreset(Mtx arg0);
void menuCamera_update(Mtx arg0);
void menuCamera_snapToPreset(Mtx arg0);
void menuCamera_setEyeFollowsSlot(u8 arg0);
void menuCamera_setFollowSlot(s16 arg0);
void menuCamera_setSpringPreset(s32 arg0);
void menuCamera_resetSpring(s32 arg0);

#endif // !__MENUS_MENU_CAMERA_H_
