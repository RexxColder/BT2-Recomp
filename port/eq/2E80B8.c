#include "common.h"

void func_002E7FB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002E8008(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002E8060(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002E80B8(s32 arg0) {
    s32 a;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 t6;
    s32 t7;
    s32 v1;
    s32 lo;
    s32 lo2;
    s32 lo3;
    s32 a1;
    s32 a3;

    a = arg0 + 0x48;
    t6 = *(s32 *)(a + 0x8);
    t7 = *(s32 *)(a + 0x18);
    lo = *(s32 *)(a + 0x4) / t6;
    t0 = *(s32 *)(a + 0x20);
    t1 = *(s32 *)(a + 0x10);
    a3 = *(s32 *)(a + 0x28);
    v1 = (a3 + t1) - 1;
    t4 = *(s32 *)(a + 0x24);
    a3 = a3 < t4;
    lo2 = v1 / t1;
    t3 = (((t7 - t0) + t1) - 1) / t1;
    a1 = (t1 - (v1 % t1)) - 1;
    if (lo2 < t3) {
        t3 += ((t0 + (t3 * t1)) - a1) < t7;
    }
    lo3 = ((a3 * a1) + t4) / t1;
    t2 = (lo3 < lo) ? lo3 : lo;
    t2 = (lo2 < t2) ? lo2 : t2;
    t2 = (t3 < t2) ? t3 : t2;
    if (t6 == 2) {
        func_002E8008(arg0, t2, 2, a3);
        return;
    }
    if (*(s32 *)(arg0 + 0xE8) != 0) {
        func_002E8060(arg0, t2, 2, a3);
        return;
    }
    func_002E7FB8(arg0, t2, 2, a3);
}
