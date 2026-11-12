#include "common.h"

extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_00386B14;
extern f32 D_00386B18;

void BattleSide_SetChara(s32 arg0, s32 arg1);
f32 BtlCharApi_GetHeight(s32 arg0);
u8 *BtlChar_GetPos(u8 *arg0);
u8 *BtlMember_GetActiveGauge(u8 *arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
void func_001F9D10(u8 *arg0, s32 arg1);
void func_001FC3B0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                   s32 a8, s32 a9, s32 a10, s32 a11, s32 a12,
                   f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211418(u8 *arg0, s32 arg1);
void func_00211828(u8 *arg0);
void func_00215E30(s32 arg0, f32 farg0, f32 farg1);
s32 func_0023F410(u8 *arg0);
void func_003126C8(u8 *arg0, u8 *arg1);

void func_00238E80(u8 *arg0) {
    u8 sp30[0x10];
    u8 sp40[0x10];
    f32 f20;
    f32 hgt;
    f32 fx;

    BattleSide_SetChara((s32)arg0, 0xFF);
    func_002113C0(arg0, 0xC, 1, 0);
    func_002113C0(arg0, 0xC, 4, 0);
    func_002113C0(arg0, 0xC, 8, 0);
    func_002113C0(arg0, 0xC, 0x10, 0);
    *(s32 *)(BtlChar_GetPos(arg0) + 0xC0) = 0;
    *(s32 *)(BtlChar_GetPos(arg0) + 0xC4) = 0;
    fx = *(f32 *)(BtlChar_GetPos(arg0) + 0x14);
    func_00215E30((s32)arg0, fx, 0.0f);
    func_00211828(arg0);
    if (func_0023F410(arg0) & 0x1000) {
        func_001F9D10(arg0, 0x1A4);
    } else {
        func_001F9D10(arg0, 0x3B);
    }
    func_002113C0(arg0, 0, 0x800, 0);
    *(s32 *)(BtlMember_GetActiveGauge(arg0) + 0x1C) = 0;
    func_002113C0(arg0, 0x10, 0x80000, 1);
    func_002113C0(arg0, 9, 0x10000000, 1);
    func_002113C0(arg0, 9, 0x20, 1);
    func_00211418(arg0, 0x08000000);
    func_00208DE8(*(s32 *)(arg0 + 0x1534), sp30, 3);
    func_003126C8(sp40, sp30);
    f20 = BtlUtil_WrapAngle(*(f32 *)(BtlChar_GetPos(arg0) + 0xB4) - D_00386B14);
    hgt = BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x1534));
    func_001FC3B0((s32)arg0, (s32)sp30, (s32)D_002C3630, (s32)sp40,
                  (s32)D_002C3630, (s32)D_002C3630, (s32)D_002C3630, -1,
                  -1, 3, 3, 1, 0xC5,
                  f20, 0.0f, D_00386B18, 0.0f, hgt * 1.5f, 0.0f);
}
