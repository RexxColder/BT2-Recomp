#include "common.h"

void func_003126C8(void *arg0, s32 arg1);
f32 func_00114570(void *arg0, void *arg1);
f32 sqrtf(f32 arg0);
extern u8 *D_00387A40;

/* 0x001165F8(a, b): the two scaled offsets a * 0x18580 and b * 0x18580 are each added to the word at D_00387A40 and
 * +0x9C0, filled into a 0x20-byte stack block by func_003126C8, then func_00114570 measures them; returns the
 * square root of its result (sqrt.s f1, f0; both branches of the NaN test return it). */
f32 func_001165F8(s32 arg0, s32 arg1) {
    s32 buf[8];
    s32 *s0 = buf + 4;
    s32 w = *(s32 *)D_00387A40;
    s32 a3v = (s32)((u32)arg0 * 0x18580u);
    s32 a2v = (s32)((u32)arg1 * 0x18580u);
    s32 s1v = a2v + w;
    s32 v0v = w + a3v;
    f32 r;

    func_003126C8(buf, v0v + 0x9C0);
    func_003126C8(s0, s1v + 0x9C0);
    buf[1] = 0;
    buf[5] = 0;
    r = func_00114570(buf, s0);
    return sqrtf(r);
}
