#include "common.h"

extern f32 D_0038737C;
extern f32 D_00387380;
extern f32 D_00387384;
extern f32 D_00387388;
extern f32 D_0038738C;
extern f32 D_00387390;
extern f32 D_00387394;
extern f32 D_00387398;
extern f32 D_0038739C;
extern f32 D_003873A0;
extern f32 D_003873A4;
extern f32 D_003873A8;

s32 func_002AF560(void *arg0);
s32 func_002ADFD8(void *arg0);
void func_002AF568(void *arg0, f32 farg0);
s32 func_002AF648(void *arg0, s32 arg1);
void BtlMenu_EndDraw(void *arg0, f32 farg0);
void func_002AF720(void *arg0, f32 farg0);
void func_002B1CA8(void *arg0, s32 arg1);
void func_002AF6A0(void *arg0);
void func_002AFC18(void *arg0, s32 arg1);
s32 func_002B0DB0(void *arg0, s32 arg1);
void func_002AF578(void *arg0, s32 arg1);
s32 func_002AF5E8(void *arg0);
void func_002B0F78(void *arg0, f32 farg0, s32 arg1);
void func_002B11F0(void *arg0, f32 farg0, f32 farg1);
void func_002B1298(void *arg0, f32 farg0, f32 farg1);
void func_002B12E0(void *arg0, s32 arg1);
void func_002AF860(void *arg0, s32 arg1);
s32 func_002B1DF8(void *arg0);

void func_002AE5B0(u8 *arg0) {
    u8 *s0;
    s32 s1;
    s32 s2;
    s32 v1;
    s32 v;
    f32 f0;
    f32 f12;

    s0 = arg0;
    s2 = 0;

    v1 = func_002AF560(arg0);
    if (v1 == 0x1F) {
        func_002AF6A0(s0);
        s2 = 1;
        func_002AFC18(s0, 1);
        if (func_002B0DB0(s0, 0x100) == 0) {
            func_002AF578(s0, 0x20);
        }
    } else if (v1 == 0x1E) {
        v = func_002ADFD8(s0);
        s1 = (v != 0) ? 0x25 : 0x1F;
        if (*(s32 *)(s0 + 0x10) != 0) {
            func_002AF568(s0, 4.0f);
        }
        if (func_002AF648(s0, s1) != 0) {
            BtlMenu_EndDraw(s0, D_0038737C);
            func_002AF720(s0, D_00387380);
            func_002B1CA8(s0, 1);
        }
    } else if (v1 == 0x20) {
        if (func_002AF5E8(s0) != 0) {
            f0 = *(f32 *)(s0 + 0x154);
            *(u8 *)(s0 + 0x188) = 1;
            *(f32 *)(s0 + 0x154) = f0 * 0.5f;
        }
    } else if (v1 == 0x25) {
        func_002AF6A0(s0);
        s2 = 1;
        func_002AFC18(s0, 1);
        if (func_002B0DB0(s0, 0x100) == 0) {
            f0 = *(f32 *)(s0 + 0x154);
            *(u8 *)(s0 + 0x188) = (u8)s2;
            *(f32 *)(s0 + 0x154) = f0 * 0.5f;
        }
    }

    if (s2 != 0) {
        if ((u32)(*(s32 *)(s0 + 0x10) - 1) < 2U) {
            func_002B0F78(s0, D_00387384, 1);
        } else {
            func_002B0F78(s0, D_00387388, 2);
        }
        func_002B11F0(s0, D_0038738C, D_00387390);
        if (func_002B0DB0(s0, 0x800) != 0) {
            f12 = D_00387394;
        } else if (func_002B0DB0(s0, 0x200) != 0) {
            f12 = D_00387398;
        } else {
            f12 = 0.0f;
        }
        func_002B1298(s0, f12, D_0038739C);
    } else {
        func_002B0F78(s0, D_003873A0, 0);
        func_002B11F0(s0, 0.0f, D_003873A4);
        func_002B1298(s0, 0.0f, D_003873A8);
    }

    func_002B12E0(s0, 1);
    func_002AF860(s0, 1);
    func_002AFC18(s0, 4);
    v = func_002B1DF8(s0);
    *(s32 *)(s0 + 0x1C) = v;
}
