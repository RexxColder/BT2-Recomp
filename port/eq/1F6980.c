#include "common.h"

void func_00206EA0(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211D80(s32 arg0, s32 arg1);

void func_001F6980(s32 arg0) {
    u8 *p = (u8 *)arg0;
    u8 *temp_a1;
    u8 *temp_s1;
    u8 *var_a0;
    u8 *var_v0;
    u8 *var_v0_2;
    u8 *var_v1;

    if (*(u8 *)(p + 0x1434) != 0) {
        func_00206EA0(arg0, 0);
    }
    func_002113C0(arg0, 0, 2, 0);
    temp_s1 = p + 0x510;
    func_002113C0(arg0, 0, 4, 1);
    func_002113C0(arg0, 0, 1, 1);
    func_002113C0(arg0, 0, 0x400000, 1);
    func_002113C0(arg0, 9, 0x10000, 0);
    memset((s32)temp_s1, 0, 0xE0);
    func_00211D80(arg0, 0);
    temp_a1 = p + 0x5F0;
    var_v1 = temp_a1;
    var_v0 = temp_s1;
    do {
        *(s64 *)(var_v1 + 0x0) = *(s64 *)(var_v0 + 0x0);
        *(s64 *)(var_v1 + 0x8) = *(s64 *)(var_v0 + 0x8);
        *(s64 *)(var_v1 + 0x10) = *(s64 *)(var_v0 + 0x10);
        *(s64 *)(var_v1 + 0x18) = *(s64 *)(var_v0 + 0x18);
        var_v0 += 0x20;
        var_v1 += 0x20;
    } while (var_v0 != temp_a1);
    var_a0 = temp_s1;
    var_v0_2 = p + 0x6D0;
    do {
        *(s64 *)(var_v0_2 + 0x0) = *(s64 *)(var_a0 + 0x0);
        *(s64 *)(var_v0_2 + 0x8) = *(s64 *)(var_a0 + 0x8);
        *(s64 *)(var_v0_2 + 0x10) = *(s64 *)(var_a0 + 0x10);
        *(s64 *)(var_v0_2 + 0x18) = *(s64 *)(var_a0 + 0x18);
        var_a0 += 0x20;
        var_v0_2 += 0x20;
    } while (var_a0 != temp_a1);
    *(s32 *)(p + 0xC00) = 2;
    *(s32 *)(p + 0xC0C) = -1;
    *(s32 *)(p + 0xB48) = 1;
    *(f32 *)(p + 0x101C) = 0.5f;
    *(f32 *)(p + 0x1020) = 500.0f;
    *(s32 *)(p + 0x984) = 0;
    *(s32 *)(p + 0xC08) = -1;
    *(s32 *)(p + 0x988) = 0;
    *(s32 *)(p + 0x98C) = 0;
}
