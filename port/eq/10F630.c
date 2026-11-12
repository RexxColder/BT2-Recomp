#include "common.h"

extern u8 D_0036C798[] __attribute__((section(".data")));
extern f32 D_00383E68;

s32 rand(void);
void func_0010CFC8(f32 *arg0, f32 arg1);
void func_0010CE18(void *arg0);

/* float to u8 as the game does it: values >= 2^31 go through the sign-bit path */
static u32 f2u(f32 v) {
    u32 r = (u32)(s32)v;
    if (v >= 2147483648.0f) {
        r = (u32)(s32)(v - 2147483648.0f) | 0x80000000;
    }
    return r;
}

/* 0x0010F630: fills 9 quads (0x60 bytes each) at a0 and a 10th at a0+0x360, picking a random
   entry from an 8-entry table (10 bytes each) that differs from the current one. */
void func_0010F630(u8 *a0, s16 *a1, f32 a2, f32 a3) {
    u8 sp[0xD0];
    f32 *vec = (f32 *)(sp + 0x50);
    u8 *q;
    s32 i;
    s32 r;
    s32 idx;
    s16 *e;
    f32 fx;
    f32 fy;
    f32 fo;

    __builtin_memcpy(sp, D_0036C798, 0x50);
    q = a0;
    for (i = 0; i < 9; i++) {
        for (;;) {
            r = rand();
            idx = r % 8;
            e = (s16 *)(sp + idx * 10);
            if (*(s16 *)(q + 0xC) != e[0]) {
                break;
            }
            if (*(s16 *)(q + 0x10) != e[2]) {
                break;
            }
            if (*(s16 *)(q + 0xE) != e[1]) {
                break;
            }
            if (*(s16 *)(q + 0x12) != e[3]) {
                break;
            }
        }
        __builtin_memcpy(q + 0xC, e, 8);
        *(s16 *)(q + 0x14) = e[4];
        __builtin_memset(vec, 0, 12);
        func_0010CFC8(vec, D_00383E68);
        func_0010CE18(vec);
        *(s32 *)q = 0x81;
        if (i < 6) {
            fo = (f32)((i % 6) << 5);
            fy = 0.0f;
        } else {
            fo = (f32)((i % 4) << 5);
            fy = 20.0f;
        }
        *(s16 *)(q + 4) = (s16)(s32)((f32)(a1[2] + 4) + vec[1] + fo);
        *(s16 *)(q + 8) = (s16)(s32)((f32)(a1[2] + 0x44) + vec[1] + fo);
        if (i < 6) {
            *(s16 *)(q + 6) = (s16)(s32)((f32)(a1[3] - 4) + vec[2]);
            fx = (f32)(a1[3] + 0x3C) + vec[2];
        } else {
            *(s16 *)(q + 6) = (s16)(s32)((f32)(a1[3] - 4) + vec[2] + fy);
            fx = (f32)(a1[3] + 0x3C) + vec[2] + fy;
        }
        *(s16 *)(q + 0xA) = (s16)(s32)fx;
        q[0x18] = 0x80;
        q[0x16] = 0x80;
        q[0x17] = 0x80;
        q[0x19] = (u8)f2u(a2 * 128.0f * a3);
        q += 0x60;
    }
    *(s32 *)(a0 + 0x360) = 0x85;
    *(u16 *)(a0 + 0x364) = *(u16 *)((u8 *)a1 + 4);
    *(u16 *)(a0 + 0x368) = *(u16 *)((u8 *)a1 + 8);
    *(u16 *)(a0 + 0x366) = *(u16 *)((u8 *)a1 + 6);
    *(u16 *)(a0 + 0x36A) = *(u16 *)((u8 *)a1 + 0xA);
    a0[0x378] = 0xFF;
    a0[0x376] = 0;
    a0[0x377] = 0;
    a0[0x379] = (u8)f2u(a2 * 44.0f * a3);
}
