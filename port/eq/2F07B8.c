#include "common.h"

s32 func_002E7AB0(s32 arg0);
s32 func_002E7AC8(s32 arg0);
s32 func_00305360(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

typedef s32 (*VFn4)(s32, s32, s32, s32);

s32 func_002F07B8(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 i;
    s32 cnt;
    s32 ok;
    s32 s4;
    s32 a3v;
    s32 elem;
    s32 r;
    s32 v0;
    s32 a0v;
    s32 t;
    u8 *s0;
    u8 *s1p;

    i = 0;
    s0 = arg0 + 0xC;
    s1p = arg0 + 0x1C;
    s4 = *(s32 *)(arg0 + 0xC);
    for (;;) {
        cnt = func_002E7AC8(*(s32 *)(arg0 + 4));
        ok = (i < cnt);
        i += 1;
        a3v = (s32)s1p;
        s1p += 8;
        if (!ok) {
            break;
        }
        elem = *(s32 *)s0;
        s0 += 4;
        ((VFn4)(*(s32 *)(*(s32 *)elem + 0x18)))(elem, 0, 0x4000, a3v);
    }
    r = func_00305360(s4, 0, 0x4000, a3v);
    *arg1 = (*(s32 *)(arg0 + 0x1C) - r) / 2;
    v0 = *(s32 *)(arg0 + 0x20) / 2;
    a0v = *(s32 *)(arg0 + 0x38);
    *arg2 = (v0 < a0v) ? v0 : a0v;
    t = *(s32 *)(arg0 + 0x3C);
    if (t < 0) {
        *arg3 = 0x1FFFFFFF;
    } else {
        *arg3 = t - *(s32 *)(arg0 + 0x40);
    }
    return func_002E7AB0(*(s32 *)(arg0 + 4));
}
