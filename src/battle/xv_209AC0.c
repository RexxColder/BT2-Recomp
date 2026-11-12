#include "common.h"

s32 func_00211288(s32 arg0);
extern s32 D_00387930;

/* when D_00387930 is set and arg0 < 2: float at +0x1F4 of func_00211288(arg0), else 1.0f */
f32 func_00209AC0(u32 arg0) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        return *(f32 *)((u8 *)func_00211288(arg0) + 0x1F4);
    }
    return 1.0f;
}
