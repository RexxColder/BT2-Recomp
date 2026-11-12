#include "common.h"

s32 func_002BDA48(s32 arg0);
void func_002BDB90(s32 arg0);
s32 func_002BDB98(s32 arg0, s32 arg1);
s32 func_002BE3F0(s32 arg0);
void func_002BE4C0(s32 arg0, s32 arg1);
s32 func_002BE788(s32 arg0);
void func_002BE7C0(s32 arg0);
void func_002BE8A0(s32 arg0);
/* GUESS arity: a0 (arg0) is passed through to func_002D07B0 (not written before the call) */
s32 func_002D07B0(s32 arg0, s32 arg1);

s32 func_002BDAF0(s32 arg0) {
    s32 sp[4];
    s32 temp_s0;
    s32 var_v0;

    var_v0 = func_002D07B0(arg0, 6);
    if (var_v0 != 0) {
        if (func_002BE788(arg0) == 1) {
            return 0;
        }
        func_002BDB90(arg0);
        temp_s0 = func_002BDB98(arg0, (s32)sp);
        func_002BE3F0(arg0);
        func_002BE4C0(arg0, sp[0]);
        func_002BE7C0(arg0);
        func_002BE8A0(arg0);
        func_002BDA48(arg0);
        var_v0 = temp_s0;
        return var_v0;
    }
    return var_v0;
}
