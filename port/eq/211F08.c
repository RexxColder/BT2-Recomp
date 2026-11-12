#include "common.h"

s32 func_00210DD8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211288(s32 arg0);
void func_00241088(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_003126C8(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_00211F08(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[8];
    s32 res1;
    s32 res2;

    if ((arg3 & 0xFF) != 0) {
        func_00241088(arg0, arg1, arg2, (s32)sp, (s32)&sp[4]);
    } else {
        res1 = func_00210DD8(arg0, arg1, arg2, (s32)sp);
        res2 = func_00211288(res1);
        func_00241088(res2, arg1, arg2, (s32)sp, (s32)&sp[4]);
    }
    func_003126C8(arg0 + 0xA50, (s32)sp);
    func_003126C8(arg0 + 0xA60, (s32)&sp[4]);
    func_002113C0(arg0, 7, 0x40, 1);
}
