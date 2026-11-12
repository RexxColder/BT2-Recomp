#include "common.h"

extern s32 D_00387930;

/* GUESS arity: func_00211270 is called with a0 = arg0 the first time and a stale a0 later; it is taken as no-arg. */
s32 func_00211270(void);
u8 *func_00211288(s32 arg0);
f32 sqrtf(f32 arg0);
u8 *BtlChar_GetPos(u8 *arg0);
void func_00312650(f32 *arg0, u8 *arg1, s32 arg2);
f32 sceVu0InnerProduct(f32 *arg0, f32 *arg1);
void BtlChar_SetVibration(u8 *arg0, f32 arg1, f32 arg2);
void BtlChar_SetSmallVibration(u8 *arg0, f32 arg1);

void func_0020D240(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 vec[4];
    s32 i;
    s32 cnt;
    u8 *s0;
    u8 *pos;
    f32 dot;
    f32 f1;
    f32 t;
    f32 f21;
    f32 f20;

    if (D_00387930 == 0) {
        return;
    }
    i = 0;
    for (;;) {
        cnt = func_00211270();
        if (!(i < cnt)) {
            break;
        }
        s0 = func_00211288(i);
        pos = BtlChar_GetPos(s0);
        func_00312650(vec, pos, arg0);
        dot = sceVu0InnerProduct(vec, vec);
        f1 = sqrtf(dot);
        t = (f1 - arg1) / (arg2 - arg1);
        f21 = 1.0f - t;
        if (f21 >= 0.0f) {
            if (f21 > 1.0f) {
                f21 = 1.0f;
            }
            f20 = arg4 * f21;
            BtlChar_SetVibration(s0, arg3 * f21, f20);
            if (0.5f < f21) {
                BtlChar_SetSmallVibration(s0, f20);
            }
        }
        i++;
    }
}
