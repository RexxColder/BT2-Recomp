#include "common.h"

/* cvt.w.s (truncates toward zero) written out, result in dst */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, x) do { (dst) = (s32)(x); } while (0)

extern s32 *D_00387AEC;
extern s32 D_003B0A84 __attribute__((section(".data")));

u8 *Dma_BeginDirect(s32 arg0);
void Dma_EndDirect(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3);

void func_0027B430(s32 arg0, s32 arg1) {
    u8 *a3;
    s32 a0, a1, a2;
    s32 s0, s1, s2, s3, s6, s7;
    s64 s4;
    s32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;
    s32 carry;
    s32 o;
    s32 v0;
    s64 hv;
    s64 hw;
    s64 v0x;
    s64 w;
    f32 f0, f1, f2, f3;

    a0 = arg0 & 0xFF;
    s0 = 0x200;
    s1 = 0;
    s2 = 0x100;
    if (a0 != 0) {
        s2 = 0x80;
        s0 = 0x100;
        if (arg1 != 0) {
            s1 = 0x100;
            s0 = 0x200;
        }
    }
    s7 = 0;
    a3 = Dma_BeginDirect(a0);
    *(s64 *)(a3 + 0x00) = ((s64)0x10000000 << 32) | 6;
    *(s64 *)(a3 + 0x08) = 0xE;
    a3 += 0x10;

    /* header: the 0x80000/0x80070 word, the 0x4C word and the 0xDF80 word */
    a0 = (D_003B0A84 & 1) ? 0x80000 : 0x80070;
    a1 = s2 - 1;
    a2 = 0x4C;
    *(s64 *)(a3 + 0x00) = a0;
    *(s64 *)(a3 + 0x08) = a2;
    a3 += 0x10;
    v0x = ((s64)(s0 - 1) << 16) | s1;
    v0x |= (s64)0xDF80 << 41;
    *(s64 *)(a3 + 0x00) = v0x;
    *(s64 *)(a3 + 0x08) = 0x40;
    a3 += 0x10;
    hv = ((s64)(s2 - 1) << 14) | ((s64)0xDF00 << 26);
    hw = ((((s64)2 << 16) | 0x2001) << 16) | 0x2A00;
    *(s64 *)(a3 + 0x08) = 6;
    *(s64 *)(a3 + 0x00) = hw;
    a3 += 0x10;
    hv |= 0xA;
    *(s64 *)(a3 + 0x08) = 8;
    *(s64 *)(a3 + 0x00) = hv;
    a3 += 0x10;
    *(s64 *)(a3 + 0x00) = 0x60;
    *(s64 *)(a3 + 0x08) = 0x14;
    a3 += 0x10;
    *(s64 *)(a3 + 0x00) = 0x44;
    *(s64 *)(a3 + 0x08) = 0x42;
    a3 += 0x10;
    s6 = 9;

    do {
        a1 = *D_00387AEC + s7;
        if (*(s32 *)a1 != 0) {
            f1 = *(f32 *)(a1 + 0x20);
            f0 = 255.0f;
            *(s64 *)(a3 + 0x00) = ((s64)0x10000000 << 32) | 1;
            f1 = f1 * f0;
            *(s64 *)(a3 + 0x08) = 0xE;
            a3 += 0x10;
            t3 = a1 + 8;
            *(s64 *)(a3 + 0x00) = 0x15C;
            t7 = 0;
            *(s64 *)(a3 + 0x08) = 0;
            a3 += 0x10;
            CVT_W_S(t9, f1);
            v0 = (t9 < 0) ? (t9 + 7) : t9;
            s0 = v0 >> 3;
            s4 = ((s64)0x3F800000 << 32) | 0x00808080;
            s2 = 0;
            t2 = t7 << 3;

L610:
            *(s64 *)(a3 + 0x00) = ((s64)0x34000000 << 32) | 0x802A;
            *(s64 *)(a3 + 0x08) = 0x531;
            a3 += 0x10;
            s1 = s2 + 1;
            t1 = t2;
            t8 = 0;
            s3 = s1;
            t0 = t1;
            carry = 0;

            do {
                a0 = t8 & 1;
                v0 = t8 + carry;
                a2 = s2;
                a1 = v0 >> 1;
                if (a0 != 0) {
                    a2 = s3;
                }
                if (!(a1 < 0x14)) {
                    a1 = a1 - 0x14;
                }
                o = (a2 == 0) ? 0x70 : ((a2 == 1) ? 0x110 : 0x1B0);
                t4 = (a2 == 1) ? t9 : s0;
                a1 = (s32)((u32)a1 << 3) + t3;
                f0 = *(f32 *)(a1 + o);
                f2 = *(f32 *)(a1 + o + 0x04);
                f3 = *(f32 *)(a1 + o + 0x1E0);
                f1 = *(f32 *)(a1 + o + 0x1E4);
                CVT_W_S(t6, f0);
                CVT_W_S(t5, f2);
                CVT_W_S(a2, f3);
                CVT_W_S(a1, f1);

                /* block A (B704): packet word from t4 and s4 */
                t7 += 1;
                *(s64 *)(a3 + t0) = ((s64)t4 << 24) | s4;
                a0 = (t7 < 2);
                t2 += 8;
                t1 += 8;
                t0 += 8;
                if (a0 == 0) {
                    a3 += 0x10;
                    t2 = 0;
                    t1 = 0;
                    t0 = 0;
                    t7 = 0;
                }

                /* block B (B75C): round f1 high, round f3 low */
                t7 += 1;
                w = (s64)(s32)((u32)a1 << 4) << 16;
                a0 = (s32)((u32)a2 << 4);
                w |= (s64)a0;
                *(s64 *)(a3 + t1) = w;
                a1 = (t7 < 2);
                t2 += 8;
                t1 += 8;
                t0 += 8;
                if (a1 == 0) {
                    a3 += 0x10;
                    t2 = 0;
                    t1 = 0;
                    t0 = 0;
                    t7 = 0;
                }

                /* block C (B7A0): round f2 high, round f0 low */
                w = (s64)(s32)((u32)t5 << 4) << 16;
                a0 = (s32)((u32)t6 << 4);
                t7 += 1;
                w |= (s64)a0;
                *(s64 *)(a3 + t2) = w;
                a1 = (t7 < 2);
                t2 += 8;
                t1 += 8;
                t0 += 8;
                if (a1 == 0) {
                    a3 += 0x10;
                    t2 = 0;
                    t1 = 0;
                    t0 = 0;
                    t7 = 0;
                }

                t8 += 1;
                carry = (u32)t8 >> 31;
            } while (t8 < 0x2A);

            s2 = s1;
            if (s2 < 2) {
                t2 = t7 << 3;
                goto L610;
            }
        }
        s6 -= 1;
        s7 += 0x460;
    } while (s6 >= 0);

    *(s64 *)(a3 + 0x00) = ((s64)0x10000000 << 32) | 0x8002;
    *(s64 *)(a3 + 0x08) = 0xE;
    a3 += 0x10;
    *(s64 *)(a3 + 0x08) = 0x4E;
    *(s64 *)(a3 + 0x00) = 0x310000E0;
    a3 += 0x10;
    *(s64 *)(a3 + 0x00) = ((((s64)0x01BF0000 << 16) | 0x1FF) << 16);
    *(s64 *)(a3 + 0x08) = 0x40;
    Dma_EndDirect(a3 + 0x10, a1, a2, a3);
}
