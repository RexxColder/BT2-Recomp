#include "common.h"

void func_002D1CB8(s32 arg0, u8 *arg1, s32 *arg2, s32 *arg3);

void func_002D1D80(s32 arg0, u8 *arg1, s32 *arg2, s32 *arg3) {
    func_002D1CB8(30000, arg1, arg2, arg3);
    *arg3 = arg0;
}
