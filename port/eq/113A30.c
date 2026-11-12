#include "common.h"

void func_00113A30(s32 arg0, s32 arg1) {
    u8 *base;
    f32 fx;
    f32 fy;
    f32 scaled;
    s32 rx;
    s32 ry;
    u16 a3;
    u16 a2;
    u16 t0;
    u16 t1;
    s16 d1;
    s16 d2;
    s16 x;
    s16 y;
    s32 p;
    s32 q;

    base = (u8 *)arg0;
    fx = *(f32 *)arg1;
    fy = *(f32 *)(arg1 + 4);
    a3 = *(u16 *)(base + 0xC);
    a2 = *(u16 *)(base + 0x10);
    t0 = *(u16 *)(base + 0x12);
    t1 = *(u16 *)(base + 0xE);
    d1 = (s16)(a2 - a3);
    d2 = (s16)(t0 - t1);

    /* x = (s16) cvt.w.s(-fx * d1): truncates toward zero */
    scaled = (-fx) * (f32)d1;
    rx = (s32)scaled;
    x = (s16)rx;

    /* y = (s16) cvt.w.s(fy * d2): truncates toward zero */
    scaled = fy * (f32)d2;
    ry = (s32)scaled;
    y = (s16)ry;

    p = x + d1;
    q = y + d2;
    if (x >= 0) {
        *(u16 *)(base + 0xC) = (u16)(x + a3);
        *(u16 *)(base + 0x10) = (u16)(x + a2);
    } else {
        *(u16 *)(base + 0xC) = (u16)(a3 + p);
        *(u16 *)(base + 0x10) = (u16)(a2 + p);
    }
    if (y < 0) {
        *(u16 *)(base + 0x12) = (u16)(t0 + q);
        *(u16 *)(base + 0xE) = (u16)(t1 + q);
    } else {
        *(u16 *)(base + 0x12) = (u16)(y + t0);
        *(u16 *)(base + 0xE) = (u16)(y + t1);
    }
}
