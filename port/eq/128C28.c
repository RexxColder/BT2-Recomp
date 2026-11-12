#include "common.h"

/* 0x00128C28: scales row 0 by arg2[0] on x, row 1 by arg2[1] on y and row 2 by arg2[2] on z; rows are copied to
 * arg0 (VU0 vmulx.x / vmuly.y / vmulz.z), row 3 is not written. */
void func_00128C28(u8 *arg0, u8 *arg1, f32 *arg2) {
    s32 i;

    for (i = 0; i < 4; i++) {
        ((s32 *)arg0)[i] = ((s32 *)arg1)[i];
        ((s32 *)(arg0 + 0x10))[i] = ((s32 *)(arg1 + 0x10))[i];
        ((s32 *)(arg0 + 0x20))[i] = ((s32 *)(arg1 + 0x20))[i];
    }
    ((f32 *)arg0)[0] = ((f32 *)arg1)[0] * arg2[0];
    ((f32 *)(arg0 + 0x10))[1] = ((f32 *)(arg1 + 0x10))[1] * arg2[1];
    ((f32 *)(arg0 + 0x20))[2] = ((f32 *)(arg1 + 0x20))[2] * arg2[2];
}
