#include "m2c_macros.h"

void func_002CF9A0(s32 *arg0, s32 *arg1) {
    s32 temp_v0;

    temp_v0 = *arg0;
    *arg1 = ((temp_v0 ^ 1) != 0) ? 0 : temp_v0;
}
