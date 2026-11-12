#include "common.h"

#define W32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))
/* cvt.w.s on the EE: truncates toward zero and saturates. */
#define CVT_W(x) (((x) >= 2147483648.0f) ? 0x7FFFFFFF : (((x) < -2147483648.0f) ? (-2147483647 - 1) : (s32)(x)))

void func_002668A8(u8 *rec, u8 *out);

s32 func_0027F368(u8 *obj, u8 *rec) {
    u8 *t1 = rec + 0xAF0;
    s32 idx = W32(t1, 0x4);
    u8 *base = obj + idx * 20;
    u8 sp[0x10];
    s32 i;

    if (W32(t1, 0x0) & 0x80000) {
        base[0] = 0;
        for (i = 1; i < 20; i++) {
            base[i] = 0xFF;
        }
        return 0;
    }

    if (W32(t1, 0x0) & 0x40000) {
        u8 v;
        func_002668A8(rec, sp);
        {
            f32 f = F32(sp, 0x0) * 90.0f;
            s32 v1;
            if (f >= 2147483648.0f) {
                v1 = (s32)((u32)CVT_W(f - 2147483648.0f) | 0x80000000u);
            } else {
                v1 = CVT_W(f);
            }
            v = (u8)(v1 & 0xFF);
        }
        base[0] = 0;
        for (i = 1; i < 20; i++) {
            base[i] = v;
        }
        return 0;
    }

    {
        f32 fc = F32(t1, 0xA8);
        u8 *p = t1 + 0x94;
        for (i = 0; i < 20; i++) {
            s32 a0v;
            if (fc == 0.0f) {
                a0v = p[i];
            } else {
                s32 p0 = p[i];
                a0v = CVT_W(fc * 160.0f);
                if (p0 != 0x80 && a0v < p0) {
                    a0v = p0;
                }
                if (a0v == 0x80) {
                    a0v = 0x81;
                }
                if (a0v >= 0x100) {
                    a0v = 0xFF;
                }
            }
            base[i] = (u8)a0v;
        }
    }
    return 0;
}
