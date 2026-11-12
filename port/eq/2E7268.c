#include "common.h"

void func_002E7070(s32 arg0, s32 arg1, s32 arg2);
void func_002E70B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 D_00347BD4 __attribute__((section(".data")));
extern u8 D_0037BA08[] __attribute__((section(".data")));

s32 func_002E7268(s32 arg0, s32 arg1, s32 arg2) {
    if (D_00347BD4 == 0) {
        func_002E7070(arg0, arg1, arg2);
    }
    func_002E70B0((s32)D_0037BA08, 6, arg0, arg1, arg2);
    return 0;
}
