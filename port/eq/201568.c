#include "common.h"

void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 func_002414E0(s32 arg0, s32 arg1);
void Vec3_DiffToEuler_20E478(f32 farg0, s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s32 arg1);
s32 func_00241958(s32 arg0, s32 arg1);
s32 BtlChar_FrameMod(s32 arg0);
void func_00210000(s32 arg0, s32 arg1);
s32 func_00212DD8(s32 arg0, s32 arg1);
s32 func_00212408(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00203C58(s32 a0, s64 a1);
s32 func_00203310(u8 *arg0, s32 arg1, s32 arg2, f32 arg3);
void func_0020D048(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_0020D240(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
s32 func_00240FC8(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00212890(s32 arg0);
extern f32 D_003858CC;
extern f32 D_003858D0;
extern f32 D_003858D4;

#define ADDR(p) ((s32)(u32)(p))

/* 0x00201568: start a character action. a1 = opponent/char, a2 = action data (+0x64 -> mode at +4). */
void bt2_fightlog_note(const char *fmt, ...);
void func_00201568(u8 *self, s32 a1, u8 *a2, s32 a3, u32 t0, s32 t1, f32 ang0) {
    u8 *state = self + 0xB48;
    u8 flag = (u8)t0;
    s32 mode = *(s32 *)(*(u8 **)(a2 + 0x64) + 4);
    s32 obj = ADDR(self);
    s32 anim;
    bt2_fightlog_note("IMPACTO-201568 victima %08X (acc %X B48 %d) atacante %08X (acc %X B48 %d) reaccion %d", (s32)self,
                      *(s32 *)(self + 0xC00), *(s32 *)(self + 0xB48), a1, *(s32 *)((u8 *)a1 + 0xC00), *(s32 *)((u8 *)a1 + 0xB48), a3);
    s32 sel;
    s32 flags;
    f32 ang;
    f32 f20;
    f32 f21;

    *(s32 *)state = a3;
    *(s32 *)(state + 0x10) = 0;
    *(s32 *)(state + 0x18) = 0;
    *(s32 *)(state + 0x40) = mode;
    func_002113C0(self, 6, 1, 1);
    if (flag != 0) {
        *(f32 *)(self + 0xB64) = ang0;
        *(s32 *)(self + 0xB68) = 0;
    } else {
        f32 w = BtlUtil_WrapAngle(ang0 + D_003858CC);
        *(s32 *)(self + 0xB68) = 0;
        *(f32 *)(self + 0xB64) = w;
    }
    state[0xC] = flag;
    *(f32 *)(state + 0x14) = ang0;
    ang = func_002414E0(a1, mode);
    Vec3_DiffToEuler_20E478(ang, obj, t1);
    func_00206958(obj, 0x800000);
    anim = func_00241958(a1, mode);
    switch (anim) {
    case 1:
        func_00210000(ADDR(a2 + 0x20), BtlChar_FrameMod(2) != 0 ? 0x1B : 0x11);
        func_00212DD8(obj, 0);
        break;
    case 2:
        func_00210000(ADDR(a2 + 0x20), 0x47);
        func_00212DD8(obj, 1);
        break;
    case 3:
        func_00210000(ADDR(a2 + 0x20), 0x4A);
        func_00212DD8(obj, 3);
        break;
    case 0:
        func_00212DD8(obj, 0);
        break;
    default:
        break;
    }
    sel = func_00212408(a1, mode, 0, 0);
    flags = 0;
    if (mode == 3) {
        flags = 0x400;
    } else if (mode == 2) {
        flags = 0x200;
    } else if (mode == 4) {
        flags = 0x800;
    }
    if (func_00203C58(a1, 0x8000000) != 0) {
        flags = flags | 1;
    }
    f21 = 100.0f;
    func_00203310(self, sel, flags, ang);
    func_002113C0(self, 6, 0x10, 1);
    f20 = D_003858D0;
    func_0020D048(ADDR(a2 + 0x20), f21, D_003858D4, 5.0f, f20);
    func_0020D240(ADDR(a2 + 0x20), f21, 1000.0f, 1.0f, f20);
    func_002113C0(self, 1, 0x40000, 1);
    func_002113C0(self, 1, 0x80000, 1);
    if (func_00240FC8(a1, mode) == 2) {
        func_002113C0((u8 *)(u32)a1, 4, 0x4000000, 1);
    }
    *(s32 *)(self + 0x1168) = 0;
    if (mode == 4) {
        if (func_00211310(obj, 1, 1) == 0) {
            func_002113C0(self, 0, 1, 0);
            if (func_00211310(obj, 10, 0x200) != 0) {
                func_002113C0(self, 0, 0x10000, 1);
            }
        }
    }
    if (mode < 2) {
        return;
    }
    if (mode < 4) {
        func_00212890(90);
    } else if (mode == 4) {
        func_00212890(120);
    }
}
