#include "m2c_macros.h"

M2C_UNK func_0011E688();                            /* extern */
M2C_UNK func_0011E6C0();                            /* extern */
void *func_0028BAA8(s32);                           /* extern */
M2C_UNK memset(void *, M2C_UNK, s32);               /* extern */
extern void *D_003876A0;
extern void *D_003876FC;

void func_0011E868(s32 arg0) {
    void *temp_v0;

    if (!(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 2)) {
        temp_v0 = func_0028BAA8(0x14);
        D_003876FC = temp_v0;
        memset(temp_v0, 0, 0x14);
        M2C_FIELD(D_003876FC, s32 *, 4) = arg0;
        M2C_FIELD(D_003876FC, void **, 0) = func_0028BAA8(M2C_FIELD(D_003876FC, s32 *, 4) * 0x11F0);
        memset(M2C_FIELD(D_003876FC, void **, 0), 0, M2C_FIELD(D_003876FC, s32 *, 4) * 0x11F0);
        func_0011E688();
        func_0011E6C0();
    }
}
