#include "m2c_macros.h"

s32 BtlCharApi_IsInTechnique(s32);                  /* extern */
s32 BtlMember_IsHealthEmpty_2127F8(void *);         /* extern */
s32 func_00203C58(void *, M2C_UNK);                 /* extern */
void *func_00211288(M2C_UNK);                       /* extern */
s32 func_00211310(void *, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK func_002113C0(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
s32 func_0023F440(void *);                          /* extern */

void func_00211028(void *arg0) {
    void *var_v0;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        var_v0 = func_00211288(1);
    } else {
        var_v0 = func_00211288(0);
    }
    func_002113C0(arg0, 0xA, -1, 0);
    if (func_00211310(var_v0, 9, 0x4000) != 0) {
        func_002113C0(arg0, 0xA, 1, 1);
    }
    if (func_00211310(var_v0, 1, 0x40) != 0) {
        func_002113C0(arg0, 0xA, 4, 1);
    }
    if (func_00211310(var_v0, 3, 0x800) != 0) {
        func_002113C0(arg0, 0xA, 8, 1);
    }
    if (BtlCharApi_IsInTechnique(M2C_FIELD(var_v0, s32 *, 0x1534)) != 0) {
        func_002113C0(arg0, 0xA, 0x10, 1);
    }
    if (func_0023F440(var_v0) == 4) {
        func_002113C0(arg0, 0xA, 0x20, 1);
    }
    if (BtlMember_IsHealthEmpty_2127F8(var_v0) != 0) {
        func_002113C0(arg0, 0xA, 0x40, 1);
    }
    if (func_00211310(var_v0, 1, 0x04000000) != 0) {
        func_002113C0(arg0, 0xA, 0x80, 1);
    }
    if (M2C_FIELD(var_v0, s32 *, 0xAF0) > 0) {
        func_002113C0(arg0, 0xA, 0x100, 1);
    }
    if (func_00203C58(var_v0, 0x40000) != 0) {
        func_002113C0(arg0, 0xA, 0x200, 1);
    }
}
