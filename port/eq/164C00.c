#include "common.h"

void func_0014EAE8(s32 arg0, u8 *arg1);
s32 func_001C1048(f32 farg0, u8 *arg1, s32 arg2, u8 *arg3, u8 *arg4, s32 t0);
u8 *func_001F3758(void *arg0);

void func_00164C00(u8 *arg0, u8 *arg1) {
    s32 var_s1;
    s32 var_s4;
    u8 *var_s0;
    u8 *var_s2;
    u8 *var_s3;
    u8 *var_s5;
    u8 *var_s6;
    u8 *var_s7;
    u8 *temp_v1;

    var_s0 = *(u8 **)(arg0 + 0x38);
    var_s4 = *(s32 *)(func_001F3758(arg0) + 0x38);
    memset(var_s0, 0, 0xA90);
    *(u8 **)(var_s0 + 0x80) = arg1;
    var_s3 = *(u8 **)(arg1 + 0x24);
    var_s1 = 0;
    *(f32 *)(var_s0 + 0xC) = *(f32 *)(var_s3 + 8);
    *(s32 *)(var_s0 + 4) = 2;
    *(f32 *)(var_s0 + 0x10) = *(f32 *)(var_s3 + 4);
    func_0014EAE8(var_s4, var_s0 + 0x84);
    var_s2 = *(u8 **)(var_s0 + 0x80);
    if (*(s32 *)(var_s0 + 4) > 0) {
        var_s7 = var_s0 + 0x40;
        var_s6 = var_s0 + 0x20;
        var_s5 = var_s0 + 8;
        do {
            temp_v1 = var_s5 + var_s1 * 4;
            var_s1 += 1;
            *(s32 *)(temp_v1 + 0xA80) = func_001C1048(*(f32 *)(var_s3 + 4), var_s2, var_s4, var_s7, var_s6, *(s32 *)var_s2);
        } while (var_s1 < *(s32 *)(var_s0 + 4));
    }
}
