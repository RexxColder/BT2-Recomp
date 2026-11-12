#include "common.h"

void func_002E81C0(u8 *arg0, u8 *arg1, s32 arg2);

void func_002E81F0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002E81C0(arg0, arg0 + arg1 * 2, arg3);
    func_002E81C0(arg0 + arg2 * 2, arg0 + (arg2 + arg1) * 2, arg3);
}
