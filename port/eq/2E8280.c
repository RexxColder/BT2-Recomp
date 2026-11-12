#include "common.h"

s32 func_002F8F18(s32 a0);
s32 func_002E81F0(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_002E8260(s32 a0, s32 a1, s32 a2, s32 a3);

s32 func_002E8280(u8 *arg0) {
    u8 *s4;
    s32 n;
    s32 m;
    s32 t;
    s32 v44;
    s32 s7;
    s32 quo;
    s32 rem;
    s32 fp;
    s32 s3;
    s32 s5;
    s32 ret;
    s32 v1;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 cmp;

    s4 = arg0 + 0x48;
    n = *(s32 *)(s4 + 0x10);
    m = *(s32 *)(s4 + 0x28);
    t = (s32)((u32)m + (u32)n - 1u);
    v44 = *(s32 *)(arg0 + 0x44);
    s7 = *(s32 *)(arg0 + 0x40);
    quo = t / n;
    rem = t % n;
    fp = *(s32 *)(s4 + 0x14);
    s3 = *(s32 *)(s4 + 0xC);
    s5 = *(s32 *)(s4 + 0x20);
    ret = func_002F8F18(*(s32 *)(arg0 + 0x8));
    v1 = *(s32 *)(s4 + 0x8);
    s0 = n - rem - 1;
    s1 = (s32)((u32)ret * (u32)n);
    s2 = (s32)((u32)quo * (u32)v1);
    s3 = (s32)((u32)ret * (u32)s3);
    *(s32 *)(arg0 + 0x94) = s3;
    s1 = s1 / v1;
    cmp = ret < s2;
    s0 = s1 - s0;
    if (cmp) {
        s0 = s1;
    }
    *(s32 *)(arg0 + 0x90) = s0;
    s5 = (s32)((u32)s5 + (u32)s0);
    if (s5 < s7) {
        s5 = (s32)((u32)s5 - (u32)s7);
        return 1;
    }
    s5 = (s32)((u32)s5 - (u32)s7);
    if (v1 == 2 || *(s32 *)(arg0 + 0xE8) != 0) {
        return func_002E81F0(fp, s7, v44, s5);
    }
    return func_002E8260(fp, s7, v44, s5);
}
