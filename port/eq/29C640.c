#include "common.h"

s32 func_0026EB60(s32 arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_0029C638(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_00387DA0;
extern u8 D_003B0B00[] __attribute__((section(".data")));

s32 func_0029C640(s32 arg0) {
    s32 var_a1;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s1;
    s32 var_v0;
    u8 *d = D_00387DA0;

    var_s1 = 0;
    var_v0 = func_0026EB60((s32)(d + 8));
    if (var_v0 != 0) {
        var_v0 = 0;
        if (*(s32 *)(d + 0x70) != 0) {
            temp_a0 = *(s32 *)(d + 0x74) * 0x180;
            temp_v1 = *(s32 *)(D_003B0B00 + temp_a0 + 0x144);
            if (temp_v1 & 0x80) {
                *(s32 *)(d + 0x58) = *(s32 *)(d + 0x58) - 1;
                if (*(s32 *)(d + 0x58) < 0) {
                    *(s32 *)(d + 0x58) = 1;
                }
                func_0029C638(temp_a0, (s32)d, (s32)D_003B0B00);
                var_a1 = 0;
                goto block_21;
            }
            if (temp_v1 & 0x20) {
                *(s32 *)(d + 0x58) = *(s32 *)(d + 0x58) + 1;
                if (*(s32 *)(d + 0x58) >= 2) {
                    *(s32 *)(d + 0x58) = 0;
                }
                func_0029C638(temp_a0, (s32)d, (s32)D_003B0B00);
                var_a1 = 0;
                goto block_21;
            }
            temp_v0 = *(s32 *)(D_003B0B00 + temp_a0 + 0x134);
            if (temp_v0 & 0x4000) {
                temp_v1_2 = *(s32 *)(d + 0x58);
                switch (temp_v1_2) {
                case 0:
                    var_s1 = 1;
block_19:
                    *(s32 *)(d + 0x54) = *(s32 *)(d + 0x54) | 1;
                    break;
                case 1:
                    var_s1 = -2;
                    goto block_19;
                }
                var_a1 = 1;
block_21:
                func_00297FE0(0, var_a1, 0x40, 0x40, 1);
            } else if ((temp_v0 & 0x1000) && (arg0 != 0)) {
                var_s1 = -1;
                func_00297FE0(0, 2, 0x40, 0x40, 1);
            }
            var_v0 = var_s1;
        }
    }
    return var_v0;
}
