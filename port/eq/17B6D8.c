#include "common.h"

#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern u8 *gEftAuraPrm;
extern u8 D_00387788[];

void *memcpy(void *d, const void *s, u32 n);
void func_00129B58();
f32 func_00129CD8();
f32 sqrtf(f32 x);
f32 fabsf(f32 x);

/* sqrt.s on the EE takes |x|: written as sqrtf(fabsf(x)) (NaN stays NaN either way). */
f32 func_0017B6D8(s32 a0, u8 *a1, u8 *a2, f32 scale) {
    u8 sp[0x20];
    u8 *pp = a2;
    f32 f20 = 0.0f;
    f32 x;
    f32 y;
    f32 m;
    f32 k;
    f32 f3;
    f32 f2;
    f32 f1;
    f32 lim;
    f32 f21;
    f32 t;
    f32 t3;
    s32 i;

    memcpy(sp + 0x10, D_00387788, 8);

    for (i = 0; i < 7; i++) {
        func_00129B58(sp, a1, pp);
        m = sqrtf(fabsf(func_00129CD8(sp, sp)));
        if (i == 0) {
            f20 = m;
        } else if (m < f20) {
            f20 = m;
        }

        x = F32(sp, 0x10);
        if (x < 0.0f) {
            F32(sp, 0x10) = f20;
        } else {
            y = F32(sp, 0x14);
            if (y < 0.0f) {
                if (f20 < x) {
                    F32(sp, 0x14) = x;
                    F32(sp, 0x10) = f20;
                } else {
                    F32(sp, 0x14) = f20;
                }
            } else {
                if (f20 < x) {
                    F32(sp, 0x14) = x;
                    F32(sp, 0x10) = f20;
                } else if (f20 < y) {
                    F32(sp, 0x14) = f20;
                }
            }
        }
        pp += 0x10;
    }

    k = F32(gEftAuraPrm, 0x18);
    f3 = 1.0f - k;
    f2 = F32(sp, 0x10) * k;
    f1 = F32(sp, 0x14) * f3;
    f20 = f2 + f1;
    lim = scale * 4.5f;
    f21 = 1.0f;
    if (f20 < lim) {
        t = f20 / lim;
        t3 = t * t;
        t3 = t3 * t;
        f21 = t3 * t3;
    }
    return f21 * 0.5f + 0.5f;
}
