#include "m2c_macros.h"

s32 func_002C3C78(u8 *arg0, s32 arg1) {
    s32 n;
    s32 v0;
    u8 *p;
    u8 v1;

    p = arg0;
    n = 0;
    if (arg1 > 0) {
        v1 = *p;
loop_2:
        p += 1;
        v0 = 0;
        if (v1 == 0) {
            n += 1;
            if (n < arg1) {
                v1 = *p;
                goto loop_2;
            }
            v0 = 1;
        }
    } else {
        v0 = 1;
    }
    return v0;
}
