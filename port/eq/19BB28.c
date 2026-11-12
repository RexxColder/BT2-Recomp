#include "common.h"

s32 EftPtcl3_Create(s32 arg0);
void EftPtcl3_SetTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
s32 func_00129C28(s32 arg0, s32 arg1);

void func_0019BB28(s32 arg0) {
    u8 sp[0x110];
    u8 *self;
    u8 *P;
    u8 *T;
    u8 *s0;
    u8 *s1;
    u8 *s4;
    u8 *s6;
    s32 fp;
    s32 spA8;
    s32 spAC;
    s32 spB0;
    s32 t0;
    s32 b;
    s32 s3;
    s32 v;
    s32 i;

    self = (u8 *)arg0;
    P = (u8 *)*(s32 *)(self + 0x38);
    T = (u8 *)*(s32 *)P;
    spA8 = 0;
    spAC = (s32)P;
    spB0 = 0;
    fp = 0;
    do {
        b = spB0;
        *(f32 *)(sp + 0x50) = *(f32 *)(T + b);
        *(f32 *)(sp + 0x54) = *(f32 *)(T + 0xC + b);
        memset(sp + 0x60, 0, 0x10);
        memset(sp + 0x70, 0, 0x10);
        t0 = fp + 0x20;
        *(s32 *)(sp + 0x80) = *(u8 *)(T + t0);
        *(s32 *)(sp + 0x84) = *(s32 *)(P + 4);
        *(s32 *)(sp + 0x88) = *(s32 *)(P + 8) + fp * 0x164;
        *(s32 *)(sp + 0x8C) = *(s32 *)(P + 0xC) + spA8;
        *(s32 *)(sp + 0x90) = *(s32 *)(P + 0x80);
        /* copy sp[0x50..0x9F] to sp[0..0x4F] as raw 8-byte words */
        for (i = 0; i < 10; i++) {
            *(s64 *)(sp + i * 8) = *(s64 *)(sp + 0x50 + i * 8);
        }

        s6 = T + t0;
        s0 = P;
        s3 = 1;
        s1 = (u8 *)spAC + 0x10;
        s4 = T + 4 + t0;
        do {
            func_00129C28((s32)(sp + 0x10), (s32)(s0 + 0x40));
            func_00129C28((s32)(sp + 0x20), (s32)(s0 + 0x60));
            s0 += 0x10;
            if (*s4 == 0) {
                func_00129BD0((s32)(sp + 0x20), (s32)(sp + 0x20), -1.0f);
            }
            s3 -= 1;
            v = EftPtcl3_Create((s32)sp);
            *(s32 *)s1 = v;
            s1 += 0xC;
            EftPtcl3_SetTexture(v, *(s32 *)(P + 4), *s6, *s6 + *(s32 *)(P + 0x84));
        } while (s3 >= 0);

        spA8 += 0x50;
        spAC += 4;
        spB0 += 4;
        fp += 1;
    } while (fp < 3);
}
