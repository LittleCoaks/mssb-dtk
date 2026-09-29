#include "Unknown/File_0x800b4048.h"
#include "Unknown/File_0x800b43a0.h"

BOOL maybeBallRelated(Actor** actor, ActorLayout* layout, u16 actorID) {
    layout->actorID = actorID;
    *actor = maybeProcessActLayout(layout);
    return TRUE;
}
