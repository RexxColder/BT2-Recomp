#include "common.h"

void func_00206958(s32 arg0, s64 arg1);
s32 func_00241958(s32 arg0, s32 arg1);
s32 BtlChar_FrameMod(s32 arg0);
s32 func_00210000(s32 arg0, s32 arg1);
void func_00212DD8(s32 arg0, s32 arg1);
s32 func_00212408(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00203C58(s32 arg0, s64 arg1);
void func_00203310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0020D048(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_0020D240(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern f32 D_003858D8;
extern f32 D_003858DC;

void func_00201968(s32 arg0, s32 arg1, s32 arg2) {
    u8 *s0;
    s32 s2;
    s32 v;
    s32 s5;
    s32 s1;

    s2 = *(s32 *)(*(u8 **)(arg2 + 0x64) + 4);
    func_00206958(arg0, 0x800000);
    v = func_00241958(arg1, s2);
    s0 = (u8 *)arg2 + 0x20;
    if (v == 1) {
        func_00210000((s32)s0, (BtlChar_FrameMod(2) == 0) ? 0x11 : 0x1B);
        func_00212DD8(arg0, 0);
    } else if (v == 0) {
        func_00212DD8(arg0, 0);
    } else if (v == 2) {
        func_00210000((s32)s0, 0x47);
        func_00212DD8(arg0, 1);
    } else if (v == 3) {
        func_00210000((s32)s0, 0x4A);
        func_00212DD8(arg0, 3);
    }

    s5 = func_00212408(arg1, s2, 0, 0);
    s1 = 0;
    if (s2 == 2) {
        s1 = 0x200;
    } else if (s2 == 3) {
        s1 = 0x400;
    } else if (s2 == 4) {
        s1 = 0x800;
    }
    v = func_00203C58(arg1, 0x08000000);
    func_00203310(arg0, s5, (v == 0) ? s1 : (s1 | 1));
    func_002113C0(arg0, 6, 0x10, 1);
    func_0020D048((s32)s0, 100.0f, D_003858DC, 5.0f, D_003858D8);
    func_0020D240((s32)s0, 100.0f, 1000.0f, 1.0f, D_003858D8);
}
