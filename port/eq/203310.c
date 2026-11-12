#include "common.h"

#define RNE_S32(x) ({ f32 _t = (x); s32 _i = (s32)_t; f32 _d = _t - (f32)_i; if (_d > 0.5f || (_d == 0.5f && (_i & 1))) { _i++; } else if (_d < -0.5f || (_d == -0.5f && (_i & 1))) { _i--; } _i; })

extern u8 *D_003876A0;
extern f32 D_003858F8;
extern f32 D_003858FC;

u8 *BtlMember_GetActiveGauge(u8 *arg0);
s32 BtlObjXf_Update(u8 *arg0);
s32 func_001FA3A8(s32 arg0);
s32 func_001F9940(u8 *arg0);
f32 func_0023FCC8(u8 *arg0);
s32 func_00203C58(u8 *arg0, s64 arg1);
void func_00203C88(u8 *arg0, s64 arg1);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
void func_002113C0();

s32 func_00203310(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *p;
    u8 *s3;
    s32 m0;
    s32 m;
    s32 s1;
    s32 w;
    s32 r;
    s32 v;
    s32 v1;
    s32 v2;
    s32 a0v;
    f32 f0;
    f32 f1;
    f32 f2;

    s1 = arg1;
    s3 = arg0 + 0xBC0;
    p = BtlMember_GetActiveGauge(arg0);
    m0 = *(s32 *)p;

    if (!(arg2 & 0x8000)) {
        r = BtlObjXf_Update(arg0);
        if (func_001FA3A8(r) & 0x100000) {
            s1 = s1 / 2;
        }
    }

    if (!(arg2 & 1)) {
        r = func_001F9940(arg0);
        s1 = (s1 * r) / 100;
        f1 = (f32)s1;
        f0 = func_0023FCC8(arg0);
        f1 = f1 * f0;
        s1 = RNE_S32(f1);
    }

    /* 2033D0 */
    if (s1 <= 0) {
        if (!(arg2 & 0x10000)) {
            return 0;
        }
        s1 = 0;
    }

    r = func_00211310(arg0, 0, 0x400000);
    if (r == 0 && !(arg2 & 0x40)) {
        return 0;
    }

    /* L414 */
    if (!(arg2 & 2)) {
        if (s1 >= 10) {
            v = s1 % 10;
            if (v != 0) {
                s1 = s1 - v + 10;
            }
        }
    }

    /* L450 */
    w = *(s32 *)(D_003876A0 + 0xB8);
    if ((u32)(w - 4) < 2) {
        if ((*(s32 *)p - 1) < s1) {
            s1 = *(s32 *)p - 1;
        }
    }

    r = func_00203C58(arg0, 0x400);
    if (r != 0 && (*(s32 *)p - 1) < s1) {
        s1 = *(s32 *)p - 1;
        func_00203C88(arg0, 0x400);
    }

    r = func_00203C58(arg0, 0x10000);
    m = *(s32 *)p;
    if (r != 0 && (m - 1) < s1) {
        s1 = m - 1;
        func_00203C88(arg0, 0x10000);
        *(s32 *)(arg0 + 0x1528) = 0x5A;
        m = *(s32 *)p;
    }

    if (arg2 & 4) {
        if ((m - 1) < s1) {
            s1 = m - 1;
        }
        r = func_00203C58(arg0, 0x20000000);
        m = *(s32 *)p;
        if (r != 0) {
            s1 = 0;
        }
    }

    /* 203508 */
    v = m - s1;
    *(s32 *)p = v;
    if (arg2 & 8) {
        if (s1 > 0 || (arg2 & 0x10000)) {
            goto L530;
        }
        goto L5F4;
    }
    goto L570;

L530:
    if (arg2 & 0x10) {
        a0v = *(s32 *)s3;
        goto L5F8;
    }
    *(s32 *)s3 = *(s32 *)s3 + s1;
    if (arg2 & 0x20) {
        goto L5EC;
    }
    f0 = (f32)*(s32 *)s3 * 30.0f * D_003858F8;
    goto L5CC;

L570:
    if (s1 > 0 || (arg2 & 0x10000)) {
        v = *(s32 *)(s3 + 4);
        goto L58C;
    }
    a0v = *(s32 *)s3;
    goto L5F8;

L58C:
    v = v + 1;
    *(s32 *)(s3 + 4) = v;
    if (!(v < 0x64)) {
        v = 0x63;
        *(s32 *)(s3 + 4) = v;
    }

L5A4:
    v = *(s32 *)s3 + s1;
    f1 = D_003858FC;
    f0 = (f32)v;
    *(s32 *)s3 = v;
    f0 = f0 * 30.0f * f1;

L5CC:
    v2 = RNE_S32(f0) + 0x1E;
    *(s32 *)(s3 + 8) = (v2 < 0x5B) ? v2 : 0x5A;

L5EC:
    *(u8 *)(s3 + 0x14) = 1;

L5F4:
    a0v = *(s32 *)s3;

L5F8:
    if (a0v > 0x1869F) {
        *(s32 *)s3 = 0x1869F;
        a0v = 0x1869F;
    }
    v = *(s32 *)(s3 + 4);
    *(s32 *)(s3 + 0xC) = a0v;
    *(s32 *)(s3 + 0x10) = v;
    *(u8 *)(s3 + 0x15) = (arg2 >> 2) & 1;

    /* 203620 */
    m = *(s32 *)p;
    if (m < 0) {
        *(s32 *)p = 0;
        m = 0;
    }
    if (m0 <= 0) {
        v = *(s32 *)(arg0 + 0x145C);
        goto L734;
    }
    if (m != 0) {
        v = *(s32 *)(arg0 + 0x145C);
        goto L734;
    }

    if (arg2 & 0x80) {
        func_002113C0(arg0, 0x10, 4, 1);
    }
    if (arg2 & 0x100) {
        func_002113C0(arg0, 0x10, 4, 1);
    }
    if (arg2 & 0x200) {
        func_002113C0(arg0, 0x10, 2, 1);
    }
    if (arg2 & 0x400) {
        func_002113C0(arg0, 0x10, 2, 1);
    }
    if (arg2 & 0x800) {
        func_002113C0(arg0, 0x10, 1, 1);
    }
    if (arg2 & 0x1000) {
        func_002113C0(arg0, 0x10, 8, 1);
    }
    if (arg2 & 0x2000) {
        func_002113C0(arg0, 0x10, 0x10, 1);
    }
    if (arg2 & 0x4000) {
        func_002113C0(arg0, 0x10, 0x20, 1);
    }
    v = *(s32 *)(arg0 + 0x145C);

L734:
    v1 = *(s32 *)s3;
    if (v < v1) {
        *(s32 *)(arg0 + 0x145C) = v1;
    }

    v1 = *(s32 *)(s3 + 4);
    v = *(s32 *)(arg0 + 0x1460);
    if (v < v1) {
        *(s32 *)(arg0 + 0x1460) = v1;
    }

    if (s1 > 0) {
        *(u8 *)(arg0 + 0x1464) = 1;
    }
    if (*(s32 *)p != 0) {
        return m0 - m;
    }
    *(s32 *)(p + 0x1C) = 0;
    *(s32 *)(p + 0xC) = 0;
    *(s32 *)(p + 0x14) = 0;
    *(s32 *)(arg0 + 0xB74) = 0;
    func_002113C0(arg0, 0, 0x4000, 0);
    return m0 - m;
}
