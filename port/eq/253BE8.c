#include "common.h"

extern u8 *D_003879D0;

void func_00253BE8(void) {
    s32 temp_v0;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    u8 *temp_a0;
    u8 *temp_a1;
    u8 *temp_a2;
    u8 *temp_v0_2;
    u8 *temp_v1;

    var_t0 = 0;
    var_t3 = 0x10C;
    var_t2 = 0x10C;
    var_t1 = 0x170;
    do {
        temp_v1 = D_003879D0 + var_t1;
        temp_a2 = D_003879D0 + var_t3;
        var_t3 += 4;
        temp_v0 = var_t0 < *(s32 *)(D_003879D0 + 0x19C);
        var_t0 += 1;
        temp_a1 = D_003879D0 + var_t2;
        var_t2 += 4;
        var_t1 += 8;
        if (temp_v0 != 0) {
            temp_a0 = (u8 *)*(s32 *)(D_003879D0 + 0x18);
            *(s32 *)(temp_a1 + 0xC) = *(s32 *)(temp_a0 + ((*(u32 *)(temp_a0 + (*(s32 *)(temp_v1 + 8) * 4) + 4) >> 2) * 4) + 0x10);
        } else {
            temp_v0_2 = (u8 *)*(s32 *)(D_003879D0 + 0x18);
            *(s32 *)(temp_a2 + 0xC) = *(s32 *)(temp_v0_2 + ((*(u32 *)(temp_v0_2 + 0x210) >> 2) * 4) + 0x10);
        }
    } while (var_t0 < 7);
}
