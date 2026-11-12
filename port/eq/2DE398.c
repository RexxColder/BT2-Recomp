#include "common.h"

s32 func_002E0750(s32 arg0);
s32 func_002DDD70(s32 arg0, s32 arg1);
s32 func_002DE6B8(s32 arg0, s32 arg1);
s32 func_002E0830(s32 arg0, s32 arg1);
s32 func_002DFD20(s32 arg0, s32 arg1, s32 arg2);
s32 func_002DE5A8(s32 arg0);
void func_002DE760(s32 arg0, s32 arg1);
void func_002DEE20(s32 arg0, s32 arg1);
void func_002DF0A0(s32 arg0, s32 arg1);
void func_002DF688(s32 arg0, s32 arg1, s32 arg2);
void func_002DF748(s32 arg0, s32 arg1, s32 arg2);

s32 func_002DE398(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 sp10[2];
    s32 s0;
    s32 s3;
    s32 temp;
    s32 vt;

    if (func_002E0750(arg0) != 0) {
        return func_002DDD70(0, (s32)0xFF03020C);
    }
    *(s32 *)(arg0 + 0x3F4) = 0;
    vt = *(s32 *)arg1;
    ((void (*)(s32, s32, s32, s32))(*(s32 *)(vt + 0x18)))(arg1, 1, 0x7FFFFFFF, (s32)sp);
    vt = *(s32 *)arg1;
    ((void (*)(s32, s32, s32))(*(s32 *)(vt + 0x1C)))(arg1, 1, (s32)sp);
    sp10[0] = sp[0];
    sp10[1] = sp[1];
    if (func_002DE6B8(arg0, (s32)sp10) == 2) {
        return func_002E0830(arg0, arg1);
    }
    s3 = 0;
    for (;;) {
        s0 = func_002DFD20(arg0, -1, arg1);
        if (s0 != 0) {
            return func_002DDD70(arg0, s0);
        }
        temp = func_002DE5A8(arg1);
        if (temp == 0) {
            return s0;
        }
        if (temp & 3) {
            return s0;
        }
        s0 = -2;
        if (temp & 0x80) {
            return s0;
        }
        if (temp == 0x10) {
            func_002DF688(arg0, arg1, s3);
        } else if (temp < 0x11) {
            if (temp == 4) {
                s3 = 4;
                func_002DF0A0(arg0, arg1);
            } else if (temp == 8) {
                s3 = 8;
                func_002DEE20(arg0, arg1);
            }
        } else if (temp == 0x20) {
            func_002DF748(arg0, arg1, s3);
        } else if (temp == 0x40) {
            s3 = 0x40;
            func_002DE760(arg0, arg1);
        }
    }
}
