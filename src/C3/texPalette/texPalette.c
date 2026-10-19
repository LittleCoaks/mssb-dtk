#include "mssbTypes.h"
#include "Dolphin/gx.h"
#include "charPipeline/texPalette.h"

TEXDescriptorPtr TEXGet(TEXPalettePtr pal, u32 id) {
    return &pal->descriptorArray[id];
}
