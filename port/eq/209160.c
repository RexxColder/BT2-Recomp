#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);
s32 func_00269A08(s32 arg0, s32 arg1);

void func_00209160(s32 arg0, u8 *arg1, s32 arg2) {
    s32 temp_v0;
    u8 *temp_v0_2;

    temp_v0 = BtlObjVis_GetView_207EA0(arg0);
    if (temp_v0 != 0) {
        temp_v0_2 = (u8 *)func_00269A08(temp_v0, arg2);
        if (temp_v0_2 != 0) {
            *(u32 *)(arg1 + 0x0) = *(u32 *)(temp_v0_2 + 0x40);
            *(u32 *)(arg1 + 0x4) = *(u32 *)(temp_v0_2 + 0x44);
            *(u32 *)(arg1 + 0x8) = *(u32 *)(temp_v0_2 + 0x48);
            *(u32 *)(arg1 + 0xC) = *(u32 *)(temp_v0_2 + 0x4C);
            return;
        }
        *(s32 *)(arg1 + 0x0) = 0;
        *(f32 *)(arg1 + 0xC) = 1.0f;
    } else {
        *(s32 *)(arg1 + 0xC) = 0;
        *(s32 *)(arg1 + 0x0) = 0;
    }
    *(s32 *)(arg1 + 0x4) = 0;
    *(s32 *)(arg1 + 0x8) = 0;
}
