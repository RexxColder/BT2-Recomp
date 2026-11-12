#include "common.h"

void func_001D35A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3,
                   f32 farg4, f32 farg5, f32 farg6, f32 farg7, f32 st0, f32 st1);
void func_001D38B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3,
                   f32 farg4, f32 farg5, f32 farg6, f32 farg7, f32 st0, f32 st1, f32 st2);
void func_001D3E80(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 rand(void);
extern f32 D_00385348;
extern f32 D_0038534C;
extern f32 D_00385350;
extern f32 D_00385354;
extern f32 D_00385358;
extern f32 D_0038535C;
extern f32 D_00385360;
extern f32 D_00385364;
extern f32 D_00385368;
extern u8 *D_00387E9C;

s32 func_001D0538(s32 arg0, f32 farg0) {
    f32 f0;
    f32 f17;
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
    s32 r;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;
    s32 r8;
    s32 r9;
    s32 r10;
    s32 s0;
    s32 s1;
    s32 v1;
    s32 a2;

    f26 = farg0;
    if (D_00387E9C[0x1491] == 0) {
        return 0;
    }

    f22 = 0.0f;
    f23 = D_00385348;
    f25 = 0.0f;
    f27 = 1.0f;
    s1 = 100;
    f24 = 0.5f;
    s0 = 7;
    f30 = D_0038534C;
    f29 = D_00385350;
    f28 = D_00385354;
    do {
        f22 = (((f32)rand() / f23) * f30) + 1.0f;
        r = rand();
        if ((r % s1) < 3) {
            f22 = ((f32)rand() / f23) * f24;
        }
        r4 = rand();
        r5 = rand();
        f20 = (((f32)r4 / f23) * f29) + f28;
        f21 = ((f32)r5 / f23) * 360.0f;
        r6 = rand();
        f0 = (f32)r6 / f23;
        f17 = (f24 < f0) ? 0.5f : -0.5f;
        s0 -= 1;
        func_001D35A8(arg0, 0, 0, -1, f22, f20, f25, 3.0f, f21, f17, f25, 70.0f, f27, f26);
    } while (s0 >= 0);

    f24 = D_00385358;
    s0 = 2;
    f30 = D_0038535C;
    s1 = 0x60;
    f23 = D_00385360;
    f29 = D_00385364;
    f28 = 360.0f;
    f27 = 0.5f;
    do {
        r7 = rand();
        f22 = 0.5f;
        f0 = (f32)r7 / f24;
        f20 = (f0 * f30) + f29;
        r8 = rand();
        f0 = (f32)r8 / f24;
        f21 = f0 * f28;
        r9 = rand();
        f0 = (f32)r9 / f24;
        if (!(f27 < f0)) {
            f22 = -0.5f;
        }
        r10 = rand();
        s0 -= 1;
        f0 = 5.0f;
        v1 = (r10 < 0) ? (r10 + 0xF) : r10;
        v1 = (v1 >> 4) << 4;
        a2 = s1 - (r10 - v1);
        f17 = D_00385368;
        func_001D38B0(arg0, 0, a2, -1, f20, f23, f25, f23, f21, f22, f17, f25, f0, f23, f26);
    } while (s0 >= 0);

    func_001D3E80(f26, arg0, 0, -1, 0x60);
    return 1;
}
