#include "common.h"

f32 func_00128090(s32 arg0);
void func_001280F8(s32 arg0);
void func_00128160(s32 arg0);
extern u8 *D_003876A0;
extern u8 *gEftHitList;

void func_00127128(s32 arg0) {
    u8 *p = (u8 *)arg0;
    u8 *temp_a3;
    u8 *temp_a1;
    u8 *var_a1;
    u8 *var_v0;
    u8 *temp_a2;

    if (gEftHitList == NULL) {
        return;
    }
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        if (*(s32 *)(gEftHitList + 0x6000) >= 0x40) {
            *(s32 *)(gEftHitList + 0x6000) = 0;
        }
        temp_a3 = *(u8 **)(p + 0x64);
        if (temp_a3 != NULL) {
            *(s32 *)(p + 0x0) = *(s32 *)(temp_a3 + 0x0);
            *(s32 *)(p + 0xF0) = *(s32 *)(temp_a3 + 0x8);
            *(f32 *)(p + 0x78) = *(f32 *)(*(u8 **)(temp_a3 + 0x24) + 0x8);
            *(s32 *)(p + 0x4) = *(s32 *)(*(u8 **)(temp_a3 + 0x20) + 0xC);
            *(s32 *)(p + 0xC) = 1;
            *(s32 *)(p + 0x8) = *(s32 *)(*(u8 **)(temp_a3 + 0x20) + 0x10);
            *(s32 *)(p + 0x54) = ((*(s32 *)(*(u8 **)(temp_a3 + 0x20) + 0x30) >> 1) & 1);
            *(f32 *)(p + 0x74) = func_00128090(arg0);
            func_001280F8(arg0);
            if (*(s32 *)(*(u8 **)(*(u8 **)(p + 0x64) + 0x20) + 0x8) == 7) {
                *(s32 *)(p + 0x50) = *(s32 *)(p + 0x50) | 8;
            }
            func_00128160(arg0);
        }
        temp_a1 = *(u8 **)(p + 0x68);
        if (temp_a1 != NULL) {
            *(s32 *)(p + 0x0) = *(s16 *)(temp_a1 + 0x12);
            *(s32 *)(p + 0xF0) = *(s16 *)(temp_a1 + 0x16);
            *(f32 *)(p + 0x78) = *(f32 *)(temp_a1 + 0x20);
            *(s32 *)(p + 0x4) = *(u8 *)(temp_a1 + 0x1B);
            *(s32 *)(p + 0xC) = 0;
            *(s32 *)(p + 0x8) = *(s32 *)(temp_a1 + 0x30);
            *(s32 *)(p + 0x54) = 0;
            *(f32 *)(p + 0x74) = func_00128090(arg0);
        }
        var_a1 = p;
        temp_a2 = var_a1 + 0x180;
        var_v0 = gEftHitList + (*(s32 *)(gEftHitList + 0x6000) * 0x180);
        do {
            *(s64 *)(var_v0 + 0x0) = *(s64 *)(var_a1 + 0x0);
            *(s64 *)(var_v0 + 0x8) = *(s64 *)(var_a1 + 0x8);
            *(s64 *)(var_v0 + 0x10) = *(s64 *)(var_a1 + 0x10);
            *(s64 *)(var_v0 + 0x18) = *(s64 *)(var_a1 + 0x18);
            var_a1 += 0x20;
            var_v0 += 0x20;
        } while (var_a1 != temp_a2);
        *(s32 *)(gEftHitList + 0x6000) = *(s32 *)(gEftHitList + 0x6000) + 1;
    }
}
