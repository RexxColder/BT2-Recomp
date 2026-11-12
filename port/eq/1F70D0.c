#include "common.h"

s32 func_00211270(void);
u8 *func_00211288(s32 arg0);
s32 func_0020A658(s32 arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);

void func_001F70D0(void) {
    s32 idx = 0;

    while (idx < func_00211270()) {
        s32 i = idx;
        u8 *s1 = func_00211288(idx);
        u8 *s0;

        idx += 1;
        s0 = *(u8 **)(s1 + 0x1530) + 0xE50;
        *(s32 *)s0 = *(s32 *)s0 & ~0x800;
        if (func_0020A658(i) != 0 || func_00211310(s1, 5, 0x20) != 0 || func_00211310(s1, 6, 2) != 0 ||
            func_00211310(s1, 3, 0x800) != 0) {
            *(s32 *)s0 = *(s32 *)s0 | 0x800;
        }
    }
}
