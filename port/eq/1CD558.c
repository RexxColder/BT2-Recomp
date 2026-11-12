#include "common.h"

#define AT(T, p, off) (*(T *)((u8 *)(p) + (off)))

s32 EftPtcl3_Create(u8 *arg0);
void EftPtcl3_SetTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void EftPtcl3_SetFlag80(s32 arg0, s32 arg1);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 farg0);
void func_00129C38(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_001CD558(u8 *arg0) {
    u8 fr[0xb0];   /* tamano de locales del original (antes 0xa0) */
    u8 *s2;
    u8 *s6;
    u8 *spB0;
    u8 *fp;
    u8 *s5;
    u8 *spA4;
    u8 *s4;
    u8 *s0;
    u8 *s1;
    s32 base;
    s32 s7;
    s32 spAC;
    s32 s3;
    s32 i;
    s32 h;
    s32 t;
    u8 tA2;

    s2 = (u8 *)AT(s32, arg0, 0x38);
    base = AT(s32, s2, 0);
    s6 = s2;
    spAC = 0;
    spA4 = (u8 *)base + 2;
    fp = (u8 *)base;
    s5 = (u8 *)base + 8;
    spB0 = s2;
    s7 = 0;

    do {
        AT(f32, fr, 0x50) = *(f32 *)fp;
        AT(f32, fr, 0x54) = *(f32 *)s5;
        memset(fr + 0x60, 0, 0x10);
        memset(fr + 0x70, 0, 0x10);
        s4 = spA4 + (s7 + 0x10);
        AT(s32, fr, 0x80) = *s4;
        AT(s32, fr, 0x84) = AT(s32, s2, 4);
        AT(s32, fr, 0x88) = AT(s32, s2, 8) + s7 * 0x164;
        AT(s32, fr, 0x8C) = AT(s32, s2, 0xC) + spAC;
        AT(s32, fr, 0x90) = AT(s32, s2, 0x110);
        for (i = 0; i < 0x50; i++) {
            fr[i] = fr[0x50 + i];
        }
        AT(f32, fr, 4) = (*(f32 *)s5) * AT(f32, s2, 0x120);
        func_00129C38(fr + 0x20, s2 + 0x100, fr + 0x40, fr + 0x20);
        if (base == -0x10) {
            func_00129BD0(fr + 0x20, fr + 0x20, -1.0f);
        }

        s3 = 1;
        s0 = s6 + 0x10;
        s1 = spB0 + 0xC0;
        do {
            s3 -= 1;
            ((void (*)(u8 *, u8 *))func_00129C38)(fr + 0x10, s1);
            s1 += 0x10;
            h = EftPtcl3_Create(fr);
            AT(s32, s0, 0) = h;
            tA2 = *s4;
            EftPtcl3_SetTexture(h, AT(s32, s2, 4), tA2, tA2 + AT(s32, s2, 0x114));
            EftPtcl3_SetFlag80(AT(s32, s0, 0), 0);
            t = AT(s32, s0, 0);
            s0 += 4;
            EftPtcl3_SetType(t, 2);
        } while (s3 >= 0);

        s7 += 1;
        s5 += 4;
        spAC += 0x50;
        spB0 += 0x20;
        s6 += 8;
        fp += 4;
    } while (s7 < 2);
}
