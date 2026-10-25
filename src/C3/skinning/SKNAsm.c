#include "C3/skinning/SKNAsm.h"

asm void SKN1Vecs16Norms16(register Mtx34 m, register s16* srcBase, register s16* dstBase, register u32 count) {
    nofralloc
	stwu r1, -0x40(r1)
	stfd f14, 0x8(r1)
	stfd f15, 0x10(r1)
	subi r6, r6, 0x1
	stfd f16, 0x18(r1)
	stfd f17, 0x20(r1)
	stfd f18, 0x28(r1)
	mtctr r6
	psq_l f0, 0x0(r3), 0, 0
	subi r4, r4, 0x8
	psq_l f1, 0x8(r3), 1, 0
	subi r5, r5, 0x4
	psq_l f6, 0x24(r3), 0, 0
	psq_lu f8, 0x8(r4), 0, 7
	psq_l f7, 0x2c(r3), 1, 0
	psq_lu f9, 0x8(r4), 0, 7
	ps_madds0 f11, f0, f8, f6
	psq_l f2, 0xc(r3), 0, 0
	ps_madds0 f12, f1, f8, f7
	psq_l f3, 0x14(r3), 1, 0
	ps_muls1 f13, f0, f9
	psq_lu f10, 0x8(r4), 0, 7
	ps_muls1 f14, f1, f9
	psq_l f5, 0x20(r3), 1, 0
	ps_madds1 f11, f2, f8, f11
	ps_madds1 f12, f3, f8, f12
	psq_l f4, 0x18(r3), 0, 0
	ps_madds0 f13, f2, f10, f13
	psq_lu f8, 0x8(r4), 0, 7
	ps_madds0 f14, f3, f10, f14
	ps_madds0 f15, f4, f9, f11
	ps_madds0 f16, f5, f9, f12
	psq_lu f9, 0x8(r4), 0, 7
	ps_madds1 f17, f4, f10, f13
	ps_madds1 f18, f5, f10, f14
	psq_lu f10, 0x8(r4), 0, 7
L_800BFF20:
	ps_madds0 f11, f0, f8, f6
	psq_stu f15, 0x4(r5), 0, 7
	ps_madds0 f12, f1, f8, f7
	psq_stu f16, 0x8(r5), 1, 7
	ps_muls1 f13, f0, f9
	psq_stu f17, 0x4(r5), 0, 7
	ps_muls1 f14, f1, f9
	psq_stu f18, 0x8(r5), 1, 7
	ps_madds1 f11, f2, f8, f11
	ps_madds1 f12, f3, f8, f12
	psq_lu f8, 0x8(r4), 0, 7
	ps_madds0 f13, f2, f10, f13
	ps_madds0 f14, f3, f10, f14
	ps_madds0 f15, f4, f9, f11
	ps_madds0 f16, f5, f9, f12
	psq_lu f9, 0x8(r4), 0, 7
	ps_madds1 f17, f4, f10, f13
	ps_madds1 f18, f5, f10, f14
	psq_lu f10, 0x8(r4), 0, 7
	bdnz L_800BFF20
	psq_stu f15, 0x4(r5), 0, 7
	psq_stu f16, 0x8(r5), 1, 7
	psq_stu f17, 0x4(r5), 0, 7
	psq_stu f18, 0x8(r5), 1, 7
	lfd f14, 0x8(r1)
	lfd f15, 0x10(r1)
	lfd f16, 0x18(r1)
	lfd f17, 0x20(r1)
	lfd f18, 0x28(r1)
	addi r1, r1, 0x40
	blr
}

asm void fn_800BFF9C(register Mtx34 m, register s16* srcBase, register s16* dstBase, register u32 count) {
    nofralloc
	stwu r1, -0x40(r1)
	stfd f14, 0x8(r1)
	stfd f15, 0x10(r1)
	subi r6, r6, 0x1
	stfd f16, 0x18(r1)
	stfd f17, 0x20(r1)
	stfd f18, 0x28(r1)
	mtctr r6
	psq_l f0, 0x0(r3), 0, 0
	subi r4, r4, 0x4
	psq_l f1, 0x8(r3), 1, 0
	subi r5, r5, 0x2
	psq_l f6, 0x24(r3), 0, 0
	psq_lu f8, 0x4(r4), 0, 6
	psq_l f7, 0x2c(r3), 1, 0
	psq_lu f9, 0x4(r4), 0, 6
	ps_madds0 f11, f0, f8, f6
	psq_l f2, 0xc(r3), 0, 0
	ps_madds0 f12, f1, f8, f7
	psq_l f3, 0x14(r3), 1, 0
	ps_muls1 f13, f0, f9
	psq_lu f10, 0x4(r4), 0, 6
	ps_muls1 f14, f1, f9
	psq_l f5, 0x20(r3), 1, 0
	ps_madds1 f11, f2, f8, f11
	ps_madds1 f12, f3, f8, f12
	psq_l f4, 0x18(r3), 0, 0
	ps_madds0 f13, f2, f10, f13
	psq_lu f8, 0x4(r4), 0, 6
	ps_madds0 f14, f3, f10, f14
	ps_madds0 f15, f4, f9, f11
	ps_madds0 f16, f5, f9, f12
	psq_lu f9, 0x4(r4), 0, 6
	ps_madds1 f17, f4, f10, f13
	ps_madds1 f18, f5, f10, f14
	psq_lu f10, 0x4(r4), 0, 6
L_800C002C:
	ps_madds0 f11, f0, f8, f6
	psq_stu f15, 0x2(r5), 0, 6
	ps_madds0 f12, f1, f8, f7
	psq_stu f16, 0x4(r5), 1, 6
	ps_muls1 f13, f0, f9
	psq_stu f17, 0x2(r5), 0, 6
	ps_muls1 f14, f1, f9
	psq_stu f18, 0x4(r5), 1, 6
	ps_madds1 f11, f2, f8, f11
	ps_madds1 f12, f3, f8, f12
	psq_lu f8, 0x4(r4), 0, 6
	ps_madds0 f13, f2, f10, f13
	ps_madds0 f14, f3, f10, f14
	ps_madds0 f15, f4, f9, f11
	ps_madds0 f16, f5, f9, f12
	psq_lu f9, 0x4(r4), 0, 6
	ps_madds1 f17, f4, f10, f13
	ps_madds1 f18, f5, f10, f14
	psq_lu f10, 0x4(r4), 0, 6
	bdnz L_800C002C
	psq_stu f15, 0x2(r5), 0, 6
	psq_stu f16, 0x4(r5), 1, 6
	psq_stu f17, 0x2(r5), 0, 6
	psq_stu f18, 0x4(r5), 1, 6
	lfd f14, 0x8(r1)
	lfd f15, 0x10(r1)
	lfd f16, 0x18(r1)
	lfd f17, 0x20(r1)
	lfd f18, 0x28(r1)
	addi r1, r1, 0x40
	blr
}

asm void SKN2Vecs16Norms16NoTouch(register Mtx34 m0, register Mtx34 m1, register u8* wtBase, register s16* srcBase, register s16* dstBase, register u32 count) {
    nofralloc
	stwu r1, -0xa0(r1)
	stfd f14, 0x8(r1)
	subi r9, r8, 0x1
	stfd f15, 0x10(r1)
	stfd f16, 0x18(r1)
	stfd f17, 0x20(r1)
	stfd f18, 0x28(r1)
	stfd f19, 0x30(r1)
	stfd f20, 0x38(r1)
	stfd f21, 0x40(r1)
	stfd f22, 0x48(r1)
	stfd f23, 0x50(r1)
	stfd f24, 0x58(r1)
	stfd f25, 0x60(r1)
	stfd f26, 0x68(r1)
	stfd f27, 0x70(r1)
	mtctr r9
	psq_l f0, 0x0(r3), 0, 0
	subi r6, r6, 0x8
	psq_l f1, 0x8(r3), 1, 0
	subi r7, r7, 0x4
	psq_l f6, 0x24(r3), 0, 0
	subi r5, r5, 0x2
	psq_lu f8, 0x8(r6), 0, 7
	psq_l f7, 0x2c(r3), 1, 0
	psq_lu f9, 0x8(r6), 0, 7
	psq_lu f27, 0x2(r5), 0, 5
	ps_madds0 f15, f0, f8, f6
	psq_l f2, 0xc(r3), 0, 0
	ps_madds0 f16, f1, f8, f7
	psq_l f3, 0x14(r3), 1, 0
	ps_muls1 f17, f0, f9
	psq_lu f10, 0x8(r6), 0, 7
	ps_muls1 f18, f1, f9
	psq_l f5, 0x20(r3), 1, 0
	ps_madds1 f15, f2, f8, f15
	psq_l f19, 0x0(r4), 0, 0
	ps_madds1 f16, f3, f8, f16
	psq_l f4, 0x18(r3), 0, 0
	ps_madds0 f17, f2, f10, f17
	psq_l f20, 0x8(r4), 1, 0
	ps_madds0 f18, f3, f10, f18
	psq_l f21, 0xc(r4), 0, 0
	ps_madds0 f15, f4, f9, f15
	psq_l f22, 0x14(r4), 1, 0
	ps_madds0 f16, f5, f9, f16
	psq_l f23, 0x18(r4), 0, 0
	ps_madds1 f17, f4, f10, f17
	psq_l f24, 0x20(r4), 1, 0
	ps_madds1 f18, f5, f10, f18
	psq_l f25, 0x24(r4), 0, 0
	ps_muls0 f15, f15, f27
	psq_l f26, 0x2c(r4), 1, 0
	ps_muls0 f16, f16, f27
	ps_muls0 f17, f17, f27
	ps_muls0 f18, f18, f27
	ps_madds0 f11, f19, f8, f25
	ps_madds0 f12, f20, f8, f26
	ps_muls1 f13, f19, f9
	ps_muls1 f14, f20, f9
	ps_madds1 f11, f21, f8, f11
	ps_madds1 f12, f22, f8, f12
	ps_madds0 f13, f21, f10, f13
	psq_lu f8, 0x8(r6), 0, 7
	ps_madds0 f14, f22, f10, f14
	ps_madds0 f11, f23, f9, f11
	ps_madds0 f12, f24, f9, f12
	ps_madds1 f13, f23, f10, f13
	ps_madds1 f14, f24, f10, f14
	psq_lu f9, 0x8(r6), 0, 7
	ps_madds1 f11, f11, f27, f15
	ps_madds1 f12, f12, f27, f16
	ps_madds1 f13, f13, f27, f17
	psq_lu f10, 0x8(r6), 0, 7
	ps_madds1 f14, f14, f27, f18
L_800C01D4:
	ps_madds0 f15, f0, f8, f6
	psq_stu f11, 0x4(r7), 0, 7
	ps_madds0 f16, f1, f8, f7
	psq_stu f12, 0x8(r7), 1, 7
	ps_muls1 f17, f0, f9
	psq_stu f13, 0x4(r7), 0, 7
	ps_muls1 f18, f1, f9
	psq_stu f14, 0x8(r7), 1, 7
	ps_madds1 f15, f2, f8, f15
	ps_madds1 f16, f3, f8, f16
	ps_madds0 f17, f2, f10, f17
	ps_madds0 f18, f3, f10, f18
	ps_madds0 f15, f4, f9, f15
	ps_madds0 f16, f5, f9, f16
	psq_lu f27, 0x2(r5), 0, 5
	ps_madds1 f17, f4, f10, f17
	ps_madds1 f18, f5, f10, f18
	ps_muls0 f15, f15, f27
	ps_muls0 f16, f16, f27
	ps_muls0 f17, f17, f27
	ps_muls0 f18, f18, f27
	ps_madds0 f11, f19, f8, f25
	ps_madds0 f12, f20, f8, f26
	ps_muls1 f13, f19, f9
	ps_muls1 f14, f20, f9
	ps_madds1 f11, f21, f8, f11
	ps_madds1 f12, f22, f8, f12
	ps_madds0 f13, f21, f10, f13
	psq_lu f8, 0x8(r6), 0, 7
	ps_madds0 f14, f22, f10, f14
	ps_madds0 f11, f23, f9, f11
	ps_madds0 f12, f24, f9, f12
	ps_madds1 f13, f23, f10, f13
	ps_madds1 f14, f24, f10, f14
	psq_lu f9, 0x8(r6), 0, 7
	ps_madds1 f11, f11, f27, f15
	ps_madds1 f12, f12, f27, f16
	ps_madds1 f13, f13, f27, f17
	psq_lu f10, 0x8(r6), 0, 7
	ps_madds1 f14, f14, f27, f18
	bdnz L_800C01D4
	psq_stu f11, 0x4(r7), 0, 7
	psq_stu f12, 0x8(r7), 1, 7
	psq_stu f13, 0x4(r7), 0, 7
	psq_stu f14, 0x8(r7), 1, 7
	lfd f14, 0x8(r1)
	lfd f15, 0x10(r1)
	lfd f16, 0x18(r1)
	lfd f17, 0x20(r1)
	lfd f18, 0x28(r1)
	lfd f19, 0x30(r1)
	lfd f20, 0x38(r1)
	lfd f21, 0x40(r1)
	lfd f22, 0x48(r1)
	lfd f23, 0x50(r1)
	lfd f24, 0x58(r1)
	lfd f25, 0x60(r1)
	lfd f26, 0x68(r1)
	lfd f27, 0x70(r1)
	addi r1, r1, 0xa0
	blr
}

asm void fn_800C02C8(register Mtx34 m0, register Mtx34 m1, register u8* wtBase, register s16* srcBase, register s16* dstBase, register u32 count) {
    nofralloc
	stwu r1, -0xa0(r1)
	stfd f14, 0x8(r1)
	subi r9, r8, 0x1
	stfd f15, 0x10(r1)
	stfd f16, 0x18(r1)
	stfd f17, 0x20(r1)
	stfd f18, 0x28(r1)
	stfd f19, 0x30(r1)
	stfd f20, 0x38(r1)
	stfd f21, 0x40(r1)
	stfd f22, 0x48(r1)
	stfd f23, 0x50(r1)
	stfd f24, 0x58(r1)
	stfd f25, 0x60(r1)
	stfd f26, 0x68(r1)
	stfd f27, 0x70(r1)
	mtctr r9
	psq_l f0, 0x0(r3), 0, 0
	subi r6, r6, 0x4
	psq_l f1, 0x8(r3), 1, 0
	subi r7, r7, 0x2
	psq_l f6, 0x24(r3), 0, 0
	subi r5, r5, 0x2
	psq_lu f8, 0x4(r6), 0, 6
	psq_l f7, 0x2c(r3), 1, 0
	psq_lu f9, 0x4(r6), 0, 6
	psq_lu f27, 0x2(r5), 0, 5
	ps_madds0 f15, f0, f8, f6
	psq_l f2, 0xc(r3), 0, 0
	ps_madds0 f16, f1, f8, f7
	psq_l f3, 0x14(r3), 1, 0
	ps_muls1 f17, f0, f9
	psq_lu f10, 0x4(r6), 0, 6
	ps_muls1 f18, f1, f9
	psq_l f5, 0x20(r3), 1, 0
	ps_madds1 f15, f2, f8, f15
	psq_l f19, 0x0(r4), 0, 0
	ps_madds1 f16, f3, f8, f16
	psq_l f4, 0x18(r3), 0, 0
	ps_madds0 f17, f2, f10, f17
	psq_l f20, 0x8(r4), 1, 0
	ps_madds0 f18, f3, f10, f18
	psq_l f21, 0xc(r4), 0, 0
	ps_madds0 f15, f4, f9, f15
	psq_l f22, 0x14(r4), 1, 0
	ps_madds0 f16, f5, f9, f16
	psq_l f23, 0x18(r4), 0, 0
	ps_madds1 f17, f4, f10, f17
	psq_l f24, 0x20(r4), 1, 0
	ps_madds1 f18, f5, f10, f18
	psq_l f25, 0x24(r4), 0, 0
	ps_muls0 f15, f15, f27
	psq_l f26, 0x2c(r4), 1, 0
	ps_muls0 f16, f16, f27
	ps_muls0 f17, f17, f27
	ps_muls0 f18, f18, f27
	ps_madds0 f11, f19, f8, f25
	ps_madds0 f12, f20, f8, f26
	ps_muls1 f13, f19, f9
	ps_muls1 f14, f20, f9
	ps_madds1 f11, f21, f8, f11
	ps_madds1 f12, f22, f8, f12
	ps_madds0 f13, f21, f10, f13
	psq_lu f8, 0x4(r6), 0, 6
	ps_madds0 f14, f22, f10, f14
	ps_madds0 f11, f23, f9, f11
	ps_madds0 f12, f24, f9, f12
	ps_madds1 f13, f23, f10, f13
	ps_madds1 f14, f24, f10, f14
	psq_lu f9, 0x4(r6), 0, 6
	ps_madds1 f11, f11, f27, f15
	ps_madds1 f12, f12, f27, f16
	ps_madds1 f13, f13, f27, f17
	psq_lu f10, 0x4(r6), 0, 6
	ps_madds1 f14, f14, f27, f18
L_800C03F4:
	ps_madds0 f15, f0, f8, f6
	psq_stu f11, 0x2(r7), 0, 6
	ps_madds0 f16, f1, f8, f7
	psq_stu f12, 0x4(r7), 1, 6
	ps_muls1 f17, f0, f9
	psq_stu f13, 0x2(r7), 0, 6
	ps_muls1 f18, f1, f9
	psq_stu f14, 0x4(r7), 1, 6
	ps_madds1 f15, f2, f8, f15
	ps_madds1 f16, f3, f8, f16
	ps_madds0 f17, f2, f10, f17
	ps_madds0 f18, f3, f10, f18
	ps_madds0 f15, f4, f9, f15
	ps_madds0 f16, f5, f9, f16
	psq_lu f27, 0x2(r5), 0, 5
	ps_madds1 f17, f4, f10, f17
	ps_madds1 f18, f5, f10, f18
	ps_muls0 f15, f15, f27
	ps_muls0 f16, f16, f27
	ps_muls0 f17, f17, f27
	ps_muls0 f18, f18, f27
	ps_madds0 f11, f19, f8, f25
	ps_madds0 f12, f20, f8, f26
	ps_muls1 f13, f19, f9
	ps_muls1 f14, f20, f9
	ps_madds1 f11, f21, f8, f11
	ps_madds1 f12, f22, f8, f12
	ps_madds0 f13, f21, f10, f13
	psq_lu f8, 0x4(r6), 0, 6
	ps_madds0 f14, f22, f10, f14
	ps_madds0 f11, f23, f9, f11
	ps_madds0 f12, f24, f9, f12
	ps_madds1 f13, f23, f10, f13
	ps_madds1 f14, f24, f10, f14
	psq_lu f9, 0x4(r6), 0, 6
	ps_madds1 f11, f11, f27, f15
	ps_madds1 f12, f12, f27, f16
	ps_madds1 f13, f13, f27, f17
	psq_lu f10, 0x4(r6), 0, 6
	ps_madds1 f14, f14, f27, f18
	bdnz L_800C03F4
	psq_stu f11, 0x2(r7), 0, 6
	psq_stu f12, 0x4(r7), 1, 6
	psq_stu f13, 0x2(r7), 0, 6
	psq_stu f14, 0x4(r7), 1, 6
	lfd f14, 0x8(r1)
	lfd f15, 0x10(r1)
	lfd f16, 0x18(r1)
	lfd f17, 0x20(r1)
	lfd f18, 0x28(r1)
	lfd f19, 0x30(r1)
	lfd f20, 0x38(r1)
	lfd f21, 0x40(r1)
	lfd f22, 0x48(r1)
	lfd f23, 0x50(r1)
	lfd f24, 0x58(r1)
	lfd f25, 0x60(r1)
	lfd f26, 0x68(r1)
	lfd f27, 0x70(r1)
	addi r1, r1, 0xa0
	blr
}

asm void SKNAccVecs16Norms16Iu161(register Mtx34 m, register u16 count, register s16* srcBase, register s16* dstBase, register u16* indices, register u8* weights) {
    nofralloc
	stwu r1, -0xa0(r1)
	subi r7, r7, 0x2
	stfd f14, 0x8(r1)
	lhzu r9, 0x2(r7)
	stfd f15, 0x10(r1)
	stfd f16, 0x18(r1)
	add r11, r9, r9
	stfd f17, 0x20(r1)
	add r9, r9, r11
	stfd f18, 0x28(r1)
	add r9, r9, r9
	stfd f19, 0x30(r1)
	add r9, r9, r9
	stfd f20, 0x38(r1)
	add r9, r9, r9
	stfd f21, 0x40(r1)
	add r10, r9, r6
	stfd f22, 0x48(r1)
	subi r8, r8, 0x1
	stfd f23, 0x50(r1)
	mtctr r4
	psq_l f0, 0x0(r3), 0, 0
	subi r5, r5, 0x8
	psq_l f1, 0x8(r3), 1, 0
	psq_l f6, 0x24(r3), 0, 0
	psq_l f7, 0x2c(r3), 1, 0
	psq_lu f8, 0x8(r5), 0, 7
	psq_lu f9, 0x8(r5), 0, 7
	psq_l f2, 0xc(r3), 0, 0
	psq_l f3, 0x14(r3), 1, 0
	psq_lu f10, 0x8(r5), 0, 7
	psq_l f5, 0x20(r3), 1, 0
	psq_l f4, 0x18(r3), 0, 0
L_800C056C:
	ps_madds0 f11, f0, f8, f6
	psq_lu f23, 0x1(r8), 1, 5
	ps_madds0 f12, f1, f8, f7
	ps_muls1 f13, f0, f9
	psq_l f19, 0x0(r10), 0, 7
	ps_muls1 f14, f1, f9
	ps_madds1 f11, f2, f8, f11
	ps_madds1 f12, f3, f8, f12
	psq_l f20, 0x8(r10), 1, 7
	ps_madds0 f13, f2, f10, f13
	ps_madds0 f14, f3, f10, f14
	psq_l f21, 0xc(r10), 0, 7
	ps_madds0 f15, f4, f9, f11
	ps_madds0 f16, f5, f9, f12
	lhzu r9, 0x2(r7)
	ps_madds1 f17, f4, f10, f13
	ps_madds1 f18, f5, f10, f14
	psq_l f22, 0x14(r10), 1, 7
	ps_madds0 f19, f15, f23, f19
	psq_lu f8, 0x8(r5), 0, 7
	ps_madds0 f20, f16, f23, f20
	psq_lu f9, 0x8(r5), 0, 7
	ps_madds0 f21, f17, f23, f21
	psq_lu f10, 0x8(r5), 0, 7
	ps_madds0 f22, f18, f23, f22
	add r11, r9, r9
	psq_st f19, 0x0(r10), 0, 7
	add r9, r9, r11
	psq_st f20, 0x8(r10), 1, 7
	add r9, r9, r9
	psq_st f21, 0xc(r10), 0, 7
	add r9, r9, r9
	psq_st f22, 0x14(r10), 1, 7
	add r9, r9, r9
	dcbst r0, r10
	add r10, r9, r6
	bdnz L_800C056C
	lfd f14, 0x8(r1)
	lfd f15, 0x10(r1)
	lfd f16, 0x18(r1)
	lfd f17, 0x20(r1)
	lfd f18, 0x28(r1)
	lfd f19, 0x30(r1)
	lfd f20, 0x38(r1)
	lfd f21, 0x40(r1)
	lfd f22, 0x48(r1)
	lfd f23, 0x50(r1)
	addi r1, r1, 0xa0
	blr
}

asm void SKNAccVecs16Norms16Iu162(register Mtx34 m, register u16 count, register s16* srcBase, register s16* dstBase, register u16* indices, register u8* weights) {
    nofralloc
	stwu r1, -0xa0(r1)
	subi r7, r7, 0x2
	stfd f14, 0x8(r1)
	lhzu r9, 0x2(r7)
	stfd f15, 0x10(r1)
	stfd f16, 0x18(r1)
	add r11, r9, r9
	stfd f17, 0x20(r1)
	add r9, r9, r11
	stfd f18, 0x28(r1)
	add r9, r9, r9
	stfd f19, 0x30(r1)
	add r9, r9, r9
	stfd f20, 0x38(r1)
	add r10, r9, r6
	stfd f21, 0x40(r1)
	subi r8, r8, 0x1
	stfd f22, 0x48(r1)
	stfd f23, 0x50(r1)
	mtctr r4
	psq_l f0, 0x0(r3), 0, 0
	subi r5, r5, 0x4
	psq_l f1, 0x8(r3), 1, 0
	psq_l f6, 0x24(r3), 0, 0
	psq_l f7, 0x2c(r3), 1, 0
	psq_lu f8, 0x4(r5), 0, 6
	psq_lu f9, 0x4(r5), 0, 6
	psq_l f2, 0xc(r3), 0, 0
	psq_l f3, 0x14(r3), 1, 0
	psq_lu f10, 0x4(r5), 0, 6
	psq_l f5, 0x20(r3), 1, 0
	psq_l f4, 0x18(r3), 0, 0
L_800C06B0:
	ps_madds0 f11, f0, f8, f6
	psq_lu f23, 0x1(r8), 1, 5
	ps_madds0 f12, f1, f8, f7
	ps_muls1 f13, f0, f9
	psq_l f19, 0x0(r10), 0, 6
	ps_muls1 f14, f1, f9
	ps_madds1 f11, f2, f8, f11
	ps_madds1 f12, f3, f8, f12
	psq_l f20, 0x4(r10), 1, 6
	ps_madds0 f13, f2, f10, f13
	ps_madds0 f14, f3, f10, f14
	psq_l f21, 0x6(r10), 0, 6
	ps_madds0 f15, f4, f9, f11
	ps_madds0 f16, f5, f9, f12
	lhzu r9, 0x2(r7)
	ps_madds1 f17, f4, f10, f13
	ps_madds1 f18, f5, f10, f14
	psq_l f22, 0xa(r10), 1, 6
	ps_madds0 f19, f15, f23, f19
	psq_lu f8, 0x4(r5), 0, 6
	ps_madds0 f20, f16, f23, f20
	psq_lu f9, 0x4(r5), 0, 6
	ps_madds0 f21, f17, f23, f21
	psq_lu f10, 0x4(r5), 0, 6
	ps_madds0 f22, f18, f23, f22
	add r11, r9, r9
	psq_st f19, 0x0(r10), 0, 6
	add r9, r9, r11
	psq_st f20, 0x4(r10), 1, 6
	add r9, r9, r9
	psq_st f21, 0x6(r10), 0, 6
	add r9, r9, r9
	psq_st f22, 0xa(r10), 1, 6
	dcbst r0, r10
	add r10, r9, r6
	bdnz L_800C06B0
	lfd f14, 0x8(r1)
	lfd f15, 0x10(r1)
	lfd f16, 0x18(r1)
	lfd f17, 0x20(r1)
	lfd f18, 0x28(r1)
	lfd f19, 0x30(r1)
	lfd f20, 0x38(r1)
	lfd f21, 0x40(r1)
	lfd f22, 0x48(r1)
	lfd f23, 0x50(r1)
	addi r1, r1, 0xa0
	blr
}
