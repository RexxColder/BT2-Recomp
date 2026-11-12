#include "common.h"

s32 Gsc_StartAction(s32 arg0, s32 arg1);
s32 func_0020C8B8(void);
s32 func_0020C950(void);
s32 func_0020C980(void);
void func_00259F20(s32 arg0);
void func_00259F40(s32 arg0);
s32 func_002A9938(void);
s32 func_002A9980(s32 arg0);
s32 func_002AD368(s32 arg0);
extern u8 *D_003876A0;
extern u8 *D_00387A40;
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 D_003B2654[] __attribute__((section(".data")));

s32 func_002A99B8(void) {
    s32 temp_s3;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s1;
    u8 temp_v0;
    u8 *temp_a0;
    u8 *temp_s2;

    temp_s2 = D_003B2654 + 0x3B8;
    temp_s3 = func_002A9938();
    temp_s6 = func_0020C950();
    temp_s5 = func_0020C980();
    if (*(s32 *)(D_003B2654 + 0x10) != 0) {
        return 1;
    }
    if (func_0020C8B8() != 0) {
        var_s1 = 0;
        if (temp_s3 > 0) {
            var_s0 = 3;
loop_7:
            if (func_002A9980(var_s0) != 0) {
                *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | (s64)0x200;
                if (var_s1 == 0) {
                    temp_v0 = temp_s2[2];
                    if (temp_s6 & 1) {
                        if (temp_v0 == 0) {
                            func_00259F20(1);
                            temp_s2[2] = 1;
                        }
                        if (*(s32 *)(D_003B0B00 + 0x134) & 0x4000) {
                            temp_v0_2 = func_002AD368(3);
                            *(s32 *)(D_003B2654 + 0x10) = Gsc_StartAction(*(s32 *)(D_003B2654 + 0xC), temp_v0_2);
                            return 1;
                        }
                        goto block_20;
                    }
                    var_s1 += 1;
                    if (temp_v0 == 1) {
                        func_00259F40(0x200);
                        temp_s2[2] = 0;
                    }
                    goto block_21;
                }
                if (temp_s5 & (1 << var_s1)) {
                    temp_v0_2 = func_002AD368(var_s0);
                    if (temp_v0_2 != -0x3E8) {
                        temp_v0_2 = Gsc_StartAction(*(s32 *)(D_003B2654 + 0xC), temp_v0_2);
                        *(s32 *)(D_003B2654 + 0x10) = temp_v0_2;
                        temp_a0 = *(u8 **)(D_00387A40 + 8);
                        *(s32 *)(temp_a0 + 0xAF0) = *(s32 *)(temp_a0 + 0xAF0) | 0x200;
                        return 1;
                    }
                    goto block_20;
                }
                goto block_20;
            }
block_20:
            var_s1 += 1;
block_21:
            var_s0 = var_s1 + 3;
            if (var_s1 >= temp_s3) {
                goto block_23;
            }
            goto loop_7;
        }
    }
block_23:
    *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) & (s64)-0x201;
    return 0;
}
