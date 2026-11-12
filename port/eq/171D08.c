#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
void func_0014EAE8(s32 arg0, u8 *arg1);
u8 *func_001F3758(s32 arg0); /* GUESS arity: a0 = arg0 passes through */
s32 func_0020B3D0(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_003848D8;
extern f32 D_003848DC;

void func_00171D08(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    s32 temp_s2;
    s32 temp_v0;
    u8 *temp_s1;
    u8 *temp_s3;

    temp_s3 = *(u8 **)(arg0 + 0x38);
    temp_s2 = *(s32 *)(func_001F3758((s32)arg0) + 0x38);
    memset(temp_s3, 0, 0xAB0);
    *(u8 **)(temp_s3 + 0xB0) = arg1;
    temp_s1 = *(u8 **)(arg1 + 0x24);
    temp_v0 = func_0020B3D0(*(s32 *)arg1);
    *(s32 *)(temp_s3 + 8) = temp_v0;
    *(f32 *)(temp_s3 + 0x18) = *(f32 *)(temp_s1 + 8);
    *(f32 *)(temp_s3 + 0x1C) = *(f32 *)(temp_s1 + 4);
    temp_f0 = BtlCharApi_GetHeight(temp_v0) / D_003848D8;
    *(f32 *)(temp_s3 + 0x20) = temp_f0;
    if (temp_f0 < D_003848DC) {
        *(f32 *)(temp_s3 + 0x20) = D_003848DC;
    }
    func_0014EAE8(temp_s2, temp_s3 + 0xB4);
}
