#include "common.h"

s32 func_0025FBE8(s32 arg0, s64 arg1);
s32 BtlChar_FrameMod(s32 arg0);
void func_0020FC38(s32 arg0, s32 arg1);
s32 func_0023F410(s32 arg0);
s32 func_001017F0();
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_0023F2B8(s32 arg0);
s32 BtlChar_GetHitSoundLine(s32 arg0);
s32 func_002100C0();

#define OBJ (*(s32 *)((u8 *)a0 + 0x1530))

s32 func_00205EE0(s32 a0) {
    s32 v;

    if (func_0025FBE8(OBJ, 0x10LL) != 0) {
        func_0020FC38(a0, BtlChar_FrameMod(3) + 40);
    }
    if (func_0025FBE8(OBJ, 0x10000000LL) != 0) {
        func_0020FC38(a0, 30);
    }
    if (func_0025FBE8(OBJ, 0x20000000LL) != 0) {
        func_0020FC38(a0, BtlChar_FrameMod(2) + 0);
    }
    if (func_0025FBE8(OBJ, 0x40000000LL) != 0) {
        func_0020FC38(a0, BtlChar_FrameMod(3) + 6);
    }
    if (func_0025FBE8(OBJ, 0x800000000LL) != 0) {
        func_0020FC38(a0, 32);
    }
    if (func_0025FBE8(OBJ, 0x1000000000LL) != 0) {
        func_0020FC38(a0, 77);
    }
    if (func_0025FBE8(OBJ, 0x2000000000LL) != 0) {
        func_0020FC38(a0, 37);
    }
    if (func_0025FBE8(OBJ, 0x4000000000LL) != 0) {
        func_0020FC38(a0, (func_0023F410(a0) & 0x8000) ? 0xB : 0x33);
    }
    if (func_0025FBE8(OBJ, 0x10000000000LL) != 0) {
        func_0020FC38(a0, 48);
    }
    if (func_0025FBE8(OBJ, 0x20000000000LL) != 0) {
        func_001017F0(15398, -0x28);
    }
    if (func_0025FBE8(OBJ, 0x80000000000000LL) != 0) {
        func_001017F0(15400, -0x28);
    }
    if (func_0025FBE8(OBJ, 0x800000000000LL) != 0) {
        func_0020FC38(a0, 72);
    }
    if (func_0025FBE8(OBJ, 0x2LL) != 0 && (func_00211310(a0, 4, 1) == 0 || func_00211310(a0, 4, 8) != 0)) {
        v = BtlChar_GetHitSoundLine(func_0023F2B8(a0));
        if (v >= 0) func_0020FC38(a0, v);
    }
    if (func_0025FBE8(OBJ, 0x1000000000000LL) != 0) {
        func_0020FC38(a0, 18);
    }
    if (func_0025FBE8(OBJ, 0x2000000000000LL) != 0) {
        func_0020FC38(a0, 24);
    }
    if (func_0025FBE8(OBJ, 0x4000000000000LL) != 0) {
        func_0020FC38(a0, 44);
    }
    if (func_0025FBE8(OBJ, 0x8000000000000LL) != 0) {
        func_0020FC38(a0, 31);
    }
    if (func_0025FBE8(OBJ, 0x10000000000000LL) != 0) {
        func_0020FC38(a0, 49);
    }
    if (func_0025FBE8(OBJ, 0x20000000000000LL) != 0) {
        func_0020FC38(a0, BtlChar_FrameMod(2) + 4);
    }
    if (func_0025FBE8(OBJ, 0x80000000LL) == 0) return 0;
    return func_002100C0(a0, BtlChar_FrameMod(2));
}
