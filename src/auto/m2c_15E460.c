#include "m2c_macros.h"

M2C_UNK BtlPool_Free(s32, s32);                     /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
M2C_UNK func_0014E968(void *);                      /* extern */

void func_0015E460(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    BtlPool_Free(BtlPool_GetCurrent(), M2C_FIELD(temp_s0, s32 *, 0x1E84));
    BtlPool_Free(BtlPool_GetCurrent(), M2C_FIELD(temp_s0, s32 *, 0x1E80));
    func_0014E968(temp_s0);
}
