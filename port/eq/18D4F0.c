#include "common.h"

void Vec4_Set(f32 *out, f32 x, f32 y, f32 z, f32 w);
void Vu0Screen_StoreMtx(f32 *m);
s32 func_00126598(s32 arg0);
void func_0018D7C8(u8 *a0, f32 *a1, f32 *a2, f32 *a3, u8 *t0, s32 t1, u8 t2, s32 t3, s32 st0, s32 st8);

void func_0018D4F0(u8 *arg0, s32 arg1, s32 arg2) {
    f32 mtx[16];
    f32 v50[4];
    f32 v60[4];
    s32 flag = 0;
    u8 *s0;

    if (*(u16 *)(arg0 + 0x56) & 0x200) {
        if (func_00126598(*(s32 *)(arg0 + 0x50)) == 0) {
            return;
        }
        flag = 1;
    }

    s0 = *(u8 **)(arg0 + 0x158);
    while (s0 != NULL) {
        if (arg2 & (1 << s0[0xF0])) {
            if (*(f32 *)(s0 + 0xB0) < 0.0f) {
                Vec4_Set(v50, 0.984375f, 0.015625f, 0.984375f, 0.984375f);
                Vec4_Set(v60, 0.015625f, 0.015625f, 0.015625f, 0.984375f);
            } else {
                Vec4_Set(v50, 0.015625f, 0.015625f, 0.015625f, 0.984375f);
                Vec4_Set(v60, 0.984375f, 0.015625f, 0.984375f, 0.984375f);
            }
        } else {
            Vec4_Set(v50, 0.015625f, 0.015625f, 0.015625f, 0.984375f);
            Vec4_Set(v60, 0.984375f, 0.015625f, 0.984375f, 0.984375f);
        }
        Vu0Screen_StoreMtx(mtx);
        func_0018D7C8(s0 + 0x70, mtx, v50, v60, s0 + 0x40, arg1, s0[0xF0], 0, flag, *(s32 *)arg0);
        s0 = *(u8 **)(s0 + 0xF4);
    }
}
