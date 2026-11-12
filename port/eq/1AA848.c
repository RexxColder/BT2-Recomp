#include "common.h"

extern f32 D_00384EE0;
void Vec3_Lerp(f32 *arg0, f32 *arg1, f32 *arg2, f32 arg3);
void func_00209D78(s32 arg0, u8 *arg1);
void func_00129C28(u8 *arg0, u8 *arg1);

/* 0x001AA848: (src, dst) lerps dst+0x90 / dst+0xA0, then flips the facing flag (dst+0x52) per src+4 bits 0x40 / 0x80. */
void func_001AA848(u8 *src, u8 *dst) {
    u8 sp[16];
    u32 fl;

    Vec3_Lerp((f32 *)(dst + 0x90), (f32 *)(src + 0x10), (f32 *)(dst + 0xA0), D_00384EE0);
    fl = *(u32 *)(src + 4);
    if ((fl & 0x40) != 0) {
        func_00209D78((s16)(*(u16 *)(dst + 0x52) ^ 1), sp);
        func_00129C28(dst + 0xB0, sp);
        *(u16 *)(dst + 0x52) ^= 1;
        *(u32 *)dst = (*(u32 *)dst & ~4u) | 8;
    } else if ((fl & 0x80) != 0) {
        func_00209D78((s16)(*(u16 *)(dst + 0x52) ^ 1), sp);
        func_00129C28(dst + 0xB0, sp);
        *(s32 *)(dst + 0xC) = *(s16 *)(dst + 0x5C);
        *(u16 *)(dst + 0x52) ^= 1;
    }
}
