#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_0020D408(s32 arg0, s32 arg1);

void func_00152960(s32 arg0, u8 *arg1) {
    s32 var_s0;

    var_s0 = -1;
    if (*(s32 *)(*(u8 **)(arg1 + 0x20) + 4) == 0) {
        if (EftShot_TestBits(arg0, 2) != 0) {
            var_s0 = ((*(s32 *)(*(u8 **)(arg1 + 0x20)) ^ 0x23) != 0) ? 0 : -1;
        }
        var_s0 = (EftShot_TestBits(arg0, 4) != 0) ? 1 : var_s0;
    }
    if (var_s0 >= 0) {
        func_0020D408(arg0, var_s0);
    }
}
