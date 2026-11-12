#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
s32 strcmp(u8 *arg0, u8 *arg1);

s32 func_0026CD98(u8 *arg0, u8 *arg1) {
    u8 sp[0x110];   /* tamano de locales del original (antes 0x104) */
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v0_3;
    u8 temp_v0_2;
    s32 var_a1;
    s32 var_s0;
    s32 var_s2;

    var_s0 = 0;
    var_s2 = 0;
loop_1:
    memset(sp, 0, 0xFF);
    var_a1 = 0;
    temp_v0 = arg0 + var_s0;
    var_s0 += 1;
    sp[0] = *temp_v0;
    if (*temp_v0 != 0) {
        do {
            temp_v1 = arg0 + var_s0;
            var_s0 += 1;
            temp_v0_2 = *temp_v1;
            var_a1 += 1;
            sp[var_a1] = temp_v0_2;
        } while (temp_v0_2 != 0);
    }
    temp_v1_2 = arg0 + var_s0;
    if (strcmp(sp, arg1) == 0) {
        return var_s2;
    }
    sp[0x100] = temp_v1_2[0];
    sp[0x101] = temp_v1_2[1];
    var_s0 += 2;
    if (*(u16 *)(sp + 0x100) != 0) {
        temp_v0_3 = arg0 + var_s0;
        sp[0x102] = temp_v0_3[0];
        sp[0x103] = temp_v0_3[1];
        if (*(u16 *)(sp + 0x102) != 0) {
            var_s2 += 1;
            var_s0 += *(u16 *)(sp + 0x100);
            goto loop_1;
        }
    }
    return -1;
}
