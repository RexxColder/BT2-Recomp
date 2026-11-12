#include "common.h"

s32 func_002EA050(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7);
extern u8 D_0037CD18[] __attribute__((section(".data")));

void func_002F6198(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7) {
    if (arg0 == NULL) {
        func_002EA050((s32)D_0037CD18, arg1, arg2, arg3, arg4, arg5, arg6, arg7, farg0, farg1, farg2, farg3, farg4, farg5, farg6, farg7);
        return;
    }
    *(s8 *)((u8 *)arg0 + 0x70) = (s8)arg1;
}
