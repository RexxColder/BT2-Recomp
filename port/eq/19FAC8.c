#include "common.h"

void BtlTask_SetDead(u8 *arg0, u8 *arg1, u8 *arg2);
extern void *D_003876A0;

void func_0019FAC8(u8 *arg0) {
    u8 *a1;
    u8 v1;
    f32 f0;
    f32 f1;

    a1 = *(u8 **)(arg0 + 0x38);
    if ((*(s64 *)((u8 *)D_003876A0 + 0x4D8) & 0x100) == 0 && *(u8 *)(a1 + 0x2C) == 0) {
        v1 = *(u8 *)(arg0 + 0x1);
        switch (v1) {
        case 0:
            f0 = *(f32 *)(a1 + 0x10) - 1.0f;
            *(s32 *)(a1 + 0x30) = 1;
            *(f32 *)(a1 + 0x10) = f0;
            *(f32 *)(a1 + 0x20) = f0 / *(f32 *)(a1 + 0x24);
            if (f0 <= 0.0f) {
                *(f32 *)(a1 + 0x10) = 0.0f;
                *(u8 *)(arg0 + 0x1) = 1;
            }
            break;
        case 1:
            f0 = *(f32 *)(a1 + 0x14) - 1.0f;
            *(s32 *)(a1 + 0x30) = 2;
            *(f32 *)(a1 + 0x14) = f0;
            if (f0 <= 0.0f) {
                *(f32 *)(a1 + 0x14) = 0.0f;
                *(u8 *)(arg0 + 0x1) = 2;
            }
            break;
        case 2:
            f0 = *(f32 *)(a1 + 0x18) - 1.0f;
            *(s32 *)(a1 + 0x30) = 4;
            f1 = f0 / *(f32 *)(a1 + 0x28);
            *(f32 *)(a1 + 0x18) = f0;
            *(f32 *)(a1 + 0x20) = 1.0f - f1;
            if (f0 <= 0.0f) {
                *(f32 *)(a1 + 0x18) = 0.0f;
                BtlTask_SetDead(arg0, a1, arg0);
            }
            break;
        }
    }
}
