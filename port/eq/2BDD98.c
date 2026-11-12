#include "common.h"

s32 func_002BE3A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002BE000(s32 arg0, s32 arg1, s32 arg2);
s32 func_002BE088(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D1270(s32 arg0, s64 arg1);
s32 func_002D07B0(s32 arg0, s32 arg1);
s32 func_002D12D0(s32 arg0, s32 arg1, s32 arg2);
void func_002D1348(s32 arg0, s32 arg1, s32 arg2);
void func_002D05E8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002F6B50(s32 arg0, s32 arg1, s32 arg2);
extern void func_002BDCE0(void);

void func_002BDD98(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 o0;
    s32 o4;
    s32 o8;
    s32 oC;
    s32 o10;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s6;
    s32 sz;
    s32 d;
    s32 q;
    s32 tmp;
    s32 rem;
    s32 v0;
    s32 v1;
    s32 a;
    s32 t;
    s64 g;

    *arg3 = 0;
    s1 = arg0 + 0xD30;
    s3 = *(s32 *)(arg0 + 0x2004);
    if (func_002BE3A0(arg0, (s32)&o0, (s32)&o4) != 0) {
        goto block6;
    }
    s2 = func_002D1270(s1, o4);
    if (s2 < 0) {
        return;
    }
    if (func_002D07B0(arg0, 5) == 0) {
        func_002D1348(s1, s2, o4);
        goto block6;
    }
    s0 = func_002D12D0(s1, o4, (s32)&o8);
    if (s0 < 0) {
        return;
    }
    func_002D1348(s1, s0, o4);
    s6 = 0;
    v1 = s0 - s2;
    v0 = *(s32 *)(s3 + 0x38);
    v1 = v1 - v0;
    if (v1 >= 0) {
        sz = ((v1 >> 5) * o0) * 18;
        oC = 0;
        if (sz > 0) {
            d = o0 * 18;
            q = arg2 / d;
            tmp = (q * o0) * 18;
            if (tmp < sz) {
                rem = tmp;
            } else {
                rem = sz;
            }
            s0 = sz - rem;
            s6 = func_002BE000(arg1, rem, (s32)&oC);
            *(s32 *)(s3 + 0x38) = *(s32 *)(s3 + 0x38) + ((s6 / (o0 * 18)) << 5);
            if (s0 > 0) {
                goto L_DF44;
            }
        }
        if (o8 != 0) {
            *(s32 *)(s3 + 0x3C) = (s32)func_002BDCE0;
            oC = func_002F6B50(arg1, arg2, (s32)&o10);
        }
L_DF44:
        if (oC != 0) {
            func_002D05E8(arg0, 6, 0);
        }
        goto L_store;
    } else {
        if (o8 == 0) {
            goto L_store;
        }
        a = -v1;
        if (a < 0) {
            t = ((a + 0x1F) >> 5) << 5;
        } else {
            t = (a >> 5) << 5;
        }
        if (t <= 0) {
            *(s32 *)(s3 + 0x3C) = (s32)func_002BDCE0;
        } else {
            v0 = func_002BE088(arg0, o0, t);
            *(s32 *)(s3 + 0x38) = *(s32 *)(s3 + 0x38) - v0;
            if (t - v0 <= 0) {
                *(s32 *)(s3 + 0x3C) = (s32)func_002BDCE0;
            }
        }
        goto L_store;
    }

L_store:
    g = *(s64 *)(arg0 + 0x9C8);
    *arg3 = s6;
    *(s64 *)(arg0 + 0x9C8) = (s64)s6 + g;
    return;

block6:
    *(s32 *)(s3 + 0x3C) = (s32)func_002BDCE0;
}
