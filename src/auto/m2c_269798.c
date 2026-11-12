#include "m2c_macros.h"

s32 BtlStage_IsReady();                             /* extern */
M2C_UNK ObjGs_AddDefaultEnv();                      /* extern */
M2C_UNK ObjShadow_AddTargetEnv();                   /* extern */
M2C_UNK func_00268C98(void *, void *);              /* extern */
M2C_UNK func_00268D50(void *, void *, f32);              /* extern */
M2C_UNK func_00268E30(void *, void *);              /* extern */
M2C_UNK func_00268F60(void *, void *);              /* extern */
s32 func_00276D80();                                /* extern */

/* f12 (farg0) is not written by the calls before func_00268D50 (func_00268C98 leaves it alone): passed through. */
void func_00269798(void *arg0, f32 farg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0xE90);
    if (BtlStage_IsReady() == 0) {
        return;
    }
    if (func_00276D80() == 1) {
        return;
    }
    if (temp_s0 == NULL) {
        return;
    }
    if (M2C_FIELD(temp_s0, s32 *, 0x10) == 0) {
        return;
    }
    ObjGs_AddDefaultEnv();
    func_00268C98(arg0, temp_s0);
    func_00268D50(arg0, temp_s0, farg0);
    func_00268E30(arg0, temp_s0);
    ObjShadow_AddTargetEnv();
    func_00268F60(arg0, temp_s0);
}
