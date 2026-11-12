#include "common.h"

void BtlAnim_SetBlend(f32 arg0, s32 arg1);
s32 BtlChar_GetPos(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
void func_00203888(s32 arg0, s32 arg1, s32 arg2);
s32 func_00203C58(s32 arg0, s64 arg1);
void func_00203C88(s32 arg0, s64 arg1);
void func_0020D048(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_0020D240(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
s32 func_00210DD8(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212878(void);
extern f32 D_00386AD4;
extern f32 D_00386AD8;
extern f32 D_00386ADC;
extern f32 D_00386AE0;

s32 func_00238538(s32 arg0) {
    s32 temp_v0;

    temp_v0 = BtlObjXf_Update(arg0);
    switch (temp_v0) {
    case 0xA9:
        if (func_00211310(arg0, 0, 0x20) == 0) {
            if (func_00212878() != 0) {
                if (func_00211310(arg0, 0, 0x40) != 0) {
                    goto block_7;
                }
                return -1;
            }
            return -1;
        }
block_7:
        BtlAnim_SetBlend(D_00386AD4, arg0);
        return 0x26;
    case 0xAA:
        if (func_00211310(arg0, 2, 1) != 0) {
            if (*(u8 *)((u8 *)arg0 + 0xB54) != 0) {
                func_002113C0(arg0, 2, 0x1000, 1);
            }
            func_002113C0(arg0, 6, 0x10, 1);
            func_0020D048(BtlChar_GetPos(arg0), 100.0f, 1000.0f, 3.0f, D_00386AD8);
            func_0020D240(BtlChar_GetPos(arg0), 100.0f, 1000.0f, D_00386ADC, D_00386AE0);
            if (func_00203C58(func_00211288(func_00210DD8(arg0)), (s64)0x8000 << 16) != 0) {
                func_002113C0(arg0, 0, 0x4000, 1);
                func_00203888(arg0, 0x186A0, 1);
                func_00203C88(func_00211288(func_00210DD8(arg0)), (s64)0x8000 << 16);
            }
            return 0xA8;
        }
        return -1;
    default:
        return -1;
    }
}
