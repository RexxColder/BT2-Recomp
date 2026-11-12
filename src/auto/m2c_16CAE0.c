#include "m2c_macros.h"

M2C_UNK Vec3_Add(void *, void *, void *);           /* extern */
M2C_UNK func_00129C28(void *, void *);              /* extern */
s32 func_0016CA38(s32);                             /* extern */
M2C_UNK func_00208DE8(s32, void *, s32);            /* extern */
s32 func_0020B3D0(s32);                             /* extern */

void func_0016CAE0(void *arg0, s32 arg1) {
    s32 *var_s1;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    void *var_s0;
    void *var_s2;

    var_s4 = arg1 & 0xFF;
    var_s0 = M2C_FIELD(arg0, void **, 0x38);
    var_s1 = M2C_FIELD(var_s0, s32 **, 0xB0);
    var_s2 = var_s0 + 0x80;
    var_s3 = func_0020B3D0(*var_s1);
    var_s5 = func_0016CA38(var_s3);
    func_0016CA38(*var_s1);
    if (M2C_FIELD(var_s0, s32 *, 0x10) == 0) {
        func_00208DE8(*var_s1, var_s0 + 0x50, M2C_FIELD(var_s0, s32 *, 8));
        func_00129C28(var_s0 + 0x90, var_s2);
        if (var_s4 == 0) {
            Vec3_Add(var_s2, var_s2, var_s0 + 0xA0);
        } else {
            func_00208DE8(var_s3, var_s2, 3);
        }
        if (var_s5 & 0x40) {
            M2C_FIELD(var_s0, s32 *, 0x10) = 1;
        }
    }
}
