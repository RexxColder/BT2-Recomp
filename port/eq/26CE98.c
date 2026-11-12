#include "common.h"

void func_0026CE98(u8 *arg0, u8 *arg1, s32 *arg2) {
    s32 t0;
    u8 *a0;

    *arg0 = arg1[*arg2];
    *arg2 += 1;
    t0 = 0;
    if ((s8)*arg0 != 0) {
        do {
            t0 += 1;
            a0 = arg0 + t0;
            *a0 = arg1[*arg2];
            *arg2 += 1;
        } while ((s8)*a0 != 0);
    }
}
