#include "common.h"

u8 *func_001F3758(u8 *arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
void func_00208F18(s32 arg0, u8 *arg1, s32 arg2, u8 *arg3);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
s32 func_00182B38(u8 *arg0);
extern f32 D_0038470C;

void func_0015C7A8(u8 *arg0) {
    u8 sp[0xA0];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *t;
    f32 f;
    s32 idx;
    s32 res;
    s32 i;

    t = func_001F3758(arg0);
    s1 = *(u8 **)(arg0 + 0x38);
    s2 = *(u8 **)(s1 + 0xA0);
    s0 = *(u8 **)(t + 0x38);
    memset(sp + 0x50, 0, 0x10);
    *(f32 *)(sp + 0x5C) = 1.0f;
    memset(sp + 0x60, 0, 0x10);
    *(f32 *)(sp + 0x6C) = 1.0f;
    *(f32 *)(sp + 0x70) = 10.0f;
    *(f32 *)(sp + 0x78) = D_0038470C;
    *(f32 *)(sp + 0x74) = *(f32 *)(*(u8 **)(s2 + 0x20) + 0x18);
    *(f32 *)(sp + 0x7C) = 6.0f;
    *(s32 *)(sp + 0x80) = *(s32 *)s2;
    *(s32 *)(sp + 0x84) = 0xF;
    *(s32 *)(sp + 0x88) = 0x12C;
    *(s32 *)(sp + 0x8C) = *(s32 *)(s1 + 0xAA0);
    *(s32 *)(sp + 0x90) = (s32)s0;
    *(s32 *)(sp + 0x94) = (s32)s2;
    *(s32 *)(sp + 0x98) = *(s32 *)(s0 + 0x1E80);
    *(u8 *)(sp + 0x9C) = 0;
    /* raw copy of the 0x50-byte parameter block from sp+0x50 to sp+0x00 (no overlap) */
    for (i = 0; i < 0x50; i++) {
        sp[i] = sp[0x50 + i];
    }

    func_00208F18(*(s32 *)s2, sp + 0x60, 0x31, sp + 0x90);
    func_00208DE8(*(s32 *)s2, sp + 0x50, 0x31);

    f = -*(f32 *)(sp + 0x80);
    *(f32 *)(sp + 0x0) = *(f32 *)(sp + 0x50);
    *(f32 *)(sp + 0x4) = *(f32 *)(sp + 0x54);
    *(f32 *)(sp + 0x8) = *(f32 *)(sp + 0x58);
    *(f32 *)(sp + 0x80) = f;
    *(f32 *)(sp + 0x88) = -*(f32 *)(sp + 0x88);
    Vec3_Normalize(sp + 0x10, sp + 0x80);

    if (*(s32 *)(s1 + 0xAA0) == 3) {
        *(u8 *)(sp + 0x4C) = 1;
    }
    res = func_00182B38(sp);
    idx = *(s32 *)(s1 + 0xAA0);
    *(s32 *)(s1 + (idx << 2) + 0xAA4) = res;
    *(s32 *)(s1 + 0xAA0) = idx + 1;
}
