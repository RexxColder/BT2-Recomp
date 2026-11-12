#include "common.h"

void EftGlow_CalcFrame(s32 arg0, s32 arg1, s32 arg2);
void func_00128900(s32 arg0, s32 arg1);

void EftGlow_UpdateFrames(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg0 + 0x100;
    if (*(s32 *) arg0 & 2) {
        var_s1 = 4;
        do {
            var_s1 -= 1;
            func_00128900(var_s0 + 0x50, var_s0 + 0x10);
            var_s0 -= 0x40;
        } while (var_s1 > 0);
        return;
    }
    EftGlow_CalcFrame(arg0 + 0x50, arg1, *(s32 *) (arg0 + 0xC));
    var_s1 = 4;
    do {
        var_s1 -= 1;
        func_00128900(var_s0 + 0x50, var_s0 + 0x10);
        var_s0 -= 0x40;
    } while (var_s1 > 0);
}
