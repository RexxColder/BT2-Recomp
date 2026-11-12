#include "common.h"

void Vec3_Sub(u8 *arg0, u8 *arg1, u8 *arg2);
void func_001865B8(u8 *arg0, u8 arg1, u8 arg2);
void func_00187470(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);

void func_001840C8(u8 *arg0, u8 *arg1) {
    u8 *s0;
    s32 a2;
    u8 temp_v0;

    s0 = *(u8 **)(arg0 + 0x38);
    memset(s0, 0, 0x1B0);
    if (*(f32 *)(arg1 + 0x1C) != 1.0f) {
        *(f32 *)(arg1 + 0x1C) = 1.0f;
    }
    *(u8 **)(s0 + 0x30) = *(u8 **)(arg1 + 0x00);
    *(s32 *)(s0 + 0x34) = *(s32 *)(arg1 + 0x04);
    *(s32 *)(s0 + 0x94) = *(s32 *)(arg1 + 0x5C);
    *(s64 *)(s0 + 0x40) = *(s64 *)(arg1 + 0x10);
    *(s64 *)(s0 + 0x48) = *(s64 *)(arg1 + 0x18);
    *(s64 *)(s0 + 0x50) = *(s64 *)(arg1 + 0x20);
    *(s64 *)(s0 + 0x58) = *(s64 *)(arg1 + 0x28);
    *(s64 *)(s0 + 0x60) = *(s64 *)(arg1 + 0x20);
    *(s64 *)(s0 + 0x68) = *(s64 *)(arg1 + 0x28);
    Vec3_Sub(s0 + 0x70, arg1 + 0x30, arg1 + 0x20);
    *(f32 *)(s0 + 0x80) = *(f32 *)(arg1 + 0x50);
    *(s32 *)(s0 + 0x8C) = 0;
    *(s32 *)(s0 + 0x90) = 0;
    *(f32 *)(s0 + 0x84) = *(f32 *)(arg1 + 0x54) * 30.0f;
    temp_v0 = *(u8 *)(arg1 + 0x58);
    *(u8 *)(s0 + 0x198) = temp_v0;
    a2 = temp_v0 & 0xFF;
    if (a2 >= *(s32 *)(*(u8 **)(arg1 + 0x08) + 0x100)) {
        *(u8 *)(s0 + 0x198) = 0;
        a2 = 0;
    }
    func_00187470(s0, *(u8 **)(arg1 + 0x08), a2, a2);
    *(s32 *)(s0 + 0x1A4) = 0;
    *(s32 *)(s0 + 0x1A8) = 0;
    *(s32 *)(s0 + 0x19C) = *(s32 *)(s0 + 0x19C) | 2;
    *(s8 *)(s0 + 0x199) = (s8)(*(u8 *)(*(u8 **)(arg1 + 0x00) + 0xA0) * *(u8 *)(*(u8 **)(arg1 + 0x00) + 0xA1));
    func_001865B8(s0, *(u8 *)(*(u8 **)(arg1 + 0x00) + 0xA0), *(u8 *)(*(u8 **)(arg1 + 0x00) + 0xA1));
}
