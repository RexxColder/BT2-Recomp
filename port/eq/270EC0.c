#include "common.h"

/* truncates toward zero, the cvt.w.s of the original (FCSR RN). */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, src) do { \
    (dst) = (s32)(src); \
} while (0)

/* 0x00270EC0(base, idx, out1, out2): e = *base + *idx * 0xC0. out1 = cvt.w.s(float at e+0x78+8), out2 = cvt.w.s(float at
 * e+0x78+0x14). When the word at e+0x48 has bit 1 set: out1 = cvt.w.s(out1 + float at e+0x4C) and out2 =
 * cvt.w.s(out2 + float at e+0x50), with the integer operands converted to float first. */
void func_00270EC0(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    u8 *e = (u8 *)*(s32 *)arg0 + *(s32 *)arg1 * 0xC0;
    f32 f;

    CVT_W_S(*arg2, *(f32 *)(e + 0x78 + 0x8));
    CVT_W_S(*arg3, *(f32 *)(e + 0x78 + 0x14));
    if (*(s32 *)(e + 0x48) & 0x2) {
        f = (f32)*arg2 + *(f32 *)(e + 0x4C);
        CVT_W_S(*arg2, f);
        f = (f32)*arg3 + *(f32 *)(e + 0x50);
        CVT_W_S(*arg3, f);
    }
}
