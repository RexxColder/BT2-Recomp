#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_001F9D78(s32 arg0, s32 arg1);
s32 func_001F9FB0(s32 arg0, s32 arg1);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
void func_001FA110(s32 arg0, s32 arg1);
s32 func_00203310(s32 arg0, s32 arg1, s32 arg2);
void func_00206958(s32 arg0, s64 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
void func_00216890(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_00386AC0;
extern f32 D_00386AC4;
extern f32 D_00386AC8;
extern f32 D_00386ACC;
extern f32 D_00386AD0;

void func_00238310(s32 arg0) {
    s32 v;
    s32 s1;

    s1 = 0;
    v = BtlObjXf_Update(arg0);
    if (v == 0xA6) {
        func_001FA0A0(arg0, 0xA9, 1);
        func_002113C0(arg0, 6, 2, 1);
    } else if (v == 0xA9) {
        func_001FA110(arg0, 0);
        func_002113C0(arg0, 6, 2, 1);
        func_002113C0(arg0, 1, 0x1000, 1);
        s1 = 1;
        if (func_00211310(arg0, 1, 0x200) == 0) {
            if (func_00211310(arg0, 0, 4) != 0) {
                func_001F9D78(arg0, 0xAA);
                func_00203310(arg0, *(s32 *)(arg0 + 0xB80), 0x4000);
            }
            s1 = 1;
        }
    } else if (v == 0xAA) {
        func_001F9FB0(arg0, 0);
    }
    func_00215068(arg0, 8, 0xD, D_00386AC0, 0.5f);
    func_00215E88(arg0, 3, D_00386AC4);
    func_00216208(arg0, 0.0f, D_00386AC8);
    if (s1 != 0) {
        func_00216890(arg0, D_00386ACC, D_00386AD0);
    } else {
        func_00216678(arg0);
    }
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 1, 0x40, 1);
    func_002113C0(arg0, 3, 0x800, 1);
    func_002113C0(arg0, 3, 0xE, 1);
    func_002113C0(arg0, 6, 8, 1);
    func_00206958(arg0, (s64)0x8000 << 29);
    func_002113C0(arg0, 1, 0x800, 1);
}
