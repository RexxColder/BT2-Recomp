#include "common.h"

extern u8 *D_003876A0;
extern f32 D_00386D08;

/* 0x00241088: arg1 in 2..4 selects a pointer at arg0+0x1538+4*arg1 (0 -> return). The 16-byte entry
 * (5*G->0xD4 + arg2) of that table gives arg3[0..2] and arg3[3] = 1.0; arg4 = {0, (entry.w / 180) * D_00386D08, 0, 0}. */
void func_00241088(s32 arg0, s32 arg1, s32 arg2, f32 *arg3, s32 *arg4) {
    f32 *e;
    s32 m;
    s32 p;

    if ((u32)(arg1 - 2) >= 3) {
        return;
    }
    p = *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x1538);
    if (p == 0) {
        return;
    }
    m = *(s32 *)(D_003876A0 + 0xD4);
    e = (f32 *)((u8 *)p + (((m << 2) + m + arg2) << 4));
    arg3[0] = e[0];
    arg3[1] = e[1];
    arg3[2] = e[2];
    arg3[3] = 1.0f;
    arg4[0] = 0;
    ((f32 *)arg4)[1] = (e[3] / 180.0f) * D_00386D08;
    arg4[2] = 0;
    arg4[3] = 0;
}
