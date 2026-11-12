#include "m2c_macros.h"

s32 BtlScene_IsTimeStopped();                       /* extern */
s32 func_00126698();                                /* extern */
f32 func_0020A1A8(M2C_UNK);                         /* extern */
extern void *D_003876A0;
extern void *D_003878E0;

void func_001DF4A8(void) {
    if (BtlScene_IsTimeStopped() == 0) {
        if (M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 2) {
            if (func_00126698() != 0) {
                M2C_FIELD(D_003878E0, s32 *, 8) = (s32) (M2C_FIELD(D_003878E0, s32 *, 8) | 8);
            } else {
                M2C_FIELD(D_003878E0, s32 *, 8) = (s32) (M2C_FIELD(D_003878E0, s32 *, 8) & ~8);
            }
        }
        M2C_FIELD(D_003878E0, f32 *, 0) = (f32) (func_0020A1A8(0) * 255.0f);
        M2C_FIELD(D_003878E0, f32 *, 4) = (f32) (func_0020A1A8(1) * 255.0f);
    }
}
