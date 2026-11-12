#include "common.h"

extern u8 *D_00428F4C __attribute__((section(".data")));
extern u8 *D_004213A0 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));
extern u8 D_00429AF8[] __attribute__((section(".data")));
extern u8 D_00429B10[] __attribute__((section(".data")));

extern u8 *func_0028BAA8();
extern u8 *func_002B24C8();
extern void func_00325370();
extern s64 GetTimerSystemTime();
extern void Res_RelocateOffsets();
extern void func_0024BED8();
extern void func_0026E7F0();
extern void func_0026EAE0();
extern void func_0026EB78();
extern void func_00249560();
extern void func_0024C120();
extern void *memset();

#define C D_00428F4C
#define CW(o) (*(u32 *)(C + (o)))
#define CP(o) (*(u8 **)(C + (o)))
#define C4 CP(4)
#define SUB(o) (C4 + (*(u32 *)(C4 + (o)) >> 2) * 4)
#define SPP (*(u8 **)sp)
#define VW(o) (*(u32 *)(SPP + (o)))
#define RELOC(o) do { u8 *v_ = SUB(o); SPP = v_; Res_RelocateOffsets(sp, v_, v_); } while (0)

u8 *func_003ECF28(s32 arg0) {
    u8 sp[0x10] __attribute__((aligned(16)));
    s32 i;
    s32 a1;
    s32 v0;
    u8 *p;

    *(u32 *)sp = 0;
    C = func_0028BAA8(500);
    memset(C, 0, 500);
    CW(0x184) = *(u32 *)(D_3876A4 + 0x47C);
    CW(0x178) = *(u32 *)(D_3876A4 + 0x480);
    CP(0) = D_004213A0 + (*(u32 *)(D_004213A0 + arg0 * 4) >> 2) * 4;
    CP(4) = func_002B24C8(CP(0), 0, 0);
    func_00325370((s32)GetTimerSystemTime());
    RELOC(0x10);
    CP(0xC8) = SPP;
    RELOC(0x38);
    CW(0xEC) = VW(0x10);
    CW(0xDC) = VW(0x10) + 0x40;
    RELOC(0x3C);
    func_0024BED8(SUB(0x68), VW(0x10));
    CW(0xF4) = VW(0x10) + 0x40;
    RELOC(0x30);
    CW(0xE4) = VW(0x10);
    CW(0xE8) = VW(0x10) + 0x40;
    RELOC(0x34);
    CP(0xD4) = SPP;
    CW(0xE0) = VW(0x10);
    CW(0x11C) = VW(0x10) + 0xC0;
    if (CW(0x184) == 1) {
        CW(0x10C) = *(u32 *)(CP(0xD4) + 0x10) + 0x100;
        CW(0x118) = *(u32 *)(CP(0xD4) + 0x10) + 0x140;
    } else {
        CW(0x10C) = *(u32 *)(CP(0xD4) + 0x10) + 0x40;
        CW(0x118) = *(u32 *)(CP(0xD4) + 0x10) + 0x80;
    }
    RELOC(0x14);
    CW(0xF0) = VW(0x10);
    CW(0x138) = VW(0x10);
    RELOC(0x70);
    CW(0xFC) = VW(0x10);
    RELOC(0x74);
    CW(0x100) = VW(0x10);
    RELOC(0x78);
    CW(0xF8) = VW(0x10);
    func_0026E7F0(C + 0xA0, SUB(4), C + 0xDC);
    func_0026EAE0(C + 0xA0, 0x3C);
    RELOC(8);
    CW(0x130) = VW(0x10);
    CW(0x134) = VW(0x10) + 0x40;
    RELOC(0xC);
    CW(0x12C) = VW(0x10);
    RELOC(0x2C);
    CW(0x108) = VW(0x10);
    CW(0x110) = VW(0x10) + 0x40;
    CW(0x114) = VW(0x10) + 0x80;
    RELOC(0x7C);
    CW(0x128) = VW(0x10);
    func_0026E7F0(C + 0x78, SUB(0x54), C + 0x108);
    RELOC(0x44);
    CW(0x144) = VW(0x10);
    func_0026E7F0(C + 0x28, SUB(0x48), C + 0x144);
    func_0026EAE0(C + 0x28, 0x3C);
    RELOC(0x24);
    CP(0xCC) = SPP;
    CW(0x148) = VW(0x10);
    CW(0x150) = VW(0x10);
    CW(0x14C) = VW(0x10);
    RELOC(0x28);
    CP(0xD0) = SPP;
    RELOC(0x20);
    CW(0x154) = VW(0x10);
    CW(0x158) = VW(0x10);
    CW(0x15C) = VW(0x10);
    RELOC(0x1C);
    CW(0x168) = VW(0x10);
    CW(0x16C) = VW(0x10);
    CW(0x170) = VW(0x10);
    func_0026E7F0(C + 0x50, SUB(0x18), C + 0x148);
    func_0026EAE0(C + 0x50, 0x3C);
    CP(0xC) = SUB(0x50);
    CP(8) = SUB(0x4C);
    CP(0x10) = SUB(0x5C);
    CP(0x14) = SUB(0x60);
    CP(0x18) = SUB(0x80);
    p = SUB(0x6C);
    CW(0x1BC) = *(u32 *)p;
    CP(0x1B4) = p + 4;
    CP(0x1AC) = SUB(0x58) + 4;
    CW(0x1B0) = *(u32 *)SUB(0x58);
    CP(0xD8) = SUB(0x84);
    Res_RelocateOffsets(C + 0xD8, CP(0xD8), CP(0xD8));
    p = SUB(0x88);
    CW(0x1C0) = *(u32 *)p;
    CP(0x1C4) = p + 4;
    CW(0x1C8) = 0;
    for (i = 0; i < 4; i++) {
        func_00249560(C + (i << 2) + 0x1CC);
    }
    CW(0x17C) = -1;
    CW(0x174) = CW(0x174) | 0x10;
    a1 = *(s32 *)(D_3876A4 + 0x484);
    if (a1 < (s32)*(u32 *)(CP(0x1AC) + (CW(0x184) << 3) + 4) - 1) {
        if (a1 > 0) {
            CW(0x188) = a1 - 1;
            CW(0x18C) = 1;
        } else {
            CW(0x188) = 0;
            CW(0x18C) = 0;
        }
    } else {
        CW(0x188) = a1 - 2;
        CW(0x18C) = 2;
    }
    if (*(s32 *)(D_3876A4 + 0x488) >= 2) {
        CW(0x1A0) = 1;
        CW(0x198) = 0x65;
        CW(0x180) = 1;
        func_0024C120(0x65);
        func_0026EB78(C + 0xA0, D_00429AF8);
        func_0026EAE0(C + 0x78, 0x3C);
        func_0026EB78(C + 0x78, D_00429AF8);
        func_0026EB78(C + 0x50, D_00429B10);
        *(u32 *)(D_387F2C + 0x608) = *(u32 *)(D_387F2C + 0x608) | (1 << *(s32 *)(D_3876A4 + 0x484));
        if (*(s16 *)(D_387F2C + 0x27FE) <= 0) {
            a1 = 0;
            for (i = 0; i < 2; i++) {
                if (i != 1) {
                    a1 += *(s32 *)(CP(0x1AC) + (i << 3) + 4);
                }
            }
            v0 = (1 << a1) - 1;
            if ((*(u32 *)(D_387F2C + 0x608) & v0) == (u32)v0) {
                CW(0x174) = CW(0x174) | 0x20;
            }
        }
    }
    *(u32 *)(D_3876A4 + 0x488) = 0;
    CP(0x1C) = func_0028BAA8(0xD800);
    CP(0x20) = func_0028BAA8(0x10560);
    CW(0x1EC) = 4;
    return C;
}
