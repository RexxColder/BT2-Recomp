#include "common.h"

s32 func_002F95C8(s32 arg0, s32 arg1, s32 arg2);
void func_002F9300(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037DBD8[] __attribute__((section(".data")));
extern u8 D_0037DC00[] __attribute__((section(".data")));
extern u8 D_0037DC28[] __attribute__((section(".data")));

s32 func_002FAEB8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[8];
    s32 var_a1;
    s32 var_a2;
    u8 *var_a0;
    s32 var_s0;
    u8 *var_s1;
    s32 var_v0;
    s32 (*temp_v1)(s32, s32, s32, s32);

    var_a1 = arg1;
    var_a2 = arg2;
    var_s0 = arg1;
    if (arg0 == 0) {
        var_a0 = D_0037DBD8;
        goto block_8;
    }
    if (var_s0 == 0) {
        var_a0 = D_0037DC00;
        goto block_8;
    }
    var_s1 = (u8 *)func_002F95C8(arg0, arg1, arg2);
    var_a1 = 0;
    var_a2 = 0x14;
    if (var_s1 == 0) {
        var_a0 = D_0037DC28;
block_8:
        func_002F9300((s32)var_a0, var_a1, var_a2);
        return -1;
    }
    memset(sp, 0, 0x14);
    sp[1] = var_s0;
    var_v0 = -1;
    temp_v1 = (s32 (*)(s32, s32, s32, s32))(*(s32 *)(var_s1 + 0x60));
    if (temp_v1 != 0) {
        var_v0 = temp_v1((s32)sp, 3, 0, 0);
    }
    return var_v0;
}
