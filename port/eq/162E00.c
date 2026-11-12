#include "common.h"

extern u8 *D_00387AD8;
extern s32 D_00387AE4;

void func_00162E00(u8 *arg0) {
    u64 mask;
    u8 *temp_a2;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_a2 = *(u8 **)(arg0 + 0x38);
    if ((*(s32 *)(*(u8 **)(*(u8 **)(temp_a2 + 0xB0) + 0x20)) == 0x172) && (*(s32 *)temp_a2 & 0x800)) {
        temp_v1 = D_00387AD8;
        D_00387AD8 += 0x40;
        *(u16 *)(temp_v1 + 0x30) = 0x7000;
        *(u16 *)(temp_v1 + 0x32) = 0x7200;
        *(u16 *)(temp_v1 + 0x38) = (u16)-0x7000;
        *(u16 *)(temp_v1 + 0x3A) = (u16)-0x7200;
        mask = ((u64)-1 << 40) >> 8;
        *(u64 *)(temp_v1 + 0x30) |= mask;
        *(u64 *)(temp_v1 + 0x38) |= mask;
        *(s64 *)(temp_v1 + 0x20) = 0x46;
        *(s64 *)(temp_v1 + 0x00) = (s64)0xA0000003ULL;
        *(s64 *)(temp_v1 + 0x10) = (s64)0x4400000000008001ULL;
        *(s64 *)(temp_v1 + 0x18) = 0x4410;
        *(u8 *)(temp_v1 + 0x2B) = 0x40;
        *(f32 *)(temp_v1 + 0x2C) = 1.0f;
        *(s8 *)(temp_v1 + 0x3F) = -1;
        *(s8 *)(temp_v1 + 0x28) = -1;
        *(s8 *)(temp_v1 + 0x29) = -1;
        *(s8 *)(temp_v1 + 0x2A) = -1;
        *(s8 *)(temp_v1 + 0x37) = -1;
        temp_v0 = (u8 *)(D_00387AE4 + 8);
        *(u8 **)(*(u8 **)(temp_v0 + 4) + 4) = temp_v1;
        *(u8 **)(temp_v0 + 4) = temp_v1;
    }
}
