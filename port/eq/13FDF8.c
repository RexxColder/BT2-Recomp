#include "common.h"

extern u8 *func_0013FD98(void);
extern void func_003126C8(u8 *dst, u8 *src);
extern f32 EftMath_WrapAngle(f32 farg0);
extern f32 func_0012A3F8(f32 farg0);
extern f32 Mathf_Cos(f32 farg0);
extern void sceVu0Normalize(void *arg0, void *arg1);
extern u8 *gEftDust;
extern f32 D_003844E4;
extern f32 D_003844E8;
extern f32 D_003844EC;
extern f32 D_003844F0;

s32 func_0013FDF8(u8 **head, u8 **tail, u8 *pos, u32 b0, u32 b1, u32 b2, u32 b3, u32 b4,
                  f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                  f32 st0, f32 st1, f32 st2, f32 st3, f32 st4, f32 st5, f32 st6, f32 st7, f32 st8, f32 st9) {
    u8 *p;
    u8 *prev;
    f32 ang1, ang2, t;
    s32 cnt;

    p = func_0013FD98();
    if (p == 0) {
        return 0;
    }
    if (*head == 0) {
        *head = p;
        *(u8 **)(p + 0x98) = 0;
        *(u8 **)(p + 0x9C) = 0;
    } else {
        prev = *tail;
        *(u8 **)(p + 0x9C) = 0;
        *(u8 **)(p + 0x98) = prev;
    }
    if (*tail != 0) {
        *(u8 **)(*tail + 0x9C) = p;
    }
    *tail = p;
    *(u32 *)(p + 0x00) = 0;
    *(u32 *)(p + 0x04) = 0;
    *(u32 *)(p + 0x08) = 0;
    *(f32 *)(p + 0x0C) = 1.0f;
    func_003126C8(p + 0x10, pos);
    *(f32 *)(p + 0x40) = f12;
    *(f32 *)(p + 0x68) = f15;
    *(f32 *)(p + 0x64) = f14;
    *(f32 *)(p + 0x14) = *(f32 *)(p + 0x14) + f13;
    if (f16 == 0.0f) {
        *(f32 *)(p + 0x6C) = 0.0f;
    } else {
        *(f32 *)(p + 0x6C) = 1.0f / f16;
    }
    *(f32 *)(p + 0x4C) = st2;
    *(f32 *)(p + 0x44) = f19;
    *(f32 *)(p + 0x48) = (st0 - f19) / (st8 * 30.0f);
    *(f32 *)(p + 0x50) = st3;
    if (st4 == 0.0f) {
        *(f32 *)(p + 0x54) = 0.0f;
    } else {
        *(f32 *)(p + 0x54) = 1.0f / st4;
    }
    *(f32 *)(p + 0x78) = st6;
    *(f32 *)(p + 0x74) = st5 * D_003844E4;
    *(f32 *)(p + 0x88) = st9 * 30.0f;
    *(f32 *)(p + 0x84) = D_003844EC;
    *(u8 *)(p + 0x93) = 1;
    *(f32 *)(p + 0x7C) = st7;
    *(f32 *)(p + 0x70) = f18;
    *(u8 *)(p + 0x8C) = b0;
    *(u8 *)(p + 0x8D) = b1;
    *(u8 *)(p + 0x8E) = b2;
    *(u8 *)(p + 0x91) = b3;
    *(u8 *)(p + 0x92) = b4;
    *(u32 *)(p + 0x80) = 0;
    *(u8 *)(p + 0x8F) = 0;
    *(u8 *)(p + 0x90) = 0;
    *(u8 *)(p + 0x94) = 0;

    ang1 = EftMath_WrapAngle(f14 / 180.0f * D_003844E8);
    t = func_0012A3F8(ang1);
    ang2 = f17 / 180.0f * D_003844E8;
    *(u32 *)(p + 0x24) = 0;
    *(f32 *)(p + 0x20) = t;
    *(f32 *)(p + 0x28) = Mathf_Cos(ang1);
    *(f32 *)(p + 0x2C) = 1.0f;
    sceVu0Normalize(p + 0x20, p + 0x20);
    *(f32 *)(p + 0x30) = st1 * Mathf_Cos(ang2);
    t = func_0012A3F8(ang2);
    *(f32 *)(p + 0x34) = -st1 * t;
    t = Mathf_Cos(ang2);
    *(u32 *)(p + 0x58) = 0;
    *(f32 *)(p + 0x38) = st1 * t;
    t = st8 * D_003844F0;
    *(f32 *)(p + 0x5C) = 96.0f;
    if (t != *(f32 *)(p + 0x58)) {
        *(f32 *)(p + 0x5C) = 96.0f / (t * 30.0f);
    }
    *(f32 *)(p + 0x60) = 96.0f;
    *(u8 *)(p + 0x90) = *(u8 *)(p + 0x90) | 1;
    cnt = *(s32 *)(gEftDust + 0x38) + 1;
    *(s32 *)(gEftDust + 0x38) = cnt;
    return cnt;
}
