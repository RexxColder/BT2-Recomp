#include "common.h"

s32 func_001FA1D0(u8 *arg0, f32 farg0) {
    u8 *v;
    f32 f0;
    f32 f1;
    f32 f2;

    v = *(u8 **)(arg0 + 0x1530) + 0xBD0;
    f1 = *(f32 *)(v + 0x14);
    f2 = *(f32 *)(v + 0x10);
    f0 = *(f32 *)(v + 0x8) * farg0;
    if (f1 <= f2) {
        if (f1 <= f0) {
            return f0 < f2;
        }
        return 0;
    }
    if (f1 <= f0) {
        return 1;
    }
    return f0 < f2;
}
