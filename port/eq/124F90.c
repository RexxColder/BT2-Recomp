#include "common.h"

u8 *func_00126040(s32 arg0);
s32 func_00210DD8(u8 *arg0);
u8 *func_00211288(s32 arg0);

void func_00124F90(s32 arg0) {
    s32 temp_v1;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_s1 = (u8 *)arg0 + 0x10A0;
    temp_v0 = func_00126040(arg0);
    temp_v0_2 = func_00211288(func_00210DD8(temp_v0));
    temp_v1 = *(s32 *)(temp_v0 + 0x146C);
    if (temp_v1 == 0) {
        *(s32 *)(temp_s1 + 0x8C) = 0;
        *(s32 *)(temp_s1 + 0x88) = 0;
        return;
    }
    *(f32 *)(temp_s1 + 0x88) = (f32)*(s32 *)(temp_v0_2 + 0x1470) / (f32)temp_v1;
    *(f32 *)(temp_s1 + 0x8C) = (f32)*(s32 *)(temp_v0_2 + 0x1474) / (f32)*(s32 *)(temp_v0 + 0x146C);
    *(f32 *)(temp_s1 + 0x90) = (f32)*(s32 *)(temp_v0_2 + 0x1478) / (f32)*(s32 *)(temp_v0 + 0x146C);
}
