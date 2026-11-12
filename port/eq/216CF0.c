#include "common.h"
extern f32 sqrtf(f32 x);
extern f32 fabsf(f32 x);
extern f32 D_00385AD8;
extern f32 D_00385ADC;
extern s32 func_002113C0();
extern s32 func_00211310();
extern s32 BtlChar_GetSnapPos();
extern s32 BtlChar_GetSnapDelta();
extern s32 func_00210808();
extern s32 func_00312650();
extern s32 func_003126C8();
extern void func_00312680(void *dst, void *src, f32 scale);
extern s32 func_00312638();
extern u8 *BtlChar_GetPos();
extern f32 BtlCharApi_GetHeight();
extern f32 func_00210D50();
extern f32 func_002086B0(s32 a);
extern f32 func_00210D10();
extern f32 sceVu0InnerProduct();

s32 func_00216CF0(u8 *c) {
    u8 sp[0x130];
    s32 flag;
    f32 f0, f1, f2, f12, f20, sum, inv;
    u8 *pos0, *pos1;

    func_002113C0(c, 4, 0x80, 0);
    func_002113C0(c, 4, 0x100, 0);
    if (func_00211310(c, 3, 0x800)) return 0;
    if (func_00211310(c, 10, 8)) return 0;
    flag = (func_00211310(c, 0, 1) == 0);
    if (func_00211310(c, 1, 0x40)) flag = 1;
    if (func_00211310(c, 10, 4)) flag = 1;
    BtlChar_GetSnapPos(c, sp + 0x40, 0);
    func_00210808(c, sp + 0x50, 0);
    func_00312650(sp + 0x10, sp + 0x50, sp + 0x40);
    if (flag) {
        *(f32 *)(sp + 0x60) = BtlCharApi_GetHeight(*(u32 *)(c + 0x1534));
        f1 = func_00210D50(c);
        f0 = *(f32 *)(sp + 0x60);
        f2 = *(f32 *)(sp + 0x14);
        *(f32 *)(sp + 0x64) = f1;
        if (f2 < -f0) return 0;
        if (f1 < f2) return 0;
    }
    func_003126C8(sp + 0x20, sp + 0x10);
    f2 = D_00385AD8;
    *(s32 *)(sp + 0x24) = 0;
    sum = *(f32 *)(sp + 0x20) * *(f32 *)(sp + 0x20) + *(f32 *)(sp + 0x28) * *(f32 *)(sp + 0x28);
    if (sum < f2) return 0;
    f1 = sqrtf(fabsf(sum));
    inv = 1.0f / f1;
    *(f32 *)(sp + 0x28) = *(f32 *)(sp + 0x28) * inv;
    *(f32 *)(sp + 0x20) = *(f32 *)(sp + 0x20) * inv;
    func_00210808(c, sp + 0x80, 0);
    func_00210808(c, sp + 0x90, 1);
    func_00312650(sp + 0x70, sp + 0x90, sp + 0x80);
    *(s32 *)(sp + 0x74) = 0;
    if (sceVu0InnerProduct(sp + 0x70, sp + 0x20) < 0.0f)
        func_003126C8(sp, sp + 0x80);
    else
        func_003126C8(sp, sp + 0x90);
    *(s32 *)(sp + 0x34) = 0;
    *(f32 *)(sp + 0x30) = -*(f32 *)(sp + 0x20);
    *(f32 *)(sp + 0x38) = -*(f32 *)(sp + 0x28);
    f0 = sceVu0InnerProduct(sp + 0x30, sp);
    *(f32 *)(sp + 0x3C) = -f0;
    f0 = func_002086B0(*(u32 *)(c + 0x1534));
    *(f32 *)(sp + 0x3C) = *(f32 *)(sp + 0x3C) - f0;
    f0 = func_00210D10(c);
    *(f32 *)(sp + 0x3C) = *(f32 *)(sp + 0x3C) - f0;
    BtlChar_GetSnapDelta(c, sp + 0xA0, 0, 1);
    func_00210808(c, sp + 0xC0, 1);
    func_00312650(sp + 0xB0, sp + 0xC0, sp);
    *(s32 *)(sp + 0xA4) = 0;
    *(s32 *)(sp + 0xB4) = 0;
    *(f32 *)(sp + 0x60) = sceVu0InnerProduct(sp + 0x20, sp + 0xA0);
    f0 = sceVu0InnerProduct(sp + 0x20, sp + 0xB0);
    f2 = *(f32 *)(sp + 0x60);
    *(f32 *)(sp + 0x64) = -f0;
    if (f2 < 0.0f) {
        f2 = 0.0f;
        *(f32 *)(sp + 0x60) = f2;
    }
    f1 = *(f32 *)(sp + 0x64);
    if (f1 < 0.0f) {
        f1 = 0.0f;
        *(f32 *)(sp + 0x64) = f1;
    }
    f1 = f2 + f1;
    /* 0.5 default is dead: the div sits in the delay slot of the compare branch (always runs) */
    f20 = f2 / f1;
    pos0 = BtlChar_GetPos(c);
    f0 = sceVu0InnerProduct(pos0, sp + 0x30);
    f1 = *(f32 *)(sp + 0x3C);
    f2 = *(f32 *)(sp + 0x60);
    f12 = (f0 + f1 + f2) * f20 - f2;
    if (f12 < 0.0f) {
        func_00312680(sp + 0xD0, sp + 0x20, f12);
        pos0 = BtlChar_GetPos(c);
        pos1 = BtlChar_GetPos(c);
        func_00312638(pos0, pos1, sp + 0xD0);
        func_002113C0(c, 4, 0x80, 1);
        if (flag) func_002113C0(c, 4, 0x100, 1);
        return 1;
    }
    return 0;
}
