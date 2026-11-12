#include "common.h"

void memset(void *arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_001DD1E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_003878D4;
extern u8 D_0036F1E0[] __attribute__((section(".data")));

void func_001DD8B0(u8 *arg0, u8 *arg1) {
    s64 sp[2];
    u8 *s0;
    s32 v1;
    s32 a2;
    s32 a3;
    f32 f1;

    s0 = *(u8 **)(arg0 + 0x38);
    memset(s0, 0, 0xD0);
    v1 = *(s32 *)(s0 + 0x40);
    *(s64 *)(s0 + 0x00) = *(s64 *)(arg1 + 0x00);
    a2 = v1 | 1;
    a3 = v1 | 9;
    *(s64 *)(s0 + 0x08) = *(s64 *)(arg1 + 0x08);
    *(s64 *)(s0 + 0x10) = *(s64 *)(arg1 + 0x10);
    *(s64 *)(s0 + 0x18) = *(s64 *)(arg1 + 0x18);
    *(s64 *)(s0 + 0x20) = *(s64 *)(arg1 + 0x20);
    *(s64 *)(s0 + 0x28) = *(s64 *)(arg1 + 0x28);
    *(s64 *)(s0 + 0x30) = *(s64 *)(arg1 + 0x30);
    *(s32 *)(s0 + 0x40) = a2;
    *(s64 *)(s0 + 0x38) = *(s64 *)(arg1 + 0x38);
    f1 = *(f32 *)(arg1 + 0x08);
    if (f1 <= 0.0f) {
        *(s32 *)(s0 + 0x40) = a3;
    } else {
        *(f32 *)(s0 + 0x58) = f1 * 30.0f;
    }
    *(s32 *)(s0 + 0x64) = 0;
    *(f32 *)(s0 + 0x60) = *(f32 *)(arg1 + 0x0C);
    *(f32 *)(s0 + 0x5C) = *(f32 *)(arg1 + 0x0C);
    *(s32 *)(s0 + 0x74) = 0;
    *(f32 *)(s0 + 0x68) = *(f32 *)(arg1 + 0x10);
    *(s32 *)(s0 + 0x78) = 0;
    *(s32 *)(s0 + 0x7C) = 0;

    sp[0] = *(s64 *)D_0036F1E0;
    sp[1] = *(s64 *)(D_0036F1E0 + 8);
    func_00129C28((s32)(s0 + 0x80), (s32)sp, a2, a3);

    *(s32 *)(s0 + 0x70) = 0;
    Vec4_Set((s32)(s0 + 0x90), 0.0f, 1.0f, 0.0f, 1.0f);
    *(s32 *)(s0 + 0x48) = 0;
    *(f32 *)(s0 + 0x50) = 1.0f;
    *(f32 *)(s0 + 0x4C) = 1.0f;
    func_001DD1E8((s32)s0, D_003878D4 + 8, 0, *(s32 *)(arg1 + 4));
}
