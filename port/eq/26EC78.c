#include "common.h"

void func_00270438(u8 *arg0, u8 *arg1, u8 *arg2);

/* 0x0026EC78: arg1 (*arg1 >= 0) is a flag; *arg2 counts up and wraps at arg7 (a remainder is taken), *arg3 counts up
 * to arg5*arg6 and wraps to 0; then the quotient/remainder of *arg3 by arg5 scale the 4-word vector arg4 into a 5-word
 * buffer that goes to func_00270438(arg0->+0x1C, arg1, buffer). */
void func_0026EC78(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 bound;
    s32 v0;
    s32 rem;
    s32 qq;
    s32 rr;
    s32 v3;
    s32 a3p;
    s32 buf[5];

    bound = arg5 * arg6;
    if (*arg1 < 0) {
        return;
    }
    *arg2 = *arg2 + 1;
    rem = *arg2 % arg7;
    if (rem == 0) {
        *arg2 = 0;
        v0 = *arg3 + 1;
        *arg3 = (v0 < bound) ? v0 : 0;
    }
    v0 = *arg3;
    if (v0 != 0) {
        qq = v0 / arg5;
        rr = v0 % arg5;
    } else {
        qq = 0;
        rr = 0;
    }
    v3 = arg4[2] * rr;
    a3p = arg4[3] * qq;
    buf[0] = arg4[0] + v3;
    buf[1] = arg4[1] + a3p;
    buf[2] = arg4[2] + v3;
    buf[3] = arg4[3] + a3p;
    buf[4] = 0;
    func_00270438(*(u8 **)(arg0 + 0x1C), (u8 *)arg1, (u8 *)buf);
}
