#include "common.h"

s32 func_002EA050(s32 arg0);
s32 func_002EA2F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002EC198(s32 arg0);
extern s32 D_0037BFE8 __attribute__((section(".data")));
extern s32 D_0037C010 __attribute__((section(".data")));

s32 func_002EC530(s32 arg0, s32 arg1, s32 arg2) {
    s32 v;

    func_002EA2F0(6, 0, arg0, arg1, arg2);
    if (arg0 == 0) {
        func_002EA050((s32)&D_0037BFE8);
        return -3;
    }
    if (*(s8 *)(arg0 + 1) == 2) {
        func_002EC198(arg0);
    }
    if (arg2 == 0) {
        *(s32 *)(arg0 + 0x18) = arg1;
    } else if (arg2 == 1) {
        *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0x18) + arg1;
    } else if (arg2 == 2) {
        *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0xC) + arg1;
    } else {
        func_002EA050((s32)&D_0037C010);
        return -3;
    }
    v = *(s32 *)(arg0 + 0x18);
    if (v >= 0) {
        if (*(s32 *)(arg0 + 0xC) < v) {
            *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0xC);
        }
    } else {
        *(s32 *)(arg0 + 0x18) = 0;
    }
    func_002EA2F0(6, 1, arg0, arg1, arg2);
    return *(s32 *)(arg0 + 0x18);
}
