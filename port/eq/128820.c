#include "common.h"

/* 0x00128820 Mtx_Translate: copies the 3x4 part of a 4x4 matrix (rows 0..2) to arg0 and sets row 3 to src row 3 plus
 * the translation (x, y, z), w copied (VU0 vadd.xyz). */
void Mtx_Translate(u8 *arg0, u8 *arg1, f32 *arg2) {
    s32 i;

    for (i = 0; i < 12; i++) {
        ((s32 *)arg0)[i] = ((s32 *)arg1)[i];
    }
    ((f32 *)(arg0 + 0x30))[0] = ((f32 *)(arg1 + 0x30))[0] + arg2[0];
    ((f32 *)(arg0 + 0x30))[1] = ((f32 *)(arg1 + 0x30))[1] + arg2[1];
    ((f32 *)(arg0 + 0x30))[2] = ((f32 *)(arg1 + 0x30))[2] + arg2[2];
    ((s32 *)(arg0 + 0x30))[3] = ((s32 *)(arg1 + 0x30))[3];
}
