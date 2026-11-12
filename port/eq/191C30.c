#include "common.h"

void func_00191C30(f32 *arg0, f32 *arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        f32 a = arg1[i];
        f32 t1 = a * farg0;
        f32 t0 = a * farg1;

        t0 = t0 - t1;
        t0 = t0 * farg2;
        arg0[i] = t1 + t0;
    }
}
