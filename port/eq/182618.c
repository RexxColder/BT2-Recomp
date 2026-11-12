#include "common.h"

void func_0014EAE8(s32 arg0, void *arg1, s64 arg2, s64 arg3);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_00182618(u8 *arg0, u8 *arg1) {
    u8 *var_s0;
    u8 *var_v0;
    u8 *temp_s1;
    u8 *temp_s2;
    u8 *temp_v1;
    s64 temp_a2;
    s64 temp_a3;

    var_s0 = arg1;
    temp_s1 = *(u8 **)(arg0 + 0x38);
    temp_s2 = temp_s1 + 0xA00;
    memset(temp_s1, 0, 0xB10);
    var_v0 = temp_s2;
    temp_v1 = arg1 + 0x80;
    do {
        temp_a2 = *(s64 *)(var_s0 + 0x10);
        temp_a3 = *(s64 *)(var_s0 + 0x18);
        *(s64 *)(var_v0 + 0) = *(s64 *)(var_s0 + 0);
        *(s64 *)(var_v0 + 8) = *(s64 *)(var_s0 + 8);
        *(s64 *)(var_v0 + 0x10) = temp_a2;
        *(s64 *)(var_v0 + 0x18) = temp_a3;
        var_s0 += 0x20;
        var_v0 += 0x20;
    } while (var_s0 != temp_v1);
    *(s32 *)(temp_s1 + 0xA84) = 0;
    *(s32 *)(temp_s1 + 0xA80) = *(s32 *)(temp_s1 + 0xA80) | 0x10;
    *(f32 *)(temp_s1 + 0xA88) = *(f32 *)(temp_s2 + 0xC);
    func_0014EAE8(*(s32 *)(temp_s2 + 0x24), temp_s1, temp_a2, temp_a3);
}
