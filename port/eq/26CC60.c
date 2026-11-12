#include "common.h"

void func_0026C9F0(s32 arg0, s32 arg1);
s32 func_0026CA00(s32 arg0, s32 arg1);

s32 func_0026CC60(s32 arg0, u32 arg1) {
    s32 temp_s2;
    s32 var_s1;
    u32 var_a0;
    u8 *p;

    var_s1 = 0;
    temp_s2 = func_0026CA00(arg0, 4);
    func_0026C9F0(arg0, 4);
    var_a0 = 0;
    if (arg1 != 0) {
        do {
            p = (u8 *)(temp_s2 + var_s1);
            var_s1 += 2;
            var_a0 += 1;
            var_s1 += (s32)(p[0] | (p[1] << 8));
        } while (var_a0 < arg1);
    }
    return temp_s2 + (var_s1 + 2);
}
