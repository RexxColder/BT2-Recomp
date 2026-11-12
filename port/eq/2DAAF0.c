#include "common.h"

void func_002DABF8(s32 arg0, s32 arg1, s32 arg2);
void func_002DB060(s32 arg0, s32 arg1, s32 arg2);
void func_002DB8D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002DC538(s32 arg0);

/* 0x002DAAF0: *arg3 = 0; v = func_002DC538(arg1); *arg4 = v. v == 0x20000: func_002DB060(arg0, arg1, arg3), return 1.
 * v == 0x40000: func_002DB8D0(arg0, arg1, arg3, word +0x10); when the function word at +0xF4 is set, it is called
 * with (word +0xF8, byte +0xB8, 64-bit +0xA8). v == 0x10000: func_002DABF8(arg0, arg1, arg3), return 1. Else 0.
 * arg2 is not read. */
s32 func_002DAAF0(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4) {
    s32 v;

    (void)arg2;
    *arg3 = 0;
    v = func_002DC538(arg1);
    *arg4 = v;
    if (v == 0x20000) {
        func_002DB060((s32)arg0, arg1, (s32)arg3);
        return 1;
    }
    if (v > 0x20000) {
        if (v == 0x40000) {
            func_002DB8D0((s32)arg0, arg1, (s32)arg3, *(s32 *)(arg0 + 0x10));
            if (*(s32 *)(arg0 + 0xF4) != 0) {
                s32 (*fp)(s32, s32, s64) = *(s32 (**)(s32, s32, s64))(arg0 + 0xF4);
                fp(*(s32 *)(arg0 + 0xF8), *(u8 *)(arg0 + 0xB8), *(s64 *)(arg0 + 0xA8));
            }
        }
        return 0;
    }
    if (v == 0x10000) {
        func_002DABF8((s32)arg0, arg1, (s32)arg3);
        return 1;
    }
    return 0;
}
