#include "common.h"

s32 DemoCam_SetScaleHeight(s32 arg0);
void Ramp_Start(s32 arg0, f32 farg0, f32 farg1, f32 farg2);
void func_00101608(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00105E18(void);
void func_0020CE78(s32 arg0);
void func_0020CF28(s32 arg0);
void func_0025ADD0(s32 arg0, s32 arg1);
void func_00267550(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 *D_00387A40;

s32 func_0010A3B0(s32 arg0) {
    s32 temp_a3;
    u8 v;

    v = *(u8 *)(arg0 + 8);
    if (v == 0) {
        if (func_00105E18() != 0) {
            func_0020CE78(*(u8 *)(arg0 + 9));
            func_0025ADD0(*(u8 *)(arg0 + 9), 1);
            DemoCam_SetScaleHeight(1);
        } else {
            func_0020CF28(*(u8 *)(arg0 + 9));
            func_0025ADD0(*(u8 *)(arg0 + 9), 2);
        }
        Ramp_Start(arg0 + 0x14, 10.0f, 0.0f, 1.0f);
        func_00101608(*(u8 *)(arg0 + 9), *(u16 *)(arg0 + 0x10), *(u16 *)(arg0 + 0xC), 0, 0);
        temp_a3 = *D_00387A40;
        func_00267550(temp_a3 + (*(u8 *)(arg0 + 9) * 0x18580), 2, *(u16 *)(arg0 + 0xC), temp_a3);
        *(u8 *)(arg0 + 8) = (u8)(*(u8 *)(arg0 + 8) + 1);
    } else if (v == 2) {
        Ramp_Start(arg0 + 0x14, 1.5f, 0.0f, 1.0f);
        *(u8 *)(arg0 + 8) = (u8)(*(u8 *)(arg0 + 8) + 1);
    }
    return 5;
}
