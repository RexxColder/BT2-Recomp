#include "common.h"

void func_00100E78(s32 arg0, s32 arg1, s32 arg2);
s32 func_0028BAA8(s32 arg0);
s32 func_002EB9B0(s32 arg0, s32 arg1);
void func_002EBB08(s32 arg0);
s32 func_002EC6B0(s32 arg0);
extern s32 D_0038768C;
extern s32 D_00387690;
extern s32 D_00387698;
extern s32 D_00387F80[];
extern s32 D_00387F20[];

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 idx;
    s32 var_s0;

    if (arg2 != 0) {
        func_00100E78(arg0, arg1, arg2);
    }
    temp_v1 = arg0 < 0x33B2;
    idx = (temp_v1 != 0) ? 0 : 1;
    do {
        temp_v0 = func_002EB9B0(D_00387F20[idx], (temp_v1 == 0) ? (arg0 - 0x33B2) : arg0);
        D_0038768C = temp_v0;
    } while (temp_v0 == 0);
    var_s0 = arg1;
    temp_v0_2 = func_002EC6B0(temp_v0);
    D_00387690 = temp_v0_2;
    if (arg1 == 0) {
        var_s0 = func_0028BAA8(temp_v0_2 << 0xB);
    }
    func_002EBB08(D_0038768C);
    D_0038768C = 0;
    temp_v1_2 = D_00387698 + 1;
    D_00387F80[D_00387698] = D_00387690;
    D_00387698 = temp_v1_2 + 2;
    D_00387F80[temp_v1_2] = var_s0;
    D_00387F80[temp_v1_2 + 1] = arg0;
    return var_s0;
}
