#include "m2c_macros.h"

M2C_UNK func_0025B5E8(void *, void *);              /* extern */
M2C_UNK func_0025BDD0(void *, void *, void *);      /* extern */
extern void *gBtlCam;

void func_0025BF28(void) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v1;
    void *temp_v0_x;

    temp_v1 = M2C_FIELD(gBtlCam, void **, 0x600);
    if (M2C_FIELD(temp_v1, u8 *, 0x2C0) != 0) {
        func_0025BDD0(temp_v1, temp_v1 + 0x2D0, temp_v1 + 0x280);
        temp_v0_x = gBtlCam;
        temp_a0 = M2C_FIELD(temp_v0_x, void **, 0x600);
        func_0025B5E8(temp_a0, temp_a0 + 0x2D0);
        return;
    }
    func_0025BDD0(temp_v1, temp_v1 + 0x270, temp_v1 + 0x280);
    temp_v0_x = gBtlCam;
    temp_a0_2 = M2C_FIELD(temp_v0_x, void **, 0x600);
    func_0025B5E8(temp_a0_2, temp_a0_2 + 0x270);
}
