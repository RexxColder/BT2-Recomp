#include "common.h"

extern f32 D_00385AF4;

f32 BtlMove_CalcJumpSpeed(f32 arg0) {
    f32 f12;
    f32 f1;

    f12 = arg0;
    f1 = 0.0f;
    do {
        f12 = f12 - f1;
        f1 = f1 + D_00385AF4;
    } while (!(f12 < 0.0f));
    return -(f1 + (((1.0f - (-f12 / f1)) * D_00385AF4) - D_00385AF4));
}
