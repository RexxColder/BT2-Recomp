#include "m2c_macros.h"

s32 BtlObjXf_Update();                        /* extern */
s32 func_001FA3A8();                             /* extern */
s32 func_00203C58();                 /* extern */
M2C_UNK func_00203C88();             /* extern */
s32 func_00211310();        /* extern */
M2C_UNK func_002113C0(); /* extern */
s32 func_00212320();                          /* extern */
s32 func_002411E0();                     /* extern */
s32 func_00241250();                     /* extern */

// Clears three flag bits via func_002113C0, runs BtlObjXf_Update/func_001FA3A8 check, sets field 0x1510/0xA34, and masks field 0xAF0 of object at 0x1530.
void func_00236310(void *arg0) {
    s32 temp_v0;
    void *temp_a0;
    void *temp_v1;

    func_002113C0(arg0, 0xC, 0x1000, 0);
    func_002113C0(arg0, 0xC, 0x2000, 0);
    func_002113C0(arg0, 0xC, 0x4000, 0);
    if (!(func_001FA3A8(BtlObjXf_Update(arg0)) & 0x10)) {
        temp_v0 = func_00241250(arg0, func_00212320(arg0));
        M2C_FIELD(arg0, s32 *, 0x1510) = 0;
        M2C_FIELD(arg0, s32 *, 0xA34) = temp_v0;
        func_00203C88(arg0, 0x08000000);
        if (func_00203C58(arg0, 0x10000000) != 0) {
            func_002113C0(arg0, 0, 0x4000, 1);
        }
        if ((func_002411E0(arg0, func_00212320(arg0)) & 0x20000) && (func_00211310(arg0, 8, 1) == 0)) {
            temp_v1 = M2C_FIELD(arg0, void **, 0x1530);
            M2C_FIELD(temp_v1, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xAF0) & 0xFF00FFFF);
            temp_a0 = M2C_FIELD(arg0, void **, 0x1530);
            M2C_FIELD(temp_a0, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xAF0) | 0x10000);
        }
    }
}
