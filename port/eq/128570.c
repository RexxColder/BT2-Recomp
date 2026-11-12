#include "common.h"
#include "vu0_state.h"

/* 0x00128570: qmtc2 vf5.x = f12, vrinit R from vf5.x (R = 0x3F800000 | mantissa bits of x). */
void func_00128570(f32 farg0) {
    u32 bits;

    memcpy(&bits, &farg0, 4);
    gVu0.vf[5][0] = farg0;
    gVu0.r = 0x3F800000 | (bits & 0x007FFFFF);
}
