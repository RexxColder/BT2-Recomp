#include "common.h"

void func_001F4288(s32 arg0);
void func_00147FE8(s32 arg0);

void func_001F4E28(s32 arg0, s32 arg1) {
    s32 sp[8];

    sp[0] = 1;
    sp[1] = 1;
    sp[2] = 0;
    *(f32 *)&sp[3] = 1.0f;
    *(f32 *)&sp[4] = 10.0f;
    sp[5] = 0;
    sp[6] = 0;
    func_001F4288(arg1);
    func_00147FE8((s32)sp);
}
