#ifndef __MENUS_TEXT_35EC0_H_
#define __MENUS_TEXT_35EC0_H_

#include "mssbTypes.h"

// Scene node used by the handle state machines: records are
// graphicsRelatedArray[firstHandle + rec->handle].object.
typedef struct TextScene {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ u16 firstHandle;
} TextScene;

// Per-record state machine block passed as the second argument.
typedef struct TextHandleRec {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ s16 state;
    /* 0x06 */ u8 unk6[4];
    /* 0x0A */ s16 unkA;       // index into a per-slot s16 table in the work area
    /* 0x0C */ u8 unkC[2];
    /* 0x0E */ s16 handle;     // added to scene->firstHandle
    /* 0x10 */ s16 unk10;      // index into lbl_2_data_C8F8 / C904
} TextHandleRec;

void fn_2_35EC0(TextScene *scene, TextHandleRec *rec);
void fn_2_36074(TextScene *scene, TextHandleRec *rec);
void fn_2_36204(TextScene *scene, TextHandleRec *rec);
void fn_2_363C8(TextScene *scene, TextHandleRec *rec);
void fn_2_36590(TextScene *scene, TextHandleRec *rec);
void fn_2_36750(TextScene *scene, TextHandleRec *rec);
void fn_2_3697C(TextScene *scene, TextHandleRec *rec);
void fn_2_36B30(TextScene *scene, TextHandleRec *rec);
void fn_2_36D04(TextScene *scene, TextHandleRec *rec);
void fn_2_36F44(TextScene *scene, TextHandleRec *rec);
void fn_2_370F8(TextScene *scene, TextHandleRec *rec);
void fn_2_372AC(TextScene *scene, TextHandleRec *rec);
void fn_2_3735C(TextScene *scene, TextHandleRec *rec);
void fn_2_37430(TextScene *scene, TextHandleRec *rec);
void fn_2_3745C(void);
void fn_2_37460(void);
void fn_2_37630(void);
void fn_2_379D0(void);
void fn_2_37D70(void);
void fn_2_37D74(void);
void fn_2_37D78(void);
void fn_2_37D7C(void);
void fn_2_37D80(void);
void fn_2_37D84(void);
void fn_2_37D88(void);
void fn_2_37D8C(void);
void fn_2_37D90(void);
void fn_2_37D94(void);
void fn_2_37D98(void);

#endif // !__MENUS_TEXT_35EC0_H_
