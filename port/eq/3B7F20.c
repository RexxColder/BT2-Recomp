#include "m2c_macros.h"

void func_003B7F20(void *arg0, void *arg1, s32 arg2) {
    u8 *a1;
    u8 *a3;
    s32 t0;

    if (arg2 <= 0) {
        return;
    }
    a1 = arg1;
    a3 = arg0;
    t0 = 0;
    for (;;) {
        if (M2C_FIELD(a1, s32 *, 0) == 2) {
            t0 += 1;
        } else if (t0 != M2C_FIELD(a3, s32 *, 0)) {
            t0 += 1;
        } else {
            M2C_FIELD(a1, s32 *, 4) = M2C_FIELD(a3, s32 *, 4);
            M2C_FIELD(a1, s32 *, 8) = M2C_FIELD(a3, s32 *, 8);
            M2C_FIELD(a1, s32 *, 0xC) = M2C_FIELD(a3, s32 *, 4) + M2C_FIELD(a3, s32 *, 0xC);
            M2C_FIELD(a1, s32 *, 0x10) = M2C_FIELD(a3, s32 *, 8) + M2C_FIELD(a3, s32 *, 0x10);
            M2C_FIELD(a1, s32 *, 0x34) = M2C_FIELD(a3, s32 *, 0x14);
            a3 += 0x18;
            if (M2C_FIELD(a3, s32 *, 0) < 0) {
                return;
            }
            t0 += 1;
        }
        a1 += 0x38;
        if (t0 >= arg2) {
            break;
        }
    }
}
