#include "common.h"

/* 0x0012A1B8 (BT3 IVec4_InGsRange, fuzzy): p = arg0[0..3] as ints in 1/16 units for x, y (vitof4) and plain for w
 * (vitof0). Returns 1 when 0 < x/16 < 4096, 0 < y/16 < 4096 and w > 0 (the VU0 sticky sign/zero flags of
 * p - 0 and 4096 - p), else 0. */
s32 func_0012A1B8(s32 *arg0) {
    f32 x = (f32)arg0[0] / 16.0f;
    f32 y = (f32)arg0[1] / 16.0f;
    f32 w = (f32)arg0[3];

    if (x > 0.0f && y > 0.0f && w > 0.0f && (4096.0f - x) > 0.0f && (4096.0f - y) > 0.0f) {
        return 1;
    }
    return 0;
}
