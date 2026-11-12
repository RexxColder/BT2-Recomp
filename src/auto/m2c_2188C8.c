#include "m2c_macros.h"

M2C_UNK func_001FA360(f32, void *);                 /* extern */
f32 func_0023FCA8();                                /* extern */
f32 func_0023FCB8(void *);                          /* extern */
extern f32 D_00385B3C;

void func_002188C8(void *arg0) {
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f21;

    temp_f20 = (f32) M2C_FIELD(arg0, s32 *, 0x9B4) / D_00385B3C;
    temp_f21 = func_0023FCA8(arg0); /* asm 0x2188F8: a0 untouched */
    temp_f20_2 = temp_f20 * temp_f20;
    func_001FA360(2.0f * (((1.0f - temp_f20_2) * temp_f21) + (temp_f20_2 * func_0023FCB8(arg0))), arg0);
}
