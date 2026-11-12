#include "common.h"

s64 func_0014F0A8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 t0, s32 t1, s32 t2, s32 t3);
void func_001513D0(f32 farg0, s32 arg1, u8 *arg2, u8 *arg3, u8 *arg4, u8 *arg5, u8 *arg6, s32 arg7, s32 arg8, s32 sp0, s32 sp8);

void func_001C0F50(u8 *arg0) {
    u8 *temp_s0;
    u8 *temp_s2;
    u8 *temp_s4;
    s32 temp_s5;
    s32 var_s1;
    s32 var_s3;
    s32 var_s6;

    var_s3 = 0;
    var_s6 = 0;
    temp_s0 = *(u8 **)(arg0 + 0x38);
    temp_s5 = *(s32 *)(temp_s0 + 0);
    do {
        temp_s4 = *(u8 **)(*(u8 **)(temp_s0 + 4)) + var_s6;
        var_s1 = 0;
        if (*temp_s4 != 0) {
            temp_s2 = temp_s0 + 0x70;
            do {
                s32 ret = func_0014F0A8(*(u8 **)(temp_s0 + 0x64), *(u8 **)(temp_s0 + 4), temp_s2, var_s3,
                                        var_s1, *(s32 *)(temp_s0 + 0xAC4), *(s32 *)(temp_s0 + 0xAC0), *(s32 *)(temp_s0 + 0xAC8));
                if (ret != 0) {
                    func_001513D0(*(f32 *)(temp_s0 + 0x60), temp_s5, *(u8 **)(temp_s0 + 4), temp_s2,
                                  temp_s0 + 0x820, temp_s0 + 0xA80, temp_s0 + 0xAB0, var_s3, var_s1, var_s1, ret);
                }
                var_s1 += 1;
            } while (var_s1 < (s32)*temp_s4);
        }
        var_s3 += 1;
        var_s6 += 0x110;
    } while (var_s3 < 0x10);
}
