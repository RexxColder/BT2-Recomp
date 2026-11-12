#include "m2c_macros.h"

f32 BtlOpp_GetDistance();                     /* extern */
s32 BtlPad_Test48();                 /* extern */
s32 BtlPad_Test4C();                 /* extern */
f32 func_0020DB08();                 /* extern */
M2C_UNK func_0020FC38();             /* extern */
s32 func_00211310();        /* extern */
s32 func_00211328();        /* extern */
M2C_UNK func_002113C0(); /* extern */

// Battle per-frame pad/state check: sets/clears counter at 0x1018, toggles flags via func_002113C0 (sub-state bits), handles distance-based flag set.
void func_0020DBC0(void *arg0) {
    f32 temp_f20;
    s32 var_v0;

    if (func_00211310(arg0, 1, 0x10000) != 0) {
        if (func_00211310(arg0, 0, 1) != 0) {
            if ((BtlPad_Test48(arg0, 0xD) != 0) && (BtlPad_Test4C(arg0, 6) != 0)) {
                M2C_FIELD(arg0, s32 *, 0x1018) = 1;
            }
            if (BtlPad_Test48(arg0, 6) != 0) {
                var_v0 = M2C_FIELD(arg0, s32 *, 0x1018);
                if (var_v0 > 0) {
                    var_v0 += 1;
                    M2C_FIELD(arg0, s32 *, 0x1018) = var_v0;
                }
                if (var_v0 >= 3) {
                    func_002113C0(arg0, 0, 1, 0);
                }
            } else {
                goto block_10;
            }
        } else {
block_10:
            M2C_FIELD(arg0, s32 *, 0x1018) = 0;
        }
    }
    if (M2C_FIELD(arg0, s32 *, 0xB8C) > 0) {
        func_002113C0(arg0, 0, 1, 0);
        if (func_00211310(arg0, 0xA, 0x200) != 0) {
            func_002113C0(arg0, 0, 0x10000, 1);
        }
    }
    if (func_00211310(arg0, 0xA, 0x80) != 0) {
        func_002113C0(arg0, 0, 1, 0);
    }
    func_002113C0(arg0, 1, 1, 0);
    if ((func_00211310(arg0, 1, 0x800) == 0) && (func_00211310(arg0, 0, 0x400000) != 0) && (M2C_FIELD(arg0, s32 *, 0xB8C) <= 0) && (M2C_FIELD(arg0, s32 *, 0xB48) < 3) && (func_00211310(arg0, 0xA, 0x80) == 0)) {
        temp_f20 = func_0020DB08(arg0, 0);
        if (BtlOpp_GetDistance(arg0) < temp_f20) {
            func_002113C0(arg0, 1, 1, 1);
            func_002113C0(arg0, 0, 1, 1);
        }
    }
    func_002113C0(arg0, 1, 0x800, 0);
    if (func_00211310(arg0, 0, 1) == 0) {
        if (func_00211328(arg0, 0, 1) != 0) {
            func_0020FC38(arg0, 0x2D);
        }
    }
    if (func_00211310(arg0, 0, 1) != 0) {
        func_002113C0(arg0, 0, 0x10000, 0);
    }
}
