#include "m2c_macros.h"

M2C_UNK ColBox_AddPoint(s32, f32 *);                /* extern */
M2C_UNK StgAabb_SetEmpty();                         /* extern */
M2C_UNK func_003126C8(f32 *, void *);               /* extern */

void ColBounds_OfCapsule(s32 arg0, void *arg1) {
    s32 sp[4];
    f32 *var_s0;
    s32 var_s4;
    void *temp_s3;

    temp_s3 = arg1 + 0x10;
    var_s4 = 2;
    StgAabb_SetEmpty(arg0);
    var_s0 = sp;
    do {
        func_003126C8(sp, arg1);
        var_s4 -= 1;
        *var_s0 += M2C_FIELD(arg1, f32 *, 0x20);
        ColBox_AddPoint(arg0, sp);
        func_003126C8(sp, arg1);
        *var_s0 -= M2C_FIELD(arg1, f32 *, 0x20);
        ColBox_AddPoint(arg0, sp);
        func_003126C8(sp, temp_s3);
        *var_s0 += M2C_FIELD(arg1, f32 *, 0x20);
        ColBox_AddPoint(arg0, sp);
        func_003126C8(sp, temp_s3);
        *var_s0 -= M2C_FIELD(arg1, f32 *, 0x20);
        ColBox_AddPoint(arg0, sp);
        var_s0 += 1;
    } while (var_s4 >= 0);
}
