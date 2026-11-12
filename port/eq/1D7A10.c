#include "common.h"

extern f32 D_003854FC;
extern f32 D_00385500;
extern void *D_00387E9C;

void func_001D7A10(u8 *arg0) {
    u8 v1;
    u8 v1_2;
    f32 f0;
    f32 f1;
    f32 f0_2;
    f32 f0_3;
    f32 f0_4;
    s32 cond;

    v1 = *(u8 *)(arg0 + 0x5F);
    if (v1 == 0) {
        f0 = *(f32 *)(arg0 + 0x54) - 1.0f;
        *(f32 *)(arg0 + 0x54) = f0;
        if (f0 <= 0.0f) {
            *(f32 *)(arg0 + 0x54) = 0.0f;
            *(u8 *)(arg0 + 0x64) = 1;
            *(u8 *)(arg0 + 0x5F) = 1;
            *(u8 *)(arg0 + 0x5F) = (u8)(*(u8 *)(arg0 + 0x5F) + 1);
        }
    } else if (v1 == 1) {
        *(u8 *)(arg0 + 0x5F) = (u8)(*(u8 *)(arg0 + 0x5F) + 1);
    }
    if (*(u8 *)(arg0 + 0x64) != 0) {
        f0_2 = *(f32 *)(arg0 + 0x38);
        f1 = f0_2 * *(f32 *)(arg0 + 0x3C);
        *(f32 *)(arg0 + 0x34) = *(f32 *)(arg0 + 0x34) + f0_2;
        f0_3 = f0_2 + f1;
        *(f32 *)(arg0 + 0x38) = f0_3;
        if (f0_3 < D_003854FC) {
            *(f32 *)(arg0 + 0x38) = D_003854FC;
        }
        v1_2 = *(u8 *)(arg0 + 0x60);
        *(f32 *)(arg0 + 0x50) = *(f32 *)(arg0 + 0x50) + D_00385500;
        if (v1_2 & 2) {
            f1 = *(f32 *)(arg0 + 0x44);
            f0_4 = *(f32 *)(arg0 + 0x40) + f1;
            *(f32 *)(arg0 + 0x40) = f0_4;
            if (f1 > 0.0f) {
                cond = *(f32 *)(arg0 + 0x48) < f0_4;
            } else {
                cond = f0_4 < *(f32 *)(arg0 + 0x48);
            }
            if (cond) {
                *(f32 *)(arg0 + 0x40) = *(f32 *)(arg0 + 0x48);
                *(u8 *)(arg0 + 0x60) = (u8)(v1_2 & 0xFD);
            }
        }
        if (*(f32 *)(arg0 + 0x40) <= 0.0f) {
            *(f32 *)(arg0 + 0x40) = 0.0f;
            *(u8 *)(arg0 + 0x64) = 0;
            *(s8 *)(arg0 + 0x63) = 0;
            *(s32 *)((u8 *)D_00387E9C + 0x1444) = *(s32 *)((u8 *)D_00387E9C + 0x1444) - 1;
        }
    }
}
