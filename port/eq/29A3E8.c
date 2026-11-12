#include "common.h"

f32 func_00299DA0(s32 arg0, s32 arg1);
void func_003126C8(s32 arg0, s32 arg1);

void func_0029A3E8(s32 arg0, s32 arg1) {
    f32 sp[4];
    f32 temp_f1;

    temp_f1 = 1.0f / func_00299DA0(arg0, arg1);
    sp[0] = *(f32 *)(arg1 + 0x0) * temp_f1;
    sp[1] = *(f32 *)(arg1 + 0x4) * temp_f1;
    sp[2] = *(f32 *)(arg1 + 0x8) * temp_f1;
    sp[3] = *(f32 *)(arg1 + 0xC) * temp_f1;
    func_003126C8(arg0, (s32)sp);
}
