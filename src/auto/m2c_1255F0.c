#include "m2c_macros.h"

s32 BtlObjAnim_QueryEvent(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
s32 BtlObjXf_Update(void *);                        /* extern */
s32 func_00126040();                                /* extern */
f32 func_001FA308(void *);                          /* extern */
s32 func_001FA3A8(s32);                             /* extern */
s32 func_0020A7D0(s32);                             /* extern */
s32 func_00210DD8(s32);                             /* extern */
void *func_00211288(s32);                           /* extern */
s32 func_00211310(void *, M2C_UNK, M2C_UNK);        /* extern */

void func_001255F0(s32 arg0) {
    f32 temp_f20;
    f32 temp_f20_2;
    void *temp_s1;
    void *temp_v0;
    void *temp_v0_2;

    temp_s1 = arg0 + 0x10A0;
    temp_v0 = func_00211288(func_00210DD8(func_00126040(arg0)));
    M2C_FIELD(temp_s1, u8 *, 0x104) = 0U;
    M2C_FIELD(temp_s1, s8 *, 0x105) = 0;
    if ((func_001FA3A8(BtlObjXf_Update(temp_v0)) & 0x400) && (!(func_001FA3A8(BtlObjXf_Update(temp_v0)) & 0x2000) || (temp_v0_2 = M2C_FIELD(temp_v0, void **, 0x1530), (M2C_FIELD(temp_v0_2, s8 *, 0xD7D) != ~M2C_FIELD(temp_v0_2, s8 *, 0xD7C))))) {
        M2C_FIELD(temp_s1, u8 *, 0x104) = 1U;
    }
    if (func_001FA3A8(BtlObjXf_Update(temp_v0)) & 0x8000) {
        M2C_FIELD(temp_s1, s8 *, 0x105) = 1;
    }
    if (func_0020A7D0(M2C_FIELD(temp_v0, s32 *, 0x1534)) != 0) {
        M2C_FIELD(temp_s1, s8 *, 0x105) = 1;
    }
    if (func_00211310(temp_v0, 5, 0x800) != 0) {
        M2C_FIELD(temp_s1, s8 *, 0x105) = 1;
    }
    if (M2C_FIELD(temp_s1, u8 *, 0x104) != 0) {
        temp_f20 = (f32) BtlObjAnim_QueryEvent(M2C_FIELD(temp_v0, void **, 0x1530), 1, 0, 0);
        temp_f20_2 = (temp_f20 - func_001FA308(temp_v0)) * 0.5f;
        M2C_FIELD(temp_s1, f32 *, 0x100) = temp_f20_2;
        if (temp_f20_2 < -1.0f) {
            M2C_FIELD(temp_s1, f32 *, 0x100) = -1.0f;
        }
    } else {
        M2C_FIELD(temp_s1, f32 *, 0x100) = -1.0f;
    }
}
