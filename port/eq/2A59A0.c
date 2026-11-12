#include "common.h"

f32 Gsc_GetFloat(void);
void func_0025B9C8(f32 *arg0, f32 *arg1);
void func_0025B9E0(f32 *arg0, f32 *arg1);
s32 func_002A0010(s32 arg0);
void func_003126C8(void *arg0, f32 *arg1);
extern f32 D_003872C4;
extern u8 D_003B1D80[] __attribute__((section(".data")));

s32 func_002A59A0(s32 arg0) {
    f32 vA[4];
    f32 vB[4];
    f32 vC[4];
    f32 vD[4];
    f32 r;
    f32 k;
    f32 temp_f20_2;
    u8 *dp;
    u8 *p;
    s32 v1;
    s32 s4;

    s4 = 0;
    dp = D_003B1D80;

    if (arg0 == 1) {
        return 0;
    }
    if (arg0 == 2) {
        return dp[0] == 0;
    }
    if (arg0 != 0) {
        return 0;
    }

    r = Gsc_GetFloat();
    vA[0] = r;
    r = Gsc_GetFloat();
    vA[1] = r;
    r = Gsc_GetFloat();
    vA[2] = r;
    k = D_003872C4;
    r = Gsc_GetFloat();
    vB[0] = (r / 180.0f) * k;
    r = Gsc_GetFloat();
    vB[1] = (r / 180.0f) * k;
    r = Gsc_GetFloat();
    vB[2] = (r / 180.0f) * k;

    dp[0] = 0;
    *(s32 *)(dp + 4) = 0;
    *(s32 *)(dp + 8) = 0;

    if (func_002A0010(0x6C) != 0) {
        v1 = 8;
        p = dp + 0x190;
        do {
            v1 -= 1;
            *(s32 *)p = 0;
            p -= 0x30;
        } while (v1 >= 0);

        temp_f20_2 = Gsc_GetFloat();
        func_0025B9E0(vC, vD);
        func_003126C8(dp + 0x20, vC);
        func_003126C8(dp + 0x30, vD);
        *(s32 *)(dp + 0x10) = 1;
        *(s32 *)(dp + 0x14) = 0;
        func_003126C8(dp + 0x50, vA);
        func_003126C8(dp + 0x60, vB);
        *(s32 *)(dp + 0x40) = 1;
        dp[0] = 1;
        *(f32 *)(dp + 0x44) = temp_f20_2;
    } else {
        func_0025B9C8(vA, vB);
        s4 = 1;
    }

    if (func_002A0010(0x77) == 0) {
        s4 = 1;
    }
    return s4;
}
