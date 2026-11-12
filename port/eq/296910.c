#include "common.h"

extern f32 D_003871BC;
extern f32 D_003871C0;
extern f32 D_003871C4;

void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00312490(s32 arg0, s32 arg1, s32 arg2);
f32 sceVu0InnerProduct(s32 arg0, s32 arg1);
void sceVu0Normalize(s32 dst, s32 src);
void Vec3_ScaleNeg(s32 arg0, s32 arg1, f32 farg0);

/* Rigid body contact: two impulse steps against the contact normal C (arg2), body B (arg1)
   supplies the matrix/vector transform, A is the body state. */
void func_00296910(f32 *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2) {
    f32 *a = arg0;
    f32 *c = (f32 *)arg2;
    f32 v41[4];
    f32 v42[4];
    f32 v45[4];
    f32 v48[4];
    f32 v49[4];
    f32 v50[4];
    f32 v51[4];
    f32 v52[4];
    f32 dot;
    f32 v15;
    f32 v20;
    f32 scale;
    f32 denom;
    s32 i;

    v15 = (1.0f - farg0) * D_003871BC * a[2];
    denom = a[2] * D_003871C0 * farg2;

    func_00312650((s32)v41, arg1, (s32)(a + 12));
    func_00312490((s32)v42, (s32)(a + 40), (s32)v41);
    v42[0] = v42[0] + a[36];
    v42[1] = v42[1] + a[37];
    v42[2] = v42[2] + a[38];

    dot = sceVu0InnerProduct((s32)v42, arg2);
    v20 = denom - v15 * dot;
    if (v20 < 0.0f) {
        return;
    }

    for (i = 0; i < 3; i++) {
        v45[i] = v20 * c[i];
    }
    func_00312650((s32)v49, arg1, (s32)(a + 12));
    func_00312490((s32)v48, (s32)v49, (s32)v45);
    sceVu0InnerProduct((s32)v48, (s32)v48);

    a[44] = a[44] + v45[0];
    a[45] = a[45] + v45[1];
    a[46] = a[46] + v45[2];
    a[48] = a[48] + v48[0];
    a[49] = a[49] + v48[1];
    a[50] = a[50] + v48[2];

    if (farg1 > 0.0f) {
        dot = sceVu0InnerProduct((s32)v42, arg2);
        v51[0] = v42[0] - dot * c[0];
        v51[1] = v42[1] - dot * c[1];
        v51[2] = v42[2] - dot * c[2];
        sceVu0Normalize((s32)v51, (s32)v51);

        scale = v20 * D_003871C4;
        Vec3_ScaleNeg((s32)v52, (s32)v51, scale);
        func_00312490((s32)v50, (s32)v49, (s32)v52);
        sceVu0InnerProduct((s32)v50, (s32)v50);

        a[44] = a[44] + v52[0];
        a[45] = a[45] + v52[1];
        a[46] = a[46] + v52[2];
        a[48] = a[48] + v50[0];
        a[49] = a[49] + v50[1];
        a[50] = a[50] + v50[2];
    }
}
