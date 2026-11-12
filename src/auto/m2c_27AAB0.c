#include "m2c_macros.h"

M2C_UNK func_0028BB60(s32);                         /* extern */
extern void *D_003876A0;
extern s32 D_00387AE8;

void func_0027AAB0(void *arg0) {
    if (M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 3) {
        func_0028BB60(M2C_FIELD(arg0, s32 *, 0));
        func_0028BB60(M2C_FIELD(arg0, s32 *, 4));
        D_00387AE8 = 0;
    }
}
