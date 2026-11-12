#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_002B1DD0(s32 arg0);
void func_00209018(s32 arg0, s32 arg1, s32 arg2);
f32 func_0029DFD0(s32 arg0);
s32 func_00312680(f32 farg0, s32 arg1, s32 arg2);
s32 func_003126C8(s32 arg0, s32 arg1);
void sceVu0Normalize(s32 arg0, s32 arg1);
extern f32 D_00385960;
extern s32 D_00387930;
extern s32 D_00387E18;

/* object (arg0 < 2 with D_00387930): arg1 = BtlChar_GetPos(func_00211288(arg0)) + 0x30 (tail call);
 * else with D_00387E18 and arg0 < 3: normalize arg1 into func_002B1DD0(arg0) + 0x130; else func_00209018(arg0, arg1, 0)
 * and, when D_00385960 < 1 / length of arg1, scale arg1 by 1 / length (tail call) */
void func_00208BE0(u32 arg0, s32 arg1) {
    f32 temp_f0;
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        func_003126C8(arg1, BtlChar_GetPos(func_00211288(arg0)) + 0x30);
    } else if ((D_00387E18 != 0) && (arg0 < 3U)) {
        sceVu0Normalize(arg1, func_002B1DD0(arg0) + 0x130);
    } else {
        func_00209018(arg0, arg1, 0);
        temp_f0 = func_0029DFD0(arg1);
        if (D_00385960 < temp_f0) {
            func_00312680(1.0f / temp_f0, arg1, arg1);
        }
    }
}
