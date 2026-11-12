#include "common.h"

void func_002C7148(void *arg0, s32 arg1);
s32 func_002C71F0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002C8E88(void *arg0, s32 arg1);
void func_002CE480(void *arg0, s32 arg1, s32 arg2);
s32 func_002DDF68(s32 arg0, s32 arg1);
s32 func_00305390(s32 arg0, s32 arg1, s32 arg2);

s32 func_002C8D98(void *arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    s32 var_v0;
    u8 *var_s2;
    u8 *var_s5;
    u8 *var_s6;

    var_s0 = arg1;
    var_s2 = (u8 *)arg0;
    var_s5 = *(u8 **)(var_s2 + 0x1FC0);
    var_s1 = *(s32 *)var_s5;
    func_002C8E88(arg0, arg1);
    var_s6 = var_s5 + 0x8C;
    var_s4 = func_00305390(var_s0, 0, 1);
    var_s3 = func_002DDF68(var_s1, var_s0);
    var_s1 = func_00305390(var_s0, 0, 1) - var_s4;
    var_s0 = func_002C71F0(arg0, var_s3, var_s1, 0xFF000F07);
    func_002C7148(arg0, var_s1);
    var_v0 = var_s0;
    if (var_s0 == 0) {
        if (*(s8 *)(var_s6 + 0x58) == 0) {
            *(s32 *)(var_s5 + 0x16C) = 1;
        }
        func_002CE480(arg0, 1, *(s32 *)(var_s6 + 0x18));
        var_v0 = 0;
    }
    return var_v0;
}
