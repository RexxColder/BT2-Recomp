#include "common.h"
#include "vu0_state.h"

/* Vec4_ToInt(out a0, in a1): out = (s32)in per lane, truncated and saturated, stored as int bits. */
void Vec4_ToInt(u8 *arg0, u8 *arg1) {
    s32 i;
    s32 v;
    f32 t;

    memcpy(gVu0.vf[4], arg1, 16);
    for (i = 0; i < 4; i++) {
        t = gVu0.vf[4][i];
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
