#include "common.h"

s32 func_002AF5E8(s32 arg0);
void func_002AF860(s32 arg0, s32 arg1);
void func_002AFC18(s32 arg0, s32 arg1);
void func_002B0F78(s32 arg0, s32 arg1, f32 farg0);
void func_002B11F0(s32 arg0, f32 farg0, f32 farg1);
void func_002B1298(s32 arg0, f32 farg0, f32 farg1);
void func_002B12E0(s32 arg0, s32 arg1);
void func_002B1CA8(s32 arg0, s32 arg1);
void func_002B1F08(s32 arg0);
void func_002B1FE8(s32 arg0);
void func_002B2388(s32 arg0, s32 arg1);
extern f32 D_003873E0;
extern f32 D_003873E4;
extern f32 D_003873E8;
extern s32 D_003B2654 __attribute__((section(".data")));

void func_002AEB68(s32 arg0) {
    if (func_002AF5E8(arg0) != 0) {
        *(u8 *)(arg0 + 0x188) = 1;
        if (D_003B2654 < 0) {
            func_002B1FE8(arg0);
            func_002B2388(arg0, 2);
            func_002AFC18(arg0, 2);
            func_002B1CA8(arg0, 0x10);
        } else {
            func_002B1F08(arg0);
        }
    }
    func_002B0F78(arg0, 0, D_003873E0);
    func_002B11F0(arg0, 0.0f, D_003873E4);
    func_002B1298(arg0, 0.0f, D_003873E8);
    func_002B12E0(arg0, 0);
    func_002AF860(arg0, 0);
    func_002AFC18(arg0, 4);
}
