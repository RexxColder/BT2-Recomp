#include "common.h"

s32 func_002BE770(s32 arg0);
void func_002BE7A0(s32 arg0, s32 arg1);
s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002D07B0(s32 arg0, s32 arg1);
void func_002D3238(s32 arg0, s32 arg1);
s32 func_002F4590(s32 arg0);
s32 func_002F5E40(s32 arg0);
void func_002F6590(s32 arg0);
extern s32 D_00393E6C __attribute__((section(".data")));

void func_002BE4C0(u8 *arg0, s32 arg1) {
    u8 *s4;
    s32 s2;
    s32 s3;
    s32 s0;
    s32 v0;

    s4 = *(u8 **)(arg0 + 0x2004);
    s2 = *(s32 *)s4;
    s3 = func_002F4590(s2);
    s0 = func_002F5E40(s2);
    if (s0 != 0) {
        D_00393E6C = s0;
    }
    if (func_002D07B0((s32)arg0, 0x1A) == 0) {
        s0 = 0;
    }
    if (s0 == -1) {
        func_002C2FF0((s32)arg0, 0xFF000C08);
    } else if (s0 == 0) {
        /* no error code */
    } else if (s0 == -2) {
        func_002C2FF0((s32)arg0, 0xFF000C09);
    } else {
        func_002C2FF0((s32)arg0, 0xFF000C07);
    }
    v0 = s3 - 4;
    if ((u32)v0 < 2U) {
        func_002D3238((s32)(arg0 + 0x1020), 0);
    }
    if (s3 == 5 || s0 != 0) {
        func_002BE7A0((s32)arg0, 1);
    }
    if (func_002BE770((s32)arg0) == 1 && arg1 == 0) {
        func_002F6590(s2);
        if (*(s32 *)(s4 + 0x48) == 0) {
            func_002BE7A0((s32)arg0, 1);
        }
    }
}
