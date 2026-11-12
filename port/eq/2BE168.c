#include "common.h"

s32 func_002F6B50(s32 arg0, s32 arg1, s32 *arg2);
void func_002C2FF0(s32 arg0, s32 arg1);

u32 func_002BE168(s32 arg0, u32 arg1, s32 arg2) {
    s32 sp[4];
    u32 s0;
    u32 s1;
    u32 s5;
    u32 s6;
    u32 s7;
    s32 s3;

    s1 = arg1;
    s7 = arg1 + 0x24;
    s5 = 0;
    s6 = 0;
    s3 = 0;
    if (s1 < s7) {
        do {
            s0 = s1;
            while (s0 < arg1 + arg2) {
                if (*(s8 *)s0 >= 0) {
                    s0 += 0x12;
                    continue;
                }
                s3 = 1;
                if (func_002F6B50(s0, 0x12, sp) != 0 && s5 < s0) {
                    s5 = s0;
                    s6 = s1;
                }
                break;
            }
            if (s3 == 0) {
                return s1;
            }
            s1 += 2;
            if (!(s1 < s7)) {
                break;
            }
            s3 = 0;
        } while (1);
    }
    if (s3 == 0) {
        return s1;
    }
    if (s6 != 0) {
        return s6;
    }
    func_002C2FF0(arg0, 0xFF000C0A);
    return arg1;
}
