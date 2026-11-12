#include "common.h"

void func_002B1298(f32 fa, f32 fb, u8 *arg0) {
    f32 f1 = *(f32 *)(arg0 + 0x158);
    f32 f0 = f1 + fb;
    f32 t;

    if (f0 < fa) {
        *(f32 *)(arg0 + 0x158) = f0;
    } else {
        t = f1 - fb;
        if (fa < t) {
            *(f32 *)(arg0 + 0x158) = t;
        } else {
            *(f32 *)(arg0 + 0x158) = fa;
        }
    }
    *(f32 *)(arg0 + 0xD4) = *(f32 *)(arg0 + 0xD4) + *(f32 *)(arg0 + 0x158);
}
