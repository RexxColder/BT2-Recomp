#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387930;
extern f32 D_00385A70;

s32 func_00211310(u8 *a0, s32 a1, s32 a2);
s32 func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
s32 func_00203C58(u8 *a0, s64 a1);
s32 func_0023FC18(u8 *a0);
void BtlMember_SubMaxPower(u8 *a0, s32 a1);
s32 BtlMember_IsMaxPowerEmpty(u8 *a0);
void func_001F9168(u8 *a0);
void func_001F9198(u8 *a0);
s32 BtlCharApi_IsInTechnique(s32 a0);
void func_00203888(u8 *a0, s32 a1, s32 a2);
s32 BtlMember_IsKiEmpty(u8 *a0);
s32 BtlMember_IsHealthEmpty_2127F8(u8 *a0);
s32 func_0023FAB8(u8 *a0);
void func_00203810(u8 *a0, s32 a1);
s32 BtlPad_Test4C(u8 *a0, s32 a1);
s32 func_0023F9A0(u8 *a0);
s32 BtlMember_HasKi(u8 *a0, s32 a1);
s32 func_0023F990(u8 *a0);
s32 func_0023FA70(u8 *a0);
s32 func_0023FB90(u8 *a0);
void func_00203968(u8 *a0, s32 a1);
s32 func_0023F430(u8 *a0);
u8 *BtlMember_GetActiveGauge(u8 *a0);
void func_001F92A0(u8 *a0);
void func_0023B0C8(u8 *a0);
s32 func_00218128(u8 *a0, s32 a1);
f32 func_0023FCD8(u8 *a0);
void BtlMember_AddHealth(u8 *a0, s32 a1);
u8 *func_00202DA0(u8 *a0, s32 a1);

#define I(o) (*(s32 *)(s1 + (o)))

s32 func_002142A8(u8 *s1) {
    s32 v0, v1, s0, c;
    u8 *a0, *a1, *g;
    s64 q;
    f32 f0, f1;

    v0 = (s32)(*(s64 *)(D_003876A0 + 0x4D8) & 0x3800);
    if (v0) return v0;
    v0 = func_00211310(s1, 0, 0x100000);
    if (v0) return v0;
    if (!func_00211310(s1, 13, 1)) {
        s0 = func_0023FC18(s1);
        if (func_00211310(s1, 13, 4)) {
            s0 = s0 * 3;
        } else if (func_00211310(s1, 13, 2)) {
            s0 = s0 << 1;
        } else if (func_00203C58(s1, 0x2000)) {
            s0 = (s0 << 1) / 3;
        }
        BtlMember_SubMaxPower(s1, s0);
        if (BtlMember_IsMaxPowerEmpty(s1)) {
            func_002113C0(s1, 0, 0x800, 0);
            func_001F9168(s1);
        }
    }
    if (func_00211310(s1, 8, 1)) {
        if (!func_00211310(s1, 8, 2)) {
            if (!BtlCharApi_IsInTechnique(I(0x1534))) {
                func_00203888(s1, I(0xAD4), 0);
                if (BtlMember_IsKiEmpty(s1)) {
                    func_002113C0(s1, 8, 1, 0);
                    a1 = *(u8 **)(s1 + 0x1530);
                    *(s32 *)(a1 + 0xAF0) = *(s32 *)(a1 + 0xAF0) & 0xFF00FFFF;
                    a1 = *(u8 **)(s1 + 0x1530);
                    *(s32 *)(a1 + 0xAF0) = *(s32 *)(a1 + 0xAF0) | 0x10000;
                    func_001F9198(s1);
                }
            }
        }
    }
    if (func_00211310(s1, 7, 0x20000)) {
        if (!BtlCharApi_IsInTechnique(I(0x1534))) {
            func_002113C0(s1, 7, 0x20000, 0);
        }
    }
    if (!BtlMember_IsHealthEmpty_2127F8(s1)) {
        if (!func_00211310(s1, 13, 8)) {
            if (func_00211310(s1, 0, 0x4000)) {
                func_00203810(s1, func_0023FAB8(s1));
                func_002113C0(s1, 15, 1, 1);
                if (BtlPad_Test4C(s1, 0x18)) func_00203810(s1, 1000);
                if (BtlMember_HasKi(s1, func_0023F9A0(s1))) {
                    func_002113C0(s1, 0, 0x4000, 0);
                }
            } else if (!func_00211310(s1, 8, 1)) {
                v0 = func_0023F990(s1);
                if (!BtlMember_HasKi(s1, v0) && !(I(0xAF0) > 0)) {
                    s0 = func_0023FA70(s1);
                    if (func_00211310(s1, 0, 0x1000)) {
                        s0 = (s0 + (s32)((u32)s0 >> 31)) >> 1;
                    }
                    func_00203810(s1, s0);
                }
            }
            if (*(s32 *)(D_003876A0 + 0xB8) == 5) {
                if (!func_00211310(s1, 8, 1)) func_00203810(s1, 1000);
            }
            if (func_00203C58(s1, 0x80000000000LL)) {
                v0 = I(0x1518) + 1;
                I(0x1518) = v0;
                if (!(v0 < 30)) {
                    I(0x1518) = 0;
                    func_00203810(s1, 1000);
                }
            } else if (func_00203C58(s1, 0x20)) {
                v0 = I(0x1518) + 1;
                I(0x1518) = v0;
                if (!(v0 < 30)) {
                    I(0x1518) = 0;
                    func_00203810(s1, 500);
                }
            }
        }
        if (!func_00211310(s1, 13, 0x10)) {
            func_00203968(s1, func_0023FB90(s1));
            if (*(s32 *)(D_003876A0 + 0xB8) == 5) func_00203968(s1, 0xD05);
        }
        if (*(s32 *)(D_00387930 + 8) & 0x10) {
            if (!(func_0023F430(s1) & 0x80)) {
                g = BtlMember_GetActiveGauge(s1);
                v0 = func_0023F990(s1);
                s0 = *(s32 *)(g + 0xC) - v0;
                if (!(s0 < 0x3E9)) s0 = 1000;
                if (s0 > 0) {
                    g = BtlMember_GetActiveGauge(s1);
                    if (*(s32 *)(g + 0x1C) == 0) {
                        v0 = I(0x151C) + 1;
                        I(0x151C) = v0;
                        if (!(v0 < 30)) {
                            I(0x151C) = 0;
                            func_00203888(s1, s0, 0);
                        }
                    }
                }
            }
        }
    }
    v0 = func_00211310(s1, 9, 0x200000);
    if (v0) return v0;
    func_001F92A0(s1);
    func_0023B0C8(s1);
    I(0x9B4) = I(0x9B4) - 200;
    v0 = func_00218128(s1, 0);
    v1 = 0xC350;
    if (v0 == 0) v1 = 0;
    a0 = 0;
    v0 = I(0xAE4);
    if (v0 > 0) {
        if (v1 < v0) v1 = v0;
    }
    if (I(0x9B4) < v1) I(0x9B4) = v1;
    if (!(*(s32 *)(D_003876A0 + 0xD8) & 1)) {
        f0 = func_0023FCD8(s1);
        f0 = f0 * 30.0f;
        f1 = D_00385A70 / f0;
        v1 = I(0x1188);
        v0 = (s32)f1;
        v1 = v1 + v0;
        I(0x1188) = v1;
        v0 = *(s32 *)(D_003876A0 + 0xB8);
        if ((u32)(v0 - 4) < 2) {
            I(0x1188) = v1 + 0x457;
        }
        if (100000 < I(0x1188)) I(0x1188) = 100000;
    }
    v0 = *(s32 *)(D_003876A0 + 0xB8);
    if ((u32)(v0 - 4) < 2) {
        if (!func_00211310(s1, 6, 4)) BtlMember_AddHealth(s1, 200);
    }
    if (!BtlMember_IsHealthEmpty_2127F8(s1)) {
        if (func_00203C58(s1, 0x10)) {
            v0 = I(0x1514) + 1;
            I(0x1514) = v0;
            if (!(v0 < 30)) {
                I(0x1514) = 0;
                BtlMember_AddHealth(s1, 100);
            }
        } else if (func_00203C58(s1, 8)) {
            v0 = I(0x1514) + 1;
            I(0x1514) = v0;
            if (!(v0 < 90)) {
                I(0x1514) = 0;
                BtlMember_AddHealth(s1, 100);
            }
        }
    }
    v0 = I(0x1520) + 1;
    I(0x1520) = v0;
    if (!(v0 < 90)) I(0x1520) = 0;
    v0 = I(0x1524) + 1;
    I(0x1524) = v0;
    if (!(v0 < 30)) I(0x1524) = 0;
    v1 = I(0x1184);
    if (v1 <= 0) return v0;
    s0 = 0;
    do {
        if (s0 != I(0x1180)) {
            a1 = func_00202DA0(s1, s0);
            a0 = a1 + 0x38;
            if (*(s32 *)a0 > 0) {
                s32 a2 = *(s32 *)a0;
                q = *(s64 *)(a1 + 0x28);
                if (q & 0x200000000LL) {
                    if (I(0x1520) == 0) {
                        v1 = *(s32 *)(a0 + 4);
                        v0 = a2 + 100;
                        *(s32 *)a0 = v0;
                        if (v1 < v0) *(s32 *)a0 = v1;
                    }
                    q = *(s64 *)(a1 + 0x28);
                }
                if (q & 0x400000000LL) {
                    if (I(0x1524) == 0) {
                        v0 = *(s32 *)(a0 + 0x24) + 1000;
                        *(s32 *)(a0 + 0x24) = v0;
                        if (100000 < v0) *(s32 *)(a0 + 0x24) = 100000;
                    }
                }
            }
        }
        s0 = s0 + 1;
    } while (s0 < I(0x1184));
    return 0;
}
