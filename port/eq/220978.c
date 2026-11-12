#include "common.h"

extern f32 D_00385F3C __attribute__((section(".data")));
extern f32 D_00385F40 __attribute__((section(".data")));
extern f32 D_00385F44 __attribute__((section(".data")));
extern f32 D_00385F48 __attribute__((section(".data")));
extern f32 D_00385F4C __attribute__((section(".data")));
extern f32 D_00385F50 __attribute__((section(".data")));

f32 func_001FA318(s32 arg0);
s32 func_00218560(u8 *arg0, f32 farg0);
s32 func_00212820(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00212878();
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00203310(s32 arg0, s32 arg1, s32 arg2);
void func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
void BtlChar_Vibrate(u8 *arg0, f32 farg0, f32 farg1);
void BtlAnim_SetBlend(u8 *arg0, f32 farg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);

s32 func_00220978(u8 *obj) {
    u8 *ctx;
    f32 x;
    f32 vib;

    x = func_001FA318((s32)obj);
    if (0.5f < x && func_00218560(obj, D_00385F3C) != 0) {
        ctx = *(u8 **)(obj + 0x1530);
        if ((*(u32 *)(ctx + 0xED0) & 0x40) != 0) {
            if (func_00212820((s32)obj) == 0) {
                return 169;
            }
            return 155;
        }

        if (func_00212820((s32)obj) == 0 || func_00211310((s32)obj, 1, 0x80000) != 0 ||
            BtlPad_Test48((s32)obj, 8) == 0) {
            vib = D_00385F40;
            func_00203310((s32)obj, 0x12C, 0);
            func_002113C0(obj, 6, 0x10, 1);
            func_001FBE80((s32)obj, 3.0f, vib);
            BtlChar_Vibrate(obj, D_00385F44, vib);
            return 169;
        }
        return 42;
    }

    x = func_001FA318((s32)obj);
    if (D_00385F48 < x) {
        if (func_00211310((s32)obj, 0, 4) == 0) {
            BtlAnim_SetBlend(obj, D_00385F4C);
            if (func_00212878() == 0) {
                return 33;
            }
            if (func_00212820((s32)obj) != 0) {
                return 38;
            }
            return 33;
        }
    }

    if (func_00211310((s32)obj, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(obj, D_00385F50);
    if (func_00212820((s32)obj) == 0) {
        return 166;
    }
    if (func_00211310((s32)obj, 1, 0x80000) != 0) {
        return 166;
    }
    if (BtlPad_Test48((s32)obj, 12) != 0) {
        func_002113C0(obj, 0, 2, 1);
        return 40;
    }
    if (BtlPad_Test48((s32)obj, 13) != 0) {
        return 39;
    }
    return 166;
}
