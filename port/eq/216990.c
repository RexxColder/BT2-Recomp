#include "common.h"

f32 sqrtf(f32);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 BtlMember_IsHealthEmpty_2127F8(s32 arg0);
s32 func_00212820(s32 arg0);
s32 func_00212878(void);
f32 func_00272FA8(void);
f32 func_00273000(void);
f32 func_00273048(void);

#define POS(a) ((f32 *)BtlChar_GetPos(a))

void func_00216990(s32 a0) {
    f32 f20, f21, f0, x, z;
    f32 *p;

    p = POS(a0);
    x = p[0];
    p = POS(a0);
    z = p[2];
    f20 = sqrtf(x * x + z * z);
    f0 = func_00272FA8() - *(f32 *)(*(u8 **)(*(u8 **)((u8 *)a0 + 0x1530) + 0xF40) + 0x10);
    if (f0 < f20) {
        f20 = f0 / f20;
        p = POS(a0);
        p[0] = p[0] * f20;
        p = POS(a0);
        p[2] = p[2] * f20;
        func_002113C0(a0, 0, 8, 1);
    } else {
        func_002113C0(a0, 0, 8, 0);
    }
    if (func_00211310(a0, 1, 0x100000) == 0) {
        f20 = func_00273000();
        f20 = f20 + BtlCharApi_GetHeight(*(s32 *)((u8 *)a0 + 0x1534)) * 0.5f;
        if (POS(a0)[1] < f20) {
            POS(a0)[1] = f20;
            func_002113C0(a0, 0, 0x10, 1);
        } else {
            func_002113C0(a0, 0, 0x10, 0);
        }
    }
    if (BtlMember_IsHealthEmpty_2127F8(a0) == 0) {
        f20 = func_00273048();
        f20 = f20 + BtlCharApi_GetHeight(*(s32 *)((u8 *)a0 + 0x1534)) * 0.5f;
        if (f20 < POS(a0)[1]) {
            POS(a0)[1] = f20;
            func_002113C0(a0, 0, 0x20, 1);
        } else {
            func_002113C0(a0, 0, 0x20, 0);
        }
    }
    func_002113C0(a0, 0, 0x40, 0);
    if (func_00212878() == 0) return;
    if (func_00212820(a0) != 0) {
        if (func_00211310(a0, 1, 0x2000000) == 0 && func_00211310(a0, 0, 0x8000) == 0) {
            f20 = -10.0f;
            if (f20 < POS(a0)[1]) {
                POS(a0)[1] = f20;
                func_002113C0(a0, 0, 0x40, 1);
            }
        }
    }
    if (func_00211310(a0, 0, 0x200000) == 0) return;
    f21 = 0x1.72p+7f;
    f20 = -f21;
    if (POS(a0)[0] < f20) POS(a0)[0] = f20;
    if (POS(a0)[2] < f20) POS(a0)[2] = f20;
    if (f21 < POS(a0)[0]) POS(a0)[0] = f21;
    if (f21 < POS(a0)[2]) POS(a0)[2] = f21;
}
