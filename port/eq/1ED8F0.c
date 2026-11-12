#include "common.h"

s32 func_0012B9B0(s32 arg0, s32 arg1, s64 arg2, s32 arg3);
s32 func_001ED2D8(s32 arg0, s32 arg1, s32 arg2);
void func_0012D868(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_001EE8B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s64 arg9, s32 arg10);

void func_001ED8F0(u8 *arg0, s32 arg1, s64 arg2, s32 arg3) {
    u8 sp[0x1A0];
    s32 s0;
    s32 s3;
    s32 s5;
    s32 o;
    s32 t;
    s32 f1;
    s32 f2;
    s32 f3;
    u8 *s4;

    *(s64 *)(sp + 0x140) = arg2;
    *(s32 *)(sp + 0x148) = arg3 & 0xFF;
    s0 = func_0012B9B0((s32)arg0, arg1, arg2, arg3 & 0xFF);
    s3 = 4;
    s5 = 3;
    do {
        s3 -= 1;
        t = func_001ED2D8(s0, s5, (s32)arg0);
        s0 += 0x10;
        s5 = t;
    } while (s3 >= 0);
    if (s5 != 0) {
        s3 = 2;
        func_0012D868((s32)(sp + 0x20), arg1, (s32)arg0, s5, (s32)(sp + 0xB0), (s32)(arg0 + 0x90));
        if (s5 > 2) {
            s4 = sp + 0x38;
            o = 0x20;
            do {
                if (*(s32 *)(sp + 0x28) > 0xFFFFFF) {
                    *(s32 *)(sp + 0x28) = 0xFFFFFF;
                }
                if (*(s32 *)s4 > 0xFFFFFF) {
                    *(s32 *)s4 = 0xFFFFFF;
                }
                if (*(s32 *)(sp + 0x20 + o + 8) > 0xFFFFFF) {
                    *(s32 *)(sp + 0x20 + o + 8) = 0xFFFFFF;
                }
                f1 = 1;
                if (*(s32 *)(sp + 0x28) > 0) {
                    if (*(s32 *)(sp + 0x20) <= 0xFFEF && *(s32 *)(sp + 0x20) > 0) {
                        f1 = (*(s32 *)(sp + 0x24) <= 0xFFEF) ? (*(s32 *)(sp + 0x24) < 1) : 1;
                    }
                }
                if (f1 != 0) {
                    f2 = 1;
                    if (*(s32 *)(sp + 0x38) > 0 && *(s32 *)(sp + 0x30) <= 0xFFEF && *(s32 *)(sp + 0x30) > 0) {
                        f2 = (*(s32 *)(sp + 0x34) <= 0xFFEF) ? (*(s32 *)(sp + 0x34) < 1) : 1;
                    }
                    f3 = 1;
                    if (f2 != 0) {
                        if (*(s32 *)(sp + 0x48) > 0 && *(s32 *)(sp + 0x40) <= 0xFFEF && *(s32 *)(sp + 0x40) > 0) {
                            f3 = (*(s32 *)(sp + 0x44) <= 0xFFEF) ? (*(s32 *)(sp + 0x44) < 1) : 1;
                        }
                    }
                } else {
                    f2 = 0;
                    f3 = 0;
                }
                if (!(f1 != 0 && f2 != 0 && f3 != 0)) {
                    t = (s32)(sp + 0x20 + o);
                    func_001EE8B0((s32)(sp + 0x20), t - 0x10, t, (s32)(arg0 + 0x120),
                                  (s32)(arg0 + o + 0x110), (s32)(arg0 + o + 0x120),
                                  (s32)(sp + 0xB0), (s32)(sp + 0xB0 + o - 0x10),
                                  (s32)(sp + 0xB0 + o), *(s64 *)(sp + 0x140), *(s32 *)(sp + 0x148));
                }
                s3 += 1;
                o += 0x10;
                s4 += 0x10;
            } while (s3 < s5);
        }
    }
}
