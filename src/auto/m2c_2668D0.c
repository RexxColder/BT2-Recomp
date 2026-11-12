#include "m2c_macros.h"

void func_002668D0(void *arg0, s32 arg1, s32 arg2) {
    if (arg1 != arg2) {
        M2C_FIELD(arg0, f32 *, 0xB98) = (f32) ((f32) arg1 / (f32) arg2);
    }
}
