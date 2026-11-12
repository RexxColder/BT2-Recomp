#include "common.h"

s32 func_002AF560(void *arg0);
void func_002AF6A0(void *arg0, s32 arg1);
void func_002AF860(void *arg0, s32 arg1);
void func_002AFC18(void *arg0, s32 arg1);
void func_002B0F78(void *arg0, s32 arg1, f32 farg2);
void func_002B11F0(void *arg0, f32 farg1, f32 farg2);
void func_002B1298(void *arg0, f32 farg1, f32 farg2);
void func_002B12E0(void *arg0, s32 arg1);
s32 func_002B1DF8(void *arg0);
extern f32 D_00387320;
extern f32 D_00387324;
extern f32 D_00387328;
extern f32 D_0038732C;

void func_002AE0A8(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_002AF560(arg0);
    switch (temp_v0) {
    case 23:
        func_002AF6A0(arg0, 0x26);
        break;
    case 38:
        func_002AF6A0(arg0, 0x26);
        break;
    }
    func_002B0F78(arg0, 0, D_00387320);
    if ((u32)(*(s32 *)((u8 *)arg0 + 0x10) - 1) < 2U) {
        func_002B11F0(arg0, 0.0f, D_00387324);
    } else {
        func_002B11F0(arg0, 0.0f, D_00387328);
    }
    func_002B1298(arg0, 0.0f, D_0038732C);
    func_002B12E0(arg0, 0);
    func_002AF860(arg0, 0);
    func_002AFC18(arg0, 4);
    *(s32 *)((u8 *)arg0 + 0x1C) = func_002B1DF8(arg0);
}
