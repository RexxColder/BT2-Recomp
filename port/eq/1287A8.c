#include "common.h"
#include "vu0_state.h"

void Mtx_MulVec4(f32 *dst, f32 *m, f32 *v);
void Vec3_DirToEuler(f32 *out, f32 *dir);
extern f32 gVu0AxisZW[4] __attribute__((section(".data")));

/* 0x001287A8 Mtx_AxisZToEuler(angles, m): a 4x4 copy of m's rows 0..2 with row 3 = vf0 = (0,0,0,1) goes through
 * Mtx_MulVec4 with (0,0,1,1); the direction is converted by Vec3_DirToEuler into angles. */
void Mtx_AxisZToEuler(f32 *angles, f32 *m) {
    f32 mt[16];
    f32 dir[4];
    s32 i;

    for (i = 0; i < 12; i++) {
        mt[i] = m[i];                  /* lq t0..t2 from a1, sq to the stack */
    }
    for (i = 0; i < 4; i++) {
        mt[12 + i] = gVu0.vf[0][i];    /* sqc2 vf0, 0x30(sp) */
    }
    Mtx_MulVec4(dir, mt, gVu0AxisZW);
    Vec3_DirToEuler(angles, dir);
}
