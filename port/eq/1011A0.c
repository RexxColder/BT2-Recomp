#include "common.h"

s32 func_002EB9B0(s32 arg0, s32 arg1);
s32 func_002EC6B0(s32 arg0);
void func_002EBB08(s32 arg0);
extern s32 D_00387F20[] __attribute__((section(".data")));

s32 func_001011A0(s32 arg0) {
    s32 s1 = (arg0 < 0x33B2) ? 0 : 4;
    s32 s2 = (arg0 < 0x33B2) ? arg0 : arg0 - 0x33B2;
    s32 r;
    s32 t;

    do {
        r = func_002EB9B0(D_00387F20[s1 / 4], s2);
    } while (r == 0);
    t = func_002EC6B0(r) << 11;
    func_002EBB08(r);
    return t;
}
