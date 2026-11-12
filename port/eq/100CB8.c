#include "common.h"

s32 func_0028BAA8(s32 arg0);
s32 func_002EB9B0(s32 arg0, s32 arg1);
void func_002EBB08(s32 arg0);
void func_002EC0C8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002EC6B0(s32 arg0);
s32 func_002EC990(s32 arg0);
void func_002EF218(void);
extern s32 D_0038768C;
extern s32 D_00387690;
extern s32 D_00387694;
extern s32 D_00387F20;
extern s32 D_00387F24;

s32 func_00100CB8(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 first;

    first = (arg0 < 0x33B2) ? D_00387F20 : D_00387F24;
    temp_v0 = func_002EB9B0(first, (arg0 < 0x33B2) ? arg0 : (arg0 - 0x33B2));
    D_0038768C = temp_v0;
    temp_v0_2 = func_002EC6B0(temp_v0);
    D_00387690 = temp_v0_2;
    temp_v0_3 = func_0028BAA8(temp_v0_2 << 11);
    D_00387694 = temp_v0_3;
    func_002EC0C8(D_0038768C, D_00387690, temp_v0_3);
    do {
        temp_s0 = func_002EC990(D_0038768C);
        func_002EF218();
    } while (temp_s0 != 3);
    func_002EBB08(D_0038768C);
    D_0038768C = 0;
    return D_00387694;
}
