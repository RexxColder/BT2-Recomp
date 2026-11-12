#include "common.h"

extern void Vec4_Set(void *dst, f32 x, f32 y, f32 z, f32 w);
void func_00129C28(void *a0, void *a1);
void func_001296A0(void *a0, void *a1, void *a2, void *a3, s32 t0);
s32 func_001E5D00(void *a0, u64 a1, s32 a2, s32 a3, s32 t0);

s32 func_001E6400(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, u64 arg9 /* TEX0 (64-bit; was u8 *: truncated to 32 bits) */, s32 arg10, u8 arg11) {
    u8 buf[0x230];
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s5;
    s32 s6;
    s32 s7;
    u8 *s0;
    u8 *s1;
    s32 v0;

    memset(buf, 0, 0x1B0);
    Vec4_Set(buf + 0x1B0, *(f32 *)(arg1 + 0x0), *(f32 *)(arg1 + 0x4), 1.0f, 1.0f);
    Vec4_Set(buf + 0x1C0, *(f32 *)(arg1 + 0x8), *(f32 *)(arg1 + 0xC), 1.0f, 1.0f);
    Vec4_Set(buf + 0x1D0, *(f32 *)(arg2 + 0x0), *(f32 *)(arg2 + 0x4), 1.0f, 1.0f);
    Vec4_Set(buf + 0x1E0, *(f32 *)(arg2 + 0x8), *(f32 *)(arg2 + 0xC), 1.0f, 1.0f);

    s3 = arg3 & 0xFF;
    s5 = arg4 & 0xFF;
    s6 = arg5 & 0xFF;
    s7 = arg6 & 0xFF;
    s4 = arg7;
    s2 = arg11;
    s0 = buf + 0x1F0;
    Vec4_Set(s0, (f32)s3, (f32)s5, (f32)s6, (f32)s7);
    s1 = buf + 0x200;
    func_00129C28(s1, s0);
    func_00129C28(buf + 0x210, s0);
    func_00129C28(buf + 0x220, s0);

    func_001296A0(buf, arg0, buf + 0x1B0, s0, 3);
    func_001E5D00(buf, arg9, s4, arg10, s2);
    func_001296A0(buf, arg0 + 0x10, buf + 0x1C0, s1, 3);
    v0 = func_001E5D00(buf, arg9, s4, arg10, s2);
    return v0;
}
