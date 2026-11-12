#include "common.h"

void func_0029C8C0(s32 arg0);

/* 0x00113598: builds the vector (arg0[0], arg0[1], 0, 1.0f) in a local 16-byte buffer and passes its address to
 * func_0029C8C0. */
void func_00113598(f32 *arg0) {
    f32 v[8];

    v[0] = arg0[0];
    v[1] = arg0[1];
    *(s32 *)&v[2] = 0;
    v[3] = 1.0f;
    func_0029C8C0((s32)v);
}
