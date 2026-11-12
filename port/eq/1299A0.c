#include "common.h"
#include "vu0_state.h"

/* 0x001299A0: for arg3 vectors n at arg1 (stride 0x30): out[k].x = dot3(arg2, n) + arg2.w, out[k].yzw = the
 * remaining lanes of vf6 (VU0 vmul.xyz / vadda.x / vmaddaz.x with vf15.x / vmaddw.x). Nothing for arg3 = 0. */
void func_001299A0(f32 *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    f32 *a = arg1;
    f32 *o = arg0;
    s32 n = arg3;
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    if (n == 0) {
        return;
    }
    do {
        x = arg2[0] * a[0];
        y = arg2[1] * a[1];
        z = arg2[2] * a[2];
        gVu0.vf[6][0] = ((x + y) + gVu0.vf[15][0] * z) + arg2[3];
        for (i = 0; i < 4; i++) {
            o[i] = gVu0.vf[6][i];
        }
        a = a + 12;
        o = o + 4;
        n = n - 1;
    } while (n != 0);
}
