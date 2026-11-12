#include "common.h"

s32 func_002A0010(s32 arg0);
void func_0025B9E0(s32 arg0, s32 arg1);
s32 func_003126C8(s32 arg0, s32 arg1);
f32 Gsc_GetFloat(void);
s32 Gsc_FindOptionN(s32 arg0, s32 arg1);

extern f32 D_003872C8;
extern u8 D_003B1D80[] __attribute__((section(".data")));

s32 func_002A5B68(s32 arg0) {
    f32 sp[16];
    f32 fA;
    f32 fB;
    f32 fC;
    f32 fD;
    f32 fE;
    f32 fF;
    f32 fG;
    f32 scale;
    s32 i;
    s32 s0;
    s32 s1;

    if (arg0 == 1) {
        return 0;
    }
    if (arg0 == 2) {
        return D_003B1D80[0] == 0;
    }
    if (arg0 != 0) {
        return 0;
    }

    D_003B1D80[0] = 0;
    *(s32 *)(D_003B1D80 + 4) = 0;
    *(s32 *)(D_003B1D80 + 8) = 0;
    for (i = 0; i < 9; i++) {
        *(s32 *)(D_003B1D80 + 0x190 - 0x30 * i) = 0;
    }

    if (func_002A0010(0x6C) != 0) {
        func_0025B9E0((s32)&sp[8], (s32)&sp[12]);
        func_003126C8((s32)(D_003B1D80 + 0x20), (s32)&sp[8]);
        func_003126C8((s32)(D_003B1D80 + 0x30), (s32)&sp[12]);
        scale = D_003872C8;
        *(s32 *)(D_003B1D80 + 0x14) = 0;
        *(s32 *)(D_003B1D80 + 0x10) = 1;

        s1 = 0;
        s0 = (s32)D_003B1D80;
        while (Gsc_FindOptionN(0x6C, s1) != 0 && s1 < 8) {
            s1 += 1;
            fA = Gsc_GetFloat();
            fB = Gsc_GetFloat();
            fC = Gsc_GetFloat();
            fD = Gsc_GetFloat();
            fE = Gsc_GetFloat();
            fF = Gsc_GetFloat();
            fG = Gsc_GetFloat();
            sp[0] = fB;
            sp[1] = fC;
            sp[2] = fD;
            sp[4] = fE / 180.0f * scale;
            sp[5] = fF / 180.0f * scale;
            sp[6] = fG / 180.0f * scale;
            func_003126C8(s0 + 0x50, (s32)&sp[0]);
            func_003126C8(s0 + 0x60, (s32)&sp[4]);
            *(s32 *)(s0 + 0x40) = 1;
            *(f32 *)(s0 + 0x44) = fA;
            s0 += 0x30;
        }
        D_003B1D80[0] = 1;
    }

    if (func_002A0010(0x77) == 0) {
        return 1;
    }
    return 0;
}
