#include "common.h"

s32 func_00269A08(u8 *arg0, s32 arg1);
s32 func_00269A40(u8 *arg0, s32 arg1);
extern f32 D_00386E8C;

void func_002604A8(u8 *arg0) {
    s32 temp_v0_2;
    u8 *temp_s0;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *var_s0;

    temp_s1 = arg0 + 0xEF0;
    temp_s0 = arg0 + 0x1C;
    memset(temp_s1, 0, 0xD0);
    *(f32 *)(temp_s1 + 0xBC) = *(f32 *)(*(u8 **)(temp_s0 + 0x28) + 0x10);
    *(f32 *)(temp_s1 + 0xC0) = *(f32 *)(*(u8 **)(temp_s0 + 0x28) + 0x14);
    *(f32 *)(temp_s1 + 0xC4) = *(f32 *)(*(u8 **)(temp_s0 + 0x28) + 0x18);
    *(f32 *)(temp_s1 + 0xC8) = *(f32 *)(*(u8 **)(temp_s0 + 0x28) + 0x1C);
    if (*(s32 *)(arg0 + 0x744) != 0) {
        *(f32 *)(temp_s1 + 0xCC) = D_00386E8C;
        *(f32 *)(temp_s1 + 0xB8) = *(f32 *)(*(u8 **)(temp_s0 + 0x728) + 4);
        temp_v0 = *(u8 **)(temp_s0 + 0x728) + 0x10;
        *(u8 **)(arg0 + 0xEF0) = temp_v0;
        var_s0 = temp_v0;
        do {
            *(s32 *)(var_s0 + 0xC) = func_00269A40(arg0, *(s32 *)(var_s0 + 4));
            *(s32 *)(var_s0 + 8) = func_00269A08(arg0, *(s32 *)(var_s0 + 4));
            temp_v0_2 = *(s32 *)var_s0 & 1;   /* asm: la marca de fin se lee del hueso ACTUAL (el addiu va en el delay slot) */
            var_s0 += 0x1D0;
        } while (temp_v0_2 == 0);
        temp_v0_2 = *(s32 *)(temp_s1 + 0x58);
        *(s32 *)(temp_s1 + 0x58) = temp_v0_2 ^ 1;
        *(u8 **)(temp_s1 + 0x50) = temp_s1 + ((u32)temp_v0_2 << 5) + 0x10;
    }
}
