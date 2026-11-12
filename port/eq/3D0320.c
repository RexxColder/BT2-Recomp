#include "common.h"

extern u8 *D_00423120;
extern u8 *D_003876A4;
extern char D_00424EF0[];
void func_0026E9E8();
s32 func_0026EB70();
void func_00297FE0();
s32 func_003D83D0();
void func_003D7E48();
void func_0026EAE0();
void func_0026EA88();
void func_0026EB78();
void func_0026EB30();
s32 func_003D77A8();

#define O D_00423120
#define P D_003876A4
#define OW(off) (*(s32 *)(O + (off)))
#define PW(off) (*(s32 *)(P + (off)))
#define OF(off) (*(f32 *)(O + (off)))
#define H(p) (*(u16 *)(p))

s32 func_003D0320(void) {
    s32 s0, s1, t, c, a1;
    u32 e;
    u16 fl;
    u8 *a3;

    s0 = 7;
    s1 = 0;
    do {
        s0--;
        func_0026E9E8(O + s1 + 0x30);
        s1 += 0x28;
    } while (s0 >= 0);
    if (OW(0x2BC) & 0x80) {
        return OW(0x2BC) & 0x80;
    }
    if (func_0026EB70(O + 0x58) & 8) {
        func_00297FE0(2, 6, 0x40, 0x40, 1);
    }
    if (OW(0x2BC) & 0x4000) {
        if (OW(0x2BC) & 0x10) {
            return 0x10;
        }
        OW(0x2BC) = OW(0x2BC) | 0x80;
        if (PW(0x94) != 1) {
            return (s32)P;
        }
        if (func_003D83D0(O) && PW(0x90)) {
            OW(0x2BC) = OW(0x2BC) | 0x1000;
        } else {
            OW(0x2BC) = OW(0x2BC) | 0x2000;
        }
        return OW(0x2BC);
    }
    if (!(OW(0x2BC) & 0x24)) {
        if (func_0026EB70(O + 0x30) & 1) {
            if (func_0026EB70(O + 0x30) & 0x200) {
                if (PW(0x18) & 0x10) {
                    func_003D7E48(O);
                } else {
                    OW(0x2BC) = OW(0x2BC) | 4;
                }
            }
        }
    }
    if (OW(0x2BC) & 0x40) {
        if (func_0026EB70(O + 0x58) & 1) {
            if (func_0026EB70(O + 0x58) & 0x200) {
                OW(0x2BC) = OW(0x2BC) ^ 0x40;
                OW(0x3310) = 1;
                func_0026EAE0(O + 0x120, 0x3C);
                if (PW(0x8C)) {
                    func_0026EAE0(O + 0xA8, 0x3C);
                    func_0026EA88(O + 0xA8);
                }
                func_0026EB78(O + 0xF8, D_00424EF0);
                OW(0x2BC) = OW(0x2BC) | 0x400;
                OW(0x332C) = (0x200 - (s32)OF(0x3330)) / 30;
            }
        }
    }
    if (OW(0x2BC) & 0x400) {
        OF(0x3330) = OF(0x3330) + (f32)OW(0x332C);
        if ((s32)OF(0x3330) >= 0x200) {
            OF(0x3330) = 512.0f;
            OW(0x2BC) = OW(0x2BC) ^ 0x400;
        }
    }
    if (!(OW(0x2BC) & 0x20)) {
        return 0;
    }
    if (!(func_0026EB70(O + 0x80) & 0x200)) {
        return 0;
    }
    OW(0x2BC) = OW(0x2BC) ^ 0x20;
    OW(0x2BC) = OW(0x2BC) | 4;
    t = OW(0x3324);
    c = OW(0x2C8);
    e = H(O + (t * 8 + (c ^ 1)) * 2 + 0x353E);
    H(O + e * 32 + 0x3330 + 0xC) = H(O + e * 32 + 0x3330 + 0xC) | 2;
    t = OW(0x3324);
    e = H(O + t * 16 + 0x353E);
    H(O + e * 32 + 0x3330 + 0xC) = H(O + e * 32 + 0x3330 + 0xC) & 0xFFF7;
    t = OW(0x3324);
    e = H(O + t * 16 + 0x3540);
    H(O + e * 32 + 0x3330 + 0xC) = H(O + e * 32 + 0x3330 + 0xC) & 0xFFF7;
    func_0026EB30(O + 0x80, 0);
    t = OW(0x3324);
    c = OW(0x2C8);
    a1 = H(O + t * 16 + 0x3544);
    e = H(O + (t * 8 + c) * 2 + 0x353E);
    H(O + e * 32 + 0x3344) = a1;
    t = OW(0x3324);
    a3 = O + t * 16 + 0x3530;
    fl = H(a3 + 0xC);
    if (fl & 0x10) {
        c = OW(0x2C8);
        e = H(O + (t * 8 + c) * 2 + 0x353E);
        a1 = 1;
        if (H(O + e * 32 + 0x333C) & 1) {
            if (PW(0x94) == 1) {
                OW(0x3310) = 0xFB;
                OW(0x2BC) = OW(0x2BC) | 0x800;
            } else {
                OW(0x3310) = 0x12D;
            }
            OW(0x2BC) = OW(0x2BC) | 0x80;
            return OW(0x2BC);
        }
    } else if (fl & 4) {
        a1 = OW(0x2C8);
        H(O + H(a3 + 0x12) * 16 + 0x353E) = H(O + (t * 8 + a1) * 2 + 0x353E);
    } else if (fl & 8) {
        a1 = OW(0x2C8);
        H(O + H(a3 + 0x12) * 16 + 0x3540) = H(O + (t * 8 + a1) * 2 + 0x353E);
    }
    return func_003D77A8(O, a1);
}
