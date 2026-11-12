#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern s32 D_0037AAE8 __attribute__((section(".data")));
extern s32 D_0037AAF0 __attribute__((section(".data")));

s32 func_002D5CD0(s32 arg0, s32 arg1);
void func_002D5D08(s32 arg0, s32 arg1, s32 arg2);
void func_002D6420(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002D6618(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D68E8(s32 arg0, s32 arg1);
void func_002D6C90(s32 arg0, s32 arg1, s32 arg2);

void func_002D61C8(s32 arg0, s32 arg1, s32 arg2) {
    s32 s0;

    s0 = W(arg0, 4);
    if (s0 == 0) {
        W(arg0, 4) = func_002D68E8(arg1, (s32)&D_0037AAE8);
    }
    switch (s0) {
    case 0x11:
        if (W(arg1, 0x90) != 1) {
            func_002D6420(arg0, arg1, arg2, 0);
            return;
        }
        /* fall through */
    case 0x1001:
        func_002D5D08(arg0, arg1, 0x15);
        func_002D6420(arg0, arg1, arg2, 1);
        return;
    case 0x21:
        func_002D5D08(arg0, arg1, 1);
        func_002D6618(arg0, arg1, arg2);
        return;
    case 0x31:
        func_002D5D08(arg0, arg1, 2);
        func_002D6420(arg0, arg1, arg2, 1);
        return;
    case 0x41:
    case 0x51:
    case 0x61:
        func_002D5D08(arg0, arg1, func_002D5CD0(arg0, arg1));
        func_002D6420(arg0, arg1, arg2, 1);
        return;
    case 0x101:
        func_002D6420(arg0, arg1, arg2, 0);
        return;
    default:
        func_002D6C90(arg0, arg1, (s32)&D_0037AAF0);
        return;
    }
}
