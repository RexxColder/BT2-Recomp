#include "common.h"

extern f32 D_003841B0;
extern f32 D_003841B4;
extern f32 D_003841B8;
extern f32 D_003841BC;
extern f32 D_003841C0;
extern f32 D_003841C4;
extern f32 D_003841C8;

s32 rand(void);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 func_00208798(s32 arg0, void *arg1);
s32 func_00208BE0(s32 arg0, void *arg1);
s32 func_001307F8(void *arg0);
void func_00312638(void *arg0, void *arg1, void *arg2);
void func_00312680(f32 farg0, void *arg0, void *arg1);
s32 func_001301D0(void *a0, void *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                  f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                  f32 st0, f32 st1, s32 st2);

s32 EftBubble_EmitBurst(s32 arg0, s32 arg1) {
    f32 sp20[4];
    f32 sp30[4];
    f32 sp40[4];
    s32 ret;
    s32 count;
    s32 r;
    s32 t3;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 f25;
    f32 f26;
    f32 f27;
    f32 f28;
    f32 h;

    func_00208798(arg0, sp20);
    ret = func_00208BE0(arg0, sp30);
    if (arg1 > 0) {
        f25 = D_003841B0;
        f28 = 0.5f;
        f27 = D_003841B4;
        f26 = D_003841B8;
        count = arg1;
        do {
            count -= 1;
            f24 = (((f32)rand() / f25) * 4.5f) + 3.0f;
            f23 = (((f32)rand() / f25) * D_003841BC) - D_003841C0;
            f22 = (f32)rand();
            r = rand();
            f20 = (f32)r / f25;
            f22 = ((f22 / f25) * f28) + f27;
            f20 = f20 * 10.0f;

            h = BtlCharApi_GetHeight(arg0);
            f24 = f24 * (h * f26);
            h = BtlCharApi_GetHeight(arg0);
            f23 = f23 * (h * f26);
            h = BtlCharApi_GetHeight(arg0);
            f22 = f22 * (h * f26);
            h = BtlCharApi_GetHeight(arg0);
            f20 = f20 * (h * f26);

            func_001307F8(sp40);
            func_00312680(f20, sp40, sp40);
            func_00312638(sp40, sp40, sp20);

            func_00312680((((f32)rand() / f25) * f27) + D_003841C4, sp30, sp30);

            f21 = ((f32)rand() / f25) * 360.0f;
            f20 = ((f32)rand() / f25) * D_003841C8;
            r = rand();
            t3 = ((r & 3) == 0) ? 3 : 2;

            ret = func_001301D0(sp40, sp30, 0x80, 0x80, 0x80, arg0, -1, t3,
                                -8.0f, f24, 112.0f, f21, f23, 6.0f, f20, f22,
                                f28, -1.0f, 0);
        } while (count != 0);
    }
    return ret;
}
