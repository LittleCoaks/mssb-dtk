#ifndef __UNKNOWN_OBJINIT_H_
#define __UNKNOWN_OBJINIT_H_

#include "mssbTypes.h"
#include "C3/actor.h"
#include "Unknown/File_0x800bdd74.h"

void f_InitBone(void);

Actor* f_InitActorWithLayout(ActorLayout* layout, void* buffer);

void BuildBoneSkinOrientationMatrix(void);

void characterAndBallDisplayRelated(ActorObjectEntry* entry, u16 buffer, u16 slot, ActorLayout* layout, void* anim,
                                    int arg5);

#endif // !__UNKNOWN_OBJINIT_H_
