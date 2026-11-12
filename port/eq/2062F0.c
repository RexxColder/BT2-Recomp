#include "common.h"

s32 func_0025FBE8(s32 arg0, s64 arg1);
void func_00267550(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* 0x002062F0: three bit tests on the 64-bit mask bits 56, 57 and 58 (func_0025FBE8 with the
 * record's handle at +0x1530). Each set bit runs two or one func_00267550 calls and two
 * func_002113C0 calls on the record (the last one is a tail call whose result is returned). */
s32 func_002062F0(u8 *arg0) {
    if (func_0025FBE8(*(s32 *)(arg0 + 0x1530), (s64)0x8000 << 41) != 0) {
        func_00267550(*(s32 *)(arg0 + 0x1530), 0, 0);
        func_00267550(*(s32 *)(arg0 + 0x1530), 0xE, 0);
        func_002113C0((s32)arg0, 2, 0x200000, 1);
        func_002113C0((s32)arg0, 2, 0x400000, 0);
    }

    if (func_0025FBE8(*(s32 *)(arg0 + 0x1530), (s64)0x8000 << 42) != 0) {
        func_00267550(*(s32 *)(arg0 + 0x1530), 0, 0);
        func_00267550(*(s32 *)(arg0 + 0x1530), 0xC, 0);
        func_002113C0((s32)arg0, 2, 0x200000, 0);
        func_002113C0((s32)arg0, 2, 0x400000, 1);
    }

    if (func_0025FBE8(*(s32 *)(arg0 + 0x1530), (s64)0x8000 << 43) != 0) {
        func_00267550(*(s32 *)(arg0 + 0x1530), 0, 0);
        func_002113C0((s32)arg0, 2, 0x200000, 0);
        return func_002113C0((s32)arg0, 2, 0x400000, 0);
    }
    return 0;
}
