#include "common.h"

extern void Vec4_Scale(u8 *dst, u8 *src, f32 s);
extern void Vec4_Add(u8 *dst, u8 *a, u8 *b);

s32 EftSpdLine_StepStreak(u8 *p) {
    u8 sp[16];

    if (*(u32 *)(p + 0x44) & 1) {
        Vec4_Scale(sp, p + 0x20, *(f32 *)(p + 0x34));
        Vec4_Add(p, p, sp);
        Vec4_Add(p + 0x10, p + 0x10, sp);
        *(f32 *)(p + 0x3C) = *(f32 *)(p + 0x3C) - *(f32 *)(p + 0x40);
    }
    if (*(f32 *)(p + 0x3C) <= 0.0f) {
        *(f32 *)(p + 0x3C) = 0.0f;
        return 1;
    }
    return 0;
}
