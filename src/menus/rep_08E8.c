#include "menus/rep_08E8.h"
#include "header_rep_data.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTransform.h"

extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_2_bss_1A81D4[];
extern u8 hugeAnimStruct[0x3154];
extern u8 drawStadiumRelated;
extern u8 lbl_2_data_12EC0[];
extern u8 lbl_2_data_13228[];
extern u16 lbl_2_data_13238[];

extern u32 lbl_803CBD0C;
extern u32 *lbl_2_data_13374;
extern u8 g_d_GameSettings[];
extern s32 lbl_2_data_38B8;
void fn_2_4B2D0(void);

static inline void addStatCounter(s32 delta) {
    *(s16 *)(lbl_2_bss_1A8248 + 0x43BE) = *(s16 *)(lbl_2_bss_1A8248 + 0x43BC);
    *(s16 *)(lbl_2_bss_1A8248 + 0x43BC) += delta;
    if (*(s16 *)(lbl_2_bss_1A8248 + 0x43BC) > 999) {
        *(s16 *)(lbl_2_bss_1A8248 + 0x43BC) = 999;
    }
    if (*(s16 *)(lbl_2_bss_1A8248 + 0x43BC) < 0) {
        *(s16 *)(lbl_2_bss_1A8248 + 0x43BC) = 0;
    }
}

void fn_800ACFB0(void *obj);
void fn_2_68690(s32 flag);
void fn_2_68DAC(void *self, Vec *out);
void fn_80031CA4(Vec *v, u32 *dst);
void fn_2_513E0(void *a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h);
void *fn_80052768_getCamera(s32 mode);
void fn_800BD670(void *model, void *arg);
void fn_800A7D4C(s32 phase, void *node);
void LITXForm(void *arg0, void *arg1);
void *_OSAllocFromHeap(s32 alignment, s32 size);
void *memcpy(void *dest, const void *src, u32 n);
void PSMTXCopy(const Mtx src, Mtx dest);
void graphics_relatedToVsScreen(void);
void fn_2_6A87C(void);
void fn_2_93BF8(void *arg);
void fn_2_9007C(void);
f64 atan2(f64 y, f64 x);

// .text:0x0004AEE4 size:0x2C8 mapped:0x80689F78
void fn_2_4AEE4(void) {
    return;
}

// .text:0x0004ACF8 size:0x1EC mapped:0x80689D8C
void fn_2_4ACF8(void) {
    fn_2_4B2D0();
    if ((s8)(lbl_2_bss_1A824C + 0x190000)[0x7843] == 0) {
        addStatCounter(*(s16 *)(g_d_GameSettings + 0x30));
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7792) = *(s16 *)(g_d_GameSettings + 0x30);
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7798) = *(s16 *)(g_d_GameSettings + 0x30);
    } else if ((s8)(lbl_2_bss_1A824C + 0x190000)[0x7843] == 1) {
        addStatCounter(lbl_2_data_38B8);
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7794) = (s16)lbl_2_data_38B8;
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7798) = (s16)lbl_2_data_38B8;
    } else if ((s8)(lbl_2_bss_1A824C + 0x190000)[0x7843] == 2) {
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7796) = 0;
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7798) = 0;
        if ((s8)lbl_2_bss_1A8248[0x44FD] > 0) {
            lbl_2_bss_1A8248[0x44FD]--;
        }
        if ((s8)(lbl_2_bss_1A824C + 0x190000)[0x7843] == 0) {
            if (lbl_2_bss_1A8248[0x4429] == 0) {
                lbl_2_bss_1A8248[0x4429] = 1;
            }
        }
    }
}

// .text:0x0004AB1C size:0x1DC mapped:0x80689BB0
void fn_2_4AB1C(void) {
    return;
}

// .text:0x0004A6E8 size:0x434 mapped:0x8068977C
void fn_2_4A6E8(void) {
    return;
}

// .text:0x0004A340 size:0x3A8 mapped:0x806893D4
void fn_2_4A340(void) {
    return;
}

// .text:0x0004A310 size:0x30 mapped:0x806893A4
s16 fn_2_4A310(s16 a, s16 b) {
    s32 d = a - b;
    s32 sign = d >> 31;
    s16 diff = (d ^ sign) - sign;
    if (diff > 0x800) {
        diff = 0x1000 - diff;
    }
    return diff;
}

// .text:0x0004A2C4 size:0x4C mapped:0x80689358
s32 fn_2_4A2C4(f32 angle) {
    f32 v = 0.0f;
    if (angle < 0.0f) {
        v = 2048.0f * (6.2831855f + angle) / 3.1415927f;
    }
    return (s32)v;
}

// .text:0x0004A234 size:0x90 mapped:0x806892C8
s16 fn_2_4A234(f32 x, f32 y) {
    s32 angle;
    if (x == 0.0f) {
        if (y >= 0.0f) {
            return 0x400;
        }
        return 0xC00;
    }
    angle = (s32)(2048.0f * (f32)atan2(y, x) / 3.1415927f);
    if (angle < 0) {
        angle += 0x1000;
    }
    return angle;
}

// .text:0x0004A1E8 size:0x4C mapped:0x8068927C
f32 fn_2_4A1E8(f32 x, f32 y) {
    if (x != 0.0f || y != 0.0f) {
        return (f32)atan2(y, x);
    }
    return 0.0f;
}

// .text:0x0004A18C size:0x5C mapped:0x80689220
f32 fn_2_4A18C(f32 angle) {
    if (angle >= 3.1415927f) {
        do {
            angle -= 6.2831855f;
        } while (angle >= 3.1415927f);
    }
    if (angle < -3.1415927f) {
        do {
            angle += 6.2831855f;
        } while (angle < -3.1415927f);
    }
    return angle;
}

// .text:0x0004A150 size:0x3C mapped:0x806891E4
s16 fn_2_4A150(s16 angle) {
    if (angle < 0) {
        do {
            angle += 0x1000;
        } while (angle < 0);
    }
    while (angle >= 0x1000) {
        angle -= 0x1000;
    }
    return angle;
}

// .text:0x0004A0C4 size:0x8C mapped:0x80689158
#pragma dont_inline on
s32 fn_2_4A0C4(u16 *a, u16 *b) {
    u16 ca = *a;
    u16 cb;
    s32 diff;
    if ((ca & 0xC000) == 0xC000) {
        return -1;
    }
    cb = *b;
    if ((cb & 0xC000) == 0xC000) {
        return 1;
    }
    if (ca == 0x4000 && cb == 0x4000) {
        return 0;
    }
    if (ca == 0x4000) {
        return -1;
    }
    if (cb == 0x4000) {
        return 1;
    }
    diff = ca - cb;
    if (diff == 0) {
        return fn_2_4A0C4(a + 1, b + 1);
    }
    return diff;
}
#pragma dont_inline reset

// .text:0x0004A094 size:0x30 mapped:0x80689128
u16 *fn_2_4A094(u16 *dst, u16 *src) {
    u16 *start = dst;
    while (*src != 0x4000) {
        *dst++ = *src++;
    }
    *dst = *src;
    return start;
}

// .text:0x0004A068 size:0x2C mapped:0x806890FC
s32 fn_2_4A068(u16 *str) {
    u16 *p = str;
    while (*p != 0x4000) {
        p++;
    }
    return p - str;
}

// .text:0x0004A064 size:0x4 mapped:0x806890F8
void fn_2_4A064(void) {
    return;
}

// .text:0x00049F7C size:0xE8 mapped:0x80689010
u16 *fn_2_49F7C(u16 *str, s32 capacity, u16 ch, s32 pos) {
    u16 *p = str;
    s32 len;
    s32 i;
    while (*p != 0x4000) {
        p++;
    }
    len = p - str;
    if (len < pos) {
        return NULL;
    }
    if (ch == 0x4000) {
        return NULL;
    }
    if (len + 2 > capacity) {
        return NULL;
    }
    for (i = len; i >= pos; i--) {
        str[i + 1] = str[i];
    }
    str[pos] = ch;
    return str;
}

// .text:0x00049EFC size:0x80 mapped:0x80688F90
s32 fn_2_49EFC(u16 *str, u16 idx) {
    s32 total = 0;
    u16 c;
    while ((c = *str) != 0x4000) {
        if (c == 0x4003) {
            total += lbl_2_data_13238[idx];
        } else if (c == 0x4002) {
            total += lbl_2_data_13238[idx] >> 1;
        } else if (!(c & 0x4000)) {
            if (c & 0x8000) {
                total += lbl_2_data_13238[idx];
            } else {
                total += lbl_2_data_13238[idx] >> 1;
            }
        }
        str++;
    }
    return total;
}

// .text:0x00049E5C size:0xA0 mapped:0x80688EF0
void fn_2_49E5C(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7, s32 p8, s32 p9) {
    void *tmp = _OSAllocFromHeap(0x10, 0x40);
    fn_2_4917C(tmp, p3, p4, p5, p6);
    fn_2_513E0(tmp, p1, p2, 0, p6, p7, p8, p9);
    if (tmp != NULL) {
        fn_800ACFB0(tmp);
    }
}

// .text:0x00049DB8 size:0xA4 mapped:0x80688E4C
void fn_2_49DB8(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7, s32 p8, s32 p9, s32 p10) {
    void *tmp = _OSAllocFromHeap(0x10, 0x40);
    fn_2_4917C(tmp, p3, p4, p6, p7);
    fn_2_513E0(tmp, p1, p2, p5, p7, p8, p9, p10);
    if (tmp != NULL) {
        fn_800ACFB0(tmp);
    }
}

// .text:0x0004917C size:0xC3C mapped:0x80688210
void fn_2_4917C(void *a, s32 b, s32 c, s32 d, s32 e) {
    return;
}

// .text:0x0004906C size:0x110 mapped:0x80688100
void fn_2_4906C(void) {
    return;
}

// .text:0x00048DB4 size:0x2B8 mapped:0x80687E48
void fn_2_48DB4(void) {
    return;
}

// .text:0x00048D54 size:0x60 mapped:0x80687DE8
void fn_2_48D54(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        LITXForm(*(void **)(hugeAnimStruct + 0xAC + i * 4), (u8 *)fn_80052768_getCamera(0) + 0x40);
    }
}

// .text:0x00048D08 size:0x4C mapped:0x80687D9C
void fn_2_48D08(void) {
    u32 idx = *(u32 *)(lbl_2_bss_1A824C + 0x19769C);
    f32 *p = (f32 *)(hugeAnimStruct + idx * 0x27C + 0xC04);
    p[13] = 0.0f;
    p[14] = 0.0f;
    p[15] = 0.0f;
    p[16] = 0.0f;
    p[17] = 0.0f;
    p[18] = 0.0f;
}

// .text:0x00048BE0 size:0x128 mapped:0x80687C74
void fn_2_48BE0(void) {
    return;
}

// .text:0x00048A1C size:0x1C4 mapped:0x80687AB0
void fn_2_48A1C(void) {
    return;
}

// .text:0x000489DC size:0x40 mapped:0x80687A70
void fn_2_489DC(void) {
    fn_800A7D4C(12, lbl_2_data_13228 + drawStadiumRelated * 8);
}

// .text:0x000487A0 size:0x23C mapped:0x80687834
void fn_2_487A0(void) {
    return;
}

// .text:0x000481F4 size:0x5AC mapped:0x80687288
void fn_2_481F4(void) {
    return;
}

// .text:0x000481B8 size:0x3C mapped:0x8068724C
void fn_2_481B8(void) {
    fn_800BD670(*(void **)(hugeAnimStruct + 0x60), (u8 *)fn_80052768_getCamera(0) + 0x40);
}

// .text:0x00047FF8 size:0x1C0 mapped:0x8068708C
void fn_2_47FF8(void) {
    Mtx44 proj;
    s32 i;
    u8 *base = lbl_2_bss_1A824C + 0x190000;
    C_MTXFrustum(proj, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    for (i = 0; i < 4; i++) {
        LITXForm(*(void **)(hugeAnimStruct + 0xAC + i * 4), (u8 *)fn_80052768_getCamera(0) + 0x40);
    }
    if (base[0x784A] != 0) {
        if (base[0x7846] == 1) {
            fn_2_6A87C();
            if (base[0x7847] != 0) {
                fn_2_93BF8(lbl_2_bss_1A81D4);
            }
        } else if (base[0x7846] == 2) {
            fn_2_9007C();
        } else {
            fn_2_93BF8(lbl_2_bss_1A81D4);
        }
    } else {
        fn_2_93BF8(lbl_2_bss_1A81D4);
    }
    memcpy((u8 *)fn_80052768_getCamera(0) + 0x70, lbl_2_bss_1A81D4 + 0x4C, 12);
    memcpy((u8 *)fn_80052768_getCamera(0) + 0x7C, lbl_2_bss_1A81D4 + 0x40, 12);
    *(f32 *)((u8 *)fn_80052768_getCamera(0) + 0xA4) = *(f32 *)(lbl_2_bss_1A81D4 + 0x3C);
    PSMTXCopy((f32 (*)[4])((u8 *)fn_80052768_getCamera(0) + 0x40), (f32 (*)[4])lbl_2_bss_1A81D4);
    graphics_relatedToVsScreen();
}

// .text:0x00047CFC size:0x2FC mapped:0x80686D90
void fn_2_47CFC(void) {
    return;
}

// .text:0x00047B24 size:0x1D8 mapped:0x80686BB8
void fn_2_47B24(void) {
    return;
}

// .text:0x00047AFC size:0x28 mapped:0x80686B90
void fn_2_47AFC(void) {
    return;
}

// .text:0x000478F4 size:0x208 mapped:0x80686988
void fn_2_478F4(void) {
    return;
}

// .text:0x000477C0 size:0x134 mapped:0x80686854
void fn_2_477C0(void) {
    u32 maxSize = 0;
    u32 aligned;
    u8 *pool;
    s32 off = 0;
    s32 i;
    s32 j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 5; j++) {
            u32 size = *(u32 *)(lbl_2_data_12EC0 + off + 4) & 0x0FFFFFFF;
            if (maxSize < size) {
                maxSize = size;
            }
            off += 0x130;
        }
    }
    aligned = (maxSize + 0x1F) & ~0x1F;
    pool = _OSAllocFromHeap(0x20, aligned * 4);
    *(u8 **)(hugeAnimStruct + 0xE88) = pool + aligned;
    *(u8 **)(hugeAnimStruct + 0x1104) = pool + aligned * 2;
    *(u8 **)(hugeAnimStruct + 0x2C8C) = pool;
    *(u8 **)(hugeAnimStruct + 0xC0C) = pool;
    *(u8 **)(hugeAnimStruct + 0x1380) = pool + aligned * 3;
}

// .text:0x0004777C size:0x44 mapped:0x80686810
void fn_2_4777C(void) {
    void *obj = *(void **)(hugeAnimStruct + 0x2C8C);
    if (obj != NULL) {
        fn_800ACFB0(obj);
    }
    *(void **)(hugeAnimStruct + 0x2C8C) = NULL;
}

// .text:0x00047540 size:0x23C mapped:0x806865D4
void fn_2_47540(void) {
    return;
}

// .text:0x000474FC size:0x44 mapped:0x80686590
void fn_2_474FC(void) {
    void *obj = *(void **)(hugeAnimStruct + 0x2C88);
    if (obj != NULL) {
        fn_800ACFB0(obj);
    }
    *(void **)(hugeAnimStruct + 0x2C88) = NULL;
}

// .text:0x000474F8 size:0x4 mapped:0x8068658C
void fn_2_474F8(void) {
    return;
}

// .text:0x000472C4 size:0x234 mapped:0x80686358
void fn_2_472C4(void) {
    return;
}

// .text:0x00046D94 size:0x530 mapped:0x80685E28
void fn_2_46D94(void) {
    return;
}

// .text:0x00046D34 size:0x60 mapped:0x80685DC8
void fn_2_46D34(s32 delta) {
    addStatCounter(delta);
}

// .text:0x00046D00 size:0x34 mapped:0x80685D94
BOOL fn_2_46D00(void) {
    u8 *state = lbl_2_bss_1A8248;
    if (state[0x441C] == 5 && state[0x4422] >= 6) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x00046C88 size:0x78 mapped:0x80685D1C
void fn_2_46C88(void *self) {
    Vec v;
    fn_2_68690(0);
    fn_2_68DAC(self, &v);
    PSVECScale(&v, 2.0f, &v);
    *lbl_2_data_13374 = lbl_803CBD0C;
    fn_80031CA4(&v, lbl_2_data_13374);
}
