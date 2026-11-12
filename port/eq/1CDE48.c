#include "common.h"

extern u8 *D_00387E9C;
extern f32 D_003851EC;
extern f32 D_003851F0;
extern f32 D_003851F4;
extern f32 D_003851F8;
extern f32 D_003851FC;
extern f32 D_00385200;
extern f32 D_00385204;
extern f32 D_00385208;
extern f32 D_0038520C;

s32 rand(void);
void func_001D35A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3,
                   f32 farg4, f32 farg5, f32 farg6, f32 farg7, f32 st0, f32 st1);
void func_001D38B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3,
                   f32 farg4, f32 farg5, f32 farg6, f32 farg7, f32 st0, f32 st1, f32 st2);

s32 func_001CDE48(s32 arg0) {
    f32 f0;
    f32 f17;
    f32 f20;
    f32 f21;
    f32 f22;
    s32 i;
    s32 r;

    if (D_00387E9C[0x1491] == 0) {
        return 0;
    }

    /* loop A: 8 iterations (s0 = 7 .. 0) */
    i = 7;
    do {
        r = rand();
        f22 = (((f32)r / D_003851EC) * D_003851F0) + 1.0f;
        r = rand();
        if ((r % 100) < 3) {
            r = rand();
            f22 = ((f32)r / D_003851EC) * 0.5f;
        }
        r = rand();
        f20 = (f32)r;
        r = rand();
        f21 = (f32)r;
        f20 = ((f20 / D_003851EC) * D_003851F4) + D_003851F8;
        f21 = (f21 / D_003851EC) * 360.0f;
        r = rand();
        f0 = (f32)r / D_003851EC;
        if (0.5f < f0) {
            f17 = 0.5f;
        } else {
            f17 = -0.5f;
        }
        i -= 1;
        func_001D35A8(arg0, 0, 0x46, -1, f22, f20, 0.0f, 3.0f, f21, f17, 0.0f, 8.0f, 1.0f, 1.0f);
    } while (i >= 0);

    /* loop B: 3 iterations (s0 = 2 .. 0) */
    i = 2;
    do {
        r = rand();
        f22 = 0.5f;
        f0 = ((f32)r / D_003851FC) * D_00385200;
        f20 = f0 + D_00385208;
        r = rand();
        f0 = (f32)r / D_003851FC;
        f21 = f0 * 360.0f;
        r = rand();
        f0 = (f32)r / D_003851FC;
        if (!(0.5f < f0)) {
            f22 = -0.5f;
        }
        r = rand();
        i -= 1;
        func_001D38B0(arg0, 0, 0x60 - (r % 16), -1, f20, D_00385204, 0.0f, D_00385204, f21, f22,
                      D_0038520C, 0.0f, 5.0f, D_00385204, 1.0f);
    } while (i >= 0);

    return 1;
}
