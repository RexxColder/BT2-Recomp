#include "common.h"

s32 func_002F95C8(s32 arg0, s32 arg1, s32 arg2);
void func_002F9300(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037DAB8[] __attribute__((section(".data")));
extern u8 D_0037DAE0[] __attribute__((section(".data")));
extern u8 D_0037DB10[] __attribute__((section(".data")));

s32 func_002FACE8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[8];
    s32 var_a1;
    s32 var_a2;
    u8 *var_a0;
    s32 temp_s0;
    u8 *temp_v0;
    s32 var_v0;
    s32 (*temp_v1)(s32, s32, s32, s32);

    var_a1 = arg1;
    var_a2 = arg2;
    temp_s0 = arg1;
    if (arg0 == 0) {
        var_a0 = D_0037DAB8;
        goto block_8;
    }
    if (temp_s0 == 0) {
        var_a0 = D_0037DAE0;
        goto block_8;
    }
    temp_v0 = (u8 *)func_002F95C8(arg0, arg1, arg2);
    var_a1 = 0;
    var_a2 = 0x14;
    if (temp_v0 == 0) {
        var_a0 = D_0037DB10;
block_8:
        func_002F9300((s32)var_a0, var_a1, var_a2);
        return -1;
    }
    memset(sp, 0, 0x14);
    sp[0] = temp_s0;
    var_v0 = -1;
    temp_v1 = (s32 (*)(s32, s32, s32, s32))(*(s32 *)(temp_v0 + 0x60));
    if (temp_v1 != 0) {
        var_v0 = temp_v1((s32)sp, 1, 0, 0);
    }
    return var_v0;
}
