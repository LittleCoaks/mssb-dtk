#include "Unknown/File_0x80025c58.h"

static inline void bindTracks(ActorBindFile* file, ActorBindActor* actor) {
    u32* ptr;
    int i;
    int type;
    ActorBindTrack* track;
    u32* extraPtr;
    ActorBindNode* nodes;
    u32 subType;
    u32 val;
    u32 extraVal;
    ActorBindExtra* extra;
    ActorBindSkeleton* skel;

    if (file->tracks == NULL) {
        return;
    }

    file->actor = actor;
    extra = actor->data->extra;
    skel = actor->data->skeleton;
    if (extra == NULL) {
        extraVal = 0;
        nodes = NULL;
    } else {
        if ((extraPtr = extra->ptrA) != NULL) {
            extraPtr = &extraPtr[0x30 / 4];
            extraVal = *extraPtr;
        } else if ((extraPtr = extra->ptrB) != NULL) {
            extraPtr = &extraPtr[0x60 / 4];
            extraVal = *extraPtr;
        } else {
            extraPtr = NULL;
            extraVal = 0;
        }
        nodes = extra->nodes;
    }

    track = file->tracks;
    for (i = 0; i < file->numTracks; i++) {
        subType = track->subType;
        type = track->type;
        switch (type) {
        case 0:
            ptr = &nodes[track->index].value;
            val = *ptr;
            break;
        case 1:
            if (subType == 6) {
                ptr = extraPtr;
                val = extraVal;
            } else {
                ptr = skel->entries[track->index].targets->a;
                val = *ptr;
            }
            break;
        case 2:
            ptr = skel->entries[track->index].targets->d;
            val = *ptr;
            break;
        case 3:
            ptr = skel->entries[track->index].targets->b;
            val = *ptr;
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            ptr = &skel->entries[track->index].targets->c[type - 4].value;
            val = *ptr;
            break;
        }
        track->ptr = ptr;
        track->value = val;
        track++;
    }
}

void ACTActorRelated(void* file, void* actor) {
    bindTracks(file, actor);
}
