#include "common.h"

s32 rand(void);
extern u8 *D_00387F2C;
extern u8 D_003B26B0[] __attribute__((section(".data")));

s32 func_002AD3E8(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a3;

    var_a0 = 0;
    temp_a3 = D_003B26B0 + 0x310;
    if (arg0 >= 0x164) {
        if (arg0 < 0x16B) {
            var_a0 = *(s16 *)(D_00387F2C + arg0 * 4 + 0x1F32) > 0;
            if (var_a0 == 0) {
                if (*(s16 *)(D_00387F2C + 0x2526) > 0) {
                    var_v0 = rand();
                    var_v1 = 6;
                } else {
                    var_v0 = rand();
                    var_v1 = 3;
                }
                goto block_12;
            }
        } else if (arg0 == 0x3E8) {
            if (arg1 < 0x3E9) {
                var_v0 = rand();
                var_v1 = 6;
block_12:
                var_a0 = (var_v0 % var_v1) != 0;
            }
        } else {
            goto block_14;
        }
    } else {
block_14:
        var_a0 = (*(u32 *)(temp_a3 + (((arg0 < 0) ? (arg0 + 0x1F) : arg0) >> 5) * 4) & (1u << (arg0 & 31))) != 0;
    }
    return var_a0;
}
