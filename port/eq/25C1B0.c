#include "m2c_macros.h"

extern void *gBtlCam;

s32 func_0025C1B0(void) {
    u8 *t0;
    s32 a0;
    s32 a2;
    s32 a3;
    s32 t1;
    s32 v1;

    t1 = -1;
    v1 = -0x270F;
    a2 = 0;
    t0 = (u8 *)gBtlCam + 0x260;
    a3 = 0;
    a0 = *(s32 *)t0;
    do {
        t0 += 0x300;
        if (v1 < a0) {
            v1 = a0;
            t1 = a3;
            a2 = 1;
        } else if ((a0 ^ v1) == 0) {
            a2 += 1;
        }
        a3 += 1;
        if (a3 < 2) {
            a0 = *(s32 *)t0;
        }
    } while (a3 < 2);
    if (a2 >= 2) {
        return (v1 > 0) ? 0 : -1;
    }
    return t1;
}
