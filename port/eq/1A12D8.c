#include "common.h"

extern s32 *D_0038780C;

s32 func_001A12D8(s32 arg0, f32 farg0) {
    u8 *e = (u8 *)D_0038780C[arg0];
    s32 v = 0;

    if (e != NULL) {
        u8 *p = *(u8 **)(e + 0x38);
        f32 t = farg0 * 8.0f;

        v = 1;
        *(f32 *)(p + 0x44) = farg0;
        *(f32 *)(p + 0x48) = t;
        *(f32 *)(p + 0x4C) = t;
    }
    return v;
}
