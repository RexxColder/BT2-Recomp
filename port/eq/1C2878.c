#include "common.h"

#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))

/* cvt.w.s with the default rounding mode (truncates toward zero) */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(x) ((s32)(x))
/* float -> byte as the asm does it: values >= 2^31 take the unsigned path, sb keeps the low byte */
#define CVT_BYTE(x) ({ f32 _y = (x); s32 _v = (_y >= 2147483648.0f) ? (CVT_W_S(_y - 2147483648.0f) | (s32)0x80000000) : CVT_W_S(_y); (u8)_v; })

extern f32 D_00385148;

void Vec4_Set(void *a0, f32 f12, f32 f13, f32 f14, f32 f15);
void func_00276828(void *a0);
void Vec3_Normalize(void *a0, void *a1);
void Vec3_Sub(void *a0, void *a1, void *a2);
f32 func_00129CD8(void *a0, void *a1);
void func_00129BD0(void *a0, void *a1, f32 f12);

void func_001C2878(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 sp[0x40];
    f32 x;
    f32 y;
    f32 z;
    f32 r;
    s32 g;
    u8 *p;

    Vec4_Set(sp + 0x20, 64.0f, 64.0f, 64.0f, 0.0f);
    func_00276828(sp);
    Vec3_Normalize(sp, sp);
    Vec3_Sub(sp + 0x30, arg2, arg1);
    F32(sp, 0x34) = F32(sp, 0x34) * D_00385148;
    Vec3_Normalize(sp + 0x30, sp + 0x30);
    r = func_00129CD8(sp + 0x30, sp);
    func_00129BD0(sp + 0x10, sp + 0x20, r);

    if (F32(sp, 0x10) < 0.0f) {
        F32(sp, 0x10) = 0.0f;
    }
    if (F32(sp, 0x14) < 0.0f) {
        F32(sp, 0x14) = 0.0f;
    }
    if (F32(sp, 0x18) < 0.0f) {
        F32(sp, 0x18) = 0.0f;
    }
    x = F32(sp, 0x10) + (f32)arg3[0];
    y = F32(sp, 0x14) + (f32)arg3[1];
    z = F32(sp, 0x18) + (f32)arg3[2];
    F32(sp, 0x10) = x;
    F32(sp, 0x14) = y;
    F32(sp, 0x18) = z;

    for (g = 0; g < 4; g++) {
        p = arg0 + 0x30 + g * 0x18;
        p[0] = CVT_BYTE(x);
        p[1] = CVT_BYTE(y);
        p[2] = CVT_BYTE(z);
        p[3] = arg3[3];
        F32(p, 0x4) = 1.0f;
    }
}
