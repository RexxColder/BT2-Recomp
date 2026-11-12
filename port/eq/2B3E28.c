#include "common.h"

s32 func_002D04A8(s32 arg0, s32 arg1, s32 arg2);
void func_002C57A8(s32 arg0, s32 arg1, s32 arg2);

void func_002B3E28(u8 *arg0, s32 arg2, s32 arg3) {
    s32 s2;
    s32 prod;
    s32 r;
    s32 var;
    s32 s3;
    f32 f;

    s2 = *(s32 *)(arg0 + 0x3C);
    func_002D04A8(s2, 8, 0);
    func_002D04A8(s2, 1, 1);
    func_002D04A8(s2, 0, 0);
    func_002D04A8(s2, 0x17, 4);

    prod = arg2 * arg3;
    f = (f32)(prod * 1000) + 0.5f;
    /* cvt.w.s truncates toward zero (saturating): plain cast */
    r = (s32)f;
    var = (f < (f32)r) ? 1 : 0;
    s3 = r - var;

    func_002D04A8(s2, 0x2D, s3);
    func_002D04A8(s2, 0x2C, s3);
    func_002D04A8(s2, 0x2A, s3);
    func_002D04A8(s2, 0xF, 2);
    func_002D04A8(s2, 0x33, 0);
    func_002D04A8(s2, 0xE, 0);
    func_002D04A8(s2, 0x1C, 0);
    func_002C57A8(s2, 5, 0);
}
