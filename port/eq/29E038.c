#include "common.h"

f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
void func_00312490(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00312638(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00312680(f32 farg0, u8 *arg1, u8 *arg2);
f32 sceVu0InnerProduct(u8 *arg0, u8 *arg1);

void Vec3_RotateAxis(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0) {
    s32 sp[4];
    s32 sp10[4];
    s32 sp20[4];
    f32 temp_f20;
    f32 temp_f21;

    temp_f21 = cosf(farg0);
    temp_f20 = sinf(farg0);
    func_00312680(temp_f21, (u8 *)sp, arg1);
    func_00312490((u8 *)sp10, arg2, arg1);
    func_00312680(temp_f20, (u8 *)sp10, (u8 *)sp10);
    func_00312680(sceVu0InnerProduct(arg2, arg1) * (1.0f - temp_f21), (u8 *)sp20, arg2);
    func_00312638(arg0, (u8 *)sp, (u8 *)sp10);
    func_00312638(arg0, arg0, (u8 *)sp20);
    *(f32 *)(arg0 + 0xC) = *(f32 *)(arg1 + 0xC);
}
