#include "common.h"

void memset(s32 arg0, s32 arg1, s32 arg2);
s32 rand(void);
extern u8 *D_003876A0;
extern u8 *D_00387F2C;

void func_00101BF0(void) {
    u8 *temp_s0;
    u8 *temp_v1_2;
    u8 *temp_v1_3;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_4;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a3;
    s32 var_v0;

    temp_s0 = D_003876A0 + 0xB8;
    memset((s32)(D_003876A0 + 0x480), 0, 0x50);
    *(s32 *)(temp_s0 + 0x20) = 0;
    temp_v1 = *(s32 *)(temp_s0 + 0x10);
    if (temp_v1 == 2) {
        *(s32 *)(temp_s0 + 0x20) = 1;
    }
    var_a3 = 0;
    if (temp_v1 == 3) {
        *(s32 *)(temp_s0 + 0x20) = *(s32 *)(temp_s0 + 0x20) | 2;
    }
    var_a2 = 1;
    do {
        temp_v1_2 = D_003876A0 + var_a3;
        temp_v1_3 = temp_v1_2 + 0xE0;
        temp_a1 = *(s32 *)(temp_v1_2 + 0xE0);
        temp_a0 = *(s32 *)(temp_v1_3 + (*(s32 *)(temp_v1_3 + 0x1C0) * 0x58) + 8);
        *(s32 *)(temp_v1_3 + 0x1CC) = temp_a0;
        *(s32 *)(temp_v1_3 + 0x1C8) = temp_a0;
        /* the original spins for temp_a1 iterations here (timing only, no effect on state): omitted */
        var_a2 -= 1;
        var_a3 += 0x1D0;
    } while (var_a2 >= 0);
    temp_v1_4 = *(s32 *)(temp_s0 + 0x0);
    if (temp_v1_4 == 0) {
        if (*(s32 *)(D_00387F2C + 0x81C) == 0) {
            temp_v0 = rand();
            var_v0 = (temp_v0 - (((temp_v0 < 0 ? (temp_v0 + 3) : temp_v0) >> 2) * 4)) + 8;
            goto block_18;
        }
    } else if (temp_v1_4 == 1) {
        var_a2_2 = 0;
        if (*(s16 *)(D_00387F2C + 0x24C2) == 0) {
            *(s32 *)(temp_s0 + 0x18) = temp_v1_4;
        } else {
loop_15:
            var_a2_2 += 1;
            if (var_a2_2 < 7) {
                if (*(s16 *)(D_00387F2C + (var_a2_2 * 4) + 0x24C2) == 0) {
                    var_v0 = var_a2_2 + 1;
block_18:
                    *(s32 *)(temp_s0 + 0x18) = var_v0;
                } else {
                    goto loop_15;
                }
            }
        }
    }
    *(s8 *)(D_003876A0 + 0x4D0) = 1;
}
