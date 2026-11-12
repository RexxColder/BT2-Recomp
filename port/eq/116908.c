#include "common.h"

void func_00116038(s32 arg0, s32 arg1, s32 arg2);
void func_00116268(s32 arg0, s32 arg1);
void func_001164C8(s32 arg0, s32 arg1, s32 arg2);
f32 func_001165F8(s32 arg0, s32 arg1);
f32 func_00116698(f32 farg0, s32 arg0);
void func_00116790(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
s32 func_0020A440(s32 arg0);
s32 func_0020BD10(s32 arg0);
f32 func_0020C198(s32 arg0);
f32 func_00272FA8(void);
void func_0029D548(void);
void func_0029D580(s32 arg0);
void func_003126C8(s32 arg0, s32 arg1);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);
extern f32 D_00383F30;
extern u8 *D_00387A40;
extern s32 gBtlCam;

void func_00116908(s32 arg0, s32 arg1) {
    u8 *p = (u8 *)arg0;
    f32 var_f0;
    s32 temp_s4;
    s32 temp_s5;
    s32 var_s2;
    s32 var_s3;

    var_s2 = arg0 + 0xB0;
    var_s3 = arg0 + 0x100;
    temp_s4 = gBtlCam + (arg1 * 0x300);
    temp_s5 = (arg1 == 0);
    *(f32 *)(p + 4) = D_00383F30;
    *(f32 *)(p + 8) = 10.0f;
    *(f32 *)(p + 0) = 800.0f;
    *(f32 *)(p + 0xC) = func_0020C198(arg1);
    *(f32 *)(p + 0x10) = func_00272FA8();
    if (func_0020BD10(arg1) == 0) {
        func_003126C8(var_s3, *(s32 *)D_00387A40 + (arg1 * 0x18580) + 0x9C0);
        sceVu0CopyMatrix(var_s2, temp_s4);
    } else {
        var_s3 = arg0 + 0x100;
        var_s2 = arg0 + 0xB0;
    }
    *(s32 *)(p + 0x104) = 0;
    if (func_0020A440(arg1) != 0) {
        var_f0 = func_001165F8(0, 1);
    } else {
        var_f0 = *(f32 *)(p + 0);
    }
    *(f32 *)(p + 0xF0) = func_00116698(var_f0, arg0);
    func_0029D548();
    func_00116790(arg0 + 0x70, var_s2, var_s3, *(f32 *)(p + 0xF0), 36.0f, 2048.0f, 2048.0f);
    func_0029D580(1);
    func_00116038(arg0, arg1, temp_s5);
    func_001164C8(arg0, arg1, temp_s5);
    func_00116268(arg0, arg1);
}
