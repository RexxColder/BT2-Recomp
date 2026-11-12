#include "common.h"

extern s32 D_00374918 __attribute__((section(".data")));

extern void *memcpy(void *dst, const void *src, u32 n);
extern void *memset(void *dst, s32 c, u32 n);

/* 0x0024A8A0: writes the decimal digits of arg1 into buf (a digit-string encoder, one byte per
 * digit; zero digits before the first non-zero one become 10, after it 0; the remainder goes into
 * the last byte). arg2 is the field width: arg2-1 digits are used, taken from a copy of the 8-word
 * table at D_00374918 (powers of ten). A zero value fills arg2-1 bytes with 10. Always returns -1.
 * A negative value is written as its absolute value. */
s32 func_0024A8A0(s8 *buf, s32 a1, s32 a2) {
    s32 tbl[8];
    s32 t0 = 0;
    s32 k;

    memcpy(tbl, &D_00374918, 0x20);

    if (a1 == 0) {
        if (0 < a2 - 1) {
            s32 n = a2 - 1;

            memset(buf, 10, n);
            buf += n;
        }
        *buf = 0;
        buf[1] = -1;
        return -1;
    }

    a2 = a2 - 1;
    if (a1 < 0) {
        a1 = -a1;
    }
    if (a2 <= 0) {
        *buf = (s8)a1;
        buf[1] = -1;
        return -1;
    }

    k = a2;
    do {
        u32 d = (u32)tbl[k];
        u32 q = (u32)a1 / d;

        if (q != 0) {
            *buf = (s8)q;
            buf++;
            t0 = 1;
            a1 = (s32)((u32)a1 - q * d);
        } else {
            *buf = (t0 == 0) ? (s8)10 : (s8)0;
            buf++;
        }
        k--;
    } while (k > 0);

    *buf = (s8)a1;
    buf[1] = -1;
    return -1;
}
