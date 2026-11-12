#include "common.h"

void func_002B2770(s32 arg0, s32 arg1, s32 arg2);
void func_002B27B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 D_00345208 __attribute__((section(".data")));
extern u8 D_00377CD0[] __attribute__((section(".data")));

s32 func_002B2968(s32 arg0, s32 arg1, s32 arg2) {
    if (D_00345208 == 0) {
        func_002B2770(arg0, arg1, arg2);
    }
    func_002B27B0((s32)D_00377CD0, 6, arg0, arg1, arg2);
    return 0;
}
