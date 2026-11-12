#include "common.h"

f32 sinf(f32 farg0);
f32 cosf(f32 farg0);
s32 func_00312680(s32 arg0, s32 arg1, f32 farg0);
void func_0020E440(s32 arg0, s32 arg1);

/* 0x0020E4B0(obj, a, b) (a in f12, b in f13): v = (sin a, 0, cos a, 0) on the stack; func_00312680(v, v, b);
 * func_0020E440(obj, v). */
void func_0020E4B0(u8 *arg0, f32 arg1, f32 arg2) {
    f32 v[4];

    v[0] = sinf(arg1);
    v[1] = 0.0f;
    v[2] = cosf(arg1);
    v[3] = 0.0f;
    func_00312680((s32)v, (s32)v, arg2);
    func_0020E440((s32)arg0, (s32)v);
}
