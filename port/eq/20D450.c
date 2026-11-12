#include "common.h"

f32 sqrtf(f32);
s32 BtlChar_GetPos(s32 arg0);
void BtlChar_GetSnapDelta(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_003126C8(s32 arg0, s32 arg1);
s32 func_0020AB00(s32 arg0);
s32 func_0020AA78(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00211328(s32 arg0, s32 arg1, s32 arg2);
s32 func_00212878(void);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 EftWater_GetSurfaceY(s32 arg0);
f32 BtlCharApi_GetHeight(s32 arg0);
extern f32 D_003859B4;

void func_0020D450(s32 a0) {
    u8 sp[0x30];
    u8 *s0 = (u8 *)a0;
    u8 *s2, *s3, *v1;
    s32 s1 = 0, s4 = 0;
    f32 f20, f2, f0, f1, h1, h2;

    s2 = (u8 *)BtlChar_GetPos(a0);
    s3 = *(u8 **)(s0 + 0x1530) + 0xE60;
    BtlChar_GetSnapDelta(a0, (s32)(sp + 0x10), 0, 1);
    func_003126C8((s32)sp, (s32)s3);
    f20 = 0.0f;
    if ((*(u32 *)(s3 + 0x20) & 0x40000000) != 0) {
        s1 = func_0020AB00(*(s32 *)(s0 + 0x1534)) != 0;
        if (func_0020AA78(*(s32 *)(s0 + 0x1534)) != 0) {
            if ((*(u32 *)(s3 + 0x20) & 0x1000000) == 0) s1 = 1;
        }
    }
    if (s1 == 0) {
        f2 = *(f32 *)(sp + 4);
        if (func_00211310(a0, 0, 4) != 0) {
            if (func_00212878() == 0 || (*(u32 *)(s3 + 0x20) & 0x80) != 0) {
                if (func_00211310(a0, 0, 2) == 0) {
                    f20 = sqrtf(*(f32 *)(sp + 0x10) * *(f32 *)(sp + 0x10) +
                                *(f32 *)(sp + 0x18) * *(f32 *)(sp + 0x18)) + 1.0f;
                    f2 = *(f32 *)(sp + 4);
                }
            }
        }
        f2 = f2 - *(f32 *)(s2 + 0x64);
        if (f2 - f20 < *(f32 *)(s2 + 4)) {
            *(f32 *)(s2 + 4) = f2;
            if (0.0f <= *(f32 *)(sp + 0x14)) {
                *(f32 *)(s2 + 0xC4) = 0.0f;
                s4 = 1;
            }
        }
    }
    func_002113C0(a0, 0, 4, s4);
    func_002113C0(a0, 0, 0x100, 0);
    func_002113C0(a0, 0, 0x200, 0);
    if (EftWater_GetSurfaceY((s32)(sp + 0x20)) != 0) {
        f0 = BtlCharApi_GetHeight(*(s32 *)(s0 + 0x1534));
        f2 = *(f32 *)(s2 + 4) - f0 * 0.5f;
        f1 = *(f32 *)(sp + 0x20);
        if (f1 < f2) {
            func_002113C0(a0, 0, 0x100, 1);
            f1 = *(f32 *)(sp + 0x20);
        }
        f0 = *(f32 *)(*(u8 **)(s0 + 0x1530) + 0xE64);
        if (f1 < f0) {
            h1 = BtlCharApi_GetHeight(*(s32 *)(s0 + 0x1534));
            f20 = *(f32 *)(s2 + 4) - h1;
            h2 = BtlCharApi_GetHeight(*(s32 *)(s0 + 0x1534));
            f2 = *(f32 *)(s2 + 4) + h2 * D_003859B4;
            f1 = *(f32 *)(sp + 0x20);
            if (f20 < f1 && f1 < f2) {
                func_002113C0(a0, 0, 0x200, 1);
            }
        }
    }
    if (func_00211310(a0, 0, 0x100) != 0 && func_00211328(a0, 0, 0x100) == 0) {
        u8 *p = (u8 *)BtlChar_GetPos(a0);
        *(f32 *)(p + 0xC4) = *(f32 *)(p + 0xC4) * 0.5f;
    }
    if (func_00212878() == 0) return;
    if (*(f32 *)(sp + 4) < -10.0f) {
        func_002113C0(a0, 0, 0x40, 0);
    }
    v1 = *(u8 **)(s0 + 0x1530);
    if ((*(u32 *)(v1 + 0xE54) & 0x20) != 0 && (*(u32 *)(v1 + 0xED0) & 0xC0) == 0) {
        func_002113C0(a0, 0, 0x8000, 1);
        v1 = *(u8 **)(s0 + 0x1530);
    }
    if ((*(u32 *)(v1 + 0xE54) & 0x40) != 0) {
        func_002113C0(a0, 0, 0x8000, 1);
    }
    if (s4 != 0 && (*(u32 *)(s3 + 0x20) & 0xC0) == 0) {
        func_002113C0(a0, 0, 0x8000, 1);
    }
}
