#include "m2c_macros.h"

void *func_00211288(s32 arg0);
extern s32 D_00387930;

void func_0020D408(u32 arg0, s32 arg1) {
    if (D_00387930 != 0 && arg0 < 2) {
        *(s32 *)((u8 *)func_00211288((s32)arg0) + 0x36C) = arg1;
    }
}
