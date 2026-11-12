#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_001804A0(void *, void *);              /* extern */
M2C_UNK func_00180500(f32, void *);                 /* extern */
M2C_UNK func_00180580(void *, s32);                 /* extern */

void func_00181990(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    func_00180500(M2C_FIELD(temp_s0, f32 *, 0xB0), temp_s0);
    func_001804A0(temp_s0, temp_s0 + 0xA0);
    if (M2C_FIELD(temp_s0, s32 *, 0xB8) & 2) {
        func_00180580(temp_s0, M2C_FIELD(temp_s0, s32 *, 0xB4));
    }
    if (M2C_FIELD(temp_s0, s32 *, 0xB8) & 4) {
        BtlTask_SetDead(arg0);
    }
}
