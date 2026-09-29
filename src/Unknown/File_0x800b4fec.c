#include "Unknown/File_0x800b4fec.h"
#include "charPipeline/structures/dolphinString.h"

ANIMSequences* ANIMGetSequence(ANIMBank* animBank, char* sequenceName, u16 seqNum) {
    u32 i;

    if (sequenceName != NULL) {
        for (i = 0; i < animBank->numSequences; i++) {
            if (Strcmp(animBank->animSequences[i].sequenceName, sequenceName) == 0) {
                return &animBank->animSequences[i];
            }
        }
    } else if (animBank == NULL) {
        return NULL;
    }
    return &animBank->animSequences[seqNum];
}
