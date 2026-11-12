#include "common.h"

extern s32 func_001F3758(s32 arg0);
extern void func_0014EAE8(s32 arg0, s32 arg1);

void func_0015B1A8(u8 *self, u8 *src) {
    u8 *other = (u8 *)func_001F3758((s32)self);
    u8 *state = *(u8 **)(self + 0x38);
    s32 otherField = *(s32 *)(other + 0x38);
    u8 *vec;

    __builtin_memset(state, 0, 0xAA0);
    *(u8 **)(state + 0xA0) = src;
    vec = *(u8 **)(src + 0x24);
    *(f32 *)(state + 0x18) = *(f32 *)(vec + 8);
    *(f32 *)(state + 0x1C) = *(f32 *)(vec + 4);
    func_0014EAE8(otherField, (s32)(state + 0xA4));
}
