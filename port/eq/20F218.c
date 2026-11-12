#include "common.h"

extern u8 *D_00387930;
extern f32 D_003859F0;
extern f32 D_003859F4;

u8 *func_00211288(s32 arg0);
void func_00210618(void *arg0, s32 arg1);
s32 func_00212320(u8 *arg0);
void func_00212DD8(u8 *arg0, s32 arg1);
s32 func_00212408(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00203310(u8 *arg0, s32 arg1, s32 arg2);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_0020A0F8(u32 arg0);
void func_0020EEF8(u8 *arg0, f32 farg0);
void func_0020ECF0(s32 arg0, s32 arg1);
void func_0020EC08(s32 arg0);
f32 func_0020F1C0(s32 arg0);
s32 func_00208DE8(s32 a0, u8 *a1, s32 a2);
void func_001A7AC8(void);
s32 BtlChar_FrameMod(s32 a0);
void sceVu0InterVector(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0);

s32 func_0020F218(s32 state) {
    u8 sp[0x20];
    u8 *base = D_00387930;
    s32 *cnt = (s32 *)(base + 0x40);
    s32 *flag = (s32 *)(base + 0x44);
    s32 *dir = (s32 *)(base + 0x48);
    f32 *phase = (f32 *)(base + 0x4C);
    u8 *vec = base + 0x50;
    s32 mode;
    s32 side;
    s32 a;
    s32 b;
    s32 v;
    f32 f20;
    f32 f12;

    switch (state) {
    case 1:
        *cnt = 0;
        *dir = 0;
        state++;
        func_00210618(func_00211288(0), 0x3C1B);
        mode = *dir;
        break;
    case 2:
        if (*cnt < 10) {
            if (func_00212320(func_00211288(0)) == 4) {
                *dir += 1;
            }
            if (func_00212320(func_00211288(1)) == 4) {
                *dir -= 1;
            }
        }
        f20 = func_0020A0F8(0);
        if (func_0020A0F8(1) < f20) {
            *dir += 1;
        }
        f20 = func_0020A0F8(0);
        if (f20 < func_0020A0F8(1)) {
            *dir -= 1;
        }
        v = *cnt;
        if (v == 0) {
            func_00212DD8(func_00211288(0), 0x14);
            v = *cnt;
        }
        if (v == 0x1E) {
            func_00212DD8(func_00211288(1), 0x14);
            v = *cnt;
        }
        if (v < 0x1E) {
            func_0020ECF0(0, 0);
        } else if (v < 0x3C) {
            func_0020ECF0(1, 0);
        } else {
            f12 = *phase;
            if (f12 < D_003859F0) {
                func_0020ECF0(0, 1);
            } else if (D_003859F4 < f12) {
                func_0020ECF0(1, 1);
            } else {
                func_0020EEF8(vec, f12);
            }
        }
        v = *cnt + 1;
        *cnt = v;
        if (v >= 0x6A) {
            *cnt = 0;
            state++;
        }
        mode = *dir;
        break;
    case 3:
        if (*cnt == 0) {
            v = *dir;
            if (v == 0) {
                v = BtlChar_FrameMod(2) ? 1 : -1;
                *dir = v;
            }
            if (v > 0) {
                func_00212DD8(func_00211288(0), 0x15);
            } else {
                func_00212DD8(func_00211288(1), 0x15);
            }
        }
        if (*dir > 0) {
            func_0020ECF0(0, 2);
        } else {
            func_0020ECF0(1, 2);
        }
        v = *cnt + 1;
        *cnt = v;
        if (v >= 0x10) {
            *cnt = 0;
            state++;
        }
        mode = *dir;
        break;
    case 4:
        v = *dir;
        if (v > 0) {
            v += 4;
        } else {
            v -= 4;
        }
        *dir = v;
        func_0020EEF8(vec, *phase);
        v = *dir;
        if (v < 0) {
            v = -v;
        }
        if (v >= 0x47) {
            *cnt = 0;
            state++;
        }
        mode = *dir;
        break;
    case 5:
        if (*cnt == 0) {
            if (*dir > 0) {
                side = 0;
            } else if (*dir < 0) {
                side = 1;
            } else {
                side = BtlChar_FrameMod(2) == 0;
            }
            a = func_00212320(func_00211288(side));
            b = func_00212320(func_00211288(side == 0));
            a = func_00212408(func_00211288(side), a, 0, 1);
            v = func_00212408(func_00211288(side == 0), b, 0, 1);
            func_00203310(func_00211288(side == 0), a + v / 2, 0);
            func_002113C0(func_00211288(side), 7, 0x800, 1);
            func_002113C0(func_00211288(side == 0), 7, 0x1000, 1);
            func_002113C0(func_00211288(side), 0x10, 0x40000000, 1);
            func_00212DD8(func_00211288(side == 0), 0x16);
            func_00210618(func_00211288(side == 0), 0x3C1C);
            func_001A7AC8();
            if ((*(s32 *)(D_00387930 + 8) & 4) == 0) {
                *(s32 *)(D_00387930 + 8) |= 4;
                func_002113C0(func_00211288(side), 0x10, 0x4000000, 1);
            }
            *flag = side;
        }
        if (*flag != 0) {
            func_0020ECF0(0, 0);
        } else {
            func_0020ECF0(1, 0);
        }
        v = *cnt + 1;
        *cnt = v;
        if (v < 0x1F) {
            mode = *dir;
        } else {
            state = 0;
            func_0020EC08(0);
            func_0020EC08(1);
            *dir = 0;
            mode = 0;
        }
        break;
    default:
        mode = *dir;
        break;
    }
    *phase = func_0020F1C0(mode);
    func_00208DE8(0, sp, 0x11);
    func_00208DE8(1, sp + 0x10, 0x11);
    sceVu0InterVector(vec, sp + 0x10, sp, *phase * 0.5f + 0.5f);
    return state;
}
