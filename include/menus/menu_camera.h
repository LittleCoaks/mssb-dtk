#ifndef __MENUS_MENU_CAMERA_H_
#define __MENUS_MENU_CAMERA_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"
#include "Dolphin/mtx.h"

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
