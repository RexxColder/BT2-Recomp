#include "common.h"

s32 func_002AF5E8(s32 arg0);
void func_002AF860(s32 arg0, s32 arg1);
void func_002AFC18(s32 arg0, s32 arg1);
void func_002B0F78(s32 arg0, s32 arg1, f32 farg0);
void func_002B11F0(s32 arg0, f32 farg0, f32 farg1);
void func_002B1298(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_00387408;
extern f32 D_0038740C;
extern f32 D_00387410;

void func_002AEEA0(s32 arg0) {
    if (func_002AF5E8(arg0) != 0) {
        *(s8 *) (arg0 + 0x188) = 1;
    }
    func_002B0F78(arg0, 0, D_00387408);
    func_002B11F0(arg0, 0.0f, D_0038740C);
    func_002B1298(arg0, 0.0f, D_00387410);
    func_002AF860(arg0, 0);
    func_002AFC18(arg0, 4);
}
