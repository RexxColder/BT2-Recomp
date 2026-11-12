#include "common.h"

void func_001EC328(s32 arg0, s32 arg1);
s32 func_003126C8(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_00387858;

void func_001AEE98(u8 *arg0, u8 *arg1) {
    u8 *s0;

    s0 = *(u8 **)(arg0 + 0x38);
    memset(s0, 0, 0x1D0);
    *(s32 *)(s0 + 0x44) = *(s32 *)(arg1 + 0x20);
    func_003126C8((s32)s0, (s32)arg1);
    func_003126C8((s32)(s0 + 0x10), (s32)arg1);
    *(s32 *)(s0 + 0x30) = 0;
    *(s32 *)(s0 + 0x34) = 0;
    *(f32 *)(s0 + 0x3C) = 1.0f;
    *(f32 *)(s0 + 0x38) = 1.0f;
    *(s32 *)(s0 + 0x40) = *(s32 *)(arg1 + 0x24);
    *(s32 *)(s0 + 0x64) = *(s32 *)(arg1 + 0x28);
    *(s32 *)(s0 + 0x6C) = 0;
    *(u8 *)(s0 + 0x5A) = *(u8 *)(arg1 + 0x49);
    *(f32 *)(s0 + 0x70) = *(f32 *)(arg1 + 0x2C);
    *(u8 *)(s0 + 0x5C) = 1;
    *(f32 *)(s0 + 0x74) = *(f32 *)(arg1 + 0x30);
    *(s32 *)(s0 + 0x54) = 0;
    *(u8 *)(s0 + 0x5B) = 0;
    *(u8 *)(s0 + 0x5D) = 0;
    memset(s0 + 0x80, 0, 0xF0);
    func_001EC328((s32)(s0 + 0xC0), (s32)(D_00387858 + 0xF0));
    *(s32 *)D_00387858 += 1;
}
