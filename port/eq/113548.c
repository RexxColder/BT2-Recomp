#include "common.h"

void func_0029D488(f32 *arg0, f32 farg0);

/* f12 (the rotation angle) passes through to func_0029D488 */
void func_00113548(s32 arg0, f32 farg0) {
    f32 sp[8];

    sp[0] = *(f32 *)((u8 *)arg0 + 0);
    sp[1] = *(f32 *)((u8 *)arg0 + 4);
    sp[2] = 0.0f;
    sp[3] = 1.0f;
    func_0029D488(sp, farg0);
}
