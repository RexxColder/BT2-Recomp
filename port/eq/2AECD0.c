#include "common.h"

s32 func_002AF560(void *arg0);
void func_002AF578(void *arg0, s32 arg1);
void func_002AF6A0(void *arg0);
void func_002B1298(f32 farg0, f32 farg1, void *arg0);
void func_002B20E0(f32 *arg0);
s32 func_002B20B0(void);
void func_002B0F78(f32 farg0, void *arg0, s32 arg1);
void func_002B11F0(f32 farg0, f32 farg1, void *arg0);
void func_002B12E0(void *arg0, s32 arg1);
void func_002AFC18(void *arg0, s32 arg1);
extern f32 D_003873F0;
extern f32 D_003873F4;
extern f32 D_003873F8;
extern f32 D_003873FC;
extern f32 D_00387400;
extern f32 D_00387404;
extern u8 *D_00387E18;

void func_002AECD0(u8 *arg0) {
    f32 sp[4];
    s32 temp_v0;
    f32 var_f1;
    f32 temp_f0;

    func_002B20E0(sp);
    temp_v0 = func_002AF560(arg0);
    if (temp_v0 == 38 || temp_v0 == 35) {
        func_002AF6A0(arg0);
        func_002B1298(D_003873F0, D_003873F4, arg0);
        if (*(s32 *)(arg0 + 0x184) >= 9) {
            func_002AF578(arg0, 0x24);
            *(s32 *)(arg0 + 0x158) = 0;
            if (*(s32 *)(arg0 + 0x10) == 0) {
                D_00387E18[9] = 1;
            }
            if (func_002B20B0() >= 0) {
                *(f32 *)(arg0 + 0xD0) = sp[0];
                *(f32 *)(arg0 + 0xD8) = sp[2];
                *(f32 *)(arg0 + 0xD4) = sp[1] - 200.0f;
            }
        }
    } else if (temp_v0 == 36) {
        func_002AF6A0(arg0);
        temp_f0 = *(f32 *)(arg0 + 0xD4);
        if (temp_f0 < sp[1]) {
            var_f1 = (sp[1] - temp_f0) / 200.0f;
            if (var_f1 < 0.0f) {
                var_f1 = 0.0f;
            }
            if (var_f1 > 1.0f) {
                var_f1 = 1.0f;
            }
            *(f32 *)(arg0 + 0x150) = var_f1;
            func_002B1298(D_003873F8, D_003873FC, arg0);
        } else {
            D_00387E18[8] = 1;
        }
    }
    func_002B0F78(D_00387400, arg0, 0);
    func_002B11F0(0.0f, D_00387404, arg0);
    func_002B12E0(arg0, 0);
    arg0[0x7D] = 1;
    func_002AFC18(arg0, 4);
}
