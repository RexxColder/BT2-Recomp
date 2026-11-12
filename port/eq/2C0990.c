#include "common.h"

s32 func_002C2FF0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002C32B0(void *arg0, s32 arg1);
void func_002C32C8(void *arg0);

s32 func_002C0990(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    s32 temp_a2_2;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s3;
    s32 var_v0;
    u8 *temp_a2;
    u8 *temp_s0;

    var_v0 = 0;
    var_s3 = 0;
    temp_a2 = arg0 + 0x1310 + (arg1 * 0x74);
    if (arg2 != 0) {
        if (*(s32 *)(temp_a2 + 4) != 0) {
            temp_s0 = temp_a2 + 0x10;
            func_002C32B0(sp, arg1);
            temp_a2_2 = *(s32 *)(temp_s0 + 0x1C);
            temp_v0 = *(s32 *)(temp_s0 + 0x20) + arg2;
            temp_a3 = temp_v0 - temp_a2_2;
            *(s32 *)(temp_s0 + 0x20) = temp_v0;
            if (temp_v0 >= temp_a2_2) {
                *(s32 *)(temp_s0 + 0x20) = temp_a3;
            }
            temp_v0_2 = *(s32 *)(temp_s0 + 0x28) + arg2;
            *(s32 *)(temp_s0 + 0x28) = temp_v0_2;
            if ((*(s32 *)(temp_s0 + 0x2C) + temp_a2_2) < temp_v0_2) {
                var_s3 = func_002C2FF0(arg0, 0xFF000406, temp_a2_2, temp_a3);
            }
            *(s32 *)(arg0 + 0x44) = 1;
            func_002C32C8(sp);
            var_v0 = var_s3;
            return var_v0;
        }
        return func_002C2FF0(arg0, 0xFF000401, (s32)temp_a2, arg3);
    }
    return var_v0;
}
