#include "common.h"

s32 func_002D5E78(s32 arg0, s32 arg1);
void func_002D5F18(s32 arg0, s32 arg1);
void func_002D5F38(s32 arg0, s32 arg1);
void func_002D6008(s32 arg0, s32 arg1);
void func_002D6028(s32 arg0, s32 arg1);
void func_002D6048(s32 arg0, s32 arg1);
void func_002D6068(s32 arg0, s32 arg1);
void func_002D6C90(s32 arg0, s32 arg1, s32 arg2);

extern u8 D_0037A8B0[] __attribute__((section(".data")));

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))

/* 0x002D5D20: dispatch on a code (arg2): the check func_002D5E78 must return 1, the code is stored at +0x34, and
 * codes 1, 2, 4, 5, 11, 13 and 21 tail-call their handler with (arg0, arg1); every other code (and codes of
 * 0x65 or more) goes to func_002D6C90 with the address D_0037A8B0. */
void func_002D5D20(s32 arg0, s32 arg1, s32 arg2) {
    if (func_002D5E78(arg0, arg2) != 1) {
        return;
    }
    LD32(arg0, 0x34) = arg2;

    if ((u32)arg2 < 0x65) {
        switch (arg2) {
        case 1:
            func_002D5F38(arg0, arg1);
            return;
        case 2:
            func_002D6008(arg0, arg1);
            return;
        case 4:
            func_002D6028(arg0, arg1);
            return;
        case 5:
            func_002D6048(arg0, arg1);
            return;
        case 11:
        case 13:
            func_002D5F18(arg0, arg1);
            return;
        case 21:
            func_002D6068(arg0, arg1);
            return;
        default:
            break;
        }
    }
    func_002D6C90(arg0, arg1, (s32)D_0037A8B0);
}
