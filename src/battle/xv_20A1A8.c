#include "common.h"

s32 func_00211288(s32 arg0);
extern s32 D_00387930;

/* when D_00387930 is set and arg0 < 2: min(1.0f, (f32)obj->+0xB90 / 90.0f) with obj = func_00211288(arg0), else 0.0f */
f32 func_0020A1A8(u32 arg0) {
    f32 t;
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        t = (f32)*(s32 *)((u8 *)func_00211288(arg0) + 0xB90) / 90.0f;
        if (t > 1.0f) {
            return 1.0f;
        }
        return t;
    }
    return 0.0f;
}
