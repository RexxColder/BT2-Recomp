#include "common.h"

s32 BtlMember_GetActiveGauge(s32 arg0);
s32 func_00202DC0(s32 arg0);

s32  BtlParam_GetType(s32 arg0) {
    s32 temp_s0;
    s8 var_s0;
    u32 temp_v1;

    temp_s0 = *(s32 *) (*(s32 *) (arg0 + 0x1530) + 0x958);
    temp_v1 = *(u32 *) (func_00202DC0(arg0) + 4);
    var_s0 = *(s8 *) (((temp_v1 >= 6U) ? 0U : temp_v1) + temp_s0 + 0x29);
    if (var_s0 < 5) {
        if (var_s0 >= 2) {
            if (*(u8 *) (BtlMember_GetActiveGauge(arg0) + 0x28) != 0) {
                var_s0 = ((var_s0 ^ 4) != 0) ? 7 : 8;
            }
        }
    }
    return (s8)(var_s0);
}
