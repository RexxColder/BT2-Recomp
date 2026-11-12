#include "common.h"

void Ramp_Start(f32 farg0, f32 farg1, f32 farg2, void *arg0);
void func_003126C8(void *arg0, void *arg1);
void func_00312650(void *arg0, void *arg1, void *arg2);
extern s64 D_00376DB0[16] __attribute__((section(".data")));
extern u8 *D_00387B00;

void func_002822C8(f32 farg0, s32 arg0, s32 arg1) {
    s64 sp[16];
    s32 i;
    u32 temp_a0;
    s32 temp_s3;
    u8 *temp_s0;
    u8 *temp_s1;
    u8 *temp_s2;
    u8 temp_v1;
    u8 var_v0_2;

    for (i = 0; i < 16; i++) {
        sp[i] = D_00376DB0[i];
    }
    temp_a0 = ((u32)arg0 < 4U) ? (u32)arg0 : 0U;
    temp_s3 = temp_a0 * 2;
    temp_s2 = D_00387B00 + temp_a0 * 0x60;
    temp_v1 = *(u8 *)(temp_s2 + 0x58);
    if (!(temp_v1 & 1)) {
        if (arg1 == 1) {
            return;
        }
        *(u8 *)(temp_s2 + 0x58) = 3;
        temp_s1 = temp_s2 + 0x10;
        temp_s0 = temp_s2 + 0x20;
        func_003126C8(temp_s1, (u8 *)sp + (temp_s3 + arg1) * 0x10);
        func_003126C8(temp_s0, (u8 *)sp + (temp_s3 + (arg1 ^ 1)) * 0x10);
        func_00312650(temp_s2 + 0x30, temp_s0, temp_s1);
    } else {
        if (arg1 == 0) {
            if (temp_v1 & 2) {
                return;
            }
            var_v0_2 = 3;
        } else {
            if (temp_v1 & 4) {
                return;
            }
            var_v0_2 = 5;
        }
        *(u8 *)(temp_s2 + 0x58) = var_v0_2;
        temp_s1 = temp_s2 + 0x10;
        temp_s0 = temp_s2 + 0x20;
        func_003126C8(temp_s1, temp_s2);
        func_003126C8(temp_s0, (u8 *)sp + (temp_s3 + (arg1 ^ 1)) * 0x10);
        func_00312650(temp_s2 + 0x30, temp_s0, temp_s1);
    }
    Ramp_Start(farg0, 0.0f, 1.0f, temp_s2 + 0x40);
}
