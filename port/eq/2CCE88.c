#include "common.h"

s32 func_002C3210(s32 arg0);
s32 func_002CCE60(s32 arg0);
extern u8 D_00346E2C[] __attribute__((section(".data")));

s32 func_002CCE88(void) {
    u8 *p = D_00346E2C;
    s32 s0 = *(s32 *)p;
    s32 s2 = 0;

    for (;;) {
        p += 4;
        if (func_002C3210(s0) == 0) {
            if (func_002CCE60(s0) == 0) {
                return 0;
            }
        }
        s2 += 1;
        if (s2 >= 8) {
            return 1;
        }
        s0 = *(s32 *)p;
    }
}
