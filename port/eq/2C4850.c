#include "common.h"

s32 func_002C0690(s32 arg0, s32 arg1);
void func_002C4720(s32 arg0, s32 arg1);
s32 func_002C4998(s32 arg0, s32 arg1);
void func_002C49E8(s32 arg0, s32 arg1);
s32 func_002DC538(s32 arg0);

s32 func_002C4850(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    u8 *s0;
    u8 *s4;
    s32 s3;
    s32 s1;
    s32 v1;

    s0 = (u8 *)arg0 + 0x1F74;
    s4 = *(u8 **)(s0 + 8);
    s3 = *(s32 *)(s0 + 0x10);

    if (arg2 >= 4) {
        s1 = func_002DC538(arg1);
        if (s1 == 0x80000) {
            if (*(s32 *)(s0 + 0x20) < 0) {
                *(s32 *)(s0 + 0x20) = func_002C0690(arg0, s3) + 4;
            }
            *(s32 *)(s4 + 0x3C) = 1;
        } else if (s1 != 0) {
            *(s32 *)(s4 + 0x3C) = 0;
        }
    } else {
        s1 = 0;
    }

    if (func_002C4998(arg0, s1) != 0) {
        func_002C4720(arg0, 1);
        return 0;
    }

    v1 = arg2 < 0x40;
    if (arg3 < 4) {
        func_002C49E8(arg0, (s32)sp);
        if (sp[0] != 0) {
            return 0;
        }
        v1 = arg2 < 0x40;
    }

    if (v1 != 0 && (s1 == 0x10000 || s1 == 0x40000)) {
        func_002C49E8(arg0, 0);
        return 0;
    }
    return 1;
}
