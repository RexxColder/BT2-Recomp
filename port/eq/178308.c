#include "common.h"

void Vu0Screen_StoreMtx(u8 *arg0);
s32 func_0012A108(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, s32 arg5);
u8 *func_0012B9B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0012BEC0(u8 *arg0, s32 arg1, u8 *arg2);
void func_00178440(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, u8 *arg5, u8 *arg6, u8 *arg7, u8 *arg8, s32 arg9, s32 arg10);

void func_00178308(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp20[0x90];
    u8 spB0[0x90];
    u8 sp140[0x40];
    u8 *s0;
    u8 *s4;
    u8 *s5;
    s32 s1;
    s32 s3;
    s32 off;

    s0 = func_0012B9B0(arg0, arg1, arg2, arg3);
    s1 = 4;
    s3 = 3;
    do {
        s3 = func_0012BEC0(s0, s3, arg0);
        s0 += 0x10;
        s1 -= 1;
    } while (s1 >= 0);
    if (s3 != 0) {
        s1 = 2;
        Vu0Screen_StoreMtx(sp140);
        func_0012A108(sp20, spB0, sp140, arg0, arg0 + 0x90, s3);
        if (s3 > 2) {
            s4 = spB0;
            s5 = arg0 + 0x120;
            off = s1 << 4;
            do {
                s1 += 1;
                func_00178440(sp20, sp20 + off - 0x10, sp20 + off, spB0, s4 + off - 0x10, s4 + off,
                              s5, arg0 + off + 0x110, arg0 + off + 0x120, arg2, arg3 & 0xFF);
                off = s1 << 4;
            } while (s1 < s3);
        }
    }
}
