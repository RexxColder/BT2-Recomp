#include "common.h"

s32 rand();
void func_001D6AB0(f32 farg0, f32 farg1, f32 farg2, s32 arg0, u8 *arg1, s32 arg2, s32 arg3);
void func_001D6348(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, s32 arg0, u8 *arg1, s32 arg2, s32 arg3);
extern u8 D_002C3630 __attribute__((section(".data")));
extern f32 D_003852B4;
extern f32 D_003852B8;
extern f32 D_003852BC;
extern f32 D_003852C0;
extern f32 D_003852C4;
extern u8 *D_00387E9C;

s32 func_001CF450(s32 arg0) {
    f32 f20;
    f32 f12;
    f32 f14;
    s32 s0;
    s32 v0;

    v0 = 0;
    if (*(u8 *)(D_00387E9C + 0x1491) != 0) {
        f20 = ((f32)rand() / D_003852B4) * 360.0f;
        s0 = 0;
        do {
            f12 = (f32)s0;
            s0 += 1;
            func_001D6AB0(f20 + 120.0f * f12, 0.0f, 1.0f, arg0, &D_002C3630, 8, 0);
        } while (s0 < 3);

        f20 = ((f32)rand() / D_003852B8) * 360.0f;
        s0 = 0;
        do {
            f14 = (f32)s0;
            s0 += 1;
            func_001D6348(4.0f, -4.0f, f20 + 120.0f * f14, D_003852BC, 1.0f, arg0, &D_002C3630, 11, 0);
        } while (s0 < 3);

        f20 = ((f32)rand() / D_003852C0) * 360.0f;
        s0 = 0;
        do {
            f14 = (f32)s0;
            s0 += 1;
            func_001D6348(12.0f, -4.0f, f20 + 72.0f * f14, D_003852C4, 1.0f, arg0, &D_002C3630, 11, 0);
            v0 = 1;
        } while (s0 < 5);
    }
    return v0;
}
