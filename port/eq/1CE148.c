#include "common.h"

extern u8 *D_00387E9C;
extern f32 D_00385210;
extern f32 D_00385214;
extern f32 D_00385218;
extern f32 D_0038521C;
extern f32 D_00385220;
extern f32 D_00385224;
extern f32 D_00385228;
extern f32 D_0038522C;
extern f32 D_00385230;
extern f32 D_00385234;

s32 rand(void);
void func_001D35A8(f32 a0f, f32 a1f, f32 a2f, f32 a3f, f32 a4f, f32 a5f, f32 a6f, f32 a7f,
                   s32 i0, s32 i1, s32 i2, s32 i3, f32 st0, f32 st1);
void func_001D38B0(f32 a0f, f32 a1f, f32 a2f, f32 a3f, f32 a4f, f32 a5f, f32 a6f, f32 a7f,
                   s32 i0, s32 i1, s32 i2, s32 i3, f32 st0, f32 st1, f32 st2);
void func_001D3E80(s32 i0, s32 i1, s32 i2, s32 i3, f32 f0);

s32 func_001CE148(s32 arg0, s32 arg1, s32 arg2) {
    s32 s0;
    s32 s1;
    s32 r;
    s32 c;
    f32 f0;
    f32 f17;
    f32 f18;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 f25;
    f32 f26;
    f32 f27;
    f32 f28;
    f32 f29;
    f32 f30;
    f32 f31;

    if (*(u8 *)(D_00387E9C + 0x1491) == 0) {
        return 0;
    }

    f27 = 2.5f;
    f29 = 3.0f;
    f30 = D_00385210;
    f28 = 1.0f;
    f31 = D_00385214;
    if (arg2 < 0x87 && arg2 >= 0x85) {
        f27 = 4.5f;
        f29 = 5.0f;
        f30 = D_00385218;
        f31 = f27;
        f28 = 2.0f;
    }

    f23 = D_0038521C;
    s1 = 0x64;
    f26 = 0.5f;
    s0 = 7;
    f24 = 0.0f;
    f25 = 1.0f;
    do {
        f0 = ((f32)rand() / f23) * D_00385220;
        f22 = f0 + 1.5f;
        r = rand();
        if ((r % s1) < 3) {
            f22 = ((f32)rand() / f23) * f26;
        }
        f20 = (f32)rand() / f23;
        f20 = f20 * D_00385224;
        f20 = f27 + f20;
        f21 = (f32)rand() / f23;
        f21 = f21 * 360.0f;
        f0 = (f32)rand() / f23;
        f17 = (f26 < f0) ? f26 : -0.5f;
        s0 -= 1;
        func_001D35A8(f22 * f28, f20, 0.0f, f29, f21, f17, 0.0f, 8.0f,
                      arg0, 0, 0x46, arg1, f25, f25);
    } while (s0 >= 0);

    f23 = D_00385228;
    s0 = 2;
    f29 = D_0038522C;
    s1 = 0x60;
    f28 = 360.0f;
    f27 = 0.5f;
    f26 = D_00385230;
    f25 = 1.0f;
    do {
        f22 = 0.5f;
        f20 = ((f32)rand() / f23) * f29;
        f20 = f31 + f20;
        f21 = (f32)rand() / f23;
        f21 = f21 * f28;
        f0 = (f32)rand() / f23;
        if (!(f27 < f0)) {
            f22 = -0.5f;
        }
        s0 -= 1;
        r = rand();
        f18 = D_00385234;
        c = s1 - (r - (((r < 0 ? r + 0xF : r) >> 4) * 0x10));
        func_001D38B0(f20, f30, 0.0f, f30, f21, f22, f18, 0.0f,
                      arg0, 0, c, arg1, 5.0f, f26, f25);
    } while (s0 >= 0);

    func_001D3E80(arg0, 0, arg1, 0x60, 1.0f);
    return 1;
}
