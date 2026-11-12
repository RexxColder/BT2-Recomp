#include "common.h"

/* GUESS arity: a0 is passed through to func_00211288 (not written before the call) */
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217488(s32 arg0);
extern s32 D_00387930;

f32 func_0020C1E8(u32 arg0) {
    f32 temp_f1;
    s32 temp_v0_2;
    u8 *temp_v0;

    if (D_00387930 != 0 && arg0 < 2U) {
        temp_v0 = (u8 *)func_00211288((s32)arg0);
        if (func_00211310((s32)temp_v0, 0xF, 0x40) != 0) {
            temp_v0_2 = func_00217488((s32)temp_v0);
            if (temp_v0_2 >= 0xB2 || temp_v0_2 < 0xAF) {
                temp_f1 = *(f32 *)(temp_v0 + 0x9B0);
                if (*(f32 *)(temp_v0 + 0xA1C) < temp_f1) {
                    return temp_f1;
                }
                return *(f32 *)(temp_v0 + 0xA1C);
            }
            return *(f32 *)(temp_v0 + 0xA30);
        }
    }
    return 0.0f;
}
