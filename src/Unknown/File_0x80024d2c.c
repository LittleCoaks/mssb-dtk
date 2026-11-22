#include "Unknown/File_0x80024d2c.h"

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

extern f32 lbl_803CC5B0;
extern f32 lbl_803CC5D0;
extern u32 lbl_803CB7F0;
extern u32 lbl_803CB7F4;

static void initActRelatedCtl(ActRelatedCtl* ctl) {
    f32 defaultA;
    f32 defaultB;

    if (ctl != NULL) {
        defaultA = lbl_803CC5B0;
        defaultB = lbl_803CC5D0;
        ctl->f00 = defaultA;
        ctl->f04 = defaultB;
        ctl->s08 = 1;
        ctl->s0A = 0;
        ctl->s0C = 0;
        ctl->s0E = -1;
        ctl->b10 = 1;
        ctl->w14 = 0;
    }
}

void adjustInternalPointers(void* file) {
    RelocFile* f = file;
    RelocSeq* seq;
    RelocSub* sub;
    s32 i;
    s32 j;
    s32 k;

    f->_10 = 0;
    if (f->entries != NULL) {
        f->entries = (RelocEntry*)((u32)file + (u32)f->entries);
    }
    if (f->seqs != NULL) {
        f->seqs = (RelocSeq*)((u32)file + (u32)f->seqs);
    }
    if (f->seqs != NULL) {
        for (i = 0; i < f->seqCount; i++) {
            seq = &f->seqs[i];
            seq->subs = (RelocSub*)((u32)file + (u32)seq->subs);
            sub = seq->subs;
            for (j = 0; j < seq->subCount; j++) {
                sub->ptr08 = (void*)((u32)file + (u32)sub->ptr08);
                for (k = 0; k < seq->linkCount; k++) {
                    sub->links[k] = (u32)file + sub->links[k];
                }
                sub = (RelocSub*)((u8*)sub + seq->subStride);
            }
        }
    }
    if (f->entries != NULL) {
        for (i = 0; i < f->entryCount; i++) {
            f->entries[i].value0C = (u32)file + f->entries[i].value0C;
        }
    }
}

void actorRelated(void* effect, int arg1, int arg2) {
    ActRelatedEffect* act = effect;
    ActRelatedCtl* ctl;
    u8* seqTable;
    s8 v;
    s8 cur;
    s32 x;
    s32 t;

    cur = act->cur;
    seqTable = act->seqTables[arg1];
    v = (s8)seqTable[arg2];
    if (cur != -0x80 && v == cur) {
        return;
    }

    ctl = (ActRelatedCtl*)((u8*)effect + 0xC);
    x = ~v;
    t = (x >> 1) - (x & v);
    ctl->flagHi = (t & 0x8000) != 0;
    if (ctl->flagHi) {
        ActRelatedDesc* desc = (ActRelatedDesc*)act->arr1[v];
        ctl->s0A = 0;
        ctl->w18.h.hi = desc->h00;
        ctl->w18.h.lo = desc->h02;
        ctl->w1C = (u32)desc + 4;
    } else {
        ctl->w18.w = lbl_803CB7F0;
        ctl->w1C = lbl_803CB7F4;
    }

    initActRelatedCtl(ctl);
    if (ctl != NULL) {
        ctl->flagMid = 3;
    }
    if (ctl != NULL) {
        ctl->flagLow = 3;
    }
    act->cur = (s8)seqTable[arg2];
}

void actRelated(void* file, void* effect) {
    ActRelatedEffect* act = effect;
    ActRelatedHeader* hdr;
    ActRelatedCtl* ctl;
    s32 i;
    s32 k;

    if (file == NULL) {
        return;
    }
    if (effect == NULL) {
        return;
    }
    if (act->header == NULL) {
        return;
    }

    act->file = file;
    hdr = act->header;
    hdr->ptr04 = (u32)hdr + hdr->ptr04;
    hdr->ptr08 = (u32)hdr + hdr->ptr08;
    act->arr1 = (u32*)hdr->ptr04;
    for (i = 0; i < hdr->count0; i++) {
        act->arr1[i] = (u32)hdr + act->arr1[i];
    }
    act->arr2 = (u32*)hdr->ptr08;
    for (k = 0; k < hdr->count2; k++) {
        act->arr2[k] = (u32)hdr + act->arr2[k];
        act->seqTables[k] = (u8*)act->arr2[k];
    }

    ctl = &act->ctl;
    initActRelatedCtl(ctl);
    ctl->w18.w = lbl_803CB7F0;
    ctl->w1C = lbl_803CB7F4;
    act->cur = -0x80;
    act->flag59 = 1;
}

void fn_80026130(void) {
    return;
}
