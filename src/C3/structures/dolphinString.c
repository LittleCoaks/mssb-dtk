#include "mssbTypes.h"
#include "charPipeline/structures/dolphinString.h"

s8 Strcmp(char* str1, char* str2) {
    do {
        if (*str1 < *str2) {
            return 1;
        }
        if (*str1 > *str2) {
            return -1;
        }
        str1++;
        str2++;
    } while (*str1 && *str2);
    return 0;
}
