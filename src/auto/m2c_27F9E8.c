#include "m2c_macros.h"

M2C_UNK func_0028BB60(s32);                         /* extern */
extern void *D_003876A0;
extern s32 D_00387AF8;

void func_0027F9E8(void) {
    if ((M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 3) && (D_00387AF8 != 0)) {
        func_0028BB60(D_00387AF8);
        D_00387AF8 = 0;
    }
}
