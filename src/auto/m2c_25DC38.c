#include "m2c_macros.h"

s32 func_0025CC80(void *);                          /* extern */
M2C_UNK func_0025D190(void *);                      /* extern */
s32 func_002696C0();                                /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_0025DC38(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 var_s2;
    s32 var_s3;
    void *var_s0;
    void *var_s1;

    var_s0 = arg1;
    var_s1 = arg0;
    var_s2 = arg2;
    var_s3 = arg3 & 0xFF;
    memset(var_s0, 0, 0x1520);
    M2C_FIELD(var_s0, void **, 0) = var_s1;
    var_s1 = var_s0 + 0xE90;
    M2C_FIELD(var_s0, s32 *, 0x10) = func_0025CC80(var_s0);
    M2C_FIELD(var_s0, s32 *, 0xC) = 1;
    M2C_FIELD(var_s0, s32 *, 0x18) = var_s2;
    func_0025D190(var_s0);
    if (var_s3 != 0) {
        M2C_FIELD(var_s0, s32 *, 0xE90) = func_002696C0();
    }
}
