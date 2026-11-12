#include "common.h"

void Quat_Inverse(f32 *arg0, f32 *arg1);
void Quat_Mul(f32 *arg0, f32 *arg1, f32 *arg2);

void func_0029A278(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 sp[4];
    f32 tmp[4];

    Quat_Inverse(sp, arg2);
    Quat_Mul(tmp, arg1, sp);
    Quat_Mul(tmp, arg2, tmp);
    arg0[3] = tmp[3];
    arg0[2] = tmp[2];
    arg0[0] = tmp[0];
    arg0[1] = tmp[1];
}
