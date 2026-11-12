#include "m2c_macros.h"

void func_00114468(s32 *arg0, s32 arg1, s32 arg2) {
    if (arg2 & 0xFF) {
        *arg0 |= arg1;
        return;
    }
    *arg0 = arg1;
}
