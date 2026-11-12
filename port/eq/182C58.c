#include "common.h"

void EftRibbon_SetUnk5C(s32 arg0, s32 arg1);
void func_00129C28(s32 arg0, s32 arg1);
s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
extern u8 *D_003876A0;

void func_00182C58(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp10[0x10] __attribute__((aligned(16)));
    s32 var_s1;
    s32 var_fp;
    s32 var_s3;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_s6;
    s32 temp_a0;
    s32 var_a1;
    s32 temp_r;
    u16 temp_t1;

    var_s1 = 0;
    var_fp = 0;
    temp_s0 = *(s32 *)(arg1 + 0x38);
    temp_s6 = *(s32 *)(temp_s0 + 0xA54);
    do {
        if (!(*(s64 *)(D_003876A0 + 0x4D8) & 2) || (var_s1 != 2)) {
            temp_s2 = *(s32 *)arg2 + var_fp;
            var_s3 = 0;
            if (*(u8 *)temp_s2 != 0) {
                do {
                    if ((var_s1 == 8) || (var_s1 == 4) || (var_s1 == 10) || (var_s1 == 11)) {
                        /* skipped */
                    } else if ((var_s1 == 6) && (var_s3 == 0)) {
                        /* skipped */
                    } else {
                        func_00129C28((s32)sp10, temp_s0 + 0xA70);
                        if ((var_s1 == 2) && (*(s32 *)(temp_s0 + 0x348) != 0)) {
                            func_00129C28((s32)sp10, temp_s0 + 0xAB0);
                        }
                        temp_t1 = *(u16 *)(temp_s0 + 0xAD6);
                        temp_r = func_0014EFA8(arg0, arg2, temp_s0, var_s1, var_s3, temp_t1 & 0x400, temp_t1 & 0x800);
                        if (temp_r != 0) {
                            func_001513D0(*(f32 *)(temp_s0 + 0xA38), temp_s6, arg2, temp_s0, temp_s0 + 0x7B0, (s32)sp10, temp_s0 + 0xA90, var_s1, var_s3, var_s3, temp_r);
                        }
                        if (var_s1 == 2) {
                            temp_a0 = *(s32 *)(temp_s0 + 0x348);
                            if (temp_a0 != 0) {
                                if (*(u16 *)(temp_s0 + 0xAD6) & 0x100) {
                                    var_a1 = 0x10;
                                } else {
                                    var_a1 = 0;
                                }
                                EftRibbon_SetUnk5C(temp_a0, var_a1);
                            }
                        }
                    }
                    var_s3 += 1;
                } while (var_s3 < *(u8 *)temp_s2);
            }
        }
        var_s1 += 1;
        var_fp += 0x110;
    } while (var_s1 < 0x10);
}
