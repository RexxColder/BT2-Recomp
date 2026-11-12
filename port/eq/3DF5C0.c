#include "common.h"

extern u8 *D_00427330 __attribute__((section(".data")));
extern u8 D_004275A0 __attribute__((section(".data")));
extern u8 D_004275A8 __attribute__((section(".data")));
extern u8 D_004275B8 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));

s32 func_26EB60(u8 *arg0);
void func_26EB78(u8 *arg0, u8 *arg1);
void func_26EA88(u8 *arg0);
void func_26EAE0(u8 *arg0, s32 arg1);
void EftShotFx_Update_2494A0(void);
s32 func_1018B8(u8 *arg0, u8 *arg1);
void func_003DF478(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
void func_297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* 0x003DF5C0: per-frame update of object G = D_00427330 (gated by func_26EB60(G + 0x14) != 0). Flags G->0xDC: bit 4 selects
 * path A (func_1018B8 check, then func_26EB78 with D_004275A0 and a fixed sequence). Otherwise path B reads the
 * D_003B0B00 words at 0x144 (0xC00 selects the G->0xE4 frame counter steps), 0x12C (0x50 selects the float window test on
 * G->0xF8 with G->0x100 and G->0xFC), and 0x134 (0x8000 and 0x1000 trigger the remaining actions). Ends in func_297FE0. */
void func_003DF5C0(s32 *arg0) {
    u8 *g;
    s32 fl;
    s32 f;
    s32 a2;
    s32 v;
    s32 f8;
    s32 flags2;
    f32 f1;
    f32 f2;
    f32 f3;

    g = D_00427330;
    if (func_26EB60(g + 0x14) == 0) {
        return;
    }

    fl = *(s32 *)(g + 0xDC);
    if (fl & 4) {
        if ((*(s32 *)(D_003B0B00 + 0x134) & 0xD000) == 0) {
            if (func_1018B8(g, g) != 5) {
                return;
            }
        }
        func_26EB78(g + 0x3C, &D_004275A0);
        EftShotFx_Update_2494A0();
        func_297FE0(0, 2, 0x40, 0x40, 1);
        *(s32 *)(g + 0xDC) &= ~4;
        return;
    }

    f = *(s32 *)(D_003B0B00 + 0x144);
    if (f & 0xC00) {
        if (f & 0x400) {
            *(s32 *)(g + 0xE8) = *(s32 *)(g + 0xE4);
            v = *(s32 *)(g + 0xE4) - 1;
            *(s32 *)(g + 0xE4) = v;
            if (v < 0) {
                *(s32 *)(g + 0xE4) = 6;
            }
            func_26EB78(g + 0x14, &D_004275A8);
            *(s32 *)(g + 0xDC) &= ~8;
            func_297FE0(2, 0, 0x40, 0x40, 1);
            return;
        }
        if (!(f & 0x800)) {
            func_297FE0(2, 0, 0x40, 0x40, 1);
            return;
        }
        *(s32 *)(g + 0xE8) = *(s32 *)(g + 0xE4);
        v = *(s32 *)(g + 0xE4) + 1;
        *(s32 *)(g + 0xE4) = v;
        if (v >= 7) {
            *(s32 *)(g + 0xE4) = 0;
        }
        func_26EB78(g + 0x14, &D_004275B8);
        *(s32 *)(g + 0xDC) &= ~8;
        func_297FE0(2, 0, 0x40, 0x40, 1);
        return;
    }

    a2 = *(s32 *)(D_003B0B00 + 0x12C);
    if (a2 & 0x50) {
        if (*(s32 *)(g + 0x104) < 0xB) {
            return;
        }
        f8 = *(s32 *)(g + 0xF8);
        f3 = (f32)*(s32 *)(g + 0x100);
        f2 = (f32)*(s32 *)(g + 0xFC);
        f1 = (f32)f8;
        if (!(((f1 - 0.5f) * f3) <= f2)) {
            return;
        }
        if (!(f2 <= ((f1 + 0.5f) * f3))) {
            return;
        }
        if (a2 & 0x10) {
            *(s32 *)(g + 0xF8) = f8 - 1;
            if (*(s32 *)(g + 0xF8) >= 0) {
                func_297FE0(0, 0, 0x40, 0x40, 1);
                return;
            }
            *(s32 *)(g + 0xF8) = 0;
            return;
        }
        if (a2 & 0x40) {
            *(s32 *)(g + 0xF8) = f8 + 1;
            v = *(s32 *)(g + 0x104) - 0xA;
            if (v >= *(s32 *)(g + 0xF8)) {
                func_297FE0(0, 0, 0x40, 0x40, 1);
                return;
            }
            *(s32 *)(g + 0xF8) = v;
        }
        return;
    }

    flags2 = *(s32 *)(D_003B0B00 + 0x134);
    if (flags2 & 0x8000) {
        *(s32 *)(g + 0xE0) = *(s32 *)(g + 0xE4) + 5;
        func_003DF478(D_003B0B00, g, a2, fl);
        func_26EA88(g + 0x3C);
        func_26EAE0(g + 0x3C, 0x3C);
        *(s32 *)(g + 0xDC) |= 4;
        func_297FE0(2, 1, 0x40, 0x40, 1);
        return;
    }
    if (flags2 & 0x1000) {
        *(s32 *)(g + 0xDC) = fl | 2;
        *arg0 = 0;
        func_297FE0(0, 2, 0x40, 0x40, 1);
    }
}
