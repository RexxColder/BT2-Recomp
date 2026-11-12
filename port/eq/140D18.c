#include "common.h"

extern f32 D_003844FC;

void sceVu0UnitMatrix(f32 *m);
void sceVu0RotMatrixY(f32 *dst, f32 *src, f32 farg0);
void sceVu0ApplyMatrix(f32 *dst, f32 *m, f32 *src);
f32 EftMath_WrapAngle(f32 farg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_001296A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00141628(s32 arg0, s32 arg1, s64 arg2);

/* Builds a 4-corner quad (half width a1 / 2, height a2 rotation) through the unit matrix, transforms it,
 * fills four colour/UV vertex sets from the byte arguments and submits both sets. */
s32 func_00140D18(s32 ctx, s32 unused_a1 /* MIPS $a1: never read */, f32 a1, f32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s64 *a7, s32 a8) {
    u8 sp[0x330];
    f32 *m = (f32 *)(sp + 0x270);
    f32 *v23 = (f32 *)(sp + 0x1B0);
    f32 *v24 = (f32 *)(sp + 0x1C0);
    f32 *v33 = (f32 *)(sp + 0x1F0);
    f32 *v34 = (f32 *)(sp + 0x200);
    f32 *v35 = (f32 *)(sp + 0x230);
    f32 *v36 = (f32 *)(sp + 0x240);
    f32 *v37 = (f32 *)(sp + 0x260);
    f32 half = a1 * 0.5f;
    f32 fa3 = (f32)a3;
    f32 fa4 = (f32)a4;
    f32 fa5 = (f32)a5;
    f32 fa6 = (f32)a6;
    f32 *p;
    s32 i;

    sceVu0UnitMatrix(m);
    if (a2 != 0.0f) {
        f32 ang = EftMath_WrapAngle((a2 / 180.0f) * D_003844FC);
        sceVu0RotMatrixY(m, m, ang);
    }

    v23[0] = -half;
    v23[1] = 0.0f;
    v23[2] = -half;
    v23[3] = 1.0f;
    v24[0] = half;
    v24[1] = 0.0f;
    v24[2] = -half;
    v24[3] = 1.0f;
    ((f32 *)(sp + 0x1D0))[0] = -half;
    ((f32 *)(sp + 0x1D0))[1] = 0.0f;
    ((f32 *)(sp + 0x1D0))[2] = half;
    ((f32 *)(sp + 0x1D0))[3] = 1.0f;
    ((f32 *)(sp + 0x1E0))[0] = half;
    ((f32 *)(sp + 0x1E0))[1] = 0.0f;
    ((f32 *)(sp + 0x1E0))[2] = half;
    ((f32 *)(sp + 0x1E0))[3] = 1.0f;

    p = v23;
    for (i = 3; i >= 0; i--) {
        sceVu0ApplyMatrix(p, m, p);
        func_00312638((s32)p, (s32)p, ctx);
        p[3] = 1.0f;
        p += 4;
    }

    v34[10] = 1.0f;
    v37[0] = fa3;
    v37[1] = fa4;
    v37[2] = fa5;
    v37[3] = fa6;
    v33[0] = 0.0f;
    v33[1] = 0.0f;
    v33[2] = 1.0f;
    v33[3] = 0.0f;
    v34[0] = 1.0f;
    v34[1] = 0.0f;
    v34[2] = 1.0f;
    v34[3] = 0.0f;
    v34[4] = 0.0f;
    v34[5] = 1.0f;
    v34[6] = 1.0f;
    v34[7] = 0.0f;
    v34[8] = 1.0f;
    v34[9] = 1.0f;
    v34[11] = 0.0f;
    v35[0] = fa3;
    v35[1] = fa4;
    v35[2] = fa5;
    v35[3] = fa6;
    v36[0] = fa3;
    v36[1] = fa4;
    v36[2] = fa5;
    v36[3] = fa6;
    v36[4] = fa3;
    v36[5] = fa4;
    v36[6] = fa5;
    v36[7] = fa6;

    func_001296A0((s32)sp, (s32)v23, (s32)v33, (s32)v35, 3);
    func_00141628((s32)sp, a8, *a7);
    func_001296A0((s32)sp, (s32)v24, (s32)v34, (s32)v36, 3);
    return func_00141628((s32)sp, a8, *a7);
}
