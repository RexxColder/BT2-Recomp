#include "common.h"

s32 func_002C2CF8(s32 a0, s32 a1, s32 a2);
s32 func_002D47B8(s32 a0, s32 a1, s32 a2);
s32 func_002D5520(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 func_002D5438[] __attribute__((section(".data")));
extern u8 func_002D54A8[] __attribute__((section(".data")));
extern u8 func_002D55D0[] __attribute__((section(".data")));
extern u8 func_002D5640[] __attribute__((section(".data")));
extern u8 func_002D56B0[] __attribute__((section(".data")));
extern u8 func_002D5720[] __attribute__((section(".data")));
extern u8 func_002D5790[] __attribute__((section(".data")));
extern u8 func_002D5808[] __attribute__((section(".data")));
extern u8 func_002D5878[] __attribute__((section(".data")));
extern u8 func_002D5900[] __attribute__((section(".data")));

void func_002C2B28(s32 arg0, s32 arg1, s32 *arg2) {
    s32 sp[4];
    s32 s5;
    s32 v1;

    s5 = arg1 & 0xFF;
    arg2[0] = func_002C2CF8(arg0, arg1, (s32)func_002D5438);
    arg2[1] = func_002C2CF8(arg0, arg1, (s32)func_002D54A8);
    if (func_002D5520(arg0, s5, (s32)(arg2 + 2), (s32)(arg2 + 3)) == 0) {
        arg2[2] = -1;
        arg2[3] = -1;
    }
    arg2[4] = func_002C2CF8(arg0, arg1, (s32)func_002D55D0);
    v1 = func_002D47B8(arg0, s5, (s32)sp);
    v1 = (v1 == 0) ? 0 : sp[0];
    arg2[5] = (v1 != 0);
    if (v1 != 0) {
        arg2[6] = func_002C2CF8(arg0, arg1, (s32)func_002D5640);
        arg2[7] = func_002C2CF8(arg0, arg1, (s32)func_002D56B0);
        arg2[8] = func_002C2CF8(arg0, arg1, (s32)func_002D5720);
        arg2[9] = func_002C2CF8(arg0, arg1, (s32)func_002D5790);
        arg2[10] = func_002C2CF8(arg0, arg1, (s32)func_002D5808);
        arg2[11] = func_002C2CF8(arg0, arg1, (s32)func_002D5878);
        arg2[12] = func_002C2CF8(arg0, arg1, (s32)func_002D5900);
    }
}
