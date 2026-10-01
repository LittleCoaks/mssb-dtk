#ifndef __UNKNOWN_FILE_0X800B4908_H_
#define __UNKNOWN_FILE_0X800B4908_H_

#include "mssbTypes.h"

void haveActLayoutPointToGeoHeader(void* layout, void* geo);
void LoadActorLayout(void* layout);
void AdjustActorPointers(void* layout);
f32 fn_800B4A44(void* actor, u16 bone);
f32 scanBoneAttachmentData(void *ptr);
void updateBoneParam(void* actor, int flag);
void fn_800B4CDC(void* actor);

#endif // !__UNKNOWN_FILE_0X800B4908_H_
