#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void func_00129C28();
void func_00181EA8(void *arg0);
extern f32 D_00384B60;

void func_00181C00(void *arg0, void *arg1) {
    s64 temp_a2;
    s64 temp_a3;
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s2;
    u8 *var_v0;
    u8 *var_v1;

    var_s0 = (u8 *)arg1;
    var_s2 = (u8 *)arg0;
    var_s1 = *(u8 **)(var_s2 + 0x38);
    memset(var_s1, 0, 0xB0);
    var_v1 = var_s1;
    var_v0 = var_s0;
    do {
        temp_a2 = *(s64 *)(var_v0 + 0x8);
        temp_a3 = *(s64 *)(var_v0 + 0x10);
        *(s64 *)(var_v1 + 0x0) = *(s64 *)(var_v0 + 0x0);
        *(s64 *)(var_v1 + 0x8) = temp_a2;
        *(s64 *)(var_v1 + 0x10) = temp_a3;
        *(s64 *)(var_v1 + 0x18) = *(s64 *)(var_v0 + 0x18);
        var_v0 += 0x20;
        var_v1 += 0x20;
    } while (var_v0 != var_s0 + 0x40);
    *(s64 *)(var_v1 + 0x0) = *(s64 *)(var_v0 + 0x0);
    var_s0 += 0x40;
    *(s64 *)(var_v1 + 0x8) = *(s64 *)(var_v0 + 0x8);
    func_00129C28(var_s1 + 0x50, var_s0, (s32)temp_a2, (s32)temp_a3);
    func_00129C28(var_s1 + 0x60, var_s0);
    func_00129C28(var_s1 + 0x70, var_s0);
    *(s32 *)(var_s1 + 0x98) = 1;
    *(f32 *)(var_s1 + 0x90) = D_00384B60;
    *(f32 *)(var_s1 + 0x94) = 30.0f;
    *(f32 *)(var_s1 + 0x9C) = 1.0f;
    func_00181EA8(var_s2);
}
