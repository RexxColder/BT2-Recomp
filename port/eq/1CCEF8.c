#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0, s32 arg1);
s32 Rand_IntRange(s32 arg0, s32 arg1);
void Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_001CD478(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001CD958(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00342E48[] __attribute__((section(".data")));
extern f32 D_003851E8;
extern u8 *D_003878C8;

void func_001CCEF8(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_a1;
    s32 temp_v1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_r;
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_s3_3;
    s32 var_s4;
    s32 var_s0_2;
    s32 var_v0;
    s32 var_v1;
    f32 temp_f0;

    var_s3 = 0;
    temp_s0 = (s32)D_003878C8;
    temp_s2 = *(s32 *)(arg0 + 0x38);
    var_s4 = temp_s2;
    memset((void *)temp_s2, 0, 0x130);
    temp_v1 = *(s32 *)(arg1 + 0x30);
    temp_a1 = temp_s0 + 8;
    *(s32 *)(temp_s2 + 0x114) = temp_v1;
    *(s32 *)(temp_s2 + 4) = temp_a1;
    *(s32 *)(temp_s2 + 0) = *(s32 *)(temp_s0 + 0);
    *(s32 *)(temp_s2 + 8) = *(s32 *)(temp_s0 + 0x114);
    *(s32 *)(temp_s2 + 0xC) = *(s32 *)(temp_s0 + 0x118) + (temp_v1 * 0x50);
    *(s32 *)(temp_s2 + 0x110) = *(s32 *)(arg1 + 0x34);
    temp_f0 = BtlCharApi_GetHeight(*(s32 *)(arg1 + 0x34), temp_a1);
    *(s32 *)(temp_s2 + 0x124) = 0;
    *(s32 *)(temp_s2 + 0x128) = 0;
    *(f32 *)(temp_s2 + 0x120) = temp_f0 / D_003851E8;
    do {
        var_s0 = var_s4 + 0xC0;
        var_s1 = 1;
        do {
            var_s1 -= 1;
            func_00208DE8(*(s32 *)(arg1 + 0x34), var_s0, 0x2F);
            var_s0 += 0x10;
        } while (var_s1 >= 0);
        var_s3 += 1;
        var_s4 += 0x20;
    } while (var_s3 < 2);
    var_s1_2 = temp_s2 + 0x20;
    var_s3_2 = 9;
    Vec4_Set(temp_s2 + 0x100, 0.0f, 0.0f, 1.0f, 1.0f);
    var_s0_2 = (s32)D_00342E48;
    do {
        temp_r = Rand_IntRange(3, 5);
        temp_a1_2 = *(s32 *)var_s0_2;
        temp_a2 = *(s32 *)(var_s0_2 + 4);
        var_s0_2 += 8;
        var_s3_2 -= 1;
        func_001CD478(var_s1_2, temp_a1_2, temp_a2, temp_r);
        var_s1_2 += 0x10;
    } while (var_s3_2 >= 0);
    func_001CD958(arg0, 5);
    var_v1 = temp_s2;
    var_s3_3 = 0;
    do {
        var_s1_3 = 1;
        var_v0 = var_v1 + 0x14;
        do {
            var_s1_3 -= 1;
            *(s32 *)var_v0 = 0;
            var_v0 -= 4;
        } while (var_s1_3 >= 0);
        var_s3_3 += 1;
        var_v1 += 8;
    } while (var_s3_3 < 2);
    *(u16 *)(temp_s2 + 0x12C) = (u16)(*(u16 *)(temp_s2 + 0x12C) | 1);
}
