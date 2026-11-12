#include "common.h"

s32 Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
s32 func_0014EAE8(s32 arg0, s32 arg1);
void func_001F3738(u8 *arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_001A0E08(u8 *arg0, u8 *arg1) {
    u8 *s0;

    s0 = *(u8 **)(arg0 + 0x38);
    memset(s0, 0, 0xA70);
    *(s64 *)(s0 + 0x00) = *(s64 *)(arg1 + 0x00);
    *(s64 *)(s0 + 0x08) = *(s64 *)(arg1 + 0x08);
    *(s64 *)(s0 + 0x10) = *(s64 *)(arg1 + 0x10);
    *(s64 *)(s0 + 0x18) = *(s64 *)(arg1 + 0x18);
    *(s64 *)(s0 + 0x20) = *(s64 *)(arg1 + 0x20);
    *(s64 *)(s0 + 0x28) = *(s64 *)(arg1 + 0x28);
    *(s64 *)(s0 + 0x30) = *(s64 *)(arg1 + 0x30);
    *(f32 *)(s0 + 0x4C) = *(f32 *)(s0 + 0x44) * 8.0f;
    *(s64 *)(s0 + 0x38) = *(s64 *)(arg1 + 0x38);
    *(f32 *)(s0 + 0x48) = 1.0f;
    Vec4_Set((s32)(s0 + 0x60), 0.0f, 0.0f, 0.0f, 1.0f);
    func_0014EAE8(*(s32 *)(s0 + 0x34), (s32)(s0 + 0x70));
    func_001F3738(arg0, (*(s32 *)s0 != 0) ? 0x1000 : 0x800);
}
