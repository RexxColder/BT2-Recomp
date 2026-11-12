#include "common.h"

/* cvt.w.s: truncates toward zero */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(x) ((s32)(x))

extern u8 D_003B0F40[] __attribute__((section(".data")));

s32 func_00261A98(s32 a0, void *a1, void *a2);
void func_00261AE8(s32 a0, f32 farg0);
f32 func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_0025B9C8(void *a0, void *a1);
void func_00312650(void *a0, void *a1, void *a2);
void func_00312680(void *a0, void *a1, f32 farg0);
void func_00312638(void *a0, void *a1, void *a2);

f32 func_002A3510(void) {
    u8 sp[0x30];
    u8 *p;
    u8 *q;
    u8 *s3;
    s32 i;
    s32 v;
    s32 kind;
    s32 nv;
    s32 s4v;
    f32 f0 = 0.0f;
    f32 f1;
    f32 f20;
    f32 f21;

    f21 = 26.0f;
    f20 = 24.0f;

    /* part 1: 16 slots, per-slot flags at -0x10 and 0 */
    for (i = 0; i < 16; i++) {
        p = D_003B0F40 + 0x16A8 + i;
        v = func_00261A98(i & 0xFFFF, sp + 0x20, sp + 0x24);
        kind = *(s32 *)(sp + 0x20);
        if (v == 0) {
            p[-0x10] = 0;
            p[0] = 0;
        } else if (kind == 27) {
            if (p[-0x10] == 0) {
                f0 = *(f32 *)(sp + 0x24);
                if (f21 <= f0) {
                    f0 = func_00297FE0(1, 0x18, 0x40, 0x40, 0);
                    p[-0x10] = 1;
                }
            }
        } else if (kind == 29) {
            if (p[0] == 0) {
                f0 = *(f32 *)(sp + 0x24);
                if (f20 <= f0) {
                    f0 = func_00297FE0(1, 0x30, 0x40, 0x40, 0);
                    p[0] = 1;
                }
            }
        } else {
            p[-0x10] = 0;
            p[0] = 0;
        }
    }

    /* part 2: one record at D+0xE40 */
    s3 = D_003B0F40 + 0xE40;
    if (s3[0] != 0) {
        v = *(s32 *)(s3 + 8);
        q = s3 + 48 * v;
        if (v < 8 && (*(s32 *)(q + 0x40) & 1)) {
            f1 = *(f32 *)(q + 0x44) * 300.0f;
            s4v = CVT_W_S(f1);
            nv = *(s32 *)(s3 + 4) + 10;
            *(s32 *)(s3 + 4) = nv;
            f20 = (f32)nv / (f32)s4v;
            if (1.0f < f20) {
                f20 = 1.0f;
            }
            func_00312650(sp, q + 0x50, q + 0x20);
            func_00312650(sp + 0x10, q + 0x60, q + 0x30);
            func_00312680(sp, sp, f20);
            func_00312680(sp + 0x10, sp + 0x10, f20);
            func_00312638(sp, sp, q + 0x20);
            func_00312638(sp + 0x10, sp + 0x10, q + 0x30);
            func_0025B9C8(sp, sp + 0x10);
            f0 = 1.0f; /* func_0025ACF8 leaves 1.0f in f0 */
            if (s4v < *(s32 *)(s3 + 4)) {
                *(s32 *)(s3 + 4) = 0;
                *(s32 *)(s3 + 8) = *(s32 *)(s3 + 8) + 1;
            }
        } else {
            *(s32 *)(s3 + 8) = 0;
            s3[0] = 0;
            *(s32 *)(s3 + 4) = 0;
        }
    }

    /* part 3: 16 entries of flags at D+0x1648 and floats at D+0x1658 */
    p = D_003B0F40 + 0x1648;
    for (i = 0; i < 16; i++) {
        if (p[0] != 0) {
            func_00261AE8(i & 0xFFFF, *(f32 *)(D_003B0F40 + 0x1658 + 4 * i));
        }
        p += 1;
    }

    /* part 4: 34 records of 0x28 bytes at D+0x10B0, index from 33 down to 0 */
    p = D_003B0F40 + 0x10B0;
    for (i = 33; i >= 0; i--) {
        if (*(s8 *)(p + 0x18) != 0 && *(s32 *)(p + 0x20) != 0) {
            s32 mode = *(s32 *)(p + 0x20);
            s16 lim = *(s16 *)(p + 0x24);
            u16 lim_u = *(u16 *)(p + 0x24);
            u16 cur = (u16)(*(u16 *)(p + 0x26) + 0xA);
            s32 cur_s;
            s32 x;
            s32 y;

            *(u16 *)(p + 0x26) = cur;
            if ((s16)cur >= lim) {
                *(u16 *)(p + 0x26) = lim_u;
            }
            cur = *(u16 *)(p + 0x26);
            f0 = (f32)(s16)cur;
            f1 = (f32)lim;
            if (mode == 1) {
                f0 = (f0 * 128.0f) / f1;
                *(s8 *)(p + 0xB) = (s8)CVT_W_S(f0);
            } else if (mode == 2) {
                f0 = 128.0f - ((f0 * 128.0f) / f1);
                *(s8 *)(p + 0xB) = (s8)CVT_W_S(f0);
            }
            cur_s = (s32)((u32)cur << 16);
            x = cur_s;
            y = (s32)((u32)lim_u << 16);
            if (!(x < y)) {
                *(s32 *)(p + 0x20) = 0;
            }
        }
        p += 0x28;
    }

    return f0;
}
