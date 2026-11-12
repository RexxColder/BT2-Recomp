#include "common.h"

s32 func_002B8280(s32 arg0);
s32 Rand_Range(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002FFC78(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 D_00379CE8[] __attribute__((section(".data")));

void func_002BB0F8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_002B8280((s32)arg0) != 1) {
        Rand_Range((s32)D_00379CE8, arg1, 0, arg2, arg3);
        return;
    }
    func_002FFC78(*(s32 *)(arg0 + 0x48), arg1, 0, arg2, arg3);
}
