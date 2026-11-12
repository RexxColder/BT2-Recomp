#include "m2c_macros.h"

void *BtlChar_GetPos();                             /* extern */
f32 func_0029DFD0(s32);                             /* extern */
M2C_UNK func_00312638(void *, void *, s32);         /* extern */
M2C_UNK func_00312680(f32, s32, s32);               /* extern */
M2C_UNK func_003126C8(s32, M2C_UNK *);              /* extern */
extern M2C_UNK D_002C3630 __attribute__((section(".data")));
extern f32 D_00385AE0;

void func_00217128(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    f32 temp_f0;
    s32 temp_s1;
    void *temp_v0;

    temp_v0 = BtlChar_GetPos(r_a0);
    temp_s1 = temp_v0 + 0xA0;
    func_00312638(temp_v0, temp_v0, temp_s1);
    M2C_FIELD(temp_v0, f32 *, 0xC) = 1.0f;
    temp_f0 = func_0029DFD0(temp_s1);
    if (temp_f0 < D_00385AE0) {
        func_003126C8(temp_s1, &D_002C3630);
        return;
    }
    func_00312680((temp_f0 - D_00385AE0) / temp_f0, temp_s1, temp_s1);
}
