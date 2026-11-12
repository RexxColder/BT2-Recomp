#include "common.h"

extern void *gBtlCamView;

void *memset(void *arg0, s32 arg1, s32 arg2);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00135F18(s32 arg0, s32 arg1, s32 arg2);

s32 func_00136758(s32 arg0, u8 *arg1, u8 *arg2) {
    u8 sp[0xb0];   /* tamano de locales del original (antes 0xa4) */
    f32 *s0 = (f32 *)arg1;
    f32 *s1 = (f32 *)arg2;
    s32 s2 = 0;
    s32 s3 = 0;
    u8 *entry;
    f32 x;
    f32 y;
    f32 z;
    f32 t;
    s32 a0;
    u8 *v3;
    s32 count;

    memset(sp + 0x90, 0, 0x14);
    Vec4_Set(sp + 0x00, s0[0], s0[1], s0[2], 1.0f);
    Vec4_Set(sp + 0x10, s1[0], s0[1], s0[2], 1.0f);
    Vec4_Set(sp + 0x20, s0[0], s1[1], s0[2], 1.0f);
    Vec4_Set(sp + 0x30, s1[0], s1[1], s0[2], 1.0f);
    Vec4_Set(sp + 0x40, s0[0], s0[1], s1[2], 1.0f);
    Vec4_Set(sp + 0x50, s1[0], s0[1], s1[2], 1.0f);
    Vec4_Set(sp + 0x60, s0[0], s1[1], s1[2], 1.0f);
    Vec4_Set(sp + 0x70, s1[0], s1[1], s1[2], 1.0f);

    entry = sp;
    for (;;) {
        func_00135F18((s32)(sp + 0x80), arg0, (s32)entry);
        x = *(f32 *)(sp + 0x80) - 1792.0f;
        y = *(f32 *)(sp + 0x84) - 1824.0f;
        z = *(f32 *)(sp + 0x88);
        *(f32 *)(sp + 0x80) = x;
        *(f32 *)(sp + 0x84) = y;
        if (z < 0.0f) {
            *(s32 *)(sp + 0xA0) = *(s32 *)(sp + 0xA0) + 1;
            a0 = 0x10;
        } else {
            v3 = (u8 *)gBtlCamView;
            a0 = 0x20;
            t = (f32)*(s32 *)(v3 + 0x200);
            if (x < t) {
                *(s32 *)(sp + 0x90) = *(s32 *)(sp + 0x90) + 1;
                a0 = 0x21;
            }
            t = (f32)(*(s32 *)(v3 + 0x204) + 1);
            if (t < x) {
                a0 |= 2;
                *(s32 *)(sp + 0x94) = *(s32 *)(sp + 0x94) + 1;
            }
            t = (f32)*(s32 *)(v3 + 0x208);
            if (y < t) {
                a0 |= 4;
                *(s32 *)(sp + 0x98) = *(s32 *)(sp + 0x98) + 1;
            }
            t = (f32)(*(s32 *)(v3 + 0x20C) + 1);
            if (t < y) {
                a0 |= 8;
                *(s32 *)(sp + 0x9C) = *(s32 *)(sp + 0x9C) + 1;
            }
        }
        s2 |= a0;
        if ((a0 & ~0x20) == 0) {
            return 1;
        }
        s3 += 1;
        entry += 0x10;
        if (!(s3 < 8)) {
            break;
        }
    }

    count = (s2 & 1) + ((s2 >> 1) & 1) + ((s2 >> 2) & 1) + ((s2 >> 3) & 1);
    if (count < 2) {
        return ((s2 & 0x30) ^ 0x30) == 0;
    }
    return 1;
}
