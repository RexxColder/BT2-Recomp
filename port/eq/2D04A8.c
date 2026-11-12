#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0);
void func_002D0560(s32 arg0, s32 arg1);
void func_002D05E8(s32 arg0, s32 arg1, s32 arg2);
void func_002D0638(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00346C28[] __attribute__((section(".data")));

s32 func_002D04A8(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == 0) {
        func_002D0560(arg1, arg2);
        *(s32 *)(D_00346C28 + arg1 * 4) = arg2;
        return 0;
    }
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000112);
    }
    func_002D05E8(arg0, arg1, arg2);
    func_002D0638(arg0, arg1, arg2);
    return 0;
}
