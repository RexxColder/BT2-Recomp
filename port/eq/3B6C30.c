#include "common.h"

void *memset(void *s, s32 c, u32 n);

/* 0x003B6C30: fills the record at arg0 from the source record P = arg0->4: clears arg0's 2-byte flag, then four
 * blocks (+0x8 0x28 bytes, +0x30 0x34 bytes, +0x64 0x18 bytes, +0x7C 0x18 bytes) each zeroed by memset and set from
 * P's fields (ints converted to float, 1.0 and 255.0 constants), then arg0+0x94 (0x28 bytes) and its three floats. */
void func_003B6C30(u8 *arg0) {
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *s5;
    f32 f;

    s0 = arg0 + 0x8;
    s2 = arg0 + 0x30;
    s4 = arg0 + 0x64;
    s5 = arg0 + 0x7C;
    *(s16 *)arg0 = 0;
    s1 = *(u8 **)(arg0 + 0x4);
    s3 = arg0 + 0x94;

    memset(s0, 0, 0x28);
    *(f32 *)(s0 + 0x10) = (f32)*(s32 *)(s1 + 0x4);
    *(f32 *)(s0 + 0x14) = (f32)*(s32 *)(s1 + 0x8);
    *(s32 *)(s0 + 0x18) = *(s32 *)(s1 + 0x4);
    *(s32 *)(s0 + 0x1C) = *(s32 *)(s1 + 0x8);
    *(s32 *)(s0 + 0x20) = *(s32 *)(s1 + 0x4);
    *(s32 *)(s0 + 0x24) = *(s32 *)(s1 + 0x8);

    memset(s2, 0, 0x34);
    *(f32 *)(s2 + 0xC) = (f32)*(s32 *)(s1 + 0x4);
    *(f32 *)(s2 + 0x10) = (f32)*(s32 *)(s1 + 0x8);
    *(f32 *)(s2 + 0x14) = (f32)(*(s32 *)(s1 + 0xC) - *(s32 *)(s1 + 0x4));
    *(f32 *)(s2 + 0x30) = 1.0f;
    *(f32 *)(s2 + 0x1C) = 1.0f;
    *(f32 *)(s2 + 0x20) = 1.0f;
    *(f32 *)(s2 + 0x24) = 1.0f;
    *(f32 *)(s2 + 0x28) = 1.0f;
    *(f32 *)(s2 + 0x2C) = 1.0f;
    *(f32 *)(s2 + 0x18) = (f32)(*(s32 *)(s1 + 0x10) - *(s32 *)(s1 + 0x8));

    memset(s4, 0, 0x18);
    f = (f32)*(s32 *)(s1 + 0x34) / 255.0f;
    *(f32 *)(s4 + 0x14) = f;
    *(f32 *)(s4 + 0xC) = f;
    *(f32 *)(s4 + 0x10) = f;

    memset(s5, 0, 0x18);
    *(f32 *)(s5 + 0xC) = 1.0f;
    *(s32 *)(s5 + 0x10) = 0;
    *(f32 *)(s5 + 0x14) = (f32)*(s32 *)(s1 + 0x34);

    memset(s3, 0, 0x28);
    *(f32 *)(arg0 + 0x94) = (f32)*(s32 *)(s1 + 0x4);
    *(f32 *)(s3 + 0x10) = 1.0f;
    *(f32 *)(s3 + 0x14) = 1.0f;
    *(f32 *)(s3 + 0x4) = (f32)*(s32 *)(s1 + 0x8);
}
