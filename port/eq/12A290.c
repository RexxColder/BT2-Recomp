#include "common.h"

/* 0x0012A290 IVec4_InGsRange4(a, b, c): the points a, b, c and c (vf7..vf10 read as ints: x and y in 12.4 fixed point,
 * z and w as integers) are each tested with the on-screen flags of Vu0Cur_ProjectPoints: x, y, w and 4096 - x,
 * 4096 - y all nonzero and positive. Returns 1 when all four points pass. */
#define IVEC_ZERO_OR_NEG(f) ({ u32 b_; memcpy(&b_, &(f), 4); ((b_ & 0x7FFFFFFFu) == 0) | (s32)(b_ >> 31); })

void *memcpy(void *arg0, const void *arg1, u32 arg2);

s32 IVec4_InGsRange4(s32 *arg0, s32 *arg1, s32 *arg2) {
    s32 *pts[4];
    s32 k;
    s32 bad = 0;

    pts[0] = arg0;
    pts[1] = arg1;
    pts[2] = arg2;
    pts[3] = arg2;
    for (k = 0; k < 4; k++) {
        s32 *ip = pts[k];
        f32 x = (f32)ip[0] * 0.0625f;
        f32 y = (f32)ip[1] * 0.0625f;
        f32 w = (f32)ip[3];
        f32 d1 = 4096.0f - x;
        f32 d2 = 4096.0f - y;

        bad |= IVEC_ZERO_OR_NEG(x) | IVEC_ZERO_OR_NEG(y) | IVEC_ZERO_OR_NEG(w) | IVEC_ZERO_OR_NEG(d1) |
               IVEC_ZERO_OR_NEG(d2);
    }
    return bad == 0;
}
