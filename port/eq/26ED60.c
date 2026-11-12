#include "common.h"

void func_00270B40(s32 arg0, s32 *arg1, s32 arg2);
void func_00270438(s32 arg0, s32 *arg1, u8 *arg2);

#define W(p, off) (*(s32 *)((p) + (off)))
#define F(p, off) (*(f32 *)((p) + (off)))

void func_0026ED60(u8 *arg0, s32 *arg1, u8 *arg2, f32 *arg3, f32 *arg4, f32 arg5, f32 arg6) {
    u8 sp[0x14];
    s32 i;
    s32 a;
    f32 f0;
    f32 f1;
    f32 lim;

    if (arg1[0] < 0) {
        return;
    }
    for (i = 0; i < 0x14; i++) {
        sp[i] = arg2[i];
    }

    if (arg3 != NULL) {
        f0 = *arg3;
        a = (s32)f0;
        f1 = f0 + arg5;
        W(sp, 0) += a;
        W(sp, 8) += a;
        if (arg5 < 0.0f) {
            *arg3 = f1;
            if (f1 < 0.0f) {
                *arg3 = f1 + (f32)W(arg2, 8);
            }
        } else {
            lim = (f32)W(arg2, 8);
            if (lim <= f1) {
                *arg3 = f1 - lim;
            }
        }
    }

    if (arg4 != NULL) {
        f0 = *arg4;
        a = (s32)f0;
        f1 = f0 + arg6;
        W(sp, 4) += a;
        W(sp, 0xC) += a;
        if (arg6 < 0.0f) {
            *arg4 = f1;
            if (f1 < 0.0f) {
                *arg4 = f1 + (f32)W(arg2, 0xC);
            }
        } else {
            lim = (f32)W(arg2, 0xC);
            if (lim <= f1) {
                *arg4 = f1 - lim;
            }
        }
    }

    func_00270B40(W(arg0, 0x1C), arg1, 0x100);
    func_00270438(W(arg0, 0x1C), arg1, sp);
}
