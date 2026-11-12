#include "common.h"

void func_001E12C0(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);

void func_001DFE00(u8 *arg0, s32 arg1, s32 arg2, f32 farg0) {
    s32 var_s2;
    u8 *var_s1;

    if (*(u8 *)(arg0 + 0x21DA) != 0) {
        var_s2 = 0;
        if (*(u8 *)(arg0 + 0x21CC) != 0) {
            var_s1 = arg0;
            do {
                var_s2 += 1;
                func_001E12C0((s32)var_s1, arg1, arg2 & 0xFF, *(f32 *)(arg0 + 0x21D0), farg0);
                var_s1 += 0x1B0;
            } while (var_s2 < *(u8 *)(arg0 + 0x21CC));
        }
    }
}
