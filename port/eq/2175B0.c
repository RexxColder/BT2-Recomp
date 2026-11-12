#include "common.h"

s32 BtlPad_Test48(s32 arg0, s32 arg1);
f32 func_00207E80(s32 arg0);
f32 func_00207E88(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);

f32 func_002175B0(s32 arg0) {
    f32 temp_f20;
    f32 temp_f0;

    if (BtlPad_Test48(arg0, 8) == 0) {
        return 0.0f;
    }
    temp_f20 = func_00207E80(arg0);
    temp_f0 = func_00207E88(arg0);
    return BtlUtil_WrapAngle(atan2f(temp_f20, -temp_f0) + *(f32 *)(arg0 + 0x150));
}
