#include "m2c_macros.h"

s32 func_0020C688(void *);
s32 func_0020C6D0(void *);

// Scroll/tilt update of an effect object: sets flag +0x744 from func_0020C6D0, then moves the value at +0x748 by +-0x40 (positive clamp 0, negative clamp -0x100).
void func_0010F220(void *arg0, void *arg1) {
    s32 temp_v0_2;
    s32 temp_v0_3;

    func_0020C688(arg1);
    M2C_FIELD(arg0, s32 *, 0x744) = 1;
    if (func_0020C6D0(arg1) != 0) {
        M2C_FIELD(arg0, s32 *, 0x744) = 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0x744) != 0) {
        temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x748) + 0x40;
        M2C_FIELD(arg0, s32 *, 0x748) = temp_v0_2;
        if (temp_v0_2 > 0) {
            M2C_FIELD(arg0, s32 *, 0x748) = 0;
        }
    } else {
        temp_v0_3 = M2C_FIELD(arg0, s32 *, 0x748) - 0x40;
        M2C_FIELD(arg0, s32 *, 0x748) = temp_v0_3;
        if (temp_v0_3 < -0x100) {
            M2C_FIELD(arg0, s32 *, 0x748) = -0x100;
        }
    }
}
