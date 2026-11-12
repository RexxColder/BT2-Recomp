#include "common.h"

s32 func_002AF6A0(s32 arg0);
s32 func_002AF860(s32 arg0, s32 arg1);
s32 func_002AFC18(s32 arg0, s32 arg1);
void func_002B0F78(s32 arg0, s32 arg1, f32 farg0);
void func_002B11F0(s32 arg0, f32 farg0, f32 farg1);
void func_002B1298(s32 arg0, f32 farg0, f32 farg1);
s32 func_002B12E0(s32 arg0, s32 arg1);
s32 func_002B1DF8(s32 arg0);
extern f32 D_003873C8;
extern f32 D_003873CC;
extern f32 D_003873D0;
extern f32 D_003873D4;
extern f32 D_003873D8;

void func_002AEA50(u8 *arg0) {
    func_002AF6A0((s32)arg0);
    func_002B0F78((s32)arg0, 1, D_003873C8);
    func_002B11F0((s32)arg0, *(f32 *)(arg0 + 0xAC) * D_003873CC, D_003873D0);
    func_002B1298((s32)arg0, D_003873D4, D_003873D8);
    func_002B12E0((s32)arg0, 0);
    func_002AF860((s32)arg0, 0);
    func_002AFC18((s32)arg0, 4);
    *(s32 *)(arg0 + 0x1C) = func_002B1DF8((s32)arg0);
}
