#include "common.h"

s32 func_0026F7A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0026F888(s32 arg0);

/* 0x0026C4F8(slot, a1, a2, a3, t0): when *slot != 0, func_0026F888(*slot) and *slot = 0. Then
 * *slot = func_0026F7A0(*(t0 + 0x20), a1, a2, a3). */
void func_0026C4F8(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    if (*arg0 != 0) {
        func_0026F888(*arg0);
        *arg0 = 0;
    }
    *arg0 = func_0026F7A0(*(s32 *)(arg4 + 0x20), arg1, arg2, arg3);
}
