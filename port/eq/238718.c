#include "common.h"

s32 func_00217488(u8 *arg0);
s32 BattleSide_SetChara(u8 *arg0, s32 arg1);
void func_001F9D10(u8 *arg0, s32 arg1);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211418(u8 *arg0, s32 arg1);
void func_00211828(u8 *arg0);
u8 *BtlChar_GetPos(u8 *arg0);
void func_00215E30(u8 *arg0, f32 farg0, f32 farg1);
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_003126C8(u8 *arg0, u8 *arg1);
f32 BtlUtil_WrapAngle(f32 arg0);
f32 BtlCharApi_GetHeight(s32 arg0);
void func_001FC3B0(f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17,
                   u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, u8 *t1, u8 *t2, s32 t3,
                   s32 s8, s32 s9, s32 s10, s32 s11, s32 s12);
extern u8 D_002C3630 __attribute__((section(".data")));
extern f32 D_00386AE4;
extern f32 D_00386AE8;
extern f32 D_00386AEC;
extern f32 D_00386AF0;
extern f32 D_00386AF4;

void func_00238718(u8 *arg0) {
    s32 sp30[4];
    s32 sp40[4];
    s32 var_a1;
    s32 var_s0;
    f32 zero;
    f32 f21;
    f32 h;
    s32 v;

    zero = 0.0f;
    var_s0 = 0x18F;
    v = func_00217488(arg0);
    var_a1 = 0x18E;
    if (v == 0x31) {
        var_a1 = 0x1AE;
        var_s0 = 0x1AF;
    }
    BattleSide_SetChara(arg0, var_a1);
    func_001F9D10(arg0, var_s0);
    func_002113C0(arg0, 0xC, 1, 0);
    func_002113C0(arg0, 0xC, 4, 0);
    func_002113C0(arg0, 0xC, 8, 0);
    func_002113C0(arg0, 0xC, 0x10, 0);
    func_00211828(arg0);
    func_00215E30(arg0, *(f32 *)(BtlChar_GetPos(arg0) + 0x14), zero);
    *(f32 *)(BtlChar_GetPos(arg0) + 0xC0) = zero;
    *(f32 *)(BtlChar_GetPos(arg0) + 0xC4) = zero;
    func_002113C0(arg0, 0, 2, 1);
    func_002113C0(arg0, 9, 0x20, 1);
    func_00211418(arg0, 0x10000000);
    func_00208DE8(*(s32 *)(arg0 + 0x1534), (u8 *)sp30, 0x11);
    func_003126C8((u8 *)sp40, (u8 *)sp30);
    f21 = BtlUtil_WrapAngle(*(f32 *)(BtlChar_GetPos(arg0) + 0xB4) - D_00386AE4);
    h = BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x1534));
    func_001FC3B0(f21, zero, D_00386AF0, D_00386AF4, h * D_00386AE8, h * D_00386AEC,
                  arg0, (u8 *)sp30, (u8 *)&D_002C3630, (u8 *)sp40,
                  (u8 *)&D_002C3630, (u8 *)sp30, (u8 *)&D_002C3630, -1,
                  -1, -1, -1, 0x1E, 0xC5);
}
