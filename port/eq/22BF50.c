#include "common.h"

u8 *BtlMember_GetActiveGauge(s32 arg0);
void func_001FA110(s32 arg0, s32 arg1);
f32 func_00207E90(s32 arg0);
void func_0020D7E8(s32 arg0, f32 farg0, f32 farg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216890(s32 arg0, f32 farg0, f32 farg1);
f32 func_00240D50(s32 arg0, s32 arg1);
f32 func_00240DD0(s32 arg0, s32 arg1);
extern f32 D_0038659C;
extern f32 D_003865A0;
extern f32 D_003865A4;

void func_0022BF50(s32 arg0) {
    s32 a1;
    f32 f20;
    f32 f21;
    f32 f13;

    a1 = 1;
    if (func_00211310(arg0, 0, 0x100) == 0) {
        a1 = 0;
    }
    f20 = func_00240D50(arg0, a1);
    f21 = f20 * func_00207E90(arg0);
    f20 = D_0038659C;
    func_001FA110(arg0, 0);
    func_00215068(arg0, 0, 0xC, D_003865A0, f20);
    func_00215E88(f20, arg0, 0);
    func_00216208(arg0, f21, D_003865A4);
    f20 = -func_00240D50(arg0, 0x10);
    f13 = func_00240DD0(arg0, 0);
    func_00216890(arg0, f20, f13);
    func_002113C0(arg0, 9, 0x80000, 1);
    func_0020D7E8(arg0, 20.0f, 50.0f);
    if (*(u8 *)(BtlMember_GetActiveGauge(arg0) + 0x29) != 0) {
        func_002113C0(arg0, 6, 8, 1);
    }
}
