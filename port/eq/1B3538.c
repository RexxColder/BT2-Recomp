#include "common.h"

void func_00129C38(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3);
void func_0012A3A0(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *t0);
extern s32 EftChain2_Update __attribute__((section(".data")));

s32 EftChain2_Warp(u8 *arg0, s32 arg1) {
    s32 temp_a2;
    s32 var_s5;
    s32 var_v0;
    u8 *temp_s4;
    u8 *temp_v0;
    u8 *var_s0;
    u8 *var_s1;

    var_v0 = 0;
    if (arg0 != NULL) {
        temp_a2 = *(s32 *)(*(u8 **)(arg0 + 0x28));
        if (temp_a2 == (s32)0x001B2FD0u) { /* PS2 address of EftChain2_Update */
            temp_s4 = *(u8 **)(arg0 + 0x38);
            if (*(s32 *)(temp_s4 + 0xA40) & 1) {
                var_s1 = temp_s4 + 0x40;
                func_00129C38(temp_s4 + 0x10, arg1, temp_a2, arg0);
                var_s5 = 0xF;
                do {
                    if (*(s32 *)(var_s1 + 8) & 1) {
                        var_s0 = *(u8 **)(var_s1 + 0);
                        if (var_s0 != NULL) {
                            do {
                                func_0012A3A0(var_s0 + 0x40, temp_s4 + 0x10, var_s1 + 0x50, var_s0 + 0x20, var_s0 + 0x30);
                                *(f32 *)(var_s0 + 0x4C) = 1.0f;
                                temp_v0 = *(u8 **)(var_s0 + 0x60);
                                var_s0 = temp_v0;
                            } while (temp_v0 != NULL);
                        }
                    }
                    var_s5 -= 1;
                    var_s1 += 0xA0;
                } while (var_s5 >= 0);
                var_v0 = 1;
            }
        }
    }
    return var_v0;
}
