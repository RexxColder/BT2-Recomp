#include "common.h"

void *strcat(s8 *arg0, s8 *arg1, s32 arg2, s8 *arg3);
s32 strlen(s8 *arg0, s32 arg1);
extern s8 D_00356D10[] __attribute__((section(".data")));
extern s8 D_0037E4B0[] __attribute__((section(".data")));

void func_002FEBB8(s8 *arg0, s8 arg2, s8 *arg3) {
    s8 *var_a3;
    s8 var_a2;
    s8 temp_v0;
    s8 temp_v1;

    var_a2 = arg2;
    var_a3 = arg3;
    if (arg0 == NULL) {
        D_00356D10[0] = 0;
    } else {
        temp_v1 = *arg0;
        if ((temp_v1 != 0x2F) && (temp_v1 != 0x5C)) {
            var_a3 = D_00356D10;
            var_a2 = D_0037E4B0[1];
            D_00356D10[0] = D_0037E4B0[0];
            D_00356D10[1] = var_a2;
        } else {
            D_00356D10[0] = 0;
        }
        strcat(D_00356D10, arg0, var_a2, var_a3);
        temp_v0 = arg0[((s32 (*)(s8 *))strlen)(arg0) - 1];
        if ((temp_v0 == 0x2F) || (temp_v0 == 0x5C)) {
            D_00356D10[strlen(D_00356D10, 0x5C) - 1] = 0;
        }
    }
}
