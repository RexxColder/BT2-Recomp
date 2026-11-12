#include "common.h"

void func_001F4288(s32 a0, s32 a1, s32 a2, s32 a3, f32 a4, s32 a5, s32 a6);
void func_00147FE8(s32 *arg0);

void func_001F4BA0(s32 pad, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[8];

    sp[0] = 0;
    sp[1] = 0;
    sp[2] = 0;
    *(f32 *)&sp[3] = 1.0f;
    *(f32 *)&sp[4] = 1.0f;
    sp[5] = 0;
    sp[6] = 0;
    func_001F4288(arg1, arg1, arg2, arg3, 1.0f, 0, 0);
    func_00147FE8(sp);
}
