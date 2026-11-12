#include "common.h"

s32 func_002AF6A0(s32 arg0);
s32 func_002AF860(s32 arg0, s32 arg1);
s32 func_002AFC18(s32 arg0, s32 arg1);
void func_002B0F78(s32 arg0, s32 arg1, f32 farg0);
void func_002B11F0(s32 arg0, f32 farg0, f32 farg1);
void func_002B1298(s32 arg0, f32 farg0, f32 farg1);
s32 func_002B12E0(s32 arg0, s32 arg1);
s32 func_002B1DF8(s32 arg0);
extern f32 D_003873B0;
extern f32 D_003873B4;
extern f32 D_003873B8;
extern f32 D_003873BC;
extern f32 D_003873C0;

void func_002AE8F0(u8 *arg0) {
    func_002AF6A0((s32)arg0);
    func_002B0F78((s32)arg0, 1, D_003873B0);
    func_002B11F0((s32)arg0, *(f32 *)(arg0 + 0xAC) * D_003873B4, D_003873B8);
    func_002B1298((s32)arg0, D_003873BC, D_003873C0);
    func_002B12E0((s32)arg0, 0);
    func_002AF860((s32)arg0, 0);
    func_002AFC18((s32)arg0, 4);
    *(s32 *)(arg0 + 0x1C) = func_002B1DF8((s32)arg0);
}
