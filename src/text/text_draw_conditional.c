#include "text/text_channel.h"
#include "text/text_draw.h"
#include "text/text_draw_conditional.h"

void DrawTextOnCondition(s32 group) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if (screenTextArray.blocks[i].state == 2 && group == screenTextArray.blocks[i].drawGroup) {
            DrawText(i);
        }
    }
}
