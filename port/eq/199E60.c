#include "common.h"

void func_00129BB8(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_00384D4C;
extern f32 D_00384D50;
extern f32 D_00384D54;
extern f32 D_00384D58;
extern f32 D_00384D5C;
extern f32 D_00384D60;
extern s32 gEftGlowCfg;

void EftGlow_SetType(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a2;
    s32 a1;
    s32 v1;
    s32 v3;
    s32 v0;
    s32 s0;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 cfg;
    s32 a1x;
    s32 a2x;
    s32 a3x;

    var_a2 = arg2;
    *(s32 *)(arg0 + 0x08) = arg3;
    v3 = *(s32 *)(arg0 + 0x00) & ~0x20;
    *(s32 *)(arg0 + 0x00) = v3;
    if ((arg3 & 0x5E) != 0) {
        var_a2 = 8;
        *(s32 *)(arg0 + 0x00) = v3 | 0x20;
        *(s32 *)(arg0 + 0x2C) = 1;
        *(s32 *)(arg0 + 0x28) = 8;
        if ((arg3 & 0x46) != 0) {
            *(s32 *)(arg0 + 0x2C) = 2;
        } else {
            v0 = 0xA;
            if ((arg3 & 0x08) == 0) {
                v0 = 0xC;
                if ((arg3 & 0x10) != 0) {
                    *(s32 *)(arg0 + 0x28) = v0;
                    *(s32 *)(arg0 + 0x2C) = 2;
                }
            } else {
                *(s32 *)(arg0 + 0x28) = v0;
                *(s32 *)(arg0 + 0x2C) = 2;
            }
        }
        a1 = *(s32 *)(arg0 + 0x00);
    } else if (var_a2 < 8) {
        a1 = *(s32 *)(arg0 + 0x00);
    } else {
        *(s32 *)(arg0 + 0x00) = v3 | 0x20;
        *(s32 *)(arg0 + 0x28) = 8;
        *(s32 *)(arg0 + 0x2C) = 2;
        a1 = *(s32 *)(arg0 + 0x00);
    }

    *(s32 *)(arg0 + 0x20) = var_a2;
    *(s32 *)(arg0 + 0x24) = 1;
    *(s32 *)(arg0 + 0x1C) = var_a2;
    if ((a1 & 0x20) != 0) {
        *(s32 *)(arg0 + 0x24) = 2;
    }

    v1 = *(s32 *)(arg0 + 0x08);
    if ((v1 & 0x02) != 0) {
        s2 = 0;
    } else if ((v1 & 0x04) != 0) {
        s2 = 1;
    } else if ((v1 & 0x08) != 0) {
        s2 = 2;
    } else if ((v1 & 0x10) != 0) {
        s2 = 3;
    } else {
        s2 = ((v1 & 0x40) != 0) ? 4 : 0;
    }

    if ((a1 & 0x20) != 0) {
        s0 = s2 * 0x50;
        cfg = gEftGlowCfg;
        func_00129BB8(D_00384D4C, arg0 + 0x190, cfg + s0 + 0x8F0, var_a2, arg3);
        cfg = gEftGlowCfg;
        ((void (*)(f32, s32, s32))func_00129BB8)(D_00384D50, arg0 + 0x1A0, cfg + s0 + 0x8F0);
    } else {
        v1 = *(s32 *)(arg0 + 0x1C);
        cfg = gEftGlowCfg;
        s0 = (((v1 * 5) << 4) + cfg + 0x620);
        func_00129BB8(D_00384D54, arg0 + 0x190, s0, var_a2, arg3);
        v1 = *(s32 *)(arg0 + 0x1C);
        cfg = gEftGlowCfg;
        s0 = (((v1 * 5) << 4) + cfg + 0x620);
        ((void (*)(f32, s32, s32))func_00129BB8)(D_00384D58, arg0 + 0x1A0, s0);
    }

    *(s32 *)(arg0 + 0x1AC) = 0;
    s3 = s2 * 0x50;
    s0 = arg0 + 0x260;
    s2 = s0;
    s4 = 0;
    do {
        if ((*(s32 *)(arg0 + 0x00) & 0x20) != 0) {
            cfg = gEftGlowCfg;
            ((void (*)(f32, s32, s32))func_00129BB8)(D_00384D5C, s2, cfg + s3 + 0x900);
            s4 += 1;
        } else {
            v3 = *(s32 *)(arg0 + 0x1C);
            v0 = 0;
            a3x = gEftGlowCfg;
            a2x = (v3 < 8) ? 1 : 0;
            if (a2x == 0) {
                v0 = s4;
            }
            a1x = ((v3 * 5 + v0) << 4) + a3x + 0x630;
            func_00129BB8(D_00384D60, s2, a1x, a2x, a3x);
            s4 += 1;
        }
        s0 += 0x10;
        s3 += 0x10;
        s2 += 0x10;
    } while (s4 < 4);
}
