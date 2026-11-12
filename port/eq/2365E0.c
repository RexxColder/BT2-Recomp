#include "common.h"

s32 func_00218540(s32 arg0, f32 farg0);
s32 func_00218560(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
void func_00203310(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
void BtlChar_Vibrate(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_003869E4;
extern f32 D_003869E8;
extern f32 D_003869EC;

s32 func_002365E0(s32 arg0) {
    f32 d;

    d = D_003869E4;
    if (func_00218540(arg0, d) != 0) {
        func_00203310(d, arg0, 0x1F4, 0);
        func_002113C0(arg0, 6, 0x10, 1);
        func_001FBE80(arg0, 5.0f, D_003869E8);
        BtlChar_Vibrate(arg0, 1.0f, D_003869E8);
        return 0xA8;
    }
    if (func_00218560(d, arg0, 0x1F4, 0) != 0) {
        func_00203310(d, arg0, 0x258, 0);
        func_002113C0(arg0, 6, 0x10, 1);
        func_001FBE80(arg0, 5.0f, D_003869EC);
        BtlChar_Vibrate(arg0, 1.0f, D_003869EC);
        return 0xA9;
    }
    return -1;
}
