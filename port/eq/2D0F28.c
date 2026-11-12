#include "common.h"

s32 func_002C3210(s32 arg0);
void func_002D0FB0(s32 arg0);
extern u8 D_00346DD8[] __attribute__((section(".data")));

void func_002D0F28(void) {
    s32 base;
    s32 var_s1;
    s32 var_s0;
    s32 var_s2;

    base = (s32) D_00346DD8;
    var_s2 = 7;
    *(s32 *) base = *(s32 *) base + 1;
    var_s1 = base + 0x54;
    var_s0 = *(s32 *) var_s1;
    for (;;) {
        var_s1 += 4;
        if (func_002C3210(var_s0) != -1) {
            func_002D0FB0(var_s0);
        }
        var_s2 -= 1;
        if (var_s2 < 0) {
            break;
        }
        var_s0 = *(s32 *) var_s1;
    }
}
