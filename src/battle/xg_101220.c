#include "m2c_macros.h"

s32 func_0028BAA8(s32);                             /* extern */
s32 func_002EB648(s32, s32);                         /* extern */
M2C_UNK func_002EBB08(s32);                         /* extern */
M2C_UNK func_002EC0C8(s32, s32, s32);               /* extern */
s32 func_002EC6B0(s32);                             /* extern */
s32 func_002EC990(s32);                             /* extern */
M2C_UNK func_002EF218();                            /* extern */
extern s32 D_0038768C;
extern s32 D_00387690;
extern s32 D_00387694;

/* Sets up a battle sub-object, polls func_002EC990 until it reports 3, then tears it down. Returns D_00387694. */
s32 func_00101220(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = func_002EB648(arg0, 0);
    D_0038768C = temp_v0;
    temp_v0_2 = func_002EC6B0(temp_v0);
    D_00387690 = temp_v0_2;
    temp_v0_3 = func_0028BAA8(temp_v0_2 << 0xB);
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
