#include "common.h"

extern u8 *D_00387E9C;
extern f32 D_00385238;
extern f32 D_0038523C;
extern f32 D_00385240;
extern f32 D_00385244;
extern f32 D_00385248;
extern f32 D_0038524C;
extern f32 D_00385250;
extern f32 D_00385254;
extern f32 D_00385258;
extern f32 D_0038525C;
extern s64 D_0036F090 __attribute__((section(".data")));

s32 rand(void);
s64 fptodp(f32 farg0);
s64 dpmul(s64 arg0, s64 arg1);
f32 dptofp(s64 arg0);
void func_001D35A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3,
                   f32 farg4, f32 farg5, f32 farg6, f32 farg7, f32 st0, f32 st1);

s32 func_001CE4D0(s32 arg0, s32 arg1, f32 farg0, f32 farg1) {
    f32 sp14;
    f32 f0;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 f25;
    f32 f27;
    s32 s3;
    s32 r;
    s64 s0;
    s64 p1;
    s64 p2;
    f32 z;

    if (D_00387E9C[0x1491] == 0) {
        return 0;
    }

    sp14 = (farg0 / 10.0f) * 10.0f;
    f27 = 0.0f;
    s3 = 7;
    do {
        if (arg1 == 1) {
            r = rand();
            f0 = (f32)r / D_00385240;
            f0 = f0 * D_00385244;
            f0 = f0 + D_00385248;
            f27 = -f0;
        } else if (arg1 < 2) {
            if (arg1 == 0) {
                f27 = 0.0f;
            }
        } else if (arg1 == 2) {
            r = rand();
            f0 = (f32)r / D_0038524C;
            f0 = f0 * D_00385250;
            f27 = f0 + D_00385254;
        }

        f20 = D_0038525C;
        r = rand();
        f21 = (((f32)r / f20) * D_00385258) + 1.0f;
        if ((rand() % 100) < 3) {
            f21 = ((f32)rand() / f20) * 0.5f;
        }

        f25 = 0.5f;
        r = rand();
        f24 = ((((f32)r / f20) * D_00385238) + D_0038523C) * farg0;
        r = rand();
        f23 = ((((f32)r / f20) * D_00385238) + D_0038523C) * farg0 * 3.0f;
        r = rand();
        f22 = ((f32)r / f20) * 360.0f;
        r = rand();
        if (!(0.5f < ((f32)r / f20))) {
            f25 = -0.5f;
        }

        s3 -= 1;
        s0 = fptodp(f21);
        p1 = dpmul(fptodp(sp14), D_0036F090);
        p2 = dpmul(s0, p1);
        z = dptofp(p2);
        func_001D35A8(arg0, 0, 0x46, -1, z, f24, 0.0f, f23, f22, f25, f27, 8.0f, farg1, 1.0f);
    } while (s3 >= 0);

    return 1;
}
