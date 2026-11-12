#include "common.h"
#include "vu0_state.h"

/* 0x00129D50(a0, a1): out.x,y = (s32)(in * 16), out.z = (s32)in.z, out.w unchanged (int bits). */
void func_00129D50(u8 *arg0, u8 *arg1) {
    s32 i;
    s32 v;
    f32 t;

    memcpy(gVu0.vf[4], arg1, 16);
    for (i = 0; i < 3; i++) {
        t = gVu0.vf[4][i] * ((i < 2) ? 16.0f : 1.0f);
        if (t >= 2147483647.0f) {
            v = 0x7FFFFFFF;
        } else if (t <= -2147483648.0f) {
            v = (s32)0x80000000u;
        } else {
            v = (s32)t;
        }
        memcpy(&gVu0.vf[5][i], &v, 4);
    }
    memcpy(arg0, gVu0.vf[5], 16);
}
