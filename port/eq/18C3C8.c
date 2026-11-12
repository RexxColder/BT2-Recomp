#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);

/* 0x0018C3C8: (re)initialises the record at arg0+0x38 from the source record arg1: clears 0x160
 * bytes, copies the header words and the 0x10..0x28 blocks, scales the float at +0x34 by 30.0f,
 * builds the list of the set bits of the source word at +4 +0xB0 (indices stored at +0x44..),
 * and resets the flags at +0x4E, +0x56 (bit 1), +0x158 and +0x15C. */
void func_0018C3C8(u8 *arg0, u8 *arg1) {
    u8 *s1 = *(u8 **)(arg0 + 0x38);
    u8 *p4;
    s32 i;
    u8 count;
    u16 flags;

    memset(s1, 0, 0x160);
    *(s32 *)(s1 + 0x00) = *(s32 *)(arg1 + 0x08);
    *(s32 *)(s1 + 0x04) = *(s32 *)(arg1 + 0x00);
    *(s32 *)(s1 + 0x08) = *(s32 *)(arg1 + 0x04);
    *(s32 *)(s1 + 0x50) = *(s32 *)(arg1 + 0x38);
    *(s64 *)(s1 + 0x10) = *(s64 *)(arg1 + 0x10);
    *(s64 *)(s1 + 0x18) = *(s64 *)(arg1 + 0x18);
    *(s64 *)(s1 + 0x20) = *(s64 *)(arg1 + 0x20);
    *(s64 *)(s1 + 0x28) = *(s64 *)(arg1 + 0x28);
    *(f32 *)(s1 + 0x30) = *(f32 *)(arg1 + 0x30);
    *(f32 *)(s1 + 0x34) = *(f32 *)(arg1 + 0x34) * 30.0f;

    p4 = *(u8 **)(s1 + 0x04);
    for (i = 0; i < 8; i++) {
        if (*(s32 *)(p4 + 0xB0) & (1 << i)) {
            *(u8 *)(s1 + 0x44 + *(u8 *)(s1 + 0x4C)) = (u8)i;
            *(u8 *)(s1 + 0x4C) = (u8)(*(u8 *)(s1 + 0x4C) + 1);
        }
    }

    count = *(u8 *)(s1 + 0x4C);
    if (count == 0) {
        *(u8 *)(s1 + 0x44) = 0;
        *(u8 *)(s1 + 0x4C) = (u8)(*(u8 *)(s1 + 0x4C) + 1);
    }
    flags = *(u16 *)(s1 + 0x56);
    *(u8 *)(s1 + 0x4E) = 0;
    *(s32 *)(s1 + 0x158) = 0;
    *(u16 *)(s1 + 0x56) = (u16)(flags | 2);
    *(s32 *)(s1 + 0x15C) = 0;
}
