#include "common.h"

f32 EftMath_WrapAngle(f32 farg0);
f32 Mathf_Cos(f32 farg0);
f32 func_0012A3F8(f32 farg0);
s32 rand(void);

extern f32 D_003854F4;
extern f32 D_003854F8;
extern u8 *D_00387E9C;

void func_001D7288(u8 *arg0) {
    f32 sp0;
    f32 sp4;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f2;
    f32 temp_f6;
    f32 temp_f13;
    f32 temp_f20;
    f32 var_f2;
    s32 state;
    s32 flag64;
    s32 cond;

    state = *(u8 *)(arg0 + 0x63);
    if (state == 0) {
        temp_f0 = *(f32 *)(arg0 + 0x58) - 1.0f;
        *(f32 *)(arg0 + 0x58) = temp_f0;
        if (temp_f0 <= 0.0f) {
            *(f32 *)(arg0 + 0x58) = 0.0f;
            *(u8 *)(arg0 + 0x63) = 1;
            *(u8 *)(arg0 + 0x68) = 1;
            goto block_12;
        }
    } else if (state == 1) {
block_12:
        *(f32 *)(arg0 + 0x34) = 200.0f;
        temp_f0 = (((f32)rand() / D_003854F4) * 0.5f) + 0.5f;
        if (temp_f0 == 0.0f) {
            var_f2 = -200.0f;
        } else {
            var_f2 = -200.0f / (((((f32)rand() / D_003854F4) * 0.5f) + 0.5f) * 30.0f);
        }
        *(f32 *)(arg0 + 0x38) = var_f2;
        *(u8 *)(arg0 + 0x64) = (u8)(*(u8 *)(arg0 + 0x64) | 2);
        *(u8 *)(arg0 + 0x63) = (u8)(*(u8 *)(arg0 + 0x63) + 1);
        *(f32 *)(arg0 + 0x3C) = 0.0f;
    } else if (state == 2) {
        if (*(u8 *)(arg0 + 0x64) == 0) {
            *(u8 *)(arg0 + 0x63) = 3;
        }
    } else {
        *(u8 *)(arg0 + 0x67) = 0;
        *(u8 *)(arg0 + 0x68) = 0;
        *(s32 *)((u8 *)D_00387E9C + 0x1440) = *(s32 *)((u8 *)D_00387E9C + 0x1440) - 1;
    }

    if (*(u8 *)(arg0 + 0x68) != 0) {
        temp_f0_2 = EftMath_WrapAngle((*(f32 *)(arg0 + 0x40) / 180.0f) * D_003854F8);
        temp_f20 = temp_f0_2;
        sp0 = func_0012A3F8(temp_f20);
        sp4 = 0.0f;
        temp_f0_3 = Mathf_Cos(temp_f20);
        temp_f2 = *(f32 *)(arg0 + 0x20);
        temp_f13 = *(f32 *)(arg0 + 0x44);
        temp_f6 = *(f32 *)(arg0 + 0x8) + (temp_f0_3 * temp_f2);
        flag64 = *(u8 *)(arg0 + 0x64);
        *(f32 *)(arg0 + 0x44) = temp_f13 + (temp_f13 * *(f32 *)(arg0 + 0x48));
        *(f32 *)(arg0 + 0x0) = *(f32 *)(arg0 + 0x0) + (sp0 * temp_f2);
        *(f32 *)(arg0 + 0x8) = temp_f6;
        *(f32 *)(arg0 + 0x40) = *(f32 *)(arg0 + 0x40) + temp_f13;
        *(f32 *)(arg0 + 0x20) = temp_f2 + (temp_f2 * *(f32 *)(arg0 + 0x24));
        *(f32 *)(arg0 + 0x4C) = *(f32 *)(arg0 + 0x4C) + *(f32 *)(arg0 + 0x50);
        *(f32 *)(arg0 + 0x4) = (*(f32 *)(arg0 + 0x4) + (sp4 * temp_f2)) + *(f32 *)(arg0 + 0x54);

        if ((flag64 & 2) != 0) {
            temp_f0_4 = *(f32 *)(arg0 + 0x34) + *(f32 *)(arg0 + 0x38);
            *(f32 *)(arg0 + 0x34) = temp_f0_4;
            if (0.0f < *(f32 *)(arg0 + 0x38)) {
                cond = *(f32 *)(arg0 + 0x3C) < temp_f0_4;
            } else {
                cond = temp_f0_4 < *(f32 *)(arg0 + 0x3C);
            }
            if (cond) {
                *(f32 *)(arg0 + 0x34) = *(f32 *)(arg0 + 0x3C);
                flag64 = flag64 & 0xFD;
                *(u8 *)(arg0 + 0x64) = (u8)flag64;
            }
        }
        if ((flag64 & 4) != 0) {
            temp_f0_5 = *(f32 *)(arg0 + 0x28) + *(f32 *)(arg0 + 0x2C);
            *(f32 *)(arg0 + 0x28) = temp_f0_5;
            if (0.0f < *(f32 *)(arg0 + 0x2C)) {
                cond = *(f32 *)(arg0 + 0x30) < temp_f0_5;
            } else {
                cond = temp_f0_5 < *(f32 *)(arg0 + 0x30);
            }
            if (cond) {
                *(f32 *)(arg0 + 0x28) = *(f32 *)(arg0 + 0x30);
                *(u8 *)(arg0 + 0x64) = (u8)(flag64 & 0xFB);
            }
        }
    }
}
