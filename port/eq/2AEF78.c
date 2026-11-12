#include "common.h"

void func_002AF6A0(s32 arg0);
void func_002AF860(s32 arg0, s32 arg1);
void func_002B0F78(s32 arg0, s32 arg1, f32 farg0);
void func_002B11F0(s32 arg0, f32 farg0, f32 farg1);
void func_002B1298(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_00387418;
extern f32 D_0038741C;
extern f32 D_00387420;

void func_002AEF78(s32 arg0) {
    f32 zero = 0.0f;

    func_002AF6A0(arg0);
    func_002B0F78(arg0, 0, D_00387418);
    func_002B11F0(arg0, zero, D_0038741C);
    func_002B1298(arg0, zero, D_00387420);
    func_002AF860(arg0, 0);
    *(u8 *)(arg0 + 0x21) = 1;
}
