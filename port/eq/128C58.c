#include "common.h"

/* 0x00128C58: arg0 rows 0..2 = arg1 rows 0..2 with the diagonal scaled by farg0
   (VU0 vmulx.x on row 0, vmulx.y on row 1, vmulx.z on row 2: m[0], m[5], m[10]; B14, the port scaled m[0], m[4], m[8]). */
void func_00128C58(u8 *arg0, u8 *arg1, f32 farg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        ((s32 *)arg0)[i] = ((s32 *)arg1)[i];
        ((s32 *)(arg0 + 0x10))[i] = ((s32 *)(arg1 + 0x10))[i];
        ((s32 *)(arg0 + 0x20))[i] = ((s32 *)(arg1 + 0x20))[i];
    }
    ((f32 *)arg0)[0] = ((f32 *)arg1)[0] * farg0;
    ((f32 *)(arg0 + 0x10))[1] = ((f32 *)(arg1 + 0x10))[1] * farg0;
    ((f32 *)(arg0 + 0x20))[2] = ((f32 *)(arg1 + 0x20))[2] * farg0;
}
