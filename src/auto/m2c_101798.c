#include "m2c_macros.h"

M2C_UNK func_002F6230(s32, M2C_UNK);                /* extern */
extern s32 D_00387F00;
extern s32 D_00387F08;

void func_00101798(void) {
    s32 *var_s1;
    s32 temp_a0;
    s32 var_s0;

    var_s1 = &D_00387F00;
    var_s0 = 1;
    func_002F6230(D_00387F08, 0);
    do {
        temp_a0 = *var_s1;
        var_s1 += 1;
        var_s0 -= 1;
        func_002F6230(temp_a0, 0);
    } while (var_s0 >= 0);
}
