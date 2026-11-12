#include "common.h"

void func_00175D70(u8 *arg0, s32 arg1);

/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(fv, out) do { \
    (out) = (s32)(fv); \
} while (0)

/* 0x00175FD0(obj): s0 = obj->+0x38; when flag 0x200 of s0->+0 is set: if the count at +0x10 is below 5, the float
 * at +0x2C truncates toward zero-even must be even for func_00175D70() to run (then the count is incremented);
 * otherwise flag 0x200 is cleared. Finally the float at +0x2C gets + 1.0f. */
void func_00175FD0(u8 *arg0) {
    u8 *s0 = *(u8 **)(arg0 + 0x38);
    s32 flags = *(s32 *)s0;
    s32 n;
    s32 r;
    f32 f;

    if ((flags & 0x200) == 0) {
        return;
    }
    n = *(s32 *)(s0 + 0x10);
    if (n < 5) {
        CVT_W_S(*(f32 *)(s0 + 0x2C), r);
        if ((r & 1) == 0) {
            func_00175D70(arg0, n);
            *(s32 *)(s0 + 0x10) = *(s32 *)(s0 + 0x10) + 1;
        }
    } else {
        *(s32 *)s0 = flags & ~0x200;
    }
    f = *(f32 *)(s0 + 0x2C);
    *(f32 *)(s0 + 0x2C) = f + 1.0f;
}
