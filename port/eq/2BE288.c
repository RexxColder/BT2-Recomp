#include "common.h"

s32 func_002BE3A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C2D60(s32 arg0);
s32 memcmp(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037A020 __attribute__((section(".data")));
extern s32 func_002BE0A8 __attribute__((section(".data")));

void func_002BE288(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 sp[2];
    s32 var_s0;
    s32 var_s1;
    s32 s4;
    s32 r;

    var_s0 = arg1;
    *arg3 = 0;
    s4 = *(s32 *)(arg0 + 0x2004);
    var_s1 = 0;
    if (func_002C2D60(arg0) >= 0x6C) {
        *(s32 *)(s4 + 0x3C) = (s32)&func_002BE0A8;
    } else {
        if (var_s1 < (arg2 - 0x12)) {
            do {
                r = memcmp(var_s0, (s32)&D_0037A020, 0x12);
                var_s0 += 0x12;
                if (r != 0) {
                    *(s32 *)(s4 + 0x3C) = (s32)&func_002BE0A8;
                    break;
                }
                var_s1 += 0x12;
            } while (var_s1 < (arg2 - 0x12));
        }
        *arg3 = var_s1;
        *(s64 *)(arg0 + 0x9C8) = (s64)var_s1 + *(s64 *)(arg0 + 0x9C8);
        if (func_002BE3A0(arg0, (s32)&sp[0], (s32)&sp[1]) == 0) {
            *(s32 *)(s4 + 0x38) = *(s32 *)(s4 + 0x38) + ((var_s1 / (sp[0] * 0x12)) << 5);
        }
    }
}
