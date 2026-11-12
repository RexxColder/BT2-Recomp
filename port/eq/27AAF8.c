#include "common.h"

s32 Ramp_Step(u8 *arg0);
void func_0027A740(u8 *arg0, s32 arg1, s64 arg2, s32 arg3);
extern u8 *D_003876A0;

#define RND_EVEN(fv, out)                                                          \
    do {                                                                           \
        double t_ = (double)(fv);                                                  \
        s32 r_ = (s32)t_;                                                          \
        double d_ = t_ - (double)r_;                                               \
        if (d_ > 0.5 || (d_ == 0.5 && (r_ & 1))) {                                 \
            r_ += 1;                                                               \
        } else if (d_ < -0.5 || (d_ == -0.5 && (r_ & 1))) {                        \
            r_ -= 1;                                                               \
        }                                                                          \
        (out) = r_;                                                                \
    } while (0)

/* 0x0027AAF8(obj): w = the 64-bit word at D_003876A0 +0x4D8; nothing when its bits 0..1 are clear. With bit 8 set the
 * stored value at obj+0x50 is used; otherwise r = Ramp_Step(obj+0x58): r == 1 clears obj+0x50 and byte +0x54;
 * else obj+0x50 = 0x80 - round(obj->+0x68 * 128). Then when obj+0x50 is nonzero, func_0027A740(obj, 0, 0x1C00,
 * (u8)obj+0x50). */
void func_0027AAF8(u8 *arg0) {
    s64 w = *(s64 *)(D_003876A0 + 0x4D8);
    s32 v;

    if ((w & 3) == 0) {
        return;
    }
    if ((w & 0x100) != 0) {
        v = *(s32 *)(arg0 + 0x50);
    } else {
        s32 r = Ramp_Step(arg0 + 0x58);

        if (r == 1) {
            *(s32 *)(arg0 + 0x50) = 0;
            arg0[0x54] = 0;
            v = 0;
        } else {
            s32 rr;

            RND_EVEN(*(f32 *)(arg0 + 0x68) * 128.0f, rr);
            *(s32 *)(arg0 + 0x50) = 0x80 - rr;
            v = *(s32 *)(arg0 + 0x50);
        }
    }
    if (v != 0) {
        func_0027A740(arg0, 0, 0x1C00, (u8)arg0[0x50]);
    }
}
