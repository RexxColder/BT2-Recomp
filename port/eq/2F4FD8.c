#include "common.h"

s32 func_002EA050(s32 arg0);
s32 func_002EFF30(s32 arg0, s32 arg1, s32 arg2);
s32 func_002F14E0(s32 arg0);
s32 func_002F1688(s32 arg0, s32 arg1);
extern s32 D_0034AED0 __attribute__((section(".data")));
extern s32 D_0037C920 __attribute__((section(".data")));
extern s32 D_0037C950 __attribute__((section(".data")));

void func_002F4FD8(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a2;
    s32 var_s1;

    if (arg0 == 0) {
        func_002EA050((s32)&D_0037C920);
        return;
    }
    var_s1 = 0;
    if (*(s8 *)(arg0 + 0xAD) == 1) {
        var_s1 = func_002F1688(*(s32 *)(arg0 + 4), arg1);
        if (var_s1 == -0x80) {
            var_s1 = 0;
        }
    }
    var_a2 = 0;
    if (D_0034AED0 == 0) {
        if (arg2 != -0x80) {
            var_a2 = arg2 + var_s1;
        } else {
            if (func_002F14E0(*(s32 *)(arg0 + 4)) != 2) {
                var_a2 = 0 + var_s1;
            } else {
                var_a2 = ((arg1 != 0) ? 0xF : -0xF) + var_s1;
            }
        }
    }
    *(s16 *)(arg0 + arg1 * 2 + 0x42) = (s16)arg2;
    if (arg1 < *(s8 *)(arg0 + 3)) {
        func_002EFF30(*(s32 *)(arg0 + 0xC), arg1, var_a2);
        return;
    }
    func_002EA050((s32)&D_0037C950);
}
