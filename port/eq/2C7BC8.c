#include "common.h"

s32 func_002C7CA8(s32 arg0, s32 arg1, s32 arg2);
void func_002C7D68(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002D05E8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D07B0(s32 arg0, s32 arg1);

void func_002C7BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 s0;
    s32 call;

    s0 = func_002D07B0(arg0, 0x34);
    call = 0;
    if (s0 == 0) {
        if (arg2 >= 0) {
            call = 1;
        } else if (*(s32 *)(arg1 + 0x30) == 0) {
            call = 1;
        } else if (*(s8 *)(arg1 + 0x57) != 0) {
            call = 1;
        } else if (arg3 != 0 && func_002C7CA8(arg0, arg1, 1) != 0) {
            call = 1;
        }
        if (call) {
            func_002D05E8(arg0, 0x34, 1);
            s0 = 1;
        }
    }
    if (s0 == 1) {
        func_002C7D68(arg0, arg1, arg2, arg3);
    }
}
