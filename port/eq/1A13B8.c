#include "common.h"

void *memset(void *s, s32 c, u32 n);
void *memcpy(void *d, const void *s, u32 n);
f32 BtlCharApi_GetHeight(s32 a0);
void func_00208DE8(s32 a0, u8 *a1, s32 a2);
void func_00129C28(u8 *a0, u8 *a1);
void Vec4_Set(void *dst, f32 f12, f32 f13, f32 f14, f32 f15);
s32 EftPtcl3_Create(u8 *a0);
void EftPtcl3_SetType(s32 a0, s32 a1);
extern f32 D_00384E1C;
extern s32 D_00387814;

void func_001A13B8(u8 *arg0, u8 *arg1) {
    s32 fr[40];
    u8 *sp = (u8 *)fr;
    u8 *p;
    u8 *s4;
    u8 *s0;
    u8 *s1;
    s32 a0v;
    f32 f0v;
    s32 ptr;

    p = *(u8 **)(arg0 + 0x38);
    s4 = p + 0x10;
    memset(p, 0, 0x30);
    a0v = *(s32 *)arg1;
    *(s32 *)p = a0v;
    f0v = BtlCharApi_GetHeight(a0v);
    *(f32 *)(p + 0x20) = 15.0f;
    *(f32 *)(p + 0x24) = f0v / D_00384E1C;
    func_00208DE8(*(s32 *)p, s4, 3);
    s0 = (u8 *)(long)D_00387814;
    *(s32 *)(sp + 0x50) = 0;
    *(f32 *)(sp + 0x54) = *(f32 *)(p + 0x24);
    memset(sp + 0x60, 0, 0x10);
    memset(sp + 0x70, 0, 0x10);
    *(s32 *)(sp + 0x80) = 1;
    *(s32 *)(sp + 0x84) = (s32)(long)(s0 + 0x10);
    s1 = s0 + 8;
    *(s32 *)(sp + 0x88) = *(s32 *)(s1 + 0x118) + 0x164;
    *(s32 *)(sp + 0x8C) = *(s32 *)(s1 + 0x11C) + 0x50;
    *(s32 *)(sp + 0x90) = *(s32 *)p;
    memcpy(sp, sp + 0x50, 0x40);
    memcpy(sp + 0x40, sp + 0x90, 0x10);
    func_00129C28(sp + 0x10, s4);
    Vec4_Set(sp + 0x20, 0.0f, -1.0f, 0.0f, 1.0f);
    ptr = EftPtcl3_Create(sp);
    *(s32 *)(p + 0x2C) = ptr;
    EftPtcl3_SetType(ptr, 2);
}
