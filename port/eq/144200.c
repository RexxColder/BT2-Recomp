#include "common.h"

void Vec3_Normalize(s32 arg0, s32 arg1);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
f32 atan2f(f32 arg0, f32 arg1);

void func_00144200(u8 *arg0, s32 *arg1) {
    f32 sp[4];
    u8 *temp_s0;

    temp_s0 = arg0 + 0x20;
    func_00208DE8(*arg1, (s32)temp_s0, 3);
    Vec3_Normalize((s32)sp, (s32)temp_s0);
    *(f32 *)(arg0 + 0x10) = atan2f(sp[0], sp[2]);
}
