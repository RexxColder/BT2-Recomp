#include "common.h"

void *func_00211288(s32 arg0);
extern f32 D_003859B0;
extern s32 D_00387930;

f32 func_0020C288(u32 arg0) {
    if (D_00387930 != 0 && arg0 < 2U) {
        return (f32)(*(s32 *)((u8 *)func_00211288(arg0) + 0x9B4)) / D_003859B0;
    }
    return 0.0f;
}
