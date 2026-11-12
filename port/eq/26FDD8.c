#include "common.h"

void func_0026DEB8(s32 arg0);
void func_0028BB60(s32 arg0);

void func_0026FDD8(s32 arg0) {
    s32 temp_a0_2;
    s32 var_s1;
    u32 var_s2;

    var_s2 = 0;
    if (*(u32 *) (arg0 + 4) != 0) {
        var_s1 = 0;
        do {
            var_s2 += 1;
            func_0026DEB8(*(s32 *) arg0 + var_s1 + 0xA8);
            var_s1 += 0xC0;
        } while (var_s2 < *(u32 *) (arg0 + 4));
    }
    temp_a0_2 = *(s32 *) arg0;
    if (temp_a0_2 != 0) {
        func_0028BB60(temp_a0_2);
        *(s32 *) arg0 = 0;
    }
}
