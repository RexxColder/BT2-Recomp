#include "m2c_macros.h"

extern s32 D_00387AE0;
extern s32 D_00387AE4;
extern void *gOt;
extern s32 gOtFirst;

void func_002791C8(s32 arg0, s32 arg1) {
    M2C_FIELD(gOt, s32 *, 0x28) = arg0;
    M2C_FIELD(gOt, s32 *, 0) = (s32) (arg0 + arg1);
    M2C_FIELD(gOt, s32 *, 4) = (s32) (M2C_FIELD(gOt, s32 *, 0) + 0x10);
    M2C_FIELD(gOt, s32 *, 8) = (s32) (M2C_FIELD(gOt, s32 *, 4) + 0x10000);
    gOtFirst = M2C_FIELD(gOt, s32 *, 0);
    D_00387AE0 = M2C_FIELD(gOt, s32 *, 4);
    D_00387AE4 = M2C_FIELD(gOt, s32 *, 8);
}
