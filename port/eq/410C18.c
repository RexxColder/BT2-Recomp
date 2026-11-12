#include "common.h"

extern u8 *D_0042BB78 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern s32 D_003876AC __attribute__((section(".data")));

s32 func_00100D58(s32 arg0, s32 arg1, s32 arg2);
s32 func_00243A80(s32 arg0, s32 arg1, s32 arg2);
void func_00243968(s32 arg0, s32 arg1, s32 arg2);
void func_0029BD28(void);
s32 func_00250978(s32 arg0);
void func_002539C8(s32 arg0);
void func_0028BB60(s32 arg0);
s32 func_0029BB88(u8 *arg0, s32 arg1);

#define G (D_0042BB78)
#define H (D_003876A4)
#define GW(o) (*(s32 *)(G + (o)))
#define HW(o) (*(s32 *)(H + (o)))

/* 4 * G[(flag ? 0x2D4 : 0x2D0) + 0xC], minus 4 when the up/down bit is set */
static s32 Idx(void) {
    s32 dec;
    s32 v;

    if (HW(0x48C) & 2) {
        dec = (GW(0x240) & 0x800) != 0;
    } else {
        dec = (GW(0x240) & 0x400) != 0;
    }
    v = *(s32 *)(G + ((HW(0x48C) & 2) ? 0x2D4 : 0x2D0) + 0xC) << 2;
    return dec ? v - 4 : v;
}

s32 func_00410C18(void) {
    u8 *t0;
    s32 x, a1, s3, run, st, g, off;

    if ((GW(0x240) & 0x10000) == 0) {
        GW(0x240) = GW(0x240) | 0x10000;
        func_00100D58(*(s32 *)(H + 4) + 0xE, 0, 1);
        return func_00243A80(0, 0, 0);
    }
    if (GW(0x240) & 0x20000) {
        return 0;
    }
    D_003876AC = func_00100D58(0, 0, 0);
    if (D_003876AC == 0) {
        return 0;
    }
    GW(0x240) = GW(0x240) | 0x20000;
    g = GW(0x240);
    if (g & 0x4000) {
        if (GW(0x37C8) == 2) {
            HW(0x48C) = HW(0x48C) | 0x20;
        }
    } else if (g & 0x8000) {
        if (GW(0x37C8) == 1) {
            HW(0x48C) = HW(0x48C) | 1;
        } else {
            HW(0x48C) = HW(0x48C) | 0x20;
        }
        HW(0x48C) = HW(0x48C) | 2;
    }
    x = Idx();
    off = (HW(0x48C) & 2) ? x + 0x254 : x + 0x240;
    t0 = (G + 4) + off;
    x = Idx();
    off = (HW(0x48C) & 2) ? x + 0x274 : x + 0x260;
    a1 = *(s32 *)t0;
    HW(0x494) = a1 + *(s32 *)(G + off + 0xC) * 7;
    s3 = HW(0x1C);
    HW(0x1C) = 0x37;
    func_0029BD28();
    run = 1;
    do {
        st = HW(0x1C);
        if (st == 0x37) {
            if (func_00250978(1)) {
                HW(0x1C) = 0x38;
            } else {
                run = 0;
            }
        } else if (st == 0x38) {
            func_002539C8(2);
            HW(0x1C) = 0x37;
        }
    } while (run);
    HW(0x1C) = s3;
    g = GW(0x240);
    if (g & 0x4000) {
        GW(0x240) = g ^ 0x4000;
    } else if (g & 0x8000) {
        GW(0x240) = g ^ 0x8000;
    }
    GW(0x240) = GW(0x240) & ~0x10000;
    GW(0x240) = GW(0x240) & ~0x20000;
    HW(0x48C) = HW(0x48C) & ~1;
    HW(0x48C) = HW(0x48C) & ~2;
    HW(0x48C) = HW(0x48C) & ~0x20;
    func_00243968(0, 0, 0);
    func_0028BB60(D_003876AC);
    D_003876AC = 0;
    return func_0029BB88(*(u8 **)(G + 4) + ((*(u32 *)(*(u8 **)(G + 4) + 0x6C) >> 2) << 2), GW(0x24));
}
