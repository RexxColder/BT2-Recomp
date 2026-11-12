#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_00230C60(s32 arg0, s32 arg1) {
    if (func_00211310(arg0, 7, 0x20000) != 0) {
        return;
    }
    if (arg1 & 0xFF) {
        func_002113C0(arg0, 3, 0xA, 1);
        func_002113C0(arg0, 9, 0x20000, 1);
    } else {
        func_002113C0(arg0, 3, 0xF, 1);
        func_002113C0(arg0, 9, 0x10000, 1);
        func_002113C0(arg0, 0xF, 0x100000, 1);
    }
    func_002113C0(arg0, 9, 0x200000, 1);
}
