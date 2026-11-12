#include "common.h"

#define U16(p) (*(u16 *)(p))

s32 rand(void);

/* 0x003D6560 (struct s0 = arg0, slot i = arg1; s3 = i*16, i8 = i*8): if the flag word at s0+0xC+s3+0x3530 has bit 1,
 * return. idx2 = U16(s0+0xE+s3+0x3530); A = U16(s0+idx2*32+0x333C): return if A & 1. idx3 = U16(s0+0xE+s3+0x3532);
 * B = U16(s0+idx3*32+0x333C): return if B & 1. If A & 2 then a1 = 0, else if B & 2 then a1 = 1, else a1 = rand() & 1 and
 * U16(s0+X*32+0x333C) |= 2 with X = U16(s0+0xE+2*(i8 + (a1^1))+0x3530). Then P = s0+0xE+2*(i8+a1)+0x3530:
 * U16(s0+U16(P)*32+0x3344) = U16(s0+s3+0x3544); if flag & 4: U16(s0+0xE+U16(s0+s3+0x3542)*16+0x3530) = U16(P);
 * else if flag & 8: the same at +0x3532. Finally flag |= 1. */
void func_003D6560(u8 *arg0, s32 arg1) {
    u8 *s0 = arg0;
    s32 s3 = arg1 << 4;
    s32 i8 = arg1 << 3;
    u8 *s2 = s0 + 0xE;
    u8 *s4 = s0 + 0xC;
    u8 *p;
    u8 *f;
    u16 idx2;
    u16 idx3;
    u16 a;
    u16 b;
    u16 x;
    u16 q;
    u16 flagv;
    s32 a1;

    if (U16(s4 + s3 + 0x3530) & 1) {
        return;
    }
    idx2 = U16(s2 + s3 + 0x3530);
    a = U16(s0 + (idx2 << 5) + 0x333C);
    if (a & 1) {
        return;
    }
    idx3 = U16(s2 + s3 + 0x3532);
    b = U16(s0 + (idx3 << 5) + 0x333C);
    if (b & 1) {
        return;
    }

    if (a & 2) {
        a1 = 0;
    } else if (b & 2) {
        a1 = 1;
    } else {
        a1 = rand() & 1;
        x = U16(s2 + 2 * (i8 + (a1 ^ 1)) + 0x3530);
        U16(s0 + (x << 5) + 0x333C) = U16(s0 + (x << 5) + 0x333C) | 0x2;
    }

    p = s2 + 2 * (i8 + a1) + 0x3530;
    q = U16(s0 + s3 + 0x3544);
    f = s4 + s3 + 0x3530;
    U16(s0 + (U16(p) << 5) + 0x3344) = q;
    flagv = U16(f);
    if (flagv & 0x4) {
        U16(s2 + (U16(s0 + s3 + 0x3542) << 4) + 0x3530) = U16(p);
    } else if (flagv & 0x8) {
        U16(s2 + (U16(s0 + s3 + 0x3542) << 4) + 0x3532) = U16(p);
    }
    U16(f) = U16(f) | 0x1;
}
