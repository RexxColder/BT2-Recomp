#include "m2c_macros.h"

void func_002C2FF0(s32 arg0, s32 arg1);

void func_002CA170(s32 arg0, s32 arg1) {
    if (arg1 < -3 || (arg1 >= -1 && arg1 != 0)) {
        func_002C2FF0(arg0, arg1);
    }
}
