#include "common.h"

s32 func_00129720(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_00129A50(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_0013A070(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, u8 *arg5, u8 *arg6, u8 *arg7, u8 *arg8, u8 *arg9, s32 arg10, s32 arg11, s32 arg12);
extern void *gEftSurf;

void func_00137E20(u8 *arg0, s32 arg1, s32 arg2) {
    u8 sp30[0x90];
    u8 spC0[0x40];
    u8 *s0;
    u8 *s4;
    u8 *s5;
    u8 *v0;
    s32 s2;
    s32 s3;
    s32 off;

    s0 = *(u8 **)((u8 *)gEftSurf + 0x10);
    s2 = 4;
    s3 = 3;
    do {
        s2 -= 1;
        s3 = func_00129720(arg0, arg0, s0, s3);
        s0 += 0x10;
    } while (s2 >= 0);
    s0 = spC0;
    if (s3 != 0) {
        s2 = 2;
        func_00129A50(sp30, s0, arg0, s3);
        if (s3 > 2) {
            s4 = s0;
            s0 = arg0 + 0x60;
            s5 = arg0 + 0x20;
            off = s2 << 4;
            do {
                s2 += 1;
                v0 = s4 + off;
                func_0013A070(sp30, sp30 + off - 0x10, sp30 + off, s5, s0 - 0x10, s0 + 0x20, s4, v0 - 0x10, v0, NULL, arg1, arg2, 2);
                s0 += 0x30;
                off = s2 << 4;
            } while (s2 < s3);
        }
    }
}
