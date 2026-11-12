#include "common.h"

s32 func_002F4FD8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002F5138(s32 arg0, s32 arg1);
void func_002F51B8(s32 arg0, s32 arg1);
s32 func_002F5278(s32 arg0);
extern s32 D_0034AED0 __attribute__((section(".data")));
extern u8 D_0034AEE0[] __attribute__((section(".data")));

void func_002F6D90(s32 arg0) {
    u8 *var_s1;
    s32 var_s0;
    s32 var_a1;
    s32 var_s2;
    s32 temp_a1;

    D_0034AED0 = arg0;
    var_s1 = D_0034AEE0;
    var_s2 = 0xF;
    do {
        if (*(s8 *)(var_s1 + 0) == 1) {
            var_s0 = 0;
            if (*(s8 *)(var_s1 + 3) > 0) {
                var_a1 = 0;
                do {
                    temp_a1 = var_s0;
                    var_s0 += 1;
                    func_002F4FD8((s32)var_s1, temp_a1, func_002F5138((s32)var_s1, var_a1));
                    var_a1 = var_s0;
                } while (var_s0 < *(s8 *)(var_s1 + 3));
            }
            func_002F51B8((s32)var_s1, func_002F5278((s32)var_s1));
        }
        var_s2 -= 1;
        var_s1 += 0xC8;
    } while (var_s2 >= 0);
}
