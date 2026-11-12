#include "common.h"

void func_001F4288(s32 a0, s32 a1, s32 a2, s32 a3, f32 a4, f32 a5, s32 a6);
void func_001F42B8(s32 arg0, s32 arg1);
void func_00147FE8(s32 *arg0);
extern f32 D_00385774;

void func_001F5768(s32 pad, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[8];

    sp[0] = 0;
    sp[1] = 2;
    sp[2] = 0;
    *(f32 *)&sp[3] = 0.5f;
    func_001F4288(arg1, arg1, arg2, arg3, 100.0f, D_00385774, 0);
    func_001F42B8(arg1, 1);
    func_00147FE8(sp);
}
