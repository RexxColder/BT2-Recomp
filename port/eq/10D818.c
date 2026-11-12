#include "common.h"

extern s32 D_0036C720[10];

s32 func_00203CC0(s32 arg0);
s32 func_0010B0A0(s32 arg0);
void func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00113860(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00113D80(u8 *arg0, s32 arg1);
void func_00113B00(u8 *arg0, s32 arg1, s32 arg2);
s32 func_0020B760(u32 arg0);
s32 func_0010D548(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_001140A8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);

#define A(p) ((s32)(u32)(p))

void func_0010D818(u8 *a0, s32 a1, s32 a2) {
    s32 *score = (s32 *)(u32)func_00203CC0(a2);
    u8 *st = a0 + a1 * 0x750 + 0xD0;
    u8 *g = (u8 *)(u32)func_0010B0A0(a1);
    u8 *top = g + 0xA20;
    s32 cur, shown, hi, lo, hiRem, loRem, color;
    s32 hiIdx, loIdx, n, i, j;
    s32 *fill;
    s32 *amt;
    u8 *slot;
    u8 *src;
    u8 *dst;

    func_00114508(A(top), 2, 0, 0x1D);
    func_00113860(g + 0xA2C, 0, 0, 0x9A, 0xC, 7);
    func_00113D80(top, 0);
    func_00113B00(top, 0x40, 0xA);

    switch (*(s32 *)(st + 0x69C)) {
    case 1:
        if (func_0020B760(a2) == 0) {
            *(s32 *)(st + 0x69C) = 2;
        }
        cur = *score;
        break;
    case 0:
        if (func_0020B760(a2) != 0) {
            *(s32 *)(st + 0x69C) = 1;
        }
        *(s32 *)(st + 0x6A0) = *(s32 *)(st + 0x6A4);
        cur = *score;
        break;
    case 2:
        shown = *(s32 *)(st + 0x6A0) - 300;
        *(s32 *)(st + 0x6A0) = shown;
        cur = *score;
        if (!(cur < shown)) {
            *(s32 *)(st + 0x69C) = 0;
            cur = *score;
        }
        if (cur < *(s32 *)(st + 0x6A4)) {
            *(s32 *)(st + 0x6A0) = *(s32 *)(st + 0x6A4);
            *(s32 *)(st + 0x69C) = 1;
            cur = *score;
        }
        break;
    default:
        cur = *score;
        break;
    }
    *(s32 *)(st + 0x6A4) = cur;

    shown = *(s32 *)(st + 0x6A0);
    cur = *score;
    hiIdx = shown / 10000;
    n = cur / 10000;
    loIdx = hiIdx;
    hi = cur - n * 10000;
    lo = shown - hiIdx * 10000;
    if (hi == 0 && n != 0) {
        n -= 1;
        hi = 10000;
    }
    loRem = lo;
    if (loRem == 0 && hiIdx != 0) {
        loIdx = hiIdx - 1;
        loRem = 10000;
    }
    hiRem = hi;
    if (n >= 9) {
        i = 9;
        color = D_0036C720[9];
    } else {
        i = n;
        color = D_0036C720[n];
    }

    if (n == loIdx) {
        if (n != 0) {
            func_0010D548(A(top + 0xC0), A(top), A(st), 10000, 10000, 1, 0, D_0036C720[i - 1]);
        }
        func_0010D548(A(top + 0x300), A(top), A(st), hiRem, loRem, 0, 0, color);
    } else if (loIdx - n < 0) {
        if (n != 0) {
            func_0010D548(A(top + 0xC0), A(top), A(st), 10000, 10000, 1, 0, D_0036C720[i - 1]);
        }
        func_0010D548(A(top + 0x300), A(top), A(st), hiRem, loRem, 0, 0, color);
    } else if (loIdx - n == 1) {
        func_0010D548(A(top + 0xC0), A(top), A(st), hiRem, 10000, 0, 1, color);
        func_0010D548(A(top + 0x300), A(top), A(st), 0, loRem, 0, 0, color);
    } else {
        func_0010D548(A(top + 0xC0), A(top), A(st), 0, 10000, 0, 1, D_0036C720[0]);
        func_0010D548(A(top + 0x300), A(top), A(st), 0, loRem, 0, 0, D_0036C720[0]);
    }

    fill = (s32 *)(st + 0x6A8);
    slot = top + 0x540;
    j = 71;
    i = 0;
    {
        s32 up = 0 < n;
        do {
            i++;
            if (up) {
                *fill += 8;
                if (*fill > 0x80) {
                    *fill = 0x80;
                }
            } else {
                s32 d = *fill - 8;
                if (d < 0) {
                    d = 0;
                }
                *fill = d;
            }
            func_00113860(slot + 0xC, 0, 0x10, 0xD, 0x18, 7);
            func_00113D80(slot, 0);
            fill++;
            func_00113B00(slot, j, 6);
            j += 9;
            slot += 0x60;
            up = i < n;
        } while (i < 7);
    }

    amt = (s32 *)(st + 8 + 0x6A0);
    dst = top + 0x7E0;
    src = top;
    for (i = 0; i < 7; i++) {
        if (*amt > 0) {
            u8 *s = src + 0x540;
            u8 *d = dst;
            while (s != src + 0x5A0) {
                *(u64 *)d = *(u64 *)s;
                *(u64 *)(d + 8) = *(u64 *)(s + 8);
                *(u64 *)(d + 0x10) = *(u64 *)(s + 0x10);
                *(u64 *)(d + 0x18) = *(u64 *)(s + 0x18);
                s += 0x20;
                d += 0x20;
            }
            *(u32 *)dst |= 0x10000;
            dst[0x19] = *(u8 *)amt;
        }
        amt++;
        dst += 0x60;
        src += 0x60;
    }
    if (a1 == 1) {
        func_001140A8(top, 0, 1, 0, 0x1D);
    }
    BtlRec_CallFlagged(A(top), 1, 0x1D);
}
