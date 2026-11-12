#include "common.h"

void func_0026DF68(s32 arg0, s32 arg1, s32 arg2);

void func_0026FE60(s32 arg0, s32 arg1) {
    u32 var_s2;
    s32 var_s1;

    var_s2 = 0;
    if (*(u32 *)(arg0 + 4) != 0) {
        var_s1 = 0;
        do {
            var_s2 += 1;
            func_0026DF68(*(s32 *)arg0 + var_s1 + 0xA8, arg1, 1);
            var_s1 += 0xC0;
        } while (var_s2 < *(u32 *)(arg0 + 4));
    }
}
