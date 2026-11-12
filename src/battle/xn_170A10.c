#include "m2c_macros.h"

void ColSphere_Set(s32, void *, f32);            /* extern */
void *EftHit_GetNew();                              /* extern */
M2C_UNK EftHit_SetShapeSpheres();   /* extern */
M2C_UNK func_00127128();                      /* extern */
s32 func_00127F88();                             /* extern */
f32 func_00152958();                             /* extern */

void func_00170A10(void *arg0) {
    f32 temp_f20;
    s32 temp_s2;
    s32 temp_s3;
    s64 temp_a0;
    void *temp_s0;
    void *temp_s1;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    temp_s1 = EftHit_GetNew();
    temp_f20 = M2C_FIELD(temp_s0, f32 *, 0x1C) * func_00152958(temp_s0 + 0xB4);
    M2C_FIELD(temp_s1, s64 *, 0x10) = (s64) M2C_FIELD(temp_s0, s64 *, 0x70);
    M2C_FIELD(temp_s1, s64 *, 0x18) = (s64) M2C_FIELD(temp_s0, s64 *, 0x78);
    M2C_FIELD(temp_s1, s64 *, 0x20) = (s64) M2C_FIELD(temp_s0, s64 *, 0x80);
    M2C_FIELD(temp_s1, s64 *, 0x28) = (s64) M2C_FIELD(temp_s0, s64 *, 0x88);
    M2C_FIELD(temp_s1, s64 *, 0x30) = (s64) M2C_FIELD(temp_s0, s64 *, 0x90);
    M2C_FIELD(temp_s1, s64 *, 0x38) = (s64) M2C_FIELD(temp_s0, s64 *, 0x98);
    M2C_FIELD(temp_s1, s64 *, 0x40) = (s64) M2C_FIELD(temp_s0, s64 *, 0xA0);
    temp_a0 = M2C_FIELD(temp_s0, s64 *, 0xA8);
    M2C_FIELD(temp_s1, void **, 0x60) = arg0;
    M2C_FIELD(temp_s1, s64 *, 0x48) = temp_a0;
    M2C_FIELD(temp_s1, s32 *, 0x64) = (s32) M2C_FIELD(temp_s0, s32 *, 0xB0);
    temp_s3 = func_00127F88(temp_a0);
    temp_s2 = func_00127F88();
    ColSphere_Set(temp_s3, temp_s0 + 0x80, temp_f20);
    ColSphere_Set(temp_s2, temp_s0 + 0x90, temp_f20);
    EftHit_SetShapeSpheres(temp_s1, temp_s3, temp_s2);
    func_00127128(temp_s1);
}
