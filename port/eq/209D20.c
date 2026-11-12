#include "common.h"

void *func_00211288(s32 arg0);
extern s32 D_00387930;

f32 func_00209D20(u32 arg0) {
    f32 temp_f0;

    if (D_00387930 != 0 && arg0 < 2U) {
        temp_f0 = *(f32 *)((u8 *)func_00211288(arg0) + 0xAC4);
        if (temp_f0 < 0.5f) {
            return 0.5f;
        }
        return temp_f0;
    }
    return 0.0f;
}
