#include "common.h"

s32 func_00101578(s32 arg0, s32 arg1, s32 arg2);
void func_002F52A8(s32 arg0, s32 arg1);
void func_002F7040(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387F08;
extern s32 D_00387F20;
extern s32 D_00387F24;

void func_001017F0(s32 arg0, s32 arg1) {
    s32 var_a1;
    s32 temp_v0;
    s32 temp_t0;

    if ((u32)(arg0 - 0xBDE) >= 0x27ECU && (u32)(arg0 - 0x3C1B) >= 0xCU) {
        temp_t0 = func_00101578(arg1, 1, arg1);
        func_002F52A8(D_00387F08, temp_t0);
    } else {
        var_a1 = ((u32)(arg0 - 0xBDE) < 0x27ECU) ? 1 : 0;
        temp_t0 = func_00101578(arg1, var_a1, arg1);
        func_002F52A8(D_00387F08, temp_t0);
    }
    temp_v0 = arg0 < 0x33B2;
    func_002F7040(D_00387F08, temp_v0 ? D_00387F20 : D_00387F24, temp_v0 ? arg0 : (arg0 - 0x33B2));
}
