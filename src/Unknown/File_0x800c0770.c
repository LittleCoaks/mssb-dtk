#include "Unknown/File_0x800c0770.h"
#include "Unknown/File_0x80034e20.h"

void convertTextureHeader(void* tex) {
    TextureRecord* entry;
    int i;

    entry = tex;
    i = 0;
    while (i < ((TextureHeader*)tex)->count) {
        if (entry->pixels != NULL) {
            entry->pixels = (void*)((u32)tex + (u32)entry->pixels);
        }
        if (entry->tlut != NULL) {
            entry->tlut = (void*)((u32)tex + (u32)entry->tlut);
        }
        entry++;
        entry->index = i;
        i++;
    }
}
