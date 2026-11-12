#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_001DD220(void *, void *);              /* extern */
M2C_UNK func_001DD2E0(void *);                      /* extern */
extern void *D_003876A0;

void func_001DDA10(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    if (!(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 0x100)) {
        func_001DD2E0(temp_s0);
    }
    if (M2C_FIELD(temp_s0, s32 *, 0x40) & 4) {
        BtlTask_SetDead(arg0);
        return;
    }
    func_001DD220(temp_s0, temp_s0);
}
