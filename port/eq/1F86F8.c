#include "common.h"

extern u8 *D_003876A0;

s32 func_0020A658(s32 arg0);
s32 func_00211270(void);
s32 func_00211288(s32 arg0);

/* 0x001F86F8: returns when the 64-bit word at D_003876A0 + 0x4D8 has bit 13 set. Otherwise for i = 0 while i <
 * func_00211270(): when func_0020A658(i) == 0, func_00211288(i) is called. */
void func_001F86F8(void) {
    s32 i;
    s64 flags;

    flags = *(s64 *)(D_003876A0 + 0x4D8);
    if (flags & 0x2000) {
        return;
    }
    for (i = 0; i < func_00211270(); i++) {
        if (func_0020A658(i) == 0) {
            func_00211288(i);
        }
    }
}
