#include "m2c_macros.h"

M2C_UNK EftSurf_Animate(s32);                       /* extern */
M2C_UNK EftSurf_UpdateTextures(s32);                /* extern */
s32 func_00276D00();                                /* extern */
extern void *D_003876A0;
extern void *gEftSurf;

void func_00136270(void) {
    if (!(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 0x100)) {
        EftSurf_Animate(M2C_FIELD(gEftSurf, s32 *, 4));
    }
    if (func_00276D00() == 0) {
        EftSurf_UpdateTextures(M2C_FIELD(gEftSurf, s32 *, 4));
    }
}
