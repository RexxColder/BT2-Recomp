#include "common.h"

void func_002C32B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002C32C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002C0608(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    s32 var_s1;
    s32 var_s2;
    u8 *var_s0;

    var_s1 = arg3;
    var_s0 = (u8 *)arg0 + arg1 * 0x74;
    var_s2 = arg2;
    var_s0 += 0x1338;
    func_002C32B0((s32)sp, arg1, arg2, arg3);
    *(s32 *)(var_s0 + 4) = var_s1;
    *(s32 *)(var_s0 + 0) = var_s2;
    func_002C32C8((s32)sp, arg1, arg2, arg3);
}
