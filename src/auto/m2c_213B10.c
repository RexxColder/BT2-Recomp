#include "m2c_macros.h"

void *BtlChar_GetPos();                       /* extern */
f32 BtlUtil_WrapAngle(f32);                         /* extern */
f32 cosf(f32);                                      /* extern */
s32 func_00211310();        /* extern */
f32 sinf(f32);                                      /* extern */
extern f32 D_00385A50;
extern f32 D_00385A54;
extern f32 D_00385A58;
extern f32 D_00385A5C;
extern f32 D_00385A60;
extern f32 D_00385A64;
extern f32 D_00385A68;
extern void *D_003876A0;

void func_00213B10(void *arg0) {
    f32 temp_f20;
    s32 temp_v0_3;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_v0;
    void *temp_v0_2;

    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0x60) = 0;
    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0x64) = 0;
    M2C_FIELD(BtlChar_GetPos(arg0), s32 *, 0x68) = 0;
    if (!(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 0x3800)) {
        if ((func_00211310(arg0, 0, 2) != 0) && (func_00211310(arg0, 1, 0x400) != 0)) {
            temp_s0 = BtlChar_GetPos(arg0);
            M2C_FIELD(temp_s0, f32 *, 0xC8) = BtlUtil_WrapAngle(M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8) + D_00385A50);
        } else {
            if (D_00385A54 < M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8)) {
                temp_s0_2 = BtlChar_GetPos(arg0);
                M2C_FIELD(temp_s0_2, f32 *, 0xC8) = (f32) (D_00385A58 - M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8));
            }
            if (M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8) < D_00385A5C) {
                temp_s0_3 = BtlChar_GetPos(arg0);
                M2C_FIELD(temp_s0_3, f32 *, 0xC8) = (f32) (D_00385A60 - M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8));
            }
            if (M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8) > 0.0f) {
                temp_v0 = BtlChar_GetPos(arg0);
                M2C_FIELD(temp_v0, f32 *, 0xC8) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xC8) - D_00385A64);
                if (M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8) < 0.0f) {
                    M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8) = 0.0f;
                }
            }
            if (M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8) < 0.0f) {
                temp_v0_2 = BtlChar_GetPos(arg0);
                M2C_FIELD(temp_v0_2, f32 *, 0xC8) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 0xC8) + D_00385A68);
                if (M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8) > 0.0f) {
                    M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8) = 0.0f;
                }
            }
        }
        temp_s0_4 = BtlChar_GetPos(arg0);
        M2C_FIELD(temp_s0_4, f32 *, 0x64) = sinf(M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC8));
        temp_v0_3 = M2C_FIELD(arg0, s32 *, 0xB7C);
        if (temp_v0_3 > 0) {
            temp_f20 = ((f32) (temp_v0_3 & 1) - 0.5f) * 0.5f;
            temp_s0_5 = BtlChar_GetPos(arg0);
            M2C_FIELD(temp_s0_5, f32 *, 0x60) = (f32) (-cosf(M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xB4)) * temp_f20);
            temp_s0_6 = BtlChar_GetPos(arg0);
            M2C_FIELD(temp_s0_6, f32 *, 0x68) = (f32) (sinf(M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xB4)) * temp_f20);
        }
    }
}
