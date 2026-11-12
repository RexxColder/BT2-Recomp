#include "common.h"

extern f32 D_00387348;
extern f32 D_0038734C;
extern f32 D_00387350;
extern f32 D_00387354;
extern f32 D_00387358;
extern f32 D_0038735C;
extern f32 D_00387360;

s32 func_002AF560(u8 *arg0);
void func_002AF648(void *arg0, s32 arg1);
void func_002AF6A0(void *arg0);
void func_002AF578(void *arg0, s32 arg1);
s32 func_002B0DB0(void *arg0, s32 arg1);
s32 func_002AF5E8(void *arg0);
void func_002B0F78(f32 farg0, void *arg0, s32 arg1);
void func_002B11F0(f32 farg0, f32 farg1, void *arg0);
void func_002B1298(f32 farg0, f32 farg1, void *arg0);
void func_002B12E0(void *arg0, s32 arg1);
void func_002AF860(void *arg0, s32 arg1);
void func_002AF720(f32 farg0, void *arg0);
void func_002AFC18(void *arg0, s32 arg1);
s32 func_002B1DF8(void *arg0);

void func_002AE2F8(u8 *arg0) {
    f32 var_f20 = 0.0f;
    s32 v = func_002AF560(arg0);

    if (v == 0x19) {
        var_f20 = D_0038734C;
        func_002AF6A0(arg0);
        if (func_002B0DB0(arg0, 0x05000000) == 0) {
            func_002AF578(arg0, 0x1A);
        }
    } else if (v < 0x1A) {
        if (v == 0x18) {
            func_002AF648(arg0, 0x19);
            var_f20 = D_00387348;
        }
    } else if (v == 0x1A) {
        if (func_002AF5E8(arg0) != 0) {
            *(s8 *)(arg0 + 0x188) = 1;
        }
    } else if (v == 0x26) {
        var_f20 = D_00387350;
        func_002AF6A0(arg0);
        if (func_002B0DB0(arg0, 0x05000000) == 0) {
            *(s8 *)(arg0 + 0x188) = 1;
        }
    }
    func_002B0F78(D_00387354, arg0, 1);
    func_002B11F0(var_f20, D_00387358, arg0);
    func_002B1298(0.0f, D_0038735C, arg0);
    func_002B12E0(arg0, 0);
    func_002AF860(arg0, 0);
    func_002AF720(D_00387360, arg0);
    func_002AFC18(arg0, 4);
    *(s32 *)(arg0 + 0x1C) = func_002B1DF8(arg0);
}
