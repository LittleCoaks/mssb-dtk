#include "Unknown/File_0x800bcd60.h"
#include "Unknown/File_0x800bcb44.h"
#include "Unknown/File_0x800bf074.h"

void convertGeometryAndSknHeader(void* geo, void* skn) {
    void* pal = LoadGeoPalette(geo);

    if (skn != NULL) {
        SKNLoadFile(skn, pal);
    }
    *(void**)geo = pal;
}
