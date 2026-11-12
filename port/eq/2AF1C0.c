#include "common.h"

s32 func_002AF560(u8 *arg0);
void func_002AF578(s32 arg0, s32 arg1);
s32 func_002AF5E8(s32 arg0);
void func_002AF648(s32 arg0, s32 arg1);
void func_002AF6A0(s32 arg0);
void func_002AF860(s32 arg0, s32 arg1);
s32 func_002B0DB0(s32 arg0, s32 arg1);
void func_002B0F78(f32 farg0, s32 arg0, s32 arg1);
void func_002B11F0(s32 arg0, f32 farg0, f32 farg1);
void func_002B1298(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_00387444;
extern f32 D_00387448;
extern f32 D_0038744C;
extern f32 D_00387450;
extern f32 D_00387454;
extern f32 D_00387458;

void func_002AF1C0(u8 *arg0) {
    s32 v;
    f32 f20;

    v = func_002AF560(arg0);
    f20 = 0.0f;
    switch (v) {
    case 24:
        func_002AF648((s32)arg0, 0x19);
        f20 = D_00387444;
        break;
    case 25:
        f20 = D_00387448;
        func_002AF6A0((s32)arg0);
        if (func_002B0DB0((s32)arg0, 0x05000000) == 0) {
            func_002AF578((s32)arg0, 0x1A);
        }
        break;
    case 26:
        if (func_002AF5E8((s32)arg0) != 0) {
            *(u8 *)(arg0 + 0x188) = 1;
        }
        break;
    case 37:
        f20 = D_0038744C;
        func_002AF6A0((s32)arg0);
        if (func_002B0DB0((s32)arg0, 0x05000000) == 0) {
            *(u8 *)(arg0 + 0x188) = 1;
        }
        break;
    }
    func_002B0F78(D_00387450, (s32)arg0, 1);
    func_002B11F0((s32)arg0, f20, D_00387454);
    func_002B1298((s32)arg0, 0.0f, D_00387458);
    func_002AF860((s32)arg0, 0);
    *(u8 *)(arg0 + 0x21) = 1;
}
