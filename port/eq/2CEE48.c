#include "common.h"

s32 func_002C3210(s32 arg0, s32 arg1, s32 arg2);
void func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002CF170(s32 arg0, s32 arg1);
s64 func_002D2750(void);
s32 func_002D2FC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void (*D_00346E6C)(s32, s32) __attribute__((section(".data")));

s32 func_002CEE48(s32 arg0, s32 arg1, s32 arg2) {
    void (*fp)(s32, s32);

    *(s32 *)arg2 = 0;
    *(s32 *)arg1 = -1;
    if (func_002C3210(arg0, arg1, arg2) != 0) {
        func_002C2FF0(0, 0xFF00013A);
        return 0;
    }
    if (func_002CF170(arg0, 2) != 0) {
        return 0;
    }
    func_002D2FC8(arg0, 6, 0xB, arg2, arg1);
    fp = D_00346E6C;
    if (fp != NULL) {
        fp(arg0, *(s32 *)arg2);
    }
    if (*(s32 *)arg2 == 0) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0x968) == 0) {
        *(s64 *)(arg0 + 0x3780) = func_002D2750();
    }
    *(s32 *)(arg0 + 0x968) = *(s32 *)(arg0 + 0x968) + 1;
    return 1;
}
