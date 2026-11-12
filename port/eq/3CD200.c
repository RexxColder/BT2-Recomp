#include "common.h"

extern u8 *D_00423118;
extern u8 D_003B0B00[];
extern u8 D_00424CD0[];
extern u8 D_00424CE0[];
extern u8 D_00424CF0[];
extern u8 D_00424D00[];
extern u8 D_00424D10[];
extern u8 D_00424D20[];
extern u8 D_00424D30[];
extern u8 D_00424D48[];
extern u8 D_00424D58[];
extern u8 D_00424D68[];
extern s32 func_0026EB60();
extern s32 func_0026EB78();
extern s32 func_0028C4B8();
extern s32 func_00297FE0();
extern s32 func_002493C0();
extern s32 func_00243A80();
extern s32 func_003CCE98();

s32 func_003CD200(s32 *arg0) {
    u8 *g;
    u8 *P = D_003B0B00;
    s32 flags;
    s32 n;
    s32 v;
    s32 a1;

    g = D_00423118;
    if (func_0026EB60(g + 0x88) == 0) {
        return 0;
    }
    flags = *(s32 *)(g + 0x134);
    if (flags & 8) {
        if ((*(s32 *)(P + 0x144) & 0x80) && *(s32 *)(P + 0x284) == 1 && func_0028C4B8(1) == 0) {
            g = D_00423118;
            *(s32 *)(g + 0x140) -= 1;
            g = D_00423118;
            if (*(s32 *)(g + 0x140) <= 0) {
                *(s32 *)(g + 0x140) = 8;
            }
            a1 = 0;
            goto call;
        }
        if ((*(s32 *)(P + 0x144) & 0x20) && *(s32 *)(P + 0x284) == 1 && func_0028C4B8(1) == 0) {
            g = D_00423118;
            *(s32 *)(g + 0x140) += 1;
            g = D_00423118;
            if (*(s32 *)(g + 0x140) >= 9) {
                *(s32 *)(g + 0x140) = 1;
            }
            a1 = 0;
            goto call;
        }
        if (*(s32 *)(P + 0x134) & 0x4000) {
            g = D_00423118;
            *(s32 *)(g + 0x148) = 1;
            a1 = 1;
            goto call;
        }
        if (!(*(s32 *)(P + 0x134) & 0x1000)) {
            return 0;
        }
        g = D_00423118;
        v = *(s32 *)(g + 0x134);
        if (v & 0x8000) {
            *(s32 *)(g + 0x134) = v & 0xFFFF7FFF;
            return 0;
        }
        func_0026EB78(g + 0x88, D_00424CD0);
        g = D_00423118;
        v = *(s32 *)(g + 0x134) ^ 8;
        goto store718;
    }
    if (flags & 0x100) {
        if (!(*(s32 *)(P + 0x134) & 0xD000)) {
            return 0;
        }
        *(s32 *)(g + 0x134) = flags ^ 0x100;
        g = D_00423118;
        *(s32 *)(g + 0x134) = *(s32 *)(g + 0x134) & -0x201;
        g = D_00423118;
        func_0026EB78(g + 0x88, D_00424CE0);
        a1 = 2;
        goto call;
    }
    if (flags & 4) {
        v = *(s32 *)(P + 0x144);
        if (v & 0x10) {
            *(s32 *)(g + 0x13C) -= 1;
            g = D_00423118;
            if (*(s32 *)(g + 0x13C) < 0) {
                *(s32 *)(g + 0x13C) = *(s32 *)(g + 0x150) - 1;
            }
            a1 = 0;
            goto call;
        }
        if (v & 0x40) {
            *(s32 *)(g + 0x13C) += 1;
            g = D_00423118;
            if (*(s32 *)(g + 0x13C) >= *(s32 *)(g + 0x150)) {
                *(s32 *)(g + 0x13C) = 0;
            }
            a1 = 0;
            goto call;
        }
        v = *(s32 *)(P + 0x134);
        if (v & 0x8000) {
            *(s32 *)(g + 0x134) = flags | 0x300;
            g = D_00423118;
            func_0026EB78(g + 0x88, D_00424CF0);
            g = D_00423118;
            *(s32 *)(g + 0x144) = 0xE;
            g = D_00423118;
            func_002493C0(*(s32 *)(g + 8), 0x342E, 0x3847, 0, *(s32 *)(g + 0x144));
            a1 = 1;
            goto call;
        }
        if (v & 0x4000) {
            func_0026EB78(g + 0x88, D_00424D00);
            g = D_00423118;
            v = *(s32 *)(g + 0x134) | 8;
            *(s32 *)(g + 0x134) = v;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            g = D_00423118;
            *(s32 *)(g + 0x144) = 5;
            g = D_00423118;
            return func_002493C0(*(s32 *)(g + 8), 0x342E, 0x3847, 0, *(s32 *)(g + 0x144));
        }
        if (!(v & 0x1000)) {
            return 0;
        }
        n = *(s32 *)(g + 0x138);
        if (n == 1) {
            func_0026EB78(g + 0x88, D_00424D20);
        } else if (n >= 2) {
            if (n == 2) {
                func_0026EB78(g + 0x88, D_00424D30);
            }
        } else if (n == 0) {
            func_0026EB78(g + 0x88, D_00424D10);
        }
        g = D_00423118;
        v = *(s32 *)(g + 0x134) ^ 4;
        goto store718;
    }
    v = *(s32 *)(P + 0x144);
    if (v & 0x10) {
        *(s32 *)(g + 0x138) -= 1;
        g = D_00423118;
        if (*(s32 *)(g + 0x138) < 0) {
            *(s32 *)(g + 0x138) = *(s32 *)(g + 0x14C) - 1;
        }
        func_003CCE98();
        a1 = 0;
        goto call;
    }
    if (v & 0x40) {
        *(s32 *)(g + 0x138) += 1;
        g = D_00423118;
        if (*(s32 *)(g + 0x138) >= *(s32 *)(g + 0x14C)) {
            *(s32 *)(g + 0x138) = 0;
        }
        func_003CCE98();
        a1 = 0;
        goto call;
    }
    v = *(s32 *)(P + 0x134);
    if (v & 0x4000) {
        n = *(s32 *)(g + 0x138);
        if (n == 1) {
            func_0026EB78(g + 0x88, D_00424D58);
        } else if (n >= 2) {
            if (n == 2) {
                func_0026EB78(g + 0x88, D_00424D68);
            }
        } else if (n == 0) {
            func_0026EB78(g + 0x88, D_00424D48);
        }
        g = D_00423118;
        v = *(s32 *)(g + 0x134) | 4;
        a1 = 1;
        goto store718b;
    }
    if (v & 0x1000) {
        func_00243A80(0, 0, 0);
        *arg0 = 0;
        return func_00297FE0(0, 2, 0x40, 0x40, 1);
    }
    return 0;
store718:
    a1 = 2;
store718b:
    *(s32 *)(g + 0x134) = v;
    return func_00297FE0(0, a1, 0x40, 0x40, 1);
call:
    return func_00297FE0(0, a1, 0x40, 0x40, 1);
}
