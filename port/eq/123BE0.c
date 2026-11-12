#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_003876FC;

void func_00123BE0(void) {
    u32 temp_v1;
    u8 *temp_a1;
    u8 *temp_t6;

    temp_a1 = *(u8 **)(D_003876A0 + 4);
    temp_v1 = *(u32 *)(temp_a1 + 0x40);
    if (*(u32 *)(temp_a1 + 0x44) != temp_v1) {
        temp_t6 = temp_a1 + ((temp_v1 >> 2) * 4);
        *(u8 **)(D_003876FC + 0x10) = temp_t6;
        if ((*(s32 *)(temp_t6 + 0) == 0x3E8) && (*(s32 *)(temp_t6 + 4) == *(s32 *)(D_003876A0 + 0xD4))) {
            *(u8 **)(temp_t6 + 0x70) = temp_t6 + *(s32 *)(temp_t6 + 0x38);
            *(u8 **)(temp_t6 + 0x74) = temp_t6 + *(s32 *)(temp_t6 + 0x3C);
            *(u8 **)(temp_t6 + 0x48) = temp_t6 + *(s32 *)(temp_t6 + 0x10);
            *(u8 **)(temp_t6 + 0x4C) = temp_t6 + *(s32 *)(temp_t6 + 0x14);
            *(u8 **)(temp_t6 + 0x50) = temp_t6 + *(s32 *)(temp_t6 + 0x18);
            *(u8 **)(temp_t6 + 0x54) = temp_t6 + *(s32 *)(temp_t6 + 0x1C);
            *(u8 **)(temp_t6 + 0x58) = temp_t6 + *(s32 *)(temp_t6 + 0x20);
            *(u8 **)(temp_t6 + 0x5C) = temp_t6 + *(s32 *)(temp_t6 + 0x24);
            *(u8 **)(temp_t6 + 0x60) = temp_t6 + *(s32 *)(temp_t6 + 0x28);
            *(u8 **)(temp_t6 + 0x64) = temp_t6 + *(s32 *)(temp_t6 + 0x2C);
            *(u8 **)(temp_t6 + 0x68) = temp_t6 + *(s32 *)(temp_t6 + 0x30);
            *(u8 **)(temp_t6 + 0x6C) = temp_t6 + *(s32 *)(temp_t6 + 0x34);
            *(u8 **)(temp_t6 + 0x78) = temp_t6 + *(s32 *)(temp_t6 + 0x40);
            *(u8 **)(temp_t6 + 0x7C) = temp_t6 + *(s32 *)(temp_t6 + 0x44);
        }
    }
}
