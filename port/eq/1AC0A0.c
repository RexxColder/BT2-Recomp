#include "common.h"

s32 func_00129DE0(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
void func_00209D78(s32 arg0, s32 arg1);
extern f32 D_00384EF4;

void func_001AC0A0(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 flags;
    u8 *s0;
    u8 *s1;

    s0 = (u8 *)arg0;
    s1 = (u8 *)arg1;
    func_00129DE0(D_00384EF4, arg1 + 0x50, arg0 + 0x10, arg1 + 0x60);
    flags = *(s32 *)(s0 + 4);
    if (flags & 0x40) {
        func_00209D78((s16)(*(u16 *)(s1 + 0x12) ^ 1), (s32)sp);
        func_00129C28(arg1 + 0x70, (s32)sp);
        *(u16 *)(s1 + 0x12) = (u16)(*(u16 *)(s1 + 0x12) ^ 1);
        *(s32 *)(s1 + 0xC0) = *(s32 *)(s1 + 0xC0) | 4;
    } else if (flags & 0x80) {
        func_00209D78((s16)(*(u16 *)(s1 + 0x12) ^ 1), (s32)sp);
        func_00129C28(arg1 + 0x70, (s32)sp);
        *(s32 *)(s1 + 0xC4) = *(s16 *)(s1 + 0x1C);
        *(u16 *)(s1 + 0x12) = (u16)(*(u16 *)(s1 + 0x12) ^ 1);
    }
}
