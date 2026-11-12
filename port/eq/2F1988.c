#include "common.h"

/* the call passes a0 = slot, a1..a3 = the four params, t0 = the fifth (arg3) */
s32 func_002F1880(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 D_00353F74 __attribute__((section(".data")));
extern s32 D_00353F78 __attribute__((section(".data")));
extern u8 D_00353F90[] __attribute__((section(".data")));

s32 func_002F1988(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *s0;
    s32 a1;
    s32 count;

    s0 = NULL;
    a1 = 0;
    count = D_00353F78;
    if (count > 0) {
        s0 = D_00353F90 + D_00353F74 * 0x60;
        if (*(s8 *)s0 != 0) {
            do {
                a1 += 1;
                if (a1 >= D_00353F78) {
                    break;
                }
                s0 = D_00353F90 + (D_00353F74 + a1) * 0x60;
            } while (*(s8 *)s0 != 0);
        }
    }
    if (a1 != D_00353F78) {
        func_002F1880((s32)s0, arg0, arg1, arg2, arg3);
        s0[3] = 1;
        return (s32)s0;
    }
    return 0;
}
