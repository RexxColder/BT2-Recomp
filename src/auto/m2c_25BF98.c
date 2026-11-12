#include "m2c_macros.h"

M2C_UNK func_0025BB38(void *, s32);                 /* extern */
M2C_UNK func_0025BF28();                            /* extern */
extern void *D_003876A0;
extern void *gBtlCam;

void func_0025BF98(s32 arg0) {
    void *temp_a0;
    void *temp_a1;

    if (M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 2) {
        temp_a1 = M2C_FIELD(gBtlCam, void **, 0x600);
        if (arg0 != M2C_FIELD(temp_a1, s32 *, 0x258)) {
            M2C_FIELD(temp_a1, s32 *, 0x258) = arg0;
            if (arg0 == 1) {
                temp_a0 = M2C_FIELD(gBtlCam, void **, 0x600);
                func_0025BB38(temp_a0, M2C_FIELD(temp_a0, s32 *, 0x250) == 0);
            } else {
                func_0025BB38(M2C_FIELD(gBtlCam, void **, 0x600), 0);
            }
            func_0025BF28();
        }
    }
}
