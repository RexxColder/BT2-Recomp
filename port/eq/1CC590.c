#include "common.h"

s32 EftMod1CC_SetTex(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void Vec4_Set(f32 farg0, f32 farg1, f32 farg2, f32 farg3, void *arg4);
void func_00129C38(void *arg0, void *arg1, s32 arg2, s32 arg3);
void *memset(void *arg0, s32 arg1, u32 arg2);

void EftMod1CC_Init(u8 *arg0, u8 *arg1) {
    u8 *temp_s0;
    u8 *temp_s2;
    u8 *temp_s3;
    s32 a2;
    s32 a2call;
    s32 temp_a3;
    s32 v0;
    f32 f1v;
    f32 v;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    temp_s3 = *(u8 **)(arg1 + 0x38);
    temp_s2 = *(u8 **)(arg1 + 0x34);
    memset(temp_s0, 0, 0xD0);
    a2 = *(s32 *)(temp_s0 + 0x40);
    *(s64 *)(temp_s0 + 0x00) = *(s64 *)(arg1 + 0x00);
    temp_a3 = a2 | 1;
    *(s64 *)(temp_s0 + 0x08) = *(s64 *)(arg1 + 0x08);
    *(s64 *)(temp_s0 + 0x10) = *(s64 *)(arg1 + 0x10);
    *(s64 *)(temp_s0 + 0x18) = *(s64 *)(arg1 + 0x18);
    *(s64 *)(temp_s0 + 0x20) = *(s64 *)(arg1 + 0x20);
    *(s64 *)(temp_s0 + 0x28) = *(s64 *)(arg1 + 0x28);
    *(s64 *)(temp_s0 + 0x30) = *(s64 *)(arg1 + 0x30);
    *(s32 *)(temp_s0 + 0x40) = temp_a3;
    *(s64 *)(temp_s0 + 0x38) = *(s64 *)(arg1 + 0x38);

    f1v = *(f32 *)(arg1 + 0x08);
    if (f1v <= 0.0f) {
        a2call = a2 | 9;
        *(s32 *)(temp_s0 + 0x40) = a2call;
    } else {
        a2call = a2;
        *(f32 *)(temp_s0 + 0x58) = f1v * 30.0f;
    }

    *(f32 *)(temp_s0 + 0x64) = *(f32 *)(temp_s2 + 0x08);
    *(s32 *)(temp_s0 + 0x74) = 0;
    *(f32 *)(temp_s0 + 0x68) = *(f32 *)(temp_s2 + 0x0C);
    *(f32 *)(temp_s0 + 0x78) = *(f32 *)(temp_s2 + 0x18) * 30.0f;
    *(f32 *)(temp_s0 + 0x7C) = *(f32 *)(temp_s2 + 0x14) - *(f32 *)(temp_s2 + 0x10);
    func_00129C38(temp_s0 + 0x80, temp_s3, a2call, temp_a3);
    *(s32 *)(temp_s0 + 0x8C) = 0;
    v = *(f32 *)(temp_s0 + 0x8C);
    *(f32 *)(temp_s0 + 0x70) = *(f32 *)(temp_s3 + 0x0C) / *(f32 *)(temp_s2 + 0x1C);
    Vec4_Set(v, 1.0f, v, 1.0f, temp_s0 + 0x90);

    v0 = (s32)((u32)*(s32 *)(temp_s2 + 0x24) * (u32)*(s32 *)(temp_s2 + 0x28));
    *(s32 *)(temp_s0 + 0x48) = v0;
    if (v0 >= 2) {
        *(s32 *)(temp_s0 + 0x40) = *(s32 *)(temp_s0 + 0x40) | 0x100;
        *(f32 *)(temp_s0 + 0x4C) = 1.0f / (f32)*(s32 *)(temp_s2 + 0x24);
        *(f32 *)(temp_s0 + 0x50) = 1.0f / (f32)*(s32 *)(temp_s2 + 0x28);
    } else {
        *(f32 *)(temp_s0 + 0x50) = 1.0f;
        *(f32 *)(temp_s0 + 0x4C) = 1.0f;
    }
    EftMod1CC_SetTex(temp_s0, *(s32 *)(arg1 + 0x30), *(s32 *)(arg1 + 0x04), *(s32 *)(arg1 + 0x04));
}
