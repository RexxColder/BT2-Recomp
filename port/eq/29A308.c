#include "common.h"

extern f32 D_00387234;
extern f32 D_00387238;
f32 fabsf(f32 farg0);
f32 cosf(f32 farg0);
s32 func_003126C8(s32 arg0, void *arg1);
void Quat_FromAxisAngle(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);

void Quat_LimitAngle(s32 arg0, s32 arg1, f32 farg0) {
    f32 *src;

    src = (f32 *)arg1;
    if (D_00387234 <= fabsf(farg0)) {
        func_003126C8(arg0, (void *)arg1);
        return;
    }
    if (D_00387238 < fabsf(src[3])) {
        func_003126C8(arg0, (void *)arg1);
        return;
    }
    if (cosf(farg0 * 0.5f) < src[3]) {
        func_003126C8(arg0, (void *)arg1);
        return;
    }
    Quat_FromAxisAngle(arg0, src[0], src[1], src[2], farg0);
}
