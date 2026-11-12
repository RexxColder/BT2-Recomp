#include "common.h"

void func_0026EFC8(s32 arg0, s32 *arg1, s32 arg2);
s32 func_0026EC18(s32 arg0, s32 *arg1, s32 arg2);

s32 func_00249708(s32 arg0, s32 *arg1, s32 arg2) {
    s32 v0 = *arg1;

    if (v0 >= 0) {
        func_0026EFC8(arg0, arg1, 4);
        return func_0026EC18(arg0, arg1, arg2 + 1);
    }
    return v0;
}
