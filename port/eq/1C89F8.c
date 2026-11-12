#include "common.h"

f32 cosf(f32 arg0);
f32 sinf(f32 arg0);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_003851A0;
extern u8 *D_003878B4;

void func_001C89F8(u8 *arg0, u8 *arg1) {
    u8 *s1;
    u8 *s0;
    u8 *s3;
    f32 f20;
    f32 f0;

    s1 = D_003878B4;
    s0 = *(u8 **)(arg0 + 0x38);
    s3 = *(u8 **)s1;
    f20 = D_003851A0;
    memset(s0, 0, 0xA0);
    *(s32 *)s0 = *(s32 *)s1;
    func_00208DE8(*(s32 *)(arg1 + 0x30), (s32)(s0 + 0x60), 0x37);
    func_00208DE8(*(s32 *)(arg1 + 0x30), (s32)(s0 + 0x70), 0x37);
    *(s32 *)(s0 + 0x80) = 0;
    *(f32 *)(s0 + 0x84) = cosf(*(f32 *)(s3 + 0x2C) * f20);
    f0 = sinf(*(f32 *)(s3 + 0x2C) * f20);
    *(s32 *)(s0 + 0x8C) = 0;
    *(f32 *)(s0 + 0x88) = f0;
    *(s32 *)(s0 + 4) = (s32)(s1 + 8);
    *(s32 *)(s0 + 8) = *(s32 *)(s1 + 0x114);
    *(s32 *)(s0 + 0xC) = *(s32 *)(s1 + 0x118);
    *(s32 *)(s0 + 0x94) = *(s32 *)(s0 + 0x94) | 1;
    *(s32 *)(s0 + 0x90) = *(s32 *)(arg1 + 0x30);
}
