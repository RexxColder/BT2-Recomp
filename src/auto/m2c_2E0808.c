#include "m2c_macros.h"

M2C_UNK StgSlot_Call06(s32);                        /* extern */

void func_002E0808(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (arg0 != NULL) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x3B4);
    }
    StgSlot_Call06(var_v0);
}
