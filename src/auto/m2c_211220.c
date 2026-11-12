#include "m2c_macros.h"

f32 BtlUtil_WrapAngle(f32);                         /* extern */

void func_00211220(void *arg0, void *arg1) {
    M2C_FIELD(arg0, f32 *, 0) = BtlUtil_WrapAngle(M2C_FIELD(arg1, f32 *, 0));
    M2C_FIELD(arg0, f32 *, 4) = BtlUtil_WrapAngle(M2C_FIELD(arg1, f32 *, 4));
    M2C_FIELD(arg0, f32 *, 8) = BtlUtil_WrapAngle(M2C_FIELD(arg1, f32 *, 8));
}
