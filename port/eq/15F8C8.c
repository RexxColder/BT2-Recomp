#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
void func_0014EAE8(s32 arg0, void *arg1);
void func_0015F260(void *arg0);
void *func_001F3758(void *arg0);
s32 func_0020B3D0(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_00384730;
extern f32 D_00384734;
extern f32 D_00384738;

void func_0015F8C8(u8 *arg0, u8 *arg1) {
    u8 *temp_s3;
    u8 *temp_s1;
    s32 temp_s2;
    s32 temp_v0;
    f32 temp_f0;

    temp_s3 = *(u8 **)(arg0 + 0x38);
    temp_s2 = *(s32 *)((u8 *)func_001F3758(arg0) + 0x38);
    memset(temp_s3, 0, 0xBA0);
    *(u8 **)(temp_s3 + 0xF0) = arg1;
    temp_s1 = *(u8 **)(arg1 + 0x24);
    temp_v0 = func_0020B3D0(*(s32 *)arg1);
    *(s32 *)(temp_s3 + 8) = temp_v0;
    *(f32 *)(temp_s3 + 0x18) = *(f32 *)(temp_s1 + 8) * D_00384730;
    *(f32 *)(temp_s3 + 0x1C) = *(f32 *)(temp_s1 + 4);
    temp_f0 = BtlCharApi_GetHeight(temp_v0) / D_00384734;
    *(f32 *)(temp_s3 + 0x20) = temp_f0;
    if (temp_f0 < D_00384738) {
        *(f32 *)(temp_s3 + 0x20) = D_00384738;
    }
    func_0014EAE8(temp_s2, temp_s3 + 0xF4);
    func_0015F260(arg0);
}
