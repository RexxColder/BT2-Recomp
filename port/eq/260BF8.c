#include "common.h"

s32 func_00269A40(s32 arg0, s32 arg1);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_002C3630[] __attribute__((section(".data")));

void func_00260BF8(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 temp_s0_2;
    s32 temp_v0;
    s32 var_s3;
    u8 *var_s1;

    var_s1 = *(u8 **)((u8 *)arg0 + 0x48);
    var_s3 = (arg0 + 0x9A0) + 0xA0;
    if ((arg1 & 0xFF) != 0) {
        temp_v0 = func_00269A40(arg0, *(u16 *)(var_s1 + 0xA));
        func_003126C8((s32)sp, temp_v0 + 0x80);
    } else {
        func_003126C8((s32)sp, (s32)D_002C3630);
    }
    for (;;) {
        temp_v0 = func_00269A40(arg0, *(u16 *)(var_s1 + 0xA));
        temp_s0_2 = temp_v0 + 0xC0;
        sceVu0ApplyMatrix(temp_s0_2, var_s3, temp_v0 + 0x30);
        func_00312650(temp_s0_2, temp_s0_2, (s32)sp);
        if (*(u16 *)(var_s1 + 6) != 0) {
            break;
        }
        var_s1 += *(s32 *)var_s1;
    }
}
