#include "m2c_macros.h"

s32 BtlObjXf_Update(void *);                        /* extern */
s32 func_00125B98(void *);                          /* extern */
s32 func_00126040();                                /* extern */
f32 func_001FA318(void *);                          /* extern */
s32 func_00210DD8(s32);                             /* extern */
void *func_00211288(s32);                           /* extern */

void func_00125580(s32 arg0) {
    void *temp_s1;
    void *temp_v0;

    temp_s1 = arg0 + 0x10A0;
    temp_v0 = func_00211288(func_00210DD8(func_00126040(arg0)));
    M2C_FIELD(temp_s1, s32 *, 0x70) = func_00125B98(temp_v0);
    M2C_FIELD(temp_s1, s32 *, 0x74) = BtlObjXf_Update(temp_v0);
    M2C_FIELD(temp_s1, f32 *, 0x78) = func_001FA318(temp_v0);
    M2C_FIELD(temp_s1, s32 *, 0xF8) = (s32) M2C_FIELD(temp_v0, s32 *, 0x1510);
}
