#include "common.h"

void ColBox_SetCenterHalf(s32 arg0, s32 arg1, s32 arg2);
void StgGround_Probe(f32 f, s32 a, void *b, void *c);
s32 func_003126C8(s32 arg0, s32 arg1);
extern s64 D_0036CBF0[2] __attribute__((section(".data")));

void func_0011CA40(u8 *arg0) {
    u8 sp[0x40] __attribute__((aligned(8)));
    s64 sp30;
    s64 sp38;
    u8 *temp_s2;
    u8 *temp_s3;
    f32 *temp_s4;

    temp_s2 = arg0 + 0x9A0;
    temp_s3 = arg0 + 0xE50;
    temp_s4 = *(f32 **)(arg0 + 0xF40);
    sp38 = D_0036CBF0[1];
    sp30 = D_0036CBF0[0];
    *(s64 *)(sp + 0x30) = sp30;
    *(s64 *)(sp + 0x38) = sp38;
    if (temp_s4 != NULL) {
        func_003126C8((s32)(sp + 0x20), (s32)(arg0 + 0x9C0));
        *(f32 *)(sp + 0x24) = temp_s4[1];
        ColBox_SetCenterHalf((s32)sp, (s32)(sp + 0x20), (s32)(sp + 0x30));
        *(f32 *)(temp_s3 + 0x10) = *(f32 *)(temp_s2 + 0x20);
        *(f32 *)(temp_s3 + 0x14) = *(f32 *)(temp_s2 + 0x24);
        *(f32 *)(temp_s3 + 0x18) = *(f32 *)(temp_s2 + 0x28);
        StgGround_Probe(temp_s4[1], *(s32 *)(temp_s2 + 0x50), (s32)sp, (s32)(arg0 + 0xE60));
    }
}
