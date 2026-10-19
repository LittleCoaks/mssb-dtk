#include "Unknown/movie.h"
static void movieMixInto(MovieDecoder* self, u8* dst, u32 len);

#define MOVIE_CNT(idx) (**(u32**)((u8*)&lbl_803CBAF8 + (idx) * 4))

void fn_800AD070(void) {
    MovieDecoder* self = lbl_803CC170;
    MovieSlot* slot;
    u32 code;
    u32 k;
    u16 w;
    u16 h;
    u8* buf;
    void (*conv)(void*, void*, u32, u32);

    if (lbl_803CC17F == 0 || self == NULL) {
        return;
    }
    if (!(self->unk1B9 & 1) && !(self->unk1BA & 0x10) && lbl_803C6CF8[0x722] == 5) {
        if (self->unk1BA & 1) {
            self->unk1BA = 2;
            self->unk1A0 = OSGetTime();
        }
        self->unk1BA |= 0x10;
    }

    if (self->unk1BA & 4) {
        code = 4;
    } else {
        s8 v = (s8)lbl_803C6CF8[0x722];

        if (v == 0) {
            if (self->unk1BA & 2) {
                code = self->unk1BA & 0x12;
            } else {
                code = self->unk1BA & 1;
            }
        } else if (v == -1) {
            code = 0xA0000000;
        } else {
            code = (u32)v | 0x80000000;
        }
    }
    if (code == 0x12 || code - 0x80000000 < 3) {
        if (self->unk1B9 != 0) {
            fn_800AD95C(self, self->unk1B9);
        }
    }

    if (!(self->unk1BA & 1)) {
        goto L42C;
    }
    if (self->unk1BA & 8) {
        for (k = 0; k < 6; k++) {
            if (((MovieSlot*)((u8*)self + 0xF4 + k * 12))->state != 1) {
                goto L42C;
            }
        }
        if (self->unk1B9 & 1) {
            self->unk1AC = 0;
            self->unk1A8 = 0;
        } else {
            self->unk198 = OSGetTime();
        }
        self->unk1BA = 1;
    }
    if (self->unk1B9 & 1) {
        self->unk180 = (u32)((((u64)self->unk1A8 << 32 | self->unk1AC) * 1000000) / (self->unk40 << 2)) / self->unk24;
    } else {
        self->unk180 = (u32)((OSGetTime() - self->unk198) * 1000000) / (*(u32*)0x800000F8 >> 2) / self->unk24;
    }

    for (k = 0; k < 6; k++) {
        slot = (MovieSlot*)((u8*)self + 0xF4 + k * 12);
        if (slot->state == 1 && self->unk180 == slot->unk04) {
            slot->state = 2;
            self->unk174 ^= 1;
            w = self->unkA4;
            h = self->unkA6;
            buf = *(u8**)((u8*)self + 0x16C + self->unk174 * 4);
            conv = ((void (**)(void*, void*, u32, u32))&yuv2rgbConverters)[self->unk1B8];
            conv(slot->unk00, buf, w, h);
            GXInitTexObj((GXTexObj*)lbl_803C78A4, buf, w, h,
                         *(u32*)((u8*)lbl_803CBAD8 + (self->unk1B8 << 2)), 0, 0, 0);
            lbl_803CC182 = 1;
        }
    }

L42C:
    if (lbl_803CC182 != 0) {
        void (*fp)(u32) = (void (*)(u32))lbl_803CC190;

        if (fp != NULL) {
            fp(self->unk180);
        } else {
            fn_800A7D4C(0, (u8*)lbl_801112E0 + lbl_803CC198 * 8);
            lbl_803CC198 ^= 1;
        }
    }
}

u32 fn_800AD490(MovieDecoder* self) {
    u8 st;
    s8 v;

    if (self == NULL) {
        return 0xC0000000;
    }
    st = self->unk1BA;
    if (st & 4) {
        return 4;
    }
    v = (s8)lbl_803C6CF8[0x722];
    if (v == 0) {
        if (st & 2) {
            return st & 0x12;
        }
        return st & 1;
    }
    if (v == -1) {
        return 0xA0000000;
    }
    return (u32)v | 0x80000000;
}

void fn_800AD500(MovieDecoder* self, u8* base) {
    u32 n = lbl_803CBAE4;
    u32 stride = n * ((((self->unk30 + 31) & ~31) + (n - 1)) / n);
    u32 prod = (u32)self->unkA4 * self->unkA6;
    u32 ab = (u32)self->unkA8 * self->unkA9;
    u32 sz = prod << (self->unk1B8 + 1);
    u32 sz31 = sz + 31;
    u32 bytes28 = stride * 28;
    u32 mid;
    u32 step;

    fn_800E4B90(self->unkA0);
    self->unk16C = base + ((fn_800E4B1C(self->unkA0) + 31) & ~31);
    self->unk170 = self->unk16C + (sz31 & ~31);
    memset(self->unk16C, 0, (sz31 << 1) & ~63);
    GXInitTexObj((GXTexObj*)lbl_803C78A4, self->unk16C, self->unkA4, self->unkA6,
                 *(u32*)((u8*)lbl_803CBAD8 + (self->unk1B8 << 2)), 0, 0, 0);
    self->unk174 = 0;
    self->unk164 = self->unk170 + (sz31 & ~31);
    self->unk168 = self->unk164 + ((self->unk28 + 31) & ~31);
    memset(self->unk168, 0, bytes28);
    self->unk154 = self->unk168 + ((self->unk30 + 31) & ~31);
    self->unkE8 = self->unk154;
    self->unkD0 = self->unk154;
    self->unk160 = self->unk154;
    self->unk158 = self->unk154;
    mid = (prod * (ab + 2)) / ab;
    self->unkF4 = self->unk154 + bytes28;
    self->unk15C = self->unkF4;
    self->unkEC = self->unkF4;
    self->unkD4 = self->unkF4;
    step = (mid + 31) & ~31;
    self->unk100 = self->unkF4 + step;
    self->unk10C = self->unk100 + step;
    self->unk118 = self->unk10C + step;
    self->unk124 = self->unk118 + step;
    self->unk130 = self->unk124 + step;
}

u32 fn_800AD6BC(MovieDecoder* self) {
    u32 ab = self->unkA8 * self->unkA9;
    u32 n = lbl_803CBAE4;
    u32 w = (self->unk30 + 31) & ~31;
    u32 count = (w + (n - 1)) / n;
    u32 prod = self->unkA4 * self->unkA6;
    u32 bits = prod << (self->unk1B8 + 1);
    u32 ext = ((bits + 0x1F) << 1) & ~0x3F;
    u32 total = ((self->unk28 + 31) & ~31) + ext + w;
    u32 q = (prod * (ab + 2)) / ab;

    total += 6 * ((q + 31) & ~31);
    total += 28 * n * count;
    total += (fn_800E4B1C(self->unkA0) + 31) & ~31;
    return total;
}

BOOL fn_800AD780(MovieDecoder* self) {
    u32 code;
    u8 st;

    if (self == NULL) {
        code = 0xC0000000;
    } else {
        st = self->unk1BA;
        if (st & 4) {
            code = 4;
        } else {
            s8 v = (s8)lbl_803C6CF8[0x722];

            if (v == 0) {
                if (st & 2) {
                    code = st & 0x12;
                } else {
                    code = st & 1;
                }
            } else if (v == -1) {
                code = 0xA0000000;
            } else {
                code = (u32)v | 0x80000000;
            }
        }
    }
    if (code == 0) {
        return TRUE;
    }
    if (code == 4 && lbl_803CC170 == 0) {
        return TRUE;
    }
    return FALSE;
}

void fn_800AD830(MovieDecoder* self) {
    u32 code;
    u8 st;

    if (self == NULL) {
        code = 0xC0000000;
    } else {
        st = self->unk1BA;
        if (st & 4) {
            code = 4;
        } else {
            s8 v = (s8)lbl_803C6CF8[0x722];

            if (v == 0) {
                if (st & 2) {
                    code = st & 0x12;
                } else {
                    code = st & 1;
                }
            } else if (v == -1) {
                code = 0xA0000000;
            } else {
                code = (u32)v | 0x80000000;
            }
        }
    }
    if (code != 0 && !(code == 4 && lbl_803CC170 == 0)) {
        OSSendMessage(&lbl_802FB870, (OSMessage)2, OS_MESSAGE_NOBLOCK);
    }
}

void fn_800AD914(MovieDecoder* self) {
    if (self->unk1BA & 1) {
        self->unk1BA = 2;
        self->unk1A0 = OSGetTime();
    }
}

void fn_800AD95C(MovieDecoder* self, u8 flag) {
    u8 st;

    if (self == NULL) {
        return;
    }
    st = self->unk1BA;
    if (st == 0 || st == 4) {
        self->unk1B9 = flag;
        OSSendMessage(&lbl_802FB870, (OSMessage)1, OS_MESSAGE_NOBLOCK);
    } else if (st & 2) {
        self->unk1BA = 1;
        self->unk198 += OSGetTime() - self->unk1A0;
    }
}

void fn_800AD9F4(MovieDecoder* self) {
    u32 code;
    u8 st;

    if (self == NULL) {
        return;
    }
    st = self->unk1BA;
    if (st & 3) {
        if (st & 4) {
            code = 4;
        } else {
            s8 v = (s8)lbl_803C6CF8[0x722];

            if (v == 0) {
                if (st & 2) {
                    code = st & 0x12;
                } else {
                    code = st & 1;
                }
            } else if (v == -1) {
                code = 0xA0000000;
            } else {
                code = (u32)v | 0x80000000;
            }
        }
        if (code != 0 && !(code == 4 && lbl_803CC170 == NULL)) {
            OSSendMessage(&lbl_802FB870, (OSMessage)2, OS_MESSAGE_NOBLOCK);
        }
    }
    OSSendMessage(&lbl_802FB870, (OSMessage)3, OS_MESSAGE_NOBLOCK);
}

u8 fn_800ADAFC(void) {
    return lbl_803CC17D;
}

BOOL fn_800ADB04(MovieSource* src, MovieDecoder* dec, u8 a, u8 b) {
    if (lbl_803CC17D != 0) {
        return FALSE;
    }
    lbl_803CC181 = b;
    lbl_803CC170 = dec;
    dec->unkF0 = src;
    lbl_803CC1A4 = src->unk0C;
    if (lbl_803CC181 != 0) {
        lbl_803CC1AC = src->unk0C;
        if (lbl_803C7A00.unk08 != 0) {
            fn_800ACFB0((void*)lbl_803C7A00.unk08);
        }
    }
    lbl_803CC170->unk13C = (u8*)lbl_803CC170 + 0xF4;
    lbl_803CC170->unk140 = (u8*)lbl_803CC170 + 0x100;
    lbl_803CC170->unk144 = (u8*)lbl_803CC170 + 0x10C;
    lbl_803CC170->unk148 = (u8*)lbl_803CC170 + 0x118;
    lbl_803CC170->unk14C = (u8*)lbl_803CC170 + 0x124;
    lbl_803CC170->unk150 = (u8*)lbl_803CC170 + 0x130;
    lbl_803CC170->unk1B8 = a;
    if (lbl_803CC17E == 0) {
        OSResumeThread(&lbl_802FB220);
    }
    OSSendMessage(&lbl_802FB870, NULL, OS_MESSAGE_NOBLOCK);
    return TRUE;
}

void fn_800ADBFC(void) {
    if (lbl_803CC17F != 0) {
        lbl_803CC17C = TRUE;
        OSSendMessage(&lbl_802FB870, (OSMessage)4, OS_MESSAGE_NOBLOCK);
    }
}

void fn_800ADC40(void* a, void* b) {
    u8* base = lbl_802F93A0;

    if (lbl_803CC17F != 0) {
        return;
    }
    lbl_803CC174 = a;
    lbl_803CC178 = b;
    if (AIGetDSPSampleRate() == 1) {
        lbl_803CBAE2 = 0xF0;
        lbl_803CBAE4 = 0x3C0;
    } else {
        lbl_803CBAE2 = 0xA0;
        lbl_803CBAE4 = 0x280;
    }
    fn_800E4AC8();
    lbl_803CC170 = NULL;
    lbl_803CC17C = 0;
    lbl_803CC190 = 0;
    lbl_803CC180 = 0;
    lbl_803CC18C = AIRegisterDMACallback(fn_800AE5B8);
    C_MTXOrtho((f32(*)[4])(base + 0x1E40), lbl_803CCEEC, lbl_803CCEF0, lbl_803CCEEC, lbl_803CCEF4,
               lbl_803CCEF8, lbl_803CCEFC);
    OSInitMessageQueue((OSMessageQueue*)(base + 0x24D0), (OSMessage*)(base + 0x24B0), 8);
    OSCreateThread((OSThread*)(base + 0x2198), fn_800AE8B8, NULL, base + 0x3500, 0x1000, 0x14, 1);
    OSCreateThread((OSThread*)(base + 0x1E80), (OSThreadStartFunction)MovDecodeThread, NULL, base + 0x5500,
                   0x2000, 0x1F, 1);
    OSResumeThread((OSThread*)(base + 0x2198));
    OSResumeThread((OSThread*)(base + 0x1E80));
    lbl_803CC17F = 1;
}

void fn_800ADD70(void) {
    MovieDecoder* self = lbl_803CC170;
    f32 savedProj[7];
    Mtx ident;
    GXColor color;
    s16* q;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 z;

    if (self == NULL) {
        return;
    }
    GXGetProjectionv(savedProj);
    GXSetProjection((void*)lbl_802FB1E0, 1);
    GXInvalidateTexAll();
    GXLoadTexObj((GXTexObj*)lbl_803C78A4, 0);
    GXInvalidateVtxCache();
    GXClearVtxDesc();
    GXSetVtxDesc(9, 2);
    GXSetVtxDesc(13, 1);
    GXSetVtxAttrFmt(0, 9, 1, 3, 0);
    GXSetVtxAttrFmt(0, 13, 1, 0, 0);
    lbl_803CC194 ^= 1;
    q = (s16*)*(u32*)(lbl_803CBB00 + ((lbl_803CC194 & 0xFF) << 2));
    x0 = self->unk1B6;
    y0 = self->unk1B4;
    x1 = x0 + (self->unk1B0 - 1);
    y1 = y0 + (self->unk1B2 - 1);
    z = (s16)(s32)lbl_803CC184;
    q[0] = x0;
    q[1] = y0;
    q[2] = z;
    q[3] = x1;
    q[4] = y0;
    q[5] = z;
    q[6] = x1;
    q[7] = y1;
    q[8] = z;
    q[9] = x0;
    q[10] = y1;
    q[11] = z;
    DCFlushRange(q, 0x18);
    GXSetArray(9, q, 6);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    *(u32*)&color = lbl_803CCEE8;
    GXSetChanMatColor(4, color);
    GXSetTevOp(0, 3);
    GXSetTevOrder(0, 0, 0, 4);
    PSMTXIdentity(ident);
    GXLoadPosMtxImm(ident, 0);
    GXSetCurrentMtx(0);
    GXCallDisplayList(lbl_801112C0, 0x20);
    GXSetProjectionv(savedProj);
}

void YUV2RGB(u8* y, u8* dst, u32 w, u32 h) {
    s16* tab = (s16*)lbl_801102C0;
    u8* clampTab = lbl_801102C0 + 0xA00;
    u8* uPlane;
    u8* vPlane;
    u32 row;
    u32 col;
    u32 ci;
    u32 idx;
    s32 yv;
    s32 rOff;
    s32 gOff;
    s32 bOff;
    s32 uu;
    s32 vv;
    u16 pix;

    if (y == NULL) {
        OSReport(lbl_800E7B50);
        for (;;) {
        }
    }
    if (dst == NULL) {
        OSReport(lbl_800E7B74);
        for (;;) {
        }
    }
    uPlane = y + w * h;
    vPlane = uPlane + (w >> 1) * (h >> 1);
    for (row = 0; row < h; row += 2) {
        for (col = 0; col < w; col += 2) {
            ci = (row >> 1) * (w >> 1) + (col >> 1);
            uu = uPlane[ci];
            vv = vPlane[ci];
            rOff = ((s16*)(lbl_801102C0 + 0x400))[vv];
            gOff = ((s16*)(lbl_801102C0 + 0x200))[vv] + ((s16*)(lbl_801102C0 + 0x600))[uu];
            bOff = ((s16*)(lbl_801102C0 + 0x800))[uu];
            for (idx = 0; idx < 4; idx++) {
                u32 dy = idx >> 1;
                u32 dx = idx & 1;

                yv = tab[y[(row + dy) * w + col + dx]];
                pix = (u16)(((clampTab[yv + rOff] >> 3) << 10) | ((clampTab[yv + gOff] >> 3) << 5) |
                            (clampTab[yv + bOff] >> 3));
                ((u16*)dst)[(row + dy) * w + col + dx] = pix;
            }
        }
    }
}

void YUV2RGB_(u8* y, u8* dst, u32 w, u32 h) {
    s16* tab = (s16*)lbl_801102C0;
    u8* clampTab = lbl_801102C0 + 0xA00;
    u8* uPlane;
    u8* vPlane;
    u32 row;
    u32 col;
    u32 ci;
    u32 idx;
    s32 yv;
    s32 rOff;
    s32 gOff;
    s32 bOff;
    s32 uu;
    s32 vv;
    u16 pix;

    if (y == NULL) {
        OSReport(lbl_800E7B50);
        for (;;) {
        }
    }
    if (dst == NULL) {
        OSReport(lbl_800E7B74);
        for (;;) {
        }
    }
    uPlane = y + w * h;
    vPlane = uPlane + (w >> 1) * (h >> 1);
    for (row = 0; row < h; row += 2) {
        for (col = 0; col < w; col += 2) {
            ci = (row >> 1) * (w >> 1) + (col >> 1);
            uu = uPlane[ci];
            vv = vPlane[ci];
            rOff = ((s16*)(lbl_801102C0 + 0x400))[vv];
            gOff = ((s16*)(lbl_801102C0 + 0x200))[vv] + ((s16*)(lbl_801102C0 + 0x600))[uu];
            bOff = ((s16*)(lbl_801102C0 + 0x800))[uu];
            for (idx = 0; idx < 4; idx++) {
                u32 dy = idx >> 1;
                u32 dx = idx & 1;

                yv = tab[y[(row + dy) * w + col + dx]];
                pix = (u16)(((clampTab[yv + rOff] >> 3) << 10) | ((clampTab[yv + gOff] >> 3) << 5) |
                            (clampTab[yv + bOff] >> 3));
                ((u16*)dst)[(row + dy) * w + col + dx] = pix;
            }
        }
    }
}

void fn_800AE5B8(void) {
    u32 toggle;
    u8* buf;
    u32 dmaAddr;
    BOOL level;
    u32 len;
    MovieDecoder* self;

    lbl_803CC18C();
    toggle = lbl_803CC188 ^ 1;
    lbl_803CC188 = toggle;
    buf = lbl_802F93E0 + toggle * 0xF00;
    dmaAddr = AIGetDMAStartAddr() + 0x80000000;
    if (dmaAddr != 0) {
        level = OSEnableInterrupts();
        len = lbl_803CBAE4;
        DCInvalidateRange((void*)dmaAddr, len);
        self = lbl_803CC170;
        if (self != NULL && (self->unk1BA & 1) && !(self->unk1BA & 8) && (self->unk1B9 & 1)) {
            if (self->unk158 >= self->unk160 ||
                (self->unk158 + len <= self->unk160 && !(self->unk1BA & 2))) {
                movieMixInto(self, (u8*)dmaAddr, len);
            }
        }
        DCFlushRange((void*)dmaAddr, len);
        OSRestoreInterrupts(level);
    } else {
        len = lbl_803CBAE4;
        AIInitDMA((u32)buf, len);
        level = OSEnableInterrupts();
        memset(buf, 0, len);
        self = lbl_803CC170;
        if (self != NULL && (self->unk1BA & 1) && !(self->unk1BA & 8) && (self->unk1B9 & 1)) {
            if (self->unk158 >= self->unk160 ||
                (self->unk158 + len <= self->unk160 && !(self->unk1BA & 2))) {
                movieMixInto(self, buf, len);
            }
        }
        DCFlushRange(buf, len);
        OSRestoreInterrupts(level);
    }
}

static void movieMixInto(MovieDecoder* self, u8* dst, u32 len) {
    u32 cur = (u32)self->unk158;
    u32 end = (u32)self->unk15C;
    u32 count = len >> 1;
    u32 i;
    u32 coeff;
    s32 x;
    s32 sum;
    s16* out = (s16*)dst;

    coeff = *(u16*)(lbl_801101C0 + ((lbl_803CBAE0 & 0x7F) << 1));
    for (i = 0; i < count; i++) {
        if (cur + i * 2 > end) {
            cur = (u32)self->unk154 - i * 2;
        }
        x = *(s16*)(cur + i * 2);
        sum = (x & 0x8000) + (((x * coeff) >> 15) & 0x7FFF);
        out[i] = (s16)(out[i] + (s16)sum);
    }
    self->unk158 = self->unk158 + len;
    self->unk1AC += len;
    if (self->unk1AC < len) {
        self->unk1A8++;
    }
    self->unk198 = OSGetTime();
    if ((u32)self->unk158 >= end) {
        self->unk158 = self->unk154 + ((u32)self->unk158 - end);
    }
}

void* fn_800AE8B8(void* arg) {
    OSThreadQueue* queue = (OSThreadQueue*)(lbl_803C7420 + 0x5C);
    MovieDecoder* self;
    u32 msg;
    BOOL level;

    for (;;) {
        OSReceiveMessage(&lbl_802FB870, (OSMessage*)&msg, OS_MESSAGE_BLOCK);
        self = lbl_803CC170;
        switch (msg) {
        case 0:
            if (MovStreamThread(self) != 0) {
                lbl_803CC17D = TRUE;
            } else {
                OSSendMessage(&lbl_802FB870, NULL, OS_MESSAGE_BLOCK);
            }
            break;
        case 1:
            if (fn_800AF9B4((u8*)self + 0x60, 0x14) == 0) {
                OSPanic(&lbl_803CCF00, 0x355, &lbl_800E7B98);
            } else {
                if ((self->unk1B9 & 1) != 0 && self->unk1BB == 0xFF) {
                    self->unk1B9 &= 0xFE;
                }
                level = OSDisableInterrupts();
                self->unk1AC = 0;
                self->unk1A8 = 0;
                self->unk198 = 0;
                self->unk184 = 0;
                self->unk188 = 0;
                self->unk190 = 0;
                self->unk18C = 0;
                self->unk17C = 0;
                self->unk178 = 0;
                self->unk160 = self->unk154;
                self->unk158 = self->unk154;
                self->unk1BA = 9;
                lbl_803CC180 = 0;
                OSRestoreInterrupts(level);
            }
            break;
        case 2:
            self->unk1BA = 4;
            while (self->unk1BC != 0) {
                OSSleepThread(queue);
            }
            if (lbl_803CC181 == 0) {
                fn_800A6C80();
                while (lbl_803C6CF8[0x715] != 1) {
                }
            }
            self->unkFC = 0;
            self->unk108 = 0;
            self->unk114 = 0;
            self->unk120 = 0;
            self->unk12C = 0;
            self->unk138 = 0;
            self->unk1AC = 0;
            self->unk1A8 = 0;
            self->unk198 = 0;
            self->unk184 = 0;
            self->unk188 = 0;
            self->unk190 = 0;
            self->unk18C = 0;
            self->unk17C = 0;
            self->unk178 = 0;
            self->unk160 = self->unk154;
            self->unk158 = self->unk154;
            lbl_803CC170 = NULL;
            if (lbl_803CC181 != 0) {
                fn_800AFBF0();
            }
            break;
        case 3:
            lbl_803CC182 = 0;
            lbl_803CC17D = 0;
            break;
        case 4:
            lbl_803CC182 = 0;
            AIRegisterDMACallback((AIDCallback)lbl_803CC18C);
            lbl_803CC18C = 0;
            while (lbl_803CC17E != 0) {
                OSSleepThread(queue);
            }
            lbl_803CC17F = 0;
            return NULL;
        default:
            break;
        }
    }
}

BOOL MovStreamThread(MovieDecoder* self) {
    u32 i;

    lbl_803CC1A0 = 0;
    fn_800A6E24(self->unkF0, lbl_803CC174, lbl_803CC178);
    if (lbl_803CC181 != 0) {
        fn_800B05E4(-1, 0x10000);
        lbl_803CC174 = (void*)lbl_803C7A00.unk08;
        lbl_803CC178 = (void*)lbl_803C7A00.unk18;
    }
    if (fn_800AF9B4((u8*)self, 0x44) == 0) {
        OSPanic(&lbl_803CCF00, 0x2ED, lbl_800E7B50 + 0x74);
        return FALSE;
    }
    if (strncmp(lbl_800E7B50 + 0xA0, (char*)self, strlen(lbl_800E7B50 + 0xA0)) != 0) {
        for (i = 0; i < 0x44; i++) {
        }
        OSPanic(&lbl_803CCF00, 0x300, lbl_800E7B50 + 0xAC);
        return FALSE;
    }
    self->unk1BB = 0xFF;
    if (self->unk40 == 0) {
    } else if (self->unk40 == 0xBBAA) {
        if (AIGetDSPSampleRate() != 1) {
            OSPanic(&lbl_803CCF00, 0x30B, lbl_800E7B50 + 0xDC);
            return FALSE;
        }
        self->unk1BB = 1;
    } else if (self->unk40 == 0x7D1C) {
        if (AIGetDSPSampleRate() != 0) {
            OSPanic(&lbl_803CCF00, 0x313, lbl_800E7B50 + 0xDC);
            return FALSE;
        }
        self->unk1BB = 0;
    } else {
        OSPanic(&lbl_803CCF00, 0x31A, lbl_800E7B50 + 0xDC);
        return FALSE;
    }
    fn_800E4AE8(self->unkA0, (u8*)self + 0x34);
    if (fn_800E4B1C(self->unkA0) == 0) {
        OSPanic(&lbl_803CCF00, 0x324, lbl_800E7B50 + 0x11C);
        return FALSE;
    }
    self->unk1B0 = self->unkA4;
    self->unk1B2 = self->unkA6;
    self->unk1B4 = (s16)((0x1E0 - (s32)self->unk1B2) >> 1);
    self->unk1B6 = (s16)((0x280 - (s32)self->unk1B0) >> 1);
    return TRUE;
}

BOOL fn_800AED24(void) {
    return lbl_803CC19C == 0;
}

void* MovDecodeThread(void* arg) {
    MovieDecoder* self;
    u32 r;
    s32 ok;

    OSSuspendThread(&lbl_802FB220);
    lbl_803CC17E = 1;
    for (;;) {
        if (lbl_803CC17C != 0) {
            goto exitThread;
        }
        self = lbl_803CC170;
        if (self == NULL) {
            continue;
        }
        if (!(self->unk1BA & 1)) {
            continue;
        }
        self->unk1BC = 1;
        r = fn_800AF1A8(self);
        lbl_803CC19C = r;
        if (r == 2) {
            OSPanic(&lbl_803CCF00, 0x27D, lbl_800E7B98);
            self->unk1BA = 4;
            self->unk1BC = 0;
            continue;
        }
        if (r >= 4) {
            self->unk1BC = 0;
            continue;
        }
        if (self->unk1B9 & 2) {
            do {
                if (self->unk1B9 & 1) {
                    self->unk180 = (u32)((((u64)self->unk1A8 << 32 | self->unk1AC) * 1000000) / (self->unk40 << 2)) / self->unk24;
                } else {
                    self->unk180 = (u32)((OSGetTime() - self->unk198) * 1000000) / (*(u32*)0x800000F8 >> 2) / self->unk24;
                }
                if (lbl_803CC17C != 0) {
                    goto exitThread;
                }
            } while (self->unk180 < self->unk1C);
            self->unk178 = 0;
            self->unk17C = 0;
            lbl_803CC1A0 = 0;
            if (lbl_803CC181 == 0) {
                fn_800A6E24(self->unkF0, lbl_803CC174, lbl_803CC178);
            } else {
                fn_800AFC10();
                lbl_803CC174 = (void*)lbl_803C7A00.unk08;
            }
        } else {
            do {
                if (self->unk1B9 & 1) {
                    self->unk180 = (u32)((((u64)self->unk1A8 << 32 | self->unk1AC) * 1000000) / (self->unk40 << 2)) / self->unk24;
                } else {
                    self->unk180 = (u32)((OSGetTime() - self->unk198) * 1000000) / (*(u32*)0x800000F8 >> 2) / self->unk24;
                }
                if (lbl_803CC17C != 0) {
                    goto exitThread;
                }
            } while (self->unk180 < self->unk1C);
            self->unk1BA = 4;
            lbl_803CC170 = NULL;
            self->unk1BC = 0;
            continue;
        }

        ok = fn_800AF9B4((u8*)self, 0x44);
        if (ok == 0) {
            ok = 0;
        } else if (fn_800AF9B4((u8*)self + 0x60, 0x14) == 0) {
            OSPanic(&lbl_803CCF00, 0x355, lbl_800E7B98);
            ok = 0;
        } else {
            ok = 1;
            if ((self->unk1B9 & 1) && self->unk1BB == 0xFF) {
                self->unk1B9 &= 0xFE;
            }
            {
                BOOL level = OSDisableInterrupts();

                self->unk1AC = 0;
                self->unk1A8 = 0;
                self->unk198 = 0;
                self->unk184 = 0;
                self->unk188 = 0;
                self->unk190 = 0;
                self->unk18C = 0;
                self->unk17C = 0;
                self->unk178 = 0;
                self->unk160 = self->unk154;
                self->unk158 = self->unk154;
                self->unk1BA = 9;
                lbl_803CC180 = 0;
                OSRestoreInterrupts(level);
            }
        }
        if (ok == 0) {
            self->unk1BA = 4;
            lbl_803CC170 = NULL;
        }
        self->unk1BC = 0;
    }

exitThread:
    lbl_803CC17E = 0;
    return NULL;
}

s32 fn_800AF1A8(MovieDecoder* self) {
    u32 r27 = 0;
    u32 r28;
    u32 r29;
    u32 idx;
    u32 t1;
    u32 t2;
    u32 p;
    u32 start;
    u32 end;
    u32 ringLen;
    s32 ret;

    switch (lbl_803CC180) {
    case 0:
        goto phase0;
    case 1:
        goto phase1;
    case 2:
        goto phase2;
    default:
        goto done;
    }

phase0:
    if (self->unk18C == self->unk68 && self->unk190 == self->unk6C) {
        self->unk17C += self->unk68;
        self->unk178 += 1;
        if (self->unk178 >= self->unk18) {
            return 3;
        }
        if (self->unk1BA == 4) {
            return 0;
        }
        idx = lbl_803CC181;
        if (MOVIE_CNT(idx) < 0x14) {
            self->unk17C -= self->unk68;
            self->unk178 -= 1;
            return 2;
        }
        if (fn_800AF9B4((u8*)self + 0x60, 0x14) == 0) {
            return 2;
        }
        if (self->unk1BA == 4) {
            return 0;
        }
        self->unk190 = 0;
        self->unk18C = 0;
    }
    lbl_803CC180 += 1;

phase1:
    idx = lbl_803CC181;
    if (MOVIE_CNT(idx) < 8) {
        return 1;
    }
    if (fn_800AF9B4((u8*)self + 0x80, 8) == 0) {
        return 2;
    }
    if (self->unk1BA == 4) {
        return 0;
    }
    lbl_803CC180 += 1;

phase2:
    idx = lbl_803CC181;
    r28 = self->unk84;
    if (MOVIE_CNT(idx) < r28) {
        return 1;
    }
    if (self->unk80 == 1) {
        if (self->unk1BA == 4) {
            return 0;
        }
        if (fn_800AF9B4(self->unk164, 4) == 0) {
            return 2;
        }
        if (self->unk1BA == 4) {
            return 0;
        }
        r27 = *(u32*)self->unk164;
        if (fn_800AF9B4(self->unk164, r28 - 4) == 0) {
            return 2;
        }
        if (self->unk1BA == 4) {
            return 0;
        }
        t1 = (u32)OSGetTime();
        r29 = (u32)(OSGetTime() >> 32);
        for (;;) {
            if (self->unk1BA == 4) {
                return 0;
            }
            ret = fn_800AF5FC(self, self->unk82, r27);
            if (ret == 2) {
                t1 = (u32)OSGetTime();
                continue;
            }
            break;
        }
        if (ret == 0) {
            if (self->unk1BA == 4) {
                return 0;
            }
            {
                s64 delta = OSGetTime() - ((s64)r29 << 32 | t1);
                self->unk188 += (u32)((delta * 8) / (s64)(*(u32*)0x800000F8 >> 2));
                self->unk184 += 1;
            }
            self->unk18C += 1;
        } else if (ret == 1) {
            return 1;
        } else {
            self->unk18C += 1;
        }
        lbl_803CC180 = 0;
        return 0;
    }
    if (self->unk80 == 0) {
        if (self->unk1BA == 4) {
            return 0;
        }
        if (fn_800AF9B4(self->unk168, 4) == 0) {
            return 2;
        }
        if (self->unk1BA == 4) {
            return 0;
        }
        r27 = *(u32*)self->unk168;
        if (fn_800AF9B4(self->unk168, r28 - 4) == 0) {
            return 2;
        }
        if (self->unk1BA == 4) {
            return 0;
        }
        start = (u32)self->unk158;
        end = (u32)self->unk15C;
        ringLen = end - start;
        p = (u32)self->unk160 + r27 * 4;
        do {
            if (p >= end) {
                p -= ringLen;
            }
        } while ((u32)self->unk160 < start && p < start);
        if (self->unk1BA == 4) {
            return 0;
        }
        fn_800DFDD4(self->unk168, self->unk160, self->unk3C, self->unk82, r27, (u8*)self + 0xC0);
        if (self->unk1BA == 4) {
            return 0;
        }
        self->unk160 = *(u8**)((u8*)self + 0xAC + self->unk3C * 0x18);
        self->unk190 += 1;
        lbl_803CC180 = 0;
        return 0;
    }
    return 2;

done:
    lbl_803CC180 = 0;
    return 0;
}

s32 fn_800AF5FC(MovieDecoder* self, u32 kind, u32 size) {
    u32 count;
    u32 ticks;
    u32 k;
    u32 r6;
    u8* slot;
    u8* tmp;
    BOOL found;

    if (self->unk184 != 0) {
        count = (self->unk188 / self->unk184) / self->unk24;
    } else {
        count = 0;
    }
    if (self->unk1B9 & 1) {
        if (self->unk1A8 != 0 || self->unk1AC != 0) {
            ticks = (u32)((((u64)self->unk1A8 << 32 | self->unk1AC) * 1000000) / (self->unk40 << 2)) / self->unk24;
        } else {
            ticks = 0;
        }
    } else {
        if (self->unk198 != 0) {
            ticks = (u32)((OSGetTime() - self->unk198) * 1000000) / (*(u32*)0x800000F8 >> 2) / self->unk24;
        } else {
            ticks = 0;
        }
    }
    r6 = (ticks != 0) ? count + 1 : 0;

    if (kind == 0x30) {
        if (self->unk13C == NULL || ((u8*)self->unk13C)[8] == 0) {
            return 3;
        }
        if (self->unk140 == NULL || ((u8*)self->unk140)[8] == 0) {
            return 3;
        }
        if (ticks + r6 > size + self->unk17C) {
            return 3;
        }
        for (k = 2; k < 6; k++) {
            slot = (u8*)self->unk13C + 0;
            slot = ((u8**)&self->unk13C)[k];
            if (slot[8] == 1 && ticks <= *(u32*)(slot + 4)) {
                continue;
            }
            slot[8] = 0;
            fn_800E5940(self->unkA0, self->unk164, *(u32*)slot, *(u32*)self->unk13C, *(u32*)self->unk140);
            *(u32*)(((u8**)&self->unk13C)[k] + 4) = self->unk17C + size;
            if (self->unk1BA == 4) {
                return 0;
            }
            ((u8**)&self->unk13C)[k][8] = 1;
            return 0;
        }
        return 2;
    }
    if (kind != 0x10 && kind != 0x20) {
        return 1;
    }

    found = FALSE;
    for (k = 2; k < 6; k++) {
        slot = ((u8**)&self->unk13C)[k];
        if (slot[8] == 1 && ticks <= *(u32*)(slot + 4)) {
            continue;
        }
        tmp = ((u8**)&self->unk13C)[k];
        ((u8**)&self->unk13C)[k] = ((u8**)&self->unk13C)[0];
        ((u8**)&self->unk13C)[0] = ((u8**)&self->unk13C)[1];
        ((u8**)&self->unk13C)[1] = tmp;
        found = TRUE;
        break;
    }
    if (!found) {
        return 2;
    }
    ((u8**)&self->unk13C)[1][8] = 0;
    if (ticks + r6 > size + self->unk17C) {
        return 3;
    }
    if (kind == 0x10) {
        fn_800E4FF4(self->unkA0, self->unk164, *(u32*)self->unk140);
    } else {
        if (((u8*)self->unk13C)[8] == 0) {
            return 3;
        }
        fn_800E591C(self->unkA0, self->unk164, *(u32*)self->unk140, *(u32*)self->unk13C);
    }
    *(u32*)(self->unk140 + 4) = self->unk17C + size;
    if (self->unk1BA == 4) {
        return 0;
    }
    self->unk140[8] = 1;
    return 0;
}

BOOL fn_800AF9B4(u8* dst, u32 len) {
    OSThreadQueue* queue = (OSThreadQueue*)(lbl_803C7420 + 0x5C);
    BOOL level;
    u32 pA;
    u32 pB;
    u32 p;
    u32 first;
    u32 secondBase = 0;
    u32 delta;
    u32 cursor;
    s32 avail;
    s32 room;

    if (lbl_803CC1A0 + len > lbl_803CC1A4) {
        return FALSE;
    }
    while (**(u32**)((u8*)&lbl_803CBAF8 + lbl_803CC181 * 4) < len) {
        if (fn_800AFFB0() == 0 && lbl_803CC181 != 0) {
            fn_800AFD4C();
        } else if (lbl_803CC181 == 0) {
            OSSleepThread(queue);
        }
        if (lbl_803CC17C != 0) {
            return FALSE;
        }
        if (lbl_803CC170 != NULL && lbl_803CC170->unk1BA == 4) {
            return FALSE;
        }
    }

    level = OSDisableInterrupts();
    pB = **(u32**)((u8*)&lbl_803CBAE8 + lbl_803CC181 * 4);
    pA = **(u32**)((u8*)&lbl_803CBAF0 + lbl_803CC181 * 4);
    if (pB < pA) {
        p = pB + (lbl_803CC1A0 & 0x1F);
        first = pA - p;
    } else {
        p = pB + (lbl_803CC1A0 & 0x1F);
        secondBase = (u32)lbl_803CC174;
        first = (u32)lbl_803CC174 + (u32)lbl_803CC178 - p;
    }
    OSRestoreInterrupts(level);

    if (len < first) {
        memcpy(dst, (void*)p, len);
    } else {
        memcpy(dst, (void*)p, first);
        memcpy(dst + first, (void*)secondBase, len - first);
    }

    cursor = lbl_803CC1A0;
    delta = ((cursor + len) + 31 & ~31) - (cursor + 31 & ~31);
    if (delta != 0) {
        if (lbl_803CC181 == 0) {
            fn_800A6D10(delta);
        } else {
            fn_800AFFC0(delta);
        }
        if (lbl_803CC181 != 0) {
            avail = (s32)(lbl_803C7A00.unk18 - lbl_803C7A00.unk1C);
            if (avail > 0) {
                room = (s32)(lbl_803CC1AC - lbl_803C79D4.unk20);
                if (room > avail) {
                    fn_800B0008((u32)avail & ~31);
                } else if (lbl_803CC1AC > lbl_803C79D4.unk20) {
                    fn_800B0008((u32)room);
                }
            }
            if (lbl_803C79D4.unk1C < lbl_803CC1AC) {
                fn_800B0134(delta);
            }
        }
    }
    lbl_803CC1A0 = lbl_803CC1A0 + len;
    return TRUE;
}

void fn_800AFBF0(void) {
    fn_800A63C8();
}

void fn_800AFC10(void) {
    u32 aligned;
    u32 seg1;
    u32 seg2;
    u32 start2;
    u32 excess;

    lbl_803C79D4.unk0C = lbl_803C79D4.unk00;
    lbl_803C79D4.unk08 = lbl_803C79D4.unk00;
    lbl_803C79D4.unk20 = 0;
    lbl_803C7A00.unk14 = lbl_803C7A00.unk08;
    lbl_803C7A00.unk10 = lbl_803C7A00.unk08;
    lbl_803C7A00.unk1C = 0;
    lbl_803C7A00.unk20 = 0;
    if (lbl_803C7A00.unk18 == 0) {
        return;
    }
    aligned = (lbl_803C7A00.unk18 + 31) & ~31;
    if (lbl_803C7A00.unk08 + aligned > lbl_803C7A00.unk0C) {
        seg1 = lbl_803C7A00.unk0C - lbl_803C7A00.unk08;
        start2 = lbl_803C7A00.unk08;
        seg2 = aligned - seg1;
    } else {
        seg1 = aligned;
        start2 = 0;
        seg2 = 0;
    }
    fn_800B0230(lbl_803C7A00.unk08, seg1);
    while (lbl_803C79D4.unk29 != 0) {
    }
    if (seg2 != 0) {
        fn_800B0230(start2, seg2);
        while (lbl_803C79D4.unk29 != 0) {
        }
    }
    if (lbl_803C7A00.unk14 + aligned >= lbl_803C7A00.unk0C) {
        lbl_803C7A00.unk14 = lbl_803C7A00.unk08 + seg2;
    } else {
        lbl_803C7A00.unk14 += seg1;
    }
    lbl_803C7A00.unk1C += aligned;
    if (lbl_803C79D4.unk20 > lbl_803CC1AC) {
        excess = lbl_803C79D4.unk20 - lbl_803CC1AC;
        memset((void*)(lbl_803C7A00.unk14 - excess), 0, excess);
    }
}

BOOL fn_800AFD4C(void) {
    u32 chunk;
    u32 base;
    u32 first;
    u32 rest;
    u32 secondBase;
    BOOL level;
    u32 aligned;
    u32 seg1;
    u32 seg2;
    u32 start2;
    u32 excess;
    u32 end;

    if (lbl_803C79D4.unk28 != 0) {
        return TRUE;
    }
    if (lbl_803C79D4.unk10 <= lbl_803C79D4.unk1C + 0x4000) {
        chunk = lbl_803C79D4.unk10 - lbl_803C79D4.unk1C;
    } else {
        chunk = 0x4000;
    }
    while (*(u32*)&lbl_803C6CF8[0x710] < chunk) {
    }
    level = OSDisableInterrupts();
    secondBase = lbl_803C7A00.unk00;
    base = *(u32*)&lbl_803C6CF8[0x708];
    end = lbl_803C7A00.unk00 + lbl_803C7A00.unk04;
    if (base + chunk >= end) {
        first = end - base;
        rest = chunk - first;
    } else {
        secondBase = 0;
        first = chunk;
        rest = 0;
    }
    OSRestoreInterrupts(level);
    if (chunk < first) {
        fn_800B03F4(base, first);
        while (lbl_803C79D4.unk29 != 0) {
        }
        fn_800B03F4(secondBase, rest);
    } else {
        fn_800B03F4(base, chunk);
    }
    while (lbl_803C79D4.unk29 != 0) {
    }
    if (chunk != 0) {
        fn_800A6D10(chunk);
    }
    if (lbl_803C79D4.unk1C < lbl_803C79D4.unk10) {
        return TRUE;
    }
    aligned = (lbl_803C7A00.unk18 + 31) & ~31;
    if (lbl_803C7A00.unk1C < lbl_803C7A00.unk18) {
        if (lbl_803C7A00.unk14 + aligned > lbl_803C7A00.unk0C) {
            seg1 = lbl_803C7A00.unk0C - lbl_803C7A00.unk14;
            start2 = lbl_803C7A00.unk08;
            seg2 = aligned - seg1;
        } else {
            seg1 = aligned;
            start2 = 0;
            seg2 = 0;
        }
        fn_800B0230(lbl_803C7A00.unk14, seg1);
        while (lbl_803C79D4.unk29 != 0) {
        }
        if (seg2 != 0) {
            fn_800B0230(start2, seg2);
            while (lbl_803C79D4.unk29 != 0) {
            }
        }
        if (lbl_803C7A00.unk14 + aligned >= lbl_803C7A00.unk0C) {
            lbl_803C7A00.unk14 = lbl_803C7A00.unk08 + seg2;
        } else {
            lbl_803C7A00.unk14 += seg1;
        }
        lbl_803C7A00.unk1C += aligned;
        if (lbl_803C79D4.unk20 > lbl_803CC1AC) {
            excess = lbl_803C79D4.unk20 - lbl_803CC1AC;
            memset((void*)(lbl_803C7A00.unk14 - excess), 0, excess);
        }
    }
    fn_800A6C80();
    while (lbl_803C6CF8[0x715] != 1) {
    }
    lbl_803C79D4.unk28 = 1;
    return TRUE;
}

u8 fn_800AFFB0(void) {
    return lbl_803C79D4.unk28;
}

void fn_800AFFC0(u32 n) {
    lbl_803C7A00.unk10 += n;
    if (lbl_803C7A00.unk10 >= lbl_803C7A00.unk0C) {
        lbl_803C7A00.unk10 -= lbl_803C7A00.unk18;
    }
    lbl_803C7A00.unk1C -= n;
    lbl_803C7A00.unk20 += n;
}

BOOL fn_800B0008(u32 n) {
    u32 aligned = (n + 31) & ~31;
    u32 seg1;
    u32 seg2;
    u32 start2;
    u32 excess;

    if (lbl_803C7A00.unk1C >= lbl_803C7A00.unk18) {
        return TRUE;
    }
    if (lbl_803C7A00.unk14 + aligned > lbl_803C7A00.unk0C) {
        seg1 = lbl_803C7A00.unk0C - lbl_803C7A00.unk14;
        start2 = lbl_803C7A00.unk08;
        seg2 = aligned - seg1;
    } else {
        seg1 = aligned;
        start2 = 0;
        seg2 = 0;
    }
    fn_800B0230(lbl_803C7A00.unk14, seg1);
    while (lbl_803C79D4.unk29 != 0) {
    }
    if (seg2 != 0) {
        fn_800B0230(start2, seg2);
        while (lbl_803C79D4.unk29 != 0) {
        }
    }
    if (lbl_803C7A00.unk14 + aligned >= lbl_803C7A00.unk0C) {
        lbl_803C7A00.unk14 = lbl_803C7A00.unk08 + seg2;
    } else {
        lbl_803C7A00.unk14 += seg1;
    }
    lbl_803C7A00.unk1C += aligned;
    if (lbl_803C79D4.unk20 > lbl_803CC1AC) {
        excess = lbl_803C79D4.unk20 - lbl_803CC1AC;
        memset((void*)(lbl_803C7A00.unk14 - excess), 0, excess);
    }
    return TRUE;
}

BOOL fn_800B0134(u32 n) {
    u32 base;
    u32 ringStart;
    u32 ringEnd;
    u32 len1;
    u32 start1;
    u32 len2;
    BOOL level;

    while (*(u32*)&lbl_803C6CF8[0x710] < n) {
    }
    level = OSDisableInterrupts();
    base = *(u32*)&lbl_803C6CF8[0x708];
    ringStart = lbl_803C7A00.unk00;
    ringEnd = ringStart + lbl_803C7A00.unk04;
    if (base + n >= ringEnd) {
        len1 = ringEnd - base;
        start1 = ringStart;
        len2 = n - len1;
    } else {
        len1 = n;
        start1 = 0;
        len2 = 0;
    }
    OSRestoreInterrupts(level);
    if (n >= len1) {
        fn_800B03F4(base, n);
    } else {
        fn_800B03F4(base, len1);
        while (lbl_803C79D4.unk29 != 0) {
        }
        fn_800B03F4(start1, len2);
    }
    while (lbl_803C79D4.unk29 != 0) {
    }
    if (n != 0) {
        fn_800A6D10(n);
    }
    return TRUE;
}

void fn_800B0230(u32 start, u32 len) {
    u32 cursor;
    u32 limit;
    u32 first;
    u32 second;
    u32 end;

    if (len == 0) {
        return;
    }
    cursor = lbl_803C79D4.unk08;
    limit = lbl_803C79D4.unk04;
    if (cursor + len <= limit) {
        first = len;
        second = 0;
    } else {
        first = limit - cursor;
        second = len - first;
    }
    if (second != 0) {
        end = lbl_803C79D4.unk00 + second;
    } else {
        end = cursor + first;
    }
    if ((lbl_803C79D4.unk0C > cursor && end > lbl_803C79D4.unk0C) ||
        (lbl_803C79D4.unk0C < cursor && end > lbl_803C79D4.unk0C && second != 0)) {
        lbl_803C79D4.unk29 = 3;
        return;
    }
    lbl_803C79D4.unk24 = len;
    DCInvalidateRange((void*)start, first);
    lbl_803C79D4.unk29 = 2;
    ARQPostRequest((ARQRequest*)lbl_803C78C4, 0, 1, 1, cursor, start, first, (ARQCallback)fn_800B0390);
    DCInvalidateRange((void*)start, first);
    if (second != 0) {
        while (lbl_803C79D4.unk29 != 0) {
        }
        lbl_803C79D4.unk29 = 2;
        DCInvalidateRange((void*)(start + first), second);
        ARQPostRequest((ARQRequest*)(lbl_803C78C4 + 0x20), 0, 1, 1, lbl_803C79D4.unk00, start + first, second,
                       (ARQCallback)fn_800B0390);
        DCInvalidateRange((void*)(start + first), second);
    }
}

void fn_800B0390(void) {
    lbl_803C79D4.unk08 += lbl_803C79D4.unk24;
    if (lbl_803C79D4.unk08 >= lbl_803C79D4.unk04) {
        lbl_803C79D4.unk08 -= lbl_803C79D4.unk10;
    }
    lbl_803C79D4.unk14 -= lbl_803C79D4.unk24;
    lbl_803C79D4.unk20 += lbl_803C79D4.unk24;
    lbl_803C79D4.unk29 = 0;
}

void fn_800B03F4(u32 start, u32 len) {
    u32 cursor;
    u32 limit;
    u32 first;
    u32 second;
    u32 end;

    cursor = lbl_803C79D4.unk0C;
    limit = lbl_803C79D4.unk04;
    if (cursor + len <= limit) {
        first = len;
        second = 0;
    } else {
        first = limit - cursor;
        second = len - first;
    }
    if (second != 0) {
        end = lbl_803C79D4.unk00 + second;
    } else {
        end = cursor + len;
    }
    if ((cursor > lbl_803C79D4.unk08 && end > lbl_803C79D4.unk08 && second != 0) ||
        (cursor < lbl_803C79D4.unk08 && end > lbl_803C79D4.unk08)) {
        lbl_803C79D4.unk29 = 3;
        return;
    }
    while (lbl_803C79D4.unk14 > lbl_803C79D4.unk10) {
    }
    lbl_803C79D4.unk18 = len;
    lbl_803CC1A8 += 1;
    lbl_803C79D4.unk29 = 1;
    DCFlushRangeNoSync((void*)start, first);
    ARQPostRequest((ARQRequest*)lbl_803C7994, 0, 0, 1, start, lbl_803C79D4.unk0C, first,
                   (ARQCallback)fn_800B0580);
    if (second != 0) {
        while (lbl_803C79D4.unk29 != 0) {
        }
        lbl_803C79D4.unk29 = 1;
        DCFlushRangeNoSync((void*)(start + first), second);
        ARQPostRequest((ARQRequest*)(lbl_803C7994 + 0x20), 0, 0, 1, start + first, lbl_803C79D4.unk00, second,
                       (ARQCallback)fn_800B0580);
    }
}

void fn_800B0580(void) {
    lbl_803C79D4.unk0C += lbl_803C79D4.unk18;
    if (lbl_803C79D4.unk0C >= lbl_803C79D4.unk04) {
        lbl_803C79D4.unk0C -= lbl_803C79D4.unk10;
    }
    lbl_803C79D4.unk1C += lbl_803C79D4.unk18;
    lbl_803C79D4.unk14 += lbl_803C79D4.unk18;
    lbl_803C79D4.unk29 = 0;
}

void fn_800B05E4(s32 sel, u32 size) {
    u32 aligned;
    u32 base;
    u32 sizeAligned;

    lbl_803CC1A8 = 0;
    memset((void*)&lbl_803C79D4, 0, 0x2C);
    if (sel == -1) {
        u32 cap = *(u32*)data_803C6780;

        lbl_803C79D4.unk10 = (lbl_803CC1AC < cap) ? lbl_803CC1AC : cap;
    } else {
        lbl_803C79D4.unk10 = (lbl_803CC1AC < sel) ? lbl_803CC1AC : sel;
    }
    aligned = (lbl_803C79D4.unk10 + 31) & ~31;
    lbl_803C79D4.unk10 = aligned;
    base = (u32)fn_800A6418(aligned);
    lbl_803C79D4.unk00 = base;
    lbl_803C79D4.unk04 = base + lbl_803C79D4.unk10;
    lbl_803C79D4.unk0C = base;
    lbl_803C79D4.unk08 = base;
    ARQSetChunkSize(0x1000);
    ARQFlushQueue();
    sizeAligned = (size + 31) & ~31;
    lbl_803C7A00.unk04 = *(u32*)&lbl_803C6CF8[0x70C];
    lbl_803C7A00.unk00 = *(u32*)&lbl_803C6CF8[0x700] - *(u32*)&lbl_803C6CF8[0x70C];
    base = (u32)_OSAllocFromHeap(0x20, sizeAligned);
    lbl_803C7A00.unk08 = base;
    lbl_803C7A00.unk0C = base + sizeAligned;
    lbl_803C7A00.unk14 = base;
    lbl_803C7A00.unk10 = base;
    lbl_803C7A00.unk18 = sizeAligned;
    lbl_803C7A00.unk1C = 0;
    lbl_803C7A00.unk20 = 0;
}
