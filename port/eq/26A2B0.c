#include "common.h"

f32 func_0029DFD0(s32 arg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_00312680(s32 arg0, s32 arg1, f32 farg0);

void func_0026A2B0(u8 *arg0, f32 farg0, s32 arg1) {
    f32 temp_f0;
    u8 *temp_s0;

    temp_s0 = arg0 + 0x1500;
    if (!(farg0 <= 0.0f)) {
        if (func_0029DFD0((s32)temp_s0) < farg0) {
            func_00312638((s32)temp_s0, (s32)temp_s0, arg1);
            temp_f0 = func_0029DFD0((s32)temp_s0);
            if (farg0 < temp_f0) {
                func_00312680((s32)temp_s0, (s32)temp_s0, farg0 / temp_f0);
            }
        }
        *(u8 *)(arg0 + 0x1514) = 1;
    }
}
