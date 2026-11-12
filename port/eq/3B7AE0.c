#include "m2c_macros.h"

void func_003B7A38(void *, void *, u8, s32);

void func_003B7AE0(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;

    for (i = 0; i < arg4; i++) {
        func_003B7A38(arg0, (u8 *)arg1 + i, (u8)arg2, arg3);
    }
}
