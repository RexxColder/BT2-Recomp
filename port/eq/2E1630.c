#include "common.h"

void *memset(void *s, s32 c, u32 n);
extern u8 D_0039D650[] __attribute__((section(".data")));

void func_002E1630(s32 arg0, s32 arg1, u32 arg2) {
    s32 temp_s1;
    s32 var_a2;
    s32 var_s0;
    s32 var_v1;
    u32 temp_v0;
    u32 var_a0;

    var_s0 = arg0;
    var_a2 = var_s0 * 8;
    temp_v0 = (u32)((var_s0 * 0x700) + 0x40);
    if (arg2 < temp_v0) {
        var_a0 = temp_v0;
        var_v1 = var_a2;
        do {
            var_a0 -= 0x700;
            var_v1 -= 8;
            var_s0 -= 1;
            var_a2 = var_v1;
        } while (arg2 < var_a0);
    }
    temp_s1 = (arg1 + 0x3F) & ~0x3F;
    memset((void *)temp_s1, 0, (u32)((var_a2 - var_s0) << 8));
    *(s32 *)(D_0039D650 + 0x44) = temp_s1;
    *(s32 *)(D_0039D650 + 0x40) = var_s0;
}
