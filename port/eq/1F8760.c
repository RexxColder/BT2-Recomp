#include "common.h"

extern s32 func_00211270(void);
extern u8 *func_00211288(s32 arg0);
extern s32 func_00210DD8(u8 *arg0);
extern s32 func_00211310(u8 *obj, s32 arg1, s32 mask);
extern s32 *BtlMember_GetActiveGauge(u8 *arg0);
extern s32 *func_00202E60(u8 *arg0, s32 arg1);
extern u8 *D_003876A0;

#define ST(o, mask, bit) \
    if (func_00211310((o), 16, (mask))) { \
        *out |= (u64)(bit); \
    }

/* Builds per-battler status flag words (u64 at a+8+i*8), two stat words (a+0x18, a+0x28) and a
   percentage (f32 at a+0x30+i*4) for every battler. Returns 0. */
s32 func_001F8760(u8 *a) {
    u64 *flagsBase = (u64 *)(a + 8);
    f32 *pct = (f32 *)(a + 0x30);
    s32 i = 0;

    while (i < func_00211270()) {
        u8 *m = func_00211288(i);
        u8 *m2 = func_00211288(func_00210DD8(m));
        u64 *out = flagsBase + i;
        s32 total, k, n, s;
        s32 sum0, sum1;

        *out = 0;
        ST(m2, 1, 1);
        ST(m2, 2, 2);
        ST(m2, 4, 4);
        ST(m2, 8, 8);
        ST(m2, 0x10, 0x10);
        ST(m2, 0x20, 0x20);
        if (func_00211310(m, 16, 0x40) && func_00211310(m, 16, 0x80) && func_00211310(m, 16, 0x100) &&
            func_00211310(m, 16, 0x200) && func_00211310(m, 16, 0x400)) {
            *out |= 0x800;
        }
        ST(m, 0x800, 0x2000);
        ST(m, 0x1000, 0x4000);
        ST(m, 0x2000, 0x8000);
        ST(m, 0x4000, 0x10000);
        ST(m, 0x8000, 0x20000);
        ST(m2, 0x10000, 0x80000);
        ST(m, 0x20000, 0x800000);
        ST(m, 0x40000, 0x1000000);
        if (!func_00211310(m, 16, 0x80000)) {
            if (*(s32 *)(D_003876A0 + i * 0x1D0 + 0xE0) >= 2) {
                *out |= 0x2000000;
            }
        }
        if (!func_00211310(m, 16, 0x100000)) {
            *out |= 0x8000000;
        }
        ST(m, 0x200000, 0x20000000);
        ST(m, 0x400000, 0x40000000);
        ST(m, 0x800000, 0x80000000);
        ST(m, 0x1000000, 0x100000000ULL);
        ST(m, 0x2000000, 0x200000000ULL);
        ST(m, 0x4000000, 0x400000000ULL);
        ST(m2, 0x8000000, 0x800000000ULL);
        ST(m, 0x10000000, 0x1000000000ULL);
        ST(m, 0x20000000, 0x2000000000ULL);
        ST(m, 0x40000000, 0x8000000000ULL);
        if (func_00211310(m, 16, (s32)0x80000000)) {
            *out |= 0x10000000000ULL;
        }
        if (*BtlMember_GetActiveGauge(m) == 1) {
            *out |= 0x40;
        }
        if (func_00211310(m, 0, 0x100)) {
            *out |= 0x80;
        }

        total = 0;
        n = *(s32 *)(m + 0x1184);
        if (n > 0) {
            s = 0;
            do {
                s32 off = 0x30;
                s32 c = 4;

                do {
                    s32 *e = func_00202E60(m, s);
                    total += *(s32 *)((u8 *)e + off);
                    off += 4;
                    c--;
                } while (c >= 0);
                s++;
            } while (s < *(s32 *)(m + 0x1184));
        }

        if (*(s32 *)(m + 0x1438) > 0) {
            if (*(s64 *)(m + 0x1448) == 0) {
                if (total == 0) {
                    *out |= 0x100;
                }
            }
        }
        if (*(s32 *)(m + 0x143C) + *(s32 *)(m + 0x1440) >= 0x96) {
            *out |= 0x200;
        }
        if (*(s32 *)(m2 + 0x1440) >= 0x1E) {
            *out |= 0x10000000;
        }
        if (*(s32 *)(m + 0x1444) >= 5) {
            *out |= 0x400;
        }
        if (*(s32 *)(m + 0x1454) > 0) {
            *out |= 0x1000;
        }
        if (*(s32 *)(m + 0x1438) == 0) {
            if (*(s32 *)(m + 0x144C) == 0 && *(s32 *)(m + 0x1448) > 0 && total == 0) {
                *out |= 0x40000;
            }
            if (*(s64 *)(m + 0x1448) == 0) {
                if (total > 0) {
                    *out |= 0x100000;
                }
            }
        }
        if (*(s32 *)(m + 0x1184) > 0) {
            for (s = 0; s < *(s32 *)(m + 0x1184); s++) {
                if (*(s32 *)((u8 *)func_00202E60(m, s) + 0x30) > 0 &&
                    *(s32 *)((u8 *)func_00202E60(m, s) + 0x34) > 0 &&
                    *(s32 *)((u8 *)func_00202E60(m, s) + 0x38) > 0 &&
                    *(s32 *)((u8 *)func_00202E60(m, s) + 0x3C) > 0 &&
                    *(s32 *)((u8 *)func_00202E60(m, s) + 0x40) > 0) {
                    *out |= 0x200000;
                    break;
                }
            }
        }
        if (!(*(s32 *)(m + 0x1450) < *(s32 *)(m + 0x1438))) {
            if (*(s32 *)(m + 0x1448) == 0 && total == 0) {
                *out |= 0x400000;
            }
        }
        if (*(s32 *)(m + 0x1458) > 0) {
            *out |= 0x4000000;
        }
        if (m[0x1464] == 0) {
            *out |= 0x4000000000000ULL;
        }
        if (m[0x1465] != 0) {
            *out |= 0x8000000000000ULL;
        }
        *(s32 *)(a + 0x18 + i * 4) = *(s32 *)(m2 + 0x145C);
        *(s32 *)(a + 0x28 + i * 4) = *(s32 *)(m2 + 0x1460);
        sum0 = 0;
        sum1 = 0;
        for (k = 0; k < *(s32 *)(m + 0x1184); k++) {
            sum0 += *(s32 *)func_00202E60(m, k);
            sum1 += *(s32 *)((u8 *)func_00202E60(m, k) + 4);
        }
        pct[i] = ((f32)sum0 / (f32)sum1) * 100.0f;
        i++;
    }
    return 0;
}
