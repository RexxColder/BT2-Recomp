#include "common.h"

s32 sceVibSetActParam(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 D_00387EB8[];
extern u8 D_00387EC0[];
extern u8 D_003B0C4C[] __attribute__((section(".data")));

void func_0028C890(void) {
    u8 *var_s0;
    u8 *t0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    u16 temp_v0;
    u16 temp_v1;
    s32 temp_a0;

    var_s0 = D_003B0C4C;
    var_s1 = 0;
    var_s2 = 1;
    var_s3 = 0;
    do {
        temp_v0 = *(u16 *)(D_00387EB8 + var_s1);
        temp_v1 = *(u16 *)(D_00387EC0 + var_s1);
        var_s1 += 4;
        temp_a0 = *(s32 *)(var_s0 - 0x4C);
        t0 = var_s0;
        *(s16 *)var_s0 = (s16)(temp_v1 | (temp_v0 * 2));
        var_s0 += 0x180;
        var_s2 -= 1;
        sceVibSetActParam(temp_a0, 1, (s32)(D_003B0C4C + 2 + var_s3), 2, (s32)t0);
        var_s3 += 0x180;
    } while (var_s2 >= 0);
    *(s32 *)(D_00387EB8 + 4) = 0;
    *(s32 *)(D_00387EC0 + 4) = 0;
    *(s32 *)(D_00387EB8 + 0) = 0;
    *(s32 *)(D_00387EC0 + 0) = 0;
}
