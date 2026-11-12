#include "common.h"
#include "vu0_state.h"

/* Their asm ran on the PS2Recomp fallback, whose VU0 R register is not gVu0.r: the seed set by func_00128570 (in C)
   never reached the generator. Now both use gVu0. */

/* vrnext: one step of the VU0 random generator (Tenkaichi3Decomp port/src/mathf_pc.c rnext). */
static u32 Vu0_RNext(void) {
    u32 b = ((gVu0.r >> 4) ^ (gVu0.r >> 22)) & 1u;

    gVu0.r = 0x3F800000u | (((gVu0.r << 1) | b) & 0x007FFFFFu);
    return gVu0.r;
}

/* 0x00128580 Rand_Float01: seven vrnext into vf5.x, vrinit R from vf5.x, seven more, minus 1.0 -> [0, 1). */
f32 Rand_Float01(void) {
    u32 f = 0;
    f32 v;
    s32 i;

    for (i = 0; i < 7; i++) {
        f = Vu0_RNext();
    }
    gVu0.r = 0x3F800000u | (f & 0x007FFFFFu);
    for (i = 0; i < 7; i++) {
        f = Vu0_RNext();
    }
    memcpy(&v, &f, 4);
    gVu0.vf[5][0] = v - 1.0f;
    return gVu0.vf[5][0];
}

/* 0x001285D0 Rand_FloatRange(lo, hi): hi when equal; the bounds are swapped when hi < lo; lo + r * (hi - lo). */
f32 Rand_FloatRange(f32 lo, f32 hi) {
    f32 t;

    if (hi == lo) {
        return hi;
    }
    if (hi < lo) {
        t = lo;
        lo = hi;
        hi = t;
    }
    return lo + Rand_Float01() * (hi - lo);
}
