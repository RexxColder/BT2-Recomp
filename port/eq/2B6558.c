#include "common.h"

extern void func_002B8178(s32 arg0, s32 arg1, s32 arg2);

/* 0x002B6558: func_002B8178(0, 0x1B, cvt.w.s(*arg0)) then func_002B8178(0, 7, 1). The float to int conversion is
 * cvt.w.s, which truncates toward zero (saturating). */
void func_002B6558(f32 *arg0) {
    f32 x = arg0[0];
    s32 t = (s32)x;

    func_002B8178(0, 0x1B, t);
    func_002B8178(0, 7, 1);
}
